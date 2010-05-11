#ifndef MODELVIEWER_H_INCLUDED
#define MODELVIEWER_H_INCLUDED

#include <memory>

#include "GameSteps.h"
#include "md2/Model.h"

class ModelViewer : public GameSteps
{
    public:
        explicit ModelViewer();

        virtual void setup();

        virtual void processEvents(const SDL_Event& event);
        virtual void processLogics();
        virtual void draw() const;

        virtual bool ended();

        virtual void teardown();
    private:
        float degreesToRotate;
        bool exit;

		std::auto_ptr<md2::Model> apModel;


};

#endif 
