#ifndef TEXTUREREADER_H
#define TEXTUREREADER_H

#include "Graphics\vertex.h"

struct TextureVertex {
	float x;
	float y;
	float z;
};

struct TextureFace
{
	int id1;
	int id2;
	int id3;
};

class TextureReader {
public:
	int numPts;
	int numFaces;
	int numVerts;


	TextureVertex vertex[5000];
	TextureVertex texCoord[5000];
	TextureFace faces[5000];
	TextureFace texfaces[5000];
	Vertex* verts;

	TextureReader();
	~TextureReader();

	void LoadVertex(char* filename);
	void LoadFace(char* filename);
	void LoadTexCoord(char* filename);
	void LoadModel(char* filename);
	void FinalVertexData();
};

#endif
