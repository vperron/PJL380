#ifndef FUNCTION_EXP_H
#define FUNCTION_EXP_H
#include "function.hpp"
#include "functions.hpp"

class functionexp: public Function {
	public :
		virtual Node *simplify(void)   ;
		virtual Node *derive(string&)    ;
		virtual Node *integrate(void) ;
		virtual void print(void)      ;

		// (victor) Ajout de constructeurs pour la simplicité, comme d'hab.
		functionexp() { };
		functionexp(Node * n) {
			arg = n;
		};
};
#endif
