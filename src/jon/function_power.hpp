#ifndef FUNCTION_POWER_H
#define FUNCTION_POWER_H
#include "Function.hpp"

class functionpower: public Function {
	public :
		virtual void simplify(void)   ;
		virtual Node *derive(void)    ;
		virtual Node *integrate(void) ;
		virtual void print(void)      ;

		int power;
};
#endif
