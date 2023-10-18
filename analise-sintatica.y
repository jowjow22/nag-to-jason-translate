%{
    #include<stdio.h>
    #include<stdlib.h>
    #include "header.h"
%}

%union {
    struct agents *a;
    struct believes *b;
    struct goals *g;
    struct plans *p;
    struct body *bo;
    struct planContent *pc;
    void *v;
    char *s;
}

%token  <s> NAME BELIEFS GOALS PLANS
%token  <s> OR NOT AND

%type <a> agent agents
%type <s> triggerEvent context logExp
%type <b> beliefs beliefsName
%type <g> goals goalsName
%type <p> plans plan
%type <pc> plansTuple
%type <bo> body bodysFormula
%type <v> initial;

%start initial

%%

initial: agents { printList($1); }
    ;
agents:  { $$ = NULL; }
    | agent '%' agents { $$ = prependAgent($3, $1); }
    ;
agent: '#' NAME BELIEFS ':' beliefs GOALS ':' goals PLANS ':' '{' plans '}' { $$ = createAgent($2, $5, $8, $12);}
    ;
beliefs: '{' beliefsName '}'  { $$ = $2; }
    ;  
beliefsName: { $$ = NULL; } 
    | NAME ';' beliefsName { $$ = prependBelieve($3, $1); }
    ;
goals: '{' goalsName '}'  { $$ = $2; }
    ;
goalsName: { $$ = NULL; } 
    | NAME ';' goalsName { $$ = prependGoal($3, $1); }
    ;
plans:  { $$ = NULL; } 
    |  plan ';' plans  { $$ = prependPlan($3, $1);}
    ;
plan:  { $$ = NULL; } 
    | NAME plansTuple { $$ = createPlan($1, $2); }
    ;
plansTuple:  '(' triggerEvent ';' context ';' body ')' { $$ = createContent($2, $4, $6); }
    ;
triggerEvent: NAME { $$ = $1; }
    ;
context: { $$ = NULL; } 
    | logExp { $$ = $1; }
    | NAME { $$ = $1; }
    ;
logExp: NAME AND NAME { $$ = newExp($1, $3, "E");}
    | NAME OR NAME { $$ = newExp($1, $3, "OU"); }
    | NOT NAME { $$ = newExp(NULL, $2, "NAO");  }
    ;
body: '{' bodysFormula '}' { $$ = $2; }
    ;
bodysFormula:  { $$ = NULL; } |
    NAME ';' bodysFormula { $$ = prependBody($3, $1); }
    ;
%%