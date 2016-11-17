/*
 * Copyright (C) 2016  Spectre, Hedede
 *
 * License — WTFPL
 */
#ifndef h_RoadkillFormat
#define h_RoadkillFormat

// painstakingly deduced precious model and texture data brought to you by Spectre & HaDDayn
// latest revision at 2016.02.20

#include <aw/io/input_stream.h>
#include <vector>


namespace {

//----------------------------------------------------------
typedef signed char int8;
typedef signed short int16;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

using aw::io::input_stream;


//----------------------------------------------------------
struct rTextureHeader
{
	uint32 _constHeader;        //always 03
	uint32 format;              //mostly 09(8bit index), sometimes 0A(4bit index), or even 06 (swizzled 8bit index)
	uint32 imgWidth;            //image dimensions
	uint32 imgHeight;
	uint32 _constNull;          //always 0
	uint32 _unknownFlag;        //0 three-quarters of the time, 2 the last quarter, can't see the meaning
	uint32 _constNulls[4];      //always 0
	uint32 something;           //mostly 0x41000050, x05000050 in 4bit
	uint32 sorok;               //mostly 0x40000000, x04000000 in 4bit
	uint32 _constEighty;        //always 8000000
	uint32 _constNul[2];        //always 0
	uint32* pallete;            //bytes stored as RGBA, alpha is in 0-80 range, 16 or 256 colors depending on index format
	uint32 _constMorenulls[3];  //always 0
	uint16 someSize1;           //always somesize+1
	uint16 _constFifty;         //always 0050
	uint32 somesize;            //always width*height divided by 16 if 8bit index, and divided by 32 if 4bit
	uint32 _constEight;         //always 0x8000000
	uint32 _constNuls[2];       //always 0
	uint8* pixels;              //width*height indices into color pallete, or only twice as much with 4bit indices

	void Fill( input_stream& file ) {
		file.read( _constHeader );
		file.read( format );
		file.read( imgWidth );
		file.read( imgHeight );
		file.read( _constNulls );
		file.read( _unknownFlag );
		file.read( something );
		file.read( sorok );
		file.read( _constEighty );
		file.read( _constNul );

		uint16 amount = (format == 0x0A) ? 16 : 256;
		pallete = new uint32[ amount ];
		file.read( (char*)pallete, amount*sizeof(uint32) );

		file.read( _constMorenulls );
		file.read( someSize1 );
		file.read( _constFifty );
		file.read( somesize );
		file.read( _constEight );
		file.read( _constNuls );

		uint32 resolution = imgWidth*imgHeight;
		if( format == 0x0A ) resolution /= 2;
		pixels = new uint8[ resolution ];
		file.read( (char*)pixels, resolution );
	}

	rTextureHeader() {
		pixels = 0;
		pallete = 0;
	}
	~rTextureHeader() {
		if( pixels ) delete[] pixels;
		if( pallete ) delete[] pallete;
	}
};



//----------------------------------------------------------
class rTextureFormat
{
public:
	rTextureHeader header;

	void Load( input_stream& file ) {
		header.Fill( file );
	}
};



//----------------------------------------------------------
struct rModelBoundBox //is this really necessary?
{
	float bboxMin[3];           //boundbox dimensions, xyz min xyz max
	float bboxMax[3];

	void Fill( input_stream& file ) {
		file.read( *this );
	}
};



//----------------------------------------------------------
struct rModelHeader
{
	uint32 _constDontcare;      //always 6, model version/header i suppose
	uint32 meshCount;           //count of rModelDescriptor structs
	uint32 hasCollision;        //indicator of a rModelCollision struct presence in file
	uint32 _constNumbers[6];    //always 1, 1, 6, 0, 0, 0
	char texName[216];          //name of the used texture

	void Fill( input_stream& file ) {
		file.read( *this );
	}
};



//----------------------------------------------------------
struct rModelCollision
{
	char _constLegacy[23];      //"theLegacyCollisionPart\0"
	char _notlegacy[9];         //junk most possibly
	uint32 _constOne;           //always 1
	uint32 vertexCount;         //vertex count
	uint32 trianglesCount;      //triangles count

	float *vertexData;          //xyz triples for vertex positions, [vertexCount*3]
	int16 *triangleData;        //triples of parent vertex ids for triangles, [trianglesCount*3]

	void Fill( input_stream& file ) {
		file.read( _constLegacy );
		file.read( _notlegacy );

		file.read( _constOne );
		file.read( vertexCount );
		file.read( trianglesCount );

		vertexData = new float[ vertexCount*3 ];
		file.read( (char*)vertexData, sizeof(float) * vertexCount*3 );

		triangleData = new short[ trianglesCount*3 ];
		file.read( (char*)triangleData, sizeof(short) * trianglesCount*3 );
	}

	rModelCollision() {
		vertexData = 0;
		triangleData = 0;
	}
	~rModelCollision() {
		if( vertexData ) delete[] vertexData;
		if( triangleData ) delete[] triangleData;
	}
};



//----------------------------------------------------------
struct rModelDescriptor
{
	char meshName[16];          //not sure about lenght, haz junk after zStr occasionly, can't be shorter than 14 + \0
	char _xz[18];               //could be rest of the name
	uint32 _constTwo;           //always 02000000
	rModelBoundBox bbox;        //min and max coords for object bound box
	uint32 _constDva;           //always 02000000
	//mesh submodels packed in chunks of various size, but chunks of whole mesh
	//always aligned by 16, hence the padding in the last chunk
	uint32 chunksSize;          //size in bytes of model geometry chunks in which this mesh is described
	uint32 _constSix;           //always 06000000
	uint32 vertexCount;         //amount of vertices after welding? only shows real count if mesh has only one chunk, else - less
	uint32 trianglesCount;      //amount of triangles in the mesh
	uint32 _moosor;             //have no idea what is stored here, seems to be junk

	void Fill( input_stream& file ) {
		file.read( meshName );
		file.read( _xz );
		file.read( _constTwo );
		bbox.Fill( file );
		file.read( _constDva );
		file.read( chunksSize );
		file.read( _constSix );
		file.read( vertexCount );
		file.read( trianglesCount );
		file.read( _moosor );
	}
};



//----------------------------------------------------------
struct rModelGeometryChunk
{
	uint32 _constBold;          //always 0080016D
	uint16 HeaderVertexCount;   //amount of vertices, same as another one
	uint16 HeaderQuadsCount;    //amount of quads, same as another one
	uint16 HeaderVertex3Count;  //amount of vertex pos floats plus one, VertexCount*3+1, same as another one

	uint32 _constObogoid[2];    //always e300030100010180
	uint8 vertexCount;          //amount of vertex position triplets
	uint8 _constDick;           //always 69
	int16* vertexData;          //xyz triples for vertex positions, fixed precision / 256.0f

	uint16 _constTwelve;        //always 0280
	uint8 normalsCount;         //amount of vertex normals triplets
	uint8 _constRanen;          //always 6A
	int8* normalsData;          //triplets of vertex normals, fixed precision /128.0f

	uint16 _constThirty;        //always 0380
	uint8 uvCount;              //amount of uv position pairs
	uint8 _constOld;            //always 65
	uint16* uvData;             //uv coordinate pairs for textures, fixed precision / 4096.0f

	uint32 _constOchki;         //always 04040001
	uint8 vertex3Count;         //amount of vertex pos floats plus one, VertexCount*3+1
	uint8 _constCoc;            //always C0
	uint8 quadsCount;           //amount of triangle pair vertex ids quadruplets
	uint8 _constStalemate;      //always 6E
	uint8* quadsData;           //quads are made of paired triangles, first uses 012 ids for triangle, second 023
	//vertex ids begin with 1 and point direct into vertices float structure,
	//counting floatnum from begining and skipping by 3
	uint32 _constSeventeen;     //always 00000017

	size_t chunkSize;           //size of data for this chunk, including padding

	void Fill( std::istream& file ) {
		chunkSize = file.position();
//		chunkSize = 36;

		file.read( _constBold );
		file.read( HeaderVertexCount );
		file.read( HeaderQuadsCount );
		file.read( HeaderVertex3Count );

		file.read( _constObogoid );
		file.read( vertexCount );
		file.read( _constDick );
		unsigned char pad = 4 - ( (sizeof(short) * vertexCount*3) %4 ); pad %= 4;
		vertexData = new int16[ vertexCount*3 + pad ];
		file.read( (char*)vertexData, sizeof(short) * vertexCount*3 + pad );
//		chunkSize += sizeof(short) * vertexCount*3 + pad;

		file.read( _constTwelve, );
		file.read( normalsCount, );
		file.read( _constRanen, );
		/*unsigned char*/ pad = 4 - ( normalsCount*3 %4 ); pad %= 4;
		normalsData = new char[ normalsCount*3 + pad ];
		file.read( (char*)normalsData, normalsCount*3 + pad );
//		chunkSize += normalsCount*3 + pad;

		file.read( _constThirty );
		file.read( uvCount );
		file.read( _constOld );
		uvData = new unsigned short[ sizeof(short) * uvCount*2 ];
		file.read( (char*)uvData, sizeof(short) * uvCount*2 );
//		chunkSize += sizeof(short) * uvCount*2;

		file.read( _constOchki );
		file.read( vertex3Count );
		file.read( _constCoc );
		file.read( quadsCount );
		file.read( _constStalemate );
		quadsData = new unsigned char[ quadsCount*4 ];
		file.read( (char*)quadsData, quadsCount*4 );
//		chunkSize += quadsCount*4;
//
		file.read( _constSeventeen );

		chunkSize = chunkSize - file.position();
	}

	rModelGeometryChunk() {
		vertexData = 0;
		normalsData = 0;
		uvData = 0;
		quadsData = 0;
	}
	~rModelGeometryChunk() {
		if( vertexData ) delete[] vertexData;
		if( normalsData ) delete[] normalsData;
		if( uvData ) delete[] uvData;
		if( quadsData ) delete[] quadsData;
	}
};



//----------------------------------------------------------
class rModelFormat
{
public:
	rModelHeader header;
	rModelCollision* collision = nullptr;
	rModelBoundBox boundbox;
	std::vector<rModelDescriptor> descriptors;
	std::vector<rModelGeometryChunk*> chunks;

	void Load( input_stream& file ) {
		header.Fill( file );

		if( header.hasCollision == 1 ) {
			collision = new rModelCollision();
			collision->Fill( file );
		}

		boundbox.Fill( file );

		descriptors.resize( header.meshCount );
		for (auto& desc : descriptors)
			desc->Fill( file );

		for (auto desc : descriptors) {
			size_t sizeToRead = desc->chunksSize;
			while (sizeToRead > 16) {
				rModelGeometryChunk* chunk = new rModelGeometryChunk;
				chunk->Fill( file );
				sizeToRead -= chunk->chunkSize;
				chunks.push_back( chunk );
			}
			file.skip( sizeToRead );
		}
	}

	~rModelFormat() {
		if( collision ) delete collision;
		for( int i = 0, e = chunks.size(); i < e; i++ )
			delete chunks[i];
	}
};


} // namespace
#endif //h_RoadkillFormat
