#ifndef FORCESREGISTER_H
#define FORCESREGISTER_H

#include "rigidbodyForceGenerator.h"
#include <vector>

struct ForceEntry
{
	/// <summary>
	/// Rigidbody � entrer dans le registre
	/// </summary>
	Rigidbody* rigidbody;

	/// <summary>
	/// G�n�rateur de force appliquant une force au rigigbody
	/// </summary>
	RigidbodyForceGenerator* generator;
};

class ForcesRegister
{
public:
	//CONSTRUCTEUR

	/// <summary>
	/// Cr�e un registre de forces
	/// </summary>
	ForcesRegister();

	//FONCTIONS

	/// <summary>
	/// Ajoute une force au registre des forces pour un rigidbody
	/// </summary>
	/// <param name="rigidbody">Rigidbody sur lequel appliquer la force</param>
	/// <param name="generator">G�n�rateur de force a appliquer</param>
	void AddEntry(Rigidbody* rigidbody, RigidbodyForceGenerator* generator);
	
	/// <summary>
	/// Supprime les entr�es li�es � un rigidbody
	/// </summary>
	/// <param name="p">Rigidbody dont les entr�es doivent �tre supprim�es</param>
	void Deleterigidbody(Rigidbody* p);
	
	/// <summary>
	/// Fonction d'application des forces
	/// </summary>
	/// <param name="
	/// Time">Temps de la simulation</param>
	void Update(float deltaTime);

	//VARIABLES

	/// <summary>
	/// Registre des forces
	/// </summary>
	std::vector<ForceEntry> forces;
};
#endif

