#pragma once

#include "Common.h"
#include "ScalarField3D.h"
#include "FieldCollection.h"

#include <vector>

#define USE_OPENMP 0
#if USE_OPENMP
#include "omp.h"
#endif

//-----------------------------------
// Forward declarations
//-----------------------------------

class DynamicMesh;

//-----------------------------------
// SamplingGridVertice
//-----------------------------------

struct SamplingGridVertice
{
	Vector3 Position;
	float ScalarValue;
};

//-----------------------------------
// SamplingGridCube
//-----------------------------------

struct SamplingGridCube
{
	SamplingGridVertice* Vertices[8];
};

//-----------------------------------
// SamplingGridChunk
//-----------------------------------

struct SamplingGridChunk
{
    Vector3 MinPos;
    Vector3 MaxPos;
    std::vector<SamplingGridCube> Cubes;
    std::vector<SamplingGridVertice> Vertices;
};


//-----------------------------------
// MarchingCubesImpl
//-----------------------------------

class MarchingCubesImpl
{
public:
	MarchingCubesImpl(DynamicMesh* meshBuilder);
	~MarchingCubesImpl();

	void Initialize(float samplingSpaceSize, float samplingResolution, float samplingThreshold);
    void InitializeChunk(SamplingGridChunk& chunk);

    void ResetChunksVertices();

	void CreateMesh();

	DynamicMesh* GetMeshBuilder() const { return m_meshBuilder; }
	void SetMeshBuilder(DynamicMesh* meshBuilder) { m_meshBuilder = meshBuilder; }

	const ScalarField3D* GetScalarField() const { return m_scalarField; }
	void SetScalarField(const ScalarField3D* scalarField) { m_scalarField = scalarField; }

    const FieldCollection* GetFields() const { return m_fields; }
    void SetFields(const FieldCollection* fields) { m_fields = fields; }

protected:
	void SampleSpace();
    void SampleField(ScalarField3D* field);

    void March();

	void SampleCube(SamplingGridCube& cube);

private:
	float m_samplingSpaceSize;
	float m_samplingResolution;
	float m_samplingThreshold;

    int m_chunkDivisionLevel;

    int m_nbrChunks;
    int m_nbrCubesPerChunk;

    float m_gridCubeSize;

	int m_nbrSamples;


	std::vector<SamplingGridVertice> m_samplingGridVertices;
	std::vector<SamplingGridCube> m_samplingGridCubes;

    std::vector<SamplingGridChunk> m_samplingGridChunks;

	DynamicMesh* m_meshBuilder;
	const ScalarField3D* m_scalarField;	

    const FieldCollection* m_fields;
};
