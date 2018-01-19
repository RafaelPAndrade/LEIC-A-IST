public class NamedAnimal extends Animal {
	
	private String _name;


	public NamedAnimal(String name, int baseEnergy, int moveEnergy) {
		super(baseEnergy, moveEnergy);
		this._name = name;
	}


	@Override
	public String toString() {
		return this._name + "(" + super.toString() + ")";
	}

	@Override
	public boolean equals(Object o) {
		if (!(o instanceof NamedAnimal)) { return false; }

		NamedAnimal n = (NamedAnimal) o;
		return super.equals(n) && n._name.equals(this._name);
	}

}
