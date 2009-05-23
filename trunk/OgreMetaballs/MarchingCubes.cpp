#include "MarchingCubes.h"

#include "ScalarField3D.h"
#include "DynamicMesh.h"
#include "MarchingCubesData.h"

//-----------------------------------
// MarchingCubes
//-----------------------------------

MarchingCubes::MarchingCubes(DynamicMesh* meshBuilder)
: m_meshBuilder(meshBuilder), m_scalarField(NULL)
{
}

MarchingCubes::~MarchingCubes()
{
}


void MarchingCubes::Initialize(float samplingSpaceSize, float samplingResolution, float samplingThreshold)
{
	m_samplingSpaceSize = samplingSpaceSize;
	m_samplingResolution = samplingResolution;
	m_samplingThreshold = samplingThreshold;

	m_nbrSamples = ceil(m_samplingSpaceSize / m_samplingResolution);

	//Provide a loose estimate of the number of vertex and triangles in the final mesh
	m_meshBuilder->EstimateSize(m_nbrSamples * m_nbrSamples * m_nbrSamples);

	float samplingMinPos = -m_nbrSamples * m_samplingResolution / 2;

	//Create and initialize the sampling grid
	m_samplingGridVertices.clear();
	m_samplingGridVertices.resize(m_nbrSamples * m_nbrSamples * m_nbrSamples);

	//Iterate through every vertice in the grid
	for(int i=0; i<m_nbrSamples; i++)
	{
		for(int j=0; j<m_nbrSamples; j++)
		{
			for(int k=0; k<m_nbrSamples; k++)
			{
				//Initialize the vertice to a default state
				SamplingGridVertice& vertice = GetGridVertice(i,j,k);
				vertice.Scalar = 0;
				vertice.Gradient = Vector3::ZERO;
				vertice.Position = Vector3(
					samplingMinPos + i * m_samplingResolution,
					samplingMinPos + j * m_samplingResolution,
					samplingMinPos + k * m_samplingResolution);
			}
		}
	}
}

void MarchingCubes::CreateMesh()
{
	//Begin the construction of the mesh
	GetMeshBuilder()->BeginMesh();

	//Sample the scalar field value on each vertice of grid
	SampleSpace();

	//For each cube defined by the grid, emit geometry if the cube intersect the surface.
	March();

	//Finalize the mesh
	GetMeshBuilder()->EndMesh();
}

void MarchingCubes::SampleSpace()
{
	for(int i=0; i<m_nbrSamples; i++)
	{
		for(int j=0; j<m_nbrSamples; j++)
		{
			for(int k=0; k<m_nbrSamples; k++)
			{
				//Get the grid vertice
				SamplingGridVertice& vertice = GetGridVertice(i,j,k);

				//Sample the field value at the vertice
				const ScalarFieldValue& sample = GetScalarField()->Sample(vertice.Position);

				vertice.Scalar = sample.Scalar;
				vertice.Gradient = sample.Gradient;
				vertice.Color = sample.Color;
			}
		}
	}
}

void MarchingCubes::March()
{
	for(int i=0; i<m_nbrSamples-1; i++)
	{
		for(int j=0; j<m_nbrSamples-1; j++)
		{
			for(int k=0; k<m_nbrSamples-1; k++)
			{
				SampleCube(j,i,k);
			}
		}
	}
}

void MarchingCubes::SampleCube(int i, int j, int k)
{
	//Store the vertices of the cube defined by i,j and k
	SamplingGridVertice* cubeVertices[8];
	cubeVertices[0] = &GetGridVertice(i  ,j+1,k);
	cubeVertices[1] = &GetGridVertice(i+1,j+1,k);
	cubeVertices[2] = &GetGridVertice(i+1,j  ,k);
	cubeVertices[3] = &GetGridVertice(i  ,j  ,k);
	cubeVertices[4] = &GetGridVertice(i  ,j+1,k+1);
	cubeVertices[5] = &GetGridVertice(i+1,j+1,k+1);
	cubeVertices[6] = &GetGridVertice(i+1,j  ,k+1);
	cubeVertices[7] = &GetGridVertice(i  ,j  ,k+1);

	//Build a index to determine the state of the cube. 
	//The #n bit is set to 1 if the vertice #n is inside of the surface.
	int cubeIndex = 0;
	for (int n=0; n<8; n++)
	{
		if (cubeVertices[n]->Scalar < m_samplingThreshold) 
			cubeIndex |= 1<<n;
	}

	//An edge of the cube intersect the surface if one vertice is inside of the surface and the other is outside.
	//Based on the previous index, we can use a static lookup table to get the list of triangles we need to generate.
	//The table return an array of egde indexes, from 0 to 11, ended by a -1 value.
	//Each three edges define a triangle.
	const int* cubeEdgeArray = GetTriangleList(cubeIndex);

	//For each intersected edges in the cube
	for(int n = 0; cubeEdgeArray[n*3] != -1; n++)
	{	
		int lastVertexIdx = 0;
		for(int m = 0; m<3; m++)
		{
			//Store the vertices corresponding to the edge.
			const SamplingGridVertice& cubeVertice0 = *cubeVertices[GetVertexInEdge(cubeEdgeArray[n*3 + m],0)];
			const SamplingGridVertice& cubeVertice1 = *cubeVertices[GetVertexInEdge(cubeEdgeArray[n*3 + m],1)];

			//Determine the position of the intersection along the edge by linear interpolation.
			float d0 = abs(cubeVertice0.Scalar - m_samplingThreshold);
			float d1 = abs(cubeVertice1.Scalar - m_samplingThreshold);
			float lerp = d1 / (d0+d1);

			//Generate a vertex at the intersection
			Vertex triangleVertex;
			triangleVertex.Position = lerp * cubeVertice0.Position + (1-lerp) * cubeVertice1.Position;
			triangleVertex.Normal = lerp * cubeVertice0.Gradient + (1-lerp) * cubeVertice1.Gradient;
			triangleVertex.Color = lerp * cubeVertice0.Color + (1-lerp) * cubeVertice1.Color;

			triangleVertex.Normal.normalise();

			//Add the vertex to the mesh
			lastVertexIdx = GetMeshBuilder()->AddVertex(triangleVertex);
		}

		//For every three vertex, add a triangle to the mesh
		GetMeshBuilder()->AddTriangle(lastVertexIdx-1, lastVertexIdx-2, lastVertexIdx);
	}
}

SamplingGridVertice& MarchingCubes::GetGridVertice(int i, int j, int k)
{
	int idx = i + j * m_nbrSamples + k * m_nbrSamples * m_nbrSamples;
	return m_samplingGridVertices[idx];
}