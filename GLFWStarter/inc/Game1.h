#pragma once
#include "Applaction.h"

class Game1 : public Applaction {
public:

	Game1();
	virtual ~Game1();

	virtual void Load();
	virtual void UnLoad();

	virtual void UpDate();
	virtual void Draw();

	void DrawTextureQuad(unsigned int textureID, int xPos, int yPos, int w, int h);

private:
	unsigned int m_vao; // handle for a vertex array object (wrapper for our vbo and ibo)
	unsigned int m_vbo; // handle for vertex buffer object
	unsigned int m_ibo; // handle for index buffer object

	unsigned int m_texture; 

	unsigned int m_shader; // handle for our shader program

};