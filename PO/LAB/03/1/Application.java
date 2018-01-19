public class Application {
	public static void main(String[] args) {
		AndGate2 g1 = new AndGate2();
		System.out.println(g1);
		AndGate2 g2 = new AndGate2(false);
		System.out.println(g2);
		AndGate2 g3 = new AndGate2(false, true);
		System.out.println(g3);

		System.out.println( g1.equals(g2) );
		System.out.println( g1.equals(g3) );
	}
}
