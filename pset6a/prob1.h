#ifndef PROB1_H
#define PROB1_H

/* maximum length of input string (including newline character) */
#define INPUT_MAX 2048

/* enable (1) or disable (0) parentheses checking in parsing strings */
/* leave disabled for part (a); enable for part (b) */
#define PARSE_PARENS 0

/* type of token */
enum token_type {
	OPERAND, /* number */
	OPERATOR, /* operator: +, -, *, / */
#if PARSE_PARENS
	LPARENS, /* left parentheses ( */
	RPARENS /* right parentheses ) */
#endif
};

/* operator identifiers (opcodes) */
enum op {
	ADD, /* a+b */
	SUBTRACT, /* a-b (binary) */
	MULTIPLY, /* a*b */
	DIVIDE, /* a/b */
	NEGATE /* -a (unary) */
};

/* direction of evaluation (associativity) */
enum assoc {
	LEFT, /* left-to-right (+, binary -, *, /) */
	RIGHT /* right-to-left (unary -) */
};

/* number of operands for each operator type */
extern const unsigned int op_operands[];

/* order-of-operations (precedence) (0 = evaluated last) */
extern const unsigned int op_precedences[];

/* evaluation direction (associativity) for each precedence level */
extern const enum assoc op_associativity[];

/* contains value of token */
union token_value {
	double operand; /* numeric value for operand */
	enum op op_code; /* opcode for operators */
};

/* data structure for token */
typedef struct s_expr_token {
	union token_value value; /* numeric value or opcode */
	enum token_type type; /* type of token */

	struct s_expr_token * linked_token; /* linked token in stack/queue */
} * p_expr_token; /* p_expr_token is shorthand for "struct s_expr_token *" */

/* data structure for queue */
struct token_queue {
	p_expr_token front; /* front of queue, where tokens are dequeued */
	p_expr_token back; /* back of queue, where tokens are added */
};

/* queue functions - enqueue and dequeue */
void enqueue(struct token_queue * pqueue, const p_expr_token ptoken);
p_expr_token dequeue(struct token_queue * pqueue);

/* stack functions - push and pop */
void push(p_expr_token * ptop, const p_expr_token ptoken);
p_expr_token pop(p_expr_token * ptop);

/* creates a new token in dynamic memory (using malloc()) */
p_expr_token new_token(const enum token_type type, const union token_value value);

/* constructs a queue of tokens in infix order from a space-delimited string */
struct token_queue expr_to_infix(char * str);

/* creates a queue of tokens in postfix order from a queue of tokens in infix order */
/* postcondition: returned queue contains all the tokens, and pqueue_infix should be
   empty */
struct token_queue infix_to_postfix(struct token_queue * pqueue_infix);

/* evalutes the postfix expression stored in the queue */
/* postcondition: returned value is final answer, and pqueue_postfix should be empty */
double evaluate_postfix(struct token_queue * pqueue_postfix);

/* handles evaluation process (calls above functions) for expression string str */
double evaluate(const char * str);

#endif