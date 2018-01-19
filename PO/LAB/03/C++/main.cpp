# include "Animal.h" 
# include "Gato.h" 
# include "Cao.h" 

int main(){
	Gato a (1, "Tareco", 9);
	Animal b (2);
	Cao c (3, "Bobby", 20);
	Cao d (1, "Bobby", 9);
	a.trepar();
	b.dormir();
	c.ladrar();
	std::cout << (d==c) << "\n";
	std::cout << d << '\n';
	return 0;
}
