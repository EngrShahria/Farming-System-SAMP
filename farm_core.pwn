#include <a_samp>
#include <streamer>
#include <ZCMD>

//Tomato, Cucumber, Potato, Lettuce
//player enters cmd to plant a seed, /plant can work
//will give dialog on what plant he wishes to grow

new 
	Float:digPosX[MAX_PLAYERS],
	Float:digPosY[MAX_PLAYERS],
	Float:digPosZ[MAX_PLAYERS],
	Float:digPosA[MAX_PLAYERS];

#define DIALOG_PLANT_LIST 1
#define DIALOG_TOMATO 2
#define DIALOG_CUCUMBER 3
#define DIALOG_POTATO 4
#define DIALOG_LETTUCE 5

#define TYPE_TOMATO 1 
#define TYPE_CUCUMBER 2
#define TYPE_POTATO 3
#define TYPE_LETTUCE 4

new //PLAYER SEED 
	TomatoSeeds[MAX_PLAYERS], 
	CucumberSeeds[MAX_PLAYERS],
	PotatoSeeds[MAX_PLAYERS],
	LettuceSeeds[MAX_PLAYERS];

new 
	pTomato[MAX_PLAYERS],
	pCucumber[MAX_PLAYERS],
	pPotato[MAX_PLAYERS],
	pLettuce[MAX_PLAYERS];


new 
	PlantString[124];
	
#define MAX_PLANTS 500
#define PLAYER_MAX_PLANTS 10

new //OBJECTS 
	SeedMaxObject[MAX_PLAYERS]
	;

enum  _plantinfo
{
	
	PlantCreated,
	PlantObject,
	Float:PlantPosX,
	Float:PlantPosY,
	Float:PlantPosZ,
	PlantType,
	PlantWaterLevel,
	PlantHealth,
	Text3D:PlantText,
	PlantItem,
	PlantItemTimer
}
new PlantInfo[MAX_PLANTS][_plantinfo];

forward PlantTimer(pID);
forward WaterTimer(pID);


public OnGameModeInit()
{
	return 1;
}
public OnGameModeExit()
{
	return 1;
}
public OnPlayerConnect(playerid)
{	

	return 1;
}
public OnPlayerDisconnect(playerid, reason)
{
	ResetPlayerPlants(playerid);
	ResetPlantSeeds(playerid);
	return 1;
}

#include "farm_data/_important.inc"
#include "farm_data/_functions.inc"
#include "farm_data/_commands.inc"
#include "farm_data/_admins.inc"


/*
A FEW THINGS YOU NEED TO KNOW BEFORE IMPLEMENT THE SCRIPT

- CREATE PROPER /buyshovel COMMAND

- CREATE PROPER /buybucket /getwater things [ PLAYER BASED ]

- CREATE A WATER TIMER [ Updates EVERY MINUTE ]

- Useful items you need.

- DETECTION, IF THE WATER MORE THAN 150+, PLANT DIES.
*/


