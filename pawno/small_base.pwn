// Лифт в высотке
// This is a comment
// uncomment the line below if you want to write a filterscript
//#define FILTERSCRIPT

#include <crashdetect>
#include <a_samp>
#include <streamer>

#include"defines.inc"

//new id_door, id_door_cool, id_door_cool1, id_door_VICE, id_door_mini, id_door_port_big, id_door_port_min, id_door_under1, id_door_under2, id_door_small1, id_door_small2, id_door_small3, id_door_small4;
new id_lift, id_door_lift_1, id_door_lift_2;
//new id_door_lift0_1, id_door_lift0_2;
//new fopened_lift;

main()
{
	print("--------------------------------------");
	print(" Map by [Sprite], small base");
	print("--------------------------------------\n");
}

public OnFilterScriptInit()
{
	CreateDynamicObject(12985, 1676.09, -1460.20, 13.66,   0.00, 0.00, 0.00,-1,-1,-1,1000.0,1000.0);
	CreateDynamicObject(3095, 1681.07, -1460.79, 15.73,   0.00, 0.00, 0.00,-1,-1,-1,1000.0,1000.0);
	CreateDynamicObject(3095, 1690.07, -1460.79, 15.73,   0.00, 0.00, 0.00,-1,-1,-1,1000.0,1000.0);
//	id_door = CreateDynamicObject(10671, 1687.0, -1451.09, 14.17,   0.00, 0.00, 90.00,-1,-1,-1,1000.0,1000.0);
	//CreateDynamicObject(10671, 1678.75, -1451.11, 14.17,   0.00, 0.00, 90.00,-1,-1,-1,1000.0,1000.0);
	CreateDynamicObject(2068, 1689.32, -1460.56, 19.48,   0.00, 0.00, 0.00,-1,-1,-1,1000.0,1000.0);
	CreateDynamicObject(2068, 1682.99, -1460.64, 19.48,   0.00, 0.00, 0.00,-1,-1,-1,1000.0,1000.0);
	CreateDynamicObject(2068, 1676.63, -1460.57, 19.48,   0.00, 0.00, 0.00,-1,-1,-1,1000.0,1000.0);
	CreateDynamicObject(16500, 1678.37, -1458.59, 19.79,   0.00, 90.00, 90.00,-1,-1,-1,1000.0,1000.0);
	CreateDynamicObject(16500, 1678.37, -1462.59, 19.79,   0.00, 90.00, 90.00,-1,-1,-1,1000.0,1000.0);
//	CreateDynamicObject(16500, 1683.37, -1462.59, 19.79,   0.00, 90.00, 90.00,-1,-1,-1,1000.0,1000.0);
	CreateDynamicObject(16500, 1678.37, -1458.59, 19.79,   0.00, 90.00, 90.00,-1,-1,-1,1000.0,1000.0);
//	CreateDynamicObject(16500, 1683.37, -1458.59, 19.79,   0.00, 90.00, 90.00,-1,-1,-1,1000.0,1000.0);
	CreateDynamicObject(16500, 1688.36, -1462.59, 19.79,   0.00, 90.00, 90.00,-1,-1,-1,1000.0,1000.0);
	CreateDynamicObject(16500, 1688.36, -1458.59, 19.79,   0.00, 90.00, 90.00,-1,-1,-1,1000.0,1000.0);
	CreateDynamicObject(1692, 1676.28, -1460.78, 20.62,   0.00, 0.00, 90.00,-1,-1,-1,1000.0,1000.0);
	CreateDynamicObject(16500, 1693.36, -1462.59, 19.79,   0.00, 90.00, 90.00,-1,-1,-1,1000.0,1000.0);
	CreateDynamicObject(16500, 1693.36, -1458.59, 19.79,   0.00, 90.00, 90.00,-1,-1,-1,1000.0,1000.0);
	CreateDynamicObject(1692, 1690.78, -1460.84, 20.62,   0.00, 0.00, 90.00,-1,-1,-1,1000.0,1000.0);

	CreateDynamicObject(1497, 192.98190, -229.18260, 0.72000,   0.00000, 0.00000, 90.00000,-1,-1,-1,1000.0,1000.0); //глухая дверь
/*
	//ворота в крутой базе (закрытые)
	id_door_cool = CreateDynamicObject(10671, 214.24680, -224.05170, 2.24000,   0.00000, 0.00000, 90.00000,-1,-1,-1,1000.0,1000.0);
	id_door_cool1 = CreateDynamicObject(10671, 202.72910, -235.60510, 2.24000,   0.00000, 0.00000, 87.00000,-1,-1,-1,1000.0,1000.0);
		
	//маленький гаражик для VICE
	id_door_VICE = CreateDynamicObject(2885, 2461.42017, -1426.41284, 25.34000,   0.00000, 0.00000, 270.00000,-1,-1,-1,1000.0,1000.0);

	//ещё один маленький гаражик
	id_door_mini = CreateDynamicObject(8948, 2461.54980, -1412.51538, 23.57380,   0.00000, 0.00000, 0.00000,-1,-1,-1,1000.0,1000.0);
	
	//база в депо, большая дверь
	id_door_port_big = CreateDynamicObject(3037, 2177.81152, -2255.02710, 15.48650, 0.00000, 0.00000, -45.00000,-1,-1,-1,1000.0,1000.0);
	//маленькая дверца
	id_door_port_min = CreateDynamicObject(2904, 2118.36328, -2274.75488, 20.92000, 0.00000, 0.00000, -45.18000,-1,-1,-1,1000.0,1000.0);
	
	//крутой подземный гараж - дверь
	id_door_under1 = CreateDynamicObject(3037, 2360.13477, -1272.75012, 23.72000, 0.00000, 0.00000, 1.00000,-1,-1,-1,1000.0,1000.0);
	//крутой подземный гараж - вторая дверь
	id_door_under2 = CreateDynamicObject(3037, 2313.65967, -1218.32129, 24.00000, 0.00000, 0.00000, 0.00000,-1,-1,-1,1000.0,1000.0);
	
	//закрытый первый гаражик из 4-х
	id_door_small1 = CreateDynamicObject(5856, 2313.47559,-1261.87451,23.48,180.0,0.0,0.0,-1,-1,-1,1000.0,1000.0);
	//CreateDynamicObject(5856, 2313.47559, -1261.87451, 20.94000,180.00000, 0.00000, 0.00000); //открыт
	id_door_small2 = CreateDynamicObject(5856, 2313.47559,-1267.43994,23.48,180.0,0.0,0.0,-1,-1,-1,1000.0,1000.0);
	id_door_small3 = CreateDynamicObject(5856, 2313.47559,-1272.97998,23.48,180.0,0.0,0.0,-1,-1,-1,1000.0,1000.0);
	id_door_small4 = CreateDynamicObject(5856, 2313.47559,-1278.43994,23.48,180.0,0.0,0.0,-1,-1,-1,1000.0,1000.0);
*/
	//лифт на первом этаже
	id_lift = CreateDynamicObject(18755, 1786.67896, -1303.44397, 14.60000,   0.00000, -0.32000, 270.00000,-1,-1,-1,100.0,100.0);
	//двери лифта открыты
	id_door_lift_1 = CreateDynamicObject(18756, 1790.40918, -1303.44385, 14.61270,   0.00000, 0.00000, 270.00000,-1,-1,-1,100.0,100.0);
	id_door_lift_2 = CreateDynamicObject(18757, 1782.96753, -1303.44385, 14.62000,   0.00000, 0.00000, 270.00000,-1,-1,-1,100.0,100.0);
/*
	//CreateDynamicObject(18756, 1788.66919, -1303.44385, 14.61270,   0.00000, 0.00000, 270.00000); //закрыты
	//CreateDynamicObject(18757, 1784.66748, -1303.43665, 14.62000,   0.00000, 0.00000, 270.00000); //закрыты
	//двери лифта на первом этаже, открыты
	id_door_lift0_1 = CreateDynamicObject(18757, 1790.26685, -1299.36975, 14.64000,   0.00000, 0.00000, 90.00000,-1,-1,-1,100.0,100.0);
	id_door_lift0_2 = CreateDynamicObject(18756, 1782.96704, -1299.36975, 14.63760,   0.00000, 0.00000, 90.00000,-1,-1,-1,100.0,100.0);
	//CreateDynamicObject(18757, 1788.60681, -1299.36975, 14.64000,   0.00000, 0.00000, 90.00000); //закрыты
	//CreateDynamicObject(18756, 1784.60706, -1299.37341, 14.63760,   0.00000, 0.00000, 90.00000); //закрыты


	//подземный гаражец
	//низ (закрыт)
	id_door_un_down = CreateDynamicObject(10671, 1533.89038, -1451.62512, 13.00000,   0.00000, 0.00000, 90.00000,-1,-1,-1,100.0,100.0);
	//CreateDynamicObject(10671, 1533.89038, -1451.62512, 10.54000,   0.00000, 0.00000, 90.00000); //открыт
	//верх (закрыт)
	id_door_un_up = CreateDynamicObject(10671, 1534.88574, -1451.62512, 16.73490,   180.00000, 0.00000, 91.00000,-1,-1,-1,100.0,100.0);
	//CreateDynamicObject(10671, 1534.88574, -1451.62512, 19.00000,   180.00000, 0.00000, 91.00000); //открыт
*/
//	fopened_lift = 1;

	return 1;
}

public OnPlayerCommandText(playerid, cmdtext[])
{
/*
	if(strcmp(cmdtext, "/open", true, 5) == 0)
	{
		MoveDynamicObject(id_door, 1678.75, -1451.11, 14.17, 3, 0.00, 0.00, 90.00);
		fopened = 1;
		return 1;
	}

	if(strcmp(cmdtext, "/close", true, 6) == 0)
	{
		MoveDynamicObject(id_door, 1688.48, -1451.09, 14.17, 3, 0.00, 0.00, 90.00);
		fopened = 0;
		return 1;
	}
*/
	return 0;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	new Float:x1, Float:x2, Float:x3, Float:y1, Float:y2, Float:y3, Float:z1, Float:z2, Float:z3;
/*
	if(newkeys & KEY_FIRE && IsPlayerInAnyVehicle(playerid) || newkeys & KEY_ANALOG_LEFT )
	{
		if(IsPlayerInRangeOfPoint(playerid, 30, 1688.0, -1451.0, 14.0))
		{
		    new name[64];

		    GetPlayerName(playerid, name, sizeof(name));
		    if( (strcmp(name, "DayZzZz") == 0 && strlen(name) == 7) || (strcmp(name, "[[Sprite]]") == 0 && strlen(name) == 10) )
		    {
				if(fopened)
				{
					MoveDynamicObject(id_door, 1687.0, -1451.09, 14.17, 4, 0.00, 0.00, 90.00);
					fopened = 0;
				    return 1;
				}
				else
				{
					MoveDynamicObject(id_door, 1678.75, -1451.11, 14.17, 4, 0.00, 0.00, 90.00);
					fopened = 1;
				    return 1;
				}
			}
		}

		if(IsPlayerInRangeOfPoint(playerid, 10, 214.2468, -224.0517, 2.24))
		{
		    new name[64];

		    GetPlayerName(playerid, name, sizeof(name));
		    if( (strcmp(name, "VICE") == 0 && strlen(name) == 4) || (strcmp(name, "DayZzZz") == 0 && strlen(name) == 7) || (strcmp(name, "[[Sprite]]") == 0 && strlen(name) == 10) )
		    {
				if(fopened_cool)
				{
					MoveDynamicObject(id_door_cool, 214.24680, -224.05170, -1.08, 4, 0.00, 0.00, 90.00);
					fopened_cool = 0;
				    return 1;
				}
				else
				{
					MoveDynamicObject(id_door_cool, 214.24680, -224.05170, 2.24000, 4, 0.00, 0.00, 90.00);
					fopened_cool = 1;
				    return 1;
				}
			}
		}
		
		if(IsPlayerInRangeOfPoint(playerid, 10, 202.72910, -235.60510, 2.24))
		{
		    new name[64];

		    GetPlayerName(playerid, name, sizeof(name));
		    if( (strcmp(name, "VICE") == 0 && strlen(name) == 4) || (strcmp(name, "DayZzZz") == 0 && strlen(name) == 7) || (strcmp(name, "[[Sprite]]") == 0 && strlen(name) == 10) )
		    {
				if(fopened_cool1)
				{
					MoveDynamicObject(id_door_cool1, 202.72910, -235.60510, -1.08, 4, 0.00, 0.00, 87.00);
					fopened_cool1 = 0;
				    return 1;
				}
				else
				{
					MoveDynamicObject(id_door_cool1, 202.72910, -235.60510, 2.24000, 4,  0.00000, 0.00000, 87.00000);
					fopened_cool1 = 1;
				    return 1;
				}
			}
		}
		
		if(IsPlayerInRangeOfPoint(playerid, 10, 2461.42017, -1426.41284, 25.34000))
		{
		    new name[64];
		    
		    GetPlayerName(playerid, name, sizeof(name));
		    if( (strcmp(name, "VICE") == 0 && strlen(name) == 4) || (strcmp(name, "DayZzZz") == 0 && strlen(name) == 7) || (strcmp(name, "[[Sprite]]") == 0 && strlen(name) == 8) )
		    {
				if(fopened_VICE)
				{
					MoveDynamicObject(id_door_VICE, 2461.42017, -1426.41284, 25.34000, 4, 0.00, 0.00, 270.00);
					fopened_VICE = 0;
				    return 1;
				}
				else
				{
					MoveDynamicObject(id_door_VICE, 2461.42017, -1426.41284, 22.76000, 4, 0.00, 0.00, 270.00);
					fopened_VICE = 1;
				    return 1;
				}
			}
		}
		
		if(IsPlayerInRangeOfPoint(playerid, 10, 2461.54980, -1412.51538, 20.98000))
		{
		    new name[64];

		    GetPlayerName(playerid, name, sizeof(name));
		    if( (strcmp(name, "DayZzZz") == 0 && strlen(name) == 7) || (strcmp(name, "[Sprite]") == 0 && strlen(name) == 8) )
		    {
				if(fopened_mini)
				{
					MoveDynamicObject(id_door_mini, 2461.54980, -1412.51538, 20.98000, 4, 0.00000, 0.00000, 0.00000);
					fopened_mini = 0;
				    return 1;
				}
				else
				{
					MoveDynamicObject(id_door_mini, 2461.54980, -1412.51538, 23.57380, 4, 0.00000, 0.00000, 0.00000);
					fopened_mini = 1;
				    return 1;
				}
			}
		}

		if(IsPlayerInRangeOfPoint(playerid, 10, 2177.81152, -2255.02710, 15.48650))
		{
		    new name[64];

		    GetPlayerName(playerid, name, sizeof(name));
		    if( (strcmp(name, "DayZzZz") == 0 && strlen(name) == 7) || (strcmp(name, "[Sprite]") == 0 && strlen(name) == 8) )
		    {
				if(fopened_port_big)
				{
					MoveDynamicObject(id_door_port_big, 2177.81152, -2255.02710, 15.48650, 4, 0.00000, 0.00000, -45.00000);
					fopened_port_big = 0;
				    return 1;
				}
				else
				{
					MoveDynamicObject(id_door_port_big, 2177.81152, -2255.02710, 11.58000, 4, 0.00000, 0.00000, -45.00000);
					fopened_port_big = 1;
				    return 1;
				}
			}
		}
		
		if(IsPlayerInRangeOfPoint(playerid, 10, 2118.36328, -2274.75488, 20.92000))
		{
		    new name[64];

		    GetPlayerName(playerid, name, sizeof(name));
		    if( (strcmp(name, "DayZzZz") == 0 && strlen(name) == 7) || (strcmp(name, "[Sprite]") == 0 && strlen(name) == 8) )
		    {
				if(fopened_port_min)
				{
					MoveDynamicObject(id_door_port_min, 2118.36328, -2274.75488, 20.92000, 4, 0.00000, 0.00000, -45.18000);
					fopened_port_min = 0;
				    return 1;
				}
				else
				{
					MoveDynamicObject(id_door_port_min, 2117.34570, -2273.72705, 20.92000, 4, 0.00000, 0.00000, -45.18000);
					fopened_port_min = 1;
				    return 1;
				}
			}
		}

		if(IsPlayerInRangeOfPoint(playerid, 10, 2360.13477, -1272.75012, 23.72000))
		{
		    new name[64];

		    GetPlayerName(playerid, name, sizeof(name));
		    if( (strcmp(name, "DayZzZz") == 0 && strlen(name) == 7) || (strcmp(name, "[Sprite]") == 0 && strlen(name) == 8) )
		    {
				if(fopened_under1)
				{
					MoveDynamicObject(id_door_under1, 2360.13477, -1272.75012, 23.72000, 4, 0.00000, 0.00000, 1.0);
					fopened_under1 = 0;
				    return 1;
				}
				else
				{
					MoveDynamicObject(id_door_under1, 2360.13477, -1272.75012, 20.66000, 4, 0.00000, 0.00000, 1.0);
					fopened_under1 = 1;
				    return 1;
				}
			}
		}

		if(IsPlayerInRangeOfPoint(playerid, 10, 2313.65967, -1218.32129, 24.00000))
		{
		    new name[64];

		    GetPlayerName(playerid, name, sizeof(name));
		    if( (strcmp(name, "DayZzZz") == 0 && strlen(name) == 7) || (strcmp(name, "[Sprite]") == 0 && strlen(name) == 8) )
		    {
				if(fopened_under2)
				{
					MoveDynamicObject(id_door_under2, 2313.65967, -1218.32129, 24.00000, 4, 0.00000, 0.00000, 0.0);
					fopened_under2 = 0;
				    return 1;
				}
				else
				{
					MoveDynamicObject(id_door_under2, 2313.65967, -1218.32129, 20.90000, 4, 0.00000, 0.00000, 0.0);
					fopened_under2 = 1;
				    return 1;
				}
			}
		}
		
		if(IsPlayerInRangeOfPoint(playerid, 3, 2313.47559,-1261.87451,23.48))
		{
		    new name[64];

		    GetPlayerName(playerid, name, sizeof(name));
		    if( (strcmp(name, "DayZzZz") == 0 && strlen(name) == 7) || (strcmp(name, "[Sprite]") == 0 && strlen(name) == 8) )
		    {
				if(fopened_small1)
				{
					MoveDynamicObject(id_door_small1, 2313.47559,-1261.87451,23.48,4,180.0,0.0,0.0);
					fopened_small1 = 0;
				    return 1;
				}
				else
				{
					MoveDynamicObject(id_door_small1, 2313.47559,-1261.87451,20.94,4,180.0,0.0,0.0);
					fopened_small1 = 1;
				    return 1;
				}
			}
		}
		
		if(IsPlayerInRangeOfPoint(playerid, 3, 2313.47559,-1267.43994,23.48))
		{
		    new name[64];

		    GetPlayerName(playerid, name, sizeof(name));
		    if( (strcmp(name, "DayZzZz") == 0 && strlen(name) == 7) || (strcmp(name, "[Sprite]") == 0 && strlen(name) == 8) )
		    {
				if(fopened_small2)
				{
					MoveDynamicObject(id_door_small2, 2313.47559,-1267.43994,23.48,4,180.0,0.0,0.0);
					fopened_small2 = 0;
				    return 1;
				}
				else
				{
					MoveDynamicObject(id_door_small2, 2313.47559,-1267.43994,20.94,4,180.0,0.0,0.0);
					fopened_small2 = 1;
				    return 1;
				}
			}
		}
		
		if(IsPlayerInRangeOfPoint(playerid, 3, 2313.47559,-1272.97998,23.48))
		{
		    new name[64];

		    GetPlayerName(playerid, name, sizeof(name));
		    if( (strcmp(name, "DayZzZz") == 0 && strlen(name) == 7) || (strcmp(name, "[Sprite]") == 0 && strlen(name) == 8) )
		    {
				if(fopened_small3)
				{
					MoveDynamicObject(id_door_small3, 2313.47559,-1272.97998,23.48,4,180.0,0.0,0.0);
					fopened_small3 = 0;
				    return 1;
				}
				else
				{
					MoveDynamicObject(id_door_small3, 2313.47559,-1272.97998,20.97,4,180.0,0.0,0.0);
					fopened_small3 = 1;
				    return 1;
				}
			}
		}
		
		if(IsPlayerInRangeOfPoint(playerid, 3, 2313.47559,-1278.43994,23.48))
		{
		    new name[64];

		    GetPlayerName(playerid, name, sizeof(name));
		    if( (strcmp(name, "DayZzZz") == 0 && strlen(name) == 7) || (strcmp(name, "[Sprite]") == 0 && strlen(name) == 8) )
		    {
				if(fopened_small4)
				{
					MoveDynamicObject(id_door_small4, 2313.47559,-1278.43994,23.48,4,180.0,0.0,0.0);
					fopened_small4 = 0;
				    return 1;
				}
				else
				{
					MoveDynamicObject(id_door_small4, 2313.47559,-1278.43994,20.94,4,180.0,0.0,0.0);
					fopened_small4 = 1;
				    return 1;
				}
			}
		}
		
		if(IsPlayerInRangeOfPoint(playerid, 10, 1533.89038, -1451.62512, 13.00000))
		{
		    new name[64];

		    GetPlayerName(playerid, name, sizeof(name));
		    if( (strcmp(name, "DayZzZz") == 0 && strlen(name) == 7) || (strcmp(name, "[Sprite]") == 0 && strlen(name) == 8) )
		    {
				if(fopened_un_down)
				{
					MoveDynamicObject(id_door_un_down, 1533.89038, -1451.62512, 13.00000,4,0.0,0.0,90.0);
					MoveDynamicObject(id_door_un_up, 1534.88574, -1451.62512, 16.73490,4,180.0,0.0,91.0);
					fopened_un_down = 0;
				    return 1;
				}
				else
				{
					MoveDynamicObject(id_door_un_down, 1533.89038, -1451.62512, 10.54000,4,0.0,0.0,90.0);
					MoveDynamicObject(id_door_un_up, 1534.88574, -1451.62512, 19.00000,4,180.0,0.0,91.0);
					fopened_un_down = 1;
				    return 1;
				}
			}
		}
		
		if(IsPlayerInRangeOfPoint(playerid, 15, 1788.60681, -1299.36975, 14.64000) && !IsDynamicObjectMoving(id_lift))
		{
		    new name[64];

		    GetPlayerName(playerid, name, sizeof(name));
		    if( (strcmp(name, "DayZzZz") == 0 && strlen(name) == 7) || (strcmp(name, "[Sprite]") == 0 && strlen(name) == 8) )
		    {
				if(fopened_lift)
				{
					MoveDynamicObject(id_door_lift0_1, 1788.60681, -1299.36975, 14.64000,1,0.0,0.0,90.0);
					MoveDynamicObject(id_door_lift0_2, 1784.60706, -1299.36975, 14.63760,1,0.0,0.0,90.0);
//					fopened_lift = 0;
				}
				else
				{
					MoveDynamicObject(id_door_lift0_1, 1790.26685, -1299.36975, 14.64000,0.8,0.0,0.0,90.0);
					MoveDynamicObject(id_door_lift0_2, 1782.96704, -1299.36975, 14.63760,0.8,0.0,0.0,90.0);
//					fopened_lift = 1;
				}
			}
		}

		GetDynamicObjectPos(id_door_lift_1, x1, y1, z1);
		GetDynamicObjectPos(id_door_lift_2, x2, y2, z2);

		if(IsPlayerInRangeOfPoint(playerid, 15, x1, y1, z1) && !IsDynamicObjectMoving(id_lift))
		{
		    new name[64];

		    GetPlayerName(playerid, name, sizeof(name));
		    if( (strcmp(name, "DayZzZz") == 0 && strlen(name) == 7) || (strcmp(name, "[Sprite]") == 0 && strlen(name) == 8) )
		    {
				if(fopened_lift)
				{
					MoveDynamicObject(id_door_lift_1, 1788.6801, -1303.44385,z1,0.8,0.0,0.0,270.0);
					MoveDynamicObject(id_door_lift_2, 1784.66748, -1303.44385,z2,0.8,0.0,0.0,270.0);
					fopened_lift = 0;
				    return 1;
				}
				else
				{
					MoveDynamicObject(id_door_lift_1, 1790.40918, -1303.44385,z1,1,0.0,0.0,270.0);
					MoveDynamicObject(id_door_lift_2, 1782.96753, -1303.44385,z2,1,0.0,0.0,270.0);
					fopened_lift = 1;
				    return 1;
				}
			}
		}
	}
*/
	if(newkeys & KEY_WALK && newkeys & KEY_ANALOG_RIGHT )
	{
		GetDynamicObjectPos(id_door_lift_1, x1, y1, z1);
		GetDynamicObjectPos(id_door_lift_2, x2, y2, z2);
		GetDynamicObjectPos(id_lift, x3, y3, z3);

		if(IsPlayerInRangeOfPoint(playerid, 15, x3, y3, z3))
		{
		    new name[64];

		    GetPlayerName(playerid, name, sizeof(name));
		    if( (strcmp(name, "DayZzZz") == 0 && strlen(name) == 7) || (strcmp(name, "[Sprite]") == 0 && strlen(name) == 8) )
		    {
				if(!IsDynamicObjectMoving(id_door_lift_1) && !IsDynamicObjectMoving(id_door_lift_2))
				{
					MoveDynamicObject(id_lift, x3,y3,14.6,10,0.0,-0.32,270.0);
					MoveDynamicObject(id_door_lift_1,x1,y1,14.612,10,0.0,0.0,270.0);
					MoveDynamicObject(id_door_lift_2,x2,y2,14.62,10,0.0,0.0,270.0);
				    return 1;
				}
			}
		}
		return 1;
	}

	if(newkeys & KEY_ANALOG_RIGHT)
	{
		GetDynamicObjectPos(id_door_lift_1, x1, y1, z1);
		GetDynamicObjectPos(id_door_lift_2, x2, y2, z2);
		GetDynamicObjectPos(id_lift, x3, y3, z3);

		if(IsPlayerInRangeOfPoint(playerid, 15, x3, y3, z3))
		{
		    new name[64];

		    GetPlayerName(playerid, name, sizeof(name));
		    if( (strcmp(name, "DayZzZz") == 0 && strlen(name) == 7) || (strcmp(name, "[Sprite]") == 0 && strlen(name) == 8) )
		    {
				if(!IsDynamicObjectMoving(id_door_lift_1) && !IsDynamicObjectMoving(id_door_lift_2))
				{
					MoveDynamicObject(id_lift, x3,y3,343.54,10,0.0,-0.32,270.0);
					MoveDynamicObject(id_door_lift_1,x1,y1,343.54,10,0.0,0.0,270.0);
					MoveDynamicObject(id_door_lift_2,x2,y2,343.54,10,0.0,0.0,270.0);
				    return 1;
				}
			}
		}
	}

	return 1;
}
/*
	//лифт на первом этаже
	CreateDynamicObject(18755, 1786.67896, -1303.44397, 14.60000,   0.00000, -0.32000, 270.00000,-1,-1,-1,100.0,100.0);
	//двери лифта открыты
	CreateDynamicObject(18756, 1790.40918, -1303.44385, 14.61270,   0.00000, 0.00000, 270.00000,-1,-1,-1,100.0,100.0);
	CreateDynamicObject(18757, 1782.96753, -1303.43665, 14.62000,   0.00000, 0.00000, 270.00000,-1,-1,-1,100.0,100.0);
	//CreateDynamicObject(18756, 1788.66919, -1303.44385, 14.61270,   0.00000, 0.00000, 270.00000); //закрыты
	//CreateDynamicObject(18757, 1784.66748, -1303.43665, 14.62000,   0.00000, 0.00000, 270.00000); //закрыты
	//двери лифта на первом этаже, открыты
	CreateDynamicObject(18757, 1790.26685, -1299.36975, 14.64000,   0.00000, 0.00000, 90.00000,-1,-1,-1,100.0,100.0);
	CreateDynamicObject(18756, 1782.96704, -1299.37341, 14.63760,   0.00000, 0.00000, 90.00000,-1,-1,-1,100.0,100.0);
	//CreateDynamicObject(18757, 1788.60681, -1299.36975, 14.64000,   0.00000, 0.00000, 90.00000); //закрыты
	//CreateDynamicObject(18756, 1784.60706, -1299.37341, 14.63760,   0.00000, 0.00000, 90.00000); //закрыты
*/
