#ifndef OPERATOR_H
#define OPERATOR_H
#include <list>
#include "node.hpp"
#include "regroupable.hpp"
class Operator : public Regroupable {
	private:

	public :
		std::list<Node *> Args;
		virtual bool compare(Node *)  ;
        Operator();
	Operator(Node* ,Node *);
};
#endif
