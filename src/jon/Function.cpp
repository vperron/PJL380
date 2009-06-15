

#include "Function.hpp"

bool Function::operator==(const Function f&){
	if (typeid(this) == typeid(op)) {
		return (*(this.arg) == *(f.arg));
	}
	else return false;

