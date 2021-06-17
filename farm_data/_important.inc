stock ResetPlantSeeds(playerid)
{
	TomatoSeeds[playerid] = 0;
	CucumberSeeds[playerid] = 0;
	PotatoSeeds[playerid] = 0;
	LettuceSeeds[playerid] = 0;
	return 1;
}

stock LoadPlantSeeds(playerid) //USE PLAYER LOADING SYSTEM
{
	TomatoSeeds[playerid] = 0;
	CucumberSeeds[playerid] = 0;
	PotatoSeeds[playerid] = 0;
	LettuceSeeds[playerid] = 0;
	return 1;
}

stock ResetPlayerPlants(playerid)
{

	pTomato[playerid] = 0;
	pCucumber[playerid] = 0;
	pPotato[playerid] = 0;
	pLettuce[playerid] = 0; 

	return 1;
}

stock LoadPlayerPlants(playerid) //USE PLAYER LOADING SYSTEM
{
	pTomato[playerid] = 0;
	pCucumber[playerid] = 0;
	pPotato[playerid] = 0;
	pLettuce[playerid] = 0; 
	return 1;
}

stock NearDynamicObject(playerid, objectid, Float:range)
{
	new Float:X, Float:Y, Float:Z;
	GetDynamicObjectPos(objectid, X, Y, Z);
	if(IsPlayerInRangeOfPoint(playerid, range, X, Y, Z)) return true;
	return false;
}

stock IsNearPlant(playerid)
{
	for(new i; i < MAX_PLANTS; i++) 
		if( PlantInfo[i][PlantCreated] == 1)
		{
			if(IsPlayerInRangeOfPoint(playerid, 2.0, PlantInfo[i][PlantPosX], PlantInfo[i][PlantPosY], PlantInfo[i][PlantPosZ]) )
				return 1;
		}	 
	return 0;
}

stock GetPlantID(playerid)
{
	new _pID;
	for(new i; i < MAX_PLANTS; i++) 
		if( PlantInfo[i][PlantCreated] == 1)
		{
			if(IsPlayerInRangeOfPoint(playerid, 2.0, PlantInfo[i][PlantPosX], PlantInfo[i][PlantPosY], PlantInfo[i][PlantPosZ]) )
			{ 
				_pID = i;
				break;
			}
		}	 
	return _pID;
}

stock GetPlayerFrontPos(playerid, &Float:x, &Float:y, &Float:z, &Float:a, Float:dist)
{
	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, a);

	x += (dist * floatsin(-a, degrees));
	y += (dist * floatcos(-a, degrees));
}

stock Float:GetAngleToXY(playerid, Float:X, Float:Y)
{	
	new  Float:Angle;
	new Float:CurrentX, Float:CurrentY, Float:CurrentZ;
	GetPlayerPos(playerid, CurrentX, CurrentY, CurrentZ);

 	Angle = atan2(Y-CurrentY, X-CurrentX);
  	Angle = floatsub(Angle, 90.0);
  	if(Angle < 0.0) Angle = floatadd(Angle, 360.0);
  	return Angle;
}