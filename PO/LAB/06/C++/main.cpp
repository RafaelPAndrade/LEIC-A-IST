# include "Beneficiaries.cpp"
# include <iostream>

int main() {

	Individual a,b,c,d;
	Village u,v;
	Region r,s;

	u.add_people(&a);
	v.add_people(&b);
	v.add_people(&c);
	
	r.add_village(&u);
	r.add_people(&d);
	s.add_village(&v);
	

	r.receive_help(10);
	d.receive_help(5);
	s.receive_help(10);
	v.receive_help(20);

	std::cout << "Region r has got a total of " << r.get_help_received() << std::endl;

	std::cout << "Region s has got a total of " << s.get_help_received() << std::endl;

	std::cout << "Individual d has got a total of " << d.get_help_received() << std::endl;

	return 0;
}
