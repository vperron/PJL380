#ifndef FRACTIONAL_H
#define FRACTIONAL_H

#include "node.hpp"

class fractional: public Node {
	public :
		virtual Node *simplify(void)   ;
		virtual Node *derive(void)    ;
		virtual Node *integrate(void) ;
		virtual void print(void)      ;
		int denom;
		int num;
};
#endif
