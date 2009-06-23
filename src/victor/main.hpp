/*=============================================================================
    Copyright (c) 2002-2003 Joel de Guzman
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#include "includes.hpp"



#include <boost/spirit.hpp>
#include <iostream>
#include <string>



using namespace std;
// Plus pratique pour appeller les fonctions de l'API spirit.
using namespace boost::spirit;



// Actions sémantiques exécutées sur trigger (reconnaissance d'un objet par exemple)
// Ce ne sont que des exemples.
namespace
{
    void    do_int(char const* str, char const* end)
    {
        string  s(str, end);
        cout << "INT(" << s << ')' << endl;

    }


    void    do_var(char const* str, char const* end)
    {
        string  s(str, end);
        cout << "VAR(" << s << ')' << endl;
    }


    void    do_add(char const*, char const*)    
    { 
        cout << "ADD\n"; 
    }
    

    void    do_subt(char const*, char const*)   
    { 
        cout << "SUBTRACT\n"; 
    }


    void    do_mult(char const*, char const*)   
    { 
        cout << "MULTIPLY\n"; 
    }
    

    void    do_div(char const*, char const*)    
    { 
        cout << "DIVIDE\n";
    }
    
    
    void    do_neg(char const*, char const*)   
    { 
        cout << "NEGATE\n"; 
    }
    
    
    // Un arbre s'adaptant à n'importe quel node
    template<typename CNode> class MyTree
    {
        public:
            CNode node;
            
            // Lien vers les fils      
            vector<CNode*> children;
    };

    MyTree<int> root;

    // Vars est un vecteur de type Variable 
    vector<Variable> args;

}

////////////////////////////////////////////////////////////////////////////
//
//  Our calculator grammar
//
////////////////////////////////////////////////////////////////////////////

// On se définit une classe publique calculator qui dérive de grammar
struct calculator : public grammar<calculator>
{
    // Elle contient une structure interne nommee definition (convention) 
    // Il s'agit d'une template sur un type ScannerT
    template <typename ScannerT> struct definition
    {

        // Constructeur qui se refere à son conteneur 
        definition(calculator const& self)
        {

            // Un entier : lexeme_d passe en mode parsing caractère. Plante sur des espaces.
            integer =
                lexeme_d[ (+digit_p)[&do_int] ]
                ;

            // une declaration de vars est un lexeme_d d'un caractere puis une suite de cars alphanums ou _ .
            // La declaration est retenue uniquement si la variable n'existe pas.
            var_decl =
                lexeme_d
                [
                    ( +alpha_p >> *( alnum_p | '_' ) )[&do_var]
                ]
                ;

            /*args = 
                while_p( integer | var_decl )[&args.push_back*/

            // Une fonction
            //function = 

                


            // Un facteur : un entier ou une variable ou une expression entre parentheses, ou +/- un autre facteur
            factor =
                integer |
                //function
                var_decl |
                '(' >> expression >> ')' |
                ( '-' >> factor )[&do_neg] |
                ( '+' >> factor )
                ;

            // un TERME est un facteur que multiplie ou divise d'autres facteurs
            term =
                factor 
                >> *( ( '*' >> factor)[&do_mult]
                    | ( '/' >> factor)[&do_div]
                )
                ;

            // Une expression est une addition d'au moins 2 termes.
            expression =
                term >> *( 
                        ( '+' >> term)[&do_add]
                      | ( '-' >> term)[&do_subt]
                 )
                ;

        }



        // Chaque element de la grammaire est une regle parametree par notre scanner.
        rule<ScannerT> expression, term, factor, integer, var_decl;

        // Symbole de demarrage de la grammaire
        rule<ScannerT> const& start() const { return expression; }
    };
};


