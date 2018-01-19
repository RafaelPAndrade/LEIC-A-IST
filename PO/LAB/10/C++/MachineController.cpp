# include <iostream>

# include "MachineController.h"
# include "WashingMachine.h"

MachineController::MachineController(WashingMachine *wm): _wm(wm) {}
void MachineController::setState(MachineController *dc) { _wm->_dc = dc; }

ClosedDoor::ClosedDoor(WashingMachine* wm): MachineController(wm) {
	std::cout << "Door is closed" << std::endl; }
void ClosedDoor::tick(){}
void ClosedDoor::power() {
		setState(new Washing(_wm)); delete this;
}
void ClosedDoor::open(){
		setState(new OpenDoor(_wm)); delete this;
};

void ClosedDoor::closed(){};

OpenDoor::OpenDoor(WashingMachine* wm): MachineController(wm) {std::cout << "Door is open" << std::endl;
}
void OpenDoor::tick(){}
void OpenDoor::power(){}
void OpenDoor::open(){}
void OpenDoor::closed() {
	setState(new ClosedDoor(_wm)); delete this;
}


Washing::Washing(WashingMachine* wm): MachineController(wm) {std::cout << "Machine is working" << std::endl;
}
void Washing::tick() {
	if(!(timer--)){
		setState(new FinishingWash(_wm));
		delete this;
	}
};
void Washing::power(){ setState(new FinishingWash(_wm)); delete this; };
void Washing::open(){};
void Washing::closed(){};

FinishingWash::FinishingWash(WashingMachine* wm): MachineController(wm) {std::cout << "Machine is finishing" << std::endl;}
void FinishingWash::tick() {
	if(!(timer--)){
		setState(new ClosedDoor(_wm));
		delete this;
	}
}
void FinishingWash::power(){}
void FinishingWash::open(){}
void FinishingWash::closed(){}

