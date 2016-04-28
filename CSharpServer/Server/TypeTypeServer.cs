using Network_Controller;
using System;
using System.Security.Cryptography;
using System.Text;
using System.Threading;

namespace Server
{
    class TypeTypeServer
    {
        const ushort PORT = 1337;
        const String SALT = "SuperSalt";

        //TEMPORARY MEMBERS UNTIL I DO A DATABASE
        string lastUsername = "";
        string lastPassword = "";

        public TypeTypeServer()
        {
            Network.Server_Awaiting_Client_Loop(ClientConnectedCallback, PORT);
        }

        protected void ClientConnectedCallback(NetworkState state)
        {
            state.CallBack = initialConnectionCallback;
            Network.RequestMoreData(state);
        }

        protected void initialConnectionCallback(NetworkState state)
        {
            SFMLPacket packet = new SFMLPacket(state.Buffer);
            state.Buffer = new byte[state.Buffer.Length];
            state.ConnectionState = NetworkState.ConnectionStates.CONNECTED;

            Thread.Sleep(500); // Wait 0.5 seconds to prevent brute-force log-in attempts

            if (packet.packetCode == 101 || packet.packetCode == 102)
            {
                if (packet.packetCode == 101) //Register request
                {
                    Console.WriteLine("Register Request");
                    String username = packet.ExtractString();
                    String realName = packet.ExtractString();
                    String email = packet.ExtractString();
                    String password = packet.ExtractString();
                    if (!registerRequest(username, password, email, realName))
                    {
                        Console.WriteLine("Unable to register new client");
                        Network.Send(state.Socket, "\u0000");
                        Thread.Sleep(5000); // Wait 5 seconds for the send to complete
                        state.Socket.Shutdown(System.Net.Sockets.SocketShutdown.Both);
                        state.Socket.Close();
                        return;
                    }
                }
                else if (packet.packetCode == 102) //Login request
                {
                    Console.WriteLine("Login Request");
                    String username = packet.ExtractString();
                    String password = packet.ExtractString();
                    if (!loginRequest(username, password))
                    {
                        Console.WriteLine("Invalid Login Attempt");
                        Network.Send(state.Socket, "\u0000");
                        Thread.Sleep(5000); // Wait 5 seconds for the send to complete
                        state.Socket.Shutdown(System.Net.Sockets.SocketShutdown.Both);
                        state.Socket.Close();
                        return;
                    }
                }
                Network.Send(state.Socket, "\u0001"); //Send success
                state.CallBack = DataReceivedCallback;
                Network.RequestMoreData(state);
            }
            else
            {
                Console.WriteLine("Illegal request from non logged in client");
                Network.Send(state.Socket, "\u0000");
                Thread.Sleep(5000); // Wait 5 seconds for the send to complete
                state.Socket.Shutdown(System.Net.Sockets.SocketShutdown.Both);
                state.Socket.Close();
            }
        }

        protected bool registerRequest(String username, String password, String email, String realName)
        {
            lastUsername = username;
            lastPassword = HashAndSalt(password);
            return true;
        }

        protected bool loginRequest(String username, String password)
        {
            password = HashAndSalt(password);
            if (username.Equals(lastUsername))
            {
                if (password.Equals(lastPassword))
                {
                    return true;
                }
            }
            return false;
        }

        protected void DataReceivedCallback(NetworkState state)
        {
            SFMLPacket incomingPacket = new SFMLPacket(state.Buffer);
            state.Buffer = new byte[state.Buffer.Length];
            state.ConnectionState = NetworkState.ConnectionStates.CONNECTED;

            foreach (String data in incomingPacket)
            {
                Console.WriteLine(data);
            }
        }


        /// <summary>
        /// Method from: https://msdn.microsoft.com/en-us/library/s02tk69a%28v=vs.110%29.aspx
        /// </summary>
        /// <param name="md5Hash"></param>
        /// <param name="input"></param>
        /// <returns></returns>
        static string HashAndSalt(string input)
        {
            using (SHA256 sha256Hash = SHA256.Create())
            {

                // Convert the input string to a byte array and compute the hash.
                byte[] data = sha256Hash.ComputeHash(Encoding.UTF8.GetBytes(input + SALT));

                // Create a new Stringbuilder to collect the bytes
                // and create a string.
                StringBuilder sBuilder = new StringBuilder();

                // Loop through each byte of the hashed data 
                // and format each one as a hexadecimal string.
                for (int i = 0; i < data.Length; i++)
                {
                    sBuilder.Append(data[i].ToString("x2"));
                }

                // Return the hexadecimal string.
                return sBuilder.ToString();
            }
        }
    }
}