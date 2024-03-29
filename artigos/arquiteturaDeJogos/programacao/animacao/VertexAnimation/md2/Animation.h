#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#include "Frame.h"
#include "md2.h"

#include <string>
#include <vector>

namespace md2
{
    class Animation
    {
        public:
            explicit Animation(const std::string& name, float _speed=5.0f, bool _loop = true);            

			void readFrame(std::istream &stream, int numVertices, const Md2Frame_t &frameHeader, float scale);

            void process();
            void draw(const std::vector<GlCommands> &commands, bool interpolate = true) const;

            void reset();

            void setPlaying(bool play);
            bool isPlaying() const;

            void setPosition(float frame);
            float getPosition() const;

            void setLoop(bool willLoop);
            bool isLooping() const;

            void setSpeed(float speed);
            float getSpeed() const;

            const std::string& getName() const;

            unsigned size() const;

            const math::Box& getBounds() const;
        private:
            std::string name;
            float fps;
            bool loop;

            float currentFrame;
            bool playing;
            float lastTicks;


            std::vector<Frame> frames;


    };
}


#endif // ANIMATION_H_INCLUDED
