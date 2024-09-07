// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "CharacterTypes.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UGroomComponent;
class AItem;

UCLASS()
class OPENWORLDPROJECT_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	FORCEINLINE void SetOverlappingItem(AItem* Item) { OverlappingItem = Item; }
	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }

protected:
	virtual void BeginPlay() override;

	// Input method
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	void EKeyPressed();
	virtual void Attack() override;

	// Montage method
	virtual void PlayAttackMontage() override;
	virtual void AttackEnd() override;

	UFUNCTION(BLueprintCallable)
	void Disarm();

	UFUNCTION(BLueprintCallable)
	void Arm();

	UFUNCTION(BLueprintCallable)
	void FinishEquipping();

	void PlayEquipMontage(const FName& SectionName);

	virtual bool CanAttack() override;
	bool CanDisarm();
	bool CanArm();

private:
	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EActionState ActionState = EActionState::EAS_Unoccupied;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera;

	UPROPERTY(VisibleInstanceOnly)
	AItem* OverlappingItem;

	// Animation montages variable
	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* EquipMontage;

public:

};
