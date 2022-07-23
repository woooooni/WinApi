#include "pch.h"
#include "CComponent.h"

CComponent::CComponent()
	: m_pOwner(nullptr)
{
}

CComponent::~CComponent()
{
}

CComponent::CComponent(const CComponent& _origin)
	:m_pOwner(_origin.m_pOwner)
{
}
