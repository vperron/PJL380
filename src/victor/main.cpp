/*=============================================================================

  Code capable de parser des expressions mathématiques...

  Victor Perron 2009 - PJL380 - TELECOM ParisTech

=============================================================================*/

#include <boost/spirit.hpp>
#include "main.hpp"
#include <iostream>
#include <string>


/*
void printTree(Node * t) {
	if(t->Left !=  NULL)
		printTree(t->Left);
	t->Me->print();
	if(t->Right !=  NULL)
		printTree(t->Right);
}
*/



////////////////////////////////////////////////////////////////////////////
//
//  Main program
//
////////////////////////////////////////////////////////////////////////////
int
main()
{
    cout << "/////////////////////////////////////////////////////////\n\n";
    cout << "\t\tTest parser...\n\n";
    cout << "/////////////////////////////////////////////////////////\n\n";
    cout << "Entrez une expression (rien ==> quitter)\n\n";

    calculator calc;    //  Our parser


    string str;
    while (getline(cin, str))
    {
        if (str.empty())
            break;

        parse_info<> info = parse(str.c_str(), calc, space_p);

        if (info.full)
        {
            cout << "-------------------------\n";
            cout << "Succès !\n";
            cout << "-------------------------\n";
			root->print();	
        }
        else
        {
            cout << "-------------------------\n";
            cout << "Erreur.\n";
            cout << "Arrêt sur: \": " << info.stop << "\"\n";
            cout << "-------------------------\n";
        }
    }

    cout << "Merci, à bientôt ! :-) \n\n";
    return 0;
}


