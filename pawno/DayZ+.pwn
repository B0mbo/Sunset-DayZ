//Требуется плагин translator.so v1.1 by Bombo

//в OnPlayerSpawn обнулять глобальный кэш игрока

//"sr":"сербский","es":"испанский","ru":"русский","bg":"болгарский","it":"итальянский","uk":"украинский","cs":"чешский",
//"de":"немецкий","tr":"турецкий","pl":"польский","ro":"румынский","fr":"французский","en":"английский","az":"азербайджанский",
//"be":"белорусский","ca":"каталанский","da":"датский","el":"греческий","et":"эстонский","fi":"финский","hr":"хорватский",
//"hu":"венгерский","hy":"армянский","lt":"литовский","lv":"латышский","mk":"македонский","nl":"голландский","no":"норвежский",
//"pt":"португальский","sk":"словатский","sl":"словенский","sq":"албанский","sv":"шведский"
//"en-ru","ru-en","ru-uk","uk-ru","pl-ru","ru-pl","tr-ru","ru-tr","tr-en","en-tr","de-ru","ru-de","fr-ru","ru-fr","it-ru",
//"ru-it","es-ru","ru-es","de-en","en-de","fr-en","en-fr","es-en","en-es","it-en","en-it","cs-en","en-cs","cs-ru","ru-cs",
//"bg-ru","ru-bg","ro-ru","ru-ro","sr-ru","ru-sr","en-uk","uk-en","pl-uk","uk-pl","fr-uk","uk-fr","it-uk","uk-it","es-uk",
//"uk-es","de-uk","uk-de","tr-uk","uk-tr","cs-uk","uk-cs","bg-uk","uk-bg","ro-uk","uk-ro","sr-uk","uk-sr"

#include <crashdetect>
#include <a_samp>
#include <a_actor>
#include <things>
#include <SAMPle>
#include <FCNPC>
#include <mapandreas>
#include <streamer>

#include"defines.inc"
#include"global.inc"
//#include"actors.inc"
#include"sensors.inc"
#include"load_objects.inc"
#include "gl_common.inc"

//#define FILTERSCRIPT

#define XSIZE 0.165
#define YSIZE 2.85
#define USED_DRAWS 1634
enum textdraw
{
	Text:idt,
	used
}
new Text:Fon;
new TextDrawInfo[USED_DRAWS][textdraw];
new PlayerLogoIndex[MAX_PLAYERS];

forward OnPlayerConnectEx(playerid);
forward OnPlayerDisconnectEx(playerid, reason);
forward OnPlayerSpawnEx(playerid);
forward OnPlayerDeathEx(playerid, killerid, reason);
forward OnPlayerTakeDamageEx(playerid, issuerid, Float: amount, weaponid, bodypart);
forward OnPlayerTextEx(playerid, in_text[]);

forward LoadPlayerPosition(playerid);

forward afk_check();
forward alt_post_handle(playerid);
forward update_player_zone_mark();
forward destroy_bug_objects();
forward player_is_located(playerid);
forward create_map_objects();
forward update_live_cells();
forward create_views_of_items(playerid, vehicleid, cell, area);
forward create_inventory_menu(playerid);
forward create_objects_menu(playerid);
forward create_vehicle_menu(playerid, vehicleid);
forward create_bag_menu(playerid);
forward create_cells();
forward show_inventory(playerid, car_menu);
forward show_bag_menu(playerid);
forward show_cells(playerid, type, cells, show);
forward hide_menu(playerid);
forward hide_bag_menu(playerid);
forward destroy_bag_menu(playerid);
forward update_neighbors_objects_menu(playerid);
forward update_objects_menu(playerid);
forward update_vehicle_menu(playerid);
forward update_bag_menu(playerid);
forward destroy_menu(playerid);
forward destroy_cells();

forward stop_all_rotates(playerid);

forward check_vehicle_menu_show();

forward is_one_inventory_cell_selected(playerid, area);

forward replace_inventory(playerid, inv1, inv2);
forward take_object(playerid, inv, obj);
forward put_object(playerid, cell); //положить созданный объект в инвентарь
forward put_vehicle_object(playerid, vehicleid, cell); //положить созданный объект в инвентарь транспорта
forward put_bag_object(playerid, cell); //отобразить созданный объект в инвентаре рюкзака

forward take_from_vehicle(playerid, vehicleid, cell, veh_cell); //переложить из инвентаря транспорта в инвентарь персонажа
forward take_from_bag(playerid, cell, bag_cell); //переложить из инвентаря рюкзака в инвентарь персонажа
forward put_in_vehicle(playerid, vehicleid, cell, veh_cell); //переложить из инвентаря персонажа в инвентарь транспорта
forward put_in_veh_from_bag(playerid, vehicleid, cell, veh_cell); //переложить из рюкзака в инвентарь транспорта
forward put_in_bag(playerid, cell, bag_cell); //переложить из инвентаря персонажа в инвентарь рюкзака
forward put_in_bag_from_veh(playerid, vehicleid, cell, bag_cell); //переложить из инвентаря авто в рюкзак
forward put_in_bag_from_grnd(playerid, cell, bag_cell); //положить в рюкзак
forward replace_vehicle_inventory(playerid, vehicleid, inv1, inv2); //переложить объект
forward replace_bag_inventory(playerid, inv1, inv2); //переложить объект

forward remove_object(playerid, cell, bool:check); //просто удалить объект из инвентаря
forward remove_vehicle_object(playerid, vehicleid, cell); //просто удалить объект из инвентаря транспорта
forward remove_bag_object(playerid, cell); //просто удалить объект из рюкзака

forward drop_object(playerid, inv, obj); //выложить объект
forward drop_bag_object(playerid, inv, obj); //выложить объект из рюкзака

forward bool:is_player_on_gas_station(playerid);
forward bool:is_player_near_fire(playerid);
forward ChooseLanguage(playerid);
forward	player_login_menu(); //окно с запросом пароля
forward imes_simple_single(playerid, color, str[]);
forward IsPlayerInVehicleReal(playerid);
forward show_help_for_player(playerid);
forward update_unoccupied_vehicles();
forward update_weapon_ammo();
forward set_player_extra(playerid, extra[128]);

forward update_car_labels(); //обновление меток авто на карте
forward unmute_a_chat_for_player(PlayerID); //для таймера сообщения о разблокировки чата
forward hide_dayz_logo_from_player(playerid);

forward apply_some_cell(playerid, vehid, cell, area); //выполнить некоторое действие над только что созданным объектом
forward unapply_one_cell(playerid, cell, area); //отменить действие содержимого ячейки
forward auto_apply_one_cell(playerid, vehid, cell, area); //автоматически использовать содержимое ячейки
forward apply_one_cell(playerid, vehid, cell, area); //использовать содержимое ячейки

#if defined _FCNPC_included
new npc_id;
#endif

main()
{
	print("----------------------------------");
	print("SA:MP DayZ+ gamemode by Bombo");
	print("----------------------------------\n");
}

// Callbacks
public FCNPC_OnCreate(npcid)
{
	return 1;
}

public FCNPC_OnSpawn(npcid)
{
	return OnPlayerSpawnEx(npcid);
}
public FCNPC_OnRespawn(npcid)
{
	return 1;//OnPlayerSpawnEx(npcid);
}
public FCNPC_OnDeath(npcid, killerid, reason)
{
	return OnPlayerDeathEx(npcid, killerid, 1);
}

// Temporarily disabled until a further notice
/*forward FCNPC_OnVehicleEntryComplete(npcid, vehicleid, seat);
forward FCNPC_OnVehicleExitComplete(npcid);*/

//public FCNPC_OnReachDestination(npcid);
//public FCNPC_OnFinishPlayback(npcid);

//public FCNPC_OnTakeDamage(npcid, damagerid, weaponid, bodypart, Float:health_loss)
public FCNPC_OnTakeDamage(npcid, issuerid, Float:amount, weaponid, bodypart)
{
	return OnPlayerTakeDamageEx(npcid, issuerid, Float: amount, weaponid, bodypart);
	//return OnPlayerTakeDamageEx(npcid, damagerid, Float:health_loss, weaponid, bodypart);
}

//public FCNPC_OnFinishNodePoint(npcid, point);
//public FCNPC_OnChangeNode(playerid, nodeid);
//public FCNPC_OnFinishNode(npcid);

public OnGameModeInit()
{
	new i, j, k;
	new player_ip[32];
	new name[64+1];
	new ret;
	new hour, minut, second;

	print("----------------------------------");
	print("SA:MP DayZ+ gamemode by Bombo");
	print("----------------------------------\n");

	AddPlayerClass(188, -2347.0, -1600.0, 485.0, 111.1425, 0, 0, 0, 0, 0, 0);

	for(i = 0; i < MAX_PLAYERS; ++i)
	{
	    for(j = 0; j < SENSORS_NUMBER; ++j)
	    {
			gSensors[i][j] = PlayerText:INVALID_TEXT_DRAW;
		}
	}
	gSmokescreen[0] = Text:INVALID_TEXT_DRAW;
	gSmokescreen[1] = Text:INVALID_TEXT_DRAW;
	gSmokescreen[2] = Text:INVALID_TEXT_DRAW;

	//отключаем\настраиваем маркеры игроков на карте
	ShowPlayerMarkers(PLAYER_MARKERS_MODE_OFF);
	//ShowPlayerMarkers(PLAYER_MARKERS_MODE_GLOBAL);
	//ShowPlayerMarkers(PLAYER_MARKERS_MODE_STREAMED);

	//имена игроков и здоровье
	//ShowNameTags(0);
	//отключаем бонусы
	EnableStuntBonusForAll(false);
	//отключаем входы/выходы в интерьерах
	DisableInteriorEnterExits();
	//отключаем автозапуск двигателя и огни автомобилей
	ManualVehicleEngineAndLights();
	//разрешить "огонь по своим" машинам
	EnableVehicleFriendlyFire();
	//увеличиваем скорость бега
	UsePlayerPedAnims();

//	SendRconCommand("loadfs ship_bot");

#if defined SAMP_ICQ
	icqconnect();//start ICQ-chat-bot
#endif

	for(i = 0; i < MAX_PLAYERS; ++i)
	{
		for(j = 0; j < MAX_INVENTORY_ON_PLAYER; ++j)
		{
			zero_craft_item(gInventoryItem[i][j]);//инвентарь
		}

		for(j = 0; j < MAX_INVENTORY_ON_GROUND; ++j)
		{
			zero_craft_item(gGroundItem[i][j]);//на земле
		}

		for(j = 0; j < MAX_INVENTORY_IN_BAG; ++j)
		{
			zero_craft_item(gBagItem[i][j]);//в рюкзаке
		}
	}

	for(i = 0; i < MAX_PLAYERS; ++i)
	{
		for(j = 0; j < MAX_INVENTORY_ON_VEHICLE; ++j)
		{
			zero_craft_item(gVehicleItem[i][j]);//в машине
		}
	}

	Fon = TextDrawCreate(-1.0,-1.0,"textdraw");
	TextDrawFont(Fon,TEXT_DRAW_FONT_MODEL_PREVIEW);
	TextDrawSetPreviewModel(Fon, 0);
	TextDrawSetPreviewRot(Fon, 90.0, 0.0, 0.0, -100.0);
	TextDrawColor(Fon, 0x000000FF);
	TextDrawBackgroundColor(Fon, 0x000000FF);
	TextDrawTextSize(Fon, 642.0, 482.0);
	TextDrawUseBox(Fon, 0);
	TextDrawSetShadow(Fon, 0);

	gNPCCount = 0;

	//логотип
//#include"logo.inc"

	create_server_time();
	create_map_objects();

	for(i = 0; i < MAX_PLAYERS; ++i)
	{
	    if(IsPlayerNPC(i))
	        continue;
	    for(j = 0; j < SENSORS_NUMBER; ++j)
	    {
			gSensors[i][j] = PlayerText:INVALID_TEXT_DRAW;
		}
		gPrivateIn[i] = INVALID_PLAYER_ID;
		gPrivateOut[i] = INVALID_PLAYER_ID;
	}
	gSmokescreen[0] = Text:INVALID_TEXT_DRAW;
	gSmokescreen[1] = Text:INVALID_TEXT_DRAW;
	gSmokescreen[2] = Text:INVALID_TEXT_DRAW;

	gTimeridUpdateVehicles = -1;
	gTimeridUpdateSensors = -1;
	gTimeridSaveSensors = -1;
	gTimerZombieAttack = -1;
	gTimerNonCheaters = -1;
	gTimerDolgSound = -1;
	gTimerCarLabels = -1;
	gTimerid = -1;

	MapAndreas_Init(MAP_ANDREAS_MODE_FULL);
	init_ifile("imessage/imes.txt");
	default_language("en");
	gLangsNumber = 31;

	//включаем/отключаем автоматический переводчик
	gTranslate = 1;
	gChatTime = 1;

	//радиус чата
	gRadius = 20000.0;

	//максимальное расстояние до подбираемого объекта
	gStandartRangeValue = 3.0;

	//количество возможных нарушений перед киком
	gMaxAnticheat = 2;

	create_things("things.txt", HOST, USER, PASSWD, DBNAME);
	init_thread_sql(HOST, USER, PASSWD, DBNAME);
	open_database();
	load_objects();
	load_vehicles();
	load_gates("SOME_DOOR_TYPE");
	set_unusual_objects();
	initialize_players();
	create_smokescreen();

//0.3.7
/*
	for(i = 0; i < MAX_ACTORS; ++i)
	{
	    gActors[i] = INVALID_ACTOR_ID;
	}
*/
	for(i = 0; i < MAX_PLAYERS; ++i)
	{
		gUnoccupiedVehData[i] = INVALID_PLAYER_ID;
	}
	gUnoccupiedUpdateTimer = -1;

	for(i = 0; i < MAX_PLAYERS; ++i)
	{
		gAltWait[i] = 0;
		
		if(IsPlayerNPC(i))
			gIsPlayerLogin[i] = 1;
		else
			gIsPlayerLogin[i] = 0;

		gAntiRadar[i] = -1;

		gPlayersNearFire[i] = 0;
			
		gPlayerMarker[i] = INVALID_OBJECT_ID;

	    strdel(gYourTime[i],0,16);
    	gMute[i] = 0;
	    gUnmuteTimers[i] = -1;
		gWeaponUpdate[i] = 0;
		gIndexCharacterWeapon[i] = 0;
		gCheatersList[i] = INVALID_PLAYER_ID;
		gBag[i][0] = 0; //количество ячеек
		gBag[i][1] = 0; //id объекта рюкзака
		for(j = 0; j < MAX_PLAYERS; ++j)
		{
		    gPsp[i][j] = 0;
		}
	    gAFK[i] = 1;
	    gAFK_update[i] = 1;
		gPlayerCheaterLevel[i] = 0;
		gAdminLevel[i] = 0;
	}
	gUpdateWeaponTimer = -1;

	gMessage[0] = Text:INVALID_TEXT_DRAW;
	gMessage[1] = Text:INVALID_TEXT_DRAW;

	for(i = 0; i < MESSAGER_STRINGS_COUNT; ++i)
	{
	    for(j = 0; j < 4; ++j)
	    {
		    gMessagerTD[i][j] = Text:INVALID_TEXT_DRAW;
		}
	}

	for(i = 0; i < SPECTATE_FON_NUMBER; ++i)
	{
		gSpectateFon[i] = Text:INVALID_TEXT_DRAW;
	}
	for(i = 0; i < SPECTATE_DATA_NUMBER; ++i)
	{
	    for(j = 0; j < MAX_PLAYERS; ++j)
	    {
			gSpectateData[j][i] = PlayerText:INVALID_TEXT_DRAW;
		}
	}

	for(i = 0; i < ADMIN_PANEL_NUMBER; ++i)
	{
	    gAdminPanel[i] = Text:INVALID_TEXT_DRAW;
	}

	for(i = 0; i < MAX_INVENTORY_ON_PLAYER; ++i)
	{
		gTdInvCells[i] = Text:INVALID_TEXT_DRAW;
	}
	for(i = 0; i < MAX_INVENTORY_ON_VEHICLE; ++i)
	{
		gTdVehCells[i] = Text:INVALID_TEXT_DRAW;
	}
	for(i = 0; i < MAX_INVENTORY_IN_BAG; ++i)
	{
	    gTdBagCells[i] = Text:INVALID_TEXT_DRAW;
	}

	for(i = 0; i < TD_SPAWN_SHADOWS; ++i)
	{
		gSpawnShadow[i] = Text:INVALID_TEXT_DRAW;
	}

	//создать пелену
	create_spawn_shadow();

	for(i = 0; i < MAX_PLAYERS; ++i)
	{
		gSinhro[i] = 0;
		if(IsPlayerConnected(i))
		{
			GetPlayerName(i, name, sizeof(name));
			GetPlayerIp(i, player_ip, sizeof(player_ip));
			get_player_db_language(i); //обнуляет gPlayerLand и gPlayerLang если игрока ещё нет в базе
			add_nick_id_ip_land_lang(name, i, player_ip, gPlayerLand[i], gPlayerLang[i], gPlayerCountry[i], gPlayerCity[i]);
		    set_player_db_land(i, gPlayerLand[i]);
		    set_player_db_lang(i, gPlayerLang[i]);
		    if( (strlen(gPlayerCountry[i]) > 0) && (strcmp(gPlayerCountry[i], "Unknown") != 0) )
			    set_player_db_country(i, gPlayerCountry[i]);
		    if( (strlen(gPlayerCity[i]) > 0) && (strcmp(gPlayerCity[i], "Unknown") != 0) )
			    set_player_db_city(i, gPlayerCity[i]);

			if(strlen(gPlayerLand[i]) == 0)
			{
			    gPlayerLand[i][0] = 'e';
			    gPlayerLand[i][1] = 'n';
			    gPlayerLand[i][2] = '\0';
			}
			if(strlen(gPlayerLang[i]) == 0)
			{
			    gPlayerLang[i][0] = 'e';
			    gPlayerLang[i][1] = 'n';
			    gPlayerLang[i][2] = '\0';
			}

			gPlayerLangSecond[i][0] = '\0';
			gPlayerLangSecond[i][1] = '\0';
			gPlayerLangSecond[i][2] = '\0';

			gShowSecond[i] = 0;

			//задаём цвет игрока
			if(strlen(name) == 7 && strcmp(name, "DayZzZz", false, 7) == 0)
			{
				gPlayerColorID[i] = 100;
				SetPlayerColor(i, gPlayerColors[100]);
			}
			else
			{
				gPlayerColorID[i] = gColor;
				SetPlayerColor(i, gPlayerColors[gPlayerColorID[i]]);
				gColor = (gColor+1)%200;
			}

			//кэшируем содержимое рюкзака
			cache_player_inventory(i);

			for(j = 0; j < MAX_INVENTORY_ON_PLAYER; ++j)
			{
			    if(gInventoryItem[i][j][obj_auto] == 1)
			    {
					auto_apply_one_cell(i, -1, j, INVENTORY_AREA);
			    }
			}
			if(IsPlayerSpawned(i))
			    gPlayerLocated[i] = 1;
			else
				gPlayerLocated[i] = 0;
		}

		gVehicleDataShow[i] = 0;
        gPlayerPasswordRequest[i] = 0;
        gPlayerPasswordCheckCount[i] = 0;
        for(j = 0; j < TD_STATISTIC_DATA; ++j)
        {
            gStatisticData[i][j] = PlayerText:INVALID_TEXT_DRAW;
        }
		for(j = 0; j < TD_COUNT_VEHICLE; ++j)
		{
			gTdDataVehicle[i][j] = PlayerText:INVALID_TEXT_DRAW;
		}

		//добавить начальную инициализацию текстдравов меню!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//...
		for(j = 0; j < TD_COUNT; ++j)
		{
			gTdMenu[i][j] = PlayerText:INVALID_TEXT_DRAW;
		}

		for(j = 0; j < MAX_INVENTORY_ON_PLAYER; ++j)
		{
		    for(k = 0; k < MAX_TURNS_OF_PREVIEW; ++k)
		    {
		        gTdInventory[i][j][k] = PlayerText:INVALID_TEXT_DRAW;
		    }
		}

		for(j = 0; j < MAX_INVENTORY_ON_GROUND; ++j)
		{
		    for(k = 0; k < MAX_TURNS_OF_PREVIEW; ++k)
		    {
		        gTdObject[i][j][k] = PlayerText:INVALID_TEXT_DRAW;
		    }
		}

		for(j = 0; j < MAX_INVENTORY_ON_VEHICLE; ++j)
		{
		    for(k = 0; k < MAX_TURNS_OF_PREVIEW; ++k)
		    {
				gTdVehicle[i][j][k] = PlayerText:INVALID_TEXT_DRAW;
			}
		}

		for(j = 0; j < MAX_INVENTORY_IN_BAG; ++j)
	    for(k = 0; k < MAX_TURNS_OF_PREVIEW; ++k)
	    {
		   gTdBag[i][j][k] = PlayerText:INVALID_TEXT_DRAW;
		}
		
		gPlayerPlacesXYZ[i][0] = 0.0;
		gPlayerPlacesXYZ[i][1] = 0.0;
		gPlayerPlacesXYZ[i][2] = 0.0;
		gPlayerPlaces[i] = 1;
	}

	create_cells();

	for(i = 0; i < MAX_PLAYERS; ++i)
	{
	    if(IsPlayerConnected(i))
	    {
			show_smoke_map(i);
	        SetPlayerTeam(i, 0);
			ResetPlayerWeapons(i);
			gPlayerWeapon[i][0] = 0;
			gPlayerWeapon[i][1] = 0;
			gPlayerWeapon[i][2] = 0;
			gPlayerWeapon[i][3] = 0;
			if(IsPlayerSpawned(i))
			{
				show_smokescreen(i);
				show_smoke_statistic(i);
				create_inventory_menu(i);  //нужна проверка!
				create_sensors(i);
				create_statistic_data(i);
				show_statistic_data(i);
			}
			
			get_admin_level(i);
		}
	}

	for(i = 0; i < MAX_PLAYERS; ++i)
	{
	    if(IsPlayerConnected(i))
	    {
			ChooseLanguage(i);
		}
	}

	gTickCnt = GetTickCount();

	gTimeridAFK = SetTimer("afk_check", AFK_TIMER_UPDATE, true);
	gTimerid = SetTimer("update_live_cells", INVENTORY_TIMER_UPDATE, true);
	gTimeridUpdateSensors = SetTimer("update_live_sensors", SENSORS_TIMER_UPDATE, true);
	gTimeridSaveSensors = SetTimer("update_character_state", SENSORS_TIMER_SAVE, true);
	gTimeridUpdateVehicles = SetTimer("update_vehicle_state", SENSORS_TIMER_VEHICLES, true);
	gTimerNonCheaters = SetTimer("cheater_finder", NON_CHEATERS_INTERVAL, true);
	gTimerCarLabels = SetTimer("update_car_labels", UPDATE_CAR_LABELS_INTERVAL, true);
	gTimerServerTime = SetTimer("update_server_time", SERVER_TIME_INTERVAL, true);
	gTimerDolgSound = SetTimer("play_dolg_sound", DOLG_SOUND_INTERVAL, true);
	gTimerZombieAttack = SetTimer("update_zombie_attack", ZOMBIE_ATTACK_INTERVAL, true);
	gTimerDestroyBug = SetTimer("destroy_bug_objects", DESTROY_BUG_INTERVAL, true);
	gTimerPlayerZoneMark = SetTimer("update_player_zone_mark", ZONE_MARK_INTERVAL, true);
	gTimerMarkFire = SetTimer("mark_players_near_fire", NEAR_FIRE_TIMER, true);

//	SetWeather(3);
//	SetWorldTime(22);

	SetWeather(1);
	gettime(hour, minut, second);
	SetWorldTime(hour);

    //размораживаем персонаж
	for(i=0;i<MAX_PLAYERS;++i)
	{
	    if(IsPlayerConnected(i) && !IsPlayerNPC(i))
	    {
			load_player_position(i);
			TogglePlayerControllable(i, 1);
			ret = get_player_mute(i);
			if(ret > 0)
			{
			    if(gUnmuteTimers[i] != -1)
			    {
			        KillTimer(gUnmuteTimers[i]);
				    gUnmuteTimers[i] = -1;
			    }
				gUnmuteTimers[i] = SetTimerEx("unmute_a_chat_for_player", ret, false, "i", gPlayersID[i]);
			}
		}
	}

	create_key_labels("SOME_KEY_TYPE");
	create_spectate_data();
	create_admin_panel();

	//делаем прозрачными маркеры игроков
	for(i = 0; i < MAX_PLAYERS; ++i)
	{
	    if(IsPlayerConnected(i))
	    {
			for(j = 0; j < MAX_PLAYERS; ++j)
			{
			    if(j != i && IsPlayerConnected(j))
					SetPlayerMarkerForPlayer(j, i, (gPlayerColors[gPlayerColorID[i]]&0xFFFFFF00));
			}
		}
	}

	destroy_bug_objects();

	FCNPC_SetUpdateRate(80);
//	FCNPC_InitZMap("./scriptfiles/SAfull.hmap");
	init_npc_zombies();

	init_antimat("replace.txt");

	SendRconCommand("loadfs animations");
//	SendRconCommand("loadfs menu");
	SendRconCommand("loadfs small_base");
//	SendRconCommand("loadfs map_by_sprite4");
//	SendRconCommand("loadfs ls_beachside");
//	SendRconCommand("loadfs ls_apartments1");

	return 0;
}

public OnGameModeExit()
{
	new i,j,k;

#if defined SAMP_ICQ
	icqdisconnect();//stop ICQ-chat-bot
#endif
	SendRconCommand("unloadfs small_base");
//	SendRconCommand("unloadfs menu");
//	SendRconCommand("unloadfs map_by_sprite4");
	SendRconCommand("unloadfs animations");
//	SendRconCommand("unloadfs ls_beachside");
//	SendRconCommand("unloadfs ls_apartments1");

	for(i = 0;i<USED_DRAWS;i++)
	{
	    if(TextDrawInfo[i][used] == 1){TextDrawDestroy(TextDrawInfo[i][idt]);}
	}
	TextDrawDestroy(Fon);

	for(i=0;i<MAX_PLAYERS;++i)
	{
		//сбрасываем флаг "в бою"
		gGunMode[i] = 0;
		gAFK[i] = 0;
		gPlayersNearFire[i] = 0;
		//замораживаем персонажи
	    if(IsPlayerConnected(i))
			TogglePlayerControllable(i, 0);
	}

 	KillTimer(gTimerMarkFire);
 	KillTimer(gTimerPlayerZoneMark);
	KillTimer(gTimerDestroyBug);
	KillTimer(gTimerZombieAttack);
	KillTimer(gTimerDolgSound);
	KillTimer(gTimerNonCheaters);
	KillTimer(gTimeridUpdateVehicles);
	KillTimer(gTimeridSaveSensors);
	KillTimer(gTimeridUpdateSensors);
	KillTimer(gTimerid);
	KillTimer(gTimeridAFK);
	KillTimer(gTimerCarLabels);
	KillTimer(gTimerServerTime);

	gTimerNonCheaters = -1;
	gTimeridUpdateVehicles = -1;
	gTimeridSaveSensors = -1;
	gTimeridUpdateSensors = -1;
	gTimerid = -1;
	gTimeridAFK = -1;
	gTimerCarLabels = -1;
	gTimerServerTime = -1;
	gTimerPlayerZoneMark = -1;
	
	//удаляем все текстдравы инвентаря
	for(i = 0; i < MAX_PLAYERS; ++i)
	{
		for(j = 0; j < TD_COUNT_VEHICLE; ++j)
		{
			if(gTdDataVehicle[i][j] != PlayerText:INVALID_TEXT_DRAW)
			{
				PlayerTextDrawDestroy(i, gTdDataVehicle[i][j]);
				gTdDataVehicle[i][j] = PlayerText:INVALID_TEXT_DRAW;
			}
		}
		gPlayerCheaterLevel[i] = 0;

		if(!IsPlayerConnected(i))
		    continue;

		ResetPlayerWeapons(i);

		save_character_ammo(i, -1, -1);

		//прекращаем выбор
		CancelSelectTextDraw(i);

		for(j = 0; j < MAX_INVENTORY_ON_PLAYER; ++j)
		for(k = 0; k < MAX_TURNS_OF_PREVIEW; ++k)
		{
			if(gTdInventory[i][j][k] != PlayerText:INVALID_TEXT_DRAW)
			{
				PlayerTextDrawDestroy(i, gTdInventory[i][j][k]);
				gTdInventory[i][j][k] = PlayerText:INVALID_TEXT_DRAW;
			}
			if(IsPlayerInAnyVehicle(i))
			{
			    destroy_vehicle_sensors(i);
			}
		}

		for(j = 0; j < MAX_INVENTORY_ON_GROUND; ++j)
		for(k = 0; k < MAX_TURNS_OF_PREVIEW; ++k)
		{
			if(gObjectsMenuShow[i] > 0)
			{
			    if(gTdObject[i][j][k] != PlayerText:INVALID_TEXT_DRAW)
			    {
					PlayerTextDrawDestroy(i, gTdObject[i][j][k]); //ОСТОРОЖНО! Может удалить другие ТД
					gTdObject[i][j][k] = PlayerText:INVALID_TEXT_DRAW;
				}
			}
		}
		
		if(gVehicleMenuShow[i] > 0)
		{
			for(j = 0; j < MAX_INVENTORY_ON_VEHICLE; ++j)
			for(k = 0; k < MAX_TURNS_OF_PREVIEW; ++k)
			{
				    if(j < gVeh[gVehicleMenuShow[i]][1])
				    {
				        if(gTdVehicle[i][j][k] != PlayerText:INVALID_TEXT_DRAW)
				        {
							PlayerTextDrawDestroy(i, gTdVehicle[i][j][k]); //ОСТОРОЖНО! Может удалить другие ТД
							gTdVehicle[i][j][k] = PlayerText:INVALID_TEXT_DRAW;
						}
					}
			}
		}

		if(gBagMenuShow[i] > 0)
		{
			for(j = 0; j < gBag[i][0]; ++j)
			for(k = 0; k < MAX_TURNS_OF_PREVIEW; ++k)
			{
		        if(gTdBag[i][j][k] != PlayerText:INVALID_TEXT_DRAW)
		        {
					PlayerTextDrawDestroy(i, gTdBag[i][j][k]); //ОСТОРОЖНО! Может удалить другие ТД
					gTdBag[i][j][k] = PlayerText:INVALID_TEXT_DRAW;
				}
			}
		}

		for(k = 0; k < TD_COUNT; ++k)
		{
		    if(gTdMenu[i][k] != PlayerText:INVALID_TEXT_DRAW)
		    {
				PlayerTextDrawDestroy(i, gTdMenu[i][k]);
				gTdMenu[i][k] = PlayerText:INVALID_TEXT_DRAW;
			}
		}

		set_character_state(i, gTemperature[i], gHealth[i], gHunger[i], gThirst[i], gWound[i]);
		set_character_c_killer(i);
  	    destroy_sensors(i);
  	}

	destroy_smokescreen();

	for(new playerid = 0; playerid < MAX_PLAYERS; ++playerid)
	{
		if(gPlayerMarker[playerid] != INVALID_OBJECT_ID)
		{
		    DestroyDynamicObject(gPlayerMarker[playerid]);
		    if(!IsPlayerNPC(playerid))
		    {
				if(IsValidDynamic3DTextLabel(gMarkerText[playerid]))
			        DestroyDynamic3DTextLabel(gMarkerText[playerid]);
			}
		}
		destroy_statistic_data(playerid);
	}
	
	for(i = 0; i < MESSAGER_STRINGS_COUNT; ++i)
	{
	    for(j = 0; j < 4; ++j)
	    {
		    if(gMessagerTD[i][j] != Text:INVALID_TEXT_DRAW)
		    {
		        TextDrawDestroy(gMessagerTD[i][j]);
			    gMessagerTD[i][j] = Text:INVALID_TEXT_DRAW;
			}
		}
	}

	destroy_admin_panel();
	destroy_spectate_data();
	destroy_server_time();
	destroy_spawn_shadow();
	destroy_cells();
   	destroy_vehicles();
	destroy_gates("SOME_DOOR_TYPE");
	destroy_objects();
	free_players();
	close_ifile();
    new_translate();
    stop_translate();
    del_all_players();
	close_database();
	stop_thread_sql();
	MapAndreas_Exit();
	stop_antimat();
}

#if defined SAMP_ICQ
public OnICQMessage(from[], icqmes[])
{
	new i;
	new message[2048];
	new tmp[256];
	new name[64];
#if defined CHATTIME
    new hour, minut, sec;
#endif

#if defined CHATTIME
    gettime(hour, minut, sec);
#endif

	strdel(message, 0, sizeof(message));
	if(strcmp(icqmes, "/list") == 0)
	{
	  format(message, sizeof(message), "SAMP online:\n");
  	  for(i = 0; i < MAX_PLAYERS; ++i)
	  {
	    if(IsPlayerConnected(i))
	    {
          GetPlayerName(i, name, 48);
          format(tmp, sizeof(tmp), "%s (id:%d)\n", name, i);
          strcat(message, tmp);
		}
	  }
	  message[strlen(message)-1] = '\0';
      icqsendtoname(from, message);//send PM
	  return;
	}

	if(strlen(icqmes) > 0 && (icqmes[0] == '/' || icqmes[0] == '!'))
	    return;

	for(i = 0; i < MAX_PLAYERS; ++i)
	{
	  if(IsPlayerConnected(i))
	  {
#if defined CHATTIME
        format(message, sizeof(message), "[%02d:%02d:%02d] {00FFFF}icq{00FF00} %s: {FFFFFF}%s",
		       hour,
			   minut,
			   sec,
			   from,
			   icqmes);
#else
        format(message, sizeof(message), "%s: {FFFFFF}%s", from, icqmes);
#endif
	    SendClientMessage(i, 0xFF00FF, message);
	  }
	}
}
#endif

public OnQueryError(errorid, error[], callback[], query[], connectionHandle)
{
	printf("MySql Error: %s, callback:%s\nquery:%s",error,callback,query);
	switch(errorid)
	{
		case CR_SERVER_GONE_ERROR:
		{
			for(new i = 0; i < MAX_PLAYERS; ++i)
			{
				if(IsPlayerAdmin(i) || gAdminLevel[i] > 9)
					SendClientMessage(i, 0xFF0000FF, error);
			}
			printf("Lost connection to server, trying reconnect...");
			mysql_reconnect(connectionHandle);
		}
		case ER_SYNTAX_ERROR:
		{
			new msg[128];
			printf("MYSQL Error:\n%s in:\n%s", error,query);
			format(msg, sizeof(msg), "Error in query: %s",query);
			for(new i = 0; i < MAX_PLAYERS; ++i)
			{
				if(IsPlayerAdmin(i) || gAdminLevel[i] > 9)
					SendClientMessage(i, 0xFF0000FF, msg);
			}
		}
		default:
		{
			new msg[128];
			format(msg, sizeof(msg), "Error (def): %s in: %s", error,query);
			for(new i = 0; i < MAX_PLAYERS; ++i)
			{
				if(IsPlayerAdmin(i) || gAdminLevel[i] > 9)
					SendClientMessage(i, 0xFF0000FF, msg);
			}
			printf("MYSQL Error (def):\n%s in:\n%s", error,query);
		}
	}
	return 1;
}

public OnPlayerConnect(playerid)
{
#include"remove.inc"

	return OnPlayerConnectEx(playerid);
}

public OnPlayerConnectEx(playerid)
{
	new name[64];
	new player_ip[16];
	new i,j, ret;
	new is_not_npc = 1;
#if defined SAMP_ICQ
	new name[64];
	new str[256];
#endif

#if defined SAMP_ICQ
	GetPlayerName(playerid, name, 48);
    format(str, sizeof(str), "----->: %s", name);
	icqsendmessage(str);//send message to ICQ-chat-bot
#endif

	//маяк 3
//	SetPlayerCameraPos(playerid, 270.4600, -1968.1625, 47.8000);
//	SetPlayerCameraLookAt(playerid, 269.4735, -1968.3602, 47.6950);

	GetPlayerName(playerid, name, sizeof(name));
    GetPlayerIp(playerid, player_ip, sizeof(player_ip));
	SetPlayerScore(playerid, -1);
	//задаём цвет игрока
	if(strlen(name) == 7 && strcmp(name, "DayZzZz", false, 7) == 0)
	{
		gPlayerColorID[playerid] = 100;
		SetPlayerColor(playerid, gPlayerColors[100]);
	}
	else
	{
	    //задаём цвет игрока
		gPlayerColorID[playerid] = gColor;
	  	SetPlayerColor(playerid, gPlayerColors[gPlayerColorID[playerid]]);
		gColor = (gColor+1)%200;
	}

#if defined DEBUG
	new opcDebug0, opcDebug1, opcDebug2;
	opcDebug1 = opcDebug2 = opcDebug0 = GetTickCount();
#endif

	is_not_npc = !IsPlayerNPC(playerid);

	//индекс последнего скрытого ТД логотипа
	PlayerLogoIndex[playerid] = 0;

	if(is_not_npc)
	{
//		PlayAudioStreamForPlayer(playerid, "http://botinform.com/muse/intro.mp3", 2286.0, 63.0, 29.0, 200.0, 0);
		//убираем кнопку spawn
		TogglePlayerSpectating(playerid, 1);
		//уничтожаем объекты вблизи ворот
		//destroy_bug_objects();
		//для античита на ТП
		gPlayerLocated[playerid] = 0;
	}

	//сбрасываем флаг наблюдения
	for(i = 0; i < MAX_PLAYERS; ++i)
	{
	    gPsp[i][playerid] = 0;
		gPlayerDeathCount[i][0] = 0;
	}
	gIsPlayerLogin[playerid] = -1;

	gPrivateIn[playerid] = INVALID_PLAYER_ID;
	gPrivateOut[playerid] = INVALID_PLAYER_ID;

	gPlayersNearFire[playerid] = 0;
	
	gAntiRadar[playerid] = -1;

	//рамки
//	shadow_spawn(playerid);
	//скрываем данные наблюдаемых игроков
	if(is_not_npc)
		hide_spectate_data(playerid);
	//сбрасываем глушилку чата
	gMute[playerid] = 0;
	//сбрасываем счётчик читов
	gPlayerCheaterLevel[playerid] = 0;
	//режим боя
	gGunMode[playerid] = 0;
	//показывать оригинал сообщения
    gSinhro[playerid] = 0;
   	//показывать перевод на второй язык
    gShowSecond[playerid] = 0;
	//второй язык
    gPlayerLangSecond[playerid][0] = 0;
    gPlayerLangSecond[playerid][1] = 0;
    gPlayerLangSecond[playerid][2] = 0;

	//показываем, что игрок ещё не ввёл пароль
    gScores[playerid] = -1000;
    gWound[playerid] = 0;

//    PlayAudioStreamForPlayer(playerid, "http://botinform.com/music.pls");

#if defined DEBUG
	opcDebug1 = GetTickCount();
	printf("OnPlayerConnect, 1 label: %d", opcDebug1-opcDebug0);
#endif

	get_player_db_language(playerid);

#if defined DEBUG
	opcDebug2 = GetTickCount();
	printf("OnPlayerConnect, 2 label: %d, %d", opcDebug2-opcDebug0,opcDebug2-opcDebug1);
	opcDebug1 = opcDebug2;
#endif

	if(is_not_npc)
		add_nick_id_ip_land_lang(name, playerid, player_ip, gPlayerLand[playerid], gPlayerLang[playerid], gPlayerCountry[playerid], gPlayerCity[playerid]);
	if(gPlayerLand[playerid][0] == '\0')
	{
	    gPlayerLand[playerid][0] = 'e';
	    gPlayerLand[playerid][1] = 'n';
	    gPlayerLand[playerid][2] = '\0';
	}
	if(gPlayerLang[playerid][0] == '\0')
	{
	    gPlayerLang[playerid][0] = 'e';
	    gPlayerLang[playerid][1] = 'n';
	    gPlayerLang[playerid][2] = '\0';
	}

#if defined DEBUG
	opcDebug2 = GetTickCount();
	printf("OnPlayerConnect, 3 label: %d, %d", opcDebug2-opcDebug0,opcDebug2-opcDebug1);
	opcDebug1 = opcDebug2;
#endif

	//чтобы не было ложного срабатывания античита при загрузке
	//помещаем игрока на Чилиад
	gNonCheaters[playerid][0] = -2347.0;
	gNonCheaters[playerid][1] = -1600.0;
	gNonCheaters[playerid][2] = 484.0;

	//флаг отладки античита
	gAntiDebug = 0;
	//уровень администратора
	gAdminLevel[playerid] = 0;

	//блокируем чат, если игрока заткнули ранее
	ret = 0;
	if(is_not_npc)
		ret = get_player_mute(playerid);
	if(ret > 0)
	{
	    if(gUnmuteTimers[i] != -1)
	    {
	        KillTimer(gUnmuteTimers[i]);
		    gUnmuteTimers[i] = -1;
	    }
		gUnmuteTimers[i] = SetTimerEx("unmute_a_chat_for_player", ret, false, "i", gPlayersID[i]);
	}

	if(is_not_npc)
	{
		show_smoke_map(playerid);
	    gPlayerPasswordRequest[playerid] = 2;
	}
	else
		gPlayerPasswordRequest[playerid] = 0;
	//формируем список сообщений о прибывших
	if(is_not_npc)
		update_sensor_messager_player(playerid, "is connected", "", 0x0000FFCC, 0);

	//фон и ввод пароля
	if(is_not_npc)
		TextDrawShowForPlayer(playerid,Fon);

	if(is_not_npc)
	for(i = 0;i<USED_DRAWS;i++)
	{
	    if(TextDrawInfo[i][used] == 1)
		{
			TextDrawShowForPlayer(playerid,TextDrawInfo[i][idt]);
		}
	}

#if defined DEBUG
	opcDebug2 = GetTickCount();
	printf("OnPlayerConnect, 4 label: %d, %d", opcDebug2-opcDebug0,opcDebug2-opcDebug1);
	opcDebug1 = opcDebug2;
#endif

	if(is_not_npc)
	{
	    ChooseLanguage(playerid);
	    if(player_ip_check(playerid) > 0)
	    {
#if defined DEBUG
			opcDebug2 = GetTickCount();
			printf("OnPlayerConnect, 4_1 label: %d, %d", opcDebug2-opcDebug0,opcDebug2-opcDebug1);
			opcDebug1 = opcDebug2;
#endif
			TogglePlayerSpectating(playerid, 0);
	        gPlayerPasswordCheckCount[playerid] = 0;
		    gPlayerPasswordRequest[playerid] = 0; //чтобы больше не запрашивать пароль
		    SetPlayerTeam(playerid, 0);
			imes_simple_single(playerid, 0xFFFF00FF, "YOU_ARE_WELCOME");
	//			imes_simple_single(playerid, 0xFF3300, "HELLO_MESSAGE");
			SpawnPlayer(playerid);
			
#if defined DEBUG
			opcDebug2 = GetTickCount();
			printf("OnPlayerConnect, 4_2 label: %d, %d", opcDebug2-opcDebug0,opcDebug2-opcDebug1);
			opcDebug1 = opcDebug2;
#endif
			show_help_for_player(playerid);
		    set_player_db_land(playerid, gPlayerLand[playerid]);
		    set_player_db_lang(playerid, gPlayerLang[playerid]);
		    if(strlen(gPlayerCountry[playerid]) > 0)
			    set_player_db_country(playerid, gPlayerCountry[playerid]);
		    if(strlen(gPlayerCity[playerid]) > 0)
			    set_player_db_city(playerid, gPlayerCity[playerid]);
			gIsPlayerLogin[playerid] = 1;
	    }
	    else
			player_login_menu();
	}
	else
	{
		gPlayerPasswordCheckCount[playerid] = 0;
  		SetPlayerTeam(playerid, 0);
  		gIsPlayerLogin[playerid] = 1;
	}

#if defined DEBUG
	opcDebug2 = GetTickCount();
	printf("OnPlayerConnect, 5 label: %d, %d", opcDebug2-opcDebug0,opcDebug2-opcDebug1);
	opcDebug1 = opcDebug2;
#endif

    gAFK[playerid] = 0;
    gAFK_update[playerid] = 0;

 	if(is_not_npc)
 	{
		//звук при входе игрока
		for(i = 0; i < MAX_PLAYERS; ++i)
		{
//		    if(IsPlayerAdmin(i) || gAdminLevel[i] > 0)
//		    {
//			    PlayerPlaySound(i, 14410, 0, 0, 0);
//	    	}
			if(i != playerid && IsPlayerConnected(i))
			{
			    PlayerPlaySound(i, 14410, 0, 0, 0);
	  		}
		}

		//сообщение о последнем читере и о вошедших/вышедших
		for(i = 0; i < MESSAGER_STRINGS_COUNT; ++i)
		{
		    for(j = 0; j < 4; ++j)
		    {
				if(gMessagerTD[i][j] != Text:INVALID_TEXT_DRAW)
				    TextDrawShowForPlayer(playerid, gMessagerTD[i][j]);
			}
		}

		reset_player_key_labels(playerid);

//		imes_simple_single(playerid, 0xFFCC00, "HELPLANG");
//		imes_simple_single(playerid, 0xFFCC00, "HELP_HELP");
		if(gTranslate)
			imes_simple_single(playerid, 0xFFCC00, "TRANSLATOR_MESSAGE");

		if(strlen(gChatHistory[gHistoryIndex%CHAT_HISTORY_LEN]) > 0)
			imes_simple_single(playerid, 0x00FF00FF, "LAST_CHAT_MESSAGES");

	 	for(i = 0; i < CHAT_HISTORY_LEN; ++i)
	 	{
			if(strlen(gChatHistory[(gHistoryIndex+i+1)%CHAT_HISTORY_LEN]) > 0)
				SendClientMessage(playerid, 0x00FF00FF, gChatHistory[(gHistoryIndex+i+1)%CHAT_HISTORY_LEN]);
	 	}

		//делаем прозрачными маркеры игроков
		for(i = 0; i < MAX_PLAYERS; ++i)
		{
		    if(i != playerid)
		    {
				SetPlayerMarkerForPlayer(i, playerid, (gPlayerColors[gPlayerColorID[playerid]]&0xFFFFFF00));
				SetPlayerMarkerForPlayer(playerid, i, (gPlayerColors[gPlayerColorID[i]]&0xFFFFFF00));
			}
		}
	}
	
#if defined DEBUG
	opcDebug2 = GetTickCount();
	printf("OnPlayerConnect, 6 label: %d, %d", opcDebug2-opcDebug0,opcDebug2-opcDebug1);
	opcDebug1 = opcDebug2;
#endif

	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	return OnPlayerDisconnectEx(playerid, reason);
}

public OnPlayerDisconnectEx(playerid, reason)
{
	new name[64];
	new msg[128];
	new i, is_spectate;
	new Float:x, Float:y, Float:z, Float:Z_coord;
	new is_not_npc = 1;

#if defined DEBUG
	new opcDebug0, opcDebug1, opcDebug2;
	opcDebug1 = opcDebug2 = opcDebug0 = GetTickCount();
#endif

#if defined SAMP_ICQ
	new name[64];
	new str[256];
	GetPlayerName(playerid, name, 48);
    format(str, sizeof(str), "<-----: %s", name);
	icqsendmessage(str);//send message to ICQ-chat-bot
#endif

	is_not_npc = !IsPlayerNPC(playerid);

	gPlayerDeathCount[playerid][0] = 0;

	if(gPlayerMarker[playerid] != INVALID_OBJECT_ID)
	{
	    DestroyDynamicObject(gPlayerMarker[playerid]);
	    gPlayerMarker[playerid] = INVALID_OBJECT_ID;
	    if(!IsPlayerNPC(playerid))
			if(IsValidDynamic3DTextLabel(gMarkerText[playerid]))
		        DestroyDynamic3DTextLabel(gMarkerText[playerid]);
 	}
	
#if defined DEBUG
	opcDebug2 = GetTickCount();
	printf("OnPlayerDisconnect, 1 label: %d, %d", opcDebug2-opcDebug0,opcDebug2-opcDebug1);
	opcDebug1 = opcDebug2;
#endif
 	
 	//метка "игрок рядом с костром"
	gPlayersNearFire[playerid] = 0;

	//скрываем данные наблюдаемых игроков
	hide_spectate_data(playerid);
	
	//отключаем античит для игрока
	gPlayerLocated[playerid] = 0;

	//если игрок вышел во время боя - кикаем
	if(gGunMode[playerid] > 0 && gAdminLevel[playerid] < 2 && gIsPlayerLogin[playerid] > 0)
	{
		mark_player_as_cheater(playerid, gMaxAnticheat);
		//замораживаем
		TogglePlayerControllable(playerid, 0);
		//сбрасываем флажок "в бою"
	    gGunMode[playerid] = 0;
		//предупреждение
		PlayerPlaySound(playerid, 3200, 0, 0, 0);
	    //сообщение в низ экрана
	    GetPlayerName(playerid, name, sizeof(name));
	    format(msg, sizeof(msg), "%s(id:%d) HAS EXITED DURING THE FIGHT! (kick)", name, playerid);
	    update_sensor_messager_cheat(msg);
		//сохраняем координаты
    	save_player_bakup_position(playerid);
		//раскидываем вещи
		if(!IsPlayerAdmin(playerid))
		{
		    GetPlayerPos(playerid, x, y, z);
			for(i = 0; i < MAX_INVENTORY_ON_PLAYER; ++i)
			{
			    if(gInventoryItem[playerid][i][db_id] > 0)
			    {
					MapAndreas_FindZ_For2DCoord_I(x, y, Z_coord);
			        if(z > (Z_coord+3))
				        drop_character_inventory_cell(playerid, i, -1, x, y, Z_coord);
					else if(z < 0 && Z_coord == 0)
						drop_character_inventory_cell(playerid, i, -1, x, y, 0);
			        else
						drop_character_inventory_cell(playerid, i, -1, x, y, z);
				}
			}
		}
		update_neighbors_objects_menu(playerid);
	}

#if defined DEBUG
	opcDebug2 = GetTickCount();
	printf("OnPlayerDisconnect, 2 label: %d, %d", opcDebug2-opcDebug0,opcDebug2-opcDebug1);
	opcDebug1 = opcDebug2;
#endif
 	
	//обновляем время игрока в игре
	if(gIsPlayerLogin[playerid] > 0)
		player_logout(playerid);

    gAFK[playerid] = 1;
    gAFK_update[playerid] = 1;

	gPlayerCheaterLevel[playerid] = 0;

    gSinhro[playerid] = 0;
	//показывать перевод на второй язык
	gShowSecond[playerid] = 0;

	if(is_not_npc)
		destroy_menu(playerid);
		
	if(is_not_npc && IsPlayerSpawned(playerid)/*(?)*/ && gIsPlayerLogin[playerid] > 0)
		set_character_state(playerid, gTemperature[playerid], gHealth[playerid], gHunger[playerid], gThirst[playerid], gWound[playerid]);
	//без этой проверки зомби становятся "злопамятными" )
	if(IsPlayerSpawned(playerid))
		set_character_c_killer(playerid);
	if(is_not_npc)
	{
		reset_player_key_labels(playerid);
		destroy_sensors(playerid);
		destroy_statistic_data(playerid);
	}
 	if(gIsPlayerLogin[playerid] > 0)
		save_character_ammo(playerid, -1, -1);
	is_spectate = 1;
	for(i = 0; i < MAX_PLAYERS; ++i)
	{
		if(gPsp[i][playerid] == 1)
		{
		    is_spectate = 0;
		    break;
		}
    }
	if(is_spectate && IsPlayerSpawned(playerid)/*(?)*/ && gIsPlayerLogin[playerid] > 0)
        save_player_position(playerid);

#if defined DEBUG
	opcDebug2 = GetTickCount();
	printf("OnPlayerDisconnect, 3 label: %d, %d", opcDebug2-opcDebug0,opcDebug2-opcDebug1);
	opcDebug1 = opcDebug2;
#endif
 	
	gPlayersID[playerid] = 0;

	GetPlayerName(playerid, name, sizeof(name));
	del_nick(name);
	if(is_not_npc)
	switch(reason)
	{
	    case 0:
			update_sensor_messager_player(playerid, "is disconnected", "(crash)", 0xFF0000CC, 0xFF9999CC);
	    case 1:
			update_sensor_messager_player(playerid, "is disconnected", "", 0xFF0000CC, 0);
	    case 2:
			update_sensor_messager_player(playerid, "is disconnected", "(kick/ban)", 0xFF0000CC, 0xFF9999CC);
		default:
			update_sensor_messager_player(playerid, "is disconnected", "(unknown)", 0xFF0000CC, 0xFF9999CC);
	}


	for(i = 0; i < MAX_PLAYERS; ++i)
	{
	    if(gCheatersList[i] == playerid)
	        gCheatersList[i] = INVALID_PLAYER_ID;

		//звук при выходе игрока
//	    if(IsPlayerAdmin(i) || gAdminLevel[i] > 0)
//	    {
//	        PlayerPlaySound(i, 14409, 0, 0, 0);
//	    }
		if(i != playerid && IsPlayerConnected(i) && is_not_npc)
		{
		    PlayerPlaySound(i, 14409, 0, 0, 0);
  		}
	}

	gBag[playerid][0] = 0;
	gBag[playerid][1] = 0;

	gAdminLevel[playerid] = 0;

    //основной язык
	gPlayerLang[playerid][0] = '\0';
	gPlayerLang[playerid][1] = '\0';
	gPlayerLang[playerid][2] = '\0';
	//второй язык
	gPlayerLangSecond[playerid][0] = '\0';
	gPlayerLangSecond[playerid][1] = '\0';
	gPlayerLangSecond[playerid][2] = '\0';
	//страна
	gPlayerLand[playerid][0] = '\0';
	gPlayerLand[playerid][1] = '\0';
	gPlayerLand[playerid][2] = '\0';

	gIsPlayerLogin[playerid] = 0;

	strdel(gYourTime[playerid], 0, 16);
	format(gYourTime[playerid], 15, "00:00:00");

	if(is_not_npc)
		TextDrawHideForPlayer(playerid,Fon);
		
	if(is_not_npc)
	for(i = 0;i<USED_DRAWS;i++)
	{
	    if(TextDrawInfo[i][used] == 1){TextDrawHideForPlayer(playerid,TextDrawInfo[i][idt]);}
	}

#if defined DEBUG
	opcDebug2 = GetTickCount();
	printf("OnPlayerDisconnect, 4 label: %d, %d", opcDebug2-opcDebug0,opcDebug2-opcDebug1);
	opcDebug1 = opcDebug2;
#endif
 	
	//очищаем кэш предметов инвентаря игрока
	for(i = 0; i < MAX_INVENTORY_ON_PLAYER; ++i)
	{
		zero_craft_item(gInventoryItem[playerid][i]);//инвентарь
	}
	for(i = 0; i < MAX_INVENTORY_ON_GROUND; ++i)
	{
		zero_craft_item(gGroundItem[playerid][i]);//на земле
	}
	for(i = 0; i < MAX_INVENTORY_IN_BAG; ++i)
	{
		zero_craft_item(gBagItem[playerid][i]);//в рюкзаке
	}
	
#if defined DEBUG
	opcDebug2 = GetTickCount();
	printf("OnPlayerDisconnect, 5 (out) label: %d, %d", opcDebug2-opcDebug0,opcDebug2-opcDebug1);
	opcDebug1 = opcDebug2;
#endif
 
	return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
//	SetPlayerPos(playerid, -2347.0, -1600.0, 484.0);

	//маяк 3
//	SetPlayerCameraPos(playerid, 270.4600, -1968.1625, 47.8000);
//	SetPlayerCameraLookAt(playerid, 269.4735, -1968.3602, 47.6950);

	//маяк 2
	//	SetPlayerCameraPos(playerid, 234.8200, -1974.6400, 42.0400);
	//	SetPlayerCameraLookAt(playerid, 233.8300, -1974.8199, 41.8800);
	//маяк 1
	//	SetPlayerCameraPos(playerid, 174.0400, -1963.6600, 49.4800);
	//	SetPlayerCameraLookAt(playerid, 173.0600, -1963.4700, 49.3900);

	return 1;
}

public OnPlayerSpawn(playerid)
{
	return OnPlayerSpawnEx(playerid);
}

public OnPlayerSpawnEx(playerid)
{
	new is_not_npc = 1;

#if defined DEBUG
	new opsDebug0, opsDebug1, opsDebug2;
	opsDebug1 = opsDebug2 = opsDebug0 = GetTickCount();
	printf("OnPlayerSpawn, 1 label: %d, %d", opsDebug2-opsDebug0,opsDebug2-opsDebug1);
	opsDebug1 = opsDebug2;
#endif

	is_not_npc = !IsPlayerNPC(playerid);

	if(is_not_npc)
		TextDrawHideForPlayer(playerid,Fon);
//	hide_dayz_logo_from_player(playerid);

	if(is_not_npc)
	{
//	    unshadow_spawn(playerid);
		show_smoke_map(playerid);

		if(gPlayersID[playerid] == 0)
		{
			new name[64];
			new msg[256];

			//"замораживаем" игрока
			TogglePlayerControllable(playerid, 0);
			//сообщение в низ экрана
			GetPlayerName(playerid, name, sizeof(name));
			format(msg, sizeof(msg), "%s(id:%d) HAS SPAWNED WITHOUT LOGIN!", name, playerid);
			update_sensor_messager_cheat(msg);
			//гарантируем игроку кик
			//gPlayerCheaterLevel[playerid] = gMaxAnticheat;
		}
		show_smokescreen(playerid);
		show_smoke_statistic(playerid);

		destroy_menu(playerid);
		destroy_sensors(playerid);
		destroy_statistic_data(playerid);
	}
	
#if defined DEBUG
	opsDebug2 = GetTickCount();
	printf("OnPlayerSpawn, 2 label: %d, %d", opsDebug2-opsDebug0,opsDebug2-opsDebug1);
	opsDebug1 = opsDebug2;
#endif

	create_sensors(playerid);
	create_statistic_data(playerid);
	
	if(is_not_npc)
	{
		show_statistic_data(playerid);
	}
	
#if defined DEBUG
	opsDebug2 = GetTickCount();
	printf("OnPlayerSpawn, 3 label: %d, %d", opsDebug2-opsDebug0,opsDebug2-opsDebug1);
	opsDebug1 = opsDebug2;
#endif

	load_player_position(playerid);
	//а вот здесь можно было бы проверить прикреплённые к персонажу
	//объекты на наличие оных в инвентаре
	//...

#if defined DEBUG
	opsDebug2 = GetTickCount();
	printf("OnPlayerSpawn, 4 label: %d, %d", opsDebug2-opsDebug0,opsDebug2-opsDebug1);
	opsDebug1 = opsDebug2;
#endif

	if(is_not_npc)
	{
		create_inventory_menu(playerid);	//нужна проверка!
	}
	
#if defined DEBUG
	opsDebug2 = GetTickCount();
	printf("OnPlayerSpawn, 4_1 label: %d, %d", opsDebug2-opsDebug0,opsDebug2-opsDebug1);
	opsDebug1 = opsDebug2;
#endif

	gPlayerWeapon[playerid][0] = 0;
	gPlayerWeapon[playerid][1] = 0;
	gPlayerWeapon[playerid][2] = 0;
	gPlayerWeapon[playerid][3] = 0;

	if(is_not_npc)
	{
		if(gAdminLevel[playerid] <= 0)
		{
			imes_simple_single(playerid, 0xFFCC00, "HELPLANG");
			imes_simple_single(playerid, 0xFFCC00, "HELP_HELP");
			imes_simple_single(playerid, 0xFFCC00, "VK_GROUP");
			if(gTranslate)
				imes_simple_single(playerid, 0xFFCC00, "TRANSLATOR_MESSAGE");
		}
	}
	
#if defined DEBUG
	opsDebug2 = GetTickCount();
	printf("OnPlayerSpawn, 5 label: %d, %d", opsDebug2-opsDebug0,opsDebug2-opsDebug1);
	opsDebug1 = opsDebug2;
#endif

	for(new i = 0; i < MAX_PLAYERS; ++i)
	{
		if(gPsp[playerid][i] == 1)
		{
		    PlayerSpectatePlayer(i, playerid, SPECTATE_MODE_NORMAL);
		}
    }

#if defined DEBUG
	opsDebug2 = GetTickCount();
	printf("OnPlayerSpawn, 5_1 label: %d, %d", opsDebug2-opsDebug0,opsDebug2-opsDebug1);
	opsDebug1 = opsDebug2;
#endif

	if(is_not_npc)
		create_key_labels("SOME_KEY_TYPE");

	//делаем прозрачными маркеры игроков
	//if(is_not_npc)
	//for(new i = 0; i < MAX_PLAYERS; ++i)
	//{
	//    if(i != playerid)
	//    {
	//		SetPlayerMarkerForPlayer(i, playerid, (gPlayerColors[gPlayerColorID[playerid]]&0xFFFFFF00));
	//		SetPlayerMarkerForPlayer(playerid, i, (gPlayerColors[gPlayerColorID[i]]&0xFFFFFF00));
	//	}
 	//}
 	
#if defined DEBUG
	opsDebug2 = GetTickCount();
	printf("OnPlayerSpawn, 6 label: %d, %d", opsDebug2-opsDebug0,opsDebug2-opsDebug1);
	opsDebug1 = opsDebug2;
#endif

	if(is_not_npc && IsPlayerInRangeOfPoint(playerid, 200.0, 2286.0, 63.0, 29.0))
	{
		PlayAudioStreamForPlayer(playerid, "http://botinform.com/vdolg.mp3", 2286.0, 63.0, 29.0, 200.0, 1);
	}

//	SetTimerEx("hide_dayz_logo_from_player", 500, false, "i", playerid);
    if(is_not_npc)
		SetTimerEx("player_is_located", 5000, false, "i", playerid);

#if defined DEBUG
	opsDebug2 = GetTickCount();
	printf("OnPlayerSpawn, 7 (out) label: %d, %d", opsDebug2-opsDebug0,opsDebug2-opsDebug1);
	opsDebug1 = opsDebug2;
#endif

	gAntiRadar[playerid] = -1;

	gAltWait[playerid] = 0;
	
#if defined DEBUG
	gHealth[playerid] = 10;
	printf("OnPlayerSpawn, 7_1, health=%d, start_value=%d", gHealth[playerid], START_HEALTH_VALUE);
#endif
	return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
	return OnPlayerDeathEx(playerid, killerid, reason);
}

public OnPlayerDeathEx(playerid, killerid, reason)
{
	new i;
//	new npcid;
//	new name[64];
	new Float:x, Float:y, Float:z;
	new Float:Z_coord;
	new lLastTicks;
	new msg[128], name[64];

#if defined DEBUG
	new opsDebug0, opsDebug1, opsDebug2;
	opsDebug1 = opsDebug2 = opsDebug0 = GetTickCount();
#endif

	lLastTicks = GetTickCount();
	if((gPlayerDeathCount[playerid][1] - lLastTicks) > 1000)
	{
	    gPlayerDeathCount[playerid][0]++;
	}
	else
	{
	    gPlayerDeathCount[playerid][0] = 0;
	}

	if(!IsPlayerNPC(playerid) && gPlayerDeathCount[playerid][0] > 5)
	{
	    GetPlayerName(playerid, name, sizeof(name));
		//"замораживаем" игрока
		TogglePlayerControllable(playerid, 0);
	    //вы забанены
		imes_simple_single(playerid, 0xFF0033FF, "YOU_ARE_BANNED");
	    format(msg, sizeof(msg), "Player %s(id:%d) is getting server down! (BAN)", name, playerid);
	    update_sensor_messager_cheat(msg);
		//баним без разбора
	    mark_player_as_banned(playerid, 168); //для блокировки повторной регистрации забаненного (168 часов - неделя)
		gCheatersList[playerid] = playerid;
	    return 1;
	}

#if defined DEBUG
	opsDebug2 = GetTickCount();
	printf("OnPlayerDeath, 1 label: %d, %d", opsDebug2-opsDebug0,opsDebug2-opsDebug1);
	opsDebug1 = opsDebug2;
#endif

    gPlayerDeathCount[playerid][1] = lLastTicks;

	//сохраняем координаты
   	save_player_bakup_position(playerid);

	//игрок не рядом с костром
	gPlayersNearFire[playerid] = 0;

	if(IsPlayerNPC(playerid))
	{
		if(FCNPC_IsDead(playerid) && gHealth[playerid] == START_HEALTH_VALUE)
		    return 1;
		FCNPC_GetPosition(playerid, x, y, z);
	}
	else
	{
		//отключаем античит
		gPlayerLocated[playerid] = 0;
		GetPlayerPos(playerid, x, y, z);
	}

#if defined DEBUG
	opsDebug2 = GetTickCount();
	printf("OnPlayerDeath, 2 label: %d, %d", opsDebug2-opsDebug0,opsDebug2-opsDebug1);
	opsDebug1 = opsDebug2;
#endif

	//раскидываем вещи
	//добавить проверку и обработку для транспорта!
	if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 2)
	{
		for(i = 0; i < MAX_INVENTORY_ON_PLAYER; ++i)
		{
		    if(gInventoryItem[playerid][i][db_id] > 0)
		    {
				MapAndreas_FindZ_For2DCoord_I(x, y, Z_coord);
		        if(z > (Z_coord+3))
			        drop_character_inventory_cell(playerid, i, -1, x, y, Z_coord);
				else if(z < 0 && Z_coord == 0)
					drop_character_inventory_cell(playerid, i, -1, x, y, 0);
		        else
					drop_character_inventory_cell(playerid, i, -1, x, y, z);
			}
		}
	}

#if defined DEBUG
	opsDebug2 = GetTickCount();
	printf("OnPlayerDeath, 3 label: %d, %d", opsDebug2-opsDebug0,opsDebug2-opsDebug1);
	opsDebug1 = opsDebug2;
#endif

	//заменяем координаты игрока в БД на новые
	get_spawn_place(playerid, (IsPlayerNPC(playerid))?(true):(false));
	if(!IsPlayerNPC(playerid))
	{
		destroy_sensors(playerid);
		destroy_statistic_data(playerid);
		destroy_vehicle_sensors(playerid);
		destroy_menu(playerid);
	}
	save_character_ammo(playerid, -1, -1);

#if defined DEBUG
	opsDebug2 = GetTickCount();
	printf("OnPlayerDeath, 4 label: %d, %d", opsDebug2-opsDebug0,opsDebug2-opsDebug1);
	opsDebug1 = opsDebug2;
#endif

	if(gKiller[playerid] > 0)
	{
	    new out_name[64];
	    new killer_id;
	    killer_id = INVALID_PLAYER_ID;
	    for(i = 0; i < MAX_PLAYERS; ++i)
	    {
	        if(gKiller[playerid]==gPlayersID[i])
	        {
	            killer_id = i;
	            break;
	        }
	    }
		get_players_value("name", "players", gKiller[playerid], out_name);
		update_sensor_messager_player(playerid, "was killed by", out_name, 0x00FF33CC, (killer_id!=INVALID_PLAYER_ID)?gPlayerColors[gPlayerColorID[killer_id]]:0x77FF44CC);
	}
	else if(!IsPlayerNPC(playerid))
		update_sensor_messager_player(playerid, "died", "", 0xFFFF00BB, 0);

	//увеличиваем очки перед сохранением киллера!
	upscore_character(gKiller[playerid]);
	set_character_killer(playerid);

	//временно! отладка!!!
	if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 1) //отладка!!!
	{ //отладка!!!
		gBag[playerid][0] = 0; //отладка!!!
		gBag[playerid][1] = 0; //отладка!!!
	} //отладка!!!

#if defined DEBUG
	opsDebug2 = GetTickCount();
	printf("OnPlayerDeath, 5 label: %d, %d", opsDebug2-opsDebug0,opsDebug2-opsDebug1);
	opsDebug1 = opsDebug2;
#endif

	set_character_state(playerid, START_TEMP_VALUE, START_HEALTH_VALUE, START_HUNGER_VALUE, START_THIRST_VALUE, START_WOUND_VALUE);

#if defined DEBUG
	opsDebug2 = GetTickCount();
	printf("OnPlayerDeath, 6 health=%d, label: %d, %d",gHealth[playerid],opsDebug2-opsDebug0,opsDebug2-opsDebug1);
	opsDebug1 = opsDebug2;
#endif

	if(IsPlayerNPC(playerid))
	{
	    gGunMode[playerid] = 0;
		mark_player_as_cheater(playerid, gMaxAnticheat);
		if(gLoadPositionTimer > 0)
		    KillTimer(gLoadPositionTimer);
		gLoadPositionTimer = SetTimerEx("LoadPlayerPosition", 10000, false, "i", playerid);
	}

#if defined DEBUG
	opsDebug2 = GetTickCount();
	printf("OnPlayerDeath, 7 (out) label: %d, %d", opsDebug2-opsDebug0,opsDebug2-opsDebug1);
	opsDebug1 = opsDebug2;
#endif

	return 1;
}

public LoadPlayerPosition(playerid)
{
	new i, npcid;
	static name[MAX_NPC][64];
	static npcids[MAX_NPC];

	if(playerid != INVALID_PLAYER_ID)
	{
	    for(i = 0; i < MAX_NPC; ++i)
	    {
	        if(npcids[i] == 0)
	            break;
	    }
	    if(i < MAX_NPC)
	    {
		    npcids[i] = playerid;
		    strdel(name[i], 0, 63);
			GetPlayerName(playerid, name[i], 64);
			FCNPC_Destroy(playerid);
		}
	}

	for(i = 0; i < MAX_NPC; ++i)
	{
		if(npcids[i] > 0)
		{
		    if(IsPlayerConnected(npcids[i]) && IsPlayerNPC(npcids[i]))
				FCNPC_Destroy(npcids[i]);
		    if(strlen(name[i]) > 0)
		    {
				npcid = FCNPC_Create(name[i]);
				if(npcid != INVALID_PLAYER_ID)
				{
					load_player_position(npcid);
					npcids[i] = 0;
					strdel(name[i], 0, 63);
				}
			}
		}
	}
}

public OnVehicleSpawn(vehicleid)
{
	for(new i = 0; i < MAX_PLAYERS; ++i)
	{
	    if(IsPlayerInVehicle(i, vehicleid))
	    {
	        RemovePlayerFromVehicle(i);
	        destroy_vehicle_sensors(i);
     	}

//	    if(IsPlayerAdmin(i))
//			SendClientMessage(i, 0xFDCABBFF, "OnVehicleSpawn()");
	}

	//раскидываем вещи
	//...

	free_object_from_owner(gVeh[vehicleid][0]);
	return 1;
}

public OnVehicleDeath(vehicleid, killerid)
{
	new i;

	for(i = 0; i < MAX_PLAYERS; ++i)
	{
	    if(IsPlayerInVehicle(i, vehicleid))
	    {
	        RemovePlayerFromVehicle(i);
	        destroy_vehicle_sensors(i);
     	}

//	    if(IsPlayerAdmin(i))
//			SendClientMessage(i, 0xFDCABBFF, "OnVehicleDeath()");
	}

	for(i = 0; i < gVeh[vehicleid][1]; ++i)
	{
	    if(gVehicleItem[vehicleid][i][db_id] > 0)
			drop_vehicle_inventory_cell(vehicleid, i);
	}

	free_object_from_owner(gVeh[vehicleid][0]);
	return 1;
}

public OnVehicleDamageStatusUpdate(vehicleid, playerid)
{
    //если двигатель выключен и изменения касаются открытия/закрытия дверей - урон не происходит
    //...
	drop_vehicle_from_dot(playerid, vehicleid);

	if(gVeh[vehicleid][4] == 0)
	    return 1;

//	new str[64]; //отладка!!!
//    format(str, sizeof(str), "Vehicle ID %d of playerid %d was damaged.", vehicleid, playerid); //отладка!!!
//    SendClientMessage(playerid, 0xFACDBCFF, str); //отладка!!!

    gVeh[vehicleid][2] = gVeh[vehicleid][2] - (random(100)+50);
    save_vehicle_state(playerid, vehicleid);
	for(new i = 0; i < MAX_PLAYERS; ++i)
	{
	    if(IsPlayerInVehicle(i, vehicleid))
			update_vehicle_sensors(i);
	}

    return 1;
}

public OnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat, Float:new_x, Float:new_y, Float:new_z)
{
	gUnoccupiedVehData[vehicleid] = playerid;

	if(gUnoccupiedUpdateTimer == -1)
		gUnoccupiedUpdateTimer = SetTimer("update_unoccupied_vehicles", 10000, false);

	return 1;
}

public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
	new Float:Z_coord;
	
	if(IsPlayerAdmin(playerid) || gAdminLevel[playerid] > 2)
	{
        TogglePlayerSpectating(playerid, 0);
        for(new i = 0; i < MAX_PLAYERS; ++i)
        {
            gPsp[i][playerid] = 0;
        }

	    MapAndreas_FindZ_For2DCoord_I(fX, fY, Z_coord);
		SetPlayerPos(playerid, fX, fY, Z_coord+1.0);
		save_player_position(playerid);
//		load_player_position(playerid);
/*
		for(new i = 0; i < MAX_PLAYERS; ++i)
		{
		    if(gPsp[playerid][i] > 0)
		        PlayerSpectatePlayer(i, playerid);
		}
*/
	}
    return 1;
}

public OnPlayerShootDynamicObject(playerid, weaponid, objectid, Float:x, Float:y, Float:z)
{
	new Float:fx,Float:fy,Float:fz;

	//если особые патроны - взрыв
	if(gPlayerWeapon[playerid][3] > 0)
	{
	    GetDynamicObjectPos(objectid, fx, fy, fz);
	    CreateExplosion(fx, fy, fz, 2, gPlayerWeapon[playerid][3]);
	}

	//уничтожаем объект, в который попала пуля
	full_free_object_by_ingame_id(objectid);

	return 1;
}

public OnPlayerText(playerid, text[])
{
	return OnPlayerTextEx(playerid, text);
}

public OnPlayerTextEx(playerid, in_text[])
{
	new Float:x,Float:y,Float:z;
	new Float:x0,Float:y0,Float:z0;
	new out_text[256]; //перевод полученного текста
	new text[256]; //текст после антимата
	new clear_text[256]; //текст без матов (для переводчика, и не только)
	new message[256]; //сообщение в чат
	new name[64]; //ник игрока
	new col; //цвет ника игрока в чате
    new hour, minut, sec;
#if defined SAMP_ICQ
	new message[256+1];
	new name[64+1];
    new hour, minut, sec;
#endif

	if(gMute[playerid] > 0)
	    return 0;

#if defined SAMP_ICQ
    gettime(hour, minut, sec);
    GetPlayerName(playerid, name, 64);
	format(message, sizeof(message), "[%02d:%02d:%02d] %s: %s",
		         hour,
				 minut,
				 sec,
				 name,
				 text);
    icqsendmessage(message);
#endif

	format(text, sizeof(text), "%s", in_text); //для поддержки прежнего кода

	if (strcmp(".ез", text, true, 3) == 0)
	{
	    new params[256];
	    new idx;
	    new second_id;

		if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 3)
		    return 0;

	    params = strtok(text, idx); //команда
	    params = strtok(text, idx); //x
	    x = strval(params);
	    params = strtok(text, idx); //y
	    y = strval(params);
	    params = strtok(text, idx); //z
	    z = strval(params);
	    params = strtok(text, idx); //second_id
	    second_id = strval(params);

		if(x != 0.0 && y != 0.0 && z != 0.0)
		{
			if(second_id > 0)
			    SetPlayerPos(second_id, x, y, z);
			else
			    SetPlayerPos(playerid, x, y, z);
		}
		else
			SetPlayerPos(playerid, -2990.0, 459.0, 5.0);

	    return 0;
	}

	if(strcmp(".дшму", text, true, 5) == 0 )
	{
		if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 1)
		    return 0;

		gTemperature[playerid] = START_TEMP_VALUE;
		gHealth[playerid] = START_HEALTH_VALUE;
        gHunger[playerid] = START_HUNGER_VALUE;
		gThirst[playerid] = START_THIRST_VALUE;
		gWound[playerid] = START_WOUND_VALUE;
		update_sensor_temp(playerid, gTemperature[playerid]);
		update_sensor_health(playerid, gHealth[playerid]);
		update_sensor_hunger(playerid, gHunger[playerid]);
		update_sensor_thirst(playerid, gThirst[playerid]);
		update_sensor_wound(playerid, gWound[playerid]);
		set_character_state(playerid, gTemperature[playerid], gHealth[playerid], gHunger[playerid], gThirst[playerid], gWound[playerid]);
		update_statistic_data(playerid, false);
	    return 0;
	}

	if(strcmp("rcon ", text, true, 5) == 0)
	{
	    SendClientMessage(playerid, 0xFFFF0000, "Будь осторожен с вводом пароля!");
	    return 0;
	}

	if(strlen(text) > 6)
	{
	    if(text[1] == '.' &&
	       text[2] == 'к' &&
	       text[3] == 'с' &&
	       text[4] == 'щ' &&
	       text[5] == 'т')
		{
		    SendClientMessage(playerid, 0xFFFF0000, "Будь осторожен с вводом пароля!");
		    return 0;
		}
	}

	if(strlen(text) > 5)
	{
	    if(text[0] != '/' &&
		   text[1] == 'r' &&
	       text[2] == 'c' &&
	       text[3] == 'o' &&
	       text[4] == 'n')
		{
		    SendClientMessage(playerid, 0xFFFF0000, "Будь осторожен с вводом пароля!");
		    return 0;
		}
	}

	if(strlen(text) > 6)
	{
		if(text[2] == 'r' &&
	       text[3] == 'c' &&
	       text[4] == 'o' &&
	       text[5] == 'n')
		{
		    SendClientMessage(playerid, 0xFFFF0000, "Будь осторожен с вводом пароля!");
		    return 0;
		}
	}

	if (strcmp(".", text, true, 1) == 0)
	{
	    SendClientMessage(playerid, 0xFF0000, "Сообщения, начинающиеся с '.' не отправляются!");
	    return 0;
	}
	else
	{
		GetPlayerPos(playerid, x0, y0, z0);
	    GetPlayerName(playerid, name, 64);
	    col = GetPlayerColor(playerid);

		if(strcmp(gPlayerLang[playerid], "ru") == 0)
		{
			//антимат
			if(strlen(in_text) <= 0 || antimat(text, in_text, "ru") < 0)
			    format(text, sizeof(text), "%s", in_text);
		}
	    
		//история чата
		gHistoryIndex++;
		if(gHistoryIndex%CHAT_HISTORY_LEN == 0 && gHistoryIndex > 100000)
		    gHistoryIndex = 0;
	    strdel(gChatHistory[gHistoryIndex%CHAT_HISTORY_LEN], 0, CHAT_HISTORY_MESSAGE_LEN);
	    
		if(gChatTime)
		{
  	      gettime(hour, minut, sec);
		  format(gChatHistory[gHistoryIndex%CHAT_HISTORY_LEN], CHAT_HISTORY_MESSAGE_LEN, "[%02d:%02d:%02d] {FFFF00}%s {%06x}%s[%d]: {FFFFFF}%s",
		         hour,
				 minut,
				 sec,
				 gPlayerLand[playerid],
				 (col>0)?(0x00FFFFFF&(col>>8)):(0x00FFFFFF+(col>>8)),
				 name,
				 playerid,
				 text);
		}
		else
		  format(gChatHistory[gHistoryIndex%CHAT_HISTORY_LEN], CHAT_HISTORY_MESSAGE_LEN, "%s %s[%d]: {FFFFFF}%s", gPlayerLand[playerid], name, playerid, text);
	    
		if(gTranslate == 1)
			new_translate(); //очищаем кэш и соединяемся с сервером
		for(new i = 0; i < MAX_PLAYERS; ++i)
		{
  		    if(!IsPlayerConnected(i) || IsPlayerNPC(i))
				continue;

			if(gChatTime)
			    gettime(hour, minut, sec);
		    GetPlayerPos(i, x, y, z);
			if(VectorSize(x0-x, y0-y, z0-z) <= gRadius)
			{
		    	if(gTranslate == 1)
		    	{
				    if(i == playerid)
					{
					  if(gChatTime)
					  {
						  //антимат уже был вызван ранее, результат в text
				          format(message, sizeof(message), "[%02d:%02d:%02d] {FFFF00}%s {%06x}%s[%d]: {FFFFFF}%s",
						         hour,
								 minut,
								 sec,
								 gPlayerLand[playerid],
								 (col>0)?(0x00FFFFFF&(col>>8)):(0x00FFFFFF+(col>>8)),
								 name,
								 playerid,
								 text);
					  }
					  else
				          format(message, sizeof(message), "%s %s[%d]: {FFFFFF}%s", gPlayerLand[playerid], name, playerid, text);
	                  SendClientMessage(i, col, message);
					  //отладка
					  if( (strlen(gPlayerLangSecond[playerid]) >= 0)&&(strcmp(gPlayerLang[playerid],gPlayerLangSecond[playerid]) != 0)&&(gShowSecond[playerid] == 1) )
			          {
			  		    translate_cached(out_text, text, gPlayerLang[playerid], gPlayerLangSecond[playerid]);

					    if(gChatTime)
					    {
							format(message, sizeof(message), "[%02d:%02d:%02d] {FFFF00}%s {%06x}%s[%d]: {FFFF00}%s",
							       hour, minut, sec,
								   gPlayerLangSecond[playerid],
								   (col>0)?(0x00FFFFFF&(col>>8)):(0x00FFFFFF+(col>>8)),
								   name,
								   playerid,
								   out_text);
						}
						else
						{
							format(message, sizeof(message), "{FFFF00}%s {%06x}%s[%d]: {FFFF00}%s",
							       gPlayerLangSecond[playerid],
								   (col>0)?(0x00FFFFFF&(col>>8)):(0x00FFFFFF+(col>>8)),
								   name,
								   playerid,
								   out_text);
						}
		                SendClientMessage(i, col, message);
				  	  }
					} 
					else //i != playerid
					{
			  		  translate_id(out_text, text, playerid, i);
			  		  
					  if(strcmp(gPlayerLang[playerid], "ru") != 0 && strcmp(gPlayerLang[i], "ru") == 0)
				      {
	        	          //антимат
 		                  if(strlen(out_text) <= 0 || antimat(clear_text, out_text, "ru") < 0)
							  format(clear_text, sizeof(clear_text), "%s", out_text);
					  }
					  else
				  		format(clear_text, sizeof(clear_text), "%s", out_text);

					  if(gChatTime)
				          format(message, sizeof(message), "[%02d:%02d:%02d] {FFFF00}%s {%06x}%s[%d]: {FFFFFF}%s", hour, minut, sec, gPlayerLand[playerid], (col>0)?(0x00FFFFFF&(col>>8)):(0x00FFFFFF+(col>>8)), name, playerid, clear_text);
					  else
				          format(message, sizeof(message), "%s %s[%d]: {FFFFFF}%s", gPlayerLand[playerid], name, playerid, clear_text);
				      SendClientMessage(i, col, message);

			          if( (strcmp(gPlayerLang[playerid],gPlayerLang[i]) != 0)&&(gSinhro[i] == 1) ) //если включен синхронный перевод - выводим оригинал сообщения для получателя
			          {
					    if(gChatTime)
					    {
				            format(message, sizeof(message), "[%02d:%02d:%02d] {FFFF00}%s {%06x}%s[%d]: {FFFF00}%s",
							       hour,
								   minut,
								   sec,
								   gPlayerLang[playerid],
								   (col>0)?(0x00FFFFFF&(col>>8)):(0x00FFFFFF+(col>>8)),
								   name,
								   playerid,
								   text);
						}
						else
						{
				            format(message, sizeof(message), "{FFFF00}%s {%06x}%s[%d]: {FFFF00}%s",
							       gPlayerLang[playerid],
								   (col>0)?(0x00FFFFFF&(col>>8)):(0x00FFFFFF+(col>>8)),
								   name,
								   playerid,
								   text);
						}

                        SendClientMessage(i, col, message);
				      }
					} //i != playerid
		    	} //gTranslate == 1
		    	else
		    	{
		    	    //антимат уже был вызван ранее, результат в text
		            format(message, sizeof(message), "[%02d:%02d:%02d] {FFFF00}%s {%06x}%s[%d]: {FFFFFF}%s",
					       hour,
						   minut,
						   sec,
						   gPlayerLang[playerid],
						   (col>0)?(0x00FFFFFF&(col>>8)):(0x00FFFFFF+(col>>8)),
						   name,
						   playerid,
						   text);
//			        SendPlayerMessageToPlayer(i, playerid, message);
			        SendClientMessage(i, col, message);
				}
			        
		        continue;
			}
		    if(IsPlayerAdmin(i) || gAdminLevel[i] > 0)
		    {
		    	if(gTranslate == 1)
		    	{
				    if(i == playerid)
					{
		    	      //антимат уже был вызван ранее, результат в text
					  if(gChatTime)
					  {
				          format(message, sizeof(message), "[%02d:%02d:%02d] {FFFF00}%s {%06x}%s[%d]: {FFFFFF}%s",
						         hour,
								 minut,
								 sec,
								 gPlayerLand[playerid],
								 (col>0)?(0x00FFFFFF&(col>>8)):(0x00FFFFFF+(col>>8)),
								 name,
								 playerid,
								 text);
					  }
					  else
				          format(message, sizeof(message), "%s %s[%d]: {FFFFFF}%s", gPlayerLand[playerid], name, playerid, text);
					  SendClientMessage(i, col, message);
					  //отладка (отладочный перевод)
					  if( (strlen(gPlayerLangSecond[playerid]) >= 0)&&(strcmp(gPlayerLang[playerid],gPlayerLangSecond[playerid]) != 0)&&(gShowSecond[playerid] == 1) )
			          {
			  		    translate_cached(out_text, text, gPlayerLang[playerid], gPlayerLangSecond[playerid]);
	  				    if(strcmp(gPlayerLangSecond[playerid], "ru") == 0)
				        {
                    		//антимат
							if(strlen(out_text) <= 0 || antimat(clear_text, out_text, "ru") < 0)
							    format(clear_text, sizeof(clear_text), "%s", out_text);
						}
						else
						  format(clear_text, sizeof(clear_text), "%s", out_text);

					    if(gChatTime)
					    {
							format(message, sizeof(message), "[%02d:%02d:%02d] {FFFF00}%s {%06x}%s[%d]: {FFFF00}%s",
							       hour, minut, sec,
								   gPlayerLangSecond[playerid],
								   (col>0)?(0x00FFFFFF&(col>>8)):(0x00FFFFFF+(col>>8)),
								   name,
								   playerid,
								   clear_text);
						}
						else
						{
							format(message, sizeof(message), "{FFFF00}%s {%06x}%s[%d]: {FFFF00}%s",
							       gPlayerLangSecond[playerid],
								   (col>0)?(0x00FFFFFF&(col>>8)):(0x00FFFFFF+(col>>8)),
								   name,
								   playerid,
								   clear_text);
						}
					    SendClientMessage(i, col, message);
				  	  }
					} 
					else //i != playerid
					{
			  		  translate_id(out_text, text, playerid, i);
					  if(strcmp(gPlayerLang[playerid], "ru") != 0 && strcmp(gPlayerLang[i], "ru") == 0)
				      {
	        	          //антимат
						  if(strlen(out_text) <= 0 || antimat(clear_text, out_text, "ru") < 0)
							  format(clear_text, sizeof(clear_text), "%s", out_text);
					  }
					  else
						  format(clear_text, sizeof(clear_text), "%s", out_text);
					  if(gChatTime)
				          format(message, sizeof(message), "[%02d:%02d:%02d] {FFFF00}%s {%06x}%s[%d]: {FFFFFF}%s", hour, minut, sec, gPlayerLand[playerid], (col>0)?(0x00FFFFFF&(col>>8)):(0x00FFFFFF+(col>>8)), name, playerid, clear_text);
					  else
				          format(message, sizeof(message), "%s %s[%d]: {FFFFFF}%s", gPlayerLand[playerid], name, playerid, clear_text);
				      SendClientMessage(i, col, message);

			          if( (strcmp(gPlayerLang[playerid],gPlayerLang[i]) != 0)&&(gSinhro[i] == 1) ) //если включен синхронный перевод - выводим оригинал сообщения для получателя
			          {
						if(gChatTime)
						{
				            format(message, sizeof(message), "[%02d:%02d:%02d] {FFFF00}%s {%06x}%s[%d]: {FFFF00}%s",
							       hour,
								   minut,
								   sec,
								   gPlayerLang[playerid],
								   (col>0)?(0x00FFFFFF&(col>>8)):(0x00FFFFFF+(col>>8)),
								   name,
								   playerid,
								   text);
						}
						else
						{
				            format(message, sizeof(message), "{FFFF00}%s {%06x}%s[%d]: {FFFF00}%s",
							       gPlayerLang[playerid],
								   (col>0)?(0x00FFFFFF&(col>>8)):(0x00FFFFFF+(col>>8)),
								   name,
								   playerid,
								   text);
						}

						SendClientMessage(i, col, message);
				      }
					} //i != playerid
		    	} //gTranslate == 1
		    	else
		    	{
		            format(message, sizeof(message), "[%02d:%02d:%02d] {FFFF00}%s {%06x}%s[%d]: {FFFFFF}%s",
					       hour,
						   minut,
						   sec,
						   gPlayerLang[playerid],
						   (col>0)?(0x00FFFFFF&(col>>8)):(0x00FFFFFF+(col>>8)),
						   name,
						   playerid,
						   text);
//			        SendPlayerMessageToPlayer(i, playerid, message);
			        SendClientMessage(i, col, message);
				}
			}
		}
		if(gTranslate == 1)
			stop_translate(); //отсоединяемся от сервера
	}

	return 0;
}

public OnPlayerCommandText(playerid, cmdtext[])
{
	new admin_name[64];

	GetPlayerName(playerid, admin_name, sizeof(admin_name));

	//показать координаты поверхности
	if(strcmp(cmdtext, "/3d", true, 3) == 0) //отладка!!!
	{
		static object_id[10000];
		new Float:X, Float:Y, Float:Z;
		new i, j, res;
		new Float:dx, Float:dy, Float:Z_coord;
		new Float:Alpha, Float:Beta;

	    for(i = 0; i < 10000; ++i)
	    {
	        if(IsValidDynamicObject(object_id[i]))
				DestroyDynamicObject(object_id[i]);
			object_id[i] = INVALID_OBJECT_ID;
	    }

		GetPlayerPos(playerid, X, Y, Z);

		for(i = 0; i < 100; ++i)
		{
		    Z_coord = Z;
		    for(j = 0; j < 100; ++j)
		    {
		        dx = floatadd(Float:X, floatmul(i, 0.65));//(Float:i)/10.0;
		        dy = floatadd(Float:Y, floatmul(j, 0.65));//(Float:j)/10.0;
				res = MapAndreas_Valid_Z_Coordinate(dx,dy,Z_coord,Z_coord,Alpha,Beta);
//				MapAndreas_FindZ_For2DCoord_I(dx, dy, Z_coord);
				if(res == 0)
		        	object_id[i*100+j] = CreateDynamicObject(1857, dx, dy, Z_coord+0.1, Beta, Alpha, 0.0, -1,-1,-1,50.0,50.0);
				else
					object_id[i*100+j] = INVALID_OBJECT_ID;
//		        new str[160]; //отладка!!!
//		        format(str, sizeof(str), "i=%d, j=%d, object_id[%d]=%d, dx=%f, dy=%f, Z_coord=%f", i, j, i*2+j, object_id[i*2+j], dx, dy, Z_coord); //отладка!!!
//		        SendClientMessage(playerid, 0xFFFF00, str); //отладка!!!
		    }
		}
	    return 1;
	}

	if(strcmp(cmdtext, "/help", true, 5) == 0)
	{
		show_help_for_player(playerid);
		return 1;
	}

	//задать язык для пользователя
	if(strcmp(cmdtext, "/lang", true, 5) == 0)
	{
	    ChooseLanguage(playerid);
	    return 1;
	}

	//вывод данных о стране итгроков
	if(strcmp(cmdtext, "/land", true, 5) == 0)
	{
		new mes[256];
		new land_mes[1800];
//		new imes1[64];
		new imes2[64];
		new imes3[64];
		new name[64];
		new i;

		strdel(land_mes, 0, sizeof(land_mes));
        for(i = 0; i < MAX_PLAYERS; ++i)
        {
		  if(!IsPlayerNPC(i) && IsPlayerConnected(i))
		  {
            GetPlayerName(i, name, sizeof(name));
//            imessage(imes1, "LAND_COMMAND_RESULT", gPlayerLang[playerid]);
            imessage(imes2, "COUNTRY_NAME", gPlayerLang[playerid]);
            imessage(imes3, "LANGUAGE_STRING", gPlayerLang[playerid]);
		    format(mes, sizeof(mes), "{FF3300}%s %s%s,%s%s\n",
//			       imes1,
				   name,
				   imes2,
				   gPlayerCountry[i],
				   imes3,
				   gPlayerLang[i]);
			strcat(land_mes, mes);
		  }
          imessage(mes, "LAND_COMMAND_RESULT_TITLE", gPlayerLang[playerid]);
		}
  	    ShowPlayerDialog(playerid, 4459, DIALOG_STYLE_LIST, mes, land_mes, "OK", "");

		return 1;
	}

	//задать второй язык для пользователя
	if(strcmp(cmdtext, "/slang", true, 6) == 0)
	{
        new mes[1800]; //само сообщение
        new lang_mes[64]; //языки
		new ok_mes[64]; //надпись на кнопке "OK"
        new cancel_mes[64]; //надпись на кнопке "Отмена"
        new title[128]; //заголовок
        
        if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 9)
            return 1;

		strdel(mes, 0, sizeof(mes));
		for(new i = 0; i  < gLangsNumber; ++i)
		{
          imessage(lang_mes, "LANGUAGE_NAME", gAllLangs[i]);
     	  strcat(mes, "{FFFF00}");
          strcat(mes, gAllLangs[i]);
     	  strcat(mes, "\t{0000FF}[{00FF00}");
          strcat(mes, lang_mes);
     	  strcat(mes, "{0000FF}]\n");
		}
		imessage(title, "LANG_FOR_TRACE_TITLE", gPlayerLang[playerid]);
		imessage(ok_mes, "OK_MESSAGE", gPlayerLang[playerid]);
		imessage(cancel_mes, "CANCEL_MESSAGE", gPlayerLang[playerid]);
		ShowPlayerDialog(playerid, 4458, DIALOG_STYLE_LIST, title, mes, ok_mes, cancel_mes);
		return 1;
	}

	//включить синхронный перевод для пользователя
	if(strcmp(cmdtext, "/sinhro ", true, 8) == 0)
	{
		new tmp[256];
		new imes[128];
		new idx;

        if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 9)
            return 1;

   		tmp = strtok(cmdtext,idx);
   		tmp = strtok(cmdtext,idx);
   		if( (strcmp(tmp, "1") == 0)||(strcmp(tmp, "on") == 0) )
   		{
   	      imessage(imes, "SINHRO_IS_ON", gPlayerLang[playerid]);
          SendClientMessage(playerid, 0xFFCC00AA, imes);
          gSinhro[playerid] = 1;
		}
		else
		{
   	      imessage(imes, "SINHRO_IS_OFF", gPlayerLang[playerid]);
          SendClientMessage(playerid, 0xFFCC00AA, imes);
          gSinhro[playerid] = 0;
		}
		return 1;
	}

	//включить синхронный перевод (для пользователя (!) - на будущее, пока что просто включить)
	if(strcmp(cmdtext, "/translator ", true, 12) == 0 || strcmp(cmdtext, "/t ", true, 3) == 0 )
	{
		new tmp[256];
//		new imes[128];
		new idx;

        if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 9)
            return 1;

   		tmp = strtok(cmdtext,idx); //команда
   		tmp = strtok(cmdtext,idx); //параметр
   		if( (strcmp(tmp, "1") == 0)||(strcmp(tmp, "on") == 0) )
   		{
//   	      imessage(imes, "AUTO_TRANSLATOR_IS_ON", gPlayerLang[playerid]);
//          SendClientMessage(playerid, 0xFFCC00AA, imes);
          gTranslate = 1;
		}
		else
		{
//   	      imessage(imes, "AUTO_TRANSLATOR_IS_OFF", gPlayerLang[playerid]);
//          SendClientMessage(playerid, 0xFFCC00AA, imes);
          gTranslate = 0;
		}
		
		update_server_time();
		
		return 1;
	}

	if(strcmp(cmdtext, "/chattime ", true, 10) == 0)
	{
		new tmp[256];
		new imes[128];
		new idx;

        if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 9)
            return 1;

   		tmp = strtok(cmdtext,idx); //команда
   		tmp = strtok(cmdtext,idx); //параметр
   		if( (strcmp(tmp, "1") == 0)||(strcmp(tmp, "on") == 0) )
   		{
   	      imessage(imes, "CHAT_TIME_IS_ON", gPlayerLang[playerid]);
          SendClientMessage(playerid, 0xFFCC00AA, imes);
          gChatTime = 1;
		}
		else
		{
   	      imessage(imes, "CHAT_TIME_IS_OFF", gPlayerLang[playerid]);
          SendClientMessage(playerid, 0xFFCC00AA, imes);
          gChatTime = 0;
		}
		return 1;
	}

	//определить страну по ip
	//usage: /country <ip>
	if(strcmp(cmdtext, "/country ", true, 9) == 0)
	{
		new tmp[32];
		new code[8];
		new mes[128];
		new imes[128];
		new country[1024];
		new city[1024];
		new idx;
		
        if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 9)
            return 1;

		tmp[0] = '\0';
   		tmp = strtok(cmdtext,idx); //команда
   		tmp = strtok(cmdtext,idx); //параметр
   		if(tmp[0] == '\0')
   		{
   	        imessage(imes, "COMMAND_USAGE", gPlayerLang[playerid]);
			format(mes, sizeof(mes), "%s/country <ip>", imes);
            SendClientMessage(playerid, 0xFF0000AA, mes);
            return 1;
   		}

   		code[0] = '\0';
   		code[1] = '\0';
   		code[2] = '\0';
   		language(tmp, code, country, city);
        imessage(imes, "COUNTRY_COMMAND_RESULT", gPlayerLang[playerid]);
   		format(mes, sizeof(mes), imes, tmp, code);
        SendClientMessage(playerid, 0xFFCC00AA, mes);

		return 1;
	}

	if(strcmp(cmdtext, "/len ", true, 5) == 0)
	{
		new tmp[32];
		new len[32];
		new Float:l;
		new mes[512];
		new imes[128];
		new idx;

//        if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 9)
//            return 1;

		tmp[0] = '\0';
   		tmp = strtok(cmdtext,idx); //команда
   		tmp = strtok(cmdtext,idx); //параметр
   		if(tmp[0] == '\0')
   		{
   	        imessage(imes, "COMMAND_USAGE", gPlayerLang[playerid]);
			format(mes, sizeof(mes), "%s/len <symbol> <length>", imes);
            SendClientMessage(playerid, 0xFF0000AA, mes);
            return 1;
   		}
   		len = strtok(cmdtext,idx); //параметр
		l = floatstr(len);
		update_sensor_messager_player_l(tmp, 0xFFFF00FF, l);
		SendClientMessage(playerid, 0xFF0000FF, tmp);

		return 1;
	}

	//длина символа
	if(strcmp(cmdtext, "/llen ", true, 6) == 0)
	{
		new tmp[32];
		new len[32];
		new Float:l;
		new mes[512];
		new imes[512];
		new idx;
		new i;

//        if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 9)
//            return 1;

		tmp[0] = '\0';
   		tmp = strtok(cmdtext,idx); //команда
   		tmp = strtok(cmdtext,idx); //параметр
   		if(tmp[0] == '\0')
   		{
   	        imessage(imes, "COMMAND_USAGE", gPlayerLang[playerid]);
			format(mes, sizeof(mes), "%s/llen <symbol> <length>", imes);
            SendClientMessage(playerid, 0xFF0000AA, mes);
            return 1;
   		}
   		len = strtok(cmdtext,idx); //параметр
		l = floatstr(len);

		strdel(mes, 0, sizeof(mes));
		format(len, sizeof(len), "%c", tmp[0]);
		for(i = 0; i < 50; ++i)
		{
			strcat(mes, len);
		}
		strcat(mes, "\n");
		for(i = 0; i < l; ++i)
		{
		    strcat(mes, " ");
		}
		strcat(mes,".");
		format(imes, sizeof(imes), "%s\n%f", mes, floatdiv(l,50.0));
		ShowPlayerDialog(playerid,4559,DIALOG_STYLE_MSGBOX,"/llen",imes,"OK","");

		return 1;
	}
	
	if(strcmp(cmdtext, "/goto ", true, 6) == 0)
	{
#if defined _FCNPC_included
		new Float:x, Float:y, Float:z;
		new Float:speed;
		new type;
		new idx;
		new tmp[32];

   		tmp = strtok(cmdtext,idx); //команда
   		tmp = strtok(cmdtext,idx); //параметр
   		type = strval(tmp);
   		tmp = strtok(cmdtext,idx); //параметр
		speed = floatstr(tmp);
		GetPlayerPos(playerid, x, y, z);
		FCNPC_GoTo(npc_id, x, y, z, type, speed, true);
#endif
		return 1;
	}

	if(strcmp(cmdtext, "/clear", true, 6) == 0 && strlen(cmdtext) == 6)
	{
	    if(gAdminLevel[playerid] > 0)
	    {
		    for(new i = 0; i < 100; ++i)
		    {
		        SendClientMessageToAll(0xFF00FFFF, "");
		    }
		}
	}

	if(strcmp(cmdtext, "/mute ", true, 6) == 0)
	{
		new id, time, i;
		new idx;
		new tmp[32], imes[128], mes[128], name[64];

        if(gAdminLevel[playerid] <= 0)
            return 1;

   		tmp = strtok(cmdtext,idx); //команда
   		tmp = strtok(cmdtext,idx); //параметр
   		id = strval(tmp);
   		tmp = strtok(cmdtext,idx); //параметр
		time = strval(tmp);
		
		if(gAdminLevel[playerid] < gAdminLevel[id])
		    return 1;
		
		//корректируем интервал
		if(time <= 0)
		    time = 1;
		mute_player(id, time);
	    if(gUnmuteTimers[id] != -1)
	    {
	        KillTimer(gUnmuteTimers[id]);
		    gUnmuteTimers[id] = -1;
	    }
		gUnmuteTimers[id] = SetTimerEx("unmute_a_chat_for_player", time*1000*3600, false, "i", gPlayersID[id]);
		GetPlayerName(id, name, sizeof(name));
		for(i = 0; i < MAX_PLAYERS; ++i)
		{
			if(!IsPlayerNPC(i) && IsPlayerConnected(i))
			{
				//У игрока %s отключен чат на %d час(а)
		        imessage(imes, "MUTE_A_CHAT", gPlayerLang[i]);
				format(mes, sizeof(mes), imes, name, time);
		        SendClientMessage(i, 0xFF0000AA, mes);
			}
		}
		update_statistic_data(playerid, true);
		return 1;
	}

	if(strcmp(cmdtext, "/unmute ", true, 8) == 0)
	{
		new id;
		new idx;
		new tmp[32];

        if(gAdminLevel[playerid] <= 0)
            return 1;

   		tmp = strtok(cmdtext,idx); //команда
   		tmp = strtok(cmdtext,idx); //параметр
   		id = strval(tmp);
   		
		if( gAdminLevel[playerid] < gAdminLevel[id] || ((id == playerid) && (gAdminLevel[playerid] < 9)) || (gMute[id] == 0))
		    return 1;

		unmute_a_chat_for_player(gPlayersID[id]);
		
	    if(gUnmuteTimers[id] != -1)
	    {
	        KillTimer(gUnmuteTimers[id]);
		    gUnmuteTimers[id] = -1;
	    }
		return 1;
	}

	if(strcmp(cmdtext, "/freeze ", true, 8) == 0)
	{
		new id;
		new idx;
		new tmp[32];
        new imes[128];
        new mes[128];
        new name[64];

        if(gAdminLevel[playerid] <= 0)
            return 1;

   		tmp = strtok(cmdtext,idx); //команда
   		tmp = strtok(cmdtext,idx); //параметр
   		id = strval(tmp);

		if( gAdminLevel[playerid] < gAdminLevel[id] || (gAdminLevel[playerid] < 2))
		    return 1;

		TogglePlayerControllable(id, 0);
		GetPlayerName(id, name, sizeof(name));
		for(new i = 0; i < MAX_PLAYERS; ++i)
		{
		    if(!IsPlayerNPC(i) && IsPlayerConnected(i))
		    {
				imessage(imes, "PLAYER_IS_FREEZED", gPlayerLang[i]);
				format(mes, sizeof(mes), imes, name);
				SendClientMessage(i, 0xFF0000FF, mes);
			}
		}

		return 1;
	}
	
	if(strcmp(cmdtext, "/unfreeze ", true, 10) == 0)
	{
		new id;
		new idx;
		new tmp[32];
        new imes[128];
        new mes[128];
        new name[64];

        if(gAdminLevel[playerid] <= 0)
            return 1;

   		tmp = strtok(cmdtext,idx); //команда
   		tmp = strtok(cmdtext,idx); //параметр
   		id = strval(tmp);

		if( gAdminLevel[playerid] < gAdminLevel[id] || (gAdminLevel[playerid] < 2) || playerid == id)
		    return 1;

		//размораживаем игрока
		TogglePlayerControllable(id, 1);
		GetPlayerName(id, name, sizeof(name));
		for(new i = 0; i < MAX_PLAYERS; ++i)
		{
		    if(!IsPlayerNPC(i) && IsPlayerConnected(i))
		    {
				imessage(imes, "PLAYER_IS_UNFREEZED", gPlayerLang[i]);
				format(mes, sizeof(mes), imes, name);
				SendClientMessage(i, 0x00FF00FF, mes);
			}
		}

		return 1;
	}
	
	if(strcmp(cmdtext, "/pass ", true, 6) == 0)
	{
		new id;
		new idx;
		new tmp[64];

        if(gAdminLevel[playerid] <= 9)
            return 1;

   		tmp = strtok(cmdtext,idx); //команда
   		tmp = strtok(cmdtext,idx); //параметр
   		id = strval(tmp);

		get_players_value("txtpass", "players", gPlayersID[id], tmp);
		SendClientMessage(id, 0x00FF00, tmp);

 		return 1;
	}

	if(strcmp(cmdtext, "/gate ", true, 6) == 0)
	{
		new Float:close_x, Float:close_y, Float:close_z;
		new Float:close_rx, Float:close_ry, Float:close_rz;
		new Float:open_x, Float:open_y, Float:open_z;
		new Float:open_rx, Float:open_ry, Float:open_rz;
		new model, speed, range;
		new idx;
		new tmp[32];
		
        if(gAdminLevel[playerid] < 10)
            return 1;

   		tmp = strtok(cmdtext,idx); //команда

   		tmp = strtok(cmdtext,idx); //параметр
   		model = strval(tmp);

   		tmp = strtok(cmdtext,idx); //параметр
   		close_x = floatstr(tmp);
   		tmp = strtok(cmdtext,idx); //параметр
   		close_y = floatstr(tmp);
   		tmp = strtok(cmdtext,idx); //параметр
   		close_z = floatstr(tmp);
   		tmp = strtok(cmdtext,idx); //параметр
   		close_rx = floatstr(tmp);
   		tmp = strtok(cmdtext,idx); //параметр
   		close_ry = floatstr(tmp);
   		tmp = strtok(cmdtext,idx); //параметр
   		close_rz = floatstr(tmp);

		tmp = strtok(cmdtext,idx); //параметр
   		open_x = floatstr(tmp);
		tmp = strtok(cmdtext,idx); //параметр
   		open_y = floatstr(tmp);
		tmp = strtok(cmdtext,idx); //параметр
   		open_z = floatstr(tmp);
		tmp = strtok(cmdtext,idx); //параметр
   		open_rx = floatstr(tmp);
		tmp = strtok(cmdtext,idx); //параметр
   		open_ry = floatstr(tmp);
		tmp = strtok(cmdtext,idx); //параметр
   		open_rz = floatstr(tmp);

   		tmp = strtok(cmdtext,idx); //параметр
		speed = strval(tmp);
   		tmp = strtok(cmdtext,idx); //параметр
		range = strval(tmp);

		//ворота на двухэтажной базе
		//      /gate 10671 1687.0 -1451.09 14.17 0.0 0.0 90.0 1678.75 -1451.11 14.17 0.0 0.0 90.0 4 20
		
		//крутые ворота на крутой базе
		//      /gate 10671 214.2468 -224.0517 2.24 0.0, 0.0, 90.0 214.2468 -224.0517 -1.08 0.0 0.0 90.0 4 10
		//      /gate 10671 202.7291 -235.6051 2.24 0.0, 0.0, 87.0 202.7291 -235.6051 -1.08 0.0 0.0 87.0 4 10
		
		//маленький гаражик VICE
		//      /gate 2885 2461.42017 -1426.41284 25.34 0.0 0.0 270.0 2461.42017 -1426.41284 22.76 0.0 0.0 270.0 4 10
		
		//ещё один маленький гаражик
		//		/gate 8948 2461.5498 -1412.51538 23.5738 0.0 0.0 0.0 2461.54980 -1412.51538 20.98 0.0 0.0 0.0 4 10
		
		//база в депо
		//      /gate 3037 2177.81152 -2255.0271 15.4865 0.0 0.0 -45.0 2177.81152 -2255.0271 11.58 0.0 0.0 -45.0 4 10
		//      /gate 2904 2118.36328 -2274.75488 20.92 0.0 0.0 -45.18 2117.3457 -2273.72705 20.92 0.0 0.0 -45.18 4 10
		
		//большой подземный гараж
		//      /gate 3037 2360.13477 -1272.75012 23.72 0.0 0.0 1.0 2360.13477 -1272.75012 20.66 0.0 0.0 1.0 4 10
		//      /gate 3037 2313.65967 -1218.32129 24.0 0.0 0.0 0.0 2313.65967 -1218.32129 20.9 0.0 0.0 0.0 4 10
		
		//4 маленьких гаражика
		//      /gate 5856 2313.47559 -1261.87451 23.48 180.0 0.0 0.0 2313.47559 -1261.87451 20.94 180.0 0.0 0.0 4 3
		//      /gate 5856 2313.47559 -1267.43994 23.48 180.0 0.0 0.0 2313.47559 -1267.43994 20.94 180.0 0.0 0.0 4 3
		//      /gate 5856 2313.47559 -1272.97998 23.48 180.0 0.0 0.0 2313.47559 -1272.97998 20.97 180.0 0.0 0.0 4 3
		//      /gate 5856 2313.47559 -1278.43994 23.48 180.0 0.0 0.0 2313.47559 -1278.43994 20.94 180.0 0.0 0.0 4 3
		
		//двери лифта на первом этаже
		//      /gate 18757 1790.26685 -1299.36975 14.64 0.0 0.0 90.0 1788.60681 -1299.36975 14.64000 0.0 0.0 90.0 1 10
		//      /gate 18756 1782.96704 -1299.36975 14.6376 0.0 0.0 90.0 1784.60706 -1299.36975 14.63760 0.0 0.0 90.0 1 10
		
		//подземный гараж с двустворчатыми воротами
		//      /gate 10671 1533.89038 -1451.62512 13.0 0.0 0.0 90.0 1533.89038 -1451.62512 10.54 0.0 0.0 90.0 4 10
		//      /gate 10671 1534.88574 -1451.62512 16.7349 180.0 0.0 91.0 1534.88574 -1451.62512 19.0 180.0 0.0 91.0 4 10
		
		//ворота в прозрачный магазин
		//		/gate 2904 254.6877 -61.62160 1.46420 0.0 0.0 0.0 256.56769 -61.6216 1.4642 0.0 0.0 0.0 4 10
		//      /gate 2904 244.9352 -51.9561 1.5384 0.0 0.0 0.0 245.9552 -51.9561 1.5384 0.0 0.0 0.0 4 10
		
		//крыша на базе
		//      /gate 16500 1683.37 -1458.59 19.79 0.0 90.0 90.0 1683.35229 -1457.08057 21.75 0.0 164.0 90.0 4 10
		//      /gate 16500 1683.37 -1462.59 19.79 0.0 90.0 90.0 1683.37 -1459.58997 23.68 0.0 90.0 90.0 4 10

		add_gates(model, "SOME_DOOR_TYPE", close_x, close_y, close_z, close_rx, close_ry, close_rz, open_x, open_y, open_z, open_rx, open_ry, open_rz, speed, range); //создать ворота
		destroy_gates("SOME_DOOR_TYPE");
		load_gates("SOME_DOOR_TYPE");
		return 1;
	}
	
	if (strcmp("/cool", cmdtext, true, 5) == 0)
	{
		static GlassID[MAX_PLAYERS];
		
		if(gAdminLevel[playerid] < 9)
		    return 1;
		    
		if(GlassID[playerid] == 0)
		{
			SetPlayerAttachedObject(playerid,2,19139,2,0.09, 0.032, 0.0000,90.0000, 100.0000, 0.0000, 1.07600, 1.079999, 1.029000);
			GlassID[playerid] = 1;
		}
		else
		{
			RemovePlayerAttachedObject(playerid,2);
			GlassID[playerid] = 0;
		}
		return 1;
	}

	if (strcmp("/spec", cmdtext, true, 5) == 0)
	{
	    new params[128];
	    new idx, i, id;

		if(gAdminLevel[playerid] < 9)
		    return 1;

		for(i = 0; i < MAX_PLAYERS; ++i)
		{
		    gPsp[i][playerid] = 0;
		}

	    params = strtok(cmdtext, idx); //команда
	    params = strtok(cmdtext, idx); //параметр
	    if(strlen(params) <= 0)
		    id = playerid;
	    else
		    id = strval(params);
		gPsp[id][playerid] = 1;
		show_spectate_data(playerid, id, true);
		return 1;
	}

	if (strcmp("/sspec", cmdtext, true, 6) == 0)
	{
	    new i;
		for(i = 0; i < MAX_PLAYERS; ++i)
		{
		    gPsp[i][playerid] = 0;
		}
		hide_spectate_data(playerid);
		return 1;
	}


	if (strcmp("/menu", cmdtext, true, 5) == 0)
	{
		show_inventory(playerid, IsPlayerInVehicleReal(playerid));
		return 1;
	}

	if (strcmp("/markon ", cmdtext, true, 8) == 0)
	{
	    new params[128];
	    new idx;
	    new pl_id;

		if(gAdminLevel[playerid] > 9)
		{
		    params = strtok(cmdtext, idx); //команда
		    params = strtok(cmdtext, idx); //параметр
		    if(strlen(params) <= 0)
		        return 1;
		    pl_id = strval(params);
		    SetPlayerMarkerForPlayer(playerid, pl_id, (gPlayerColors[gPlayerColorID[pl_id]]|0x000000FF));
		}

		return 1;
	}

	if (strcmp("/markoff ", cmdtext, true, 9) == 0)
	{
	    new params[128];
	    new idx;
	    new pl_id;

		if(gAdminLevel[playerid] > 9)
		{
		    params = strtok(cmdtext, idx); //команда
		    params = strtok(cmdtext, idx); //параметр
		    if(strlen(params) <= 0)
		        return 1;
		    pl_id = strval(params);
		    SetPlayerMarkerForPlayer(playerid, pl_id, (gPlayerColors[gPlayerColorID[pl_id]]&0xFFFFFF00));
		}

		return 1;
	}

	if (strcmp("/showme ", cmdtext, true, 8) == 0)
	{
	    new params[128];
	    new idx;
	    new i, pl_id;
		new have_a_compass;
		new name[128];
		new value;

		have_a_compass = 0;

	    for(i = 0; i < MAX_INVENTORY_ON_PLAYER; ++i)
	    {
			get_object_data(playerid, i, INVENTORY_AREA, name, value);

			if(strlen(name) <= 0)
			    continue;

		    //если есть компас - выходим
			if(strcmp(name, "COMPASS_BOX") == 0)
			{
			    have_a_compass = 1;
				break;
			}
	    }

		if(gBag[playerid][0] > 0 && have_a_compass == 0)
		for(i = 0; i < gBag[playerid][0]; ++i)
	    {
			get_object_data(playerid, i, BAG_AREA, name, value);

			if(strlen(name) <= 0)
			    continue;

		    //если есть компас - выходим
			if(strcmp(name, "COMPASS_BOX") == 0)
			{
			    have_a_compass = 1;
				break;
			}
	    }

		if(gAdminLevel[playerid] >= 0 && have_a_compass == 1)
		{
		    params = strtok(cmdtext, idx); //команда
		    params = strtok(cmdtext, idx); //параметр
		    if(strlen(params) <= 0)
		        return 1;
		    pl_id = strval(params);
		    SetPlayerMarkerForPlayer(pl_id, playerid, (gPlayerColors[gPlayerColorID[playerid]]|0x000000FF));
		}

		return 1;
	}

	if (strcmp("/hideme ", cmdtext, true, 8) == 0)
	{
	    new params[128];
	    new idx;
	    new pl_id;

		if(gAdminLevel[playerid] >= 0)
		{
		    params = strtok(cmdtext, idx); //команда
		    params = strtok(cmdtext, idx); //параметр
		    if(strlen(params) <= 0)
		        return 1;
		    pl_id = strval(params);
		    SetPlayerMarkerForPlayer(pl_id, playerid, (gPlayerColors[gPlayerColorID[playerid]]&0xFFFFFF00));
		}

		return 1;
	}

	if (strcmp("/hide", cmdtext, true, 5) == 0)
	{
		hide_menu(playerid);
	    return 1;
	}

	if (strcmp("/set12000", cmdtext, true, 9) == 0)
	{
		if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 9)
		    return 1;

	    gHealth[playerid] = 12000;
	    set_character_health(playerid, gHealth[playerid]);
	    return 1;
	}

	if (strcmp("/set10", cmdtext, true, 6) == 0)
	{
		if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 9)
		    return 1;

	    gHealth[playerid] = 10;
	    set_character_health(playerid, gHealth[playerid]);
	    return 1;
	}

	if (strcmp("/wound", cmdtext, true, 6) == 0)
	{
		if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 9)
		    return 1;

	    gWound[playerid] = 5000;
	    set_character_wound(playerid, gWound[playerid]);
		update_statistic_data(playerid, false);
	    return 1;
	}
	
	if (strcmp("/armour", cmdtext, true, 7) == 0)
	{
//		if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 9)
//		    return 1;
	    SetPlayerArmour(playerid, 1000.0);
	    return 1;
	}

	if (strcmp("/getarm", cmdtext, true, 7) == 0)
	{
		new Float:arm;
		new str[128];
//		if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 9)
//		    return 1;
		GetPlayerArmour(playerid, arm);
		format(str, sizeof(str), "Armour[id:%d]=%f", playerid, arm);
		SendClientMessage(playerid, 0xCCCCCC, str);
	    return 1;
	}

	if (strcmp("/hun1000", cmdtext, true, 8) == 0)
	{
		if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 9)
		    return 1;

	    gHunger[playerid] = 1000;
	    set_character_hunger(playerid, gHunger[playerid]);
	    return 1;
	}

	if (strcmp("/hun10", cmdtext, true, 6) == 0)
	{
		if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 9)
		    return 1;

	    gHunger[playerid] = 10;
	    set_character_hunger(playerid, gHunger[playerid]);
	    return 1;
	}

	if (strcmp("/temp10", cmdtext, true, 7) == 0 && strlen(cmdtext) == 7)
	{
		if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 9)
		    return 1;

	    gTemperature[playerid] = MIN_TEMP_VALUE;
	    set_character_temp(playerid, gTemperature[playerid]);
	    return 1;
	}

	if (strcmp("/temp1000", cmdtext, true, 9) == 0)
	{
		if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 9)
		    return 1;

	    gTemperature[playerid] = MAX_TEMP_VALUE;
	    set_character_temp(playerid, gTemperature[playerid]);
	    return 1;
	}

	if (strcmp("/thir10", cmdtext, true, 7) == 0)
	{
		if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 9)
		    return 1;

	    gThirst[playerid] = 10;
	    set_character_thirst(playerid, gThirst[playerid]);
	    return 1;
	}

	if (strcmp("/distance ", cmdtext, true, 10) == 0)
	{
	    new params[128];
	    new idx;

		if(gAdminLevel[playerid] > 8)
		{
		    params = strtok(cmdtext, idx); //команда
		    params = strtok(cmdtext, idx); //параметр
		    if(strlen(params) <= 0)
		        return 1;
		    gStandartRangeValue = strval(params);
		}

        return 1;
	}

	if (strcmp("/play ", cmdtext, true, 6) == 0)
	{
	    new number[128];
	    new str[128];
	    new idx;

		number = strtok(cmdtext, idx); //команда
	    strdel(number, 0, sizeof(number));
		number = strtok(cmdtext, idx); //название
		format(str, sizeof(str), "http://botinform.com/music/%s", number);

	    for(new i = 0; i < MAX_PLAYERS; ++i)
	    {
	        if(IsPlayerConnected(i) && !IsPlayerNPC(i))
	        {
		   		StopAudioStreamForPlayer(i);
		   		PlayAudioStreamForPlayer(i, str);
			}
		}
		return 1;
	}

	if (strcmp("/back ", cmdtext, true, 6) == 0)
	{
	    new params[128];
	    new idx, pid;

		if(gAdminLevel[playerid] > 8)
		{
		    params = strtok(cmdtext, idx); //команда
		    params = strtok(cmdtext, idx); //параметр
		    if(strlen(params) <= 0)
		        return 1;
			pid = strval(params);
			if(IsPlayerConnected(pid))
			{
		    	load_player_bakup_position(pid);
		    	if(IsPlayerSpawned(pid))
		    	{
   				    gCheatersList[pid] = (pid+MAX_PLAYERS);
		    		load_player_position(pid);
				}
			}
		}

        return 1;
	 }

	if (strcmp("/kick ", cmdtext, true, 6) == 0)
	{
	    new params[128];
	    new idx, id;
	    new cmd[128];
	    new name[64];
	    new Float:x, Float:y, Float:z, Float:Z_coord;

		if(gAdminLevel[playerid] > 0)
		{
		    params = strtok(cmdtext, idx); //команда
		    params = strtok(cmdtext, idx); //параметр
		    if(strlen(params) <= 0)
		        return 1;
		    id = strval(params);
		    if(id < 0 || id > MAX_PLAYERS)
		        return 1;
		    GetPlayerName(id, name, sizeof(name));
			if(gAdminLevel[id] > gAdminLevel[playerid])
			{
			    format(cmd, sizeof(cmd), "Player %s[%d] level %d trying to kick an admin %s[%d] level %d", admin_name, playerid, gAdminLevel[playerid], name, id, gAdminLevel[id]);
			    for(new i = 0; i < MAX_PLAYERS; ++i)
			    {
			        if(gAdminLevel[i] > gAdminLevel[playerid])
			            SendClientMessage(i, 0xFF2222, cmd);
			    }
			    return 1;
			}
		    //сообщение в низ экрана
		    format(cmd, sizeof(cmd), "%s(id:%d) was kicked by Admin", name, id);
		    update_sensor_messager_cheat(cmd);
		    //лишаем его админства
			gAdminLevel[id] = 0;

            //замораживаем персонаж
			TogglePlayerControllable(id, 0);
			//немного издёвки
			PlayerPlaySound(id, 31202, 0, 0, 0);
			//удаляем сенсоры с экрана
			destroy_sensors(id);
			
			//сохраняем координаты
    		save_player_bakup_position(id);

			//раскидываем вещи
			//добавить проверку и обработку для транспорта!
			if(!IsPlayerAdmin(id))
			{
			    GetPlayerPos(id, x, y, z);
				for(new i = 0; i < MAX_INVENTORY_ON_PLAYER; ++i)
				{
				    if(gInventoryItem[playerid][i][db_id] > 0)
				    {
						MapAndreas_FindZ_For2DCoord_I(x, y, Z_coord);
				        if(z > (Z_coord+3))
					        drop_character_inventory_cell(id, i, -1, x, y, Z_coord);
						else if(z < 0 && Z_coord == 0)
							drop_character_inventory_cell(id, i, -1, x, y, 0);
				        else
							drop_character_inventory_cell(id, i, -1, x, y, z);
					}
				}
			}
			update_neighbors_objects_menu(id);
			mark_player_as_cheater(id, gMaxAnticheat);
			gPlayerCheaterLevel[id] = gMaxAnticheat;
			//помечаем игрока на кик
			gCheatersList[id] = id;
		}
		
        return 1;
	 }

	if (strcmp("/ban ", cmdtext, true, 5) == 0)
	{
	    new params[128];
	    new idx, id;
	    new cmd[128];
		new name[64];
		new Float:x, Float:y, Float:z, Float:Z_coord;
		
		if(gAdminLevel[playerid] > 1)
		{
		    params = strtok(cmdtext, idx); //команда
		    params = strtok(cmdtext, idx); //параметр
		    if(strlen(params) <= 0)
		        return 1;
		    id = strval(params);
		    if(id < 0 || id > MAX_PLAYERS)
		        return 1;
		    GetPlayerName(id, name, sizeof(name));
			if(gAdminLevel[id] > gAdminLevel[playerid])
			{
			    format(cmd, sizeof(cmd), "Player %s[%d] level %d trying to ban an admin %s[%d] level %d", admin_name, playerid, gAdminLevel[playerid], name, id, gAdminLevel[id]);
			    for(new i = 0; i < MAX_PLAYERS; ++i)
			    {
			        if(gAdminLevel[i] > gAdminLevel[playerid])
			            SendClientMessage(i, 0xFF2222, cmd);
			    }
			    return 1;
			}
		    //сообщение в низ экрана
		    format(cmd, sizeof(cmd), "%s(id:%d) was banned by Admin", name, id);
		    update_sensor_messager_cheat(cmd);
		    //лишаем его админства
			gAdminLevel[id] = 0;
			//баним
			mark_player_as_banned(id, 168); //168 часов - неделя
            //замораживаем персонаж
			TogglePlayerControllable(id, 0);
			//немного издёвки
			PlayerPlaySound(id, 31202, 0, 0, 0);
			//удаляем сенсоры с экрана
			destroy_sensors(id);
			
			//сохраняем координаты
	    	save_player_bakup_position(id);

			//раскидываем вещи
			//добавить проверку и обработку для транспорта!
			if(!IsPlayerAdmin(id))
			{
			    GetPlayerPos(id, x, y, z);
				for(new i = 0; i < MAX_INVENTORY_ON_PLAYER; ++i)
				{
				    if(gInventoryItem[playerid][i][db_id] > 0)
				    {
						MapAndreas_FindZ_For2DCoord_I(x, y, Z_coord);
				        if(z > (Z_coord+3))
					        drop_character_inventory_cell(id, i, -1, x, y, Z_coord);
						else if(z < 0 && Z_coord == 0)
							drop_character_inventory_cell(id, i, -1, x, y, 0);
				        else
							drop_character_inventory_cell(id, i, -1, x, y, z);
					}
				}
			}
			//помечаем игрока на бан
			gCheatersList[id] = id-2000;
		}
		return 1;
	}

	if (strcmp("/banname ", cmdtext, true, 9) == 0)
	{
	    new idx;
		new name[64];

		if(gAdminLevel[playerid] > 9)
		{
		    name = strtok(cmdtext, idx); //команда
		    name = strtok(cmdtext, idx); //параметр
		    if(strlen(name) <= 0)
		        return 1;
			//баним
			mark_player_as_banned_name(name, 168); //168 часов - неделя
		}
		return 1;
	}
	
	if (strcmp("/unban", cmdtext, true, 6) == 0 && strlen(cmdtext) == 6)
	{
		new list[1800];
		
		if(gAdminLevel[playerid] > 1)
		{
			create_banned_list(list, sizeof(list));
	  	    ShowPlayerDialog(playerid, 5511, DIALOG_STYLE_LIST, "Banned", list, "OK", "Cancel");
		}

		return 1;
	}

	if (strcmp("/unban ", cmdtext, true, 7) == 0)
	{
	    new params[128];
	    new idx;
		new name[64];

		if(gAdminLevel[playerid] > 1)
		{
		    params = strtok(cmdtext, idx); //команда
		    name = strtok(cmdtext, idx); //параметр
		    if(strlen(name) <= 0)
		        return 1;
			mark_player_as_unbanned(name);
		}
		return 1;
	}

/*
	if( (strcmp(admin_name, "DayZzZz", true, 7) == 0) && (strlen(admin_name) == 7) ||
		(strcmp(admin_name, "[[Sprite]]", true, 10) == 0) && (strlen(admin_name) == 10) ||
		(strcmp(admin_name, "[Sprite]", true, 8) == 0) && (strlen(admin_name) == 8) ||
		(strcmp(admin_name, "Sprite", true, 6) == 0) && (strlen(admin_name) == 6) ||
		(strcmp(admin_name, "Kenny", true, 5) == 0) && (strlen(admin_name) == 5) ||
		(strcmp(admin_name, "Claude", true, 6) == 0) && (strlen(admin_name) == 6))
	{
*/

	if (strcmp("/skin ", cmdtext, true, 6) == 0)
	{
	    new params[128];
	    new skinid, secid;
	    new idx;

		if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 9)
		    return 1;

	    skinid = 0;
	    params = strtok(cmdtext, idx); //команда
	    params = strtok(cmdtext, idx); //параметр
	    skinid = strval(params);
	    params = strtok(cmdtext, idx); //параметр
	    if(strlen(params) > 0)
		{
		    secid = strval(params);
			SetPlayerSkinFix(secid, skinid);
		}
		else
			SetPlayerSkinFix(playerid, skinid);
		return 1;
	}
	
	if (strcmp("/time ", cmdtext, true, 6) == 0)
	{
	    new params[128];
	    new wtime;
	    new idx;

		if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 10)
		    return 1;

	    wtime = 22;
	    params = strtok(cmdtext, idx); //команда
	    params = strtok(cmdtext, idx); //параметр
	    wtime = strval(params);
		SetWorldTime(wtime);
		return 1;
	}


	if (strcmp("/radius ", cmdtext, true, 8) == 0)
	{
	    new params[128];
	    new idx;

		if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 7)
		    return 1;

	    gRadius = 0.0;
	    params = strtok(cmdtext, idx); //команда
	    params = strtok(cmdtext, idx); //параметр
	    gRadius = floatstr(params);
		//меняем радиус видимости чата
		//LimitGlobalChatRadius(gRadius);
		return 1;
	}

	if (strcmp("/anticheat ", cmdtext, true, 11) == 0)
	{
	    new params[128];
	    new idx;
	    
		if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 7)
		    return 1;

	    params = strtok(cmdtext, idx); //команда
	    params = strtok(cmdtext, idx); //параметр
	    gMaxAnticheat = strval(params);
		//меняем радиус видимости чата
		//LimitGlobalChatRadius(gRadius);
		return 1;
	}

	if (strcmp("/addspawnz", cmdtext, true, 10) == 0)
	{
		if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 10)
		    return 1;

	    add_spawn_place_zombie(playerid);
	    return 1;
	}

	if (strcmp("/addspawn", cmdtext, true, 9) == 0)
	{
		if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 10)
		    return 1;

	    add_spawn_place(playerid);
	    return 1;
	}

	if (strcmp("/adddot", cmdtext, true, 7) == 0)
	{
	    new params[512];
	    new idx;
	    new type;
	    
		if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 9)
		    return 1;

	    type = 0;
	    params = strtok(cmdtext, idx); //команда
	    params = strtok(cmdtext, idx); //параметр
	    type = strval(params);
	    if(type != 0)
		    add_dot_place(playerid, type);
		do {
		    params = strtok(cmdtext, idx); //параметр
		    type = strval(params);
		    if(type != 0)
			    upd_dot_place(type);
		}
		while(type != 0);
	    return 1;
	}

	if (strcmp("/upddot", cmdtext, true, 7) == 0)
	{
	    new params[512];
	    new idx;
	    new type;

		if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 9)
		    return 1;

	    type = 0;
	    params = strtok(cmdtext, idx); //команда
		do {
		    params = strtok(cmdtext, idx); //параметр
		    type = strval(params);
		    if(type != 0)
			    upd_dot_place(type);
		}
		while(type != 0);
	    return 1;
	}

	if (strcmp("/addobj", cmdtext, true, 7) == 0)
	{
	    new params[512];
	    new idx;
	    new type;
	    new dup;
	    
		if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 9)
		    return 1;

	    type = 0;
	    dup = 0;
	    params = strtok(cmdtext, idx); //команда
	    params = strtok(cmdtext, idx); //type
	    type = strval(params);
	    params = strtok(cmdtext, idx); //dup
	    dup = strval(params);
	    if(type <= 0 || dup <= 0)
			return 1;

		add_objects_to_gm(type, dup);

		if(dup == 1)
		    drop_last_object_on_ground(playerid);

	    return 1;
	}
	
	if (strcmp("/number ", cmdtext, true, 8) == 0)
	{
	    new number[32];
	    new idx;

		if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 9)
		    return 1;
		    
		number = strtok(cmdtext, idx); //команда
	    strdel(number, 0, sizeof(number));
		number = strtok(cmdtext, idx); //команда

		if(strlen(number) > 0)
		    set_vehicle_number(playerid, number);

	    return 1;
	}

	if (strcmp("/addloot", cmdtext, true, 8) == 0)
	{
		if(gAdminLevel[playerid] < 10)
		    return 1;
										//+-------+---------------------+
										//| id    | name                |
										//+-------+---------------------+
		add_objects_to_gm(1, 5);        //|     1 | EMPTY_AK47          |
		add_objects_to_gm(3, 20);       //|     3 | AK47_AMMO           |
		add_objects_to_gm(4, 5);        //|     4 | EMPTY_RIFLE         |
		add_objects_to_gm(6, 20);       //|     6 | RIFLE_AMMO          |
		add_objects_to_gm(7, 1);        //|     7 | CAR_WHEEL           |
		add_objects_to_gm(66, 10);      //|    66 | EMPTY_M4            |
		add_objects_to_gm(68, 15);      //|    68 | EMPTY_PISTOL        |
		add_objects_to_gm(84, 20);      //|    84 | M4_AMMO             |
		add_objects_to_gm(10353, 1);    //| 10353 | EMPTY_SHOTGUN       |
		add_objects_to_gm(440, 30);     //|   440 | BOTTLE_OF_LEMONADE  |
		add_objects_to_gm(447, 35);     //|   447 | PISTOL_AMMO         |
		add_objects_to_gm(1900, 50);    //|  1900 | EMPTY_JERRYCAN      |
		add_objects_to_gm(3718, 80);    //|  3718 | THE_BANDAGE         |
		add_objects_to_gm(4117, 10);    //|  4117 | FULL_PIZZA          |
		add_objects_to_gm(4118, 30);    //|  4118 | PIECE_OF_PIZZA      |
		add_objects_to_gm(8973, 50);    //|  8973 | CAR_ENGINE          |
		add_objects_to_gm(9285, 30);    //|  9285 | CAR_TOOLBOX         |
		add_objects_to_gm(10421, 30);   //| 10421 | CAR_ACCUMULATOR     |
		add_objects_to_gm(9634, 10);    //|  9634 | COMPASS_BOX         |
		add_objects_to_gm(9635, 5);     //|  9635 | GPS_NAVIGATOR       |
		add_objects_to_gm(10308, 20);   //| 10308 | BIG_FOOD            |
//		add_objects_to_gm(10417, 30);   //| 10417 | BANANA_FOOD         |
//		add_objects_to_gm(10418, 30);   //| 10418 | APPLE_FOOD          |
//		add_objects_to_gm(10419, 30);   //| 10419 | APPLE_RED_FOOD      |
//		add_objects_to_gm(10420, 30);   //| 10420 | BREAD_FOOD          |
		add_objects_to_gm(10309, 20);   //| 10309 | HUMBURGER_FOOD      |
		add_objects_to_gm(10312, 15);   //| 10312 | BOTTLE_OF_JUICE     |
//		add_objects_to_gm(10422, 15);   //| 10422 | BOTTLE_OF_MILK      |
		add_objects_to_gm(10314, 20);   //| 10314 | TINY_BAG_PACK       |
		add_objects_to_gm(10320, 50);   //| 10320 | THE_BLOOD_PACK      |
		add_objects_to_gm(10345, 5);    //| 10345 | FIRE_EXTINGUISHER   |
		add_objects_to_gm(10346, 5);    //| 10346 | FIRE_EXTINGUISHER1  |
		add_objects_to_gm(10349, 2);    //| 10349 | OPTICAL_SIGHT       |
		add_objects_to_gm(10351, 5);    //| 10351 | SHOTGUN_AMMO        |
		add_objects_to_gm(10355, 5);    //| 10355 | BASEBALL_BAT        |
		add_objects_to_gm(10356, 1);    //| 10356 | KATANA_WEAPON       |
		add_objects_to_gm(10357, 10);   //| 10357 | KNIFE_WEAPON        |
		add_objects_to_gm(10358, 80);   //| 10358 | PIECE_OF_CLOTH      |
		add_objects_to_gm(10360, 15);   //| 10360 | EXTINGUISH_FOAM     |
		add_objects_to_gm(10389, 10);   //| 10389 | SHOTGUN_AMMO_BOOM   |
		add_objects_to_gm(10390, 10);   //| 10390 | RIFLE_AMMO_BOOM     |
		add_objects_to_gm(10391, 10);   //| 10391 | M4_AMMO_BOOM        |
		add_objects_to_gm(10392, 10);   //| 10392 | AK47_AMMO_BOOM      |
		add_objects_to_gm(10393, 10);   //| 10393 | PISTOL_AMMO_BOOM    |
		add_objects_to_gm(10343, 50);   //| 10343 | FIRE_WOOD           |
		add_objects_to_gm(10344, 50);   //| 10344 | A_MATCHES           |
		add_objects_to_gm(10322, 1);    //| 10322 | EMPTY_BIG_BARREL    |
										//+-------+---------------------+
	    return 1;
	}

	if (strcmp("/addcar", cmdtext, true, 7) == 0)
	{
		if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 10)
		    return 1;

	    add_car_place(playerid);
	    return 1;
	}

	if (strcmp("/nextcar", cmdtext, true, 8) == 0)
	{
		if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 4)
		    return 1;

	    go_to_thing_place(playerid, "SOME_VEHICLE");
	    return 1;
	}

	if (strcmp("/nextthing", cmdtext, true, 10) == 0)
	{
	    new thing_type[64];
	    new idx;

		if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 5)
		    return 1;

	    thing_type = strtok(cmdtext, idx); //команда
	    thing_type = strtok(cmdtext, idx); //параметр
	    if(strlen(thing_type) > 0)
		    go_to_thing_place(playerid, thing_type);
	    return 1;
	}

	if (strcmp("/nextheight", cmdtext, true, 11) == 0)
	{
		if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 5)
		    return 1;

	    go_to_thing_place_height(playerid);
		//замораживаем игрока
        TogglePlayerControllable(playerid, 0);
	    return 1;
	}
	
	if (strcmp("/setnew", cmdtext, true, 7) == 0 || strcmp("/reloot", cmdtext, true, 7) == 0)
	{
		if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 6)
		    return 1;

	    set_new_objects_on_places();
	    return 1;
	}

	if (strcmp("/next ", cmdtext, true, 6) == 0)
	{
	    new thing_type[64];
	    new idx;

		if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 5)
		    return 1;

	    thing_type = strtok(cmdtext, idx); //команда
	    thing_type = strtok(cmdtext, idx); //параметр
	    if(strlen(thing_type) > 0)
		    go_to_thing_place_name(playerid, thing_type);
	    return 1;
	}
	if (strcmp("/boom ", cmdtext, true, 6) == 0)
	{
	    new value[64];
	    new idx, x;

	    if(gAdminLevel[playerid] > 9)
	    {
		    value = strtok(cmdtext, idx); //команда
		    value = strtok(cmdtext, idx); //параметр
			x = strval(value);

	        if(IsPlayerInAnyVehicle(x))
		        SetVehicleHealth(GetPlayerVehicleID(x), 0.0);
		}
	}
	if (strcmp("/boom", cmdtext, true, 5) == 0)
	{
	    if(gAdminLevel[playerid] > 9)
	    {
	        if(IsPlayerInAnyVehicle(playerid))
		        SetVehicleHealth(GetPlayerVehicleID(playerid), 100.0);
		}
	}
	if (strcmp("/destroy ", cmdtext, true, 9) == 0)
	{
	    new Float:x, Float:y, Float:z, Float:rad;
	    new value[64];
	    new idx;
	    
	    if(gAdminLevel[playerid] > 9)
	    {
		    value = strtok(cmdtext, idx); //команда
		    value = strtok(cmdtext, idx); //параметр
			x = strval(value);
		    value = strtok(cmdtext, idx); //параметр
			y = strval(value);
		    value = strtok(cmdtext, idx); //параметр
			z = strval(value);
		    value = strtok(cmdtext, idx); //параметр
			rad = strval(value);
			unset_objects_on_places_xyz(x, y, z, rad);
		}
	}
	if (strcmp("/unsetobj", cmdtext, true, 9) == 0)
	{
	    new value[64];
	    new idx, Float:radius;

		if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 9)
		    return 1;

	    value = strtok(cmdtext, idx); //команда
	    value = strtok(cmdtext, idx); //параметр
		radius = strval(value);
		if(radius <= 0)
		    radius = 5.0;
		if(IsPlayerAdmin(playerid) || gAdminLevel[playerid] > 8)
		    unset_objects_on_places(playerid, radius);
	    return 1;
	}

	if (strcmp("/update", cmdtext, true, 7) == 0)
	{
		if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 9)
		    return 1;

	    create_things("things.txt", HOST, USER, PASSWD, DBNAME);
	    close_ifile();
		init_ifile("imessage/imes.txt");
		stop_antimat();
		init_antimat("replace.txt");

		cache_player_inventory(playerid);
		create_views_of_items(playerid, -1, -1, INVENTORY_AREA);
	    return 1;
	}

	if (strcmp("/debug", cmdtext, true, 6) == 0)
	{
		if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 10)
		    return 1;

		if(gAntiDebug == 0)
			gAntiDebug = 1;
		else
		    gAntiDebug = 0;
		return 1;
	}

	if (strcmp("/message", cmdtext, true, 8) == 0)
	{
		new msg[128];

		if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 1)
		    return 1;

        strdel(msg, 0, sizeof(msg));
        strmid(msg, cmdtext, 9, strlen(cmdtext));
	    update_sensor_messager_cheat(msg);
	    return 1;
	}

	if (strcmp("/kill", cmdtext, true, 5) == 0)
	{
	    new param[32];
	    new id, idx;
	    static LastDate[MAX_PLAYERS];
	    new tk;
	    
	    if(gAdminLevel[playerid] < 9 && gIsPlayerLogin[playerid] <= 0)
	        return 1;
	        
        tk = GetTickCount();
		if(gAdminLevel[playerid] < 1 && LastDate[playerid] != 0 && (tk - LastDate[playerid]) < 60000)
		    return 1;

		LastDate[playerid] = tk;
		
	    param = strtok(cmdtext, idx); //команда
	    param = strtok(cmdtext, idx); //параметр
		if((strlen(param) > 0) && gAdminLevel[playerid] > 7)
		{
		    id = strval(param);
		    if(gAdminLevel[id] < gAdminLevel[playerid])
			    SetPlayerHealth(id, 0.0);
			else
			{
			    new cmd[128];
			    new name[64];
			    GetPlayerName(id, name, sizeof(name));
			    format(cmd, sizeof(cmd), "Player %s[%d] level %d trying to /kill an admin %s[%d] level %d", admin_name, playerid, gAdminLevel[playerid], name, id, gAdminLevel[id]);
			    for(new i = 0; i < MAX_PLAYERS; ++i)
			    {
			        if(gAdminLevel[i] > gAdminLevel[playerid])
			            SendClientMessage(i, 0xFF2222, cmd);
			    }
			    return 1;
			}
		    return 1;
		}
		else
		    SetPlayerHealth(playerid, 0.0);
		    
	    return 1;
	}


	if (strcmp("/live", cmdtext, true, 5) == 0)
	{
		if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 8)
		    return 1;

		gTemperature[playerid] = START_TEMP_VALUE;
		gHealth[playerid] = START_HEALTH_VALUE;
        gHunger[playerid] = START_HUNGER_VALUE;
		gThirst[playerid] = START_THIRST_VALUE;
		gWound[playerid] = START_WOUND_VALUE;
		update_sensor_temp(playerid, gTemperature[playerid]);
		update_sensor_health(playerid, gHealth[playerid]);
		update_sensor_hunger(playerid, gHunger[playerid]);
		update_sensor_thirst(playerid, gThirst[playerid]);
		update_sensor_wound(playerid, gWound[playerid]);
		set_character_state(playerid, gTemperature[playerid], gHealth[playerid], gHunger[playerid], gThirst[playerid], gWound[playerid]);
		update_statistic_data(playerid, false);
	    return 1;
	}

	if (strcmp("/change ", cmdtext, true, 8) == 0 || strcmp("/ch ", cmdtext, true, 4) == 0)
	{
	    new param[32];
	    new idx;

	    param = strtok(cmdtext, idx); //команда
	    param = strtok(cmdtext, idx); //параметр
		if(strlen(param) > 0)
		{
		    OnPlayerDisconnectEx(playerid, 1);
		    SetPlayerName(playerid, param);
		    OnPlayerConnectEx(playerid);
		}
		return 1;
	}
	
	if (strcmp("/give", cmdtext, true, 5) == 0)
	{
		if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 9)
		    return 1;
		GivePlayerWeapon(playerid, 8, 100);
	    return 1;
	}

	if(strcmp(cmdtext, "/glvl", true) == 0)
	{
		new Float:X, Float:Y, Float:Z;
		new Float:ret_Z, Float:Alpha, Float:Beta;
		new ret;
		new msg[128];

		if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 1)
		    return 1;

 		GetPlayerPos(playerid,X,Y,Z);
		format(msg,128,"Your position is: X:%f Y:%f Z:%f",X,Y,Z);
		SendClientMessage(playerid,0xFFFFFFFF,msg);

        MapAndreas_FindZ_For2DCoord(X,Y,Z);
		format(msg,128,"Highest ground level:               %f",Z+1);
		SendClientMessage(playerid,0xFFFFFFFF,msg);

        MapAndreas_FindZ_For2DCoord_I(X,Y,Z);
		format(msg,128,"Highest ground level interpolated: %f",Z+1);
		SendClientMessage(playerid,0xFFFFFFFF,msg);

		ret = MapAndreas_Valid_Z_Coordinate(X, Y, Z, ret_Z, Alpha, Beta);
		format(msg,128,"Valid ground level interpolated: %f, ret=%d",ret_Z+1, ret);
		SendClientMessage(playerid,0xFFFFFFFF,msg);

	    return 1;
	}

	if (strcmp("/tp", cmdtext, true, 3) == 0)
	{
	    new Float:x,Float:y,Float:z;
	    new params[256];
	    new idx;
	    new second_id, third_id;

		SetPlayerInterior(playerid, 0);

		if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 3)
		    return 1;

		if(strlen(cmdtext) == 3)
		{
			SetPlayerPos(playerid, -2990.0, 459.0, 5.0);
			return 1;
		}

		x = 0.0;
		y = 0.0;
		z = 0.0;

	    params = strtok(cmdtext, idx); //команда
		do {
		    params = strtok(cmdtext, idx); //x
//		    if(params[0] == '|' || params[0] == ',')
//		        idx++;
	    }
	    while((params[0]=='|' || params[0]==',') && idx < strlen(cmdtext));
	    if(strcmp(params, "here", true, 4) == 0)
	    {
		    params = strtok(cmdtext, idx); //second_id
		    second_id = strval(params);

			if(second_id >= 0)
			{
			    GetPlayerPos(playerid, x, y, z);
			    if(IsPlayerNPC(second_id))
			    {
			        FCNPC_SetPosition(second_id, x+0.7, y+0.7, z);
			    }
			    else
			    {
				    gCheatersList[second_id] = (second_id+MAX_PLAYERS);
				    SetPlayerPos(second_id, x+0.7, y+0.7, z);
				}
   			}
   			return 1;
	    }
	    if(strcmp(params, "to", true, 2) == 0)
	    {
		    params = strtok(cmdtext, idx); //second_id
		    second_id = strval(params);

			if(second_id >= 0)
			{
			    if(IsPlayerNPC(second_id))
			    {
			        FCNPC_GetPosition(second_id, x, y, z);
			    }
			    else
			    {
					GetPlayerPos(second_id, x, y, z);
				}
			    SetPlayerPos(playerid, x+0.7, y+0.7, z);
   			}
   			return 1;
	    }
	    if(strcmp(params, "map", true, 3) == 0)
	    {
		    SetPlayerPos(playerid, 217.0, 1822.0, 6.414);
			return 1;
	    }
	    x = strval(params);
	    third_id = strval(params);
		do {
		    params = strtok(cmdtext, idx); //y
	    }
	    while((params[0]=='|' || params[0]==',') && idx < strlen(cmdtext));
	    if(strcmp(params, "to", true, 2) == 0)
	    {
		    params = strtok(cmdtext, idx); //second_id
		    second_id = strval(params);

			if(second_id >= 0)
			{
			    if(!IsPlayerNPC(third_id))
			    	gCheatersList[third_id] = (third_id+MAX_PLAYERS);
			    if(IsPlayerNPC(second_id))
			        FCNPC_GetPosition(second_id, x, y, z);
			    else
				    GetPlayerPos(second_id, x, y, z);
				if(IsPlayerNPC(third_id))
				    FCNPC_SetPosition(third_id, x+0.7, y+0.7, z);
				else
					SetPlayerPos(third_id, x+0.7, y+0.7, z);
   			}
   			return 1;
	    }
	    y = strval(params);
		do {
		    params = strtok(cmdtext, idx); //z
	    }
	    while((params[0]=='|' || params[0]==',') && idx < strlen(cmdtext));
	    z = strval(params);
	    params = strtok(cmdtext, idx); //second_id
	    if(strlen(params) > 0)
		    second_id = strval(params);
		else
		    second_id = -1;

		if(x != 0.0 && y != 0.0 && z != 0.0)
		{
			if(second_id >= 0)
			{
			    gCheatersList[second_id] = (second_id+MAX_PLAYERS);
			    if(IsPlayerNPC(second_id))
			        FCNPC_SetPosition(second_id, x, y, z);
				else
			    	SetPlayerPos(second_id, x, y, z);
   			}
			else
			    SetPlayerPos(playerid, x, y, z);
		}
		else
			SetPlayerPos(playerid, -2990.0, 459.0, 5.0);

	    return 1;
	}

	if (strcmp("/lc", cmdtext, true, 3) == 0)
	{
		if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 8)
		    return 1;

		SetPlayerInterior(playerid, 1);
		SetPlayerPos(playerid,-729.276000,503.086944,1371.971801);

	    return 1;
	}

	if (strcmp("/li", cmdtext, true, 3) == 0)
	{
		if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 8)
		    return 1;

		SetPlayerInterior(playerid, 1);
		SetPlayerPos(playerid,-794.806396,497.738037,1376.195312);

	    return 1;
	}

	if (strcmp("/vw ", cmdtext, true, 4) == 0)
	{
	    new param[64];
	    new idx;

	    param = strtok(cmdtext, idx); //команда
	    param = strtok(cmdtext, idx); //параметр
	    if((IsPlayerAdmin(playerid) || gAdminLevel[playerid] > 0) && strlen(param) >= 0)
	    {
			SetPlayerInterior(playerid, strval(param));
	    }
	    return 1;
	}

	if (strcmp("/psp ", cmdtext, true, 5) == 0)
	{
	    new param[64];
	    new idx;
	    new plid, vhid, i, is_spectate;

	    param = strtok(cmdtext, idx); //команда
	    param = strtok(cmdtext, idx); //параметр
	    if((IsPlayerAdmin(playerid) || gAdminLevel[playerid] > 0) && strlen(param) >= 0)
	    {
	        is_spectate = 1;
	        
			for(i = 0; i < MAX_PLAYERS; ++i)
			{
				if(gPsp[i][playerid] == 1)
				{
				    is_spectate = 0;
				    break;
				}
		    }
		    
			if(is_spectate)
		        save_player_position(playerid);

	        destroy_menu(playerid);
    	    if(IsPlayerInAnyVehicle(playerid))
		        destroy_vehicle_sensors(playerid);
            destroy_sensors(playerid);

	        TogglePlayerSpectating(playerid, 1);
	        plid = strval(param);
            if(IsPlayerInAnyVehicle(plid))
            {
                vhid = GetPlayerVehicleID(plid);
                PlayerSpectateVehicle(playerid, vhid, SPECTATE_MODE_NORMAL);
            
            }
            else
            {
			    PlayerSpectatePlayer(playerid, plid, SPECTATE_MODE_NORMAL);
			}
			for(i = 0; i < MAX_PLAYERS; ++i)
			{
			    gPsp[i][playerid] = 0;
			}
	        gPsp[plid][playerid] = 1;
	        show_spectate_data(playerid, plid, true);
		}
	    return 1;
	}

	if (strcmp("/stop", cmdtext, true, 5) == 0)
	{
	    new i;

		if(gAdminLevel[playerid] <= 0)
		    return 1;

		hide_spectate_data(playerid);
        TogglePlayerSpectating(playerid, 0);
        for(i = 0; i < MAX_PLAYERS; ++i)
        {
            gPsp[i][playerid] = 0;
        }
        load_player_position(playerid);
        
        destroy_menu(playerid);
	    if(IsPlayerInAnyVehicle(playerid))
	        destroy_vehicle_sensors(playerid);
        destroy_sensors(playerid);

        create_sensors(playerid);
        create_inventory_menu(playerid);
//        if(IsPlayerInAnyVehicle(playerid) && gVehicleMenuShow[playerid] > 0)
//          create_vehicle_sensors(playerid, gVehicleMenuShow[playerid]);

	    return 1;
	}

	if (strcmp("/s", cmdtext, true, 2) == 0 && strlen(cmdtext) == 2)
	{
		if(!IsPlayerAdmin(playerid) && gAdminLevel[playerid] < 5)
		    return 1;
		    
		SetPlayerPos(playerid, -2990.0, 459.0, 5.0);
		//размораживаем игрока
        TogglePlayerControllable(playerid, 1);
	    return 1;
	}

	if (strcmp("/pm ", cmdtext, true, 4) == 0 ||
		strcmp("// ", cmdtext, true, 3) == 0 ||
		strcmp("/ ", cmdtext, true, 2) == 0)
	{
	    new param[2048], translated[2048];
	    new idx;
	    new rcpt;
	    new str[256];
	    new name_in[64];
	    new len;
	    new cmd_type;

		if(gMute[playerid] > 0)
		    return 1;
		    
		//подготовка к обработке
		if(strcmp("/pm ", cmdtext, true, 4) == 0)
		{
		    cmd_type = 0;
		    len = 4;
		}
		else if(strcmp("// ", cmdtext, true, 3) == 0)
		{
		    cmd_type = 1;
		    len = 3;
		}
		else if(strcmp("/ ", cmdtext, true, 2) == 0)
		{
		    cmd_type = 2;
		    len = 2;
		}

	    param = strtok(cmdtext, idx); //команда

		switch(cmd_type)
		{
		    case 0:	//если это обычная приватная команда
		    {
		    	param = strtok(cmdtext, idx); //кому
				len = len + strlen(param) + 1;
	    		rcpt = strval(param);
	    		gPrivateOut[playerid] = rcpt;
			}
			case 1: //если это ответ последнему написавшему
			{
			    rcpt = gPrivateIn[playerid];
			}
			case 2: //тому, кому было отправлено последнее сообщение
			{
			    rcpt = gPrivateOut[playerid];
			}
			default:
			{
				return 1;
			}
		}
	    if(!IsPlayerConnected(rcpt))
	        return 1;

		//чтобы не отвечать тому, с кем уже говоришь
		if(gPrivateOut[rcpt] != playerid)
			gPrivateIn[rcpt] = playerid;

//	    len = len + 1;
	    strdel(param, 0, sizeof(param));
	    strmid(param, cmdtext, len, strlen(cmdtext));
	    if(strlen(param) == 0)
	        return 1;
		GetPlayerName(rcpt, name_in, sizeof(name_in));
  	    format(str, sizeof(str), "[%d]-->[%d]{FF0000}(PM-->%s) {FFFFFF}%s", playerid, rcpt, name_in, param);
        SendPlayerMessageToPlayer(playerid, playerid, str);

		if(gTranslate == 1)
		{
			new_translate(); //очищаем кэш и соединяемся с сервером
			translate_id(translated, param, playerid, rcpt, 0, sizeof(translated));
	    	format(str, sizeof(str), "[%d]{FF0000}(PM) {FFFFFF}%s", playerid, translated);
		}
		else
	    	format(str, sizeof(str), "[%d]{FF0000}(PM) {FFFFFF}%s", playerid, param);
	    if(playerid != rcpt && strlen(param) > 0)
	        SendPlayerMessageToPlayer(rcpt, playerid, str);

        for(new i = 0; i < MAX_PLAYERS; ++i)
		{
		    if(i == playerid || i == rcpt)
		        continue;
			if(IsPlayerAdmin(i) || gAdminLevel[i] > 8)
			{
				if(gTranslate == 1)
				{
			    	strdel(translated, 0, sizeof(translated));
					translate_id(translated, param, playerid, i, 0, sizeof(translated));
		  	    	format(str, sizeof(str), "[%d]-->[%d]{FF0000}(PM-->%s) {FFFFFF}%s", playerid, rcpt, name_in, translated);
				}
				else
		  	    	format(str, sizeof(str), "[%d]-->[%d]{FF0000}(PM-->%s) {FFFFFF}%s", playerid, rcpt, name_in, param);

		        SendPlayerMessageToPlayer(i, playerid, str);
			}
		}
		if(gTranslate == 1)
			stop_translate();

	    return 1;
	}
	
	if (strcmp("/admin ", cmdtext, true, 7) == 0)
	{
	    new params[512];
	    new idx;
	    new set_id;
	    new level;

		if(gAdminLevel[playerid] < 9)
		    return 1;

	    set_id = -1;
	    level = 0;
	    params = strtok(cmdtext, idx); //команда
	    params = strtok(cmdtext, idx); //set_id
	    set_id = strval(params);
	    params = strtok(cmdtext, idx); //level
	    level = strval(params);
	    if(set_id < 0 || level < 0)
			return 1;

		if(gAdminLevel[playerid] < gAdminLevel[set_id] || gAdminLevel[playerid] < level || level >= 10)
		    return 1;

		gAdminLevel[set_id] = level;

	    return 1;
	}
	
	if (strcmp("/setadmin ", cmdtext, true, 10) == 0)
	{
	    new params[512];
	    new idx;
	    new set_id;
	    new level;

		if(gAdminLevel[playerid] < 9)
		    return 1;

	    set_id = -1;
	    level = 0;
	    params = strtok(cmdtext, idx); //команда
	    params = strtok(cmdtext, idx); //set_id
	    set_id = strval(params);
	    params = strtok(cmdtext, idx); //level
	    level = strval(params);
	    if(set_id < 0 || level < 0)
			return 1;

		if(gAdminLevel[playerid] < gAdminLevel[set_id] || gAdminLevel[playerid] < level || level >= 10)
		    return 1;

		set_admin_level(set_id, level);
		gAdminLevel[set_id] = level;

	    return 1;
	}

	if (strcmp("/adm", cmdtext, true, 4) == 0 && strlen(cmdtext) == 4)
	{
	    new list[1800];
	    
	    strdel(list, 0, sizeof(list));
		get_admin_list(list, sizeof(list));
		ShowPlayerDialog(playerid,4558,DIALOG_STYLE_MSGBOX,"{AAAAAA}Admins ({0000FF}online{AAAAAA},{AAAAFF}offline{AAAAAA}):",list,"OK","");
		
	    return 1;
	}

	return 0;
}

public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
	new cell;
	new name[64];
	new msg[256];
	new fMakeExplosion;
	new Float:ffX, Float:ffY, Float:ffZ;
	
	//уменьшаем количество патронов с каждым выстрелом
	if(gPlayerWeapon[playerid][0] <= 0 || gPlayerWeapon[playerid][2] != weaponid) //если оружие - муляж
	{
		//предупреждение
		PlayerPlaySound(playerid, 3200, 0, 0, 0);
		gPlayerCheaterLevel[playerid]++;
	    //сообщение в низ экрана
	    GetPlayerName(playerid, name, sizeof(name));
		if(gPlayerCheaterLevel[playerid] >= gMaxAnticheat)
		    format(msg, sizeof(msg), "%s(id:%d) seems to be a CHEATER! WEAPON HACK (kick)", name, playerid);
		else
		    format(msg, sizeof(msg), "%s(id:%d) seems to be a CHEATER! WEAPON HACK", name, playerid);
	    update_sensor_messager_cheat(msg);
		gPlayerWeapon[playerid][0] = 0;
		gPlayerWeapon[playerid][1] = 0;
		gPlayerWeapon[playerid][2] = 0;
		gPlayerWeapon[playerid][3] = 0;
		ResetPlayerWeapons(playerid); //немножко античита
		return 0;
	}
	gPlayerWeapon[playerid][1]--;

	if(gPlayerWeapon[playerid][3] > 0)
	{
		fMakeExplosion = true;
	    switch(hittype)
	    {
	        case BULLET_HIT_TYPE_NONE: //выстрел по земле или статичным объектам
	        {
//				fMakeExplosion = false;
				ffX = fX;
				ffY = fY;
				ffZ = fZ;
			}
	        case BULLET_HIT_TYPE_PLAYER:
	        {
				fMakeExplosion = false;
			}
	        case BULLET_HIT_TYPE_PLAYER_OBJECT:
	        {
				fMakeExplosion = false;
			}
	        case BULLET_HIT_TYPE_VEHICLE:
	        {
				if(weaponid == 25) //дробовик
				{
		            GetVehiclePos(hitid, ffX, ffY, ffZ);
				}
	            else
					fMakeExplosion = false;
			}
		}
		
		if(fMakeExplosion)
		{
			switch(weaponid)
			{
				case 24: //пистолет (пустынный орёл)
				{
				    CreateExplosion(ffX,ffY,ffZ,0,gPlayerWeapon[playerid][3]);
				}
				case 25: //дробовик
				{
				    CreateExplosion(ffX,ffY,ffZ,2,gPlayerWeapon[playerid][3]);
				}
				case 30: //АК47
				{
				    CreateExplosion(ffX,ffY,ffZ,0,gPlayerWeapon[playerid][3]);
				}
				case 31: //M4
				{
				    CreateExplosion(ffX,ffY,ffZ,0,gPlayerWeapon[playerid][3]);
				}
				case 33: //винтовка
				{
				    CreateExplosion(ffX,ffY,ffZ,2,gPlayerWeapon[playerid][3]);
				}
				case 34: //снайперская винтовка
				{
				    CreateExplosion(ffX,ffY,ffZ,6,gPlayerWeapon[playerid][3]);
				}
			}
		}
	}

	gWeaponUpdate[playerid] = 1;
	
	if(gUpdateWeaponTimer < 0)
		gUpdateWeaponTimer = SetTimer("update_weapon_ammo", UPDATE_WEAPON_AMMO_TIMER, false);
		
	if(gPlayerWeapon[playerid][1] <= 0) //если кончились патроны, строго < 0 для последнего австрела
	{
	    //собственно, освобождаем пустые обоймы
	    save_character_ammo(playerid, -1, -1);
		//разбираем оружие в инвентаре
		cell = disassemble_inventory_object(gPlayerWeapon[playerid][0]);
		if(cell >= 0)
		{
			cache_player_inventory(playerid);
			create_views_of_items(playerid, -1, -1, INVENTORY_AREA);
		}

		if(gPlayerWeapon[playerid][1] < 0)
		{
			gPlayerWeapon[playerid][0] = 0;
			gPlayerWeapon[playerid][1] = 0;
			gPlayerWeapon[playerid][2] = 0;
			gPlayerWeapon[playerid][3] = 0;
			ResetPlayerWeapons(playerid); //немножко античита
		    return 0;
		}

		//убираем оружие из рук
		gPlayerWeapon[playerid][0] = 0;
		gPlayerWeapon[playerid][1] = 0;
		//gPlayerWeapon[playerid][2] = 0; //не обнуляем для возможности последнего попадания
		gPlayerWeapon[playerid][3] = 0;
		ResetPlayerWeapons(playerid); //немножко античита
	}

//	if(gAdminLevel[playerid] > 9)
//	    CreateExplosion(fX, fY, fZ, 6, 10);

	return 1;
}

public OnPlayerTakeDamage(playerid, issuerid, Float: amount, weaponid, bodypart)
{
	return OnPlayerTakeDamageEx(playerid, issuerid, Float: amount, weaponid, bodypart);
}

public OnPlayerTakeDamageEx(playerid, issuerid, Float: amount, weaponid, bodypart)
{
	new str_amount[16];
	new buff;
	new Float:x,Float:y,Float:z;
	
	buff = gHealth[playerid]*100/START_HEALTH_VALUE;

	if(IsPlayerNPC(playerid))
		FCNPC_SetHealth(playerid, buff>8?buff:8);
	else
		SetPlayerHealth(playerid, buff>8?buff:8);

    if(gHealth[playerid] <= 0)
    {
		kill_character(playerid);
        return 1;
    }
//	SetPlayerHealth(playerid, 1000000.0);

//	new str[128];
//	format(str, sizeof(str), "playerid=%d, issuerid=%d, amount=%f, weaponid=%d, bodypart=%d", playerid, issuerid, amount, weaponid, bodypart);
//	SendClientMessage(playerid, 0xFFFF55, str);

	//если у наносящего урон в руках нету оружия, из которого урон наносится
	if(issuerid != INVALID_PLAYER_ID && issuerid >= 0 && issuerid < MAX_PLAYERS && gPlayerWeapon[issuerid][2] != weaponid)
	    return 0;
	//обнуляем оружие после последнего выстрела (если кончились патроны)
    if(issuerid != INVALID_PLAYER_ID && issuerid >= 0 && issuerid < MAX_PLAYERS && gPlayerWeapon[issuerid][1] == 0)
    	gPlayerWeapon[issuerid][2] = 0;

	if(issuerid != INVALID_PLAYER_ID)
	{
		if(gPlayersID[issuerid] > 0)
		    gKiller[playerid] = gPlayersID[issuerid];
	}

	switch(weaponid)
	{
	    case 54: //падение
	    {
			if(amount < 3.290000 || amount > 3.310000)
			{
				if(gWound[playerid] >= MAX_WOUND_REAL_VALUE)
				    return 1;
				if(issuerid != INVALID_PLAYER_ID)
				{
					if(gPlayersID[issuerid] > 0)
					    gKiller[playerid] = gPlayersID[issuerid];
				}
//		        imes_simple_single(playerid, 0x66FF55, "O_O_O_H_H_H");
				format(str_amount, sizeof(str_amount), "%.0f", amount);
				gWound[playerid] = gWound[playerid] + strval(str_amount)*10;
				update_sensor_wound(playerid, gWound[playerid]);
				update_statistic_data(playerid, false);
				return 1;
			}
	    }
	    case 53: //утопающий
		{
				if(gWound[playerid] >= MAX_WOUND_REAL_VALUE)
				    return 1;
//		        imes_simple_single(playerid, 0x66FF55, "A_A_A_H_H_H");
				format(str_amount, sizeof(str_amount), "%.0f", amount);
				gWound[playerid] = gWound[playerid] + strval(str_amount)*100;
				update_sensor_wound(playerid, gWound[playerid]);
				update_statistic_data(playerid, false);
				return 1;
		}
	    case 37: //огонь
	    {
		    if(gWound[playerid] < FIRE_WOUND_VALUE)
		    {
		        gWound[playerid] = FIRE_WOUND_VALUE;
				update_sensor_wound(playerid, gWound[playerid]);
				update_statistic_data(playerid, false);
      		}
	        if(gTemperature[playerid] < (MAX_TEMP_VALUE-30))
	        {
		        gTemperature[playerid] = MAX_TEMP_VALUE - 30;
	            update_sensor_temp(playerid, gTemperature[playerid]);
				update_statistic_data(playerid, false);
	        }
			if(issuerid != INVALID_PLAYER_ID)
			{
				if(gPlayersID[issuerid] > 0)
				    gKiller[playerid] = gPlayersID[issuerid];
			}
	        return 1;
		}
		case 24: //пистолет (пустынный орёл)
		{
		    if(!IsPlayerNPC(playerid))
		    {
				gGunMode[playerid] = GetTickCount();
				update_sensor_gun(playerid);
			}
			if(issuerid != INVALID_PLAYER_ID && !IsPlayerNPC(issuerid))
			{
				gGunMode[issuerid] = GetTickCount();
				update_sensor_gun(issuerid);
			}
			if(amount > 5.0)
				gHealth[playerid] = gHealth[playerid] - 1000;
			else
				gHealth[playerid] = gHealth[playerid] - 50; //удар рукояткой
			update_sensor_health(playerid, gHealth[playerid]);
			if(gPlayerWeapon[playerid][3] > 0)
			{
			    GetPlayerPos(playerid,x,y,z);
			    CreateExplosion(x,y,z,0,gPlayerWeapon[playerid][3]);
			}
			update_statistic_data(playerid, false);
		}
		case 25: //дробовик
		{
		    if(!IsPlayerNPC(playerid))
		    {
				gGunMode[playerid] = GetTickCount();
				update_sensor_gun(playerid);
			}
			if(issuerid != INVALID_PLAYER_ID && !IsPlayerNPC(issuerid))
			{
				gGunMode[issuerid] = GetTickCount();
				update_sensor_gun(issuerid);
			}
			if(amount > 5.0)
				gHealth[playerid] = gHealth[playerid] - 3000;
			else
				gHealth[playerid] = gHealth[playerid] - 30; //удар прикладом
			update_sensor_health(playerid, gHealth[playerid]);
			if(gPlayerWeapon[playerid][3] > 0)
			{
			    GetPlayerPos(playerid,x,y,z);
			    CreateExplosion(x,y,z,2,gPlayerWeapon[playerid][3]);
			}
			update_statistic_data(playerid, false);
		}
		case 30: //АК47
		{
			if(!IsPlayerNPC(playerid))
		    {
				gGunMode[playerid] = GetTickCount();
				update_sensor_gun(playerid);
			}
			if(issuerid != INVALID_PLAYER_ID && !IsPlayerNPC(issuerid))
			{
				gGunMode[issuerid] = GetTickCount();
				update_sensor_gun(issuerid);
			}
			if(amount > 5.0)
				gHealth[playerid] = gHealth[playerid] - 700;
			else
				gHealth[playerid] = gHealth[playerid] - 70; //удар прикладом
			update_sensor_health(playerid, gHealth[playerid]);
			if(gPlayerWeapon[playerid][3] > 0)
			{
			    GetPlayerPos(playerid,x,y,z);
			    CreateExplosion(x,y,z,0,gPlayerWeapon[playerid][3]);
			}
			update_statistic_data(playerid, false);
		}
		case 31: //M4
		{
		    if(!IsPlayerNPC(playerid))
		    {
				gGunMode[playerid] = GetTickCount();
				update_sensor_gun(playerid);
			}
			if(issuerid != INVALID_PLAYER_ID && !IsPlayerNPC(issuerid))
			{
				gGunMode[issuerid] = GetTickCount();
				update_sensor_gun(issuerid);
			}
			gHealth[playerid] = gHealth[playerid] - 100;
			update_sensor_health(playerid, gHealth[playerid]);
			if(gPlayerWeapon[playerid][3] > 0)
			{
			    GetPlayerPos(playerid,x,y,z);
			    CreateExplosion(x,y,z,0,gPlayerWeapon[playerid][3]);
			}
			update_statistic_data(playerid, false);
		}
		case 33: //винтовка
		{
		    if(!IsPlayerNPC(playerid))
		    {
				gGunMode[playerid] = GetTickCount();
				update_sensor_gun(playerid);
			}
			if(issuerid != INVALID_PLAYER_ID && !IsPlayerNPC(issuerid))
			{
				gGunMode[issuerid] = GetTickCount();
				update_sensor_gun(issuerid);
			}
			if(amount > 5.0)
				gHealth[playerid] = gHealth[playerid] - 4000;
			else
				gHealth[playerid] = gHealth[playerid] - 40; //удар прикладом
			update_sensor_health(playerid, gHealth[playerid]);
			if(gPlayerWeapon[playerid][3] > 0)
			{
			    GetPlayerPos(playerid,x,y,z);
			    CreateExplosion(x,y,z,2,gPlayerWeapon[playerid][3]);
			}
			update_statistic_data(playerid, false);
		}
		case 34: //снайперская винтовка
		{
		    if(!IsPlayerNPC(playerid))
		    {
				gGunMode[playerid] = GetTickCount();
				update_sensor_gun(playerid);
			}
			if(issuerid != INVALID_PLAYER_ID && !IsPlayerNPC(issuerid))
			{
				gGunMode[issuerid] = GetTickCount();
				update_sensor_gun(issuerid);
			}
			if(amount > 5.0)
				gHealth[playerid] = gHealth[playerid] - 12000;
			else
				gHealth[playerid] = gHealth[playerid] - 120; //удар прикладом
			update_sensor_health(playerid, gHealth[playerid]);
			if(gPlayerWeapon[playerid][3] > 0)
			{
			    GetPlayerPos(playerid,x,y,z);
			    CreateExplosion(x,y,z,6,gPlayerWeapon[playerid][3]);
			}
			update_statistic_data(playerid, false);
		}
		case 42: //огнетушитель
		{
		    if(!IsPlayerNPC(playerid))
		    {
				gGunMode[playerid] = GetTickCount();
				update_sensor_gun(playerid);
			}
			if(issuerid != INVALID_PLAYER_ID && !IsPlayerNPC(issuerid))
			{
				gGunMode[issuerid] = GetTickCount();
				update_sensor_gun(issuerid);
			}
		    if(gWound[playerid] < EXTING_WOUND_VALUE)
		    {
		        gWound[playerid] = EXTING_WOUND_VALUE;
				update_sensor_wound(playerid, gWound[playerid]);
      		}
			if(issuerid != INVALID_PLAYER_ID)
			{
				if(gPlayersID[issuerid] > 0)
				    gKiller[playerid] = gPlayersID[issuerid];
			}
	        return 1;
//			gHealth[playerid] = gHealth[playerid] - 1000;
//			update_sensor_health(playerid, gHealth[playerid]);
		}
		case 18: //коктейль молотова
		{
		    if(!IsPlayerNPC(playerid))
		    {
				gGunMode[playerid] = GetTickCount();
				update_sensor_gun(playerid);
			}
			if(issuerid != INVALID_PLAYER_ID && !IsPlayerNPC(issuerid))
			{
				gGunMode[issuerid] = GetTickCount();
				update_sensor_gun(issuerid);
			}
			gHealth[playerid] = gHealth[playerid] - 2000;
			update_sensor_health(playerid, gHealth[playerid]);
			update_statistic_data(playerid, false);
		}
		case 4: //нож
		{
		    if(!IsPlayerNPC(playerid))
		    {
				gGunMode[playerid] = GetTickCount();
				update_sensor_gun(playerid);
			}
			if(issuerid != INVALID_PLAYER_ID && !IsPlayerNPC(issuerid))
			{
				gGunMode[issuerid] = GetTickCount();
				update_sensor_gun(issuerid);
			}
			gHealth[playerid] = gHealth[playerid] - gPlayerWeapon[issuerid][1];
			update_sensor_health(playerid, gHealth[playerid]);
			update_statistic_data(playerid, false);
		}
		case 5: //бита
		{
		    if(!IsPlayerNPC(playerid))
		    {
				gGunMode[playerid] = GetTickCount();
				update_sensor_gun(playerid);
			}
			if(issuerid != INVALID_PLAYER_ID && !IsPlayerNPC(issuerid))
			{
				gGunMode[issuerid] = GetTickCount();
				update_sensor_gun(issuerid);
			}
			if(issuerid != INVALID_PLAYER_ID)
				gHealth[playerid] = gHealth[playerid] - gPlayerWeapon[issuerid][1];
			update_sensor_health(playerid, gHealth[playerid]);
			update_statistic_data(playerid, false);
		}
		case 8: //катана
		{
		    if(!IsPlayerNPC(playerid))
		    {
				gGunMode[playerid] = GetTickCount();
				update_sensor_gun(playerid);
			}
			if(issuerid != INVALID_PLAYER_ID && !IsPlayerNPC(issuerid))
			{
				gGunMode[issuerid] = GetTickCount();
				update_sensor_gun(issuerid);
			}
			if(issuerid != INVALID_PLAYER_ID)
				gHealth[playerid] = gHealth[playerid] - gPlayerWeapon[issuerid][1];
			update_sensor_health(playerid, gHealth[playerid]);
			if(gPlayerWeapon[playerid][3] > 0)
			{
			    GetPlayerPos(playerid,x,y,z);
			    CreateExplosion(x,y,z,6,gPlayerWeapon[playerid][3]);
			}
			update_statistic_data(playerid, false);
		}
		case 0: //кулак
		{
		    if(!IsPlayerNPC(playerid))
		    {
				gGunMode[playerid] = GetTickCount();
				update_sensor_gun(playerid);
			}
			if(issuerid != INVALID_PLAYER_ID && !IsPlayerNPC(issuerid))
			{
				gGunMode[issuerid] = GetTickCount();
				update_sensor_gun(issuerid);
			}
			if(issuerid != INVALID_PLAYER_ID && IsPlayerNPC(issuerid))
				gHealth[playerid] = gHealth[playerid] - 3000;
			else
				gHealth[playerid] = gHealth[playerid] - 100;
			update_sensor_health(playerid, gHealth[playerid]);
			update_statistic_data(playerid, false);
		}
	    default:
        {
			return 0;
		}
	}

	if(bodypart == WEAPON_BODY_PART_HEAD)
	{
		if(issuerid != INVALID_PLAYER_ID && !IsPlayerNPC(issuerid))
			PlayerPlaySound(issuerid, 6401, 0, 0, 0);
		kill_character(playerid);
		return 1;
	}
//    if(!IsPlayerNPC(playerid))
//	    imes_simple_single(playerid, 0x66FF55, "A_A_A_H_H_H");
	format(str_amount, sizeof(str_amount), "%.0f", amount);
	
	if(issuerid != INVALID_PLAYER_ID && IsPlayerNPC(issuerid) && weaponid == 0)
		gWound[playerid] = gWound[playerid] + strval(str_amount)*200;
	else
		gWound[playerid] = gWound[playerid] + strval(str_amount)*10;

	if(gWound[playerid] > MAX_WOUND_REAL_VALUE)
        gWound[playerid] = MAX_WOUND_REAL_VALUE;
	update_sensor_wound(playerid, gWound[playerid]);
    if(issuerid != INVALID_PLAYER_ID && !IsPlayerNPC(issuerid))
		PlayerPlaySound(issuerid, 19403, 0, 0, 0);

    return 1;
}

public OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart)
{
/*
	for(new i = 0; i < MAX_PLAYERS; ++i)
	{
		if(IsPlayerAdmin(i) || gAdminLevel[i] > 9)
		{
		    new mes[128];
		    format(mes, sizeof(mes), "damageid=%d,weaponid=%d", damagedid,weaponid);
			SendClientMessage(i, 0x33FF88, mes);
		}
	}
*/

	switch(weaponid)
	{
	    case 54: //падение
			return 1;
	    case 53: //утопающий
		    return 1;
	    case 37: //огонь
			return 1;
		case 24: //пистолет (пустынный орёл)
			return 1;
		case 25: //дробовик
			return 1;
		case 30: //АК47
			return 1;
		case 31: //M4
			return 1;
		case 33: //винтовка
			return 1;
		case 34: //снайперская винтовка
			return 1;
		case 42: //огнетушитель
			return 1;
		case 18: //коктейль молотова
			return 1;
		case 4: //нож
			return 1;
		case 5: //бита
			return 1;
		case 8: //катана
			return 1;
		case 0: //кулак
			return 1;
		default:
		{
		}
	}
	
	if(gAdminLevel[playerid] < 5)
	{
		new name[64];
		new msg[256];

		//сообщение в низ экрана
		GetPlayerName(playerid, name, sizeof(name));
		format(msg, sizeof(msg), "%s(id:%d) seems to be a CHEATER! FORBIDDEN WEAPON (kick)", name, playerid);
		update_sensor_messager_cheat(msg);
		//гарантируем игроку кик
		gPlayerCheaterLevel[playerid] = gMaxAnticheat;
	}

	return 0;
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	static CheckTimerID_0, CheckTimerID_1;
	new spect_id;

	//если расход топлива нулевой - "заводим двигатель"
	if(gVeh[vehicleid][5] == 0)
	    gVeh[vehicleid][4] = 1;

	drop_vehicle_from_dot(playerid, vehicleid);
	save_vehicle_state(INVALID_PLAYER_ID, vehicleid);
	hide_menu(playerid);

	if(CheckTimerID_0 > 0)
	{
	    KillTimer(CheckTimerID_0);
	    CheckTimerID_0 = 0;
	}
	if(CheckTimerID_1 > 0)
	{
	    KillTimer(CheckTimerID_1);
	    CheckTimerID_1 = 0;
	}
	create_vehicle_sensors(playerid, vehicleid);
	CheckTimerID_0 = SetTimer("check_vehicle_menu_show", VEHICLE_DATA_SHOW_CHECK, false);
	CheckTimerID_1 = SetTimer("check_vehicle_menu_show", VEHICLE_DATA_SHOW_CHECK*2, false);
	
	for(spect_id = 0; spect_id < MAX_PLAYERS; ++spect_id)
	{
	    if(gPsp[playerid][spect_id] > 0)
	    {
   		    PlayerSpectateVehicle(spect_id, vehicleid, SPECTATE_MODE_NORMAL);
	    }
	}

	return 1;
}

public OnPlayerExitVehicle(playerid, vehicleid)
{
	static CheckTimerID_0, CheckTimerID_1;
	new spect_id;

	//если расход топлива не нулевой - "глушим двигатель" уменьшения времени
	//обработки таймера обновления состояния авто
	if(gVeh[vehicleid][5] == 0)
	    gVeh[vehicleid][4] = 0;

	//убираем авто из точки респавна, если она заводится вдали от таковой
	drop_vehicle_from_dot(playerid, vehicleid);
	save_vehicle_state(playerid, vehicleid);
	hide_menu(playerid);

	if(CheckTimerID_0 > 0)
	{
	    KillTimer(CheckTimerID_0);
	    CheckTimerID_0 = 0;
	}
	if(CheckTimerID_1 > 0)
	{
	    KillTimer(CheckTimerID_1);
	    CheckTimerID_1 = 0;
	}

	destroy_vehicle_sensors(playerid);
	CheckTimerID_0 = SetTimer("check_vehicle_menu_show", VEHICLE_DATA_SHOW_CHECK, false);
	CheckTimerID_1 = SetTimer("check_vehicle_menu_show", VEHICLE_DATA_SHOW_CHECK*2, false);
	
	for(spect_id = 0; spect_id < MAX_PLAYERS; ++spect_id)
	{
	    if(gPsp[playerid][spect_id] > 0)
	    {
   		    PlayerSpectatePlayer(spect_id, playerid, SPECTATE_MODE_NORMAL);
	    }
	}

	return 1;
}

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	return 1;
}

public OnPlayerEnterCheckpoint(playerid)
{
	return 1;
}

public OnPlayerLeaveCheckpoint(playerid)
{
	return 1;
}

public OnPlayerEnterRaceCheckpoint(playerid)
{
	return 1;
}

public OnPlayerLeaveRaceCheckpoint(playerid)
{
	return 1;
}

public OnRconCommand(cmd[])
{
	return 1;
}

public OnPlayerRequestSpawn(playerid)
{
	return 1;
}

public OnObjectMoved(objectid)
{
//	SendClientMessage(0, 0xFF00FF,"Object moved!");
	return 1;
}

public OnPlayerObjectMoved(playerid, objectid)
{
	return 1;
}

public OnPlayerPickUpPickup(playerid, pickupid)
{
	return 1;
}

public OnVehicleMod(playerid, vehicleid, componentid)
{
	return 0;
}

public OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{
	return 1;
}

public OnVehicleRespray(playerid, vehicleid, color1, color2)
{
	return 1;
}

public OnPlayerSelectedMenuRow(playerid, row)
{
	return 1;
}

public OnPlayerExitedMenu(playerid)
{
	return 1;
}

public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)
{
	return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	new vehicleid;

	//показать инвентарь
	if( (newkeys & KEY_YES) && !(oldkeys & KEY_YES) )
	{
		if(gInventoryMenuShow[playerid] == 0)
		    show_inventory(playerid, IsPlayerInVehicleReal(playerid));
		else
		    hide_menu(playerid);
		return 1;
	}

	//взять вещь
	if( (newkeys & KEY_WALK) && !(oldkeys & KEY_WALK) ||	//взять вещь при нажатии Alt
		(newkeys & KEY_CROUCH) && !(oldkeys & KEY_CROUCH) )	//взять вещь присев
	{
		new no_place;

		no_place = 1;

		if(IsPlayerSpawned(playerid) && !IsPlayerInAnyVehicle(playerid))
		{
			if(gAltWait[playerid]) //если запрос уже находится в обработке
				return 1;

			if(gFullInvent[playerid] == 1) //если нет места
				return 1;

			gAltWait[playerid] = 1;

			for(new i = 0; i < MAX_INVENTORY_ON_PLAYER; ++i)
			{
				if(gInventoryItem[playerid][i][db_id] != -1)
				{
					no_place = 0;
					break;
				}
			}
			if(no_place && gBag[playerid][1] > 0)
			{
				for(new i = 0; i < MAX_INVENTORY_IN_BAG; ++i)
				{
					if(gBagItem[playerid][i][db_id] != -1)
					{
						no_place = 0;
						break;
					}
				}
			}

			if(no_place)
			{
				gFullInvent[playerid] = 1;
				imes_simple_single(playerid, 0xFF8888FF, "NOT_ENOUGH_SPACE");
				return 1;
			}

			add_objects_from_ground(playerid,gStandartRangeValue);
		}
	}

	//открыть ворота
	if( (newkeys & KEY_ANALOG_LEFT) && !(oldkeys & KEY_ANALOG_LEFT))
	{
		//открываем ворота
		if(open_a_gate(playerid, "SOME_KEY_TYPE", "SOME_DOOR_TYPE") < 0)
			open_a_gate(playerid, "PUBLIC_KEY_TYPE", "SOME_DOOR_TYPE");
		return 1;
	}

	//открыть авто
	if( (newkeys & KEY_ANALOG_RIGHT) && !(oldkeys & KEY_ANALOG_RIGHT) )
	{
		//открываем авто
		if(open_a_car(playerid, "PUBLIC_KEY_TYPE", "SOME_VEHICLE") < 0)
		{
			if(open_a_car(playerid, "SOME_KEY_TYPE", "SOME_VEHICLE") < 0)
			{
				if(open_a_car(playerid, "SOME_KEY_TYPE", "SOME_BOAT_TYPE") < 0)
					if(open_a_car(playerid, "SOME_KEY_TYPE", "SOME_HELICOPTER_TYPE") < 0)
						if(open_a_car(playerid, "SOME_KEY_TYPE", "SOME_TANK") < 0)
							open_a_car(playerid, "SOME_KEY_TYPE", "SOME_BUS_VEH");
			}
		}
		return 1;
	}

	//завести мотор
	if( ( ((newkeys & KEY_SUBMISSION) && !(newkeys & KEY_SUBMISSION)) || ((newkeys & KEY_NO) && !(oldkeys & KEY_NO)) ) && IsPlayerInVehicleReal(playerid) )
	{
		vehicleid = GetPlayerVehicleID(playerid);
		if(vehicleid == INVALID_VEHICLE_ID)
		    return 1;
		if(gVeh[vehicleid][0] <= 0) //немного античита
		{
			DestroyVehicle(vehicleid);
			return 1;
		}
		if(gVeh[vehicleid][4] > 0)
		{
			//если расход не нулевой
		    if(gVeh[vehicleid][5] != 0)
			{
		        create_vehicle_sensors(playerid, vehicleid);
		        //imes_simple_single(playerid, 0xFDBCADFF, "ON_STOP_ENGINE");
				//если мотор был включен - глушим
				gVeh[vehicleid][4] = 0;
			}
			save_vehicle_state(playerid, vehicleid);
			for(new i = 0; i < MAX_PLAYERS; ++i)
			{
			    if(IsPlayerInVehicle(i, vehicleid))
					update_vehicle_sensors(i);
			}
			return 1;
		}
		else
		{
	        create_vehicle_sensors(playerid, vehicleid);
		    //gVeh[vehicleid][2] = 500; //gVeh[vehicleid][3] = 50; //отладка!!!
			//если мотор был выключен - пытаемся завести
			//если есть работоспособный движок и бензин (либо расход бензина нулевой) - заводим!
			if( (gVeh[vehicleid][2] > 0) && (gVeh[vehicleid][9] > 0) && ((gVeh[vehicleid][3] > 0) || gVeh[vehicleid][5] == 0) )
			{
				//разряжаем аккумулятор
				if(gVeh[vehicleid][9] < 50)
				{
			        imes_simple_single(playerid, 0xFF8888FF, "ON_START_LOW_ACCUMUL");
				    return 1;
				}
				gVeh[vehicleid][9] = gVeh[vehicleid][9] - 50; //минус 5% от заряда
				
				gVeh[vehicleid][4] = 1;
				save_vehicle_state(playerid, vehicleid);
		        //imes_simple_single(playerid, 0xFDBCADFF, "ON_START_ENGINE");
				for(new i = 0; i < MAX_PLAYERS; ++i)
				{
				    if(IsPlayerInVehicle(i, vehicleid))
						update_vehicle_sensors(i);
				}
				//убираем авто из точки респавна, если она заводится вдали от таковой
				drop_vehicle_from_dot(playerid, vehicleid);
			    return 1;
			}
			else
			{
			    //если расход нулевой - выходим
			    if(gVeh[vehicleid][5] == 0)
			        return 1;

			    //если двигатель поломан
			    if(gVeh[vehicleid][2] <= 0)
			    {
			        imes_simple_single(playerid, 0xFF5555FF, "ON_START_BROKEN_ENGINE");
				    return 1;
				}

				//если нету топлива
			    if(gVeh[vehicleid][3] <= 0)
			    {
			        imes_simple_single(playerid, 0xFF8888FF, "ON_START_NO_FUEL_ENGINE");
				    return 1;
				}

				//если разряжен аккумулятор
			    if(gVeh[vehicleid][9] <= 0)
			    {
			        imes_simple_single(playerid, 0xFF8888FF, "ON_START_LOW_ACCUMUL");
				    return 1;
				}
			}
		}
	}

	//показать панель администратора (при наблюдении)
	if( (newkeys & KEY_SECONDARY_ATTACK) && !(oldkeys & KEY_SECONDARY_ATTACK) )
	{
		for(new i = 0; i < MAX_PLAYERS; ++i)
		{
		    if(gPsp[i][playerid] != 0)
		    {
		        show_admin_panel(playerid);
		        return 1;
		    }
		}
	}
	
	//включаем/выключаем фары (с учётом Alt+Tab)
	if( (newkeys & KEY_ACTION) && !(oldkeys & KEY_ACTION) && !(newkeys & KEY_WALK) )
	{
		new engine, lights, alarm, doors, bonnet, boot, objective;
	    if(IsPlayerInAnyVehicle(playerid))
	    {
		    if(GetPlayerVehicleSeat(playerid) == 0)
		    {
		        vehicleid = GetPlayerVehicleID(playerid);
				if(gVeh[vehicleid][9] > 0)
				{
			        GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
			        lights = lights^1;
			        gVeh[vehicleid][7] = lights;
			        SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
			        save_vehicle_state(playerid, vehicleid);
				}
				else
				{
			        imes_simple_single(playerid, 0xFF8888FF, "ON_START_LOW_ACCUMUL");
				}
			}
	    }
	}

	//переключить наблюдаемого игрока
	if( (newkeys & KEY_FIRE) && !(oldkeys & KEY_FIRE) )
	{
		new vhid;
		new next;

		for(new i = 0; i < MAX_PLAYERS; ++i)
		{
		    if(gPsp[i][playerid] != 0)
		    {
		        for(new j = i+1; j < MAX_PLAYERS; ++j)
		        {
					if(j != playerid && !IsPlayerNPC(j) && IsPlayerConnected(j))
					{
						next = 0;
				        for(new k = 0; k < MAX_PLAYERS; ++k)
				        {
				            if(gPsp[k][j] != 0)
				            {
				                next = 1;
				                break;
				            }
				        }
				        if(next)
				            continue;
				        TogglePlayerSpectating(playerid, 1);
				        if(IsPlayerInAnyVehicle(j))
				        {
				            vhid = GetPlayerVehicleID(j);
				            PlayerSpectateVehicle(playerid, vhid, SPECTATE_MODE_NORMAL);
				        }
				        else
				        {
						    PlayerSpectatePlayer(playerid, j, SPECTATE_MODE_NORMAL);
						}
			            gPsp[i][playerid] = 0;
			            gPsp[j][playerid] = 1;
						show_spectate_data(playerid, j, true);
				        return 1;
					}
		        }
		        for(new j = 0; j < i; ++j)
		        {
					if(j != playerid && !IsPlayerNPC(j) && IsPlayerConnected(j))
					{
						next = 0;
				        for(new k = 0; k < MAX_PLAYERS; ++k)
				        {
				            if(gPsp[k][j] != 0)
				            {
				                next = 1;
				                break;
				            }
				        }
				        if(next)
				            continue;
				        TogglePlayerSpectating(playerid, 1);
				        if(IsPlayerInAnyVehicle(j))
				        {
				            vhid = GetPlayerVehicleID(j);
				            PlayerSpectateVehicle(playerid, vhid, SPECTATE_MODE_NORMAL);
				        }
				        else
				        {
						    PlayerSpectatePlayer(playerid, j, SPECTATE_MODE_NORMAL);
						}
			            gPsp[i][playerid] = 0;
			            gPsp[j][playerid] = 1;
						show_spectate_data(playerid, j, true);
				        return 1;
					}
		        }
		        return 1;
		    }
		}
	}

	//переключить игрока в обратном порядке
	if( (newkeys & KEY_WALK) && !(oldkeys & KEY_WALK) )
	{
		new vhid;
		new next;

		for(new i = 0; i < MAX_PLAYERS; ++i)
		{
		    if(gPsp[i][playerid] != 0)
		    {
		        for(new j = i-1; j >= 0; --j)
		        {
					if(j != playerid && !IsPlayerNPC(j) && IsPlayerConnected(j))
					{
						next = 0;
				        for(new k = 0; k < MAX_PLAYERS; ++k)
				        {
				            if(gPsp[k][j] != 0)
				            {
				                next = 1;
				                break;
				            }
				        }
				        if(next)
				            continue;
				        TogglePlayerSpectating(playerid, 1);
				        if(IsPlayerInAnyVehicle(j))
				        {
				            vhid = GetPlayerVehicleID(j);
				            PlayerSpectateVehicle(playerid, vhid, SPECTATE_MODE_NORMAL);
				        }
				        else
				        {
						    PlayerSpectatePlayer(playerid, j, SPECTATE_MODE_NORMAL);
						}
			            gPsp[i][playerid] = 0;
			            gPsp[j][playerid] = 1;
						show_spectate_data(playerid, j, true);
				        return 1;
					}
		        }
		        for(new j = MAX_PLAYERS; j > i; --j)
		        {
					if(j != playerid && !IsPlayerNPC(j) && IsPlayerConnected(j))
					{
						next = 0;
				        for(new k = 0; k < MAX_PLAYERS; ++k)
				        {
				            if(gPsp[k][j] != 0)
				            {
				                next = 1;
				                break;
				            }
				        }
				        if(next)
				            continue;
				        TogglePlayerSpectating(playerid, 1);
				        if(IsPlayerInAnyVehicle(j))
				        {
				            vhid = GetPlayerVehicleID(j);
				            PlayerSpectateVehicle(playerid, vhid, SPECTATE_MODE_NORMAL);

				        }
				        else
				        {
						    PlayerSpectatePlayer(playerid, j, SPECTATE_MODE_NORMAL);
						}
			            gPsp[i][playerid] = 0;
			            gPsp[j][playerid] = 1;
						show_spectate_data(playerid, j, true);
				        return 1;
					}
		        }
		        return 1;
		    }
		}
	}

	//если с шифтом - телепорт к игроку
	if( ((newkeys & KEY_HANDBRAKE) && !(oldkeys & KEY_HANDBRAKE)) && (newkeys & KEY_SPRINT))
	{
	    new Float:x, Float:y, Float:z;
		for(new i = 0; i < MAX_PLAYERS; ++i)
		{
		    if(gPsp[i][playerid] != 0)
		    {
				hide_spectate_data(playerid);
		        TogglePlayerSpectating(playerid, 0);
		        for(new j = 0; j < MAX_PLAYERS; ++j)
		        {
		            gPsp[j][playerid] = 0;
		        }
		        GetPlayerPos(i, x, y, z);
		        SetPlayerPos(playerid, x, y, z);
		        save_player_position(playerid);
		        return 1;
		    }
		}
	}
	//вернуться в игру из наблюдения
	if( (newkeys & KEY_HANDBRAKE) && !(oldkeys & KEY_HANDBRAKE) )
	{
		for(new i = 0; i < MAX_PLAYERS; ++i)
		{
		    if(gPsp[i][playerid] != 0)
		    {
				hide_spectate_data(playerid);
		        TogglePlayerSpectating(playerid, 0);
		        for(i = 0; i < MAX_PLAYERS; ++i)
		        {
		            gPsp[i][playerid] = 0;
		        }
		        load_player_position(playerid);
		        return 1;
		    }
		}
	}

	//сменить оружие
	if( (newkeys & KEY_NO) && !(oldkeys & KEY_NO) )
	{
		new out_cell;
	    find_character_weapon(playerid, out_cell);
	    if(out_cell >= 0)
		    apply_one_cell(playerid, -1, out_cell, INVENTORY_AREA);
		return 1;
	}
	
    // //предотвращаем комбинацию Alt+Tab (пытаемся)
	// if( (newkeys & KEY_ACTION) && !(oldkeys & KEY_ACTION) )
	// {
	    // gFullInvent[playerid] = 0;
	    // return 1;
	// }
	// if( (oldkeys & KEY_WALK) && !(newkeys & KEY_WALK) )
	// {
		// //сообщаем о полном инвентаре
		// if(FullInvent[playerid] > 0)
		// {
			// imes_simple_single(playerid, 0xFF8888FF, "NOT_ENOUGH_SPACE");
			// gFullInvent[playerid] = 0;
		// }
		// return 1;
	// }

	if( (newkeys & KEY_SECONDARY_ATTACK) && !(oldkeys & KEY_SECONDARY_ATTACK))
	{
		if(gInventoryMenuShow[playerid] == 1)
		        hide_menu(playerid);
	}

	return 1;
}

public OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	if(clickedid == Text:INVALID_TEXT_DRAW && gInventoryMenuShow[playerid] == 1)
	{
	    hide_menu(playerid);
	    return 1;
	}
	
	//close
	if(clickedid == Text:INVALID_TEXT_DRAW)
	{
	    for(new i = 0; i < MAX_PLAYERS; ++i)
	    {
	        if(gPsp[i][playerid] == 1)
	        {
				hide_admin_panel(playerid);
				return 1;
			}
		}
		return 1;
	}

	//mute
	if(clickedid == gAdminPanel[3] || clickedid == gAdminPanel[4])
	{
	    new name[64];
	    new time, id;
	    new imes[256], mes[256];
	    
	    if(gAdminLevel[playerid] < 1)
	        return 1;
	    for(new i = 0; i < MAX_PLAYERS; ++i)
	    {
	        if(gPsp[i][playerid] == 1)
	        {
		        if(i == playerid)
		            return 1;
			    if(gAdminLevel[playerid] < gAdminLevel[i])
			        return 1;
				id = i;
			    time = 1;
				mute_player(i, time);
			    if(gUnmuteTimers[id] != -1)
			    {
			        KillTimer(gUnmuteTimers[id]);
				    gUnmuteTimers[id] = -1;
			    }
				gUnmuteTimers[id] = SetTimerEx("unmute_a_chat_for_player", time*1000*3600, false, "i", gPlayersID[id]);
				GetPlayerName(id, name, sizeof(name));
				for(new j = 0; j < MAX_PLAYERS; ++j)
				{
					if(IsPlayerConnected(j))
					{
						//У игрока %s отключен чат на %d час(а)
				        imessage(imes, "MUTE_A_CHAT", gPlayerLang[j]);
						format(mes, sizeof(mes), imes, name, time);
				        SendClientMessage(j, 0xFF0000AA, mes);
					}
				}
				update_statistic_data(playerid, true);
				return 1;
			}
		}
	}

	//unmute
	if(clickedid == gAdminPanel[5] || clickedid == gAdminPanel[6])
	{
	    if(gAdminLevel[playerid] < 1)
	        return 1;
	    for(new i = 0; i < MAX_PLAYERS; ++i)
	    {
	        if(gPsp[i][playerid] == 1)
	        {
			    if(i == playerid)
			        return 1;
			    if(gAdminLevel[playerid] < gAdminLevel[i])
			        return 1;
				unmute_a_chat_for_player(gPlayersID[i]);
				return 1;
			}
		}
	}

	//freeze
	if(clickedid == gAdminPanel[7] || clickedid == gAdminPanel[8])
	{
		new imes[128];
	    new mes[128];
	    new name[64];

	    if(gAdminLevel[playerid] < 2)
	        return 1;
	    for(new i = 0; i < MAX_PLAYERS; ++i)
	    {
	        if(gPsp[i][playerid] == 1)
	        {
			    if(gAdminLevel[playerid] < gAdminLevel[i])
			        return 1;

				TogglePlayerControllable(i, 0);
				GetPlayerName(i, name, sizeof(name));
				for(new j = 0; j < MAX_PLAYERS; ++j)
				{
				    if(IsPlayerConnected(j))
				    {
						imessage(imes, "PLAYER_IS_FREEZED", gPlayerLang[j]);
						format(mes, sizeof(mes), imes, name);
						SendClientMessage(j, 0xFF0000FF, mes);
					}
				}
				
				return 1;
			}
		}
	}

	//unfreeze
	if(clickedid == gAdminPanel[9] || clickedid == gAdminPanel[10])
	{
		new imes[128];
	    new mes[128];
	    new name[64];

	    if(gAdminLevel[playerid] < 2)
	        return 1;
	    for(new i = 0; i < MAX_PLAYERS; ++i)
	    {
	        if(gPsp[i][playerid] == 1)
	        {
			    if(gAdminLevel[playerid] < gAdminLevel[i])
			        return 1;

				TogglePlayerControllable(i, 1);
				GetPlayerName(i, name, sizeof(name));
				for(new j = 0; j < MAX_PLAYERS; ++j)
				{
				    if(IsPlayerConnected(j))
				    {
						imessage(imes, "PLAYER_IS_UNFREEZED", gPlayerLang[j]);
						format(mes, sizeof(mes), imes, name);
						SendClientMessage(j, 0x00FF00FF, mes);
					}
				}
				return 1;
			}
		}
	}

	//kick
	if(clickedid == gAdminPanel[13] || clickedid == gAdminPanel[14])
	{
	    new id;
	    new cmd[128];
	    new name[64], admin_name[64];
	    new Float:x, Float:y, Float:z, Float:Z_coord;
	    
	    if(gAdminLevel[playerid] < 1)
	        return 1;
	    for(new i = 0; i < MAX_PLAYERS; ++i)
	    {
	        if(gPsp[i][playerid] == 1)
	        {
	            if(i == playerid)
	                return 1;
			    id = i;
			    if(id < 0 || id > MAX_PLAYERS)
			        return 1;
			    GetPlayerName(id, name, sizeof(name));
	            GetPlayerName(playerid, admin_name, sizeof(admin_name));
				if(gAdminLevel[id] > gAdminLevel[playerid])
				{
				    format(cmd, sizeof(cmd), "Player %s[%d] level %d trying to kick an admin %s[%d] level %d", admin_name, playerid, gAdminLevel[playerid], name, id, gAdminLevel[id]);
				    for(new j = 0; j < MAX_PLAYERS; ++j)
				    {
				        if(gAdminLevel[j] > gAdminLevel[playerid])
				            SendClientMessage(j, 0xFF2222, cmd);
				    }
				    return 1;
				}
			    //сообщение в низ экрана
			    format(cmd, sizeof(cmd), "%s(id:%d) was kicked by Admin", name, id);
			    update_sensor_messager_cheat(cmd);
			    //лишаем его админства
				gAdminLevel[id] = 0;

	            //замораживаем персонаж
				TogglePlayerControllable(id, 0);
				//немного издёвки
				PlayerPlaySound(id, 31202, 0, 0, 0);
				//удаляем сенсоры с экрана
				destroy_sensors(id);
				
				//сохраняем координаты
		    	save_player_bakup_position(id);

				//добавляем игроку кик в счётчик и отбрасываем на спавн при заходе
				mark_player_as_cheater(id, gMaxAnticheat);

				//раскидываем вещи
				//добавить проверку и обработку для транспорта!
				if(!IsPlayerAdmin(id))
				{
				    GetPlayerPos(id, x, y, z);
					for(new j = 0; j < MAX_INVENTORY_ON_PLAYER; ++j)
					{
					    if(gInventoryItem[playerid][j][db_id] > 0)
					    {
							MapAndreas_FindZ_For2DCoord_I(x, y, Z_coord);
					        if(z > (Z_coord+3))
						        drop_character_inventory_cell(id, j, -1, x, y, Z_coord);
							else if(z < 0 && Z_coord == 0)
								drop_character_inventory_cell(id, j, -1, x, y, 0);
					        else
								drop_character_inventory_cell(id, j, -1, x, y, z);
						}
					}
				}
				update_neighbors_objects_menu(id);
				gPlayerCheaterLevel[id] = gMaxAnticheat;
				//помечаем игрока на кик
				gCheatersList[id] = id;
				return 1;
			}
		}
	}

	//ban
	if(clickedid == gAdminPanel[17] || clickedid == gAdminPanel[18])
	{
	    new id;
	    new cmd[128];
	    new name[64], admin_name[64];
	    new Float:x, Float:y, Float:z, Float:Z_coord;

		if(gAdminLevel[playerid] < 2)
		    return 1;
	    for(new i = 0; i < MAX_PLAYERS; ++i)
	    {
	        if(gPsp[i][playerid] == 1)
	        {
	            if(i == playerid)
	                return 1;
			    id = i;
			    if(id < 0 || id > MAX_PLAYERS)
			        return 1;
			    GetPlayerName(id, name, sizeof(name));
	            GetPlayerName(playerid, admin_name, sizeof(admin_name));
				if(gAdminLevel[id] > gAdminLevel[playerid])
				{
				    format(cmd, sizeof(cmd), "Player %s[%d] level %d trying to ban an admin %s[%d] level %d", admin_name, playerid, gAdminLevel[playerid], name, id, gAdminLevel[id]);
				    for(new j = 0; j < MAX_PLAYERS; ++j)
				    {
				        if(gAdminLevel[j] > gAdminLevel[playerid])
				            SendClientMessage(j, 0xFF2222, cmd);
				    }
				    return 1;
				}
			    //сообщение в низ экрана
			    format(cmd, sizeof(cmd), "%s(id:%d) was banned by Admin", name, id);
			    update_sensor_messager_cheat(cmd);
			    //лишаем его админства
				gAdminLevel[id] = 0;

				//баним
				mark_player_as_banned(id, 168); //168 часов - неделя

	            //замораживаем персонаж
				TogglePlayerControllable(id, 0);
				//немного издёвки
				PlayerPlaySound(id, 31202, 0, 0, 0);
				//удаляем сенсоры с экрана
				destroy_sensors(id);

				//сохраняем координаты
		    	save_player_bakup_position(id);

				//раскидываем вещи
				//добавить проверку и обработку для транспорта!
				if(!IsPlayerAdmin(id))
				{
				    GetPlayerPos(id, x, y, z);
					for(new j = 0; j < MAX_INVENTORY_ON_PLAYER; ++j)
					{
					    if(gInventoryItem[playerid][j][db_id] > 0)
					    {
							MapAndreas_FindZ_For2DCoord_I(x, y, Z_coord);
					        if(z > (Z_coord+3))
						        drop_character_inventory_cell(id, j, -1, x, y, Z_coord);
							else if(z < 0 && Z_coord == 0)
								drop_character_inventory_cell(id, j, -1, x, y, 0);
					        else
								drop_character_inventory_cell(id, j, -1, x, y, z);
						}
					}
				}
				update_neighbors_objects_menu(id);
				//помечаем игрока на бан
				gCheatersList[id] = id-2000;
				return 1;
			}
		}
	}
	
	//unban
	if(clickedid == gAdminPanel[19] || clickedid == gAdminPanel[20])
	{
	    new list[1800];
	    
	    if(gAdminLevel[playerid] < 2)
	        return 1;
	    for(new i = 0; i < MAX_PLAYERS; ++i)
	    {
	        if(gPsp[i][playerid] == 1)
	        {
				create_banned_list(list, sizeof(list));
		  	    ShowPlayerDialog(playerid, 5511, DIALOG_STYLE_LIST, "Banned", list, "OK", "Cancel");
				return 1;
			}
		}
	}

	return 1;
}

public OnRconLoginAttempt(ip[], password[], success)
{
	return 1;
}

public OnPlayerUpdate(playerid)
{
	gAFK_update[playerid] = 0;
	return 1;
}

public OnPlayerStreamIn(playerid, forplayerid)
{
	return 1;
}

public OnPlayerStreamOut(playerid, forplayerid)
{
	return 1;
}

public OnVehicleStreamIn(vehicleid, forplayerid)
{
	new color1, color2;
	new result[64];

    get_vehicle_value(vehicleid, "color1", "veh_data", result);
    color1 = strval(result);
    get_vehicle_value(vehicleid, "color2", "veh_data", result);
    color2 = strval(result);
	ChangeVehicleColor(vehicleid, color1, color2);
	return 1;
}

public OnVehicleStreamOut(vehicleid, forplayerid)
{
	return 1;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
	  case 756:
	  {
        if(response)
        {
		  new imes[254];
		  new lang_name[32];
		  new mes[256];
		  new len;

		  if(listitem == 0) //если оставить какой есть
		  {
		    if(gPlayerPasswordRequest[playerid] > 0)
				gPlayerPasswordRequest[playerid] = 1;
			return 1;
		  }

		  len = strlen(inputtext);
		  if(len < 2)
		  {
   	        imessage(imes, "ERROR_MESSAGE", gPlayerLang[playerid]);
            SendClientMessage(playerid, 0xFFCC00AA, imes);
		    if(gPlayerPasswordRequest[playerid] > 0)
				gPlayerPasswordRequest[playerid] = 1;
			return 1;
		  }
		  imes[0] = inputtext[0];
  		  imes[1] = inputtext[1];
  		  imes[2] = '\0';
		  for(new i = 0; i < gLangsNumber; ++i)
		  {
			if(strcmp(imes, gAllLangs[i]) == 0)
			{
              gPlayerLang[playerid][0] = gAllLangs[i][0];
              gPlayerLang[playerid][1] = gAllLangs[i][1];
              gPlayerLang[playerid][2] = '\0';
              set_player_db_lang(playerid, gPlayerLang[playerid]);
              setplayerlang(playerid, gPlayerLang[playerid]);
   	          imessage(imes, "NEWLANG", gPlayerLang[playerid]);
   	          imessage(lang_name, "LANGUAGE_NAME", gPlayerLang[playerid]);
		      format(mes, sizeof(mes), "%s%s", imes, lang_name);
              SendClientMessage(playerid, 0xFFCC00AA, mes);
		      if(gPlayerPasswordRequest[playerid] > 0)
				gPlayerPasswordRequest[playerid] = 1;
			  update_statistic_data(playerid, false);
              return 1;
			}
		  }
	      imessage(imes, "ERROR_MESSAGE", gPlayerLang[playerid]);
          SendClientMessage(playerid, 0xFFCC00AA, imes);
		  if(gPlayerPasswordRequest[playerid] > 0)
			gPlayerPasswordRequest[playerid] = 1;
		  return 1;
		}
	  }
	  case 456:
	  {
        if(response)
        {
            new ret;
            new msg[128];
            new name[MAX_PLAYER_NAME];
            
			GetPlayerName(playerid, name, sizeof(name));
            
		    if(strlen(inputtext) < 6)
		    {
				//"замораживаем" игрока
				TogglePlayerControllable(playerid, 0);
                gPlayerPasswordCheckCount[playerid]++;
                if(gPlayerPasswordCheckCount[playerid] >= 3)
                {
				    format(msg, sizeof(msg), "%s(id:%d) seems to be a HACKER! SHORT PASSWORD (kick)", name, playerid);
				    update_sensor_messager_cheat(msg);
					gPlayerCheaterLevel[playerid] = gMaxAnticheat;
	                gPlayerPasswordRequest[playerid] = 0;
				}
				else
				{
	                gPlayerPasswordRequest[playerid] = 1;
				    format(msg, sizeof(msg), "%s(id:%d) seems to be a HACKER! SHORT PASSWORD", name, playerid);
				    update_sensor_messager_cheat(msg);
			        SetTimer("player_login_menu", 10000, false);
				}
				imes_simple_single(playerid, 0xFFFF00FF, "TOO_SHORT_PASSWORD");
		        return 1;
		    }

			ret = player_login(playerid, inputtext);
		    if(ret == -1)
		    {
				//"замораживаем" игрока
				TogglePlayerControllable(playerid, 0);
                gPlayerPasswordCheckCount[playerid]++;
                if(gPlayerPasswordCheckCount[playerid] == 3)
				{
				    format(msg, sizeof(msg), "%s(id:%d) seems to be a HACKER! WRONG PASSWORD (kick)", name, playerid);
				    update_sensor_messager_cheat(msg);
					gPlayerCheaterLevel[playerid] = gMaxAnticheat;
	                gPlayerPasswordRequest[playerid] = 0;
				}
				else
				{
				    format(msg, sizeof(msg), "%s(id:%d) seems to be a HACKER! WRONG PASSWORD", name, playerid);
				    update_sensor_messager_cheat(msg);
	                gPlayerPasswordRequest[playerid] = 1;
			        SetTimer("player_login_menu", 10000, false);
				}
				imes_simple_single(playerid, 0xFF0033FF, "WRONG_PASSWORD");
			}
			else if(ret == -2)
			{
				//"замораживаем" игрока
				TogglePlayerControllable(playerid, 0);
			    //вы забанены
				imes_simple_single(playerid, 0xFF0033FF, "YOU_ARE_BANNED");
			    format(msg, sizeof(msg), "Banned player %s(id:%d) is trying to come in!", name, playerid);
			    update_sensor_messager_cheat(msg);
			    mark_player_as_banned(playerid, 168); //для блокировки повторной регистрации забаненного на неделю
				gCheatersList[playerid] = playerid;
				return 1;
			}
			else if(ret == -3)
			{
				//"замораживаем" игрока
				TogglePlayerControllable(playerid, 0);
			    //вы не можете зайти на сервер
				imes_simple_single(playerid, 0xFF0033FF, "YOU_CANT_BE_REGISTERED");
			    format(msg, sizeof(msg), "New player %s(id:%d) is trying to be created!", name, playerid);
			    update_sensor_messager_cheat(msg);
				gCheatersList[playerid] = playerid;
				return 1;
			}
			else if(ret > 0)
			{
				TogglePlayerSpectating(playerid, 0);
		        gPlayerPasswordCheckCount[playerid] = 0;
			    SetPlayerTeam(playerid, 0);
				imes_simple_single(playerid, 0xFFFF00FF, "YOU_ARE_WELCOME");
	//			imes_simple_single(playerid, 0xFF3300, "HELLO_MESSAGE");
				SpawnPlayer(playerid);
				show_help_for_player(playerid);
			    set_player_db_land(playerid, gPlayerLand[playerid]);
			    set_player_db_lang(playerid, gPlayerLang[playerid]);
			    if(strlen(gPlayerCountry[playerid]) > 0)
				    set_player_db_country(playerid, gPlayerCountry[playerid]);
			    if(strlen(gPlayerCity[playerid]) > 0)
				    set_player_db_city(playerid, gPlayerCity[playerid]);
	    		gIsPlayerLogin[playerid] = 1;
			}
		}
		else
		{
			new name[64];
			new msg[256];

			//"замораживаем" игрока
			TogglePlayerControllable(playerid, 0);
			//сообщение в низ экрана
			GetPlayerName(playerid, name, sizeof(name));
			format(msg, sizeof(msg), "%s(id:%d) has canceled a login (quick kick)", name, playerid);
			update_sensor_messager_cheat(msg);
			Kick(playerid);
			//гарантируем игроку кик
			//gPlayerCheaterLevel[playerid] = gMaxAnticheat;
		}

    	return 1;
	  }
	  case 4458:
	  {
		new imes[254];
		new lang_name[32];
		new mes[256];
  	    new len;

  	    gShowSecond[playerid] = 0;

        if(response)
        {
		  len = strlen(inputtext);
		  if(len < 2)
		  {
   	        imessage(imes, "ERROR_MESSAGE", gPlayerLang[playerid]);
            SendClientMessage(playerid, 0xFFCC00AA, imes);
			return 1;
		  }
		  imes[0] = inputtext[0];
  		  imes[1] = inputtext[1];
  		  imes[2] = '\0';
		  for(new i = 0; i < gLangsNumber; ++i)
		  {
			if(strcmp(imes, gAllLangs[i]) == 0)
			{
              gPlayerLangSecond[playerid][0] = gAllLangs[i][0];
              gPlayerLangSecond[playerid][1] = gAllLangs[i][1];
              gPlayerLangSecond[playerid][2] = '\0';
              gShowSecond[playerid] = 1;
   	          imessage(imes, "LANG_FOR_TRACE", gPlayerLang[playerid]);
   	          imessage(lang_name, "LANGUAGE_NAME", gPlayerLangSecond[playerid]);
		      format(mes, sizeof(mes), "%s%s", imes, lang_name);
              SendClientMessage(playerid, 0xFFCC00AA, mes);
              return 1;
			}
		  }
	      imessage(imes, "NO_LANG_FOR_TRACE", gPlayerLang[playerid]);
          SendClientMessage(playerid, 0xFFCC00AA, imes);
  		  gPlayerLangSecond[playerid][0] = '\0';
  		  gPlayerLangSecond[playerid][1] = '\0';
  		  gPlayerLangSecond[playerid][2] = '\0';
		  return 1;
		}
		else
		{
	      imessage(imes, "NO_LANG_FOR_TRACE", gPlayerLang[playerid]);
          SendClientMessage(playerid, 0xFFCC00AA, imes);
  		  gPlayerLangSecond[playerid][0] = '\0';
  		  gPlayerLangSecond[playerid][1] = '\0';
  		  gPlayerLangSecond[playerid][2] = '\0';
		  return 1;
		}
	  }
	  case 4461:
	  {
        if(response)
        {
		  SendClientMessage(playerid, 0xFFCC00, "OK");
        }
        return 1;
	  }
	  case 5511:
	  {
        if(response)
        {
            new imes[128];
            new mes[128];
            
            mark_player_as_unbanned(inputtext);
			for(new i = 0; i < MAX_PLAYERS; ++i)
			{
			    if(!IsPlayerNPC(i) && IsPlayerConnected(i))
			    {
			        for(new j = 0; j < strlen(inputtext); ++j)
			        {
			            if(inputtext[j] == ' ')
			                inputtext[j] = '\0';
			        }
					imessage(imes, "PLAYER_IS_UNBANNED", gPlayerLang[i]);
					format(mes, sizeof(mes), imes, inputtext);
					SendClientMessage(i, 0x00FF00FF, mes);
				}
			}
        }
        return 1;
	  }

	  default: return 1;
    }
	return 1;
}

public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
    new vhid, i, is_spectate;

    if( IsPlayerAdmin(playerid) || (gAdminLevel[playerid] > 8) )
    {
        if(playerid == clickedplayerid)
        {
			hide_spectate_data(playerid);
	        TogglePlayerSpectating(playerid, 0);
	        for(i = 0; i < MAX_PLAYERS; ++i)
	        {
	            gPsp[i][playerid] = 0;
	        }
	        load_player_position(playerid);
            return 1;
        }
    
        is_spectate = 1;

		for(i = 0; i < MAX_PLAYERS; ++i)
		{
			if(gPsp[i][playerid] == 1)
			{
			    is_spectate = 0;
			    break;
			}
	    }

		if(is_spectate && IsPlayerSpawned(playerid))
	        save_player_position(playerid);

        TogglePlayerSpectating(playerid, 1);
        if(IsPlayerInAnyVehicle(clickedplayerid))
        {
            vhid = GetPlayerVehicleID(clickedplayerid);
            PlayerSpectateVehicle(playerid, vhid, SPECTATE_MODE_NORMAL);

        }
        else
        {
		    PlayerSpectatePlayer(playerid, clickedplayerid, SPECTATE_MODE_NORMAL);
		}
		for(i = 0; i < MAX_PLAYERS; ++i)
		{
		    gPsp[i][playerid] = 0;
		}
        gPsp[clickedplayerid][playerid] = 1;
        show_spectate_data(playerid, clickedplayerid, true);
	}
		
	return 1;
}

public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
	new j,k,i,cell,res,vehicleid;
	new Float:x,Float:y,Float:z;
	new extra[128];
	
	//кнопка отмены
    if(playertextid == gTdMenu[playerid][1])
    {
		hide_menu(playerid);
		return 1;
    }

	strdel(extra, 0, sizeof(extra));

	//кнопка вопроса
    if(playertextid == gTdMenu[playerid][3])
    {
        new name[128];
        new value;
		new owner[128], owner_country[128], last_owner[128], last_owner_country[128], last_time[128], type_name[128];

        cell = is_one_inventory_cell_selected(playerid, INVENTORY_AREA);
		if(cell >= 0)
		{
		    //получаем внутримодовое имя вещи и значение
			get_object_data_all(playerid, cell, INVENTORY_AREA, name, value, owner, owner_country, last_owner, last_owner_country, last_time, type_name);
		}
		else
		{
			cell = is_one_inventory_cell_selected(playerid, GROUND_AREA);
			if(cell >= 0)
			{
			    //получаем внутримодовое имя вещи и значение
				get_object_data_all(playerid, cell, GROUND_AREA, name, value, owner, owner_country, last_owner, last_owner_country, last_time, type_name);
			}
			else
			{
				cell = is_one_inventory_cell_selected(playerid, VEHICLE_AREA);
				if(cell >= 0)
				{
				    //получаем внутримодовое имя вещи и значение
					get_object_data_all(playerid, cell, VEHICLE_AREA, name, value, owner, owner_country, last_owner, last_owner_country, last_time, type_name);
				}
				else
				{
					cell = is_one_inventory_cell_selected(playerid, BAG_AREA);
					if(cell >= 0)
					{
					    //получаем внутримодовое имя вещи и значение
						get_object_data_all(playerid, cell, BAG_AREA, name, value, owner, owner_country, last_owner, last_owner_country, last_time, type_name);
					}
				}
			}
		}

		stop_all_rotates(playerid);
		if(cell >= 0)
		{
	        new buff1[128], buff2[64], object_meaning_str[128], object_meaning[128], meaning_name[64], title[64], mes[512], ok_mes[32];
	        new owner_str[128], last_owner_str[128], last_time_str[128];

			strdel(mes, 0, sizeof(mes));
			//получаем формат строки
			imessage(buff1, "OBJECT_NAME_FOR_ABOUT", gPlayerLang[playerid]);
			imessage(owner_str, "OBJECT_OWNER_FOR_ABOUT", gPlayerLang[playerid]);
			imessage(last_owner_str, "OBJECT_LAST_FOR_ABOUT", gPlayerLang[playerid]);
			imessage(last_time_str, "OBJECT_TIME_FOR_ABOUT", gPlayerLang[playerid]);
			format(owner, sizeof(owner), owner_str, owner, owner_country);
			format(last_owner, sizeof(owner), last_owner_str, last_owner, last_owner_country);
			format(last_time, sizeof(owner), last_time_str, last_time);

			if(strlen(name) > 0)
			{
			    //получаем обычное имя вещи
				imessage(buff2, name, gPlayerLang[playerid]);

			    //получаем нименование состояния вещи ("количество", "состояние" и т.д.)
			    format(meaning_name, sizeof(meaning_name), "%s_VALUE", name);
			    //вот сюда бы проверочку полученного результата imessage()!
			    //...
				imessage(object_meaning, meaning_name, gPlayerLang[playerid]);
				//...

				//получаем окончательную строчку ссостояния вещи
				format(object_meaning_str, sizeof(object_meaning_str), object_meaning, value);

				//получаем описание вещи
			    //получаем нименование состояния вещи ("количество", "состояние" и т.д.)
			    format(meaning_name, sizeof(meaning_name), "%s_ABOUT", name);
			    //вот сюда бы проверочку полученного результата imessage()!
			    //...
				imessage(object_meaning, meaning_name, gPlayerLang[playerid]);
				//...

				//формируем окончательное сообщение
				format(mes, sizeof(mes), buff1, strlen(buff2)>0?buff2:name, "\n", object_meaning_str, "\n\n", owner, "\n\n", last_owner, "\n", last_time, "\n\n", object_meaning);
			}
			else
			{
				imessage(object_meaning, "DEFAULT_OBJECT_MEANING_STRING", gPlayerLang[playerid]);
				//получаем окончательную строчку ссостоянием вещи
				format(object_meaning_str, sizeof(object_meaning_str), object_meaning, value);
				//формируем окончательное сообщение
				format(mes, sizeof(mes), buff1, strlen(name)>0?name:"unknown", "\n", "-", "\n", "-", "\n", "-", "\n", object_meaning_str, "\n\n", "-");
			}
			imessage(title, "TITLE_FOR_ABOUT_OBJECT", gPlayerLang[playerid]);
			imessage(ok_mes, "OK_MESSAGE", gPlayerLang[playerid]);
			ShowPlayerDialog(playerid, 1111, DIALOG_STYLE_MSGBOX, title, mes, ok_mes, "");
		}
		return 1;
    }

	//кнопка "применить" (или кулак)
    if(playertextid == gTdMenu[playerid][4])
    {
        set_player_extra(playerid, extra);
        //подсчитываем количество выделенных объектов и решаем - надо ли пытаться создавать композит
        cell = is_one_inventory_cell_selected(playerid, INVENTORY_AREA);
        if(cell >= 0) //выбрана одна ячейка инвентаря
        {
            //используем объект в ячейке
            apply_one_cell(playerid, -1, cell, INVENTORY_AREA);

            //обновляем содержимое ячейки
			put_object(playerid, cell);

			stop_all_rotates(playerid); //сброс выбора
			return 1;
        }
		else //выбрано более одной ячейки
		{
		    res = create_composite_object(playerid, extra, cell);
	        if(res > 0)
	        {
	            //если обновилось текущее оружие - обновим патроны
	            apply_one_cell(playerid, -1, cell, INVENTORY_AREA);
			}
			else if(res == -1)
			{
				imes_simple_single(playerid, 0xFF5555FF, "MAX_VALUE_ACHIEVED");
			}

			if(cell < 0) //объект не создан
			{
				//здесь пытаемся добавить элементы к композитному объекту
				//...
	  		}
			else //объект создан
			{
			    for(i = 0; i < MAX_INVENTORY_ON_PLAYER; ++i)
			    {
			        if(gRotate[playerid][i] > 0 && i != cell) //проверка на (cell == i) здесь не требуется!
			        {
						//освобождаем одну ячейку инвентаря
						//если прежний и новый объекты совпадают по типу, то прежний остаётся в своей ячейке в инвентаре
						//т.к. функция remove_object предварительно проверяет содержимое ячейки инвентаря перед удалением
						//текстдравов, то прежние текстдравы объекта останутся на своём месте!
						//remove_object(playerid, i, true);
						put_object(playerid, i);
					}
					//обновляем одну ячейку инвентаря (gInventoryItem[playerid][cell] фактически уже инициализирован)
					put_object(playerid, cell);
				}
			}
		}

		vehicleid = gVehicleMenuShow[playerid];

		cell = is_one_inventory_cell_selected(playerid, VEHICLE_AREA);
		if(cell >= 0)
		{
            //используем объект в ячейке
            apply_one_cell(playerid, vehicleid, cell, VEHICLE_AREA);

            //обновляем содержимое ячейки
			remove_vehicle_object(playerid, vehicleid, cell);
			put_vehicle_object(playerid, vehicleid, cell);

            stop_all_rotates(playerid); //сброс выбора
            return 1;
		}
		else
		{
	        set_player_extra(playerid, extra);
	        res = create_composite_object_veh(playerid, vehicleid, extra, cell);
	        if(res > 0)
	        {
	            //если обновилось текущее оружие - обновим патроны
	            apply_one_cell(playerid, vehicleid, cell, VEHICLE_AREA);
			}
			else if(res < 0)
			{
				imes_simple_single(playerid, 0xFF5555FF, "MAX_VALUE_ACHIEVED");
			}

			if(cell < 0) //объект не создан
			{
				//здесь пытаемся добавить элементы к композитному объекту
				//...
	  		}
			else //объект создан
			{
			    for(i = 0; i < gVeh[vehicleid][1]; ++i)
			    {
			        if(gRotateVehicle[playerid][i] > 0) //проверка на (cell == i) здесь не требуется!
			        {
						//освобождаем одну ячейку инвентаря
						//если прежний и новый объекты совпадают по типу, то прежний остаётся в своей ячейке в инвентаре
						//т.к. функция remove_object предварительно проверяет содержимое ячейки инвентаря перед удалением
						//текстдравов, то прежние текстдравы объекта останутся на своём месте!
						remove_vehicle_object(playerid, vehicleid, i);
					}
				}
				//обновляем одну ячейку инвентаря (gInv[playerid][cell] фактически уже инициализирован)
				put_vehicle_object(playerid, vehicleid, cell);
			}
		}

		cell = is_one_inventory_cell_selected(playerid, GROUND_AREA);
		if(cell >= 0)
		{
            //используем объект в ячейке
            apply_one_cell(playerid, -1, cell, GROUND_AREA);

            //обновляем содержимое ячейки
			//update_objects_menu(playerid);
			create_views_of_items(playerid, -1, -1, GROUND_AREA);
			update_neighbors_objects_menu(playerid);

            stop_all_rotates(playerid); //сброс выбора
            return 1;
		}
		else
		{
	        set_player_extra(playerid, extra);
	        res = create_composite_object_obj(playerid, extra);

	        if(res < 0) //объект не создан
			{
				//здесь пытаемся добавить элементы к композитному объекту
				//...
				if(res == -3)
					imes_simple_single(playerid, 0xFF5555FF, "MAX_VALUE_ACHIEVED");
	  		}
			else if(res >= 0) //объект создан
			{
				apply_some_cell(playerid, -1, res, GROUND_AREA);
				create_views_of_items(playerid, -1, -1, GROUND_AREA);
		        //update_objects_menu(playerid);
		        update_neighbors_objects_menu(playerid);
			}
		}

		cell = is_one_inventory_cell_selected(playerid, BAG_AREA);
		if(cell >= 0)
		{
            //используем объект в ячейке
            apply_one_cell(playerid, -1, cell, BAG_AREA);

            //обновляем содержимое ячейки
			remove_bag_object(playerid, cell);
			put_bag_object(playerid, cell);

            stop_all_rotates(playerid); //сброс выбора
            return 1;
		}
		else
		{
	        set_player_extra(playerid, extra);
	        res = create_composite_object_bag(playerid, extra, cell);
	        if(res > 0)
	        {
	            //если обновилось текущее оружие - обновим патроны
	            //тут надо бы разобраться..
	            apply_one_cell(playerid, -1, cell, BAG_AREA);
			}
			else if(res == -3)
			{
				imes_simple_single(playerid, 0xFF5555FF, "MAX_VALUE_ACHIEVED");
			}

			if(cell < 0) //объект не создан
			{
				//здесь пытаемся добавить элементы к композитному объекту
				//...
	  		}
			else //объект создан
			{
			    for(i = 0; i < gBag[playerid][0]; ++i)
			    {
			        if(gRotateBag[playerid][i] > 0) //проверка на (cell == i) здесь не требуется!
			        {
						//освобождаем одну ячейку инвентаря
						//если прежний и новый объекты совпадают по типу, то прежний остаётся в своей ячейке в инвентаре
						//т.к. функция remove_object предварительно проверяет содержимое ячейки инвентаря перед удалением
						//текстдравов, то прежние текстдравы объекта останутся на своём месте!
						//remove_bag_object(playerid, i);
						put_bag_object(playerid, i);
					}
				}
				//обновляем одну ячейку инвентаря рюкзака (gBagObj[playerid][cell] фактически уже инициализирован)
				put_bag_object(playerid, cell);
			}
		}
		
		//остановим вращение (сбросим выбор) объектов
		if(cell < 0)
		{
			stop_all_rotates(playerid);
		}

		return 1;
    }

	//кнопка "гаечный ключ"
    if(playertextid == gTdMenu[playerid][5])
    {
		cell = is_one_inventory_cell_selected(playerid, INVENTORY_AREA);
        if(cell >= 0 && (res = disassemble_cell_object(playerid, cell)) >= 0)
        {
//            destroy_menu(playerid);
//            create_inventory_menu(playerid);
//            show_inventory(playerid, IsPlayerInVehicleReal(playerid));
		    for(i = 0; i < MAX_INVENTORY_ON_PLAYER; ++i)
		    {
				//освобождаем одну ячейку инвентаря
				//если прежний и новый объекты совпадают по типу, то прежний остаётся в своей ячейке в инвентаре
				//т.к. функция remove_object предварительно проверяет содержимое ячейки инвентаря перед удалением
				//текстдравов, то прежние текстдравы объекта останутся на своём месте!
				//remove_object(playerid, i, true);

				//обновляем одну ячейку инвентаря (gInventoryItem[playerid][cell] фактически уже инициализирован)
				put_object(playerid, i);
			}

		    for(i = 0; i < gBag[playerid][0]; ++i)
		    {
				//освобождаем одну ячейку инвентаря
				//если прежний и новый объекты совпадают по типу, то прежний остаётся в своей ячейке в инвентаре
				//т.к. функция remove_object предварительно проверяет содержимое ячейки инвентаря перед удалением
				//текстдравов, то прежние текстдравы объекта останутся на своём месте!
				remove_bag_object(playerid, i);
				//обновляем одну ячейку инвентаря (gBagItem[playerid][cell] фактически уже инициализирован)
				put_bag_object(playerid, i);
			}
        }

		vehicleid = gVehicleMenuShow[playerid];

		cell = is_one_inventory_cell_selected(playerid, VEHICLE_AREA);
        if(cell >= 0 && (res = disassemble_cell_object_veh(vehicleid, cell)) >= 0)
        {
//            destroy_menu(playerid);
//            create_inventory_menu(playerid);
//            show_inventory(playerid, IsPlayerInVehicleReal(playerid));
		    for(i = 0; i < gVeh[vehicleid][1]; ++i)
		    {
				//освобождаем одну ячейку инвентаря
				//если прежний и новый объекты совпадают по типу, то прежний остаётся в своей ячейке в инвентаре
				//т.к. функция remove_vehicle_object предварительно проверяет содержимое ячейки инвентаря перед удалением
				//текстдравов, то прежние текстдравы объекта останутся на своём месте!
				remove_vehicle_object(playerid, vehicleid, i);
				//обновляем одну ячейку инвентаря (gVehObj[vehicleid][cell] фактически уже инициализирован)
				put_vehicle_object(playerid, vehicleid, i);
			}
        }

		cell = is_one_inventory_cell_selected(playerid, GROUND_AREA);
        if(cell >= 0)
        {
			res = disassemble_ground_object(playerid, cell);
			//тут обновить бы меню..
			//...
		}

		cell = is_one_inventory_cell_selected(playerid, BAG_AREA);
        if(cell >= 0 && (res = disassemble_cell_object_bag(playerid, cell)) >= 0)
        {
		    for(i = 0; i < gBag[playerid][0]; ++i)
		    {
				//освобождаем одну ячейку инвентаря рюкзака
				//если прежний и новый объекты совпадают по типу, то прежний остаётся в своей ячейке в инвентаре
				//т.к. функция remove_bag_object предварительно проверяет содержимое ячейки инвентаря перед удалением
				//текстдравов, то прежние текстдравы объекта останутся на своём месте!
				remove_bag_object(playerid, i);
				//обновляем одну ячейку инвентаря (gBagObj[playerid][cell] фактически уже инициализирован)
				put_bag_object(playerid, i);
			}
        }
		
		//остановим вращение (сбросим выбор) объектов
		if(res < 0 || cell < 0)
		{
			stop_all_rotates(playerid);
		}

		//обновим объекты рядом с другими игроками
		update_neighbors_objects_menu(playerid);
		if(!IsPlayerInAnyVehicle(playerid))
		{
			GetPlayerPos(playerid, x, y, z);
			//обновляем стример игрока
		    SetPlayerPos(playerid, x+0.001, y, z);
		}
		else
		{
			GetVehiclePos(vehicleid, x, y, z);
		    SetVehiclePos(vehicleid, x+0.001, y, z);
		}
		//обновляем меню игрока "на земле"
		update_objects_menu(playerid);

		return 1;
    }

	//звук при клике на ячейке
	PlayerPlaySound(playerid, 40407, 0, 0, 0);

	for(j = 0; j < MAX_INVENTORY_ON_PLAYER; ++j)
	for(k = 0; k < MAX_TURNS_OF_PREVIEW; ++k)
	{
		//проверка и действие при клике на объекте инвентаря
	    if(gInventoryMenuShow[playerid] > 0 && playertextid == gTdInventory[playerid][j][k])
	    {
			//если ячейка пустая - пытаемся в неё что-нибудь положить
	        if(gInventoryItem[playerid][j][db_id] < 0)
	        {
		        cell = is_one_inventory_cell_selected(playerid, INVENTORY_AREA);
	            if(cell >= 0)
	            {
	                replace_inventory(playerid, cell, j);
		            return 1;
	            }

		        cell = is_one_inventory_cell_selected(playerid, GROUND_AREA);
	            if(cell >= 0)
	            {
	                take_object(playerid, j, cell);
		            return 1;
	            }

	            if(gVehicleMenuShow[playerid] > 0)
	            {
			        cell = is_one_inventory_cell_selected(playerid, VEHICLE_AREA);
		            if(cell >= 0)
		            {
		                take_from_vehicle(playerid, gVehicleMenuShow[playerid], j, cell);
			            return 1;
		            }
           		}

	            if(gBagMenuShow[playerid] > 0)
	            {
			        cell = is_one_inventory_cell_selected(playerid, BAG_AREA);
		            if(cell >= 0)
		            {
		                take_from_bag(playerid, j, cell);
			            return 1;
		            }
           		}
	            return 1;
		    }

	        //заставляем объект вращаться, либо останавливаем
	        if(gRotate[playerid][j] == 0)
	        {
				if(gTdInventory[playerid][j][0] != PlayerText:INVALID_TEXT_DRAW)
					PlayerTextDrawHide(playerid, gTdInventory[playerid][j][0]);
				gIndex[playerid][j] = 0;
				gRotate[playerid][j] = 1;
			}
			else
			{
			    gRotate[playerid][j] = 0;
			    if(gTdInventory[playerid][j][gIndex[playerid][j]] != PlayerText:INVALID_TEXT_DRAW)
					PlayerTextDrawHide(playerid, gTdInventory[playerid][j][gIndex[playerid][j]]);
				if(gTdInventory[playerid][j][0] != PlayerText:INVALID_TEXT_DRAW)
					PlayerTextDrawShow(playerid, gTdInventory[playerid][j][0]);
				gIndex[playerid][j] = 0;
			}
			return 1;
	    }
	 }
	 
	 
	for(j = 0; j < MAX_INVENTORY_ON_GROUND; ++j)
	for(k = 0; k < MAX_TURNS_OF_PREVIEW; ++k)
	{
		//проверка и действие при клике на объекте меню земли
	    if(gObjectsMenuShow[playerid] > 0 && playertextid == gTdObject[playerid][j][k])
	    {
			//если ячейка пустая - пытаемся в неё что-нибудь положить
	        if(gGroundItem[playerid][j][db_id] < 0)
	        {
		        cell = is_one_inventory_cell_selected(playerid, INVENTORY_AREA);
	            if(cell >= 0)
	            {
	                drop_object(playerid, cell, j);
		            return 1;
	            }

		        cell = is_one_inventory_cell_selected(playerid, BAG_AREA);
	            if(cell >= 0)
	            {
	                drop_bag_object(playerid, cell, j);
		            return 1;
	            }
	            return 1;
		    }

	        //заставляем объект вращаться, либо останавливаем
	        if(gRotateObject[playerid][j] == 0)
	        {
	            if(gTdObject[playerid][j][0] != PlayerText:INVALID_TEXT_DRAW)
					PlayerTextDrawHide(playerid, gTdObject[playerid][j][0]);
				gIndexObject[playerid][j] = 0;
				gRotateObject[playerid][j] = 1;
			}
			else
			{
			    gRotateObject[playerid][j] = 0;
			    if(gTdObject[playerid][j][gIndexObject[playerid][j]] != PlayerText:INVALID_TEXT_DRAW)
					PlayerTextDrawHide(playerid, gTdObject[playerid][j][gIndexObject[playerid][j]]);

				if(gTdObject[playerid][j][0] != PlayerText:INVALID_TEXT_DRAW)
					PlayerTextDrawShow(playerid, gTdObject[playerid][j][0]);
				gIndexObject[playerid][j] = 0;
			}
			return 1;
	    }
    }

	//проверка и действие при клике на объекте инвентаря авто
	for(j = 0; j < MAX_INVENTORY_ON_VEHICLE; ++j)
	for(k = 0; k < MAX_TURNS_OF_PREVIEW; ++k)
	{
	    if(gVehicleMenuShow[playerid] > 0 && playertextid == gTdVehicle[playerid][j][k])
	    {
	        vehicleid = gVehicleMenuShow[playerid];

			//если ячейка пустая - пытаемся в неё что-нибудь положить
	        if(gVehicleItem[vehicleid][j][db_id] < 0)
	        {
		        cell = is_one_inventory_cell_selected(playerid, INVENTORY_AREA);
	            if(cell >= 0)
	            {
	                put_in_vehicle(playerid, vehicleid, cell, j);
		            return 1;
	            }

		        cell = is_one_inventory_cell_selected(playerid, VEHICLE_AREA);
	            if(cell >= 0)
	            {
	                replace_vehicle_inventory(playerid, vehicleid, cell, j);
		            return 1;
	            }

		        cell = is_one_inventory_cell_selected(playerid, BAG_AREA);
	            if(cell >= 0)
	            {
		            put_in_veh_from_bag(playerid, vehicleid, cell, j);
		            return 1;
				}

	            return 1;
		    }

	        //заставляем объект вращаться, либо останавливаем
	        if(gRotateVehicle[playerid][j] == 0)
	        {
	            if(gTdVehicle[playerid][j][0] != PlayerText:INVALID_TEXT_DRAW)
					PlayerTextDrawHide(playerid, gTdVehicle[playerid][j][0]);
				gIndexVehicle[playerid][j] = 0;
				gRotateVehicle[playerid][j] = 1;
			}
			else
			{
			    gRotateVehicle[playerid][j] = 0;
			    if(gTdVehicle[playerid][j][gIndexVehicle[playerid][j]] != PlayerText:INVALID_TEXT_DRAW)
					PlayerTextDrawHide(playerid, gTdVehicle[playerid][j][gIndexVehicle[playerid][j]]);
				if(gTdVehicle[playerid][j][0] != PlayerText:INVALID_TEXT_DRAW)
					PlayerTextDrawShow(playerid, gTdVehicle[playerid][j][0]);
				gIndexVehicle[playerid][j] = 0;
			}
			return 1;
	    }
	}

	//проверка и действие при клике на объекте инвентаря рюкзака
	for(j = 0; j < gBag[playerid][0]; ++j)
	for(k = 0; k < MAX_TURNS_OF_PREVIEW; ++k)
	{
	    if(gBagMenuShow[playerid] > 0 && playertextid == gTdBag[playerid][j][k])
	    {
			//если ячейка пустая - пытаемся в неё что-нибудь положить
	        if(gBagItem[playerid][j][db_id] < 0)
	        {
		        cell = is_one_inventory_cell_selected(playerid, INVENTORY_AREA);
	            if(cell >= 0)
	            {
	                put_in_bag(playerid, cell, j);
		            return 1;
	            }

		        cell = is_one_inventory_cell_selected(playerid, VEHICLE_AREA);
	            if(cell >= 0)
	            {
		            vehicleid = gVehicleMenuShow[playerid];
					put_in_bag_from_veh(playerid, vehicleid, cell, j);
		            return 1;
	            }

		        cell = is_one_inventory_cell_selected(playerid, GROUND_AREA);
	            if(cell >= 0)
	            {
	                put_in_bag_from_grnd(playerid, cell, j);
		            return 1;
	            }

		        cell = is_one_inventory_cell_selected(playerid, BAG_AREA);
	            if(cell >= 0)
	            {
	                replace_bag_inventory(playerid, cell, j);
		            return 1;
	            }

	            return 1;
		    }

	        //заставляем объект вращаться, либо останавливаем
	        if(gRotateBag[playerid][j] == 0)
	        {
	            if(gTdBag[playerid][j][0] != PlayerText:INVALID_TEXT_DRAW)
					PlayerTextDrawHide(playerid, gTdBag[playerid][j][0]);
				gIndexBag[playerid][j] = 0;
				gRotateBag[playerid][j] = 1;
			}
			else
			{
			    gRotateBag[playerid][j] = 0;
			    if(gTdBag[playerid][j][gIndexBag[playerid][j]] != PlayerText:INVALID_TEXT_DRAW)
					PlayerTextDrawHide(playerid, gTdBag[playerid][j][gIndexBag[playerid][j]]);
				if(gTdBag[playerid][j][0] != PlayerText:INVALID_TEXT_DRAW)
					PlayerTextDrawShow(playerid, gTdBag[playerid][j][0]);
				gIndexBag[playerid][j] = 0;
			}
			return 1;
	    }
	}
    return 1;
}

public afk_check()
{
	for(new playerid = 0; playerid < MAX_PLAYERS; ++playerid)
	{
	    if(IsPlayerConnected(playerid))
	    {
		    gAFK[playerid] = gAFK_update[playerid];
		    gAFK_update[playerid] = 1;
		}
	}
}

//обновить содержимое инвентаря
public alt_post_handle(playerid)
{
	for(new i = 0; i < MAX_INVENTORY_ON_PLAYER; ++i)
	{
		if(gInventoryItem[playerid][i][db_id] > 0 && gCachePlayerInventory[playerid][i][db_id] == -1)
			put_object(playerid, i);
	}
	if(gBag[playerid][1] > 0)
	{
		for(new i = 0; i < gBag[playerid][0]; ++i)
		{
			if(gBagItem[playerid][i][db_id] > 0 && gCacheBagInventory[playerid][i][db_id] == -1)
				put_bag_object(playerid, i);
		}
	}

	update_neighbors_objects_menu(playerid);

	gAltWait[playerid] = 0;

	return 1;
}

//метки игроков в зоне 51
public update_player_zone_mark()
{
	new i, j, col, Float:height;
	new Float:x, Float:y, Float:z;
	new Float:x0, Float:y0, Float:z0, Float:path, Float:speed;
	new name[64];
	static Float:MarkerXY[MAX_PLAYERS][2];

	for(i = 0; i < MAX_PLAYERS; ++i)
	{
		if(IsPlayerSpawned(i) && gAntiRadar[i] < 0)
		{
			strdel(name, 0, sizeof(name)-1);
			GetPlayerName(i, name, sizeof(name));
	        col = GetPlayerColor(i);
	        GetPlayerPos(i, x, y, z);
	        
	        if(x > 3000.0) x = 3000.0;
			if(x < -3000.0)x = -3000.0;
			if(y > 3000.0) y = 3000.0;
			if(y < -3000.0) y = -3000.0;

   			for(j = 0, height = 0.0; j < i; ++j)
			{
			    if(IsPlayerInRangeOfPoint(j, 200, x, y, z))
			        height = floatadd(height, 0.08);
			}

			col = (col>>8)|(0xFF000000);
			y = floatsub(221.7,floatmul(3.45,floatdiv(floatadd(3000.0,y),6000.0)));
			x = floatadd(1821.1,floatmul(3.45,floatdiv(floatadd(3000.0,x),6000.0)));

	        if(gPlayerMarker[i] != INVALID_OBJECT_ID)
	        {
	            GetDynamicObjectPos(gPlayerMarker[i], y0, x0, z0);
	            path = VectorSize(y0-y, x0-x, 0);
				speed = floatdiv(path,floatdiv(ZONE_MARK_INTERVAL.0,1200.0));
	            
				if(IsPlayerNPC(i))
					MoveDynamicObject(gPlayerMarker[i], y, x, 6.81, speed);
				else
				{
					MoveDynamicObject(gPlayerMarker[i], y, x, 7.41, speed);
					if(VectorSize(MarkerXY[i][0]-x, MarkerXY[i][1]-y, 0) > 0.03)
					{
						if(IsValidDynamic3DTextLabel(gMarkerText[i]))
							DestroyDynamic3DTextLabel(gMarkerText[i]);
						gMarkerText[i] = CreateDynamic3DTextLabel(name, GetPlayerColor(i), y, x, floatadd(7.51,height), 7.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);
				        MarkerXY[i][0] = x;
				        MarkerXY[i][1] = y;
					}
				}
	        }
	        else
	        {
				if(IsPlayerNPC(i))
	        		gPlayerMarker[i] = CreateDynamicObject(2590, y, x, 6.81, 0, 0, 0);
				else
				{
	        		gPlayerMarker[i] = CreateDynamicObject(2590, y, x, 7.41, 0, 0, 0);
					gMarkerText[i] = CreateDynamic3DTextLabel(name, GetPlayerColor(i), y, x, floatadd(7.51,height), 7.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);
				}
	        	if(gPlayerMarker[i] != INVALID_OBJECT_ID)
					SetDynamicObjectMaterial(gPlayerMarker[i], 0, 10770, "carrier_sfse", "ws_shipmetal4", col);
	        }
		}
	}
	
	for(j = 0; j < MAX_PLAYERS; ++j)
	{
	    if(!IsPlayerConnected(j))
	        continue;
		if(IsPlayerInRangeOfPoint(j, 10.0, 220, 1822, 7.4))
		{
		    GetPlayerPos(j, x, y, z);
		    SetPlayerPos(j, floatadd(x,0.00001), y, z);
		}
	}
}

public destroy_bug_objects()
{
	//LS, CJ home
	unset_objects_on_places_xyz(2505.5234, -1690.9922, 14.3281, 15.0);
	unset_objects_on_places_xyz(2520.7344, -1673.8359, 15.5469, 15.0);
	//LS, bomb
	unset_objects_on_places_xyz(1843.3672, -1856.3203, 13.8750, 5.0);
	//LV, airo
	unset_objects_on_places_xyz(1586.2578, 1222.7031, 19.7500, 5.0);
	unset_objects_on_places_xyz(1586.2578, 1222.7031, 19.7500, 5.0);
	//LV
	unset_objects_on_places_xyz(2386.6563, 1043.6016, 11.5938, 5.0);
	//SF, тюн рядом с салоном
	unset_objects_on_places_xyz(-1935.8594, 239.5313, 35.3516, 30.0);
	//SF, тюн далеко от салона
	unset_objects_on_places_xyz(-2716.3516, 217.4766, 5.3828, 5.0);
	//SF, гараж автосервис)
	unset_objects_on_places_xyz(-2026.9141, 129.4063, 30.4531, 15.0);
	unset_objects_on_places_xyz(-2052.6250, 150.4688, 29.9375, 15.0);
	unset_objects_on_places_xyz(-2038.8672, 170.3203, 29.9375, 5.0);
	//SF, гараж рядом с салоном
	unset_objects_on_places_xyz(-1904.5313, 277.8984, 42.9531, 5.0);
	//гараж в LS на пляжу
	unset_objects_on_places_xyz(322.4141, -1769.0313, 5.2500, 5.0);
	//покраска у пляжа LS
	unset_objects_on_places_xyz(488.2813, -1734.6953, 12.3906, 5.0);
	//гараж у автошколы
	unset_objects_on_places_xyz(-2102.9297, -16.0547, 36.4844, 5.0);
	//покраска и тюн а LS
	unset_objects_on_places_xyz(1024.9844, -1029.3516, 33.1953, 25.0);
	unset_objects_on_places_xyz(1041.3516, -1025.9297, 32.6719, 25.0);
	//дверь в аммуницию в городке, недалеко от спавна
	unset_objects_on_places_xyz(-2113.0391, -2460.6172, 30.9141, 10.0);
	unset_objects_on_places_xyz(-2093.3359, -2465.7422, 29.6250, 10.0);
	//дверь в доках SF
	unset_objects_on_places_xyz(-1790.4531, 1430.1250, 8.9766, 5);
	//бомбы в SF
	unset_objects_on_places_xyz(-1786.8125, 1209.4219, 25.8359, 10);
	//бургер в LS
	unset_objects_on_places_xyz(810.1016, -1616.9922, 12.5156, 5);
	//парикмахерская в LS
	unset_objects_on_places_xyz(1977.0547, -2035.8906, 12.5391, 10);
	//xxx магазин в LS
	unset_objects_on_places_xyz(1939.6016, -2116.7578, 12.6797, 10);
	//гараж в LS
	unset_objects_on_places_xyz(1698.9063, -2088.7422, 14.1406, 10);
	//дом в LS
	unset_objects_on_places_xyz(1684.0078, -2097.7734, 12.9141, 10);
	//гараж в LS
	unset_objects_on_places_xyz(1798.6875, -2146.7344, 14.0000, 10);
	//гараж в LS
	unset_objects_on_places_xyz(1877.4141, -2096.5078, 14.0391, 10);
	//маленькая дверь в SFPD
	unset_objects_on_places_xyz(-1618.6016, 680.9141, 6.1719, 30);
	//дверь в бомб в SF
	unset_objects_on_places_xyz(-1695.0703, 1035.6172, 45.7031, 25);
	//гараж на извилистой дороге SF
	unset_objects_on_places_xyz(-2105.1953, 896.9297, 77.4453, 10);
	//не ясно, что это..
	//unset_objects_on_places_xyz(-1645.67, 654.614, -4.90625, 5);
	//ангар на заброшенном аэропорте
	unset_objects_on_places_xyz(397.4766, 2476.6328, 19.5156, 25);
	unset_objects_on_places_xyz(412.1172, 2476.6328, 19.5156, 25);
}

//включаем античит для игрока
public player_is_located(playerid)
{
	new Float:x, Float:y, Float:z;
	
	GetPlayerPos(playerid, x, y, z);
	//для античита
	gNonCheaters[playerid][0] = x;
	gNonCheaters[playerid][1] = y;
	gNonCheaters[playerid][2] = z;
	gPlayerLocated[playerid] = 1;
}

public create_map_objects()
{
#include"objects.inc"
}

public update_live_cells()
{
	new i,j;

	if(gTimerid == -1)
	    return;

	for(i = 0; i < MAX_PLAYERS; ++i)
	{
	    if(gInventoryMenuShow[i] == 0 && gObjectsMenuShow[i] == 0 && gVehicleMenuShow[i] == 0 && gBagMenuShow[i] == 0)
	        continue;

	    for(j = 0; j < MAX_INVENTORY_ON_PLAYER; ++j)
	    {
			//вращаем выбранные объекты в инвентаре
	        if(gInventoryMenuShow[i] > 0 && gRotate[i][j] > 0)
	        {
				if(gIndex[i][j] < (MAX_TURNS_OF_PREVIEW-1))
				{
				    if(gTdInventory[i][j][gIndex[i][j]+1] != PlayerText:INVALID_TEXT_DRAW)
				    {
						PlayerTextDrawShow(i, gTdInventory[i][j][gIndex[i][j]+1]);
						if(gTdInventory[i][j][gIndex[i][j]] != PlayerText:INVALID_TEXT_DRAW)
							PlayerTextDrawHide(i, gTdInventory[i][j][gIndex[i][j]]);
						gIndex[i][j]++;
						if(gIndex[i][j] >= MAX_TURNS_OF_PREVIEW)
							gIndex[i][j] = 0;
					}
				}
				else
				{
				    if(gTdInventory[i][j][0] != PlayerText:INVALID_TEXT_DRAW)
				    {
			  		    PlayerTextDrawShow(i, gTdInventory[i][j][0]);
						if(gTdInventory[i][j][gIndex[i][j]] != PlayerText:INVALID_TEXT_DRAW)
							PlayerTextDrawHide(i, gTdInventory[i][j][gIndex[i][j]]);
						gIndex[i][j] = 0;
					}
				}
			}
		}

	    for(j = 0; j < MAX_INVENTORY_ON_GROUND; ++j)
	    {
			//вращаем выбранные объекты вне инвентаря
			if(gObjectsMenuShow[i] > 0 && gRotateObject[i][j] > 0)
	        {
				if(gIndexObject[i][j] < (MAX_TURNS_OF_PREVIEW-1))
				{
				    if(gTdObject[i][j][gIndexObject[i][j]+1] != PlayerText:INVALID_TEXT_DRAW)
				    {
			  		  PlayerTextDrawShow(i, gTdObject[i][j][gIndexObject[i][j]+1]);
					  if(gTdObject[i][j][gIndexObject[i][j]] != PlayerText:INVALID_TEXT_DRAW)
						PlayerTextDrawHide(i, gTdObject[i][j][gIndexObject[i][j]]);
					  gIndexObject[i][j]++;
					  if(gIndexObject[i][j] >= MAX_TURNS_OF_PREVIEW)
						gIndexObject[i][j] = 0;
					}
				}
				else
				{
				    if(gTdObject[i][j][0] != PlayerText:INVALID_TEXT_DRAW)
				    {
			  		  PlayerTextDrawShow(i, gTdObject[i][j][0]);
					  if(gTdObject[i][j][gIndexObject[i][j]] != PlayerText:INVALID_TEXT_DRAW)
						PlayerTextDrawHide(i, gTdObject[i][j][gIndexObject[i][j]]);
					  gIndexObject[i][j]++;
					  if(gIndexObject[i][j] >= MAX_TURNS_OF_PREVIEW)
						gIndexObject[i][j] = 0;
					}
				}
			}
		}

		if(gVehicleMenuShow[i] > 0)
		{
		    for(j = 0; j < MAX_INVENTORY_ON_VEHICLE; ++j)
		    {
				//вращаем выбранные объекты в инвентаре транспорта
				if(j < gVeh[gVehicleMenuShow[i]][1] && gRotateVehicle[i][j] > 0)
		        {
					if(gIndexVehicle[i][j] < (MAX_TURNS_OF_PREVIEW-1))
					{
					    if(gTdVehicle[i][j][gIndexVehicle[i][j]+1] != PlayerText:INVALID_TEXT_DRAW)
					    {
				  		  PlayerTextDrawShow(i, gTdVehicle[i][j][gIndexVehicle[i][j]+1]);
						  if(gTdVehicle[i][j][gIndexVehicle[i][j]] != PlayerText:INVALID_TEXT_DRAW)
							PlayerTextDrawHide(i, gTdVehicle[i][j][gIndexVehicle[i][j]]);
						  gIndexVehicle[i][j]++;
						  if(gIndexVehicle[i][j] >= MAX_TURNS_OF_PREVIEW)
						 	gIndexVehicle[i][j] = 0;
						}
					}
					else
					{
					    if(gTdVehicle[i][j][0] != PlayerText:INVALID_TEXT_DRAW)
					    {
				  		  PlayerTextDrawShow(i, gTdVehicle[i][j][0]);
						  if(gTdVehicle[i][j][gIndexVehicle[i][j]] != PlayerText:INVALID_TEXT_DRAW)
							PlayerTextDrawHide(i, gTdVehicle[i][j][gIndexVehicle[i][j]]);
					 	  gIndexVehicle[i][j] = 0;
						}
					}
				}
			} // for()
		} // if()

		if(gBagMenuShow[i] > 0)
		{
		    for(j = 0; j < gBag[i][0]; ++j)
		    {
				//вращаем выбранные объекты в инвентаре рюкзака
				if(gRotateBag[i][j] > 0)
		        {
					if(gIndexBag[i][j] < (MAX_TURNS_OF_PREVIEW-1))
					{
					    if(gTdBag[i][j][gIndexBag[i][j]+1] != PlayerText:INVALID_TEXT_DRAW)
					    {
				  		  PlayerTextDrawShow(i, gTdBag[i][j][gIndexBag[i][j]+1]);
						  if(gTdBag[i][j][gIndexBag[i][j]] != PlayerText:INVALID_TEXT_DRAW)
							PlayerTextDrawHide(i, gTdBag[i][j][gIndexBag[i][j]]);
						  gIndexBag[i][j]++;
						  if(gIndexBag[i][j] >= MAX_TURNS_OF_PREVIEW)
						 	gIndexBag[i][j] = 0;
						}
					}
					else
					{
					    if(gTdBag[i][j][0] != PlayerText:INVALID_TEXT_DRAW)
					    {
				  		  PlayerTextDrawShow(i, gTdBag[i][j][0]);
						  if(gTdBag[i][j][gIndexBag[i][j]] != PlayerText:INVALID_TEXT_DRAW)
							PlayerTextDrawHide(i, gTdBag[i][j][gIndexBag[i][j]]);
	  				 	  gIndexBag[i][j] = 0;
						}
					}
				}
			} // for()
		} // if()
	}
}

public create_views_of_items(playerid, vehicleid, cell, area)
{
	new k, m;
	
	switch(area)
	{
	    case INVENTORY_AREA:
	    {
			for(m = 0; m < MAX_INVENTORY_ON_PLAYER; ++m)
			{
    	        if(cell >= 0)
    	            m = cell;
				//если обнуляется уже пустая ячейка - пропускаем
	            if( !(gTdInventory[playerid][m][0] != PlayerText:INVALID_TEXT_DRAW &&
	                  gTdInventory[playerid][m][1] == PlayerText:INVALID_TEXT_DRAW &&
	                  gInventoryItem[playerid][m][db_id] < 0) )
             	{
					for(k = 0; k < MAX_TURNS_OF_PREVIEW; ++k)
					{
						//проверка
				        if(gTdInventory[playerid][m][k] != PlayerText:INVALID_TEXT_DRAW)
				        {
							PlayerTextDrawDestroy(playerid, gTdInventory[playerid][m][k]);
							gTdInventory[playerid][m][k] = PlayerText:INVALID_TEXT_DRAW;
						}

						//размещаем объекты в инвентаре
						if(gInventoryItem[playerid][m][db_id] >= 0 && gInventoryItem[playerid][m][inv_id] >= 0)
						{
							gTdInventory[playerid][m][k] = CreatePlayerTextDraw(playerid, INVENTORY_START_POSITION_X+(m%INVENTORY_CELLS_PER_ROW)*CELL_SIZE, INVENTORY_START_POSITION_Y+(m/INVENTORY_CELLS_PER_ROW)*CELL_SIZE, "MyText");
							PlayerTextDrawFont(playerid, gTdInventory[playerid][m][k], TEXT_DRAW_FONT_MODEL_PREVIEW);
							PlayerTextDrawSetPreviewVehCol(playerid, gTdInventory[playerid][m][k], 0, 1);
							PlayerTextDrawUseBox(playerid, gTdInventory[playerid][m][k], 0);
					//			PlayerTextDrawBoxColor(playerid, gTdInventory[playerid][m][k], 0xFFFFFF88);
							PlayerTextDrawSetShadow(playerid, gTdInventory[playerid][m][k], 0);
							PlayerTextDrawBackgroundColor(playerid, gTdInventory[playerid][m][k], 0xFFFFFF00);
							PlayerTextDrawTextSize(playerid, gTdInventory[playerid][m][k], CELL_SIZE, CELL_SIZE);

							PlayerTextDrawSetPreviewModel(playerid, gTdInventory[playerid][m][k], gInventoryItem[playerid][m][inv_id]);
							PlayerTextDrawSetPreviewRot(playerid,
														gTdInventory[playerid][m][k],
														floatadd(floatmul(floatmul(gInventoryItem[playerid][m][isrot][n_X],k),floatdiv(360.0,MAX_TURNS_OF_PREVIEW)),gInventoryItem[playerid][m][deg][f_X]),
														floatadd(floatmul(floatmul(gInventoryItem[playerid][m][isrot][n_Y],k),floatdiv(360.0,MAX_TURNS_OF_PREVIEW)),gInventoryItem[playerid][m][deg][f_Y]),
														floatadd(floatmul(floatmul(gInventoryItem[playerid][m][isrot][n_Z],k),floatdiv(360.0,MAX_TURNS_OF_PREVIEW)),gInventoryItem[playerid][m][deg][f_Z]),
														gInventoryItem[playerid][m][zoom]);
						}
						else
						{
						    if(k == 0)
						    {
								gTdInventory[playerid][m][k] = CreatePlayerTextDraw(playerid, INVENTORY_START_POSITION_X+(m%INVENTORY_CELLS_PER_ROW)*CELL_SIZE, INVENTORY_START_POSITION_Y+(m/INVENTORY_CELLS_PER_ROW)*CELL_SIZE, "Empty");
								PlayerTextDrawFont(playerid, gTdInventory[playerid][m][k], TEXT_DRAW_FONT_MODEL_PREVIEW);
								PlayerTextDrawSetPreviewVehCol(playerid, gTdInventory[playerid][m][k], 0, 1);
								PlayerTextDrawUseBox(playerid, gTdInventory[playerid][m][k], 0);
						//			PlayerTextDrawBoxColor(playerid, gTdInventory[playerid][m][k], 0xFFFFFF88);
								PlayerTextDrawSetShadow(playerid, gTdInventory[playerid][m][k], 0);
								PlayerTextDrawBackgroundColor(playerid, gTdInventory[playerid][m][k], 0xFFFFFF00);
								PlayerTextDrawTextSize(playerid, gTdInventory[playerid][m][k], CELL_SIZE, CELL_SIZE);

							    //если в ячейке пусто, ставим нулевой объект
								PlayerTextDrawSetPreviewModel(playerid, gTdInventory[playerid][m][k], 0);
								PlayerTextDrawSetPreviewRot(playerid, gTdInventory[playerid][m][k], 90.0, 0.0, 0.0, -100.0);
							}
							else
							{
								gTdInventory[playerid][m][k] = PlayerText:INVALID_TEXT_DRAW;
							}

						}
						if(gTdInventory[playerid][m][k] != PlayerText:INVALID_TEXT_DRAW)
							PlayerTextDrawSetSelectable(playerid, gTdInventory[playerid][m][k], 1);
					}
				}

				//отображаем созданный объект
				if(gInventoryMenuShow[playerid] > 0)
				{
					if(gTdInventory[playerid][m][0] != PlayerText:INVALID_TEXT_DRAW)
						PlayerTextDrawShow(playerid, gTdInventory[playerid][m][0]);
				}
				
    	        if(cell >= 0)
    	            return;
			}
		}
	    case GROUND_AREA:
	    {
			for(m = 0; m < MAX_INVENTORY_ON_GROUND; ++m)
			{
    	        if(cell >= 0)
    	            m = cell;

				//если обнуляется уже пустая ячейка - пропускаем
	            if( !(gTdObject[playerid][m][0] != PlayerText:INVALID_TEXT_DRAW &&
	                  gTdObject[playerid][m][1] == PlayerText:INVALID_TEXT_DRAW &&
	               	  (gGroundItem[playerid][m][db_id] < 0)) )
             	{
					for(k = 0; k < MAX_TURNS_OF_PREVIEW; ++k)
					{
						//проверка
				        if(gTdObject[playerid][m][k] != PlayerText:INVALID_TEXT_DRAW)
				        {
							PlayerTextDrawDestroy(playerid, gTdObject[playerid][m][k]);
							gTdObject[playerid][m][k] = PlayerText:INVALID_TEXT_DRAW;
						}

						if(gGroundItem[playerid][m][db_id] >= 0 && gGroundItem[playerid][m][inv_id] >= 0)
						{
							gTdObject[playerid][m][k] = CreatePlayerTextDraw(playerid, INVENTORY_START_POSITION_X+(m/(MAX_INVENTORY_ON_GROUND/GROUND_CELLS_PER_ROW))*CELL_SIZE, INVENTORY_START_POSITION_Y-(m%(MAX_INVENTORY_ON_GROUND/GROUND_CELLS_PER_ROW)+1)*CELL_SIZE-20.0, "MyText");
							PlayerTextDrawFont(playerid, gTdObject[playerid][m][k], TEXT_DRAW_FONT_MODEL_PREVIEW);
							PlayerTextDrawSetPreviewVehCol(playerid, gTdObject[playerid][m][k], 0, 1);
							PlayerTextDrawUseBox(playerid, gTdObject[playerid][m][k], 0);
							PlayerTextDrawSetShadow(playerid, gTdObject[playerid][m][k], 0);
							PlayerTextDrawBackgroundColor(playerid, gTdObject[playerid][m][k], 0xFFFFFF00);
							PlayerTextDrawTextSize(playerid, gTdObject[playerid][m][k], CELL_SIZE, CELL_SIZE);

							PlayerTextDrawSetPreviewModel(playerid, gTdObject[playerid][m][k], gGroundItem[playerid][m][inv_id]);
							PlayerTextDrawSetPreviewRot(playerid,
														gTdObject[playerid][m][k],
														floatadd(floatmul(floatmul(gGroundItem[playerid][m][isrot][n_X],k),floatdiv(360.0,MAX_TURNS_OF_PREVIEW)),gGroundItem[playerid][m][deg][f_X]),
														floatadd(floatmul(floatmul(gGroundItem[playerid][m][isrot][n_Y],k),floatdiv(360.0,MAX_TURNS_OF_PREVIEW)),gGroundItem[playerid][m][deg][f_Y]),
														floatadd(floatmul(floatmul(gGroundItem[playerid][m][isrot][n_Z],k),floatdiv(360.0,MAX_TURNS_OF_PREVIEW)),gGroundItem[playerid][m][deg][f_Z]),
														gGroundItem[playerid][m][zoom]);
						}
						else
						{
							if(k == 0)
							{
								gTdObject[playerid][m][k] = CreatePlayerTextDraw(playerid, INVENTORY_START_POSITION_X+(m/(MAX_INVENTORY_ON_GROUND/GROUND_CELLS_PER_ROW))*CELL_SIZE, INVENTORY_START_POSITION_Y-(m%(MAX_INVENTORY_ON_GROUND/GROUND_CELLS_PER_ROW)+1)*CELL_SIZE-20.0, "Empty");
								PlayerTextDrawFont(playerid, gTdObject[playerid][m][k], TEXT_DRAW_FONT_MODEL_PREVIEW);
								PlayerTextDrawSetPreviewVehCol(playerid, gTdObject[playerid][m][k], 0, 1);
								PlayerTextDrawUseBox(playerid, gTdObject[playerid][m][k], 0);
								PlayerTextDrawSetShadow(playerid, gTdObject[playerid][m][k], 0);
								PlayerTextDrawBackgroundColor(playerid, gTdObject[playerid][m][k], 0xFFFFFF00);
								PlayerTextDrawTextSize(playerid, gTdObject[playerid][m][k], CELL_SIZE, CELL_SIZE);

							    //ставим нулевой объект
								PlayerTextDrawSetPreviewModel(playerid, gTdObject[playerid][m][k], 0);
								PlayerTextDrawSetPreviewRot(playerid, gTdObject[playerid][m][k], 90.0, 0.0, 0.0, -100.0);
							}
							else
							{
								gTdObject[playerid][m][k] = PlayerText:INVALID_TEXT_DRAW;
							}
						}
						if(gTdObject[playerid][m][k] != PlayerText:INVALID_TEXT_DRAW)
							PlayerTextDrawSetSelectable(playerid, gTdObject[playerid][m][k], 1);
					}
				}
				
				//отображаем созданный объект
				if(gObjectsMenuShow[playerid] > 0)
				{
					if(gTdObject[playerid][m][0] != PlayerText:INVALID_TEXT_DRAW)
						PlayerTextDrawShow(playerid, gTdObject[playerid][m][0]);
				}				
				
    	        if(cell >= 0)
    	            return;
			}
		}
  	    case VEHICLE_AREA:
  	    {
			for(m = 0; m < MAX_INVENTORY_ON_VEHICLE; ++m)
			{
    	        if(cell >= 0)
    	            m = cell;

				//если обнуляется уже пустая ячейка - пропускаем
	            if(!(gTdVehicle[playerid][m][0] != PlayerText:INVALID_TEXT_DRAW &&
	               gTdVehicle[playerid][m][1] == PlayerText:INVALID_TEXT_DRAW &&
	               gVehicleItem[vehicleid][m][db_id] < 0))
             	{
					for(k = 0; k < MAX_TURNS_OF_PREVIEW; ++k)
					{
					    if(m < gVeh[vehicleid][1])
					    {
							//проверка
					        if(gTdVehicle[playerid][m][k] != PlayerText:INVALID_TEXT_DRAW)
					        {
								PlayerTextDrawDestroy(playerid, gTdVehicle[playerid][m][k]);
								gTdVehicle[playerid][m][k] = PlayerText:INVALID_TEXT_DRAW;
							}

							if(gVehicleItem[vehicleid][m][db_id] > 0 && gVehicleItem[vehicleid][m][inv_id] >= 0)
							{
								gTdVehicle[playerid][m][k] = CreatePlayerTextDraw(playerid, INVENTORY_START_POSITION_X+(m/(MAX_INVENTORY_ON_VEHICLE/VEHICLE_CELLS_PER_ROW))*CELL_SIZE, INVENTORY_START_POSITION_Y-CELL_SIZE*2-20.0+(m%(MAX_INVENTORY_ON_VEHICLE/VEHICLE_CELLS_PER_ROW))*CELL_SIZE, "MyText");
								PlayerTextDrawFont(playerid, gTdVehicle[playerid][m][k], TEXT_DRAW_FONT_MODEL_PREVIEW);
								PlayerTextDrawSetPreviewVehCol(playerid, gTdVehicle[playerid][m][k], 0, 1);
								PlayerTextDrawUseBox(playerid, gTdVehicle[playerid][m][k], 0);
								PlayerTextDrawSetShadow(playerid, gTdVehicle[playerid][m][k], 0);
								PlayerTextDrawBackgroundColor(playerid, gTdVehicle[playerid][m][k], 0xFFFFFF00);
								PlayerTextDrawTextSize(playerid, gTdVehicle[playerid][m][k], CELL_SIZE, CELL_SIZE);

								PlayerTextDrawSetPreviewModel(playerid, gTdVehicle[playerid][m][k], gVehicleItem[vehicleid][m][inv_id]);
					//			PlayerTextDrawSetPreviewRot(playerid, gTdVehicle[playerid][m][k], 90.0, 0.0, 0.0, -100.0);
								PlayerTextDrawSetPreviewRot(playerid,
															gTdVehicle[playerid][m][k],
															floatadd(floatmul(floatmul(gVehicleItem[vehicleid][m][isrot][n_X],k),floatdiv(360.0,MAX_TURNS_OF_PREVIEW)),gVehicleItem[vehicleid][m][deg][f_X]),
															floatadd(floatmul(floatmul(gVehicleItem[vehicleid][m][isrot][n_Y],k),floatdiv(360.0,MAX_TURNS_OF_PREVIEW)),gVehicleItem[vehicleid][m][deg][f_Y]),
															floatadd(floatmul(floatmul(gVehicleItem[vehicleid][m][isrot][n_Z],k),floatdiv(360.0,MAX_TURNS_OF_PREVIEW)),gVehicleItem[vehicleid][m][deg][f_Z]),
															gVehicleItem[vehicleid][m][zoom]);
							}
							else
							{
								if(k == 0)
								{
									gTdVehicle[playerid][m][k] = CreatePlayerTextDraw(playerid, INVENTORY_START_POSITION_X+(m/(MAX_INVENTORY_ON_VEHICLE/VEHICLE_CELLS_PER_ROW))*CELL_SIZE, INVENTORY_START_POSITION_Y-CELL_SIZE*2-20.0+(m%(MAX_INVENTORY_ON_VEHICLE/VEHICLE_CELLS_PER_ROW))*CELL_SIZE, "Empty");
									PlayerTextDrawFont(playerid, gTdVehicle[playerid][m][k], TEXT_DRAW_FONT_MODEL_PREVIEW);
									PlayerTextDrawSetPreviewVehCol(playerid, gTdVehicle[playerid][m][k], 0, 1);
									PlayerTextDrawUseBox(playerid, gTdVehicle[playerid][m][k], 0);
									PlayerTextDrawSetShadow(playerid, gTdVehicle[playerid][m][k], 0);
									PlayerTextDrawBackgroundColor(playerid, gTdVehicle[playerid][m][k], 0xFFFFFF00);
									PlayerTextDrawTextSize(playerid, gTdVehicle[playerid][m][k], CELL_SIZE, CELL_SIZE);

								    //ставим нулевой объект
									PlayerTextDrawSetPreviewModel(playerid, gTdVehicle[playerid][m][k], 0);
									PlayerTextDrawSetPreviewRot(playerid, gTdVehicle[playerid][m][k], 90.0, 0.0, 0.0, -100.0);
								}
								else
								{
									gTdVehicle[playerid][m][k] = PlayerText:INVALID_TEXT_DRAW;
								}
							}

							if(gTdVehicle[playerid][m][k] != PlayerText:INVALID_TEXT_DRAW)
								PlayerTextDrawSetSelectable(playerid, gTdVehicle[playerid][m][k], 1);
						}
						else
						    return;
					}
				}
				
				//отображаем созданный объект
				if(gVehicleMenuShow[playerid] > 0)
				{
					if(gTdVehicle[playerid][m][0] != PlayerText:INVALID_TEXT_DRAW)
						PlayerTextDrawShow(playerid, gTdVehicle[playerid][m][0]);
				}
				
    	        if(cell >= 0)
    	            return;
			}
		}
	    case BAG_AREA:
	    {
   	        if(cell < 0)
   	        {
				//предварительно удаляем прежние объекты рюкзака для игрока
				for(m = 0; m < MAX_INVENTORY_IN_BAG; ++m)
				{
					for(k = 0; k < MAX_TURNS_OF_PREVIEW; ++k)
					{
						if(gTdBag[playerid][m][k] != PlayerText:INVALID_TEXT_DRAW)
							PlayerTextDrawDestroy(playerid, gTdBag[playerid][m][k]);
						gTdBag[playerid][m][k] = PlayerText:INVALID_TEXT_DRAW;
					}
				}
			}

			for(m = 0; m < MAX_INVENTORY_IN_BAG; ++m)
			{
    	        if(cell >= 0)
    	            m = cell;

				//если обнуляется уже пустая ячейка - пропускаем
	            if(!(gTdBag[playerid][m][0] != PlayerText:INVALID_TEXT_DRAW &&
	               gTdBag[playerid][m][1] == PlayerText:INVALID_TEXT_DRAW &&
	               gBagItem[playerid][m][db_id] < 0))
             	{
					for(k = 0; k < MAX_TURNS_OF_PREVIEW; ++k)
					{
					    if(m < gBag[playerid][0])
					    {
							//проверка
					        if(gTdBag[playerid][m][k] != PlayerText:INVALID_TEXT_DRAW)
					        {
								PlayerTextDrawDestroy(playerid, gTdBag[playerid][m][k]);
								gTdBag[playerid][m][k] = PlayerText:INVALID_TEXT_DRAW;
							}

							if(gBagItem[playerid][m][db_id] > 0 && gBagItem[playerid][m][inv_id] >= 0)
							{
								gTdBag[playerid][m][k] = CreatePlayerTextDraw(playerid, INVENTORY_START_POSITION_X+(m%BACKPACK_LINE)*CELL_SIZE_BAG+CELL_SIZE*INVENTORY_CELLS_PER_ROW+MENU_BORDER, INVENTORY_START_POSITION_Y+(m/BACKPACK_LINE)*CELL_SIZE_BAG, "MyBag");
								PlayerTextDrawFont(playerid, gTdBag[playerid][m][k], TEXT_DRAW_FONT_MODEL_PREVIEW);
								PlayerTextDrawSetPreviewVehCol(playerid, gTdBag[playerid][m][k], 0, 1);
								PlayerTextDrawUseBox(playerid, gTdBag[playerid][m][k], 0);
								PlayerTextDrawSetShadow(playerid, gTdBag[playerid][m][k], 0);
								PlayerTextDrawBackgroundColor(playerid, gTdBag[playerid][m][k], 0xFFFFFF00);
								PlayerTextDrawTextSize(playerid, gTdBag[playerid][m][k], CELL_SIZE_BAG, CELL_SIZE_BAG);

								PlayerTextDrawSetPreviewModel(playerid, gTdBag[playerid][m][k], gBagItem[playerid][m][inv_id]);
					//			PlayerTextDrawSetPreviewRot(playerid, gTdBag[playerid][m][k], 90.0, 0.0, 0.0, -100.0);
								PlayerTextDrawSetPreviewRot(playerid,
															gTdBag[playerid][m][k],
															floatadd(floatmul(floatmul(gBagItem[playerid][m][isrot][n_X],k),floatdiv(360.0,MAX_TURNS_OF_PREVIEW)),gBagItem[playerid][m][deg][f_X]),
															floatadd(floatmul(floatmul(gBagItem[playerid][m][isrot][n_Y],k),floatdiv(360.0,MAX_TURNS_OF_PREVIEW)),gBagItem[playerid][m][deg][f_Y]),
															floatadd(floatmul(floatmul(gBagItem[playerid][m][isrot][n_Z],k),floatdiv(360.0,MAX_TURNS_OF_PREVIEW)),gBagItem[playerid][m][deg][f_Z]),
															gBagItem[playerid][m][zoom]);
							}
							else
							{
								if(k == 0)
								{
									gTdBag[playerid][m][k] = CreatePlayerTextDraw(playerid, INVENTORY_START_POSITION_X+(m%BACKPACK_LINE)*CELL_SIZE_BAG+CELL_SIZE*INVENTORY_CELLS_PER_ROW+MENU_BORDER, INVENTORY_START_POSITION_Y+(m/BACKPACK_LINE)*CELL_SIZE_BAG, "Empty");
									PlayerTextDrawFont(playerid, gTdBag[playerid][m][k], TEXT_DRAW_FONT_MODEL_PREVIEW);
									PlayerTextDrawSetPreviewVehCol(playerid, gTdBag[playerid][m][k], 0, 1);
									PlayerTextDrawUseBox(playerid, gTdBag[playerid][m][k], 0);
									PlayerTextDrawSetShadow(playerid, gTdBag[playerid][m][k], 0);
									PlayerTextDrawBackgroundColor(playerid, gTdBag[playerid][m][k], 0xFFFFFF00);
									PlayerTextDrawTextSize(playerid, gTdBag[playerid][m][k], CELL_SIZE_BAG, CELL_SIZE_BAG);

								    //ставим нулевой объект
									PlayerTextDrawSetPreviewModel(playerid, gTdBag[playerid][m][k], 0);
									PlayerTextDrawSetPreviewRot(playerid, gTdBag[playerid][m][k], 90.0, 0.0, 0.0, -100.0);
								}
								else
								{
									gTdBag[playerid][m][k] = PlayerText:INVALID_TEXT_DRAW;
								}
							}

							if(gTdBag[playerid][m][k] != PlayerText:INVALID_TEXT_DRAW)
								PlayerTextDrawSetSelectable(playerid, gTdBag[playerid][m][k], 1);
						}
						else
						    return;
					}
				}
				//отображаем созданный объект
				if(gBagMenuShow[playerid] > 0)
				{
					if(gTdBag[playerid][m][0] != PlayerText:INVALID_TEXT_DRAW)
						PlayerTextDrawShow(playerid, gTdBag[playerid][m][0]);
				}
				
    	        if(cell >= 0)
    	            return;
			}
		}
	}
}

public create_inventory_menu(playerid)
{
	//hud:radar_modGarage - гаечный ключ
	//hud:fist - кулак
	//hud:radar_qmark - знак вопроса
	//hud:radar_hostpital, hud:radar_airYard - крестики

	//hud:radar_dateDisco - аккуратный кружок

	new i;

	//фон инвентаря
	gTdMenu[playerid][0] = CreatePlayerTextDraw(playerid, INVENTORY_START_POSITION_X, INVENTORY_START_POSITION_Y, "fon");
	PlayerTextDrawFont(playerid, gTdMenu[playerid][0], TEXT_DRAW_FONT_MODEL_PREVIEW);
	PlayerTextDrawUseBox(playerid, gTdMenu[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, gTdMenu[playerid][0], 0xFFFFFF88); //0xFFFFFF88
	PlayerTextDrawSetPreviewRot(playerid, gTdMenu[playerid][0], 90.0, 0.0, 0.0, -100.0);
	PlayerTextDrawTextSize(playerid, gTdMenu[playerid][0], CELL_SIZE*INVENTORY_CELLS_PER_ROW, CELL_SIZE*(MAX_INVENTORY_ON_PLAYER/INVENTORY_CELLS_PER_ROW));

	gTdMenu[playerid][11] = CreatePlayerTextDraw(playerid, INVENTORY_START_POSITION_X, INVENTORY_START_POSITION_Y-10.0, "plfon");
	PlayerTextDrawFont(playerid, gTdMenu[playerid][11], TEXT_DRAW_FONT_MODEL_PREVIEW);
	PlayerTextDrawUseBox(playerid, gTdMenu[playerid][11], 0);
	PlayerTextDrawBackgroundColor(playerid, gTdMenu[playerid][11], 0x000000FF); //0xFFFFFF88
	PlayerTextDrawSetPreviewRot(playerid, gTdMenu[playerid][11], 90.0, 0.0, 0.0, -100.0);
	PlayerTextDrawTextSize(playerid, gTdMenu[playerid][11], CELL_SIZE*INVENTORY_CELLS_PER_ROW, 10.0);

	gTdMenu[playerid][12] = CreatePlayerTextDraw(playerid, INVENTORY_START_POSITION_X, INVENTORY_START_POSITION_Y-10.0, "Player");
	PlayerTextDrawFont(playerid, gTdMenu[playerid][12], 1);
	PlayerTextDrawBackgroundColor(playerid, gTdMenu[playerid][12], 0x00FFFF88); //0xFFFFFF88
	PlayerTextDrawSetShadow(playerid, gTdMenu[playerid][12], 0);
	PlayerTextDrawTextSize(playerid, gTdMenu[playerid][12], CELL_SIZE*INVENTORY_CELLS_PER_ROW, 6.0);

	//фон для объектов не из инвентаря
	gTdMenu[playerid][7] = CreatePlayerTextDraw(playerid, INVENTORY_START_POSITION_X, INVENTORY_START_POSITION_Y-CELL_SIZE*(MAX_INVENTORY_ON_GROUND/GROUND_CELLS_PER_ROW)-20.0, "noninventfon");
	PlayerTextDrawFont(playerid, gTdMenu[playerid][7], TEXT_DRAW_FONT_MODEL_PREVIEW);
	PlayerTextDrawUseBox(playerid, gTdMenu[playerid][7], 0);
	PlayerTextDrawBackgroundColor(playerid, gTdMenu[playerid][7], 0xFFFFFF88); //0x55BB1133
	PlayerTextDrawSetPreviewRot(playerid, gTdMenu[playerid][7], 90.0, 0.0, 0.0, -100.0);
	PlayerTextDrawTextSize(playerid, gTdMenu[playerid][7], CELL_SIZE*GROUND_CELLS_PER_ROW, CELL_SIZE*(MAX_INVENTORY_ON_GROUND/GROUND_CELLS_PER_ROW));

	gTdMenu[playerid][13] = CreatePlayerTextDraw(playerid, INVENTORY_START_POSITION_X, INVENTORY_START_POSITION_Y-CELL_SIZE*(MAX_INVENTORY_ON_GROUND/GROUND_CELLS_PER_ROW)-30.0, "grfon");
	PlayerTextDrawFont(playerid, gTdMenu[playerid][13], TEXT_DRAW_FONT_MODEL_PREVIEW);
	PlayerTextDrawUseBox(playerid, gTdMenu[playerid][13], 0);
	PlayerTextDrawBackgroundColor(playerid, gTdMenu[playerid][13], 0x000000FF); //0xFFFFFF88
	PlayerTextDrawSetPreviewRot(playerid, gTdMenu[playerid][13], 90.0, 0.0, 0.0, -100.0);
	PlayerTextDrawTextSize(playerid, gTdMenu[playerid][13], CELL_SIZE*GROUND_CELLS_PER_ROW, 10.0);

	gTdMenu[playerid][14] = CreatePlayerTextDraw(playerid, INVENTORY_START_POSITION_X, INVENTORY_START_POSITION_Y-CELL_SIZE*(MAX_INVENTORY_ON_GROUND/GROUND_CELLS_PER_ROW)-30.0, "Ground");
	PlayerTextDrawFont(playerid, gTdMenu[playerid][14], 1);
	PlayerTextDrawBackgroundColor(playerid, gTdMenu[playerid][14], 0x00FFFF88); //0xFFFFFF88
	PlayerTextDrawSetShadow(playerid, gTdMenu[playerid][14], 0);
	PlayerTextDrawTextSize(playerid, gTdMenu[playerid][14], CELL_SIZE*GROUND_CELLS_PER_ROW, 6.0);

	//фон для объектов из инвентаря авто
	gTdMenu[playerid][10] = CreatePlayerTextDraw(playerid, INVENTORY_START_POSITION_X, INVENTORY_START_POSITION_Y-CELL_SIZE*(MAX_INVENTORY_ON_VEHICLE/VEHICLE_CELLS_PER_ROW)-20.0, "vehfon");
	PlayerTextDrawFont(playerid, gTdMenu[playerid][10], TEXT_DRAW_FONT_MODEL_PREVIEW);
	PlayerTextDrawUseBox(playerid, gTdMenu[playerid][10], 0);
	PlayerTextDrawBackgroundColor(playerid, gTdMenu[playerid][10], 0xFFFFFF88); //0x88118833
	PlayerTextDrawSetPreviewRot(playerid, gTdMenu[playerid][10], 90.0, 0.0, 0.0, -100.0);
	PlayerTextDrawTextSize(playerid, gTdMenu[playerid][10], CELL_SIZE*VEHICLE_CELLS_PER_ROW, CELL_SIZE*(MAX_INVENTORY_ON_VEHICLE/VEHICLE_CELLS_PER_ROW));

	gTdMenu[playerid][15] = CreatePlayerTextDraw(playerid, INVENTORY_START_POSITION_X, INVENTORY_START_POSITION_Y-CELL_SIZE*(MAX_INVENTORY_ON_VEHICLE/VEHICLE_CELLS_PER_ROW)-30.0, "vhfon");
	PlayerTextDrawFont(playerid, gTdMenu[playerid][15], TEXT_DRAW_FONT_MODEL_PREVIEW);
	PlayerTextDrawUseBox(playerid, gTdMenu[playerid][15], 0);
	PlayerTextDrawBackgroundColor(playerid, gTdMenu[playerid][15], 0x000000FF); //0xFFFFFF88
	PlayerTextDrawSetPreviewRot(playerid, gTdMenu[playerid][15], 90.0, 0.0, 0.0, -100.0);
	PlayerTextDrawTextSize(playerid, gTdMenu[playerid][15], CELL_SIZE*VEHICLE_CELLS_PER_ROW, 10.0);

	gTdMenu[playerid][16] = CreatePlayerTextDraw(playerid, INVENTORY_START_POSITION_X, INVENTORY_START_POSITION_Y-CELL_SIZE*(MAX_INVENTORY_ON_VEHICLE/VEHICLE_CELLS_PER_ROW)-30.0, "Vehicle");
	PlayerTextDrawFont(playerid, gTdMenu[playerid][16], 1);
	PlayerTextDrawBackgroundColor(playerid, gTdMenu[playerid][16], 0x00FFFF88); //0xFFFFFF88
	PlayerTextDrawSetShadow(playerid, gTdMenu[playerid][16], 0);
	PlayerTextDrawTextSize(playerid, gTdMenu[playerid][16], CELL_SIZE*VEHICLE_CELLS_PER_ROW, 6.0);

	//фон для объектов из инвентаря рюкзака
	gTdMenu[playerid][2] = CreatePlayerTextDraw(playerid, INVENTORY_START_POSITION_X+CELL_SIZE*INVENTORY_CELLS_PER_ROW+MENU_BORDER, INVENTORY_START_POSITION_Y, "bagfon");
	PlayerTextDrawFont(playerid, gTdMenu[playerid][2], TEXT_DRAW_FONT_MODEL_PREVIEW);
	PlayerTextDrawUseBox(playerid, gTdMenu[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, gTdMenu[playerid][2], 0xFFFFFF88); //0x88118833
	PlayerTextDrawSetPreviewRot(playerid, gTdMenu[playerid][2], 90.0, 0.0, 0.0, -100.0);
	PlayerTextDrawTextSize(playerid, gTdMenu[playerid][2], CELL_SIZE_BAG*BACKPACK_LINE, CELL_SIZE_BAG*BACKPACK_LINE);

	gTdMenu[playerid][8] = CreatePlayerTextDraw(playerid, INVENTORY_START_POSITION_X+CELL_SIZE*INVENTORY_CELLS_PER_ROW+MENU_BORDER, INVENTORY_START_POSITION_Y-10.0, "bgfon");
	PlayerTextDrawFont(playerid, gTdMenu[playerid][8], TEXT_DRAW_FONT_MODEL_PREVIEW);
	PlayerTextDrawUseBox(playerid, gTdMenu[playerid][8], 0);
	PlayerTextDrawBackgroundColor(playerid, gTdMenu[playerid][8], 0x000000FF); //0xFFFFFF88
	PlayerTextDrawSetPreviewRot(playerid, gTdMenu[playerid][8], 90.0, 0.0, 0.0, -100.0);
	PlayerTextDrawTextSize(playerid, gTdMenu[playerid][8], CELL_SIZE_BAG*BACKPACK_LINE, 10.0);

	gTdMenu[playerid][9] = CreatePlayerTextDraw(playerid, INVENTORY_START_POSITION_X+CELL_SIZE*INVENTORY_CELLS_PER_ROW+MENU_BORDER, INVENTORY_START_POSITION_Y-10.0, "Bag");
	PlayerTextDrawFont(playerid, gTdMenu[playerid][9], 1);
	PlayerTextDrawBackgroundColor(playerid, gTdMenu[playerid][9], 0x00FFFF88); //0xFFFFFF88
	PlayerTextDrawSetShadow(playerid, gTdMenu[playerid][9], 0);
	PlayerTextDrawTextSize(playerid, gTdMenu[playerid][9], CELL_SIZE_BAG*BACKPACK_LINE, 6.0);

	//кнопка отмены "-->"
	gTdMenu[playerid][1] = CreatePlayerTextDraw(playerid, INVENTORY_START_POSITION_X+6.0, INVENTORY_START_POSITION_Y+CELL_SIZE*(MAX_INVENTORY_ON_PLAYER/INVENTORY_CELLS_PER_ROW)+10.0, "hud:skipicon");
	PlayerTextDrawFont(playerid, gTdMenu[playerid][1], 4);
//	PlayerTextDrawFont(playerid, gTdMenu[playerid][1], 3);
	PlayerTextDrawColor(playerid, gTdMenu[playerid][1], 0xFF0000DD);
//	PlayerTextDrawTextSize(playerid, gTdMenu[playerid][1], INVENTORY_START_POSITION_X+16, 200.0);
	PlayerTextDrawTextSize(playerid, gTdMenu[playerid][1], CELL_SIZE/2.0, CELL_SIZE/2.0);
	PlayerTextDrawSetShadow(playerid, gTdMenu[playerid][1], 0);
	PlayerTextDrawSetSelectable(playerid, gTdMenu[playerid][1], 1);

    gTdMenu[playerid][6] = PlayerText:INVALID_TEXT_DRAW;
/*
	//кнопка "рюкзак"
	gTdMenu[playerid][6] = CreatePlayerTextDraw(playerid, INVENTORY_START_POSITION_X+45.0, INVENTORY_START_POSITION_Y+CELL_SIZE*2+10.0, "Object");
	PlayerTextDrawFont(playerid, gTdMenu[playerid][6], TEXT_DRAW_FONT_MODEL_PREVIEW);
	PlayerTextDrawSetPreviewModel(playerid, gTdMenu[playerid][6], 1550); //Большой рюкзак
	PlayerTextDrawSetPreviewRot(playerid, gTdMenu[playerid][6],-30.0, 0.0, 48.0, 0.8);
	PlayerTextDrawColor(playerid, gTdMenu[playerid][6], 0xFFFFFFDD);
	PlayerTextDrawSetPreviewVehCol(playerid, gTdMenu[playerid][6], 0, 1);
	PlayerTextDrawUseBox(playerid, gTdMenu[playerid][6], 0);
	PlayerTextDrawSetShadow(playerid, gTdMenu[playerid][6], 0);
	PlayerTextDrawBackgroundColor(playerid, gTdMenu[playerid][6], 0xFFFFFF00);
	PlayerTextDrawTextSize(playerid, gTdMenu[playerid][6], CELL_SIZE/2.0, CELL_SIZE/2.0);
	PlayerTextDrawSetSelectable(playerid, gTdMenu[playerid][6], 1);
*/
	//кнопка "?"
	//gTdMenu[playerid][3]
	gTdMenu[playerid][3] = CreatePlayerTextDraw(playerid, INVENTORY_START_POSITION_X+122.0, INVENTORY_START_POSITION_Y+CELL_SIZE*(MAX_INVENTORY_ON_PLAYER/INVENTORY_CELLS_PER_ROW)+MENU_BORDER, "hud:radar_qmark");
	PlayerTextDrawFont(playerid, gTdMenu[playerid][3], 4);
	PlayerTextDrawColor(playerid, gTdMenu[playerid][3], 0xFFFF00DD);
//	PlayerTextDrawTextSize(playerid, gTdMenu[playerid][3], INVENTORY_START_POSITION_X+57.0, 400.0);
	PlayerTextDrawTextSize(playerid, gTdMenu[playerid][3], CELL_SIZE/2.0, CELL_SIZE/2.0);
	PlayerTextDrawSetShadow(playerid, gTdMenu[playerid][3], 0);
	PlayerTextDrawSetSelectable(playerid, gTdMenu[playerid][3], 1);

	//кнопка "кулак"
	//gTdMenu[playerid][5]
	gTdMenu[playerid][4] = CreatePlayerTextDraw(playerid, INVENTORY_START_POSITION_X+85.5, INVENTORY_START_POSITION_Y+CELL_SIZE*(MAX_INVENTORY_ON_PLAYER/INVENTORY_CELLS_PER_ROW)+MENU_BORDER, "hud:fist");
	PlayerTextDrawFont(playerid, gTdMenu[playerid][4], 4);
	PlayerTextDrawColor(playerid, gTdMenu[playerid][4], 0x0066FFDD);
//	PlayerTextDrawTextSize(playerid, gTdMenu[playerid][4], INVENTORY_START_POSITION_X+95.5, 400.0);
	PlayerTextDrawTextSize(playerid, gTdMenu[playerid][4], CELL_SIZE/2.0, CELL_SIZE/2.0);
	PlayerTextDrawSetShadow(playerid, gTdMenu[playerid][4], 0);
	PlayerTextDrawSetSelectable(playerid, gTdMenu[playerid][4], 1);

	//кнопка "гаячный ключ"
	//gTdMenu[playerid][8]
	gTdMenu[playerid][5] = CreatePlayerTextDraw(playerid, INVENTORY_START_POSITION_X+155.0, INVENTORY_START_POSITION_Y+CELL_SIZE*(MAX_INVENTORY_ON_PLAYER/INVENTORY_CELLS_PER_ROW)+MENU_BORDER, "hud:radar_modGarage");
	PlayerTextDrawFont(playerid, gTdMenu[playerid][5], 4);
	PlayerTextDrawColor(playerid, gTdMenu[playerid][5], 0x552288DD);
//	PlayerTextDrawTextSize(playerid, gTdMenu[playerid][5], INVENTORY_START_POSITION_X+165.0, 500.0);
	PlayerTextDrawTextSize(playerid, gTdMenu[playerid][5], CELL_SIZE/2.0, CELL_SIZE/2.0);
	PlayerTextDrawSetShadow(playerid, gTdMenu[playerid][5], 0);
	PlayerTextDrawSetSelectable(playerid, gTdMenu[playerid][5], 1);

	//создаём анимации для всех предметов в инвентаре
	//17050 (?)
	//17051 патроны дробовик (?)
	//12911 патроны пистолет
	//10811 патроны дробовик
	//2036 снайперка
	//2061 - патроны винтовка и автомат

	//получаем перечень инвентаря персонажа
	cache_player_inventory(playerid);
	create_views_of_items(playerid, -1, -1, INVENTORY_AREA);

	for(i = 0; i < MAX_INVENTORY_ON_PLAYER; ++i)
	{
	    if(gInventoryItem[playerid][i][obj_auto] == 1)
	    {
			auto_apply_one_cell(playerid, -1, i, INVENTORY_AREA);
	    }
	}
}

public create_objects_menu(playerid)
{
	//получаем свойства объектов для меню объектов
	//get_objects_properties(playerid, inv_isrot, inv_deg, inv_zoom, gStandartRangeValue);
	cache_ground_inventory(playerid, gStandartRangeValue);
	create_views_of_items(playerid, -1, -1, GROUND_AREA);
//	find_and_cache_objects(playerid, 50.0);
}

public create_vehicle_menu(playerid, vehicleid)
{
//	cache_vehicle_inventory(vehicleid); //тут не обязательно
	create_views_of_items(playerid, vehicleid, -1, VEHICLE_AREA);
}

public create_bag_menu(playerid)
{
	new i, count;

	//фон рюкзака по размеру количества ячеек в нём
	if(gTdMenu[playerid][2] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawTextSize(playerid, gTdMenu[playerid][2], CELL_SIZE_BAG*BACKPACK_LINE, CELL_SIZE_BAG*(gBag[playerid][0]/BACKPACK_LINE));

	//проверяем, один ли рюкзак в инвентаре
	for(i = 0, count = 0; i < MAX_INVENTORY_ON_PLAYER; ++i)
	{
		if(gInventoryItem[playerid][i][obj_inventory] == 2)
		    count++;
	}

	if(count > 1)
	    return;

	//кэшируем свойства объектов для меню рюкзака
	cache_bag_inventory(playerid);
	create_views_of_items(playerid, -1, -1, BAG_AREA);
}

//создать отображение ячеек
public create_cells()
{
	new i;
	
	for(i = 0; i < MAX_INVENTORY_ON_PLAYER; ++i)
	{
		gTdInvCells[i] = TextDrawCreate(INVENTORY_START_POSITION_X+CELL_SIZE*(i%INVENTORY_CELLS_PER_ROW)+CELL_BORDER, INVENTORY_START_POSITION_Y+CELL_SIZE*(i/INVENTORY_CELLS_PER_ROW)+CELL_BORDER, "textdraw");
		TextDrawFont(gTdInvCells[i], TEXT_DRAW_FONT_MODEL_PREVIEW);
		TextDrawSetPreviewModel(gTdInvCells[i], 0);
		TextDrawSetPreviewRot(gTdInvCells[i], 90.0, 0.0, 0.0, -100.0);
		TextDrawColor(gTdInvCells[i], 0x00000077);
		TextDrawBackgroundColor(gTdInvCells[i], 0x00000077); //0xFFFFFF88
		TextDrawTextSize(gTdInvCells[i], CELL_SIZE-CELL_BORDER*2, CELL_SIZE-CELL_BORDER*2);
		TextDrawUseBox(gTdInvCells[i], 0);
		TextDrawSetShadow(gTdInvCells[i], 0);
	}
	for(i = 0; i < MAX_INVENTORY_ON_VEHICLE; ++i)
	{
		gTdVehCells[i] = TextDrawCreate(INVENTORY_START_POSITION_X+CELL_SIZE*(i/(MAX_INVENTORY_ON_VEHICLE/VEHICLE_CELLS_PER_ROW))+CELL_BORDER, INVENTORY_START_POSITION_Y-CELL_SIZE*2-20.0+CELL_SIZE*(i%(MAX_INVENTORY_ON_VEHICLE/VEHICLE_CELLS_PER_ROW))+CELL_BORDER, "textdraw");
		TextDrawFont(gTdVehCells[i], TEXT_DRAW_FONT_MODEL_PREVIEW);
		TextDrawSetPreviewModel(gTdVehCells[i], 0);
		TextDrawSetPreviewRot(gTdVehCells[i], 90.0, 0.0, 0.0, -100.0);
		TextDrawColor(gTdVehCells[i], 0x00000077);
		TextDrawBackgroundColor(gTdVehCells[i], 0x00000077); //0xFFFFFF88
		TextDrawTextSize(gTdVehCells[i], CELL_SIZE-CELL_BORDER*2, CELL_SIZE-CELL_BORDER*2);
		TextDrawUseBox(gTdVehCells[i], 0);
		TextDrawSetShadow(gTdVehCells[i], 0);
	}
	for(i = 0; i < MAX_INVENTORY_IN_BAG; ++i)
	{
		gTdBagCells[i] = TextDrawCreate(INVENTORY_START_POSITION_X+CELL_SIZE*INVENTORY_CELLS_PER_ROW+MENU_BORDER+CELL_SIZE_BAG*(i%BACKPACK_LINE)+CELL_BORDER_BAG, INVENTORY_START_POSITION_Y+CELL_SIZE_BAG*(i/BACKPACK_LINE)+CELL_BORDER_BAG, "textdraw");
		TextDrawFont(gTdBagCells[i], TEXT_DRAW_FONT_MODEL_PREVIEW);
		TextDrawSetPreviewModel(gTdBagCells[i], 0);
		TextDrawSetPreviewRot(gTdBagCells[i], 90.0, 0.0, 0.0, -100.0);
		TextDrawColor(gTdBagCells[i], 0x00000077);
		TextDrawBackgroundColor(gTdBagCells[i], 0x00000077); //0xFFFFFF88
		TextDrawTextSize(gTdBagCells[i], CELL_SIZE_BAG-CELL_BORDER_BAG*2, CELL_SIZE_BAG-CELL_BORDER_BAG*2);
		TextDrawUseBox(gTdBagCells[i], 0);
		TextDrawSetShadow(gTdBagCells[i], 0);
	}
}

public show_cells(playerid, type, cells, show)
{
	new i;
	
	switch(type)
	{
	    case INVENTORY_AREA:
	    {
			for(i = 0; i < cells; ++i)
			{
				if(show)
		    	    TextDrawShowForPlayer(playerid, gTdInvCells[i]);
				else
					TextDrawHideForPlayer(playerid, gTdInvCells[i]);
			}
		}
	    case GROUND_AREA:
	    {
			for(i = 0; i < cells; ++i)
			{
				if(show)
		    	    TextDrawShowForPlayer(playerid, gTdVehCells[i]);
				else
					TextDrawHideForPlayer(playerid, gTdVehCells[i]);
			}
	    }
	    case VEHICLE_AREA:
	    {
			for(i = 0; i < cells; ++i)
			{
				if(show)
		    	    TextDrawShowForPlayer(playerid, gTdVehCells[i]);
				else
					TextDrawHideForPlayer(playerid, gTdVehCells[i]);
			}
	    }
	    case BAG_AREA:
	    {
			for(i = 0; i < cells; ++i)
			{
				if(show)
		    	    TextDrawShowForPlayer(playerid, gTdBagCells[i]);
				else
					TextDrawHideForPlayer(playerid, gTdBagCells[i]);
			}
	    }
	}
}

public show_inventory(playerid, car_menu)
{
	new i,j,k,m;
	new vehicleid, cells;

	if(gIsPlayerLogin[playerid] <= 0)
	    return;
	
	if(car_menu)
		vehicleid = GetPlayerVehicleID(playerid);

	//создаём отображение ячеек
	show_cells(playerid, INVENTORY_AREA, MAX_INVENTORY_ON_PLAYER, true);

	if(car_menu)
	{
		//создаём отображение ячеек
		show_cells(playerid, VEHICLE_AREA, gVeh[vehicleid][1], true);
	}
	else
	{
		//создаём отображение ячеек
		show_cells(playerid, GROUND_AREA, MAX_INVENTORY_ON_GROUND, true);
	}

	//фон инвентаря
	if(gTdMenu[playerid][0] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawShow(playerid, gTdMenu[playerid][0]);
	if(gTdMenu[playerid][11] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawShow(playerid, gTdMenu[playerid][11]);
	if(gTdMenu[playerid][12] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawShow(playerid, gTdMenu[playerid][12]);
	//кнопка закрытия
	if(gTdMenu[playerid][1] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawShow(playerid, gTdMenu[playerid][1]);
	//кнопка 'вопросик'
	if(gTdMenu[playerid][3] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawShow(playerid, gTdMenu[playerid][3]);
	//кнопка 'действие'
	if(gTdMenu[playerid][4] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawShow(playerid, gTdMenu[playerid][4]);
	//кнопка 'гаячный ключ'
	if(gTdMenu[playerid][5] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawShow(playerid, gTdMenu[playerid][5]);

	if(car_menu && (vehicleid > 0))
	{
	    //получим id транспорта
//	    vehicleid = GetPlayerVehicleID(playerid);
	    cells = gVeh[vehicleid][1];
	    if(cells > 8)
	    {
			//скрываем данные игрока, ибо мешаются
			hide_statistic_data(playerid);
	    }
		//фон инвентаря авто
		PlayerTextDrawTextSize(playerid, gTdMenu[playerid][10], (cells > 2)?CELL_SIZE*(cells/2):CELL_SIZE, (cells > 1)?CELL_SIZE*2:CELL_SIZE);
		PlayerTextDrawTextSize(playerid, gTdMenu[playerid][15], (cells > 2)?CELL_SIZE*(cells/2):CELL_SIZE, 10.0);
		PlayerTextDrawShow(playerid, gTdMenu[playerid][10]);
		PlayerTextDrawShow(playerid, gTdMenu[playerid][15]);
		PlayerTextDrawShow(playerid, gTdMenu[playerid][16]);

	}
	else
	{
	    car_menu = 0;
		//фон объектов
		PlayerTextDrawShow(playerid, gTdMenu[playerid][7]);
		PlayerTextDrawShow(playerid, gTdMenu[playerid][13]);
		PlayerTextDrawShow(playerid, gTdMenu[playerid][14]);
	}

	//фон рюкзака и элементы
	if(gBag[playerid][0] > 0 && gBag[playerid][1] > 0)
	{
		//update_bag_menu(playerid);
		show_bag_menu(playerid);
	}

	//делаем все элементы инвентаря статическими
	for(k = 0; k < MAX_INVENTORY_ON_PLAYER; ++k)
	{
		gRotate[playerid][k] = 0;
	}

	for(k = 0; k < MAX_INVENTORY_ON_GROUND; ++k)
	{
		gRotateObject[playerid][k] = 0;
	}

	for(k = 0; k < MAX_INVENTORY_ON_VEHICLE; ++k)
	{
		gRotateVehicle[playerid][k] = 0;
	}

	for(k = 0; k < MAX_INVENTORY_IN_BAG; ++k)
	{
		gRotateBag[playerid][k] = 0;
	}

	//назначаем начальную позицию вращения
	for(k = 0; k < MAX_INVENTORY_ON_PLAYER; ++k)
	{
		gIndex[playerid][k] = 0;
	}

	for(k = 0; k < MAX_INVENTORY_ON_GROUND; ++k)
	{
		gIndexObject[playerid][k] = 0;
	}

	for(k = 0; k < MAX_INVENTORY_ON_VEHICLE; ++k)
	{
		gIndexVehicle[playerid][k] = 0;
	}

	for(k = 0; k < MAX_INVENTORY_IN_BAG; ++k)
	{
		gIndexBag[playerid][k] = 0;
	}

	//отображаем элементы инвентаря
	m = 0;
	for(i = 0; i < MAX_INVENTORY_ON_PLAYER/INVENTORY_CELLS_PER_ROW; ++i)
	for(j = 0; j < INVENTORY_CELLS_PER_ROW; ++j, ++m)
	{
	    if(gTdInventory[playerid][m][0] != PlayerText:INVALID_TEXT_DRAW)
			PlayerTextDrawShow(playerid, gTdInventory[playerid][m][0]);
	}

	if(car_menu)
	{
		create_vehicle_menu(playerid, vehicleid);
		for(m = 0; m < MAX_INVENTORY_ON_VEHICLE; ++m)
		{
		    if(m < gVeh[vehicleid][1])
		    {
		        if(gTdVehicle[playerid][m][0] != PlayerText:INVALID_TEXT_DRAW)
					PlayerTextDrawShow(playerid, gTdVehicle[playerid][m][0]);
			}
		}
	}
	else
	{
		//помечаем меню объектов как открытое
		gObjectsMenuShow[playerid] = 1;
		//create_objects_menu(playerid);
		find_and_cache_objects(playerid, 50.0);
		// m = 0;
		// for(i = 0; i < MAX_INVENTORY_ON_GROUND/GROUND_CELLS_PER_ROW; ++i)
		// for(j = 0; j < GROUND_CELLS_PER_ROW; ++j, ++m)
		// {
		    // if(gTdObject[playerid][m][0] != PlayerText:INVALID_TEXT_DRAW)
				// PlayerTextDrawShow(playerid, gTdObject[playerid][m][0]);
		// }
	}

	//запускаем выбор элементов инвентаря
	SelectTextDraw(playerid, 0x00FF00FF);

	//помечаем меню игрока как открытое
	gInventoryMenuShow[playerid] = 1;
	
	if(car_menu)
	{
		//помечаем меню авто как открытое
		gVehicleMenuShow[playerid] = vehicleid;
	}
	else
	{
		//помечаем меню объектов как открытое
		//gObjectsMenuShow[playerid] = 1;
	}

	if(gBag[playerid][0] > 0 && gBag[playerid][1] > 0)
	{
		//помечаем меню рюкзака как открытое
		gBagMenuShow[playerid] = 1;
	}
}

public hide_menu(playerid)
{
	new j,k;

	if( gInventoryMenuShow[playerid] == 0 &&
		gObjectsMenuShow[playerid] == 0 &&
		gVehicleMenuShow[playerid] == 0 &&
		gBagMenuShow[playerid] == 0 )
		return;

	//убираем отображение ячеек
	show_cells(playerid, INVENTORY_AREA, MAX_INVENTORY_ON_PLAYER, false);
	show_cells(playerid, VEHICLE_AREA, MAX_INVENTORY_ON_VEHICLE, false);
	show_cells(playerid, GROUND_AREA, MAX_INVENTORY_ON_GROUND, false);
	show_cells(playerid, BAG_AREA, MAX_INVENTORY_IN_BAG, false);

	//отображаем данные игрока
	show_statistic_data(playerid);

	//делаем все элементы инвентаря статическими
	//для корректного скрытия
	for(k = 0; k < MAX_INVENTORY_ON_PLAYER; ++k)
	{
		gRotate[playerid][k] = 0;
	}

	for(k = 0; k < MAX_INVENTORY_ON_GROUND; ++k)
	{
		gRotateObject[playerid][k] = 0;
	}

	for(k = 0; k < MAX_INVENTORY_ON_VEHICLE; ++k)
	{
		gRotateVehicle[playerid][k] = 0;
	}

	for(k = 0; k < MAX_INVENTORY_IN_BAG; ++k)
	{
		gRotateBag[playerid][k] = 0;
	}

	//прячем анимации инвентаря
	for(j = 0; j < MAX_INVENTORY_ON_PLAYER; ++j)
    for(k = 0; k < MAX_TURNS_OF_PREVIEW; ++k)
    {
        if(gTdInventory[playerid][j][k] != PlayerText:INVALID_TEXT_DRAW)
			PlayerTextDrawHide(playerid, gTdInventory[playerid][j][k]);
	}

	//прячем анимации земли
	for(j = 0; j < MAX_INVENTORY_ON_GROUND; ++j)
    for(k = 0; k < MAX_TURNS_OF_PREVIEW; ++k)
    {
		if(gObjectsMenuShow[playerid])
		{
//		    if(gTdObject[playerid][j][k] != PlayerText:INVALID_TEXT_DRAW)
		    {
				PlayerTextDrawDestroy(playerid, gTdObject[playerid][j][k]);
				gTdObject[playerid][j][k] = PlayerText:INVALID_TEXT_DRAW;
			}
		}
	}

	//прячем анимации меню авто
	for(j = 0; j < MAX_INVENTORY_ON_VEHICLE; ++j)
    for(k = 0; k < MAX_TURNS_OF_PREVIEW; ++k)
    {
		if(gVehicleMenuShow[playerid] > 0 && j < gVeh[gVehicleMenuShow[playerid]][1])
		{
			if(gTdVehicle[playerid][j][k] != PlayerText:INVALID_TEXT_DRAW)
			{
				PlayerTextDrawDestroy(playerid, gTdVehicle[playerid][j][k]);
				gTdVehicle[playerid][j][k] = PlayerText:INVALID_TEXT_DRAW;
			}
		}
	}

	//прячем содержимое рюкзака
	for(j = 0; j < MAX_INVENTORY_IN_BAG; ++j)
    for(k = 0; k < MAX_TURNS_OF_PREVIEW; ++k)
    {
		if(gTdBag[playerid][j][k] != PlayerText:INVALID_TEXT_DRAW)
		{
		   PlayerTextDrawHide(playerid, gTdBag[playerid][j][k]);
		   //gTdBag[playerid][j][k] = PlayerText:INVALID_TEXT_DRAW;
		}
	}

	//прячем дополнительные поля
	for(k = 0; k < TD_COUNT; ++k)
	{
	    if(gTdMenu[playerid][k] != PlayerText:INVALID_TEXT_DRAW)
			PlayerTextDrawHide(playerid, gTdMenu[playerid][k]);
	}

	//помечаем меню игрока как закрытое
	gInventoryMenuShow[playerid] = 0;

	//помечаем меню объектов как закрытое
	gObjectsMenuShow[playerid] = 0;

	//помечаем меню авто как закрытое
	gVehicleMenuShow[playerid] = 0;

	//помечаем меню рюкзака как закрытое
	gBagMenuShow[playerid] = 0;

	//прекращаем выбор
	CancelSelectTextDraw(playerid);
}

public hide_bag_menu(playerid)
{
	//убираем отображение ячеек
	show_cells(playerid, BAG_AREA, MAX_INVENTORY_IN_BAG, false);

	//помечаем меню рюкзака как закрытое
	gBagMenuShow[playerid] = 0;

	//делаем все элементы инвентаря статическими
	stop_all_rotates(playerid);

    if(gTdMenu[playerid][2] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawHide(playerid, gTdMenu[playerid][2]);
    if(gTdMenu[playerid][8] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawHide(playerid, gTdMenu[playerid][8]);
    if(gTdMenu[playerid][9] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawHide(playerid, gTdMenu[playerid][9]);
}

public destroy_bag_menu(playerid)
{
	new j, k;
	
    hide_bag_menu(playerid);
    
	//удаляем анимации меню рюкзака
	for(j = 0; j < MAX_INVENTORY_IN_BAG; ++j)
    for(k = 0; k < MAX_TURNS_OF_PREVIEW; ++k)
    {
        if(gTdBag[playerid][j][k] != PlayerText:INVALID_TEXT_DRAW)
        {
			PlayerTextDrawDestroy(playerid, gTdBag[playerid][j][k]);
			gTdBag[playerid][j][k] = PlayerText:INVALID_TEXT_DRAW;
		}
	}
}

public update_neighbors_objects_menu(playerid)
{
	new i;
	new Float:x, Float:y, Float:z;

	GetPlayerPos(playerid, x, y, z);

	for(i = 0; i < MAX_PLAYERS; ++i)
	{
	    if(playerid != i && IsPlayerStreamedIn(playerid, i) && IsPlayerInRangeOfPoint(i, 50.0, x, y, z))
	    {
	        new Float:x1, Float:y1, Float:z1;
	        new AnimIndex;//, LibName[128], AnimName[128];

			AnimIndex = GetPlayerAnimationIndex(i);
//			GetAnimationName(AnimIndex, LibName, sizeof(LibName), AnimName, sizeof(AnimName));
	        if(AnimIndex == 1189 || //стоит
			   AnimIndex == 1274 || //сидит
			   AnimIndex == 1159 || //закончил переход гусиным шагом
			   AnimIndex == 1177 || //очухался после удара (стоит)
			   AnimIndex == 1133) //закончил прыжок
	        {
		        GetPlayerPos(i, x1, y1, z1);
				//обновляем стример игрока
		        SetPlayerPos(i, x1+0.001, y1, z1);
		        //можно было бы ещё обновлять меню объектов, если оно отображается и персонаж находится достаточно близко
		        //...
		        if(gObjectsMenuShow[i] > 0 && IsPlayerInRangeOfPoint(i, 5.0, x, y, z))
				{
					//обновляем меню игрока "на земле"
				    update_objects_menu(i);
				}
			}
//			ApplyAnimation(i, LibName, AnimName, 4.1, 0, 1, 1, 0, 1000, 2);
	    }
	}
}

public update_objects_menu(playerid)
{
//	new i, j, k, m;

	if(gObjectsMenuShow[playerid] > 0)
	{
		//удаляем анимации дополнительного меню объектов
		//for(j = 0; j < MAX_INVENTORY_ON_GROUND; ++j)
	    //for(k = 0; k < MAX_TURNS_OF_PREVIEW; ++k)
	    //{
	    //    if(gTdObject[playerid][j][k] != PlayerText:INVALID_TEXT_DRAW)
	    //    {
		//		PlayerTextDrawDestroy(playerid, gTdObject[playerid][j][k]);
		//		gTdObject[playerid][j][k] = PlayerText:INVALID_TEXT_DRAW;
		//	}
		//}
		stop_all_rotates(playerid);
		//создаём дополнительное меню заново
		//create_objects_menu(playerid);

		find_and_cache_objects(playerid, 50.0);
		//короче тут надо отобразить меню в зависимости от кэша

		//m = 0;
		//for(i = 0; i < MAX_INVENTORY_ON_GROUND/GROUND_CELLS_PER_ROW; ++i)
		//for(j = 0; j < GROUND_CELLS_PER_ROW; ++j, ++m)
		//{
		//    if(gTdObject[playerid][m][0] != PlayerText:INVALID_TEXT_DRAW)
		//		PlayerTextDrawShow(playerid, gTdObject[playerid][m][0]);
		//}
	}
}

public update_vehicle_menu(playerid)
{
	new j, k;
	new vehicleid;
	
	vehicleid = gVehicleMenuShow[playerid];
	
	if(vehicleid > 0)
	{
		//удаляем анимации меню объектов авто
		for(j = 0; j < gVeh[vehicleid][1]; ++j)
	    for(k = 0; k < MAX_TURNS_OF_PREVIEW; ++k)
	    {
	        if(gTdVehicle[playerid][j][k] != PlayerText:INVALID_TEXT_DRAW)
	        {
				PlayerTextDrawDestroy(playerid, gTdVehicle[playerid][j][k]);
				gTdVehicle[playerid][j][k] = PlayerText:INVALID_TEXT_DRAW;
			}
		}
		stop_all_rotates(playerid);
		//создаём меню заново
		create_vehicle_menu(playerid, vehicleid);
		for(j = 0; j < gVeh[vehicleid][1]; ++j)
		{
		    if(gTdVehicle[playerid][j][0] != PlayerText:INVALID_TEXT_DRAW)
				PlayerTextDrawShow(playerid, gTdVehicle[playerid][j][0]);
		}
	}
}

public update_bag_menu(playerid)
{
	if(gBag[playerid][0] <= 0 && gBag[playerid][1] <= 0)
	{
	    destroy_bag_menu(playerid);
	    return;
	}

	//делаем все элементы инвентаря статическими
	stop_all_rotates(playerid);
	//создаём дополнительное меню заново
	create_bag_menu(playerid);
}

public show_bag_menu(playerid)
{
	new m;

	if(gBag[playerid][0] <= 0 && gBag[playerid][1] <= 0)
	{
	    destroy_bag_menu(playerid);
	    return;
	}

	//отображаем фон меню рюкзака
	if(gTdMenu[playerid][2] != PlayerText:INVALID_TEXT_DRAW)
	{
		PlayerTextDrawTextSize(playerid, gTdMenu[playerid][2], CELL_SIZE_BAG*BACKPACK_LINE, CELL_SIZE_BAG*(gBag[playerid][0]/BACKPACK_LINE));
		PlayerTextDrawShow(playerid, gTdMenu[playerid][2]);
	}
    if(gTdMenu[playerid][8] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawShow(playerid, gTdMenu[playerid][8]);
    if(gTdMenu[playerid][9] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawShow(playerid, gTdMenu[playerid][9]);

	for(m = 0; m < gBag[playerid][0]; ++m)
	{
	    if(gTdBag[playerid][m][0] != PlayerText:INVALID_TEXT_DRAW)
			PlayerTextDrawShow(playerid, gTdBag[playerid][m][0]);
	}

	gBagMenuShow[playerid] = 1;

	//отображение ячеек
	show_cells(playerid, BAG_AREA, MAX_INVENTORY_IN_BAG, false); //прячем все возможные ячейки
	show_cells(playerid, BAG_AREA, gBag[playerid][0], true); //показываем столько, сколько в рюкзаке
}

public destroy_menu(playerid)
{
	new j,k;

	//прекращаем выбор
	CancelSelectTextDraw(playerid);

	//спрячем весь инвентарь
	hide_menu(playerid);

	//удаляем анимации инвентаря
	for(j = 0; j < MAX_INVENTORY_ON_PLAYER; ++j)
    for(k = 0; k < MAX_TURNS_OF_PREVIEW; ++k)
    {
        if(gTdInventory[playerid][j][k] != PlayerText:INVALID_TEXT_DRAW)
        {
			PlayerTextDrawDestroy(playerid, gTdInventory[playerid][j][k]);
			gTdInventory[playerid][j][k] = PlayerText:INVALID_TEXT_DRAW;
		}
	}

	//удаляем анимации земли
	for(j = 0; j < MAX_INVENTORY_ON_GROUND; ++j)
    for(k = 0; k < MAX_TURNS_OF_PREVIEW; ++k)
    {
		if(gObjectsMenuShow[playerid])
		{
		    if(gTdObject[playerid][j][k] != PlayerText:INVALID_TEXT_DRAW)
		    {
				PlayerTextDrawDestroy(playerid, gTdObject[playerid][j][k]);
				gTdObject[playerid][j][k] = PlayerText:INVALID_TEXT_DRAW;
			}
		}
	}

	//удаляем анимации авто
	for(j = 0; j < MAX_INVENTORY_ON_VEHICLE; ++j)
    for(k = 0; k < MAX_TURNS_OF_PREVIEW; ++k)
    {
		if(gVehicleMenuShow[playerid] > 0 && j < gVeh[gVehicleMenuShow[playerid]][1])
		{
			if(gTdVehicle[playerid][j][k] != PlayerText:INVALID_TEXT_DRAW)
			{
				PlayerTextDrawDestroy(playerid, gTdVehicle[playerid][j][k]);
				gTdVehicle[playerid][j][k] = PlayerText:INVALID_TEXT_DRAW;
			}
		}
	}

	//удаляем анимации рюкзака
	for(j = 0; j < MAX_INVENTORY_IN_BAG; ++j)
    for(k = 0; k < MAX_TURNS_OF_PREVIEW; ++k)
    {
		if(gTdBag[playerid][j][k] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, gTdBag[playerid][j][k]);
			gTdBag[playerid][j][k] = PlayerText:INVALID_TEXT_DRAW;
		}
	}

	//удаляем дополнительные поля
	for(k = 0; k < TD_COUNT; ++k)
	{
	    if(gTdMenu[playerid][k] != PlayerText:INVALID_TEXT_DRAW)
	    {
			PlayerTextDrawDestroy(playerid, gTdMenu[playerid][k]);
			gTdMenu[playerid][k] = PlayerText:INVALID_TEXT_DRAW;
		}
	}

	//помечаем меню игрока как закрытое
	gInventoryMenuShow[playerid] = 0;

	//помечаем меню объектов как закрытое
	gObjectsMenuShow[playerid] = 0;

	//помечаем меню авто как закрытое
	gVehicleMenuShow[playerid] = 0;

	//помечаем меню рюкзака как закрытое
	gBagMenuShow[playerid] = 0;
}

//удалить отображение ячеек
public destroy_cells()
{
	new i;
	
	for(i = 0; i < MAX_INVENTORY_ON_PLAYER; ++i)
	{
		if(gTdInvCells[i] != Text:INVALID_TEXT_DRAW)
		{
		    TextDrawDestroy(gTdInvCells[i]);
		    gTdInvCells[i] = Text:INVALID_TEXT_DRAW;
		}
	}
	for(i = 0; i < MAX_INVENTORY_ON_VEHICLE; ++i)
	{
		if(gTdVehCells[i] != Text:INVALID_TEXT_DRAW)
		{
		    TextDrawDestroy(gTdVehCells[i]);
		    gTdVehCells[i] = Text:INVALID_TEXT_DRAW;
		}
	}
	for(i = 0; i < MAX_INVENTORY_IN_BAG; ++i)
	{
	    if(gTdBagCells[i] != Text:INVALID_TEXT_DRAW)
	    {
			TextDrawDestroy(gTdBagCells[i]);
		    gTdBagCells[i] = Text:INVALID_TEXT_DRAW;
	    }
	}
}

//сбросить весь выбор
public stop_all_rotates(playerid)
{
	new i;

	for(i = 0; i < MAX_INVENTORY_ON_PLAYER; ++i)
	{
	    if(gRotate[playerid][i] == 1)
	    {
		    gRotate[playerid][i] = 0;
		    if(gTdInventory[playerid][i][gIndex[playerid][i]] != PlayerText:INVALID_TEXT_DRAW)
				PlayerTextDrawHide(playerid, gTdInventory[playerid][i][gIndex[playerid][i]]);
			if(gTdInventory[playerid][i][0] != PlayerText:INVALID_TEXT_DRAW)
				PlayerTextDrawShow(playerid, gTdInventory[playerid][i][0]);
			gIndex[playerid][i] = 0;
		}
	}

	for(i = 0; i < MAX_INVENTORY_ON_GROUND; ++i)
	{
	    if(gObjectsMenuShow[playerid] > 0 && gRotateObject[playerid][i] == 1)
	    {
		    gRotateObject[playerid][i] = 0;
		    if(gTdObject[playerid][i][gIndexObject[playerid][i]] != PlayerText:INVALID_TEXT_DRAW)
				PlayerTextDrawHide(playerid, gTdObject[playerid][i][gIndexObject[playerid][i]]);
			if(gTdObject[playerid][i][0] != PlayerText:INVALID_TEXT_DRAW)
				PlayerTextDrawShow(playerid, gTdObject[playerid][i][0]);
			gIndexObject[playerid][i] = 0;
		}
	}

    for(i = 0; i < MAX_INVENTORY_ON_VEHICLE; ++i)
	{
	    if(gVehicleMenuShow[playerid] > 0 && i < gVeh[gVehicleMenuShow[playerid]][1] && gRotateVehicle[playerid][i] == 1)
	    {
		    gRotateVehicle[playerid][i] = 0;
		    if(gTdVehicle[playerid][i][gIndexVehicle[playerid][i]] != PlayerText:INVALID_TEXT_DRAW)
				PlayerTextDrawHide(playerid, gTdVehicle[playerid][i][gIndexVehicle[playerid][i]]);
			if(gTdVehicle[playerid][i][0] != PlayerText:INVALID_TEXT_DRAW)
				PlayerTextDrawShow(playerid, gTdVehicle[playerid][i][0]);
			gIndexVehicle[playerid][i] = 0;
		}
	}

    for(i = 0; i < MAX_INVENTORY_IN_BAG; ++i)
	{
	    if(gBagMenuShow[playerid] > 0 && i < gBag[playerid][0] && gRotateBag[playerid][i] == 1)
	    {
		    gRotateBag[playerid][i] = 0;
		    if(gTdBag[playerid][i][gIndexBag[playerid][i]] != PlayerText:INVALID_TEXT_DRAW)
				PlayerTextDrawHide(playerid, gTdBag[playerid][i][gIndexBag[playerid][i]]);
			if(gTdBag[playerid][i][0] != PlayerText:INVALID_TEXT_DRAW)
				PlayerTextDrawShow(playerid, gTdBag[playerid][i][0]);
			gIndexBag[playerid][i] = 0;
		}
	}
}

//проверяет, не нужно ли удалить отображение статуса авто
public check_vehicle_menu_show()
{
	for(new i = 0; i < MAX_PLAYERS; ++i)
	{
	    if(gVehicleDataShow[i] > 0 && !IsPlayerInVehicleReal(i))
	    {
	        destroy_vehicle_sensors(i);
		}
/*
	    if(gVehicleDataShow[i] == 0 && IsPlayerInAnyVehicle(i))
	    {
	        new anim;

	        anim = GetPlayerAnimationIndex(i);
	        if(anim == 0)
		        create_vehicle_sensors(i, GetPlayerVehicleID(i));
		}
*/
	}
}

public is_one_inventory_cell_selected(playerid, area)
{
	new i, count, mem;

	count = 0;
	mem = -1;
	for(i = 0; i < MAX_INVENTORY_ON_PLAYER; ++i)
	{
	    if(gRotate[playerid][i] > 0)
	    {
	        if(area == INVENTORY_AREA)
		        mem = i;
	        count++;
	    }
	}

	for(i = 0; i < MAX_INVENTORY_ON_GROUND; ++i)
	{
	    if(gRotateObject[playerid][i] > 0)
	    {
	        if(area == GROUND_AREA)
		        mem = i;
	        count++;
		}

	 }

	for(i = 0; i < MAX_INVENTORY_ON_VEHICLE; ++i)
	{
		if(gVehicleMenuShow[playerid])
		{
		    if(gRotateVehicle[playerid][i] > 0)
		    {
		        if(area == VEHICLE_AREA)
			        mem = i;
		        count++;
		    }
		}
	}

	for(i = 0; i < MAX_INVENTORY_IN_BAG; ++i)
	{
		if(gBagMenuShow[playerid])
		{
		    if(gRotateBag[playerid][i] > 0)
		    {
		        if(area == BAG_AREA)
			        mem = i;
		        count++;
		    }
		}
	}

	if(count == 1 && mem != -1)
	    return mem;
	else
	    return -1;
}

//inv1 - откуда
//inv2 - куда
//нумерация с 0
public replace_inventory(playerid, inv1, inv2)
{
	new k;

	//защита от некорректного вызова функции
	if(gInventoryItem[playerid][inv2][db_id] != -1 || gInventoryItem[playerid][inv1][db_id] == -1)
	    return;

	//остановим вращение выбранного объекта
	gRotate[playerid][inv1] = 0;
	gIndex[playerid][inv1] = 0;
	gRotate[playerid][inv2] = 0;
	gIndex[playerid][inv2] = 0;

	//удаляем анимации выбранных объектов
    for(k = 0; k < MAX_TURNS_OF_PREVIEW; ++k)
    {
		if(gTdInventory[playerid][inv2][k] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, gTdInventory[playerid][inv2][k]);
			gTdInventory[playerid][inv2][k] = PlayerText:INVALID_TEXT_DRAW;
		}
	}

	//производим перенос в БД и перенос кэш
	move_character_inventory_cell(playerid, inv1, inv2);
	create_views_of_items(playerid, -1, inv2, INVENTORY_AREA); //куда
	create_views_of_items(playerid, -1, inv1, INVENTORY_AREA); //откуда
}

//inv - ячейка инвентаря
//obj - ячейка объектов
//нумерация с 0
public take_object(playerid, inv, obj)
{
	new k, m, ret;
	new old_gBag;

	//защита от некорректного вызова функции
	if(gInventoryItem[playerid][inv][db_id] != -1 || gGroundItem[playerid][obj][db_id] == -1)
	    return;

	//запоминаем состояние рюкзака
	old_gBag = gBag[playerid][1];

	//остановим вращение выбранного объекта
	gRotate[playerid][inv] = 0;
	gRotateObject[playerid][obj] = 0;

	//проверяем, не автомобиль ли перемещаемый объект
	for(new i = 0; i < MAX_PLAYERS; ++i)
	{
	    if(gVeh[i][0] == gGroundItem[playerid][obj][db_id])
	    {
	        //сбрасываем выбор ячейки
		    if(gTdObject[playerid][obj][gIndexObject[playerid][obj]] != PlayerText:INVALID_TEXT_DRAW)
				PlayerTextDrawHide(playerid, gTdObject[playerid][obj][gIndexObject[playerid][obj]]);
			if(gTdObject[playerid][obj][0] != PlayerText:INVALID_TEXT_DRAW)
				PlayerTextDrawShow(playerid, gTdObject[playerid][obj][0]);
			gIndex[playerid][inv] = 0;
			gIndexObject[playerid][obj] = 0;
			return;
		}
	}

	//установим индексы активных текстдравов
	gIndex[playerid][inv] = 0;
	gIndexObject[playerid][obj] = 0;
	
	ret = 0;

	if(gGroundItem[playerid][obj][obj_owner] != 0 && gGroundItem[playerid][obj][obj_owner] != gPlayersID[playerid])
	{
		//чужая вещь!
		imes_simple_single(playerid, 0xFF3333FF, "NOT_YOUR_OBJECT");
	    ret = -1;
	}

	//производим перенос в БД, если объект ещё никто не подобрал
	switch(gGroundItem[playerid][obj][obj_inventory])
	{
	    case 0:
		{
			//вещь не для инвентаря - выходим
		    ret = -2;
		}
	    case 2:
	    {
	        //не даём взять второй рюкзак
	        if(gBag[playerid][1] > 0)
	        {
	            ret = -3;
			}
	    }
	}

	if(ret < 0)
	{
	    stop_all_rotates(playerid);
		//отображаем ячейку
		if(gObjectsMenuShow[playerid] > 0)
		{
			for(k = 0; k < MAX_TURNS_OF_PREVIEW; ++k)
			{
			    if(gTdObject[playerid][obj][k] != PlayerText:INVALID_TEXT_DRAW)
					PlayerTextDrawHide(playerid, gTdObject[playerid][obj][k]);
			}
		    if(gTdObject[playerid][obj][0] != PlayerText:INVALID_TEXT_DRAW)
				PlayerTextDrawShow(playerid, gTdObject[playerid][obj][0]);
		}
	    return;
	}
	//перемещаем кэш объекта
    move_craft_item(gInventoryItem[playerid][inv], gGroundItem[playerid][obj]);

	//создаём картинки в инвентаре
	create_views_of_items(playerid, -1, inv, INVENTORY_AREA);
	//удаляем картинки в инвентаре
	create_views_of_items(playerid, -1, obj, GROUND_AREA);

    //обновляем БД, перед этим обязательно должен быть уже перенесён кэш объекта
	set_character_inventory_cell(playerid, inv, gInventoryItem[playerid][inv][db_id], false);

	//удаляем анимации выбранных объектов
    //for(k = 0; k < MAX_TURNS_OF_PREVIEW; ++k)
    //{
    //    if(gTdObject[playerid][obj][k] != PlayerText:INVALID_TEXT_DRAW)
    //    {
	//		PlayerTextDrawDestroy(playerid, gTdObject[playerid][obj][k]);
	//		gTdObject[playerid][obj][k] = PlayerText:INVALID_TEXT_DRAW;
	//	}
	//}
	
	if(gInventoryItem[playerid][inv][obj_auto] == 1)
	{
		auto_apply_one_cell(playerid, -1, inv, INVENTORY_AREA);
	}

	if(gBag[playerid][1] != old_gBag)
	{
	    if(gBag[playerid][1] > 0) //если есть рюкзак
		{
			for(m = 0; m < gBag[playerid][0]; ++m)
			{
				if(gBagItem[playerid][m][obj_auto] == 1)
				    auto_apply_one_cell(playerid, -1, m, BAG_AREA);
			}
		}
	}

	update_neighbors_objects_menu(playerid);
}

//показать созданный объект в инвентаре
public put_object(playerid, cell)
{
	//остановим вращение выбранного объекта
	gRotate[playerid][cell] = 0;
	gIndex[playerid][cell] = 0;

	//создаём картинки в инвентаре
	create_views_of_items(playerid, -1, cell, INVENTORY_AREA);

	if(gInventoryItem[playerid][cell][obj_auto] == 1)
	    auto_apply_one_cell(playerid, -1, cell, INVENTORY_AREA);
}

//отобразить созданный объект в инвентаре транспорта
public put_vehicle_object(playerid, vehicleid, cell)
{
	new k;
	
	//остановим вращение выбранного объекта
	gRotateVehicle[playerid][cell] = 0;
	gIndexVehicle[playerid][cell] = 0;

	//создаём картинки в инвентаре
	create_views_of_items(playerid, vehicleid, cell, VEHICLE_AREA);

	for(k = 0; k < MAX_PLAYERS; ++k)
	{
	    if(k != playerid && gVehicleMenuShow[k] == vehicleid)
	    {
	        update_vehicle_menu(k);
	    }
	}
}

//отобразить созданный объект в инвентаре рюкзака
public put_bag_object(playerid, cell)
{
	if(gBag[playerid][0] <= 0 || gBag[playerid][1] <= 0)
	    return;

	if(cell < 0 || cell >= MAX_INVENTORY_IN_BAG)
	    return;

	//остановим вращение выбранного объекта
	gRotateBag[playerid][cell] = 0;
	gIndexBag[playerid][cell] = 0;

	//создаём картинки в инвентаре
	create_views_of_items(playerid, -1, cell, BAG_AREA);
}

//просто удалить катинки объекта из инвентаря
public remove_object(playerid, cell, bool:check)
{
	//остановим вращение выбранного объекта
	gRotate[playerid][cell] = 0;
	gIndex[playerid][cell] = 0;

	if(check)
	{
	    if(gInventoryItem[playerid][cell][db_id] > 0)
	        return;
	}
	//обнуляем кэш
	zero_craft_item(gInventoryItem[playerid][cell]);

	//создаём картинки в инвентаре
	create_views_of_items(playerid, -1, cell, INVENTORY_AREA);
}

//просто удалить объект из инвентаря авто
public remove_vehicle_object(playerid, vehicleid, cell)
{
	new k;

	//остановим вращение выбранного объекта
	gRotateVehicle[playerid][cell] = 0;
	gIndexVehicle[playerid][cell] = 0;

	//создаём картинки в инвентаре
	create_views_of_items(playerid, vehicleid, cell, VEHICLE_AREA);

	for(k = 0; k < MAX_PLAYERS; ++k)
	{
	    if(k != playerid && gVehicleMenuShow[k] == vehicleid)
	    {
	        update_vehicle_menu(k);
	    }
	}
}

//просто удалить объект из рюкзака
public remove_bag_object(playerid, cell)
{
	if(gBag[playerid][0] <= 0 || gBag[playerid][1] <= 0)
	    return;

	if(cell < 0 || cell >= MAX_INVENTORY_IN_BAG)
	    return;

	//остановим вращение выбранного объекта
	gRotateBag[playerid][cell] = 0;
	gIndexBag[playerid][cell] = 0;

	//создаём картинки в инвентаре
	create_views_of_items(playerid, -1, cell, BAG_AREA);
}

public take_from_vehicle(playerid, vehicleid, cell, veh_cell)
{
	new ret;
	
	//перекладываем из БД авто в БД игрока
    if((ret = take_vehicle_inventory_cell(playerid, vehicleid, cell, veh_cell)) < 0)
    {
	    if(ret == -5)
	        imes_simple_single(playerid, 0xFF3333FF, "NOT_YOUR_OBJECT");
	    stop_all_rotates(playerid);
		//отображаем ячейку
		if(gVehicleMenuShow[playerid] > 0)
		{
			for(new k = 0; k < MAX_TURNS_OF_PREVIEW; ++k)
			{
			    if(gTdVehicle[playerid][veh_cell][k] != PlayerText:INVALID_TEXT_DRAW)
					PlayerTextDrawHide(playerid, gTdVehicle[playerid][veh_cell][k]);
			}
		    if(gTdVehicle[playerid][veh_cell][0] != PlayerText:INVALID_TEXT_DRAW)
				PlayerTextDrawShow(playerid, gTdVehicle[playerid][veh_cell][0]);
		}
        return;
	}
    //помещаем в инвентарь игрока
    put_object(playerid, cell);
    //удаляем из инветнаря авто
	remove_vehicle_object(playerid, vehicleid, veh_cell);
}

public take_from_bag(playerid, cell, bag_cell)
{
	new ret;
	//перекладываем из БД рюкзака в БД игрока
    if((ret = take_bag_inventory_cell(playerid, cell, bag_cell)) < 0)
    {
	    if(ret == -5)
	        imes_simple_single(playerid, 0xFF3333FF, "NOT_YOUR_OBJECT");
	    stop_all_rotates(playerid);
		//отображаем ячейку
		if(gBagMenuShow[playerid] > 0)
		{
			for(new k = 0; k < MAX_TURNS_OF_PREVIEW; ++k)
			{
			    if(gTdBag[playerid][bag_cell][k] != PlayerText:INVALID_TEXT_DRAW)
					PlayerTextDrawHide(playerid, gTdBag[playerid][bag_cell][k]);
			}
		    if(gTdBag[playerid][bag_cell][0] != PlayerText:INVALID_TEXT_DRAW)
				PlayerTextDrawShow(playerid, gTdBag[playerid][bag_cell][0]);
		}
        return;
	}
    //помещаем в инвентарь игрока
    put_object(playerid, cell);
    //удаляем из инветнаря рюкзака
	remove_bag_object(playerid, bag_cell);
}

public put_in_vehicle(playerid, vehicleid, cell, veh_cell)
{
	//отменить действие вещи для игрока
	unapply_one_cell(playerid, cell, INVENTORY_AREA);
	//помещаем в БД авто, удаляем из БД игрока
    give_vehicle_inventory_cell(playerid, vehicleid, cell, veh_cell);
	//удаляем из инвентаря игрока
    remove_object(playerid, cell, false);
	//помещаем в инвентарь авто
	put_vehicle_object(playerid, vehicleid, veh_cell);
}

public put_in_veh_from_bag(playerid, vehicleid, cell, veh_cell)
{
	//отменить действие вещи для игрока
	unapply_one_cell(playerid, cell, BAG_AREA);
	//помещаем в БД авто, удаляем из БД игрока
    give_veh_invent_cell_from_bag(playerid, vehicleid, cell, veh_cell);
	//удаляем из инвентаря рюкзака
    remove_bag_object(playerid, cell);
	//помещаем в инвентарь авто
	put_vehicle_object(playerid, vehicleid, veh_cell);
}

public put_in_bag(playerid, cell, bag_cell)
{
	//отменить действие вещи для игрока
	//unapply_one_cell(playerid, cell, INVENTORY_AREA);
	//помещаем в БД рюкзака, удаляем из БД игрока
    if(give_bag_inventory_cell(playerid, cell, bag_cell) < 0)
    {
	    stop_all_rotates(playerid);
		//отображаем ячейку
		if(gInventoryMenuShow[playerid] > 0)
		{
			for(new k = 0; k < MAX_TURNS_OF_PREVIEW; ++k)
			{
			    if(gTdInventory[playerid][bag_cell][k] != PlayerText:INVALID_TEXT_DRAW)
					PlayerTextDrawHide(playerid, gTdInventory[playerid][bag_cell][k]);
			}
		    if(gTdInventory[playerid][bag_cell][0] != PlayerText:INVALID_TEXT_DRAW)
				PlayerTextDrawShow(playerid, gTdInventory[playerid][bag_cell][0]);
		}
        //apply_one_cell(playerid, -1, cell, INVENTORY_AREA);
        return;
	}
	//удаляем из инвентаря игрока
    remove_object(playerid, cell, false);
	//помещаем в рюкзак
	put_bag_object(playerid, bag_cell);
}

public put_in_bag_from_veh(playerid, vehicleid, cell, bag_cell)
{
	new ret;

	//помещаем в БД рюкзака, удаляем из БД авто
    if((ret = give_bag_invent_cell_from_veh(playerid, vehicleid, cell, bag_cell)) < 0)
    {
		printf("put_in_bag_from_veh: error, ret=%d", ret);
	    stop_all_rotates(playerid);
		//отображаем ячейку
		if(gVehicleMenuShow[playerid] > 0)
		{
			for(new k = 0; k < MAX_TURNS_OF_PREVIEW; ++k)
			{
			    if(gTdVehicle[playerid][cell][k] != PlayerText:INVALID_TEXT_DRAW)
					PlayerTextDrawHide(playerid, gTdVehicle[playerid][cell][k]);
			}
		    if(gTdVehicle[playerid][cell][0] != PlayerText:INVALID_TEXT_DRAW)
				PlayerTextDrawShow(playerid, gTdVehicle[playerid][cell][0]);
		}
        return;
	}
	//удаляем картинки из инвентаря авто
    remove_vehicle_object(playerid, vehicleid, cell);
	//помещаем картинки в рюкзак
	put_bag_object(playerid, bag_cell);
	//применяем, если вещь с автоприменением
	if(gBagItem[playerid][bag_cell][obj_auto] == 1)
	    auto_apply_one_cell(playerid, -1, bag_cell, BAG_AREA);
}

public put_in_bag_from_grnd(playerid, cell, bag_cell)
{
	new ret;
	
	//помещаем в БД рюкзака
	ret = give_bag_invent_cell_from_grnd(playerid, cell, bag_cell);

    if(ret < 0)
    {
		if(ret == -5)
		    imes_simple_single(playerid, 0xFF3333FF, "NOT_YOUR_OBJECT");
	    stop_all_rotates(playerid);
        return;
	}
	//перемещаем кэш
	move_craft_item(gBagItem[playerid][bag_cell], gGroundItem[playerid][cell]);
	//помещаем в рюкзак
	put_bag_object(playerid, bag_cell);
    //обновляем содержимое ячейки
	//update_objects_menu(playerid);
	create_views_of_items(playerid, -1, cell, GROUND_AREA);
	update_neighbors_objects_menu(playerid);
    stop_all_rotates(playerid);
	if(gBagItem[playerid][bag_cell][obj_auto] == 1)
	    auto_apply_one_cell(playerid, -1, bag_cell, BAG_AREA);
}

public replace_vehicle_inventory(playerid, vehicleid, inv1, inv2)
{
	//перемещаем объект БД и его кэш в авто
	move_vehicle_inventory_cell(vehicleid, inv1, inv2);
	//удаляем из стаарой позиции в инвентаре авто
	remove_vehicle_object(playerid, vehicleid, inv1);
	//помещаем в новую позицию в инвентаре авто
	put_vehicle_object(playerid, vehicleid, inv2);
}

public replace_bag_inventory(playerid, inv1, inv2)
{
	//перемещаем объект в БД рюкзака
	move_bag_inventory_cell(playerid, inv1, inv2);
	//удаляем из стаарой позиции в инвентаре рюкзака
	remove_bag_object(playerid, inv1);
	//помещаем в новую позицию в инвентаре рюкзака
	put_bag_object(playerid, inv2);
}

//inv - ячейка инвентаря
//obj - ячейка объектов
//нумерация с 0
public drop_object(playerid, inv, obj)
{
	new Float:x,Float:y,Float:z;

	//защита от некорректного вызова функции
	if(gInventoryItem[playerid][inv][db_id] == -1 || gGroundItem[playerid][obj][db_id] != -1)
	    return;

	GetPlayerPos(playerid,x,y,z);

	//остановим вращение выбранного объекта
	gRotate[playerid][inv] = 0;
	gIndex[playerid][inv] = 0;
	gRotateObject[playerid][obj] = 0;
	gIndexObject[playerid][obj] = 0;

	if(gInventoryItem[playerid][inv][obj_auto] == 1)
	{
		//отменить действие вещи
		unapply_one_cell(playerid, inv, INVENTORY_AREA);
	}

	//переносим кэш
	move_craft_item(gGroundItem[playerid][obj],gInventoryItem[playerid][inv]);

	//создаём картинки
	create_views_of_items(playerid, -1, inv, INVENTORY_AREA);
	create_views_of_items(playerid, -1, obj, GROUND_AREA);

	//производим перенос в БД
	drop_character_inventory_cell(playerid, inv, obj, x,y,z);

	update_neighbors_objects_menu(playerid);
	
	gFullInvent[playerid] = 0;
}

//inv - ячейка инвентаря
//obj - ячейка объектов
//нумерация с 0
public drop_bag_object(playerid, inv, obj)
{
	new Float:x,Float:y,Float:z;

	//защита от некорректного вызова функции
	if(gBagItem[playerid][inv][db_id] == -1 || gGroundItem[playerid][obj][db_id] != -1)
	    return;

	GetPlayerPos(playerid,x,y,z);

	//остановим вращение выбранного объекта
	gRotateBag[playerid][inv] = 0;
	gIndexBag[playerid][inv] = 0;
	gRotateObject[playerid][obj] = 0;
	gIndexObject[playerid][obj] = 0;

	if(gBagItem[playerid][inv][obj_auto] == 1)
	{
		//отменить действие вещи
		unapply_one_cell(playerid, inv, BAG_AREA);
	}

	//перемещаем кэш
	move_craft_item(gGroundItem[playerid][obj], gBagItem[playerid][inv]);
	create_views_of_items(playerid, -1, inv, BAG_AREA);
	create_views_of_items(playerid, -1, obj, GROUND_AREA);

	//производим перенос в БД
	drop_bag_inventory_cell(playerid, inv, obj, x,y,z);

	update_neighbors_objects_menu(playerid);

	gFullInvent[playerid] = 0;
}

public bool:is_player_on_gas_station(playerid)
{
	new Float:radius;

	radius=50.0; //пока не сделаю свои точки

	if( IsPlayerInRangeOfPoint(playerid, radius, 1920.6521, -1791.8212, 13.3802) ||	//Idlewood Gas
		IsPlayerInRangeOfPoint(playerid, radius, 995.0821, -920.3821, 42.1803) ||	//Mulholland Gas
		IsPlayerInRangeOfPoint(playerid, radius, 647.5121, -564.8921, 16.21022) ||	//Dillimore Gas
		IsPlayerInRangeOfPoint(playerid, radius, 1369.6621, 464.6521, 20.0112) ||	//Montgomery Gas
		IsPlayerInRangeOfPoint(playerid, radius, -66.4521, -1172.1201, 1.8501) ||	//Flint Gas
		IsPlayerInRangeOfPoint(playerid, radius, -1581.6712, -2714.9921, 48.5401) ||	//Whestone Gas
		IsPlayerInRangeOfPoint(playerid, radius, -2237.3245, -2570.9921, 31.9201) ||	//Angel Pine Gas
		IsPlayerInRangeOfPoint(playerid, radius, 2061.2015, 159.2013, 28.8412) ||	//Doherty Gas
		IsPlayerInRangeOfPoint(playerid, radius, -2428.3821, 993.9012, 45.3012) ||	//Juniper Gas
		IsPlayerInRangeOfPoint(playerid, radius, -1699.9421, 413.5921, 7.1821) ||	//Easter Gas
		IsPlayerInRangeOfPoint(playerid, radius, -1326.5312, 2698.5210, 50.0612) ||	//El Guebrabos Gas
		IsPlayerInRangeOfPoint(playerid, radius, -1462.7121, 1864.5721, 32.6312) ||	//Tierra Robada Gas
		IsPlayerInRangeOfPoint(playerid, radius, 65.1613, 1211.3212, 18.8101) ||	//Fort Carson Gas
		IsPlayerInRangeOfPoint(playerid, radius, 2173.1231, 2478.3012, 10.8201) ||	//Emerald Isle Gas
		IsPlayerInRangeOfPoint(playerid, radius, 2138.4712, 2747.6012, 10.8201) ||	//Prickle Pine Gas
		IsPlayerInRangeOfPoint(playerid, radius, 2639.6113, 1121.9921, 10.8201) ||	//Jullius Gas
		IsPlayerInRangeOfPoint(playerid, radius, 2115.6001, 919.36, 10.8201) ||	//Come A Lot Gas
		IsPlayerInRangeOfPoint(playerid, radius, 606.2412, 1688.6121, 6.9915) ||	//Bone County Gas
		IsPlayerInRangeOfPoint(playerid, radius, 1597.5412, 2213.2810, 10.8201) ||	//Redsands West Gas
		IsPlayerInRangeOfPoint(playerid, radius, -2026.0, 156.0, 29.0) ||	//SF Garage
		IsPlayerInRangeOfPoint(playerid, radius, -737, 2745.0, 47.22) ||	//LV, Small Gas Station
		is_player_near_objects(playerid, "\"GAS_OBJECT\",\"GASOLINE_VEHICLE\"", 10.0) )
	{
        return true;
	}

	return false;
}

public bool:is_player_near_fire(playerid)
{
	 return is_player_near_objects(playerid, "\"FIRE_OBJECT\",\"NODJA_OBJECT\"", 10.0);
}

public ChooseLanguage(playerid)
{
  new i;
  new mes[1800]; //само сообщение
  new lang_mes[64]; //языки
  new ok_mes[64]; //надпись на кнопке "OK"
  new cancel_mes[64]; //надпись на кнопке "Отмена"
  new title[128]; //заголовок

  strdel(mes, 0, sizeof(mes));
  strcat(mes, "{FFFFFF}");
  imessage(mes, "DONT_CHANGE", gPlayerLang[playerid]);
  strcat(mes, "\n");
  for(i = 0; i  < gLangsNumber; ++i)
  {
    imessage(lang_mes, "LANGUAGE_NAME", gAllLangs[i]);
    strcat(mes, "{FFFF00}");
    strcat(mes, gAllLangs[i]);
    strcat(mes, "\t{0000FF}[{00FF00}");
    strcat(mes, lang_mes);
    strcat(mes, "{0000FF}]\n");
  }
  imessage(title, "LANGUAGE_TITLE", gPlayerLang[playerid]);
  imessage(ok_mes, "OK_MESSAGE", gPlayerLang[playerid]);
  imessage(cancel_mes, "CANCEL_MESSAGE", gPlayerLang[playerid]);
  ShowPlayerDialog(playerid, 756, DIALOG_STYLE_LIST, title, mes, ok_mes, cancel_mes);
}

public player_login_menu()
{
	new mes[1024]; //само сообщение
	new reg_date_mes[256]; //сообщение о дате регистрации
	new reg_date[64]; //дата регистрации
	new name[64]; //ник игрока
	new pass[128]; //предупреждение о длине пароля
	new ok_mes[16]; //надпись на кнопке "OK"
	new cancel_mes[16]; //надпись на кнопке "Отмена"
	new title[64]; //заголовок
	new bool:restart;

	restart = false;
	for(new playerid = 0; playerid < MAX_PLAYERS; ++playerid)
	{
	    if(gPlayerPasswordRequest[playerid] == 0)
	        continue;

	    if(gPlayerPasswordRequest[playerid] == 2)
	    {
			restart = true;
		}
		else
		{
	        gPlayerPasswordRequest[playerid] = 0;
			strdel(mes, 0, sizeof(mes));
			get_players_value("reg_date", "players", gPlayersID[playerid], reg_date);
			if(strlen(reg_date) > 0)
			{
				GetPlayerName(playerid, name, sizeof(name));
				imessage(reg_date_mes, "REG_DATE_MESSAGE", gPlayerLang[playerid]);
				format(mes, sizeof(mes), reg_date_mes, name, reg_date);
				strcat(mes, "\n");
			}
			imessage(pass, "PASSWORD_WORD", gPlayerLang[playerid]);
			strcat(mes, pass);
			imessage(title, "PASSWORD_INPUT_TITLE", gPlayerLang[playerid]);
			imessage(ok_mes, "OK_MESSAGE", gPlayerLang[playerid]);
			imessage(cancel_mes, "CANCEL_MESSAGE", gPlayerLang[playerid]);
			ShowPlayerDialog(playerid, 456, DIALOG_STYLE_PASSWORD, title, mes, ok_mes, cancel_mes);
		}
	}

	if(restart)
	    SetTimer("player_login_menu", 1000, false);
}

public imes_simple_single(playerid, color, str[])
{
	new imes[256];

	imessage(imes, str, gPlayerLang[playerid]);
	//переделать бы плагин и добавить сюда проверку на нахождение искомой строки
	//и если строка не найдена - отсылается её имя (т.е. str)
	//...
	SendClientMessage(playerid, color, imes);
}

public IsPlayerInVehicleReal(playerid)
{
	new anim;

	if( IsPlayerInAnyVehicle(playerid))
		return 1;

	anim = GetPlayerAnimationIndex(playerid);
	if( anim == 0 || anim == 1009 || anim == 1043 || anim == 1026 || anim == 1013 ||
	    anim == 1010 || anim == 1044 || anim == 1027 || anim == 1014 || anim == 1054)
		return 1;

	return 0;
}

public show_help_for_player(playerid)
{
	new mes[256];
	new help_mes[1536];

	strdel(help_mes, 0, sizeof(help_mes));
	imessage(mes, "HELP_ALL_COMMANDS_ABOUT", gPlayerLang[playerid]);
	strcat(help_mes, mes);
	strcat(help_mes, "\n");
	imessage(mes, "HELP_ALL_COMMANDS_Y", gPlayerLang[playerid]);
	strcat(help_mes, mes);
	strcat(help_mes, "\n");
	imessage(mes, "HELP_ALL_COMMANDS_2", gPlayerLang[playerid]);
	strcat(help_mes, mes);
	strcat(help_mes, "\n\n");

	imessage(mes, "HELP_INVENTORY_BUTTONS_ABOUT", gPlayerLang[playerid]);
	strcat(help_mes, mes);
	strcat(help_mes, "\n");
	imessage(mes, "HELP_INVENTORY_BUTTONS_X", gPlayerLang[playerid]);
	strcat(help_mes, mes);
	strcat(help_mes, "\n");
	imessage(mes, "HELP_INVENTORY_BUTTONS_Q", gPlayerLang[playerid]);
	strcat(help_mes, mes);
	strcat(help_mes, "\n");
	imessage(mes, "HELP_INVENTORY_BUTTONS_V", gPlayerLang[playerid]);
	strcat(help_mes, mes);
	strcat(help_mes, "\n");
	imessage(mes, "HELP_INVENTORY_BUTTONS_M", gPlayerLang[playerid]);
	strcat(help_mes, mes);
	strcat(help_mes, "\n\n");
/*
	imessage(mes, "HELP_TEST_ABOUT", gPlayerLang[playerid]);
	strcat(help_mes, mes);
	strcat(help_mes, "\n");
	imessage(mes, "HELP_TEST_CMDS_TP", gPlayerLang[playerid]);
	strcat(help_mes, mes);
	strcat(help_mes, "\n");
	imessage(mes, "HELP_TEST_CMDS_LIVE", gPlayerLang[playerid]);
	strcat(help_mes, mes);
	strcat(help_mes, "\n");
	imessage(mes, "HELP_TEST_CMDS_SKIN", gPlayerLang[playerid]);
	strcat(help_mes, mes);
	strcat(help_mes, "\n");
*/
	imessage(mes, "HELP_FAQ_INFORMATION", gPlayerLang[playerid]);
	strcat(help_mes, mes);
	strcat(help_mes, "\n");
	imessage(mes, "HELP_DROP_SOMETHING", gPlayerLang[playerid]);
	strcat(help_mes, mes);
	strcat(help_mes, "\n");
	imessage(mes, "HELP_CHARGE_A_WEAPON", gPlayerLang[playerid]);
	strcat(help_mes, mes);
	strcat(help_mes, "\n");
	imessage(mes, "HELP_USE_SOMETHING", gPlayerLang[playerid]);
	strcat(help_mes, mes);
	strcat(help_mes, "\n");
	imessage(mes, "HELP_GET_WATER", gPlayerLang[playerid]);
	strcat(help_mes, mes);
	strcat(help_mes, "\n");
	imessage(mes, "HELP_MAKE_BAG", gPlayerLang[playerid]);
	strcat(help_mes, mes);
	strcat(help_mes, "\n\n");

	imessage(mes, "HELP_USEFULL_COMMANDS",gPlayerLang[playerid]);
	strcat(help_mes, mes);
	strcat(help_mes, "\n");
	imessage(mes, "HELP_LANG",gPlayerLang[playerid]);
	strcat(help_mes, mes);
	strcat(help_mes, "\n");
	imessage(mes, "HELP_LAND", gPlayerLang[playerid]);
	strcat(help_mes, mes);
	strcat(help_mes, "\n");
	imessage(mes, "HELP_HELP", gPlayerLang[playerid]);
	strcat(help_mes, mes);
	strcat(help_mes, "\n");
	imessage(mes, "HELP_PM_COMMAND", gPlayerLang[playerid]);
	strcat(help_mes, mes);
	strcat(help_mes, "\n");
	imessage(mes, "HELP_ADM_COMMAND", gPlayerLang[playerid]);
	strcat(help_mes, mes);
	strcat(help_mes, "\n");

	ShowPlayerDialog(playerid,4557,DIALOG_STYLE_MSGBOX,"/help",help_mes,"OK","");
}

//обновляем позицию перемещённого транспорта
public update_unoccupied_vehicles()
{
	gUnoccupiedUpdateTimer = -1;

	for(new vehicleid = 1; vehicleid < MAX_PLAYERS; ++vehicleid)
	{
	    if(gUnoccupiedVehData[vehicleid] != INVALID_PLAYER_ID)
		{
			drop_vehicle_from_dot(gUnoccupiedVehData[vehicleid], vehicleid);
		    save_vehicle_position(vehicleid);
			gUnoccupiedVehData[vehicleid] = INVALID_PLAYER_ID;
		}
	}
}

public update_weapon_ammo()
{
	gUpdateWeaponTimer = -1;

	for(new playerid = 0; playerid < MAX_PLAYERS; ++playerid)
	{
	    if(gWeaponUpdate[playerid] > 0)
	    {
		    //собственно, освобождаем пустые обоймы
		    save_character_ammo(playerid, -1, -1);
		}
	}
}

//плюсуем к правилу дополнительные параметры
public set_player_extra(playerid, extra[128])
{
	new thing[64];
	
	if(IsPlayerInAnyVehicle(playerid))
	{
        if(strlen(extra) != 0)
            strcat(extra, ",");
		strdel(thing, 0, sizeof(thing));
        format(thing, sizeof(thing), "%d", gUnusualObject[VEHICLE_OBJECT]);
		strcat(extra, thing);
	}
	if(is_player_on_gas_station(playerid))
	{
        if(strlen(extra) != 0)
            strcat(extra, ",");
		strdel(thing, 0, sizeof(thing));
        format(thing, sizeof(thing), "%d", gUnusualObject[GAS_OBJECT]);
		strcat(extra, thing);
	}
	if(IsPlayerInWater(playerid))
	{
        if(strlen(extra) != 0)
            strcat(extra, ",");
		strdel(thing, 0, sizeof(thing));
        format(thing, sizeof(thing), "%d", gUnusualObject[WATER_OBJECT]);
		strcat(extra, thing);
	}
	if(is_player_near_fire(playerid))
	{
        if(strlen(extra) != 0)
            strcat(extra, ",");
		strdel(thing, 0, sizeof(thing));
        format(thing, sizeof(thing), "%d", gUnusualObject[FIRE_OBJECT]);
		strcat(extra, thing);
	}
}

//обновление меток авто на карте
public update_car_labels()
{
    update_key_cars("SOME_VEHICLE");
    update_key_cars("SOME_BUS_VEH");
}

//разблокировать чат для игрока и сообщить об этом
public unmute_a_chat_for_player(PlayerID)
{
	new imes[128], mes[128], name[64];
	new i, playerid;
	
	unmute_player(PlayerID);

	//если игрок не в игре - выходим
	for(i = 0; i < MAX_PLAYERS; ++i)
	{
	    if(gPlayersID[i] == PlayerID)
	    {
	        playerid = i;
	        break;
	    }
	}
	
	if(i == MAX_PLAYERS)
	    return;

	GetPlayerName(playerid, name, sizeof(name));
	
	for(i = 0; i < MAX_PLAYERS; ++i)
	{
		if(!IsPlayerNPC(i) && IsPlayerConnected(i))
		{
			//У игрока %s включен чат
		    imessage(imes, "UNMUTE_A_CHAT", gPlayerLang[i]);
			format(mes, sizeof(mes), imes, name);
		    SendClientMessage(i, 0x00FF00AA, mes);
		}
	}
	
	update_statistic_data(playerid, false);
}

//спрятать логотип DayZ от игрока
public hide_dayz_logo_from_player(playerid)
{
	new min_value;
	
	min_value = ((PlayerLogoIndex[playerid]+100)>USED_DRAWS)?(USED_DRAWS):(PlayerLogoIndex[playerid]+100);
	//прячем логотип DayZ
	for(new i = PlayerLogoIndex[playerid]; i < min_value; ++i)
	{
	    if(TextDrawInfo[i][used] == 1){TextDrawHideForPlayer(playerid,TextDrawInfo[i][idt]);}
	}
	PlayerLogoIndex[playerid] = PlayerLogoIndex[playerid]+100;
	if(PlayerLogoIndex[playerid] < USED_DRAWS)
	    SetTimerEx("hide_dayz_logo_from_player", 500, false, "i", playerid);
}

//использовать объект в ячейке
public apply_some_cell(playerid, vehid, cell, area)
{
	new name[128];
	new value, out_cell, i;

	//получим имя вещи и присвоенное ей значение
	value = 0;
	switch(area)
	{
		case INVENTORY_AREA:
		{
			if(get_object_data(playerid, cell, INVENTORY_AREA, name, value) < 0)
			  return;
  		}
  		case VEHICLE_AREA:
  		{
			if(get_object_data(playerid, cell, VEHICLE_AREA, name, value) < 0)
			  return;
		}
		case GROUND_AREA:
		{
			if(get_object_data(playerid, cell, GROUND_AREA, name, value) < 0)
			  return;
		}
		case BAG_AREA:
		{
			if(get_object_data(playerid, cell, BAG_AREA, name, value) < 0)
			  return;
		}
		default: return;
	}
	
	if(strcmp(name, "KEY_OBJECT") == 0 ||
	   strcmp(name, "PUBLIC_KEY_OBJECT") == 0)
	{
		switch(area)
		{
		    case INVENTORY_AREA:
			    {}
		    case VEHICLE_AREA:
			    {}
		    case GROUND_AREA:
			    {
			        if(gAdminLevel[playerid] >= 9)
			        {
			            out_cell = -1;
						for(i = 0; i < MAX_INVENTORY_ON_GROUND; ++i)
						{
						    if( (gRotateObject[playerid][i] == 1) && (i != cell) )
						    {
						        out_cell = i;
						        break;
						    }
						}
						if(out_cell < 0)
						    return;
						
				        if(set_a_key(playerid, cell, out_cell) > 0)
							imes_simple_single(playerid, 0x008800FF, "THE_KEY_IS_SET");
						else
							imes_simple_single(playerid, 0x880000FF, "THE_KEY_IS_UNSET");
					}
				}
		    case BAG_AREA:
			    {}
		}
	    return;
	}
}

public unapply_one_cell(playerid, cell, area)
{
	new name[128];
	new value;
	new i, have_a_compass;

	//получим имя вещи и присвоенное ей значение
	value = 0;
	get_object_data(playerid, cell, area, name, value);

	if(strlen(name) <= 0)
	    return;

	have_a_compass = 0;

	if(strcmp(name, "GPS_NAVIGATOR") == 0)
	{
	    for(i = 0; i < MAX_INVENTORY_ON_PLAYER; ++i)
	    {
	        if(area == INVENTORY_AREA && i == cell)
	        {
	            continue;
			}

			get_object_data(playerid, i, INVENTORY_AREA, name, value);

			if(strlen(name) <= 0)
			    continue;

		    //если есть ещё один GPS - выходим
			if(strcmp(name, "GPS_NAVIGATOR") == 0)
			{
			    return;
			}
			if(strcmp(name, "COMPASS_BOX") == 0)
			{
			    have_a_compass = 1;
			}
	    }

		if(gBag[playerid][0] > 0)
		for(i = 0; i < gBag[playerid][0]; ++i)
	    {
	        if(area == BAG_AREA && i == cell)
	        {
	            continue;
			}

			get_object_data(playerid, i, BAG_AREA, name, value);

			if(strlen(name) <= 0)
			    continue;

		    //если есть ещё один GPS - выходим
			if(strcmp(name, "GPS_NAVIGATOR") == 0)
			{
			    return;
			}
			if(strcmp(name, "COMPASS_BOX") == 0)
			{
			    have_a_compass = 1;
			}
	    }

		if(have_a_compass == 0)
		{
			//делаем прозрачными маркеры игроков
			for(i = 0; i < MAX_PLAYERS; ++i)
			{
			    if(i != playerid)
			    {
					SetPlayerMarkerForPlayer(i, playerid, (gPlayerColors[gPlayerColorID[playerid]]&0xFFFFFF00));
					SetPlayerMarkerForPlayer(playerid, i, (gPlayerColors[gPlayerColorID[i]]&0xFFFFFF00));
				}
			}
		    show_smokescreen(playerid);
		}
		show_smoke_map(playerid);
	    return;
	}

	if(strcmp(name, "COMPASS_BOX") == 0)
	{
	    for(i = 0; i < MAX_INVENTORY_ON_PLAYER; ++i)
	    {
	        if(area == INVENTORY_AREA && i == cell)
	            continue;

			get_object_data(playerid, i, INVENTORY_AREA, name, value);

			if(strlen(name) <= 0)
			    continue;

		    //если есть ещё один GPS - выходим
			if(strcmp(name, "GPS_NAVIGATOR") == 0)
			    return;
			if(strcmp(name, "COMPASS_BOX") == 0)
			    return;
	    }

	    if(gBag[playerid][0] > 0)
	    {
		    for(i = 0; i < gBag[playerid][0]; ++i)
		    {
		        if(area == BAG_AREA && i == cell)
		            continue;

				get_object_data(playerid, i, BAG_AREA, name, value);

				if(strlen(name) <= 0)
				    continue;

			    //если есть ещё один GPS - выходим
				if(strcmp(name, "GPS_NAVIGATOR") == 0)
				    return;
				if(strcmp(name, "COMPASS_BOX") == 0)
				    return;
		    }
		}

		//делаем прозрачными маркеры игроков
		for(i = 0; i < MAX_PLAYERS; ++i)
		{
		    if(i != playerid)
		    {
				SetPlayerMarkerForPlayer(i, playerid, (gPlayerColors[gPlayerColorID[playerid]]&0xFFFFFF00));
				SetPlayerMarkerForPlayer(playerid, i, (gPlayerColors[gPlayerColorID[i]]&0xFFFFFF00));
			}
		}

	    show_smokescreen(playerid);
	    return;
	}

	if(strcmp(name, "HUGE_BAG_PACK") == 0 ||
	   strcmp(name, "BIG_BAG_PACK") == 0 ||
	   strcmp(name, "MID_BAG_PACK") == 0 ||
	   strcmp(name, "TINY_BAG_PACK") == 0 )
	{
		if(area == INVENTORY_AREA)
		{
		    for(i = 0; i < gBag[playerid][0]; ++i)
		    {
		        unapply_one_cell(playerid, i, BAG_AREA);
		        remove_bag_object(playerid, i);
		    }
		}
	    destroy_bag_menu(playerid);
	    gBag[playerid][1] = 0;
	    gBag[playerid][0] = 0;
		RemovePlayerAttachedObject(playerid,1);
	    return;
	}
	
	if(strcmp(name, "KEY_OBJECT") == 0)
	{
		switch(area)
		{
		    case INVENTORY_AREA:
			    {
			        set_key_labels(playerid, cell, INVENTORY_AREA, false);
				}
		    case VEHICLE_AREA:
			    {}
		    case GROUND_AREA:
			    {}
		    case BAG_AREA:
			    {
			        set_key_labels(playerid, cell, BAG_AREA, false);
				}
		}
	    return;
	}
	
	if(strcmp(name, "ANTI_RADAR") == 0)
	{
		switch(area)
		{
		    case INVENTORY_AREA:
			    {
					gAntiRadar[playerid] = -gAntiRadar[playerid];
				}
		    case VEHICLE_AREA:
			    {
					return;
				}
		    case GROUND_AREA:
			    {
					return;
				}
		    case BAG_AREA:
			    {
					gAntiRadar[playerid] = -gAntiRadar[playerid];
				}
		}
	}		
}

public auto_apply_one_cell(playerid, vehid, cell, area)
{
	new name[128];
	new value;

	//получим имя вещи и присвоенное ей значение
	value = 0;
	switch(area)
	{
		case INVENTORY_AREA:
		{
			if(get_object_data(playerid, cell, INVENTORY_AREA, name, value) < 0)
			  return;
  		}
  		case VEHICLE_AREA:
  		{
			if(get_object_data(playerid, cell, VEHICLE_AREA, name, value) < 0)
			  return;
		}
		case GROUND_AREA:
		{
			if(get_object_data(playerid, cell, GROUND_AREA, name, value) < 0)
			  return;
		}
		case BAG_AREA:
		{
			if(get_object_data(playerid, cell, BAG_AREA, name, value) < 0)
			  return;
		}
		default: return;
	}

	if(strcmp(name, "ANTI_RADAR") == 0)
	{
		if(gAntiRadar[playerid] < -1)
		{
			gAntiRadar[playerid] = -gAntiRadar[playerid];
			if(gTdAntiCountDown[playerid] == PlayerText:INVALID_TEXT_DRAW)
			{
				//время до отключения антирадара
				gTdAntiCountDown[playerid] = CreatePlayerTextDraw(playerid, SERVER_TIME_POSITION_X, SERVER_TIME_POSITION_Y+15, "00:00");
				PlayerTextDrawColor(playerid, gTdAntiCountDown[playerid], 0x00FF00AA);
				PlayerTextDrawBoxColor(playerid, gTdAntiCountDown[playerid], 0x00FF00AA);
				PlayerTextDrawBackgroundColor(playerid, gTdAntiCountDown[playerid], 0x777777AA); //0xFFFFFF88
				PlayerTextDrawFont(playerid, gTdAntiCountDown[playerid], 1);
				PlayerTextDrawTextSize(playerid, gTdAntiCountDown[playerid], 640, 20);
				PlayerTextDrawLetterSize(playerid, gTdAntiCountDown[playerid], 0.4, 1);
				PlayerTextDrawSetShadow(playerid, gTdAntiCountDown[playerid], 1);
			}			
		}
	    return;
	}	

	apply_one_cell(playerid, vehid, cell, area);
}

//использовать объект в ячейке
public apply_one_cell(playerid, vehid, cell, area)
{
	new name[128];
	new value, def_value;
	new vehicleid, out_cell;
	new extra[128];
	
	strdel(extra, 0, sizeof(extra));
	set_player_extra(playerid, extra);

	//получим имя вещи и присвоенное ей значение
	value = 0;
	switch(area)
	{
		case INVENTORY_AREA:
		{
			if(get_object_data(playerid, cell, INVENTORY_AREA, name, value) < 0)
			  return;
  		}
  		case VEHICLE_AREA:
  		{
			if(get_object_data(playerid, cell, VEHICLE_AREA, name, value) < 0)
			  return;
		}
		case GROUND_AREA:
		{
			if(get_object_data(playerid, cell, GROUND_AREA, name, value) < 0)
			  return;
		}
		case BAG_AREA:
		{
			if(get_object_data(playerid, cell, BAG_AREA, name, value) < 0)
			  return;
		}
		default: return;
	}

//	imes_simple_single(playerid, 0xFFFF00, name); //отладка!!!

	if(area == INVENTORY_AREA)
	{
		if(strcmp(name, "HUGE_BAG_PACK") == 0 ||
		   strcmp(name, "BIG_BAG_PACK") == 0 ||
 		   strcmp(name, "MID_BAG_PACK") == 0 ||
		   strcmp(name, "TINY_BAG_PACK") == 0 )
		{
		    load_a_bag(playerid, cell);
		    update_bag_menu(playerid);
		    if(gInventoryMenuShow[playerid] > 0)
	    		show_bag_menu(playerid);
			if(strcmp(name, "MID_BAG_PACK") == 0 ||
			   strcmp(name, "TINY_BAG_PACK") == 0 )
			{
				SetPlayerAttachedObject(playerid,1,3026,1,-0.176000, -0.066000, 0.0000,0.0000, 0.0000, 0.0000, 1.07600, 1.079999, 1.029000);
			}
			else if(strcmp(name, "HUGE_BAG_PACK") == 0 ||
	 			    strcmp(name, "BIG_BAG_PACK") == 0 )
			{
				SetPlayerAttachedObject(playerid, 1, 1550, 1, 0.08, -0.195, 0.0, 1.00, 90.0, 180.0);
			}
		    return;
		}

		if(strcmp(name, "LOADED_AK47") == 0)
		{
			ResetPlayerWeapons(playerid);
			give_character_weapon(playerid, cell); //инициализация gPlayerWeapon[playerid][0] и gPlayerWeapon[playerid][1]
			if(gPlayerWeapon[playerid][0] != 0)
			{
				gPlayerWeapon[playerid][2] = 30;
				GivePlayerWeapon(playerid, 30, gPlayerWeapon[playerid][1]); //даём автомат Калашникова
			}
		    return;
		}

		if(strcmp(name, "LOADED_M4") == 0)
		{
			ResetPlayerWeapons(playerid);
			give_character_weapon(playerid, cell);
			if(gPlayerWeapon[playerid][0] != 0)
			{
				gPlayerWeapon[playerid][2] = 31;
				GivePlayerWeapon(playerid, 31, gPlayerWeapon[playerid][1]); //даём M4
			}
		    return;
		}

		if(strcmp(name, "LOADED_PISTOL") == 0)
		{
			ResetPlayerWeapons(playerid);
			give_character_weapon(playerid, cell);
			if(gPlayerWeapon[playerid][0] != 0)
			{
				gPlayerWeapon[playerid][2] = 24;
				GivePlayerWeapon(playerid, 24, gPlayerWeapon[playerid][1]); //даём Пустынный Орёл
			}
		    return;
		}

		if(strcmp(name, "LOADED_RIFLE") == 0)
		{
			ResetPlayerWeapons(playerid);
			give_character_weapon(playerid, cell);
			if(gPlayerWeapon[playerid][0] != 0)
			{
				gPlayerWeapon[playerid][2] = 33;
				GivePlayerWeapon(playerid, 33, gPlayerWeapon[playerid][1]); //даём винтовку (снайперка 34)
			}
		    return;
		}

		if(strcmp(name, "LOADED_SNIPER_RIFLE") == 0)
		{
			ResetPlayerWeapons(playerid);
			give_character_weapon(playerid, cell);
			if(gPlayerWeapon[playerid][0] != 0)
			{
				gPlayerWeapon[playerid][2] = 34;
				GivePlayerWeapon(playerid, 34, gPlayerWeapon[playerid][1]); //даём снайперскую винтовку
			}
		    return;
		}

		if(strcmp(name, "LOADED_SHOTGUN") == 0)
		{
			ResetPlayerWeapons(playerid);
			give_character_weapon(playerid, cell);
			if(gPlayerWeapon[playerid][0] != 0)
			{
				gPlayerWeapon[playerid][2] = 25;
				GivePlayerWeapon(playerid, 25, gPlayerWeapon[playerid][1]); //даём дробовик
			}
		    return;
		}

		if(strcmp(name, "KNIFE_WEAPON") == 0)
		{
			ResetPlayerWeapons(playerid);
			give_character_weapon(playerid, cell);
			if(gPlayerWeapon[playerid][0] != 0)
			{
				gPlayerWeapon[playerid][2] = 4;
				gPlayerWeapon[playerid][3] = 0;
				GivePlayerWeapon(playerid, 4, gPlayerWeapon[playerid][1]); //даём нож
			}
		    return;
		}

		if(strcmp(name, "KATANA_WEAPON") == 0)
		{
			ResetPlayerWeapons(playerid);
			give_character_weapon(playerid, cell);
			if(gPlayerWeapon[playerid][0] != 0)
			{
				gPlayerWeapon[playerid][2] = 8;
				gPlayerWeapon[playerid][3] = 0;
				GivePlayerWeapon(playerid, 8, gPlayerWeapon[playerid][1]); //даём катану
			}
		    return;
		}

		if(strcmp(name, "NUKE_KATANA_WEAPON") == 0)
		{
			ResetPlayerWeapons(playerid);
			give_character_weapon(playerid, cell);
			if(gPlayerWeapon[playerid][0] != 0)
			{
				gPlayerWeapon[playerid][2] = 8;
				gPlayerWeapon[playerid][3] = 1;
				GivePlayerWeapon(playerid, 8, gPlayerWeapon[playerid][1]); //даём катану
			}
		    return;
		}

		if(strcmp(name, "BASEBALL_BAT") == 0)
		{
			ResetPlayerWeapons(playerid);
			give_character_weapon(playerid, cell);
			if(gPlayerWeapon[playerid][0] != 0)
			{
				gPlayerWeapon[playerid][2] = 5;
				gPlayerWeapon[playerid][3] = 0;
				GivePlayerWeapon(playerid, 5, gPlayerWeapon[playerid][1]); //даём биту
			}
		    return;
		}

		if(strcmp(name, "FIRE_EXTINGUISHER") == 0 ||
		   strcmp(name, "FIRE_EXTINGUISHER1") == 0 )
		{
			if(value <= 0)
			{
				gPlayerWeapon[playerid][1] = value;
				save_character_ammo(playerid, -1, -1);
//				disassemble_cell_object(playerid, cell); //освобождаем флаконы с пеной
			    return;
			}
			ResetPlayerWeapons(playerid);
			give_character_weapon(playerid, cell);
			if(gPlayerWeapon[playerid][0] != 0)
			{
				gPlayerWeapon[playerid][2] = 42;
				gPlayerWeapon[playerid][3] = 0;
				GivePlayerWeapon(playerid, 42, 1000); //даём огнетушитель
			}
			gPlayerWeapon[playerid][1]--;
			save_character_ammo(playerid, -1, -1);
			set_character_cell_value(playerid, cell, value-1); //придаём необходимый объём пены в огнетушителе
		    return;
		}

		if(strcmp(name, "MOLOTOV_COCTAIL") == 0)
		{
			ResetPlayerWeapons(playerid);
			give_character_weapon(playerid, cell);
			if(gPlayerWeapon[playerid][0] != 0)
			{
				gPlayerWeapon[playerid][2] = 18;
				GivePlayerWeapon(playerid, 18, gPlayerWeapon[playerid][1]); //даём коктэйль Молотова
				full_free_object_from_owner(gPlayerWeapon[playerid][0]);
				gPlayerWeapon[playerid][0] = 0;
				gPlayerWeapon[playerid][1] = 0;
				gPlayerWeapon[playerid][3] = 0;
			}
			
		    return;
		}
	}
	
	if(strcmp(name, "GPS_NAVIGATOR") == 0)
	{
		if(area == INVENTORY_AREA || area == BAG_AREA)
		{
		    hide_smokescreen(playerid);
			hide_smoke_map(playerid);
		    return;
		}
	}

	if(strcmp(name, "COMPASS_BOX") == 0)
	{
		if(area == INVENTORY_AREA || area == BAG_AREA)
		{
		    hide_smokescreen(playerid);
		    return;
		}
	}


	if(strcmp(name, "BOTTLE_OF_LEMONADE") == 0 ||
	   strcmp(name, "BOTTLE_OF_MILK") == 0 ||
	   strcmp(name, "BOTTLE_OF_JUICE") == 0)
	{
	    if(gThirst[playerid] >= MAX_THIRST_VALUE-5)
	    {
	        imes_simple_single(playerid, 0x008800FF, "YOU_ARE_NOT_THIRSTY");
	        return;
	    }
		switch(area)
		{
		    case INVENTORY_AREA:
				if(create_composite_object(playerid, extra, out_cell) < 0)
				{
					imes_simple_single(playerid, 0xFF5555FF, "MAX_VALUE_ACHIEVED");
					return;
				}
			case VEHICLE_AREA:
				if(create_composite_object_veh(playerid, vehid, extra, out_cell) < 0)
				{
					imes_simple_single(playerid, 0xFF5555FF, "MAX_VALUE_ACHIEVED");
					return;
				}
			case GROUND_AREA:
				return;
			case BAG_AREA:
				if(create_composite_object_bag(playerid, extra, out_cell) < 0)
				{
					imes_simple_single(playerid, 0xFF5555FF, "MAX_VALUE_ACHIEVED");
					return;
				}
		}

		gThirst[playerid] = gThirst[playerid] + value; //утоляем жажду
		if(gThirst[playerid] > MAX_THIRST_VALUE)
		    gThirst[playerid] = MAX_THIRST_VALUE;
		set_character_thirst(playerid, gThirst[playerid]);
		update_statistic_data(playerid, false);
	    return;
	}

	if(strcmp(name, "BOTTLE_OF_WATER") == 0)
	{
	    if(gThirst[playerid] >= MAX_THIRST_VALUE-5)
	    {
	        imes_simple_single(playerid, 0x008800FF, "YOU_ARE_NOT_THIRSTY");
	        return;
	    }

	    switch(area)
	    {
	        case INVENTORY_AREA:
				if(disassemble_cell_object(playerid, cell) < 0)	return;
	        case VEHICLE_AREA:
				if(disassemble_cell_object_veh(vehid, cell) < 0) return;
	        case GROUND_AREA:
				return;//disassemble_ground_object(playerid, cell);
			case BAG_AREA:
				if(disassemble_cell_object_bag(playerid, cell) < 0) return;
  		}

		gThirst[playerid] = gThirst[playerid] + value; //утоляем жажду
		if(gThirst[playerid] > MAX_THIRST_VALUE)
		    gThirst[playerid] = MAX_THIRST_VALUE;
		set_character_thirst(playerid, gThirst[playerid]);
		update_statistic_data(playerid, false);
	    return;
	}

	if(strcmp(name, "WATER_BIG_BARREL") == 0 && area != GROUND_AREA)
	{
	    if(gThirst[playerid] >= MAX_THIRST_VALUE-5)
	    {
	        imes_simple_single(playerid, 0x008800FF, "YOU_ARE_NOT_THIRSTY");
	        return;
	    }

		gThirst[playerid] = gThirst[playerid] + 1000; //утоляем жажду
		if(gThirst[playerid] > MAX_THIRST_VALUE)
		    gThirst[playerid] = MAX_THIRST_VALUE;
		set_character_thirst(playerid, gThirst[playerid]);

		if( value <= 1 )
		{
		    switch(area)
		    {
		        case INVENTORY_AREA:
					disassemble_cell_object(playerid, cell);
		        case VEHICLE_AREA:
					disassemble_cell_object_veh(vehid, cell);
		        case GROUND_AREA:
					return;//disassemble_ground_object(playerid, cell);
				case BAG_AREA:
					disassemble_cell_object_bag(playerid, cell);
	  		}
		}
		else
		{
			switch(area)
			{
			    case INVENTORY_AREA:
				{
					set_character_cell_value(playerid, cell, value-1); //придаём необходимый объём бензину в канистре
				}
				case VEHICLE_AREA:
				{
					set_vehicle_cell_value(vehid, cell, value-1); //придаём необходимый объём бензину в канистре
				}
				case GROUND_AREA:
				{}
			    case BAG_AREA:
				{
					set_bag_cell_value(playerid, cell, value-1); //придаём необходимый объём бензину в канистре
				}
			}
		}

	    return;
	}

	if(strcmp(name, "EMPTY_JERRYCAN") == 0 ||
   	   strcmp(name, "EMPTY_BIG_BARREL") == 0 ||
	   strcmp(name, "EMPTY_BOTTLE") == 0 )
	{
		switch(area)
		{
		    case INVENTORY_AREA:
				if(create_composite_object(playerid, extra, out_cell) < 0) //наполняем канистру из бака доверху
				{
					imes_simple_single(playerid, 0xFF5555FF, "MAX_VALUE_ACHIEVED");
					return;
				}
		    case VEHICLE_AREA:
				if(create_composite_object_veh(playerid, vehid, extra, out_cell) < 0) //наполняем канистру из бака доверху
				{
					imes_simple_single(playerid, 0xFF5555FF, "MAX_VALUE_ACHIEVED");
					return;
				}
		    case GROUND_AREA:
		    {}
		    case BAG_AREA:
				if(create_composite_object_bag(playerid, extra, out_cell) < 0) //наполняем канистру из бака доверху
				{
					imes_simple_single(playerid, 0xFF5555FF, "MAX_VALUE_ACHIEVED");
					return;
				}
		}
		
		if(out_cell >= 0) //если сборка состоялась
		{
			if(IsPlayerInAnyVehicle(playerid))
			{
			    vehicleid = GetPlayerVehicleID(playerid);
			    def_value = 10000;

				if(vehicleid > 0 && gVeh[vehicleid][3] > 0 && gVehicleDataShow[playerid] == vehicleid) //если персонаж тот, за кого себя выдаёт
				{
			        new out_data[64];

					strdel(out_data, 0, sizeof(out_data));
					if(strcmp(name, "EMPTY_JERRYCAN") == 0)
						get_thing_field("def_value", "FULL_JERRYCAN", out_data);
					else if(strcmp(name, "EMPTY_BIG_BARREL") == 0)
						  get_thing_field("def_value", "FULL_BIG_BARREL", out_data);
					else if(strcmp(name, "EMPTY_BOTTLE") == 0)
						  get_thing_field("def_value", "BOTTLE_OF_GAS", out_data);
						else
						{
						    switch(area)
						    {
							    case INVENTORY_AREA:
									disassemble_cell_object(playerid, out_cell);
							    case VEHICLE_AREA:
									disassemble_cell_object_veh(vehid, out_cell);
								case GROUND_AREA:
									return;
							    case BAG_AREA:
									disassemble_cell_object_bag(playerid, out_cell);
							}
						    return;
		    			}

					def_value = strval(out_data);

//					printf("def_value=%d, out_data=%s", def_value, out_data); //отладка!!!
				}

			    if(gVeh[vehicleid][3] >= def_value) //если в баке достаточно на полную канистру
			    {
				    gVeh[vehicleid][3] = gVeh[vehicleid][3] - def_value; //сливаем из него
				    save_vehicle_state(playerid, vehicleid); //обновляем состояние авто
				}
				else
				{
					if(gVeh[vehicleid][3] <= 0)
					{
					    switch(area)
					    {
						    case INVENTORY_AREA:
								disassemble_cell_object(playerid, out_cell);
						    case VEHICLE_AREA:
								disassemble_cell_object_veh(vehid, out_cell);
							case GROUND_AREA:
								return;
						    case BAG_AREA:
								disassemble_cell_object_bag(playerid, out_cell);
						}
						return;
					}

					switch(area)
					{
					    case INVENTORY_AREA:
						{
							set_character_cell_value(playerid, out_cell, gVeh[vehicleid][3]); //придаём необходимый объём бензину в канистре
						}
						case VEHICLE_AREA:
						{
							set_vehicle_cell_value(vehid, out_cell, gVeh[vehicleid][3]); //придаём необходимый объём бензину в канистре
						}
						case GROUND_AREA:
						{}
					    case BAG_AREA:
						{
							set_bag_cell_value(playerid, out_cell, gVeh[vehicleid][3]); //придаём необходимый объём бензину в канистре
						}
					}
					
				    gVeh[vehicleid][3] = 0; //сливаем из него
				    save_vehicle_state(playerid, vehicleid); //обновляем состояние авто
				}
				for(new i = 0; i < MAX_PLAYERS; ++i)
				{
				    if(IsPlayerInVehicle(i, vehicleid))
						update_vehicle_sensors(i);
				}

				if(gVeh[vehicleid][3] > 0)
				{
					//сообщаем игроку о том, что он сейчас сделал
					imes_simple_single(playerid, 0xFFFF44FF, "YOU_POURED_OUT_A_GAS");
				}
				else
				{
					//сообщаем игроку о том, что он сейчас сделал
					imes_simple_single(playerid, 0xFF5577FF, "YOU_POURED_OFF_A_GAS");
				}

			    return;
			}

		    if(is_player_on_gas_station(playerid))
		    {
				switch(area)
				{
				    case INVENTORY_AREA:
				    {}
					case GROUND_AREA:
					{
						update_objects_menu(playerid);
					}
				    case BAG_AREA:
					{}
				}
			    return;
			}
		}
	    return;
	}

	if(strcmp(name, "FULL_JERRYCAN") == 0 ||
	   strcmp(name, "FULL_BIG_BARREL") == 0 ||
	   strcmp(name, "BOTTLE_OF_GAS") == 0 )
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        vehicleid = GetPlayerVehicleID(playerid);

            if(gVeh[vehicleid][5] == 0)
            {
		        imes_simple_single(playerid, 0xFF5577FF, "CANT_DO_WITH_VEHICLE");
                return;
            }

            if(gVeh[vehicleid][3] >= gVeh[vehicleid][6])
            {
		        new out_data[64];
		        new old_value;

				get_thing_field("def_value", name, out_data);
				def_value = strval(out_data);

				if(def_value >= value)
				{
				    old_value = gVeh[vehicleid][3];
				    gVeh[vehicleid][3] = gVeh[vehicleid][3] - (def_value-value); //сливаем из него
				    save_vehicle_state(playerid, vehicleid); //обновляем состояние авто
				    switch(area)
				    {
				        case INVENTORY_AREA:
							set_character_cell_value(playerid, cell, ((old_value+value)>def_value)?def_value:old_value+value); //придаём необходимый объём бензину в канистре
				        case VEHICLE_AREA:
							set_vehicle_cell_value(vehid, cell, ((old_value+value)>def_value)?def_value:old_value+value); //придаём необходимый объём бензину в канистре
						case GROUND_AREA:
							set_ground_cell_value(playerid, cell, ((old_value+value)>def_value)?def_value:old_value+value); //придаём необходимый объём бензину в канистре
				        case BAG_AREA:
							set_bag_cell_value(playerid, cell, ((old_value+value)>def_value)?def_value:old_value+value); //придаём необходимый объём бензину в канистре
					}
					for(new i = 0; i < MAX_PLAYERS; ++i)
					{
					    if(IsPlayerInVehicle(i, vehicleid))
							update_vehicle_sensors(i);
					}
					imes_simple_single(playerid, 0xFFFF44FF, "YOU_POURED_OUT_A_GAS");
				}
				else
				{
			        imes_simple_single(playerid, 0xFF5577FF, "THE_GAS_TANK_IS_FULL");
					//сообщаем игроку о том, что он сейчас сделал
				}
                return;
            }

	        gVeh[vehicleid][3] = gVeh[vehicleid][3] + value; //заливаем бензин в бак
	        if(gVeh[vehicleid][3] > gVeh[vehicleid][6])
	        {
	            switch(area)
	            {
					case INVENTORY_AREA:
		    			set_character_cell_value(playerid, cell, gVeh[vehicleid][3] - gVeh[vehicleid][6]); //придаём необходимый объём бензину в канистре
					case VEHICLE_AREA:
						set_vehicle_cell_value(vehid, cell, gVeh[vehicleid][3] - gVeh[vehicleid][6]); //придаём необходимый объём бензину в канистре
					case GROUND_AREA:
					    return;
					case BAG_AREA:
		    			set_bag_cell_value(playerid, cell, gVeh[vehicleid][3] - gVeh[vehicleid][6]); //придаём необходимый объём бензину в канистре
				}
	            gVeh[vehicleid][3] = gVeh[vehicleid][6];
		        imes_simple_single(playerid, 0xFF8800FF, "THE_GAS_TANK_IS_FULL");
			}
			else
			{
			    switch(area)
			    {
				    case INVENTORY_AREA:
						disassemble_cell_object(playerid, cell);
				    case VEHICLE_AREA:
						disassemble_cell_object_veh(vehid, cell);
					case GROUND_AREA:
						return;
				    case BAG_AREA:
						disassemble_cell_object_bag(playerid, cell);
				}
			}
			for(new i = 0; i < MAX_PLAYERS; ++i)
			{
			    if(IsPlayerInVehicle(i, vehicleid))
					update_vehicle_sensors(i);
			}
	        save_vehicle_state(playerid, vehicleid);
	        return;
		}

	    if(is_player_on_gas_station(playerid))
	    {
	        new out_data[64];

			get_thing_field("def_value", name, out_data);
			def_value = strval(out_data);

			switch(area)
			{
			    case INVENTORY_AREA:
					set_character_cell_value(playerid, cell, def_value); //придаём необходимый объём бензину в канистре
				case GROUND_AREA:
					set_ground_cell_value(playerid, cell, def_value); //придаём необходимый объём бензину в канистре
			    case BAG_AREA:
					set_bag_cell_value(playerid, cell, def_value); //придаём необходимый объём бензину в канистре
			}
		    return;
		}
	    return;
	}

	if(strcmp(name, "CAR_WHEEL") == 0)
	{
        new Float:x, Float:y, Float:z;

	    if(IsPlayerInAnyVehicle(playerid))
	    {
			new panels, doors, lights, tires;

	        vehicleid = GetPlayerVehicleID(playerid);

			GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);

			if(tires == 0)
			{
		        imes_simple_single(playerid, 0x008800FF, "ALL_VEHICLE_TIRES_ARE_GOOD");
				return;
			}
			else
			{
				new tires_state;

				GetVehicleVelocity(vehicleid, x, y, z);
				tires_state = 0x01;
				while(!(tires_state & 0x100))
				{
					if(tires & tires_state)
					{
						tires = tires ^ tires_state;
						break;
					}
					tires_state = tires_state << 1;
				}

				UpdateVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
				save_vehicle_state(playerid, vehicleid);
				switch(area)
				{
				    case INVENTORY_AREA:
					    free_cell_from_owner(playerid, cell);
				    case VEHICLE_AREA:
					    free_cell_from_owner_veh(vehid, cell);
				    case GROUND_AREA:
						free_cell_from_owner_obj(playerid, cell);
				    case BAG_AREA:
					    free_cell_from_owner_bag(playerid, cell);
    			}
				SetVehicleVelocity(vehicleid, x, y, z);
				return;
            }
		}
	    return;
	}

	//временная функция для ремонта двигателя
	if(strcmp(name, "CAR_ENGINE") == 0)
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        new out_data[64];
	        new Float:x, Float:y, Float:z;

			get_thing_field("def_value", "CAR_ENGINE", out_data);
			def_value = strval(out_data);

	        vehicleid = GetPlayerVehicleID(playerid);

			if(gVeh[vehicleid][2] >= def_value)
			{
		        imes_simple_single(playerid, 0x008800FF, "VEHICLE_ENGINE_IS_GOOD");
				return;
			}
			else
			{
				GetVehicleVelocity(vehicleid, x, y, z);
				gVeh[vehicleid][2] = value;
				save_vehicle_state(playerid, vehicleid);
				for(new i = 0; i < MAX_PLAYERS; ++i)
				{
				    if(IsPlayerInVehicle(i, vehicleid))
						update_vehicle_sensors(i);
				}
				switch(area)
				{
				    case INVENTORY_AREA:
					    free_cell_from_owner(playerid, cell);
				    case VEHICLE_AREA:
					    free_cell_from_owner_veh(vehid, cell);
				    case GROUND_AREA:
						free_cell_from_owner_obj(playerid, cell);
				    case BAG_AREA:
					    free_cell_from_owner_bag(playerid, cell);
    			}
				SetVehicleVelocity(vehicleid, x, y, z);
				return;
            }
		}
	    return;
	}

	//временная функция для установки аккумулятора
	if(strcmp(name, "CAR_ACCUMULATOR") == 0)
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        new out_data[64];
	        new Float:x, Float:y, Float:z;

			get_thing_field("def_value", "CAR_ACCUMULATOR", out_data);
			def_value = strval(out_data);

	        vehicleid = GetPlayerVehicleID(playerid);

			if(gVeh[vehicleid][9] >= def_value)
			{
		        imes_simple_single(playerid, 0x008800FF, "VEHICLE_ACCUMULATOR_IS_GOOD");
				return;
			}
			else
			{
				GetVehicleVelocity(vehicleid, x, y, z);
				gVeh[vehicleid][9] = value;
				save_vehicle_state(playerid, vehicleid);
				for(new i = 0; i < MAX_PLAYERS; ++i)
				{
				    if(IsPlayerInVehicle(i, vehicleid))
						update_vehicle_sensors(i);
				}
				switch(area)
				{
				    case INVENTORY_AREA:
					    free_cell_from_owner(playerid, cell);
				    case VEHICLE_AREA:
					    free_cell_from_owner_veh(vehid, cell);
				    case GROUND_AREA:
						free_cell_from_owner_obj(playerid, cell);
				    case BAG_AREA:
					    free_cell_from_owner_bag(playerid, cell);
    			}
				SetVehicleVelocity(vehicleid, x, y, z);
				return;
            }
		}
	    return;
	}
	
	//временная функция для ремонта авто
	if(strcmp(name, "CAR_TOOLBOX") == 0)
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
			new panels, doors, lights, tires;
			new Float:veh_health;
	        new Float:x, Float:y, Float:z;

	        vehicleid = GetPlayerVehicleID(playerid);

			GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
			GetVehicleHealth(vehicleid, veh_health);

			if(panels == 0 && doors == 0 && veh_health >= 990.0)
			{
		        imes_simple_single(playerid, 0x008800FF, "VEHICLE_STATE_IS_GOOD");
				return;
			}
			else
			{
				GetVehicleVelocity(vehicleid, x, y, z);
				RepairVehicle(vehicleid);
				UpdateVehicleDamageStatus(vehicleid, 0, 0, 0, tires);
				save_vehicle_state(playerid, vehicleid);
				switch(area)
				{
				    case INVENTORY_AREA:
					    free_cell_from_owner(playerid, cell);
				    case VEHICLE_AREA:
					    free_cell_from_owner_veh(vehid, cell);
				    case GROUND_AREA:
						free_cell_from_owner_obj(playerid, cell);
				    case BAG_AREA:
					    free_cell_from_owner_bag(playerid, cell);
    			}
				SetVehicleVelocity(vehicleid, x, y, z);
				return;
            }
		}
	    return;
	}
	
	if(strcmp(name, "NITRO_OBJECT") == 0)
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        if(value <= 0)
	        {
		        imes_simple_single(playerid, 0xFF8888FF, "NO_NITRO_IN_OBJECT");
	            return;
			}
	            
	        vehicleid = GetPlayerVehicleID(playerid);

	        switch(GetVehicleModel(vehicleid))
	        {
	        	case 446,432,448,452,424,453,454,461,462,463,468,471,430,472,449,473,481,484,493,495,509,510,521,538,522,523,
					 532,537,570,581,586,590,569,595,604,611: return;
	        }

			switch(area)
			{
			    case INVENTORY_AREA:
				    free_cell_from_owner(playerid, cell);
			    case VEHICLE_AREA:
				    free_cell_from_owner_veh(vehid, cell);
			    case GROUND_AREA:
					free_cell_from_owner_obj(playerid, cell);
			    case BAG_AREA:
				    free_cell_from_owner_bag(playerid, cell);
			}
	        AddVehicleComponent(vehicleid, 1010);
		}
		return;
	}

	if(strcmp(name, "TRANSPORT_VEHICLE") == 0)
	{
			switch(area)
			{
			    case INVENTORY_AREA:
				    {}
			    case VEHICLE_AREA:
				    {}
			    case GROUND_AREA:
			    {
			        new val_id[64];
			        new num_id;

			        get_players_value("obj_id","objects",gGroundItem[playerid][cell][db_id],val_id);
			        num_id = strval(val_id);
					DetachTrailerFromVehicle(num_id);
				}
				case BAG_AREA:
				    {}
			}
			return;
	}

	if(strcmp(name, "THE_BANDAGE") == 0 ||
	   strcmp(name, "THE_MASK") == 0)
	{
	    if(gWound[playerid] == 0)
	    {
	        imes_simple_single(playerid, 0x008800FF, "YOU_HAVE_NO_WOUND");
	        return;
	    }
		gWound[playerid] = gWound[playerid] - value; //лечим рану
		if(gWound[playerid] < 0)
		    gWound[playerid] = 0;
		set_character_wound(playerid, gWound[playerid]);
		switch(area)
		{
		    case INVENTORY_AREA:
			    free_cell_from_owner(playerid, cell);
		    case VEHICLE_AREA:
			    free_cell_from_owner_veh(vehid, cell);
		    case GROUND_AREA:
				free_cell_from_owner_obj(playerid, cell);
		    case BAG_AREA:
			    free_cell_from_owner_bag(playerid, cell);
		}
		update_statistic_data(playerid, false);
	    return;
	}

	if(strcmp(name, "THE_BLOOD_PACK") == 0)
	{
	    if(gHealth[playerid] >= MAX_HEALTH_VALUE)
	    {
	        imes_simple_single(playerid, 0x008800FF, "YOU_ARE_HEALTHY");
	        return;
	    }
		gHealth[playerid] = (gHealth[playerid] + value); //восстанавливаем здоровье
		if(gHealth[playerid] > MAX_HEALTH_VALUE)
		    gHealth[playerid] = MAX_HEALTH_VALUE;
		set_character_health(playerid, gHealth[playerid]);
		switch(area)
		{
		    case INVENTORY_AREA:
			    free_cell_from_owner(playerid, cell);
		    case VEHICLE_AREA:
			    free_cell_from_owner_veh(vehid, cell);
		    case GROUND_AREA:
				free_cell_from_owner_obj(playerid, cell);
		    case BAG_AREA:
			    free_cell_from_owner_bag(playerid, cell);
		}
		update_statistic_data(playerid, false);
	    return;
	}

	if(strcmp(name, "PIECE_OF_PIZZA") == 0 ||
	   strcmp(name, "FULL_PIZZA") == 0 ||
	   strcmp(name, "BANANA_FOOD") == 0 ||
	   strcmp(name, "APPLE_FOOD") == 0 ||
	   strcmp(name, "APPLE_RED_FOOD") == 0 ||
	   strcmp(name, "BREAD_FOOD") == 0 ||
	   strcmp(name, "BIG_FOOD") == 0 ||
	   strcmp(name, "HUMBURGER_FOOD") == 0)
	{
	    if(gHunger[playerid] >= MAX_HUNGER_VALUE-10)
	    {
	        imes_simple_single(playerid, 0xFF5577FF, "YOU_ARE_NOT_HUNGRY");
	        return;
	    }
		gHunger[playerid] = gHunger[playerid] + value; //утоляем голод
		if(gHunger[playerid] > MAX_HUNGER_VALUE)
		    gHunger[playerid] = MAX_HUNGER_VALUE;
		set_character_hunger(playerid, gHunger[playerid]);

		if(value < 500)
			gHealth[playerid] = gHealth[playerid] + value*7; //лечим персонаж
		else
			gHealth[playerid] = gHealth[playerid] + value*4; //лечим персонаж

		if(gHealth[playerid] > MAX_HEALTH_VALUE)
		    gHealth[playerid] = MAX_HEALTH_VALUE;
		set_character_health(playerid, gHealth[playerid]);
		switch(area)
		{
		    case INVENTORY_AREA:
			    free_cell_from_owner(playerid, cell);
		    case VEHICLE_AREA:
			    free_cell_from_owner_veh(vehid, cell);
		    case GROUND_AREA:
				free_cell_from_owner_obj(playerid, cell);
		    case BAG_AREA:
			    free_cell_from_owner_bag(playerid, cell);
  		}
		update_statistic_data(playerid, false);
	    return;
	}
	
	if(strcmp(name, "NODJA_OBJECT") == 0)
	{
        new Float:x, Float:y, Float:z;
        
        GetPlayerPos(playerid, x, y, z);
		switch(area)
		{
		    case INVENTORY_AREA:
			    {
//					drop_character_inventory_cell(playerid, cell, -1, x, y, z);
				}
		    case VEHICLE_AREA:
			    {
//					drop_vehicle_inventory_cell(vehid, cell);
				}
		    case GROUND_AREA:
			    {}
		    case BAG_AREA:
			    {
//					drop_bag_inventory_cell(playerid, cell, -1, x, y, z);
				}
		}
//		update_objects_menu(playerid); //обновить меню самого игрока
//		update_neighbors_objects_menu(playerid); //обновить меню соседних игроков
	    return;
	}
	
	if(strcmp(name, "KEY_OBJECT") == 0)
	{
		switch(area)
		{
		    case INVENTORY_AREA:
			    {
			        set_key_labels(playerid, cell, INVENTORY_AREA, true);
				}
		    case VEHICLE_AREA:
			    {}
		    case GROUND_AREA:
			    {}
		    case BAG_AREA:
			    {
			        set_key_labels(playerid, cell, BAG_AREA, true);
				}
		}
	    return;
	}

	if(strcmp(name, "ANTI_RADAR") == 0)
	{
		new ticks;

		ticks = GetTickCount();

		switch(area)
		{
		    case INVENTORY_AREA:
			    {
					save_character_ammo(playerid, gInventoryItem[playerid][cell][db_id], 0);
					gInventoryItem[playerid][cell][obj_value] = 0;
				}
		    case VEHICLE_AREA:
			    {
					return;
				}
		    case GROUND_AREA:
			    {
					return;
				}
		    case BAG_AREA:
			    {
					save_character_ammo(playerid, gBagItem[playerid][cell][db_id], 0);
					gBagItem[playerid][cell][obj_value] = 0;
				}
		}

		if(value > 0)
		{
			if(gTdAntiCountDown[playerid] == PlayerText:INVALID_TEXT_DRAW)
			{
				//время до отключения антирадара
				gTdAntiCountDown[playerid] = CreatePlayerTextDraw(playerid, SERVER_TIME_POSITION_X, SERVER_TIME_POSITION_Y+15, "00:00");
				PlayerTextDrawColor(playerid, gTdAntiCountDown[playerid], 0x00FF00AA);
				PlayerTextDrawBoxColor(playerid, gTdAntiCountDown[playerid], 0x00FF00AA);
				PlayerTextDrawBackgroundColor(playerid, gTdAntiCountDown[playerid], 0x777777AA); //0xFFFFFF88
				PlayerTextDrawFont(playerid, gTdAntiCountDown[playerid], 1);
				PlayerTextDrawTextSize(playerid, gTdAntiCountDown[playerid], 640, 20);
				PlayerTextDrawLetterSize(playerid, gTdAntiCountDown[playerid], 0.4, 1);
				PlayerTextDrawSetShadow(playerid, gTdAntiCountDown[playerid], 1);
			}
		}
		else
		{
			gAntiRadar[playerid] = 0;
			return;
		}

		if(gAntiRadar[playerid] < ticks)
		{
			gAntiRadar[playerid] = ticks;
		}
		gAntiRadar[playerid] = gAntiRadar[playerid] + value * 60000;

	    return;
	}	
}

