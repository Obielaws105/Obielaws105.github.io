//Module Eight Practice Nine Assignment - Olivia Bielawski
#include <iostream> // Includes C++ and i/o stream
#include <GL/glew.h>
#include <GL/freeglut.h> // Include the freeGLUT header file

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc.type_ptr.hpp>

using namespace std; // Uses the standard namespace

#define WINDOW_TITLE "Modern OpenGL" //Macro for window title

//Vertex and fragment shader source macro
#ifndef GLSL;
#define GLSL(Version, Source)"#version" #Version "\n" #Source
#endif

GLint shaderProgram, WindowWidth = 800, WindowHeight = 600;
GLuint VBO, VAO, EBO, texture;

//Function prototypes
void UResizeWindow(int, int);
void URenderGraphics(void);
void UCreateShader(void);
void UCreateBuffers(void);

//vertex shader program source code
const GLchar * VertexShader = GLSL(330,
	in layout(location = 0) vec3 vertex_Position;
	in layout(location = 1)vec4 color;

	out vec3 mobileColor; //variable to transfer color data to the fragment shader

	//Global variables for the transform matrix
	uniform mat4 model;
	uniform mat4 view;
	uniform mat4 projection;

	  void main(){
		  gl_Position = projection * view * model *vec4(position, 1.0f); //transforms vertices to clip coordinates
		  mobileColor = color
	  }
);

const GLchar * FragmentShaderSource = GLSL(330,
		in vec3 mobileColor; //Variable to hold incoming color data from the vertex shader
		out vec4 gpuColor; //Variable to pass color data to the GPU

	void main(){
	gpuColor = vec4(mobileColor, 1.0); //Sends color data to the GPU for rendering
}
);

//Main program
int main(int argc, char* argv[]){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH |GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(WindowWidth, WindowHeight);
	glutCreateWindow(WINDOW_TITLE);

	glutReshapeFunc(UResizeWindow);

	glewExperimental = GL_TRUE;
		if(glewInit() != GLEW_OK){
			std::cout << "Failed to initialize GLEW" << std::endl;
			return -1;
		}

	UCreateShader();
	UCreateBuffers();

	//Use the shader program
	glUseProgram(shaderProgram);

	glClearColor(0.0f, 0.0f, 0.01, 1.0f); //Set background color
	glutDisplayFunc(URenderGraphics);
	glutMainLoop();

	//Destroys buffer objects once used
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	return 0;
}

//Implements the UResizeWindow function
void UResizeWindow(int w, int h){
	WindowWidth = w;
	WindowHeight = h;
	glViewport(0, 0, WindowWidth, WindowHeight);
}

//Implements the URenderGraphics function
void URenderGraphics(void){
	glEnable(GL_DEPTH_TEST); //Enable z-depth

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clears the screen

	glBindVertexArray(VAO); //Activate the vertex array object before rendering and transforming them

	//Transforms the object
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0.0, 0.0f, 0.0f)); //Place the object at the center of the viewport
	model = glm::rotate(model, 45.0f, glm::vec3(1.0f, 1.0f, 1.0f)); //Rotate 45 degrees on XYZ
	model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f)); //Increase the scale by 2

	glm::mat4 view
	view = glm::translate(view, glm::vec3(0.5f, 0.0f, -5.0f)); //moves the world 0.5 units on x and -5 units in z

	//Create a perspective projection
	glm::mat4 projection
	projection = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 100.0f);

	//Retrieves and passes transform matrices to the shader program
	GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
	GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
	GLint projLoc = glGetUniformLocation(shaderProgram, "projection");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glutPostRedisplay();

	//Draws the triangles
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0); //Deactivate the vertex array object

	glutSwapBuffers(); //Flips the back buffer with the front buffer every frame. Similar to Gl Flush
}

void UCreateShader(){

	//Create a shader program object

	GLint vertexShader = glCreateShader(GL_VERTEX_SHADER); //Create a vertex shader object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); //retrieves the vertex shader source code
	glCompileShader(vertexShader);

	GLint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // Create a vertex shader object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); //retrieves the fragment shader source code
	glCompileShader(fragmentShader);

	//Attaches the vertex and fragment shaders to the shader program
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//Deletes the vertex and fragment shaders once linked
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

void UCreateBuffers(){
	GLfloat vertices[] = {
			//Positions         Colors
			0.5f,  0.5f,  0.0f,  1.0f, 0.0f, 0.0f,
			0.5f, -0.5f,  0.0f,  0.0f, 1.0f, 0.0f,
		   -0.5f, -0.5f,  0.0f,  0.0f, 0.0f, 1.0f,
		   -0.5f, -0.5f,  0.0f,  1.0f, 0.0f, 1.0f,

		    0.5f, -0.5f, -1.0f,  0.5f, 0.5f, 1.0f,
			0.5f,  0.5f,  1.0f,  0.5f, 0.5f, 1.0f,
		   -0.5f,  0.5f, -1.0f,  0.2f, 0.2f, 0.2f,
		   -0.5f, -0.5f, -1.0f,  1.0f, 0.0f, 1.0f,

	};

	GLuint indices[] = {
			//Triangles
			0, 1, 3,
			1, 2, 3,
			0, 1, 4,
			0, 4, 5,
			0, 5, 6,
			0, 3, 6,
			4, 5, 6,
			4, 6, 7,
			2, 3, 6,
			2, 6, 7,
			1, 4, 7,
			1, 2, 7,
	};
	//Generate buffer ids
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//Activate the vertex array before binding and setting any VBO's and vertex attribute pointers
	glBindVertexArray(VAO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, &EBO); //activates the buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, &EBO); //activates the buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}





























