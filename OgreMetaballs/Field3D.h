#pragma once

#include "Ogre.h"

namespace Metaballs{

	//-----------------------------------
	// IField3D
	//-----------------------------------

	class IField3D
	{
	public:
		IField3D();
		virtual ~IField3D();

		virtual float Value(float x, float y, float z) = 0;
	};
}
