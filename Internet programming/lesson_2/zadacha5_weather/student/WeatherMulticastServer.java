package lesson_2.zadacha5_weather.student;

import java.io.IOException;
import java.net.MulticastSocket;

public class WeatherMulticastServer {
    private static final String MULTICAST_ADDRESS = "224.0.0.1";
    private static final int PORT = 5000;

    public static void main(String[] args) {
        try (MulticastSocket multicastSocket = new MulticastSocket()) {
            //
            System.out.println("Server is started:");

            while (true) {
            //send packet
            }
        } catch (IOException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }

    private static String generateWeatherForecast(String city) {
        return "Forecast for  " + city + ": Sunny, 25°C.";
    }
}
