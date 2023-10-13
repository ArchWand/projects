public class Speedometer {
    // Name: ArcWand
    // Fun fact: stands for Arcane Wanderer

    public static void main(String[] args) {
        int kilometers = 50;
        double kmPerMile = 1.60934;
        double hours = 0.54;
        String name = "ArcWand";

        double miles = kilometers / kmPerMile;
        double milesTrunc = ((int) (miles * 1000)) / 1000d;

        double speed = ((int) (milesTrunc / hours * 100)) / 100d;

        System.out.println(name + " drove at a speed of " + speed + " mph for " + milesTrunc + " miles!");
    }
}
