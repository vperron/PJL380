#ifndef OPERATOR_PLUS_H
#define OPERATOR_PLUS_H
#include "operator.hpp"

class operatorplus: public Operator {
	public :
		virtual Node *simplify(void)   ;
		virtual Node *derive(void)    ;
		virtual Node *integrate(void) ;
		virtual void print(void)      ;

};
#endif
