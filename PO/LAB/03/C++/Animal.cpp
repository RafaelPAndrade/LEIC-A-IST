# include "Animal.h"

Animal::Animal(int i, std::string n): idade(i), nome(n) {}
Animal::Animal(int i): Animal(i, "") {}

std::string Animal::getNome() const {
	return nome;
}

int Animal::getIdade() const {
	return idade;
}

void Animal::dormir() {
	std::cout << *this << " esta a dormir.\n";
}

bool Animal::operator==(const Animal &animal) {
	return (this->idade == animal.idade) && (!this->nome.compare(animal.nome));}

std::ostream& operator<<(std::ostream &os, const Animal &a) {
	std::string res;
	if(a.nome.compare(""))
		res = a.nome;
	else
		res = "<Animal>";
	return os << res << " com " << a.idade << " anos";
}


