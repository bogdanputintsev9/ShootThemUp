// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "STUHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent
{
    GENERATED_BODY()

  public:
    USTUHealthComponent();

    float GetHealth() const
    {
        return Health;
    }

    UFUNCTION(BlueprintCallable)
    bool IsDead() const
    {
        return FMath::IsNearlyZero(Health);
    }

    FOnDeath OnDeath;
    FOnHealthChanged OnHealthChanged;

  protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0"))
    float MaxHealth = 100.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
    bool AutoHeal = true;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0", EditCondition = "AutoHeal"))
    float HealUpdateTime = 1.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0", EditCondition = "AutoHeal"))
    float HealDelay = 3.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0", EditCondition = "AutoHeal"))
    float HealModifier = 5.0f;

    virtual void BeginPlay() override;

  private:
    float Health = 0.0f;

    FTimerHandle HealTimerHandle;

    UFUNCTION()
    void OnTakeAnyDamage(AActor *DamagedActor, float Damage, const class UDamageType *DamageType,
                         class AController *InstigatedBy, AActor *DamageCauser);

    void HealUpdate();
    void SetHealth(const float NewHealth);
};