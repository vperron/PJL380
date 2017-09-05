#include <iostream>
#include "operator_plus.hpp"
#include "operator_mult.hpp"
#include "function_power.hpp"
#include "fractional.hpp"
#include "variable.hpp"
#include "math.h"
using namespace std;

/*functioncos::functioncos(const &functioncos) {

  }*/

Node* functioncos::simplify() {
	arg = arg->simplify();	
	return this;
}
Node* functioncos::derive(string &s) {
	Node *l = this->arg->derive(s);
	operatormult *result = new operatormult;
	functionsin *res3 = new functionsin;
	res3->arg = this->arg;
	(result->Args).push_back(l);
	(result->Args).push_back(res3);
	operatormult *negresult = new operatormult;
	(negresult->Args).push_back(new fractional(-1));
	(negresult->Args).push_back(result);
	return negresult;
}
Node* functioncos::integrate() {
	return (Node *) 0;
}
void functioncos::print() {
	cout << "cos("; 
	arg->print();
	cout << ")";
}
