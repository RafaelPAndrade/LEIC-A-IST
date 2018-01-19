# include <iostream>
# include "Motor.cpp"



class Car {
	private:
		std::string Gama;
	protected:
		EconomyMotor *m1;
		Car(std::string g): Gama(g),  m1(new EconomyMotor()) {}
	public:
		Car(): Car("Basica") {}
		~Car() { delete m1; }
		void andar() {
			std::cout << "A iniciar o carro da gama " << Gama << "..." << std::endl;
			m1->ligar();
		}
		void parar() {
			std::cout << "A parar o carro da gama " << Gama << "..." << std::endl;
			m1->desligar();
		}
};


class MediumCar: public Car {
	protected:
		MediumCar(std::string g) : Car(g) {}
	public:
		MediumCar(): Car("Media") {}
		void trocarMotor(EconomyMotor * n) {
			std::cout << "A trocar Motor " << n->getMotorType() << std::endl;
			delete m1;
			m1 = n;
		}
};


class TopCar: public MediumCar {
	private:
		XtremeMotor *m2 = nullptr;
	public:
		TopCar(): MediumCar(" de topo") {}
		~TopCar() { delete m2; }
		void porMotor(XtremeMotor * n) {
			std::cout << "A colocar Motor " << n->getMotorType() << std::endl;
			delete m2;
			m2 = n;
		}
		void andar() {
			Car::andar();
			if (m2 != nullptr) m2->ligar();
		}	
		void parar() {
			Car::parar();
			if (m2 != nullptr) m2->desligar();
		}

};
