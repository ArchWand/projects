import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;

public class CheckCoin {
	public static void compile(String src) {
		// Remove any existing Coin.class file
		File classFile = new File("Coin.class");
		if (classFile.exists()) {
			classFile.delete();
		}

		ProcessBuilder compilerProcess = new ProcessBuilder("javac", src);
		compilerProcess.redirectError();
		try {
			System.out.println("Compiling Coin.java...");
			Process p = compilerProcess.start();
			int result = p.waitFor();

			if (result != 0) {
				System.out.println("Error: Coin.java did not compile successfully.");
				System.exit(1);
			}
		} catch (Exception e) {
			System.out.println("Error: " + e.getMessage());
			System.out.println("Please send this error message to the course instructor.");
			System.exit(1);
		}
	}

	private static int runCount = 0;
	public static void run(String[] input) {
		try {
			// Run the Coin program
			ProcessBuilder runnerProcess = new ProcessBuilder("java", "Coin");
			Process run = runnerProcess.start();

			// Capture and display the output of the Coin program
			InputStream inputStream = run.getInputStream();
			BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));

			// Write to the input of the Coin program
			OutputStream outputStream = run.getOutputStream();
			BufferedWriter writer = new BufferedWriter(new java.io.OutputStreamWriter(outputStream));

			for (String line : input) {
				writer.write(line);
				writer.newLine();
			}
			writer.flush();

			String line;
			String prompt = null;
			int i = 0;
			// System.out.println("Output of the Coin program:");
			while ((line = reader.readLine()) != null) {
				// System.out.println(line);

				i++;
				// Check that they aren't looping too much
				if (i > 11) {
					System.out.println("Error: Printing too many lines");
					System.exit(1);
				}
				if (i == input.length + 1) {
					if (reader.readLine() == null) { break; }
					System.out.println("Error: Coin program printed too many lines");
					System.out.println("       Possible cause: missing error check");
					System.exit(1);
				}

				if (prompt == null) {
					prompt = line;
				} else if (!line.equals(prompt)) {
					System.out.println("Error: Unexpected print statement");
					System.exit(1);
				}
			}

			// Wait for the Coin program to complete
			System.out.print("Program failed to finish running.\r");
			int programResult = run.waitFor();
			if (programResult != 0) {
				System.out.println("Error: Coin program did not complete successfully.");
				System.exit(1);
			}
			// Check that they aren't looping too little
			if (i < input.length) {
				System.out.println("Error: Coin program did not print enough lines");
				System.out.println("       Possible cause: loop did not run enough times");
				System.exit(1);
			}
			System.out.println("Test " + ++runCount + " successfully completed.                   ");

		} catch (Exception e) {
			System.out.println("Error: " + e.getMessage());
			System.out.println("Please send this error message to the course instructor.");
			System.exit(1);
		}
	}

	public static void main(String[] args) {
		String src = "Coin.java";
		File srcFile = new File(src);
		if (!srcFile.exists() || srcFile.isDirectory()) {
			System.out.println("File not found: Coin.java");
			System.exit(1);
		}

		// Compile and test Coin.java
		compile(src);
		String[][] test = {
			{ "heads", "heads", "heads", "heads", "heads", "heads", "heads", "heads", "heads", "heads" },
			{ "tails", "tails", "tails", "tails", "tails", "tails", "tails", "tails", "tails", "tails" },
			{ "heads", "tails", "heads", "tails", "heads", "tails", "heads", "tails", "heads", "tails" },
			{ "tails", "heads", "tails", "tails", "heads", "tails", "heads", "heads", "tails", "heads" },
			{ "lkjsi*Flwn" },
			{ "heads", "tails", "tails", "heads", "fj91298ha" },
			{ "tails", "heads", "no" },
			{ "heads", "heads", "a" },
			{ "tails", "tails", "b" },
			{ "heads", "tails", "tails", "heads", "heads", "tails", "heads", "htealdis" }
		};

		for (String[] input : test) {
			run(input);
		}
	}
}
