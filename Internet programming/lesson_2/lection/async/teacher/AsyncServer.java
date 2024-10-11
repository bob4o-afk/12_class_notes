package lesson_2.lection.async.teacher;

import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.AsynchronousServerSocketChannel;
import java.nio.channels.AsynchronousSocketChannel;
import java.util.concurrent.Future;


public class AsyncServer {
    public static void main(String[] args) throws Exception {
        //creates a new asynchronous server socket channel
        //server listen for client connections
        AsynchronousServerSocketChannel serverSocketChannel = AsynchronousServerSocketChannel.open();
        InetSocketAddress address = new InetSocketAddress("localhost", 9238);
        serverSocketChannel.bind(address);

        while (true) {
            //accepts a new connection asynchronously
            Future<AsynchronousSocketChannel> acceptFuture = serverSocketChannel.accept();
            //wait for client to connect,block till the client connects
            AsynchronousSocketChannel clientChannel = acceptFuture.get();

            //buffer to store data
            ByteBuffer buffer = ByteBuffer.allocate(2048);
            Future<Integer> readFuture = clientChannel.read(buffer);
            //block till data is read
            readFuture.get();

            buffer.flip();
            String message = new String(buffer.array()).trim();
            System.out.println("Message received from client: " + message);
            buffer.clear();
            clientChannel.close();
        }
    }
}
