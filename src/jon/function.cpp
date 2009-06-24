
#include "function.hpp"
#include <typeinfo>


bool Function::compare (Node *a) {
	if ( typeid(*this) == typeid(*a)) {
		return arg->compare(((Function*)a)->arg);
	}
	else return false;
}

Function::Function() {

}
