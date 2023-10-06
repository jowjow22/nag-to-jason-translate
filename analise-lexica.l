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
"E"                 { return AND; }
"NAO"               { return NOT; }
"crencas"           { return BELIEFS; }
"objetivos"         { return GOALS; }
"planos"            { return PLANS; }
[a-z][a-zA-Z0-9]*   { return NAME; }
[\n]                { }
[\t]                { }
.                   { yyerror ("Caracter não reconhecido: %c\n", *yytext); }

%%