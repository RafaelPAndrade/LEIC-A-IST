public class Application {
	public static void main(String[] args){
		Cat c = new Cat("Tareco", 12, 0.1);
		System.out.println(c);
		System.out.println(c.equals(new Cat("Malaquias", 0, 0)));
		System.out.println(c.equals(new Cat("Tareco", 12, 0.1)));
	}

}
