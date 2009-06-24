#ifndef FUNCTION_SIN_H
#define FUNCTION_SIN_H
#include "function.hpp"
#include "functions.hpp"

class functionsin: public Function {
	public :
		virtual Node *simplify(void)   ;
		virtual Node *derive(void)    ;
		virtual Node *integrate(void) ;
		virtual void print(void)      ;

		int power;

		// (victor) Ajout de constructeurs pour la simplicité, comme d'hab.
		functionsin() { };
		functionsin(int p, Node * n) {
			power = p;
			arg = n;
		};
};
#endif
