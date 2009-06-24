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
			(*i)->print();
			for (list<Node *>::iterator j = temp->Args.begin();j!= temp->Args.end(); j++) {
				Args.push_front(*j);
			}
			i = Args.erase(i);
			i--;
		}

	}
}
void operatorplus::simplify_fractionnals() {
	for (list<Node *>::iterator i=Args.begin();i!=Args.end();i++) {
		fractional* ii = dynamic_cast<fractional*>(*i);
		if (ii!=0 ) {
			for (list<Node *>::iterator j=Args.begin();j!=Args.end();j++) {
				fractional* jj = dynamic_cast<fractional*>(*j);
				if (jj!=0 && i != j) {
					fractional *result = new fractional;
					result->denom = ii->denom * jj->denom;
					result->num = ii->num * jj->denom + ii->denom * jj->num;
					result = result->simplify();
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
*/
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
