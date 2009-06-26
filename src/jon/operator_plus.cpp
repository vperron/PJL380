#include <iostream>
#include "operator_plus.hpp"
#include "fractional.hpp"
#include "regroupable.hpp"
#include "operator_mult.hpp"
#include "utils.hpp"
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
	if (first_fractional_found_ptr != 0) Args.push_back(first_fractional_found_ptr);
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

void operatorplus::simplify_regroupables() {
	for (list<Node *>::iterator i=Args.begin();i!=Args.end();i++) {
		Regroupable *expr = dynamic_cast<Regroupable *>(*i);
		operatormult *mul = dynamic_cast<operatormult *>(*i);
		fractional *count = new fractional(0);
		Node *matched_node = 0;
		if (expr != 0) {
			count = new fractional(1);
			for (list<Node *>::iterator j=Args.begin();j!=Args.end();j++) {
				Regroupable *expr2 = dynamic_cast<Regroupable *>(*j);
				operatormult *mul2 = dynamic_cast<operatormult *>(*j);
				if (expr2 != 0 && i!=j && expr->compare(expr2)) {
					matched_node = expr;
					j=Args.erase(j);
					j--;
					count = (fractional *) (new operatorplus(count,new fractional(1)))->simplify();
				} else if (mul2 !=0 && i!=j) {
					fractional *constant;
					bool has_constant = get_constant(mul2->Args,&constant);
					if ((mul2->Args.size() == 2) && has_constant && member_of(expr,mul2->Args)) {
						matched_node = expr;
						j= Args.erase(j);
						j--;
						count =  (fractional *) (new operatorplus(count,constant))->simplify();
					}
				}
			}
		} else if (mul != 0) {
			get_constant(mul->Args,&count);
			for (list<Node *>::iterator j=Args.begin();j!=Args.end();j++) {
				Regroupable *expr2 = dynamic_cast<Regroupable *>(*j);
				operatormult *mul2 = dynamic_cast<operatormult *>(*j);
				if (expr2 != 0 && i!=j) {
					bool has_constant;
					fractional *constant;
					has_constant = get_constant(mul->Args,&constant);
					if ((mul->Args.size() == 2) && has_constant && member_of(expr2,mul->Args)) {
						matched_node = expr2;
						j= Args.erase(j);
						j--;
						count =  (fractional *) (new operatorplus(count,new fractional(1)))->simplify();
					}
				} else if (mul2!=0 && i!=j && mycompare(mul2->Args,mul->Args)) {
					bool has_constant;
					fractional *constant;
					has_constant = get_constant(mul->Args,&constant);
					j= Args.erase(j);
					j--;
					count =  (fractional *) (new operatorplus(count,constant))->simplify();
					operatormult *mul3 = new operatormult;
					mul3->Args = remove_constants(mul2->Args);
					matched_node = mul3;
				}
			}
		}
		if (matched_node != NULL) {
			operatormult *result = new operatormult(count,matched_node);
			Args.push_back(result->simplify());
			Args.erase(i);
			i--;
		}
	}
}

Node* operatorplus::simplify() {
	for (list<Node *>::iterator i=Args.begin();i!=Args.end();i++) {
		*i = (*i)->simplify();
	}
	flatten();
	remove_zeros();
	simplify_fractionnals();
	simplify_regroupables();
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
