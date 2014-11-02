#include "stdafx.h"
#include "Container.h"
#include "WorldSetting.h"
#include "Chunk.h"
#include "BasicTutorial2.h"
#include "noise\noise.h"
using namespace Ogre;

Container::Container(int x ,int y,int z)
{
	mData = NULL;
	loaded = false;
	bShow = false;
	cointainerBlockSizeX = WorldSetting::ContainerBlockSizeX;
	cointainerBlockSizeY = WorldSetting::ContainerBlockSizeY;
	cointainerBlockSizeZ = WorldSetting::ContainerBlockSizeZ;

	numberOfChunkX = cointainerBlockSizeX / WorldSetting::ChunkBlockSizeX ;
	numberOfChunkY = cointainerBlockSizeY / WorldSetting::ChunkBlockSizeY ;
	numberOfChunkZ = cointainerBlockSizeZ / WorldSetting::ChunkBlockSizeZ ;

	if(mChunks.size() <1)
	{
		uint size = numberOfChunkX*numberOfChunkY*numberOfChunkZ;
		mChunks.resize(size);
		for(int i =0 ; i < size ; i++)
		{
			mChunks[i] = NULL;
		}
			
	}

	worldPos = Vector3(x,y,z);
	player = BasicTutorial2::Instance().mCamera;

	Noise = new noise::module::Perlin();   
}
Container::~Container()
{
}
void Container::GenerateContainer()
{
	loaded = false;
	
	if(mData == NULL)
	{
		mData = new BYTE[cointainerBlockSizeX * cointainerBlockSizeY * cointainerBlockSizeZ];

		tbb::parallel_for(0,cointainerBlockSizeX,[=](size_t x){
			for(int z =0 ; z < cointainerBlockSizeZ; z++)
			{
				
				int stone = PerlinNoise(Ogre::Math::IFloor(x + worldPos.x), Ogre::Math::IFloor(0 + worldPos.y), Ogre::Math::IFloor(z + worldPos.z), 100, 25, 1.0f);
				stone += PerlinNoise(Ogre::Math::IFloor(x + worldPos.x),  Ogre::Math::IFloor(100 + worldPos.y),  Ogre::Math::IFloor(z + worldPos.z), 20, 4, 0) + 10;
				int dirt = PerlinNoise(Ogre::Math::IFloor(x + worldPos.x),  Ogre::Math::IFloor(100 + worldPos.y), Ogre::Math::IFloor(z + worldPos.z), 50, 3, 0) + 1;
				for(int y = 0 ; y < cointainerBlockSizeY ; y++)
				{
					if (y <= stone)
					{
						mData[x + cointainerBlockSizeX * (y + cointainerBlockSizeY * z)] = 1;
					}
					else if (y <= dirt + stone)
					{
						mData[x + cointainerBlockSizeX * (y + cointainerBlockSizeY * z)] = 2;
					}
					
				}
			}
		});
	}

	loaded = true;
}
void Container::Update()
{
	if(!loaded)
		return;
	
        if (columnToLoad.size() > 0)
        {
            GenColumn(columnToLoad.back().x, columnToLoad.back().y);
            columnToLoad.pop_back();
        }
        
        if (columnToLoad.size() < 1)
        {
			LoadChunks(player->getPosition(), 250, 300);
        }

		for(int i =0 ; i < numberOfChunkX;i++)
		{
			for(int j = 0 ; j < numberOfChunkZ; j++)
			{
			if(mChunks[i + numberOfChunkX * (0 + numberOfChunkY * j)]!=NULL)
				mChunks[i + numberOfChunkX * (0 + numberOfChunkY * j)]->Update();
			}
		}
}

void Container::Load()
{
	if(bShow)
		return;

	bShow = true;

	GenerateContainer();
}
void Container::UnLoad()
{
	if(!bShow)
		return;

	if(mData != NULL)
	{
		delete[] mData;
		mData = NULL;
	}

	loaded = false;
	bShow = false;

	for (int x = 0; x < numberOfChunkX; x++)
	{
		for (int z = 0; z < numberOfChunkZ; z++)
		{
			if( mChunks[x + numberOfChunkX * (0 + numberOfChunkY * z)]!=NULL)
				DeGenColumn(x,z);
		}
	}

}
void Container::LoadChunks(Vector3 playerPosition,float distToLoad,float distToUnload)
{
	columnToLoad.clear();
	for(int x= 0 ; x < numberOfChunkX;x++)
	{
		for(int z= 0 ; z < numberOfChunkZ;z++)
		{
			for(int y = 0 ; y < numberOfChunkY;y++)
			{
				
				float dist = Vector2(Vector2(x * WorldSetting::ChunkBlockSizeX + worldPos.x, z * WorldSetting::ChunkBlockSizeZ + worldPos.z)).distance(Vector2(playerPosition.x,playerPosition.z));
				Chunk * cc = mChunks[x + numberOfChunkX *(y + numberOfChunkY *z)];
				if(dist < distToLoad)
				{
					if(cc == NULL)
					{
						columnToLoad.push_back(Vector2(x,z));
					}
				}else if( dist > distToUnload)
				{
					if(cc != NULL)
					{
						DeGenColumn(x,z);
					}
				}

			}
		}
	}
}
void Container::GenColumn(int x , int z)
{
        int y =0;

            Chunk * newChunk = new Chunk();

			newChunk->position=  Vector3(x * WorldSetting::ChunkBlockSizeX - 0.5f + worldPos.x, worldPos.y, z * WorldSetting::ChunkBlockSizeZ - 0.5f + worldPos.z);
			mChunks[x + numberOfChunkX * (y + numberOfChunkY * z)] = newChunk;
			mChunks[x + numberOfChunkX * (y + numberOfChunkY * z)]->container = this;
			mChunks[x + numberOfChunkX * (y + numberOfChunkY * z)]->chunkX = x * WorldSetting::ChunkBlockSizeX;
			mChunks[x + numberOfChunkX * (y + numberOfChunkY * z)]->chunkY =0;// y* chunkSizeY;
			mChunks[x + numberOfChunkX * (y + numberOfChunkY * z)]->chunkZ = z * WorldSetting::ChunkBlockSizeZ;
			mChunks[x + numberOfChunkX * (y + numberOfChunkY * z)]->update = true;

			if(newChunk->mesh->getParentNode()== NULL)
				BasicTutorial2::Instance().mSceneMgr->getRootSceneNode()->attachObject(newChunk->mesh);
				
}
void Container::DeGenColumn(int x , int z)
{
for (int y = 0; y < numberOfChunkY; y++)
        {			
			mChunks[x + numberOfChunkX * (y + numberOfChunkY * z)]->mesh->detachFromParent();
			delete mChunks[x + numberOfChunkX * (y + numberOfChunkY * z)];
            mChunks[x + numberOfChunkX * (y + numberOfChunkY * z)] = NULL;
            
        }
}
int Container::PerlinNoise(int x, int y, int z, float scale, float height, float power)
{
    float rValue;
    rValue = Noise->GetValue(((double)x) / scale, ((double)y) / scale, ((double)z) / scale);
    rValue *= height;

    if (power != 0)
    {
		rValue = Ogre::Math::Pow(rValue, power);
    }

    return (int)rValue;
}

BYTE Container::Block(int x, int y, int z)
{

    if (x >= cointainerBlockSizeX || x < 0 ||y >= cointainerBlockSizeY || y < 0 || z >= cointainerBlockSizeZ || z < 0)
    {
        return (BYTE)1;
    }

    return mData[ x + cointainerBlockSizeX * (y + cointainerBlockSizeY * z)];
}