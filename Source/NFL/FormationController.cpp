// Fill out your copyright notice in the Description page of Project Settings.

#include "FormationController.h"

// Sets default values
AFormationController::AFormationController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFormationController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFormationController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AFormationController::LoadTextFromFile(FString FileName, TArray<FString>& TextArray)
{

	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FileName))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Could not Find File"));
		return false;
	}
	else
	{
		// Convert filepath to character array and save to array
		const TCHAR* FILEPATH = *FileName;
		return FFileHelper::LoadFileToStringArray(TextArray, *FileName);
	}
}

bool AFormationController::SaveArrayText(FString SaveDirectory, FString FileName, TArray<FString> SaveText, bool AllowOverwriting = false)
{
	// Set complete file path
	SaveDirectory += "\\";
	SaveDirectory += FileName;

	if (!AllowOverwriting)
	{
		if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*SaveDirectory))
		{
			return false;
		}
	}

	FPlatformFileManager::Get().GetPlatformFile().DeleteFile(*SaveDirectory);
	FString FinalString = "";
	for (FString& Each : SaveText)
	{
		FinalString += Each;
		FinalString += LINE_TERMINATOR;
	}

	return FFileHelper::SaveStringToFile(FinalString, *SaveDirectory);

}

bool AFormationController::DeleteTextFile(FString SaveDirectory, FString FileName)
{
	// Set complete file path
	SaveDirectory += "\\";
	SaveDirectory += FileName;

	return FPlatformFileManager::Get().GetPlatformFile().DeleteFile(*SaveDirectory);
}

void AFormationController::LoadFootballCSV(FString playfolder, FString SaveDirectory, FFootballArray& football)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Football: %s"), *(SaveDirectory)));
	TArray<FString> loadfoot;
	LoadTextFromFile(SaveDirectory, loadfoot);
	TArray<float> onlyLook = { 3, 4, 18, 19};
	TArray<float> readfloat = { 0, 0, 0, 0 };
	FFootballArray temp;
	for (int i = 1; i < loadfoot.Num(); i++)
	{
		FString left = "";
		int flag = 0;
		FString br = loadfoot[i];
		int j = 0, k=0;

		while (j < br.Len()) {
			if (br[j] == ',') {
				if (flag<4 && k==onlyLook[flag]) {
					readfloat[flag] = FCString::Atof(*left);
					flag++;
					//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Float : %s"), *left));
				}
				else if (k == 8 && playfolder=="NFL") {
					const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ENFLEvent"), true);
					if (left.Contains(TEXT(";"))) {
						TArray<FString> eventarr;
						left.ParseIntoArray(eventarr, TEXT(";"), true);
						for (int ev = 1; ev < eventarr.Num(); ev++) {
							//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Event : %s"), *eventarr[ev]));
							int32 Index = EnumPtr->GetIndexByName(FName(*eventarr[ev]));
							if (Index != INDEX_NONE) {
								ENFLEvent Status = static_cast<ENFLEvent>(EnumPtr->GetValueByIndex(Index));
								temp.FFootballEventArray.Add(Status, i);
							}
						}
					}
					else {
						//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Event : %s"), *left));
						int32 Index = EnumPtr->GetIndexByName(FName(*left));
						if (Index != INDEX_NONE) {
							ENFLEvent Status = static_cast<ENFLEvent>(EnumPtr->GetValueByIndex(Index));
							temp.FFootballEventArray.Add(Status, i);
						}
					}
					
				}
				left = "";
				k++;
			}
			else {
				left += br[j];
			}
			j++;
		}
		if (flag < 4 && k == onlyLook[flag]) {
			readfloat[flag] = FCString::Atof(*left);
			flag++;
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Float : %s"), *left));
		}
		temp.FFootballSpeedArray.Add(readfloat[0]);
		temp.FFootballAccelArray.Add(readfloat[1]);
		temp.FFootballLocationArray.Add(FTransform(FVector(readfloat[2], readfloat[3], 0.0f)));
	}
	football = temp;
}

void AFormationController::LoadPlayerCSV(FString playfolder, FString SaveDirectory, FPlayerArray& someplayer, int& penaltyJerseyNumber, TArray<ENFLPenalty>& penaltyType)
{
	FPlayerArray temp;
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Player: %s"), *(SaveDirectory)));
	TArray<FString> loadplayer;
	
	LoadTextFromFile(SaveDirectory, loadplayer);
	
	FString FileName = FPaths::GetCleanFilename(SaveDirectory);
	TArray<FString> Parts;
	FileName.ParseIntoArray(Parts, TEXT("_"), true);

	// Now Parts[0] contains "17", Parts[1] contains "WR", and Parts[2] contains "AM-POL.csv"
	temp.playerJerseyNumber = FCString::Atoi(*Parts[0]); // "17"
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ENFLPosition"), true);
	int32 Index;
	if (playfolder == "NFL") {
		Index = EnumPtr->GetIndexByName(FName(*Parts[1]));
		if (Index != INDEX_NONE) {
			temp.playerPosition = static_cast<ENFLPosition>(EnumPtr->GetValueByIndex(Index));
		}

		if (Parts.Num() == 3) {
			FString ThirdPart = Parts[2].LeftChop(4); // "AM-POL"
			Parts.Empty();
			if (ThirdPart.Len() == 0) {

			}
			else {
				ThirdPart.ParseIntoArray(Parts, TEXT("-"), true);
				for (int i = 0; i < Parts.Num(); i++) {
					const UEnum* EnumPtr1 = FindObject<UEnum>(ANY_PACKAGE, TEXT("ENFLPenalty"), true);
					Index = EnumPtr1->GetIndexByName(FName(*Parts[i]));
					if (Index != INDEX_NONE) {
						penaltyType.Add(static_cast<ENFLPenalty>(EnumPtr1->GetValueByIndex(Index)));
						penaltyJerseyNumber = temp.playerJerseyNumber;
					}
				}
			}
		}
	}
	
	TArray<float> readfloat = { 0, 0, 0, 0, 0 };
	
	for (int i = 1; i < loadplayer.Num(); i++)
	{
		FString left = "";
		FString br = loadplayer[i];
		int j = 0, k = 0;

		while (j < br.Len()) {
			if (br[j] == ',') {
				if (k<4) {
					readfloat[k] = FCString::Atof(*left);
					//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Float : %s"), *left));
				}
				left = "";
				k++;
			}
			else {
				left += br[j];
			}
			j++;
		}
		if (k == 4) {
			readfloat[k] = FCString::Atof(*left);
			k++;
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Float : %s"), *left));
		}
		temp.FPlayerLocationArray.Add(FTransform(FVector(readfloat[0], readfloat[1], 0.0f)));
		temp.FPlayerSpeedArray.Add(readfloat[2]);
		temp.FPlayerAccelArray.Add(readfloat[3]);
		temp.FPlayerHeadingArray.Add(readfloat[4]);
		
	}
	someplayer = temp;
}




void AFormationController::readRandomFormation(FString playfolder, int& penaltyJerseyNumber, bool& penaltyHome, TArray<ENFLPenalty>& penaltyType, TArray<FFootballArray>& Football, TArray<FPlayerArray>& HomeTeam, TArray<FPlayerArray>& AwayTeam){
	TArray<FString> penalties = {"WED", "TRPd", "FCI", "IDP", "ILH", "UOHd", "KCI", "HC", "RNK", "OFK", "CHB", "UNSd", "ILF", "TRP", "UNRd", "DOF", "UNR", "ITK", "OH", "POK", "UNS", "IDT", "IBW", "FMM"};
	FString Directory = UKismetSystemLibrary::GetProjectSavedDirectory() + "inputs/"+playfolder+"/";// +TEXT("*");
	
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	TArray<FString> all_plays;
	LoadTextFromFile(Directory+ "name.csv", all_plays);
	int32 RandomIndex = FMath::RandRange(0, all_plays.Num() - 1);
	FString gp = all_plays[RandomIndex];
	TArray<ENFLPenalty> all_penalties;

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Outside: %s"), *(Directory+gp)));
	if (PlatformFile.DirectoryExists(*(Directory + gp)))
	{
		FString ext = ".csv";
		FFootballArray randfoot;
		LoadFootballCSV(playfolder, Directory + gp + "/football.csv", randfoot);
		Football.Add(randfoot);
		
		
		TArray<FString> Homefolder;
		PlatformFile.FindFiles(Homefolder, *(Directory+gp+"/home/"), *ext);
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Inside: %s"), *(Directory + gp + "/home/")));
		for (size_t i = 0; i < Homefolder.Num(); i++)
		{
			FPlayerArray someplayer;
			LoadPlayerCSV(playfolder, Homefolder[i], someplayer, penaltyJerseyNumber, all_penalties);
			HomeTeam.Add(someplayer);
		}
		if (all_penalties.Num() > 0) {
			penaltyHome = true;
		}
		else {
			penaltyHome = false;
		}

		TArray<FString> Awayfolder;
		PlatformFile.FindFiles(Awayfolder, *(Directory + gp + "/away/"), *ext);
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Inside: %s"), *(Directory + gp + "/away/")));
		for (size_t i = 0; i < Awayfolder.Num(); i++)
		{
			FPlayerArray someplayer;
			LoadPlayerCSV(playfolder, Awayfolder[i], someplayer, penaltyJerseyNumber, all_penalties);
			AwayTeam.Add(someplayer);
		}
		penaltyType = all_penalties;
	}
}