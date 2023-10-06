#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "header.h"

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