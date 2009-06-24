#ifndef FRACTIONAL_H
#define FRACTIONAL_H

#include "node.hpp"

class fractional: public Node {
	public :
		virtual fractional *simplify(void)   ;
		virtual Node *derive(void)    ;
		virtual Node *integrate(void) ;
		virtual void print(void)      ;
	       	virtual bool compare(Node*);
		int denom;
		int num;
};
#endif
