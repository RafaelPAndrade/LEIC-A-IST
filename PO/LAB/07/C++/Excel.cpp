# include <vector>
# include <string>
# include <iostream>

template<class FType>
class Formula {
	public:
		virtual FType execute()=0;
};

class Cell {
	private:
		int _line, _column;
	public:
		Cell(int l, int c): _line(l), _column(c) {}
		virtual int get_key() const =0;
		std::string get_position() { return "(" + std::to_string(_line) + ", " + std::to_string(_column) + ")";}
		virtual std::string get_description() {
			return "Celula, " + get_position();
		}
		bool operator<(const Cell &c) const { return get_key() < c.get_key();}
		friend std::ostream &operator<<(std::ostream &os, Cell &c) {
			return os << c.get_description() << std::endl;
		}

};

class NumberCell: public Cell{
	private:
		int _content;
	public:
		NumberCell(int l, int c, int n): Cell(l,c), _content(n) {}
		virtual int get_key() { return _content;}
		virtual std::string get_description() {
			return Cell::get_description() + "[Tipo: Numerico, Valor: "+ std::to_string(_content)+"]";
		}
};

class StringCell: public Cell {
	private:
		std::string _content;
	public:
		StringCell(int l, int c, std::string s): Cell(l,c), _content(s) {}
		virtual int get_key() const { return 0;}
		virtual std::string get_description() {
			return Cell::get_description() + "[Tipo: Cadeia de Caracteres, Valor: "+_content+"]";
		}
};

class PointerCell: public Cell {
	private:
		Cell *_content;
	public:
		PointerCell(int l, int c, Cell *cell): Cell(l,c), _content(cell) {}
		virtual int get_key() {  return _content->get_key(); }
		virtual std::string get_description() {
			return Cell::get_description() + "[Tipo: Referencia, Valor: "+_content->get_position()+"]";
		}
};


class NumericFormulaCell: public Cell {
	private:
		Formula<int>* _content;
	public:
		NumericFormulaCell(int l, int c, Formula<int> *f): Cell(l,c), _content(f) {}
		virtual int execute() { return _content->execute();}
		virtual int get_key() { return _content->execute();}
		virtual std::string get_description() {
			return Cell::get_description() + "[Tipo: Formula Numerica]";
		}
};

class StringFormulaCell: public Cell {
	private:
		Formula<std::string>* _content;
	public:
		StringFormulaCell(int l, int c, Formula<std::string> *f): Cell(l,c), _content(f) {}
		virtual std::string execute() { return _content->execute();}
		virtual int get_key() { return 0;}
		virtual std::string get_description() {
			return Cell::get_description() + "[Tipo: Formula de Cadeia de Caracteres]";
		}
};

class Sheet {
	private:
		std::vector<Cell*> _contents;
	public:
		Sheet(int size): _contents(size) {}
		void addCell(Cell *c) {_contents.push_back(c);}
		friend std::ostream &operator<<(std::ostream &os, Sheet &s) {
			os << "Folha de Calculo\n";
			for(int i=0; i<s._contents.size(); ++i)
				os << s._contents[i];
			return os;
		}
};
