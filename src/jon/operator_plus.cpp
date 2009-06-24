#include <iostream>
#include "operator_plus.hpp"
#include "fractional.hpp"
using namespace std;

bool operatorplus::compare(Node *a) {
	(Operator *)this->compare(a);	
}

void operatorplus::flatten() {
	for (list<Node *>::iterator i = Args.begin();i!= Args.end(); i++) {
		operatorplus *temp = dynamic_cast<operatorplus*>(*i);
		if (temp != 0) {
			for (list<Node *>::iterator j = temp->Args.begin();j!= temp->Args.end(); j++) {
				Args.push_front(*j);
			}
			i = Args.erase(i);
			i--;
		}

	}
}
void operatorplus::simplify_fractionnals() {
	fractional *first_fractional_found_ptr = 0;
	for (list<Node *>::iterator i=Args.begin();i!=Args.end();i++) {
		fractional* ii = dynamic_cast<fractional*>(*i);
		if (ii!=0) {
			if (first_fractional_found_ptr == 0) {
				first_fractional_found_ptr = ii;
				i = Args.erase(i);
				i--;
			}
			else {
				fractional *result = new fractional;
				result->denom = ii->denom * first_fractional_found_ptr->denom;
				result->num = ii->num * first_fractional_found_ptr->denom + ii->denom * first_fractional_found_ptr->num;
				result = result->simplify();
				first_fractional_found_ptr = result; 
				i = Args.erase(i);
				i--;
			}
		}
	}	
	Args.push_back(first_fractional_found_ptr);
}


void operatorplus::remove_zeros(){
	for (list<Node *>::iterator i=Args.begin();i!=Args.end();i++) {
		fractional* ii = dynamic_cast<fractional*>(*i);
		if (ii!=0) {
			if (ii->num == 0) {
				i = Args.erase(i);
				i--;
			}	
		}
	}
}


Node* operatorplus::simplify() {
	flatten();
	for (list<Node *>::iterator i=Args.begin();i!=Args.end();i++) {
		*i = (*i)->simplify();
	}
	remove_zeros();
	simplify_fractionnals();
	if (Args.size() == 1) return Args.front();
	else return this;
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
	list<Node *>::iterator beforelast = --Args.end();
	cout << "(";
	for (list<Node *>::iterator i=Args.begin();i!=Args.end();i++) {
		(*i)->print();
		if (i!=beforelast) cout <<"+";
	}
	cout << ")";
}

operatorplus::operatorplus() {
}
