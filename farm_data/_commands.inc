CMD:buyshovel(playerid)
{
	GivePlayerWeapon(playerid, 6, 1);
	return 1;
}

CMD:dig(playerid)
{
	new pWeapon = GetPlayerWeapon(playerid);
	new string[124];
	if(pWeapon == 6)
	{
		GetPlayerFrontPos(playerid, digPosX[playerid], digPosY[playerid], digPosZ[playerid], digPosA[playerid], 1.0);
		format(string, 124, " X %f Y %f Z %f", digPosX[playerid], digPosY[playerid], digPosZ[playerid]);
		SendClientMessage(playerid, -1, string);
		
		ApplyAnimation(playerid, "KNIFE", "Knife_4", 4.1, 0, 0, 0, 0, 0);
		
	}
	return 1;
}


CMD:plant(playerid)
{
	new 
		pWeapon = GetPlayerWeapon(playerid),
		dialogString[512];
		
	if(IsNearPlant(playerid)) return SendClientMessage(playerid, -1, "You cannot plant close to another plant.");

	if( pWeapon == 6 )
	{
		if( digPosX[playerid] == 0.00 && digPosY[playerid] == 0.00 ) return SendClientMessage(playerid, -1, "You need to /dig first.");
   		if (!IsPlayerInRangeOfPoint(playerid, 1.0, digPosX[playerid], digPosY[playerid], digPosZ[playerid])) 
   			return SendClientMessage(playerid, -1, "You must be near your last digged location.");

   		format(dialogString, sizeof dialogString,
		 "Seen name\t Amount\n\
		 Tomato Seeds\t %d pieces\n\
		 Cucumber Seeds\t %d pieces\n\
		 Potato Seeds\t %d pieces\n\
		 Lettuce Seeds\t %d pieces\
		 ", TomatoSeeds[playerid],
		CucumberSeeds[playerid],
		PotatoSeeds[playerid],
		LettuceSeeds[playerid]);

		ShowPlayerDialog(playerid, DIALOG_PLANT_LIST, DIALOG_STYLE_TABLIST_HEADERS, "Select your plant", dialogString, "Plant", "Cancel");
	}

	return 1;
}

CMD:giveseeds(playerid)
{
	TomatoSeeds[playerid] = 10;
	CucumberSeeds[playerid] = 10;
	PotatoSeeds[playerid] = 10;
	LettuceSeeds[playerid] = 10;

	return 1;
}

CMD:s(playerid)
{
	TomatoSeeds[playerid] += 10;
	CucumberSeeds[playerid] += 10;
	PotatoSeeds[playerid] += 10;
	LettuceSeeds[playerid] += 10;

	return 1;
}


CMD:pick(playerid)
{
	if(!IsNearPlant(playerid)) return SendClientMessage(playerid, -1, "You must be near the plant.");
	
	new PlantID = GetPlantID(playerid),
		str[128];
	new Float:ObjectX, Float:ObjectY, Float:ObjectZ;
	GetDynamicObjectPos(PlantInfo[PlantID][PlantObject], ObjectX, ObjectY, ObjectZ);

	SetPlayerFacingAngle(playerid, GetAngleToXY(playerid, ObjectX, ObjectY));

	ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.0, 0, 0, 0, 0, 0);


	if(PlantInfo[PlantID][PlantType] == TYPE_TOMATO)
	{
		pTomato[playerid] += PlantInfo[PlantID][PlantItem];
		format(str, sizeof str, "You have picked total %d Tomato", PlantInfo[PlantID][PlantItem]);
		PlantInfo[PlantID][PlantItem] = 0;
	}
	else if(PlantInfo[PlantID][PlantType] == TYPE_CUCUMBER)
	{
		pCucumber[playerid] += PlantInfo[PlantID][PlantItem];
		format(str, sizeof str, "You have picked total %d Cucumber", PlantInfo[PlantID][PlantItem]);
		PlantInfo[PlantID][PlantItem] = 0;	}
	else if(PlantInfo[PlantID][PlantType] == TYPE_POTATO)
	{
		pPotato[playerid] += PlantInfo[PlantID][PlantItem];
		format(str, sizeof str, "You have picked total %d Potato", PlantInfo[PlantID][PlantItem]);
		PlantInfo[PlantID][PlantItem] = 0;	}
	else if(PlantInfo[PlantID][PlantType] == TYPE_LETTUCE)
	{
		pLettuce[playerid] += PlantInfo[PlantID][PlantItem];
		format(str, sizeof str, "You have picked total %d Lettuce leaf-set", PlantInfo[PlantID][PlantItem]);
		PlantInfo[PlantID][PlantItem] = 0;
	}
	SendClientMessage(playerid, -1, "You have picked the plant!");
	DestroyPlant(PlantID);

	return 1;
}

CMD:pourwater(playerid)
{
	/*
	CRAETE A DETECTION TO LET PLAYER HAVE A BUCKET/ANYTHING AND CAN HAVE WATER WITH THEM TO POUR

	MAKE PLAYER_WATER_DATA -= 10; 
	*/


	if(!IsNearPlant(playerid)) return SendClientMessage(playerid, -1, "You must be near the plant.");
	new PlantID = GetPlantID(playerid);

	if(PlantInfo[PlantID][PlantWaterLevel] > 80) return SendClientMessage(playerid, -1, "The Plant doesn't need more water.");

	new Float:ObjectX, Float:ObjectY, Float:ObjectZ;
	GetDynamicObjectPos(PlantInfo[PlantID][PlantObject], ObjectX, ObjectY, ObjectZ);

	SetPlayerFacingAngle(playerid, GetAngleToXY(playerid, ObjectX, ObjectY));

	ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.0, 0, 0, 0, 0, 0);

	PlantInfo[PlantID][PlantWaterLevel] += 10;
	if(PlantInfo[PlantID][PlantHealth] < 80)
	{
		if(PlantInfo[PlantID][PlantHealth] > 20)
		{
			PlantInfo[PlantID][PlantHealth] += 40;
		}
	}

	format(PlantString, sizeof PlantString, "Lettuce Plant (ID:%d)\nPlant Health %d\n Water Level %d", PlantID, PlantInfo[PlantID][PlantHealth], PlantInfo[PlantID][PlantWaterLevel]);
	UpdateDynamic3DTextLabelText(PlantInfo[PlantID][PlantText],  -1, PlantString);
	return 1;
}


CMD:checkplant(playerid)
{

	if(!IsNearPlant(playerid)) return SendClientMessage(playerid, -1, "You must be near the plant.");
	new PlantID = GetPlantID(playerid),
		str[128];

	new Float:ObjectX, Float:ObjectY, Float:ObjectZ;
	GetDynamicObjectPos(PlantInfo[PlantID][PlantObject], ObjectX, ObjectY, ObjectZ);

	SetPlayerFacingAngle(playerid, GetAngleToXY(playerid, ObjectX, ObjectY));

	ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.0, 0, 0, 0, 0, 0);

	if(PlantInfo[PlantID][PlantType] == TYPE_TOMATO)
	{
		format(str, sizeof str, "The plant has total %d Tomato", PlantInfo[PlantID][PlantItem]);
	}

	else if(PlantInfo[PlantID][PlantType] == TYPE_CUCUMBER)
	{
			format(str, sizeof str, "The plant has total %d Cucumber", PlantInfo[PlantID][PlantItem]);
	}
	else if(PlantInfo[PlantID][PlantType] == TYPE_POTATO)
	{
			format(str, sizeof str, "The plant has total %d Potato", PlantInfo[PlantID][PlantItem]);
	}
	else if(PlantInfo[PlantID][PlantType] == TYPE_LETTUCE)
	{
			format(str, sizeof str, "The plant has total %d lettuce leaf-set", PlantInfo[PlantID][PlantItem]);
	}

	SendClientMessage(playerid, -1, str);
	return 1;
}

CMD:grab(playerid)
{
	if(!IsNearPlant(playerid)) return SendClientMessage(playerid, -1, "You must be near the plant.");
	new PlantID = GetPlantID(playerid),
		str[128];

	new Float:ObjectX, Float:ObjectY, Float:ObjectZ;
	GetDynamicObjectPos(PlantInfo[PlantID][PlantObject], ObjectX, ObjectY, ObjectZ);

	SetPlayerFacingAngle(playerid, GetAngleToXY(playerid, ObjectX, ObjectY));

	ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.0, 0, 0, 0, 0, 0);

	if(PlantInfo[PlantID][PlantType] == TYPE_TOMATO)
	{
		pTomato[playerid] += PlantInfo[PlantID][PlantItem];
		format(str, sizeof str, "You have picked total %d Tomato", PlantInfo[PlantID][PlantItem]);
		PlantInfo[PlantID][PlantItem] = 0;
	}
	else if(PlantInfo[PlantID][PlantType] == TYPE_CUCUMBER)
	{
		pCucumber[playerid] += PlantInfo[PlantID][PlantItem];
		format(str, sizeof str, "You have picked total %d Cucumber", PlantInfo[PlantID][PlantItem]);
		PlantInfo[PlantID][PlantItem] = 0;	}
	else if(PlantInfo[PlantID][PlantType] == TYPE_POTATO)
	{
		pPotato[playerid] += PlantInfo[PlantID][PlantItem];
		format(str, sizeof str, "You have picked total %d Potato", PlantInfo[PlantID][PlantItem]);
		PlantInfo[PlantID][PlantItem] = 0;	}
	else if(PlantInfo[PlantID][PlantType] == TYPE_LETTUCE)
	{
		pLettuce[playerid] += PlantInfo[PlantID][PlantItem];
		format(str, sizeof str, "You have picked total %d Lettuce leaf-set", PlantInfo[PlantID][PlantItem]);
		PlantInfo[PlantID][PlantItem] = 0;
	}
	SendClientMessage(playerid, -1, str);
	return 1;
}

CMD:inv(playerid)
{
	new str[128];
	format(str, sizeof str, "You have Tomato (%d), Cucumber (%d), Potato (%d), Lettuce leaf-set (%d)",
									pTomato[playerid], pCucumber[playerid], pPotato[playerid], pLettuce[playerid]);
	SendClientMessage(playerid, -1, str);
	return 1;
}