import java.math.BigInteger;
import java.util.Scanner;

public class bigger {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		BigInteger t = sc.nextBigInteger();
		BigInteger s = sc.nextBigInteger();
		// Take absolute value of s
		s = s.abs();

		System.out.println(reduce(taxicab(t), spider(s)));
	}

	public static BigInteger gcd(BigInteger a, BigInteger b) {
		if (b.equals(BigInteger.ZERO))
			return a;
		return gcd(b, a.mod(b));
	}

	public static String reduce(BigInteger a, BigInteger b) {
		if (a.mod(b).equals(BigInteger.ZERO)) {
			return a.divide(b).toString();
		}
		if (a.compareTo(b) > 0) {
			return "1";
		}
		BigInteger c = gcd(a, b);
		a = a.divide(c);
		b = b.divide(c);
		return a.toString() + "/" + b.toString();
	}

	public static BigInteger triangle(BigInteger n) {
		return n.multiply(n.add(BigInteger.ONE)).divide(BigInteger.valueOf(2));
	}

	public static BigInteger taxicab(BigInteger n) {
		return triangle(n).multiply(BigInteger.valueOf(4)).add(BigInteger.ONE);
	}

	public static BigInteger quarter_spider(BigInteger s) {
		BigInteger c = s.divide(BigInteger.valueOf(3));
		return s.multiply(s.add(BigInteger.ONE)).add(c.multiply(BigInteger.valueOf(2).multiply(s).subtract(BigInteger.valueOf(3).multiply(c)).subtract(BigInteger.ONE))).divide(BigInteger.valueOf(2));
	}

	public static BigInteger spider(BigInteger s) {
		return quarter_spider(s).multiply(BigInteger.valueOf(4)).add(BigInteger.ONE);
	}
}


