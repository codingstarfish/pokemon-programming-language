#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

extern FILE *asm_out;

typedef struct
{
    char *name;
    int offset;

} Symbol;

#define MAX_SYMBOLS 128
static Symbol sym_table[MAX_SYMBOLS];
static int sym_count = 0;
static int find_symbol(char *name)
{
    for (int i = 0; i < sym_count; i++)
    {
        if (strcmp(sym_table[i].name, name) == 0)
        {
            return sym_table[i].offset;
        }
    }
    return 0; // 못찾음
}

static void add_symbol(char *name)
{
    if (find_symbol(name) != 0) // 이미 존재함
        return;
    if (sym_count >= MAX_SYMBOLS)
    {
        fprintf(stderr, "Error: Too many variables\n"); // 변수 최대 개수 넘음
        exit(1);
    }
    sym_table[sym_count].name = name;
    sym_table[sym_count].offset = -4 * (sym_count + 1); // -4,-8, ...
    sym_count++;
}
/*수식 + 변수 값 설정 코드 생성*/
void gen_expr(AST *node, FILE *fp)
{
    if (node == NULL)
    {
        return;
    }
    int offset;
    switch (node->type)
    {
    case AST_VAR:
        offset = find_symbol(node->sval);
        if (offset == 0)
        {
            fprintf(stderr, "Error: Undefined variable %s\n", node->sval);
            exit(1);
        }
        fprintf(fp, "    movl %d(%%rbp), %%eax\n", offset);
        break;
    case AST_INT:
        fprintf(fp, "    movl $%d, %%eax\n", node->ival);
        break;
    case AST_ADD:
    case AST_SUB:
    case AST_MUL:
    case AST_DIV:
        gen_expr(node->left, fp);
        fprintf(fp, "    pushq %%rax\n");
        gen_expr(node->right, fp);
        fprintf(fp, "    movl %%eax, %%ebx\n");
        fprintf(fp, "    popq %%rax\n");
        if (node->type == AST_ADD) // 더하기
            fprintf(fp, "    addl %%ebx, %%eax\n");
        if (node->type == AST_SUB) // 빼기
            fprintf(fp, "    subl %%ebx, %%eax\n");
        if (node->type == AST_MUL) // 곱하기
            fprintf(fp, "    imul %%ebx, %%eax\n");
        if (node->type == AST_DIV) // 나누기
        {
            fprintf(fp, "    cltd\n");
            fprintf(fp, "    idivl %%ebx\n");
        }
        break;
    default:
        break;
    }
}
/* 문장 코드 생성 */
void gen_stmt(AST *node, FILE *fp)
{
    if (node == NULL)
        return;
    int offset;
    switch (node->type)
    {
    case AST_PRINTF: // 출력
        gen_expr(node->left, fp);
#ifdef _WIN32 // Windows
        fprintf(fp, "    movl %%eax, %%edx\n");
        fprintf(fp, "    leaq .LC0(%%rip), %%rcx\n");
        fprintf(fp, "    subq $32, %%rsp\n");
        fprintf(fp, "    call printf\n");
        fprintf(fp, "    addq $32, %%rsp\n");
#else // linux
        fprintf(fp, "    movl %%eax, %%esi\n");
        fprintf(fp, "    leaq .LC0(%%rip), %%rdi\n");
        fprintf(fp, "    movl $0, %%eax\n");
        fprintf(fp, "    call printf\n");
#endif
        break;
    case AST_ASSIGN: // 대입
        gen_expr(node->right, fp);
        offset = find_symbol(node->left->sval);
        fprintf(fp, "    movl %%eax, %d(%%rbp)\n", offset);
        break;
    case AST_VAR_DECL: // 변수선언
        offset = find_symbol(node->sval);
        fprintf(fp, "    movl $0, %d(%%rbp)\n", offset); // 0으로 초기화
        break;
    default:
        break;
    }
}

void gen_code(AST *root)
{
    // 심볼 수집하기
    AST *ptr = root;
    while (ptr != NULL)
    {
        if (ptr->type == AST_VAR_DECL)
        {
            add_symbol(ptr->sval);
        }
        ptr = ptr->next;
    }
    // 어셈블리 헤더
    fprintf(asm_out, "   .section .rodata\n");
    fprintf(asm_out, ".LC0:\n    .string \"%%d\\n\"\n");
    fprintf(asm_out, "    .text\n    .globl main\nmain:\n");
    fprintf(asm_out, "    pushq %%rbp\n    movq %%rsp, %%rbp\n");

    int stack_size = (sym_count * 4 + 15) & ~15; // 16바이트 정렬
    if (stack_size > 0)
        fprintf(asm_out, "   subq $%d, %%rsp\n", stack_size);

    ptr = root;
    while (ptr != NULL)
    {
        gen_stmt(ptr, asm_out);
        ptr = ptr->next;
    }
    fprintf(asm_out, "    movl $0, %%eax\n");
    fprintf(asm_out, "    leave\n");
    fprintf(asm_out, "    ret\n");
}