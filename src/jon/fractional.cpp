#include <iostream>
#include "fractional.hpp"
#include "operator_mult.hpp"
#include "variable.hpp"
using namespace std;

//simplifier d'abord les deux eventuels fractionals pour les comparer
bool fractional::compare(Node* a) {
	fractional *b = dynamic_cast<fractional*>(a);
	if (b != 0) {
		fractional *test1 = this->simplify();
		fractional *test2 = b->simplify();
		return (test1->num==num && test2->denom==denom);
	}
	return false;
}

//La dérivée d'une constante est nulle...
Node* fractional::derive() {
	fractional * res = new fractional;
	res->num = 0;
	res->denom = 1;
	return res;
}

//essayer tous les nombres plus petits que le minimum du denom et du num
fractional* fractional::simplify() {
	int divisor = 2;
	if (num!=0) {
		while ((divisor <= denom) && (divisor <= num)) {
			if ((denom % divisor == 0) && (num % divisor == 0)) {
				denom /= divisor;
				num /= divisor;
			}
			else {
				divisor++;
			}
		}
	}
	//traitement spécial du zéro, pour qu'il soit écrit à chaque fois pareil
	else {
		denom=1;
	}
	return this;
}

//TODO : prendre le nom en argument ?
Node* fractional::integrate() {
	return new operatormult(new Variable("x"),this);
}


//la representation des entiers est d'avoir un denominateur de 1
//Pas besoin de l'imprimer donc s'il vaut 1. Pareil pour le zéro.
void fractional::print() {
	cout << this->num ;
	if (denom!=1 && num!= 0) cout << '/' << this->denom;
}


fractional::fractional() {
}
