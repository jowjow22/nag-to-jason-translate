bisonTradutor: analise-lexica.l analise-sintatica.y converter.c
	bison -d analise-sintatica.y -Wcounterexamples
	flex -o analise-lexica.lex.c tradutorLex.l
	gcc -o $@ analise-lexica.tab.c analise-sintatica.lex.c converter.c -lfl -lm
	@echo Parser do tradutor pronto...