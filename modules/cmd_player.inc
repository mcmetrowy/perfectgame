//CMD ADMINA

CMD:setadmin(playerid, params[])
{
	new give_playerid, name[MAX_PLAYER_NAME],
	string[128], string2[128],
	level, query[256];

	GetPlayerName(give_playerid, name, sizeof(name));

	if(PlayerCache[playerid][pLevel] != 6)
	{
		SendClientMessage(playerid, 0xFF0F3BFF, "[INFO] {ffffff}Nie masz uprawnieñ do u¿ycia tej komendy!");
		PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		return 1;
	}

	if(sscanf(params, "ui", give_playerid, level))
	{
		SendClientMessage(playerid, 0xFF0F3BFF, "[INFO] {ffffff}Prawid³owe u¿ycie komendy: /setadmin [ID] [LEVEL]");
		PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		return 1;
	}

	if(!IsPlayerConnected(give_playerid))
	{
		SendClientMessage(playerid, 0xFF0F3BFF, "[INFO] {ffffff}Gracz o takim ID nie istnieje!");
		PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		return 1;
	}
	if(level < 0 || level > 6)
	{
		SendClientMessage(playerid, 0xFF0F3BFF, "[INFO] {ffffff}Level nie mo¿e byæ mniejszy ni¿ 0 i wiêkszy od 6!");
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

CMD:hp(playerid, params[])
{
	new give_playerid,
		name[MAX_PLAYER_NAME],
		string[128],
		hp;

	if(PlayerCache[playerid][pLevel] != 6)
	{
		SendClientMessage(playerid, 0xFF0F3BFF, "[INFO] {ffffff}Nie masz uprawnieñ do u¿ycia tej komendy!");
		PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		return 1;
	}

	GetPlayerName(give_playerid, name, sizeof(name));

	if(sscanf(params, "ui", give_playerid, hp))
	{
		SendClientMessage(playerid, 0xFF0F3BFF, "[INFO] {ffffff}Prawid³owe u¿ycie komendy: /hp [ID] [ILOŒÆ HP]");
		PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		return 1;
	}

	if(!IsPlayerConnected(give_playerid))
	{
		SendClientMessage(playerid, 0xFF0F3BFF, "[INFO] {ffffff}Gracz o takim ID nie istnieje!");
		PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		return 1;
	}

	if(hp < 1 || hp > 100)
	{
		SendClientMessage(playerid, 0xFF0F3BFF, "[INFO] {ffffff}Nie mo¿esz nadaæ mniej ni¿ 0, ani wiêcej ni¿ 100 hp!");
		PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		return 1;
	}

	GetPlayerName(playerid, name, sizeof(name));
	format(string, sizeof(string), "{ff0f3b}Administrator{ffffff} %s da³ ci %i zdrowia!", name, hp);

	SetPlayerHealth(give_playerid, hp);
	SendClientMessage(give_playerid, -1, string);
	return 1;
}

CMD:me(playerid,params[])
{
    new text[144];
    if(sscanf(params,"s[144]",text))
    {
        SendClientMessage(playerid, 0xFF0F3BFF, "[INFO] {ffffff}Prawid³owe u¿ycie komendy: /me [tekst]");
        PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
        return 1;
    }
 
    //oblsuga blêdów
 
    new name[MAX_PLAYER_NAME], Float:x, Float:y, Float:z,vw;
    GetPlayerName(playerid, name, sizeof(name));
    for(new i = 0, len=strlen(name); i < len; i++)
    {
        if(name[i] == '_') name[i] = ' ';
    }
 
    text[0] = tolower(text[0]);
    if(text[strlen(text)-1] != '.')
        strins(text, ".", strlen(text));
 
    GetPlayerPos(playerid,x,y,z);
    vw=GetPlayerVirtualWorld(playerid);
 
    format(text, sizeof(text), "* %s %s", name, text);
 
    for(new i=0,pool=GetPlayerPoolSize();i<=pool;i++)
    {
        if(IsPlayerConnected(i) && GetPlayerVirtualWorld(i)==vw && IsPlayerInRangeOfPoint(i, 20.0, x, y, z))
        {
            SendClientMessage(playerid, 0xC2A2DAFF, text);
 
        }
    }
    return 1;
}