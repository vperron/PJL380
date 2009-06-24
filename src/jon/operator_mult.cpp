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
	for (list<Node *>::iterator i=Args.begin();i!=Args.end();i++) {
		fractional* ii = dynamic_cast<fractional*>(*i);
		if (ii!=0 ) {
			for (list<Node *>::iterator j=Args.begin();j!=Args.end();j++) {
				fractional* jj = dynamic_cast<fractional*>(*j);
				if (jj!=0 && i != j) {
					fractional *result = new fractional;
					result->denom = ii->denom * jj->denom;
					result->num = ii->num * jj->num;
					*i = result;
					j = Args.erase(j);
				}
			}
		}
	}	
/*	for (list<Node *>::iterator i=Args.begin();i!=Args.end();i++) {
		fractional* ii = dynamic_cast<fractional*>(*i);
		if (ii!=0 ) {
			for (list<Node *>::iterator j=Args.begin();j!=Args.end();j++) {
*/}

Node* get_not_null(Node *ptr1, Node *ptr2) {
	if (ptr1 != 0) return ptr1;
	return ptr2;
}
void operatormult::simplify_regroupables() {
	cout << endl <<"simplify variable" << endl;
	print();
	cout << endl;
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
				cout << "je traite : " ;
				(*j)->print();
			       	cout <<endl;
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
			cout <<"j'en suis là : ";
			print();
			cout <<endl;
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
	cout << endl <<"avant variable" << endl;
	print();
	cout << endl;
	flatten();
	cout << endl <<"après variable" << endl;
	print();
	cout << endl;
	for (list<Node *>::iterator i=Args.begin();i!=Args.end();i++) {
		*i = (*i)->simplify();
	}
	cout << endl <<"simplify variable" << endl;
	print();
	cout << endl;

	remove_ones();

	cout << endl <<"simplify variable" << endl;
	print();
	cout << endl;
	//if there is at least one zero, the whole expression is this zero
	Node *test = get_zero();
	if (test != 0) return test;
	simplify_fractionnals();
	cout << endl <<"simplify variable" << endl;
	print();
	cout << endl;
	remove_ones();
	cout << endl <<"simplify variable" << endl;
	print();
	cout << endl;
	simplify_regroupables();
	cout << endl <<"simplify variable" << endl;
	print();
	cout << endl;
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
