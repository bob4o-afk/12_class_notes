package lesson_1.zadacha4_clientServer.teacher;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class ClientFinal {
    public static void main(String[] args) {
        System.out.println("Hello World.I am Client!");
        try {
            Socket socket = new Socket("localhost", 9708);
            //we need to read data in from keyboard and sent it to the
            try (BufferedReader userInput = new BufferedReader(new InputStreamReader(System.in))) {
                System.out.println("Enter string");
                String str = userInput.readLine();
                PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
                out.println(str);
                BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                System.out.println(in.readLine());
            }
            socket.close();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
