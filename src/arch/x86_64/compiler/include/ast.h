#ifndef AST_H
#define AST_H

#include <Foxlang.h>

typedef struct ast_node{
	struct ast_node ** children;
	int childsize;
	int childfilled;
	struct ast_node * parent;
	char * value;
}ast_node;


ast_node * ast_new_node();
ast_node *  ast_add_new_node(ast_node *);
void ast_add_node(ast_node *,ast_node *);
void ast_free_node(ast_node *);
void ast_print(ast_node * root);
void ast_set_value(ast_node * n,char * s);
void ast_remove_children(ast_node * n);
void ast_remove(ast_node * n);

#endif