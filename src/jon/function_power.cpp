#include <iostream>
#include "operator_plus.hpp"
#include "operator_mult.hpp"
#include "function_power.hpp"
#include "fractional.hpp"
#include "variable.hpp"
using namespace std;

/*functionpower::functionpower(const &functionpower) {
	
}*/

void functionpower::simplify() {
	cout << "coucou" << endl;
}
Node* functionpower::derive() {
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
Node* functionpower::integrate() {
	return (Node *) 0;
}
void functionpower::print() {
	cout << '('; 
	arg->print();
	cout << ")^" << this->power;
}
