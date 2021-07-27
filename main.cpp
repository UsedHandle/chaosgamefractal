// std
#include <iostream>
#include <vector>

// Window Events and Graphics
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Math
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Custom headers
#include "glInit.hpp"
#include "coordinates.hpp"
#include "shaderHandler.hpp"

#define WIDTH 800
#define HEIGHT 800

int main(){

	// Inits glfw and core profile
	glfwGLInit();

	// Creates window with a width of xxx, a height of xxx, a name of xxx, without fullscreen, and window to share resources with 
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpengl", NULL, NULL);

	// Checks if there was no errors
	if(window == NULL){
		glfwTerminate();		
		std::cout << "Failed to create a window with GLFW" << std::endl;

		return -1;
	}

	// Tells glfw that the window will be used
	glfwMakeContextCurrent(window);

	// Loads configurations for OpenGL
	gladLoadGL();

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		std::cout << "Failed to initialize GLAD" << std::endl;

		return -1;
	}
	
	cout << "OpenGL version: " <<glGetString(GL_VERSION) << endl;

	// Creates shader program
	GLuint shaderProgram = makeShader("shaders/shader.vert", "shaders/shader.frag");

	// Creates and VBO, VAO, and EBO
	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Chooses the VAO as the vertex array to be modified, binds a VBO to the VAO and passes vertices to the VBO
	// GL_STATIC_DRAW means that the data will not be changed, used many times, and will be drawn to the screen
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Chooses the EBO as the element to be modified, and passes in the indices
	// GL_STATIC_DRAW still means the same thing as above
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	// Tells the vertex shader how the data from the binded vbo 
	// Tells glsl the location that was told in the .vert, how many numbers per point, the type, 
	// if it is normalized, the amount of bytes until the next vertex, and where the data begins in the vbo 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

	// Unbinds the objects
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	
	using namespace glm;
	mat4 model = mat4(1.0f);
	mat4 view = mat4(1.0f);
	mat4 proj = mat4(1.0f);
	

	view = translate(view, vec3(0.0f, 0.0f, -2.0f));
	proj = perspective(radians(45.0f), (float)(WIDTH/HEIGHT), 0.1f, 100.0f); 

	// Area OpenGL renders from (0,0) to (width, height)
	glViewport(0, 0, WIDTH, HEIGHT);

	// Specify the color of the background to GL_COLOR_BUFFER_BIT
	glClearColor(0.19f, 0.24f, 0.27, 1.0f);

	glUseProgram(shaderProgram);

	GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));
	GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));
	GLint projLoc = glGetUniformLocation(shaderProgram, "proj");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, value_ptr(proj));

	srand(time(nullptr));
	for(int i = 0; i < 100000; i++){
		vec3 newPos = positions.back();
		int vertexIndex = rand()/((RAND_MAX +1u)/3);
		vec3 difference = positions[vertexIndex] - newPos;

		vec3 halfOfDifference = vec3(difference.x/2, difference.y/2, difference.z/2);	

		newPos += halfOfDifference;

		positions.push_back(newPos);
	}
	

	long unsigned int frameCount = 1;
	// while window is open 
	while(!glfwWindowShouldClose(window)){
		// Check for events (like resizing)
		glfwPollEvents();	

		
		// Draw GL_COLOR_BUFFER_BIT to the back buffer 
		glClear(GL_COLOR_BUFFER_BIT);	
	

		// Binds the VAO to draw the data
		glBindVertexArray(VAO);
			
		for(long unsigned int i = 0; i < positions.size() && i < frameCount*30; i++){
			GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
			mat4 tempModel;
			tempModel = mat4(1.0f);
			tempModel = translate(tempModel, positions[i]);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(tempModel));

			glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, nullptr);

		}
		
		
		// Swap the drawn back buffer with the front buffer
		glfwSwapBuffers(window);
		frameCount++;	
	}

	glDeleteProgram(shaderProgram);

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	

	// Terminate glfw and the window
	glfwDestroyWindow(window);
	glfwTerminate();

}
