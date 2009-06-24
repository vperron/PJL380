#ifndef VARIABLE_H
#define VARIABLE_H

#include "node.hpp"
#include "regroupable.hpp"
#include <string>

class Variable: public Regroupable {
	public :
		virtual Node *simplify(void)  ;
		virtual Node *derive(void)    ;
		virtual Node *integrate(void) ;
		virtual void print(void)      ;
	       	virtual bool compare(Node *)  ;
		std::string name;
		
};
#endif
