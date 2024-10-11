package lesson_1.zadacha3Streams.student;


import java.util.Scanner;

public class StudentDiary {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        boolean exit = false;

        while (!exit) {
            System.out.println("Изберете опция:");
            System.out.println("1. Добавяне на студент");
            System.out.println("2. Преглед на всички студенти и оценки");
            System.out.println("3. Изчисляване на средна оценка");
            System.out.println("4. Изход");

            int choice = scanner.nextInt();
           //

            switch (choice) {
                case 1:
                    System.out.println("Въведете име на студент:");
                    //
                    System.out.println("Въведете оценка:");
                    //
                    break;

                case 2:

                    System.out.println("Списък със студенти и оценки:");
                    //
                    break;

                case 3:
                    double averageGrade = 0.0;
                    //
                    System.out.println("Средната оценка на всички студенти е: " + averageGrade);
                    break;

                case 4:
                    exit = true;
                    System.out.println("Изход...");
                    break;

                default:
                    System.out.println("Невалидна опция. Опитайте отново.");
            }
        }
    }
}

