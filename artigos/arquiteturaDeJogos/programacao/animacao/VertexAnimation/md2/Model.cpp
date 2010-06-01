#include "Model.h"

#include <fstream>
#include <vector>

#include "md2.h"


using namespace md2;
using namespace std;

Model::Model(const string& filename, const string& texFilename, float loadScale): 
	currentAnimation(NULL), 
	texture(texFilename),
	fInterpolate(true)
{
    load(filename, loadScale);
}

void Model::load(const string& filename, float loadScale)
{
    /* ------------- STEP 1. READ FILE INFORMATION ------------- */
    Md2Header_t header;

    std::ifstream file (filename.c_str (), std::ios::binary);

    if (file.fail())
        throw std::runtime_error("Couldn't open file: '" + filename + "'");

    // Read header
    file.read (reinterpret_cast<char *>(&header), sizeof (Md2Header_t));

    if (header.ident != MD2_MAGIC_NUMBER)
        throw std::runtime_error("Invalid magic number when loading '" +
            filename + "' md2 file!");

    if (header.version != MD2_VERSION)
        throw std::runtime_error("Invalid md2 version in '" + filename
        + "' file!");

	//Read frames and animations
	file.seekg (header.offsetFrames, std::ios::beg);
	for(int i = 0;i < header.numFrames; ++i)
	{
		Md2Frame_t frame;

		file.read(reinterpret_cast<char*>(&frame), sizeof(frame));

		Animation* animation = createAnimationIfNeed(frame.name);
		animation->readFrame(file, header.numVertices, frame, loadScale);
	}

	// Read OpenGL commands
	std::vector<GlCmd> glCmds(header.numGlCmds);   
    file.seekg (header.offsetGlCmds, std::ios::beg);
    file.read (reinterpret_cast<char*>(&glCmds[0]), sizeof (GlCmd) * header.numGlCmds);

    file.close();

    //Loads OpenGL commands.
    int *pGlCmds = &glCmds[0];
    int number = glCmds[0];
    pGlCmds++;

    while (number != 0)
    {
        GLenum kind;

        if (number > 0)
            kind = GL_TRIANGLE_STRIP;
        else
        {
            kind = GL_TRIANGLE_FAN;
            number = -number;
        }

        GlCommands command(kind);

        for (int j = 0; j < number; j++)
        {
            Md2Glcmd_t* cmd = reinterpret_cast<Md2Glcmd_t*>(pGlCmds);
            command.add(GlCommandVertex(cmd->s, cmd->t, cmd->index));
            pGlCmds += 3; //Since we read integers, jump the index 3 positions forward.
        }

        commands.push_back(command);

        number = *pGlCmds; //Read the next number of commands.
        pGlCmds++; //Advance another position.
    }
}

Animation* Model::createAnimationIfNeed(const char* frameName)
{
    string name(frameName);

    int pos = name.find_first_of("0123456789");
    if (name.rfind("death") != string::npos &&
        name.rfind("crdeath") == string::npos)
        pos++;

    name = name.substr(0, pos);

    //No animation with this name?
    //Create one and add it to the map
	AnimationMap_t::iterator it = animations.find(name);
    if (it == animations.end())
    {
        Animation* animation = new Animation(name);
		animations.insert(std::make_pair(name, animation));        
        if (currentAnimation == NULL)
            currentAnimation = animation;

		return animation;
    }

    //Return the animation
    return it->second;
}

void Model::process()
{
    currentAnimation->process();
}

void Model::draw() const
{
    texture.bind();

	glPushMatrix();
	glPushAttrib(GL_POLYGON_BIT);
    currentAnimation->draw(commands, fInterpolate);
	glPopAttrib();
	glPopMatrix();
    texture.release();
}

void Model::setAnimation(Animation *animation, bool playing, bool looping)
{
	currentAnimation = animation;
    currentAnimation->reset();
    currentAnimation->setPlaying(playing);
    currentAnimation->setLoop(looping);
}

void Model::setAnimation(const string& name, bool playing, bool looping)
{
	AnimationMap_t::iterator it = animations.find(name);
    if (it == animations.end())
        throw std::invalid_argument("Invalid animation name: " + name);

	this->setAnimation(it->second, playing, looping);    
}

void Model::play(const string& animation, bool loop)
{
    setAnimation(animation, true, loop);
}

Animation& Model::getAnimation() const
{
    return *currentAnimation;
}

void Model::playNextAnimation()
{
	AnimationMap_t::iterator it = animations.find(currentAnimation->getName());
	++it;
	if(it == animations.end())
		it = animations.begin();

	this->setAnimation(it->second, true, true);
}

void Model::playPreviousAnimation()
{
	AnimationMap_t::iterator it = animations.find(currentAnimation->getName());
	if(it == animations.begin())
		it = animations.end();

	--it;
	this->setAnimation(it->second, true, true);
}

const math::Box& Model::getBounds() const
{
    return getAnimation().getBounds();
}

Model::~Model()
{
    for(std::map<string, Animation*>::iterator it = animations.begin(); it != animations.end(); it++)
        delete (*it).second;
}
