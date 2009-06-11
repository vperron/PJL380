#include <iostream>
#include "variable.hpp"
#include "fractional.hpp"
using namespace std;

Node* Variable::derive() {
	fractional* result = new fractional;
	result->num = 1;
	result->denom = 1;
	return result;
}


void Variable::simplify() {
	cout << "coucou" << endl;
}
Node* Variable::integrate() {
	/*Node *l = this->args[0]->integrate();
	Node *r = this->args[1]->integrate();
	Node *result = new operatormult;
	result->args[0] = l;
	result->args[1] = r;
	return result;*/
	return this;
}
void Variable::print() {
	cout << this->name;
}
