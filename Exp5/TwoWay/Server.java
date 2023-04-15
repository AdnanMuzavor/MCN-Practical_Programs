
import java.net.*;
import java.io.*;
import java.util.*;

public class Server {

    // initialize socket and input stream
    private Socket socket = null;
    private ServerSocket server = null;
    private DataInputStream in = null; // To get ClientMessage
    private DataOutputStream out = null; // To write ServerMessage
    private Scanner sc = null; // To take server message as i/p

    // constructor with port
    public Server(int port) {
        // starts server and waits for a connection
        try {
            server = new ServerSocket(port);
            System.out.println("Server started");

            System.out.println("Waiting for a client ...");

            socket = server.accept();
            System.out.println("Client accepted");

            // Help us reading ClientMessage
            in = new DataInputStream(socket.getInputStream());
            // Help up sending ServerMessage to Client
            out = new DataOutputStream(socket.getOutputStream());

            String ClientMessage = "", ServerMessage = "";

            // reads message from client until "Over" is sent or server wants to over the
            // communication
            while (!ClientMessage.equalsIgnoreCase("Over") && !ServerMessage.equalsIgnoreCase("Over")
            
                ) {
                try {
                    ClientMessage = in.readUTF(); // Read what client sent
                    if (ClientMessage.equalsIgnoreCase("Over")) {
                        System.out.println("Client left!");
                        continue;
                    }
                    // Display what client sent
                    System.out.println("Client Says : " + ClientMessage);
                    // Take i/p the server message
                    System.out.println("Enter message to be sent to client: ");
                    sc = new Scanner(System.in);
                    ServerMessage = sc.nextLine();
                    // Send server message to the client via socket
                    out.writeUTF(ServerMessage);

                } catch (IOException e) {
                    System.out.println("Client left");
                }
            }
            System.out.println("Closing connection");

            // close connection
            socket.close();
            in.close();
            sc.close();
        } catch (IOException i) {
            System.out.println(i);
        }
    }

    public static void main(String args[]) {
        try {
            new Server(6668);
        } catch (Exception e) {
            System.out.println("Client has left");
        }

    }
}
