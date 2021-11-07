// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Abilities/Components/MDBaseAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Math/UnrealMathUtility.h"
#include "Net/UnrealNetwork.h"

UMDBaseAttributeSet::UMDBaseAttributeSet()
{
}

void UMDBaseAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UMDBaseAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMDBaseAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMDBaseAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMDBaseAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMDBaseAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMDBaseAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);

}

void UMDBaseAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	const FGameplayAttribute Attribute = Data.EvaluatedData.Attribute;
	
	if (Attribute.IsSystemAttribute())
	{
		if (Attribute.GetName() == GetHealthAttribute().GetName())
		{
			SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
			SetMaxHealth(FMath::Clamp(GetMaxHealth(), 0.0f, GetMaxHealth()));
		}

		if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
		{
			SetStamina(FMath::Clamp(GetStamina(), 0.0f, GetMaxStamina()));
			SetMaxStamina(FMath::Clamp(GetMaxStamina(), 0.0f, GetMaxStamina()));
		}

		if (Data.EvaluatedData.Attribute == GetManaAttribute())
		{
			SetMana(FMath::Clamp(GetMana(), 0.0f, GetMaxMana()));
			SetMaxMana(FMath::Clamp(GetMaxMana(), 0.0f, GetMaxMana()));
		}
	}
}

void UMDBaseAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMDBaseAttributeSet, Health, OldHealth);
}

void UMDBaseAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMDBaseAttributeSet, MaxHealth, OldMaxHealth);
}

void UMDBaseAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMDBaseAttributeSet, Stamina, OldStamina);
}

void UMDBaseAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMDBaseAttributeSet, MaxStamina, OldMaxStamina);
}

void UMDBaseAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMDBaseAttributeSet, Mana, OldMana);
}

void UMDBaseAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMDBaseAttributeSet, MaxMana, OldMaxMana);
}
