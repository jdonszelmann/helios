
#ifndef TOKENIZER_H
#define TOKENIZER_H

#define addcase(x) case x:return #x

#define IDENTIFIERS "if" "else" "elif" "for" "while" "do" "try" "except" "finally" "import"


typedef enum {
	NAME,
	STRING,
	NUMBER,
	INDENT,
	DEDENT,
	NEWLINE,
	ENDMARKER,
	IDENTIFIER,

	PLUS,
	MINUS,
	STAR,
	DSTAR,
	SLASH,
	DSLASH,
	PERCENT,
	HAT,
	AMPER,
	TILDE,
	VBAR,
	AT,
	RSHIFT,
	LSHIFT,

	PLUSEQ,
	MINUSEQ,
	STAREQ,
	DSTAREQ,
	DIVEQ,
	DDIVEQ,
	PERCENTEQ,
	HATEQ,
	AMPEREQ,
	TILDEEQ,
	VBAREQ,
	ATEQ,
	RSHIFTEQ,
	LSHIFTEQ,

	RARROW,
	LARROW,

	DOLLAR,
	EXCLAIM,
	QUESTION,
	HASHTAG,
	COLON,
	SEMICOLON,

	LPAR,
	RPAR,
	LSQB,
	RSQB,
	LBRACE,
	RBRACE,

	EQUAL,
	DEQUAL,
	GREATER,
	LESS,
	GREATEREQ,
	LESSEQ,
	NOTEQ,


} TokenID;

inline char * id_to_token(TokenID id){
	switch(id){

		addcase(NAME);
		addcase(STRING);
		addcase(NUMBER);
		addcase(INDENT);
		addcase(DEDENT);
		addcase(NEWLINE);
		addcase(ENDMARKER);
		addcase(IDENTIFIER);

		addcase(PLUS);
		addcase(MINUS);
		addcase(STAR);
		addcase(DSTAR);
		addcase(SLASH);
		addcase(DSLASH);
		addcase(PERCENT);
		addcase(HAT);
		addcase(AMPER);
		addcase(TILDE);
		addcase(VBAR);
		addcase(AT);
		addcase(RSHIFT);
		addcase(LSHIFT);

		addcase(PLUSEQ);
		addcase(MINUSEQ);
		addcase(STAREQ);
		addcase(DSTAREQ);
		addcase(DIVEQ);
		addcase(DDIVEQ);
		addcase(PERCENTEQ);
		addcase(HATEQ);
		addcase(AMPEREQ);
		addcase(TILDEEQ);
		addcase(VBAREQ);
		addcase(ATEQ);
		addcase(RSHIFTEQ);
		addcase(LSHIFTEQ);

		addcase(RARROW);
		addcase(LARROW);

		addcase(DOLLAR);
		addcase(EXCLAIM);
		addcase(QUESTION);
		addcase(HASHTAG);
		addcase(COLON);
		addcase(SEMICOLON);

		addcase(LPAR);
		addcase(RPAR);
		addcase(LSQB);
		addcase(RSQB);
		addcase(LBRACE);
		addcase(RBRACE);

		addcase(EQUAL);
		addcase(DEQUAL);
		addcase(GREATER);
		addcase(LESS);
		addcase(GREATEREQ);
		addcase(LESSEQ);
		addcase(NOTEQ);

		default:return "ENDMARKER";
	}
}

typedef struct{
	TokenID id;
	int start;
	int end;
}Token;

Token * tokenize(char * code);
void printtokens(Token * t);
void printtokenswithcode(Token * t, char * code);

#endif