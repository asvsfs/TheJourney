#include "stdafx.h"
#include "World.h"
#include "container.h"
#include "chunk.h"
#include "WorldSetting.h"
#include "BasicTutorial2.h"

using namespace Ogre;
World::~World()
{
}
int World::PerlinNoise(int x, int y, int z, float scale, float height, float power)
{
	float rValue;
	rValue = Noise->GetValue(((double)x) / scale, ((double)y) / scale, ((double)z) / scale);
	rValue *= height;

	if (power != 0)
	{
		rValue = Math::Pow(rValue, power);
	}

	return (int)rValue;
}

World::World()
{
	bFrameDelay = true;

	numberOfContainersX = Math::IFloor(WorldSetting::WorldBlockSizeX / WorldSetting::ContainerBlockSizeX);
	numberOfContainersY = Math::IFloor(WorldSetting::WorldBlockSizeY / WorldSetting::ContainerBlockSizeY);
	numberOfContainersZ = Math::IFloor(WorldSetting::WorldBlockSizeZ / WorldSetting::ContainerBlockSizeZ);

	ContainerSize = numberOfContainersX * numberOfContainersY * numberOfContainersZ;
	mContainers = new Container*[ContainerSize];

	for (int x = 0; x < numberOfContainersX; x++)
	{
		for (int z = 0; z < numberOfContainersZ; z++)
		{
			for (int y = 0; y < numberOfContainersY; y++)
			{
				int index = x + numberOfContainersX * (y + numberOfContainersY * z);
				mContainers[x + numberOfContainersX * (y + numberOfContainersY * z)] = new Container(x * WorldSetting::ContainerBlockSizeX, y * WorldSetting::ContainerBlockSizeY, z * WorldSetting::ContainerBlockSizeZ);
			}
		}

	}
	mPlayer = BasicTutorial2::Instance().mCameraMan->getCamera();
}
 
void World::LoadContainers(Vector3 playerPos, float distToLoad, float distToUnload)
{
    for (int i = 0; i < ContainerSize; i++)
    {
		float dist = Vector2(mContainers[i]->worldPos.x, mContainers[i]->worldPos.z).distance(Vector2(playerPos.x, playerPos.z));
		
		if( dist< distToLoad)
		{
			mContainers[i]->Load();
		}else if ( dist > distToUnload)
		{
			mContainers[i]->UnLoad();
		}
    }

}
void World::Update()
{
	if(bFrameDelay)
	{
		LoadContainers(mPlayer->getPosition(), 400, 500);
	}
	bFrameDelay = !bFrameDelay;

    for (int i = 0; i < ContainerSize; i++)
    {
        mContainers[i]->Update();
    }
    return;
}


