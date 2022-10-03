#include <glew.h>
#include <glfw3.h>

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

#include "Config.h"

class Application
{
private:
	std::vector<std::vector<int>> _upoints;
	int _bw, _bh; // Buffer width and height

public:
	const std::vector<std::vector<int>> getPoints() { return _upoints; }
	void addPoint(int x, int y) {
		_upoints.push_back({ x, y });
	}

	Application(int bufferWidth, int bufferHeight) : _bw(bufferWidth), _bh(bufferHeight)
	{

	}

	void draw_points()
	{
		glBegin(GL_POINTS);
		for (const auto j : _upoints) {
			glVertex2f(j[0], j[1]);
		}
		glEnd();
	}

	void mouse_click_callback(GLFWwindow* window, int button, int action, int mods) {
		std::cout << button << " | " << action << " | " << mods << std::endl;
	};
	void mouse_move_callback(GLFWwindow* window, double xpos, double ypos) {};

};

static void mouse_click_callback(GLFWwindow* window, int button, int action, int mods) {
	std::cout << button << " | " << action << " | " << mods << std::endl;
};

std::vector<std::vector<double>> _upoints;

static void mouse_move_callback(GLFWwindow* window, double xpos, double ypos) {
	std::cout << xpos << " " << ypos << std::endl;
	_upoints.push_back({ xpos, ypos });

};

static void draw_points()
{
	glBegin(GL_POINTS);
	for (const auto dblvec : _upoints)
	{
		glVertex2d(dblvec[0], dblvec[1]);
	}

	glEnd();
}


float clamp(float max, float value)
{
	return std::fmod(max, value) / max;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	std::cout << "Key:" << key << " ScanCode:" << scancode << " action:" << action << " mods:" << mods << std::endl;
	if (key == 256)
		exit(1);
}


void make_circle(int radius, int subdivs)
{
	GLfloat px, py, pz;
	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(1.0f, 1.0f, 1.0f);
	for (int j = 0; j < subdivs; ++j) {
		py = sin(clamp(j, 3.14));
		px = clamp(j, 500); //TODO get rid of 500 (should be window width in px).
		glVertex3f(px, py, 0.0f);
	}
	glEnd();
}

void make_triangle()
{
	glBegin(GL_POINTS);
	glColor3f(1.0, 0.0, 2.0);
	glVertex2f(-0.5f, -0.5f);
	glVertex2f(0.5f, -0.5f);
	glVertex2f(-0.5f, -0.5f);

	glEnd();



}


void get_shaders(int* ret)
{
	
	const char * shaderPath = "Shaders\\PixelShader.hlsl";
	GLuint vshader = glCreateShader(GL_VERTEX_SHADER); 
	GLchar* src;
	FILE* ff;
	errno_t ferr = fopen_s(&ff, shaderPath, "r");
	const size_t MAX_BUFF_SIZE = 35000; 

	char tbuf[500];
	auto fsize = fread_s(tbuf, sizeof(GLchar) * MAX_BUFF_SIZE, 1, 1, ff);

	glShaderSource(vshader, 1, &tbuf, NULL);
}

void t1()
{
	int c;
	get_shaders(&c);
}

void set_viewport()
{
	
}

void create_vertex_buffer()
{
	float poss[6] = {
		-0.5f, -0.5f,
		0.0f, 0.5f,
		0.5f, -0.5f
	};

	unsigned int id;
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), poss, GL_STATIC_DRAW);
}

int make_graphics(void)
{
	GLFWwindow* window;
	Application* app = new Application(640, 480);


	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	


#ifdef DEBUG
	int xscale, yscale = 0.0f;
	glfwGetFramebufferSize(window, &xscale, &yscale);
	std::cout << xscale << " " << yscale << std::endl;
#endif // DEBUG



	glfwSetWindowTitle(window, "The Title");
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_move_callback);
	glfwSetMouseButtonCallback(window, mouse_click_callback);
	

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	GLenum err = glewInit();
	if (GLEW_OK != err) {
		std::cout << "Error: " << glewGetErrorString(err) << std::endl;
	}
	/* Loop until the user closes the window */

	std::cout << glewGetString(GLEW_VERSION) << std::endl;

	float _vbo[200];
	for (int j = 0; j < 200; ++j) {

	}

	int p = 0;
	get_shaders(&p); 




	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		//make_circle(5, 10);
		make_triangle();
		draw_points();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

int main(int argc, char* argv[])
{
	make_graphics(); 

	t1(); 
}