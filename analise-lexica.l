%option noyywrap nodefault yylineno

%{
    #include "header.h"
    #include "analise-sintatica.tab.h"

%}

%%

":" |
";" |
"{" |
"}" |
"(" |
")"                 { return yytext[0]; }
"E"                 { return E; }
"NAO"               { return NAO; }
"crencas"           { return CRENCAS; }
"objetivos"         { return OBJETIVOS; }
"planos"            { return PLANOS; }
[a-z][a-zA-Z0-9]*   { return NAME; }
[\n]                { }
[\t]                { }
.                   { yyerror ("Caracter não reconhecido: %c\n", *yytext); }

%%