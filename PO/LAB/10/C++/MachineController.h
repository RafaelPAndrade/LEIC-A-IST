
class WashingMachine;


class MachineController {
	protected:
		WashingMachine* _wm;
	public:
		MachineController(WashingMachine *wm);
		virtual ~MachineController(){};
		void setState(MachineController *dc);
		virtual void tick()=0;
		virtual void power()=0;
		virtual void open()=0;
		virtual void closed()=0;
};

class Washing: public MachineController {
	private:
		int timer = 5400;
	public:
		Washing(WashingMachine* wm);
		~Washing(){};
 		virtual void tick();
 		virtual void power();
 		virtual void open();
 		virtual void closed();
}; 

class OpenDoor: public MachineController {

	public:
		OpenDoor(WashingMachine* wm);
		~OpenDoor(){};
 		virtual void tick();
 		virtual void power();
 		virtual void open();
 		virtual void closed();
}; 

class FinishingWash: public MachineController {
	private:
		int timer = 120;
	public:
		FinishingWash(WashingMachine* wm);
		~FinishingWash(){};
 		virtual void tick();
 		virtual void power();
 		virtual void open();
 		virtual void closed();
}; 

class ClosedDoor: public MachineController {

	public:
		ClosedDoor(WashingMachine* wm);
		~ClosedDoor(){};
 		virtual void tick();
 		virtual void power();
 		virtual void open();
 		virtual void closed();
}; 
