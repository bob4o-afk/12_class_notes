package lesson_2.zadacha4_game.student;

import java.net.DatagramSocket;
import java.util.Scanner;

public class RockPaperScissorsClient {
    public static void main(String[] args) {
        String serverAddress = "localhost";
        int serverPort = 12345;

        try (DatagramSocket socket = new DatagramSocket();
             Scanner scanner = new Scanner(System.in)) {

            while (true) {
                System.out.println("\n--- Choice ---");
                System.out.println("1. Rock");
                System.out.println("2. Scissors");
                System.out.println("3. Paper");
                System.out.println("4. Exit");
                System.out.print("ChoseOption (1-4): ");

                String choice = scanner.nextLine();

                if (choice.equals("1")) {
                   // sendMessage
                } else if (choice.equals("2")) {
                    //sendMessage
                } else if (choice.equals("3")) {
                    //sendMessage(socket
                } else if (choice.equals("4")) {
                    System.out.println("Exit of game...");
                    break;
                } else {
                    System.out.println("Invalid choice.Try again!");
                    continue;
                }

               //receive message
            }
        } catch (Exception e) {
            System.err.println(e.getMessage());
        }
    }

    private static void sendMessage(DatagramSocket socket, String serverAddress, int serverPort, String message) {

    }

    private static String receiveMessage(DatagramSocket socket) {
        //should be changed
      return null;
    }
}
