#include <iostream>
#include "operator_plus.hpp"
using namespace std;


void operatorplus::simplify() {
	cout << "coucou" << endl;
}
Node* operatorplus::derive() {
	Node *l = this->args[0]->derive();
	Node *r = this->args[1]->derive();
	operatorplus *result = new operatorplus;
	result->args[0] = l;
	result->args[1] = r;
	return result;
}
Node* operatorplus::integrate() {
	Node *l = this->args[0]->integrate();
	Node *r = this->args[1]->integrate();
	operatorplus *result = new operatorplus;
	result->args[0] = l;
	result->args[1] = r;
	return result;
}
void operatorplus::print() {
	args[0]->print();
	cout << '+'; 
	args[1]->print();
}
