package lesson_2.zadacha5_weather.student;

import java.io.IOException;
import java.net.MulticastSocket;

public class WeatherMulticastClient {
    private static final String MULTICAST_ADDRESS = "224.0.0.1";
    private static final int PORT = 5000;

    public static void main(String[] args) {
        try (MulticastSocket multicastSocket = new MulticastSocket(PORT)) {
           //
            System.out.println("Client join the group.Wait to receive forecast...");

            while (true) {
               //receive packet
            }
        } catch (IOException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}