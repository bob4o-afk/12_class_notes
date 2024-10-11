package lesson_2.zadacha3_udp_chat.teacher;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

public class UDPChatServer {

    private static final int SERVER_PORT = 9876;

    public static void main(String[] args) throws Exception {
        //A socket for sending and receiving datagram packets through a port
        DatagramSocket serverSocket = new DatagramSocket(SERVER_PORT);
        byte[] receiveData = new byte[1024];

        System.out.println("UDP chat server started on port " + SERVER_PORT);

        while (true) {

            //receive packet
            DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
            serverSocket.receive(receivePacket);

            //get data from packet
            String message = new String(receivePacket.getData(), 0, receivePacket.getLength());
            InetAddress clientAddress = receivePacket.getAddress();
            int clientPort = receivePacket.getPort();

            System.out.println("Message is received: " + message + " от " + clientAddress + ":" + clientPort);
            if ("exit".equalsIgnoreCase(message)) {
                System.out.println("Server is stopped");
                break;
            }
            //send confirmation
            String confirmation = "Server receive message '" + message + "'";
            byte[] sendData = confirmation.getBytes();
            DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, clientAddress, clientPort);
            serverSocket.send(sendPacket);
        }
        serverSocket.close();
        System.out.println("Server socket closed.");
    }
}
