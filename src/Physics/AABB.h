#pragma once
#include "Particle.h"

class AABB : Particle
{
public:
	//CONSTRUCTEURS
	
	/// <summary>
	/// Initialise une Axis-Aligned Bounding Box
	/// </summary>
	AABB();
	/// <summary>
	/// Initialise une Axis-Aligned Bounding Box avec des paramètres donnés
	/// </summary>
	/// <param name="position">Position du AABB</param>
	/// <param name="scale">Taille du AABB</param>
	/// <param name="textureID">ID de texture</param>
	AABB(Vector3D position, Vector3D scale, int textureID);
	
	//GETTERS

	float GetMinX() { return position.x - scale.x * 0.5f; };
	float GetMaxX() { return position.x + scale.x * 0.5f; };
	float GetMinY() { return position.y - scale.y * 0.5f; };
	float GetMaxY() { return position.y + scale.y * 0.5f; };
	float GetMinZ() { return position.z - scale.z * 0.5f; };
	float GetMaxZ() { return position.z + scale.z * 0.5f; };
	Vector3D GetScale() { return scale; };
	Vector3D GetPosition() { return position; };
	int GetTextureID() { return textureID; };

	//VARIABLES PRIVEES

private: 
	Vector3D scale;
	int textureID;
};

