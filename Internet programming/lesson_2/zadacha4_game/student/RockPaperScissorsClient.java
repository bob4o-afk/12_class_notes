package lesson_2.zadacha4_game.student;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.Scanner;

public class RockPaperScissorsClient {
    public static void main(String[] args) {
        String serverAddress = "localhost";
        int serverPort = 12345;

        try (DatagramSocket socket = new DatagramSocket(); Scanner scanner = new Scanner(System.in)) {
            while (true) {
                System.out.println("\n--- Choose Option ---");
                System.out.println("1. Rock");
                System.out.println("2. Scissors");
                System.out.println("3. Paper");
                System.out.println("4. Exit");
                System.out.print("Choose an option (1-4): ");

                String choice = scanner.nextLine();

                if (choice.equals("1")) {
                    sendMessage(socket, serverAddress, serverPort, "Rock");
                } else if (choice.equals("2")) {
                    sendMessage(socket, serverAddress, serverPort, "Scissors");
                } else if (choice.equals("3")) {
                    sendMessage(socket, serverAddress, serverPort, "Paper");
                } else if (choice.equals("4")) {
                    System.out.println("Exiting the game...");
                    break;
                } else {
                    System.out.println("Invalid choice. Try again!");
                    continue;
                }

                String serverResponse = receiveMessage(socket);
                System.out.println(serverResponse);
            }
        } catch (Exception e) {
            System.err.println("Client error: " + e.getMessage());
        }
    }

    private static void sendMessage(DatagramSocket socket, String serverAddress, int serverPort, String message) throws Exception {
        InetAddress address = InetAddress.getByName(serverAddress);
        byte[] messageBytes = message.getBytes(); // Convert the message to bytes

        DatagramPacket packet = new DatagramPacket(messageBytes, messageBytes.length, address, serverPort);
        socket.send(packet);
    }

    // Method for receiving a message from the server
    private static String receiveMessage(DatagramSocket socket) throws Exception {
        byte[] buffer = new byte[1024];

        DatagramPacket receivedPacket = new DatagramPacket(buffer, buffer.length);
        socket.receive(receivedPacket);

        return new String(receivedPacket.getData(), 0, receivedPacket.getLength());
    }
}
