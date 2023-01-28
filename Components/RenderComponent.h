#pragma once

#include "Component.h"

class RenderComponent : public Component
{
public:
	RenderComponent();
	virtual ~RenderComponent();

	void BeginPlay() override;
	void Update() override;
};