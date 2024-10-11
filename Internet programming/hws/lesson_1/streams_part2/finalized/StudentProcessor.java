package lesson_1.streams_part2.finalized;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class StudentProcessor {

    private static final String FILE_NAME = "./internet_programming/lesson_2/sockets_part3/initial/grades/files/students.txt";

    public static void addStudent(String name, double grade) {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(FILE_NAME, true))) {
            writer.write(name + "," + grade);
            writer.newLine();
            System.out.println("Успешно добавихте студента: " + name + " с оценка: " + grade);
        } catch (IOException e) {
            System.out.println("Грешка при записване на данните: " + e.getMessage());
        }
    }

    public static List<Student> readStudents() {
        List<Student> students = new ArrayList<>();
        try (BufferedReader reader = new BufferedReader(new FileReader(FILE_NAME))) {
            String line;
            while ((line = reader.readLine()) != null) {
                String[] parts = line.split(",");
                String name = parts[0];
                double grade = Double.parseDouble(parts[1]);
                students.add(new Student(name, grade));
            }
        } catch (IOException e) {
            System.out.println("Грешка при четене на данните: " + e.getMessage());
        }
        return students;
    }

    public static double calculateAverageGrade(List<Student> students) {
        return students.stream()
                .mapToDouble(Student::getGrade)
                .average()
                .orElse(0);
    }
}
