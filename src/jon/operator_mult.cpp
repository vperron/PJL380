#include <iostream>
#include "operator_mult.hpp"
#include "operator_plus.hpp"
#include "fractional.hpp"
using namespace std;


Node* operatormult::simplify() {

	for (list<Node *>::iterator i=Args.begin();i!=Args.end();i++) {
		*i = (*i)->simplify();
	}

	for (list<Node *>::iterator i=Args.begin();i!=Args.end();i++) {
		fractional* ii = dynamic_cast<fractional*>(*i);
		if (ii!=0) {
			if (ii->num == 0) {
				return ii;
			}	
			if (ii->num == ii->denom) {
				i = Args.erase(i);
				i--;
			}
		}
	}
	for (list<Node *>::iterator i=Args.begin();i!=Args.end();i++) {
		for (list<Node *>::iterator j=Args.begin();j!=Args.end();j++) {
			fractional* ii = dynamic_cast<fractional*>(*i);
			fractional* jj = dynamic_cast<fractional*>(*j);
			if (ii !=0 && jj!=0 && ii != jj) {
				ii->denom*=jj->denom;
				ii->num*=jj->num;
				j = Args.erase(j);
				j--;
			}
		}
	}

	if (Args.size() == 1) return Args.front();
	else return this;
}
Node* operatormult::derive() {
	cout << "mult derive" << endl;
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
	return this;
}
void operatormult::print() {
	list<Node *>::iterator beforelast = --Args.end();
	for (list<Node *>::iterator i=Args.begin();i!=Args.end();i++) {
		(*i)->print();
		if (i!=beforelast) cout <<"*";
	}
}
