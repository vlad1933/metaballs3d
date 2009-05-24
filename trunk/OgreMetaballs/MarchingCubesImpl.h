#pragma once

#include "Common.h"
#include <vector>

#define USE_OPENMP 1
#if USE_OPENMP
#include "omp.h"
#endif

//-----------------------------------
// Forward declarations
//-----------------------------------

class DynamicMesh;
class ScalarField3D;

//-----------------------------------
// SamplingGridVertice
//-----------------------------------

struct SamplingGridVertice
{
	float Scalar;
	Vector3 Gradient;
	Vector3 Position;
	ColourValue Color;
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
	void CreateMesh();

	DynamicMesh* GetMeshBuilder() const { return m_meshBuilder; }
	void SetMeshBuilder(DynamicMesh* meshBuilder) { m_meshBuilder = meshBuilder; }

	const ScalarField3D* GetScalarField() const { return m_scalarField; }
	void SetScalarField(const ScalarField3D* scalarField) { m_scalarField = scalarField; }

protected:
	void SampleSpace();
	void March();
	void SampleCube(int i, int j, int k);

	SamplingGridVertice& GetGridVertice(int i, int j, int k);

private:
	float m_samplingSpaceSize;
	float m_samplingResolution;
	float m_samplingThreshold;

	int m_nbrSamples;

	std::vector<SamplingGridVertice> m_samplingGridVertices;

	DynamicMesh* m_meshBuilder;
	const ScalarField3D* m_scalarField;	
};
