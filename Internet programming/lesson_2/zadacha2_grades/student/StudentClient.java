package lesson_2.zadacha2_grades.student;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.InputMismatchException;
import java.util.NoSuchElementException;
import java.util.Scanner;

public class StudentClient {
    private static Socket socket;
    private static PrintWriter out;
    private static BufferedReader in;

    public static void main(String[] args) {

        try {
            // Establish connection to the server
            socket = new Socket("localhost", 8080);
            out = new PrintWriter(socket.getOutputStream(), true);
            in = new BufferedReader(new InputStreamReader(socket.getInputStream()));

            Scanner scanner = new Scanner(System.in);

            while (true) {
                System.out.println("1. Add student");
                System.out.println("2. View all students");
                System.out.println("3. Search student by name");
                System.out.println("4. Average mark for all students");
                System.out.println("5. Exit");
                System.out.print("Choose option (1-5): ");

                String choice = scanner.nextLine();

                switch (choice) {
                    case "1" -> addStudent(scanner);
                    case "2" -> viewAllStudents();
                    case "3" -> searchStudent(scanner);
                    case "4" -> viewAverageGrade();
                    case "5" -> {
                        out.println("EXIT");
                        System.out.println("Exit...");
                        return;
                    }
                    default -> System.out.println("Invalid choice. Try again.");
                }
            }
        } catch (UnknownHostException e) {
            System.err.println("Unable to connect to the host: " + e.getMessage());
        } catch (IOException e) {
            System.err.println("I/O error: " + e.getMessage());
        } catch (InputMismatchException e) {
            System.err.println("Input mismatch: Please enter a valid input. " + e.getMessage());
        } catch (NoSuchElementException e) {
            System.err.println("Input error: " + e.getMessage());
        } finally {
            closeResources();
        }
    }

    private static void addStudent(Scanner scanner) {
        try {
            System.out.print("Enter student name: ");
            String name = scanner.nextLine();

            System.out.print("Enter student grade: ");
            double grade = scanner.nextDouble();
            scanner.nextLine();

            out.println("ADD_STUDENT");
            out.println(name);
            out.println(grade);

            readServerResponse();
        } catch (InputMismatchException e) {
            System.err.println("Invalid grade input. Please enter a valid number.");
            scanner.nextLine();
        } catch (IOException e) {
            System.err.println("Error communicating with the server: " + e.getMessage());
        }
    }

    private static void viewAllStudents() throws IOException {
        out.println("VIEW_ALL_STUDENTS");
        readServerResponse();
    }

    private static void searchStudent(Scanner scanner) throws IOException {
        System.out.print("Enter student name to search: ");
        String name = scanner.nextLine();

        out.println("SEARCH_STUDENT");
        out.println(name);

        readServerResponse();
    }

    private static void viewAverageGrade() throws IOException {
        out.println("VIEW_AVERAGE_GRADE");
        readServerResponse();
    }

    private static void readServerResponse() throws IOException {
        String response;
        while ((response = in.readLine()) != null) {
            if (response.equals("END")) {
                break;
            }
            System.out.println(response);
        }
    }

    private static void closeResources() {
        try {
            if (in != null) in.close();
            if (out != null) out.close();
            if (socket != null) socket.close();
        } catch (IOException e) {
            System.err.println("Error closing resources: " + e.getMessage());
        }
    }
}
