# include <iostream>
# include <string>


class Renderable {
	public:
		virtual std::string render()=0;
		virtual std::string text()=0;

};

class Text: public Renderable {
	private:
		std::string _content;
	public:
		Text(std::string t): _content(t) {}
		virtual std::string text() {
			return _content;
		}

		virtual std::string render() {
			return "<span>" + _content + "<span>";
		}
};


class Formatter: public Renderable {
	private:
		Renderable &_content;
	public:
		Formatter(Renderable &r): _content(r) {}
		virtual std::string text() {
			return _content.text();
		}

		virtual std::string render() {
			return _content.render();
		}
};


class Italic: public Formatter {
	public:
		Italic(Renderable &r): Formatter(r) {}
		virtual std::string render() {
			return "<i>" + Formatter::render() + "</i>";
		}
};

class Bold: public Formatter {
	public:
		Bold(Renderable &r): Formatter(r) {}
		virtual std::string render() {
			return "<b>" + Formatter::render() + "</b>";
		}
};


class Underline: public Formatter {
	public:
		Underline(Renderable &r): Formatter(r) {}
		virtual std::string render() {
			return "<u>" + Formatter::render() + "</u>";
		}
};

int main() {

	Text r("Olá!");
	Italic i(r);
	Bold b(i);
	Underline u(b);

	std::cout << "Rendering: " << u.render() << std::endl;
	std::cout << "Text: " << u.text() << std::endl;

	return 0;
}

