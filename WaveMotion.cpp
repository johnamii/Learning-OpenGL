#include "WaveMotion.h"

int waveMotion(float wavelength, float amplitude, float frequency)
{
	if (!glfwInit())
		exit(1);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	GLFWwindow* window = glfwCreateWindow(1000, 600, "Wave Window", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		exit(1);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(10);

	float x, y, k;
	double clock = 360 * DEG2RAD;

	particle particles[40][40];
	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			particles[i][j].centerX = ((float)i * 2) / 40 - 1;
			particles[i][j].centerY = ((float)j * 2) / 40 - 1;

			if (j > 0)
				particles[i][j].radius = (float)j / 200;
		}
	}

	// set up view
	float ratio;
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float)height;
	glViewport(0, 0, width, height);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		// movement


		// color
		glClearColor(1, 1, 1, 1);

		// drawing
		glPointSize(4);

		glColor3f(.7f, .9f, 1.0f);
		glBegin(GL_POLYGON);

		glVertex2f(-1.0f, -1.0f);
		//glVertex2f(-1.0f, 0.0f);

		for (int i = 0; i < 40; i++)
		{
			x = particles[i][20].centerX + particles[i][20].radius * cos(clock + i / 2.5);
			y = particles[i][20].centerY + particles[i][20].radius * sin(clock + i / 2.5);

			glVertex2f(x, y);
		}

		//glVertex2f(1.0f, 0.0f);
		glVertex2f(1.0f, -1.0f);

		glEnd();

		glColor3f(0, 0, .1);
		glBegin(GL_POINTS);

		for (int i = 0; i < 40; i += 2)
		{
			for (int j = 0; j < 20; j += 4)
			{

				x = particles[i][j].centerX + particles[i][j].radius * cos(clock + i / 2.5);
				y = particles[i][j].centerY + particles[i][j].radius * sin(clock + i / 2.5);

				glVertex2f(x, y);
			}
		}

		glEnd();

		clock -= 15 * DEG2RAD;

		// buffer swap / events
		Sleep(1);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(1);
}