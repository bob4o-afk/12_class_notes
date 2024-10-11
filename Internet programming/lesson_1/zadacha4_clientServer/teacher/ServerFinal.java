package lesson_1.zadacha4_clientServer.teacher;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class ServerFinal {
    public static void main(String[] args) {
        System.out.println("Hello World.I am Server!");
        try (ServerSocket serverSocket = new ServerSocket(9708)) {
            System.out.println("Server is listening on port 9708...");
            boolean exit = false;
            while (!exit) {

                try (Socket clientSocket = serverSocket.accept()) {
                    System.out.println("Client is connected!");

                    BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
                    String receivedMessage = in.readLine();
                    System.out.println("Received message from client: " + receivedMessage);


                    PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);
                    out.println("Server response: " + receivedMessage);

                    if (receivedMessage.equalsIgnoreCase("exit")) {
                        out.println("Exitting serve...");
                        System.out.println("Received command for closing the server.");
                        exit = true;
                    } else {
                        out.println("Received message from server is : " + receivedMessage);
                    }

                } catch (IOException e) {
                    System.out.println("Error while prcessing client request: " + e.getMessage());
                }
            }
        } catch (IOException e) {
            System.out.println("Error while starting the server: " + e.getMessage());
        }
    }
}

