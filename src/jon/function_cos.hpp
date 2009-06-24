#ifndef FUNCTION_COS_H
#define FUNCTION_COS_H
#include "function.hpp"
#include "functions.hpp"

class functioncos: public Function {
	public :
		virtual Node *simplify(void)   ;
		virtual Node *derive(void)    ;
		virtual Node *integrate(void) ;
		virtual void print(void)      ;

		int power;

		// (victor) Ajout de constructeurs pour la simplicité, comme d'hab.
		functioncos() { };
		functioncos(int p, Node * n) {
			power = p;
			arg = n;
		};
};
#endif
