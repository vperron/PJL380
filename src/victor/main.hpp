/*=============================================================================
    Copyright (c) 2002-2003 Joel de Guzman
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#include "includes.hpp"



#include <boost/spirit.hpp>
#include <boost/lexical_cast.hpp>
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




    // Template d'arbre (pas forcément utile puisqu'on l'instancie sur le meme type mais bon...)
    struct Tree {


            Node * Me;

            Node * Left;
            Node * Right;

            // Des methodes de manipulation
            Tree(); 
            // Forme polonaise inverse : si on retire des éléments de la stack ce sera droite-gauche
            Tree(Node * me, Node * right, Node * left) {
                Me          = me;
                Right       = right;
                Left        = left;
            };

    };

    Tree::Tree() {
    }

    // Fonction str2frac ( conversion string --> fractional)
    fractional* str2frac(const string s) {
        int pos = s.find('/');
        return new fractional(
                boost::lexical_cast<int>(s.substr(0,pos)), 
                boost::lexical_cast<int>(s.substr(pos+1, s.size()-pos))
                    );
    }

    // Fonction dbl2frac ( conversion double --> fractional)
    fractional* dbl2frac(const double u) {
        
        int denom = 1;

        // Ici sans precision fixée, mais on peut imaginer de limiter à un certain nombre de decimales.
        while(modf(u*(double)denom,NULL) != 0) 
            denom *= 10;

        return new fractional(
                boost::lexical_cast<int>(u*denom), 
                denom);
    }



    // Racine et arbre courant
    Tree *root    = NULL;

    // Pile
    stack<Node*>  pile  = stack<Node *>();
    
    
    // ================================================= VARIABLES
    void    do_int(const int Value)   {
        cout << "INT(" << Value << ')' << endl;
        pile.push(new fractional(Value, 1));
    }

    void    do_var(char const* str, char const* end)    {
        string  s(str, end);
        cout << "VAR(" << s << ')' << endl;
        pile.push(new Variable(s));
    }

     
    void    do_frac(char const* str, char const* end)     { 
        string  s(str, end);
        cout << "FRACT(" << s << ')' << endl;
        pile.push(str2frac(s));

    }

    void    do_reel(const double Value)     { 
        cout << "REAL(" << Value << ')' << endl;
        pile.push(dbl2frac(Value));
    }   


    // =============================================== OPERATEURS
    void    do_pow(char const* str, char const* end)    {
        string  s(str, end);
        cout << "POWER" << endl;
        // Creation du noeud de fonction temporaire

        // Si la racine n'existe pas
        if ( root == NULL )
            root = new Tree(
                    new functionpower(),
                    pile.pop(),
                    pile.pop()
                    );
        else
            root = new Tree(new functionpower(),pile.pop(),root->Me);
    }

    void    do_add(char const*, char const*)     { 
        cout << "ADD\n"; 
        // Creation du noeud de fonction temporaire

        // Si la racine n'existe pas
        if ( root == NULL )
            root = new Tree(new operatorplus(),pile.pop(),pile.pop());
        else
            root = new Tree(new operatorplus(),pile.pop(),root->Me);
    }
    
    void    do_subt(char const*, char const*)    { 
        cout << "SUBTRACT\n"; 
        // Creation du noeud de fonction temporaire

        // Si la racine n'existe pas
        if ( root == NULL )
            root = new Tree(new functionpower(),pile.pop(),pile.pop());
        else
            root = new Tree(new functionpower(),pile.pop(),root->Me);
    }

    void    do_mult(char const*, char const*)    { 
        cout << "MULTIPLY\n"; 
        // Creation du noeud de fonction temporaire

        // Si la racine n'existe pas
        if ( root == NULL )
            root = new Tree(new operatormult(),pile.pop(),pile.pop());
        else
            root = new Tree(new operatormult(),pile.pop(),root->Me);
    }
    
    void    do_div(char const*, char const*)     { 
        cout << "DIVIDE\n";
        // Creation du noeud de fonction temporaire

        // Si la racine n'existe pas
        if ( root == NULL )
            root = new Tree(new functionpower(),pile.pop(),pile.pop());
        else
            root = new Tree(new functionpower(),pile.pop(),root->Me);
    }
    
    void    do_neg(char const*, char const*)     { 
        cout << "NEGATE\n"; 
        // Creation du noeud de fonction temporaire

        // Si la racine n'existe pas
        if ( root == NULL )
            root = new Tree(new functionpower(),pile.pop(),pile.pop());
        else
            root = new Tree(new functionpower(),pile.pop(),root->Me);
    }


    void    do_func(char const* str, char const* end)     { 
        string  s(str, end-1);
        cout << "FUNC(" << s << ')' << endl;
        // Creation du noeud de fonction temporaire

        // Si la racine n'existe pas
        if ( root == NULL )
            root = new Tree(new functionpower(),pile.pop(),pile.pop());
        else
            root = new Tree(new functionpower(),pile.pop(),root->Me);
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
                    //( +digit_p >> ch_p('/') >> +digit_p )[&do_frac]
                    ( uint_p >> ch_p('/') >> uint_p )[&do_frac]
                    ];

            // Reconnaître des flottants à convertir en fractional
            reel = strict_ureal_p[&do_reel];          // Ne reconnait, strictement, que les flottants.

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


