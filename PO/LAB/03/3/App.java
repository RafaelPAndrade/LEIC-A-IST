public class App {
	public static void main(String[] args) {
		Mouse a = new Mouse();
		Mouse b = new Mouse();
		b.escape();
		System.out.println(a.equals(b));
	}
}
