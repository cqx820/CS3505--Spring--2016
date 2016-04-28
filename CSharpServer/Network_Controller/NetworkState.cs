using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Runtime.Serialization;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using static Network_Controller.Network;

namespace Network_Controller
{
    /// <summary>
    /// State-storage which is passed around in the AgCubio.Network methods
    /// </summary>
    /// <authors>Wesley Oates and Simon Redman</authors>
    /// <date>Nov 17, 2015</date>
    public class NetworkState
    {
        /// <summary>
        /// Enum representing current state of the connection
        /// </summary>
        public enum ConnectionStates
        {
            /// <summary>
            /// The socket is in the connected state, with no data waiting to be read.
            /// </summary>
            CONNECTED,
            /// <summary>
            /// The socket is in the disconnected state.
            /// </summary>
            DISCONNECTED,
            /// <summary>
            /// The socket is in the connected state with data waiting to be read.
            /// </summary>
            HAS_DATA
        }

        /// <summary>
        /// Buffer storing data to do with this connection
        /// </summary>
        public byte[] Buffer { get; set; }

        /// <summary>
        /// The function to be called on a successful connection
        /// </summary>
        public ConnectionCallBack CallBack { get; set; }
        
        /// <summary>
        /// The socket being stored with this network communication
        /// </summary>
        public Socket Socket { get; set; }

        /// <summary>
        /// Stores the current state of the connection
        /// </summary>
        public ConnectionStates ConnectionState { get; set; }

        /// <summary>
        /// Stores the IAsyncResult passed when starting BeginReceive, so we 
        /// can pass it back if C# gives us useless shit
        /// </summary>
        public IAsyncResult CurrentAsyncResult { get; set; }


        /// <summary>
        /// An identification number used to identify the callback chain that is being used.  This is 
        /// useful for server applications, where multiple threads may be operating on multiple sockets 
        /// and the server needs a way to distinguish among clients.
        /// </summary>
        public int ID { get; set; }


        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="connectionCallBack">A function to be called on a successful connection</param>
        /// <param name="socket">Socket referring to this connection</param>
        /// <param name="id">The ID number of the callback chain to identify unique clients.</param>
        public NetworkState(ConnectionCallBack connectionCallBack, Socket socket, int id = 0)
        {
            this.CallBack = connectionCallBack;
            this.Socket = socket;
            this.Buffer = new byte[Network.PACKET_SIZE];
            this.ConnectionState = ConnectionStates.DISCONNECTED;
            this.ID = id;

            
        }

        /// <summary>
        /// Returns the hash of the string of this NetworkState's associated
        /// connection end point
        /// </summary>
        /// <returns></returns>
        public override int GetHashCode()
        {
            return this.ToString().GetHashCode();
        }

        /// <summary>
        /// Returns the details of this NetworkState's associated connection
        /// end point as a string
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            return this.Socket.RemoteEndPoint.ToString();
        }

        [Serializable]
        internal class NetworkStateException : Exception
        {
            //public NetworkStateException()
            //{
            //}

            public NetworkStateException(string message) : base(message)
            {
            }

            //public NetworkStateException(string message, Exception innerException) : base(message, innerException)
            //{
            //}

            //protected NetworkStateException(SerializationInfo info, StreamingContext context) : base(info, context)
            //{
            //}
        }
    }
}
