package lesson_2.sockets_part3.initial.grades;

import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class StudentProcessor {

    private static final String FILE_NAME = "students.txt";

    public static synchronized void addStudent(String name, double grade) {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(FILE_NAME, true))) {
            writer.write(name + "," + grade);
            writer.newLine();
            System.out.println("Student successfully added: " + name + " with grade: " + grade);
        } catch (IOException e) {
            System.out.println("Error while writing student data: " + e.getMessage());
        }
    }

    public static synchronized List<Student> readStudents() {
        List<Student> students = new ArrayList<>();
        try (BufferedReader reader = new BufferedReader(new FileReader(FILE_NAME))) {
            String line;
            while ((line = reader.readLine()) != null) {
                String[] parts = line.split(",");
                if (parts.length == 2) {
                    String name = parts[0];
                    double grade = Double.parseDouble(parts[1]);
                    students.add(new Student(name, grade));
                } else {
                    System.out.println("Malformed line in students.txt: " + line);
                }
            }
        } catch (IOException e) {
            System.out.println("Error reading student data: " + e.getMessage());
        }
        return students;
    }

    public static synchronized String searchStudent(String name) {
        List<Student> students = readStudents();
        Optional<Student> student = students.stream()
                .filter(st -> st.getName().equalsIgnoreCase(name))
                .findFirst();

        return student
                .map(st -> "Found student: " + st.getName() + " with grade: " + st.getGrade())
                .orElse("Student not found.");
    }

    public static double calculateAverageGrade(List<Student> students) {
        return students.stream()
                .mapToDouble(Student::getGrade)
                .average()
                .orElse(0);
    }
}
