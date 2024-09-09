// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/HitInterface.h"
#include "BaseCharacter.generated.h"

class AWeapon;
class UAttributeComponent;
class UAnimMontage;


UCLASS()
class OPENWORLDPROJECT_API ABaseCharacter : public ACharacter, public IHitInterface
{
	GENERATED_BODY()

public:
	ABaseCharacter();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetWeaponCollisionEnabled(ECollisionEnabled::Type CollisionEnabled);

protected:
	virtual void BeginPlay() override;
	virtual void Attack();
	virtual void Die();

	void PlayHitReactMontage(const FName& SectionName);
	void DirectionalHitReact(const FVector& Location);
	void PlayHitSound(const FVector& ImpactPoint);
	void SpawnHitParticles(const FVector& ImpactPoint);
	virtual void HandleDamage(float DamageAmount);

	// 특정 몽타주의 애니메이션을 실행하는 메소드
	void PlayMontageSection(UAnimMontage* Montage, const FName& SectionName);

	// 랜덤한 몽타주의 애니메이션을 실행하는 메소드
	int32 PlayRandomMontageSection(UAnimMontage* Montage, const TArray<FName>& SectionNames);

	// 몽타주 실행 메소드
	virtual int32 PlayAttackMontage();
	virtual int32 PlayDeathMontage();

	// 캡슐 해제 메소드
	void DisableCapsule();

	virtual bool CanAttack();
	bool IsAlive();

	UFUNCTION(BlueprintCallable)
	virtual void AttackEnd();

protected: // Protected variables

	/*
	* Weapon variables
	*/
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	AWeapon* EquippedWeapon;

	/*
	* Montage variables
	*/
	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* HitReactMontage;

	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* DeathMontage;

	UPROPERTY(EditAnywhere, Category = Combat)
	TArray<FName> AttackMontageSections;

	UPROPERTY(EditAnywhere, Category = Combat)
	TArray<FName> DeathMontageSections;

	/*
	* Component variables
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UAttributeComponent* Attributes;

private:
	UPROPERTY(EditAnywhere, Category = Sounds)
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category = VisualEffects)
	UParticleSystem* HitParticles;


};
