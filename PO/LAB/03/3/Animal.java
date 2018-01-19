public class Animal {
	
	private int _energy;
	private int _baseEnergy;
	private int _moveEnergy;


	public Animal(int baseEnergy, int moveEnergy) {
		this._energy = this._baseEnergy = baseEnergy;
		this._moveEnergy = moveEnergy;
	}

	/**
	 * All Animals can move, and lose some of their energy in the process
	 */
	public boolean move() {
		if( this._energy >= this._moveEnergy ) {
			this._energy -= this._moveEnergy;
			return true;
		} else {
			return false;
		}
	}

	/**
	 * Let's an Animal recover to it's baseEnergy values.
	 * Extra energy is discarded.
	 */
	public void sleep() {
		this._energy = this._baseEnergy;
	}

	public int changeEnergy(int change) {
		if( change < 0 ) {
			if( change < this._energy ) {
				this._energy -= change;
				return change;
			} else {
				int res = this._energy;
				this._energy = 0;
				return res;
			}
		} else {
			this._energy += change;
			return change;
		}
	}

	/* Getters */

	public int getEnergy() {
		return this._energy;
	}

	public int getBaseEnergy() {
		return this._baseEnergy;
	}

	public int getmoveEnergy() {
		return this._moveEnergy;
	}

	/* Setters */

	public void setEnergy(int e) {
		this._energy = e;
	}


	@Override
	public String toString() {
		return "Energy: " + this._energy;
	}

	@Override
	public boolean equals(Object o) {
		if(!(o instanceof Animal)) { return false; }
		
		Animal a = (Animal) o;
		return a._baseEnergy == this._baseEnergy && a._moveEnergy == this._moveEnergy && a._energy == this._energy;
	}
}
