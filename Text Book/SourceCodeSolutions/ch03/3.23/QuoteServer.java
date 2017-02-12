/**
 * Quote server listening to port 6017.
 *
 * @author Gagne, Galvin, Silberschatz
 * Operating System Concepts  - Ninth Edition
 * Copyright John Wiley & Sons - 2013
 */
 
import java.net.*;
import java.io.*;

public class QuoteServer
{
	static final int PORT = 6017;

	private static final String[] fortunes = { 
							"Buy Low and Sell High",
							"Eat Your Vegetables",
							"Good Fences Make Good Neighbors",
							"Never Underestimate Your Competition",
							"A Clean Camp is a Happy Camp",
							"Write tests before writing code.",
							"Do no evil."
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
				// write the Date to the socket
				pout.println(fortunes[(int)(java.lang.Math.random() * fortunes.length)] );

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
