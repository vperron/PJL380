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
#include <stack>
#include <string>



using namespace std;
// Plus pratique pour appeller les fonctions de l'API spirit.
using namespace boost::spirit;



// Actions sémantiques exécutées sur trigger (reconnaissance d'un objet par exemple)
// Ce ne sont que des exemples.

// A l'intérieur de ce namespace, tout sera statique.
namespace
{
    
    double val = 0;



    // Template d'arbre
    template <typename T> struct Tree {

            Tree<T> Parent;

            T Id;

            Tree<T>* Left;
            Tree<T>* Right;

    };

    // Racine et arbre courant
    Tree<Node>* root    = NULL;
    Tree<Node>* current = NULL;

    // Pile
    stack<Node*>  pile  = stack<Node *>();
    
    
    void    do_int(const int Value)   {
        cout << "INT(" << Value << ')' << endl;
        pile.push(new fractional(Value, 1));
    }

    void    do_var(char const* str, char const* end)    {
        string  s(str, end);
        cout << "VAR(" << s << ')' << endl;
        pile.push(new Variable(s));
    }

    void    do_pow(char const* str, char const* end)    {
        string  s(str, end);
        cout << "POWER" << endl;
    }

    void    do_add(char const*, char const*)     { 
        cout << "ADD\n"; 
    }
    
    void    do_subt(char const*, char const*)    { 
        cout << "SUBTRACT\n"; 
    }

    void    do_mult(char const*, char const*)    { 
        cout << "MULTIPLY\n"; 
    }
    
    void    do_div(char const*, char const*)     { 
        cout << "DIVIDE\n";
    }
    
    void    do_neg(char const*, char const*)     { 
        cout << "NEGATE\n"; 
    }
     
    void    do_frac(char const* str, char const* end)     { 
        string  s(str, end);
        cout << "FRACT(" << s << ')' << endl;
    }

    void    do_reel(double Value)     { 
        cout << "REAL(" << Value << ')' << endl;
        Value++;
    }   

    void    foo(const double Value)     { 
        cout << "foo = " << val << endl;
    }   

    void    do_func(char const* str, char const* end)     { 
        string  s(str, end-1);
        cout << "FUNC(" << s << ')' << endl;
    }






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

            // Reconnaitre des fractional comme variables
            fractional = 
                lexeme_d[
                    ( +digit_p >> ch_p('/') >> +digit_p )[&do_frac]
                    ];

            // Reconnaître des flottants à convertir en fractional
            reel = strict_ureal_p[&do_reel][&foo];          // Ne reconnait, strictement, que les flottants.

            // Un entier : lexeme_d passe en mode parsing caractère. Plante sur des espaces.
            integer = uint_p[&do_int]  ;

            // une declaration de vars est un lexeme_d d'un caractere puis une suite de cars alphanums ou _ .
            // La declaration est retenue uniquement si la variable n'existe pas.
            var_decl =
                lexeme_d[  ( +alpha_p >> *( alnum_p | '_' ) )[&do_var] ];


            // Une fonction
            function = confix_p(lexeme_d[ ((+alpha_p >> *(alnum_p | '_')) >> '(')[&do_func] ], expression, ch_p(')'));



            // Un facteur : un entier ou une variable ou une expression entre parentheses, ou +/- un autre facteur
            // Attention aux priorités.
            factor =
                reel |
                fractional |
                integer |
                function |
                var_decl |
                '(' >> expression >> ')' |
                ( '-' >> factor )[&do_neg] |
                ( '+' >> factor )
                ;

            // un TERME est un facteur que multiplie ou divise d'autres facteurs
            term =
                factor 
                >> *(    ( '^' >> factor)[&do_pow]
                     | ( '/' >> factor)[&do_div]
                     | ( '*' >> factor)[&do_mult]
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
        rule<ScannerT> expression, term, factor, integer, var_decl, function, reel, fractional, power;



        // Symbole de demarrage de la grammaire
        rule<ScannerT> const& start() const { return expression; }
    };
};


