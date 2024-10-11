package lesson_2.zadacha1.teacher;

import java.io.IOException;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.Socket;
import java.util.Enumeration;

public class ClientHandler implements Runnable {
    private final Socket clientSocket;

    public ClientHandler(Socket clientSocket) {
        this.clientSocket = clientSocket;
    }

    @Override
    public void run() {
        try {
            // Get the client's IP address
            InetAddress clientAddress = clientSocket.getInetAddress();
            String clientIp = clientAddress.getHostAddress();
            System.out.println("IP of the client: " + clientIp);

            StringBuilder networkInfo = new StringBuilder();
            Enumeration<NetworkInterface> interfaces = NetworkInterface.getNetworkInterfaces();
            while (interfaces.hasMoreElements()) {
                NetworkInterface networkInterface = interfaces.nextElement();
                networkInfo.append("Interface: ").append(networkInterface.getDisplayName()).append("\n");

                Enumeration<InetAddress> inetAddresses = networkInterface.getInetAddresses();
                while (inetAddresses.hasMoreElements()) {
                    InetAddress inetAddress = inetAddresses.nextElement();
                    networkInfo.append("\tAddress: ").append(inetAddress.getHostAddress()).append("\n");
                }
            }

            // Send the client's IP and server network information
            PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);
            out.println("IP address of client: " + clientIp);
            out.println("NetworkAddressOfServer:\n" + networkInfo);

            // Close the connection after sending the information
            clientSocket.close();
        } catch (IOException e) {
            System.out.println("Error handling client: " + e.getMessage());
        }
    }
}
