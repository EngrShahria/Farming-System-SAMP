public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(dialogid == DIALOG_PLANT_LIST)
	{
		if(!response) return 0;
		switch(listitem)
		{
			case 0: //Tomato Seeds
			{
				if(TomatoSeeds[playerid] == 0) return SendClientMessage(playerid, -1, "You do not have Tomato plant seeds, please buy them.");
				if(SeedMaxObject[playerid] >= MAX_PLANTS) return SendClientMessage(playerid, -1, "You already have maximum plants.");
				CreatePlant(playerid, TYPE_TOMATO);		
			}
			case 1: //Cucumber Seeds
			{
				if(CucumberSeeds[playerid] == 0) return SendClientMessage(playerid, -1, "You do not have Cucumber plant seeds, please buy them.");
				if(SeedMaxObject[playerid] >= MAX_PLANTS) return SendClientMessage(playerid, -1, "You already have maximum plants.");
				CreatePlant(playerid, TYPE_CUCUMBER);
			}
			case 2: //Potato Seeds
			{
				if(PotatoSeeds[playerid] == 0) return SendClientMessage(playerid, -1, "You do not have Potato plant seeds, please buy them.");
				if(SeedMaxObject[playerid] >= MAX_PLANTS) return SendClientMessage(playerid, -1, "You already have maximum plants.");
				CreatePlant(playerid, TYPE_POTATO);
			}
			case 3: //Lettuce Seeds 
			{
				if(LettuceSeeds[playerid] == 0) return SendClientMessage(playerid, -1, "You do not have Lattuce plant seeds, please buy them.");
				if(SeedMaxObject[playerid] >= MAX_PLANTS) return SendClientMessage(playerid, -1, "You already have maximum plants.");
				CreatePlant(playerid, TYPE_LETTUCE);
			}
			
		}
		return 1;
	}

	return 0;
}


//==============================================================================

/* {
	PlantCreated,
	PlantObject,
	Float:PlantPosX,
	Float:PlantPosY,
	Float:PlantPosZ,
	PlantType,
	PlantWaterLevel,
	PlantHealth,
	Text3D:PlantText*/
stock GetFreePlantID()
{
	new FreeID;
	for(new i; i < MAX_PLANTS; i++)
	{
		if(PlantInfo[i][PlantCreated] == 0) 
		{ 
			FreeID = i;
			break;
		}
	}
	return FreeID;
}


stock CreatePlant(playerid, type)
{
	new SeedID;
	if(type == TYPE_TOMATO)
	{
		SendClientMessage(playerid, -1, "PlantTomatoSeeds"); // 855
		SeedID = GetFreePlantID();

		PlantInfo[SeedID][PlantCreated] = 1;
		PlantInfo[SeedID][PlantObject] = CreateDynamicObject(811, digPosX[playerid], digPosY[playerid], digPosZ[playerid], 0, 0, 0, -1);

		PlantInfo[SeedID][PlantPosX] = digPosX[playerid];
		PlantInfo[SeedID][PlantPosY] = digPosY[playerid];
		PlantInfo[SeedID][PlantPosZ] = digPosZ[playerid];


		PlantInfo[SeedID][PlantWaterLevel]  = random(100) +8;
		PlantInfo[SeedID][PlantHealth] = random(100) +8;

		format(PlantString, sizeof PlantString, "Tomato Plant (ID:%d)\nPlant Health %d\n Water Level %d", SeedID, PlantInfo[SeedID][PlantHealth], PlantInfo[SeedID][PlantWaterLevel]);
		PlantInfo[SeedID][PlantText] = CreateDynamic3DTextLabel(PlantString, -1, digPosX[playerid], digPosY[playerid], digPosZ[playerid] - 1.0, 5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1);
		
		ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.0, 0, 0, 0, 0, 0);

		PlantInfo[SeedID][PlantItemTimer] = SetTimerEx("PlantTimer", 5*6000, true, "d", SeedID);

		PlantInfo[SeedID][PlantType] = TYPE_TOMATO;
		digPosX[playerid] = 0.0;
		digPosY[playerid] = 0.0;
		digPosZ[playerid] = 0.0;
		TomatoSeeds[playerid]--;
	}
	if(type == TYPE_CUCUMBER)
	{
		SendClientMessage(playerid, -1, "PlantCucumberSeeds"); //2010
		SeedID = GetFreePlantID();
		PlantInfo[SeedID][PlantCreated] = 1;

		PlantInfo[SeedID][PlantObject] = CreateDynamicObject(2011, digPosX[playerid], digPosY[playerid], digPosZ[playerid] -2.2, 0, 0, 0, -1);
		
		PlantInfo[SeedID][PlantWaterLevel] = random(100) +8;

		PlantInfo[SeedID][PlantHealth] = random(100) +8;


		format(PlantString, sizeof PlantString, "Cucumber Plant (ID%d)\nPlant Health %d\n Water Level %d",SeedID, PlantInfo[SeedID][PlantHealth], PlantInfo[SeedID][PlantWaterLevel]);
		PlantInfo[SeedID][PlantText] = CreateDynamic3DTextLabel(PlantString, -1, digPosX[playerid], digPosY[playerid], digPosZ[playerid] -1.0, 5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1);

		PlantInfo[SeedID][PlantPosX] = digPosX[playerid];
		PlantInfo[SeedID][PlantPosY] = digPosY[playerid];
		PlantInfo[SeedID][PlantPosZ] = digPosZ[playerid];

		ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.0, 0, 0, 0, 0, 0);


		PlantInfo[SeedID][PlantType] = TYPE_CUCUMBER;
		PlantInfo[SeedID][PlantItemTimer] = SetTimerEx("PlantTimer", 5*6000, true, "d", SeedID);


		digPosX[playerid] = 0.0;
		digPosY[playerid] = 0.0;
		digPosZ[playerid] = 0.0;
		CucumberSeeds[playerid]--;
	}

	if(type == TYPE_POTATO)
	{
		SendClientMessage(playerid, -1, "PlantPotatoSeeds"); //861
		SeedID = GetFreePlantID();

		PlantInfo[SeedID][PlantCreated] = 1;

		PlantInfo[SeedID][PlantObject] = CreateDynamicObject(862, digPosX[playerid], digPosY[playerid], digPosZ[playerid] - 1.20, 0, 0, 0, -1);
		
		PlantInfo[SeedID][PlantWaterLevel] = random(100) +8;

		PlantInfo[SeedID][PlantHealth] = random(100) +8;


		format(PlantString, sizeof PlantString, "Potato Plant (ID:%d)\nPlant Health %d\n Water Level %d", SeedID, PlantInfo[SeedID][PlantHealth], PlantInfo[SeedID][PlantWaterLevel]);
		PlantInfo[SeedID][PlantText] = CreateDynamic3DTextLabel(PlantString, -1, digPosX[playerid], digPosY[playerid], digPosZ[playerid] - 1.0, 5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1);
		

		PlantInfo[SeedID][PlantPosX] = digPosX[playerid];
		PlantInfo[SeedID][PlantPosY] = digPosY[playerid];
		PlantInfo[SeedID][PlantPosZ] = digPosZ[playerid];
		
		ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.0, 0, 0, 0, 0, 0);

		PlantInfo[SeedID][PlantType] = TYPE_POTATO;
		PlantInfo[SeedID][PlantItemTimer] = SetTimerEx("PlantTimer", 5*6000, true, "d", SeedID);

		digPosX[playerid] = 0.0;
		digPosY[playerid] = 0.0;
		digPosZ[playerid] = 0.0;
		PotatoSeeds[playerid]--;
	}
	if(type == TYPE_LETTUCE)
	{
		SendClientMessage(playerid, -1, "PlantLettuceSeeds"); //860 for later use
		SeedID = GetFreePlantID();
		PlantInfo[SeedID][PlantObject] = CreateDynamicObject(859, digPosX[playerid], digPosY[playerid], digPosZ[playerid] - 1, 0, 0, 0, -1);
		
		PlantInfo[SeedID][PlantCreated] = 1;

		PlantInfo[SeedID][PlantWaterLevel] = random(100) +8;

		PlantInfo[SeedID][PlantHealth] = random(100) +8;

		format(PlantString, sizeof PlantString, "Lettuce Plant (ID:%d)\nPlant Health %d\n Water Level %d",SeedID, PlantInfo[SeedID][PlantHealth], PlantInfo[SeedID][PlantWaterLevel]);
		PlantInfo[SeedID][PlantText] = CreateDynamic3DTextLabel(PlantString, -1, digPosX[playerid], digPosY[playerid], digPosZ[playerid] - 1.0, 5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1);
		ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.0, 0, 0, 0, 0, 0);

		PlantInfo[SeedID][PlantPosX] = digPosX[playerid];
		PlantInfo[SeedID][PlantPosY] = digPosY[playerid];
		PlantInfo[SeedID][PlantPosZ] = digPosZ[playerid];

		PlantInfo[SeedID][PlantType] = TYPE_LETTUCE;
		PlantInfo[SeedID][PlantItemTimer] = SetTimerEx("PlantTimer", 5*6000, true, "d", SeedID);

		digPosX[playerid] = 0.0;
		digPosY[playerid] = 0.0;
		digPosZ[playerid] = 0.0;
		LettuceSeeds[playerid]--;
	}
	return 1;
}

stock DestroyPlant(ID)
{
	if(PlantInfo[ID][PlantCreated] == 0 ) return 0;

	if(IsValidDynamicObject(PlantInfo[ID][PlantObject])) 
		DestroyDynamicObject(PlantInfo[ID][PlantObject]);
	if(IsValidDynamic3DTextLabel(PlantInfo[ID][PlantText]))
		DestroyDynamic3DTextLabel(PlantInfo[ID][PlantText]);

	PlantInfo[ID][PlantCreated] = 0;
	PlantInfo[ID][PlantWaterLevel] = 0;
	PlantInfo[ID][PlantHealth] = 0;	
	PlantInfo[ID][PlantType] = 0;
	PlantInfo[ID][PlantItem] = 0;

	KillTimer(PlantInfo[ID][PlantItemTimer]);
	return 1;
}

public PlantTimer(pID)
{
	new items = random(6);
	new ran = random(5),
		ran2 = random(3);

	if(PlantInfo[pID][PlantHealth] >= 9)
	{
		if(PlantInfo[pID][PlantItem] < 40){
			PlantInfo[pID][PlantItem] += items;
		}
				
		PlantInfo[pID][PlantHealth] -= ran2;
		PlantInfo[pID][PlantWaterLevel] -= ran;
	}

	if(PlantInfo[pID][PlantWaterLevel] <= 10)
	{
		PlantInfo[pID][PlantHealth] -= ran2;
	}
	if(PlantInfo[pID][PlantWaterLevel] >= 50)
	{
		PlantInfo[pID][PlantHealth] += ran2;
	}
	if(PlantInfo[pID][PlantHealth] <= 3)
	{
		DestroyPlant(pID);
	}

	if(PlantInfo[pID][PlantWaterLevel] <= 1)
	{
		PlantInfo[pID][PlantWaterLevel] = 0;
	}
	if(PlantInfo[pID][PlantHealth] >= 100)
	{
		PlantInfo[pID][PlantHealth] = 100;
	}

	if(PlantInfo[pID][PlantType] == TYPE_TOMATO)
	{
		format(PlantString, sizeof PlantString, "Tomato Plant (ID:%d)\nPlant Health %d\n Water Level %d", pID, PlantInfo[pID][PlantHealth], PlantInfo[pID][PlantWaterLevel]);
	}

	else if(PlantInfo[pID][PlantType] == TYPE_CUCUMBER)
	{
		format(PlantString, sizeof PlantString, "Cucumber Plant (ID:%d)\nPlant Health %d\n Water Level %d", pID, PlantInfo[pID][PlantHealth], PlantInfo[pID][PlantWaterLevel]);
	}
	else if(PlantInfo[pID][PlantType] == TYPE_POTATO)
	{
		format(PlantString, sizeof PlantString, "Potato Plant (ID:%d)\nPlant Health %d\n Water Level %d", pID, PlantInfo[pID][PlantHealth], PlantInfo[pID][PlantWaterLevel]);
	}
	else if(PlantInfo[pID][PlantType] == TYPE_LETTUCE)
	{
		format(PlantString, sizeof PlantString, "Lettuce Plant (ID:%d)\nPlant Health %d\n Water Level %d", pID, PlantInfo[pID][PlantHealth], PlantInfo[pID][PlantWaterLevel]);
	}
	UpdateDynamic3DTextLabelText(PlantInfo[pID][PlantText],  -1, PlantString);
	return 1;
}

