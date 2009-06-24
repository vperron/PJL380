#include <iostream>
#include "operator_mult.hpp"
#include "operator_plus.hpp"
#include "fractional.hpp"
#include "variable.hpp"
#include "function_power.hpp"
using namespace std;


bool operatormult::compare(Node *a) {
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
	fractional *first_fractional_found_ptr = 0;
	for (list<Node *>::iterator i=Args.begin();i!=Args.end();i++) {
		fractional* ii = dynamic_cast<fractional*>(*i);
		if (ii!=0) {
			//this first fractional will act as the accumulator
			//store it, then remove it from the list
			if (first_fractional_found_ptr == 0) {
				first_fractional_found_ptr = ii;
				i = Args.erase(i);
				i--;
			}
			//remove the other fractionals and compute them with the accumulator
			else {
				fractional *result = new fractional;
				result->denom = ii->denom * first_fractional_found_ptr->denom;
				result->num = ii->num * first_fractional_found_ptr->num;
				first_fractional_found_ptr = result; 
				i = Args.erase(i);
				i--;
			}
		}
	}	
	//if there was at least one fractional in the expression, put it back
	if (first_fractional_found_ptr) {
		Args.push_back(first_fractional_found_ptr);
	}
}

Node* get_not_null(Node *ptr1, Node *ptr2) {
	if (ptr1 != 0) return ptr1;
	return ptr2;
}
void operatormult::simplify_regroupables() {
	for (list<Node *>::iterator i=Args.begin();i!=Args.end();i++) {
		Regroupable* ii = dynamic_cast<Regroupable*>(*i);
		functionpower* iii = dynamic_cast<functionpower*>(*i);
		int count ;
		Node *maybe_function_arg = 0;
		if (ii!=0) count = 1;
		else if (iii!=0) {
			count = iii->power;
			maybe_function_arg = iii->arg;
		}
		Node *maybe_regroupable = get_not_null(ii,maybe_function_arg);
		if (maybe_regroupable!=0) {
			for (list<Node *>::iterator j=Args.begin();j!=Args.end();j++) {
				Regroupable* jj = dynamic_cast<Regroupable*>(*j);
				functionpower* jjj = dynamic_cast<functionpower*>(*j);
				if (jj!=0 && i!=j && jj->compare(maybe_regroupable) ) {
				       	count++;
					j = Args.erase(j);
					j--;
				}
				else if (jjj!=0 && i!=j && (jjj->arg)->compare(maybe_regroupable)) {
					count += jjj->power;
					j = Args.erase(j);
					j--;
				}
			}
		}
		if (count!=1) {
			i = Args.erase(i);
			i--;
			if (count !=0) {
				functionpower *toto = new functionpower;
				toto->power = count;
				toto->arg = ii;
				Args.push_front(toto);	
			}
			else {
			   fractional *toto = new fractional;
			   toto->num = toto->denom = 1;
			   Args.push_front(toto);
			}
			count = 1;
		}
	}
}

void operatormult::flatten() {
	for (list<Node *>::iterator i = Args.begin();i!= Args.end(); i++) {
		operatormult *temp = dynamic_cast<operatormult*>(*i);
		functionpower *pow = dynamic_cast<functionpower*>(*i);
		if (temp != 0) {
			for (list<Node *>::iterator j = temp->Args.begin();j!= temp->Args.end(); j++) {
				Args.push_front(*j);
			}
			i = Args.erase(i);
			i--;
		}
		else if (pow!=0 && pow->power>0) {
			for (int j = 0; j < pow->power;j++) {
				Args.push_front(pow->arg);
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
	simplify_regroupables();
	remove_ones();
	if (Args.size() == 0) return new fractional(1);
	if (Args.size() == 1) return Args.front();
	else return this;
}
Node* operatormult::derive() {
	operatorplus* result = new operatorplus();
	for (list<Node *>::iterator i=Args.begin();i!=Args.end();i++) {
		operatormult* temp = new operatormult();
		for (list<Node *>::iterator j=Args.begin();j!=Args.end();j++) {
			if (i != j) {
				(temp->Args).push_back(*j);	
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
