public class AndGate3 extends AndGate2 {
	private boolean C;

	public AndGate3() {
		super();
		this.C = false;
	}

	public AndGate3(boolean val) {
		super(val);
		this.C = false;
	}

	public AndGate3(boolean val1, boolean val2, boolean val3) {
		super(val1, val2);
		this.C = val3;
	}

	/* Setters */

	public void setC(boolean val) {
		this.C = val;
	}

	/* Getter */
	@Override
	public boolean getOutput() {
		return super.getOutput() && this.C;
	}

	@Override
	public String toString() {
		return super.toString() + " C: " + this.C;
	}

	@Override
	public boolean equals(Object o) {
		if(!(o instanceof AndGate3)) return false;
		AndGate3 g = (AndGate3) o;
		return super.equals(g) && this.C == g.C;
	}
}
