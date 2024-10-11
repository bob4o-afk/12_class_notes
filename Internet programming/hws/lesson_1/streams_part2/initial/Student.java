package lesson_1.streams_part2.initial;

public class Student {
        private String name;
        private double grade;

        public Student(String name, double grade) {
            this.name = name;
            this.grade = grade;
        }

        public String getName() {
            return name;
        }

        public double getGrade() {
            return grade;
        }

        @Override
        public String toString() {
            return name + " - Оценка: " + grade;
        }
}
