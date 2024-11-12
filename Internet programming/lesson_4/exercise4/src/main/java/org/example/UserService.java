package org.example;

import com.google.gson.Gson;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import java.io.IOException;
import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;

public class UserService {
    private static final String BASE_URL = "https://reqres.in/api";
    private final HttpClient client;
    private final Gson gson;

    public UserService() {
        client = HttpClient.newHttpClient();
        gson = new Gson();
    }

    public void listUsers() throws IOException, InterruptedException {
        HttpRequest request = HttpRequest.newBuilder()
                .uri(URI.create(BASE_URL + "/users?page=2"))
                .GET()
                .build();

        HttpResponse<String> response = client.send(request, HttpResponse.BodyHandlers.ofString());

        if (response.statusCode() == 200) {
            System.out.println("Users on Page 2:");
            JsonObject jsonResponse = JsonParser.parseString(response.body()).getAsJsonObject();
            System.out.println(jsonResponse);
        } else {
            System.out.println("Failed to fetch users, Status code: " + response.statusCode());
        }
    }

    // 2. Get Single User
    public void getUser(int userId) throws IOException, InterruptedException {
        HttpRequest request = HttpRequest.newBuilder()
                .uri(URI.create(BASE_URL + "/users/" + userId))
                .GET()
                .build();

        HttpResponse<String> response = client.send(request, HttpResponse.BodyHandlers.ofString());

        if (response.statusCode() == 200) {
            User user = gson.fromJson(response.body(), User.class);
            System.out.println("User Details: " + user);
        } else {
            System.out.println("User not found, Status code: " + response.statusCode());
        }
    }

    // 3. Handle "User Not Found"
    public void handleUserNotFound(int userId) throws IOException, InterruptedException {
        HttpRequest request = HttpRequest.newBuilder()
                .uri(URI.create(BASE_URL + "/users/" + userId))
                .GET()
                .build();

        HttpResponse<String> response = client.send(request, HttpResponse.BodyHandlers.ofString());

        if (response.statusCode() == 404) {
            System.out.println("User not found with ID: " + userId);
        } else {
            System.out.println("Unexpected status code: " + response.statusCode());
        }
    }

    // 4. Create a New User
    public void createUser(String name, String job) throws IOException, InterruptedException {
        JsonObject userData = new JsonObject();
        userData.addProperty("name", name);
        userData.addProperty("job", job);

        HttpRequest request = HttpRequest.newBuilder()
                .uri(URI.create(BASE_URL + "/users"))
                .header("Content-Type", "application/json")
                .POST(HttpRequest.BodyPublishers.ofString(userData.toString()))
                .build();

        HttpResponse<String> response = client.send(request, HttpResponse.BodyHandlers.ofString());

        System.out.println("Created User: " + response.body());
    }

    // 5. Update User
    public void updateUser(int userId, String name, String job) throws IOException, InterruptedException {
        JsonObject userData = new JsonObject();
        userData.addProperty("name", name);
        userData.addProperty("job", job);

        HttpRequest request = HttpRequest.newBuilder()
                .uri(URI.create(BASE_URL + "/users/" + userId))
                .header("Content-Type", "application/json")
                .PUT(HttpRequest.BodyPublishers.ofString(userData.toString()))
                .build();

        HttpResponse<String> response = client.send(request, HttpResponse.BodyHandlers.ofString());

        System.out.println("Updated User: " + response.body());
    }

    // 5.2. Update only job of User
    public void updateUserJob(int userId, String job) throws IOException, InterruptedException {
        JsonObject userData = new JsonObject();
        userData.addProperty("job", job);

        HttpRequest request = HttpRequest.newBuilder()
                .uri(URI.create(BASE_URL + "/users/" + userId))
                .header("Content-Type", "application/json")
                .PUT(HttpRequest.BodyPublishers.ofString(userData.toString()))
                .build();

        HttpResponse<String> response = client.send(request, HttpResponse.BodyHandlers.ofString());

        System.out.println("Updated User's Job: " + response.body());
    }

    // 6. Delete User
    public void deleteUser(int userId) throws IOException, InterruptedException {
        HttpRequest request = HttpRequest.newBuilder()
                .uri(URI.create(BASE_URL + "/users/" + userId))
                .DELETE()
                .build();

        HttpResponse<String> response = client.send(request, HttpResponse.BodyHandlers.ofString());

        if (response.statusCode() == 204) {
            System.out.println("User deleted successfully.");
        } else {
            System.out.println("Failed to delete user, Status code: " + response.statusCode());
        }
    }
}
