#include "contact.h"

Contact::Contact()
{
}

Contact::Contact(Rigidbody* a, Rigidbody* b, Vector3D contactNormal, float interpenetration, Vector3D point)
{
	this->rigidbodyA = a;
	this->rigidbodyB = b;
	this->normal = contactNormal;
	this->interpenetration = interpenetration;
	this->point = point;
}

// M�thode pour r�soudre la collision
void Contact::Resolve()
{
	// On calcule la vitesse d'approche des deux objets
	float totalMass = rigidbodyA->GetInvMass() + rigidbodyB->GetInvMass();

	//collision entre deux objets statiques
	if (totalMass == 0)
		return; //empeche les divisions par 0

	float separationVelocity = Vector3D::ScalarProduct(rigidbodyA->GetVelocity() - rigidbodyB->GetVelocity(), this->normal);
	// Si la vitesse d'approche est inf�rieure � z�ro cela veut dire que les rigidbodies s'�loignent entre eux, 
	// donc on a d�j� le comportement souhait�
	if (separationVelocity < 0) 
		return;
	
	// Sinon on calcule la vitesse de s�paration pour justement les �loigner
	float separationVelocity2 = -restitutionFactor * separationVelocity;
	float deltaSeparationVelocity = separationVelocity2 - separationVelocity;

	// On applique une impulsion sur les deux rigidbodys
	Vector3D impulsion = this->normal * (deltaSeparationVelocity / totalMass);

	rigidbodyA->AddForceAtPoint(impulsion * rigidbodyA->GetInvMass(), rigidbodyA->transformMatrix.Inverse() * this->point);
	rigidbodyB->AddForceAtPoint(-impulsion * rigidbodyB->GetInvMass(), rigidbodyB->transformMatrix.Inverse() * this->point);
		
	// On r�sout �galement l'interp�n�tration en modifiant les positions des rigidbodys
	//Vector3D correction = this->normal * (-this->interpenetration / (rigidbodyA->GetInvMass() + rigidbodyB->GetInvMass()));
	//rigidbodyA->SetPosition(rigidbodyA->GetPosition() + correction * rigidbodyA->GetInvMass());
	//rigidbodyB->SetPosition(rigidbodyB->GetPosition() - correction * rigidbodyB->GetInvMass());
}
  