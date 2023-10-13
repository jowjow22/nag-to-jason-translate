void yyerror(char *s, ...);
int yyparse(void);
void yyrestart(FILE *f);
int yylex(void);
extern int yylineno;

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

struct agents
{
  char *name;
  struct believes *believes;
  struct goals *goals;
  struct plans *plans;
  struct agents *next;
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
struct agents *createAgent(char *name, struct believes *believes, struct goals *goals, struct plans *plans);
struct agents *prependAgent(struct agents *agents, struct agents *newAgent);
// exp
char *newExp(char *leftSide, char *rightSide, char *operator);
