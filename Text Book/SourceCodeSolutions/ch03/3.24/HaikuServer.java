/**
 * Haiku server listening to port 5575.
 *
 * A few example Haikus come from http://www.boche.net/technology_haiku.htm
 *
 * @author Gagne, Galvin, Silberschatz
 * Operating System Concepts  - Ninth Edition
 * Copyright John Wiley & Sons - 2013
 */
 
import java.net.*;
import java.io.*;

public class HaikuServer
{
	static final int PORT = 5575;

	private static final String[] haiku = { 
	"Java, Perl, Python \n are all so very perfect \n to write web-based apps.",
	"Odd bed fellows \n are Solaris and Linux \n who would have thunk it?",
	"A crash reduces \n your expensive computer \n to a simple stone.",
	"Hello World is the \n most famous computer code \n ever written in C",
	"Stay the patient course \n of little worth is your ire \n the network is down.",
	"Having been erased, \n the document you are seeking \n must now be retyped."
	};
                                                
	public static void main(String[] args) throws IOException {
		Socket client = null;
		ServerSocket sock = null;

		try {
			sock = new ServerSocket(PORT);
			// now listen for connections
			while (true) {
				client = sock.accept();

				// we have a connection
				PrintWriter pout = new PrintWriter(client.getOutputStream(), true);
				// write the haiku to the socket
				pout.println(haiku[(int)(java.lang.Math.random() * haiku.length)] );

				pout.close();
				client.close();
			}
		}
		catch (IOException ioe) {
				System.err.println(ioe);
		}
		finally {
			if (sock != null)
				sock.close();
			if (client != null)
				client.close();
		}
	}
}
