package org.example;

import java.io.IOException;

public class Main {
    public static void main(String[] args) throws IOException, InterruptedException {
        UserService userService = new UserService();

        userService.listUsers();
        userService.getUser(2);
        userService.handleUserNotFound(23);
        userService.createUser("John Doe", "Software Developer");
        userService.updateUser(2, "Jane Doe", "Project Manager");
        userService.updateUserJob(2, "Senior Developer");
        userService.deleteUser(2);
    }
}
