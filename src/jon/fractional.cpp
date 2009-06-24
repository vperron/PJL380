#include <iostream>
#include "fractional.hpp"
using namespace std;

bool fractional::compare(Node* a) {
	/*fractional *b = dynamic_cast<fractional*> a;
	if (b != 0) {
		return (b->num==num && b->denom=denom);
	}*/
	return false;
}

Node* fractional::derive() {
	fractional * res = new fractional;
	res->num = 0;
	res->denom = 1;
	return res;
}

fractional* fractional::simplify() {
	int divisor = 2;
	while ((divisor <= denom) && (divisor <= num)) {
		if ((denom % divisor == 0) && (num % divisor == 0)) {
			denom /= divisor;
			num /= divisor;
		}
		else {
			divisor++;
		}
	}
	return this;
}
Node* fractional::integrate() {
	/*Node *l = this->args[0]->integrate();
	Node *r = this->args[1]->integrate();
	Node *result = new operatormult;
	result->args[0] = l;
	result->args[1] = r;
	return result;*/
	return this;
}
void fractional::print() {
	cout << this->num ;
	if (denom!=1 && num!= 0) cout << '/' << this->denom;
}
