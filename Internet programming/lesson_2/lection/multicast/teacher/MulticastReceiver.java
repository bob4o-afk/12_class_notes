package lesson_2.lection.multicast.teacher;

import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.MulticastSocket;

public class MulticastReceiver {
    public static void main(String[] args) {

        try (MulticastSocket socket = new MulticastSocket(9238)) {  // Must match the sender's port
            InetAddress group = InetAddress.getByName("224.0.0.1");
            socket.joinGroup(group);

            System.out.println("Waiting for multicast messages...");

            while (true) {
                byte[] buf = new byte[256];
                DatagramPacket packet = new DatagramPacket(buf, buf.length);
                socket.receive(packet);

                String received = new String(packet.getData(), 0, packet.getLength());
                System.out.println("Received: " + received);
            }
        } catch (Exception e) {
            System.err.println(e.getMessage());
        }
    }
}
