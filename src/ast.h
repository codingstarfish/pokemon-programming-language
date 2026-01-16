#ifndef AST_H
#define AST_H

typedef enum{
    /*사칙연산*/
    AST_ADD, AST_SUB, AST_MUL,AST_DIV,

    AST_VAR,
    AST_INT,
    AST_STMT_LIST,
    AST_PRINTF,
    AST_ASSIGN,
    AST_VAR_DECL,


}NodeType;

typedef struct AST{
    NodeType type;
    int ival;
    char* sval;
    struct AST* left;
    struct AST* right;
    struct AST* next;
}AST;

AST* ast_var(char* name);
AST* ast_int(int value);
AST* ast_stmt_list(AST*head,AST*tail);
AST* ast_printf(AST*expr);
AST* ast_assign(AST*var,AST*expr);
AST* ast_var_decl(char* name);
AST* ast_bin(NodeType type,AST*left,AST*right);

#endif
