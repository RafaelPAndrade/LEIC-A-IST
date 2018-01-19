public class AndGate2 {
	private boolean A;
	private boolean B;

	public AndGate2() {
		this.A = false;
		this.B = false;
	}

	
	public AndGate2(boolean val) {
		this.A = val;
		this.B = val;
	}


	public AndGate2(boolean val1, boolean val2) {
		this.A = val1;
		this.B = val2;
	}


	/* Setters */
	public void setA(boolean val) {
		this.A = val;
	}

	public void setB(boolean val) {
		this.B = val;
	}

	/* Getter */
	public boolean getOutput() {
		return this.A && this.B;
	}


	@Override
	public String toString() {
		return "A: " + this.A + " B: " + this.B;
	}

	@Override
	public boolean equals(Object o) {
		if(!(o instanceof AndGate2)) return false;
		AndGate2 g = (AndGate2) o;
		return this.A == g.A && this.B == g.B;
	}
}
