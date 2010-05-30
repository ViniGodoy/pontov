#include "GameWindow.h"
#include "ModelViewer.h"

int main(int argc,char* argv[])
{
	if(argc < 3)
	{
		printf("Usage: modelViewer <modelName> <textureName>\n");
		return 0;
	}

	GameWindow &gw = GameWindow::getInstance();

	gw.setup("Model Viewer", 800, 600);    
    gw.show(new ModelViewer(argv[1], argv[2]));

	return 0;
}

