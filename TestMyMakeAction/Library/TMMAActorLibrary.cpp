// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMAActorLibrary.h"

void UTMMAActorLibrary::GetPlayerLocation(FVector& PlayerLocation)
{
	FVector ReturnVector = FVector(0.0, 0.0, 0.0);
	UWorld* world = GEngine->GameViewport->GetWorld();
	APawn* PlayerCharacter = UGameplayStatics::GetPlayerPawn(world, 0);
	// クラッシュ防止でプレイヤー存在するかの二重チェック
	if (PlayerCharacter != nullptr) {
		if (IsValid(PlayerCharacter) == true) {
			ReturnVector = UGameplayStatics::GetPlayerPawn(world, 0)->GetActorLocation();
		}
	}
	PlayerLocation = ReturnVector;
}

void UTMMAActorLibrary::GetPlayerTransform(FTransform& PlayerTransform)
{
	FTransform ReturnTransform = UKismetMathLibrary::MakeTransform(FVector(0.0, 0.0, 0.0), FRotator(0.0, 0.0, 0.0), FVector(0.0, 0.0, 0.0));
	UWorld* world = GEngine->GameViewport->GetWorld();
	APawn* PlayerCharacter = UGameplayStatics::GetPlayerPawn(world, 0);
	// クラッシュ防止でプレイヤー存在するかの二重チェック
	if (PlayerCharacter != nullptr) {
		if (IsValid(PlayerCharacter) == true) {
			ReturnTransform = UGameplayStatics::GetPlayerPawn(world, 0)->GetActorTransform();
		}
	}
	PlayerTransform = ReturnTransform;
}
void  UTMMAActorLibrary::GetActorLocationForAdd(AActor* InActor, FVector AddVector, FVector& ActorLocation)
{
	FVector ReturnActorLocation = FVector(0.0, 0.0, 0.0);
	if (UTMMAUnrealLibrary::GetIsNotNullPtrAndIsValid(InActor) == true) {
		ReturnActorLocation = InActor->GetActorLocation() + AddVector;
	}
	ActorLocation = ReturnActorLocation;
}

void UTMMAActorLibrary::GetComponentLocationForAdd(USceneComponent* InComponent, FVector AddVector, FVector& ComponentLocation)
{
	ComponentLocation = InComponent->GetComponentLocation() + AddVector;
}

void UTMMAActorLibrary::GetAimTransform(FVector SetVector, AActor* StartActor, AActor* TargetActor, FVector ScaleVector, FTransform& GetTransform)
{
	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(
		StartActor->GetActorLocation(),
		TargetActor->GetActorLocation()
	);
	FVector RoVector = LookAtRotation.RotateVector(SetVector);
	GetTransform = UKismetMathLibrary::MakeTransform(StartActor->GetActorLocation() + RoVector, LookAtRotation, ScaleVector);

}

void UTMMAActorLibrary::GetAimTransformAngle(FVector SetVector, AActor* StartActor, AActor* TargetActor, FVector ScaleVector, int CombineIndex, float Angle, FTransform& GetTransform)
{
	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(
		StartActor->GetActorLocation(),
		TargetActor->GetActorLocation()
	);
	FVector RoVector = LookAtRotation.RotateVector(SetVector);
	LookAtRotation += FRotator(CombineIndex * Angle, 0, 0);
	GetTransform = UKismetMathLibrary::MakeTransform(StartActor->GetActorLocation() + RoVector, LookAtRotation, ScaleVector);

}

void UTMMAActorLibrary::GetAimTransformForVector(FVector SetVector, FVector StartVector, FVector TargetVector, FVector ScaleVector, FTransform& GetTransform)
{
	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(StartVector, TargetVector);
	FVector RoVector = LookAtRotation.RotateVector(SetVector);
	GetTransform = UKismetMathLibrary::MakeTransform(StartVector + RoVector, LookAtRotation, ScaleVector);
}

void UTMMAActorLibrary::GetRoundTransformForVector(FVector SetVector, FVector StartVector, FVector TargetVector, FVector ScaleVector, FRotator InB_Rotator, FTransform& GetTransform) {
	FRotator LookAtRotation = TargetVector.Rotation();
	FVector RoVector = LookAtRotation.RotateVector(SetVector);
	FRotator CRotator = LookAtRotation + InB_Rotator;
	GetTransform = UKismetMathLibrary::MakeTransform(StartVector + RoVector, CRotator, ScaleVector);
}

void UTMMAActorLibrary::GetAimTransformComponent(FVector SetVector, USceneComponent * StartComponent, USceneComponent * TargetCompoonent, FVector ScaleVector, FTransform & GetTransform)
{
	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(
		StartComponent->GetComponentLocation(),
		TargetCompoonent->GetComponentLocation()
	);
	FVector RoVector = LookAtRotation.RotateVector(SetVector);
	GetTransform = UKismetMathLibrary::MakeTransform(StartComponent->GetComponentLocation() + RoVector, LookAtRotation, ScaleVector);

}

void UTMMAActorLibrary::GetXVectorTransform(FVector SetVector, FVector StartVector, FVector TargetVector, FVector ScaleVector, FTransform& GetTransform)
{
	FRotator LookAtRotation = TargetVector.Rotation();
	LookAtRotation.Roll = 0.0;
	FVector RoVector = LookAtRotation.RotateVector(SetVector);
	// 引数の各値で0以下ののものはデフォルトの1に設定。
	if (ScaleVector.X <= 0) {
		ScaleVector.X = 1.0;
	}
	if (ScaleVector.Y <= 0) {
		ScaleVector.Y = 1.0;
	}
	if (ScaleVector.Y <= 0) {
		ScaleVector.Y = 1.0;
	}
	GetTransform = UKismetMathLibrary::MakeTransform(StartVector + RoVector, LookAtRotation, ScaleVector);
}

void UTMMAActorLibrary::GetXVectorTransformByCombine(FVector SetVector, FVector StartVector, FVector TargetVector, FVector ScaleVector, FRotator AddRotate, FTransform& GetTransform)
{
	FRotator LookAtRotation = TargetVector.Rotation();
	LookAtRotation.Roll = 0.0;
	FVector RoVector = LookAtRotation.RotateVector(SetVector);
	FRotator CombineRotator = LookAtRotation + AddRotate;
	// 引数の各値で0以下ののものはデフォルトの1に設定。
	if (ScaleVector.X <= 0) {
		ScaleVector.X = 1.0;
	}
	if (ScaleVector.Y <= 0) {
		ScaleVector.Y = 1.0;
	}
	if (ScaleVector.Y <= 0) {
		ScaleVector.Y = 1.0;
	}
	GetTransform = UKismetMathLibrary::MakeTransform(StartVector + RoVector, CombineRotator, ScaleVector);

}

bool UTMMAActorLibrary::GetDistanceIn(float Float1, float Float2, float PlusDistance, float MinusDistance)
{
	bool IsDistanceIn = false;
	if (((Float1 - Float2) <= PlusDistance) && (Float1 - Float2) >= MinusDistance) {
		IsDistanceIn = true;
	}
	return IsDistanceIn;
}

bool UTMMAActorLibrary::GetIsInDistanceX(AActor* Actor1, AActor* Actor2, float PlusDistance, float MinusDistance)
{
	float Actor1VectorX = Actor1->GetActorLocation().X;
	float Actor2VectorX = Actor2->GetActorLocation().X;
	return GetDistanceIn(Actor1VectorX, Actor2VectorX, PlusDistance, MinusDistance);

}

bool UTMMAActorLibrary::GetIsInDistanceY(AActor* Actor1, AActor* Actor2, float PlusDistance, float MinusDistance)
{
	float Actor1VectorY = Actor1->GetActorLocation().Y;
	float Actor2VectorY = Actor2->GetActorLocation().Y;
	return GetDistanceIn(Actor1VectorY, Actor2VectorY, PlusDistance, MinusDistance);

}

bool UTMMAActorLibrary::GetIsInDistanceZ(AActor* Actor1, AActor* Actor2, float PlusDistance, float MinusDistance)
{
	float Actor1VectorZ = Actor1->GetActorLocation().Z;
	float Actor2VectorZ = Actor2->GetActorLocation().Z;
	return GetDistanceIn(Actor1VectorZ, Actor2VectorZ, PlusDistance, MinusDistance);

}


void UTMMAActorLibrary::AddMigityTime(float SetTime, float AddTime, float LimitTime, float& NowTime)
{
	if (SetTime <= LimitTime) {
		SetTime += AddTime;
	}
	NowTime = SetTime;
}

void UTMMAActorLibrary::SpawnSeAndParticle(AActor* InActor, UParticleSystem* Particle, USoundBase* Se, FVector InVector, FVector InScale) {
	if (InScale.X < 0.0f) {
		InScale.X = 1.0f;
	}
	if (InScale.Y < 0.0f) {
		InScale.Y = 1.0f;
	}
	if (InScale.Y < 0.0f) {
		InScale.Y = 1.0f;
	}

	UGameplayStatics::PlaySound2D(InActor->GetWorld(), Se, 1.0f, 1.0f, 0.0f, nullptr, InActor);
	UGameplayStatics::SpawnEmitterAtLocation(InActor->GetWorld(), Particle, InVector, FRotator(0.0f, 0.0f, 0.0f), InScale, true, EPSCPoolMethod::None, true);
}

void UTMMAActorLibrary::SpawnSeAndParticleBySoft(AActor* InActor, TSoftObjectPtr<UParticleSystem> SoftParticle, TSoftObjectPtr<USoundBase> SoftSe, FVector InVector, FVector InScale)
{
	if (InActor != nullptr) {
		UParticleSystem* Particle = SoftParticle.LoadSynchronous();
		USoundBase* Se = SoftSe.LoadSynchronous();
		SpawnSeAndParticle(InActor, Particle, Se, InVector, InScale);
	}
}


void UTMMAActorLibrary::AddActorVector(AActor* InActor, FVector AddVector) {
	FVector MovedLocation = InActor->GetActorLocation() + AddVector;
	InActor->SetActorLocation(MovedLocation);
}

void UTMMAActorLibrary::AddComponentVector(USceneComponent* InComponent, FVector AddVector)
{
	FVector MoveVector = InComponent->GetComponentLocation() + AddVector;
	InComponent->SetWorldLocation(MoveVector);
}


void UTMMAActorLibrary::AddActorVectorWithFloat(AActor* InActor, FVector AddVector, float AddFloat) {
	FVector MovedLocation = InActor->GetActorLocation() +(AddVector * AddFloat);
	InActor->SetActorLocation(MovedLocation);
}

void UTMMAActorLibrary::SetRotatorForEase(AActor* EasedActor, AActor* TargetActor, float InAlpha, bool InIsShortestPath, TEnumAsByte<EEasingFunc::Type> InEasingType)
{
	if (IsValid(EasedActor) && IsValid(TargetActor)) {
		FRotator ToTargetRotator = UKismetMathLibrary::FindLookAtRotation(EasedActor->GetActorLocation(), TargetActor->GetActorLocation());
		FRotator EasedRotator = UKismetMathLibrary::REase(EasedActor->GetActorRotation(), ToTargetRotator, InAlpha, InIsShortestPath, InEasingType, 2.0, 2);
		EasedActor->SetActorRotation(EasedRotator);
	}
}
//bool UTMMAActorLibrary::LineTraceByTargetToPlayer(FVector StartVector, FVector TargetVector, float TraceDistance, ECollisionChannel TraceChannel) {
//	FVector TargetTrace = TargetVector * TraceDistance;
//	TargetTrace += StartVector;
//	FHitResult ResultOutHit;
//	bool traceFlag = GetWorld()->LineTraceSingleByChannel(ResultOutHit, StartVector, TargetVector, TraceChannel);
//	return false;
//}

void UTMMAActorLibrary::MoveActorToTarget(AActor* MoveActor, AActor* TargetActor, float MoveVelocity)
{
	FVector DiffVector = TargetActor->GetActorLocation() - MoveActor->GetActorLocation();
	DiffVector.Normalize();
	FVector MoveVector = DiffVector * MoveVelocity;
	UE_LOG(LogTemp, Log, TEXT("DiffActorVector_Y=%f"), MoveVector.Y);
	MoveActor->AddActorWorldOffset(MoveVector);
}

void UTMMAActorLibrary::GetIsInRangeVector(AActor* TargetActor1, AActor* TargetActor2, float DiffRange_X, float DiffRange_Y, float DiffRange_Z, bool& IsInRangeX, bool& IsInRangeY, bool& IsInRangeZ)
{
	IsInRangeX = false;
	IsInRangeY = false;
	IsInRangeZ = false;
	FVector TargetActor1Vector = TargetActor1->GetActorLocation();
	FVector TargetActor2Vector = TargetActor2->GetActorLocation();
	FVector DiffActorVector = TargetActor1Vector - TargetActor2Vector;
	if (DiffActorVector.X < 0) {
		DiffActorVector.X *= -1.0;
	}
	if (DiffActorVector.Y < 0) {
		DiffActorVector.Y *= -1.0;
	}
	if (DiffActorVector.Z < 0) {
		DiffActorVector.Z *= -1.0;
	}
	//	DiffActorVector.Normalize();
	if (DiffActorVector.X <= DiffRange_X) {
		IsInRangeX = true;
	}
	if (DiffActorVector.Y <= DiffRange_Y) {
		IsInRangeY = true;
	}
	if (DiffActorVector.Z <= DiffRange_Z) {
		IsInRangeZ = true;
	}

}

bool UTMMAActorLibrary::GetIsHitBrushByTag(AActor* UsedActor, FName TagName)
{
	bool IsHitBrushByTag = false;
	if (UsedActor != nullptr) {
		TSubclassOf<ABrush> BrushActorClass;
		TArray<AActor*> ActorList;
		UGameplayStatics::GetAllActorsOfClassWithTag(UsedActor->GetWorld(), BrushActorClass, TagName, ActorList);
		if (IsValid(ActorList[0]) == true) {
			if (ActorList[0]->ActorHasTag(TagName) == true) {
				IsHitBrushByTag = true;
			}
		}
	}
	return IsHitBrushByTag;
}

