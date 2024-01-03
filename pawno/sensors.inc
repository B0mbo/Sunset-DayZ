#if defined _SENSORS_INC_
	#endinput
#endif

#define _SENSORS_INC_

#include<a_samp>
#include<FCNPC>
#include"global.inc"
#include"load_objects.inc"

#define SENSORS_START_POSITION_X 610.0
#define SENSORS_START_POSITION_Y 310.0
#define SENSORS_SIZE 15 //размер иконок
#define SENSORS_INTERVAL 5 //расстояние между иконками состояния

#define SENSOR_GUN_NUM 0
#define SENSOR_TEMP_NUM 1
#define SENSOR_HEALTH_NUM 2
#define SENSOR_HUNGER_NUM 3
#define SENSOR_THIRST_NUM 4
#define SENSOR_WOUND_NUM 5

#define SENSOR_MESSAG_NUM 104

forward update_character_state(); //функция таймера сохранение состояния персонажа в БД
forward update_live_sensors(); //функция таймера обновления состояния персонажа
forward update_vehicle_state(); //функция обновления состояния авто

forward update_zombie_attack(); //функция атаки зомби

forward cheater_finder(); //функция вычисления читеров

forward create_sensors(playerid); //сенсоры
forward destroy_sensors(playerid);
forward create_vehicle_sensors(playerid, vehicleid);
forward destroy_vehicle_sensors(playerid);

forward create_spectate_data();
forward show_spectate_data(playerid, spec_player, bool:update); //показать данные одного игрока для другого
forward hide_spectate_data(playerid); //скрыть данные одного игрока для другого
forward destroy_spectate_data();

forward create_admin_panel();
forward show_admin_panel(playerid); //показать панель управления
forward hide_admin_panel(playerid); //скрыть панель управления
forward destroy_admin_panel();

forward update_vehicle_sensors(playerid);
forward update_sensor_gun(playerid);
forward update_sensor_temp(playerid, temp);
forward update_sensor_health(playerid, health);
forward update_sensor_hunger(playerid, hunger);
forward update_sensor_thirst(playerid, thirst);
forward update_sensor_wound(playerid, wound);
forward update_sensor_time(playerid);
forward create_smokescreen(); //завеса на радар и время
forward create_statistic_data(playerid);
forward show_smokescreen(playerid);
forward hide_smokescreen(playerid);
forward show_smoke_map(playerid);
forward hide_smoke_map(playerid);
forward show_smoke_statistic(playerid);
forward hide_smoke_statistic(playerid);
forward show_statistic_data(playerid);
forward hide_statistic_data(playerid);
forward update_statistic_data(playerid, bool:update);
forward update_sensor_messager_cheat(msg[]);
forward update_sensor_messager_player(playerid, msg[], text[], color1, color2);
forward update_sensor_messager_player_l(msg[], color, Float:len);
forward Float:get_textdraw_length(msg[]);
forward Float:get_dialog_length(msg[]);

forward create_server_time();
forward update_server_time();
forward destroy_server_time();
forward play_dolg_sound();

forward destroy_smokescreen();
forward destroy_statistic_data(playerid);
forward IsPlayerSpawned(playerid);

forward create_spawn_shadow(); //создать пелену
forward shadow_spawn(playerid); //закрыть кнопку "spawn"
forward unshadow_spawn(playerid); //открыть кнопку "spawn"
forward destroy_spawn_shadow(); //удалить тень

forward IsPlayerInWater(playerid);

public update_character_state()
{
	new i;
	
	if(gTimeridSaveSensors == -1)
	    return;

	//обновим тут состояния временных объектов
	update_tickval_objects("'SOME_TICKVAL_TYPE'", 1);

	for(i = 0; i < MAX_PLAYERS; ++i)
	{
	    if(gIsPlayerLogin[i] <= 0)
			continue;

		if(IsPlayerNPC(i))
		{
		    if(!FCNPC_IsSpawned(i) || FCNPC_IsDead(i))
			    continue;
		}
		else
		{
			if(!IsPlayerConnected(i))
			    continue;
		}

		if(!IsPlayerSpawned(i))
	        continue;

		if(gHealth[i] <= 0)
		{
			kill_character(i);
		    continue;
		}
		
		save_state_and_position(i);
	}
}

public update_live_sensors()
{
	new i, animid, ticks;
	new name[64], msg[128];
	new bool:is_npc, bool:is_jetpack, bool:is_armour, bool:is_money;
	new Float:arm_value;
	
	if(gTimeridUpdateSensors == -1)
	    return;

	ticks = GetTickCount();

	for(i = 0; i < MAX_PLAYERS; ++i)
	{
	    if(gIsPlayerLogin[i] <= 0 || gPlayerCheaterLevel[i] >= gMaxAnticheat)
			continue;

		is_jetpack = false;
		is_armour = false;
		is_money = false;
		arm_value = 0.0;
		is_npc = bool:IsPlayerNPC(i);

		if(is_npc)
		{
		    if(!FCNPC_IsSpawned(i) || FCNPC_IsDead(i))
			    continue;
		}
		else
		{
			if(!IsPlayerConnected(i))
			    continue;

			if(gAntiRadar[i] >= 0)
			{
				if(ticks > gAntiRadar[i])
					gAntiRadar[i] = -1;
			}
			else
			{
				if(gTdAntiCountDown[i] != PlayerText:INVALID_TEXT_DRAW)
				{
					PlayerTextDrawDestroy(i, gTdAntiCountDown[i]);
					gTdAntiCountDown[i] = PlayerText:INVALID_TEXT_DRAW;
				}
			}

			if(gAdminLevel[i] < 9)
			{
				is_jetpack = (GetPlayerSpecialAction(i) == SPECIAL_ACTION_USEJETPACK);
				GetPlayerArmour(i, arm_value);
				if(arm_value > 0)
				    is_armour = true;
				if(GetPlayerMoney(i) > 0)
				    is_money = true;
			}
		}

		if(!IsPlayerSpawned(i))
		{
			update_sensor_time(i);
			if(!gAFK[i])
				update_statistic_data(i, false);
	        continue;
		}

  		if((gGunMode[i] > 0 && gAFK[i] && gAdminLevel[i] < 10 && !is_npc) || is_jetpack || is_armour || is_money)
		{
		    new j;
		    new Float:x, Float:y, Float:z, Float:Z_coord;
		    
			//замораживаем
			TogglePlayerControllable(i, 0);
			//получим ник
		    GetPlayerName(i, name, sizeof(name));
			//сбрасываем флажок "в бою"
		    gGunMode[i] = 0;
			//предупреждение
			PlayerPlaySound(i, 3200, 0, 0, 0);
		    //сообщение в низ экрана
		    GetPlayerName(i, name, sizeof(name));

		    update_sensor_messager_cheat(msg);
			//сохраняем координаты
	    	save_player_bakup_position(i);
			//раскидываем вещи
			if(!IsPlayerAdmin(i) && gAdminLevel[i] < 2)
			{
			    GetPlayerPos(i, x, y, z);
				for(j = 0; j < MAX_INVENTORY_ON_PLAYER; ++j)
				{
				    if(gInventoryItem[i][j][db_id] > 0)
				    {
						MapAndreas_FindZ_For2DCoord_I(x, y, Z_coord);
				        if(z > (Z_coord+3))
					        drop_character_inventory_cell(i, j, -1, x, y, Z_coord);
						else if(z < 0 && Z_coord == 0)
							drop_character_inventory_cell(i, j, -1, x, y, 0);
				        else
							drop_character_inventory_cell(i, j, -1, x, y, z);
					}
				}
			}

			if(is_jetpack)
			{
				format(msg, sizeof(msg), "%s(id:%d) JETPACK HACK! (BAN)", name, i);
				mark_player_as_banned(i, 168); //168 часов - неделя
				gCheatersList[i] = i-2000;
			}
			else if(is_armour)
			{
				format(msg, sizeof(msg), "%s(id:%d) IS A CHEATER! (BAN)", name, i);
				mark_player_as_banned(i, 168); //168 часов - неделя
				gCheatersList[i] = i-2000;
			}
			else if(is_money)
			{
				format(msg, sizeof(msg), "%s(id:%d) DO IS A CHEATER! (BAN)", name, i);
				mark_player_as_banned(i, 168); //168 часов - неделя
				gCheatersList[i] = i-2000;
			}
			else
			{
				format(msg, sizeof(msg), "%s(id:%d) AFK DURING THE FIGHT! (kick)", name, i);
				mark_player_as_cheater(i, gMaxAnticheat);
				gCheatersList[i] = i;
			}
			update_sensor_messager_cheat(msg);
		}

		if(gHealth[i] <= 0)
		{
			kill_character(i);
		    continue;
		}

		//если режим боя закончен - помечаем
		if(ticks - gGunMode[i] > 15000)
		{
		    gGunMode[i] = 0;
		    update_sensor_gun(i);
		}

		//если персонаж рядом с костром - повышаем температуру
		if(gPlayersNearFire[i])
		{
			if(gTemperature[i] < 3800)
		    	gTemperature[i] = gTemperature[i] + 30;
		}

		//если персонаж плывёт - уменьшаем температуру
		if(IsPlayerInWater(i))
		    gTemperature[i] = gTemperature[i] - 20;

		//если персонаж бежит - увеличиваем температуру
		if(is_npc)
		{
//			if(FCNPC_IsMoving(i))
//			{
//				gTemperature[i] = gTemperature[i] + 1;
//			}
//			gHunger[i] = gHunger[i] - 1;
//			gThirst[i] = gThirst[i] - 1;
		}
		else
		{
			animid = GetPlayerAnimationIndex(i);
			if(animid == 1231 || animid == 1195 || animid == 1196 || animid == 1197)
			{
				gTemperature[i] = gTemperature[i] + 2;
			}
			gHunger[i] = gHunger[i] - 2;
			gThirst[i] = gThirst[i] - 3;
		}
		if(gWound[i] != 0)
			gHealth[i] = gHealth[i] - gWound[i];

		//обновляем сенсоры
		update_sensor_temp(i, gTemperature[i]);
		update_sensor_health(i, gHealth[i]);
		update_sensor_hunger(i, gHunger[i]);
		update_sensor_thirst(i, gThirst[i]);
		update_sensor_time(i);

		if(!gAFK[i])
			update_statistic_data(i, false);
	}

	for(i = 0; i < MAX_PLAYERS; ++i)
	{
		for(new j = 0; j < MAX_PLAYERS; ++j)
		{
			if(gPsp[j][i] == 1)
			{
		        show_spectate_data(i, j, false);
		        break;
			}
		}
	}
}

public update_vehicle_state()
{
	new vehicleid, id;
	new is_working, is_lights, is_alarm, is_doors, is_bonnet, is_boot, is_objective;
	
	if(gTimeridUpdateVehicles == -1)
	    return;

	for(vehicleid = 0; vehicleid < MAX_VEHICLES; ++vehicleid)
	{
	    if(gVeh[vehicleid][0] <= 0)
	    {
			//античит на случай, если факен читеры додумаются созавать авто с уже заведённым двигателем
			new Float:health;
			GetVehicleHealth(vehicleid, health);
	        if(health > 0.0)
	        {
				new bool:IsAdmin;
				new playerid;
				
				IsAdmin = false;
	            for(playerid = 0; playerid < MAX_PLAYERS; ++playerid)
	            {
	            	if(IsPlayerInVehicle(playerid, vehicleid))
	            	{
						IsAdmin = bool:IsPlayerAdmin(playerid);
						break;
	            	}
	            }
	            if(!IsAdmin)
	            {
			        SendClientMessage(playerid, 0xFFAACCFF, "It was an admin's vehicle!");
		            DestroyVehicle(vehicleid);
				}
	        }
	        continue;
		}
		
		if(gVeh[vehicleid][4] > 0)
		{
		    //уменьшаем топливо в баке
		    gVeh[vehicleid][3] = gVeh[vehicleid][3] - gVeh[vehicleid][5];
		    //подзаряжаем аккумулятор
		    gVeh[vehicleid][9] = gVeh[vehicleid][9] + gVeh[vehicleid][8];
		    
			if(gVeh[vehicleid][9] > gVeh[vehicleid][10])
				gVeh[vehicleid][9] = gVeh[vehicleid][10];
		}

		if(gVeh[vehicleid][7] > 0 && gVeh[vehicleid][9] > 0) //если включены фары
		{
		    //уменьшаем заряд аккумулятора
		    gVeh[vehicleid][9] = gVeh[vehicleid][9] - gVeh[vehicleid][8];
		}

		if(gVeh[vehicleid][4] > 0 || (gVeh[vehicleid][7] > 0 && gVeh[vehicleid][9] > 0))
		{
		    //сохраняем состояние авто
			save_vehicle_state(INVALID_PLAYER_ID, vehicleid);
		}

		if(gVeh[vehicleid][9] <= 0)
		{
			gVeh[vehicleid][9] = 0;
		    gVeh[vehicleid][7] = 0;
			GetVehicleParamsEx(vehicleid, is_working, is_lights, is_alarm, is_doors, is_bonnet, is_boot, is_objective);
			is_lights = 0;
			SetVehicleParamsEx(vehicleid, is_working, is_lights, is_alarm, is_doors, is_bonnet, is_boot, is_objective); //а вот тут можно включить/выключить фары
		}

//		if(gVeh[vehicleid][3] < 0 || gVeh[vehicleid][2] < 0) //не надо сравнивать с нулём, т.к. это чревато бесконечными вызовами!
//			save_vehicle_state(INVALID_PLAYER_ID, vehicleid);
	}

	for(id = 0; id < MAX_PLAYERS; ++id)
	{
//		if(!IsPlayerConnected(id))
//		    continue;
	    if(gVehicleDataShow[id] > 0)
		{
		    update_vehicle_sensors(id);
		}
	}
}

public update_zombie_attack()
{
	new i, j, k, count;
	new Float:x, Float:y, Float:z;
	new Float:player_x, Float:player_y, Float:player_z;
	new Float:zomb_x, Float:zomb_y, Float:zomb_z;
	new Float:dx, Float:dy, Float:len;
	
	for(i = 0; i < MAX_PLAYERS; ++i)
	{
	    if(IsPlayerNPC(i) && FCNPC_IsSpawned(i) && !FCNPC_IsDead(i))
	    {
	    	FCNPC_GetPosition(i, x, y, z);
			for(j = 0; j < MAX_PLAYERS; ++j)
			{
			    if(!IsPlayerSpawned(j) || IsPlayerNPC(j)/* || gAdminLevel[j] > 9*/)
			        continue;
		        GetPlayerPos(j, player_x, player_y, player_z);
			    if(!IsPlayerNPC(j) && IsPlayerInRangeOfPoint(j, 1.2, x, y, z))
			    {
			        if(FCNPC_IsMoving(i))
			        	FCNPC_Stop(i);
			    	FCNPC_AimAt(i, player_x, player_y, player_z, false);
			    	FCNPC_MeleeAttack(i, 50);
			        break;
			    }
			    if(!IsPlayerNPC(j) && IsPlayerInRangeOfPoint(j, 99, x, y, z))
			    {
			        for(k = 0, count = 0; k < i; ++k)
			        {
			            if(IsPlayerNPC(k) && !FCNPC_IsDead(k) && FCNPC_IsSpawned(k) && k != i)
						{
							FCNPC_GetPosition(k, zomb_x, zomb_y, zomb_z);
						 	if(VectorSize(player_x-zomb_x,player_y-zomb_y,0) < 20)
			                	count++;
						}
						else
							continue;
							
						if(count >= 5)
						    break;
			        }
			        if(FCNPC_IsAiming(i))
			        {
			            FCNPC_StopAttack(i);
			        	FCNPC_StopAim(i);
					}
					dx = x - player_x;
					dy = y - player_y;
					len = VectorSize(dx,dy,0);
			        if(count >= 5)
					FCNPC_GoTo(i, player_x+20.0*dx/len, player_y+30.0*dy/len, player_z, FCNPC_MOVE_TYPE_RUN, 2.0, true);
    	   			else
					FCNPC_GoTo(i, player_x+0.5*dx/len, player_y+0.5*dy/len, player_z, FCNPC_MOVE_TYPE_RUN, 2.0, true);
			        break;
			    }
			}
			if(FCNPC_IsAiming(i))
			{
				FCNPC_StopAttack(i);
				FCNPC_StopAim(i);
			}
	    }
	}
}

public cheater_finder()
{
	new playerid;
	new Float:x, Float:y, Float:z;
	new Float:max_path, Float:path, Float:pathz, Float:max_path_veh, Float:max_path_foot;
	new msg[128], name[64];
	new i, weapid, ammo;
	new Float:seconds, cnt;

	if(gTimerNonCheaters == -1)
	    return;

	cnt = GetTickCount();
	seconds = floatadd(floatdiv((cnt-gTickCnt),1000.0),1.0);
	gTickCnt = GetTickCount();

	for(playerid = 0; playerid < MAX_PLAYERS; ++playerid)
	{
	    if(IsPlayerNPC(playerid))
	        continue;
	        
	    if(gCheatersList[playerid] != INVALID_PLAYER_ID)
	    {
	        if(gCheatersList[playerid] == (playerid+MAX_PLAYERS))
	            continue;
			TogglePlayerControllable(playerid, 1);
	        if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 1)
	        {
	            if(gCheatersList[playerid] >= 0)
	            {
					Kick(playerid);
				}
				else
				{
					Ban(playerid);
				}
			}
	        gCheatersList[playerid] = INVALID_PLAYER_ID;
     	}
	}
	
	max_path_veh = floatmul(75.0,seconds); //max 300 m
	max_path_foot = floatmul(42.0,seconds); //max 210 m

	for(playerid = 0; playerid < MAX_PLAYERS; ++playerid)
	{
	    if(!IsPlayerConnected(playerid) || IsPlayerNPC(playerid))
	        continue;
	        
		if(gAFK[playerid])
		{
		    gCheatersList[playerid] = (playerid+MAX_PLAYERS);
		    continue;
		}
	        
		if(gAntiDebug && IsPlayerAdmin(playerid))
		{
		    new str[128]; //отладка!!!
			GetPlayerPos(playerid, x, y, z); //отладка!!!
			path = VectorSize(gNonCheaters[playerid][0]-x,gNonCheaters[playerid][1]-y,0.0); //отладка!!!
			if(IsPlayerInAnyVehicle(playerid))
			    max_path = max_path_veh;
			else
			    max_path = max_path_foot;
			format(str,sizeof(str),"path = %f, max_path=%f, seconds=%f", path, max_path, seconds); //отладка!!!
			SendClientMessage(playerid, 0xFF00FFFF, str); //отладка!!!
			gNonCheaters[playerid][0] = x; //отладка!!!
			gNonCheaters[playerid][1] = y; //отладка!!!
			gNonCheaters[playerid][2] = z; //отладка!!!
		}
/*
	 	GetPlayerName(playerid, name, sizeof(name));
		if(gAdminLevel[playerid] > 9 || strcmp(name, "Kenny", true, 5) == 0)
		{
			format(msg, sizeof(msg), "gAFK=%d, weapid=%d, gCheatersList=%d, CheterLevel=%d, admin=%d, level=%d, ID=%d, noncheat=%f, spawned=%d", gAFK[playerid], GetPlayerWeapon(playerid), gCheatersList[playerid], gPlayerCheaterLevel[playerid], IsPlayerAdmin(playerid), gAdminLevel[playerid], gPlayersID[playerid], gNonCheaters[playerid][2], IsPlayerSpawned(playerid));
			SendClientMessage(playerid, 0xFF00FFFF, msg);
		}
*/
		if(IsPlayerAdmin(playerid) || (gAdminLevel[playerid] > 2) || (gPlayersID[playerid] <= 0) || (gNonCheaters[playerid][2] == 484.0) || !IsPlayerSpawned(playerid))
		    continue;

		if(gCheatersList[playerid] == (playerid+MAX_PLAYERS))
		{
//		    printf("MAX_PLAYERS = %d", MAX_PLAYERS); //отладка!!!
			gCheatersList[playerid] = INVALID_PLAYER_ID;
			GetPlayerPos(playerid, x, y, z);
			gNonCheaters[playerid][0] = x;
			gNonCheaters[playerid][1] = y;
			gNonCheaters[playerid][2] = z;
			continue;
		}

		for(i = 0; i <= 12; ++i)
		{
			GetPlayerWeaponData(playerid, i, weapid, ammo);
			if(weapid == 0)
			    continue;
			switch(weapid)
			{
				case 0: //кулак
				{}
				case 4: //нож
				{}
				case 5: //бита
				{}
				case 8: //катана
				{}
				case 18: //молотов
				{}
				case 24: //пустынный орёл
				{}
				case 25: //дробовик
				{}
				case 30: //АК47
				{}
				case 31: //M4
				{}
				case 33: //винтовка
				{}
				case 34: //снайперская винтовка
				{}
				case 42: //огнетушитель
				{}
				case 46: //парашют
				{}
				default:
				{
					if(gAdminLevel[playerid] < 5)
					{
					    //кикаем засранца!
						//сообщение в низ экрана
						GetPlayerName(playerid, name, sizeof(name));
						format(msg, sizeof(msg), "%s(id:%d) seems to be a CHEATER! FORBIDDEN WEAPON (kick)", name, playerid);
						update_sensor_messager_cheat(msg);
						//гарантируем игроку кик
						gPlayerCheaterLevel[playerid] = gMaxAnticheat;
					}
				}
			}

			if( (weapid != 0) && (weapid != gPlayerWeapon[playerid][2]) )
			{
			    //проверка только не наличае холодного оружия, т.к. из него не выстрелишь (огнестрельное отслеживается в другом месте)
				switch(weapid)
				{
					case 24: //пустынный орёл
					{}
					case 25: //дробовик
					{}
					case 30: //АК47
					{}
					case 31: //M4
					{}
					case 33: //винтовка
					{}
					case 34: //снайперская винтовка
					{}
					case 46: //парашют
					{}
					default:
					{
						ResetPlayerWeapons(playerid);
						gPlayerWeapon[playerid][0] = 0;
						gPlayerWeapon[playerid][1] = 0;
						gPlayerWeapon[playerid][2] = 0;
						GetPlayerName(playerid, name, sizeof(name));
						if((gPlayerCheaterLevel[playerid]+1) >= gMaxAnticheat)
							format(msg, sizeof(msg), "%s(id:%d) seems to be a CHEATER! HANDLESS WEAPON (kick)", name, playerid);
						else
							format(msg, sizeof(msg), "%s(id:%d) seems to be a CHEATER! HANDLESS WEAPON", name, playerid);
						update_sensor_messager_cheat(msg);
						gPlayerCheaterLevel[playerid]++;
					}
				}
			}
		}

		GetPlayerPos(playerid, x, y, z);
		path = VectorSize(gNonCheaters[playerid][0]-x,gNonCheaters[playerid][1]-y,0.0);
		pathz = VectorSize(0,0,gNonCheaters[playerid][2]-z);
		if(IsPlayerInAnyVehicle(playerid))
		    max_path = max_path_veh;
		else
		    max_path = max_path_foot;

		if( (path > max_path || ((pathz > (max_path + 100.0)) && (path < 100.0))) && gPlayerLocated[playerid] == 1 )
		{
		    new str[128]; //отладка!!!
		    new ch_name[64]; //отладка!!!

			if( (gNonCheaters[playerid][0] > -2351.0 && gNonCheaters[playerid][0] < -2343.0) &&
				(gNonCheaters[playerid][1] > -1604.0 && gNonCheaters[playerid][1] < -1596.0) &&
				(gNonCheaters[playerid][2] > 470.0 && gNonCheaters[playerid][2] < 510.0) ||
				(x > -2351.0 && x < -2343.0) &&
				(y > -1604.0 && y < -1596.0) &&
				(z > 470.0 && z < 510.0) )
				continue;

		    GetPlayerName(playerid, ch_name, sizeof(ch_name)); //отладка!!!
			format(str,sizeof(str),"%s: path = %f, max_path=%f, ch_x=%f, ch_y=%f, ch_z=%f", ch_name, path, max_path, gNonCheaters[playerid][0], gNonCheaters[playerid][1], gNonCheaters[playerid][2]); //отладка!!!
			for(i = 0; i < MAX_PLAYERS; ++i) //отладка!!!
			{ //отладка!!!
			    if(IsPlayerAdmin(i) || gAdminLevel[i] > 8) //отладка!!!
					SendClientMessage(i, 0xFF00FFFF, str); //отладка!!!
			} //отладка!!!

			gPlayerCheaterLevel[playerid]++;
	        
	        if(gPlayerCheaterLevel[playerid] >= gMaxAnticheat)
	        {
				GetPlayerName(playerid, name, sizeof(name));
			    //сообщение в низ экрана
			    format(msg, sizeof(msg), "%s(id:%d) seems to be a CHEATER! TELEPORT HACK (kick)", name, playerid);
			    update_sensor_messager_cheat(msg);

	//			Kick(playerid);
	        }
	        else
	        {
				//предупреждение
				PlayerPlaySound(playerid, 3200, 0, 0, 0);
				GetPlayerName(playerid, name, sizeof(name));
			    //сообщение в низ экрана
			    format(msg, sizeof(msg), "%s(id:%d) seems to be a CHEATER! TELEPORT HACK", name, playerid);
			    update_sensor_messager_cheat(msg);
	        }
		}
		
        if(gPlayerCheaterLevel[playerid] >= gMaxAnticheat)
        {
            //замораживаем персонаж
			TogglePlayerControllable(playerid, 0);
			//немного издёвки
			PlayerPlaySound(playerid, 31202, 0, 0, 0);
			//удаляем сенсоры с экрана
			destroy_sensors(playerid);
			//помечаем игрока в БД как читера
			mark_player_as_cheater(playerid, gPlayerCheaterLevel[playerid]);
			//сохраняем координаты
	    	save_player_bakup_position(playerid);
			//раскидываем вещи
			//добавить проверку и обработку для транспорта!
			if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 1)
			{
				for(i = 0; i < MAX_INVENTORY_ON_PLAYER; ++i)
				{
				    if(gInventoryItem[playerid][i][db_id] > 0)
						drop_character_inventory_cell(playerid, i, -1, x,y,z);
				}
			}

			//помечаем игрока на кик
			gCheatersList[playerid] = playerid;
        }

		gNonCheaters[playerid][0] = x;
		gNonCheaters[playerid][1] = y;
		gNonCheaters[playerid][2] = z;
	}
}

public create_sensors(playerid)
{
	new i, temperature, health, hunger, thirst, wound;
	
	for(i = 0; i < SENSORS_NUMBER; ++i)
	{
		if(!IsPlayerNPC(playerid))
	    if(gSensors[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
	    {
	        PlayerTextDrawDestroy(playerid, gSensors[playerid][i]);
	        gSensors[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
	    }
	    
	    get_character_state(playerid, temperature, health, hunger, thirst, wound);

		switch(i)
		{
			case SENSOR_HEALTH_NUM:
			{
			    //здоровье
			    if(!IsPlayerNPC(playerid))
					gSensors[playerid][i] = CreatePlayerTextDraw(playerid, SENSORS_START_POSITION_X, SENSORS_START_POSITION_Y+i*(SENSORS_SIZE+SENSORS_INTERVAL), "hud:radar_Girlfriend");
				gHealth[playerid] = health;
				update_sensor_health(playerid, gHealth[playerid]);
			}
			case SENSOR_HUNGER_NUM:
			{
			    //жратва
			    if(!IsPlayerNPC(playerid))
					gSensors[playerid][i] = CreatePlayerTextDraw(playerid, SENSORS_START_POSITION_X, SENSORS_START_POSITION_Y+i*(SENSORS_SIZE+SENSORS_INTERVAL), "hud:radar_dateFood");
				gHunger[playerid] = hunger;
				update_sensor_hunger(playerid, gHunger[playerid]);
			}
			case SENSOR_THIRST_NUM:
			{
				//питьё
				if(!IsPlayerNPC(playerid))
					gSensors[playerid][i] = CreatePlayerTextDraw(playerid, SENSORS_START_POSITION_X, SENSORS_START_POSITION_Y+i*(SENSORS_SIZE+SENSORS_INTERVAL), "hud:radar_Diner");
				gThirst[playerid] = thirst;
				update_sensor_thirst(playerid, gThirst[playerid]);
			}
			case SENSOR_WOUND_NUM:
			{
			    //капля
			    if(!IsPlayerNPC(playerid))
					gSensors[playerid][i] = CreatePlayerTextDraw(playerid, SENSORS_START_POSITION_X, SENSORS_START_POSITION_Y+i*(SENSORS_SIZE+SENSORS_INTERVAL), "hud:radar_centre");
				gWound[playerid] = wound;
				update_sensor_wound(playerid, gWound[playerid]);
			}
			case SENSOR_GUN_NUM:
			{
			    //режим боя
			    if(!IsPlayerNPC(playerid))
					gSensors[playerid][i] = CreatePlayerTextDraw(playerid, SENSORS_START_POSITION_X, SENSORS_START_POSITION_Y+i*(SENSORS_SIZE+SENSORS_INTERVAL), "hud:radar_ammugun");
				gGunMode[playerid] = 0;
				PlayerTextDrawColor(playerid, gSensors[playerid][i], 0x00FF00FF);//Цвет
			}
			case SENSOR_TEMP_NUM:
			{
			    if(!IsPlayerNPC(playerid))
					gSensors[playerid][i] = CreatePlayerTextDraw(playerid, SENSORS_START_POSITION_X, SENSORS_START_POSITION_Y+i*(SENSORS_SIZE+SENSORS_INTERVAL), "hud:radar_TORENO");
				gTemperature[playerid] = temperature;
				update_sensor_temp(playerid, gTemperature[playerid]);
			    //hud:radar_ammugun - пистолет
			    //hud:radar_spray - спрэй
			    //hud:radar_hostpital - больничный крест
			    //hud:radar_impound - машина
			    //hud:radar_TORENO - буква Т
//				gSensors[playerid][i] = CreatePlayerTextDraw(playerid, SENSORS_START_POSITION_X, SENSORS_START_POSITION_Y+i*(SENSORS_SIZE+SENSORS_INTERVAL), "hud:radar_impound");
//	  	    	PlayerTextDrawColor(playerid, gSensors[playerid][i], 0x00FF00FF);//Цвет
			}
		}
		if(!IsPlayerNPC(playerid))
		{
		    PlayerTextDrawFont(playerid, gSensors[playerid][i], 4);//Шрифт
		    PlayerTextDrawTextSize(playerid, gSensors[playerid][i], SENSORS_SIZE, SENSORS_SIZE);//Размер
		    if(gSensors[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
				PlayerTextDrawShow(playerid, gSensors[playerid][i]);
		}
	}
	gScores[playerid] = get_character_scores(playerid);
	SetPlayerScore(playerid, gScores[playerid]);
}

public destroy_sensors(playerid)
{
	new i;
	
	if(IsPlayerNPC(playerid))
	    return;
	    
	for(i = 0; i < SENSORS_NUMBER; ++i)
	{
		if(gSensors[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, gSensors[playerid][i]);
			gSensors[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
	}
}

//вывести показатели авто
public create_vehicle_sensors(playerid, vehicleid)
{
	new Float:level;
	new color, buff;
	new Float:VehHealth;
	new VehHealthStr[16];
	new VehHealthInt;
	new engine, lights, alarm, doors, bonnet, boot, objective;

	if(vehicleid == INVALID_VEHICLE_ID || playerid == INVALID_PLAYER_ID)
	    return;

	//если расход топлива нулевой - не показываем состояние бака
	if(gVeh[vehicleid][5] == 0)
	{
        destroy_vehicle_sensors(playerid);
	}
	else
	{
	    if(gTdDataVehicle[playerid][0] == PlayerText:INVALID_TEXT_DRAW)
	    {
			//уровень топлива автомобиля - фон
			gTdDataVehicle[playerid][0] = CreatePlayerTextDraw(playerid, VEHICLE_START_POSITION_X+2.0, VEHICLE_START_POSITION_Y-2.0, "~n~");
		}
		PlayerTextDrawUseBox(playerid, gTdDataVehicle[playerid][0], 1);
		PlayerTextDrawBoxColor(playerid, gTdDataVehicle[playerid][0], 0x00000055); //цвет
		PlayerTextDrawSetShadow(playerid, gTdDataVehicle[playerid][0], 0);
		PlayerTextDrawColor(playerid, gTdDataVehicle[playerid][0], 0x00000000);
		PlayerTextDrawLetterSize(playerid, gTdDataVehicle[playerid][0], 300.0, 8.5);
		PlayerTextDrawBackgroundColor(playerid, gTdDataVehicle[playerid][0], 0x00000055);
		PlayerTextDrawTextSize(playerid, gTdDataVehicle[playerid][0], 18.0, 70.0); //размер

	    if(gTdDataVehicle[playerid][1] == PlayerText:INVALID_TEXT_DRAW)
	    {
			//уровень топлива автомобиля
			gTdDataVehicle[playerid][1] = CreatePlayerTextDraw(playerid, VEHICLE_START_POSITION_X, VEHICLE_START_POSITION_Y+75.0, "~n~");
		}
		PlayerTextDrawUseBox(playerid, gTdDataVehicle[playerid][1], 1);
		PlayerTextDrawSetShadow(playerid, gTdDataVehicle[playerid][1], 0);
		PlayerTextDrawColor(playerid, gTdDataVehicle[playerid][1], 0x00000000);
		PlayerTextDrawBackgroundColor(playerid, gTdDataVehicle[playerid][1], 0x00FF0055);
		PlayerTextDrawTextSize(playerid, gTdDataVehicle[playerid][1], 20.0, 0.0);

	    if(gVeh[vehicleid][3] < gVeh[vehicleid][6])
	    {
	        buff = (255*gVeh[vehicleid][3])/gVeh[vehicleid][6];
	        color = ((0xFF-buff) << 24) | (buff<<16) | 0x55;
	    }
		else
		    color = 0x00FF0055;
		if(gVeh[vehicleid][3] <= 0)
		{
		    level = -0.4;
		}
		else
		{
			level = floatsub(floatdiv(floatmul((-8.1),Float:gVeh[vehicleid][3]),Float:gVeh[vehicleid][6]),0.5);
			if(level < -8.6)
			    level = -8.6;
	    }
		PlayerTextDrawBoxColor(playerid, gTdDataVehicle[playerid][1], color); //цвет
		PlayerTextDrawLetterSize(playerid, gTdDataVehicle[playerid][1], 300.0, level); //от -0.4 до -8.6 //размер

	    if(gTdDataVehicle[playerid][2] == PlayerText:INVALID_TEXT_DRAW)
	    {
			//состояние двигателя - фон
			gTdDataVehicle[playerid][2] = CreatePlayerTextDraw(playerid, VEHICLE_START_POSITION_X+2.0, VEHICLE_START_POSITION_Y+82.0, "~n~");
		}
		PlayerTextDrawUseBox(playerid, gTdDataVehicle[playerid][2], 1);
		PlayerTextDrawBoxColor(playerid, gTdDataVehicle[playerid][2], 0x00000055); //цвет
		PlayerTextDrawSetShadow(playerid, gTdDataVehicle[playerid][2], 0);
		PlayerTextDrawColor(playerid, gTdDataVehicle[playerid][2], 0x00000000);
		PlayerTextDrawLetterSize(playerid, gTdDataVehicle[playerid][2], 18.0, 1.0);
		PlayerTextDrawBackgroundColor(playerid, gTdDataVehicle[playerid][2], 0x00000055);
		PlayerTextDrawTextSize(playerid, gTdDataVehicle[playerid][2], 18.0, 18.0); //размер
	    if(gVeh[vehicleid][2] > 0)
	    {
			buff = (0xFF*gVeh[vehicleid][2])/1000;
			color = ((0xFF-buff) << 24) | (buff<<16) | 0x55;
	    }
		else
		    color = 0xFF000055;
		PlayerTextDrawBoxColor(playerid, gTdDataVehicle[playerid][2], color); //цвет фона двигателя

	    if(gTdDataVehicle[playerid][3] == PlayerText:INVALID_TEXT_DRAW)
	    {
			//состояние двигателя - работает/выключен
			if(gVeh[vehicleid][4] > 0)
				gTdDataVehicle[playerid][3] = CreatePlayerTextDraw(playerid, VEHICLE_START_POSITION_X-12, VEHICLE_START_POSITION_Y+84.0, "ON");
			else
				gTdDataVehicle[playerid][3] = CreatePlayerTextDraw(playerid, VEHICLE_START_POSITION_X-12, VEHICLE_START_POSITION_Y+84.0, "OFF");
		}
	    PlayerTextDrawFont(playerid, gTdDataVehicle[playerid][3], 1);//Шрифт
    	PlayerTextDrawAlignment(playerid, gTdDataVehicle[playerid][3], 1);
		PlayerTextDrawSetShadow(playerid, gTdDataVehicle[playerid][3], 0);
		PlayerTextDrawColor(playerid, gTdDataVehicle[playerid][3], 0x000000FF);
		PlayerTextDrawBackgroundColor(playerid, gTdDataVehicle[playerid][3], 0x00000055);
		PlayerTextDrawTextSize(playerid, gTdDataVehicle[playerid][3], 8.0, 8.0);
		PlayerTextDrawLetterSize(playerid, gTdDataVehicle[playerid][3], 0.15, 0.5);

	    if(gTdDataVehicle[playerid][4] == PlayerText:INVALID_TEXT_DRAW)
	    {
			//состояние корпуса авто
			gTdDataVehicle[playerid][4] = CreatePlayerTextDraw(playerid, VEHICLE_START_POSITION_X-15, VEHICLE_START_POSITION_Y+94.0, "hud:radar_impound");
		}
	    PlayerTextDrawFont(playerid, gTdDataVehicle[playerid][4], 4);//Шрифт
    	PlayerTextDrawAlignment(playerid, gTdDataVehicle[playerid][4], 1);
		PlayerTextDrawSetShadow(playerid, gTdDataVehicle[playerid][4], 0);
		PlayerTextDrawColor(playerid, gTdDataVehicle[playerid][4], 0x000000FF);
		PlayerTextDrawBackgroundColor(playerid, gTdDataVehicle[playerid][4], 0x00000055);
		PlayerTextDrawTextSize(playerid, gTdDataVehicle[playerid][4], 15.0, 15.0);
		PlayerTextDrawLetterSize(playerid, gTdDataVehicle[playerid][4], 0.15, 0.5);
		GetVehicleHealth(vehicleid, VehHealth);
		format(VehHealthStr, sizeof(VehHealthStr), "%f", VehHealth);
		VehHealthInt = strval(VehHealthStr);
	    if(VehHealthInt > 300)
	    {
			buff = (0xFF*(VehHealthInt-300))/700;
			color = ((0xFF-buff) << 24) | (buff<<16) | 0x55;
	    }
		else
		    color = 0xFF000055;
		PlayerTextDrawBoxColor(playerid, gTdDataVehicle[playerid][4], color); //цвет состояния корпуса
		PlayerTextDrawColor(playerid, gTdDataVehicle[playerid][4], color);

	    if(gTdDataVehicle[playerid][5] == PlayerText:INVALID_TEXT_DRAW)
	    {
			//состояние двигателя - фон
			gTdDataVehicle[playerid][5] = CreatePlayerTextDraw(playerid, VEHICLE_START_POSITION_X+2.0, VEHICLE_START_POSITION_Y+115.0, "~n~");
		}
		PlayerTextDrawUseBox(playerid, gTdDataVehicle[playerid][5], 1);
		PlayerTextDrawBoxColor(playerid, gTdDataVehicle[playerid][5], 0x00000055); //цвет
		PlayerTextDrawSetShadow(playerid, gTdDataVehicle[playerid][5], 0);
		PlayerTextDrawColor(playerid, gTdDataVehicle[playerid][5], 0x00000000);
		PlayerTextDrawLetterSize(playerid, gTdDataVehicle[playerid][5], 18.0, 1.0);
		PlayerTextDrawBackgroundColor(playerid, gTdDataVehicle[playerid][5], 0x00000055);
		PlayerTextDrawTextSize(playerid, gTdDataVehicle[playerid][5], 18.0, 18.0); //размер
	    if(gVeh[vehicleid][9] > 0)
	    {
			buff = (0xFF*gVeh[vehicleid][9])/1000;
			color = ((0xFF-buff) << 24) | (buff<<16) | 0x55;
	    }
		else
		    color = 0xFF000055;
		PlayerTextDrawBoxColor(playerid, gTdDataVehicle[playerid][5], color); //цвет фона двигателя

	    if(gTdDataVehicle[playerid][6] == PlayerText:INVALID_TEXT_DRAW)
	    {
			//заряд аккумулятора
			format(VehHealthStr, sizeof(VehHealthStr), "%d%%", gVeh[vehicleid][9]/10);
			gTdDataVehicle[playerid][6] = CreatePlayerTextDraw(playerid, VEHICLE_START_POSITION_X-12, VEHICLE_START_POSITION_Y+117.0, VehHealthStr);
		}
	    PlayerTextDrawFont(playerid, gTdDataVehicle[playerid][6], 1);//Шрифт
    	PlayerTextDrawAlignment(playerid, gTdDataVehicle[playerid][6], 1);
		PlayerTextDrawSetShadow(playerid, gTdDataVehicle[playerid][6], 0);
		PlayerTextDrawColor(playerid, gTdDataVehicle[playerid][6], 0x000000FF);
		PlayerTextDrawBackgroundColor(playerid, gTdDataVehicle[playerid][6], 0x00000055);
		PlayerTextDrawTextSize(playerid, gTdDataVehicle[playerid][6], 8.0, 8.0);
		PlayerTextDrawLetterSize(playerid, gTdDataVehicle[playerid][6], 0.15, 0.5);

	    if(gTdDataVehicle[playerid][7] == PlayerText:INVALID_TEXT_DRAW)
	    {
			//состояние замка - фон
			gTdDataVehicle[playerid][7] = CreatePlayerTextDraw(playerid, VEHICLE_START_POSITION_X+2.0, VEHICLE_START_POSITION_Y+134.0, "~n~");
		}
		PlayerTextDrawUseBox(playerid, gTdDataVehicle[playerid][7], 1);
		PlayerTextDrawBoxColor(playerid, gTdDataVehicle[playerid][7], 0x00000055); //цвет
		PlayerTextDrawSetShadow(playerid, gTdDataVehicle[playerid][7], 0);
		PlayerTextDrawColor(playerid, gTdDataVehicle[playerid][7], 0x00000000);
		PlayerTextDrawLetterSize(playerid, gTdDataVehicle[playerid][7], 18.0, 1.0);
		PlayerTextDrawBackgroundColor(playerid, gTdDataVehicle[playerid][7], 0x00000055);
		PlayerTextDrawTextSize(playerid, gTdDataVehicle[playerid][7], 18.0, 18.0); //размер
	    GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	    if(doors == 0)
			color = 0x00FF0055;
		else
		    color = 0xFF000055;
		PlayerTextDrawBoxColor(playerid, gTdDataVehicle[playerid][7], color); //цвет фона двигателя

	    if(gTdDataVehicle[playerid][8] == PlayerText:INVALID_TEXT_DRAW)
	    {
			//замок - текст
		    if(doors == 0)
				gTdDataVehicle[playerid][8] = CreatePlayerTextDraw(playerid, VEHICLE_START_POSITION_X-12, VEHICLE_START_POSITION_Y+136.0, "UL");
			else
				gTdDataVehicle[playerid][8] = CreatePlayerTextDraw(playerid, VEHICLE_START_POSITION_X-12, VEHICLE_START_POSITION_Y+136.0, "LD");
		}
	    PlayerTextDrawFont(playerid, gTdDataVehicle[playerid][8], 1);//Шрифт
    	PlayerTextDrawAlignment(playerid, gTdDataVehicle[playerid][8], 1);
		PlayerTextDrawSetShadow(playerid, gTdDataVehicle[playerid][8], 0);
		PlayerTextDrawColor(playerid, gTdDataVehicle[playerid][8], 0x000000FF);
		PlayerTextDrawBackgroundColor(playerid, gTdDataVehicle[playerid][8], 0x00000055);
		PlayerTextDrawTextSize(playerid, gTdDataVehicle[playerid][8], 8.0, 8.0);
		PlayerTextDrawLetterSize(playerid, gTdDataVehicle[playerid][8], 0.15, 0.5);

		//фон уровня бензина
		if(gTdDataVehicle[playerid][0] != PlayerText:INVALID_TEXT_DRAW)
			PlayerTextDrawShow(playerid, gTdDataVehicle[playerid][0]);
		//уровень бензина
		if(gTdDataVehicle[playerid][1] != PlayerText:INVALID_TEXT_DRAW)
			PlayerTextDrawShow(playerid, gTdDataVehicle[playerid][1]);
		//фон состояния двигателя
		if(gTdDataVehicle[playerid][2] != PlayerText:INVALID_TEXT_DRAW)
			PlayerTextDrawShow(playerid, gTdDataVehicle[playerid][2]);
		//двигатель вкл/выкл
		if(gTdDataVehicle[playerid][3] != PlayerText:INVALID_TEXT_DRAW)
			PlayerTextDrawShow(playerid, gTdDataVehicle[playerid][3]);
		//состояние корпуса авто
		if(gTdDataVehicle[playerid][4] != PlayerText:INVALID_TEXT_DRAW)
			PlayerTextDrawShow(playerid, gTdDataVehicle[playerid][4]);

		//состояние аккумулятора (фон)
		if(gTdDataVehicle[playerid][5] != PlayerText:INVALID_TEXT_DRAW)
			PlayerTextDrawShow(playerid, gTdDataVehicle[playerid][5]);
		//состояние аккумулятора (проценты)
		if(gTdDataVehicle[playerid][6] != PlayerText:INVALID_TEXT_DRAW)
			PlayerTextDrawShow(playerid, gTdDataVehicle[playerid][6]);

		//состояние замка (фон)
		if(gTdDataVehicle[playerid][7] != PlayerText:INVALID_TEXT_DRAW)
			PlayerTextDrawShow(playerid, gTdDataVehicle[playerid][7]);
		//состояние замка (надпись)
		if(gTdDataVehicle[playerid][8] != PlayerText:INVALID_TEXT_DRAW)
			PlayerTextDrawShow(playerid, gTdDataVehicle[playerid][8]);
	}

	gVehicleDataShow[playerid] = vehicleid;
}

//убрать показатели авто
public destroy_vehicle_sensors(playerid)
{
	new i;

	for(i = 0; i < TD_COUNT_VEHICLE; ++i)
	{
		if(gTdDataVehicle[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, gTdDataVehicle[playerid][i]);
			gTdDataVehicle[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
	}
	gVehicleDataShow[playerid] = 0;
}

public update_vehicle_sensors(playerid)
{
	new vehicleid;
	new Float:level;
	new color, buff;
	new Float:VehHealth;
	new VehHealthStr[16];
	new VehHealthInt;
	new engine, lights, alarm, doors, bonnet, boot, objective;

	if(playerid == INVALID_PLAYER_ID)
	    return;

	//если сенсор не отображается - выходим
	if(gVehicleDataShow[playerid] == 0)// || !IsPlayerInAnyVehicle(playerid))
	    return;

	vehicleid = gVehicleDataShow[playerid];

	//если расход топлива нулевой - не показываем состояние бака
	if(gVeh[vehicleid][5] == 0)
	{
        destroy_vehicle_sensors(playerid);
	}
	else
	{
	    if(gTdDataVehicle[playerid][1] == PlayerText:INVALID_TEXT_DRAW)
	    {
			//уровень топлива автомобиля
			gTdDataVehicle[playerid][1] = CreatePlayerTextDraw(playerid, VEHICLE_START_POSITION_X, VEHICLE_START_POSITION_Y+75.0, "~n~");
		}
		//уровень бензина
		PlayerTextDrawHide(playerid, gTdDataVehicle[playerid][1]);
		
		PlayerTextDrawUseBox(playerid, gTdDataVehicle[playerid][1], 1);
		PlayerTextDrawSetShadow(playerid, gTdDataVehicle[playerid][1], 0);
		PlayerTextDrawColor(playerid, gTdDataVehicle[playerid][1], 0x00000000);
		PlayerTextDrawTextSize(playerid, gTdDataVehicle[playerid][1], 20.0, 0.0);
		PlayerTextDrawBackgroundColor(playerid, gTdDataVehicle[playerid][1], 0x00FF0055);

	    if(gVeh[vehicleid][3] < gVeh[vehicleid][6])
	    {
	        buff = (255*gVeh[vehicleid][3])/gVeh[vehicleid][6];
	        color = ((0xFF-buff) << 24) | (buff<<16) | 0x55;
	    }
		else
		    color = 0x00FF0055;

		if(gVeh[vehicleid][3] <= 0)
		{
		    level = -0.4;
		}
		else
		{
			level = floatsub(floatdiv(floatmul((-8.1),Float:gVeh[vehicleid][3]),Float:gVeh[vehicleid][6]),0.5);
			if(level < -8.6)
			    level = -8.6;
	    }
		PlayerTextDrawBoxColor(playerid, gTdDataVehicle[playerid][1], color); //цвет
		PlayerTextDrawLetterSize(playerid, gTdDataVehicle[playerid][1], 300.0, level); //от -0.4 до -8.6


		if(gTdDataVehicle[playerid][3] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawHide(playerid, gTdDataVehicle[playerid][2]);
		    if(gVeh[vehicleid][2] > 0)
		    {
				buff = (0xFF*gVeh[vehicleid][2])/1000;
				color = ((0xFF-buff) << 24) | (buff<<16) | 0x55;
		    }
			else
			    color = 0xFF000055;
		    
			PlayerTextDrawBoxColor(playerid, gTdDataVehicle[playerid][2], color); //цвет фона двигателя
		}


		if(gTdDataVehicle[playerid][3] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawHide(playerid, gTdDataVehicle[playerid][3]);
		    if(gVeh[vehicleid][4] > 0)
				PlayerTextDrawSetString(playerid, gTdDataVehicle[playerid][3], "ON");
			else
				PlayerTextDrawSetString(playerid, gTdDataVehicle[playerid][3], "OFF");
		}
		
		
	    if(gTdDataVehicle[playerid][4] == PlayerText:INVALID_TEXT_DRAW)
	    {
			//состояние корпуса авто
			gTdDataVehicle[playerid][4] = CreatePlayerTextDraw(playerid, VEHICLE_START_POSITION_X-13, VEHICLE_START_POSITION_Y+94.0, "hud:radar_impound");
		}
	    PlayerTextDrawFont(playerid, gTdDataVehicle[playerid][4], 4);//Шрифт
    	PlayerTextDrawAlignment(playerid, gTdDataVehicle[playerid][4], 1);
		PlayerTextDrawSetShadow(playerid, gTdDataVehicle[playerid][4], 0);
		PlayerTextDrawBackgroundColor(playerid, gTdDataVehicle[playerid][4], 0x00000055);
		PlayerTextDrawTextSize(playerid, gTdDataVehicle[playerid][4], 15.0, 15.0);
		PlayerTextDrawLetterSize(playerid, gTdDataVehicle[playerid][4], 0.15, 0.5);
		GetVehicleHealth(vehicleid, VehHealth);
		format(VehHealthStr, sizeof(VehHealthStr), "%f", VehHealth);
		VehHealthInt = strval(VehHealthStr);
	    if(VehHealthInt > 300)
	    {
			buff = (0xFF*(VehHealthInt-300))/700;
			color = ((0xFF-buff) << 24) | (buff<<16) | 0x55;
	    }
		else
		    color = 0xFF000055;

//		new msg[128]; //отладка!!!
//		format(msg, sizeof(msg), "VehHealth=%f, VehHealthInt=%d, color=0x%x", VehHealth, VehHealthInt, color); //отладка!!!
//		SendClientMessage(playerid, color, msg); //отладка!!!
		
		PlayerTextDrawBoxColor(playerid, gTdDataVehicle[playerid][4], color); //цвет состояния корпуса
		PlayerTextDrawColor(playerid, gTdDataVehicle[playerid][4], color);


		if(gTdDataVehicle[playerid][5] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawHide(playerid, gTdDataVehicle[playerid][5]);
		    if(gVeh[vehicleid][9] > 0) //аккумулятор
		    {
				buff = (0xFF*gVeh[vehicleid][9])/1000;
				color = ((0xFF-buff) << 24) | (buff<<16) | 0x55;
		    }
			else
			    color = 0xFF000055;

			PlayerTextDrawBoxColor(playerid, gTdDataVehicle[playerid][5], color); //цвет фона двигателя
		}

		if(gTdDataVehicle[playerid][6] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawHide(playerid, gTdDataVehicle[playerid][6]);
			format(VehHealthStr, sizeof(VehHealthStr), "%d%%", gVeh[vehicleid][9]/10);
			PlayerTextDrawSetString(playerid, gTdDataVehicle[playerid][6], VehHealthStr);
		}
		
	    GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
		if(gTdDataVehicle[playerid][7] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawHide(playerid, gTdDataVehicle[playerid][7]);
		    if(doors == 0) //замок
				color = 0x00FF0055;
			else
			    color = 0xFF000055;
			PlayerTextDrawBoxColor(playerid, gTdDataVehicle[playerid][7], color); //цвет фона двигателя
		}
		if(gTdDataVehicle[playerid][8] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawHide(playerid, gTdDataVehicle[playerid][8]);
			if(doors == 0)
				PlayerTextDrawSetString(playerid, gTdDataVehicle[playerid][8], "UL");
			else
				PlayerTextDrawSetString(playerid, gTdDataVehicle[playerid][8], "LD");
		}

		//уровень бензина
		if(gTdDataVehicle[playerid][1] != PlayerText:INVALID_TEXT_DRAW)
			PlayerTextDrawShow(playerid, gTdDataVehicle[playerid][1]);
			
		//фон состояния двигателя
		if(gTdDataVehicle[playerid][2] != PlayerText:INVALID_TEXT_DRAW)
			PlayerTextDrawShow(playerid, gTdDataVehicle[playerid][2]);
		//состояние двигателя
		if(gTdDataVehicle[playerid][3] != PlayerText:INVALID_TEXT_DRAW)
			PlayerTextDrawShow(playerid, gTdDataVehicle[playerid][3]);

		//состояние корпуса
		if(gTdDataVehicle[playerid][4] != PlayerText:INVALID_TEXT_DRAW)
			PlayerTextDrawShow(playerid, gTdDataVehicle[playerid][4]);

		//состояние аккумулятора (фон)
		if(gTdDataVehicle[playerid][5] != PlayerText:INVALID_TEXT_DRAW)
			PlayerTextDrawShow(playerid, gTdDataVehicle[playerid][5]);
		//состояние аккумулфтора (значение)
		if(gTdDataVehicle[playerid][6] != PlayerText:INVALID_TEXT_DRAW)
			PlayerTextDrawShow(playerid, gTdDataVehicle[playerid][6]);

		//состояние замка (фон)
		if(gTdDataVehicle[playerid][7] != PlayerText:INVALID_TEXT_DRAW)
			PlayerTextDrawShow(playerid, gTdDataVehicle[playerid][7]);
		//состояние замка (надпись)
		if(gTdDataVehicle[playerid][8] != PlayerText:INVALID_TEXT_DRAW)
			PlayerTextDrawShow(playerid, gTdDataVehicle[playerid][8]);
	}
}

public create_spectate_data()
{
    if(gSpectateFon[0] == Text:INVALID_TEXT_DRAW)
    {
		//большой фон данных игрока
		gSpectateFon[0] = TextDrawCreate(SPECTATE_START_POSITION_X, SPECTATE_START_POSITION_Y, "Data");
	}
	
	TextDrawFont(gSpectateFon[0], TEXT_DRAW_FONT_MODEL_PREVIEW);
	TextDrawUseBox(gSpectateFon[0], 0);
	TextDrawBackgroundColor(gSpectateFon[0], 0x88888855); //0xFFFFFF88
	TextDrawSetPreviewRot(gSpectateFon[0], 90.0, 0.0, 0.0, -100.0);
	TextDrawSetShadow(gSpectateFon[0], 0);
	TextDrawColor(gSpectateFon[0], 0x88888855);
	TextDrawTextSize(gSpectateFon[0], 200.0, 224.0);
	TextDrawBackgroundColor(gSpectateFon[0], 0x88888855);
	TextDrawBoxColor(gSpectateFon[0], 0x88888855); //цвет

    if(gSpectateFon[1] == Text:INVALID_TEXT_DRAW)
    {
		//фон полоса (ник и id игрока)
		gSpectateFon[1] = TextDrawCreate(SPECTATE_START_POSITION_X, SPECTATE_START_POSITION_Y, "Data");
	}
	TextDrawFont(gSpectateFon[1], TEXT_DRAW_FONT_MODEL_PREVIEW);
	TextDrawUseBox(gSpectateFon[1], 0);
	TextDrawBackgroundColor(gSpectateFon[1], 0x00000055); //0xFFFFFF88
	TextDrawSetPreviewRot(gSpectateFon[1], 90.0, 0.0, 0.0, -100.0);
	TextDrawSetShadow(gSpectateFon[1], 0);
	TextDrawColor(gSpectateFon[1], 0x00000055);
	TextDrawTextSize(gSpectateFon[1], 200.0, 15.0);
	TextDrawBackgroundColor(gSpectateFon[1], 0x00000055);
	TextDrawBoxColor(gSpectateFon[1], 0x00000055); //цвет

    if(gSpectateFon[2] == Text:INVALID_TEXT_DRAW)
    {
		//название - очки
		gSpectateFon[2] = TextDrawCreate(SPECTATE_START_POSITION_X+10, SPECTATE_START_POSITION_Y+20, "Score:");
	}
	TextDrawFont(gSpectateFon[2], 1);
	TextDrawUseBox(gSpectateFon[2], 0);
	TextDrawBackgroundColor(gSpectateFon[2], 0x00CC0055);
	TextDrawSetShadow(gSpectateFon[2], 0);
	TextDrawColor(gSpectateFon[2], 0x00CC0055);
	TextDrawTextSize(gSpectateFon[2], 100.0, 15.0);
	TextDrawLetterSize(gSpectateFon[2], 0.2, 1.0);


    if(gSpectateFon[3] == Text:INVALID_TEXT_DRAW)
    {
		//название - температура
		gSpectateFon[3] = TextDrawCreate(SPECTATE_START_POSITION_X+10, SPECTATE_START_POSITION_Y+34, "Temperature:");
	}
	TextDrawFont(gSpectateFon[3], 1);
	TextDrawUseBox(gSpectateFon[3], 0);
	TextDrawBackgroundColor(gSpectateFon[3], 0x33FF3355);
	TextDrawSetShadow(gSpectateFon[3], 0);
	TextDrawColor(gSpectateFon[3], 0x33FF3355);
	TextDrawTextSize(gSpectateFon[3], 100.0, 15.0);
	TextDrawLetterSize(gSpectateFon[3], 0.2, 1.0);

    if(gSpectateFon[4] == Text:INVALID_TEXT_DRAW)
    {
		//название - кров ь
		gSpectateFon[4] = TextDrawCreate(SPECTATE_START_POSITION_X+10, SPECTATE_START_POSITION_Y+44, "Blood:");
	}
	TextDrawFont(gSpectateFon[4], 1);
	TextDrawUseBox(gSpectateFon[4], 0);
	TextDrawBackgroundColor(gSpectateFon[4], 0x33FF3355);
	TextDrawSetShadow(gSpectateFon[4], 0);
	TextDrawColor(gSpectateFon[4], 0x33FF3355);
	TextDrawTextSize(gSpectateFon[4], 100.0, 15.0);
	TextDrawLetterSize(gSpectateFon[4], 0.2, 1.0);

    if(gSpectateFon[5] == Text:INVALID_TEXT_DRAW)
    {
		//название - голод
		gSpectateFon[5] = TextDrawCreate(SPECTATE_START_POSITION_X+10, SPECTATE_START_POSITION_Y+54, "Hunger:");
	}
	TextDrawFont(gSpectateFon[5], 1);
	TextDrawUseBox(gSpectateFon[5], 0);
	TextDrawBackgroundColor(gSpectateFon[5], 0x33FF3355);
	TextDrawSetShadow(gSpectateFon[5], 0);
	TextDrawColor(gSpectateFon[5], 0x33FF3355);
	TextDrawTextSize(gSpectateFon[5], 100.0, 15.0);
	TextDrawLetterSize(gSpectateFon[5], 0.2, 1.0);

    if(gSpectateFon[6] == Text:INVALID_TEXT_DRAW)
    {
		//название - жажда
		gSpectateFon[6] = TextDrawCreate(SPECTATE_START_POSITION_X+10, SPECTATE_START_POSITION_Y+64, "Thirst:");
	}
	TextDrawFont(gSpectateFon[6], 1);
	TextDrawUseBox(gSpectateFon[6], 0);
	TextDrawBackgroundColor(gSpectateFon[6], 0x33FF3355);
	TextDrawSetShadow(gSpectateFon[6], 0);
	TextDrawColor(gSpectateFon[6], 0x33FF3355);
	TextDrawTextSize(gSpectateFon[6], 100.0, 15.0);
	TextDrawLetterSize(gSpectateFon[6], 0.2, 1.0);

    if(gSpectateFon[7] == Text:INVALID_TEXT_DRAW)
    {
		//название - ранение
		gSpectateFon[7] = TextDrawCreate(SPECTATE_START_POSITION_X+10, SPECTATE_START_POSITION_Y+74, "Wound:");
	}
	TextDrawFont(gSpectateFon[7], 1);
	TextDrawUseBox(gSpectateFon[7], 0);
	TextDrawBackgroundColor(gSpectateFon[7], 0x33FF3355);
	TextDrawSetShadow(gSpectateFon[7], 0);
	TextDrawColor(gSpectateFon[7], 0x33FF3355);
	TextDrawTextSize(gSpectateFon[7], 100.0, 15.0);
	TextDrawLetterSize(gSpectateFon[7], 0.2, 1.0);

    if(gSpectateFon[8] == Text:INVALID_TEXT_DRAW)
    {
		//название - время в игре
		gSpectateFon[8] = TextDrawCreate(SPECTATE_START_POSITION_X+10, SPECTATE_START_POSITION_Y+87, "Survival_time:");
	}
	TextDrawFont(gSpectateFon[8], 1);
	TextDrawUseBox(gSpectateFon[8], 0);
	TextDrawBackgroundColor(gSpectateFon[8], 0x99999955);
	TextDrawSetShadow(gSpectateFon[8], 0);
	TextDrawColor(gSpectateFon[8], 0x99999955);
	TextDrawTextSize(gSpectateFon[8], 100.0, 15.0);
	TextDrawLetterSize(gSpectateFon[8], 0.2, 1.0);

    if(gSpectateFon[9] == Text:INVALID_TEXT_DRAW)
    {
		//название - время в игре
		gSpectateFon[9] = TextDrawCreate(SPECTATE_START_POSITION_X+10, SPECTATE_START_POSITION_Y+100, "Gun_mode:");
	}
	TextDrawFont(gSpectateFon[9], 1);
	TextDrawUseBox(gSpectateFon[9], 0);
	TextDrawBackgroundColor(gSpectateFon[9], 0x3333BB55);
	TextDrawSetShadow(gSpectateFon[9], 0);
	TextDrawColor(gSpectateFon[9], 0x3333BB55);
	TextDrawTextSize(gSpectateFon[9], 100.0, 15.0);
	TextDrawLetterSize(gSpectateFon[9], 0.2, 1.0);

    if(gSpectateFon[10] == Text:INVALID_TEXT_DRAW)
    {
		//IP
		gSpectateFon[10] = TextDrawCreate(SPECTATE_START_POSITION_X+92, SPECTATE_START_POSITION_Y+20, "IP:");
	}
	TextDrawFont(gSpectateFon[10], 1);
	TextDrawUseBox(gSpectateFon[10], 0);
	TextDrawBackgroundColor(gSpectateFon[10], 0xEEEECC55);
	TextDrawSetShadow(gSpectateFon[10], 0);
	TextDrawColor(gSpectateFon[10], 0xEEEECC55);
	TextDrawTextSize(gSpectateFon[10], 20.0, 15.0);
	TextDrawLetterSize(gSpectateFon[10], 0.2, 1.0);
	TextDrawAlignment(gSpectateFon[10], 1); //по левому краю

    if(gSpectateFon[11] == Text:INVALID_TEXT_DRAW)
    {
		//REG IP
		gSpectateFon[11] = TextDrawCreate(SPECTATE_START_POSITION_X+92, SPECTATE_START_POSITION_Y+28, "REG_IP:");
	}
	TextDrawFont(gSpectateFon[11], 1);
	TextDrawUseBox(gSpectateFon[11], 0);
	TextDrawBackgroundColor(gSpectateFon[11], 0xEEEECC55);
	TextDrawSetShadow(gSpectateFon[11], 0);
	TextDrawColor(gSpectateFon[11], 0xEEEECC55);
	TextDrawTextSize(gSpectateFon[11], 20.0, 15.0);
	TextDrawLetterSize(gSpectateFon[11], 0.2, 1.0);
	TextDrawAlignment(gSpectateFon[11], 1); //по левому краю

    if(gSpectateFon[12] == Text:INVALID_TEXT_DRAW)
    {
		//дата входа
		gSpectateFon[12] = TextDrawCreate(SPECTATE_START_POSITION_X+92, SPECTATE_START_POSITION_Y+38, "DATE:");
	}
	TextDrawFont(gSpectateFon[12], 1);
	TextDrawUseBox(gSpectateFon[12], 0);
	TextDrawBackgroundColor(gSpectateFon[12], 0xEEEECC55);
	TextDrawSetShadow(gSpectateFon[12], 0);
	TextDrawColor(gSpectateFon[12], 0xEEEECC55);
	TextDrawTextSize(gSpectateFon[12], 20.0, 15.0);
	TextDrawLetterSize(gSpectateFon[12], 0.2, 1.0);
	TextDrawAlignment(gSpectateFon[12], 1); //по левому краю

    if(gSpectateFon[13] == Text:INVALID_TEXT_DRAW)
    {
		//дата регистрации
		gSpectateFon[13] = TextDrawCreate(SPECTATE_START_POSITION_X+92, SPECTATE_START_POSITION_Y+46, "REG_DATE:");
	}
	TextDrawFont(gSpectateFon[13], 1);
	TextDrawUseBox(gSpectateFon[13], 0);
	TextDrawBackgroundColor(gSpectateFon[13], 0xEEEECC55);
	TextDrawSetShadow(gSpectateFon[13], 0);
	TextDrawColor(gSpectateFon[13], 0xEEEECC55);
	TextDrawTextSize(gSpectateFon[13], 20.0, 15.0);
	TextDrawLetterSize(gSpectateFon[13], 0.2, 1.0);
	TextDrawAlignment(gSpectateFon[13], 1); //по левому краю
	
    if(gSpectateFon[14] == Text:INVALID_TEXT_DRAW)
    {
		//администратор (уровень)
		gSpectateFon[14] = TextDrawCreate(SPECTATE_START_POSITION_X+92, SPECTATE_START_POSITION_Y+56, "ADMIN_LEVEL:");
	}
	TextDrawFont(gSpectateFon[14], 1);
	TextDrawUseBox(gSpectateFon[14], 0);
	TextDrawBackgroundColor(gSpectateFon[14], 0xEEEECC55);
	TextDrawSetShadow(gSpectateFon[14], 0);
	TextDrawColor(gSpectateFon[14], 0xEEEECC55);
	TextDrawTextSize(gSpectateFon[14], 20.0, 15.0);
	TextDrawLetterSize(gSpectateFon[14], 0.2, 1.0);
	TextDrawAlignment(gSpectateFon[14], 1); //по левому краю

    if(gSpectateFon[15] == Text:INVALID_TEXT_DRAW)
    {
		//страна
		gSpectateFon[15] = TextDrawCreate(SPECTATE_START_POSITION_X+92, SPECTATE_START_POSITION_Y+66, "COUNTRY:");
	}
	TextDrawFont(gSpectateFon[15], 1);
	TextDrawUseBox(gSpectateFon[15], 0);
	TextDrawBackgroundColor(gSpectateFon[15], 0xEEEECC55);
	TextDrawSetShadow(gSpectateFon[15], 0);
	TextDrawColor(gSpectateFon[15], 0xEEEECC55);
	TextDrawTextSize(gSpectateFon[15], 20.0, 15.0);
	TextDrawLetterSize(gSpectateFon[15], 0.2, 1.0);
	TextDrawAlignment(gSpectateFon[15], 1); //по левому краю

    if(gSpectateFon[16] == Text:INVALID_TEXT_DRAW)
    {
		//город
		gSpectateFon[16] = TextDrawCreate(SPECTATE_START_POSITION_X+92, SPECTATE_START_POSITION_Y+74, "CITY:");
	}
	TextDrawFont(gSpectateFon[16], 1);
	TextDrawUseBox(gSpectateFon[16], 0);
	TextDrawBackgroundColor(gSpectateFon[16], 0xEEEECC55);
	TextDrawSetShadow(gSpectateFon[16], 0);
	TextDrawColor(gSpectateFon[16], 0xEEEECC55);
	TextDrawTextSize(gSpectateFon[16], 20.0, 15.0);
	TextDrawLetterSize(gSpectateFon[16], 0.2, 1.0);
	TextDrawAlignment(gSpectateFon[16], 1); //по левому краю

    if(gSpectateFon[17] == Text:INVALID_TEXT_DRAW)
    {
		//язык
		gSpectateFon[17] = TextDrawCreate(SPECTATE_START_POSITION_X+92, SPECTATE_START_POSITION_Y+82, "LANGUAGE:");
	}
	TextDrawFont(gSpectateFon[17], 1);
	TextDrawUseBox(gSpectateFon[17], 0);
	TextDrawBackgroundColor(gSpectateFon[17], 0xEEEECC55);
	TextDrawSetShadow(gSpectateFon[17], 0);
	TextDrawColor(gSpectateFon[17], 0xEEEECC55);
	TextDrawTextSize(gSpectateFon[17], 20.0, 15.0);
	TextDrawLetterSize(gSpectateFon[17], 0.2, 1.0);
	TextDrawAlignment(gSpectateFon[17], 1); //по левому краю
	
    if(gSpectateFon[18] == Text:INVALID_TEXT_DRAW)
    {
		//количество киков
		gSpectateFon[18] = TextDrawCreate(SPECTATE_START_POSITION_X+92, SPECTATE_START_POSITION_Y+92, "MUTE_COUNT:");
	}
	TextDrawFont(gSpectateFon[18], 1);
	TextDrawUseBox(gSpectateFon[18], 0);
	TextDrawBackgroundColor(gSpectateFon[18], 0xEEEECC55);
	TextDrawSetShadow(gSpectateFon[18], 0);
	TextDrawColor(gSpectateFon[18], 0xEEEECC55);
	TextDrawTextSize(gSpectateFon[18], 20.0, 15.0);
	TextDrawLetterSize(gSpectateFon[18], 0.2, 1.0);
	TextDrawAlignment(gSpectateFon[18], 1); //по левому краю

    if(gSpectateFon[19] == Text:INVALID_TEXT_DRAW)
    {
		//количество киков
		gSpectateFon[19] = TextDrawCreate(SPECTATE_START_POSITION_X+92, SPECTATE_START_POSITION_Y+100, "KICK_COUNT:");
	}
	TextDrawFont(gSpectateFon[19], 1);
	TextDrawUseBox(gSpectateFon[19], 0);
	TextDrawBackgroundColor(gSpectateFon[19], 0xEEEECC55);
	TextDrawSetShadow(gSpectateFon[19], 0);
	TextDrawColor(gSpectateFon[19], 0xEEEECC55);
	TextDrawTextSize(gSpectateFon[19], 20.0, 15.0);
	TextDrawLetterSize(gSpectateFon[19], 0.2, 1.0);
	TextDrawAlignment(gSpectateFon[19], 1); //по левому краю
	
    if(gSpectateFon[20] == Text:INVALID_TEXT_DRAW)
    {
		//количество банов
		gSpectateFon[20] = TextDrawCreate(SPECTATE_START_POSITION_X+92, SPECTATE_START_POSITION_Y+108, "BAN_COUNT:");
	}
	TextDrawFont(gSpectateFon[20], 1);
	TextDrawUseBox(gSpectateFon[20], 0);
	TextDrawBackgroundColor(gSpectateFon[20], 0xEEEECC55);
	TextDrawSetShadow(gSpectateFon[20], 0);
	TextDrawColor(gSpectateFon[20], 0xEEEECC55);
	TextDrawTextSize(gSpectateFon[20], 20.0, 15.0);
	TextDrawLetterSize(gSpectateFon[20], 0.2, 1.0);
	TextDrawAlignment(gSpectateFon[20], 1); //по левому краю
	
    if(gSpectateFon[21] == Text:INVALID_TEXT_DRAW)
    {
		//отключен ли чат
		gSpectateFon[21] = TextDrawCreate(SPECTATE_START_POSITION_X+92, SPECTATE_START_POSITION_Y+118, "IS_MUTED:");
	}
	TextDrawFont(gSpectateFon[21], 1);
	TextDrawUseBox(gSpectateFon[21], 0);
	TextDrawBackgroundColor(gSpectateFon[21], 0xEEEECC55);
	TextDrawSetShadow(gSpectateFon[21], 0);
	TextDrawColor(gSpectateFon[21], 0xEEEECC55);
	TextDrawTextSize(gSpectateFon[21], 20.0, 15.0);
	TextDrawLetterSize(gSpectateFon[21], 0.2, 1.0);
	TextDrawAlignment(gSpectateFon[21], 1); //по левому краю

    if(gSpectateFon[22] == Text:INVALID_TEXT_DRAW)
    {
		//отключен ли чат
		gSpectateFon[22] = TextDrawCreate(SPECTATE_START_POSITION_X+10, SPECTATE_START_POSITION_Y+128, "THE_SAME_PLAYER:");
	}
	TextDrawFont(gSpectateFon[22], 1);
	TextDrawUseBox(gSpectateFon[22], 0);
	TextDrawBackgroundColor(gSpectateFon[22], 0xEEEECC55);
	TextDrawSetShadow(gSpectateFon[22], 0);
	TextDrawColor(gSpectateFon[22], 0xEEEECC55);
	TextDrawTextSize(gSpectateFon[22], 50.0, 15.0);
	TextDrawLetterSize(gSpectateFon[22], 0.2, 1.0);
	TextDrawAlignment(gSpectateFon[22], 1); //по левому краю

    if(gSpectateFon[23] == Text:INVALID_TEXT_DRAW)
    {
		//отключен ли чат
		gSpectateFon[23] = TextDrawCreate(SPECTATE_START_POSITION_X+10, SPECTATE_START_POSITION_Y+170, "PLAYERS_WITH_THE_SAME_IP:");
	}
	TextDrawFont(gSpectateFon[23], 1);
	TextDrawUseBox(gSpectateFon[23], 0);
	TextDrawBackgroundColor(gSpectateFon[23], 0xEEEECC55);
	TextDrawSetShadow(gSpectateFon[23], 0);
	TextDrawColor(gSpectateFon[23], 0xEEEECC55);
	TextDrawTextSize(gSpectateFon[23], 180.0, 15.0);
	TextDrawLetterSize(gSpectateFon[23], 0.2, 1.0);
	TextDrawAlignment(gSpectateFon[23], 1); //по левому краю
	
	for(new i = 0; i < SPECTATE_FON_NUMBER; ++i)
	{
		TextDrawHideForAll(gSpectateFon[i]);
	}

	for(new i = 0; i < SPECTATE_DATA_NUMBER; ++i)
	{
	    for(new j = 0; j < MAX_PLAYERS; ++j)
	    {
		    if(gSpectateData[j][i] != PlayerText:INVALID_TEXT_DRAW)
		    {
				PlayerTextDrawDestroy(j, gSpectateData[j][i]);
		        gSpectateData[j][i] = PlayerText:INVALID_TEXT_DRAW;
			}
	    }
	}
}

//показать данные одного игрока для другого
//update - смена игрока
public  show_spectate_data(playerid, spec_player, bool:update)
{
	new name[64];
	new str[128];
	new list[512];
	static PrevMute[MAX_PLAYERS];
	static PrevValue[MAX_PLAYERS][64];

	if(update)
	{
		hide_spectate_data(playerid);
		for(new i = 0; i < SPECTATE_FON_NUMBER; ++i)
		{
		    if(gSpectateFon[i] != Text:INVALID_TEXT_DRAW)
		    {
				TextDrawShowForPlayer(playerid, gSpectateFon[i]);
			}
		}
	}

	if(update)
	{
	    //ник
		GetPlayerName(spec_player, name, sizeof(name));
		if(gSpectateData[playerid][0] != PlayerText:INVALID_TEXT_DRAW)
		    PlayerTextDrawDestroy(playerid, gSpectateData[playerid][0]);
		gSpectateData[playerid][0] = CreatePlayerTextDraw(playerid, SPECTATE_START_POSITION_X+15, SPECTATE_START_POSITION_Y+3, name);
		PlayerTextDrawFont(playerid, gSpectateData[playerid][0], 1);
		PlayerTextDrawUseBox(playerid, gSpectateData[playerid][0], 0);
		PlayerTextDrawBackgroundColor(playerid, gSpectateData[playerid][0], 0xFFFFFF55);
		PlayerTextDrawSetShadow(playerid, gSpectateData[playerid][0], 0);
		PlayerTextDrawColor(playerid, gSpectateData[playerid][0], 0xFFFFFF55);
		PlayerTextDrawTextSize(playerid, gSpectateData[playerid][0], 200.0, 10.0);
		PlayerTextDrawLetterSize(playerid, gSpectateData[playerid][0], 0.2, 1.0);
		PlayerTextDrawAlignment(playerid, gSpectateData[playerid][0], 1); //по левому краю
		PlayerTextDrawShow(playerid, gSpectateData[playerid][0]);

		//id
		if(gSpectateData[playerid][1] != PlayerText:INVALID_TEXT_DRAW)
		    PlayerTextDrawDestroy(playerid, gSpectateData[playerid][1]);
		format(str, sizeof(str), "[id:%d]", spec_player);
		gSpectateData[playerid][1] = CreatePlayerTextDraw(playerid, SPECTATE_START_POSITION_X+170, SPECTATE_START_POSITION_Y+3, str);
		PlayerTextDrawFont(playerid, gSpectateData[playerid][1], 1);
		PlayerTextDrawUseBox(playerid, gSpectateData[playerid][1], 0);
		PlayerTextDrawBackgroundColor(playerid, gSpectateData[playerid][1], 0xFFFFFF55);
		PlayerTextDrawSetShadow(playerid, gSpectateData[playerid][1], 0);
		PlayerTextDrawColor(playerid, gSpectateData[playerid][1], 0xFFFFFF55);
		PlayerTextDrawTextSize(playerid, gSpectateData[playerid][1], 100.0, 10.0);
		PlayerTextDrawLetterSize(playerid, gSpectateData[playerid][1], 0.2, 1.0);
//		PlayerTextDrawAlignment(playerid, gSpectateData[playerid][1], 3); //по правому краю
		PlayerTextDrawShow(playerid, gSpectateData[playerid][1]);
	}

	//очки
	if(update)
	{
		if(gSpectateData[playerid][2] != PlayerText:INVALID_TEXT_DRAW)
		    PlayerTextDrawDestroy(playerid, gSpectateData[playerid][2]);
		format(str, sizeof(str), "%d", GetPlayerScore(spec_player));
		gSpectateData[playerid][2] = CreatePlayerTextDraw(playerid, SPECTATE_START_POSITION_X+85, SPECTATE_START_POSITION_Y+20, str);
		PlayerTextDrawFont(playerid, gSpectateData[playerid][2], 1);
		PlayerTextDrawUseBox(playerid, gSpectateData[playerid][2], 0);
		PlayerTextDrawBackgroundColor(playerid, gSpectateData[playerid][2], 0x5555FF55);
		PlayerTextDrawSetShadow(playerid, gSpectateData[playerid][2], 0);
		PlayerTextDrawColor(playerid, gSpectateData[playerid][2], 0x5555FF55);
		PlayerTextDrawTextSize(playerid, gSpectateData[playerid][2], 35.0, 10.0);
		PlayerTextDrawLetterSize(playerid, gSpectateData[playerid][2], 0.2, 1.0);
		PlayerTextDrawAlignment(playerid, gSpectateData[playerid][2], 3); //по правому краю
	}
	else
	{
		if(gSpectateData[playerid][2] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawHide(playerid, gSpectateData[playerid][2]);
			format(str, sizeof(str), "%d", GetPlayerScore(spec_player));
			PlayerTextDrawSetString(playerid, gSpectateData[playerid][2], str);
		}
	}
	if(gSpectateData[playerid][2] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawShow(playerid, gSpectateData[playerid][2]);

	//температура
	if(update)
	{
		if(gSpectateData[playerid][3] != PlayerText:INVALID_TEXT_DRAW)
		    PlayerTextDrawDestroy(playerid, gSpectateData[playerid][3]);
		format(str, sizeof(str), "%d.%d", gTemperature[spec_player]/100, (gTemperature[spec_player]%100)/10);
		gSpectateData[playerid][3] = CreatePlayerTextDraw(playerid, SPECTATE_START_POSITION_X+85, SPECTATE_START_POSITION_Y+34, str);
		PlayerTextDrawFont(playerid, gSpectateData[playerid][3], 1);
		PlayerTextDrawUseBox(playerid, gSpectateData[playerid][3], 0);
		PlayerTextDrawBackgroundColor(playerid, gSpectateData[playerid][3], 0xDDDDDD55);
		PlayerTextDrawSetShadow(playerid, gSpectateData[playerid][3], 0);
		PlayerTextDrawColor(playerid, gSpectateData[playerid][3], 0xDDDDDD55);
		PlayerTextDrawTextSize(playerid, gSpectateData[playerid][3], 35.0, 10.0);
		PlayerTextDrawLetterSize(playerid, gSpectateData[playerid][3], 0.2, 1.0);
		PlayerTextDrawAlignment(playerid, gSpectateData[playerid][3], 3); //по правому краю
	}
	else
	{
		if(gSpectateData[playerid][3] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawHide(playerid, gSpectateData[playerid][3]);
			format(str, sizeof(str), "%d.%d", gTemperature[spec_player]/100, (gTemperature[spec_player]%100)/10);
			PlayerTextDrawSetString(playerid, gSpectateData[playerid][3], str);
		}
	}
	if(gSpectateData[playerid][3] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawShow(playerid, gSpectateData[playerid][3]);
	
	//кров ь
	if(update)
	{
		if(gSpectateData[playerid][4] != PlayerText:INVALID_TEXT_DRAW)
		    PlayerTextDrawDestroy(playerid, gSpectateData[playerid][4]);
		format(str, sizeof(str), "%d", gHealth[spec_player]);
		gSpectateData[playerid][4] = CreatePlayerTextDraw(playerid, SPECTATE_START_POSITION_X+85, SPECTATE_START_POSITION_Y+44, str);
		PlayerTextDrawFont(playerid, gSpectateData[playerid][4], 1);
		PlayerTextDrawUseBox(playerid, gSpectateData[playerid][4], 0);
		PlayerTextDrawBackgroundColor(playerid, gSpectateData[playerid][4], 0xDD191D55);
		PlayerTextDrawSetShadow(playerid, gSpectateData[playerid][4], 0);
		PlayerTextDrawColor(playerid, gSpectateData[playerid][4], 0xDD191D55);
		PlayerTextDrawTextSize(playerid, gSpectateData[playerid][4], 35.0, 10.0);
		PlayerTextDrawLetterSize(playerid, gSpectateData[playerid][4], 0.2, 1.0);
		PlayerTextDrawAlignment(playerid, gSpectateData[playerid][4], 3); //по правому краю
	}
	else
	{
		if(gSpectateData[playerid][4] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawHide(playerid, gSpectateData[playerid][4]);
			format(str, sizeof(str), "%d", gHealth[spec_player]);
			PlayerTextDrawSetString(playerid, gSpectateData[playerid][4], str);
		}
	}
	if(gSpectateData[playerid][4] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawShow(playerid, gSpectateData[playerid][4]);
	
	//голод
	if(update)
	{
		if(gSpectateData[playerid][5] != PlayerText:INVALID_TEXT_DRAW)
		    PlayerTextDrawDestroy(playerid, gSpectateData[playerid][5]);
		format(str, sizeof(str), "%d", gHunger[spec_player]);
		gSpectateData[playerid][5] = CreatePlayerTextDraw(playerid, SPECTATE_START_POSITION_X+85, SPECTATE_START_POSITION_Y+54, str);
		PlayerTextDrawFont(playerid, gSpectateData[playerid][5], 1);
		PlayerTextDrawUseBox(playerid, gSpectateData[playerid][5], 0);
		PlayerTextDrawBackgroundColor(playerid, gSpectateData[playerid][5], 0xA86CFC55);
		PlayerTextDrawSetShadow(playerid, gSpectateData[playerid][5], 0);
		PlayerTextDrawColor(playerid, gSpectateData[playerid][5], 0xA86CFC55);
		PlayerTextDrawTextSize(playerid, gSpectateData[playerid][5], 35.0, 10.0);
		PlayerTextDrawLetterSize(playerid, gSpectateData[playerid][5], 0.2, 1.0);
		PlayerTextDrawAlignment(playerid, gSpectateData[playerid][5], 3); //по правому краю
	}
	else
	{
		if(gSpectateData[playerid][5] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawHide(playerid, gSpectateData[playerid][5]);
			format(str, sizeof(str), "%d", gHunger[spec_player]);
			PlayerTextDrawSetString(playerid, gSpectateData[playerid][5], str);
		}
	}
	if(gSpectateData[playerid][5] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawShow(playerid, gSpectateData[playerid][5]);
	
	//жажда
	if(update)
	{
		if(gSpectateData[playerid][6] != PlayerText:INVALID_TEXT_DRAW)
		    PlayerTextDrawDestroy(playerid, gSpectateData[playerid][6]);
		format(str, sizeof(str), "%d", gThirst[spec_player]);
		gSpectateData[playerid][6] = CreatePlayerTextDraw(playerid, SPECTATE_START_POSITION_X+85, SPECTATE_START_POSITION_Y+64, str);
		PlayerTextDrawFont(playerid, gSpectateData[playerid][6], 1);
		PlayerTextDrawUseBox(playerid, gSpectateData[playerid][6], 0);
		PlayerTextDrawBackgroundColor(playerid, gSpectateData[playerid][6], 0xE2BD6355);
		PlayerTextDrawSetShadow(playerid, gSpectateData[playerid][6], 0);
		PlayerTextDrawColor(playerid, gSpectateData[playerid][6], 0xE2BD6355);
		PlayerTextDrawTextSize(playerid, gSpectateData[playerid][6], 35.0, 10.0);
		PlayerTextDrawLetterSize(playerid, gSpectateData[playerid][6], 0.2, 1.0);
		PlayerTextDrawAlignment(playerid, gSpectateData[playerid][6], 3); //по правому краю
	}
	else
	{
		if(gSpectateData[playerid][6] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawHide(playerid, gSpectateData[playerid][6]);
			format(str, sizeof(str), "%d", gThirst[spec_player]);
			PlayerTextDrawSetString(playerid, gSpectateData[playerid][6], str);
		}
	}
	if(gSpectateData[playerid][6] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawShow(playerid, gSpectateData[playerid][6]);
	
	//рана
	if(update)
	{
		if(gSpectateData[playerid][7] != PlayerText:INVALID_TEXT_DRAW)
		    PlayerTextDrawDestroy(playerid, gSpectateData[playerid][7]);
		format(str, sizeof(str), "%s%d", (gWound[spec_player]>0)?("-"):(""), gWound[spec_player]);
		gSpectateData[playerid][7] = CreatePlayerTextDraw(playerid, SPECTATE_START_POSITION_X+85, SPECTATE_START_POSITION_Y+74, str);
		PlayerTextDrawFont(playerid, gSpectateData[playerid][7], 1);
		PlayerTextDrawUseBox(playerid, gSpectateData[playerid][7], 0);
		PlayerTextDrawBackgroundColor(playerid, gSpectateData[playerid][7], 0xFF242B55);
		PlayerTextDrawSetShadow(playerid, gSpectateData[playerid][7], 0);
		PlayerTextDrawColor(playerid, gSpectateData[playerid][7], 0xFF242B55);
		PlayerTextDrawTextSize(playerid, gSpectateData[playerid][7], 35.0, 10.0);
		PlayerTextDrawLetterSize(playerid, gSpectateData[playerid][7], 0.2, 1.0);
		PlayerTextDrawAlignment(playerid, gSpectateData[playerid][7], 3); //по правому краю
	}
	else
	{
		if(gSpectateData[playerid][7] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawHide(playerid, gSpectateData[playerid][7]);
			format(str, sizeof(str), "%s%d", (gWound[spec_player]>0)?("-"):(""), gWound[spec_player]);
			PlayerTextDrawSetString(playerid, gSpectateData[playerid][7], str);
		}
	}
	if(gSpectateData[playerid][7] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawShow(playerid, gSpectateData[playerid][7]);
	
	//время в игре
	if(update)
	{
		if(gSpectateData[playerid][8] != PlayerText:INVALID_TEXT_DRAW)
		    PlayerTextDrawDestroy(playerid, gSpectateData[playerid][8]);
		format(str, sizeof(str), "%s", gYourTime[spec_player]);
		gSpectateData[playerid][8] = CreatePlayerTextDraw(playerid, SPECTATE_START_POSITION_X+85, SPECTATE_START_POSITION_Y+87, str);
		PlayerTextDrawFont(playerid, gSpectateData[playerid][8], 1);
		PlayerTextDrawUseBox(playerid, gSpectateData[playerid][8], 0);
		PlayerTextDrawBackgroundColor(playerid, gSpectateData[playerid][8], 0x519A4255);
		PlayerTextDrawSetShadow(playerid, gSpectateData[playerid][8], 0);
		PlayerTextDrawColor(playerid, gSpectateData[playerid][8], 0x519A4255);
		PlayerTextDrawTextSize(playerid, gSpectateData[playerid][8], 35.0, 10.0);
		PlayerTextDrawLetterSize(playerid, gSpectateData[playerid][8], 0.2, 1.0);
		PlayerTextDrawAlignment(playerid, gSpectateData[playerid][8], 3); //по правому краю
	}
	else
	{
		if(gSpectateData[playerid][8] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawHide(playerid, gSpectateData[playerid][8]);
			format(str, sizeof(str), "%s", gYourTime[spec_player]);
			PlayerTextDrawSetString(playerid, gSpectateData[playerid][8], str);
		}
	}
	if(gSpectateData[playerid][8] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawShow(playerid, gSpectateData[playerid][8]);
	
	//режим боя
	if(update)
	{
		if(gSpectateData[playerid][9] != PlayerText:INVALID_TEXT_DRAW)
		    PlayerTextDrawDestroy(playerid, gSpectateData[playerid][9]);
		format(str, sizeof(str), "%s", ((gGunMode[spec_player]==0)?("OFF"):("ON")));
		gSpectateData[playerid][9] = CreatePlayerTextDraw(playerid, SPECTATE_START_POSITION_X+85, SPECTATE_START_POSITION_Y+100, str);
		PlayerTextDrawFont(playerid, gSpectateData[playerid][9], 1);
		PlayerTextDrawUseBox(playerid, gSpectateData[playerid][9], 0);
		PlayerTextDrawBackgroundColor(playerid, gSpectateData[playerid][9], 0xCCDD0055);
		PlayerTextDrawSetShadow(playerid, gSpectateData[playerid][9], 0);
		PlayerTextDrawColor(playerid, gSpectateData[playerid][9], 0xCCDD0055);
		PlayerTextDrawTextSize(playerid, gSpectateData[playerid][9], 35.0, 10.0);
		PlayerTextDrawLetterSize(playerid, gSpectateData[playerid][9], 0.2, 1.0);
		PlayerTextDrawAlignment(playerid, gSpectateData[playerid][9], 3); //по правому краю
	}
	else
	{
		if(gSpectateData[playerid][9] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawHide(playerid, gSpectateData[playerid][9]);
			format(str, sizeof(str), "%s", ((gGunMode[spec_player]==0)?("OFF"):("ON")));
			PlayerTextDrawSetString(playerid, gSpectateData[playerid][9], str);
		}
	}
	if(gSpectateData[playerid][9] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawShow(playerid, gSpectateData[playerid][9]);
		
	//текущий ip
	if(update)
	{
		if(gSpectateData[playerid][10] != PlayerText:INVALID_TEXT_DRAW)
		    PlayerTextDrawDestroy(playerid, gSpectateData[playerid][10]);
		if(gAdminLevel[playerid] >= gAdminLevel[spec_player])
		    GetPlayerIp(spec_player, str, sizeof(str));
		else
		    format(str, sizeof(str), "xxx.xxx.xxx.xxx");
		gSpectateData[playerid][10] = CreatePlayerTextDraw(playerid, SPECTATE_START_POSITION_X+190, SPECTATE_START_POSITION_Y+20, str);
		PlayerTextDrawFont(playerid, gSpectateData[playerid][10], 1);
		PlayerTextDrawUseBox(playerid, gSpectateData[playerid][10], 0);
		PlayerTextDrawBackgroundColor(playerid, gSpectateData[playerid][10], 0x00CCFF55);
		PlayerTextDrawSetShadow(playerid, gSpectateData[playerid][10], 0);
		PlayerTextDrawColor(playerid, gSpectateData[playerid][10], 0x00CCFF55);
		PlayerTextDrawTextSize(playerid, gSpectateData[playerid][10], 55.0, 10.0);
		PlayerTextDrawLetterSize(playerid, gSpectateData[playerid][10], 0.2, 1.0);
		PlayerTextDrawAlignment(playerid, gSpectateData[playerid][10], 3); //по правому краю
		PlayerTextDrawShow(playerid, gSpectateData[playerid][10]);
	}
	
	//ip регистрации
	if(update)
	{
		if(gSpectateData[playerid][11] != PlayerText:INVALID_TEXT_DRAW)
		    PlayerTextDrawDestroy(playerid, gSpectateData[playerid][11]);
		if(gAdminLevel[playerid] >= gAdminLevel[spec_player])
			get_players_value("reg_ip", "players", gPlayersID[spec_player], name);
		else
		    format(name, sizeof(name), "xxx.xxx.xxx.xxx");
		gSpectateData[playerid][11] = CreatePlayerTextDraw(playerid, SPECTATE_START_POSITION_X+190, SPECTATE_START_POSITION_Y+28, name);
		PlayerTextDrawFont(playerid, gSpectateData[playerid][11], 1);
		PlayerTextDrawUseBox(playerid, gSpectateData[playerid][11], 0);
		PlayerTextDrawBackgroundColor(playerid, gSpectateData[playerid][11], 0x0000EE55);
		PlayerTextDrawSetShadow(playerid, gSpectateData[playerid][11], 0);
		PlayerTextDrawColor(playerid, gSpectateData[playerid][11], 0x0000EE55);
		PlayerTextDrawTextSize(playerid, gSpectateData[playerid][11], 55.0, 10.0);
		PlayerTextDrawLetterSize(playerid, gSpectateData[playerid][11], 0.2, 1.0);
		PlayerTextDrawAlignment(playerid, gSpectateData[playerid][11], 3); //по правому краю
		PlayerTextDrawShow(playerid, gSpectateData[playerid][11]);
	}
	
	//дата входа
	if(update)
	{
		if(gSpectateData[playerid][12] != PlayerText:INVALID_TEXT_DRAW)
		    PlayerTextDrawDestroy(playerid, gSpectateData[playerid][12]);
		get_players_value("last_date", "players", gPlayersID[spec_player], name);
		gSpectateData[playerid][12] = CreatePlayerTextDraw(playerid, SPECTATE_START_POSITION_X+190, SPECTATE_START_POSITION_Y+38, name);
		PlayerTextDrawFont(playerid, gSpectateData[playerid][12], 1);
		PlayerTextDrawUseBox(playerid, gSpectateData[playerid][12], 0);
		PlayerTextDrawBackgroundColor(playerid, gSpectateData[playerid][12], 0xFFCC0055);
		PlayerTextDrawSetShadow(playerid, gSpectateData[playerid][12], 0);
		PlayerTextDrawColor(playerid, gSpectateData[playerid][12], 0xFFCC0055);
		PlayerTextDrawTextSize(playerid, gSpectateData[playerid][12], 55.0, 10.0);
		PlayerTextDrawLetterSize(playerid, gSpectateData[playerid][12], 0.2, 1.0);
		PlayerTextDrawAlignment(playerid, gSpectateData[playerid][12], 3); //по правому краю
		PlayerTextDrawShow(playerid, gSpectateData[playerid][12]);
	}
	
	//дата регистрации
	if(update)
	{
		if(gSpectateData[playerid][13] != PlayerText:INVALID_TEXT_DRAW)
		    PlayerTextDrawDestroy(playerid, gSpectateData[playerid][13]);
		if(gAdminLevel[playerid] >= gAdminLevel[spec_player])
			get_players_value("reg_date", "players", gPlayersID[spec_player], name);
		else
		    format(name, sizeof(name), "XXXX-XX-XX XX:XX:XX");
		gSpectateData[playerid][13] = CreatePlayerTextDraw(playerid, SPECTATE_START_POSITION_X+190, SPECTATE_START_POSITION_Y+46, name);
		PlayerTextDrawFont(playerid, gSpectateData[playerid][13], 1);
		PlayerTextDrawUseBox(playerid, gSpectateData[playerid][13], 0);
		PlayerTextDrawBackgroundColor(playerid, gSpectateData[playerid][13], 0xEE000055);
		PlayerTextDrawSetShadow(playerid, gSpectateData[playerid][13], 0);
		PlayerTextDrawColor(playerid, gSpectateData[playerid][13], 0xEE000055);
		PlayerTextDrawTextSize(playerid, gSpectateData[playerid][13], 55.0, 10.0);
		PlayerTextDrawLetterSize(playerid, gSpectateData[playerid][13], 0.2, 1.0);
		PlayerTextDrawAlignment(playerid, gSpectateData[playerid][13], 3); //по правому краю
		PlayerTextDrawShow(playerid, gSpectateData[playerid][13]);
	}
	
	//админ (уровень)
	if(update)
	{
		if(gSpectateData[playerid][14] != PlayerText:INVALID_TEXT_DRAW)
		    PlayerTextDrawDestroy(playerid, gSpectateData[playerid][14]);
		format(name, sizeof(name), "%d", gAdminLevel[spec_player]);
		gSpectateData[playerid][14] = CreatePlayerTextDraw(playerid, SPECTATE_START_POSITION_X+190, SPECTATE_START_POSITION_Y+56, name);
		PlayerTextDrawFont(playerid, gSpectateData[playerid][14], 1);
		PlayerTextDrawUseBox(playerid, gSpectateData[playerid][14], 0);
		PlayerTextDrawBackgroundColor(playerid, gSpectateData[playerid][14], 0xAA00AA55);
		PlayerTextDrawSetShadow(playerid, gSpectateData[playerid][14], 0);
		PlayerTextDrawColor(playerid, gSpectateData[playerid][14], 0xAA00AA55);
		PlayerTextDrawTextSize(playerid, gSpectateData[playerid][14], 55.0, 10.0);
		PlayerTextDrawLetterSize(playerid, gSpectateData[playerid][14], 0.2, 1.0);
		PlayerTextDrawAlignment(playerid, gSpectateData[playerid][14], 3); //по правому краю
	}
	else
	{
		if(gSpectateData[playerid][14] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawHide(playerid, gSpectateData[playerid][14]);
			format(name, sizeof(name), "%d", gAdminLevel[spec_player]);
			PlayerTextDrawSetString(playerid, gSpectateData[playerid][14], name);
		}
	}
	if(gSpectateData[playerid][14] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawShow(playerid, gSpectateData[playerid][14]);

	//страна
	if(update)
	{
		if(gSpectateData[playerid][15] != PlayerText:INVALID_TEXT_DRAW)
		    PlayerTextDrawDestroy(playerid, gSpectateData[playerid][15]);
		gSpectateData[playerid][15] = CreatePlayerTextDraw(playerid, SPECTATE_START_POSITION_X+190, SPECTATE_START_POSITION_Y+66, gPlayerCountry[spec_player]);
		PlayerTextDrawFont(playerid, gSpectateData[playerid][15], 1);
		PlayerTextDrawUseBox(playerid, gSpectateData[playerid][15], 0);
		PlayerTextDrawBackgroundColor(playerid, gSpectateData[playerid][15], 0xFF6A0055);
		PlayerTextDrawSetShadow(playerid, gSpectateData[playerid][15], 0);
		PlayerTextDrawColor(playerid, gSpectateData[playerid][15], 0xFF6A0055);
		PlayerTextDrawTextSize(playerid, gSpectateData[playerid][15], 55.0, 10.0);
		PlayerTextDrawLetterSize(playerid, gSpectateData[playerid][15], 0.2, 1.0);
		PlayerTextDrawAlignment(playerid, gSpectateData[playerid][15], 3); //по правому краю
		PlayerTextDrawShow(playerid, gSpectateData[playerid][15]);
	}

	//город
	if(update)
	{
		if(gSpectateData[playerid][16] != PlayerText:INVALID_TEXT_DRAW)
		    PlayerTextDrawDestroy(playerid, gSpectateData[playerid][16]);
		if(gAdminLevel[playerid] >= gAdminLevel[spec_player])
			format(str, sizeof(str), "%s", gPlayerCity[spec_player]);
		else
		    format(str, sizeof(str), "XXXXXXXX");
		gSpectateData[playerid][16] = CreatePlayerTextDraw(playerid, SPECTATE_START_POSITION_X+190, SPECTATE_START_POSITION_Y+74, str);
		PlayerTextDrawFont(playerid, gSpectateData[playerid][16], 1);
		PlayerTextDrawUseBox(playerid, gSpectateData[playerid][16], 0);
		PlayerTextDrawBackgroundColor(playerid, gSpectateData[playerid][16], 0xFF711955);
		PlayerTextDrawSetShadow(playerid, gSpectateData[playerid][16], 0);
		PlayerTextDrawColor(playerid, gSpectateData[playerid][16], 0xFF711955);
		PlayerTextDrawTextSize(playerid, gSpectateData[playerid][16], 55.0, 10.0);
		PlayerTextDrawLetterSize(playerid, gSpectateData[playerid][16], 0.2, 1.0);
		PlayerTextDrawAlignment(playerid, gSpectateData[playerid][16], 3); //по правому краю
		PlayerTextDrawShow(playerid, gSpectateData[playerid][16]);
	}
	
	//язык
	if(update)
	{
		if(gSpectateData[playerid][17] != PlayerText:INVALID_TEXT_DRAW)
		    PlayerTextDrawDestroy(playerid, gSpectateData[playerid][17]);
		gSpectateData[playerid][17] = CreatePlayerTextDraw(playerid, SPECTATE_START_POSITION_X+190, SPECTATE_START_POSITION_Y+82, gPlayerLang[spec_player]);
		PlayerTextDrawFont(playerid, gSpectateData[playerid][17], 1);
		PlayerTextDrawUseBox(playerid, gSpectateData[playerid][17], 0);
		PlayerTextDrawBackgroundColor(playerid, gSpectateData[playerid][17], 0xAAFFAA55);
		PlayerTextDrawSetShadow(playerid, gSpectateData[playerid][17], 0);
		PlayerTextDrawColor(playerid, gSpectateData[playerid][17], 0xAAFFAA55);
		PlayerTextDrawTextSize(playerid, gSpectateData[playerid][17], 55.0, 10.0);
		PlayerTextDrawLetterSize(playerid, gSpectateData[playerid][17], 0.2, 1.0);
		PlayerTextDrawAlignment(playerid, gSpectateData[playerid][17], 3); //по правому краю
	}
	else
	{
		if(gSpectateData[playerid][17] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawHide(playerid, gSpectateData[playerid][17]);
		    PlayerTextDrawSetString(playerid, gSpectateData[playerid][17], gPlayerLang[spec_player]);
		}
	}
	if(gSpectateData[playerid][17] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawShow(playerid, gSpectateData[playerid][17]);

	//количество отключений чата
	if(update)
	{
		if(gSpectateData[playerid][18] != PlayerText:INVALID_TEXT_DRAW)
		    PlayerTextDrawDestroy(playerid, gSpectateData[playerid][18]);
		get_character_value(spec_player, "mute_count", "characters", name);
		gSpectateData[playerid][18] = CreatePlayerTextDraw(playerid, SPECTATE_START_POSITION_X+190, SPECTATE_START_POSITION_Y+92, name);
		PlayerTextDrawFont(playerid, gSpectateData[playerid][18], 1);
		PlayerTextDrawUseBox(playerid, gSpectateData[playerid][18], 0);
		PlayerTextDrawBackgroundColor(playerid, gSpectateData[playerid][18], 0xFF711955);
		PlayerTextDrawSetShadow(playerid, gSpectateData[playerid][18], 0);
		PlayerTextDrawColor(playerid, gSpectateData[playerid][18], 0xFFFFAA55);
		PlayerTextDrawTextSize(playerid, gSpectateData[playerid][18], 55.0, 10.0);
		PlayerTextDrawLetterSize(playerid, gSpectateData[playerid][18], 0.2, 1.0);
		PlayerTextDrawAlignment(playerid, gSpectateData[playerid][18], 3); //по правому краю
		PlayerTextDrawShow(playerid, gSpectateData[playerid][18]);
	}
	
	//количество киков
	if(update)
	{
		if(gSpectateData[playerid][19] != PlayerText:INVALID_TEXT_DRAW)
		    PlayerTextDrawDestroy(playerid, gSpectateData[playerid][19]);
		get_character_value(spec_player, "kick_count", "characters", name);
		gSpectateData[playerid][19] = CreatePlayerTextDraw(playerid, SPECTATE_START_POSITION_X+190, SPECTATE_START_POSITION_Y+100, name);
		PlayerTextDrawFont(playerid, gSpectateData[playerid][19], 1);
		PlayerTextDrawUseBox(playerid, gSpectateData[playerid][19], 0);
		PlayerTextDrawBackgroundColor(playerid, gSpectateData[playerid][19], 0xFF711955);
		PlayerTextDrawSetShadow(playerid, gSpectateData[playerid][19], 0);
		PlayerTextDrawColor(playerid, gSpectateData[playerid][19], 0xFFFFAA55);
		PlayerTextDrawTextSize(playerid, gSpectateData[playerid][19], 55.0, 10.0);
		PlayerTextDrawLetterSize(playerid, gSpectateData[playerid][19], 0.2, 1.0);
		PlayerTextDrawAlignment(playerid, gSpectateData[playerid][19], 3); //по правому краю
		PlayerTextDrawShow(playerid, gSpectateData[playerid][19]);
	}

	//количество банов
	if(update)
	{
		if(gSpectateData[playerid][20] != PlayerText:INVALID_TEXT_DRAW)
		    PlayerTextDrawDestroy(playerid, gSpectateData[playerid][20]);
		get_character_value(spec_player, "ban_count", "characters", name);
		gSpectateData[playerid][20] = CreatePlayerTextDraw(playerid, SPECTATE_START_POSITION_X+190, SPECTATE_START_POSITION_Y+108, name);
		PlayerTextDrawFont(playerid, gSpectateData[playerid][20], 1);
		PlayerTextDrawUseBox(playerid, gSpectateData[playerid][20], 0);
		PlayerTextDrawBackgroundColor(playerid, gSpectateData[playerid][20], 0xFFFFEE55);
		PlayerTextDrawSetShadow(playerid, gSpectateData[playerid][20], 0);
		PlayerTextDrawColor(playerid, gSpectateData[playerid][20], 0xFFFFEE55);
		PlayerTextDrawTextSize(playerid, gSpectateData[playerid][20], 55.0, 10.0);
		PlayerTextDrawLetterSize(playerid, gSpectateData[playerid][20], 0.2, 1.0);
		PlayerTextDrawAlignment(playerid, gSpectateData[playerid][20], 3); //по правому краю
		PlayerTextDrawShow(playerid, gSpectateData[playerid][20]);
	}
	
	//отключен ли чат, и если да, то на сколько
	if(update)
	{
		if(gSpectateData[playerid][21] != PlayerText:INVALID_TEXT_DRAW)
		    PlayerTextDrawDestroy(playerid, gSpectateData[playerid][21]);
		if(gMute[spec_player] > 0)
		{
			strdel(PrevValue[spec_player], 0, 64);
			get_players_value("mute", "players", gPlayersID[spec_player], name);
			format(PrevValue[spec_player], 64, "%s", name);
			PrevMute[spec_player] = gMute[spec_player];
		}
		else
			format(name, sizeof(name), "NO");
		gSpectateData[playerid][21] = CreatePlayerTextDraw(playerid, SPECTATE_START_POSITION_X+190, SPECTATE_START_POSITION_Y+118, name);
		PlayerTextDrawFont(playerid, gSpectateData[playerid][21], 1);
		PlayerTextDrawUseBox(playerid, gSpectateData[playerid][21], 0);
		PlayerTextDrawBackgroundColor(playerid, gSpectateData[playerid][21], 0x22557755);
		PlayerTextDrawSetShadow(playerid, gSpectateData[playerid][21], 0);
		PlayerTextDrawColor(playerid, gSpectateData[playerid][21], 0x22557755);
		PlayerTextDrawTextSize(playerid, gSpectateData[playerid][21], 55.0, 10.0);
		PlayerTextDrawLetterSize(playerid, gSpectateData[playerid][21], 0.2, 1.0);
		PlayerTextDrawAlignment(playerid, gSpectateData[playerid][21], 3); //по правому краю
	}
	else
	{
		if(gSpectateData[playerid][21] != PlayerText:INVALID_TEXT_DRAW)
		{
			if(gMute[spec_player] > 0)
			{
			    //кэшируем запрос к базе
			    if(gMute[spec_player] != PrevMute[spec_player])
				{
					strdel(PrevValue[spec_player], 0, 64);
					get_players_value("mute", "players", gPlayersID[spec_player], name);
					format(PrevValue[spec_player], 64, "%s", name);
					PrevMute[spec_player] = gMute[spec_player];
				}
				else
				{
				    format(name, sizeof(name), "%s", PrevValue[spec_player]);
				}
			}
			else
				format(name, sizeof(name), "NO");
			PlayerTextDrawHide(playerid, gSpectateData[playerid][21]);
		    PlayerTextDrawSetString(playerid, gSpectateData[playerid][21], name);
		}
	}
	if(gSpectateData[playerid][21] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawShow(playerid, gSpectateData[playerid][21]);
		
	//другие ники этого же игрока
	if(update)
	{
		if(gSpectateData[playerid][22] != PlayerText:INVALID_TEXT_DRAW)
		    PlayerTextDrawDestroy(playerid, gSpectateData[playerid][22]);
		strdel(list, 0, sizeof(list));
		get_the_same_players(spec_player, list, sizeof(list));
		gSpectateData[playerid][22] = CreatePlayerTextDraw(playerid, SPECTATE_START_POSITION_X+10, SPECTATE_START_POSITION_Y+136, list);
		PlayerTextDrawFont(playerid, gSpectateData[playerid][22], 1);
		PlayerTextDrawUseBox(playerid, gSpectateData[playerid][22], 0);
		PlayerTextDrawBackgroundColor(playerid, gSpectateData[playerid][22], 0x00FF2155);
		PlayerTextDrawSetShadow(playerid, gSpectateData[playerid][22], 0);
		PlayerTextDrawColor(playerid, gSpectateData[playerid][22], 0x00FF2155);
		PlayerTextDrawTextSize(playerid, gSpectateData[playerid][22], 50.0, 10.0);
		PlayerTextDrawLetterSize(playerid, gSpectateData[playerid][22], 0.2, 1.0);
		PlayerTextDrawAlignment(playerid, gSpectateData[playerid][22], 1); //по левому краю
		PlayerTextDrawShow(playerid, gSpectateData[playerid][22]);
	}
	
	//другие игроки с таким же ip
	if(update)
	{
		if(gSpectateData[playerid][23] != PlayerText:INVALID_TEXT_DRAW)
		    PlayerTextDrawDestroy(playerid, gSpectateData[playerid][23]);
		strdel(list, 0, sizeof(list));
		get_the_same_players_ip(spec_player, list, sizeof(list));
		gSpectateData[playerid][23] = CreatePlayerTextDraw(playerid, SPECTATE_START_POSITION_X+10, SPECTATE_START_POSITION_Y+178, list);
		PlayerTextDrawFont(playerid, gSpectateData[playerid][23], 1);
		PlayerTextDrawUseBox(playerid, gSpectateData[playerid][23], 0);
		PlayerTextDrawBackgroundColor(playerid, gSpectateData[playerid][23], 0xAAFF2155);
		PlayerTextDrawSetShadow(playerid, gSpectateData[playerid][23], 0);
		PlayerTextDrawColor(playerid, gSpectateData[playerid][23], 0xAAFF2155);
		PlayerTextDrawTextSize(playerid, gSpectateData[playerid][23], 50.0, 10.0);
		PlayerTextDrawLetterSize(playerid, gSpectateData[playerid][23], 0.2, 1.0);
		PlayerTextDrawAlignment(playerid, gSpectateData[playerid][23], 1); //по левому краю
		PlayerTextDrawShow(playerid, gSpectateData[playerid][23]);
	}
}

//скрыть данные одного игрока для другого
public hide_spectate_data(playerid)
{
	for(new i = 0; i < SPECTATE_FON_NUMBER; ++i)
	{
	    if(gSpectateFon[i] != Text:INVALID_TEXT_DRAW)
	    {
			TextDrawHideForPlayer(playerid, gSpectateFon[i]);
		}
	}

	for(new i = 0; i < SPECTATE_DATA_NUMBER; ++i)
	{
	    if(gSpectateData[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
	    {
			PlayerTextDrawDestroy(playerid, gSpectateData[playerid][i]);
			gSpectateData[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
	}
}

public destroy_spectate_data()
{
	for(new i = 0; i < SPECTATE_FON_NUMBER; ++i)
	{
	    if(gSpectateFon[i] != Text:INVALID_TEXT_DRAW)
	    {
			TextDrawDestroy(gSpectateFon[i]);
			gSpectateFon[i] = Text:INVALID_TEXT_DRAW;
		}
	}
	
	for(new i = 0; i < SPECTATE_DATA_NUMBER; ++i)
	{
		for(new j = 0; j < MAX_PLAYERS; ++j)
		{
		    if(gSpectateData[j][i] != PlayerText:INVALID_TEXT_DRAW)
		    {
				PlayerTextDrawDestroy(j, gSpectateData[j][i]);
				gSpectateData[j][i] = PlayerText:INVALID_TEXT_DRAW;
			}
		}
	}
}

public create_admin_panel()
{
    if(gAdminPanel[0] == Text:INVALID_TEXT_DRAW)
    {
		//большой фон панели управления админа
		gAdminPanel[0] = TextDrawCreate(PANEL_START_POSITION_X, PANEL_START_POSITION_Y, "Data");
	}

	TextDrawFont(gAdminPanel[0], TEXT_DRAW_FONT_MODEL_PREVIEW);
	TextDrawUseBox(gAdminPanel[0], 0);
	TextDrawSetPreviewRot(gAdminPanel[0], 90.0, 0.0, 0.0, -100.0);
	TextDrawSetShadow(gAdminPanel[0], 0);
	TextDrawColor(gAdminPanel[0], 0x88888855);
	TextDrawBackgroundColor(gAdminPanel[0], 0x88888855);
	TextDrawTextSize(gAdminPanel[0], 100.0, 189.0);

    if(gAdminPanel[1] == Text:INVALID_TEXT_DRAW)
    {
		//фон полоса (наименование)
		gAdminPanel[1] = TextDrawCreate(PANEL_START_POSITION_X, PANEL_START_POSITION_Y, "Data");
	}
	TextDrawFont(gAdminPanel[1], TEXT_DRAW_FONT_MODEL_PREVIEW);
	TextDrawUseBox(gAdminPanel[1], 0);
	TextDrawSetPreviewRot(gAdminPanel[1], 90.0, 0.0, 0.0, -100.0);
	TextDrawSetShadow(gAdminPanel[1], 0);
	TextDrawColor(gAdminPanel[1], 0x88888888);
	TextDrawBackgroundColor(gAdminPanel[1], 0x88888888);
	TextDrawTextSize(gAdminPanel[1], 100.0, 15.0);

    if(gAdminPanel[2] == Text:INVALID_TEXT_DRAW)
    {
		//наименование
		gAdminPanel[2] = TextDrawCreate(PANEL_START_POSITION_X+30, PANEL_START_POSITION_Y+2, "ADMIN_PANEL");
	}
	TextDrawFont(gAdminPanel[2], 1);
	TextDrawUseBox(gAdminPanel[2], 0);
	TextDrawSetShadow(gAdminPanel[2], 0);
	TextDrawColor(gAdminPanel[2], 0xCCCCCC88);
	TextDrawBackgroundColor(gAdminPanel[2], 0xCCCCCC88);
	TextDrawTextSize(gAdminPanel[2], 100.0, 15.0);
	TextDrawLetterSize(gAdminPanel[2], 0.2, 1.0);

    if(gAdminPanel[3] == Text:INVALID_TEXT_DRAW)
    {
		//кнопка mute
		gAdminPanel[3] = TextDrawCreate(PANEL_START_POSITION_X+3, PANEL_START_POSITION_Y+19, "Data");
	}
	TextDrawFont(gAdminPanel[3], TEXT_DRAW_FONT_MODEL_PREVIEW);
	TextDrawUseBox(gAdminPanel[3], 0);
	TextDrawSetPreviewRot(gAdminPanel[3], 90.0, 0.0, 0.0, -100.0);
	TextDrawSetShadow(gAdminPanel[3], 0);
	TextDrawColor(gAdminPanel[3], 0x88888888);
	TextDrawBackgroundColor(gAdminPanel[3], 0x88888888);
	TextDrawTextSize(gAdminPanel[3], 45.0, 30.0);
	TextDrawSetSelectable(gAdminPanel[3], 1);

    if(gAdminPanel[4] == Text:INVALID_TEXT_DRAW)
    {
		//надпись на кнопке mute
		gAdminPanel[4] = TextDrawCreate(PANEL_START_POSITION_X+9, PANEL_START_POSITION_Y+27, "mute");
	}
	TextDrawFont(gAdminPanel[4], 1);
	TextDrawUseBox(gAdminPanel[4], 0);
	TextDrawSetShadow(gAdminPanel[4], 0);
	TextDrawColor(gAdminPanel[4], 0xEECCCC88);
	TextDrawBackgroundColor(gAdminPanel[4], 0xEECCCC88);
	TextDrawTextSize(gAdminPanel[4], 30.0, 15.0);
	TextDrawLetterSize(gAdminPanel[4], 0.4, 1.2);
	
    if(gAdminPanel[5] == Text:INVALID_TEXT_DRAW)
    {
		//кнопка unmute
		gAdminPanel[5] = TextDrawCreate(PANEL_START_POSITION_X+52, PANEL_START_POSITION_Y+19, "Data");
	}
	TextDrawFont(gAdminPanel[5], TEXT_DRAW_FONT_MODEL_PREVIEW);
	TextDrawUseBox(gAdminPanel[5], 0);
	TextDrawSetPreviewRot(gAdminPanel[5], 90.0, 0.0, 0.0, -100.0);
	TextDrawSetShadow(gAdminPanel[5], 0);
	TextDrawColor(gAdminPanel[5], 0x88888888);
	TextDrawBackgroundColor(gAdminPanel[5], 0x88888888);
	TextDrawTextSize(gAdminPanel[5], 45.0, 30.0);
	TextDrawSetSelectable(gAdminPanel[5], 1);

    if(gAdminPanel[6] == Text:INVALID_TEXT_DRAW)
    {
		//надпись на кнопке unmute
		gAdminPanel[6] = TextDrawCreate(PANEL_START_POSITION_X+57, PANEL_START_POSITION_Y+27, "unmute");
	}
	TextDrawFont(gAdminPanel[6], 1);
	TextDrawUseBox(gAdminPanel[6], 0);
	TextDrawSetShadow(gAdminPanel[6], 0);
	TextDrawColor(gAdminPanel[6], 0xCCEECC88);
	TextDrawBackgroundColor(gAdminPanel[6], 0xCCEECC88);
	TextDrawTextSize(gAdminPanel[6], 30.0, 15.0);
	TextDrawLetterSize(gAdminPanel[6], 0.3, 1.2);
	
    if(gAdminPanel[7] == Text:INVALID_TEXT_DRAW)
    {
		//кнопка freeze
		gAdminPanel[7] = TextDrawCreate(PANEL_START_POSITION_X+3, PANEL_START_POSITION_Y+53, "Data");
	}
	TextDrawFont(gAdminPanel[7], TEXT_DRAW_FONT_MODEL_PREVIEW);
	TextDrawUseBox(gAdminPanel[7], 0);
	TextDrawSetPreviewRot(gAdminPanel[7], 90.0, 0.0, 0.0, -100.0);
	TextDrawSetShadow(gAdminPanel[7], 0);
	TextDrawColor(gAdminPanel[7], 0x88888888);
	TextDrawBackgroundColor(gAdminPanel[7], 0x88888888);
	TextDrawTextSize(gAdminPanel[7], 45.0, 30.0);
	TextDrawSetSelectable(gAdminPanel[7], 1);

    if(gAdminPanel[8] == Text:INVALID_TEXT_DRAW)
    {
		//надпись на кнопке freeze
		gAdminPanel[8] = TextDrawCreate(PANEL_START_POSITION_X+11, PANEL_START_POSITION_Y+61, "freeze");
	}
	TextDrawFont(gAdminPanel[8], 1);
	TextDrawUseBox(gAdminPanel[8], 0);
	TextDrawSetShadow(gAdminPanel[8], 0);
	TextDrawColor(gAdminPanel[8], 0xEECCCC88);
	TextDrawBackgroundColor(gAdminPanel[8], 0xEECCCC88);
	TextDrawTextSize(gAdminPanel[8], 30.0, 15.0);
	TextDrawLetterSize(gAdminPanel[8], 0.3, 1.2);

    if(gAdminPanel[9] == Text:INVALID_TEXT_DRAW)
    {
		//кнопка unfreeze
		gAdminPanel[9] = TextDrawCreate(PANEL_START_POSITION_X+52, PANEL_START_POSITION_Y+53, "Data");
	}
	TextDrawFont(gAdminPanel[9], TEXT_DRAW_FONT_MODEL_PREVIEW);
	TextDrawUseBox(gAdminPanel[9], 0);
	TextDrawSetPreviewRot(gAdminPanel[9], 90.0, 0.0, 0.0, -100.0);
	TextDrawSetShadow(gAdminPanel[9], 0);
	TextDrawColor(gAdminPanel[9], 0x88888888);
	TextDrawBackgroundColor(gAdminPanel[9], 0x88888888);
	TextDrawTextSize(gAdminPanel[9], 45.0, 30.0);
	TextDrawSetSelectable(gAdminPanel[9], 1);

    if(gAdminPanel[10] == Text:INVALID_TEXT_DRAW)
    {
		//надпись на кнопке unfreeze
		gAdminPanel[10] = TextDrawCreate(PANEL_START_POSITION_X+57, PANEL_START_POSITION_Y+61, "unfreeze");
	}
	TextDrawFont(gAdminPanel[10], 1);
	TextDrawUseBox(gAdminPanel[10], 0);
	TextDrawSetShadow(gAdminPanel[10], 0);
	TextDrawColor(gAdminPanel[10], 0xCCEECC88);
	TextDrawBackgroundColor(gAdminPanel[10], 0xCCEECC88);
	TextDrawTextSize(gAdminPanel[10], 30.0, 15.0);
	TextDrawLetterSize(gAdminPanel[10], 0.25, 1.2);



    if(gAdminPanel[11] == Text:INVALID_TEXT_DRAW)
    {
		//кнопка kill
		gAdminPanel[11] = TextDrawCreate(PANEL_START_POSITION_X+3, PANEL_START_POSITION_Y+87, "Data");
	}
	TextDrawFont(gAdminPanel[11], TEXT_DRAW_FONT_MODEL_PREVIEW);
	TextDrawUseBox(gAdminPanel[11], 0);
	TextDrawSetPreviewRot(gAdminPanel[11], 90.0, 0.0, 0.0, -100.0);
	TextDrawSetShadow(gAdminPanel[11], 0);
	TextDrawColor(gAdminPanel[11], 0x88888888);
	TextDrawBackgroundColor(gAdminPanel[11], 0x88888888);
	TextDrawTextSize(gAdminPanel[11], 45.0, 30.0);
	TextDrawSetSelectable(gAdminPanel[11], 1);

    if(gAdminPanel[12] == Text:INVALID_TEXT_DRAW)
    {
		//надпись на кнопке kill
		gAdminPanel[12] = TextDrawCreate(PANEL_START_POSITION_X+19, PANEL_START_POSITION_Y+96, "kill");
	}
	TextDrawFont(gAdminPanel[12], 1);
	TextDrawUseBox(gAdminPanel[12], 0);
	TextDrawSetShadow(gAdminPanel[12], 0);
	TextDrawColor(gAdminPanel[12], 0xEE333388);
	TextDrawBackgroundColor(gAdminPanel[12], 0xEE333388);
	TextDrawTextSize(gAdminPanel[12], 30.0, 15.0);
	TextDrawLetterSize(gAdminPanel[12], 0.3, 1.2);

    if(gAdminPanel[13] == Text:INVALID_TEXT_DRAW)
    {
		//кнопка kick
		gAdminPanel[13] = TextDrawCreate(PANEL_START_POSITION_X+52, PANEL_START_POSITION_Y+87, "Data");
	}
	TextDrawFont(gAdminPanel[13], TEXT_DRAW_FONT_MODEL_PREVIEW);
	TextDrawUseBox(gAdminPanel[13], 0);
	TextDrawSetPreviewRot(gAdminPanel[13], 90.0, 0.0, 0.0, -100.0);
	TextDrawSetShadow(gAdminPanel[13], 0);
	TextDrawColor(gAdminPanel[13], 0x88888888);
	TextDrawBackgroundColor(gAdminPanel[13], 0x88888888);
	TextDrawTextSize(gAdminPanel[13], 45.0, 30.0);
	TextDrawSetSelectable(gAdminPanel[13], 1);

    if(gAdminPanel[14] == Text:INVALID_TEXT_DRAW)
    {
		//надпись на кнопке kick
		gAdminPanel[14] = TextDrawCreate(PANEL_START_POSITION_X+61, PANEL_START_POSITION_Y+96, "kick");
	}
	TextDrawFont(gAdminPanel[14], 1);
	TextDrawUseBox(gAdminPanel[14], 0);
	TextDrawSetShadow(gAdminPanel[14], 0);
	TextDrawColor(gAdminPanel[14], 0xFF222288);
	TextDrawBackgroundColor(gAdminPanel[14], 0xFF222288);
	TextDrawTextSize(gAdminPanel[14], 30.0, 15.0);
	TextDrawLetterSize(gAdminPanel[14], 0.5, 1.2);

    if(gAdminPanel[15] == Text:INVALID_TEXT_DRAW)
    {
		//кнопка ban name
		gAdminPanel[15] = TextDrawCreate(PANEL_START_POSITION_X+3, PANEL_START_POSITION_Y+121, "Data");
	}
	TextDrawFont(gAdminPanel[15], TEXT_DRAW_FONT_MODEL_PREVIEW);
	TextDrawUseBox(gAdminPanel[15], 0);
	TextDrawSetPreviewRot(gAdminPanel[15], 90.0, 0.0, 0.0, -100.0);
	TextDrawSetShadow(gAdminPanel[15], 0);
	TextDrawColor(gAdminPanel[15], 0x88888888);
	TextDrawBackgroundColor(gAdminPanel[15], 0x88888888);
	TextDrawTextSize(gAdminPanel[15], 45.0, 30.0);
	TextDrawSetSelectable(gAdminPanel[15], 1);

    if(gAdminPanel[16] == Text:INVALID_TEXT_DRAW)
    {
		//надпись на кнопке ban name
		gAdminPanel[16] = TextDrawCreate(PANEL_START_POSITION_X+12, PANEL_START_POSITION_Y+130, "ban_name");
	}
	TextDrawFont(gAdminPanel[16], 1);
	TextDrawUseBox(gAdminPanel[16], 0);
	TextDrawSetShadow(gAdminPanel[16], 0);
	TextDrawColor(gAdminPanel[16], 0xFF222288);
	TextDrawBackgroundColor(gAdminPanel[16], 0xFF222288);
	TextDrawTextSize(gAdminPanel[16], 30.0, 15.0);
	TextDrawLetterSize(gAdminPanel[16], 0.2, 1.2);

    if(gAdminPanel[17] == Text:INVALID_TEXT_DRAW)
    {
		//кнопка ban
		gAdminPanel[17] = TextDrawCreate(PANEL_START_POSITION_X+52, PANEL_START_POSITION_Y+121, "Data");
	}
	TextDrawFont(gAdminPanel[17], TEXT_DRAW_FONT_MODEL_PREVIEW);
	TextDrawUseBox(gAdminPanel[17], 0);
	TextDrawSetPreviewRot(gAdminPanel[17], 90.0, 0.0, 0.0, -100.0);
	TextDrawSetShadow(gAdminPanel[17], 0);
	TextDrawColor(gAdminPanel[17], 0x88888888);
	TextDrawBackgroundColor(gAdminPanel[17], 0x88888888);
	TextDrawTextSize(gAdminPanel[17], 45.0, 30.0);
	TextDrawSetSelectable(gAdminPanel[17], 1);

    if(gAdminPanel[18] == Text:INVALID_TEXT_DRAW)
    {
		//надпись на кнопке ban
		gAdminPanel[18] = TextDrawCreate(PANEL_START_POSITION_X+61, PANEL_START_POSITION_Y+130, "ban");
	}
	TextDrawFont(gAdminPanel[18], 1);
	TextDrawUseBox(gAdminPanel[18], 0);
	TextDrawSetShadow(gAdminPanel[18], 0);
	TextDrawColor(gAdminPanel[18], 0xEE333388);
	TextDrawBackgroundColor(gAdminPanel[18], 0xEE333388);
	TextDrawTextSize(gAdminPanel[18], 30.0, 15.0);
	TextDrawLetterSize(gAdminPanel[18], 0.5, 1.2);


	
    if(gAdminPanel[19] == Text:INVALID_TEXT_DRAW)
    {
		//кнопка unban
		gAdminPanel[19] = TextDrawCreate(PANEL_START_POSITION_X+3, PANEL_START_POSITION_Y+155, "Data");
	}
	TextDrawFont(gAdminPanel[19], TEXT_DRAW_FONT_MODEL_PREVIEW);
	TextDrawUseBox(gAdminPanel[19], 0);
	TextDrawSetPreviewRot(gAdminPanel[19], 90.0, 0.0, 0.0, -100.0);
	TextDrawSetShadow(gAdminPanel[19], 0);
	TextDrawColor(gAdminPanel[19], 0x88888888);
	TextDrawBackgroundColor(gAdminPanel[19], 0x88888888);
	TextDrawTextSize(gAdminPanel[19], 94.0, 30.0);
	TextDrawSetSelectable(gAdminPanel[19], 1);

    if(gAdminPanel[20] == Text:INVALID_TEXT_DRAW)
    {
		//надпись на кнопке unban
		gAdminPanel[20] = TextDrawCreate(PANEL_START_POSITION_X+27, PANEL_START_POSITION_Y+164, "unban");
	}
	TextDrawFont(gAdminPanel[20], 1);
	TextDrawUseBox(gAdminPanel[20], 0);
	TextDrawSetShadow(gAdminPanel[20], 0);
	TextDrawColor(gAdminPanel[20], 0x22FF2288);
	TextDrawBackgroundColor(gAdminPanel[20], 0x22FF2288);
	TextDrawTextSize(gAdminPanel[20], 30.0, 15.0);
	TextDrawLetterSize(gAdminPanel[20], 0.5, 1.2);
}
//показать панель управления
public show_admin_panel(playerid)
{
	new i;

	for(i = 0; i < ADMIN_PANEL_NUMBER; ++i)
	{
	    if(gAdminPanel[i] != Text:INVALID_TEXT_DRAW)
		    TextDrawShowForPlayer(playerid, gAdminPanel[i]);
	}
	SelectTextDraw(playerid, 0xFFFF0055);
}
//скрыть панель управления
public hide_admin_panel(playerid)
{
	new i;
	
	for(i = 0; i < ADMIN_PANEL_NUMBER; ++i)
	{
	    if(gAdminPanel[i] != Text:INVALID_TEXT_DRAW)
		    TextDrawHideForPlayer(playerid, gAdminPanel[i]);
	}
//	CancelSelectTextDraw(playerid);
}
public destroy_admin_panel()
{
	new i;
	
	for(i = 0; i < ADMIN_PANEL_NUMBER; ++i)
	{
	    if(gAdminPanel[i] != Text:INVALID_TEXT_DRAW)
		    TextDrawDestroy(gAdminPanel[i]);
	}
}

public update_sensor_gun(playerid)
{
	new color;
	
	if(IsPlayerNPC(playerid))
	    return;
	
	if(gSensors[playerid][SENSOR_GUN_NUM] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawHide(playerid, gSensors[playerid][SENSOR_GUN_NUM]);

	if( (gGunMode[playerid] > 0) && ((GetTickCount() - gGunMode[playerid]) < 15000) )
		color = 0xFF000088;
	else
		color = 0x00FF0088;

	if(gSensors[playerid][SENSOR_GUN_NUM] != PlayerText:INVALID_TEXT_DRAW)
	    PlayerTextDrawColor(playerid, gSensors[playerid][SENSOR_GUN_NUM], color);//Цвет
	if(gSensors[playerid][SENSOR_GUN_NUM] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawShow(playerid, gSensors[playerid][SENSOR_GUN_NUM]);
}

public update_sensor_temp(playerid, temp)
{
	new buff, color;

	if(!IsPlayerNPC(playerid))
	if(gSensors[playerid][SENSOR_TEMP_NUM] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawHide(playerid, gSensors[playerid][SENSOR_TEMP_NUM]);

	if(temp < MIN_TEMP_VALUE || temp > MAX_TEMP_VALUE)
	{
	    gHealth[playerid] = 0;
	    update_sensor_health(playerid, gHealth[playerid]);
	    return;
	}
	
	if(IsPlayerNPC(playerid))
	    return;

    if(temp <= START_TEMP_VALUE)
    {
        buff = 255-((255*(START_TEMP_VALUE-temp))/(START_TEMP_VALUE-MIN_TEMP_VALUE));
		//0x0000FF88 Крайний цвет
        color = ((0xFF-buff) << 8) | (buff<<16) | 0x88;
    }
	else
	{
        buff = (255-(255*(temp-START_TEMP_VALUE))/(MAX_TEMP_VALUE-START_TEMP_VALUE));
		//0xFF000088 Крайний цвет
        color = ((0xFF-buff) << 24) | (buff<<16) | 0x88;
	}
	if(gSensors[playerid][SENSOR_TEMP_NUM] != PlayerText:INVALID_TEXT_DRAW)
	    PlayerTextDrawColor(playerid, gSensors[playerid][SENSOR_TEMP_NUM], color);//Цвет
	if(gSensors[playerid][SENSOR_TEMP_NUM] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawShow(playerid, gSensors[playerid][SENSOR_TEMP_NUM]);

	update_statistic_data(playerid, false); //обновляем данные игрока
}

public update_sensor_health(playerid, health)
{
	new buff, color;
	
	if(!IsPlayerNPC(playerid))
	if(gSensors[playerid][SENSOR_HEALTH_NUM] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawHide(playerid, gSensors[playerid][SENSOR_HEALTH_NUM]);

	if(health <= 0)
	{
	    kill_character(playerid);
	    return;
	}
	
	if(health > START_HEALTH_VALUE)
	    health = START_HEALTH_VALUE;

    if(health < START_HEALTH_VALUE)
    {
        buff = (255*health)/START_HEALTH_VALUE;
		//0xFF000088 Крайний цвет
        color = ((0xFF-buff) << 24) | (buff<<16) | 0x88;
		if(!IsPlayerNPC(playerid))
		if(gSensors[playerid][SENSOR_HEALTH_NUM] != PlayerText:INVALID_TEXT_DRAW)
		    PlayerTextDrawColor(playerid, gSensors[playerid][SENSOR_HEALTH_NUM], color);//Цвет
    }
	else
	{
		if(!IsPlayerNPC(playerid))
		if(gSensors[playerid][SENSOR_HEALTH_NUM] != PlayerText:INVALID_TEXT_DRAW)
		    PlayerTextDrawColor(playerid, gSensors[playerid][SENSOR_HEALTH_NUM], 0x00FF0088);//Цвет
	}

	if(!IsPlayerNPC(playerid))
	if(gSensors[playerid][SENSOR_HEALTH_NUM] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawShow(playerid, gSensors[playerid][SENSOR_HEALTH_NUM]);

//	SetPlayerHealth(playerid, floatmul(1000.0,(floatdiv(float(health), float(START_HEALTH_VALUE)))));
	buff = health*100/START_HEALTH_VALUE;
	if(IsPlayerNPC(playerid))
		FCNPC_SetHealth(playerid, buff>8?buff:8);
	else
		SetPlayerHealth(playerid, buff>8?buff:8);
	
	if(!IsPlayerNPC(playerid))
		update_statistic_data(playerid, false); //обновляем данные игрока
}

public update_sensor_hunger(playerid, hunger)
{
	new buff, color;

	if(!IsPlayerNPC(playerid))
	if(gSensors[playerid][SENSOR_HUNGER_NUM] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawHide(playerid, gSensors[playerid][SENSOR_HUNGER_NUM]);

	if(hunger <= 0)
	{
	    gHealth[playerid] = 0;
	    set_character_health(playerid, 0);
//	    kill_character(playerid);
	    return;
	}

	if(hunger > START_HUNGER_VALUE)
	    hunger = START_HUNGER_VALUE;
	    
    if(hunger < START_HUNGER_VALUE)
    {
        buff = (255*hunger)/START_HUNGER_VALUE;
        color = ((0xFF-buff) << 24) | (buff<<16) | 0x88;
       	if(!IsPlayerNPC(playerid))
		if(gSensors[playerid][SENSOR_HUNGER_NUM] != PlayerText:INVALID_TEXT_DRAW)
		    PlayerTextDrawColor(playerid, gSensors[playerid][SENSOR_HUNGER_NUM], color);//Цвет
    }
	else
	{
		if(!IsPlayerNPC(playerid))
		if(gSensors[playerid][SENSOR_HUNGER_NUM] != PlayerText:INVALID_TEXT_DRAW)
		    PlayerTextDrawColor(playerid, gSensors[playerid][SENSOR_HUNGER_NUM], 0x00FF0088);//Цвет
	}
	
	if(!IsPlayerNPC(playerid))
	if(gSensors[playerid][SENSOR_HUNGER_NUM] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawShow(playerid, gSensors[playerid][SENSOR_HUNGER_NUM]);
}

public update_sensor_thirst(playerid, thirst)
{
	new buff, color;

	if(!IsPlayerNPC(playerid))
	if(gSensors[playerid][SENSOR_THIRST_NUM] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawHide(playerid, gSensors[playerid][SENSOR_THIRST_NUM]);

	if(thirst <= 0)
	{
	    gHealth[playerid] = 0;
	    set_character_health(playerid, 0);
//	    kill_character(playerid);
	    return;
	}

	if(thirst > START_THIRST_VALUE)
	    thirst = START_THIRST_VALUE;
    if(thirst < START_THIRST_VALUE)
    {
        buff = (255*thirst)/START_THIRST_VALUE;
        color = ((0xFF-buff) << 24) | (buff<<16) | 0x88;
		if(!IsPlayerNPC(playerid))
		if(gSensors[playerid][SENSOR_THIRST_NUM] != PlayerText:INVALID_TEXT_DRAW)
		    PlayerTextDrawColor(playerid, gSensors[playerid][SENSOR_THIRST_NUM], color);//Цвет
    }
	else
	{
		if(!IsPlayerNPC(playerid))
		if(gSensors[playerid][SENSOR_THIRST_NUM] != PlayerText:INVALID_TEXT_DRAW)
		    PlayerTextDrawColor(playerid, gSensors[playerid][SENSOR_THIRST_NUM], 0x00FF0088);//Цвет
	}

	if(!IsPlayerNPC(playerid))
	if(gSensors[playerid][SENSOR_THIRST_NUM] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawShow(playerid, gSensors[playerid][SENSOR_THIRST_NUM]);
}

public update_sensor_wound(playerid, wound)
{
	new buff, color;

	if(!IsPlayerNPC(playerid))
	if(gSensors[playerid][SENSOR_WOUND_NUM] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawHide(playerid, gSensors[playerid][SENSOR_WOUND_NUM]);

	if(wound > MAX_WOUND_VALUE)
	    wound = MAX_WOUND_VALUE;
	    
    if(wound > 0)
    {
        buff = (255*wound)/MAX_WOUND_VALUE + 0xAA;
        if(buff >= 0xFF)
            buff = 0xFF;
        color = (buff<<24) | ((0xFF-buff) << 16) | 0x88;
		if(!IsPlayerNPC(playerid))
		if(gSensors[playerid][SENSOR_WOUND_NUM] != PlayerText:INVALID_TEXT_DRAW)
		    PlayerTextDrawColor(playerid, gSensors[playerid][SENSOR_WOUND_NUM], color);//Цвет
	}
	else
	{
		if(!IsPlayerNPC(playerid))
		if(gSensors[playerid][SENSOR_WOUND_NUM] != PlayerText:INVALID_TEXT_DRAW)
    	    PlayerTextDrawColor(playerid, gSensors[playerid][SENSOR_WOUND_NUM], 0x00FF0088);//Цвет
	}
	
	if(!IsPlayerNPC(playerid))
	if(gSensors[playerid][SENSOR_WOUND_NUM] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawShow(playerid, gSensors[playerid][SENSOR_WOUND_NUM]);
}

public update_sensor_time(playerid)
{
	new i, j, hour, minut, second;
	new buff[32];
	
	if(IsPlayerNPC(playerid))
		return;
	
    hour = strval(gYourTime[playerid]);
	for(i = 0; i < 16; ++i)
	{
	    if(gYourTime[playerid][i] == ':')
	    {
	        strmid(buff, gYourTime[playerid], i+1, 14-i);
		    minut = strval(buff);
		    break;
	    }
	}
	for(j = i+1; j < 16; ++j)
	{
	    if(gYourTime[playerid][j] == ':')
	    {
	        strmid(buff, gYourTime[playerid], j+1, 14-j);
		    second = strval(buff);
		    break;
	    }
	}
	second = second + SENSORS_TIMER_UPDATE/1000;
	if(second >= 60)
	{
	    minut = minut + second/60;
	    second = second%60;
		if(minut >= 60)
		{
		    hour = hour + minut/60;
		    minut = minut%60;
		}
	}
	strdel(gYourTime[playerid],0,15);
	format(gYourTime[playerid], 15, "%02d:%02d:%02d", hour, minut, second);
}

public update_sensor_messager_cheat(msg[])
{
	format(gMessagerString0, sizeof(gMessagerString0), "%s", msg);
//	SendClientMessageToAll(0xFF00FF00, gMessagerString0);
	
    if(gMessagerTD[0][0] != Text:INVALID_TEXT_DRAW)
    {
		TextDrawDestroy(gMessagerTD[0][0]);
		gMessagerTD[0][0] = Text:INVALID_TEXT_DRAW;
	}
    if(gMessagerTD[0][1] != Text:INVALID_TEXT_DRAW)
    {
		TextDrawDestroy(gMessagerTD[0][1]);
		gMessagerTD[0][1] = Text:INVALID_TEXT_DRAW;
	}
    if(gMessagerTD[0][2] != Text:INVALID_TEXT_DRAW)
    {
		TextDrawDestroy(gMessagerTD[0][2]);
		gMessagerTD[0][2] = Text:INVALID_TEXT_DRAW;
	}
	gMessagerTD[0][0] = TextDrawCreate(MESSAGE_START_POSITION_CH_X, MESSAGE_START_POSITION_CH_Y, "textdraw");
	TextDrawColor(gMessagerTD[0][0], 0x999999FF);
	TextDrawBackgroundColor(gMessagerTD[0][0], 0x000000FF); //0xFFFFFF88
	TextDrawFont(gMessagerTD[0][0], 1);
	TextDrawTextSize(gMessagerTD[0][0], 640, 20);
	TextDrawLetterSize(gMessagerTD[0][0], 0.28, 0.8);
	TextDrawSetShadow(gMessagerTD[0][0], 1);
	TextDrawSetString(gMessagerTD[0][0], gMessagerString0);
	TextDrawShowForAll(gMessagerTD[0][0]);
}

public update_sensor_messager_player(playerid, msg[], text[], color1, color2)
{
	new i, j;
	new name[64];
	
	GetPlayerName(playerid, name, sizeof(name));
	for(i = MESSAGER_STRINGS_COUNT-2; i >= 0; --i)
	{
		for(j = 0; j < 4; ++j)
		{
			gMessagerColors[i+1][j] = gMessagerColors[i][j];
			gMessagerSize[i+1][j] = gMessagerSize[i][j];
		}
	}
	gMessagerColors[1][0] = gPlayerColors[gPlayerColorID[playerid]];
	gMessagerColors[1][1] = 0xFFFFFFFF;
	gMessagerColors[1][2] = color1;
	gMessagerColors[1][3] = color2;

	format(gMessagerString8, sizeof(gMessagerString8), "%s", gMessagerString7);
	format(gMessagerString8_1, sizeof(gMessagerString8_1), "%s", gMessagerString7_1);
	format(gMessagerString8_2, sizeof(gMessagerString8_2), "%s", gMessagerString7_2);
	format(gMessagerString8_3, sizeof(gMessagerString8_3), "%s", gMessagerString7_3);

	format(gMessagerString7, sizeof(gMessagerString7), "%s", gMessagerString6);
	format(gMessagerString7_1, sizeof(gMessagerString7_1), "%s", gMessagerString6_1);
	format(gMessagerString7_2, sizeof(gMessagerString7_2), "%s", gMessagerString6_2);
	format(gMessagerString7_3, sizeof(gMessagerString7_3), "%s", gMessagerString6_3);

	format(gMessagerString6, sizeof(gMessagerString6), "%s", gMessagerString5);
	format(gMessagerString6_1, sizeof(gMessagerString6_1), "%s", gMessagerString5_1);
	format(gMessagerString6_2, sizeof(gMessagerString6_2), "%s", gMessagerString5_2);
	format(gMessagerString6_3, sizeof(gMessagerString6_3), "%s", gMessagerString5_3);

	format(gMessagerString5, sizeof(gMessagerString5), "%s", gMessagerString4);
	format(gMessagerString5_1, sizeof(gMessagerString5_1), "%s", gMessagerString4_1);
	format(gMessagerString5_2, sizeof(gMessagerString5_2), "%s", gMessagerString4_2);
	format(gMessagerString5_3, sizeof(gMessagerString5_3), "%s", gMessagerString4_3);

	format(gMessagerString4, sizeof(gMessagerString4), "%s", gMessagerString3);
	format(gMessagerString4_1, sizeof(gMessagerString4_1), "%s", gMessagerString3_1);
	format(gMessagerString4_2, sizeof(gMessagerString4_2), "%s", gMessagerString3_2);
	format(gMessagerString4_3, sizeof(gMessagerString4_3), "%s", gMessagerString3_3);

	format(gMessagerString3, sizeof(gMessagerString3), "%s", gMessagerString2);
	format(gMessagerString3_1, sizeof(gMessagerString3_1), "%s", gMessagerString2_1);
	format(gMessagerString3_2, sizeof(gMessagerString3_2), "%s", gMessagerString2_2);
	format(gMessagerString3_3, sizeof(gMessagerString3_3), "%s", gMessagerString2_3);

	format(gMessagerString2, sizeof(gMessagerString2), "%s", gMessagerString1);
	format(gMessagerString2_1, sizeof(gMessagerString2_1), "%s", gMessagerString1_1);
	format(gMessagerString2_2, sizeof(gMessagerString2_2), "%s", gMessagerString1_2);
	format(gMessagerString2_3, sizeof(gMessagerString2_3), "%s", gMessagerString1_3);

	format(gMessagerString1, sizeof(gMessagerString1), "%s", name);
	format(gMessagerString1_1, sizeof(gMessagerString1_1), "%s", gPlayerCountry[playerid]);
	format(gMessagerString1_2, sizeof(gMessagerString1_2), "%s", msg);
	format(gMessagerString1_3, sizeof(gMessagerString1_3), "%s", text);
	gMessagerSize[1][0] = 0;
	gMessagerSize[1][1] = get_textdraw_length(gMessagerString1)+2.0;
	gMessagerSize[1][2] = get_textdraw_length(gMessagerString1_1)+2.0+gMessagerSize[1][1];
	gMessagerSize[1][3] = get_textdraw_length(gMessagerString1_2)+2.0+gMessagerSize[1][2];

	for(i = 1; i < MESSAGER_STRINGS_COUNT; ++i)
	{
		for(j = 0; j < 4; ++j)
		{
		    if(gMessagerTD[i][j] != Text:INVALID_TEXT_DRAW)
		    {
				TextDrawDestroy(gMessagerTD[i][j]);
				gMessagerTD[i][j] = Text:INVALID_TEXT_DRAW;
			}
			gMessagerTD[i][j] = TextDrawCreate(MESSAGE_START_POSITION_PL_X+gMessagerSize[i][j], MESSAGE_START_POSITION_PL_Y-(i-1)*6, "textdraw");
			TextDrawColor(gMessagerTD[i][j], gMessagerColors[i][j]);
			TextDrawFont(gMessagerTD[i][j], 1);
			TextDrawTextSize(gMessagerTD[i][j], 300, 10);
			TextDrawLetterSize(gMessagerTD[i][j], 0.18, 0.7);
			TextDrawSetShadow(gMessagerTD[i][j], 0);
			TextDrawBoxColor(gMessagerTD[i][j], 0x00000011);
			TextDrawBackgroundColor(gMessagerTD[i][j], 0x00000055);
		}
	}

	TextDrawSetString(gMessagerTD[1][0], gMessagerString1);
	TextDrawSetString(gMessagerTD[1][1], gMessagerString1_1);
	TextDrawSetString(gMessagerTD[1][2], gMessagerString1_2);
	TextDrawSetString(gMessagerTD[1][3], gMessagerString1_3);

	TextDrawSetString(gMessagerTD[2][0], gMessagerString2);
	TextDrawSetString(gMessagerTD[2][1], gMessagerString2_1);
	TextDrawSetString(gMessagerTD[2][2], gMessagerString2_2);
	TextDrawSetString(gMessagerTD[2][3], gMessagerString2_3);

	TextDrawSetString(gMessagerTD[3][0], gMessagerString3);
	TextDrawSetString(gMessagerTD[3][1], gMessagerString3_1);
	TextDrawSetString(gMessagerTD[3][2], gMessagerString3_2);
	TextDrawSetString(gMessagerTD[3][3], gMessagerString3_3);

	TextDrawSetString(gMessagerTD[4][0], gMessagerString4);
	TextDrawSetString(gMessagerTD[4][1], gMessagerString4_1);
	TextDrawSetString(gMessagerTD[4][2], gMessagerString4_2);
	TextDrawSetString(gMessagerTD[4][3], gMessagerString4_3);

	TextDrawSetString(gMessagerTD[5][0], gMessagerString5);
	TextDrawSetString(gMessagerTD[5][1], gMessagerString5_1);
	TextDrawSetString(gMessagerTD[5][2], gMessagerString5_2);
	TextDrawSetString(gMessagerTD[5][3], gMessagerString5_3);

	TextDrawSetString(gMessagerTD[6][0], gMessagerString6);
	TextDrawSetString(gMessagerTD[6][1], gMessagerString6_1);
	TextDrawSetString(gMessagerTD[6][2], gMessagerString6_2);
	TextDrawSetString(gMessagerTD[6][3], gMessagerString6_3);

	TextDrawSetString(gMessagerTD[7][0], gMessagerString7);
	TextDrawSetString(gMessagerTD[7][1], gMessagerString7_1);
	TextDrawSetString(gMessagerTD[7][2], gMessagerString7_2);
	TextDrawSetString(gMessagerTD[7][3], gMessagerString7_3);

	TextDrawSetString(gMessagerTD[8][0], gMessagerString8);
	TextDrawSetString(gMessagerTD[8][1], gMessagerString8_1);
	TextDrawSetString(gMessagerTD[8][2], gMessagerString8_2);
	TextDrawSetString(gMessagerTD[8][3], gMessagerString8_3);

	for(i = 1; i < MESSAGER_STRINGS_COUNT; ++i)
	{
	    for(j = 0; j < 4; ++j)
	    {
			TextDrawShowForAll(gMessagerTD[i][j]);
		}
	}
}

public update_sensor_messager_player_l(msg[], color, Float:len)
{
	new i, l;

	for(i = 0; i < 2; ++i)
	{
	    if(gMessage[i] != Text:INVALID_TEXT_DRAW)
	    {
			TextDrawDestroy(gMessage[i]);
			gMessage[i] = Text:INVALID_TEXT_DRAW;
		}
		l = strlen(msg);
		gMessage[i] = TextDrawCreate(MESSAGE_START_POSITION_PL_X+l*len*i, MESSAGE_START_POSITION_PL_Y-100, "textdraw");
		TextDrawColor(gMessage[i], color);
		TextDrawBackgroundColor(gMessage[i], 0x000000FF); //0xFFFFFF88
		TextDrawFont(gMessage[i], 1);
		TextDrawTextSize(gMessage[i], 300, 10);
		TextDrawLetterSize(gMessage[i], 0.18, 0.7);
		TextDrawSetShadow(gMessage[i], 1);
		TextDrawSetString(gMessage[i], ((i==0)?msg:"string"));
		TextDrawShowForAll(gMessage[i]);
	}
}

public Float:get_textdraw_length(msg[])
{
	new i, len;
	new Float:length;
	
	len = strlen(msg);
	length = 0.0;
	
	for(i = 0; i < len; ++i)
	{
	    switch(msg[i])
	    {
	        case 'a': length = floatadd(length,3.25);
	        case 'b': length = floatadd(length,3.45);
	        case 'c': length = floatadd(length,2.9);
	        case 'd': length = floatadd(length,3.45);
	        case 'e': length = floatadd(length,3.27);
	        case 'f': length = floatadd(length,2.7);
	        case 'g': length = floatadd(length,3.45);
	        case 'h': length = floatadd(length,3.28);
	        case 'i': length = floatadd(length,1.63);
	        case 'j': length = floatadd(length,2.35);
	        case 'k': length = floatadd(length,3.25);
	        case 'l': length = floatadd(length,1.63);
	        case 'm': length = floatadd(length,4.9);
	        case 'n': length = floatadd(length,3.45);
	        case 'o': length = floatadd(length,3.45);
	        case 'p': length = floatadd(length,3.45);
	        case 'q': length = floatadd(length,3.45);
	        case 'r': length = floatadd(length,2.35);
	        case 's': length = floatadd(length,2.7);
	        case 't': length = floatadd(length,2.54);
	        case 'u': length = floatadd(length,3.45);
	        case 'v': length = floatadd(length,3.6);
	        case 'w': length = floatadd(length,4.87);
	        case 'x': length = floatadd(length,3.45);
	        case 'y': length = floatadd(length,3.45);
	        case 'z': length = floatadd(length,3.06);

	        case 'A': length = floatadd(length,4.0);
	        case 'B': length = floatadd(length,3.25);
	        case 'C': length = floatadd(length,3.63);
	        case 'D': length = floatadd(length,3.8);
	        case 'E': length = floatadd(length,2.9);
	        case 'F': length = floatadd(length,2.9);
	        case 'G': length = floatadd(length,4.0);
	        case 'H': length = floatadd(length,3.8);
	        case 'I': length = floatadd(length,1.63);
	        case 'J': length = floatadd(length,2.72);
	        case 'K': length = floatadd(length,3.63);
	        case 'L': length = floatadd(length,2.9);
	        case 'M': length = floatadd(length,4.72);
	        case 'N': length = floatadd(length,3.78);
	        case 'O': length = floatadd(length,4.2);
	        case 'P': length = floatadd(length,3.25);
	        case 'Q': length = floatadd(length,4.2);
	        case 'R': length = floatadd(length,3.42);
	        case 'S': length = floatadd(length,3.25);
	        case 'T': length = floatadd(length,3.63);
	        case 'U': length = floatadd(length,3.63);
	        case 'V': length = floatadd(length,4.0);
	        case 'W': length = floatadd(length,5.24);
	        case 'X': length = floatadd(length,3.8);
	        case 'Y': length = floatadd(length,3.8);
	        case 'Z': length = floatadd(length,3.63);

	        case '1': length = floatadd(length,2.54);
	        case '2': length = floatadd(length,3.42);
	        case '3': length = floatadd(length,3.42);
	        case '4': length = floatadd(length,3.42);
	        case '5': length = floatadd(length,3.42);
	        case '6': length = floatadd(length,3.42);
	        case '7': length = floatadd(length,3.42);
	        case '8': length = floatadd(length,3.42);
	        case '9': length = floatadd(length,3.42);
	        case '0': length = floatadd(length,3.42);

	        case ']': length = floatadd(length,2.0);
	        case '[': length = floatadd(length,2.0);
	        case '(': length = floatadd(length,2.0);
	        case ')': length = floatadd(length,2.0);
	        case ':': length = floatadd(length,1.63);
	        case ';': length = floatadd(length,2.2);
	        case '_': length = floatadd(length,1.75);
	        case '.': length = floatadd(length,1.85);
	        case ',': length = floatadd(length,1.9);
	        case '-': length = floatadd(length,2.4);
	        case '+': length = floatadd(length,3.63);
	        case '!': length = floatadd(length,1.63);
	        case '@': length = floatadd(length,1.9);
	        case '#': length = floatadd(length,3.3);
	        case '$': length = floatadd(length,3.3);
	        case '%': length = floatadd(length,3.3);
	        case '^': length = floatadd(length,2.0);
	        case '&': length = floatadd(length,4.15);
	        case '*': length = floatadd(length,4.65);
	        case '/': length = floatadd(length,2.52);
	        case '\\': length = floatadd(length,2.52);
	        case '~': length = floatadd(length,2.0);
	        case '<': length = floatadd(length,3.63);
	        case '>': length = floatadd(length,3.63);
	        case '{': length = floatadd(length,3.5);
	        case '}': length = floatadd(length,3.5);
	        case '?': length = floatadd(length,2.75);
	        case '|': length = floatadd(length,3.05);
	        case '=': length = floatadd(length,3.63);
	        case ' ': length = floatadd(length,1.85);
	        default:
	            length = floatadd(length,2.5);
	    }
	}
	
	return length;
}

public Float:get_dialog_length(msg[])
{
	new i, len;
	new Float:length;

	len = strlen(msg);
	length = 0.0;

	for(i = 0; i < len; ++i)
	{
	    switch(msg[i])
	    {
	        case 'a': length = floatadd(length,2.0);
	        case 'b': length = floatadd(length,2.24);
	        case 'c': length = floatadd(length,2.0);
	        case 'd': length = floatadd(length,2.24);
	        case 'e': length = floatadd(length,2.24);
	        case 'f': length = floatadd(length,1.24);
	        case 'g': length = floatadd(length,2.24);
	        case 'h': length = floatadd(length,2.24);
	        case 'i': length = floatadd(length,1.0);
	        case 'j': length = floatadd(length,1.0);
	        case 'k': length = floatadd(length,2.0);
	        case 'l': length = floatadd(length,1.0);
	        case 'm': length = floatadd(length,3.0);
	        case 'n': length = floatadd(length,2.24);
	        case 'o': length = floatadd(length,2.24);
	        case 'p': length = floatadd(length,2.24);
	        case 'q': length = floatadd(length,2.24);
	        case 'r': length = floatadd(length,1.5);
	        case 's': length = floatadd(length,2.0);
	        case 't': length = floatadd(length,1.24);
	        case 'u': length = floatadd(length,2.24);
	        case 'v': length = floatadd(length,2.24);
	        case 'w': length = floatadd(length,2.74);
	        case 'x': length = floatadd(length,2.0);
	        case 'y': length = floatadd(length,1.74);
	        case 'z': length = floatadd(length,2.0);

	        case 'A': length = floatadd(length,2.24);
	        case 'B': length = floatadd(length,2.74);
	        case 'C': length = floatadd(length,2.74);
	        case 'D': length = floatadd(length,2.74);
	        case 'E': length = floatadd(length,2.5);
	        case 'F': length = floatadd(length,2.24);
	        case 'G': length = floatadd(length,3.0);
	        case 'H': length = floatadd(length,2.74);
	        case 'I': length = floatadd(length,1.0);
	        case 'J': length = floatadd(length,2.0);
	        case 'K': length = floatadd(length,2.74);
	        case 'L': length = floatadd(length,2.24);
	        case 'M': length = floatadd(length,3.24);
	        case 'N': length = floatadd(length,2.74);
	        case 'O': length = floatadd(length,3.0);
	        case 'P': length = floatadd(length,2.5);
	        case 'Q': length = floatadd(length,3.0);
	        case 'R': length = floatadd(length,2.74);
	        case 'S': length = floatadd(length,2.5);
	        case 'T': length = floatadd(length,2.5);
	        case 'U': length = floatadd(length,2.74);
	        case 'V': length = floatadd(length,2.24);
	        case 'W': length = floatadd(length,3.24);
	        case 'X': length = floatadd(length,2.5);
	        case 'Y': length = floatadd(length,2.5);
	        case 'Z': length = floatadd(length,2.0);

	        case '1': length = floatadd(length,1.74);
	        case '2': length = floatadd(length,2.0);
	        case '3': length = floatadd(length,2.0);
	        case '4': length = floatadd(length,2.0);
	        case '5': length = floatadd(length,2.0);
	        case '6': length = floatadd(length,2.0);
	        case '7': length = floatadd(length,2.0);
	        case '8': length = floatadd(length,2.0);
	        case '9': length = floatadd(length,2.0);
	        case '0': length = floatadd(length,2.0);

	        case ']': length = floatadd(length,1.24);
	        case '[': length = floatadd(length,1.24);
	        case '(': length = floatadd(length,1.24);
	        case ')': length = floatadd(length,1.24);
	        case ':': length = floatadd(length,1.0);
	        case ';': length = floatadd(length,1.0);
	        case '_': length = floatadd(length,2.0);
	        case '.': length = floatadd(length,1.0);
	        case ',': length = floatadd(length,1.0);
	        case '-': length = floatadd(length,1.24);
	        case '+': length = floatadd(length,2.24);
	        case '!': length = floatadd(length,1.0);
	        case '@': length = floatadd(length,3.74);
	        case '#': length = floatadd(length,2.0);
	        case '$': length = floatadd(length,2.0);
	        case '%': length = floatadd(length,2.0);
	        case '^': length = floatadd(length,2.24);
	        case '&': length = floatadd(length,2.74);
	        case '*': length = floatadd(length,1.48);
	        case '/': length = floatadd(length,1.0);
	        case '\\': length = floatadd(length,1.0);
	        case '~': length = floatadd(length,2.24);
	        case '<': length = floatadd(length,2.24);
	        case '>': length = floatadd(length,2.24);
	        case '{': length = floatadd(length,1.5);
	        case '}': length = floatadd(length,1.5);
	        case '?': length = floatadd(length,2.24);
	        case '|': length = floatadd(length,1.0);
	        case '=': length = floatadd(length,2.24);
	        case ' ': length = floatadd(length,1.0);
	        default:
	            length = floatadd(length,2.5);
	    }
	}

	return length;
}

public create_smokescreen()
{
	gSmokescreen[0] = TextDrawCreate(25.0, 330.0, "hud:radar_north");
    TextDrawTextSize(gSmokescreen[0], 125.0, 104.0);//Размер
    TextDrawFont(gSmokescreen[0], 4);//Шрифт
   	TextDrawColor(gSmokescreen[0], 0x000000FF);//Цвет
   	
	gSmokescreen[1] = TextDrawCreate(495.0, 20.0, "hud:radar_saveGame");
    TextDrawTextSize(gSmokescreen[1], 115.0, 92.0);//Размер
    TextDrawFont(gSmokescreen[1], 4);//Шрифт
//   	TextDrawColor(gSmokescreen[1], 0x000000FF);//Цвет
   	TextDrawColor(gSmokescreen[1], 0x000000FF);//Цвет

	gHideMapZone = GangZoneCreate(-6000.0, -6000.0, 6000.0, 6000.0);
	GangZoneShowForAll(gHideMapZone, 0xFF0000FF);
}

public create_statistic_data(playerid)
{
	new nick[64];
	new players, i;

	if(IsPlayerNPC(playerid))
		return;

	for(i = 0, players = 0; i < MAX_PLAYERS; ++i)
	{
	    if(!IsPlayerNPC(i) && IsPlayerConnected(i))
	        players++;
	}

	GetPlayerName(playerid, nick, sizeof(nick));
	if(gStatisticData[playerid][0] != PlayerText:INVALID_TEXT_DRAW)
	{
	    PlayerTextDrawDestroy(playerid, gStatisticData[playerid][0]);
		gStatisticData[playerid][0] = PlayerText:INVALID_TEXT_DRAW;
	}
	gStatisticData[playerid][0] = CreatePlayerTextDraw(playerid, 510.0, 24.0, nick);
    PlayerTextDrawFont(playerid, gStatisticData[playerid][0], 1);//Шрифт
	PlayerTextDrawAlignment(playerid, gStatisticData[playerid][0], 1);
   	PlayerTextDrawColor(playerid, gStatisticData[playerid][0], 0xFFFF00FF);//Цвет
   	PlayerTextDrawTextSize(playerid, gStatisticData[playerid][0], 80, 15);//размер надписи
   	PlayerTextDrawLetterSize(playerid, gStatisticData[playerid][0], 0.2, 1.0);//размер букв
   	
	format(nick, sizeof(nick), "Players_online:");
	if(gStatisticData[playerid][11] != PlayerText:INVALID_TEXT_DRAW)
	{
	    PlayerTextDrawDestroy(playerid, gStatisticData[playerid][11]);
		gStatisticData[playerid][11] = PlayerText:INVALID_TEXT_DRAW;
	}
	gStatisticData[playerid][11] = CreatePlayerTextDraw(playerid, 506.0, 39.0, nick);
    PlayerTextDrawFont(playerid, gStatisticData[playerid][11], 1);//Шрифт
	PlayerTextDrawAlignment(playerid, gStatisticData[playerid][11], 1);
   	PlayerTextDrawColor(playerid, gStatisticData[playerid][11], 0xAA4433FF);//Цвет
   	PlayerTextDrawTextSize(playerid, gStatisticData[playerid][11], 100, 10);//размер
   	PlayerTextDrawLetterSize(playerid, gStatisticData[playerid][11], 0.3, 0.8);//размер букв

	format(nick, sizeof(nick), "%d", players);
	if(gStatisticData[playerid][12] != PlayerText:INVALID_TEXT_DRAW)
	{
	    PlayerTextDrawDestroy(playerid, gStatisticData[playerid][12]);
		gStatisticData[playerid][12] = PlayerText:INVALID_TEXT_DRAW;
	}
	gStatisticData[playerid][12] = CreatePlayerTextDraw(playerid, 600.0, 39.0, nick);
    PlayerTextDrawFont(playerid, gStatisticData[playerid][12], 1);//Шрифт
	PlayerTextDrawAlignment(playerid, gStatisticData[playerid][12], 3);
   	PlayerTextDrawColor(playerid, gStatisticData[playerid][12], 0x8888DDFF);//Цвет
   	PlayerTextDrawTextSize(playerid, gStatisticData[playerid][12], 20, 10);//размер
   	PlayerTextDrawLetterSize(playerid, gStatisticData[playerid][12], 0.3, 0.8);//размер букв

	format(nick, sizeof(nick), "Score:");
	if(gStatisticData[playerid][1] != PlayerText:INVALID_TEXT_DRAW)
	{
	    PlayerTextDrawDestroy(playerid, gStatisticData[playerid][1]);
		gStatisticData[playerid][1] = PlayerText:INVALID_TEXT_DRAW;
	}
	gStatisticData[playerid][1] = CreatePlayerTextDraw(playerid, 506.0, 47.0, nick);
    PlayerTextDrawFont(playerid, gStatisticData[playerid][1], 1);//Шрифт
	PlayerTextDrawAlignment(playerid, gStatisticData[playerid][1], 1);
   	PlayerTextDrawColor(playerid, gStatisticData[playerid][1], 0x44AA33FF);//Цвет
   	PlayerTextDrawTextSize(playerid, gStatisticData[playerid][1], 100, 10);//размер
   	PlayerTextDrawLetterSize(playerid, gStatisticData[playerid][1], 0.3, 0.8);//размер букв

	format(nick, sizeof(nick), "~b~%d", gScores[playerid]);
	if(gStatisticData[playerid][2] != PlayerText:INVALID_TEXT_DRAW)
	{
	    PlayerTextDrawDestroy(playerid, gStatisticData[playerid][2]);
		gStatisticData[playerid][2] = PlayerText:INVALID_TEXT_DRAW;
	}
	gStatisticData[playerid][2] = CreatePlayerTextDraw(playerid, 600.0, 47.0, nick);
    PlayerTextDrawFont(playerid, gStatisticData[playerid][2], 1);//Шрифт
	PlayerTextDrawAlignment(playerid, gStatisticData[playerid][2], 3);
   	PlayerTextDrawColor(playerid, gStatisticData[playerid][2], 0x00FF00FF);//Цвет
   	PlayerTextDrawTextSize(playerid, gStatisticData[playerid][2], 20, 10);//размер
   	PlayerTextDrawLetterSize(playerid, gStatisticData[playerid][2], 0.3, 0.8);//размер букв


	format(nick, sizeof(nick), "Temperature:");
	if(gStatisticData[playerid][3] != PlayerText:INVALID_TEXT_DRAW)
	{
	    PlayerTextDrawDestroy(playerid, gStatisticData[playerid][15]);
		gStatisticData[playerid][15] = PlayerText:INVALID_TEXT_DRAW;
	}
	gStatisticData[playerid][15] = CreatePlayerTextDraw(playerid, 506.0, 58.0, nick);
    PlayerTextDrawFont(playerid, gStatisticData[playerid][15], 1);//Шрифт
	PlayerTextDrawAlignment(playerid, gStatisticData[playerid][15], 1);
   	PlayerTextDrawColor(playerid, gStatisticData[playerid][15], 0x00FF00FF);//Цвет
   	PlayerTextDrawTextSize(playerid, gStatisticData[playerid][15], 100, 10);//размер
   	PlayerTextDrawLetterSize(playerid, gStatisticData[playerid][15], 0.2, 0.8);//размер букв

	format(nick, sizeof(nick), "~p~~h~~h~%d.%d", gTemperature[playerid]/100, (gTemperature[playerid]%100)/10);
	if(gStatisticData[playerid][16] != PlayerText:INVALID_TEXT_DRAW)
	{
	    PlayerTextDrawDestroy(playerid, gStatisticData[playerid][16]);
		gStatisticData[playerid][16] = PlayerText:INVALID_TEXT_DRAW;
	}
	gStatisticData[playerid][16] = CreatePlayerTextDraw(playerid, 600.0, 58.0, nick);
    PlayerTextDrawFont(playerid, gStatisticData[playerid][16], 1);//Шрифт
	PlayerTextDrawAlignment(playerid, gStatisticData[playerid][16], 3);
   	PlayerTextDrawColor(playerid, gStatisticData[playerid][16], 0x55FF55FF);//Цвет
   	PlayerTextDrawTextSize(playerid, gStatisticData[playerid][16], 20, 10);//размер
   	PlayerTextDrawLetterSize(playerid, gStatisticData[playerid][16], 0.3, 0.8);//размер букв


	format(nick, sizeof(nick), "Blood_(KPOBb):");
	if(gStatisticData[playerid][3] != PlayerText:INVALID_TEXT_DRAW)
	{
	    PlayerTextDrawDestroy(playerid, gStatisticData[playerid][3]);
		gStatisticData[playerid][3] = PlayerText:INVALID_TEXT_DRAW;
	}
	gStatisticData[playerid][3] = CreatePlayerTextDraw(playerid, 506.0, 65.0, nick);
    PlayerTextDrawFont(playerid, gStatisticData[playerid][3], 1);//Шрифт
	PlayerTextDrawAlignment(playerid, gStatisticData[playerid][3], 1);
   	PlayerTextDrawColor(playerid, gStatisticData[playerid][3], 0x00FF00FF);//Цвет
   	PlayerTextDrawTextSize(playerid, gStatisticData[playerid][3], 100, 10);//размер
   	PlayerTextDrawLetterSize(playerid, gStatisticData[playerid][3], 0.2, 0.8);//размер букв

	format(nick, sizeof(nick), "~r~%d", gHealth[playerid]);
	if(gStatisticData[playerid][4] != PlayerText:INVALID_TEXT_DRAW)
	{
	    PlayerTextDrawDestroy(playerid, gStatisticData[playerid][4]);
		gStatisticData[playerid][4] = PlayerText:INVALID_TEXT_DRAW;
	}
	gStatisticData[playerid][4] = CreatePlayerTextDraw(playerid, 600.0, 65.0, nick);
    PlayerTextDrawFont(playerid, gStatisticData[playerid][4], 1);//Шрифт
	PlayerTextDrawAlignment(playerid, gStatisticData[playerid][4], 3);
   	PlayerTextDrawColor(playerid, gStatisticData[playerid][4], 0x00FF00FF);//Цвет
   	PlayerTextDrawTextSize(playerid, gStatisticData[playerid][4], 20, 10);//размер
   	PlayerTextDrawLetterSize(playerid, gStatisticData[playerid][4], 0.3, 0.8);//размер букв

	format(nick, sizeof(nick), "Hunger_(ecTb):");
	if(gStatisticData[playerid][5] != PlayerText:INVALID_TEXT_DRAW)
	{
	    PlayerTextDrawDestroy(playerid, gStatisticData[playerid][5]);
		gStatisticData[playerid][5] = PlayerText:INVALID_TEXT_DRAW;
	}
	gStatisticData[playerid][5] = CreatePlayerTextDraw(playerid, 506.0, 72.0, nick);
    PlayerTextDrawFont(playerid, gStatisticData[playerid][5], 1);//Шрифт
	PlayerTextDrawAlignment(playerid, gStatisticData[playerid][5], 1);
   	PlayerTextDrawColor(playerid, gStatisticData[playerid][5], 0x00FF00FF);//Цвет
   	PlayerTextDrawTextSize(playerid, gStatisticData[playerid][5], 100, 10);//размер
   	PlayerTextDrawLetterSize(playerid, gStatisticData[playerid][5], 0.2, 0.8);//размер букв

	format(nick, sizeof(nick), "~p~%d", gHunger[playerid]);
	if(gStatisticData[playerid][6] != PlayerText:INVALID_TEXT_DRAW)
	{
	    PlayerTextDrawDestroy(playerid, gStatisticData[playerid][6]);
		gStatisticData[playerid][6] = PlayerText:INVALID_TEXT_DRAW;
	}
	gStatisticData[playerid][6] = CreatePlayerTextDraw(playerid, 600.0, 72.0, nick);
    PlayerTextDrawFont(playerid, gStatisticData[playerid][6], 1);//Шрифт
	PlayerTextDrawAlignment(playerid, gStatisticData[playerid][6], 3);
   	PlayerTextDrawColor(playerid, gStatisticData[playerid][6], 0x00FF00FF);//Цвет
   	PlayerTextDrawTextSize(playerid, gStatisticData[playerid][6], 20, 10);//размер
   	PlayerTextDrawLetterSize(playerid, gStatisticData[playerid][6], 0.3, 0.8);//размер букв

	format(nick, sizeof(nick), "Thirst_(nuTb):");
	if(gStatisticData[playerid][7] != PlayerText:INVALID_TEXT_DRAW)
	{
	    PlayerTextDrawDestroy(playerid, gStatisticData[playerid][7]);
		gStatisticData[playerid][7] = PlayerText:INVALID_TEXT_DRAW;
	}
	gStatisticData[playerid][7] = CreatePlayerTextDraw(playerid, 506.0, 79.0, nick);
    PlayerTextDrawFont(playerid, gStatisticData[playerid][7], 1);//Шрифт
	PlayerTextDrawAlignment(playerid, gStatisticData[playerid][7], 1);
   	PlayerTextDrawColor(playerid, gStatisticData[playerid][7], 0x00FF00FF);//Цвет
   	PlayerTextDrawTextSize(playerid, gStatisticData[playerid][7], 100, 10);//размер
   	PlayerTextDrawLetterSize(playerid, gStatisticData[playerid][7], 0.2, 0.8);//размер букв

	format(nick, sizeof(nick), "~y~%d", gThirst[playerid]);
	if(gStatisticData[playerid][8] != PlayerText:INVALID_TEXT_DRAW)
	{
	    PlayerTextDrawDestroy(playerid, gStatisticData[playerid][8]);
		gStatisticData[playerid][8] = PlayerText:INVALID_TEXT_DRAW;
	}
	gStatisticData[playerid][8] = CreatePlayerTextDraw(playerid, 600.0, 79.0, nick);
    PlayerTextDrawFont(playerid, gStatisticData[playerid][8], 1);//Шрифт
	PlayerTextDrawAlignment(playerid, gStatisticData[playerid][8], 3);
   	PlayerTextDrawColor(playerid, gStatisticData[playerid][8], 0x00FF00FF);//Цвет
   	PlayerTextDrawTextSize(playerid, gStatisticData[playerid][8], 20, 10);//размер
   	PlayerTextDrawLetterSize(playerid, gStatisticData[playerid][8], 0.3, 0.8);//размер букв

	format(nick, sizeof(nick), "Wound_(PAHA):");
	if(gStatisticData[playerid][9] != PlayerText:INVALID_TEXT_DRAW)
	{
	    PlayerTextDrawDestroy(playerid, gStatisticData[playerid][9]);
		gStatisticData[playerid][9] = PlayerText:INVALID_TEXT_DRAW;
	}
	gStatisticData[playerid][9] = CreatePlayerTextDraw(playerid, 506.0, 86.0, nick);
    PlayerTextDrawFont(playerid, gStatisticData[playerid][9], 1);//Шрифт
	PlayerTextDrawAlignment(playerid, gStatisticData[playerid][9], 1);
   	PlayerTextDrawColor(playerid, gStatisticData[playerid][9], 0x00FF00FF);//Цвет
   	PlayerTextDrawTextSize(playerid, gStatisticData[playerid][9], 100, 10);//размер
   	PlayerTextDrawLetterSize(playerid, gStatisticData[playerid][9], 0.2, 0.8);//размер букв

	if(gWound[playerid] == 0)
		format(nick, sizeof(nick), "~r~~h~%d", gWound[playerid]);
	else
		format(nick, sizeof(nick), "~r~~h~-%d", gWound[playerid]);
	if(gStatisticData[playerid][10] != PlayerText:INVALID_TEXT_DRAW)
	{
	    PlayerTextDrawDestroy(playerid, gStatisticData[playerid][10]);
		gStatisticData[playerid][10] = PlayerText:INVALID_TEXT_DRAW;
	}
	gStatisticData[playerid][10] = CreatePlayerTextDraw(playerid, 600.0, 86.0, nick);
    PlayerTextDrawFont(playerid, gStatisticData[playerid][10], 1);//Шрифт
	PlayerTextDrawAlignment(playerid, gStatisticData[playerid][10], 3);
   	PlayerTextDrawColor(playerid, gStatisticData[playerid][10], 0x77FF77FF);//Цвет
   	PlayerTextDrawTextSize(playerid, gStatisticData[playerid][10], 20, 10);//размер
   	PlayerTextDrawLetterSize(playerid, gStatisticData[playerid][10], 0.3, 0.8);//размер букв
   	
	format(nick, sizeof(nick), "Survival_time:");
	if(gStatisticData[playerid][13] != PlayerText:INVALID_TEXT_DRAW)
	{
	    PlayerTextDrawDestroy(playerid, gStatisticData[playerid][13]);
		gStatisticData[playerid][13] = PlayerText:INVALID_TEXT_DRAW;
	}
	gStatisticData[playerid][13] = CreatePlayerTextDraw(playerid, 506.0, 99.0, nick);
    PlayerTextDrawFont(playerid, gStatisticData[playerid][13], 1);//Шрифт
	PlayerTextDrawAlignment(playerid, gStatisticData[playerid][13], 1);
   	PlayerTextDrawColor(playerid, gStatisticData[playerid][13], 0x999999FF);//Цвет
   	PlayerTextDrawTextSize(playerid, gStatisticData[playerid][13], 100, 10);//размер
   	PlayerTextDrawLetterSize(playerid, gStatisticData[playerid][13], 0.2, 0.8);//размер букв

	format(nick, sizeof(nick), "~g~~h~%s", gYourTime[playerid]);
	if(gStatisticData[playerid][14] != PlayerText:INVALID_TEXT_DRAW)
	{
	    PlayerTextDrawDestroy(playerid, gStatisticData[playerid][14]);
		gStatisticData[playerid][14] = PlayerText:INVALID_TEXT_DRAW;
	}
	gStatisticData[playerid][14] = CreatePlayerTextDraw(playerid, 600.0, 99.0, nick);
    PlayerTextDrawFont(playerid, gStatisticData[playerid][14], 1);//Шрифт
	PlayerTextDrawAlignment(playerid, gStatisticData[playerid][14], 3);
   	PlayerTextDrawColor(playerid, gStatisticData[playerid][14], 0x77FF77FF);//Цвет
   	PlayerTextDrawTextSize(playerid, gStatisticData[playerid][14], 20, 10);//размер
   	PlayerTextDrawLetterSize(playerid, gStatisticData[playerid][14], 0.3, 0.8);//размер букв
}

public show_smokescreen(playerid)
{
	if(!IsPlayerNPC(playerid))
	if(gSmokescreen[0] != Text:INVALID_TEXT_DRAW)
		TextDrawShowForPlayer(playerid, gSmokescreen[0]);
}

public hide_smokescreen(playerid)
{
	if(!IsPlayerNPC(playerid))
	if(gSmokescreen[0] != Text:INVALID_TEXT_DRAW)
		TextDrawHideForPlayer(playerid, gSmokescreen[0]);
}

public show_smoke_map(playerid)
{
	if(!IsPlayerNPC(playerid))
   	GangZoneShowForPlayer(playerid, gHideMapZone, 0xFF0000FF);
}

public hide_smoke_map(playerid)
{
	if(!IsPlayerNPC(playerid))
   	GangZoneHideForPlayer(playerid, gHideMapZone);
}

public show_smoke_statistic(playerid)
{
	if(!IsPlayerNPC(playerid))
	if(gSmokescreen[1] != Text:INVALID_TEXT_DRAW)
		TextDrawShowForPlayer(playerid, gSmokescreen[1]);
}

public hide_smoke_statistic(playerid)
{
	if(!IsPlayerNPC(playerid))
	if(gSmokescreen[1] != Text:INVALID_TEXT_DRAW)
		TextDrawHideForPlayer(playerid, gSmokescreen[1]);
}

public show_statistic_data(playerid)
{
	if(!IsPlayerNPC(playerid))
	for(new i; i < TD_STATISTIC_DATA; ++i)
	{
	    if(gStatisticData[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
			PlayerTextDrawShow(playerid, gStatisticData[playerid][i]);
	}
}

public hide_statistic_data(playerid)
{
	if(!IsPlayerNPC(playerid))
	for(new i; i < TD_STATISTIC_DATA; ++i)
	{
	    if(gStatisticData[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
			PlayerTextDrawHide(playerid, gStatisticData[playerid][i]);
	}
}

public update_statistic_data(playerid, bool:update)
{
	new Buff[32];
	new players, i;
	
	if(IsPlayerNPC(playerid))
		return;
		
	for(i = 0, players = 0; i < MAX_PLAYERS; ++i)
	{
	    if(!IsPlayerNPC(i) && IsPlayerConnected(i))
	        players++;
	}

    if(gStatisticData[playerid][12] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawHide(playerid, gStatisticData[playerid][12]);
    if(gStatisticData[playerid][2] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawHide(playerid, gStatisticData[playerid][2]);
	if(gStatisticData[playerid][4] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawHide(playerid, gStatisticData[playerid][4]);
	if(gStatisticData[playerid][6] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawHide(playerid, gStatisticData[playerid][6]);
	if(gStatisticData[playerid][8] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawHide(playerid, gStatisticData[playerid][8]);
	if(gStatisticData[playerid][10] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawHide(playerid, gStatisticData[playerid][10]);
	if(gStatisticData[playerid][14] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawHide(playerid, gStatisticData[playerid][14]);
	if(gStatisticData[playerid][16] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawHide(playerid, gStatisticData[playerid][16]);

	format(Buff, sizeof(Buff), "%d", players);
    if(gStatisticData[playerid][12] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawSetString(playerid, gStatisticData[playerid][12], Buff);
	format(Buff, sizeof(Buff), "~p~~h~~h~%d.%d", gTemperature[playerid]/100, (gTemperature[playerid]%100)/10);
    if(gStatisticData[playerid][16] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawSetString(playerid, gStatisticData[playerid][16], Buff);
	format(Buff, sizeof(Buff), "~b~%d", gScores[playerid]);
    if(gStatisticData[playerid][2] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawSetString(playerid, gStatisticData[playerid][2], Buff);
	format(Buff, sizeof(Buff), "~r~%d", gHealth[playerid]);
    if(gStatisticData[playerid][4] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawSetString(playerid, gStatisticData[playerid][4], Buff);
	format(Buff, sizeof(Buff), "~p~%d", gHunger[playerid]);
    if(gStatisticData[playerid][6] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawSetString(playerid, gStatisticData[playerid][6], Buff);
	format(Buff, sizeof(Buff), "~y~%d", gThirst[playerid]);
    if(gStatisticData[playerid][8] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawSetString(playerid, gStatisticData[playerid][8], Buff);
	if(gWound[playerid] == 0)
		format(Buff, sizeof(Buff), "~r~~h~%d", gWound[playerid]);
	else
		format(Buff, sizeof(Buff), "~r~~h~-%d", gWound[playerid]);
    if(gStatisticData[playerid][10] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawSetString(playerid, gStatisticData[playerid][10], Buff);
	format(Buff, sizeof(Buff), "~g~~h~%s", gYourTime[playerid]);
    if(gStatisticData[playerid][14] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawSetString(playerid, gStatisticData[playerid][14], Buff);

    if(gStatisticData[playerid][12] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawShow(playerid, gStatisticData[playerid][12]);
    if(gStatisticData[playerid][2] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawShow(playerid, gStatisticData[playerid][2]);
    if(gStatisticData[playerid][4] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawShow(playerid, gStatisticData[playerid][4]);
    if(gStatisticData[playerid][6] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawShow(playerid, gStatisticData[playerid][6]);
    if(gStatisticData[playerid][8] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawShow(playerid, gStatisticData[playerid][8]);
    if(gStatisticData[playerid][10] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawShow(playerid, gStatisticData[playerid][10]);
    if(gStatisticData[playerid][14] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawShow(playerid, gStatisticData[playerid][14]);
    if(gStatisticData[playerid][14] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawShow(playerid, gStatisticData[playerid][16]);
		
	for(i = 0; i < MAX_PLAYERS; ++i)
	{
        if(gPsp[playerid][i] != 0)
        {
            show_spectate_data(i, playerid, update);
        }
        if(gPsp[i][playerid] != 0)
        {
            show_spectate_data(playerid, i, update);
        }
	}
}

public create_server_time()
{
	new hour, minut, second;

	//время сервера
	gettime(hour, minut, second);
	format(gServerTimeString, sizeof(gServerTimeString), "%02d:%02d", hour, minut);
	gServerTime = TextDrawCreate(SERVER_TIME_POSITION_X, SERVER_TIME_POSITION_Y, gServerTimeString);
	TextDrawColor(gServerTime, 0xFFFFFFAA);
	TextDrawBoxColor(gServerTime, 0xFFFFFFAA);
	TextDrawBackgroundColor(gServerTime, 0x777777AA); //0xFFFFFF88
	TextDrawFont(gServerTime, 1);
	TextDrawTextSize(gServerTime, 640, 20);
	TextDrawLetterSize(gServerTime, 0.4, 1);
	TextDrawSetShadow(gServerTime, 1);
//	TextDrawSetString(gServerTime, gServerTimeString);
	TextDrawShowForAll(gServerTime);

	//состояние переводчика чата
	format(gTranslatorStateString, sizeof(gTranslatorStateString), "Translator is %s", (gTranslate==1)?("on"):("off"));
	gTranslatorState = TextDrawCreate(SERVER_TIME_POSITION_X-65, SERVER_TIME_POSITION_Y-15, gTranslatorStateString);
	if(gTranslate == 1)
	{
		TextDrawColor(gTranslatorState, 0x00FF00AA);
		TextDrawBoxColor(gTranslatorState, 0x00FF00AA);
	}
	else
	{
		TextDrawColor(gTranslatorState, 0xFF0000AA);
		TextDrawBoxColor(gTranslatorState, 0xFF0000AA);
	}
	TextDrawBackgroundColor(gTranslatorState, 0x777777AA); //0xFFFFFF88
	TextDrawFont(gTranslatorState, 1);
	TextDrawTextSize(gTranslatorState, 640, 20);
	TextDrawLetterSize(gTranslatorState, 0.4, 1);
	TextDrawSetShadow(gTranslatorState, 1);
//	TextDrawSetString(gServerTime, gServerTimeString);
	TextDrawShowForAll(gTranslatorState);
}

public play_dolg_sound()
{
	new i;
	
	for(i = 0; i < MAX_PLAYERS; ++i)
	{
	    if(IsPlayerConnected(i) && !IsPlayerNPC(i))
	    {
			if(IsPlayerInRangeOfPoint(i, 200.0, 2286.0, 63.0, 29.0))
				PlayAudioStreamForPlayer(i, "http://botinform.com/vdolg.mp3", 2286.0, 63.0, 29.0, 200.0, 1);
		}
	}
}

public update_server_time()
{
	new hour, minut, second, ticks, count_down;
	new cd_time[32];
	static dotts;

	dotts = dotts^1;
	gettime(hour, minut, second);
	ticks = GetTickCount();
	if(dotts)
		format(gServerTimeString, sizeof(gServerTimeString), "%02d:%02d", hour, minut);
	else
		format(gServerTimeString, sizeof(gServerTimeString), "%02d %02d", hour, minut);

	TextDrawHideForAll(gServerTime);
	TextDrawSetString(gServerTime, gServerTimeString);
	TextDrawShowForAll(gServerTime);

	if(minut == 0)
		SetWorldTime(hour);

	format(gTranslatorStateString, sizeof(gTranslatorStateString), "Translator is %s", (gTranslate==1)?("on"):("off"));

	TextDrawHideForAll(gTranslatorState);
	if(gTranslate == 1)
	{
		TextDrawColor(gTranslatorState, 0x00FF00AA);
		TextDrawBoxColor(gTranslatorState, 0x00FF00AA);
	}
	else
	{
		TextDrawColor(gTranslatorState, 0xFF0000AA);
		TextDrawBoxColor(gTranslatorState, 0xFF0000AA);
	}
	TextDrawSetString(gTranslatorState, gTranslatorStateString);
	TextDrawShowForAll(gTranslatorState);

	for(new i = 0; i < MAX_PLAYERS; ++i)
	{
		if(gAntiRadar[i] >= 0 && IsPlayerSpawned(i) && !IsPlayerNPC(i))
		{
			if(gTdAntiCountDown[i] != PlayerText:INVALID_TEXT_DRAW)
			{
				count_down = gAntiRadar[i] - ticks;
				if(count_down < 0)
					count_down = 0;
				format(cd_time, sizeof(cd_time), "%02d%s%02d",(count_down/60000),(dotts > 0)?(":"):(" "),(count_down/1000)%60);
				PlayerTextDrawHide(i, gTdAntiCountDown[i]);
				PlayerTextDrawSetString(i, gTdAntiCountDown[i], cd_time);
				PlayerTextDrawShow(i, gTdAntiCountDown[i]);
			}
		}
	}
}

public destroy_server_time()
{
	TextDrawDestroy(gServerTime);
	TextDrawDestroy(gTranslatorState);
	for(new i = 0; i < MAX_PLAYERS; ++i)
	{
		//время до отключения антирадара
		PlayerTextDrawDestroy(i, gTdAntiCountDown[i]);
	}	
}

public destroy_smokescreen()
{
	if(gSmokescreen[0] != Text:INVALID_TEXT_DRAW)
	{
		TextDrawDestroy(gSmokescreen[0]);
		gSmokescreen[0] = Text:INVALID_TEXT_DRAW;
	}
	if(gSmokescreen[1] != Text:INVALID_TEXT_DRAW)
	{
		TextDrawDestroy(gSmokescreen[1]);
		gSmokescreen[1] = Text:INVALID_TEXT_DRAW;
	}
//	TextDrawDestroy(gSmokescreen[2]);
	GangZoneDestroy(gHideMapZone);
}

public destroy_statistic_data(playerid)
{
	if(IsPlayerNPC(playerid))
		return;
		
	for(new i = 0; i < TD_STATISTIC_DATA; ++i)
	{
	    if(gStatisticData[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
	    {
		    PlayerTextDrawDestroy(playerid, gStatisticData[playerid][i]);
		    gStatisticData[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
	}
}

stock IsPlayerSpawned(playerid)
{
    new player_state;

   	if(IsPlayerNPC(playerid))
		return FCNPC_IsSpawned(playerid);
		
	player_state = GetPlayerState(playerid);

    return (player_state != PLAYER_STATE_NONE && player_state != PLAYER_STATE_WASTED && player_state != PLAYER_STATE_SPECTATING);
}

//создать пелену
public create_spawn_shadow()
{
	gSpawnShadow[0] = TextDrawCreate(-1, 370, "textdraw");
	TextDrawFont(gSpawnShadow[0], TEXT_DRAW_FONT_MODEL_PREVIEW);
	TextDrawSetPreviewModel(gSpawnShadow[0], 0);
	TextDrawSetPreviewRot(gSpawnShadow[0], 90.0, 0.0, 0.0, -100.0);
	TextDrawColor(gSpawnShadow[0], 0x000000FF);
	TextDrawBackgroundColor(gSpawnShadow[0], 0x000000FF); //0xFFFFFF88
	TextDrawTextSize(gSpawnShadow[0], 645, 110);
	TextDrawUseBox(gSpawnShadow[0], 1);
	TextDrawSetShadow(gSpawnShadow[0], 0);

	gSpawnShadow[1] = TextDrawCreate(-1, -1, "textdraw");
	TextDrawFont(gSpawnShadow[1], TEXT_DRAW_FONT_MODEL_PREVIEW);
	TextDrawSetPreviewModel(gSpawnShadow[1], 0);
	TextDrawSetPreviewRot(gSpawnShadow[1], 90.0, 0.0, 0.0, -100.0);
	TextDrawColor(gSpawnShadow[1], 0x000000FF);
	TextDrawBackgroundColor(gSpawnShadow[1], 0x000000FF); //0xFFFFFF88
	TextDrawTextSize(gSpawnShadow[1], 645, 110);
	TextDrawUseBox(gSpawnShadow[1], 1);
	TextDrawSetShadow(gSpawnShadow[1], 0);
}
//закрыть кнопку "spawn"
public shadow_spawn(playerid)
{
	new i;
	
	if(IsPlayerNPC(playerid))
		return;
		
	for(i = 0; i < TD_SPAWN_SHADOWS; ++i)
	{
	    TextDrawShowForPlayer(playerid, gSpawnShadow[i]);
	}
}
//открыть кнопку "spawn"
public unshadow_spawn(playerid)
{
	new i;

	if(IsPlayerNPC(playerid))
		return;

	for(i = 0; i < TD_SPAWN_SHADOWS; ++i)
	{
	    TextDrawHideForPlayer(playerid, gSpawnShadow[i]);
	}
}
//удалить пелену
public destroy_spawn_shadow()
{
	new i;

	for(i = 0; i < TD_SPAWN_SHADOWS; ++i)
	{
		if(gSpawnShadow[i] != Text:INVALID_TEXT_DRAW)
		{
			TextDrawDestroy(gSpawnShadow[i]);
			gSpawnShadow[i] = Text:INVALID_TEXT_DRAW;
		}
	}
}

public IsPlayerInWater(playerid)
{
	new animid;

//	new str[64]; //отладка!!!
//	format(str, sizeof(str), "%d", GetPlayerAnimationIndex(playerid)); //отладка!!!
//	SendClientMessage(playerid, 0x55FFCAFF, str); //отладка!!!

    animid = GetPlayerAnimationIndex(playerid);

	if(animid == 1250 ||
	   animid == 1540 ||
	   animid == 1541 ||
	   animid == 1544 ||
	   animid == 1539 ||
	   animid == 1538)
	{
		new Float:pnX,Float:pnY,Float:pnZ;

		if(IsPlayerNPC(playerid))
			FCNPC_GetPosition(playerid,pnX,pnY,pnZ);
		else
			GetPlayerPos(playerid,pnX,pnY,pnZ);

		if(pnZ < 1.5)
			return 1;
			
		//вода перед платиной
		if(pnX < 0 && pnY > 2000)
		    return 1;

		if((IsPlayerInRangeOfPoint(playerid, 300.0, -1168.11,2151.00,40.0) ||
	        IsPlayerInRangeOfPoint(playerid, 300.0, -958.11,2401.0,40.0) ||
            IsPlayerInRangeOfPoint(playerid, 300.0, -1084.94,2649.50,40.04))&& pnZ < 45)
			return 1;

	    if((IsPlayerInRangeOfPoint(playerid, 100.0, 1962.16,1599.64,10.0) ||
	        IsPlayerInRangeOfPoint(playerid, 50.0, 2147.28,1131.29,10.0) ||
	        IsPlayerInRangeOfPoint(playerid, 30.0, 1237.01,-2378.30,10.0) ||
			IsPlayerInRangeOfPoint(playerid, 50.0, 2108.07,1907.37,10.0)) && pnZ < 10)
			return 1;

	    if(IsPlayerInRangeOfPoint(playerid, 50.0, 1962.66,-1190.69,17.45) && pnZ < 20)
			return 1;
	}
    return 0;
}

