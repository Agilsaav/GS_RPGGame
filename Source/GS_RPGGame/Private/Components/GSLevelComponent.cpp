#include "Components/GSLevelComponent.h"

int UGSLevelComponent::GetLevel() const
{
	return CurrentLevel;
}

float UGSLevelComponent::GetRemainingExpToLevelUp() const
{
	return LevelCurve->GetFloatValue(CurrentLevel + 1) - CurrentLevelExp;
}

void UGSLevelComponent::AddExperience(float ExpAmount)
{
	if (!IsMaxLevel())
	{
		return;
	}

	float ExpNeeded = GetRemainingExpToLevelUp();

	while (ExpAmount > ExpNeeded && !IsMaxLevel())
	{
		ExpAmount -= ExpNeeded;
		TotalExp += ExpAmount;

		LevelUp();
		ExpNeeded = GetRemainingExpToLevelUp();

		if (IsMaxLevel())
		{
			return;
		}
	}

	CurrentLevelExp += ExpAmount;
	TotalExp += ExpAmount;
}

void UGSLevelComponent::AddLevels(int Levels)
{
	if (Levels <= 0)
	{
		return;
	}

	for (int Level = 0; Level < Levels; ++Level)
	{
		if (!IsMaxLevel())
		{
			TotalExp += (GetRemainingExpToLevelUp() - CurrentLevelExp);
			LevelUp();
		}
	}
}

bool UGSLevelComponent::IsMaxLevel() const
{
	return CurrentLevel == MaxLevel;
}

void UGSLevelComponent::LevelUp()
{
	CurrentLevelExp = 0.f;
	++CurrentLevel;
	OnLevelChanged.Broadcast(CurrentLevel);
}

