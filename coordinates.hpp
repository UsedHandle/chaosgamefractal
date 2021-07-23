#pragma once

// docs/glslCoordinates.png     
// ....0,1..... .....,......
// ............ ....;#;.....
// ....0,0..1,0 ...^###^....
// ............ ..'''''''...
GLfloat vertices[] = 
{
	-0.002f, -0.002f, 0.0f, 
   0.002f, -0.002f, 0.0f, 
	-0.002f,  0.002f, 0.0f, 
	 0.002f,  0.002f, 0.0f 
};

// Indices tell which vertices to draw
GLuint indices[] {
	// Set of vertices that make a triangle
	0, 1, 2, 
	1, 2, 3, 
};

using namespace glm;
using namespace std;
vector<vec3> positions {
	vec3(  0.0f,  0.5f, 0.0f),
	vec3( -0.5f, -0.5f, 0.0f),
	vec3(  0.5f, -0.5f, 0.0f),
	vec3(  0.0f,  0.0f, 0.0f)
};
