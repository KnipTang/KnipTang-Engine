#include "PengoState.h"

void DyingState::Enter(dae::GameObject* gameObject)
{
	Animation* animationComp = gameObject->GetComponent<Animation>();
	if (animationComp != nullptr)
	{
		animationComp->ToggleAnimation(true);

		SDL_Rect dyingRect{};
		dyingRect = { 0, 16 * 2, 16, 16 };

		animationComp->SetStartSourceRect(dyingRect);
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



void MoveState::Enter(dae::GameObject* )
{
	//gameObject->GetComponent<Animation>()->ToggleAnimation(true);
}

void MoveState::Enter(dae::GameObject* gameObject, Controlls control)
{
	//Enter(gameObject);

	Animation* animationComp = gameObject->GetComponent<Animation>();
	if (animationComp != nullptr)
	{
		if (animationComp->IsAnimating())
			return;

		animationComp->ToggleAnimation(true);

		SDL_Rect currentStartingRect = animationComp->GetCurrentSourceRect();

		switch (control)
		{
		case Controlls::UP:
			if (animationComp != nullptr)
				currentStartingRect = {16 * 4, 0, 16, 16};
			break;

		case Controlls::DOWN:
			if (animationComp != nullptr)
				currentStartingRect = { 16 * 0, 0, 16, 16 };
			break;

		case Controlls::LEFT:
			if (animationComp != nullptr)
				currentStartingRect = { 16 * 2, 0, 16, 16 };
			break;

		case Controlls::RIGHT:
			if (animationComp != nullptr)
				currentStartingRect = { 16 * 6, 0, 16, 16 };
			break;

		case Controlls::ATTACK:
			break;
		}

		animationComp->SetStartSourceRect(currentStartingRect);
	}
}

std::unique_ptr<PengoState> MoveState::HandleInput(dae::GameObject* gameObject, Controlls)
{
	return std::make_unique<MoveState>(gameObject);
}



void Idle::Enter(dae::GameObject* gameObject)
{
	gameObject->GetComponent<Animation>()->ToggleAnimation(false);
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
