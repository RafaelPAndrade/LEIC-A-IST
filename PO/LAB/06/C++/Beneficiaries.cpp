# include <vector>

class Beneficiary {
	public:
		virtual void receive_help(int h)=0;
		virtual int get_help_received()=0;
};

class Individual: public Beneficiary {
	private:
		int help_received=0;
	public:
		virtual void receive_help(int h) {
			help_received+=h;
		}
		virtual int get_help_received(){
			return help_received;
		};
};

class Village: public Beneficiary {
	private:
		std::vector<Individual*> population;
	public:
		void add_people(Individual *i) {
			population.push_back(i);
		}
		virtual void receive_help(int h) {
			int i;
			for(i=0; i < population.size(); ++i)
				population[i]->receive_help(h/population.size());
		}
		virtual int get_help_received() {
			int res=0, i;
			for (i=0; i < population.size(); ++i)
				res+=population[i]->get_help_received();
			return res;
		}
};


class Region: public Beneficiary {
	private:
		std::vector<Beneficiary*> subgroups;
	public:
		void add_people(Individual* i) {
			subgroups.push_back(i);
		}
		void add_village(Village* v) {
			subgroups.push_back(v);
		}

		virtual void receive_help(int h) {
			int i;
			for(i=0; i < subgroups.size(); ++i)
				subgroups[i]->receive_help(h/subgroups.size());
		}
		virtual int get_help_received() {
			int res=0, i;
			for (i=0; i < subgroups.size(); ++i)
				res+=subgroups[i]->get_help_received();
			return res;
		}
};
