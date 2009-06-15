#include <iostream>
#include "fractional.hpp"
using namespace std;

Node* fractional::derive() {
	this->denom = 0;
	return this;
}

void fractional::simplify() {
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
	if (denom!=1) cout << '/' << this->denom;
}
