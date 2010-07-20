#include "Animation.h"

#include <SDL.h>

namespace md2
{

Animation::Animation(const std::string& _name, float _speed, bool _loop)
: name(_name), fps(_speed), loop(_loop), currentFrame(0.0), playing(false), lastTicks(0.0f)
{
}

void Animation::readFrame(std::istream &stream, int numVertices, const Md2Frame_t &frameHeader, float scale)
{
	frames.push_back(Frame(stream, numVertices, frameHeader, scale));
}

void Animation::process()
{
    if (!playing)
        return;

    //Calculate the time between the last and this frame, in milliseconds
    float ticks = lastTicks == 0 ? 0 : SDL_GetTicks() - lastTicks;
    lastTicks = static_cast<float>(SDL_GetTicks());

    ticks /= 1000;  //1000 ticks = 1 sec.

    //Skip update frame position
    currentFrame += ticks * fps;

    if (currentFrame >= size())
    {
        if (loop)
        {
            //Rewind if must loop
            while (currentFrame >= size())
                currentFrame -= size();
        }
        else
        {
            //Stop animation if should not loop
            playing = false;
            currentFrame = static_cast<float>(size()-1);
            return;
        }
    }
}

void Animation::draw(const std::vector<GlCommands> &commands, bool interpolate) const
{
    unsigned frame = static_cast<unsigned>(currentFrame); //Gets the frame index
    float interpolation = currentFrame - frame;

    if (frame == size())
        frame = 0;
	
    if ((interpolation == 0) || (!interpolate))
    {
        frames[frame].draw(commands);
    }
    else
    {
        frames[frame].draw(commands, frame == size()-1 ? frames[0] : frames[frame+1], interpolation);
    }
}

void Animation::reset()
{
    currentFrame = 0.0f;
    lastTicks = 0;
}

void Animation::setPlaying(bool play)
{
    playing = play;
}

bool Animation::isPlaying() const
{
    return playing;
}

void Animation::setPosition(float position)
{
    if (position > size()-1)
        throw std::out_of_range("Position bigger than last frame!");
    if (position < 0.0f)
        throw std::out_of_range("Position smaller than one!");

    currentFrame = position;
}

void Animation::setLoop(bool willLoop)
{
    loop = willLoop;
}

bool Animation::isLooping() const
{
    return loop;
}


void Animation::setSpeed(float speed)
{
    fps = speed;
}

float Animation::getSpeed() const
{
    return fps;
}

const std::string& Animation::getName() const
{
    return name;
}

unsigned Animation::size() const
{
    return frames.size();
}

float Animation::getPosition() const
{
    return currentFrame;
}

const math::Box& Animation::getBounds() const
{
    return frames[static_cast<int>(currentFrame)].getBounds();
}
}