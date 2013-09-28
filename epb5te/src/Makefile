
all: turtle eins.ps

eins.ps: eins.tlt turtle
	./turtle < eins.tlt > eins.ps

lex.yy.o:  lex.yy.c turtle-epb5te.tab.h symtab.h
	gcc -c lex.yy.c

lex.yy.c: turtle.l
	flex turtle.l
	
turtle-epb5te.tab.h: turtle-epb5te.y
	bison -d turtle-epb5te.y
	
turtle-epb5te.tab.c: turtle-epb5te.y
	bison -d turtle-epb5te.y
	
turtle-epb5te.tab.o: turtle-epb5te.tab.c symtab.h
	gcc -c turtle-epb5te.tab.c

turtle: turtle-epb5te.tab.o lex.yy.o symtab.c
	gcc lex.yy.o turtle-epb5te.tab.o symtab.c -lfl -o turtle

clean:
	rm -f turtle lex.* turtle-epb5te.tab.* *.o eins.ps

