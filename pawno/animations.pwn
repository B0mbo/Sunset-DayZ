//Animations by Bombo
//Version: 1.0.1
//01.03.2014

#include<crashdetect>
#include<a_samp>

#define INVALID_TIMER_ID 0xFFFF

new gDebShow;
new gDebugPlayerID;

#pragma unused gDebShow
#pragma unused gDebugPlayerID

forward ShowAnim();

main()
{
	print("--------------------------------------");
	print(" Animations by Bombo");
	print("--------------------------------------\n");
}

public ShowAnim()
{
	static prev_anim;
	new anim;
	new str[64];

	if(!IsPlayerConnected(gDebugPlayerID))
	{
	    KillTimer(gDebShow);
	    return;
	}

    anim = GetPlayerAnimationIndex(gDebugPlayerID);
    if(prev_anim != anim)
    {
		format(str, sizeof(str), "Animation code: %d", anim);
		SendClientMessage(0, 0x55FFCAFF, str);
		prev_anim = anim;
	}
}

public OnFilterScriptInit()
{
	gDebShow = INVALID_TIMER_ID;
//	gDebShow = SetTimer("ShowAnim", 100, true);
}

public OnFilterScriptExit()
{
	if(gDebShow != INVALID_TIMER_ID)
		KillTimer(gDebShow);
}

public OnPlayerCommandText(playerid, cmdtext[])
{
	if(strcmp(cmdtext, "/animations", true) == 0)
	{
		if(gDebShow == INVALID_TIMER_ID)
		{
		    gDebugPlayerID = playerid;
			gDebShow = SetTimer("ShowAnim", 100, true);
			SendClientMessage(playerid, 0xFF00FFFF, "Animations: debugging is ON");
		}
		else
		{
			KillTimer(gDebShow);
			gDebShow = INVALID_TIMER_ID;
			SendClientMessage(playerid, 0xFF00FFFF, "Animations: debugging is OFF");
		}
	    return 1;
	}

	return 0;
}

