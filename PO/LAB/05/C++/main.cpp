# include "Table.cpp"

int main() {

	Table ola(5);
	Table adeus(2);
	BracketsPrinter a;
	DuplicatePrinter b;

	ola.print(&a);
	adeus.print(&b);
}
