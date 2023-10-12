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

  strcat(new->believes, ".");

  new->believes = strdup(newBelieve);
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

  char *formatedGoal = (char *)malloc(sizeof(char) * strlen(newGoal) + 2);
  strcat(formatedGoal, "!");
  strcat(formatedGoal, newGoal);
  strcat(formatedGoal, ".");

  new->goals = strdup(formatedGoal);
  new->next = goals;

  return new;
}

struct planContent *createPlanContent(char *triggerEvent, char *context, struct body *body)
{
  struct planContent *new = (struct planContent *)malloc(sizeof(struct planContent));

  new->triggerEvent = strdup(triggerEvent);
  new->context = strdup(context);
  new->body = body;

  return new;
}

struct plans *prependPlan(struct plans *plans, char *newPlan)
{
  if (newPlan == NULL)
  {
    return plans;
  }

  struct plans *new = (struct plans *)malloc(sizeof(struct plans));

  strcat(new->name, ".");

  new->name = strdup(newPlan);
  new->next = plans;

  return new;
}

struct body *prependBody(struct body *body, char *newBody)
{
  if (newBody == NULL)
  {
    return body;
  }

  struct body *new = (struct body *)malloc(sizeof(struct body));

  strcat(new->body, ".printf(\"");
  strcat(new->body, newBody);
  strcat(new->body, "\");");

  new->body = newBody;
  new->next = body;

  return new;
}
char *newExp(char *leftSide, char *rightSide, char *operator)
{
  char *new = (char *)malloc(sizeof(char) * strlen(leftSide) + strlen(rightSide) + strlen(operator) + 1);
  if (strcmp(operator, "E"))
  {
    strcat(new, leftSide);
    strcat(new, " & ");
    strcat(new, rightSide);
  }
  else if (strcmp(operator, "OU"))
  {
    strcat(new, leftSide);
    strcat(new, " | ");
    strcat(new, rightSide);
  }
  else if (strcmp(operator, "NAO") && leftSide == NULL)
  {
    strcat(new, "not");
    strcat(new, rightSide);
  }
  else if (strcmp(operator, "NAO") && rightSide == NULL)
  {
    strcat(new, "not");
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

  new->triggerEvent = triggerEvent;
  new->context = context;
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