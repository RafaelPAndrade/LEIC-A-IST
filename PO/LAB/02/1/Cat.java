public class Cat {
	/**
	 * The name of the Cat.
	 */
	private String name;

	/**
	 * The age of the Cat.
	 */
	private	int age;

	/**
	 * The weight of the Cat.
	 */
	private	double weight;


	/**
	 * Specify all the attributes of the Cat object:
	 *
	 * @param name
	 * @param age
	 * @param weight
	 */
	public Cat(String name, int age, double weight){
		this.name = name;
		this.age = age;
		this.weight = weight;
	}


	/*  Getters  */

	/**
	 * @return the name of the cat
	 */
	public String getName(){
		return this.name;
	}

	/**
	 * @return the age of the cat
	 */
	public int getAge(){
		return this.age;
	}

	/**
	 * @return the weight of the cat
	 */
	public double getWeight(){
		return this.weight;
	}


	/* Setters */

	/**
	 * @param name a new name for the cat
	 */
	public void setName(String name){
		this.name = name;
	}

	/**
	 * @param age a new age for the cat
	 */
	public void setAge(int age){
		this.age = age;
	}

	/**
	 * @param weight the weight of the cat, in double
	 */
	public void setWeight(double weight){
		this.weight = weight;
	}


	/* Overrides */

	/**
	 * Provides alternative definition of toString() for the class Cat
	 *
	 * @return a string representation of a Cat object
	 */
	@Override
	public String toString() {
		return this.name + " (Age: " + this.age + "; Weight: " + this.weight + ")";
	}

	/**
	 * Provides alternative definition of equals() for the class Cat
	 *
	 * @param x the other object, besides "this", to test equality
	 *
	 * @return boolean: True if all the proprieties are equal, False otherwise
	 */
	public boolean equals(Object x) {
		if (x instanceof Cat) {
			Cat t = (Cat) x;
			return t.name.equals(name) && this.age == t.age && this.weight == t.weight;
		}
		return false;
	}

}

