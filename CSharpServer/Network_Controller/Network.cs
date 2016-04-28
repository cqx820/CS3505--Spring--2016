using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Runtime.Remoting.Messaging;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Network_Controller
{

    /// <summary>
    /// A static class containing the Network controllers, including the connection, send, and receive 
    /// methods.
    /// </summary>
    /// <authors>Wesley Oates and Simon Redman</authors>
    /// <date>Nov 17, 2015</date>
    public static class Network
    {
        //Since this whole class is static, there is no hugely intelligent way to change this on the go
        private static System.Text.UTF8Encoding encoding = new System.Text.UTF8Encoding();

        /// <summary>
        /// We are sending 1KB at a time
        /// </summary>
        public const int PACKET_SIZE = 1024;
        //private static int SEND_TIMEOUT = 500;

        ///// <summary>
        ///// Semaphores which make sure multi-packet sends don't get interleaved with new sends
        ///// </summary>
        //public static Dictionary<string, Semaphore> SendsInProgress
        //{
        //    get;
        //    private set;
        //}

        /// <summary>
        /// Delegate describing the function to be called for a successful connection
        /// </summary>
        public delegate void ConnectionCallBack(NetworkState state);

        /// <summary>
        /// Attempts to connect to a server with the given hostname
        /// </summary>
        /// <param name="callBack">Function to call when a connection is made</param>
        /// <param name="hostName">hostname:port to connect to</param>
        public static Socket ConnectToServer(ConnectionCallBack callBack, string hostName)
        {
            //Unpack the name and port from the host name.
            string serverName = hostName.Split(':')[0];
            int port = int.Parse(hostName.Split(':')[1]);

            //Create the socket.
            IPAddress serverAddress;
            if (!IPAddress.TryParse(serverName, out serverAddress))
            {
                IPHostEntry hostEntry = Dns.GetHostEntry(serverName);
                serverAddress = hostEntry.AddressList[0];
            }
            IPEndPoint ipEndpoint = new IPEndPoint(serverAddress, port);
            Socket socket = new Socket(ipEndpoint.AddressFamily, SocketType.Stream, ProtocolType.Tcp);

            // Machnination which will be passed around within this class ferrying data
            NetworkState state = new NetworkState(callBack, socket);
            //Begins the connection, but does not wait for it to complete
            socket.BeginConnect(ipEndpoint.Address, port, ConnectedToServer, state);
            return socket;
        }


        /// <summary>
        /// Callback method which is called by the OS when the connection is established.
        /// Or, apparently, when the connection fails
        /// </summary>        
        public static void ConnectedToServer(IAsyncResult ar)
        {
            NetworkState nstate = (NetworkState)ar.AsyncState;
            //nstate.CurrentAsyncResult = ar;
            //nstate.ID = nstate.GetHashCode();
            if (nstate.Socket.Connected)
            {
                nstate.ConnectionState = NetworkState.ConnectionStates.CONNECTED;
            }
            else
            {
                nstate.ConnectionState = NetworkState.ConnectionStates.DISCONNECTED;
            }

            nstate.CallBack(nstate);
            if (nstate.ConnectionState == NetworkState.ConnectionStates.CONNECTED)
            {
                nstate.CurrentAsyncResult = nstate.Socket.BeginReceive(nstate.Buffer, 0, nstate.Buffer.Length, SocketFlags.None, ReceiveCallback, ar);
            }
        }

        /// <summary>
        /// Method to be called by the OS when data is received
        /// Checks if 0 data has been received, which indicates
        /// the connection has been terminated, and acts appropriately
        /// </summary>
        public static void ReceiveCallback(IAsyncResult ar)
        {
            NetworkState nstate;
            if (!(ar.AsyncState is NetworkState))
            {
                // For some reason, state comes in as an
                // OverlappedAsyncResult. I don't know why, but in
                // every situation I've seen, the ConnectAsyncResult
                // we want is just one level down.
                nstate = (NetworkState)((IAsyncResult)ar.AsyncState).AsyncState;
            }
            else
            {
                // Hopefully there are no more weird situations...
                nstate = (NetworkState)ar.AsyncState;
            }
            if (ar != nstate.CurrentAsyncResult)
            {
                //return;
            }

            int amountOfDataReceived = 0;

            //Check if the socket has been closed
            if (!nstate.Socket.Connected)
            {
                nstate.ConnectionState = NetworkState.ConnectionStates.DISCONNECTED;
                nstate.CallBack(nstate);
                return;
            }

            try
            {
                amountOfDataReceived = nstate.Socket.EndReceive(ar);
            } catch (SocketException e)
            {
                Console.WriteLine("Network.ReceiveCallback: SocketException: " + e.Message);
            }
            //Check if we have received no data
            if (amountOfDataReceived == 0)
            {
                //nstate.Socket.EndConnect(ar);
                //nstate.Socket.Close();
                nstate.ConnectionState = NetworkState.ConnectionStates.DISCONNECTED;
            }
            else
            {
                nstate.ConnectionState = NetworkState.ConnectionStates.HAS_DATA;
            }
            nstate.CallBack(nstate);
        }

        /// <summary>
        /// Function to be called when the client wants more data
        /// </summary>
        public static void RequestMoreData(NetworkState state)
        {
            if (state.ConnectionState == NetworkState.ConnectionStates.DISCONNECTED)
            {
                throw new NetworkState.NetworkStateException("Socket is disconnected.");
            }
            else if (state.ConnectionState == NetworkState.ConnectionStates.HAS_DATA)
            {
                throw new NetworkState.NetworkStateException("Socket already has data in the buffer.");
            }

            if (state.Socket == null)
            {
                return;
            }
            state.CurrentAsyncResult = state.Socket.BeginReceive(state.Buffer, 0, state.Buffer.Length, SocketFlags.None, ReceiveCallback, state);
        }

        /// <summary>
        /// Begins a send of the given data on the given socket.
        /// </summary>
        /// <param name="socket">The socket to send stuff on.</param>
        /// <param name="data">The stuff to send.</param>
        /// <param name="sendCallback">The method to invoke after sending.  If this argument is omitted, 
        /// it will call the standard Network.SendCallBack method.  If it is not omitted, it is the 
        /// responsibility of the programmer to ensure Socket.EndSend() is called.</param>
        public static void Send(Socket socket, string data, AsyncCallback sendCallback = null)
        {
            //Console.WriteLine("Sending: " + data);
            byte[] outgoingBuffer = encoding.GetBytes(data);
            if (sendCallback == null) sendCallback = SendCallBack;
            socket.BeginSend(outgoingBuffer, 0, outgoingBuffer.Length, SocketFlags.None, sendCallback, socket);
        }
        /// <summary>
        /// The standard callback that is invoked after a send is executed.  IT calls EndSend();
        /// </summary>
        /// <param name="ar"></param>
        public static void SendCallBack(IAsyncResult ar)
        {
            Socket socket = (Socket)ar.AsyncState;
            socket.EndSend(ar);
        }

        /*
        /// <summary>
        /// Sends the data through the given socket. Calls SendCallBack if it
        /// is unable to send all data at once
        /// </summary>
        public static void Send(Socket socket, string data)
        {
            byte[] outgoingBuffer = encoding.GetBytes(data);
            //Console.WriteLine("Network.Send : Amount of data is " + outgoingBuffer.Length);
            int length = (outgoingBuffer.Length < PACKET_SIZE) ? outgoingBuffer.Length : PACKET_SIZE;
            // I need both the data and the socket in the SendCallBack, so simply passing both
            Tuple<Socket, byte[]> toPass = new Tuple<Socket, byte[]>(socket, outgoingBuffer);
            //Creates a semaphore using the socket, which we unlock in the callback
            //when we are done sending all of this string's data
            Semaphore sendingSemaphore;
            if (SendsInProgress == null) SendsInProgress = new Dictionary<string, Semaphore>();
            //lock (SendsInProgress)
            //{
                if (!SendsInProgress.TryGetValue(socket.RemoteEndPoint.ToString(), out sendingSemaphore))
                {
                    if (!Semaphore.TryOpenExisting(socket.RemoteEndPoint.ToString(), out sendingSemaphore))
                    {
                        sendingSemaphore = new Semaphore(0, 1, socket.RemoteEndPoint.ToString());
                        sendingSemaphore.Release();
                    }
                    SendsInProgress.Add(socket.RemoteEndPoint.ToString(), sendingSemaphore);
                }
            //}
            //if (sendingSemaphore.WaitOne(SEND_TIMEOUT))
            //{
            sendingSemaphore.WaitOne();
                socket.BeginSend(outgoingBuffer, 0, length, SocketFlags.None, SendCallBack, toPass);
            //} else
            //{
            //    Send(socket, data);
            //}
        }

        /// <summary>
        /// Method to be called when sending has completed.
        /// Checks that the whole message has been sent, and send more if it has not.
        /// </summary>
        public static void SendCallBack(IAsyncResult ar)
        {
            Tuple<Socket, byte[]> toPass = (Tuple<Socket, byte[]>)ar.AsyncState;
            Socket socket = toPass.Item1;
            byte[] outgoingBuffer = toPass.Item2;

            if (outgoingBuffer.Length > PACKET_SIZE)
            {
                outgoingBuffer = outgoingBuffer.SubArray(PACKET_SIZE,
                                outgoingBuffer.Length - PACKET_SIZE);
                toPass = new Tuple<Socket, byte[]>(socket, outgoingBuffer);
                int length = (outgoingBuffer.Length < PACKET_SIZE) ? outgoingBuffer.Length : PACKET_SIZE;
                socket.BeginSend(outgoingBuffer, 0, length, SocketFlags.None, SendCallBack, toPass);
            } else
            {
                // If getting the sendingSemaphore fails, things will go directly to hell, so probably best to crash
                Semaphore sendingSemaphore = SendsInProgress[socket.RemoteEndPoint.ToString()];
                int debug = sendingSemaphore.Release();
                //Console.WriteLine("Network.SendCallBack : Exited Semaphore held by " + debug + " clients");
            }
        }
        */

        /// <summary>
        /// Returns a shallow copy of the given portion of the given array
        /// Idea from http://stackoverflow.com/questions/943635
        /// </summary>
        public static T[] SubArray<T>(this T[] data, int startIndex, int length)
        {
            T[] toReturn = new T[length];
            Array.Copy(data, startIndex, toReturn, 0, length);
            return toReturn;
        }


        #region Network server methods


        /// <summary>
        /// Starts the server listening for activity on all network interfaces
        /// </summary>
        /// <param name="callback">The method to call when a new client has connected</param>
        /// <param name="port">The port on which to listen.</param>
        public static void Server_Awaiting_Client_Loop(ConnectionCallBack callback, int port)
        {

            //Establish the local address and endpoint.
            IPAddress localIpAddress = IPAddress.IPv6Any;
            IPEndPoint localEndPoint = new IPEndPoint(localIpAddress, port);

            //Create the socket that will listen.
            Socket listener =
                new Socket(AddressFamily.InterNetworkV6, SocketType.Stream, ProtocolType.Tcp);
            //WWO:  should this really be IPv6Only?  ARen't we likely to get IPv4 data come is as well?
            //SER: the IPv6Only property is being set to false...
            listener.SetSocketOption(SocketOptionLevel.IPv6, SocketOptionName.IPv6Only, false);

            //Create the state object that will be passed to the new client thread.
            NetworkState state = new NetworkState(callback, listener);
            state.ConnectionState = NetworkState.ConnectionStates.DISCONNECTED;
            state.Buffer = new byte[PACKET_SIZE];

            //Bind the endpoint to the socket, and kick off the listening chain.
            listener.Bind(localEndPoint);
            //WWO:  What is the backlog for?  Is this a limit to the number of players that can come in?
            //SER: My understanding is the backlog is the number of requests we can have before we deal with them
            listener.Listen(100);
            listener.BeginAccept(Accept_A_New_Client, state);
        }

        /// <summary>
        /// Method called when the server receives a connection. It adds the
        /// newly connected socket to the NetworkState, then calls the callback
        /// specified in ServerAwaitingConnectionLoop
        /// </summary>        
        public static void Accept_A_New_Client(IAsyncResult ar)
        {
            NetworkState state = (NetworkState)ar.AsyncState;

            Socket oldListener = state.Socket;
            ConnectionCallBack serverAwaitingClientCallback = state.CallBack;
            int oldPort = ((IPEndPoint)oldListener.LocalEndPoint).Port;

            // WWO:  Why the distinction between a new socket and the old socket?  What if the old socket already has data ready to go?
            /* SER: It doesn't. This is how you accept a connection from a
               client. I think the idea is that this new socket is on a new 
               port, so that the original port (11000) is still free to accept
               connections.
            */
            Socket newConnection = state.Socket.EndAccept(ar);
            state.ConnectionState = NetworkState.ConnectionStates.CONNECTED;
            state.Socket = newConnection;

            // DONE: Not disposing of the old socket would be a resource leak; and would not let us re-use the port, but I don't know the proper procedure.
            //WWO:  I think this is good as far as the procedure, I just don't understand the reasoning behind doing this.
            /*SER: I have changed the TODO to DONE, since I think it is. You 
              have to dispose of the old socket so that port 11000 is free
              again. The easier solution would be for ServerAwaitingClientLoop
              to accept a socket, but that would violate the specification.
            */
            oldListener.Close();
            oldListener.Dispose();

            state.CallBack(state);
           
            // WWO:  shouldn't this be a call to newConnection.BeginReceive() ?
            /*SER: Whatever program is using our library is in charge of using
              the sockets; maybe they don't want data yet. That's why we update
              the state object and toss it to the callback
            */
            Server_Awaiting_Client_Loop(serverAwaitingClientCallback, oldPort);

        }
        #endregion


    }
}
