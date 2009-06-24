#ifndef FUNCTION_POWER_H
#define FUNCTION_POWER_H
#include "function.hpp"

class functionpower: public Function {
	public :
		virtual Node *simplify(void)   ;
		virtual Node *derive(void)    ;
		virtual Node *integrate(void) ;
		virtual void print(void)      ;

		int power;

		// (victor) Ajout de constructeurs pour la simplicité, comme d'hab.
		functionpower() { };
		functionpower(int p, Node * n) {
			power = p;
			arg = n;
		};
};
#endif
