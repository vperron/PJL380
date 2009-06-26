#include <iostream>
#include "operator_plus.hpp"
#include "operator_mult.hpp"
#include "function_power.hpp"
#include "fractional.hpp"
#include "variable.hpp"
#include "math.h"
using namespace std;

/*functionln::functionln(const &functionln) {

  }*/

Node* functionln::simplify() {
	arg = arg->simplify();	
	fractional *frac = dynamic_cast<fractional*>(arg);
	functionexp *func = dynamic_cast<functionexp*>(arg);
	if (frac != 0) {
		if ( frac->num == 1 ) {
			return new fractional(0);
		}
	}
	else if (func != 0) {
		return func->arg;
	}
	return this;
}

Node* functionln::derive(string &s) {
	Node *l = this->arg->derive(s);
	operatormult *result = new operatormult;
	functionpower *res2 = new functionpower;
	res2->power = -1;
	res2->arg = this->arg;
	(result->Args).push_back(l);
	(result->Args).push_back(res2);
	return result;
}
Node* functionln::integrate() {
	return (Node *) 0;
}
void functionln::print() {
	cout << "ln("; 
	arg->print();
	cout << ")";
}
