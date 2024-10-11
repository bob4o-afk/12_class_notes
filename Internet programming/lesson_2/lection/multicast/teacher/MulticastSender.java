package lesson_2.lection.multicast.teacher;

import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.MulticastSocket;
import java.util.Scanner;

public class MulticastSender {
    public static void main(String[] args) {
        // 1. Create a MulticastSocket
        // 2. Create a DatagramPacket
        // 3. Send the packet
        try (MulticastSocket multicastSocket = new MulticastSocket()) {
            InetAddress group = InetAddress.getByName("224.0.0.1");  // Multicast group
            Scanner scanner = new Scanner(System.in);

            System.out.println("Enter messages to send to the multicast group. Type 'exit' to stop.");

            while (true) {

                System.out.print("Message to send: ");
                String message = scanner.nextLine();

                if ("exit".equalsIgnoreCase(message)) {
                    break;
                }

                byte[] data = message.getBytes();
                //send message to group
                DatagramPacket packet = new DatagramPacket(data, data.length, group, 9238);

                multicastSocket.send(packet);
                System.out.println("Message sent: " + message);
            }

        } catch (Exception e) {
            System.err.println(e.getMessage());
        }
    }
}
