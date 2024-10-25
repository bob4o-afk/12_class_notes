package org.example;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.AsynchronousSocketChannel;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.concurrent.Future;

public class AsyncFileTransferClient {
    private final String serverHost;
    private final int serverPort;

    public AsyncFileTransferClient(String serverHost, int serverPort) {
        this.serverHost = serverHost;
        this.serverPort = serverPort;
    }

    public void sendFile(Path filePath) {
        try (AsynchronousSocketChannel clientChannel = AsynchronousSocketChannel.open()) {
            connectToServer(clientChannel);
            sendFileName(clientChannel, filePath);
            sendFileData(clientChannel, filePath);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void connectToServer(AsynchronousSocketChannel clientChannel) throws Exception {
        Future<Void> futureConnection = clientChannel.connect(new java.net.InetSocketAddress(serverHost, serverPort));
        futureConnection.get();
        System.out.println("Connected to server: " + serverHost + ":" + serverPort);
    }

    private void sendFileName(AsynchronousSocketChannel clientChannel, Path filePath) throws IOException, InterruptedException, java.util.concurrent.ExecutionException {
        byte[] fileNameBytes = filePath.getFileName().toString().getBytes();
        ByteBuffer fileNameBuffer = ByteBuffer.allocate(4 + fileNameBytes.length);
        fileNameBuffer.putInt(fileNameBytes.length);
        fileNameBuffer.put(fileNameBytes);
        fileNameBuffer.flip();
        clientChannel.write(fileNameBuffer).get();
        System.out.println("File name sent: " + filePath.getFileName());
    }

    private void sendFileData(AsynchronousSocketChannel clientChannel, Path filePath) throws IOException, InterruptedException, java.util.concurrent.ExecutionException {
        byte[] fileData = Files.readAllBytes(filePath);
        ByteBuffer fileBuffer = ByteBuffer.wrap(fileData);
        clientChannel.write(fileBuffer).get();
        System.out.println("File sent: " + filePath.getFileName());
    }

    public static void main(String[] args) {
        String serverHost = "localhost";
        int serverPort = 5000;
        Path filePath = Path.of("client_files", "example.txt");

        AsyncFileTransferClient client = new AsyncFileTransferClient(serverHost, serverPort);
        client.sendFile(filePath);
    }
}
