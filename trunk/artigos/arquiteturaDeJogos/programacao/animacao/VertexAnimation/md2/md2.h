#ifndef MD2_H
#define MD2_H

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
        Vec3 scale;        // Scale factors
        Vec3 translate;    // Translation vector
        char name[16];       // Frame name		
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


#endif

