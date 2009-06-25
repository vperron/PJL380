
#include "operator_plus.hpp"
#include "variable.hpp"
#include "function_power.hpp"
#include "node.hpp"
#include "fractional.hpp"
#include "operator_mult.hpp"
#include <iostream>
using namespace std;

int main(void) {
/*	functionpower f;
	f.power = 2;
	Variable x;
	x.name = "x";
	f.arg = &x;
	Node* g = f.derive();
	g->print();
	cout << endl;
	Node* h = g->simplify();
	h->print();
	cout << endl;
	Node* k = h->derive();
	k->print();
	cout << endl;
	Node* l = k->simplify();
	l->print();
	cout << endl;
*/
	/*
	functionexp *a = new functionexp;
	functionln *b = new functionln;
	b->arg= a;
	Variable x;
	x.name="x";
	a->arg = &x;
	cout << "La dérivée de ";
	b->print();
	cout << endl << "simplifiée en : " ;
	Node *res1 = b->simplify();
	res1->print();
	cout << endl;
	cout << endl << "          est : \n";
	Node *res = res1->derive();
	res->print();
	cout << endl << "simplifiée en : ";
	res = res->simplify();
	res->print();
*/

	operatormult* toto = new operatormult;
	toto->Args.push_back(new fractional(2));
	toto->Args.push_back(new fractional(3));
	toto->print();
	toto->simplify()->print();
	return 0;
}
