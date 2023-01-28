#include "InputComponent.h"

#include "../BananaWindow.h"
#include "../GameObject.h"

InputComponent::InputComponent()
{
    BeginPlay();
}

void InputComponent::BeginPlay()
{

}

void InputComponent::Update()
{
    CheckForInput(GetOwner());
}

std::string InputComponent::GetComponentName() { return "InputComponent"; }

// Helper Functions
void InputComponent::CheckForInput(GameObject* object)
{
    GLFWwindow* window = BananaWindowHandler::getInstance().GetCurrentContext();

    // Movement Keys
    int stateW = glfwGetKey(window, GLFW_KEY_W);
    int stateA = glfwGetKey(window, GLFW_KEY_A);
    int stateS = glfwGetKey(window, GLFW_KEY_S);
    int stateD = glfwGetKey(window, GLFW_KEY_D);

    int stateUP = glfwGetKey(window, GLFW_KEY_UP);
    int stateLEFT = glfwGetKey(window, GLFW_KEY_LEFT);
    int stateDOWN = glfwGetKey(window, GLFW_KEY_DOWN);
    int stateRIGHT = glfwGetKey(window, GLFW_KEY_RIGHT);

    // Rotation Keys
    int stateE = glfwGetKey(window, GLFW_KEY_E);
    int stateQ = glfwGetKey(window, GLFW_KEY_Q);

    // Action Keys
    int stateSpaceBar = glfwGetKey(window, GLFW_KEY_SPACE);

    PhysicsComponent* physicsComponent_ = (PhysicsComponent*)(object->FindComponent<PhysicsComponent>());
    if (physicsComponent_ == nullptr)
    {
        std::cout << "[Error: Input Component] Cannot find Physics Component for " 
            << object->GetObjectName() << std::endl;
        return;
    }

    float minV_ = physicsComponent_->GetMinVelocity();
    float maxV_ = physicsComponent_->GetMaxVelocity();

    if (stateW || stateA || stateS || stateD || stateE || stateQ)
    {
        if (stateW == GLFW_PRESS) { physicsComponent_->SetVelocity(glm::vec3(0.0f, maxV_, 0.0f)); }
        if (stateS == GLFW_PRESS) { physicsComponent_->SetVelocity(glm::vec3(0.0f, -maxV_, 0.0f)); }
        if (stateD == GLFW_PRESS) { physicsComponent_->SetVelocity(glm::vec3(maxV_, 0.0f, 0.0f)); }
        if (stateA == GLFW_PRESS) { physicsComponent_->SetVelocity(glm::vec3(-maxV_, 0.0f, 0.0f)); }
    }
    else
        physicsComponent_->SetVelocity(glm::vec3(minV_));

    if (stateE || stateQ)
    {
        if (stateE == GLFW_PRESS) { physicsComponent_->SetAngularVelocity(glm::vec3(0.0f, 0.0f, maxV_)); }
        if (stateQ == GLFW_PRESS) { physicsComponent_->SetAngularVelocity(glm::vec3(0.0f, 0.0f, -maxV_)); }
    }
    else
        physicsComponent_->SetAngularVelocity(glm::vec3(minV_));

    //std::cout << "Current Velocity: " << glm::to_string(physicsComponent_->GetVelocity()) << std::endl;

    if (stateSpaceBar == GLFW_PRESS) {} // Does nothing ATM
}

void InputComponent::Serialize()
{

}

void InputComponent::Deserialize(rapidjson::Value& componentMembers)
{

}

InputComponent::~InputComponent()
{

}
