#ifndef FUNCTION_EXP_H
#define FUNCTION_EXP_H
#include "function.hpp"
#include "functions.hpp"

class functionexp: public Function {
	public :
		virtual Node *simplify(void)   ;
		virtual Node *derive(void)    ;
		virtual Node *integrate(void) ;
		virtual void print(void)      ;

		int power;

		// (victor) Ajout de constructeurs pour la simplicité, comme d'hab.
		functionexp() { };
		functionexp(int p, Node * n) {
			power = p;
			arg = n;
		};
};
#endif