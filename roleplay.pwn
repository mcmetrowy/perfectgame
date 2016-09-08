//includes
#include a_samp
#include "/include/sscanf.inc" //Y_Less > 2.8.1
#include "/include/streamer.inc"
#include "/include/zcmd.inc"
#include "/include/mysql.inc"
#include "/include/foreach.inc"

#undef MAX_PLAYERS
#define MAX_PLAYERS 	5
#define COLOR_DARKBLUE	0x003366FF
#define COLOR_GRAY 		0xC3C3C3FF
#define COLOR_WHITE 	0xFFFFFFFF
#define COLOR_RED		0xFF0F3BFF
#define PlayerMarker 	100

new bool:PlayerHasBW[200];

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
	mysql_connect("localhost", "root", "DEZVLOPS", "youtube");

	UsePlayerPedAnims();
	DisableInteriorEnterExits();
	ShowNameTags(false);
	ShowPlayerMarkers(1);
	LimitPlayerMarkerRadius(PlayerMarker);

	AddPlayerClass(0, 1552.7522, -1675.7068, 16.1953, 0.0, 0,0, 0, 0, 0, 0);


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
	SavePlayer(playerid);
	return 1;
}

public OnPlayerDeath(playerid)
{
	new Float:posX, Float:posY, Float:posZ;
	PlayerHasBW[playerid] = true;
	GetPlayerPos(playerid, posX, posY, posZ);
	SetPlayerPos(playerid, posX, posY, posZ);
	SetSpawnInfo(playerid, 0, PlayerCache[playerid][pSkin], posX, posY, posZ, 0.0, 0, 0, 0, 0, 0, 0);
	TogglePlayerControllable(playerid, 0);
	ApplyAnimation(playerid,"CRACK","crckdeth2",4.1,0,0,0,1,0);
	ApplyAnimation(playerid,"CRACK","crckdeth2",4.1,0,0,0,1,0);
	SetTimer("PlayerBW", 300000, false);
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
	PreloadAllAnimLibs(playerid);
	return 1;
}

public OnPlayerText(playerid, text[])
{
	if(PlayerHasBW[playerid] == false)
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
	} else {
		SendClientMessage(playerid, -1, "Nie mo¿esz mówiæ podczas BW!");
		return 0;
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

/* co dodac?
do systemu bw textdraw, lekko naprawic /me ktore powinno przechodzic do drugiej linii
jak jest za dlugie, albo nie wysylac sie w ogole jesli wiadomosc jest za dluga.
dodac podstawowe komendy rp.
*/