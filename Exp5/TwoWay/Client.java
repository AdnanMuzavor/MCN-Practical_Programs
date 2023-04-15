import java.net.*;
import java.io.*;
import java.util.*;
// class Client{
// public static void main(String args[])throws Exception{
//     //Socket listening to port 6666 to send message to server who also listens at same socket
// Socket s=new Socket("localhost",6666);
// DataInputStream din=new DataInputStream(s.getInputStream());
// DataOutputStream dout=new DataOutputStream(s.getOutputStream());
// Scanner sc=new Scanner(System.in);

// String str="",str2="";
// while(!str.equals("stop")){
// System.out.println("Enter message to be sent to server: ");
// str=sc.nextLine();
// dout.writeUTF(str);
// dout.flush();
// str2=din.readUTF();
// System.out.println("Server replied: --->  "+str2);
// }

// dout.close();
// s.close();
// sc.close();
// }}

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
            System.out.println("Connected to server");

            // read what server sends
            input = new DataInputStream(socket.getInputStream());

            // sends message to the server
            out = new DataOutputStream(socket.getOutputStream());
            // Take i/p from terminal
            sc = new Scanner(System.in);
        } catch (Exception e) {
            System.out.println("Client Exited");
        }

        // string to read message from input
        String ClientMessage = "", ServerMessage = "";
        sc = new Scanner(System.in);
        // keep reading until "Over" is input
        while (!ClientMessage.equals("Over") && !ServerMessage.equals("Over")) {
            try {
                System.out.println("Enter message to be sent to server: ");
                ClientMessage = sc.nextLine(); // Take line to be sent to server
                if (ClientMessage.equals("Over")) {
                    System.out.println("Client wants to leave!");

                }
                out.writeUTF(ClientMessage); // Send to server
                ServerMessage = input.readUTF(); // Receive message from server
                System.out.println("Server replied: --->  " + ServerMessage); // display it
            } catch (Exception e) {
                // System.out.println("AN____ E R R O R____OCCURRED: " + e);

            }
        }

        // close the connection
        try {
            input.close();
            out.close();
            socket.close();
            sc.close();
        } catch (IOException i) {
            System.out.println("Client exited");
        }
    }

    public static void main(String args[]) {

        new Client("localhost", 6666);
    }
}
