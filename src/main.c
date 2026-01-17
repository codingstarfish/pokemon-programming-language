#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

#ifdef _WIN32
#include <windows.h>
#endif

extern FILE *yyin;    // scanner 가 읽을 입력 파일 스트림
extern int yyparse(); // parser 진입함수
extern AST *root;     // AST의 루트노드

FILE *asm_out; // 출력파일 포인터

void gen_code(AST *root); // generate code

int main(int argc, char **argv)
{

    #ifdef _WIN32
        SetConsoleOutputCP(65001); // 콘솔 출력을 UTF-8로 고정
    #endif
    
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <inputfile>\n", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r"); // 입력파일 열기
    if (!yyin)                  // 입력파일 열기 실패
    {
        perror("Failed to open input file");
        return 1;
    }
    printf("file opened successfully");

    printf("Compiling %s...\n", argv[1]); // 파싱 시작(AST 생성)
    if (yyparse() != 0)                   // 파싱 실패, 문법 오류
    {
        fprintf(stderr, "Parsing failed due to syntax errors\n");
        fclose(yyin);
        return 1;
    }
    printf("Parsing completed! AST generated.\n");

    asm_out = fopen("out.s", "w"); // 출력파일 열기
    if (!asm_out)                  // 출력파일 열기 실패
    {
        perror("Failed to open output file 'out.s'");
        fclose(yyin);
        return 1;
    }

    if (root != NULL) // root node 존재, 프로그램 작성 성공
    {
        gen_code(root);
        printf("Code generation completed!");
    }
    else // root node 없음
    {
        printf("AST root is NULL(Empty program?)\n");
    }

    fclose(yyin);
    fclose(asm_out);
    ast_free(root);
    return 0;
}