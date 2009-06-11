
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
	/*fractional a;
	a.num = 3;
	a.denom = 2;
	f.args[0] = &a;*/
	Variable x;
	x.name = "x";
	Variable x1;
	x1.name = "x";
	f.arg = &x;
	ff.arg = &x1;
	operatormult g;
	g.args[0] = &f;
	g.args[1] = &ff;
	cout << "La derivée de ";
	g.print();
	Node *h = g.derive();
	cout << endl;
	cout << "est ";
	h->print();
	fractional toto;
	cout << endl;
	toto.denom = 15;
	toto.num = 5;
	toto.print();
	toto.simplify();
	toto.print();
	return 0;
}
