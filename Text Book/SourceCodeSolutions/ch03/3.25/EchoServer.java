/**
 * An echo server listening on port 6007. This server reads from the client
 * and echoes back the result. 
 *
 * Operating System Concepts - Ninth Edition
 * Copyright John Wiley & Sions - 2013
 */

import java.net.*;
import java.io.*;

public class  EchoServer
{
	public static final int DEFAULT_PORT = 6007;
    public static final int BUFFER_SIZE = 256;
    
    public static void process(Socket client) throws java.io.IOException {
		byte[] buffer = new byte[BUFFER_SIZE];
		InputStream  fromClient = null;
		OutputStream toClient = null;
		
		try {
			/**
			 * get the input and output streams associated with the socket.
			 */
			fromClient = new BufferedInputStream(client.getInputStream());
			toClient = new BufferedOutputStream(client.getOutputStream());
			int numBytes;
			
			/** continually loop until the client closes the connection */
			while ( (numBytes = fromClient.read(buffer)) != -1) {
				toClient.write(buffer,0,numBytes);
				toClient.flush();
			}
   		}
		catch (IOException ioe) {
			System.err.println(ioe);
		}
		finally {
			// close streams and socket
			if (fromClient != null)
				fromClient.close();
			if (toClient != null)
				toClient.close();
			if (client != null)
				client.close();
		}
	}

	
    public static void main(String[] args) throws IOException {
		ServerSocket sock = null;
		
		try {
			// establish the socket
			sock = new ServerSocket(DEFAULT_PORT);
			
			while (true) {
				/**
				 * now listen for connections */
				process(sock.accept());
			}
		}
		catch (IOException ioe) { }
		finally {
			if (sock != null)
				sock.close();
		}
	}
}
