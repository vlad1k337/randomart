#include <stdio.h>
#include <time.h>
#include <math.h>

#include "ast.h"

#define MAX_TREE_SIZE 5

#define COLOR_RES 255

#define CROSSOVER_COUNT 15

#define WIDTH  1920
#define HEIGHT 1368

static double x, y;

static Node* r;
static Node* g;
static Node* b;

double* get_var_random()
{
	if(random() & 1)
	{
		return &x;
	} else {
		return &y;
	}
}

Node** get_tree(int number)
{
    switch(number)
    {
        case 0:
            return &r;

        case 1: 
            return &g;

        case 2:
            return &b;

        default:
        {
            puts("get_tree_random() : number should be in ragne [0, 3]!\n");
            exit(-1);
        }
    }
}

void crossover_random()
{
    int tree_num1 = random() % 3;
    int tree_num2 = random() % 3;

    while(tree_num1 == tree_num2)
    {
        tree_num2 = random() % 3;
    }

    node_crossover(get_tree(tree_num1), get_tree(tree_num2));
}

int main()
{
	srandom(time(0));

	r = node_base_create_random(get_var_random());	
	g = node_base_create_random(get_var_random());	
    b = node_base_create_random(get_var_random());	

	for(int i = 0; i < random() % MAX_TREE_SIZE + 3; ++i)
	{
		node_expand(&r, get_var_random());
	}

	for(int i = 0; i < random() % MAX_TREE_SIZE + 3; ++i)
	{
		node_expand(&g, get_var_random());
	}

	for(int i = 0; i < random() % MAX_TREE_SIZE + 3; ++i)
	{
		node_expand(&b, get_var_random());
	}

	for(int i = 0; i < CROSSOVER_COUNT; ++i)
	{
        crossover_random();
	}

	printf("P3 %d %d\n%d\n", WIDTH, HEIGHT, COLOR_RES);

	for(y = -HEIGHT / 4; y < HEIGHT / 4; y += 2.0 / 4)
	{
		for(x = -WIDTH / 4; x < WIDTH / 4; x += 2.0 / 4)
		{
            /* Take sine to ensure values are in [-1, 1] range. Feel free to use any other function */

			printf("%d %d %d\n", 
                    (int)fabs(COLOR_RES * sin(node_parse(r))),
                    (int)fabs(COLOR_RES * sin(node_parse(g))), 
                    (int)fabs(COLOR_RES * sin(node_parse(b))));
		}
	}

	node_free(r);
	node_free(g);
	node_free(b);

	return 0;
}
