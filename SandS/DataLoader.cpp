#include "stdafx.h"
#include "DataLoader.h"
#include "WorldSetting.h"
#include "World.h"
#include "Container.h"
#include "BasicTutorial2.h"
#include "Chunk.h"
using namespace Ogre;
DataLoader::DataLoader()
{
	Noise = new noise::module::Perlin();   
	isThreadRunning = true;
	LoadingThread = std::thread(&DataLoader::Update,this);
	LoadingThread.detach();
}
DataLoader::~DataLoader()
{

}
void DataLoader::Update()
{
	while(true)
	{
		if(mDatas.size() >0)
		{
			for(int i = 0 ; i < mDatas.size() ; i++)
			{

				BYTE* data = mDatas[i];
				Vector3 worldPos = worldPoses[i];
				for (int x = 0; x < WorldSetting::ContainerBlockSizeX; x++)
				{
					for (int z = 0; z < WorldSetting::ContainerBlockSizeZ; z++)
					{
						int stone = PerlinNoise(Math::Floor(x + worldPos.x), Math::Floor(0 + worldPos.y), Math::Floor(z + worldPos.z), 100, 25, 1.0f);
						stone += PerlinNoise(Math::Floor(x + worldPos.x),  Math::Floor(100 + worldPos.y),  Math::Floor(z + worldPos.z), 20, 4, 0) + 10;
						int dirt = PerlinNoise(Math::Floor(x + worldPos.x),  Math::Floor(100 + worldPos.y),  Math::Floor(z + worldPos.z), 50, 3, 0) + 1;
						
						for (int y = 0; y < WorldSetting::ContainerBlockSizeY; y++)
						{

							if (y <= stone)
							{
								data[x + WorldSetting::ContainerBlockSizeX * (y + WorldSetting::ContainerBlockSizeY * z)] = 1;
							}
							else if (y <= dirt + stone)
							{
								data[x + WorldSetting::ContainerBlockSizeX * (y + WorldSetting::ContainerBlockSizeY * z)] = 2;
							}else
							{
							   data[x + WorldSetting::ContainerBlockSizeX * (y + WorldSetting::ContainerBlockSizeY * z)] = 0;
							}
						}
					}
				}
				pContainers[i]->loaded = true;
			}
			mDatas.clear();
			pContainers.clear();
			worldPoses.clear();
		}else
		{
			//!
			isThreadRunning = false;
			return;
		}
	}
}
void DataLoader::LoadData(BYTE* data,Vector3 worldPos,Container * cont)
{
		if(data != NULL)
		{
			//this is important to first push worldpos because mData is processing in other thread so thread will go over worldpos before it has any member
			worldPoses.push_back(worldPos);
			pContainers.push_back(cont);
			mDatas.push_back(data);

			if(isThreadRunning == false)
			{
				isThreadRunning = true;
				LoadingThread = std::thread(&DataLoader::Update,this);
				LoadingThread.detach();
			}
		}
		
}

int DataLoader::PerlinNoise(int x, int y, int z, float scale, float height, float power)
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