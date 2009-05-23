#pragma once

#include "Common.h"
#include <vector>

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
// MarchingCubes
//-----------------------------------

class MarchingCubes
{
public:
	MarchingCubes(DynamicMesh* meshBuilder);
	~MarchingCubes();

	void Initialize(float samplingSpaceSize, float samplingResolution, float samplingThreshold);
	void CreateMesh();

	DynamicMesh* GetMeshBuilder() const { return m_meshBuilder; }
	void SetMeshBuilder(DynamicMesh* meshBuilder) { m_meshBuilder = meshBuilder; }

	ScalarField3D* GetScalarField() const { return m_scalarField; }
	void SetScalarField(ScalarField3D* scalarField) { m_scalarField = scalarField; }

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
	ScalarField3D* m_scalarField;	
};
