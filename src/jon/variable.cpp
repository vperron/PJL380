#include <iostream>
#include "variable.hpp"
#include "fractional.hpp"
using namespace std;


Node* Variable::derive(string& the_name) {
	fractional* result = new fractional;
	if (name.compare(the_name) == 0) {
		result->num = 1;
	}
	else {
		result->num = 0;
	}
	result->denom = 1;
	return result;
}

bool Variable::compare(Node *a) {
	Variable* v= dynamic_cast<Variable *>(a);
	if (v!=0) {
		return (0 == name.compare(v->name));
	}
	else return false;
}


Node* Variable::simplify() {
	return this;
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
