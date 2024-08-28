#pragma once

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	ECS_Unequipped UMETA(DispleyName = "Unequipped"),
	ECS_EquippedOneHandedWeapon UMETA(DispleyName = "Equipped One-Handed Weapon"),
	ECS_EquippedTwoHandedWeapon UMETA(DispleyName = "Equipped Two-Handed Weapon")
};

UENUM(BlueprintType)
enum class EActionState : uint8
{
	EAS_Unoccupied UMETA(DisplayName = "Unoccupied"),
	EAS_Attacking UMETA(DisplayName = "Attacking"),
	EAS_EquippingWeapon UMETA(DisplayName = "Equipping Weapon")
};