
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include <Foxlang.h>


int currentpos = 0;
Token * nowparsing;
Token sym;


static void next(){
	currentpos++;
	sym = nowparsing[currentpos];
}

static int acceptident(char * c, ast_node * ast){
	ast_node * temp = ast_add_new_node(ast);
	ast_set_value(temp,c);

	if(sym.id == IDENT && sym.content != NULL && strcmp(sym.content,c)==0){
		next();
		return 1;
	}
	ast_remove(temp);
	return 0;
}

static int accept(TokenID id, ast_node * ast){
	ast_node * temp = ast_add_new_node(ast);
	ast_set_value(temp,id_to_token(id));

	if(sym.id == id){
		next();
		return 1;
	}
	ast_remove(temp);
	return 0;
}

static int getpos(){
	return currentpos;
}

static void setpos(int pos){
	currentpos = pos;
}

static int testlist_comp(ast_node * ast){
	ast_node * temp = ast_add_new_node(ast);
	ast_set_value(temp,"testlist_comp");
	// testlist_comp: (test|star_expr) ( comp_for | (',' (test|star_expr))* [','] )
	return 0;
}

static int dictset_comp(ast_node * ast){
	ast_node * temp = ast_add_new_node(ast);
	ast_set_value(temp,"dictset_comp");
	// testlist_comp: (test|star_expr) ( comp_for | (',' (test|star_expr))* [','] )
	ast_remove(temp);
	return 0;
}

static int atom(ast_node * ast){
	ast_node * temp = ast_add_new_node(ast);
	ast_set_value(temp,"atom");

	int savepos = getpos();
	if(accept(LPAR,temp)){
		if(testlist_comp(temp)){

		}
		if(accept(RPAR,temp)){
			return 1;
		}
		ast_remove(temp);
		return 0;
	}
	ast_remove_children(temp);
	setpos(savepos);
	if(accept(LSQB,temp)){
		if(testlist_comp(temp)){

		}
		if(accept(RSQB,temp)){
			return 1;
		}
		ast_remove(temp);
		return 0;
	}
	ast_remove_children(temp);
	setpos(savepos);
	if(accept(LBRACE,temp)){
		if(dictset_comp(temp)){

		}
		if(accept(RBRACE,temp)){
			return 1;
		}
		ast_remove(temp);
		return 0;
	}
	ast_remove_children(temp);
	setpos(savepos);
	if(accept(NAME,temp)){
		return 1;
	}
	ast_remove_children(temp);
	setpos(savepos);
	if(accept(NUMBER,temp)){
		return 1;
	}
	ast_remove_children(temp);
	setpos(savepos);
	if(accept(STRING,temp)){
		while(accept(STRING,temp)){

		}
		return 1;
	}
	ast_remove_children(temp);
	setpos(savepos);
	if(acceptident("None",temp)){
		return 1;
	}
	ast_remove_children(temp);
	setpos(savepos);
	if(acceptident("False",temp)){
		return 1;
	}
	ast_remove_children(temp);
	setpos(savepos);
	if(acceptident("True",temp)){
		return 1;
	}
	ast_remove(temp);
	return 0;
}

static int trailer(ast_node * ast){
	ast_node * temp = ast_add_new_node(ast);
	ast_set_value(temp,"trailer");

	ast_remove(temp);
	return 0;
}

static int atom_expr(ast_node * ast){
	#if AST_LARGE
	ast_node * temp = ast_add_new_node(ast);
	ast_set_value(temp,"atom_expr");
	#else
	ast_node * temp = ast;
	#endif

	if(atom(temp)){
		while(trailer(temp)){

		}
		return 1;
	}
	#if AST_LARGE
	ast_remove(temp);
	#endif
	return 0;
}

//forward declaration of factor to make power work.
static int factor(ast_node * ast);

static int power(ast_node * ast){
	#if AST_LARGE
	ast_node * temp = ast_add_new_node(ast);
	ast_set_value(temp,"power");
	#else
	ast_node * temp = ast;
	#endif

	if(atom_expr(temp)){
		if(accept(DSTAR,temp)){
			if(factor(temp)){
				return 1;
			}
			#if AST_LARGE
			ast_remove(temp);
			#endif
			return 0;
		}
		return 1;
	}
	#if AST_LARGE
	ast_remove(temp);
	#endif
	return 0;
}

static int factor(ast_node * ast){
	#if AST_LARGE
	ast_node * temp = ast_add_new_node(ast);
	ast_set_value(temp,"factor");
	#else
	ast_node * temp = ast;
	#endif

	if(accept(PLUS,temp)){
		if(factor(temp)){
			
		}else{
			#if AST_LARGE
			ast_remove(temp);
			#endif
			return 0;
		}
	}
	if(accept(MINUS,temp)){
		if(factor(temp)){
			
		}else{
			ast_remove(temp);
			return 0;
		}			
	}
	if(accept(TILDE,temp)){
		if(factor(temp)){

		}else{
			ast_remove(temp);
			return 0;
		}
	}
	if(power(temp)){
		return 1;
	}
	ast_remove(temp);
	return 0;
}

static int stardivmod(ast_node * ast){
	#if AST_LARGE
	ast_node * temp = ast_add_new_node(ast);
	ast_set_value(temp,"stardivmod");
	#else
	ast_node * temp = ast;
	#endif

	int savepos = getpos();
	if(accept(STAR,temp)){
		return 1;
	}
	#if AST_LARGE
	ast_remove_children(temp);
	#endif
	setpos(savepos);
	if(accept(AT,temp)){
		return 1;
	}
	#if AST_LARGE
	ast_remove_children(temp);
	#endif
	setpos(savepos);
	if(accept(SLASH,temp)){
		return 1;
	}
	#if AST_LARGE
	ast_remove_children(temp);
	#endif
	setpos(savepos);
	if(accept(PERCENT,temp)){
		return 1;
	}
	#if AST_LARGE
	ast_remove_children(temp);
	#endif
	setpos(savepos);
	if(accept(DSLASH,temp)){
		return 1;
	}
	#if AST_LARGE
	ast_remove(temp);
	#endif
	return 0;	
}

static int term(ast_node * ast){
	#if AST_LARGE
	ast_node * temp = ast_add_new_node(ast);
	ast_set_value(temp,"term");
	#else
	ast_node * temp = ast;
	#endif

	if(factor(temp)){
		while(stardivmod(temp)){
			if(factor(temp)){
				continue;
			}
			#if AST_LARGE
			ast_remove(temp);
			#endif
			return 0;
		}
		return 1;
	}
	#if AST_LARGE
	ast_remove(temp);
	#endif
	return 0;
}

static int plusminus(ast_node * ast){
	#if AST_LARGE
	ast_node * temp = ast_add_new_node(ast);
	ast_set_value(temp,"plusminus");
	#else
	ast_node * temp = ast;
	#endif

	int savepos = getpos();
	if(accept(PLUS,temp)){
		return 1;
	}
	#if AST_LARGE
	ast_remove_children(temp);
	#endif
	setpos(savepos);
	if(accept(MINUS,temp)){
		return 1;
	}
	#if AST_LARGE
	ast_remove(temp);
	#endif
	return 0;
}

static int arith_expr(ast_node * ast){
	#if AST_LARGE
	ast_node * temp = ast_add_new_node(ast);
	ast_set_value(temp,"arith_expr");
	#else
	ast_node * temp = ast;
	#endif

	if(term(temp)){
		while(plusminus(temp)){
			if(term(temp)){
				continue;
			}
			#if AST_LARGE
			ast_remove(temp);
			#endif
			return 0;
		}
		return 1;
	}
	#if AST_LARGE
	ast_remove(temp);
	#endif
	return 0;
}

static int shift(ast_node * ast){
	#if AST_LARGE
	ast_node * temp = ast_add_new_node(ast);
	ast_set_value(temp,"shift");
	#else
	ast_node * temp = ast;
	#endif

	int savepos = getpos();
	if(accept(LSHIFT,temp)){
		return 1;
	}
	#if AST_LARGE
	ast_remove_children(temp);
	#endif
	setpos(savepos);
	if(accept(RSHIFT,temp)){
		return 1;
	}
	#if AST_LARGE
	ast_remove(temp);
	#endif
	return 0;
}

static int shift_expr(ast_node * ast){
	#if AST_LARGE
	ast_node * temp = ast_add_new_node(ast);
	ast_set_value(temp,"shift_expr");
	#else
	ast_node * temp = ast;
	#endif

	if(arith_expr(temp)){
		while(shift(temp)){
			if(arith_expr(temp)){
				continue;
			}
			#if AST_LARGE
			ast_remove(temp);
			#endif
			return 0;
		}
		return 1;
	}
	#if AST_LARGE
	ast_remove(temp);
	#endif
	return 0;
}


static int and_expr(ast_node * ast){
	#if AST_LARGE
	ast_node * temp = ast_add_new_node(ast);
	ast_set_value(temp,"and_expr");
	#else
	ast_node * temp = ast;
	#endif

	if(shift_expr(temp)){
		while(accept(AMPER,temp)){
			if(shift_expr(temp)){
				continue;
			}
			#if AST_LARGE
			ast_remove(temp);
			#endif
			return 0;
		}
		return 1;
	}
	#if AST_LARGE
	ast_remove(temp);
	#endif
	return 0;
}


static int xor_expr(ast_node * ast){
	#if AST_LARGE
	ast_node * temp = ast_add_new_node(ast);
	ast_set_value(temp,"xor_expr");
	#else
	ast_node * temp = ast;
	#endif

	if(and_expr(temp)){
		while(accept(HAT,temp)){
			if(and_expr(temp)){
				continue;
			}
			#if AST_LARGE
			ast_remove(temp);
			#endif
			return 0;
		}
		return 1;
	}
	#if AST_LARGE
	ast_remove(temp);
	#endif
	return 0;
}

static int expr(ast_node * ast){
	#if AST_LARGE
	ast_node * temp = ast_add_new_node(ast);
	ast_set_value(temp,"expr");
	#else
	ast_node * temp = ast;
	#endif

	if(xor_expr(temp)){
		while(accept(VBAR,temp)){
			if(xor_expr(temp)){
				continue;
			}
			#if AST_LARGE
			ast_remove(temp);
			#endif
			return 0;
		}
		return 1;
	}
	#if AST_LARGE
	ast_remove(temp);
	#endif
	return 0;
}

static int comp_op(ast_node * ast){
	ast_node * temp = ast_add_new_node(ast);
	ast_set_value(temp,"comp_op");

	int savepos = getpos();
	if(accept(NOTEQ,temp)){
		return 1;
	}
	ast_remove_children(temp);
	setpos(savepos);
	if(accept(DEQUAL,temp)){
		return 1;
	}
	ast_remove_children(temp);
	setpos(savepos);
	if(accept(GREATER,temp)){
		return 1;
	}
	ast_remove_children(temp);
	setpos(savepos);
	if(accept(LESS,temp)){
		return 1;
	}
	ast_remove_children(temp);
	setpos(savepos);
	if(accept(GREATEREQ,temp)){
		return 1;
	}
	ast_remove_children(temp);
	setpos(savepos);
	if(accept(LESSEQ,temp)){
		return 1;
	}
	ast_remove_children(temp);
	setpos(savepos);
	if(acceptident("is",temp)){
		if(acceptident("not",temp)){
			return 1;
		}
		return 1;
	}
	ast_remove_children(temp);
	setpos(savepos);
	if(acceptident("not",temp)){
		if(acceptident("in",temp)){
			return 1;
		}
		ast_remove(temp);
		return 0;
	}
	ast_remove_children(temp);
	setpos(savepos);
	if(acceptident("in",temp)){
		return 1;
	}
	ast_remove(temp);
	return 0;
}

static int comparison(ast_node * ast){
	#if AST_LARGE
	ast_node * temp = ast_add_new_node(ast);
	ast_set_value(temp,"comparison");
	#else
	ast_node * temp = ast;
	#endif

	if(expr(temp)){
		while(comp_op(temp)){
			if(expr(temp)){
				continue;
			}
			#if AST_LARGE
			ast_remove(temp);
			#endif
			return 0;
		}
		return 1;
	}
	#if AST_LARGE
	ast_remove(temp);
	#endif
	return 0;
}

static int not(ast_node * ast){
	#if AST_LARGE
	ast_node * temp = ast_add_new_node(ast);
	ast_set_value(temp,"not");
	#else
	ast_node * temp = ast;
	#endif

	int savepos = getpos();
	// if(accept(EXCLAIM)){
	// 	return 1;
	// }
	#if AST_LARGE
	ast_remove_children(temp);
	#endif
	setpos(savepos);
	if(acceptident("not",temp)){
		return 1;
	}
	#if AST_LARGE
	ast_remove(temp);
	#endif
	return 0;	
}

static int not_test(ast_node * ast){
	#if AST_LARGE
	ast_node * temp = ast_add_new_node(ast);
	ast_set_value(temp,"not_test");
	#else
	ast_node * temp = ast;
	#endif

	int savepos = getpos();
	if(not(temp)){
		if(not_test(temp)){
			return 1;
		}
		return 0;
	}
	#if AST_LARGE
	ast_remove_children(temp);
	#endif
	setpos(savepos);
	if(comparison(temp)){
		return 1;
	}
	#if AST_LARGE
	ast_remove(temp);
	#endif
	return 0;
}

static int and(ast_node * ast){
	#if AST_LARGE
	ast_node * temp = ast_add_new_node(ast);
	ast_set_value(temp,"and");
	#else
	ast_node * temp = ast;
	#endif

	int savepos = getpos();
	if(accept(DAMPER,temp)){
		return 1;
	}
	#if AST_LARGE
	ast_remove_children(temp);
	#endif
	setpos(savepos);
	if(acceptident("and",temp)){
		return 1;
	}
	#if AST_LARGE
	ast_remove(temp);
	#endif
	return 0;
}

static int and_test(ast_node * ast){
	#if AST_LARGE
	ast_node * temp = ast_add_new_node(ast);
	ast_set_value(temp,"and_test");
	#else
	ast_node * temp = ast;
	#endif
	if(not_test(temp)){
		while(and(temp)){
			if(not_test(temp)){
				continue;
			}
			#if AST_LARGE
			ast_remove(temp);
			#endif
			return 0;
		}
		return 1;
	}
	#if AST_LARGE
	ast_remove(temp);
	#endif
	return 0;
}

static int or(ast_node * ast){
	#if AST_LARGE
	ast_node * temp = ast_add_new_node(ast);
	ast_set_value(temp,"or");
	#else
	ast_node * temp = ast;
	#endif

	int savepos = getpos();
	if(accept(DVBAR,temp)){
		return 1;
	}
	#if AST_LARGE
	ast_remove_children(temp);
	#endif

	setpos(savepos);
	if(acceptident("or",temp)){
		return 1;
	}
	#if AST_LARGE
	ast_remove(temp);
	#endif
	return 0;
}

static int or_test(ast_node * ast){
	#if AST_LARGE
	ast_node * temp = ast_add_new_node(ast);
	ast_set_value(temp,"or_test");
	#else
	ast_node * temp = ast;
	#endif

	if(and_test(temp)){
		while(or(temp)){
			if(and_test(temp)){
				continue;
			}
			#if AST_LARGE
			ast_remove(temp);
			#endif
			return 0;
		}
		return 1;
	}
	#if AST_LARGE
	ast_remove(temp);
	#endif
	return 0;
}

// static int test_nocond(){
// 	ast_node * temp = ast_add_new_node(ast);
// 	ast_set_value(temp,"test_nocond");

// 	if(or_test()){
// 		return 1;
// 	}
// 	ast_remove_children(temp);
// 	return 0;
// }

static int test(ast_node * ast){
	#if AST_LARGE
	ast_node * temp = ast_add_new_node(ast);
	ast_set_value(temp,"test");
	#else
	ast_node * temp = ast;
	#endif

	if(or_test(temp)){
		if(acceptident("if",temp)){
			if(or_test(temp)){
				if(acceptident("else",temp)){
					if(test(temp)){
						return 1;
					}
				}
			}
			#if AST_LARGE
			ast_remove(temp);
			#endif
			return 0;
		}
		return 1;
	}
	#if AST_LARGE
	ast_remove(temp);
	#endif
	return 0;
}

static int starexpr(ast_node * ast){
	ast_node * temp = ast_add_new_node(ast);
	ast_set_value(temp,"starexpr");

	ast_remove(temp);
	return 0;
}

static int testorstar(ast_node * ast){
	#if AST_LARGE
	ast_node * temp = ast_add_new_node(ast);
	ast_set_value(temp,"testorstar");
	#else
	ast_node * temp = ast;
	#endif


	int savepos = getpos();
	if(test(temp)){
		return 1;
	}
	#if AST_LARGE
	ast_remove_children(temp);
	#endif
	setpos(savepos);
	if(starexpr(temp)){
		return 1;
	}
	#if AST_LARGE
	ast_remove(temp);
	#endif
	return 0;
}

static int testorstarlist(ast_node * ast){
	#if AST_LARGE
	ast_node * temp = ast_add_new_node(ast);
	ast_set_value(temp,"testorstarlist");
	#else
	ast_node * temp = ast;
	#endif

	if(testorstar(temp)){
		while(accept(COMMA,temp)){
			if(testorstar(temp)){
				continue;
			}
		}
		return 1;
	}
	#if AST_LARGE
	ast_remove(temp);
	#endif
	return 0;
}

static int testlist(ast_node * ast){
	#if AST_LARGE
	ast_node * temp = ast_add_new_node(ast);
	ast_set_value(temp,"testlist");
	#else
	ast_node * temp = ast;
	#endif

	if(test(temp)){
		while(accept(COMMA,temp)){
			if(test(temp)){
				continue;
			}
		}
		return 1;
	}
	ast_remove(temp);
	return 0;
}

static int annotatedassign(ast_node * ast){
	ast_node * temp = ast_add_new_node(ast);
	ast_set_value(temp,"annotatedassign");

	if(accept(COLON,temp)){
		if(test(temp)){
			if(accept(EQUAL,temp)){
				if(test(temp)){
					return 1;
				}
			}
		}
	}
	ast_remove(temp);
	return 0;
}

static int assign(ast_node * ast){
	ast_node * temp = ast_add_new_node(ast);
	ast_set_value(temp,"assign");

	while(accept(EQUAL,temp)){
		if(testorstarlist(temp)){
			continue;
		}
		ast_remove(temp);
		return 0;
	}
	return 1;
}

static int augmentoperator(ast_node * ast){
	#if AST_LARGE
	ast_node * temp = ast_add_new_node(ast);
	ast_set_value(temp,"augmentoperator");
	#else
	ast_node * temp = ast;
	#endif

	int savepos = getpos();
	if(accept(PLUSEQ,temp)){
		return 1;
	}
	#if AST_LARGE
	ast_remove_children(temp);
	#endif
	setpos(savepos);
	if(accept(MINUSEQ,temp)){
		return 1;
	}
	#if AST_LARGE
	ast_remove_children(temp);
	#endif
	setpos(savepos);
	if(accept(STAREQ,temp)){
		return 1;
	}
	#if AST_LARGE
	ast_remove_children(temp);
	#endif
	setpos(savepos);
	if(accept(DSTAREQ,temp)){
		return 1;
	}
	#if AST_LARGE
	ast_remove_children(temp);
	#endif
	setpos(savepos);
	if(accept(SLASHEQ,temp)){
		return 1;
	}
	#if AST_LARGE
	ast_remove_children(temp);
	#endif
	setpos(savepos);
	if(accept(DSLASHEQ,temp)){
		return 1;
	}
	#if AST_LARGE
	ast_remove_children(temp);
	#endif
	setpos(savepos);
	if(accept(PERCENTEQ,temp)){
		return 1;
	}
	#if AST_LARGE
	ast_remove_children(temp);
	#endif
	setpos(savepos);
	if(accept(HATEQ,temp)){
		return 1;
	}
	#if AST_LARGE
	ast_remove_children(temp);
	#endif
	setpos(savepos);
	if(accept(AMPEREQ,temp)){
		return 1;
	}
	#if AST_LARGE
	ast_remove_children(temp);
	#endif
	setpos(savepos);
	if(accept(DAMPEREQ,temp)){
		return 1;
	}
	#if AST_LARGE
	ast_remove_children(temp);
	#endif
	setpos(savepos);
	if(accept(TILDEEQ,temp)){
		return 1;
	}
	#if AST_LARGE
	ast_remove_children(temp);
	#endif
	setpos(savepos);
	if(accept(VBAREQ,temp)){
		return 1;
	}
	#if AST_LARGE
	ast_remove_children(temp);
	#endif
	setpos(savepos);
	if(accept(DVBAREQ,temp)){
		return 1;
	}
	#if AST_LARGE
	ast_remove_children(temp);
	#endif
	setpos(savepos);
	if(accept(ATEQ,temp)){
		return 1;
	}
	#if AST_LARGE
	ast_remove_children(temp);
	#endif
	setpos(savepos);
	if(accept(RSHIFTEQ,temp)){
		return 1;
	}
	#if AST_LARGE
	ast_remove_children(temp);
	#endif
	setpos(savepos);
	if(accept(LSHIFTEQ,temp)){
		return 1;
	}
	#if AST_LARGE
	ast_remove_children(temp);
	#endif
	setpos(savepos);
	if(accept(DOLLAREQ,temp)){
		return 1;
	}
	#if AST_LARGE
	ast_remove_children(temp);
	#endif
	setpos(savepos);
	if(accept(QUESTIONEQ,temp)){
		return 1;
	}
	setpos(savepos);
	#if AST_LARGE
	ast_remove(temp);
	#endif
	return 0;
}

static int augmentedassign(ast_node * ast){
	ast_node * temp = ast_add_new_node(ast);
	ast_set_value(temp,"augmentedassign");

	if(augmentoperator(temp)){
		if(testlist(temp)){
			return 1;
		}
	}
	ast_remove(temp);
	return 0;
}

static int expression(ast_node * ast){
	#if AST_LARGE
	ast_node * temp = ast_add_new_node(ast);
	ast_set_value(temp,"expression");
	#else
	ast_node * temp = ast;
	#endif

	if(testorstarlist(temp)){
		int savepos = getpos();
		if(annotatedassign(temp)){
			return 1;
		}
		#if AST_LARGE
		ast_remove_children(temp);
		#endif
		setpos(savepos);
		if(augmentedassign(temp)){
			return 1;
		}
		#if AST_LARGE
		ast_remove_children(temp);
		#endif
		setpos(savepos);
		if(assign(temp)){
			return 1;
		}
	}
	#if AST_LARGE
	ast_remove(temp);
	#endif
	return 0;
}

static int small_stmt(ast_node * ast){
	//expression or things like del/pass/continue/break
	// int savepos = getpos();
	ast_node * temp = ast_add_new_node(ast);
	ast_set_value(temp,"small_stmt");

	if(expression(temp)){
		return 1;
	}
	ast_remove(temp);
	return 0;
}

static int simple_stmt(ast_node * ast){
	#if AST_LARGE
	ast_node * temp = ast_add_new_node(ast);
	ast_set_value(temp,"simple_stmt");
	#else
	ast_node * temp = ast;
	#endif

	if(small_stmt(temp)){
		if(accept(SEMICOLON,temp)){
			do{
				int savepos = getpos();
				if(small_stmt(temp)){
					continue;
				}
				setpos(savepos);
			}while(accept(SEMICOLON,temp));
		}
		if(accept(NEWLINE,temp)){
			return 1;
		}
		#if AST_LARGE
		ast_remove(temp);
		#endif
		return 0;
	}
	#if AST_LARGE
	ast_remove(temp);
	#endif
	return 0;
}

static int compound_smt(ast_node * ast){
	ast_node * temp = ast_add_new_node(ast);
	ast_set_value(temp,"stmt");
	ast_remove(temp);
	return 0;
}

static int stmt(ast_node * ast){
	#if AST_LARGE
	ast_node * temp = ast_add_new_node(ast);
	ast_set_value(temp,"stmt");
	#else
	ast_node * temp = ast;
	#endif

	int savepos = getpos();
	if(simple_stmt(temp)){
		return 1;
	}
	#if AST_LARGE
	ast_remove_children(temp);
	#endif
	setpos(savepos);
	if(compound_smt(temp)){
		return 1;
	}
	#if AST_LARGE
	ast_remove(temp);
	#endif
	return 0;
}

static int program(ast_node * ast){
	#if AST_LARGE
	ast_node * temp = ast_add_new_node(ast);
	ast_set_value(temp,"program");
	#else
	ast_node * temp = ast;
	#endif

	while(1){
		if(stmt(temp)){
			continue;
		}else if(accept(NEWLINE,temp)){
			continue;
		}else{
			break;
		}
	}
	return accept(ENDMARKER,temp);
}

void fox_parse(Token * t, char * code){
	nowparsing = t;
	sym = nowparsing[currentpos];
	ast_node * ast = ast_new_node();


	if(program(ast)){
		printf("correct grammar\n");
		ast_print(ast);
	}else{

		//syntax error traceback
		printf("SyntaxError: at %i:%i\n",sym.linenum,sym.start);
		int startofline = currentpos;
		while(1){
			if(startofline<0){
				startofline = 0;
				break;			
			}
			if(nowparsing[startofline].id==NEWLINE){
				startofline++;
				break;
			}
			startofline--;
		}
		int endofline = currentpos;
		while(1){
			if(nowparsing[endofline].id==ENDMARKER){
				endofline--;
				break;			
			}
			if(nowparsing[endofline].id==NEWLINE){
				break;
			}
			endofline++;
		}
		int startoflinec = nowparsing[startofline].start;
		int endoflinec = nowparsing[endofline].end;

		char * buf = calloc(endoflinec-startoflinec+2,1);
		memcpy(buf, &code[startoflinec], endoflinec-startoflinec);
		printf("%s\n",buf);
		free(buf);		

		int x = sym.start-1;
		char *result = calloc(sizeof(" ") * x + 2,1);
		while (x > 0) {
			strcat(result, " ");
			x--;
		}
		strcat(result, "^");
		printf("%s\n",result);
		free(result);
	}
}