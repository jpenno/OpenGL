#include "Game1.h"
#include "gl_core_4_4.h"
#include "lodepng.h"
#include <iostream>
#include <vector>
using namespace std;
Game1::Game1()
{
}

Game1::~Game1()
{
}

void Game1::Load()
{
	static const char* vertex_shader =
		"#version 400\n"
		"in vec3 vp;"
		"in vec4 vc;"
		"in vec2 vuv;"
		"out vec2 fuv;"
		"out vec4 fc;"
		"uniform mat4 projection;"
		"void main ()"
		"{"
		"  fc = vc;"
		"  fuv = vuv;"
		"  gl_Position = projection * vec4(vp, 1.0);"
		"}";

	static const char* fragment_shader =
		"#version 400\n"
		"in vec4 fc;"
		"in vec2 fuv;"
		"uniform sampler2D texture;"
		"out vec4 frag_colour;"
		"void main ()"
		"{"
		"  frag_colour = texture2D(texture, fuv) * fc;"
		"}";

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);

	m_shader = glCreateProgram();
	glAttachShader(m_shader, vs);
	glAttachShader(m_shader, fs);

	glBindAttribLocation(m_shader, 0, "vp");
	glBindAttribLocation(m_shader, 1, "vc");
	glBindAttribLocation(m_shader, 2, "vuv"); // this one is new

	glLinkProgram(m_shader);

	glDeleteShader(vs);
	glDeleteShader(fs);

	float x = 10;
	float y = 10;
	float w = 100;
	float h = 100;

	float verts[] =
	{
		//   x,     y,    z,    r,    g,    b,    a,    u,    v
		x,     y + h,  0.0f, 1.0f, 0.0f, 0.0f,  1.0f,    0,    1, // bottom left
		x + w, y + h,  0.0f, 0.0f, 1.0f, 0.0f,  1.0f,    1,    1, // bottom right
		x + w, y,      0.0f, 0.0f, 0.0f, 1.0f,  1.0f,    1,    0, // top right
		x,     y,      0.0f, 1.0f, 1.0f, 1.0f,  1.0f,    0,    0  // top left
	};

	unsigned char indices[] =
	{
		0, 1, 2,
		0, 2, 3 
	};

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ibo);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Here we are describing the format of our vertices to openGL
	// Our vertices has only one Attribute - position
	// we need to describe to openGL the size, location & offset in memory for each vertex.
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,                  // attribute 0 (position)
		3,                  // size - how many floats make up the position (x, y, z)
		GL_FLOAT,           // type - our x,y,z are float values
		GL_FALSE,           // normalized? - not used
		sizeof(float) * 9,  // stride - size of the entire vertex object
		(void*)0            // offset in bytes for the position component
	);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,                  // attribute 1 (color)
		4,                  // size - how many floats make up the color (r, g, b, a)
		GL_FLOAT,           // type - our r,g,b,a are float values
		GL_FALSE,           // normalized? - not used
		sizeof(float) * 9,  // stride - size of the vertex
		(void*)(sizeof(float) * 3) // there are 3 floats before the r component
	);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(
		2,                  // attribute 2 (uv)
		2,                  // size - how many floats make up the uv coords
		GL_FLOAT,           // type - our u and v are float values
		GL_FALSE,           // normalized? - not used
		sizeof(float) * 9,  // stride - size of the vertex
		(void*)(sizeof(float) * 7) // there are 7 floats before the u component
	);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	vector<unsigned char> image;
	unsigned int width;
	unsigned int height;

	lodepng::decode(image, width, height, "box.png");

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);

	// set some standard texture paramaters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Game1::UnLoad()
{
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ibo);
	glDeleteVertexArrays(1, &m_vao);
	glDeleteProgram(m_shader);
	glDeleteTextures(GL_TEXTURE_2D, &m_texture);
}

void Game1::UpDate()
{
	cout << "hello world" << endl;
}

void Game1::Draw()
{
	DrawTextureQuad(m_texture, 10, 10, 100, 100);
	DrawTextureQuad(m_texture, 150, 150, 200, 50);
}

void Game1::DrawTextureQuad(unsigned int textureID, int x, int y, int w, int h)
{
	float verts[] =
	{
		//  x,     y,    z,    r,    g,    b,    a,    u,    v
		x,       y + h,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0,    1,// bottom left
		x + w,   y + h,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1,    1,// bottom right
		x + w,   y,      0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1,    0,// top right
		x,       y,      0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0,    0// top left
	};

	unsigned char indices[] =
	{
		0, 1, 2,
		0, 2, 3
	};

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	float l = 0;                 // left side of the window
	float r = GetWindowWidth();  // right side of the window
	float t = 0;                 // top side of the window
	float b = GetWindowHeight(); // bottom side of the window
	float n = 0.0f;              // closest side of the window (imagine the window is 3d)
	float f = 1000.0f;           // farthest side of the window (imagine the window is 3d)

	 //create an orthographic projection matrix
	 //you will find helper functions available in math libraries for doing this.
	 //on the shader, our verts will be multiplied by this matrix
	static float projection[] =
	{
		2.0f / (r - l),         0,                      0,                      0,
		0,                      2.0f / (t - b),         0,                      0,
		0,                      0,                      2.0f / (f - n),         0,
		-(r + l) / (r - l),     -(t + b) / (t - b),     -(f + n) / (f - n),     1
	};

	// tell openGL to use our shader program
	glUseProgram(m_shader);
	glUniformMatrix4fv(glGetUniformLocation(m_shader, "projection"), 1, false, projection);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glUniform1i(glGetUniformLocation(m_shader, "texture"), 0);

	// Bind our VAO, remember, its grouped our VBO and IBO
	glBindVertexArray(m_vao);
	// Draw our buffers. We've hard coded 3, referring to the number of verts. 
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);

	// unbind our VAO so nothing else accidental changes it
	glBindVertexArray(0);
}
