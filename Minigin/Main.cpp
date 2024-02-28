#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "Scene.h"
#include "RenderComponent.h"
#include "Transform.h"
#include "FpsComponent.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	//Background image
	auto go = std::make_shared<dae::GameObject>();
	go.get()->AddComponent(new dae::RenderComponent(go.get()));
    go.get()->GetComponent<dae::RenderComponent>()->SetTexture("background.tga");
	scene.Add(go);

	//DAE logo image
	go = std::make_shared<dae::GameObject>();
	go.get()->AddComponent(new dae::RenderComponent(go.get()));
	go.get()->GetComponent<dae::RenderComponent>()->SetTexture("logo.tga");
	go.get()->AddComponent(new dae::Transform(go.get()));
	go.get()->GetComponent<dae::Transform>()->SetPosition(216, 180);
	scene.Add(go);

	//Text
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_shared<dae::GameObject>();
	go.get()->AddComponent(new dae::Transform(go.get()));
	go.get()->GetComponent<dae::Transform>()->SetPosition(80, 20);
	go.get()->AddComponent(new dae::TextObject(go.get(),"Programming 4 Assignment", font));
	scene.Add(go);

	//FPS
	go = std::make_shared<dae::GameObject>();
	go.get()->AddComponent(new dae::Transform(go.get()));
	go.get()->GetComponent<dae::Transform>()->SetPosition(0, 70);
	go.get()->AddComponent(new dae::TextObject(go.get(), "0FPS", font));
	go.get()->AddComponent(new dae::FpsComponent(go.get(), go.get()->GetComponent<dae::TextObject>()));
	scene.Add(go);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}