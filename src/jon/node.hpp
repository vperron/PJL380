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

#endif
