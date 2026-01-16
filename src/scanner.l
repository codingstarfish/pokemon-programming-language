%option noyywrap

%{
    #include "ast.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "parser.tab.h"
%}

%%

[\t\r\n]+ {}/* 공백,줄바꿈 처리*/  
"//".* {}/*주석 무시*/


/*변수선언 키워드*/

"를 잡았다!" { return CAUGHT; }


/*변수대입 키워드 */

"는" { return START_NUM_ASSIGN; }

"레벨이다." {return END_NUM_ASSIGN;}

"를 향해" { return START_ASSIGN; }
"는 쓰러졌다." { return END_ASSIGN; }



/*사칙연산 키워드*/


"몸통박치기!" { return OP_ADD; }
"화염방사!" { return OP_SUB; }
"물대포!" { return OP_MUL; }
"나뭇잎!" { return OP_DIV; }

/*출력 키워드*/

"는 기분 좋은듯이 울음소리를 냈다!" { return PRINT; }

/* 숫자 */
[0-9]+  { 
    yylval.ival = atoi(yytext);
    return NUMBER; 
}
/* 식별자 */

[a-zA-Z가-힣_][a-zA-Z0-9가-힣_]* {
    yylval.sval = strdup(yytext);
    return IDENT;
}

/* 예외처리 */
.       { printf("알 수 없는 문자: %s\n", yytext); }

%%