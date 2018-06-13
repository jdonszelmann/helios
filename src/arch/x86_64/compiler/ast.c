#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include <Foxlang.h>

ast_node * ast_new_node(){
	ast_node * t = malloc(sizeof(ast_node));
	*t = (ast_node){
		malloc(5*sizeof(ast_node*)),
		50,
		0,
		NULL,
		NULL,
	};
	return t;
}

ast_node * ast_add_new_node(ast_node * n){
	ast_node * new = ast_new_node();
	new->parent = n;
	n->children[n->childfilled]=new;
	if(n->childfilled >= n->childsize-2){
		n->childsize*=2;
		n->children = realloc(n->children,n->childsize*sizeof(ast_node*));
	}
	n->childfilled++;
	return new;
}

void ast_set_value(ast_node * n,char * s){
	n->value = malloc(strlen(s)*sizeof(char)+1);
	strcpy(n->value,s);
}

void ast_add_node(ast_node * n1,ast_node * n2){
	n2->parent = n1;
	n1->children[n1->childfilled]=n2;
	if(n1->childfilled>=n1->childsize){
		n1->childsize*=2;
		n1->children = realloc(n1->children,n1->childsize*sizeof(ast_node *));
	}
}

void ast_remove_children_helper(ast_node * n){
	for (int i = 0; i < n->childfilled; ++i){
		ast_remove_children_helper(n->children[i]);
	}
	ast_free_node(n);
}

void ast_remove_children(ast_node * n){
	// ast_remove_children_helper(n);
	n->childfilled = 0;
}

void ast_remove(ast_node * n){
	// ast_remove_children_helper(n);
	int found = 0;
	n->parent->childfilled-=1;
	for (int i = 0; i < n->parent->childfilled; ++i){
		if(n->parent->children[i]==n){
			found = 1;
		}
		if(found){
			n->parent->children[i] = n->parent->children[i+1];
		}
	}
}


void ast_free_node(ast_node * n){
	free(n->value);
	free(n);
}

static void ast_print_helper(ast_node * n,int indent){
	for (int i = 0; i < indent; ++i){
		printf("  ");
	}
	if(n->value == NULL){
		printf("<nil>\n");
	}else{
		printf("%s\n",n->value);
	}	
	for (int i = 0; i < n->childfilled; ++i){
		ast_print_helper(n->children[i],indent+1);
	}
}

void ast_print(ast_node * root){
	ast_print_helper(root,0);
}

