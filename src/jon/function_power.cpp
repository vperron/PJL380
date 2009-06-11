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
	operatormult *res1 = new operatormult;
	fractional *res2 = new fractional;
	functionpower *res3 = new functionpower;//TODO : constructeur de copie
	result->args[0] = l;
	result->args[1] = res1;
	res2->num = this->power;
	res2->denom = 1;
	res3->power = this->power - 1;
	res3->arg = this->arg;
	res1->args[0] = res2;
	res1->args[1] = res3;
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
