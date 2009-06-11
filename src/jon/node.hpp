#ifndef NODE_H
#define NODE_H

class Node {
	private:
	
	public :
		//Node();
		virtual void simplify(void)   = 0;
		virtual Node *derive(void)    = 0;
		virtual Node *integrate(void) = 0;
		virtual void print(void)      = 0;

};


class Function : public Node {
	private:

	public :
		Node* arg;
};


class Operator : public Node {
	private:

	public :
		Node* args[10]; //TODO : dynamic size, STL ?
		int   argc;

};


#endif
