#include <iostream>
#include "operator_mult.hpp"
#include "operator_plus.hpp"
#include "fractional.hpp"
#include "variable.hpp"
#include "function_power.hpp"
using namespace std;

//Node : pas mal de fonctions de cette classe ressemblent à celle de operatorplus... j'aurais surement pu factoriser ça un peu plus...

//la comparaison est la même pour les 2 types d'opérateurs : + et *
bool operatormult::compare(Node *a) {
	Operator::compare(a);	
}

//Pareil qu'enlever les zéros pour une addition, on enlève les uns de la multiplication
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

//Le zéro est absorbant pour la multiplication, c'est cool pour facilement simplifier !!
//renvoit null si il n'y en a pas ou l'objet representant le zéro sinon
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

//Traitement à part des fractionels comme pour +
//J'aurais surement pu factoriser pas mal de choses au niveau d'operator....
void operatormult::simplify_fractionnals() {
	fractional *first_fractional_found_ptr = 0;
	for (list<Node *>::iterator i=Args.begin();i!=Args.end();i++) {
		fractional* ii = dynamic_cast<fractional*>(*i);
		if (ii!=0) {
			//this first fractional will act as the accumulator
			//store it, then remove it from the list
			if (first_fractional_found_ptr == 0) {
				first_fractional_found_ptr = ii;
				i = Args.erase(i);
				i--;
			}
			//remove the other fractionals and compute them with the accumulator
			else {
				fractional *result = new fractional;
				result->denom = ii->denom * first_fractional_found_ptr->denom;
				result->num = ii->num * first_fractional_found_ptr->num;
				first_fractional_found_ptr = result; 
				i = Args.erase(i);
				i--;
			}
		}
	}	
	//if there was at least one fractional in the expression, put it back
	if (first_fractional_found_ptr) {
		Args.push_back(first_fractional_found_ptr);
	}
}

//fonction auxiliaire dont on se sert juste au dessous
Node* get_not_null(Node *ptr1, Node *ptr2) {
	if (ptr1 != 0) return ptr1;
	return ptr2;
}
//Fonction monstres qui ressemble beaucoup à celle de plus, mais moins compliqué parce que les puissances sont forcéments des entiers
//(d'ailleurs, ça pourrait être des fractionals...) Du coup en transformant x^i en x*x*x, il suffit de compter les occurences de x
//Neanmoins, c'est pas si facile.. il y a plein de cas ... et pleins de bugs...
void operatormult::simplify_regroupables() {
	for (list<Node *>::iterator i=Args.begin();i!=Args.end();i++) {
		Regroupable* ii = dynamic_cast<Regroupable*>(*i);
		functionpower* iii = dynamic_cast<functionpower*>(*i);
		bool found_something = 0;
		int count = 0;
		Node *maybe_function_arg = 0;
		//check for functionpower first, since it is also regroupable
		if (iii!=0) {
			count = iii->power;
			maybe_function_arg = iii->arg;
			//UNSET ii since we want to use functionpower first to catch things like (x+1)/(x+1)
			ii = 0;
		}
		else if (ii!=0) {
			count = 1;
		}
		Node *maybe_regroupable = get_not_null(maybe_function_arg,ii);
		if (maybe_regroupable!=0) {
			for (list<Node *>::iterator j=Args.begin();j!=Args.end();j++) {
				Regroupable* jj = dynamic_cast<Regroupable*>(*j);
				functionpower* jjj = dynamic_cast<functionpower*>(*j);
				//same as before, functionpower is also regroupable..
				if ( jjj !=0 ) jj = 0;
				if (jj!=0 && i!=j && jj->compare(maybe_regroupable) ) {
					found_something = true;
					count++;
					j = Args.erase(j);
					j--;
				}
				else if (jjj!=0 && i!=j && (jjj->arg)->compare(maybe_regroupable)) {
					found_something = true;
					count += jjj->power;
					j = Args.erase(j);
					j--;
				}
			}
		}
		if (count!=1 && found_something) {
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
		}
	}
}
// Applatir... pareil que +, sauf qu'on peut aussi applatir les puissances parce qu'on accepte que des entiers héhé...
//Gare aux complications si on passe en fractionels :)
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

//la simplification qui fait appel aux autres méthodes
Node* operatormult::simplify() {
	for (list<Node *>::iterator i=Args.begin();i!=Args.end();i++) {
		*i = (*i)->simplify();
	}
	flatten();

	remove_ones();

	//if there is at least one zero, the whole expression is this zero
	Node *test = get_zero();
	if (test != 0) return test;
	simplify_fractionnals();
	simplify_regroupables();
	remove_ones();
	if (Args.size() == 0) return new fractional(1);
	if (Args.size() == 1) return Args.front();
	else return this;
}

//La dérivée d'un produit est la somme de tous les produits où on en dérive que un seul
Node* operatormult::derive(string &s) {
	operatorplus* result = new operatorplus();
	for (list<Node *>::iterator i=Args.begin();i!=Args.end();i++) {
		operatormult* temp = new operatormult();
		for (list<Node *>::iterator j=Args.begin();j!=Args.end();j++) {
			if (i != j) {
				(temp->Args).push_back(*j);	
			}
			else {
				(temp->Args).push_back((*j)->derive(s));	
			}
		}
		(result->Args).push_back(temp);
	}
	return result;
}

//là, il faut essayer de partitioner en 2 le produit pour retomber sur la formule : (uov)' = v' * u'ov.. Good luck...
//Et encore, on parle pas d'intégration par parties, de changement de variables....
Node* operatormult::integrate() {
	return this;
}

//Imprimer un produit et les fils (enfin un truc pas dur, ouf)
void operatormult::print() {
	list<Node *>::iterator beforelast = --Args.end();
	cout << "(";
	for (list<Node *>::iterator i=Args.begin();i!=Args.end();i++) {
		(*i)->print();
		if (i!=beforelast) cout <<"*";
	}
	cout << ")";
}
