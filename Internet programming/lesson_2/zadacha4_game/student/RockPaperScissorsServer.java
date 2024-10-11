package lesson_2.zadacha4_game.student;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;

public class RockPaperScissorsServer {
    public static void main(String[] args) throws SocketException {
        System.out.println("Starting the Game Server...");

        try (DatagramSocket socket = new DatagramSocket(12345)) {
            byte[] buffer = new byte[1024];

            while (true) {
                DatagramPacket receivedPacket = new DatagramPacket(buffer, buffer.length);
                socket.receive(receivedPacket);

                String clientChoice = new String(receivedPacket.getData(), 0, receivedPacket.getLength());
                System.out.println("Client chose: " + clientChoice);

                String result = getResult(clientChoice);

                byte[] responseBytes = result.getBytes();
                DatagramPacket responsePacket = new DatagramPacket(
                        responseBytes,
                        responseBytes.length,
                        receivedPacket.getAddress(),
                        receivedPacket.getPort()
                );
                socket.send(responsePacket);
            }
        } catch (Exception e) {
            System.err.println("Server error: " + e.getMessage());
        }
    }

    private static String getResult(String clientChoice) {
        String[] choices = {"Rock", "Scissors", "Paper"};
        String serverChoice = choices[(int) (Math.random() * 3)]; // Random server choice
        System.out.println("Server choice is: " + serverChoice);

        if (clientChoice.equalsIgnoreCase(serverChoice)) {
            return "Draw! Both of you chose " + clientChoice + ".";
        } else if (("Rock".equalsIgnoreCase(clientChoice) && "Scissors".equalsIgnoreCase(serverChoice)) ||
                ("Scissors".equalsIgnoreCase(clientChoice) && "Paper".equalsIgnoreCase(serverChoice)) ||
                ("Paper".equalsIgnoreCase(clientChoice) && "Rock".equalsIgnoreCase(serverChoice))) {
            return "You win! You chose " + clientChoice + ", and server chose " + serverChoice + ".";
        } else {
            return "You lose! You chose " + clientChoice + ", and server chose " + serverChoice + ".";
        }
    }
}
