typedef enum{FALSE, TRUE} boolean;

const char* keyword_token[] = {"if", "else", "for", "while", "int", "float", "string"};

const char symbole_token[] = {'*', ',', ';', '{', '}', '(', ')'};

typedef enum{
    IF_TOKEN, ELSE_TOKEN, FOR_TOKEN, WHILE_TOKEN, INT_TOKEN, FLOAT_TOKEN, STRING_TOKEN,

    PLUS_TOKEN, MINUS_TOKEN, DIV_TOKEN, STAR_TOKEN, COMMA_TOKEN, SEMICOLON_TOKEN,
    OPEN_BRACE_TOKEN, CLOSE_BRACE_TOKEN, OPEN_PARENS_TOKEN, CLOSE_PARENS_TOKEN,
    ASSIGNMENT_TOKEN, GT_TOKEN, LT_TOKEN, OP_EQ_TOKEN, OP_GE_TOKEN, OP_LE_TOKEN,

	IDF_TOKEN,
	VARCHAR_TOKEN,
	NUMBER_TOKEN,
	EOF_TOKEN,
	ERROR_TOKEN
} nameToken;

const char* tokens[] = {"IF_TOKEN", "ELSE_TOKEN", "FOR_TOKEN", "WHILE_TOKEN", "INT_TOKEN", "FLOAT_TOKEN", "STRING_TOKEN",
                        "PLUS_TOKEN", "MINUS_TOKEN", "DIV_TOKEN", "STAR_TOKEN", "COMMA_TOKEN", "SEMICOLON_TOKEN", "OPEN_BRACE_TOKEN",
                        "CLOSE_BRACE_TOKEN", "OPEN_PARENS_TOKEN", "CLOSE_PARENS_TOKEN", "ASSIGNMENT_TOKEN", "GT_TOKEN", "LT_TOKEN",
                        "OP_EQ_TOKEN", "OP_GE_TOKEN", "OP_LE_TOKEN",
                        "IDF_TOKEN",
                        "VARCHAR_TOKEN",
                        "NUMBER_TOKEN",
                        "EOF_TOKEN",
                        "ERROR_TOKEN"};

typedef struct{
    char* name;
}idfToken;

typedef struct{
    char c; 
    char* value;
}varcharToken;

typedef struct{
    boolean isInt; 
    union{
       int n;
       float x;
    }value;
}numberToken;

typedef struct{
	nameToken name; 
	union{
       idfToken idf; 
       numberToken number; 
       varcharToken varchar;
    }properties;
} token;
