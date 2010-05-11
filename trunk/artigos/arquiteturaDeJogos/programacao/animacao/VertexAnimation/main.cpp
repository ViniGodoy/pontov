#include "GameWindow.h"
#include "ModelViewer.h"

int main(int argc,char* argv[])
{
	GameWindow &gw = GameWindow::getInstance();

	gw.setup("Model Viewer", 800, 600);    
    gw.show(new ModelViewer());

	return 0;
}

