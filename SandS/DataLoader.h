#pragma once

#include "stdafx.h"
#include "Singleton.h"
#include <vector>
#include "noise\noise.h"
#include <thread>
#include <atomic>
class Chunk;
class Container;
class DataLoader :public CSingleton<DataLoader>
{
public : 
	DataLoader();
	~DataLoader();

	int PerlinNoise(int x, int y, int z, float scale, float height, float power);

	void LoadData(BYTE* data,Ogre::Vector3 worldPos,Container * cont);
	void Update();

	//void LoadChunk(std::vector<Chunk *>* chunkArray);
	//void UpdateChunks();
	//void GenColumn(int x, int z);
    //void UnloadColumn(int x, int z);
	//void LoadChunks(Ogre::Vector3 playerPos, float distToLoad, float distToUnload);

	std::atomic<bool> isThreadRunning;
	//std::atomic<bool> isChunkThreadRunning;
	//VAR
	noise::module::Perlin* Noise;

	std::thread LoadingThread;

	std::vector<BYTE*> mDatas;
	//std::vector<std::vector<Chunk*>* > mChunkArrays;
	std::vector<Ogre::Vector3> worldPoses;
	std::vector<class Container*> pContainers;

	//std::vector<Ogre::Vector2> columnToLoad;
    //std::vector<Ogre::Vector2> columnToUnload;
};