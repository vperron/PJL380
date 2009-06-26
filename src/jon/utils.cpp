#include <iostream>
#include "utils.hpp"
using namespace std;


//ce fichier regroupe les fonctions de manipulation de listes nécéssaires pour matcher dans operatorplus::simplify_regroupables()

//un boolean qui dit si les deux listes sont égales à une constante près
bool mycompare(list<Node *>l1, list<Node *>l2) {
	return compare_lists(l1,l2) && compare_lists(l2,l1);
}

// l1  inclu dans l2 à une constante pres
bool compare_lists(list<Node*> l1,list<Node *>l2) {
	for (list<Node *>::iterator i=l1.begin();i!=l1.end();i++) {
		if (!member_of(*i,l2)) return false;	
	}
	return true;
}

// membre (les constantes renvoient true)
bool member_of(Node *e, list<Node *>l) {
	fractional *f = dynamic_cast<fractional *>(e);
	if (f==0) {
		for (list<Node *>::iterator i=l.begin();i!=l.end();i++) {
			if (e->compare(*i)) return true;
		}
		return false;
	}
	return true;
}
//renvoit la premiere constante trouvée et un boolean pour savoir s'il en a trouvé une
bool get_constant(list<Node *>l,fractional **a) {
	for (list<Node *>::iterator i=l.begin();i!=l.end();i++) {
		fractional *frac = dynamic_cast<fractional *>(*i);
		if (frac != 0) {
			*a = frac;
			return true;
		}
	}
	*a = new fractional(1);
	return false;
}

//strip une liste de ses constants
list<Node *> remove_constants(list<Node *> l) {
	list<Node *> result;
	for (list<Node *>::iterator i=l.begin();i!=l.end();i++) {
		fractional *f = dynamic_cast<fractional *>(*i);
		if (f==0) {
			result.push_back(*i);
		}
	}
	return result;
}
