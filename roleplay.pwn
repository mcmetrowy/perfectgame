//includes
#include a_samp
#include "/include/sscanf.inc" //Y_Less > 2.8.1
#include "/include/streamer.inc"
#include "/include/zcmd.inc"
#include "/include/mysql.inc"
#include "/include/foreach.inc"

#undef MAX_PLAYERS
#define MAX_PLAYERS 	5
#define COLOR_DARKBLUE	0x003366
#define COLOR_GRAY 		0xC3C3C3
#define COLOR_WHITE 	0xFFFFFF
#define COLOR_RED		0xFF0F3B
#define PlayerMarker 	100

main()
{
	print("Skrypt za³adowano pomyœlnie");
}

enum E_PLAYER
{
	pUID,
	pName[24],
	pLevel,
	pCash,
	Float:pHealth,
	Float:pArmor,
	pSkin,
	Float:pPosX,
	Float:pPosY,
	Float:pPosZ
}
new PlayerCache[MAX_PLAYERS][E_PLAYER];

public OnGameModeInit()
{
	mysql_init(LOG_ONLY_ERRORS);
	mysql_connect("zmien", "zmien", "zmien", "zmien");

	UsePlayerPedAnims();
	DisableInteriorEnterExits();
	ShowNameTags(false);
	ShowPlayerMarkers(1);
	LimitPlayerMarkerRadius(PlayerMarker);

	AddPlayerClass(0, 0.0, 0.0, 0.0, 0.0, 0,0, 0, 0, 0, 0);
	return 1;
}

public OnPlayerConnect(playerid)
{
	new name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, MAX_PLAYER_NAME);
	UnderscoreToSpace(name);
	new query[128];
	new data[128];
	format(query, sizeof(query), "SELECT * FROM members WHERE name = '%s'", name);

	mysql_query(query);
	mysql_store_result();
	if(mysql_fetch_row(data, "|"))
	{
		sscanf(data, "p<|>ds[24]ddffdfff",
				PlayerCache[playerid][pUID],
				PlayerCache[playerid][pName],
				PlayerCache[playerid][pLevel],
				PlayerCache[playerid][pCash],
				PlayerCache[playerid][pHealth],
				PlayerCache[playerid][pArmor],
				PlayerCache[playerid][pSkin],
				PlayerCache[playerid][pPosX],
				PlayerCache[playerid][pPosY],
				PlayerCache[playerid][pPosZ] );
	} else {
		SendClientMessage(playerid, -1, "Nie znaleziono Twojego konta!");
		Kick(playerid);
	}

	mysql_free_result();
	for(new c=0; c<100; c++)
		SendClientMessage(playerid, -1, " ");
	new string1[128], string2[128];
	format(string1, sizeof(string1), "Witamy Ciê {006600}%s{FFFFFF} na RolePlay!", PlayerCache[playerid][pName]);
	format(string2, sizeof(string2), "Zalogowano na postaæ: {006600}%s{FFFFFF}(UID:{006600} %d{FFFFFF}).", PlayerCache[playerid][pName], PlayerCache[playerid][pUID]);

	SendClientMessage(playerid, -1, string1);
	SendClientMessage(playerid, -1, string2);

	return 1;
}

public OnPlayerDisconnect(playerid, reason)
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

public OnPlayerDeath(playerid)
{
	SetPlayerHealth(playerid, 10);
	return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
	SetSpawnInfo(playerid, 0, PlayerCache[playerid][pSkin], PlayerCache[playerid][pPosX], PlayerCache[playerid][pPosY], PlayerCache[playerid][pPosZ], 0.0, 0, 0, 0, 0, 0, 0);
	SpawnPlayer(playerid);
	return 1;
}

public OnPlayerSpawn(playerid)
{
	GivePlayerMoney(playerid, PlayerCache[playerid][pCash]);
	SetPlayerHealth(playerid, PlayerCache[playerid][pHealth]);
	SetPlayerArmour(playerid, PlayerCache[playerid][pArmor]);

	SetPlayerPos(playerid, PlayerCache[playerid][pPosX], PlayerCache[playerid][pPosY], PlayerCache[playerid][pPosZ]);
	return 1;
}

public OnPlayerText(playerid, text[])
{
	new string[128];
	if(IsPlayerConnected(playerid))
	{
	  	if(strlen(text) > 65)
		{
			new line[66];
	  		format(line, sizeof(line), text);
	    	strdel(line, 66, strlen(line));
	 		format(string, sizeof(string),"%s mówi: {FFFFFF}%s", PlayerCache[playerid][pName], line);
	 		ShowText(playerid, COLOR_GRAY, 7.0, string);
			strdel(text, 0, 65);
			format(string, sizeof(string),"... %s", text);
	 		ShowText(playerid, COLOR_GRAY, 7.0, string);
	  		return 0;
		}
		else
		{
			format(string, sizeof(string),"%s mówi: {FFFFFF}%s", PlayerCache[playerid][pName], text);
	 		ShowText(playerid, COLOR_GRAY, 7.0, string);
	 		return 0;
		}
	}
	return 1;
}

public OnPlayerCommandPerformed(playerid, cmdtext[], success)//zcmd
{
	if(!success)
	{
		PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
	}
	return 1;
}

#include "/modules/cmd_player.inc"
#include "/modules/dialogs.inc"
#include "/modules/functions.inc"