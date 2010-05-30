#ifndef MODELVIEWER_H_INCLUDED
#define MODELVIEWER_H_INCLUDED

#include <memory>

#include "GameSteps.h"
#include "md2/Model.h"

class ModelViewer : public GameSteps
{
    public:
        explicit ModelViewer(const char *modelName, const char *textureName);

        virtual void setup();

        virtual void processEvents(const SDL_Event& event);
        virtual void processLogics();
        virtual void draw() const;

        virtual bool ended();

        virtual void teardown();
    private:
        float fpDegreesToRotate;
        bool fExit;
		bool fPaused;
		bool fInterpolate;

		std::auto_ptr<md2::Model> apModel;

		std::string strModelName;
		std::string strTextureName;
};

#endif 
