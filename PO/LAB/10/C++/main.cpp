# include "WashingMachine.h"
# include "MachineController.h"

int main() {

	WashingMachine m;
	m.closed();
	m.power();
	for(int i = 5400 + 120 + 1; i>=0; --i) {
		m.tick();
	}


	m.open();

}

