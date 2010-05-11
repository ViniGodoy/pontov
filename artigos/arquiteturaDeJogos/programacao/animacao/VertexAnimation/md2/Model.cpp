#include "Model.h"

#include <fstream>
#include <vector>

namespace md2
{
    typedef GLint GlCmd;

    typedef struct
    {
        int ident;              // Magic number, "IDP2"
        int version;            // Md2 format version, should be 8

        int skinWidth;          // Texture width
        int skinHeight;         // Texture height

        int framesize;          // Size of a frame, in bytes

        int numSkins;           // Number of skins
        int numVertices;        // Number of vertices per frame
        int numTexCoord;        // Number of texture coords
        int numTriangles;       // Number of triangles
        int numGlCmds;          // Number of OpenGL commands
        int numFrames;          // Number of frames

        int offsetSkins;        // offset to skin data
        int offsetSt;           // offset to texture coords
        int offsetTriangles;    // offset to triangle data
        int offsetFrames;       // offset to frame data
        int offsetGlCmds;       // offset to OpenGL commands
        int offsetEnd;          // offset to the end of the file
    } Md2Header_t;

    // Skin data
    typedef struct
    {
        char name[64];  // Texture's filename
    } Md2Skin_t;

// Vertex data
    typedef struct
    {
        unsigned char v[3];         // Compressed vertex position
        unsigned char normalIndex;  // Normal vector index
    } Md2Vertex_t;


// Frame data
    struct Md2Frame_t
    {
        // Destructor
        ~Md2Frame_t ()
        {
            delete [] vertices;
        }

        Vec3 scale;        // Scale factors
        Vec3 translate;    // Translation vector
        char name[16];       // Frame name
        Md2Vertex_t *vertices;  // Frames's vertex list
    } ;


// OpenGL command packet
    typedef struct
    {
        float s;    // S texture coord.
        float t;    // T texture coord.
        int index;  // Vertex index
    } Md2Glcmd_t;

    static const int MD2_MAGIC_NUMBER = 0x32504449;
    static const int MD2_VERSION = 8;
}

using namespace md2;
using namespace std;

Model::Model(const string& filename, const string& texFilename, float loadScale)
: currentAnimation(NULL), texture(texFilename)
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

    //No reading of skin, texture or triangle data, since we use OpenGL.

    // Read frames
    Md2Frame_t *frames = new Md2Frame_t[header.numFrames];

    file.seekg (header.offsetFrames, std::ios::beg);
    for (int i = 0; i < header.numFrames; i++)
    {
        // Memory allocation for the vertices of this frame
        frames[i].vertices = new Md2Vertex_t[header.numVertices];

        // Read frame data
        file.read (reinterpret_cast<char*>(&frames[i].scale), sizeof (Vec3));
        file.read (reinterpret_cast<char*>(&frames[i].translate), sizeof (Vec3));
        file.read (reinterpret_cast<char*>(&frames[i].name), sizeof (char) * 16);
        file.read (reinterpret_cast<char*>(frames[i].vertices), sizeof (Md2Vertex_t) * header.numVertices);
    }

    // Read OpenGL commands
    GlCmd* glCmds = new GlCmd[header.numGlCmds];
    file.seekg (header.offsetGlCmds, std::ios::beg);
    file.read (reinterpret_cast<char*>(glCmds), sizeof (GlCmd) * header.numGlCmds);

    file.close();

    /* ------------- STEP 2. Load information into classes -------------*/

    //Load vertices, frames and animations
    for (int i = 0; i < header.numFrames; i++)
    {
        Animation* animation = createAnimationIfNeed(frames[i].name);

        std::vector<Vertex> vertices;
        for (int j = 0; j < header.numVertices; j++)
        {
            Vertex vertex(
                (frames[i].vertices[j].v[0] * frames[i].scale[0] + frames[i].translate[0]) * loadScale,
                (frames[i].vertices[j].v[1] * frames[i].scale[1] + frames[i].translate[1]) * loadScale,
                (frames[i].vertices[j].v[2] * frames[i].scale[2] + frames[i].translate[2]) * loadScale,
                 frames[i].vertices[j].normalIndex);
            vertices.push_back(vertex);

        }
        animation->add(Frame(vertices));
    }

    //Loads OpenGL commands.
    int *pGlCmds = glCmds;
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

    /* ------------- STEP 3. Delete buffers -------------*/
    delete [] glCmds;
    delete [] frames;
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
    if (animations.find(name) == animations.end())
    {
        Animation* animation = new Animation(name);
        animations[name] = animation;
        if (currentAnimation == NULL)
            currentAnimation = animation;
    }

    //Return the animation
    return animations[name];
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
    currentAnimation->draw(commands);
	glPopAttrib();
	glPopMatrix();
    texture.release();
}

void Model::setAnimation(const string& name, bool playing, bool looping)
{
    if (animations.find(name) == animations.end())
        throw std::invalid_argument("Invalid animation name: " + name);

    currentAnimation = animations[name];
    currentAnimation->reset();
    currentAnimation->setPlaying(playing);
    currentAnimation->setLoop(looping);
}

void Model::play(const string& animation, bool loop)
{
    setAnimation(animation, true, loop);
}

Animation& Model::getAnimation() const
{
    return *currentAnimation;
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
