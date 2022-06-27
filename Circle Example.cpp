#include "Circle Example.h"

int circle()
{
	if (!glfwInit())
		exit(1);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	GLFWwindow* window = glfwCreateWindow(480, 480, "Test", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(1);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // refresh rate between each frame

	float circRadius = 0.3;
	float r = 0.0;
	float g = 0.3;
	float b = 0.6;
	float x = 0; // everything -1 <= a <= 1
	float y = 0;
	bool ballLeft = true;
	bool ballDown = true;
	float speed = 0.05;

	while (!glfwWindowShouldClose(window))
	{
		// set up view
		float ratio;
		int width, height;
		glfwGetFramebufferSize(window, &width, &height); // (calls for pointer, can dereference& and change our int
		ratio = width / (float)height;
		glViewport(0, 0, width, height); // what we can see 0,0 to 480,480
		glClear(GL_COLOR_BUFFER_BIT); // causes to draw new frame every iteration

		// movement
		if (ballLeft)
			if (x > -1 + circRadius)
				x -= speed;
			else
				ballLeft = false;
		else
			if (x < 1 - circRadius)
				x += speed;
			else
				ballLeft = true;


		if (ballDown)
			if (y > -1 + circRadius)
				y -= speed - .01;
			else
				ballDown = false;
		else
			if (y < 1 - circRadius)
				y += speed - .01;
			else
				ballDown = true;

		//color
		r = fmod(r + 0.01, 1); // modulo operator for a float. .01 increment, resets to 0 once hits 
		g = fmod(g + 0.02, 1);
		b = fmod(b + 0.03, 1);

		// drawing
		glColor3f(r, g, b);
		glBegin(GL_POLYGON); // lots of different shapes, line strip = hollow circle, polygon = filled

		for (int i = 0; i < 360; i++)
		{
			float degInRad = i * DEG2RAD;
			glVertex2f((cos(degInRad) * circRadius) + x, (sin(degInRad) * circRadius) + y);
		}

		glEnd();

		glBegin(GL_POINTS);

		glVertex2f(0, 0);

		glEnd();

		// swap buffer and check for events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(1);
}