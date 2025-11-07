// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleSessionWidget.h"

#include "SessionSubsystem.h"
#include "Kismet/GameplayStatics.h"

void USimpleSessionWidget::CreateSession()
{
	UKismetSystemLibrary::PrintString(this, "CreateSession",
		true, true, FColor::Yellow, 4.f, TEXT("None"));
	if (auto* Sub = GetGameInstance()->GetSubsystem<USessionSubsystem>())
	{
		Sub->CreateLanSession(3);
	}
}


void USimpleSessionWidget::FindSession()
{
	UKismetSystemLibrary::PrintString(this, "FindSession",
		true, true, FColor::Yellow, 4.f, TEXT("None"));
	if (auto* Sub = GetGameInstance()->GetSubsystem<USessionSubsystem>())
	{
		Sub->FindLanSessions();
	}
}

void USimpleSessionWidget::Print()
{
	UKismetSystemLibrary::PrintString(this, "Print",
		true, true, FColor::Yellow, 4.f, TEXT("None"));
}