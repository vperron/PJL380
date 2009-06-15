#include <iostream>
#include "operator_mult.hpp"
#include "operator_plus.hpp"
using namespace std;


void operatormult::simplify() {
	cout << "coucou" << endl;
}
Node* operatormult::derive() {
	operatorplus* result = new operatorplus();
	for (list<Node *>::iterator i=Args.begin();i!=Args.end();i++) {
		operatormult* temp = new operatormult();
		for (list<Node *>::iterator j=Args.begin();j!=Args.end();j++) {
			if (i == j) {
				(temp->Args).push_back(*i);	
			}
			else {
				(temp->Args).push_back((*j)->derive());	
			}
		}
		(result->Args).push_back(temp);
	}
	return result;
}
Node* operatormult::integrate() {
	/*
	   Node *l = this->args[0]->integrate();
	Node *r = this->args[1]->integrate();
	operatormult *result = new operatormult;
	result->args[0] = l;
	result->args[1] = r;
	*/
	return this;
}
void operatormult::print() {
	for (list<Node *>::iterator i=Args.begin();i!=Args.end();i++) {
		(*i)->print();
		cout <<"*";
	}
}
