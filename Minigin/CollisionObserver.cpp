#include "CollisionObserver.h"
#include "Subject.h"
#include "GameObject.h"
#include <string>
void dae::CollisionObserver::Notify(GameEvent event, Subject* actor)
{
	if (event == GameEvent::Collision)
	{
		std::string tag = actor->GetGameObject()->GetTag();

		if (tag == "Player")
		{
			std::cout << "CollisionPlayer";
		}
	}
}
