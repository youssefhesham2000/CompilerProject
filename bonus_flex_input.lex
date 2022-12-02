
/* scanner for a toy Pascal-like language */

%option noyywrap
%{
/* need this for the call to atof() below */
#include <math.h>
%}

LETTER   [a-z]|[A-Z]
DIGIT    [0-9]
ID       {LETTER}({LETTER}|{DIGIT})*
DIGITS   {DIGIT}+
NUM      {DIGITS}|{DIGITS}"."{DIGITS}(E{DIGITS})?
RELOP    ==|!=|>|>=|<|<=
ADDOP    "+"|"-"
MULOP    "*"|"/"
ASSIGN   =



%%

{DIGITS}      {
             printf( "A whole number: %s (%d)\n", yytext,
                    atoi( yytext ) );     
            }

{NUM}         {
            printf( "A floating point number: %s (%d)\n", yytext,
                    atoi( yytext ) );
            }



if|else|while        {
            printf( "A keyword: %s\n", yytext );
            }

{ID}        printf( "An identifier: %s\n", yytext );

{ADDOP}     printf( "An addition operator: %s\n", yytext );

{MULOP}     printf( "A multiplication operator: %s\n", yytext );

{RELOP}     printf( "A relational operator: %s\n", yytext );

";"|","|"("|")"|"{"|"}" printf( "Punctuation: %s\n", yytext );

[ \t\n]+          /* eat up whitespace */

.           printf( "Unrecognized character: %s\n", yytext );
  
%%
  
main( argc, argv )
int argc;
char **argv;
{
  ++argv, --argc;  /* skip over program name */
  if ( argc > 0 )
    yyin = fopen( argv[0], "r" );
  else
    yyin = stdin;

  yylex();
}