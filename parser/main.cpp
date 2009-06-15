/*
  
   First test file for parsing 

   Victor Perron - PJL380 - 2009

   Thanks to Dave Handley, Codeproject
    http://www.codeproject.com/KB/stl/introduction_spirit.aspx

*/


///////////////////////////////////////////////////////////////////////////////


// Include files for the boost spirit parsing library
#include <boost/spirit/core.hpp>

// Needs for input&output
#include <iostream>

// On fera des listes
#include <list>

// On manipulera des strings
#include <string>


///////////////////////////////////////////////////////////////////////////////


    // Definition du parser

// Definition d'un type de grammaire nommé Syntax
struct Syntax : public boost::spirit::grammar<Syntax>
{
    public:
        // Constructeur de la classe
        Syntax( CParser &parser );

        // Destructeur
        virtual ~Syntax();

        // Nested struct that constains the grammar def
        template <typename ScannerT>
            struct definition
            {
                public:
                    definition( Syntax const &self )
                    {
                        integer =
                            lexeme_d[ (+digit_p) ]
                            ;
                        factor =
                            integer |
                            vars |
                            '(' >> expression >> ')' |
                            ( '-' >> factor ) |
                            ( '+' >> factor )
                            ;
                        term =
                            factor >> *( ( '*' >> factor) | ( '/' >> factor ) )
                            ;
                        expression =
                            term >> *( ( '+' >> term ) | ( '-' >> term ) )
                            ;
                        assignment =
                            vars
                            >> '=' >> expression
                            ;
                        var_decl =
                            lexeme_d
                            [
                            ( ( alpha_p >> *( alnum_p | '_' ) )
                              - vars )[vars.add]
                            ]
                            ;
                        declaration =
                            "int" >> var_decl >> *( ',' >> var_decl )
                            ;
                        baseExpression =
                            str_p( "exit" )[*self.m_finishedProcessing] |
                            str_p( "mod" ) >> integer |
                            declaration |
                            assignment |
                            '?' >> expression
                            ;
                    }
                    boost::spirit::symbols<int> vars;
                    boost::spirit::rule<ScannerT> integer, factor, term,
                        expression, assignment, var_decl, declaration,
                        baseExpression;
                    const boost::spirit::rule<ScannerT> &start() const { return baseExpression; }
            };
        friend struct definition;
    private:
        Private::FinishedProcessing *m_finishedProcessing;
};



boost::spirit::parse_info<> info;
Syntax parser;
info = boost::spirit::parse( line.c_str(), parser, boost::spirit::space_p );
