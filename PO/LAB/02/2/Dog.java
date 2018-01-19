public class Dog {
	private String name;
	private int energyLevel;

	public Dog(String name, int energyLevel) {
		this.name = name;
		this.energyLevel = ( energyLevel > 0 && energyLevel <= 1000) ? energyLevel : 1000;
	}

	public boolean run() {
		if ( this.energyLevel >50 ) {
			this.energyLevel-=50;
			return true;
		} else {
			return false;
		}
	}

	public boolean hunt(Mouse m) {
		if ( this.run() ) {
			m.run()
			if ( (int) Math.random()*25  == 0 ) {
				this.energyLevel = m.drain();
				return true;
			} else {
				m.escaped()
				return false;
			}
		
		} else {
			return false;
		}
