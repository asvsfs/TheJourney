#pragma once
#include "stdafx.h"
#include <vector>
#include "CMemoryPool.h"
class Container;
class Chunk 
{
public:
	std::vector<Ogre::Vector3> newVertices ;
	std::vector<Ogre::Vector3> newTriangles;
	std::vector<Ogre::Vector3> newUV ;
	
	 float tUnit ;

	 static Ogre::Vector2 tStone ;//= new Vector2(0, 0);
	 static Ogre::Vector2 tGrass;// = new Vector2(3, 0);
	 static Ogre::Vector2 tDirt ;//= new Vector2(1, 0);
	 static Ogre::Vector2 tGrassTop ;//= new Vector2(2, 0);
	 static Ogre::Vector2 tWater ;//= new Vector2(0, 1);

	 Ogre::Vector3 position;
	
	Ogre::ManualObject * mesh;
	//MeshCollider col;
	
	Container * container;
	
	int faceCount;
	
	static int chunkSizeX ;// = WorldSetting.ChunkBlockSizeX;
	static int chunkSizeY ;//= WorldSetting.ChunkBlockSizeY;
	static int chunkSizeZ ;//= WorldSetting.ChunkBlockSizeZ;
	
	int chunkX;
	int chunkY;
	int chunkZ;
	
	bool update;
	bool bInit;

	void LateUpdate();
    // Use this for initialization
    Chunk();
	~Chunk();
	void Init();
    void GenerateMesh();
	
    BYTE Block(int x, int y, int z);

    void CubeTop(int x, int y, int z, BYTE block);
    void CubeNorth(int x, int y, int z, BYTE block);
    void CubeEast(int x, int y, int z, BYTE block);
    void CubeSouth(int x, int y, int z, BYTE block);
    void CubeWest(int x, int y, int z, BYTE block);
    void CubeBot(int x, int y, int z, BYTE block);

    void Cube(Ogre::Vector2 texturePos);

    void UpdateMesh();
	void Update();

	static int s_ChunkID;

	static MemPool::CMemoryPool *s_ptrMemPool;

	    void *operator new(std::size_t ObjectSize)
	{
		return s_ptrMemPool->GetMemory(ObjectSize) ;
	}

	void operator delete(void *ptrObject, std::size_t ObjectSize)
	{
		s_ptrMemPool->FreeMemory(ptrObject, ObjectSize) ;
	}
    
};