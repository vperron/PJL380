#ifndef FUNCTION_SIN_H
#define FUNCTION_SIN_H
#include "function.hpp"
#include "functions.hpp"

class functionsin: public Function {
	public :
		virtual Node *simplify(void)   ;
		virtual Node *derive(string&)    ;
		virtual Node *integrate(void) ;
		virtual void print(void)      ;


		// (victor) Ajout de constructeurs pour la simplicité, comme d'hab.
		functionsin() { };
		functionsin(Node * n) {
			arg = n;
		};
};
#endif
