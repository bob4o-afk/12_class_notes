package lesson_1.zadacha1.teacher;

import java.io.IOException;
import java.net.InetAddress;


public class NSLookupFinal {

    public static final String WWW_YAHOO_COM = "www.yahoo.com";

    public static void main(String[] args) {
        try {
            // To get and print InetAddress of Local Host
            InetAddress address1 = InetAddress.getLocalHost();
            System.out.println("IP of Local Host : " + address1);

            //Loopback address
            InetAddress loopback = InetAddress.getLoopbackAddress();
            System.out.println("Loopback InetAddress - Local Host : "
                    + loopback);

            // IP address for reverse DNS lookup - find by "8.8.8.8" the Google's public DNS
            InetAddress addressReverse = InetAddress.getByName("8.8.8.8");
            String hostname = addressReverse.getHostName();
            System.out.println("Hostname for IP 8.8.8.8: " + hostname);


            // obtain the IP address of a domain name -google.cmo,yahoo or other
            InetAddress addr4 = InetAddress.getByName(WWW_YAHOO_COM);
            System.out.println("IP of " + WWW_YAHOO_COM + "  is: " + addr4.getHostAddress());

            //simulate nslookup
            InetAddress[] addresses = InetAddress.getAllByName("google.com");

            System.out.println("NSLookup for google.com:");
            for (InetAddress address : addresses) {
                System.out.println("Host Name: " + address.getHostName());
                System.out.println("IP Address: " + address.getHostAddress());
            }

            //Simulate ping
            String ipAddressPing = "133.192.31.42";
            InetAddress ping = InetAddress.getByName(ipAddressPing);
            System.out.println("Sending Ping Request to " + ipAddressPing);
            if (ping.isReachable(5000))

                System.out.println("Host is reachable");
            else
                System.out.println("Sorry ! We can't reach to this host");


        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}

