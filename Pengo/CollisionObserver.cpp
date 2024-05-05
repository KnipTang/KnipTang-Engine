#include "CollisionObserver.h"
#include "Subject.h"
#include "GameObject.h"
#include <string>

void dae::CollisionObserver::Notify(GameEvent event, Subject* actor)
{
	if (event == GameEvent::Collision)
	{
		std::string tag = actor->GetGameObject()->GetTag();
		std::cout << "Begin OverLapping: " << m_pOwner->GetTag() << " With: ";

		if (tag == "Player")
		{
			std::cout << "Player\n";
		}
		else if (tag == "Enemy")
		{
			std::cout << "Enemy\n";
		}

	}
}
