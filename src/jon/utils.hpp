#include <list>
#include "node.hpp"
#include "fractional.hpp"
using namespace std;

bool mycompare(list<Node *>l1, list<Node *>l2) ;
bool compare_lists(list<Node*> l1,list<Node *>l2) ;
bool member_of(Node *e, list<Node *>l) ;
bool get_constant(list<Node *>l,fractional **a) ;
list<Node *> remove_constants(list<Node *> l);
