#include <iostream>
#include "operator_plus.hpp"
#include "operator_mult.hpp"
#include "function_power.hpp"
#include "fractional.hpp"
#include "variable.hpp"
using namespace std;

/*functionpower::functionpower(const &functionpower) {

  }*/

Node* functionpower::simplify() {
	//TODO : simplifier recurisivement
	switch (this->power) {
		case 0: {
				fractional *res = new fractional;
				res->num = 1;
				res->denom = 1;
				return res;
			}	
		case 1:
			return this->arg;
		default: 
			return this;
	}
}
Node* functionpower::derive() {
	cout << "power derive" << endl;
	if (this->power != 1) { //TODO passer en fractional
		Node *l = this->arg->derive();
		operatormult *result = new operatormult;
		fractional *res2 = new fractional;
		functionpower *res3 = new functionpower;
		res2->num = this->power;
		res2->denom = 1;
		res3->power = this->power - 1;
		res3->arg = this->arg;
		(result->Args).push_back(l);
		(result->Args).push_back(res2);
		(result->Args).push_back(res3);
		return result;
	}
	else {
		return this->arg->derive();
	}
}
Node* functionpower::integrate() {
	return (Node *) 0;
}
void functionpower::print() {
	cout << '('; 
	arg->print();
	cout << ")^" << this->power;
}
