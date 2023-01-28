#include "BananaWindow.h"

#include "GameObject.h"
#include "Textures/Texture.h"
#include "Camera.h"

#include <cstdlib>

GameObject::GameObject()
	: m_Name("GameObject"), texture(nullptr), m_TextureSlot(0U)
{}

GameObject::GameObject(const std::string& name)
	: m_Name(name), texture(nullptr), m_TextureSlot(0U)
{}

void GameObject::AssignTexture(Texture* _texture, const unsigned int& _texSlot)
{
	//texture->Unbind();
	texture = _texture;
	m_TextureSlot = _texSlot;
	texture->Bind(m_TextureSlot);
}

void GameObject::BeginPlay()
{
	// Calls BeginPlay for all the components in the list
	for (auto component : m_ComponentsList)
		component->BeginPlay();
}

void GameObject::Update()
{
	// Call Update for all the components in the list
	for (auto component : m_ComponentsList)
		component->Update();

	updateSelfAndChild();
}

void GameObject::addChild(GameObject* child)
{
	if (child == this)
		return;

	children.emplace_back(child);
	children.back()->parent = this;
}

//Update transform if it was changed
void GameObject::updateSelfAndChild()
{
	TransformComponent* transformComp = (TransformComponent*)(this->FindComponent<TransformComponent>());
	if (transformComp)
	{
		bool bDirtyFlag = transformComp->GetDirtyFlag();
		if (!bDirtyFlag)
			return;

		forceUpdateSelfAndChild();
	}
	else
		return;
}

//Force update of transform even if local space don't change
void GameObject::forceUpdateSelfAndChild()
{
	TransformComponent* transformComp = (TransformComponent*)(this->FindComponent<TransformComponent>());

	if (parent)
	{
		TransformComponent* parentTransformComp = (TransformComponent*)(parent->FindComponent<TransformComponent>());
		if (transformComp && parentTransformComp)
		{
			transformComp->ComputeModelMatrix(parentTransformComp->GetModelMatrix());
		}
	}
	else
	{
		if (transformComp)
			transformComp->ComputeModelMatrix();
	}

	for (auto& child : children)
	{
		child->forceUpdateSelfAndChild();
	}
}

void GameObject::Draw(Shader& shader, Renderer& renderer)
{
	TransformComponent* transformComp = (TransformComponent*)(this->FindComponent<TransformComponent>());
	MeshComponent* meshComp = (MeshComponent*)(this->FindComponent<MeshComponent>());
	Camera camera_ = Camera::GetInstance();
	if (meshComp && transformComp)
	{
		glm::mat4 mvp = camera_.GetViewProjection() * transformComp->GetModelMatrix();

		// Bind the Shader with all the Uniform variables
		shader.Bind();
		shader.SetUniformMat4("u_MVP", mvp);				// Model View Projection Matrix
		shader.SetUniform1i("u_Texture", m_TextureSlot);	// Texture

		// Draw the mesh
		meshComp->DrawMesh(shader, renderer);
	}
}

//////////////// Helper Functions and the Destructors Below ////////////////
void GameObject::CalculateSize()
{
	TransformComponent* transformComp = (TransformComponent*)(this->FindComponent<TransformComponent>());
	MeshComponent* meshComp = (MeshComponent*)(this->FindComponent<MeshComponent>());
	
	if (meshComp && transformComp) {
		m_size.x = abs(meshComp->m_vertices[0].GetPosition().x - meshComp->m_vertices[1].GetPosition().x);// *transformComp->GetLocalScale().x;
		m_size.y = abs(meshComp->m_vertices[0].GetPosition().y - meshComp->m_vertices[3].GetPosition().y);// *transformComp->GetLocalScale().y;
		m_size.z = 0.0f;
	}
	else
		std::cout << "Error: Cannot Calculate Size! Mesh or Tranform Component or both doesn't exists!" << std::endl;
}

void GameObject::SetActive(bool _state)
{
	bActive = _state;
}

bool GameObject::IsActive()
{
	return bActive;
}

GameObject::~GameObject()
{
	for (auto component : m_ComponentsList)
		if (component)
			delete component;
}