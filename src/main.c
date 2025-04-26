#include <stdio.h>
#include <time.h>
#include <math.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stbi_image_write.h"

#include "ast.h"

#define IMAGE_NAME "image.hdr"

#define MAX_TREE_DEPTH 10


/* From experience, increasing the crossover count usually leads to more interesting, but noisier images.  */ 

#define CROSSOVER_COUNT 100

#define WIDTH  1920
#define HEIGHT 1080


static double x, y;

static Node* r;
static Node* g;
static Node* b;

static float image[3 * WIDTH * HEIGHT];

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

void build_trees()
{
    r = node_base_create_random(&x, "x");	
	g = node_base_create_random(&y, "y");	
	b = node_base_create_random(&x, "x");	

	for(int i = 0; i < random() % MAX_TREE_DEPTH + 1; ++i)
	{
		node_expand(&r, &x, "x");
		node_expand(&r, &y, "y");
	}

	for(int i = 0; i < random() % MAX_TREE_DEPTH + 1; ++i)
	{
		node_expand(&g, &y, "y");
	}

	for(int i = 0; i < random() % MAX_TREE_DEPTH + 1; ++i)
	{
		node_expand(&b, &x, "x");
	}

	for(int i = 0; i < CROSSOVER_COUNT; ++i)
	{
        crossover_random();
	}
}

void clean_trees()
{
    node_free(r);
	node_free(g);
	node_free(b);
}

int main()
{
	srandom(time(0));

    build_trees();	

    uint32_t index = 0;
	for(y = -HEIGHT / 2; y < HEIGHT / 2; y += 1.0)
	{
		for(x = -WIDTH / 2; x < WIDTH / 2; x += 1.0)
		{
            /* You may additionaly choose to normalize color values by applying sine/cosine */

            image[index++] = fabs(node_parse(r));
            image[index++] = fabs(node_parse(g)); 
            image[index++] = fabs(node_parse(b));
		}
	}


    clean_trees();	

    stbi_write_hdr(IMAGE_NAME, WIDTH, HEIGHT, 3, image); 

	return 0;
}
