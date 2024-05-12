#include "PengoState.h"

void DyingState::Enter(dae::GameObject* gameObject)
{
	SDL_Rect currentRect{};

	Animation* animationComp = gameObject->GetComponent<Animation>();
	if (animationComp != nullptr)
	{
		currentRect = animationComp->GetCurrentSourceRect();

		currentRect.x = 0;
		currentRect.y = 16 * 2;

		animationComp->SetCurrentSourceRect(currentRect);
	}

	gameObject->RemoveComponent(gameObject->GetComponent<MovementComponent>());
}

std::unique_ptr<PengoState> DyingState::HandleInput(dae::GameObject*, Controlls)
{
	return std::make_unique<DyingState>();
}

std::unique_ptr<PengoState> DyingState::Update()
{
	std::cout << "Dying :OO\n";
	return std::make_unique<DyingState>();
}



void MoveState::Enter(dae::GameObject* gameObject)
{
	gameObject->GetComponent<Animation>()->ToggleAnimation(true);
}

void MoveState::Enter(dae::GameObject* gameObject, Controlls control)
{
	Enter(gameObject);

	SDL_Rect currentRect{};

	Animation* animationComp = gameObject->GetComponent<Animation>();
	if (animationComp != nullptr)
		currentRect = animationComp->GetCurrentSourceRect();

	switch (control)
	{
	case Controlls::UP:
		if (animationComp != nullptr)
			currentRect.x = 16 * 4;
		break;

	case Controlls::DOWN:
		if (animationComp != nullptr)
			currentRect.x = 16 * 0;
		break;

	case Controlls::LEFT:
		if (animationComp != nullptr)
			currentRect.x = 16 * 2;
		break;

	case Controlls::RIGHT:
		if (animationComp != nullptr)
			currentRect.x = 16 * 6;
		break;

	case Controlls::ATTACK:
		break;
	}

	if (animationComp != nullptr)
		animationComp->SetCurrentSourceRect(currentRect);
}

std::unique_ptr<PengoState> MoveState::HandleInput(dae::GameObject* gameObject, Controlls)
{
	return std::make_unique<MoveState>(gameObject);
}



std::unique_ptr<PengoState> Idle::HandleInput(dae::GameObject* gameObject, Controlls control)
{
	switch (control)
	{
	case Controlls::UP:

	case Controlls::DOWN:

	case Controlls::LEFT:

	case Controlls::RIGHT:
		return std::make_unique<MoveState>(gameObject, control);
		break;

	case Controlls::ATTACK:
		return std::make_unique<PushingState>();
		break;
	}

	return std::make_unique<Idle>(gameObject);
}
