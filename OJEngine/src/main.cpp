#include "../OJEngine/core.h"
#include "timer.h"
#include "random.h"
#define WINDOW_WIDTH 1820
#define WINDOW_HEIGHT 980
#define VERTEX_CAP 8

Window wnd(WINDOW_WIDTH, WINDOW_HEIGHT, "FractalGen\tPress R to regenerate fractal");
Graphics gfx(&wnd);
rng_mt19937_std rng;


struct vertexAttrib
{
	vertexAttrib() { randomize(); }
	int x, y;
	float xMul, yMul;
	int r, g, b;

	inline void randomize()
	{
		x = rng.randomInteger<int>(0, WINDOW_WIDTH);
		y = rng.randomInteger<int>(0, WINDOW_HEIGHT);
		xMul = rng.randomReal<float>(0, 1);
		yMul = rng.randomReal<float>(0, 1);
		r = rng.randomInteger<int>(0, 255);
		g = rng.randomInteger<int>(0, 255);
		b = rng.randomInteger<int>(0, 255);
	}
};

vertexAttrib vertecic[VERTEX_CAP] = {};

void activate(int &posX, int &posY, int &r, int &g, int&b, int index);

int main()
{
	gfx.clear();

	int posX = rng.randomInteger<int>(0, WINDOW_WIDTH), posY = rng.randomInteger<int>(0, WINDOW_HEIGHT);

	int r = 0, g = 0, b = 0;
	int maxVertecis = rng.randomInteger<int>(2, VERTEX_CAP);

	glfwSwapInterval(0);
	while (!wnd.closed())
	{
		// calcs per frame
		for (int j = 0; j < 1000; j++)
		{
			activate(posX, posY, r, g, b, rng.randomInteger<int>(0, maxVertecis));
			gfx.putpixel(posX, posY, r, g, b);
		}

		if (wnd.getKey(KEY_R).pressed)
		{
			gfx.clear();
			vertecic[0].randomize();
			vertecic[1].randomize();
			vertecic[2].randomize();
			vertecic[3].randomize();
			posX = rng.randomInteger<int>(0, WINDOW_WIDTH);
			posY = rng.randomInteger<int>(0, WINDOW_HEIGHT);
			maxVertecis = rng.randomInteger<int>(2, VERTEX_CAP);
			for (int j = 0; j < 10; j++)
			{
				activate(posX, posY, r, g, b, rng.randomInteger<int>(0, maxVertecis));
			}
		}

		gfx.display();
		wnd.pollEvent();
	}

	return 0;
}

void activate(int &posX, int &posY, int &r, int &g, int&b, int index)
{
		posX += (vertecic[index].x - posX) * vertecic[index].xMul;
		posY += (vertecic[index].y - posY) * vertecic[index].yMul;
		r = vertecic[index].r;
		g = vertecic[index].g;
		b = vertecic[index].b;
}