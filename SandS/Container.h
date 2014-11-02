#pragma once
#include "stdafx.h"
#include <vector>
#include "noise\noise.h"
class Chunk;
class Container
{
public :
	int numberOfChunkX ;
    int numberOfChunkY ;
    int numberOfChunkZ ;

    int cointainerBlockSizeX ;
    int cointainerBlockSizeY ;
    int cointainerBlockSizeZ ;

	Container(int x ,int y,int z);
	~Container();

	void GenerateContainer();
	void Load();
	void UnLoad();
	void LoadChunks(Ogre::Vector3 playerPosition,float distToLoad,float distToUnload);
	void Update();
	void GenColumn(int x , int y);
	void DeGenColumn(int x , int y);

	int PerlinNoise(int x, int y, int z, float scale, float height, float power);
	
	BYTE Block(int x, int y, int z);

	bool loaded;
	bool bShow;
	
	BYTE * mData;

	std::vector<Ogre::Vector2> columnToLoad;
	std::vector<Chunk*> mChunks;

	Ogre::Vector3 worldPos;

	Ogre::Camera *player;

	noise::module::Perlin * Noise;

};