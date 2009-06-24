#include <iostream>
#include "operator_plus.hpp"
#include "operator_mult.hpp"
#include "function_power.hpp"
#include "fractional.hpp"
#include "variable.hpp"
#include "math.h"
using namespace std;

/*functionexp::functionexp(const &functionexp) {

  }*/

Node* functionexp::simplify() {
	arg = arg->simplify();	
	fractional *frac = dynamic_cast<fractional*>(arg);
	functionln *func = dynamic_cast<functionln*>(arg);
	if (frac != 0) {
		if ( frac->num == 0 ) {
			return new fractional(1);
		}
	} else if (func != 0) {
		return func->arg;
	}
	return this;
}

Node* functionexp::derive() {
	Node *l = this->arg->derive();
	operatormult *result = new operatormult;
	functionexp *res3 = new functionexp;
	res3->arg = this->arg;
	(result->Args).push_back(l);
	(result->Args).push_back(res3);
	return result;
}
Node* functionexp::integrate() {
	return (Node *) 0;
}
void functionexp::print() {
	cout << "exp("; 
	arg->print();
	cout << ")";
}
