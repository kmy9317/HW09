// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "HWGameStateBase.generated.h"

class AHWPlayerState;
/**
 * 
 */
UCLASS()
class UNREALHW09_API AHWGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCBroadcastLoginMessage(const FString& InNameString = FString(TEXT("XXXXXXX")));

	UFUNCTION(BlueprintCallable, BlueprintPure)
	AHWPlayerState* GetCurrentTurnPlayerState() const { return CurrentTurnPlayerState; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetTurnRemainingTime() const { return TurnRemainingTime; }
	
	UPROPERTY(Replicated)
	TObjectPtr<AHWPlayerState> CurrentTurnPlayerState; 

	UPROPERTY(Replicated)
	float TurnRemainingTime; 
};
