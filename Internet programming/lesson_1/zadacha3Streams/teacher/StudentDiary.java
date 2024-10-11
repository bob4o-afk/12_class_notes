package lesson_1.zadacha3Streams.teacher;


import java.util.List;
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
            scanner.nextLine();

            switch (choice) {
                case 1:
                    System.out.println("Въведете име на студент:");
                    String name = scanner.nextLine();
                    System.out.println("Въведете оценка:");
                    double grade = scanner.nextDouble();
                    StudentProcessor.addStudent(name, grade);
                    break;

                case 2:
                    List<Student> students = StudentProcessor.readStudents();
                    System.out.println("Списък със студенти и оценки:");
                    students.forEach(System.out::println);
                    break;

                case 3:
                    List<Student> studentsForAverage = StudentProcessor.readStudents();
                    double averageGrade = StudentProcessor.calculateAverageGrade(studentsForAverage);
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

