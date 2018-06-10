
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include <Foxlang.h>

#define addtoken(__i,__s,__e)										\
			result[tokenfilled] = (Token){__i,__s,__e};				\
			tokenfilled++;											\
			if(tokenfilled>=tokensize){								\
				tokensize*=2;										\
				result = realloc(result,tokensize*sizeof(Token));	\
			}

#define addtokenhere(__i)											\
			result[tokenfilled] = (Token){__i,i,i+1};				\
			tokenfilled++;											\
			if(tokenfilled>=tokensize){								\
				tokensize*=2;										\
				result = realloc(result,tokensize*sizeof(Token));	\
			}

int isident(char * name){
	char *x[] = {IDENTIFIERS, 0};
	int i = 0;
	while(x[i]) {
		if(strcmp(x[i], name) == 0) {
			return 1;
		}
		i++;
	}
	return 0;
}

static TokenID onechar(char c1){
	switch(c1){
		case '=':
			return EQUAL;
		case '+':
			return PLUS;
		case '-':
			return MINUS;
		case '*':
			return STAR;
		case '/':
			return SLASH;
		case '%':
			return PERCENT;
		case '^':
			return HAT;
		case '&':
			return AMPER;
		case '~':
			return TILDE;
		case '|':
			return VBAR;
		case '@':
			return AT;
		case '>':
			return GREATER;
		case '<':
			return LESS;
		case '$':
			return DOLLAR;
		case '!':
			return EXCLAIM;
		case '?':
			return QUESTION;
		case '#':
			return HASHTAG;
		case ':':
			return COLON;
		case ';':
			return SEMICOLON;
		case '(':
			return LPAR;
		case ')':
			return RPAR;
		case '[':
			return LSQB;
		case ']':
			return RSQB;
		case '{':
			return LBRACE;
		case '}':
			return RBRACE;
	}
	return -1;
}

static TokenID twochar(char c1, char c2){
	switch(c1){
		case '=':
			
			return DEQUAL;
		case '+':
			return PLUS;
		case '-':
			return MINUS;
		case '*':
			return STAR;
		case '/':
			return SLASH;
		case '%':
			return PERCENT;
		case '^':
			return HAT;
		case '&':
			return AMPER;
		case '~':
			return TILDE;
		case '|':
			return VBAR;
		case '@':
			return AT;
		case '>':
			return GREATER;
		case '<':
			return LESS;
		case '$':
			return DOLLAR;
		case '!':
			return EXCLAIM;
		case '?':
			return QUESTION;
		case '#':
			return HASHTAG;
		case ':':
			return COLON;
		case ';':
			return SEMICOLON;
		case '(':
			return LPAR;
		case ')':
			return RPAR;
		case '[':
			return LSQB;
		case ']':
			return RSQB;
		case '{':
			return LBRACE;
		case '}':
			return RBRACE;
	}
}

static TokenID threechar(char c1, char c2, char c3){
	return -1;
}

Token * tokenize(char * code){
	int length = strlen(code);
	char c1,c2,c3;

	int tokensize=100;
	Token * result = malloc(tokensize*sizeof(Token));
	int tokenfilled=0;

	for (int i = 0; i < length; ++i){
		if(isalpha(code[i]) || code[i]=='_'){
			int start = i;
			do{
				i++;
			}while(isalnum(code[i]) || code[i]=='_');
			int end = i;

			char subbuff[end-start+2];
			memcpy(subbuff, &code[start], end );
			if(isident(subbuff)){
				addtoken(IDENTIFIER,start,end-start);
			}else{
				addtoken(NAME,start,end);
			}
			continue;			
		}
		if(code[i]=='\''||code[i]=='\"'){
			int start = i;
			do{
				i++;
			}while(!(code[i]=='\''||code[i]=='\"'));
			i++;
			int end = i;
			addtoken(STRING,start,end);
			continue;
		}

		c1 = code[i];
		c2 = i+1>=length?'\0':code[i+1];
		c3 = i+2>=length?'\0':code[i+2];

		TokenID res3 = threechar(c1,c2,c3);
		if(res3 != -1){
			addtokenhere(res3);
			continue;
		}
		TokenID res2 = twochar(c1,c2);
		if(res2 != -1){
			addtokenhere(res2);
			continue;
		}
		TokenID res1 = onechar(c1);
		if(res1 != -1){
			addtokenhere(res1);
			continue;
		}
	}

	addtoken(ENDMARKER,0,0);

	printtokenswithcode(result, code);
	return result;
}



void printtokens(Token * t){
	for (int i = 0; t[i].id!=ENDMARKER; ++i){
		printf("%s\t\t%i-%i\n",id_to_token(t[i].id),t[i].start,t[i].end);
	}
}

void printtokenswithcode(Token * t, char * code){
	for (int i = 0; t[i].id!=ENDMARKER; ++i){
		char * subbuff = calloc(t[i].end-t[i].start+2,1);
		memcpy(subbuff, &code[t[i].start], t[i].end-t[i].start);
		printf("%s\t\t%i-%i, \t[%s]\n",id_to_token(t[i].id),t[i].start,t[i].end,subbuff);
		free(subbuff);
	}
}