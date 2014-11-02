#include "stdafx.h"
#include "Chunk.h"
#include "WorldSetting.h"
#include "Container.h"
#include "BasicTutorial2.h"

using namespace Ogre;

int Chunk::s_ChunkID = 0;

Vector2 Chunk::tStone =  Vector2(0, 0);
Vector2 Chunk::tGrass =  Vector2(3, 0);
Vector2 Chunk::tDirt =  Vector2(1, 0);
Vector2 Chunk::tGrassTop =  Vector2(2, 0);
Vector2 Chunk::tWater =  Vector2(0, 1);

int Chunk::chunkSizeX = 0;
int Chunk::chunkSizeY = 0;
int Chunk::chunkSizeZ = 0;


MemPool::CMemoryPool * Chunk::s_ptrMemPool = new MemPool::CMemoryPool();

void Chunk::LateUpdate()
    {
        if (update)
        {
            GenerateMesh();
            update = false;
        }
    }
    // Use this for initialization
	Chunk::~Chunk()
	{
		delete mesh;
	}
    Chunk::Chunk()
    {
		update = false;

		chunkX = 0 ;
		chunkY = 0 ;
		chunkZ = 0 ;

		chunkSizeX = WorldSetting::ChunkBlockSizeX;
		chunkSizeY = WorldSetting::ChunkBlockSizeY;
		chunkSizeZ = WorldSetting::ChunkBlockSizeZ;

		mesh = new Ogre::ManualObject("Chunk" + Ogre::StringConverter::toString(s_ChunkID));

		s_ChunkID++;
		faceCount = 0 ;
    }
	void Chunk::Init()
	{
		if(bInit == true)
			return;

		bInit = true;		
	}
	void Chunk::GenerateMesh()
    {

		int iVertex = 0;
		mesh->begin("BoxColor");
        for (int x = 0; x < chunkSizeX; x++)
        {
            for (int y = 0; y < chunkSizeY; y++)
            {
                for (int z = 0; z < chunkSizeZ; z++)
                {
                    //This code will run for every block in the chunk

                    if (Block(x, y, z) != 0)
                    {
                        if (Block(x, y + 1, z) == 0)
                        {
                            //Block above is air
                            //CubeTop(x, y, z, Block(x, y, z));
							mesh->position(x + position.x,   y+1 + position.y, z+1 + position.z);		mesh->normal(0,1,0); mesh->textureCoord(0, 1);
							mesh->position(x+1 + position.x, y+1 + position.y, z+1 + position.z);		mesh->normal(0,1,0); mesh->textureCoord(1, 1);
							mesh->position(x+1 + position.x, y+1 + position.y, z + position.z);		mesh->normal(0,1,0); mesh->textureCoord(1, 0);
							mesh->position(x + position.x,   y+1 + position.y, z + position.z);		mesh->normal(0,1,0); mesh->textureCoord(0, 0);
 
							mesh->triangle(iVertex, iVertex+1, iVertex+2);
							mesh->triangle(iVertex+2, iVertex+3, iVertex);
 
							iVertex += 4;
							
                        }

                        if (Block(x, y - 1, z) == 0)
                        {
                            //Block below is air
                           // CubeBot(x, y, z, Block(x, y, z));
							mesh->position(x + position.x,   y + position.y, z + position.z);		mesh->normal(0,-1,0); mesh->textureCoord(0, 1);
							mesh->position(x+1 + position.x, y + position.y, z + position.z);		mesh->normal(0,-1,0); mesh->textureCoord(1, 1);
							mesh->position(x+1 + position.x, y + position.y, z+1 + position.z);	mesh->normal(0,-1,0); mesh->textureCoord(1, 0);
							mesh->position(x + position.x,   y + position.y, z+1 + position.z);	mesh->normal(0,-1,0); mesh->textureCoord(0, 0);
 
							mesh->triangle(iVertex, iVertex+1, iVertex+2);
							mesh->triangle(iVertex+2, iVertex+3, iVertex);
 
							iVertex += 4;
                        }

                        if (Block(x + 1, y, z) == 0)
                        {
                            //Block east is air
                            //CubeEast(x, y, z, Block(x, y, z));
							mesh->position(x+1 + position.x, y + position.y,   z + position.z);	mesh->normal(1,0,0); mesh->textureCoord(0, 1);
							mesh->position(x+1 + position.x, y+1 + position.y, z + position.z);	mesh->normal(1,0,0); mesh->textureCoord(1, 1);
							mesh->position(x+1 + position.x, y+1 + position.y, z+1 + position.z);	mesh->normal(1,0,0); mesh->textureCoord(1, 0);
							mesh->position(x+1 + position.x, y + position.y,   z+1 + position.z);	mesh->normal(1,0,0); mesh->textureCoord(0, 0);
 
							mesh->triangle(iVertex, iVertex+1, iVertex+2);
							mesh->triangle(iVertex+2, iVertex+3, iVertex);
 
							iVertex += 4;
                        }

                        if (Block(x - 1, y, z) == 0)
                        {
                            //Block west is air
                            //CubeWest(x, y, z, Block(x, y, z));
							mesh->position(x + position.x, y + position.y,   z+1 + position.z);	mesh->normal(-1,0,0);	mesh->textureCoord(0, 1);
							mesh->position(x + position.x, y+1 + position.y, z+1 + position.z);	mesh->normal(-1,0,0);	mesh->textureCoord(1, 1);
							mesh->position(x + position.x, y+1 + position.y, z + position.z);		mesh->normal(-1,0,0);	mesh->textureCoord(1, 0);
							mesh->position(x + position.x, y + position.y,   z + position.z);		mesh->normal(-1,0,0);	mesh->textureCoord(0, 0);
 
							mesh->triangle(iVertex, iVertex+1, iVertex+2);
							mesh->triangle(iVertex+2, iVertex+3, iVertex);
 
							iVertex += 4;
                        }

                        if (Block(x, y, z + 1) == 0)
                        {
                            //Block north is air
                            //CubeNorth(x, y, z, Block(x, y, z));
							mesh->position(x + position.x,   y + position.y,   z+1 + position.z);		mesh->normal(0,0,1); mesh->textureCoord(0, 1);
							mesh->position(x+1 + position.x, y + position.y,   z+1 + position.z);		mesh->normal(0,0,1); mesh->textureCoord(1, 1);
							mesh->position(x+1 + position.x, y+1 + position.y, z+1 + position.z);		mesh->normal(0,0,1); mesh->textureCoord(1, 0);
							mesh->position(x + position.x,   y+1 + position.y, z+1 + position.z);		mesh->normal(0,0,1); mesh->textureCoord(0, 0);
 
							mesh->triangle(iVertex, iVertex+1, iVertex+2);
							mesh->triangle(iVertex+2, iVertex+3, iVertex);
 
							iVertex += 4;
                        }

                        if (Block(x, y, z - 1) == 0)
                        {
                            //Block south is air
                            //CubeSouth(x, y, z, Block(x, y, z));
							mesh->position(x + position.x,   y+1 + position.y, z + position.z);		mesh->normal(0,0,-1); mesh->textureCoord(0, 1);
							mesh->position(x+1 + position.x, y+1 + position.y, z + position.z);		mesh->normal(0,0,-1); mesh->textureCoord(1, 1);
							mesh->position(x+1 + position.x, y + position.y,   z + position.z);		mesh->normal(0,0,-1); mesh->textureCoord(1, 0);
							mesh->position(x + position.x,   y + position.y,   z + position.z);		mesh->normal(0,0,-1); mesh->textureCoord(0, 0);
 
							mesh->triangle(iVertex, iVertex+1, iVertex+2);
							mesh->triangle(iVertex+2, iVertex+3, iVertex);
 
							iVertex += 4;
                        }

                    }

                }
            }
        }

        UpdateMesh();
		mesh->end();
	}

    inline BYTE Chunk::Block(int x, int y, int z)
    {
        return container->Block(x + chunkX, y + chunkY, z + chunkZ);
    }


	//DO NOT USE THIS FUNCTION DEPRECATED 
    void Chunk::CubeTop(int x, int y, int z, BYTE block)
    {
		mesh->position(Vector3(x+position.x,y+position.y+1,z+1+position.z+1));
        mesh->position(Vector3(x+position.x, y+position.y+1, z + 1+position.z+1));
        mesh->position(Vector3(x+position.x + 1, y+position.y+1, z+position.z));
        mesh->position(Vector3(x+position.x + 1, y+position.y+1, z+position.z));
        mesh->position(Vector3(x+position.x, y+position.y+1, z+position.z));

		mesh->normal(0,1,0);
		mesh->normal(0,1,0);
		mesh->normal(0,1,0);
		mesh->normal(0,1,0);

        Vector2 texturePos =  Vector2(0, 0);

        if (Block(x, y, z) == 1)
        {
            texturePos = tStone;
        }
        else if (Block(x, y, z) == 2)
        {
            texturePos = tGrassTop;
        }

        Cube(texturePos);

    }
	//DO NOT USE THIS FUNCTION DEPRECATED 
    void Chunk::CubeNorth(int x, int y, int z, BYTE block)
    {

        mesh->position(Vector3(x+position.x , y+position.y, z+position.z + 1));
        mesh->position(Vector3(x+position.x + 1, y+position.y, z+position.z + 1));
        mesh->position(Vector3(x+position.x+1, y+position.y+1, z+position.z + 1));
        mesh->position(Vector3(x+position.x, y+position.y + 1, z+position.z + 1));

		mesh->normal(0,0,1);
		mesh->normal(0,0,1);
		mesh->normal(0,0,1);
		mesh->normal(0,0,1);

        Vector2 texturePos = Vector2(0, 0);

        if (Block(x, y, z) == 1)
        {
            texturePos = tStone;
        }
        else if (Block(x, y, z) == 2)
        {
            texturePos = tGrass;
        }

        Cube(texturePos);

    }
	//DO NOT USE THIS FUNCTION DEPRECATED 
    void Chunk::CubeEast(int x, int y, int z, BYTE block)
    {

        mesh->position(Vector3(x+position.x + 1, y+position.y , z+position.z));
        mesh->position(Vector3(x+position.x + 1, y+position.y+1, z+position.z));
        mesh->position(Vector3(x+position.x + 1, y+position.y+1, z+position.z + 1));
        mesh->position(Vector3(x+position.x + 1, y+position.y , z+position.z + 1));

		mesh->normal(1,0,0);
		mesh->normal(1,0,0);
		mesh->normal(1,0,0);
		mesh->normal(1,0,0);

        Vector2 texturePos = Vector2(0, 0);

        if (Block(x, y, z) == 1)
        {
            texturePos = tStone;
        }
        else if (Block(x, y, z) == 2)
        {
            texturePos = tGrass;
        }

        Cube(texturePos);

    }
	//DO NOT USE THIS FUNCTION DEPRECATED 
    void Chunk::CubeSouth(int x, int y, int z, BYTE block)
    {

        mesh->position(Vector3(x+position.x, y+position.y + 1, z+position.z));
        mesh->position(Vector3(x+position.x+1, y+position.y+1, z+position.z));
        mesh->position(Vector3(x+position.x + 1, y+position.y, z+position.z));
        mesh->position(Vector3(x+position.x , y+position.y, z+position.z));

		mesh->normal(0,0,-1);
		mesh->normal(0,0,-1);
		mesh->normal(0,0,-1);
		mesh->normal(0,0,-1);

        Vector2 texturePos =  Vector2(0, 0);

        if (Block(x, y, z) == 1)
        {
            texturePos = tStone;
        }
        else if (Block(x, y, z) == 2)
        {
            texturePos = tGrass;
        }

        Cube(texturePos);

    }
	//DO NOT USE THIS FUNCTION DEPRECATED 
    void Chunk::CubeWest(int x, int y, int z, BYTE block)
    {

        mesh->position(Vector3(x+position.x, y+position.y , z+position.z + 1));
        mesh->position(Vector3(x+position.x, y+position.y+1, z+position.z + 1));
        mesh->position(Vector3(x+position.x, y+position.y+1, z+position.z));
        mesh->position(Vector3(x+position.x, y+position.y , z+position.z));

		mesh->normal(-1,0,0);
		mesh->normal(-1,0,0);
		mesh->normal(-1,0,0);
		mesh->normal(-1,0,0);

        Vector2 texturePos = Vector2(0, 0);

        if (Block(x, y, z) == 1)
        {
            texturePos = tStone;
        }
        else if (Block(x, y, z) == 2)
        {
            texturePos = tGrass;
        }

        Cube(texturePos);

    }
	//DO NOT USE THIS FUNCTION DEPRECATED 
    void Chunk::CubeBot(int x, int y, int z, BYTE block)
    {

        mesh->position(Vector3(x+position.x, y+position.y, z+position.z));
        mesh->position(Vector3(x+position.x + 1, y+position.y , z+position.z));
        mesh->position(Vector3(x+position.x + 1, y+position.y , z+position.z + 1));
        mesh->position(Vector3(x+position.x, y+position.y , z+position.z + 1));

		mesh->normal(0,-1,0);
		mesh->normal(0,-1,0);
		mesh->normal(0,-1,0);
		mesh->normal(0,-1,0);

        Vector2 texturePos = Vector2(0, 0);

        if (Block(x, y, z) == 1)
        {
            texturePos = tStone;
        }
        else if (Block(x, y, z) == 2)
        {
            texturePos = tGrass;
        }

        Cube(texturePos);

    }
	//DO NOT USE THIS FUNCTION DEPRECATED 
    void Chunk::Cube(Vector2 texturePos)
    {
		mesh->triangle(faceCount * 4,faceCount * 4 + 1,faceCount * 4 + 2);
		mesh->triangle(faceCount * 4 +2,faceCount * 4 + 3,faceCount * 4 );

        mesh->textureCoord( Vector2(tUnit * texturePos.x + tUnit, tUnit * texturePos.y));
        mesh->textureCoord( Vector2(tUnit * texturePos.x + tUnit, tUnit * texturePos.y + tUnit));
        mesh->textureCoord( Vector2(tUnit * texturePos.x, tUnit * texturePos.y + tUnit));
        mesh->textureCoord( Vector2(tUnit * texturePos.x, tUnit * texturePos.y));

        faceCount++; // Add this line
    }

    void Chunk::UpdateMesh()
    {
        faceCount = 0;
    }
	void Chunk::Update()
	{
		if (update)
        {
            GenerateMesh();
            update = false;
        }
	}