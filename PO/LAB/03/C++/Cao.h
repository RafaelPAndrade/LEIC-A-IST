
# ifndef _CAO_
# define _CAO_

# include "Animal.h"

class Cao: public Animal {
		int peso;
	public:
		Cao(int i, std::string n, int p);
		int getPeso() const;
		void ladrar();
		bool operator==(Cao &cao);
		friend std::ostream& operator<<(std::ostream &os, const Cao &c);
};

# endif
