#include <stdio.h>
#include <time.h>
#include <math.h>

#include "ast.h"

#define MAX_TREE_RES 5

#define COLOR_RES 255

#define CROSSOVER_COUNT 10

#define WIDTH  800
#define HEIGHT 600

static double x, y;

double* get_var_random()
{
	if(random() & 1)
	{
		return &x;
	} else {
		return &y;
	}
}

int main()
{
	srandom(time(0));

	Node* r = node_base_create_random(get_var_random());	
	Node* g = node_base_create_random(get_var_random());	
	Node* b = node_base_create_random(get_var_random());	

	for(int i = 0; i < random() % MAX_TREE_RES + 1; ++i)
	{
		node_expand(&r, get_var_random());
	}

	for(int i = 0; i < random() % MAX_TREE_RES + 1; ++i)
	{
		node_expand(&g, get_var_random());
	}

	for(int i = 0; i < random() % MAX_TREE_RES + 1; ++i)
	{
		node_expand(&b, get_var_random());
	}

	for(int i = 0; i < CROSSOVER_COUNT; ++i)
	{
		node_crossover(&r, &g);
		node_crossover(&r, &b);
		node_crossover(&g, &b);
	}

	printf("P3 %d %d\n%d\n", WIDTH, HEIGHT, COLOR_RES);

	for(y = -HEIGHT/2; y < HEIGHT/2; y += 1.0)
	{
		for(x = -WIDTH/2; x < WIDTH/2; x += 1.0)
		{
			printf("%d %d %d\n", (int)fabs(COLOR_RES * sin(node_parse(r))), (int)fabs(COLOR_RES * sin(node_parse(g))), (int)fabs(COLOR_RES * sin(node_parse(b))));
		}
	}

	node_free(r);
	node_free(g);
	node_free(b);

	return 0;
}
