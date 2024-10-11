import java.io.*;
import java.net.*;
import java.util.*;


public class Main {
    public static void main(String[] args) throws UnknownHostException {
        InetAddress address = InetAddress.getLocalHost();
        System.out.println(address);

        address = InetAddress.getLoopbackAddress();
        System.out.println(address);

        InetAddress[] addressByName = InetAddress.getAllByName("8.8.8.8");
        for (InetAddress inetAddress : addressByName) {
            System.out.println("ALL InetAddresses of Named Host : " + inetAddress.getHostName());
            System.out.println("ALL InetAddresses of Named Host : " + inetAddress.getHostAddress());

        }

    }

}
