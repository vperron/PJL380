#ifndef FUNCTION_LN_H
#define FUNCTION_LN_H
#include "function.hpp"
#include "functions.hpp"

class functionln: public Function {
	public :
		virtual Node *simplify(void)   ;
		virtual Node *derive(void)    ;
		virtual Node *integrate(void) ;
		virtual void print(void)      ;

		int power;

		// (victor) Ajout de constructeurs pour la simplicité, comme d'hab.
		functionln() { };
		functionln(int p, Node * n) {
			power = p;
			arg = n;
		};
};
#endif
