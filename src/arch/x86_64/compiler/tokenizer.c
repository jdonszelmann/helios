
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include <Foxlang.h>

#define spacespertab 4

#define addtoken(__i,__s,__e)										\
			result[tokenfilled] = (Token){__i,__s,__e,__line__};	\
			tokenfilled++;											\
			if(tokenfilled>=tokensize){								\
				tokensize*=2;										\
				result = realloc(result,tokensize*sizeof(Token));	\
			}

#define addtokenhere(__i)											\
			result[tokenfilled] = (Token){__i,i,i+1,__line__};		\
			tokenfilled++;											\
			if(tokenfilled>=tokensize){								\
				tokensize*=2;										\
				result = realloc(result,tokensize*sizeof(Token));	\
			}

#define addtokenherel(__i,__l)										\
			result[tokenfilled] = (Token){__i,i,i+__l,__line__};	\
			tokenfilled++;											\
			if(tokenfilled>=tokensize){								\
				tokensize*=2;										\
				result = realloc(result,tokensize*sizeof(Token));	\
			}

#define addtokenwithname(__i,__s,__e, name)							\
			result[tokenfilled] =(Token){__i,__s,__e,__line__,name};\
			tokenfilled++;											\
			if(tokenfilled>=tokensize){								\
				tokensize*=2;										\
				result = realloc(result,tokensize*sizeof(Token));	\
			}


static TokenID onechar(char c1){
	switch(c1){
		case ',':
			return COMMA;
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
			switch(c2){
				case '=':
					return DEQUAL;
			}
			break;
		case '+':
			switch(c2){
				case '=':
					return PLUSEQ;
				case '+':
					return INC;
			}
			break;
		case '-':
			switch(c2){
				case '=':
					return MINUSEQ;
				case '-':
					return DEC;
			}
			break;
		case '*':
			switch(c2){
				case '=':
					return STAREQ;
				case '*':
					return DSTAR;
			}
			break;
		case '/':
			switch(c2){
				case '=':
					return SLASHEQ;
				case '/':
					return DSLASH;
			}
			break;
		case '%':
			switch(c2){
				case '=':
					return PERCENTEQ;
			}
			break;
		case '^':
			switch(c2){
				case '=':
					return HATEQ;
			}
			break;
		case '&':
			switch(c2){
				case '=':
					return AMPEREQ;
				case '&':
					return DAMPER;
			}
			break;
		case '~':
			switch(c2){
				case '=':
					return TILDEEQ;
			}
			break;
		case '|':
			switch(c2){
				case '=':
					return VBAREQ;
				case '|':
					return DVBAR;
			}
			break;
		case '@':
			switch(c2){
				case '=':
					return ATEQ;
			}
			break;
		case '>':
			switch(c2){
				case '=':
					return GREATEREQ;
				case '>':
					return RSHIFT;
			}
			break;
		case '<':
			switch(c2){
				case '=':
					return  LESSEQ;
				case '<':
					return LSHIFT;
				case '>':
					return NOTEQ;
			}
			break;
		case '$':
			switch(c2){
				case '=':
					return  DOLLAREQ;
			}
			break;
		case '!':
			switch(c2){
				case '=':
					return  NOTEQ;
			}
			break;
		case '?':
			switch(c2){
				case '=':
					return  QUESTIONEQ;
			}
			break;
	}
	return -1;
}

static TokenID threechar(char c1, char c2, char c3){
	switch(c1){
		case '*':
			switch(c2){
				case '*':
					switch(c3){
						case '=':
							return DSTAREQ;
					}
				break;
			}
			break;
		case '/':
			switch(c2){
				case '/':
					switch(c3){
						case '=':
							return DSLASHEQ;
					}
				break;
			}
			break;
		case '&':
			switch(c2){
				case '&':
					switch(c3){
						case '=':
							return DAMPEREQ;
					}
					break;
			}
			break;
		case '|':
			switch(c2){
				case '|':
					switch(c3){
						case '=':
							return DVBAREQ;
					}
				break;
			}
			break;
		case '>':
			switch(c2){
				case '>':
					switch(c3){
						case '=':
							return RSHIFTEQ;
					}
				break;
			}
			break;
		case '<':
			switch(c2){
				case '<':
					switch(c3){
						case '=':
							return LSHIFTEQ;
					}
			}
			break;
	}
	return -1;
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

int lineempty(char * line){
	int i = 0;
	while(line[i] != '\0' || line[i] == '\n'){
		if(!isspace(line[i])){
			return 0;
		}
		i++;
	}
	return 1;
}

Token * fox_tokenize(char * code){
	int length = strlen(code);
	char c1,c2,c3;
	int indent = 0;

	int tokensize=100;
	Token * result = malloc(tokensize*sizeof(Token));
	int tokenfilled=0;

	int __line__ = 1;

	for (int i = 0; i < length; ++i){
		if(isalpha(code[i]) || code[i]=='_'){
			int start = i;
			do{
				i++;
			}while(isalnum(code[i]) || code[i]=='_');
			int end = i;

			char * subbuff = calloc(end-start+2,1);
			memcpy(subbuff, &code[start], end-start );
			if(isident(subbuff)){
				addtokenwithname(IDENT,start,end,subbuff);
			}else{
				addtoken(NAME,start,end);
				free(subbuff);
			}
			i--;
			continue;			
		}
		if(code[i]=='#'){
			// int start = i;
			do{
				i++;
			}while(!(code[i] == '\n' || code[i] == '#') && i < length);
			i++;
			// int end = i;
			// addtoken(COMMENT,start,end);
			i--;
			continue;
		}

		if((code[i]=='\''&&code[i+1]=='\''&&code[i+2]=='\'')||(code[i]=='\"'&&code[i+1]=='\"'&&code[i+2]=='\"')){
			int start = i;
			do{
				i++;
			}while(!((code[i]=='\''&&code[i+1]=='\''&&code[i+2]=='\'')||(code[i]=='\"'&&code[i+1]=='\"'&&code[i+2]=='\"')) && i < length);
			i+=3;
			int end = i;
			addtoken(STRING,start,end);
			i--;
			continue;
		}
		if((code[i] == 'b'||code[i] == 'r'||code[i] == 'f')&&(code[i+1]=='\''||code[i+1]=='\"')){
			int start = i;
			do{
				i++;
			}while(!(code[i]=='\''||code[i]=='\"') && i < length);
			i++;
			int end = i;
			addtoken(STRING,start,end);
			i--;
			continue;
		}
		if(code[i]=='\''||code[i]=='\"'){
			int start = i;
			do{
				i++;
			}while(!(code[i]=='\''||code[i]=='\"') && i < length);
			i++;
			int end = i;
			addtoken(STRING,start,end);
			i--;
			continue;
		}
		if(code[i] == '0' && (code[i+1] == 'x'||code[i+1] == 'o'||code[i+1] == 'b'||code[i+1] == 'X'||code[i+1] == 'O'||code[i+1] == 'B')){
			int start = i;
			i+=2;
			do{
				i++;
			}while((isdigit(code[i]) || (code[i] == '.' && isdigit(code[i+1]))) && i < length);
			int end = i;
			addtoken(NUMBASE,start,end);
			i--;
			continue;
		}
		if(isdigit(code[i]) || (code[i] == '.' && isdigit(code[i+1]))){
			int start = i;
			do{
				i++;
			}while((isdigit(code[i]) || (code[i] == '.' && isdigit(code[i+1]))) && i < length);
			int end = i;
			addtoken(NUMBER,start,end);
			i--;
			continue;
		}
		if(code[i] == '\n'){
			addtokenherel(NEWLINE,0);
			__line__++;
			int tempindent = 0;
			int j = i+1;
			do{
				if(code[j]==' '){
					tempindent++;
				}else if(code[j] == '\t'){
					tempindent+=4;
				}else{
					break;
				}
				j++;
			}while(1);
			if(tempindent%4!=0){
				RAISE(ExceptionObject_FromCHARPNT_FMT("IndentError: Invalid use of tabs and indentation at line %i",__line__));
			}
			int currentindent = tempindent/4;
			if(currentindent > indent){
				for (int i = 0; i < currentindent-indent; ++i){
					addtokenherel(INDENT,0);
				}
			}else if(currentindent < indent){
				for (int i = 0; i < indent-currentindent; ++i){
					addtokenherel(DEDENT,0);
				}
			}
			indent = currentindent;
		}

		c1 = code[i];
		c2 = i+1>=length?'\0':code[i+1];
		c3 = i+2>=length?'\0':code[i+2];

		TokenID res3 = threechar(c1,c2,c3);
		if(res3 != -1){
			addtokenherel(res3,3);
			i+=2;
			continue;
		}
		TokenID res2 = twochar(c1,c2);
		if(res2 != -1){
			addtokenherel(res2,2);
			i++;
			continue;
		}
		TokenID res1 = onechar(c1);
		if(res1 != -1){
			addtokenherel(res1,1);
			continue;
		}
	}
	for (int i = 0; i < indent; ++i){
		addtokenherel(DEDENT,0);
	}

	addtoken(ENDMARKER,0,0);
	#if DEBUGTOKENIZER
	printtokenswithcode(result, code);
	#endif
	return result;
}


void freetokenarr(Token * t){
	for (int i = 0; t[i].id!=ENDMARKER; ++i){
		free(t[i].content);
	}
	free(t);
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
		if(t[i].content != NULL){
			printf("%s\t\t%i-%i,\t%i\t \t[%s]\t\t%s\n",id_to_token(t[i].id),t[i].start,t[i].end,t[i].linenum,subbuff,t[i].content);

		}else{
			printf("%s\t\t%i-%i,\t%i\t \t[%s]\n",id_to_token(t[i].id),t[i].start,t[i].end,t[i].linenum,subbuff);
		}
		free(subbuff);
	}
}