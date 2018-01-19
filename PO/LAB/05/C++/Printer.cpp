# include <iostream>

class Printer {
	public:
		virtual std::string format(int i)=0;
};


class BracketsPrinter: public Printer {
	public:
		virtual std::string format(int i) {
			return "[" + std::to_string(i) + "]";
		}
};

class DuplicatePrinter: public Printer {
	public:
		virtual std::string format(int i) {
			std::string res = std::to_string(i);
			return res + '\n' + res;
		}
};
