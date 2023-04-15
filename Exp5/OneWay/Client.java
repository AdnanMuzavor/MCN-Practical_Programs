
// A Java program for a Client
import java.net.*;
import java.io.*;
import java.util.*;

public class Client {
    // initialize socket and input output streams
    private Socket socket = null;
    private DataInputStream input = null;
    private DataOutputStream out = null;
    private Scanner sc = null;

    // constructor to put ip address and port
    public Client(String address, int port) {

        // establish a connection
        try {

            socket = new Socket(address, port);

            System.out.println(socket);
            System.out.println("Connected");

            // takes input from terminal
            input = new DataInputStream(System.in);

            // sends output to the socket
            out = new DataOutputStream(socket.getOutputStream());

            sc = new Scanner(System.in);
        } catch (UnknownHostException u) {
            System.out.println(u);
        } catch (IOException i) {
            System.out.println(i);
        }

        // string to read message from input
        String line = "";

        // keep reading until "Over" is input
        while (!line.equalsIgnoreCase("Over")) {
            try {
                System.out.print("Enter the message to be sent to server: ");
                line = sc.nextLine();
                out.writeUTF(line);
            } catch (IOException i) {
                System.out.println(i);
            }
        }

        // close the connection
        try {
            input.close();
            out.close();
            socket.close();
        } catch (IOException i) {
            System.out.println(i);
        }
    }

    public static void main(String args[]) {

        new Client("localhost", 9999);
    }
}
