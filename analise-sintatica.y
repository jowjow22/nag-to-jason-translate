%{
    #include<stdio.h>
    #include<stdlib.h>
    #include "header.h"
%}

%union {

}

// precisa arrumar isso aqui, fiz só a bnf

%token  <s> NAME BELIEFS GOALS PLANS
%token  <s> OR NOT AND

%type <a> agent agents
%type <s> triggerEvent context logExp
%type <s> plansName beliefs beliefsName body plans, goalsName, goals

%%

agents:  { $$ = NULL; }
    | agent '%' agents { $$  = newAgent($1, $2); }
    ;
agent: '#' NAME BELIEFS beliefs GOALS goals PLANS plans { $$ = newAgent($2, $4, $6, $8); }
    ;
beliefs: '{' beliefsName '}' { $$ = $2 }
    ;  
beliefsName:{ $$ = NULL} 
    | NAME ';' beliefsName { $$ = newBelief($1, $3); }
    ;
goals: '{' goalsName '}' { $$ = $2 }
    ;
goalsName: { $$ = NULL} 
    | NAME ';' goalsName { $$ = newGoal($1, $3); }
    ;
plans: '{' plansName '}' { $$ = $2 }
    ;
plansName: { $$ = NULL} 
    | NAME ';' plansName { $$ = newPlan($1, $3); }
    ;
plansTuple:  '(' triggerEvent ';' context ';' body ')'
    ;
triggerEvent: NAME
    ;
context: { $$ = NULL } | logExp | NAME
    ;
logExp: NAME AND NAME | NAME OR NAME | NOT NAME
    ;
body: '{' bodysFormula ';' '}'
    ;
bodysFormula: NAME
    ;
%%