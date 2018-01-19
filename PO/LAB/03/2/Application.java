public class Application {
	public static void main(String[] args) {
		AndGate3 g1 = new AndGate3();
		System.out.println(g1);
		AndGate3 g2 = new AndGate3(false);
		System.out.println(g2);
		AndGate2 g3 = new AndGate3(false, true, false);
		System.out.println(g3);

		System.out.println( g1.equals(g2) );
		System.out.println( g1.equals(g3) );
	}
}
