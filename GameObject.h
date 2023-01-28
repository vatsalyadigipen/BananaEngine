#pragma once

#include "Camera.h"
#include "Shader.h"
#include "Object.h"

#include "Components/TransformComponent.h"
#include "Components/InputComponent.h"
#include "Components/MeshComponent.h"
#include "Components/PhysicsComponent.h"

#include <string>
#include <list>
#include <memory>

class Texture;

class GameObject : public Object
{
public:
	// Size to make the calculation easier
	glm::vec3 m_size = glm::vec3(0.0f);

private:
	std::string m_Name;	// Gameobject name

	// Components List
	std::vector<Component*> m_ComponentsList;
	
	// SceneGraph
	std::list<GameObject*> children;
	GameObject* parent = nullptr;
	
	// Texture stuff
	Texture* texture;
	unsigned int m_TextureSlot;

	// destroy gameobject flag
	bool bActive = true;

public:
	GameObject();
	GameObject(const std::string& name);

	// override from Object Class
	void BeginPlay() override;
	void Update() override;

	inline void SetObjectName(const std::string& name) { m_Name = name; }
	const std::string& GetObjectName() { return m_Name; }

	void AssignTexture(Texture* _texture, const unsigned int& _texSlot = 0U);
	// 1. SceneGraph(SG) Hierarchy Builder
	// 2. [SG Helper] Update transform if it was changed
	// 3. [SG Helper] Force update of transform even if local space don't change
	void addChild(GameObject* child);
	void updateSelfAndChild();
	void forceUpdateSelfAndChild();

	void Draw(Shader& shader, Renderer& renderer);

	// Helper Function
	// Calculates Size of each side of the shape
	void CalculateSize();
	inline const glm::vec3& GetSize() const { return m_size; }

	// Destroy Game Object
	void SetActive(bool _state);
	bool IsActive();

	/// Add, Find Components ///////////////////////////////////
	/// Transform, Input and Mesh Componenets //////////////////
	template<typename T>
	Component* AddComponent()
	{
		static_assert(false);
		return nullptr;
	}

	template<>
	Component* AddComponent<InputComponent>()
	{
		InputComponent* input_ = new InputComponent();
		if (input_) {
			input_->SetOwner(this);
			m_ComponentsList.emplace_back(input_);
			return input_;
		}
		else {
			std::cout << "Cannot create Input Component!" << std::endl;
			return nullptr;
		}
	}

	template<>
	Component* AddComponent<TransformComponent>()
	{
		TransformComponent* transform_ = new TransformComponent();
		if (transform_) {
			transform_->SetOwner(this);
			m_ComponentsList.emplace_back(transform_);
			return transform_;
		}
		else {
			std::cout << "Cannot create Transform Component!" << std::endl;
			return nullptr;
		}
	}

	template<>
	Component* AddComponent<MeshComponent>()
	{
		MeshComponent* mesh_ = new MeshComponent();
		if (mesh_ == nullptr)
			std::cout << "Hello World!" << std::endl;
		if (mesh_) {
			mesh_->SetOwner(this);
			m_ComponentsList.emplace_back(mesh_);
			return mesh_;
		}
		else {
			std::cout << "Cannot create Mesh Component!" << std::endl;
			return nullptr;
		}
	}

	template<>
	Component* AddComponent<PhysicsComponent>()
	{
		PhysicsComponent* physics_ = new PhysicsComponent();
		if (physics_) {
			physics_->SetOwner(this);
			m_ComponentsList.emplace_back(physics_);
			return physics_;
		}
		else {
			std::cout << "Cannot create Physics Component!" << std::endl;
			return nullptr;
		}
	}

	template<typename T>
	Component* FindComponent()
	{
		static_assert(false);
	}

	template<>
	Component* FindComponent<InputComponent>()
	{
		for (auto component : m_ComponentsList)
		{
			if (component && component->GetComponentName() == "InputComponent")
				return component;
		}

		std::cout << "Input Component not found!" << std::endl;
		return nullptr;
	}

	template<>
	Component* FindComponent<TransformComponent>()
	{
		for (auto component : m_ComponentsList)
		{
			if (component && component->GetComponentName() == "TransformComponent")
				return component;
		}

		std::cout << "Tranform Component not found!" << std::endl;
		return nullptr;
	}

	template<>
	Component* FindComponent<MeshComponent>()
	{
		for (auto component : m_ComponentsList)
		{
			if (component && component->GetComponentName() == "MeshComponent")
				return component;
		}

		std::cout << "Mesh Component not found!" << std::endl;
		return nullptr;
	}

	template<>
	Component* FindComponent<PhysicsComponent>()
	{
		for (auto component : m_ComponentsList)
		{
			if (component && component->GetComponentName() == "PhysicsComponent")
			{
				TransformComponent* TC_ = (TransformComponent*)this->FindComponent<TransformComponent>();
				if (!TC_)
					std::cout << "Cannot find Transform Component for Physics Component!" << std::endl;
				else
				{
					PhysicsComponent* PC_ = (PhysicsComponent*)component;
					PC_->AddTransformComponent(TC_);
				}

				return component;
			}
		}

		std::cout << "Physics Component not found!" << std::endl;
		return nullptr;
	}
	
	// Destructor
	~GameObject();
};