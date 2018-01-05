#include "../OJEngine/core.h"
#include "timer.h"
#include "random.h"
#define WINDOW_WIDTH 1820
#define WINDOW_HEIGHT 980
#define VERTEX_CAP 8 
#define MOVE_SPEED 1500
#define ZOOM_SPEED 1000

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

	timer t;

	glfwSwapInterval(0);
	while (!wnd.closed())
	{
		float dt = t.restart<float>();
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
		}

		if (wnd.getKey(KEY_UP).held)
		{
			gfx.clear();
			for (size_t i = 0; i < maxVertecis; i++)
			{
				vertecic[i].x *= 1.01f;
				vertecic[i].y *= 1.01f;
			}
		}

		if (wnd.getKey(KEY_DOWN).held)
		{
			gfx.clear();
			for (size_t i = 0; i < maxVertecis; i++)
			{
				vertecic[i].x *= 0.99f;
				vertecic[i].y *= 0.99f;
			}
		}

		if (wnd.getKey(KEY_W).held)
		{
			gfx.clear();
			for (size_t i = 0; i < maxVertecis; i++)
			{
				vertecic[i].y += MOVE_SPEED * dt;
			}
		}
		if (wnd.getKey(KEY_S).held)
		{
			gfx.clear();
			for (size_t i = 0; i < maxVertecis; i++)
			{
				vertecic[i].y += MOVE_SPEED * -dt;
			}
		}
		if (wnd.getKey(KEY_A).held)
		{
			gfx.clear();
			for (size_t i = 0; i < maxVertecis; i++)
			{
				vertecic[i].x += MOVE_SPEED * dt;
			}
		}
		if (wnd.getKey(KEY_D).held)
		{
			gfx.clear();
			for (size_t i = 0; i < maxVertecis; i++)
			{
				vertecic[i].x += MOVE_SPEED * -dt;
			}
		}



		// calcs per frame
		for (int j = 0; j < 10000; j++)
		{
			activate(posX, posY, r, g, b, rng.randomInteger<int>(0, maxVertecis - 1));
			gfx.putpixel(posX, posY, r, g, b);
		}
		for (size_t i = 0; i < maxVertecis; i++)
		{
			gfx.drawLine(vertecic[i].x - 5, vertecic[i].y - 5, vertecic[i].x + 5, vertecic[i].y + 5, 255, 255, 255);
			gfx.drawLine(vertecic[i].x - 5, vertecic[i].y + 5, vertecic[i].x + 5, vertecic[i].y - 5, 255, 255, 255);
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