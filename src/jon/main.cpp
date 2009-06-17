
#include "operator_plus.hpp"
#include "variable.hpp"
#include "function_power.hpp"
#include "node.hpp"
#include "fractional.hpp"
#include "operator_mult.hpp"
#include <iostream>
using namespace std;

int main(void) {
	functionpower f;
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

	/*functionpower ff;
	ff.power = 1;
	Variable x;
	x.name = "x";
	Variable x1;
	x1.name = "x";
	f.arg = &x;
	ff.arg = &x1;
	operatorplus *gr = new operatorplus;
	(gr->Args).push_back(&f);
	(gr->Args).push_back(&ff);
	cout << "La dérivée de ";
	gr->print();
	//cout << endl << "simplifiée en : ";
	//Node *res1 = gr->simplify();
	//res1->print();
	cout << endl;
	Node *res = gr->derive();
	cout << endl << "          est : \n";
	res->print();
	res = res->simplify();
	cout << endl << "simplifiée en : ";
	res->print();*/
	return 0;
}
