#include "rigidbodyContact.h"

RigidbodyContact::RigidbodyContact()
{
}

RigidbodyContact::RigidbodyContact(Rigidbody* a, Rigidbody* b, Vector3D contactNormal, float interpenetration, float coefRestitution)
{
	this->rigidbodys[0] = a;
	this->rigidbodys[1] = b;
	this->normal = contactNormal;
	this->interpenetration = interpenetration;
	this->coefRestitution = coefRestitution;
}

// Méthode pour résoudre la collision
void RigidbodyContact::Resolve()
{
	// On calcule la vitesse d'approche des deux objets
	float totalMass = rigidbodys[0]->GetInvMass() + rigidbodys[1]->GetInvMass();
	float separationVelocity = Vector3D::ScalarProduct(rigidbodys[0]->GetVelocity() - rigidbodys[1]->GetVelocity(), this->normal);
	// Si la vitesse d'approche est inférieure à zéro cela veut dire que les particules s'éloignent entre elles, 
	// donc on a déjà le comportement souhaité
	if (separationVelocity > 0) 
		return;
	
	// Sinon on calcule la vitesse de séparation pour justement les éloigner
	float separationVelocity2 = -coefRestitution * separationVelocity;
	float deltaSeparationVelocity = separationVelocity2 - separationVelocity;

	// On applique une impulsion sur les deux particules
	Vector3D impulsion = this->normal * (deltaSeparationVelocity / totalMass);

	rigidbodys[0]->SetVelocity(rigidbodys[0]->GetVelocity() + impulsion * rigidbodys[0]->GetInvMass());
	rigidbodys[1]->SetVelocity(rigidbodys[1]->GetVelocity() - impulsion * rigidbodys[1]->GetInvMass());
		
	// On résout également l'interpénétration en modifiant les positions des particules
	Vector3D correction = this->normal * (this->interpenetration / (rigidbodys[0]->GetInvMass() + rigidbodys[1]->GetInvMass()));
	rigidbodys[0]->SetPosition(rigidbodys[0]->GetPosition() + correction * rigidbodys[0]->GetInvMass());
	rigidbodys[1]->SetPosition(rigidbodys[1]->GetPosition() - correction * rigidbodys[1]->GetInvMass());
}
  