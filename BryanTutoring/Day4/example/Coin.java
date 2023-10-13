import java.util.Scanner;

public class Coin {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);

		for (int i = 0; i < 10; i++) {
			System.out.println("Flip a coin: ");
			String flip = in.nextLine();
			// Error checking; can only be "heads" or "tails"
			if (!flip.equals("heads") && !flip.equals("tails")) {
				System.out.println("Error: Invalid input. Should be either 'heads' or 'tails'");
				return;
			}
		}
	}
}
