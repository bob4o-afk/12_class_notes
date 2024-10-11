package lesson_2.zadacha1.teacher;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class TCPServer {
    public static void main(String[] args) {
        try (ServerSocket serverSocket = new ServerSocket(9238)) {
            System.out.println("Server is started on port 9238...");
            while (true) {
                try (Socket clientSocket = serverSocket.accept()) {
                    // Handle the client connection in a separate thread
                    new Thread(new ClientHandler(clientSocket)).start();
                } catch (IOException e) {
                    System.err.println("Error handling client connection: " + e.getMessage());
                }
            }
        } catch (IOException e) {
            System.err.println("Error starting the server: " + e.getMessage());
        }
    }
}
