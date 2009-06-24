#ifndef NODE_H
#define NODE_H

class Node {
	private:
	
	public :
		//Node();
		virtual Node *simplify(void)  = 0;
		virtual Node *derive(void)    = 0;
		virtual Node *integrate(void) = 0;
		virtual void print(void)      = 0;
	       	virtual bool compare(Node *)  = 0;
};

#endif