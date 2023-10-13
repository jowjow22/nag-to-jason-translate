#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "header.h"

struct believes *prependBelieve(struct believes *believes, char *newBelieve)
{
  if (newBelieve == NULL)
  {
    return believes;
  }

  struct believes *new = (struct believes *)malloc(sizeof(struct believes));

  new->believes = (char *)malloc(sizeof(char) * strlen(newBelieve) + 2);

  new->believes = newBelieve;

  strcat(new->believes, ".");
  new->next = believes;

  return new;
}

struct goals *prependGoal(struct goals *goals, char *newGoal)
{
  if (newGoal == NULL)
  {
    return goals;
  }

  struct goals *new = (struct goals *)malloc(sizeof(struct goals));

  char *formatedGoal = (char *)malloc(sizeof(char) * strlen(newGoal) + 3);
  strcat(formatedGoal, "!");
  strcat(formatedGoal, newGoal);

  new->goals = formatedGoal;
  new->next = goals;

  return new;
}

struct body *prependBody(struct body *body, char *newBody)
{
  if (newBody == NULL)
  {
    return body;
  }

  struct body *aux = body;

  struct body *new = (struct body *)malloc(sizeof(struct body));

  new->body = (char *)malloc(sizeof(char) * strlen(newBody) + 100);

  strcat(new->body, " .printf(\"");
  strcat(new->body, newBody);
  strcat(new->body, "\");");
  new->next = body;

  return new;
}
char *newExp(char *leftSide, char *rightSide, char *operator)
{
  char *new = (char *)malloc(1000);
  if (!strcmp(operator, "E"))
  {
    strcpy(new, leftSide);
    strcat(new, " & ");
    strcat(new, rightSide);
  }
  else if (!strcmp(operator, "OU"))
  {
    strcpy(new, leftSide);
    strcat(new, " | ");
    strcat(new, rightSide);
  }
  else if (!strcmp(operator, "NAO") && leftSide == NULL)
  {
    strcpy(new, "not ");
    strcat(new, rightSide);
  }
  else if (!strcmp(operator, "NAO") && rightSide == NULL)
  {
    strcpy(new, "not ");
    strcat(new, leftSide);
  }
  return new;
}

struct planContent *createContent(char *triggerEvent, char *context, struct body *body)
{
  struct planContent *new = (struct planContent *)malloc(sizeof(struct planContent));

  if (new == NULL)
  {
    yyerror("out of memory");
    exit(0);
  }

  new->triggerEvent = (char *)malloc(sizeof(char) * strlen(triggerEvent) + 2);
  strcat(new->triggerEvent, "+!");
  strcat(new->triggerEvent, triggerEvent);
  strcat(new->triggerEvent, ":");
  new->context = (char *)malloc(sizeof(char) * strlen(context) + 3);
  strcat(new->context, context);
  strcat(new->context, " <-");
  new->body = body;

  return new;
}

struct plans *createPlan(char *name, struct planContent *planContent)
{
  struct plans *new = (struct plans *)malloc(sizeof(struct plans));

  if (new == NULL)
  {
    yyerror("out of memory");
    exit(0);
  }

  new->name = name;
  new->planContent = planContent;
  new->next = NULL;

  return new;
}

struct plans *prependPlan(struct plans *plans, struct plans *newPlan)
{
  if (newPlan == NULL)
  {
    return plans;
  }

  newPlan->next = plans;

  return newPlan;
}
struct agents *createAgent(char *name, struct believes *believes, struct goals *goals, struct plans *plans)
{
  struct agents *new = (struct agents *)malloc(sizeof(struct agents));

  if (new == NULL)
  {
    yyerror("out of memory");
    exit(0);
  }

  new->name = name;
  new->believes = believes;
  new->goals = goals;
  new->plans = plans;
  new->next = NULL;

  return new;
}

struct agents *prependAgent(struct agents *agents, struct agents *newAgent)
{
  if (newAgent == NULL)
  {
    return agents;
  }

  // print agent
  printf("%s\n\n", newAgent->name);
  struct believes *auxBelieves = newAgent->believes;
  while (auxBelieves != NULL)
  {
    printf("%s\n", auxBelieves->believes);
    auxBelieves = auxBelieves->next;
  }
  printf("\n\n");

  struct goals *auxGoals = newAgent->goals;
  while (auxGoals != NULL)
  {
    printf("%s\n", auxGoals->goals);
    auxGoals = auxGoals->next;
  }

  printf("\n\n");

  struct plans *auxPlans = newAgent->plans;
  while (auxPlans != NULL)
  {

    printf("%s", auxPlans->planContent->triggerEvent);
    printf(" %s", auxPlans->planContent->context);

    struct body *aux = auxPlans->planContent->body;

    while (aux != NULL)
    {
      printf(" %s\n", aux->body);
      aux = aux->next;
    }

    auxPlans = auxPlans->next;
  }

  printf("\n");

  newAgent->next = agents;

  return newAgent;
}

void yyerror(char *s, ...)
{
  va_list ap;
  va_start(ap, s);
  fprintf(stderr, "%d: error: ", yylineno);
  vfprintf(stderr, s, ap);
  fprintf(stderr, "\n");
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    yyparse();
    return 0;
  }

  for (int i = 0; i < argc; i++)
  {
    FILE *f = fopen(argv[i], "r");

    if (!f)
    {
      perror(argv[i]);
      return 1;
    }

    yyrestart(f);
    yylineno = 1;
    yyparse();
    fclose(f);
  }
  return 0;
}