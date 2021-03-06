#ifndef PROB1_H
#define PROB1_H

#define INPUT_MAX_LENGTH 2048

/* enable (1) or disable (0) parentheses checking in parsing strings */
/* leave disabled for part (a); enable for part (b) */
#define PARSE_PARENTHESES 1

extern char operators[];

enum token_type {
	OPERAND,
	OPERATOR,
#if PARSE_PARENTHESES
	LEFT_PARENTHESES,
	RIGHT_PARENTHESES
#endif
};

/* operator identifiers (opcodes) */
enum op {
	ADD, /* a+b */
	SUBTRACT, /* a-b (binary) */
	MULTIPLY, /* a*b */
	DIVIDE, /* a/b */
	KEEP, /* +a (unary) */
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
typedef union token_value {
	double operand; /* numeric value for operand */
	enum op op_code; /* opcode for operators */
} token_value;

/* data structure for token */
typedef struct s_expr_token {
	token_value value; /* numeric value or opcode */
	enum token_type type; /* type of token */

	struct s_expr_token * linked_token; /* linked token in stack/queue */
} * p_expr_token; /* p_expr_token is shorthand for "struct s_expr_token *" */

/* data structure for queue */
typedef struct token_queue {
	p_expr_token front; /* front of queue, where tokens are dequeued */
	p_expr_token back; /* back of queue, where tokens are added */
} token_queue;

/* queue functions - enqueue and dequeue */
void enqueue(token_queue * pqueue, const p_expr_token ptoken);
p_expr_token dequeue(token_queue * pqueue);

/* stack functions - push and pop */
void push(p_expr_token * ptop, const p_expr_token ptoken);
p_expr_token pop(p_expr_token * ptop);

p_expr_token create_new_token(const enum token_type type, const union token_value value);

#endif
