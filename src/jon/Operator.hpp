#ifndef OPERATOR_H
#define OPERATOR_H
#include <list>
#include "node.hpp"
class Operator : public Node {
	private:

	public :
		std::list<Node *> Args;
};
#endif
