flex lang.flex
bison --verbose -d analis.y -o analis.cc
cc -c lex.yy.c -o lex.yy.o
c++ lex.yy.o analis.cc -o bison.out
