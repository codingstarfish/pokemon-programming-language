%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "ast.h"
    #include "codegen_x86.h"
    extern int yylex(void);
    void yyerror(const char* s);
    extern FILE* asm_out;
    AST* root;
%}

%code requires{
    #include "ast.h"
}

%union{
    int ival; /* 정수값 */
    char *sval; /* 문자열값 */
    AST* node;
}

/*토큰 선언*/

%token <ival> NUMBER /**/
%token <sval> IDENT /**/

%token CAUGHT /*"를 잡았다!"*/
%token START_ASSIGN /*"를 향해"*/
%token END_ASSIGN /*"는 쓰러졌다."*/
%token START_NUM_ASSIGN /*"는"*/
%token END_NUM_ASSIGN /*"레벨이다."*/
%token PRINT /*"는 기분 좋은듯이 울음소리를 냈다!"*/

%token OP_ADD /**/
%token OP_SUB /**/
%token OP_MUL /**/
%token OP_DIV /**/

%type <node> program stmt_list stmt expr

/*연산자, 우선순위 아래일수록 높음*/

%left OP_ADD OP_SUB
%left OP_MUL OP_DIV

%%

program:
    stmt_list{
        root = $1;
        printf("parsing completed, AST created\n");
    }
    ;
stmt_list:
    stmt {$$=$1}
    | stmt_list stmt {$$= ast_stmt_list($1,$2);}
    ;
stmt:
      IDENT CAUGHT { $$ = ast_var_decl($1);} /*<변수>를 잡았다!*/
    | IDENT START_NUM_ASSIGN NUMBER END_NUM_ASSIGN { $$ = ast_assign(ast_var($1),ast_int($3)); } /*<변수>는<number>레벨이다.*/
    | IDENT START_ASSIGN expr END_ASSIGN { $$ = ast_assign(ast_var($1),$3); }/*<변수>를 향해<expr>는 쓰러졌다.*/
    | IDENT PRINT { $$ = ast_printf(ast_var($1)); } /*<변수>는 기분 좋은듯이 울음소리를 냈다!*/
    ;
expr: 
    IDENT {$$ = ast_var($1);}
    | expr OP_ADD expr{$$ = ast_bin(AST_ADD,$1,$3);}
    | expr OP_SUB expr{$$ = ast_bin(AST_SUB,$1,$3);}
    | expr OP_MUL expr{$$ = ast_bin(AST_MUL,$1,$3);}
    | expr OP_DIV expr{$$ = ast_bin(AST_DIV,$1,$3);}
    ;
%%

void yyerror(const char* s) {
    fprintf(stderr, "Parse error: %s\n", s);
}