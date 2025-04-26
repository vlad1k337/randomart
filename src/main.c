#include <stdio.h>
#include <time.h>
#include <math.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stbi_image_write.h"

#include "ast.h"

#define IMAGE_NAME "image.jpg"

#define MAX_TREE_SIZE 5

#define COLOR_RES 255

#define CROSSOVER_COUNT 10

#define WIDTH  1920
#define HEIGHT 1368

static double x, y, t;

static Node* r;
static Node* g;
static Node* b;

static uint32_t image[3 * WIDTH * HEIGHT];

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
    r = node_base_create_random(&x, "uv.x");	
	g = node_base_create_random(&t, "iTime");	
	b = node_base_create_random(&y, "uv.y");	

	for(int i = 0; i < random() % MAX_TREE_SIZE + 2; ++i)
	{
		node_expand(&r, &t, "iTime");
		node_expand(&r, &y, "uv.y");
	}

	for(int i = 0; i < random() % MAX_TREE_SIZE + 2; ++i)
	{
		node_expand(&g, &y, "uv.y");
		node_expand(&g, &x, "uv.x");
	}

	for(int i = 0; i < random() % MAX_TREE_SIZE + 2; ++i)
	{
		node_expand(&b, &x, "uv.x");
		node_expand(&b, &t, "iTime");
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

    puts("void mainImage( out vec4 fragColor, in vec2 fragCoord )");
    puts("{");
    puts("vec2 uv = fragCoord;");
    puts("vec3 col;");

    printf("col.r = abs(");
    node_print(r);
    puts(");\n");

    printf("col.g = abs(");
    node_print(g);
    puts(");\n");

    printf("col.b = abs(");
    node_print(b);
    puts(");\n");

    puts("fragColor = vec4(col, 1.0);");
    puts("}");

    uint32_t index = 0;
	for(y = -HEIGHT / 2; y < HEIGHT / 2; y += 1.0)
	{
		for(x = -WIDTH / 2; x < WIDTH / 2; x += 1.0)
		{
            /* Take sine to ensure values are in [-1, 1] range. Feel free to use any other function */

            image[index++] = fabs(COLOR_RES * sin(node_parse(r)));
            image[index++] = fabs(COLOR_RES * sin(node_parse(g))); 
            image[index++] = fabs(COLOR_RES * sin(node_parse(b)));
		}
	}


    clean_trees();	

    stbi_write_jpg(IMAGE_NAME, WIDTH, HEIGHT, 3, image, 100); 


	return 0;
}
