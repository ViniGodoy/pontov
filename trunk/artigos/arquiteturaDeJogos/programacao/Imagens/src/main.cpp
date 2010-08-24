/******************************************************************************
*
* COPYRIGHT Bruno C Sanches ALL RIGHTS RESERVED.
*
* This software cannot be copied, stored, distributed without  
* Bruno C Sanches prior authorization.
*
* This file was made available on http://www.pontov.com.br and it is free 
* to be restributed or used under Creative Commons license 2.5 br: 
* http://creativecommons.org/licenses/by-sa/2.5/br/
*
*******************************************************************************
* Este software nao pode ser copiado, armazenado, distribuido sem autorização 
* a priori de Bruno C Sanches
*
* Este arquivo foi disponibilizado no site http://www.pontov.com.br e esta 
* livre para distribuição seguindo a licença Creative Commons 2.5 br: 
* http://creativecommons.org/licenses/by-sa/2.5/br/
*
******************************************************************************/

#include <stdlib.h>

#if	defined(linux)
	#include <SDL/SDL.h>
#else
	#include <SDL.h>
#endif

static SDL_Surface *pScreen_gl = NULL;

static void CreateGreyscaleImage(SDL_Surface *work, const SDL_Surface *logo)
{
	for(int y = 0;y < logo->h; ++y)
	{
		for(int x = 0; x < logo->w; ++x)
		{			
			Uint32 *srcPixel = (Uint32 *)logo->pixels + (y * logo->pitch / 4) + x;
			Uint32 *destPixel = (Uint32 *)work->pixels + (y * work->pitch / 4) + x;

			float red = (float) (((*srcPixel) & logo->format->Rmask) >> logo->format->Rshift);
			float green = (float) (((*srcPixel) & logo->format->Gmask) >> logo->format->Gshift);
			float blue = (float) (((*srcPixel) & logo->format->Bmask) >> logo->format->Bshift);

			float color = (red * 0.3f) + (green * 0.59f) + (blue * 0.11f);
			color = ((int)color) + 0.5f;

			Uint8 finalColor = color > 255 ? 255 : (int) color;

			*destPixel = SDL_MapRGBA(work->format, finalColor, finalColor, finalColor, 0);
		}
	}
}

static void CreateSingleChannelImage(SDL_Surface *work, const SDL_Surface *logo, Uint32 mask)
{
	for(int y = 0;y < logo->h; ++y)
	{
		for(int x = 0; x < logo->w; ++x)
		{			
			Uint32 *srcPixel = (Uint32 *)logo->pixels + (y * logo->pitch / 4) + x;
			Uint32 *destPixel = (Uint32 *)work->pixels + (y * work->pitch / 4) + x;

			*destPixel = mask & *srcPixel;
		}
	}
}

static void CreateRedImage(SDL_Surface *work, const SDL_Surface *logo)
{
	CreateSingleChannelImage(work, logo, logo->format->Rmask);
}

static void CreateGreenImage(SDL_Surface *work, const SDL_Surface *logo)
{
	CreateSingleChannelImage(work, logo, logo->format->Gmask);
}

static void CreateBlueImage(SDL_Surface *work, const SDL_Surface *logo)
{
	CreateSingleChannelImage(work, logo, logo->format->Bmask);
}

static void CreatePinkImage(SDL_Surface *work, const SDL_Surface *logo)
{
	CreateSingleChannelImage(work, logo, logo->format->Rmask | logo->format->Bmask);
}

static void MainLoop()
{		
	Uint32 last=SDL_GetTicks();
	SDL_Surface *logo = SDL_LoadBMP("logo.bmp");	

	if(logo == NULL)
	{
		fprintf(stderr, "Não foi possivel carregar logo.bmp\n");

		return;
	}

	//Criando uma surface auxiliar e convertendo todas para um formato de trabalho
	SDL_Surface *work = SDL_DisplayFormat(logo);
	SDL_FreeSurface(logo);
	logo = SDL_DisplayFormat(work);	

	bool exit = false;
    while(!exit)
    {     		
    	Uint32 current=SDL_GetTicks();    	
    	Uint32 elapsed=current-last;    		    	
    	if(elapsed<10)
    		continue;

		last = current;

		SDL_Event ev;

		//checando input
		while ( SDL_PollEvent(&ev) ) 
		{
			switch(ev.type)
			{
				case SDL_QUIT:
					exit = true;
					break;
				
				case SDL_KEYDOWN:
					//ESC?
					switch(ev.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							exit = true;
							break;

						case SDLK_1:
						case SDLK_KP1:
							CreateRedImage(work,logo);
							break;

						case SDLK_2:
						case SDLK_KP2:
							CreateGreenImage(work,logo);
							break;

						case SDLK_3:
						case SDLK_KP3:
							CreateBlueImage(work,logo);
							break;

						case SDLK_4:
						case SDLK_KP4:
							CreatePinkImage(work,logo);
							break;

						case SDLK_5:
						case SDLK_KP5:
							CreateGreyscaleImage(work,logo);
							break;

					}				
					break;
			}
		}

    	// Limpa a tela
    	SDL_FillRect(pScreen_gl, NULL, SDL_MapRGB(pScreen_gl->format, 0, 0, 0));

		SDL_Rect rect;

		rect.x = 0;
		rect.y = 0;
		rect.w = logo->w;
		rect.h = logo->h;

		SDL_BlitSurface(logo, NULL, pScreen_gl, &rect);	

		if(work != NULL)
		{
			rect.x = 0;
			rect.y = logo->h;
			SDL_BlitSurface(work, NULL, pScreen_gl, &rect);	
		}		
                
		//Atualiza tela
        SDL_UpdateRect(pScreen_gl, 0, 0, 0, 0);
    }
}

int main(int argc, char *argv[])
{
	// Inicializa a SDL
    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) 
	{
        fprintf(stderr, "Nao consegui inicializar a SDL: %s\n", SDL_GetError());
        exit(1);
    }    
	atexit(SDL_Quit);

    pScreen_gl = SDL_SetVideoMode(429, 141*2, 32, SDL_SWSURFACE);
    if ( pScreen_gl == NULL ) 
    {
        fprintf(stderr, "Falhou inicializacao do video: %s\n", SDL_GetError());
        exit(1);
    }    	

	MainLoop();

	exit(0);

    return 0; 
}
