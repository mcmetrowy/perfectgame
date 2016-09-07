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