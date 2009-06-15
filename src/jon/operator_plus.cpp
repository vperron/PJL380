#include <iostream>
#include "operator_plus.hpp"
using namespace std;


void operatorplus::simplify() {
}
Node* operatorplus::derive() {
	for (list<Node *>::iterator i=Args.begin();i!=Args.end();i++) {
		*i = (*i)->derive();
	}
	return this;
}
Node* operatorplus::integrate() {
/*	Node *l = this->args[0]->integrate();
	Node *r = this->args[1]->integrate();
	operatorplus *result = new operatorplus;
	result->args[0] = l;
	result->args[1] = r;
	return result; */
}
void operatorplus::print() {
	for (list<Node *>::iterator i=Args.begin();i!=Args.end();i++) {
		(*i)->print();
		cout <<"+";
	}
}
