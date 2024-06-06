#include "Component.h"
#include "HealthComponent.h"

class DisplayLivesComponent : public dae::Component
{
public:
	void Render() const override;

	DisplayLivesComponent(dae::GameObject* gameObject, HealthComponent*) : Component(gameObject)
	{
		
	}
	virtual ~DisplayLivesComponent() = default;
	DisplayLivesComponent(const DisplayLivesComponent& other) = delete;
	DisplayLivesComponent(DisplayLivesComponent&& other) = delete;
	DisplayLivesComponent& operator=(const DisplayLivesComponent& other) = delete;
	DisplayLivesComponent& operator=(DisplayLivesComponent&& other) = delete;

private:
};
