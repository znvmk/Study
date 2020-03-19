/*
	texture.h v1.4
	neo6
	neo6@users.sourceforge.net, http://dx66.dyndns.org/neo6/

	Load image files as textures.

	Revision 1.1: Add loadBMP(),loadTGA(),loadRGB().
	Revision 1.3: Add m_width, m_height, width(), height()
	Revision 1.4: Add loadPCX(),modify loadTGA()
*/

#ifndef _INC_TEXTURE
#define _INC_TEXTURE

#pragma comment(lib, "texture.lib")
/*

 This code is based on a code from OpenGL Challenge
 (http://OGLChallenge.dhs.org).
 The original author is Chris Stephenson(chrisstephenson@home.com).
 The original file is crstextures.h.
 It is one entry of the "Collision Crazy (2000-09-17)" 
 competation.
 I wrapped it into a class.
  -neo6

 File that need to be linked to.
 opengl32.lib glu32.lib glut32.lib glaux.lib

Usage:
	(create/load texture)
	Texture* tex = new Texture("foo.bmp",true);

	(values can be any from the list at the end of the file)
	tex->ChangeSettings(GL_LINEAR,GL_LINEAR_MIPMAP_LINEAR,GL_REPEAT,GL_REPEAT,GL_MODULATE);
	
	(if you have more than one texture and you need to flip between them)
	tex->MakeCurrent(&TextureName);

	make calls usein texture here...
*/

class Texture
{
	int m_width;
	int m_height;
	int m_tex;

	void loadBMP(const char* fname, bool make_mipmaps);
	void loadTGA(const char* fname, bool make_mipmaps);
	void loadRGB(const char* fname, bool make_mipmaps);
	void loadPPM(const char* fname, bool make_mipmaps);
	void loadPCX(const char* fname, bool make_mipmaps);

public:
	Texture() { m_width = 0; m_height = 0;}
	Texture(const char* fname,	bool make_mipmaps=true);
	~Texture();

	bool IsValid() const { return m_tex != 0;}
	int Width() const { return m_width;}
	int Height() const { return m_height;}

	void ChangeSettings(GLuint mag_filter, 
		GLuint min_filter,
		GLuint wrap_s,
		GLuint wrap_t,
		GLuint env_mode);
	void MakeCurrent();
};

/**
 Parameters for ChangeSettings:
 mag_filter
    GL_LINEAR
	GL_NEAREST

 min_filter
	GL_LINEAR_MIPMAP_LINEAR
	GL_LINEAR_MIPMAP_NEAREST
	GL_LINEAR
	GL_NEAREST_MIPMAP_LINEAR
	GL_NEAREST_MIPMAP_NEAREST
	GL_NEAREST

 wrap_s
	GL_REPEAT
	GL_CLAMP
	
 wrap_t
	GL_REPEAT
	GL_CLAMP

 env_mode
	GL_BLEND
	GL_DECAL
	GL_MODULATE
	GL_REPLACE
*/

#endif