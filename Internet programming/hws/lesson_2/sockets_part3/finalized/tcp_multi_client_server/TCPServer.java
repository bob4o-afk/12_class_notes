package lesson_2.sockets_part3.finalized.tcp_multi_client_server;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class TCPServer {
    public static void main(String[] args) {
        try {
            ServerSocket serverSocket = new ServerSocket(9238);
            System.out.println("Server is started on port 9238...");
            while (true) {
                Socket clientSocket = serverSocket.accept();

                new Thread(new ClientHandler(clientSocket)).start();
            }

        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
