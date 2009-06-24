#include <iostream>
#include "operator_plus.hpp"
#include "operator_mult.hpp"
#include "function_power.hpp"
#include "fractional.hpp"
#include "variable.hpp"
#include "math.h"
using namespace std;

/*functionsin::functionsin(const &functionsin) {

  }*/

Node* functionsin::simplify() {
	arg = arg->simplify();	
	switch (this->power) {
		case 0: {
				fractional *res = new fractional;
				res->num = 1;
				res->denom = 1;
				return res;
			}	
		case 1:
			return this->arg;
		default: 
			{
				fractional *frac = dynamic_cast<fractional*>(arg);
				if (frac != 0) {
					fractional *result = new fractional;
					if (power > 0 ) {
						result->denom = pow(frac->denom,power);
						result->num = pow(frac->num,power);
					}
					else {
						result->num = pow(frac->denom,-power);
						result->denom = pow(frac->num,-power);
					}
					return result;
				}
				else {
					return this;
				}
			}
	}
}
Node* functionsin::derive() {
	if (this->power != 1) { //TODO passer en fractional
		Node *l = this->arg->derive();
		operatormult *result = new operatormult;
		fractional *res2 = new fractional;
		functionsin *res3 = new functionsin;
		res2->num = this->power;
		res2->denom = 1;
		res3->power = this->power - 1;
		res3->arg = this->arg;
		(result->Args).push_back(l);
		(result->Args).push_back(res2);
		(result->Args).push_back(res3);
		return result;
	}
	else {
		return this->arg->derive();
	}
}
Node* functionsin::integrate() {
	return (Node *) 0;
}
void functionsin::print() {
	cout << '('; 
	arg->print();
	cout << ")^" << this->power;
}
