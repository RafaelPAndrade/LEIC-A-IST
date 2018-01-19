# include <iostream>
# include <vector>
# include "Printer.cpp"

class Table {
	private:
		std::vector<int> values;
	public:
		Table(int size): values(size) {}

		void print(Printer* p) {
			int i;
			for(i=0; i<values.size(); ++i)
				std::cout << p->format(values[i]) << std::endl;
		}

		void setValuePos(int val, int pos) {
			if(pos < values.size()) values[pos] = val;
		}
};
