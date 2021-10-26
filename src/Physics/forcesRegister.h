#ifndef FORCESREGISTER_H
#define FORCESREGISTER_H

#include "particleForceGenerator.h"
#include <vector>

struct ForceEntry
{
	/// <summary>
	/// Particule à entrer dans le registre
	/// </summary>
	Particle* particle;

	/// <summary>
	/// Générateur de force appliquant une force à la particule
	/// </summary>
	ParticleForceGenerator* generator;
};

class ForcesRegister
{
public:
	//CONSTRUCTEUR

	/// <summary>
	/// Crée un registre de forces
	/// </summary>
	ForcesRegister();

	//FONCTIONS

	/// <summary>
	/// Ajoute une force au registre des forces pour une particule
	/// </summary>
	/// <param name="particle">Particule sur laquelle appliquer la force</param>
	/// <param name="generator">Générateur de force a appliquer</param>
	void AddEntry(Particle* particle, ParticleForceGenerator* generator);
	
	/// <summary>
	/// Supprime les entrées liées à une particule
	/// </summary>
	/// <param name="p">Particule dont les entrées doivent être supprimées</param>
	void DeleteParticle(Particle* p);
	
	/// <summary>
	/// Fonction d'application des forces
	/// </summary>
	/// <param name="deltaTime">Temps de la simulation</param>
	void Update(float deltaTime);

	//VARIABLES

	/// <summary>
	/// Registre des forces
	/// </summary>
	std::vector<ForceEntry> forces;
};
#endif

