/**
 * Modified DateClient so that it requests a haiku
 * from the haiku server.
 *
 * @author Gagne, Galvin, Silberschatz
 * Operating System Concepts  - Ninth Edition
 * Copyright John Wiley & Sons - 2013
 */
 
import java.net.*;
import java.io.*;

public class HaikuClient
{
	static final int PORT  = 5575;
	static final String HOST = "127.0.0.1";
	public static void main(String[] args) throws IOException {
		InputStream in = null;
		BufferedReader bin = null;
		Socket sock = null;

		try {
			sock = new Socket(HOST,PORT);
			in = sock.getInputStream();
			bin = new BufferedReader(new InputStreamReader(in));

			String line;
			while( (line = bin.readLine()) != null)
				System.out.println(line);
		}
		catch (IOException ioe) {
				System.err.println(ioe);
		}
                finally {
                    sock.close();
                }
	}
}
