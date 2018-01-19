# include <string>
# include <iostream>
# include <sstream>

class Cat {
	private:
		std::string _name;
		float _age;
	public:
		Cat(): _name("anonimo"), _age(0) {}
		Cat(std::string n, float a)
		:_name(n), _age(a) {}
		float getAge() { return _age; }
		std::string getName() { return _name; }
		void setAge(float a) { _age = a; }
		void setName(std::string n) { _name = n; }
};

std::ostream& operator<<(std::ostream &os, Cat &c) {
	return os << c.getName() << " " << c.getAge() << "\n";
}

std::istream& operator>>(std::istream &is, Cat &c) {
	std::string n;
	float a;
	is >> n >> a;
	c.setName(n);
	c.setAge(a);
	return is;
}

int main() {

	Cat c1("Tareco", 2);
	Cat c2("Pantufa", 0.5);
	
	std::stringstream buffer;
	buffer << c1 << c2;

	Cat c3;
	Cat c4;

	buffer >> c3 >> c4;

	std::cout << c3 << c4;

	return 0;
}
