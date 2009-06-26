#ifndef FUNCTION_COS_H
#define FUNCTION_COS_H
#include "function.hpp"
#include "functions.hpp"

class functioncos: public Function {
	public :
		virtual Node *simplify(void)   ;
		virtual Node *derive(string&)    ;
		virtual Node *integrate(void) ;
		virtual void print(void)      ;


		// (victor) Ajout de constructeurs pour la simplicité, comme d'hab.
		functioncos() { };
		functioncos(Node * n) {
			arg = n;
		};
};
#endif
