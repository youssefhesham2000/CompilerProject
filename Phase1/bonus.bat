IF EXIST bonus.exe DEL bonus.exe
IF EXIST lex.yy.c DEL lex.yy.c

"D:\Programs\GnuWin32\bin\flex.exe" bonus_flex_input.lex
gcc lex.yy.c -o bonus.exe
type input.txt | bonus.exe