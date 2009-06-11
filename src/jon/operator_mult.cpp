#include <iostream>
#include "operator_mult.hpp"
#include "operator_plus.hpp"
using namespace std;


void operatormult::simplify() {
	cout << "coucou" << endl;
}
Node* operatormult::derive() {
	Node *l = this->args[0]->derive();
	Node *r = this->args[1]->derive();
	operatormult *res = new operatormult;
	operatormult *res1 = new operatormult;
	operatorplus *result = new operatorplus;
	res->args[0] = l;
	res->args[1] = this->args[1];
	res1->args[0] = this->args[0];
	res1->args[1] = r;
	result->args[0] = res;
	result->args[1] = res1;
	return result;
}
Node* operatormult::integrate() {
	Node *l = this->args[0]->integrate();
	Node *r = this->args[1]->integrate();
	operatormult *result = new operatormult;
	result->args[0] = l;
	result->args[1] = r;
	return result;
}
void operatormult::print() {
	args[0]->print();
	cout << '*'; 
	args[1]->print();
}
