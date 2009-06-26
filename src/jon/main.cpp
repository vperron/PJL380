#include "utils.hpp"
#include "operator_plus.hpp"
#include "variable.hpp"
#include "function_power.hpp"
#include "node.hpp"
#include "fractional.hpp"
#include "operator_mult.hpp"
#include <iostream>
using namespace std;

int main(void) {
	fractional toto(1);
	fractional tutu(2);
	cout << toto.compare(&tutu) <<endl;
	return 0;
}
