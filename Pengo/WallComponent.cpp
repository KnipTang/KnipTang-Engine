#include "WallComponent.h"
#include "GameObject.h"

void WallComponent::DeleteWall()
{
	GetOwner()->RemoveGameObject();

	//for (int i = 0; i < GetOwner()->GetChildCount(); i++)
	//{
	//	GetOwner()->GetChildAt(i)->RemoveGameObject();
	//}
	//GetOwner()->RemoveAllChildren();
}
