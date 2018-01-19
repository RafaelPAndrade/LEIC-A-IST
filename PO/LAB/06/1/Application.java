/**
 * Sample uses.
  */
  public class Application {

/**
 * @param args
 */
public static void main(String[] args) {
	Table t = new Table(3); // table with 3 integers

	t.setAll(90);

	SelectionPredicate p1 = new 
	GreaterThan(9);

	if (t.contains(p1))
		System.out.println("YES");
	else
		System.out.println("NO");

	SelectionPredicate p2 = new EqualTo(2);

	if (t.contains(p2))
		System.out.println("YES");
	else
		System.out.println("NO");
}

}
 
