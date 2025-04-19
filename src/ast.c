#include "ast.h"

#include <stdio.h>
#include <assert.h>
#include <math.h>

Node* node_const_create(double value)
{
	Node* new_node = malloc(sizeof *new_node);	
	assert(new_node != NULL);

	new_node->operation = VALUE;
	new_node->type = CONST;

	new_node->value = value;

	return new_node;
}

Node* node_var_create(double* variable)
{
	Node* new_node = malloc(sizeof *new_node);
	assert(new_node != NULL);

	new_node->operation = VALUE;
	new_node->type = VAR;

	new_node->variable = variable;

	return new_node;
}

Node* node_unop_create(node_type type)
{
	Node* new_node = malloc(sizeof *new_node);	
	assert(new_node != NULL);

	new_node->operation = UNARY_OP;
	new_node->type = type;

	new_node->child = NULL;

	return new_node;
}

Node* node_binop_create(node_type type)
{
	Node* new_node = malloc(sizeof *new_node);
	assert(new_node != NULL);

	new_node->operation = BIN_OP;
	new_node->type = type;

	new_node->left = NULL;
	new_node->right = NULL;

	return new_node;
}

Node* node_base_create_random(double* variable)
{
	Node* new_base_node = NULL;
	int rand_op_type = random() & 1;
	if(rand_op_type == 0)
	{
		new_base_node = node_binop_create(get_binop_random());

		new_base_node->left = node_var_create(variable);
		new_base_node->right = node_const_create(random()/RAND_MAX);

		return new_base_node;
	}

	if(rand_op_type == 1)
	{
		new_base_node = node_unop_create(get_unop_random());

		new_base_node->child = node_var_create(variable);

		return new_base_node;
	}

	NODE_UNREACHABLE("Undefined operation type");
}

void node_get_random(Node** root, Node*** result, uint32_t* count)
{
	if(*root == NULL)
	{
		return;
	}


	(*count)++;

	if(random() % (*count) == 0)
	{
		*result = root;
	}


	switch((*root)->operation)
	{
		case VALUE:
			return;
		
		case UNARY_OP:
			node_get_random(&(*root)->child, result, count);
			return;

		case BIN_OP:
			node_get_random(&(*root)->left, result, count);
			node_get_random(&(*root)->right, result, count);
			return;

		default:
			NODE_UNREACHABLE("Undefined operation type");
	}
}

void node_free(Node* root)
{
	if(root == NULL)
	{
		return;
	}

	switch(root->operation)
	{
		case VALUE:
			break;	

		case UNARY_OP:
			node_free(root->child);
			break;

		case BIN_OP:
			node_free(root->left);
			node_free(root->right);
			break;

		default:
			NODE_UNREACHABLE("Undefined operation type");
	}

	free(root);
	root = NULL;
}

void node_crossover(Node** a, Node** b)
{
	assert(a != NULL);
	assert(b != NULL);

	Node** random_a = NULL; 
	Node** random_b = NULL;	

	uint32_t node_count = 0;
	node_get_random(a, &random_a, &node_count);

	node_count = 0;
	node_get_random(b, &random_b, &node_count);

	Node* temp = *random_a;
	*random_a = *random_b;
	*random_b = temp;
}

void node_expand(Node** root, double* variable)
{
	switch((*root)->operation)
	{
		case VALUE:
		{
			node_free(*root);
			*root = node_base_create_random(variable);
			return;
		}

		case UNARY_OP:
			node_expand(&(*root)->child, variable);
			return;

		case BIN_OP:
			node_expand(&(*root)->left, variable);
			node_expand(&(*root)->right, variable);
			return;
	}
}

double node_parse(Node* root)
{
	switch(root->type)
	{
		case CONST:
		{
			return root->value;
		}

		case VAR:
		{
			return *root->variable;
		}
		
		case ADD:
		{
			return node_parse(root->left) + node_parse(root->right);
		}

		case SUB: 
		{
			return node_parse(root->left) - node_parse(root->right);
		}

		case MUL:
		{
			return node_parse(root->left) * node_parse(root->right);
		}

		case DIV:
		{
			return node_parse(root->left) / (node_parse(root->right) + 0.001);
		}

		case MOD:
		{
			return fmod(node_parse(root->left), node_parse(root->right) + 0.001);
		}

		case SIN:
		{
			return sin(node_parse(root->child));
		}

		case COS:
		{
			return cos(node_parse(root->child));
		}

		case TAN:
		{
			return tan(node_parse(root->child));
		}
		
		case SQRT:
		{
			return sqrt(fabs(node_parse(root->child)));
		}

		case LOGN:
		{
			return log(fabs(node_parse(root->child)) + 0.001);
		}

		default:
		{
			NODE_UNREACHABLE("Undefined node type");
		}
	}
}

void node_print(Node* root)
{
	switch(root->type)
	{
		case CONST:
		{
			printf("%f", root->value);
			return;
		}

		case VAR:
		{
			printf("VAR");
			return;
		}
		
		case ADD:
		{
			fputs("(", stdout);
			node_print(root->left);
			fputs(" + ", stdout);
			node_print(root->right);
			fputs(")", stdout);
			return;
		}

		case SUB: 
		{
			fputs("(", stdout);
			node_print(root->left);
			fputs(" - ", stdout);
			node_print(root->right);
			fputs(")", stdout);
			return;
		}

		case MUL:
		{
			fputs("(", stdout);
			node_print(root->left);
			fputs(" * ", stdout);
			node_print(root->right);
			fputs(")", stdout);
			return;
		}

		case DIV:
		{
			fputs("(", stdout);
			node_print(root->left);
			fputs(" / ", stdout);
			node_print(root->right);
			fputs(")", stdout);
			return;
		}

		case MOD:
		{
			fputs("(", stdout);
			node_print(root->left);
			fputs(" mod ", stdout);
			node_print(root->right);
			fputs(")", stdout);
			return;
		}

		case SIN:
		{
			fputs("sin(", stdout);
			node_print(root->child);
			fputs(")", stdout);
			return;
		}

		case COS:
		{
			fputs("cos(", stdout);
			node_print(root->child);
			fputs(")", stdout);
			return;
		}

		case TAN:
		{
			fputs("tan(", stdout);
			node_print(root->child);
			fputs(")", stdout);
			return;
		}

		case SQRT:
		{
			fputs("sqrt(", stdout);
			node_print(root->child);
			fputs(")", stdout);
			return;
		}

		case LOGN:
		{
			fputs("ln(", stdout);
			node_print(root->child);
			fputs(")", stdout);
			return;
		}

		default:
		{
			NODE_UNREACHABLE("Undefined node type");
		}
	}
}

op_type get_op_from_type(node_type type)
{
	switch(type)
	{
		case CONST:
		case VAR:
			return VALUE;
		
		case ADD:
		case SUB:
		case MUL:
		case DIV:
		case MOD:
			return BIN_OP;

		case SIN:
		case COS:
		case TAN:
		case SQRT:
			return UNARY_OP;

		default:
			NODE_UNREACHABLE("Undefined node type");
	}
}

node_type get_unop_random()
{
	int rand_value = random() % 5;

	switch(rand_value)
	{
		case 0:
			return SIN;
		
		case 1:
			return COS;

		case 2: 
			return TAN;

		case 3:
			return SQRT;

		case 4:
			return LOGN;

		default:
			NODE_UNREACHABLE("Undefined unary operation");
	}
}

node_type get_binop_random()
{
	int rand_value = random() % 5;
	switch(rand_value)
	{
		case 0:
			return ADD;

		case 1:
			return SUB;
		
		case 2:
			return MUL;

		case 3: 
			return DIV;

		case 4:
			return MOD;

		default:
			NODE_UNREACHABLE("Undefined binary operation");
	}
}
