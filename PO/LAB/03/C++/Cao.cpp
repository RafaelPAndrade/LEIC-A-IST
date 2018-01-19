# include "Cao.h"

Cao::Cao(int i, std::string n, int p):
	Animal(i,n), peso(p) {}

int Cao::getPeso() const {
	return peso;
}

void Cao::ladrar() {
	std::cout << *this << " esta a ladrar\n";
}

bool Cao::operator==(Cao &cao) {
	return (this->peso == cao.peso) && (Animal::operator==(cao));
}

std::ostream& operator<<(std::ostream &os, const Cao &c) {
	return os << (Animal&) c << " e com " << c.peso << " kg";
}
