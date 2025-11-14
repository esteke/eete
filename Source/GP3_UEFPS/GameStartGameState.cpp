// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStartGameState.h"

#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "LobbyGameMode.h"


void AGameStartGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AGameStartGameState, RemainingTime);
    DOREPLIFETIME(AGameStartGameState, bGameStarted);
}


void AGameStartGameState::BeginPlay()
{
    Super::BeginPlay();

    if (HasAuthority()) // サーバーのみで実行
    {
        GetWorld()->GetTimerManager().SetTimer(CheckTimerHandle, this,
            &AGameStartGameState::CheckPlayerCount, 1.0f, true);
    }
}


void AGameStartGameState::CheckPlayerCount()
{
    if (bGameStarted)
        return;

    const int32 NumPlayers = PlayerArray.Num();

    if (NumPlayers >= ALobbyGameMode::MaxPlayers)
    {
        StartCountdown(3);
    }
}


void AGameStartGameState::StartCountdown(int32 InSeconds)
{
    if (!HasAuthority())
        return;

    RemainingTime = InSeconds;
    GetWorld()->GetTimerManager().SetTimer(CountdownTimerHandle, this,
        &AGameStartGameState::TickCountdown, 1.0f, true);
}


void AGameStartGameState::TickCountdown()
{
    if (--RemainingTime <= 0)
    {
        GetWorld()->GetTimerManager().ClearTimer(CountdownTimerHandle);
        bGameStarted = true;
        OnRep_GameStarted(); // 明示呼び出し（サーバー側）
    }

    OnRep_RemainingTime(); // 全クライアントに更新を通知
}


void AGameStartGameState::OnRep_RemainingTime()
{
    auto str = FString::Printf(TEXT("RemainingTime = %d"), RemainingTime);
    UKismetSystemLibrary::PrintString(this, str, true, true, FColor::Orange, 6.f, TEXT("None"));
}


void AGameStartGameState::OnRep_GameStarted()
{
    UKismetSystemLibrary::PrintString(this, TEXT("Game Start!!"), true, true, FColor::Yellow, 6.f, TEXT("None"));
}
