#ifndef VARIABLE_H
#define VARIABLE_H

#include "node.hpp"
#include <string>

class Variable: public Node {
	public :
		virtual Node *simplify(void)   ;
		virtual Node *derive(void)    ;
		virtual Node *integrate(void) ;
		virtual void print(void)      ;
		std::string name;
};
#endif
