# include <iostream> 
# include <string> 

# ifndef _ANIMAL_
# define _ANIMAL_

class Animal {
	private:
		int idade;
		std::string nome;
	public:
		Animal(int i, std::string n);
		Animal(int i);
		void dormir();
		// Getters
		int getIdade() const;
		std::string getNome() const;
		bool operator==(const Animal &animal);
		friend std::ostream& operator<<(std::ostream &o, const Animal &a);
};

# endif
