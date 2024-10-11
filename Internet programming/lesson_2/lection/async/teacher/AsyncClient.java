package lesson_2.lection.async.teacher;

import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.AsynchronousSocketChannel;
import java.util.concurrent.Future;

public class AsyncClient {
    public static void main(String[] args) throws Exception {
        //Create client channel for asynchronous communication
        AsynchronousSocketChannel client = AsynchronousSocketChannel.open();
        //The address of server and port the client will connect to
        InetSocketAddress hostAddress = new InetSocketAddress("localhost", 9238);
        //Connect to server from client
        Future<Void> connect = client.connect(hostAddress);
        //wait for connection to be established
        connect.get();
        // Send message to server
        String message = "Hi Server! I am Asynchronous Client";
        ByteBuffer buffer = ByteBuffer.wrap(message.getBytes());
        Future<Integer> writeResult = client.write(buffer);
        //wait for message to be sent
        writeResult.get();
        //clear buffer
        buffer.clear();
        //close socket channel
        client.close();
    }
}
