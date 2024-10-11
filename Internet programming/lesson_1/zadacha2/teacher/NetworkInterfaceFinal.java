package lesson_1.zadacha2.teacher;


import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.util.Enumeration;

public class NetworkInterfaceFinal {

    public static void main(String[] args) throws SocketException {
        try {
            // Get all network adresses
            Enumeration<NetworkInterface> interfaces = NetworkInterface.getNetworkInterfaces();

            // For all network interface traverse
            while (interfaces.hasMoreElements()) {
                NetworkInterface networkInterface = interfaces.nextElement();

                // Show the name of interface
                System.out.println("Interface: " + networkInterface.getName());
                System.out.println("Description: " + networkInterface.getDisplayName());

                // Show  MAC address
                byte[] mac = networkInterface.getHardwareAddress();
                if (mac != null) {
                    System.out.print("MAC address: ");
                    for (int i = 0; i < mac.length; i++) {
                        System.out.format("%02X%s", mac[i], (i < mac.length - 1) ? "-" : "");
                    }
                    System.out.println();
                } else {
                    System.out.println("MAC address: No information.");
                }

                // List IP addresses (и IPv4, и IPv6)
                Enumeration<InetAddress> inetAddresses = networkInterface.getInetAddresses();
                while (inetAddresses.hasMoreElements()) {
                    InetAddress inetAddress = inetAddresses.nextElement();
                    System.out.println("IP address: " + inetAddress.getHostAddress());
                }

                // Show if the Interface is active
                System.out.println("Interface is active: " + networkInterface.isUp());

                // show if support multicast
                System.out.println("Support multicast: " + networkInterface.supportsMulticast());

                // Show if loopback interface
                System.out.println("Loopback interface: " + networkInterface.isLoopback());

                System.out.println("---------------------------------------------------");
            }
        } catch (SocketException e) {
            System.out.println("Error when extraction Network interfaces: " + e.getMessage());
        }
    }
}

