// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "Misc/Paths.h"
#include "Kismet/KismetSystemLibrary.h"
#include "FormationController.generated.h"

UENUM(BlueprintType)
enum class ENFLEvent : uint8
{
	kickoff UMETA(DisplayName = "kickoff"),
	touchback UMETA(DisplayName = "touchback"),
	ball_snap UMETA(DisplayName = "ball_snap"),
	field_goal_attempt UMETA(DisplayName = "field_goal_attempt"),
	field_goal UMETA(DisplayName = "field_goal"),
	kick_received UMETA(DisplayName = "kick_received"),
	first_contact UMETA(DisplayName = "first_contact"),
	tackle UMETA(DisplayName = "tackle"),
	punt UMETA(DisplayName = "punt"),
	punt_land UMETA(DisplayName = "punt_land"),
	punt_downed UMETA(DisplayName = "punt_downed"),
	out_of_bounds UMETA(DisplayName = "out_of_bounds"),
	extra_point_attempt UMETA(DisplayName = "extra_point_attempt"),
	extra_point UMETA(DisplayName = "extra_point"),
	fair_catch UMETA(DisplayName = "fair_catch"),
	punt_received UMETA(DisplayName = "punt_received"),
	touchdown UMETA(DisplayName = "touchdown"),
	kickoff_land UMETA(DisplayName = "kickoff_land"),
	punt_muffed UMETA(DisplayName = "punt_muffed"),
	fumble_offense_recovered UMETA(DisplayName = "fumble_offense_recovered"),
	autoevent_kickoff UMETA(DisplayName = "autoevent_kickoff"),
	onside_kick UMETA(DisplayName = "onside_kick"),
	kick_recovered UMETA(DisplayName = "kick_recovered"),
	extra_point_missed UMETA(DisplayName = "extra_point_missed"),
	punt_play UMETA(DisplayName = "punt_play"),
	line_set UMETA(DisplayName = "line_set"),
	fumble UMETA(DisplayName = "fumble"),
	fumble_defense_recovered UMETA(DisplayName = "fumble_defense_recovered"),
	free_kick UMETA(DisplayName = "free_kick"),
	field_goal_missed UMETA(DisplayName = "field_goal_missed"),
	field_goal_blocked UMETA(DisplayName = "field_goal_blocked"),
	pass_forward UMETA(DisplayName = "pass_forward"),
	pass_arrived UMETA(DisplayName = "pass_arrived"),
	pass_outcome_caught UMETA(DisplayName = "pass_outcome_caught"),
	lateral UMETA(DisplayName = "lateral"),
	run UMETA(DisplayName = "run"),
	pass_shovel UMETA(DisplayName = "pass_shovel"),
	field_goal_play UMETA(DisplayName = "field_goal_play"),
	extra_point_blocked UMETA(DisplayName = "extra_point_blocked"),
	penalty_flag UMETA(DisplayName = "penalty_flag"),
	man_in_motion UMETA(DisplayName = "man_in_motion"),
	punt_fake UMETA(DisplayName = "punt_fake"),
	punt_blocked UMETA(DisplayName = "punt_blocked"),
	drop_kick UMETA(DisplayName = "drop_kick"),
	field_goal_fake UMETA(DisplayName = "field_goal_fake"),
	pass_outcome_incomplete UMETA(DisplayName = "pass_outcome_incomplete"),
	safety UMETA(DisplayName = "safety"),
	snap_direct UMETA(DisplayName = "snap_direct"),
	handoff UMETA(DisplayName = "handoff"),
	kickoff_play UMETA(DisplayName = "kickoff_play"),
	qb_sack UMETA(DisplayName = "qb_sack"),
	shift UMETA(DisplayName = "shift"),
	huddle_break_offense UMETA(DisplayName = "huddle_break_offense"),
	huddle_start_offense UMETA(DisplayName = "huddle_start_offense"),
	two_point_conversion UMETA(DisplayName = "two_point_conversion"),
	field_goal_miseed UMETA(DisplayName = "field_goal_miseed")
};


UENUM(BlueprintType)
enum class ENFLPosition : uint8
{
	C UMETA(DisplayName = "C"),
	CB UMETA(DisplayName = "CB"),
	DB UMETA(DisplayName = "DB"),
	DE UMETA(DisplayName = "DE"),
	DL UMETA(DisplayName = "DL"),
	DT UMETA(DisplayName = "DT"),
	FB UMETA(DisplayName = "FB"),
	FS UMETA(DisplayName = "FS"),
	G UMETA(DisplayName = "G"),
	HB UMETA(DisplayName = "HB"),
	ILB UMETA(DisplayName = "ILB"),
	K UMETA(DisplayName = "K"),
	LB UMETA(DisplayName = "LB"),
	LS UMETA(DisplayName = "LS"),
	MLB UMETA(DisplayName = "MLB"),
	NT UMETA(DisplayName = "NT"),
	OG UMETA(DisplayName = "OG"),
	OLB UMETA(DisplayName = "OLB"),
	OT UMETA(DisplayName = "OT"),
	P UMETA(DisplayName = "P"),
	QB UMETA(DisplayName = "QB"),
	RB UMETA(DisplayName = "RB"),
	S UMETA(DisplayName = "S"),
	SAF UMETA(DisplayName = "SAF"),
	SS UMETA(DisplayName = "SS"),
	T UMETA(DisplayName = "T"),
	TE UMETA(DisplayName = "TE"),
	WR UMETA(DisplayName = "WR")
};

UENUM(BlueprintType)
enum class ENFLPenalty : uint8
{
	BAT UMETA(DisplayName = "BAT"),
	CHB UMETA(DisplayName = "CHB"),
	DOF UMETA(DisplayName = "DOF"),
	DPI UMETA(DisplayName = "DPI"),
	DSQd UMETA(DisplayName = "DSQd"),
	DTM UMETA(DisplayName = "DTM"),
	FCI UMETA(DisplayName = "FCI"),
	FMM UMETA(DisplayName = "FMM"),
	HC UMETA(DisplayName = "HC"),
	IBB UMETA(DisplayName = "IBB"),
	IBW UMETA(DisplayName = "IBW"),
	IDK UMETA(DisplayName = "IDK"),
	IDP UMETA(DisplayName = "IDP"),
	IDT UMETA(DisplayName = "IDT"),
	IFC UMETA(DisplayName = "IFC"),
	ILF UMETA(DisplayName = "ILF"),
	ILH UMETA(DisplayName = "ILH"),
	ILHd UMETA(DisplayName = "ILHd"),
	ILM UMETA(DisplayName = "ILM"),
	ING UMETA(DisplayName = "ING"),
	ISH UMETA(DisplayName = "ISH"),
	ITK UMETA(DisplayName = "ITK"),
	KCI UMETA(DisplayName = "KCI"),
	KOB UMETA(DisplayName = "KOB"),
	LBL UMETA(DisplayName = "LBL"),
	LEA UMETA(DisplayName = "LEA"),
	LEV UMETA(DisplayName = "LEV"),
	OFK UMETA(DisplayName = "OFK"),
	OH UMETA(DisplayName = "OH"),
	POK UMETA(DisplayName = "POK"),
	RNK UMETA(DisplayName = "RNK"),
	RRK UMETA(DisplayName = "RRK"),
	TAU UMETA(DisplayName = "TAU"),
	TAUd UMETA(DisplayName = "TAUd"),
	TRP UMETA(DisplayName = "TRP"),
	TRPd UMETA(DisplayName = "TRPd"),	
	UNR UMETA(DisplayName = "UNR"),
	UNRd UMETA(DisplayName = "UNRd"),
	UNS UMETA(DisplayName = "UNS"),
	UNSd UMETA(DisplayName = "UNSd"),
	UOHd UMETA(DisplayName = "UOHd"),
	WED UMETA(DisplayName = "WED")
};

USTRUCT(BlueprintType)
struct FPlayerArray
{
	GENERATED_BODY()

	// The following member variable will be accessible by Blueprint Graphs:
	UPROPERTY(BlueprintReadWrite, Category = "Player Location Array")
	TArray<FTransform> FPlayerLocationArray;

	UPROPERTY(BlueprintReadWrite, Category = "Player Location Array")
	TArray<float> FPlayerHeadingArray;

	UPROPERTY(BlueprintReadWrite, Category = "Player Location Array")
	TArray<float> FPlayerSpeedArray;

	UPROPERTY(BlueprintReadWrite, Category = "Player Location Array")
	TArray<float> FPlayerAccelArray;
	
	UPROPERTY(BlueprintReadWrite, Category = "Player Information")
	int playerJerseyNumber;

	UPROPERTY(BlueprintReadWrite, Category = "Player Information")
	ENFLPosition playerPosition;
};

USTRUCT(BlueprintType)
struct FFootballArray
{
	GENERATED_BODY()

	// The following member variable will be accessible by Blueprint Graphs:
	UPROPERTY(BlueprintReadWrite, Category = "Football Location Array")
	TArray<FTransform> FFootballLocationArray;

	UPROPERTY(BlueprintReadWrite, Category = "Football Location Array")
	TArray<float> FFootballSpeedArray;

	UPROPERTY(BlueprintReadWrite, Category = "Football Location Array")
	TArray<float> FFootballAccelArray;

	UPROPERTY(BlueprintReadWrite, Category = "Football Event Array")
	TMap<ENFLEvent, int> FFootballEventArray;
};


UCLASS()
class NFL_API AFormationController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFormationController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable, Category = "Fileread", meta = (Keywords = "Load"))
	static bool LoadTextFromFile(FString FileName, TArray<FString>& TextArray);

	UFUNCTION(BlueprintCallable, Category = "Fileread", meta = (Keywords = "Save"))
	static bool SaveArrayText(FString SaveDirectory, FString FileName, TArray<FString> SaveText, bool AllowOverwriting);

	UFUNCTION(BlueprintCallable, Category = "Fileread", meta = (Keywords = "Save"))
	static bool DeleteTextFile(FString SaveDirectory, FString FileName);

	UFUNCTION(BlueprintCallable, Category = "Fileread", meta = (Keywords = "Save"))
	void LoadFootballCSV(FString playfolder, FString SaveDirectory, FFootballArray& football);

	UFUNCTION(BlueprintCallable, Category = "Fileread", meta = (Keywords = "Save"))
	void LoadPlayerCSV(FString playfolder, FString SaveDirectory, FPlayerArray& someplayer, int& penaltyJerseyNumber, TArray<ENFLPenalty>& penaltyType);

	UFUNCTION(BlueprintCallable, Category = "Fileread", meta = (Keywords = "Save"))
	void readRandomFormation(FString playfolder, int& penaltyJerseyNumber, bool& penaltyHome, TArray<ENFLPenalty>& penaltyType, TArray<FFootballArray>& Football, TArray<FPlayerArray>& HomeTeam, TArray<FPlayerArray>& AwayTeam);
};
