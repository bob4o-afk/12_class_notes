import java.net.InetAddress;
import java.net.InterfaceAddress;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Enumeration;

public class Main
{
    public static void main(String[] args) throws SocketException, UnknownHostException
    {

        // getNetworkInterfaces() returns a list of all interfaces
        // present in the system.
        ArrayList<NetworkInterface> interfaces = Collections.list(
                NetworkInterface.getNetworkInterfaces());

        System.out.println("Information about present Network Interfaces...\n");
        for (NetworkInterface iface : interfaces)
        {
            // isUp() method used for checking whether the interface in process
            // is up and running or not.
            if (iface.isUp())
            {

                // getName() method
                System.out.println("Interface Name: " + iface.getName());

                // getDisplayName() method
                System.out.println("Interface display name: " + iface.getDisplayName());

                // gethardwareaddress() method
                System.out.println("Hardware Address: " +
                        Arrays.toString(iface.getHardwareAddress()));

                // getParent() method
                System.out.println("Parent: " + iface.getParent());

                // getIndex() method
                System.out.println("Index: " + iface.getIndex());
                // Interface addresses of the network interface
                System.out.println("\tInterface addresses: ");

                // getInterfaceAddresses() method
                for (InterfaceAddress addr : iface.getInterfaceAddresses())
                {
                    System.out.println("\t\t" + addr.getAddress().toString());
                }
                // Interface addresses of the network interface
                System.out.println("\tInetAddresses associated with this interface: ");

                // getInetAddresses() method returns list of all
                // addresses currently bound to this interface
                Enumeration<InetAddress> en = iface.getInetAddresses();
                while (en.hasMoreElements())
                {
                    System.out.println("\t\t" + en.nextElement().toString());
                }

                // getMTU() method
                System.out.println("\tMTU: " + iface.getMTU());

                // getSubInterfaces() method
                System.out.println("\tSubinterfaces: " +
                        Collections.list(iface.getSubInterfaces()));

                // isLoopback() method
                System.out.println("\this loopback: " + iface.isLoopback());

                // isVirtual() method
                System.out.println("\this virtual: " + iface.isVirtual());

                // isPointToPoint() method
                System.out.println("\this point to point: " + iface.isPointToPoint());

                // supportsMulticast() method
                System.out.println("Supports Multicast: " + iface.supportsMulticast());

            }
        }

        // getByIndex() method returns network interface
        // with the specified index
        NetworkInterface nif = NetworkInterface.getByIndex(1);

        // toString() method is used to display textual
        // information about this network interface
        System.out.println("Network interface 1: " + nif.toString());

        // getByName() method returns network interface
        // with the specified name
        NetworkInterface nif2 = NetworkInterface.getByName("eth0");
        InetAddress ip = InetAddress.getByName("localhost");

        // getbyInetAddress() method
        NetworkInterface nif3 = NetworkInterface.getByInetAddress(ip);
        System.out.println("\nlocalhost associated with: " + nif3);

        // equals() method
        boolean eq = nif.equals(nif2);
        System.out.println("nif==nif2: " + eq);

        // hashCode() method
        System.out.println("Hashcode : " + nif.hashCode());
    }
}
