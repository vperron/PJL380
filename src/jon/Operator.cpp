
#include "Operator.hpp"

bool Operator::operator==(const Operator op&){
	if (typeid(this) == typeid(op)) {
		return (this.Args == op.Args);
	}
	else return false;

