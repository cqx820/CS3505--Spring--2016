using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Server
{
    class SFMLPacket
    {
        protected static System.Text.UTF8Encoding _Encoding = new System.Text.UTF8Encoding();

        public ushort packetCode { get; protected set; }
        protected LinkedList<String> storedStrings;

        public SFMLPacket()
        {
            storedStrings = new LinkedList<string>();
            packetCode = 0;
        }

        /// <summary>
        /// Parse the byte array into useful data
        /// </summary>
        /// <param name="data"></param>
        public SFMLPacket(byte[] data) : this()
        {
            int index = 0; //Used to keep track of where we are in the array
            int totalBytes = 0; //Used to keep track of how many bytes the packet thinks should exist

            int counter = 0; //Temporarily used to keep track of position within elements of a packet

            //First four bytes are the number of (remaining) bytes in this packet
            while (index < 4)
            {
                totalBytes += data[index];
                index++;
            }

            //The first byte is the number of bytes in this packet
            packetCode = data[index];
            index++;

            while (index < totalBytes + 4)
            {
                //Step 1: Read the number of bytes of the next string
                int startIndex = index;
                int numberOfBytes = 0;
                while (index < startIndex + 4)
                {
                    numberOfBytes += data[index];
                    index++;
                }

                //Step 2: Read that number of bytes into a string
                startIndex = index;
                byte[] thisElement = new byte[numberOfBytes];
                while (index < startIndex + numberOfBytes)
                {
                    thisElement[index - startIndex] = data[index];
                    index++;
                }
                storedStrings.AddLast(_Encoding.GetString(thisElement));
            }

        }

        public IEnumerator<String> GetEnumerator()
        {
            while (storedStrings.Count != 0)
            {
                yield return ExtractString();
            }
        }

        /// <summary>
        /// Pop and return the first string in the packet
        /// </summary>
        /// <returns></returns>
        public String ExtractString()
        {
            String toReturn = storedStrings.ElementAt(0);
            storedStrings.RemoveFirst();
            return toReturn;
        }

        /// <summary>
        /// Add a string to the packet
        /// </summary>
        /// <param name="toInsert"></param>
        public void InsertString(String toInsert)
        {
            storedStrings.AddLast(toInsert);
        }
    }
}
