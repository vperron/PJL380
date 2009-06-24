#ifndef FUNCTION_H
#define FUNCTION_H
#include "node.hpp"

#include "regroupable.hpp"
class Function : public Regroupable {
	private:

	public :
		bool compare (Node *a);
		Node* arg;
        Function();
        Function(Node *a);
};

#endif
