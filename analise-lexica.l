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
"%" |
")"                 { return yytext[0]; }
"E"                 { return AND; }
"OU"                { return OR; }
"NAO"               { return NOT; }
"crencas"           { return BELIEFS; }
"objetivos"         { return GOALS; }
"planos"            { return PLANS; }
[a-z][a-zA-Z0-9]*   { yylval.s = strdup(yytext); return NAME; }
[\n]                { }
[\\\n]              { }
[\t]                { }
.                   { yyerror ("Caracter não reconhecido: %d\n", *yytext); }

%%