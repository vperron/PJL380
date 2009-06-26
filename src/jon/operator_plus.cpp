#include <iostream>
#include "operator_plus.hpp"
#include "fractional.hpp"
#include "regroupable.hpp"
#include "operator_mult.hpp"
#include "utils.hpp"
using namespace std;

//Node : pas mal de fonctions de cette classe ressemblent à celle de operatormult... j'aurais surement pu factoriser ça un peu plus...

//la comparaison est la même pour les 2 types d'opérateurs : + et *
bool operatorplus::compare(Node *a) {
	Operator::compare(a);	
}

//Cette fonction sert à applatir les arbres de type (x y +) x +
//Elle n'est pas récursive parcequ'elle suppose que tous les sous-arbres ont déjà étés simplifiés (donc applatis)
void operatorplus::flatten() {
	for (list<Node *>::iterator i = Args.begin();i!= Args.end(); i++) {
		operatorplus *temp = dynamic_cast<operatorplus*>(*i);
		if (temp != 0) {
			for (list<Node *>::iterator j = temp->Args.begin();j!= temp->Args.end(); j++) {
				Args.push_front(*j);
			}
			i = Args.erase(i);
			i--;
		}

	}
}

//Les fractionals ont un traitement à part : on peut simplifier ensemble deux fractionals non égaux (alors qu'on ne fait rien de x+y)
//cette fonction se charge de simplifier tous les fractionals fils 
void operatorplus::simplify_fractionnals() {
	fractional *first_fractional_found_ptr = 0;
	for (list<Node *>::iterator i=Args.begin();i!=Args.end();i++) {
		fractional* ii = dynamic_cast<fractional*>(*i);
		if (ii!=0) {
			//on stock le premier fractional
			if (first_fractional_found_ptr == 0) {
				first_fractional_found_ptr = ii;
				i = Args.erase(i);
				i--;
			}
			//on effectue l'opération sur les fractionals suivants et on accumule dans first_fractional_found_ptr
			else {
				fractional *result = new fractional;
				result->denom = ii->denom * first_fractional_found_ptr->denom;
				result->num = ii->num * first_fractional_found_ptr->denom + ii->denom * first_fractional_found_ptr->num;
				result = result->simplify();
				first_fractional_found_ptr = result; 
				i = Args.erase(i);
				i--;
			}
		}
	}	
	//On remet first_fractional_found_ptr si il existe (ie il y'a au moins un fractional dans l'expression
	if (first_fractional_found_ptr != 0) Args.push_back(first_fractional_found_ptr);
}


//traitement special des zeros pour le fun/la performance (au choix du lecteur ...)
void operatorplus::remove_zeros(){
	for (list<Node *>::iterator i=Args.begin();i!=Args.end();i++) {
		fractional* ii = dynamic_cast<fractional*>(*i);
		if (ii!=0) {
			if (ii->num == 0) {
				i = Args.erase(i);
				i--;
			}	
		}
	}
}

//la fonction monstre qui simplifie les autres choses que les fractionels.
// On cherche des sous arbres qui  peuvent se factoriser : il y'a plusieurs cas (d'où  l'énorme fonction)
// On veut pouvoir factoriser les cas suivants : 
// x x x +                 -> 3 x *
// (2 x *) x +           -> 3 x *
// x ( 2 x * ) +         -> 3 x *
// ( 2 x * ) ( 2 x * ) + -> 4 x *
// ou x est un sous-arbre, et la constante peut bien sur être n'importe quoi.
// par exemple : ( Var(x) Var(y) * ) ( Var(x) Var(y) *) +     -> Var(x) Var(y) 2 *

//Le type Regroupable represente un sous-arbre quelconque, différent de fractionels (les fractions ont un statut à part)
void operatorplus::simplify_regroupables() {
	// On commence à parcourir la liste
	for (list<Node *>::iterator i=Args.begin();i!=Args.end();i++) {
		Regroupable *expr = dynamic_cast<Regroupable *>(*i);
		operatormult *mul = dynamic_cast<operatormult *>(*i);
		//count sert à calculer la constante par laquelle on factorise.
		fractional *count = new fractional(0);
		Node *matched_node = 0;
		// On tombe sur un produit, on va donc regarder les arguments pour voir si on peut regrouper quelquechose
		if (mul != 0) {
			// On garde la constante présente dans ce produit (1 s'il n'y en a pas)
			// on la met dans count
			get_constant(mul->Args,&count);
			//Ici, on peut commencer à partir de i+1, mais je sais pas le faire avec les itérateurs,
		        //et à partir de zéro ça change rien parce que rien ne va matcher avant i
			for (list<Node *>::iterator j=Args.begin();j!=Args.end();j++) {
				Regroupable *expr2 = dynamic_cast<Regroupable *>(*j);
				operatormult *mul2 = dynamic_cast<operatormult *>(*j);
				//On essaye de voir si on a trouvé quelque chose d'intéréssant
				if (mul2!=0 && i!=j && mycompare(mul2->Args,mul->Args)) {
					//on est tombé sur une autre multiplication, et mycompare dit que c'est la même chose que 
				        //la premiere, à une constante près, qu'on récupere,
				        //et qu'on ajoute à la premiere qui est dans count	
					bool has_constant;
					fractional *constant;
					has_constant = get_constant(mul2->Args,&constant);
					//on simplifie en effacant cette partie de l'expression
					j= Args.erase(j);
					j--;
					count =  (fractional *) (new operatorplus(count,constant))->simplify();
					operatormult *mul3 = new operatormult;
					mul3->Args = remove_constants(mul2->Args);
					//on se souvient qu'on a pu regrouper qqchose pour la suite
					matched_node = mul3;
				} else if (expr2 != 0 && i!=j) {
					// on essaye de matcher sur un sous-arbre. Pour que ça réussisse, il faut
				        // beaucoup de choses sur mul : elle n'a que deux arguments : une constante et un sous-arbre	
					// en fait c'est le cas  ( 2 x * ) x +     -> 3 x *
					bool has_constant;
					fractional *constant;
					has_constant = get_constant(mul->Args,&constant);
					// on vérifie les contraintes et que c'est bien le même sous-arbre
					if ((mul->Args.size() == 2) && has_constant && member_of(expr2,mul->Args)) {
						//on a trouvé quelquechose
						matched_node = expr2;
						//on simplifie en effacant cette partie de l'expression
						j= Args.erase(j);
						j--;
						//on stock la nouvelle constante
						count =  (fractional *) (new operatorplus(count,new fractional(1)))->simplify();
					}
				}
			}
		// On tombe sur un sous-arbre qui n'est pas un produit (à cause du else) 
		} else if (expr != 0) {
			// On stocke la nouvelle valeur de count 
			count = new fractional(1);
			//même remarque sur le début de la boucle à partir de i+1...
			for (list<Node *>::iterator j=Args.begin();j!=Args.end();j++) {
				Regroupable *expr2 = dynamic_cast<Regroupable *>(*j);
				operatormult *mul2 = dynamic_cast<operatormult *>(*j);
				//On tombe sur un produit, c'est le même cas qu'au dessus à l'envers
				//et on déduit les mêmes contraintes sur le produit trouvé (taille=2 : constante*x)
				if (mul2 !=0 && i!=j) {
					fractional *constant;
					bool has_constant = get_constant(mul2->Args,&constant);
					// on vérifie les contraintes et que c'est bien le même sous-arbre
					if ((mul2->Args.size() == 2) && has_constant && member_of(expr,mul2->Args)) {
						matched_node = expr;
						j= Args.erase(j);
						j--;
						count =  (fractional *) (new operatorplus(count,constant))->simplify();
					}
					// on match sur un sous arbre, c'est le cas x x + (le plus simple, pfiou ...)
				} else if (expr2 != 0 && i!=j && expr->compare(expr2)) {
					matched_node = expr;
					j=Args.erase(j);
					j--;
					count = (fractional *) (new operatorplus(count,new fractional(1)))->simplify();
				}
			}
		}
		//Si on a effacé quelquechose
		if (matched_node != NULL) {
			//on crée le resultat de la simplification
			operatormult *result = new operatormult(count,matched_node);
			//on met le resultat
			Args.push_back(result->simplify());
			// On vire le premier élément trouvé qu'on avait pas viré car on s'en servait pour matcher.
			Args.erase(i);
			i--;
		}
	}
}

//on simplifie récursivement, puis on applique les différentes fonctions de simplification
Node* operatorplus::simplify() {
	for (list<Node *>::iterator i=Args.begin();i!=Args.end();i++) {
		*i = (*i)->simplify();
	}
	flatten();
	remove_zeros();
	simplify_fractionnals();
	simplify_regroupables();
	if (Args.size() == 1) return Args.front();
	else return this;
}
//la dérivée d'une somme est la somme des dérivées
Node* operatorplus::derive() {
	for (list<Node *>::iterator i=Args.begin();i!=Args.end();i++) {
		*i = (*i)->derive();
	}
	return this;
}
//L'intégrale est la somme des intégrales, 
Node* operatorplus::integrate() {
	for (list<Node *>::iterator i=Args.begin();i!=Args.end();i++) {
		*i = (*i)->integrate();
	}
	return this;
}
//imprimer les fils avec des '+' entre
void operatorplus::print() {
	list<Node *>::iterator beforelast = --Args.end();
	cout << "(";
	for (list<Node *>::iterator i=Args.begin();i!=Args.end();i++) {
		(*i)->print();
		if (i!=beforelast) cout <<"+";
	}
	cout << ")";
}

operatorplus::operatorplus() {
}
