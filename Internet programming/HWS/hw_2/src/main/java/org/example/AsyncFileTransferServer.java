package org.example;

import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.AsynchronousChannelGroup;
import java.nio.channels.AsynchronousServerSocketChannel;
import java.nio.channels.AsynchronousSocketChannel;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

public class AsyncFileTransferServer {
    private final int port;
    private AsynchronousServerSocketChannel serverChannel;

    public AsyncFileTransferServer(int port) {
        this.port = port;
    }

    public void startServer() throws IOException {
        ExecutorService threadPool = Executors.newFixedThreadPool(4);
        AsynchronousChannelGroup group = AsynchronousChannelGroup.withThreadPool(threadPool);
        serverChannel = AsynchronousServerSocketChannel.open(group).bind(new java.net.InetSocketAddress(port));

        System.out.println("Server listening on port: " + port);

        try {
            while (true) {
                Future<AsynchronousSocketChannel> futureChannel = serverChannel.accept();
                try {
                    AsynchronousSocketChannel clientChannel = futureChannel.get();
                    System.out.println("Client connected: " + clientChannel.getRemoteAddress());
                    handleClient(clientChannel);
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                    System.err.println("Server was interrupted: " + e.getMessage());
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        } finally {
            threadPool.shutdown();
        }
    }

    private void handleClient(AsynchronousSocketChannel clientChannel) {
        ByteBuffer buffer = ByteBuffer.allocate(1024);

        clientChannel.read(buffer, null, new ReadFileNameCompletionHandler(clientChannel, buffer));
    }

    private void saveFile(AsynchronousSocketChannel clientChannel, String outputFileName) {
        Path serverDir = Paths.get("server_files");
        try {
            if (!Files.exists(serverDir)) {
                Files.createDirectories(serverDir);
            }

            Path filePath = serverDir.resolve(outputFileName);
            FileOutputStream fos = new FileOutputStream(filePath.toFile());
            ByteBuffer buffer = ByteBuffer.allocate(4096);

            clientChannel.read(buffer, null, new FileDataCompletionHandler(clientChannel, fos, buffer));

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void closeChannel(AsynchronousSocketChannel channel) {
        if (channel != null) {
            try {
                channel.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public static void main(String[] args) throws IOException {
        int port = 5000;
        AsyncFileTransferServer server = new AsyncFileTransferServer(port);
        server.startServer();
    }

    private class ReadFileNameCompletionHandler implements java.nio.channels.CompletionHandler<Integer, Void> {
        private final AsynchronousSocketChannel clientChannel;
        private final ByteBuffer buffer;

        public ReadFileNameCompletionHandler(AsynchronousSocketChannel clientChannel, ByteBuffer buffer) {
            this.clientChannel = clientChannel;
            this.buffer = buffer;
        }

        @Override
        public void completed(Integer result, Void attachment) {
            if (result == -1) {
                closeChannel(clientChannel);
                return;
            }

            buffer.flip();
            int fileNameLength = buffer.getInt();
            buffer.clear();

            readFileName(clientChannel, fileNameLength);
        }

        @Override
        public void failed(Throwable exc, Void attachment) {
            exc.printStackTrace();
        }

        private void readFileName(AsynchronousSocketChannel clientChannel, int fileNameLength) {
            ByteBuffer fileNameBuffer = ByteBuffer.allocate(fileNameLength);

            clientChannel.read(fileNameBuffer, null, new FileNameCompletionHandler(clientChannel, fileNameBuffer));
        }
    }

    private class FileNameCompletionHandler implements java.nio.channels.CompletionHandler<Integer, Void> {
        private final AsynchronousSocketChannel clientChannel;
        private final ByteBuffer fileNameBuffer;

        public FileNameCompletionHandler(AsynchronousSocketChannel clientChannel, ByteBuffer fileNameBuffer) {
            this.clientChannel = clientChannel;
            this.fileNameBuffer = fileNameBuffer;
        }

        @Override
        public void completed(Integer result, Void attachment) {
            if (result == -1) {
                closeChannel(clientChannel);
                return;
            }

            fileNameBuffer.flip();
            byte[] fileNameBytes = new byte[fileNameBuffer.remaining()];
            fileNameBuffer.get(fileNameBytes);
            String fileName = new String(fileNameBytes).trim();
            String outputFileName = "output.txt";

            System.out.println("Receiving file: " + fileName + " (will save as " + outputFileName + ")");
            fileNameBuffer.clear();

            saveFile(clientChannel, outputFileName);
        }

        @Override
        public void failed(Throwable exc, Void attachment) {
            exc.printStackTrace();
        }
    }

    private class FileDataCompletionHandler implements java.nio.channels.CompletionHandler<Integer, Void> {
        private final AsynchronousSocketChannel clientChannel;
        private final FileOutputStream fos;
        private final ByteBuffer buffer;

        public FileDataCompletionHandler(AsynchronousSocketChannel clientChannel, FileOutputStream fos, ByteBuffer buffer) {
            this.clientChannel = clientChannel;
            this.fos = fos;
            this.buffer = buffer;
        }

        @Override
        public void completed(Integer result, Void attachment) {
            if (result == -1) {
                System.out.println("File received successfully.");
                closeResources();
                return;
            }

            buffer.flip();
            try {
                fos.write(buffer.array(), 0, buffer.limit());
            } catch (IOException e) {
                e.printStackTrace();
            }
            buffer.clear();

            clientChannel.read(buffer, null, this);
        }

        @Override
        public void failed(Throwable exc, Void attachment) {
            exc.printStackTrace();
            closeResources();
        }

        private void closeResources() {
            try {
                fos.close();
                clientChannel.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
