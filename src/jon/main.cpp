
#include "operator_plus.hpp"
#include "variable.hpp"
#include "function_power.hpp"
#include "node.hpp"
#include "fractional.hpp"
#include "operator_mult.hpp"
#include <iostream>
using namespace std;

int main(void) {
	cout << "hello world!" << endl;
	functionpower f;
	f.power = 2;
	functionpower ff;
	ff.power = 1;
	Variable x;
	x.name = "x";
	Variable x1;
	x1.name = "x";
	f.arg = &x;
	ff.arg = &x1;
	operatormult *gr = new operatormult;
	list<Node *> l; 
	l.push_back(&f);
	l.push_back(&ff);
	gr->Args = l;
	Node *res = gr->derive();
	res->print();
	return 0;
}
