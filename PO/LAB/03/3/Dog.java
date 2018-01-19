public class Dog extends NamedAnimal {

	/**
	 * Predefined values from spec
	 *
	 * @param name The dog's name
	 */
	public Dog(String name} {
		super(name, 1000, 50)
	}

	public void attackCat(Cat c) {
		c.changeEnergy(-25);
		this.changeEnergy(-100);
	}

}
