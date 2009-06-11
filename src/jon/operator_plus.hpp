#ifndef OPERATOR_PLUS_H
#define OPERATOR_PLUS_H
#include "node.hpp"

class operatorplus: public Operator {
	public :
		virtual void simplify(void)   ;
		virtual Node *derive(void)    ;
		virtual Node *integrate(void) ;
		virtual void print(void)      ;
};
#endif
