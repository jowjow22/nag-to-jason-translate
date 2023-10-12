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

// believes
struct believes *prependBelieve(struct believes *believes, char *newBelieve);
// goals
struct goals *prependGoal(struct goals *goals, char *newGoal);
// planContent
struct planContent *createPlanContent(char *triggerEvent, char *context, struct body *body);

struct body *prependBody(struct body *body, char *newBody);
// plans
struct plans *createPlan(char *name, struct planContent *planContent);

struct plans *prependPlan(struct plans *plans, struct plans *newPlan);

struct planContent *createContent(char *triggerEvent, char *context, struct body *body);
// exp
char *newExp(char *leftSide, char *rightSide, char *operator);
