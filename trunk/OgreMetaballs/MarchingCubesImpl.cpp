#include "MarchingCubesImpl.h"

#include "ScalarField3D.h"
#include "DynamicMesh.h"
#include "MarchingCubesData.h"

#include "FieldHelper.h"

//-----------------------------------
// Helper
//-----------------------------------

int GetIdx3DGrid(int size, int i, int j ,int k)
{
    return i + j * size + k * size * size;
}


//-----------------------------------
// MarchingCubesImpl
//-----------------------------------

MarchingCubesImpl::MarchingCubesImpl(DynamicMesh* meshBuilder)
: m_meshBuilder(meshBuilder), m_scalarField(NULL)
{
    m_chunkDivisionLevel = 3;
}


MarchingCubesImpl::~MarchingCubesImpl()
{ 
}


void MarchingCubesImpl::Initialize(float samplingSpaceSize, float samplingResolution, float samplingThreshold)
{
	m_samplingSpaceSize = samplingSpaceSize;
	m_samplingResolution = samplingResolution;
	m_samplingThreshold = samplingThreshold;

	m_nbrSamples = ceil(m_samplingSpaceSize / m_samplingResolution);

	//Provide a loose estimate of the number of vertex and triangles in the final mesh
	m_meshBuilder->EstimateSize(m_nbrSamples * m_nbrSamples * m_nbrSamples);

	float samplingMinPos = -m_nbrSamples * m_samplingResolution / 2;

    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////

    int nbrSamples = 64;
    float sampleCubeSize = m_samplingSpaceSize / nbrSamples;
    m_gridCubeSize = sampleCubeSize;

    m_nbrChunks = 1 << (m_chunkDivisionLevel+1);
    m_nbrCubesPerChunk = nbrSamples / m_nbrChunks;

    float chunkSize = sampleCubeSize * m_nbrCubesPerChunk;

    m_samplingGridChunks.clear();
    m_samplingGridChunks.resize(m_nbrChunks * m_nbrChunks * m_nbrChunks);

    for(int i=0; i<m_nbrChunks; i++)
    {
        for(int j=0; j<m_nbrChunks; j++)
        {
            for(int k=0; k<m_nbrChunks; k++)
            {
                SamplingGridChunk& chunk = m_samplingGridChunks[GetIdx3DGrid(m_nbrChunks, i,j,k)];
                chunk.MinPos = Vector3(
                    i * chunkSize,
                    j * chunkSize,
                    k * chunkSize
                    );

                chunk.MaxPos = Vector3(
                    (i+1) * chunkSize,
                    (j+1) * chunkSize,
                    (k+1) * chunkSize
                    );

                InitializeChunk(chunk);
            }
        }
    }
}

void MarchingCubesImpl::InitializeChunk(SamplingGridChunk& chunk)
{
    chunk.Vertices.clear();
    chunk.Vertices.resize(m_nbrCubesPerChunk * m_nbrCubesPerChunk * m_nbrCubesPerChunk);

    //Iterate through every vertice in the grid
    for(int i=0; i<m_nbrCubesPerChunk; i++)
    {
        for(int j=0; j<m_nbrCubesPerChunk; j++)
        {
            for(int k=0; k<m_nbrCubesPerChunk; k++)
            {
                //Initialize the vertice to a default state
                SamplingGridVertice& vertice = chunk.Vertices[GetIdx3DGrid(m_nbrCubesPerChunk, i,j,k)];
                vertice.Position = Vector3(
                    chunk.MinPos.x + i * m_gridCubeSize,
                    chunk.MinPos.y + j * m_gridCubeSize,
                    chunk.MinPos.z + k * m_gridCubeSize);
            }
        }
    }

    chunk.Cubes.clear();
    chunk.Cubes.resize((m_nbrCubesPerChunk-1) * (m_nbrCubesPerChunk-1) * (m_nbrCubesPerChunk-1));

    for(int i=0; i<m_nbrCubesPerChunk-1; i++)
    {
        for(int j=0; j<m_nbrCubesPerChunk-1; j++)
        {			
            for(int k=0; k<m_nbrCubesPerChunk-1; k++)
            {
                SamplingGridCube& cube = chunk.Cubes[GetIdx3DGrid(m_nbrCubesPerChunk-1, i,j,k)];

                cube.Vertices[0] = &chunk.Vertices[GetIdx3DGrid(m_nbrCubesPerChunk, i  ,j+1,k)];
                cube.Vertices[1] = &chunk.Vertices[GetIdx3DGrid(m_nbrCubesPerChunk, i+1,j+1,k)];
                cube.Vertices[2] = &chunk.Vertices[GetIdx3DGrid(m_nbrCubesPerChunk, i+1,j  ,k)];
                cube.Vertices[3] = &chunk.Vertices[GetIdx3DGrid(m_nbrCubesPerChunk, i  ,j  ,k)];
                cube.Vertices[4] = &chunk.Vertices[GetIdx3DGrid(m_nbrCubesPerChunk, i  ,j+1,k+1)];
                cube.Vertices[5] = &chunk.Vertices[GetIdx3DGrid(m_nbrCubesPerChunk, i+1,j+1,k+1)];
                cube.Vertices[6] = &chunk.Vertices[GetIdx3DGrid(m_nbrCubesPerChunk, i+1,j  ,k+1)];
                cube.Vertices[7] = &chunk.Vertices[GetIdx3DGrid(m_nbrCubesPerChunk, i  ,j  ,k+1)];
            }
        }
    }
}

void MarchingCubesImpl::CreateMesh()
{
	//Begin the construction of the mesh
	GetMeshBuilder()->BeginMesh();

    ////Sample the scalar field value on each vertice of grid
    //SampleSpace();

    ResetChunksVertices();

    FieldList fields = m_fields->GetFields();
    int size = fields.size();
    for(int i=0; i<size; i++)
    {
        SampleField(fields[i]);
    }

    ////For each cube defined by the grid, emit geometry if the cube intersect the surface.
    March();

	//Add a dummy triangle to avoid empty mesh     
	Vertex v;
	m_meshBuilder->AddVertex(v);
	m_meshBuilder->AddVertex(v);
	m_meshBuilder->AddVertex(v);

	m_meshBuilder->AddTriangle(0,1,2);

	//Finalize the mesh
	GetMeshBuilder()->EndMesh();
}

void MarchingCubesImpl::SampleSpace()
{
    int size = m_samplingGridVertices.size();
    for(int i=0; i<size; i++)
	{		
		SamplingGridVertice& vertice = m_samplingGridVertices[i];
		vertice.ScalarValue =  GetScalarField()->Scalar(vertice.Position);
	}
}

void MarchingCubesImpl::ResetChunksVertices()
{
    int size = m_samplingGridChunks.size();
    for(int i=0; i<size; i++)
    {		
        SamplingGridChunk& chunk = m_samplingGridChunks[i];
        int size2 = chunk.Vertices.size();
        for(int j=0; i<size2; i++)
        {		
            SamplingGridVertice& vertice = chunk.Vertices[j];
            vertice.ScalarValue = 0;
        }
    }
}

void MarchingCubesImpl::SampleField(ScalarField3D* field)
{
    int size = m_samplingGridChunks.size();
    for(int i=0; i<size; i++)
    {		
        SamplingGridChunk& chunk = m_samplingGridChunks[i];
        if(field->BoundingBox()->Collide(AABBox(chunk.MinPos, chunk.MaxPos)))
        {
            int size2 = chunk.Vertices.size();
            for(int j=0; i<size2; i++)
            {		
                SamplingGridVertice& vertice = chunk.Vertices[j];
                vertice.ScalarValue += field->Scalar(vertice.Position);
            }
        }
    }
}

void MarchingCubesImpl::March()
{
    int size = m_samplingGridChunks.size();
    for(int i=0; i<size; i++)
    {		
        SamplingGridChunk& chunk = m_samplingGridChunks[i];
        int size2 = chunk.Cubes.size();
        for(int j=0; i<size2; i++)
        {		
            SamplingGridCube& cube = chunk.Cubes[j];
            SampleCube(cube);
        }
    }
}

void MarchingCubesImpl::SampleCube(SamplingGridCube& cube)
{
	//Build a index to determine the state of the cube. 
	//The #n bit is set to 1 if the vertice #n is inside of the surface.
	int cubeIndex = 0;
	for (int n=0; n<8; n++)
	{
		if (cube.Vertices[n]->ScalarValue <= m_samplingThreshold) 
			cubeIndex |= 1<<n;
	}

	//An edge of the cube intersect the surface if one vertice 
	// is inside of the surface and the other is outside.
	//Based on the previous index, we can use a static lookup table to get the list 
	// of vertex and triangles we need to generate.
	static Vertex meshVertex[12];
	static int vertexIdxs[12];

	//The table return a bit field in which the #n bit is set to 1 if the edge #n intersect the surface
	int intersectionList = MarchingCubesData::GetVertexList(cubeIndex);

    //For each edge of the cube
	for(int n=0; n<12; n++)
	{
		//If the edge is intersected
		if(intersectionList & 1<<n)
		{
			//Store the vertices corresponding to the edge.
			const SamplingGridVertice* cubeVertice0 = cube.Vertices[MarchingCubesData::GetVertexInEdge(n,0)];
			const SamplingGridVertice* cubeVertice1 = cube.Vertices[MarchingCubesData::GetVertexInEdge(n,1)];

			//Determine the position of the intersection along the edge by linear interpolation.
			float d0 = abs(cubeVertice0->ScalarValue - m_samplingThreshold);
			float d1 = abs(cubeVertice1->ScalarValue - m_samplingThreshold);
			float lerp = d1 / (d0+d1);

			//Generate the vertex at the intersection
			Vertex triangleVertex;
			triangleVertex.Position = lerp * cubeVertice0->Position + (1-lerp) * cubeVertice1->Position;
			triangleVertex.Normal = m_scalarField->Gradient(triangleVertex.Position);
			triangleVertex.Color = lerp * m_scalarField->Color(cubeVertice0->Position) + (1-lerp) * m_scalarField->Color(cubeVertice1->Position);
			
			triangleVertex.Normal.normalise();

			vertexIdxs[n] = GetMeshBuilder()->AddVertex(triangleVertex);
		}
	}

	//The table return an array of egde indexes, from 0 to 11, ended by a -1 value.
	//Every three edges define a triangle.
	const int* cubeEdgeArray = MarchingCubesData::GetTriangleList(cubeIndex);
	for(int n = 0; cubeEdgeArray[n] != -1; n+=3)
	{	
		GetMeshBuilder()->AddTriangle(
			vertexIdxs[cubeEdgeArray[n+1]], 
			vertexIdxs[cubeEdgeArray[n]], 
			vertexIdxs[cubeEdgeArray[n+2]]);
	}
}