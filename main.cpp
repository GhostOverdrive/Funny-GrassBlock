#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#pragma comment(lib, "glu32.lib")

using namespace sf;

GLuint LoadTexture(sf::String path)
{
		sf::Image image;
		image.loadFromFile(path);
		GLuint texture = 0;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image.getSize().x, image.getSize().y, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		return texture;
}

int main()
{
	RenderWindow window(VideoMode(800, 600), "SFML OpenGL");

	Texture t;
	t.loadFromFile("resources/background.jpg");
	Sprite background(t);

	GLuint grass[3];
	grass[0] = LoadTexture("resources/grass/bottom.jpg");
	grass[1] = LoadTexture("resources/grass/side.jpg");
	grass[2] = LoadTexture("resources/grass/top.jpg");

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glClearDepth(1.f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.f, 1.f, 1.f, 500.f);
	glEnable(GL_TEXTURE_2D);

	Clock clock;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == event.Closed)
			{
				window.close();
			}
		}
		float time = clock.getElapsedTime().asSeconds() * 100;
		float size = 20.f;

		//Draw the bg
		window.pushGLStates();
		window.draw(background);
		window.popGLStates();

		//Clear the depth buffer
		glClear(GL_DEPTH_BUFFER_BIT);

		//Apply some transformations
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0, 0, -100);
		glRotatef(time * 0.5, 50, 50, 0);

		//Lol Drawing the qube
		//All sides : 

		//Back :
		glBindTexture(GL_TEXTURE_2D, grass[1]);
		glBegin(GL_QUADS);
			glTexCoord2f(0, 0); glVertex3f(-size, -size, -size);
			glTexCoord2f(1, 0); glVertex3f( size, -size, -size);
			glTexCoord2f(1, 1); glVertex3f( size,  size, -size);
			glTexCoord2f(0, 1); glVertex3f(-size,  size, -size);
		glEnd();

		//Front :
		glBindTexture(GL_TEXTURE_2D, grass[1]);
		glBegin(GL_QUADS);
			glTexCoord2f(0, 0); glVertex3f( size, -size,  size);
			glTexCoord2f(1, 0); glVertex3f(-size, -size,  size);
			glTexCoord2f(1, 1); glVertex3f(-size,  size,  size);
			glTexCoord2f(0, 1); glVertex3f( size,  size,  size);
		glEnd();

		//Left :
		glBindTexture(GL_TEXTURE_2D, grass[1]);
		glBegin(GL_QUADS);
			glTexCoord2f(0, 0); glVertex3f(-size, -size,  size);
			glTexCoord2f(1, 0); glVertex3f(-size, -size, -size);
			glTexCoord2f(1, 1); glVertex3f(-size,  size, -size);
			glTexCoord2f(0, 1); glVertex3f(-size,  size,  size);
		glEnd();

		//Right :
		glBindTexture(GL_TEXTURE_2D, grass[1]);
		glBegin(GL_QUADS);
			glTexCoord2f(0, 0); glVertex3f( size, -size, -size);
			glTexCoord2f(1, 0); glVertex3f( size, -size,  size);
			glTexCoord2f(1, 1); glVertex3f( size,  size,  size);
			glTexCoord2f(0, 1); glVertex3f( size,  size, -size);
		glEnd();

		//Bottom :
		glBindTexture(GL_TEXTURE_2D, grass[0]);
		glBegin(GL_QUADS);
			glTexCoord2f(0, 0); glVertex3f(-size, -size,  size);
			glTexCoord2f(1, 0); glVertex3f( size, -size,  size);
			glTexCoord2f(1, 1); glVertex3f( size, -size, -size);
			glTexCoord2f(0, 1); glVertex3f(-size, -size, -size);
		glEnd();

		//Top :
		glBindTexture(GL_TEXTURE_2D, grass[2]);
		glBegin(GL_QUADS);
			glTexCoord2f(0, 0); glVertex3f(-size,  size, -size);
			glTexCoord2f(1, 0); glVertex3f( size,  size, -size);
			glTexCoord2f(1, 1); glVertex3f( size,  size,  size);
			glTexCoord2f(0, 1); glVertex3f(-size,  size,  size);
		glEnd();

		//display, please
		window.display();
	}

	//glDeleteTextures(1, &texture);

    return 0;
}