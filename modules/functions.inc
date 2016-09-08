UnderscoreToSpace(name[])
{
	new pos = strfind(name,"_", true);
	if( pos != -1 )
	name[pos] = ' ';
}

ShowText(playerid, color, Float:range, text[])
{
    new Float:Pos[3];
	GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);
	new vw = GetPlayerVirtualWorld(playerid);
	new int = GetPlayerInterior(playerid);
    foreach(Player, i)
	{
	    if(DoInRange(range, i, Pos[0], Pos[1], Pos[2]) && GetPlayerInterior(i) == int && GetPlayerVirtualWorld(i) == vw)
		{
  			SendClientMessage(i, color, text);
		}
	}
	return 1;
}

stock DoInRange(Float: radi, playerid, Float:x, Float:y, Float:z)
{
	if(IsPlayerInRangeOfPoint(playerid, radi, x, y, z)) return 1;
	return 0;
}

forward PlayerBW(playerid);
public PlayerBW(playerid)
{
	SpawnPlayer(playerid);
	TogglePlayerControllable(playerid, 1);
	SetPlayerDrunkLevel(playerid, 50000);
	SetPlayerHealth(playerid, 10);
	ClearAnimations(playerid);
	PlayerHasBW[playerid] = false;
	SetTimer("LowerDrunk", 200000, false);
	return 1;
}

forward LowerDrunk(playerid);
public LowerDrunk(playerid)
{
	SetPlayerDrunkLevel(playerid, 0);
	return 1;
}

SavePlayer(playerid)
{
	new Float:health, Float:armor, Float:posX, Float:posY, Float:posZ, query[256];
	GetPlayerHealth(playerid, health);
	GetPlayerArmour(playerid, armor);
	GetPlayerPos(playerid, posX, posY, posZ);
 
	format(query, sizeof(query), "UPDATE members SET health = '%f', armor = '%f', posX = '%f', posY = '%f', posZ = '%f' WHERE uid = '%d'",
		health, armor, posX, posY, posZ, PlayerCache[playerid][pUID]);
 
 	mysql_query(query);
 	return 1;
}

PreloadAllAnimLibs(playerid)
{
  ApplyAnimation(playerid,"BOMBER","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"RAPPING","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"SHOP","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"BEACH","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"SMOKING","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"FOOD","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"ON_LOOKERS","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"DEALER","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"CRACK","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"CARRY","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"COP_AMBIENT","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"PARK","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"INT_HOUSE","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"FOOD","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"PED","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"SWEET","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"FREEWEIGHTS","null",0.0,0,0,0,0,0);
       
  ApplyAnimation(playerid,"AIRPORT","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"Attractors","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"BAR","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"BASEBALL","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"BD_FIRE","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"benchpress","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"BF_injection","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"BLOWJOBZ","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"BOX","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"BSKTBALL","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"BUDDY","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"CAMERA","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"CARRY","null",0.0,0,0,0,0,0);
 
  ClearAnimations(playerid);
  return 1;
}