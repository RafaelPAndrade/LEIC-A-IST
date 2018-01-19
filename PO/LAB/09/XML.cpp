# include <string>
# include <vector>
# include <iostream>

# define INDENT "  "

class Element {
	public:
		std::string indentMaker(int indentLevel) {
			std::string res = "";
			for(int i=0; i<indentLevel; ++i)
				res+= INDENT;
			return res;
		}
		virtual std::string render(int indentLevel)=0;
};

class Container: public Element {
	protected:
		std::vector<Element*> _elements;
	public:
		void addElement(Element *e) {_elements.push_back(e);}
		std::string renderElements(int indentLevel) {
			std::string res;
			for(int i=0; i<_elements.size(); ++i) {
				res += _elements[i]->render(indentLevel) +"\n";
			}
			return res;
		}
};


class Page: public Container {
	public:
		virtual std::string render(int indentLevel) {
			std::string res = "";
			res += Element::indentMaker(indentLevel) + "<page>\n";
			res += Container::renderElements(indentLevel+1);
			res += Element::indentMaker(indentLevel) + "</page>";
			return res;
		}
};


class Paragraph: public Container {
	public:
		virtual std::string render(int indentLevel) {
			std::string res = "";
			res += Element::indentMaker(indentLevel) + "<p>\n";
			res += Container::renderElements(indentLevel+1);
			res += Element::indentMaker(indentLevel) + "</p>";
			return res;
		}
};

class Span: public Element {
	private:
		std::string _text;
	public:
		Span(std::string t): _text(t) {}
		virtual std::string render(int indentLevel) {
			return Element::indentMaker(indentLevel) + "<span>" + _text + "</span>";
		}
};



class Image: public Element {
	public:
		virtual std::string render(int indentLevel) {
			return Element::indentMaker(indentLevel) + "<img src=\"IMG\"/>";
		}
};

int main() {
	Page page;
	Paragraph p1;
	Paragraph p2;
	Span t1("TEXT");
	Span t2("TEXT");
	Image i;

	p1.addElement(&t1);
	p1.addElement(&t2);

	p2.addElement(&i);

	page.addElement(&p1);
	page.addElement(&p2);


	std::cout << page.render(0);
	return 0;
}
