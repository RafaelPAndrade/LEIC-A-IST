
# ifndef _GATO_
# define _GATO_

# include "Animal.h"


class Gato: public Animal {
		int nVidas;
	public:
		Gato(int i, std::string n, int v);
		int getNVidas() const;
		void trepar();
		bool operator==(const Gato &gato);
		friend std::ostream& operator<<(std::ostream &o, const Gato &g);
};

# endif
