#include "polyrythm.h"

void calculateTip(vector& src, float timer)
{
	src.tip.x = cos(timer) * src.rad + src.center.x;
	src.tip.y = sin(timer) * src.rad + src.center.y;
}

void drawCircle(vector src, float r, float g, float b)
{
	glColor3f(r, g, b);
	glBegin(GL_LINE_STRIP);

	for (int i = 0; i < 361; i++)
	{
		float degInRad = i * DEG2RAD;
		glVertex2f((cos(degInRad) * src.rad) + src.center.x, (sin(degInRad) * src.rad) + src.center.y);
	}

	glEnd();
}

void drawVector(vector& src, coord base, float color, float counter, float speed)
{
	counter = counter * speed;
	src.center.x = base.x;
	src.center.y = base.y;

	glColor3f(1, 1, 1);
	glBegin(GL_LINES);

	glVertex2f(src.center.x, src.center.y);
	calculateTip(src, counter);
	glVertex2f(src.tip.x, src.tip.y);

	glEnd();

	if (cos(counter * speed) == 0)
		drawCircle(src, 1, 1, 1);
	else
		drawCircle(src, .3f, .3f, .3f);
}

int polyrythm(int vecCount, int bpm)
{
	const int numVecs = 6;
	if (!glfwInit())
		exit(1);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	GLFWwindow* window = glfwCreateWindow(1000, 1000, "Fourier", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		exit(1);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(2);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	vector vecs[numVecs];
	list<coord> trail;

	for (int i = 0; i < numVecs; i++)
		vecs[i].rad = 1 / (float)(i + 1) / 2.5;
		

	float timer = 270 * DEG2RAD;
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glClearColor(0, 0, 0, 1);
		glColor3f(1, 1, 1);

		glBegin(GL_LINES);

		coord base(0.0f, 0.0f);

		float counter = timer;
		for (int i = 0; i < numVecs; i++)
		{
			counter = -counter;

			if (i == 0)
				drawVector(vecs[i], base, 1, counter, 1);
			else
				drawVector(vecs[i], vecs[i - 1].tip, 1, counter, i + 1);
		}

		trail.push_back(vecs[numVecs - 1].tip);

		glColor3f(0.0f, .7f, .95f);
		glBegin(GL_LINE_STRIP);

		list<coord>::iterator it = trail.begin();
		while (it != trail.end())
		{
			glVertex2f((*it).x, (*it).y);
			it++;
		}

		if (trail.size() > 380)
			trail.clear();

		glEnd();

		// buffer swap / events
		
		glfwSwapBuffers(window);
		glfwPollEvents();
		timer += 1 / (float)bpm; // change start position and speed
		if (sin(timer) == 1 && cos(timer) == 0)
			timer = 0.0f;
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(1);
}