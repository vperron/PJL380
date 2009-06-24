#ifndef OPERATOR_PLUS_H
#define OPERATOR_PLUS_H
#include "operator.hpp"

class operatorplus: public Operator {
	private:
		void simplify_fractionnals();
		void flatten() ;
		void remove_zeros();

	public :
		virtual Node *simplify(void)  ;
		virtual Node *derive(void)    ;
		virtual Node *integrate(void) ;
		virtual void print(void)      ;
		virtual bool compare(Node *)  ;
		operatorplus();
		operatorplus(Node * a,Node * b) : Operator(a,b) { };

};
#endif
