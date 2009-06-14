#ifndef OPERATOR_MULT_H
#define OPERATOR_MULT_H
#include "Operator.hpp"

class operatormult: public Operator {
	public :
		virtual void simplify(void)   ;
		virtual Node *derive(void)    ;
		virtual Node *integrate(void) ;
		virtual void print(void)      ;
};
#endif
