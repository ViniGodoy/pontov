#ifndef MD2MODEL_H_INCLUDED
#define MD2MODEL_H_INCLUDED

#include <string>
#include <stdexcept>

#include <SDL_opengl.h>
#include <Vector3D.h>

#include "ogl/Texture.h"

#include "Animation.h"

#include <map>

namespace md2
{
    class Model
    {
        public:
			explicit Model(const std::string& filename, const std::string& texFilename, float loadScale=1.0);
            ~Model();

            void process();
            void draw() const;

            void setAnimation(const std::string& name, bool playing=false, bool looping=true);
            void play(const std::string& animation, bool loop=true);
            Animation& getAnimation() const;

			const math::Vector3D& getPosition() const;
            const math::Vector3D& getLooking() const;
            float getRotation() const;

            const math::Box& getBounds() const;

        private:
            float scale;

            Animation* currentAnimation;

            std::vector<GlCommands> commands;
            std::map<std::string, Animation*> animations;

			void load(const std::string& filename, float loadScale);
            Animation* createAnimationIfNeed(const char* frameName);
            ogl::Texture texture;

    };
}

#endif // MD2MODEL_H_INCLUDED
