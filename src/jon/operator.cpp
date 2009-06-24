#include "operator.hpp"
#include <typeinfo>
using namespace std;

bool Operator::compare(Node *a) {
	//checker meme type
	Operator *op = dynamic_cast<Operator*>(a);
	if (op != 0) {
		for (list<Node *>::iterator i=Args.begin();i!=Args.end();i++) {
			if (Args.size() == op->Args.size()) {
				bool found = false;
				for (list<Node *>::iterator j=Args.begin();j!=Args.end();j++) {
					found = (*j)->compare(*i);
				}
				if (!found) return false;
			}
			else return false;
		}
	}
	return true;
}

Operator::Operator() {

}
