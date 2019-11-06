#include <GL/freeglut.h>
#include <fstream>
#include <iostream>
#include <string>

#include "Reader.h"

using namespace std;

TextureReader::TextureReader()
{
	numPts = 0;
	for (int i = 0; i < 5000; i++) {
		vertex[i].x = 0;
		vertex[i].y = 0;
		vertex[i].z = 0;

		texCoord[i].x = 0;
		texCoord[i].y = 0;
	}

	for (int i = 0; i < 5000; i++) {
		faces[i].id1 = 0;
		faces[i].id2 = 0;
		faces[i].id3 = 0;

		texfaces[i].id1 = 0;
		texfaces[i].id2 = 0;
		texfaces[i].id3 = 0;
	}
}

TextureReader::~TextureReader()
{

}

void TextureReader::LoadVertex(char* filename)
{
	ifstream file;
	file.open(filename);

	string str;

	while (!file.eof()) //while we are still in the file
	{
		getline(file, str); //move one line down
		if (str[0] == 'v'&&str[1] != 't') break; //if we have a vertex line, stop
	}

	int v = 0;

	while (str[0] == 'v'&&str[1] != 't') {

		//convert data into X,Y,Z
		str[0] = ' ';
		sscanf_s(str.c_str(), "%f %f %f",							// Read floats from the line: v X Y Z
			&vertex[v].x,
			&vertex[v].y,
			&vertex[v].z);

		v++;
		getline(file, str);
	}

	numPts = v;
}

void TextureReader::LoadTexCoord(char* filename)
{
	ifstream file;
	file.open(filename);

	string str;

	while (!file.eof()) //while we are still in the file
	{
		getline(file, str); //move one line down
		if (str[0] == 'v'&&str[1] == 't') break; //if we have a vertex line, stop
	}

	int v = 0;

	while (str[0] == 'v'&&str[1] == 't') {

		//convert data into X,Y,Z
		str[0] = ' '; str[1] = ' ';

		sscanf_s(str.c_str(), "%f %f",							// Read floats from the line: vt X Y Z
			&texCoord[v].x,
			&texCoord[v].y);

		v++;
		getline(file, str);
	}

	numPts = v;
}

void TextureReader::LoadFace(char *filename)
{
	int count;
	ifstream file;
	file.open(filename);

	string str;

	while (true)
	{
		getline(file, str);
		if (str[0] == 'f') {
			break;
		}
	}

	count = 0;
	while (str[0] == 'f')
	{
		str[0] = ' ';
		sscanf_s(str.c_str(), "%d/%d %d/%d %d/%d ",
			&faces[count].id1, &texfaces[count].id1,
			&faces[count].id2, &texfaces[count].id2,
			&faces[count].id3, &texfaces[count].id3);

		faces[count].id1--;
		faces[count].id2--;
		faces[count].id3--;

		texfaces[count].id1--;
		texfaces[count].id2--;
		texfaces[count].id3--;

		count++;

		getline(file, str);
	}

	numFaces = count;
}

void TextureReader::LoadModel(char *filename)
{
	LoadVertex(filename);
	LoadTexCoord(filename);
	LoadFace(filename);
	FinalVertexData();

}

void TextureReader::FinalVertexData()
{
	verts = new Vertex[numFaces * 3];

	int texid;
	int faceid;
	int index = 0;

	for (int i = 0; i < numFaces; ++i)
	{
		texid = texfaces[i].id1;
		faceid = faces[i].id1;
		Vertex v1;
		v1.texCoords = glm::vec2(texCoord[texid].x, texCoord[texid].y);
		v1.coords = glm::vec4(vertex[faceid].x, vertex[faceid].y, vertex[faceid].z, 1.0f);

		verts[index++] = v1;

		texid = texfaces[i].id2;
		faceid = faces[i].id2;
		Vertex v2;
		v2.texCoords = glm::vec2(texCoord[texid].x, texCoord[texid].y);
		v2.coords = glm::vec4(vertex[faceid].x, vertex[faceid].y, vertex[faceid].z, 1.0f);

		verts[index++] = v2;

		texid = texfaces[i].id3;
		faceid = faces[i].id3;
		Vertex v3;
		v3.texCoords = glm::vec2(texCoord[texid].x, texCoord[texid].y);
		v3.coords = glm::vec4(vertex[faceid].x, vertex[faceid].y, vertex[faceid].z, 1.0f);

		verts[index++] = v3;
	}
}