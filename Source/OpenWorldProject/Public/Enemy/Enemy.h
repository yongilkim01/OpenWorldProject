#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Characters/CharacterTypes.h"
#include "Enemy.generated.h"

class UInputComponent;
class UHealthBarComponent;
class UPawnSensingComponent;
class AWeapon;
UCLASS()
class OPENWORLDPROJECT_API AEnemy : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AEnemy();

	virtual void Tick(float DeltaTime) override;
	void CheckPatrolTarget();
	void CheckCombatTarget();

	virtual void GetHit_Implementation(const FVector& ImpactPoint) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void Destroyed() override;
	virtual bool CanAttack() override;

protected:
	virtual void BeginPlay() override;
	virtual void Die() override;
	virtual void Attack() override;
	virtual int32 PlayDeathMontage() override;
	virtual void HandleDamage(float DamageAmount) override;

	bool InTargetRange(AActor* Target, double Radius);
	void MoveToTarget(AActor* Target);
	AActor* SelectPatrolTarget();

	UFUNCTION()
	void SeePawn(APawn* SeenPawn);

private:
	void PatrolTimerFinished();

	/** AI behavior */
	void HideHealthBar();
	void ShowHealthBar();
	void LoseInterest();
	void StartPatrolling();
	void ChaseTarget();
	bool IsOutsideCombatRadius();
	bool IsOutsideAttackRadius();
	bool IsInsideAttackRadius();
	bool IsChasing();
	bool IsAttacking();
	bool IsDead();
	bool IsEngaged();
	void ClearPatrolTimer();

	/** Combat */
	void StartAttackTimer();
	void ClearAttackTimer();


private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AWeapon> WeaponClass;

	UPROPERTY(VisibleAnywhere)
	UHealthBarComponent* HealthBarWidget;

	// Combat variables

	UPROPERTY()
	AActor* CombatTarget;

	UPROPERTY(EditAnywhere)
	double CombatRadius = 500.f;

	// Patrol variables

	UPROPERTY(EditInstanceOnly, Category = "AI Navigation", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	AActor* PatrolTarget;

	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	TArray<AActor*> PatrolTargets;

	UPROPERTY(EditAnywhere)
	double PatrolRadius = 200.f;

	// Attack variables
	UPROPERTY(EditAnywhere)
	double AttackRadius = 150.f;

	FTimerHandle PatrolTimer;

	// Time variables
	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float WaitMin = 5.f;

	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float WaitMax = 10.f;

	UPROPERTY()
	class AAIController* EnemyController;

	UPROPERTY(VisibleAnywhere)
	class UPawnSensingComponent* PawnSensingComponent;

	FTimerHandle AttackTimer;

	UPROPERTY(EditAnywhere, Category = Combat)
	float AttackMin = 0.5f;

	UPROPERTY(EditAnywhere, Category = Combat)
	float AttackMax = 1.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	float PatrollingSpeed = 125.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	float ChasingSpeed = 300.f;

protected:
	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<EDeathPose> DeathPose;

	UPROPERTY(BlueprintReadOnly)
	EEnemyState EnemyState = EEnemyState::EES_Patrolling;

	UPROPERTY(EditAnywhere, Category = Combat)
	float DeathLifeSpan = 8.f;
};
