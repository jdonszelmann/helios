
#ifndef TOKENIZER_H
#define TOKENIZER_H

#define addcase(x) case x:return #x

#define IDENTIFIERS "if", "else", "elif", "for", "while", "do", "try", "except", "finally", "import", "in", "del", "continue", "True", "False", "None", "or", "and", "is", "not"


typedef enum {
	NAME,
	STRING,
	NUMBER,
	NUMBASE,
	INDENT,
	DEDENT,
	NEWLINE,
	ENDMARKER,
	IDENT,
	COMMA,

	PLUS,
	MINUS,
	STAR,
	DSTAR,
	SLASH,
	DSLASH,
	PERCENT,
	HAT,
	AMPER,
	DAMPER,
	TILDE,
	VBAR,
	DVBAR,
	AT,
	RSHIFT,
	LSHIFT,
	INC,
	DEC,

	PLUSEQ,
	MINUSEQ,
	STAREQ,
	DSTAREQ,
	SLASHEQ,
	DSLASHEQ,
	PERCENTEQ,
	HATEQ,
	AMPEREQ,
	DAMPEREQ,
	TILDEEQ,
	VBAREQ,
	DVBAREQ,
	ATEQ,
	RSHIFTEQ,
	LSHIFTEQ,
	DOLLAREQ,
	QUESTIONEQ,

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

	COMMENT,
	//used to have ast tree nodes without a token in it
	NOTOKEN,

} TokenID;

inline char * id_to_token(TokenID id){
	switch(id){

		addcase(NAME);
		addcase(STRING);
		addcase(NUMBER);
		addcase(NUMBASE);
		addcase(INDENT);
		addcase(DEDENT);
		addcase(NEWLINE);
		addcase(ENDMARKER);
		addcase(IDENT);
		addcase(COMMA);

		addcase(PLUS);
		addcase(MINUS);
		addcase(STAR);
		addcase(DSTAR);
		addcase(SLASH);
		addcase(DSLASH);
		addcase(PERCENT);
		addcase(HAT);
		addcase(AMPER);
		addcase(DAMPER);
		addcase(TILDE);
		addcase(VBAR);
		addcase(DVBAR);
		addcase(AT);
		addcase(RSHIFT);
		addcase(LSHIFT);
		addcase(INC);
		addcase(DEC);


		addcase(PLUSEQ);
		addcase(MINUSEQ);
		addcase(STAREQ);
		addcase(DSTAREQ);
		addcase(SLASHEQ);
		addcase(DSLASHEQ);
		addcase(PERCENTEQ);
		addcase(HATEQ);
		addcase(AMPEREQ);
		addcase(DAMPEREQ);
		addcase(TILDEEQ);
		addcase(VBAREQ);
		addcase(DVBAREQ);
		addcase(ATEQ);
		addcase(RSHIFTEQ);
		addcase(LSHIFTEQ);

		addcase(RARROW);
		addcase(LARROW);

		addcase(DOLLAR);
		addcase(DOLLAREQ);
		addcase(EXCLAIM);
		addcase(QUESTION);
		addcase(QUESTIONEQ);
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

		addcase(COMMENT);
		addcase(NOTOKEN);

		default:return "ENDMARKER";
	}
}

typedef struct{
	TokenID id;
	int start;
	int end;
	int linenum;
	char * content;
}Token;

Token * fox_tokenize(char * code);
void printtokens(Token * t);
void printtokenswithcode(Token * t, char * code);
void freetokenarr(Token * t);

#endif