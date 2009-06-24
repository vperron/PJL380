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

        // Added a new constructor (victor)
        fractional(const int n, const int d = 1) {
            denom = d;
            num   = n;
        }

        fractional();

		int denom;
		int num;
};
#endif
