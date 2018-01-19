
class MachineController;

class WashingMachine {
	private:
		MachineController* _dc;
	public:
		WashingMachine();
		~WashingMachine();
		void tick();
		void power();
		void open();
		void closed();
		friend class MachineController;
};
