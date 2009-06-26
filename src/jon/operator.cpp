#include "operator.hpp"
#include <iostream>
#include <typeinfo>
using namespace std;

bool Operator::compare(Node *a) {
	if (typeid(*this) != typeid(*a)) return false;
	Operator *op = dynamic_cast<Operator*>(a);
	if (op != 0) {
		if (Args.size() == op->Args.size()) {
			for (list<Node *>::iterator i=Args.begin();i!=Args.end();i++) {
				bool found = false;
				for (list<Node *>::iterator j=op->Args.begin();j!=op->Args.end();j++) {
					found = (*j)->compare(*i) ;
					if (found) {
						break;
					}

				}
				if (!found) {
					return false;
				}
			}
		}
		else return false;
	}
	return true;
}

Operator::Operator() {}

Operator::Operator(Node *a,Node *b) {
	this->Args.push_back(a);
	this->Args.push_back(b);
}
