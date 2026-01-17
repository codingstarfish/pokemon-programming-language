#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

static AST *make_node(NodeType type)
{
    AST *node = (AST *)malloc(sizeof(AST)); // 메모리 동적배당
    if (node == NULL)                       // 메모리 배당 실패
    {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(1);
    }
    node->type = type;
    node->ival = NULL;
    node->left = NULL;
    node->right = NULL;
    node->next = NULL;
    node->sval = NULL;
    return node;
}
AST *ast_var(char *name)
{
    AST *node = make_node(AST_VAR);
    node->sval = name; // 변수 이름 저장
    return node;
}
AST *ast_int(int value)
{
    AST *node = make_node(AST_INT);
    node->ival = value; //값 저장
    return node;
}
AST *ast_stmt_list(AST *head, AST *tail)
{
    if (head == NULL)
        return tail; // tail이 전체 리스트임
    AST *ptr = head;
    while (ptr->next != NULL) //리스트 끝 찾기
    {
        ptr = ptr->next;
    }
    ptr->next = tail; // 리스트 끝과 tail 연결
    return head;
}
AST *ast_printf(AST *expr)
{
    AST *node = make_node(AST_PRINTF);
    node->left = expr; //출력 값 저장
    return node;
}
AST *ast_assign(AST *var, AST *expr)
{
    AST *node = make_node(AST_ASSIGN);
    node->left = var; // 변수이름
    node->right = expr; // 저장할 값
    return node;
}
AST *ast_var_decl(char *name) 
{
    AST *node = make_node(AST_VAR_DECL);
    node->sval = name; // 변수 이름 설정
    return node;
}
AST *ast_bin(NodeType type, AST *left, AST *right)
{
    AST *node = make_node(type);
    node->left = left; // 왼쪽 피연산자
    node->right = right; //오른쪽 피연산자
    return node;
}
void ast_free(AST *node) //메모리 해제
{
    if (node == NULL)
        return;
    ast_free(node->left);
    ast_free(node->right);
    ast_free(node->next);
    free(node->sval);
    free(node);
}