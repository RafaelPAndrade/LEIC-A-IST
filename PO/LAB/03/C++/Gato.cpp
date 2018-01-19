# include "Gato.h"

Gato::Gato(int i, std::string n, int v):
	Animal(i, n), nVidas(v) {}

int Gato::getNVidas() const {
	return nVidas;
}

void Gato::trepar() {
	std::cout << *this << " esta a trepar.\n";
}


bool Gato::operator==(const Gato &gato) {
	return (this->nVidas == gato.nVidas) && ( Animal::operator==(gato) );
}


std::ostream& operator<<(std::ostream &os, const Gato &g) {
	return os << (Animal&) g << " e com "<< g.nVidas << " vidas";
}
