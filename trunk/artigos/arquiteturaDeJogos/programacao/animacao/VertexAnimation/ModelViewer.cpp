#include "ModelViewer.h"

#include <SDL.h>
#include <SDL_opengl.h>

#include <MathUtil.h>

#include "GameWindow.h"

using namespace md2;

ModelViewer::ModelViewer() : exit(false), degreesToRotate(0) {}

void MyGluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
   GLdouble xmin, xmax, ymin, ymax;

   ymax = zNear * tan(fovy * math::PI / 360.0);
   ymin = -ymax;
   xmin = ymin * aspect;
   xmax = ymax * aspect;


   glFrustum(xmin, xmax, ymin, ymax, zNear, zFar);   	
}


void ModelViewer::setup()
{	
	apModel.reset(new Model("data/models/penguim.md2", "data/models/penguimRed.png"));

	glMatrixMode (GL_PROJECTION);
        glLoadIdentity();
        MyGluPerspective(60.0f, GameWindow::getInstance().getRatio(),1,15000);	        
    glMatrixMode (GL_MODELVIEW);

	glEnable(GL_TEXTURE_2D);

	glFrontFace(GL_CW);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
}

void ModelViewer::processEvents(const SDL_Event& event)
{
    switch (event.type)
    {
        case SDL_QUIT:
            exit = true;
            break;

		case SDL_KEYDOWN:
			if(event.key.keysym.sym == SDLK_ESCAPE)
				exit = true;
			break;
    }
}

void ModelViewer::processLogics()
{
    //Distância para girar (em graus) =
    //velocidade (0.180f) * tempo (ticks)
    float distance = 0.180f * GAMEWINDOW.getTicks();

    //Lemos o estado das teclas
    Uint8* keys = SDL_GetKeyState(NULL);

    //Está com a seta esquerda pressionada?
    if (keys[SDLK_LEFT])
        degreesToRotate += distance;
    //Está com a seta direita pressionada?
    else if (keys[SDLK_RIGHT])
        degreesToRotate -= distance;
}

void ModelViewer::draw() const
{
	//Limpa a tela
    glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	/*
    glPushMatrix();        
        //Gira o triângulo
		glTranslatef(0,0.0f,-6.0f);
        glRotatef(degreesToRotate, 0,0,1);

        //Desenha o triângulo
        glBegin(GL_TRIANGLES);
            glColor3f(1,0,0);
            glVertex2f(0.0f,0.5f);
            glColor3f(0,1,0);
            glVertex2f(-0.5f, -0.5f);
            glColor3f(0,0,1);
            glVertex2f(0.5f, -0.5f);
        glEnd();
    glPopMatrix();*/
	

	glPushMatrix();		
		glTranslatef(0, 0, -50);
		glRotatef(degreesToRotate, 0,1,0);
		apModel->draw();
	glPopMatrix();
	
}

bool ModelViewer::ended()
{
    return exit;
}

void ModelViewer::teardown() {}

