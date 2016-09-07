//CMD ADMINA

CMD:setadmin(playerid, params[])
{
	new give_playerid, name[MAX_PLAYER_NAME],
	string[128], string2[128],
	level, query[256];

	GetPlayerName(give_playerid, name, sizeof(name));

	if(sscanf(params, "ui", give_playerid, level))
	{
		SendClientMessage(playerid, 0xFF0F3B, "[INFO] {ffffff}Prawid³owe u¿ycie komendy: /setadmin [ID] [LEVEL]");
		PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		return 1;
	}

	if(!IsPlayerConnected(give_playerid))
	{
		SendClientMessage(playerid, 0xFF0F3B, "[INFO] {ffffff}Gracz o takim ID nie istnieje!");
		PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		return 1;
	}
	if(level < 0 || level > 6)
	{
		SendClientMessage(playerid, 0xFF0F3B, "[INFO] {ffffff}Level nie mo¿e byæ mniejszy ni¿ 0 i wiêkszy od 6!");
		PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		return 1;
	}

	format(string, sizeof(string), "{ff0f3b}Administrator {FFFFFF}%s nada³ ci %d poziom! SprawdŸ nowe komendy pod /acmd!", PlayerCache[playerid][pName], level);
	SendClientMessage(give_playerid, -1, string);

	format(string2, sizeof(string2), "Nada³eœ graczowi {ff0f3b}%s {FFFFFF}(ID: %d) %d poziom admina!", name, give_playerid, level);
	SendClientMessage(playerid, -1, string2);

	format(query, sizeof(query), "UPDATE members SET level = '%d' WHERE uid = '%d'", level, PlayerCache[playerid][pUID]);
	mysql_query(query);
	return 1;
}

CMD:sethp(playerid, params[])
{
	new give_playerid,
		name[MAX_PLAYER_NAME],
		string[128],
		hp;

	GetPlayerName(give_playerid, name, sizeof(name));

	if(sscanf(params, "ui", give_playerid, hp))
	{
		SendClientMessage(playerid, 0xFF0F3B, "[INFO] {ffffff}Prawid³owe u¿ycie komendy: /hp [ID] [ILOŒÆ HP]");
		PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		return 1;
	}

	if(!IsPlayerConnected(give_playerid))
	{
		SendClientMessage(playerid, 0xFF0F3B, "[INFO] {ffffff}Gracz o takim ID nie istnieje!");
		PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		return 1;
	}

	if(hp < 0 || hp > 100)
	{
		SendClientMessage(playerid, 0xFF0F3B, "[INFO] {ffffff}Nie mo¿esz nadaæ mniej ni¿ 0, ani wiêcej ni¿ 100 hp!");
		PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		return 1;
	}

	GetPlayerName(playerid, name, sizeof(name));
	format(string, sizeof(string), "{ff0f3b}Administrator{ffffff} %s da³ ci %i zdrowia!", name, hp);

	SetPlayerHealth(give_playerid, hp);
	SendClientMessage(give_playerid, -1, string);
	return 1;
}

CMD:setarmor(playerid, params[])
{
	new give_playerid,
		name[MAX_PLAYER_NAME],
		string[128],
		armor;

	GetPlayerName(give_playerid, name, sizeof(name));

	if(sscanf(params, "ui", give_playerid, armor))
	{
		SendClientMessage(playerid, 0xFF0F3B, "[INFO] {ffffff}Prawid³owe u¿ycie komendy: /setarmor [ID] [ILOŒÆ ARMOR]");
		PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		return 1;
	}

	if(!IsPlayerConnected(give_playerid))
	{
		SendClientMessage(playerid, 0xFF0F3B, "[INFO] {ffffff}Gracz o takim ID nie istnieje!");
		PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		return 1;
	}

	if(armor < 0 || armor > 100)
	{
		SendClientMessage(playerid, 0xFF0F3B, "[INFO]{ffffff} Nie mo¿esz nadaæ mniej ni¿ 0, ani wiêcej ni¿ 100 armora!");
		PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		return 1;
	}

	GetPlayerName(playerid, name, sizeof(name));
	format(string, sizeof(string), "{ff0f3b}Administrator {ffffff}%s da³ ci %i armora!", name, armor);

	SetPlayerArmour(give_playerid, armor);
	SendClientMessage(give_playerid, -1, string);
	return 1;
}