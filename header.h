void yyerror(char *s, ...);
extern yylineno;

struct believes
{
  char *believes;
  struct believes *next;
}

struct goals
{
  char *goals;
  struct goals *next;
}

struct body
{
  char *body;
  struct body *next;
}

struct plans
{
  char *plans;
  struct plans *next;
}
