#include "ModelViewer.h"

#include <SDL.h>
#include <SDL_opengl.h>

#include <MathUtil.h>

#include "GameWindow.h"

using namespace md2;

ModelViewer::ModelViewer(const char *modelName, const char *textureName): 
	fExit(false), 
	fPaused(false),
	fInterpolate(true),
	fpDegreesToRotate(0),
	strModelName(modelName),
	strTextureName(textureName)
{
}

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
	apModel.reset(new Model(strModelName, strTextureName));
	apModel->play("run", true);

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
            fExit = true;
            break;

		case SDL_KEYDOWN:
			switch(event.key.keysym.sym)
			{
				case SDLK_ESCAPE:
					fExit = true;
					break;

				case SDLK_SPACE:
					fPaused = !fPaused;
					break;

				case SDLK_UP:
					apModel->playNextAnimation();
					break;

				case SDLK_DOWN:
					apModel->playPreviousAnimation();
					break;

				case SDLK_i:
					fInterpolate = !fInterpolate;
					apModel->setInpoterlate(fInterpolate);
					break;
			}			
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
        fpDegreesToRotate += distance;
    //Está com a seta direita pressionada?
    else if (keys[SDLK_RIGHT])
        fpDegreesToRotate -= distance;	

	if(!fPaused)
		apModel->process();
}

void ModelViewer::draw() const
{
	//Limpa a tela
    glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		
	glPushMatrix();		
		glTranslatef(0, 0, -50);
		glRotatef(fpDegreesToRotate, 0,1,0);
		apModel->draw();
	glPopMatrix();
	
}

bool ModelViewer::ended()
{
    return fExit;
}

void ModelViewer::teardown() {}

