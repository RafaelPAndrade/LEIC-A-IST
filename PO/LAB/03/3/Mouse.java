public class Mouse extends Animal {


	public Mouse() {
		super(50, 2);
	}


	protected void escape() {
		this.changeEnergy(5);
	}

	@Override
	public String toString() {
		return "Mouse (" + super.toString() + ")";
	}

	@Override
	public boolean equals(Object o) {
		return (o instanceof Mouse) && super.equals(o);
	}
}
