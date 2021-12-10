#include "primitive.h"
#include "rigidbody.h"

Primitive::Primitive()
{
	rigidbody = NULL;
}

void Primitive::UpdateOffsetTRS(Vector3D position, Quaternion orientation, Vector3D scale)
{
	transformOffset.UpdateTRS(position, orientation, scale);
}

Matrix4 Primitive::GetTransform()
{
	return transformOffset * rigidbody->transformMatrix;
}