bisonTradutor: analise-lexica.l analise-sintatica.y main.c
	bison -d analise-sintatica.y -Wcounterexamples
	flex -o analise-lexica.lex.c analise-lexica.l
	gcc -o $@ analise-sintatica.tab.c analise-lexica.lex.c main.c -lfl -lm
	rm analise-sintatica.tab.c analise-sintatica.tab.h analise-lexica.lex.c
	@echo Parser do tradutor pronto...