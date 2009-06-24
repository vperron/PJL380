#ifndef VARIABLE_H
#define VARIABLE_H

#include "node.hpp"

#include "regroupable.hpp"
#include <string>

// (victor) Plus cool avec le namespace ;)
using namespace std;

class Variable: public Regroupable {
	public :
		virtual Node *simplify(void)  ;
		virtual Node *derive(void)    ;
		virtual Node *integrate(void) ;
		virtual void print(void)      ;
	       	virtual bool compare(Node *)  ;
		string name;
		
        // Added new constructor (victor)
        Variable(string s = string()) { 
            // On est sereins, l'operateur = de string effectue une COPIE
            name = s;
        }
};
#endif
