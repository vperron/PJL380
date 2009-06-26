#include <iostream>
#include "operator_plus.hpp"
#include "operator_mult.hpp"
#include "function_power.hpp"
#include "fractional.hpp"
#include "variable.hpp"
#include "math.h"
using namespace std;

/*functionsin::functionsin(const &functionsin) {

  }*/

Node* functionsin::simplify() {
	arg = arg->simplify();	
	return this;
}
Node* functionsin::derive() {
	Node *l = this->arg->derive();
	operatormult *result = new operatormult;
	functioncos *res3 = new functioncos;
	res3->arg = this->arg;
	(result->Args).push_back(l);
	(result->Args).push_back(res3);
	return result;
}
Node* functionsin::integrate() {
	return (Node *) 0;
}
void functionsin::print() {
	cout << "sin("; 
	arg->print();
	cout << ")";
}
