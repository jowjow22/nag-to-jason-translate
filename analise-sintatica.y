%{
    #include<stdio.h>
    #include<stdlib.h>
    #include "header.h"
%}

%union {
    struct agent *a;
    struct beliefs *b;
    struct goals *g;
    struct plans *p;
    struct body *bo;
    struct planContent *pc;
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

%start agents

%%

agents:  { $$ = NULL; }
    | agent '%' agents { $$ = NULL; }
    ;
agent: '#' NAME BELIEFS beliefs GOALS goals PLANS plans { $$ = NULL; }
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
plans: 
    | { $$ = NULL; } 
    | '{' plan ';' plans '}' { prependPlan($4, $2);}
    ;
plan:  { $$ = NULL; } 
    | NAME plansTuple { createPlan($1, $2); }
    ;
plansTuple:  '(' triggerEvent ';' context ';' body ')' { $$ = createContent($2, $4, $6); }
    ;
triggerEvent: NAME { $$ = $1; }
    ;
context: { $$ = NULL; } 
    | logExp { $$ = $1; }
    | NAME { $$ = $1; }
    ;
logExp: NAME AND NAME { $$ = newExp($1, $3, $2); }
    | NAME OR NAME { $$ =newExp($1, $3, $2); }
    | NOT NAME { $$ = newExp(NULL, $3, $2); }
    ;
body: '{' bodysFormula '}' { $$ = $2; }
    ;
bodysFormula:  { $$ = NULL; } |
    NAME ';' bodysFormula { $$ = prependBody($3, $1); }
    ;
%%