#include <iostream>
#include "operator_mult.hpp"
#include "operator_plus.hpp"
#include "fractional.hpp"
#include "variable.hpp"
#include "function_power.hpp"
using namespace std;


bool operatorplus::compare(Node *a) {
	(Operator *)this->compare(a);	
}

void operatormult::remove_ones() {
	for (list<Node *>::iterator i=Args.begin();i!=Args.end();i++) {
		fractional* ii = dynamic_cast<fractional*>(*i);
		if (ii!=0) {
			if (ii->num == ii->denom) {
				i = Args.erase(i);
				i--;
			}
		}
	}
}

Node * operatormult::get_zero() {

	for (list<Node *>::iterator i=Args.begin();i!=Args.end();i++) {
		fractional* ii = dynamic_cast<fractional*>(*i);
		if (ii!=0) {
			if (ii->num == 0) {
				return ii;
			}	
		}
	}
	return 0; 
}

void operatormult::simplify_fractionnals() {
	for (list<Node *>::iterator i=Args.begin();i!=Args.end();i++) {
		fractional* ii = dynamic_cast<fractional*>(*i);
		if (ii!=0 ) {
			for (list<Node *>::iterator j=Args.begin();j!=Args.end();j++) {
				fractional* jj = dynamic_cast<fractional*>(*j);
				if (jj!=0 && i != j) {
					fractional *result = new fractional;
					result->denom = ii->denom * jj->denom;
					result->num = ii->num * jj->num;
					Args.insert(i,result);
					i = Args.erase(i);
					i--;
					j = Args.erase(j);
					j--;
				}
			}
		}
	}	
/*	for (list<Node *>::iterator i=Args.begin();i!=Args.end();i++) {
		fractional* ii = dynamic_cast<fractional*>(*i);
		if (ii!=0 ) {
			for (list<Node *>::iterator j=Args.begin();j!=Args.end();j++) {
*/}

void operatormult::simplify_regroupables() {
	for (list<Node *>::iterator i=Args.begin();i!=Args.end();i++) {
		Regroupable* ii = dynamic_cast<Regroupable*>(*i);
		int count = 1;
		if (ii!=0) {
			for (list<Node *>::iterator j=Args.begin();j!=Args.end();j++) {
				Regroupable* jj = dynamic_cast<Regroupable*>(*j);
				if (jj!=0 && jj->compare(ii) && i!=j ) {
				       	count++;
					j = Args.erase(j);
					j--;
				}
			}
		}
		if (count>1) {
			i = Args.erase(i);
			i--;
			functionpower *toto = new functionpower;
			toto->power = count;
			toto->arg = ii;
			Args.push_back(toto);	
		}
	}
}

void operatormult::flatten() {
	for (list<Node *>::iterator i = Args.begin();i!= Args.end(); i++) {
		operatormult *temp = dynamic_cast<operatormult*>(*i);
		if (temp != 0) {
			for (list<Node *>::iterator j = temp->Args.begin();j!= temp->Args.end(); j++) {
				Args.push_front(*j);
			}
			i = Args.erase(i);
			i--;
		}

	}
}

Node* operatormult::simplify() {
	flatten();
	for (list<Node *>::iterator i=Args.begin();i!=Args.end();i++) {
		*i = (*i)->simplify();
	}

	remove_ones();

	//if there is at least one zero, the whole expression is this zero
	Node *test = get_zero();
	if (test != 0) return test;
	simplify_fractionnals();
	remove_ones();
	simplify_regroupables();
	if (Args.size() == 1) return Args.front();
	else return this;
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
	return this;
}
void operatormult::print() {
	list<Node *>::iterator beforelast = --Args.end();
	cout << "(";
	for (list<Node *>::iterator i=Args.begin();i!=Args.end();i++) {
		(*i)->print();
		if (i!=beforelast) cout <<"*";
	}
	cout << ")";
}
