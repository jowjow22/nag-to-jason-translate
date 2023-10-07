void yyerror(char *s, ...);
extern yylineno;

struct believes
{
  char *believes;
  struct believes *next;
};

struct goals
{
  char *goals;
  struct goals *next;
};

struct body
{
  char *body;
  struct body *next;
};

struct planContent
{
  char *triggerEvent;
  char *context;
  struct body *body;
};
struct plans
{
  char *name;
  struct planContent *planContent;
  struct plans *next;
};

struct agent
{
  char *name;
  struct believes *believes;
  struct goals *goals;
  struct plans *plans;
  struct agent *next;
};
