package org.example;

public class User {
    private int id;
    private String email;
    private String first_name;
    private String last_name;
    private String avatar;

    // Getters and setters
    // toString method to print user details
    @Override
    public String toString() {
        return "User{" +
                "id=" + id +
                ", email='" + email + '\'' +
                ", first_name='" + first_name + '\'' +
                ", last_name='" + last_name + '\'' +
                ", avatar='" + avatar + '\'' +
                '}';
    }
}
