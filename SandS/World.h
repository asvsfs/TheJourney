#pragma once
#include "stdafx.h"
#include "Singleton.h"
#include <vector>
#include "noise\noise.h"
class Container;
class Chunk;
class World :public CSingleton<World>
{
public:
	World();
	~World();

	Container** mContainers; 

	int ContainerSize;
	int numberOfContainersX;
	int numberOfContainersY;
	int numberOfContainersZ;

	bool bFrameDelay;

	std::vector<int> data;
	std::vector<Container*> mActiveContainers;

	BYTE* dataAll ;

	Ogre::Camera * mPlayer;

	noise::module::Perlin* Noise;

public:
	void LoadContainers(Ogre::Vector3 playerPos, float distToLoad, float distToUnload);
	void Update();

	int PerlinNoise(int x, int y, int z, float scale, float height, float power);


};