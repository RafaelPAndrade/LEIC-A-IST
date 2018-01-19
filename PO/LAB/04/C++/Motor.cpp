# include <iostream>


class Motor {
	std::string type;
	protected:
		Motor(std::string t): type(t) {}
	public:
		void ligar() {
			std::cout << "A ligar motor " << type << std::endl;
		}
		void desligar() {
			std::cout << "A desligar motor " << type << std::endl;
		}
		std::string getMotorType() {
			return type;
		}
};



class EconomyMotor : public Motor {
	public:
		EconomyMotor(): Motor("Economy") {}
};


class XtremeMotor : public Motor {
	public:
		XtremeMotor(): Motor("Xtreme") {}
};
