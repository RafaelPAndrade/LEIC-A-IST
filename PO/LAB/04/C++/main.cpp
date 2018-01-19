# include "Car.cpp"

int main() {


	Car a;
	MediumCar b;
	TopCar c;

    a.andar();
    b.parar();
    b.trocarMotor(new EconomyMotor());
    c.andar();
    c.porMotor(new XtremeMotor());
    c.andar();
	TopCar d;
}
