////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Logger.hpp"
#include "config.h"
#include <SFML/Graphics.hpp>
#include <OpenGL/gl.h>
#include <iostream>

////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////

int main()
{
    // Create main window
    sf::RenderWindow App(sf::VideoMode(640, 480), "SFML Graphics");
    App.PreserveOpenGLStates(true);

    // Load an OpenGL texture.
    // We could directly use a sf::Image as an OpenGL texture (with its Bind() member function),
    // but here we want more control on it (generate mipmaps, ...) so we create a new one
    GLuint Texture = 0;
    {
        sf::Image Image;
        std::string dataPath = DATA_PATH;
        if (!Image.LoadFromFile(dataPath + "/barnacle.png"))
            return EXIT_FAILURE;
        Image.SetSmooth(false);
        glGenTextures(1, &Texture);
        glBindTexture(GL_TEXTURE_2D, Texture);
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, Image.GetWidth(), Image.GetHeight(), GL_RGBA, GL_UNSIGNED_BYTE, Image.GetPixelsPtr());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    }

    // Enable Z-buffer read and write
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_TRUE);
    glClearDepth(1.f);

    // Setup a perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.f, 1.f, 1.f, 500.f);

    // Bind our texture
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, Texture);
    glColor4f(1.f, 1.f, 1.f, 1.f);

    sf::Clock Clock;

    // Start game loop
    while (App.IsOpened())
    {
        // Process events
        sf::Event Event;
        while (App.GetEvent(Event))
        {
            // Close window : exit
            if (Event.Type == sf::Event::Closed)
                App.Close();
        }

        sf::View& view = App.GetDefaultView();
        view.Move(1, 1);

        // Clear screen
        App.Clear();

        // Clear depth buffer
        glClear(GL_DEPTH_BUFFER_BIT);

        // Apply some transformations
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.f, 0.f, -200.f);
        glRotatef(Clock.GetElapsedTime() * 50, 1.f, 0.f, 0.f);
        glRotatef(Clock.GetElapsedTime() * 30, 0.f, 1.f, 0.f);
        glRotatef(Clock.GetElapsedTime() * 90, 0.f, 0.f, 1.f);

        // Draw a cube
        glBegin(GL_QUADS);

        glTexCoord2f(0, 0); glVertex3f(-50.f, -50.f, -50.f);
        glTexCoord2f(0, 1); glVertex3f(-50.f,  50.f, -50.f);
        glTexCoord2f(1, 1); glVertex3f( 50.f,  50.f, -50.f);
        glTexCoord2f(1, 0); glVertex3f( 50.f, -50.f, -50.f);

        glTexCoord2f(0, 0); glVertex3f(-50.f, -50.f, 50.f);
        glTexCoord2f(0, 1); glVertex3f(-50.f,  50.f, 50.f);
        glTexCoord2f(1, 1); glVertex3f( 50.f,  50.f, 50.f);
        glTexCoord2f(1, 0); glVertex3f( 50.f, -50.f, 50.f);

        glTexCoord2f(0, 0); glVertex3f(-50.f, -50.f, -50.f);
        glTexCoord2f(0, 1); glVertex3f(-50.f,  50.f, -50.f);
        glTexCoord2f(1, 1); glVertex3f(-50.f,  50.f,  50.f);
        glTexCoord2f(1, 0); glVertex3f(-50.f, -50.f,  50.f);

        glTexCoord2f(0, 0); glVertex3f(50.f, -50.f, -50.f);
        glTexCoord2f(0, 1); glVertex3f(50.f,  50.f, -50.f);
        glTexCoord2f(1, 1); glVertex3f(50.f,  50.f,  50.f);
        glTexCoord2f(1, 0); glVertex3f(50.f, -50.f,  50.f);

        glTexCoord2f(0, 1); glVertex3f(-50.f, -50.f,  50.f);
        glTexCoord2f(0, 0); glVertex3f(-50.f, -50.f, -50.f);
        glTexCoord2f(1, 0); glVertex3f( 50.f, -50.f, -50.f);
        glTexCoord2f(1, 1); glVertex3f( 50.f, -50.f,  50.f);

        glTexCoord2f(0, 1); glVertex3f(-50.f, 50.f,  50.f);
        glTexCoord2f(0, 0); glVertex3f(-50.f, 50.f, -50.f);
        glTexCoord2f(1, 0); glVertex3f( 50.f, 50.f, -50.f);
        glTexCoord2f(1, 1); glVertex3f( 50.f, 50.f,  50.f);

        glEnd();

        // Finally, display the rendered frame on screen
        App.Display();
    }

    glDeleteTextures(1, &Texture);

    return EXIT_SUCCESS;
}
