package lesson_2.zadacha4_game.student;

public class RockPaperScissorsServer {
    public static void main(String[] args) {

        //1. Create DatagramSocket
        //2. received data packet from client
        //3. prepare and send response to client


    }

    private static String getResult(String clientChoice) {
        String[] choices = {"Rock", "Scissors", "Paper"};
        String serverChoice = choices[(int) (Math.random() * 3)];
        System.out.println("Server choice is: " + serverChoice);

        if (clientChoice.equals(serverChoice)) {
            return "Draw! Both of you chose " + clientChoice + ".";
        } else if (("Rock".equalsIgnoreCase(clientChoice) && "Scissors".equalsIgnoreCase(serverChoice)) ||
                ("Scissors".equalsIgnoreCase(clientChoice) && "Paper".equalsIgnoreCase(serverChoice)) ||
                ("Paper".equalsIgnoreCase(clientChoice) && "Rock".equalsIgnoreCase(serverChoice))) {
            return "You win! You chose " + clientChoice + ", аnd server chose " + serverChoice + ".";
        } else {
            return "You lose! You chose " + clientChoice + ", аnd server chose " + serverChoice + ".";
        }
    }
}
