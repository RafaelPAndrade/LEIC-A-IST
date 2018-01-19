
# include "WashingMachine.h"
# include "MachineController.h"

WashingMachine::WashingMachine() {
	_dc = new OpenDoor(this);
}

WashingMachine::~WashingMachine() {
	delete _dc;
}

void WashingMachine::tick()  { _dc->tick();   };
void WashingMachine::power() { _dc->power();  };
void WashingMachine::open()  { _dc->open();   };
void WashingMachine::closed(){ _dc->closed(); };
