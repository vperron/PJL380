#ifndef OPERATOR_MULT_H
#define OPERATOR_MULT_H
#include "operator.hpp"

class operatormult: public Operator {
	private :
		void flatten() ;
		void remove_ones(void);
		Node *get_zero(void);
		void simplify_fractionnals();
		void simplify_regroupables();
	public :
		virtual Node *simplify(void)  ;
		virtual Node *derive(string&)    ;
		virtual Node *integrate(void) ;
		virtual void print(void)      ;
		virtual bool compare(Node *)  ;
		operatormult() {} ;
		operatormult(Node * a,Node * b) : Operator(a,b) { };
};
#endif
