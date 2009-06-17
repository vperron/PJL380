#include <iostream>
#include "operator_plus.hpp"
#include "fractional.hpp"
using namespace std;


Node* operatorplus::simplify() {
	for (list<Node *>::iterator i=Args.begin();i!=Args.end();i++) {
		*i = (*i)->simplify();
	}

	for (list<Node *>::iterator i=Args.begin();i!=Args.end();i++) {
		fractional* ii = dynamic_cast<fractional*>(*i);
		if (ii!=0) {
			if (ii->num == 0) {
				i = Args.erase(i);
				i--;
			}	
		}
	}
	if (Args.size() == 1) return Args.front();
	else return this;
}
Node* operatorplus::derive() {
	cout << "plus derive" << endl;
	for (list<Node *>::iterator i=Args.begin();i!=Args.end();i++) {
		*i = (*i)->derive();
	}
	cout << endl << "plus derive end" << endl;
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
	list<Node *>::iterator beforelast = --Args.end();
	for (list<Node *>::iterator i=Args.begin();i!=Args.end();i++) {
		(*i)->print();
		if (i!=beforelast) cout <<"+";
	}
}
