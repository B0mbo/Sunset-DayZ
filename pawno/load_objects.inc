#if defined _LOAD_OBJECTS_INC_
	#endinput
#endif

#define _LOAD_OBJECTS_INC_

#pragma dynamic 16000

#define LOAD_DEBUG

#include<a_samp>
#include<things>
#include<a_mysql>
#include<mapandreas>
#include<streamer>

#include"defines.inc"
#include"sensors.inc"
#include"global.inc"
/*
stock _cache_get_field_content_int(row, const field_name[], connectionHandle = 1)
{
	printf("cache_get_field_content_int debug: row - %d, field_name - %s", row, field_name);

	return cache_get_field_content_int(row, field_name, connectionHandle);
}
#define cache_get_field_content_int(%0) _cache_get_field_content_int(%0)
*/
forward open_database();
forward close_database();
forward player_login(playerid, password[]); //вызывается при входе игрока на сервер
forward player_logout(playerid); //обновляет данные игрока
forward player_ip_check(playerid); //вход по ip
forward create_player(playerid, password[]); //создаёт нового игрока
forward get_player_db_language(playerid); //загрузить язык игрока из БД
forward set_player_db_lang(playerid, lang[]); //сохранить язык игрока в БД
forward set_player_db_land(playerid, land[]); //сохранить страну игрока в БД
forward set_player_db_country(playerid, country[]); //сохранить страну игрока в БД
forward set_player_db_city(playerid, city[]); //сохранить город игрока в БД
forward set_player_id(playerid); //задаёт gPlayersID игрока
forward update_player(playerid); //обновляет время и ip игрока
forward initialize_players(); //задаёт gPlayersID для всех онлайн-игроков
forward free_players(); //обнуляет все gPlayersID
forward get_admin_list(list[], list_size); //получить список админов

forward load_objects();
forward destroy_objects();
forward load_vehicles();
forward load_gates(door_type[]);
forward set_new_objects_on_places();
forward set_new_objects_on_places_th();
forward set_new_objects_on_places_th_t(Float:rotx,Float:roty,Float:rotz,rotatable,inworld_id,Float:height,id,type_id,def_value,is_vehicle,prev_id);
forward unset_objects_on_places(playerid, Float:range); //разместить по местам респавна вещи в радиусе 5.0 метров от игрока
forward unset_objects_on_places_xyz(Float:x, Float:y, Float:z, Float:range); //разместить по местам респавна вещи в радиусе 5.0 метров от заданной координаты
forward unset_objects_on_places_xyz_t(Float:x, Float:y, Float:z, Float:range); //разместить по местам респавна вещи в радиусе 5.0 метров от заданной координаты
forward destroy_vehicles();
forward destroy_gates(door_type[]);
forward find_and_cache_objects(playerid, Float:range); //кэшировать объекты, лежащие рядом с игроком
forward find_and_cache_objects_t(playerid, Float:range, Float:player_x, Float:player_y, Float:player_z); ////кэшировать объекты, лежащие рядом с игроком в потоке
forward is_any_object_in_range(playerid, Float:x, Float:y, Float:z, Float:range, Float:cache_distance, object_id); //определить, лежит ли какой-нибудь объект в указанном радиусе от заданной точки
forward set_character_inventory_cell(playerid, cell, object_id, bool:init); //положить объект в ячейку инвентаря
forward set_vehicle_inventory_cell(vehicleid, cell, object_id, bool:init); //положить объект в ячейку инвентаря транспорта
forward set_bag_inventory_cell(playerid, cell, object_id, bool:init); //положить объект в ячейку инвентаря рюкзака
forward drop_character_inventory_cell(playerid, cell, obj_cell, Float:x,Float:y,Float:z); //выложить объект из инвентаря
forward drop_vehicle_inventory_cell(vehicleid, cell); //выложить объект из инвентаря авто
forward drop_bag_inventory_cell(playerid, cell, obj_cell, Float:in_x,Float:in_y,Float:in_z); //выложить из рюкзака
forward drop_object_on_ground(playerid, obj_id); //положить объект на землю рядом с игроком
forward drop_bag_object_on_ground(playerid, obj_id); //положить объект из рюкзака на землю рядом с игроком
forward drop_last_object_on_ground(playerid); //положить последний созданный объект на землю рядом с игроком
forward take_vehicle_inventory_cell(playerid, vehicleid, cell, veh_cell); //переложить объект из транспорта в инвентарь персонажа
forward take_bag_inventory_cell(playerid, cell, bag_cell); //переложить объект из рюкзака в инвентарь персонажа
forward give_vehicle_inventory_cell(playerid, vehicleid, cell, veh_cell); //переложить объект из инвентаря персонажа в транспорт
forward give_veh_invent_cell_from_bag(playerid, vehicleid, cell, veh_cell); //переложить объект из инвентаря рюкзака в ячейку инвентаря транспорта
forward give_bag_inventory_cell(playerid, cell, bag_cell); //переложить объект из инвентаря персонажа в рюкзак
forward give_bag_invent_cell_from_veh(playerid, vehicleid, cell, bag_cell); //переложить объект из авто в рюкзак
forward give_bag_invent_cell_from_grnd(playerid, cell, bag_cell); //положить объект в рюкзак
forward move_character_inventory_cell(playerid, cell1, cell2); //переложить объект в инвентаре на пустое место
forward move_vehicle_inventory_cell(vehicleid, cell1, cell2); //переложить объект в инвентаре на пустое место
forward move_bag_inventory_cell(playerid, cell1, cell2); //переложить объект в рюкзаке на пустое место
forward get_object_data(playerid, cell, area, name[128], &value);
forward get_object_data_all(playerid, cell, area, name[128], &value, owner[128], owner_country[128], last_owner[128], last_owner_country[128], last_time[128], type[128]);
forward give_character_weapon(playerid, cell);
forward find_character_weapon(playerid, &cell);
forward save_character_ammo(playerid, in_object, in_value);

forward save_vehicle_state(playerid, vehicleid);
forward save_vehicle_position(vehicleid);
forward create_new_vehicle(object_id, Float:x, Float:y, Float:z, Float:rotz, inworld_id, def_value);
forward create_old_vehicle(object_id, Float:x, Float:y, Float:z, Float:rotz, inworld_id);
forward set_vehicle_number(playerid, number[32]); //задать новый номер для авто, в котором сидит игрок
forward create_new_bag(obj_id); //создать новый рюкзак
forward drop_vehicle_from_dot(playerid, vehicleid); //удалить авто из точки появления, если оно не находится в этой точке

forward load_a_bag(playerid, cell); //установить параметры рюкзака для игрока

forward get_unused_object(thing_id); //получить из базы свободный (unused=1) объект заданного типа, либо создать новый такой
forward set_object_owner(th_owner_id, object_id); //присвоить объект новому объекту-владельцу

forward check_object_owner(playerid, vehicleid, owner_cell, area); //проверяем составляющие объекты на максимальное значение

forward create_resident_object(object_id, old_thing_id, new_thing_id); //создать резидентный объект (для объектов, помеченных как '!' в файле описания вещей)
forward create_composite_object(playerid, extra[], &cell); //создать новую составную вещь
forward create_composite_object_veh(playerid, vehicleid, extra[], &cell); //создать новую составную вещь в инвентаре транспорта
forward create_composite_object_obj(playerid, extra[]); //создать новую составную вещь на земле
forward create_composite_object_bag(playerid, extra[], &cell); //создать новую составную вещь в рюкзаке

forward disassemble_resident_object(object_id, prev_id); //разобрать резидентный объект (по-сути лишь вернуть прежний thing_id)
forward disassemble_cell_object(playerid, cell); //разобрать составной объект из ячейки
forward disassemble_cell_object_veh(vehicleid, cell); //разобрать составной объект из ячейки инвентаря авто
forward disassemble_cell_object_bag(playerid, cell); //разобрать составной объект из ячейки инвентаря рюкзака
forward disassemble_inventory_object(object_id); //разобрать объект с автопоиском ячейки в инвентаре
forward disassemble_ground_object(playerid, cell); //разобрать объект, лежащий на земле
forward pick_object_from_owner(obj_id); //выковырять объект из композитного объекта

forward clear_all_owners(object_id); //освободить объект от всех владельцев (используется при профилактике БД)
forward free_cell_from_owner(playerid, cell); //освободить объект, находящийся в ячейке инвентаря, и разместить на свободном месте
forward free_cell_from_owner_veh(vehicleid, cell); //освободить объект, находящийся в ячейке инвентаря, и разместить на свободном месте
forward free_cell_from_owner_obj(playerid, cell); //освободить объект, лежащий на земле, и разместить на свободном месте
forward free_cell_from_owner_bag(playerid, cell); //освободить объект, лежащий в рюкзаке, и разместить на свободном месте
forward full_free_object_from_owner(object_id); //полное освобождение объекта с освобождением всех вложенных объектов и разместить их на свободном месте
forward free_object_from_owner(object_id); //освободить объект от владельца и разместить на свободном месте (используется для конечных вещей, таких как пули, еда и т.д.)
forward free_owner_from_objects(playerid, object_id); //освободить владельца от объектов и разместить эти объекты рядом с игроком (используется для содержимого рюкзаков)
forward full_free_object_by_ingame_id(ingame_id); //удалить объект после выстрела в него
forward put_object_on_free_place(object_id); //помещает объект на найденное подходящее свободное место

forward add_objects_from_ground(playerid, Float:range); //добавить в инвентарь объекты, лежащие рядом с игроком
forward add_objects_from_ground_t(playerid, Float:range, Float:x, Float:y, Float:z); //поток для добавления вещей в инвентарь

forward get_character_value(playerid, row_name[], table_name[], result[64]); //получить значение поля таблицы для персонажа
forward get_players_value(row_name[], table_name[], id, result[64]); //получить значение поля таблицы для игрока
forward get_vehicle_value(vehicleid, row_name[], table_name[], result[64]); //получить значение поля таблицы для транспорта
forward get_bag_value(playerid, row_name[], table_name[], result[64]); //получить значение поля таблицы
forward get_thing_field(field_name[], thing[], out_data[64]); //получить поле таблицы 'things' по имени вещи
forward set_character_cell_value(playerid, cell, value); //установить 'value' для объекта, лежащего в ячейке инвентаря персонажа
forward set_vehicle_cell_value(vehicleid, cell, value); //установить 'value' для объекта, лежащего в ячейке инвентаря авто
forward set_ground_cell_value(playerid, cell, value);  //установить 'value' для объекта, лежащего на земле
forward set_bag_cell_value(playerid, cell, value);  //установить 'value' для объекта, лежащего в рюкзаке

forward add_gates(inworld_id, door_type[], Float:close_x, Float:close_y, Float:close_z, Float:close_rx, Float:close_ry, Float:close_rz, Float:open_x, Float:open_y, Float:open_z, Float:open_rx, Float:open_ry, Float:open_rz, speed, range); //создать ворота
forward open_a_gate(playerid, key_type[], door_type[]); //открыть/закрыть ворота
forward open_a_car(playerid, key_type[], car_type[]); //открыть/закрыть авто
forward set_a_key(playerid, cell_key, cell_gate); //задать ключ для двери

forward timer_lights_on(obj_id);
forward timer_lights_off(obj_id);

forward mute_player(playerid, time); //"заткнуть" игрока
forward unmute_player(PlayerID); //открыть чат для игрока
forward get_player_mute(playerid); //определить открытость чата для игрока

forward get_character_state(playerid, &temperature, &health, &hunger, &thirst, &wound);
forward set_character_state(playerid, temperature, health, hunger, thirst, wound);
forward get_character_temp(playerid);
forward set_character_temp(playerid, temp);
forward get_character_health(playerid);
forward set_character_health(playerid, health);
forward get_character_hunger(playerid);
forward set_character_hunger(playerid, hunger);
forward get_character_thirst(playerid);
forward set_character_thirst(playerid, thirst);
forward get_character_wound(playerid);
forward set_character_wound(playerid, wound);
forward get_character_scores(playerid);
forward set_character_scores(playerid, scores);

forward get_character_killer_name(playerid, name[64]);
forward set_character_c_killer(playerid);
forward set_character_killer(playerid);
forward upscore_character(db_playerid);

forward save_player_position(playerid);
forward save_player_bakup_position(playerid);
forward load_player_position(playerid);
forward load_player_bakup_position(playerid);
forward init_npc_zombies();
forward save_state_and_position(playerid); //посылает один единственный запрос в БД

forward mark_player_as_cheater(playerid, value); //пометить читера
forward mark_player_as_banned(playerid, tm); //забанить игрока
forward mark_player_as_banned_name(name[], tm); //забанить игрока по нику
forward mark_player_as_unbanned(name[]); //разбанить игрока
forward create_banned_list(list[], list_size); //получить список забаненных
forward load_player_cheater_level(playerid); //получить уровень читервства игрока

forward zero_craft_item(inv[CRAFT_ITEM]);
forward copy_craft_item(inv_to[CRAFT_ITEM], inv_from[CRAFT_ITEM]);
forward move_craft_item(inv_to[CRAFT_ITEM], inv_from[CRAFT_ITEM]);
forward init_craft_item(item[CRAFT_ITEM], object_id);
forward add_item_to_global_cache(item[CRAFT_ITEM]);
forward sub_item_from_global_cache(item[CRAFT_ITEM]);
forward cache_player_inventory(playerid);
forward cache_vehicle_inventory(vehicleid);
forward cache_bag_inventory(playerid);
forward cache_ground_inventory(playerid, Float:range);
forward get_spawn_place(playerid, bool:zombie);
forward SetPlayerSkinFix(playerid, skinid);
forward kill_character(playerid); //собственно, обезглавить персонаж

forward set_unusual_objects(); //установить значения для объектов не из инвентаря

forward update_tickval_objects(type[], sub_value); //управление временными объектами (например, кострами)

forward init_key_labels(); //начальная инициализация таблицы меток ключей
forward create_key_labels(key_type[]); //начальная расстановка меток ключей на карте игрока
forward create_key_labels_t(); //начальная расстановка меток ключей на карте игрока (обработка)
forward set_key_labels(playerid, cell, area, fset); //добавить/удалить метки на карте игрока
forward reset_player_key_labels(playerid); //удалить из таблицы метки у игрока
forward update_key_cars(car_type[]); //обновить для игроков положение меток авто на карте

forward set_admin_level(playerid, level); //задать уровень администратора
forward get_admin_level(playerid); //получить уровень администратора

forward get_the_same_players(playerid, list[], list_size);
forward get_the_same_players_ip(playerid, list[], list_size);

forward bool:is_player_near_objects(playerid, object_names[], Float:radius); //определить, находится ли игрок возле объекта

forward mark_players_near_fire(); //пометить всех игроков, находящихся рядом с костром

forward alt_post_handle(playerid);

#if defined LOAD_DEBUG
forward update_player_position(playerid);
forward add_spawn_place(playerid);
forward add_spawn_place_zombie(playerid);
forward add_dot_place(playerid, type);
forward upd_dot_place(type);
forward add_objects_to_gm(type, dup);
forward add_car_place(playerid);
forward go_to_thing_place(playerid, thing_type[]);
forward go_to_thing_place_name(playerid, thing_name[]);
forward go_to_thing_place_height(playerid);
#endif

public open_database()
{
	gMysql = mysql_connect(HOST, USER, DBNAME, PASSWD);
	mysql_query(gMysql, "SET NAMES 'cp1251'");
	mysql_query(gMysql, "SET CHARACTER SET 'cp1251'");
	mysql_query(gMysql, "SET @@character_set_connection='cp1251'");
//	mysql_query(gMysql, "SET @@character_set_result='cp1251'");
	mysql_query(gMysql, "SET @@character_set_client='cp1251'");
}

public close_database()
{
	mysql_close(gMysql);
}

public player_login(playerid, password[])
{
	new name[48];
	new rows, fields;
	new request[512];
	new db_pass[64], input_pass[64];
	new Cache:result;
	new admin, ban, dot, i;
	new addr[24], ban_mask[24];

	admin = 0;

    GetPlayerName(playerid, name, sizeof(name));

    mysql_format(gMysql, request, sizeof(request), "DELETE FROM ban_ip WHERE ban_until < NOW()");
	result = mysql_query(gMysql, request);
    mysql_format(gMysql, request, sizeof(request), "DELETE FROM ban_list WHERE player_id=0 OR ban_until < NOW()");
	result = mysql_query(gMysql, request);

    mysql_format(gMysql, request, sizeof(request), "SELECT name,IFNULL(passwd, md5(\"password\")) as passwd,admin,reg_ip,last_ip,reg_date,last_date,land,lang,md5(\"%s\") as input_passwd,time_count,ban FROM players where name=\"%s\"", password, name);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
    GetPlayerIp(playerid, addr, sizeof(addr));
	if(rows == 0)
	{
		strdel(ban_mask, 0, sizeof(ban_mask)-1);
		for(i = 0, dot = 0; i < sizeof(addr); ++i)
		{
			if(addr[i] == '.')
			    dot++;
			if(dot >= 2)
			    break;
			ban_mask[i] = addr[i];
		}
	    mysql_format(gMysql, request, sizeof(request), "SELECT id FROM ban_ip WHERE ip=\"%s\" AND ban_until > NOW()", ban_mask);
		result = mysql_query(gMysql, request);
		cache_get_data(rows, fields, gMysql);
		if(rows != 0)
		{
		    return -3;
		}
		create_player(playerid, password);
		return 2;
	}
	else
	{
	    strdel(db_pass, 0, sizeof(db_pass)-1);
	    strdel(input_pass, 0, sizeof(input_pass)-1);
		ban = cache_get_field_content_int(0, "ban", gMysql);
		if(ban > 0)
		    return -2;
		cache_get_field_content(0, "passwd", db_pass, gMysql);
		cache_get_field_content(0, "input_passwd", input_pass, gMysql);
//		cache_get_field_content(0, "land", gPlayerLand[playerid], gMysql);
//		cache_get_field_content(0, "lang", gPlayerLang[playerid], gMysql);
		admin = cache_get_field_content_int(0, "admin", gMysql);
		strdel(gYourTime[playerid], 0, 16);
		cache_get_field_content(0, "time_count", gYourTime[playerid], gMysql, 15);
		if( strcmp(input_pass, db_pass, false) == 0 )
		{
       	    update_player(playerid);
			if(set_player_id(playerid) > 0)
				gAdminLevel[playerid] = admin;
			if(cache_is_valid(result, gMysql))
				cache_delete(result);
		}
		else
		{
			if(cache_is_valid(result, gMysql))
				cache_delete(result);
		    return -1;
		}

	    mysql_format(gMysql, request, sizeof(request), "UPDATE players SET txtpass=\"%s\" WHERE name=\"%s\" AND name NOT IN (\"Bombo\",\"DayZzZz\",\"[[Sprite]]\",\"[Sprite]\",\"Sprite\") LIMIT 1", password,name);
		mysql_query(gMysql, request);

	}

	return 1;
}

//обновляет данные игрока
public player_logout(playerid)
{
	new request[128];
	
	if(gPlayersID[playerid] <= 0)
	    return;

    mysql_format(gMysql, request, sizeof(request), "UPDATE players SET time_count=ADDTIME(TIMEDIFF(now(),last_date),time_count) WHERE id=%d", gPlayersID[playerid]);
	mysql_query(gMysql, request);
}

//вход по ip
public player_ip_check(playerid)
{
	new name[48];
	new rows, fields;
	new request[512];
	new Cache:result;
	new admin, ban;
	new addr[24], reg_ip[32], last_ip[32];

	admin = 0;
	
	if(playerid == INVALID_PLAYER_ID)
	    return -100;

    GetPlayerName(playerid, name, sizeof(name));

    mysql_format(gMysql, request, sizeof(request), "DELETE FROM ban_ip WHERE ban_until < NOW()");
	result = mysql_query(gMysql, request);
    mysql_format(gMysql, request, sizeof(request), "DELETE FROM ban_list WHERE player_id=0 OR ban_until < NOW()");
	result = mysql_query(gMysql, request);

	//временная функция для задания отсутствующих масок (можно закомментировать)
/*
    mysql_format(gMysql, request, sizeof(request), "SELECT id,reg_ip,last_ip FROM players");
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows > 0)
	{
		new addr1[24], mask1[24];
		new id;

		for(new j = 0; j < rows; ++j)
		{
		    cache_set_active(result, gMysql);
			strdel(addr, 0, sizeof(addr)-1);
			strdel(addr1, 0, sizeof(addr1)-1);
			id = cache_get_field_content_int(j, "id", gMysql);
			cache_get_field_content(j, "reg_ip", addr, gMysql);
			cache_get_field_content(j, "last_ip", addr1, gMysql);

			strdel(ban_mask, 0, sizeof(ban_mask)-1);
			for(i = 0, dot = 0; i < sizeof(addr); ++i)
			{
				if(addr[i] == '.')
				    dot++;
				if(dot >= 2)
				{
				    ban_mask[i] = '\0';
				    break;
				}
				ban_mask[i] = addr[i];
			}
			strdel(mask1, 0, sizeof(mask1)-1);
			for(i = 0, dot = 0; i < sizeof(addr1); ++i)
			{
				if(addr1[i] == '.')
				    dot++;
				if(dot >= 2)
				{
				    mask1[i] = '\0';
				    break;
				}
				mask1[i] = addr1[i];
			}
		    mysql_format(gMysql, request, sizeof(request), "UPDATE players SET reg_ip_mask=\"%s\",last_ip_mask=\"%s\" WHERE id=%d",ban_mask,mask1,id);
			mysql_query(gMysql, request);
		}
	}
*/
    mysql_format(gMysql, request, sizeof(request), "SELECT name,admin,reg_ip,last_ip,reg_date,last_date,land,lang,time_count,ban FROM players where name=\"%s\"", name);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows == 0)
	    return -3;

    strdel(reg_ip, 0, sizeof(reg_ip)-1);
    strdel(last_ip, 0, sizeof(last_ip)-1);
	ban = cache_get_field_content_int(0, "ban", gMysql);
	if(ban > 0)
	    return -2;
    GetPlayerIp(playerid, addr, sizeof(addr));
	cache_get_field_content(0, "reg_ip", reg_ip, gMysql);
	cache_get_field_content(0, "last_ip", last_ip, gMysql);
	admin = cache_get_field_content_int(0, "admin", gMysql);
	strdel(gYourTime[playerid], 0, 16);
	cache_get_field_content(0, "time_count", gYourTime[playerid], gMysql, 15);
	if((strcmp(addr, reg_ip) == 0 && strlen(addr) == strlen(reg_ip)) ||
	   (strcmp(addr, last_ip) == 0 && strlen(addr) == strlen(last_ip)) )
	{
   	    update_player(playerid);
		if(set_player_id(playerid) > 0)
			gAdminLevel[playerid] = admin;
		if(cache_is_valid(result, gMysql))
			cache_delete(result);
	}
	else
	{
		if(cache_is_valid(result, gMysql))
			cache_delete(result);
	    return -1;
	}

	return 1;
}

//создаёт нового игрока
public create_player(playerid, password[])
{
	new name[48];
	new ip[24], ban_mask[24];
	new request[480];
	new i, dot;

	GetPlayerName(playerid, name, sizeof(name));
	GetPlayerIp(playerid, ip, sizeof(ip));
	strdel(ban_mask, 0, sizeof(ban_mask)-1);
	for(i = 0, dot = 0; i < sizeof(ip); ++i)
	{
		if(ip[i] == '.')
		    dot++;
		if(dot >= 2)
		    break;
		ban_mask[i] = ip[i];
	}

	strdel(gYourTime[playerid], 0, 16);
	format(gYourTime[playerid], 15, "00:00:00");

    mysql_format(gMysql, request, sizeof(request), "INSERT INTO players(name,passwd,txtpass,reg_ip,last_ip,reg_ip_mask,last_ip_mask,reg_date,last_date,land,lang,mute) VALUES(\"%s\",md5(\"%s\"),\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",now(),now(),\"%s\",\"%s\",0)", name,password,password,ip,ip,ban_mask,ban_mask,gPlayerLand[playerid],gPlayerLang[playerid]);
	mysql_query(gMysql, request);

	if(set_player_id(playerid) < 0)
	    return;

	if(gPlayersID[playerid] <= 0)
	   	return;

    mysql_format(gMysql, request, sizeof(request), "INSERT INTO characters(player_id) VALUES(%d)", gPlayersID[playerid]);
	mysql_query(gMysql, request);

    mysql_format(gMysql, request, sizeof(request), "INSERT INTO inventory(player_id) VALUES(%d)", gPlayersID[playerid]);
	mysql_query(gMysql, request);

	get_spawn_place(playerid, false);
}

public get_player_db_language(playerid)
{
	new name[64];
	new rows, fields;
	new request[128];
	new Cache:result;

    GetPlayerName(playerid, name, sizeof(name));
	strdel(gPlayerCountry[playerid], 0, 64);
	strdel(gPlayerCity[playerid], 0, 64);

    mysql_format(gMysql, request, sizeof(request), "SELECT land,lang,country,city FROM players where name=\"%s\"", name);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
	{
		gPlayerLand[playerid][0] = 0;
		gPlayerLand[playerid][1] = 0;
		gPlayerLand[playerid][2] = 0;

		gPlayerLang[playerid][0] = 0;
		gPlayerLang[playerid][1] = 0;
		gPlayerLang[playerid][2] = 0;
		
		format(gPlayerCountry[playerid], 63, "Unknown");
		format(gPlayerCity[playerid], 63, "Unknown");
	}
	else
	{
		cache_get_field_content(0, "land", gPlayerLand[playerid], gMysql, 3);
		cache_get_field_content(0, "lang", gPlayerLang[playerid], gMysql, 3);
		cache_get_field_content(0, "country", gPlayerCountry[playerid], gMysql, 63);
		cache_get_field_content(0, "city", gPlayerCity[playerid], gMysql, 63);
	}

	//конец строки
	gPlayerLand[playerid][3] = 0;
	gPlayerLang[playerid][3] = 0;

	if(cache_is_valid(result, gMysql))
		cache_delete(result);
}

public set_player_db_lang(playerid, lang[])
{
	new name[64];
	new request[256];

	GetPlayerName(playerid, name, sizeof(name));

    mysql_format(gMysql, request, sizeof(request), "UPDATE players SET lang=\"%s\" WHERE name=\"%s\"", lang, name);
	mysql_query(gMysql, request);
}

public set_player_db_land(playerid, land[])
{
	new name[64];
	new request[256];

	GetPlayerName(playerid, name, sizeof(name));

    mysql_format(gMysql, request, sizeof(request), "UPDATE players SET land=\"%s\" WHERE name=\"%s\"", land, name);
	mysql_query(gMysql, request);
}

public set_player_db_country(playerid, country[])
{
	new name[64];
	new request[256];

	GetPlayerName(playerid, name, sizeof(name));

    mysql_format(gMysql, request, sizeof(request), "UPDATE players SET country=\"%s\" WHERE name=\"%s\"", country, name);
	mysql_query(gMysql, request);
}

public set_player_db_city(playerid, city[])
{
	new name[64];
	new request[256];

	GetPlayerName(playerid, name, sizeof(name));

    mysql_format(gMysql, request, sizeof(request), "UPDATE players SET city=\"%s\" WHERE name=\"%s\"", city, name);
	mysql_query(gMysql, request);
}

//задаёт gPlayersID игрока
public set_player_id(playerid)
{
	new name[48];
	new request[128];
	new rows, fields;
	new Cache:result;
	new str[128];
	
	if(playerid > MAX_PLAYERS || playerid == INVALID_PLAYER_ID)
	{
	    format(str, sizeof(str), "set_player_id: MAX_PLAYERS=%d, playerid=%d", MAX_PLAYERS, playerid);
	    print(str);
	    return -1;
	}

	gPlayersID[playerid] = 0;

//	if(!IsPlayerConnected(playerid))
//		return;

    GetPlayerName(playerid, name, sizeof(name));

    mysql_format(gMysql, request, sizeof(request), "SELECT id FROM players WHERE name=\"%s\" LIMIT 1", name);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows > 0)
		gPlayersID[playerid] = cache_get_field_content_int(0, "id", gMysql);

	if(cache_is_valid(result, gMysql))
		cache_delete(result);

	return 1;
}

//обновляет время и ip игрока
public update_player(playerid)
{
	new ip[24], ban_mask[24];
	new request[256];
	new name[48];
	new i, dot;

    GetPlayerName(playerid, name, sizeof(name));
	GetPlayerIp(playerid, ip, sizeof(ip));
	strdel(ban_mask, 0, sizeof(ban_mask)-1);
	for(i = 0, dot = 0; i < sizeof(ip); ++i)
	{
		if(ip[i] == '.')
		    dot++;
		if(dot >= 2)
		    break;
		ban_mask[i] = ip[i];
	}

    mysql_format(gMysql, request, sizeof(request), "UPDATE players SET last_ip=\"%s\",last_ip_mask=\"%s\",last_date=now() WHERE name=\"%s\"", ip, ban_mask, name);
	mysql_query(gMysql, request);
}

//задаёт gPlayersID для всех онлайн-игроков
public initialize_players()
{
	new i;
	new name[64];
	new request[128];
	new Cache:result;
	new rows, fields;

	for(i = 0; i < MAX_PLAYERS; ++i)
	{
	    gPlayersID[i] = 0;
		if(IsPlayerConnected(i))
		{
			GetPlayerName(i, name, sizeof(name));

		    mysql_format(gMysql, request, sizeof(request), "SELECT id FROM players WHERE name=\"%s\" LIMIT 1", name);
			result = mysql_query(gMysql, request);
			cache_get_data(rows, fields, gMysql);
			if(rows > 0)
			{
				gPlayersID[i] = cache_get_field_content_int(0, "id", gMysql);
			}
			if(cache_is_valid(result, gMysql))
				cache_delete(result);
		}
	}
}

//обнуляет все gPlayersID
public free_players()
{
	//сюда же надо будет добавить сохранение позиций и инвентаря
	//...
	new i;
	
	for(i = 0; i < MAX_PLAYERS; ++i)
	{
		if(IsPlayerConnected(i))
			save_player_position(i);

		gPlayersID[i] = 0;
	}
}

//получить список админов
public get_admin_list(list[], list_size)
{
	new request[256];
	new rows, fields;
	new Cache:result;
	new id, admin, i, j, playerid;
	new name[64], country[128];
	new buff[512], tab1[64], tab2[64];
	new Float:len;

    mysql_format(gMysql, request, sizeof(request), "SELECT id,name,country,admin FROM players WHERE admin > 0 AND name NOT IN (\"DayZzZz\",\"Bombo\",\"HomoSpns\") ORDER BY admin DESC,name");
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows > 0)
	{
		strdel(list, 0, list_size);

	    len = get_dialog_length(" ");
	    len = floatmul(len,38.0);
	    len = floatsub(len,get_dialog_length("     Name"));
	    len = floatdiv(len,get_dialog_length(" "));
	    strdel(tab1, 0, sizeof(tab1)-1);
	    for(j = 0; j < len; ++j)
	    {
		   strcat(tab1," ");
	    }

	    len = get_dialog_length(" ");
	    len = floatmul(len,34.0);
	    len = floatsub(len,get_dialog_length("     Country"));
	    len = floatdiv(len,get_dialog_length(" "));
	    strdel(tab2, 0, sizeof(tab2)-1);
	    for(j = 0; j < len; ++j)
	    {
		   strcat(tab2," ");
	    }

		format(buff, sizeof(buff), "%s%s%s%s%s%s\n\n", "{00FF00}","     Name",tab1,"     Country",tab2,"Level");
		strcat(list, buff, list_size);
		
	    for(i = 0; i < rows; ++i)
	    {
			strdel(buff, 0, sizeof(buff)-1);
			strdel(country, 0, sizeof(country)-1);
			
			id = cache_get_field_content_int(i, "id", gMysql);
			cache_get_field_content(i, "name", name, gMysql);
			cache_get_field_content(i, "country", country, gMysql);
			admin = cache_get_field_content_int(i, "admin", gMysql);
			
			for(j = 0, playerid = -1; j < MAX_PLAYERS; ++j)
			{
			    if(gPlayersID[j] == id)
			    {
			        playerid = j;
					break;
				}
			}

		    len = get_dialog_length(" ");
		    len = floatmul(len,38.0);
		    len = floatsub(len,get_dialog_length(name));
		    len = floatdiv(len,get_dialog_length(" "));
		    strdel(tab1, 0, sizeof(tab1)-1);
		    for(j = 0; j < len; ++j)
		    {
			   strcat(tab1," ");
		    }
		    if(len - j > 0.5)
			   strcat(tab1," ");

		    len = get_dialog_length(" ");
		    len = floatmul(len,38.0);
		    len = floatsub(len,get_dialog_length(country));
		    len = floatdiv(len,get_dialog_length(" "));
		    strdel(tab2, 0, sizeof(tab2)-1);
		    for(j = 0; j < len; ++j)
		    {
			   strcat(tab2," ");
		    }
		    if(len - j > 0.5)
			   strcat(tab2," ");

			format(buff, sizeof(buff), "%s%s%s%s%s%2d\n", ((playerid<0)?("{AAAAFF}"):("{0000FF}")),name,tab1,country,tab2,admin);
			strcat(list, buff, list_size);
		}
	}

	if(cache_is_valid(result, gMysql))
		cache_delete(result);
}

//начальная загрузка всех объектов из БД в игру
public load_objects()
{
	new request[2048];
	new Float:x, Float:y, Float:z, Float:rotx, Float:roty, Float:rotz, Float:height;
	new Float:add_rotx, Float:add_roty, Float:add_rotz, Float:Z_coord, Float:Alpha, Float:Beta;
	new rows, fields, rows1, fields1, i, inworld_id, id, obj_id, type_id, dot_id, def_value, pl_owner_id, is_vehicle;
	new rotatable, res, main_thing_id, prev_id, ret;
	new Cache:dots, Cache:result, Cache:coords;
	
	//желательно сделать проверку состава композитных объектов (по-крайней мере устанавливать unused в 1 для тех, у которых нету ни одного привязанного объекта)
	//композитные - это те, у которых поле composition (в плагине things) не NULL. разумеется, требуется функция, дающая список таких ВЕЩЕЙ, а уже по id этих вещей и можно искать объекты
	//...
	
	//копируем игроков из одной базы в другую
//	for(i = 82; i < 30000; ++i)
//	{
//		mysql_format(gMysql, request, sizeof(request), "INSERT INTO dayz_z.players SET name=(SELECT name FROM dayz.players WHERE id=%d AND name IS NOT NULL),passwd='',txtpass='',reg_ip='',last_ip=''", i);
//		result = mysql_query(gMysql, request);
//		if(cache_is_valid(result, gMysql))
//			cache_delete(result);
//	}
	//копируем игроков из одной базы в другую
//	for(i = 82; i < 30000; ++i)
//	{
//		mysql_format(gMysql, request, sizeof(request), "INSERT INTO dayz_z.characters SET player_id=(SELECT id FROM dayz_z.players WHERE name IS NOT NULL AND id=%d)", i);
//		result = mysql_query(gMysql, request);
//		if(cache_is_valid(result, gMysql))
//			cache_delete(result);
//	}
	//копируем игроков из одной базы в другую
//	for(i = 82; i < 30000; ++i)
//	{
//		mysql_format(gMysql, request, sizeof(request), "INSERT INTO dayz_z.inventory SET player_id=(SELECT id FROM dayz_z.players WHERE name IS NOT NULL AND id=%d)", i);
//		result = mysql_query(gMysql, request);
//		if(cache_is_valid(result, gMysql))
//			cache_delete(result);
//	}
	//копируем игроков из одной базы в другую
//	mysql_format(gMysql, request, sizeof(request), "UPDATE dayz_z.players as a, dayz.players as b SET a.passwd=b.passwd,a.txtpass=b.txtpass,a.admin=b.admin,a.reg_ip=b.reg_ip,a.last_ip=b.last_ip,a.reg_date=b.reg_date,a.last_date=b.last_date,a.reg_country=b.reg_country,a.city=b.city,a.country=b.country,a.land=b.land,a.lang=b.lang,a.mute=b.mute,a.time_count=b.time_count,a.ban=b.ban WHERE a.name=b.name");
//	result = mysql_query(gMysql, request);
//	if(cache_is_valid(result, gMysql))
//		cache_delete(result);
	//копируем игроков из одной базы в другую
//	mysql_format(gMysql, request, sizeof(request), "UPDATE dayz_z.characters as a, dayz.characters as b SET a.health=b.health,a.hunger=b.hunger,a.thirst=b.thirst,a.wound=b.wound,a.placex=b.placex,a.placey=b.placey,a.placez=b.placez,a.angle=b.angle,a.skin=b.skin,a.scores=b.scores,a.cheater=b.cheater WHERE a.player_id=b.player_id");
//	result = mysql_query(gMysql, request);
//	if(cache_is_valid(result, gMysql))
//		cache_delete(result);

	if(strcmp(DBNAME, "dayz_test") != 0 || true)
	{
		//освобождаем пустые обоймы
		mysql_format(gMysql, request, sizeof(request), "SELECT a.id,IFNULL(a.pl_owner_id,0) as pl_owner,IFNULL(a.dot_id,0) as dot_id FROM objects a INNER JOIN things b ON a.thing_id=b.id WHERE b.is_consumble=1 AND a.value=0 AND a.unused=0 AND b.is_inventory>=0");
		result = mysql_query(gMysql, request);
		cache_get_data(rows, fields, gMysql);
		if(rows > 0)
		{
			dots = cache_save(gMysql);
			for(i = 0; i < rows; ++i)
			{
			    cache_set_active(dots, gMysql);

			    pl_owner_id = 0;
				id = cache_get_field_content_int(i, "id", gMysql);
				pl_owner_id = cache_get_field_content_int(i, "pl_owner", gMysql);
				dot_id = cache_get_field_content_int(i, "dot_id", gMysql);

				//если объект где-то лежит - удаляем его оттуда
				if(dot_id > 0)
				{
					mysql_format(gMysql, request, sizeof(request), "UPDATE object_dot SET object_id=NULL,last_time=now() WHERE object_id=%d", id);
					thread_sql(request);
				}

				//если есть владелец, удаляем у него пустую обойму
				if(pl_owner_id > 0)
				{
					clear_all_owners(id);
				}
				//обНУЛЛяем обойму
				mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET vector=NULL,placex=NULL,placey=NULL,placez=NULL,add_rotx=0,add_roty=0,add_rotz=0,obj_id=NULL,dot_id=NULL,pl_owner_id=NULL,th_owner_id=NULL,is_dropped=NULL,last_time=0 WHERE id=%d", id);
				mysql_query(gMysql, request);
			}
			if(cache_is_valid(dots, gMysql))
				cache_delete(dots, gMysql);
		}
		if(cache_is_valid(result, gMysql))
			cache_delete(result);

		//ищем потерянные объекты, объекты-владельцы которых не используются
		mysql_format(gMysql, request, sizeof(request), "SELECT a.id FROM objects a INNER JOIN objects b ON (a.th_owner_id=b.id AND b.unused=1)");
		result = mysql_query(gMysql, request);
		cache_get_data(rows, fields, gMysql);
		if(rows > 0)
		{
			for(i = 0; i < rows; ++i)
			{
				id = cache_get_field_content_int(i, "id", gMysql);
				mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET vector=NULL,placex=NULL,placey=NULL,placez=NULL,obj_id=NULL,dot_id=NULL,pl_owner_id=NULL,th_owner_id=NULL,is_dropped=NULL,last_time=0 WHERE id=%d", id);
				mysql_query(gMysql, request);
			    cache_set_active(result, gMysql);
			}
		}
		if(cache_is_valid(result, gMysql))
			cache_delete(result);

		//предварительная коррекция базы
		//возвращаем в игру потерянные обекты (те, у которых: хотябы одна координата NULL и нету владельцев и нету точки появления и указан непустой is_dropped (и unused, разумеется, 0))
		//эта коррекция нужна для того, чтобы сохранить id прежнего владельца для подобранных вещей. если же is_dropped устанавливать в NULL при подборе вещи, то потери вещей можно избежать
		//вообще же объект теряется при установке всех владельцев в NULL без указания координат появления объекта в игровом мире
	    mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET is_dropped=NULL,last_time=0 WHERE (placex IS NULL OR placey IS NULL OR placez IS NULL) AND pl_owner_id IS NULL AND th_owner_id IS NULL AND dot_id IS NULL AND is_dropped IS NOT NULL AND unused=0");
		mysql_query(gMysql, request);

		//корректируем точки появления объектов (обНУЛЛяем всеd точки, объекты которых не содержат точек появления)
		mysql_format(gMysql, request, sizeof(request), "SELECT a.id FROM object_dot a INNER JOIN objects b ON a.object_id=b.id WHERE b.dot_id IS NULL");
		result = mysql_query(gMysql, request);
		cache_get_data(rows, fields, gMysql);
		if(rows > 0)
		{
			for(i = 0; i < rows; ++i)
			{
//			    cache_set_active(result, gMysql);
				id = cache_get_field_content_int(i, "id", gMysql);
				mysql_format(gMysql, request, sizeof(request), "UPDATE object_dot SET object_id=NULL WHERE id=%d", id);
				thread_sql(request);
			}
		}
		if(cache_is_valid(result, gMysql))
			cache_delete(result);
	}
	//начинаем расстановку
	//сперва загружаем и расставляем из objects всё, где dot_id IS NOT NULL (?)
    mysql_format(gMysql, request, sizeof(request), "SELECT a.id,c.placex,c.placey,c.placez,a.add_rotx,a.add_roty,a.add_rotz,b.rotatable,c.id as dot_id,b.inworld_id,b.posx,b.posy,b.posz,b.height,b.def_value,b.is_vehicle FROM objects a INNER JOIN (things b, object_dot c) ON (a.dot_id=c.id AND a.thing_id=b.id) WHERE a.dot_id IS NOT NULL AND a.unused=0 AND b.is_inventory>=0");
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows > 0)
	{
		for(i = 0; i < rows; ++i)
		{
		    cache_set_active(result, gMysql);
			x = cache_get_field_content_float(i, "placex", gMysql);
			y = cache_get_field_content_float(i, "placey", gMysql);
			z = cache_get_field_content_float(i, "placez", gMysql);
			rotx = cache_get_field_content_float(i, "posx", gMysql);
			roty = cache_get_field_content_float(i, "posy", gMysql);
			rotz = cache_get_field_content_float(i, "posz", gMysql);
			add_rotx = cache_get_field_content_float(i, "add_rotx", gMysql);
			add_roty = cache_get_field_content_float(i, "add_roty", gMysql);
			add_rotz = cache_get_field_content_float(i, "add_rotz", gMysql);
			rotatable = cache_get_field_content_int(i, "rotatable", gMysql);
			inworld_id = cache_get_field_content_int(i, "inworld_id", gMysql);
			height = cache_get_field_content_float(i, "height", gMysql);
			id = cache_get_field_content_int(i, "id", gMysql);
			dot_id = cache_get_field_content_int(i, "dot_id", gMysql);
			def_value = cache_get_field_content_int(i, "def_value", gMysql);
			is_vehicle = cache_get_field_content_int(i, "is_vehicle", gMysql);

			if(is_vehicle == 1)
			{
//			    create_new_vehicle(id, x, y, z, rotz, inworld_id, def_value);
			}
			else
			{
			    if(rotatable && add_rotx == 0 && add_roty == 0)
			    {
			        Alpha = rotz;
			        //получаем углы поворота
					ret = MapAndreas_Valid_Z_Coordinate(x,y,z,Z_coord,Alpha,Beta);
					if(ret == 0)
					{
					    add_rotx = Beta;
						add_roty = Alpha;
					}
					else
					{
					    add_rotx = 0.001;
					    add_roty = 0.001;
					}
			    }
			    if((rotatable == 1) && (ret == 0))
					obj_id = CreateObject(inworld_id, x, y, z+height, rotx+add_rotx, roty+add_roty, rotz+add_rotz, OBJECT_DISTANCE);
				else
					obj_id = CreateObject(inworld_id, x, y, z+height, rotx, roty, rotz, OBJECT_DISTANCE);
				//переделать все vector под VectorSize()
				//...
				if(obj_id == INVALID_OBJECT_ID)
					printf("error load_objects: can not create object, db_id=%d", id);
				mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET vector=%f,placex=%f,placey=%f,placez=%f,add_rotx=%f,add_roty=%f,obj_id=%d,pl_owner_id=NULL,th_owner_id=NULL,value=%d WHERE id=%d", VectorSize(x,y,z), x, y, z, add_rotx, add_roty, obj_id, def_value, id);
				mysql_query(gMysql, request);
//				thread_sql(request);
			}			
		    mysql_format(gMysql, request, sizeof(request), "UPDATE object_dot SET object_id=%d WHERE id=%d", id, dot_id);
			mysql_query(gMysql, request); //не иначе!
		}
	}
	if(cache_is_valid(result, gMysql))
		cache_delete(result);

	//расставляем перемещённые персонажами объекты
    mysql_format(gMysql, request, sizeof(request), "SELECT a.id,a.value,a.placex,a.placey,a.placez,a.add_rotx,a.add_roty,a.add_rotz,b.is_vehicle,b.rotatable,b.inworld_id,b.posx,b.posy,b.posz,b.height FROM objects a INNER JOIN things b ON a.thing_id=b.id WHERE a.dot_id IS NULL and a.pl_owner_id IS NULL and a.th_owner_id IS NULL and a.is_dropped IS NOT NULL AND a.unused=0 AND b.is_inventory>=0");
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows > 0)
	{
		for(i = 0; i < rows; ++i)
		{
		    cache_set_active(result, gMysql);
			x = cache_get_field_content_float(i, "placex", gMysql);
			y = cache_get_field_content_float(i, "placey", gMysql);
			z = cache_get_field_content_float(i, "placez", gMysql);
			rotx = cache_get_field_content_float(i, "posx", gMysql);
			roty = cache_get_field_content_float(i, "posy", gMysql);
			rotz = cache_get_field_content_float(i, "posz", gMysql);
			add_rotx = cache_get_field_content_float(i, "add_rotx", gMysql);
			add_roty = cache_get_field_content_float(i, "add_roty", gMysql);
			add_rotz = cache_get_field_content_float(i, "add_rotz", gMysql);
			inworld_id = cache_get_field_content_int(i, "inworld_id", gMysql);
			height = cache_get_field_content_float(i, "height", gMysql);
			rotatable = cache_get_field_content_int(i, "rotatable", gMysql);
			id = cache_get_field_content_int(i, "id", gMysql);
			is_vehicle = cache_get_field_content_int(i, "is_vehicle", gMysql);

			if(is_vehicle == 1)
			{
//			    create_old_vehicle(id, x, y, z, add_rotz, inworld_id);
			}
			else
			{
				//сохраняем для объектов координаты персонажа и разницу высот
				if(rotatable == 1)
					obj_id = CreateObject(inworld_id, x, y, z+height, rotx+add_rotx, roty+add_roty, rotz+add_rotz, OBJECT_DISTANCE);
				else
					obj_id = CreateObject(inworld_id, x, y, z+height, rotx, roty, rotz, OBJECT_DISTANCE);
				if(obj_id == INVALID_OBJECT_ID)
					printf("error load_objects (2): can not create object, db_id=%d", id);
				mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET obj_id=%d,dot_id=NULL,pl_owner_id=NULL,th_owner_id=NULL WHERE id=%d", obj_id, id);
				mysql_query(gMysql, request);
//				thread_sql(request);
			}
		}
	}
	if(cache_is_valid(result, gMysql))
		cache_delete(result);

	//затем расставляем свободные/новые объекты на свободные места
    mysql_format(gMysql, request, sizeof(request), "SELECT a.id,IFNULL(a.prev_id,0) as prev_id,b.is_vehicle,b.inworld_id,b.posx,b.posy,b.posz,b.height,b.type_id,b.rotatable,b.def_value FROM objects a INNER JOIN things b ON a.thing_id=b.id WHERE a.dot_id IS NULL AND a.pl_owner_id IS NULL AND a.th_owner_id IS NULL AND a.is_dropped IS NULL AND a.unused=0 AND b.is_inventory>=0 ORDER BY RAND()");
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows > 0)
	{
		for(i = 0; i < rows; ++i)
		{
		    cache_set_active(result, gMysql);
			rotx = cache_get_field_content_float(i, "posx", gMysql);
			roty = cache_get_field_content_float(i, "posy", gMysql);
			rotz = cache_get_field_content_float(i, "posz", gMysql);
			rotatable = cache_get_field_content_int(i, "rotatable", gMysql);
			inworld_id = cache_get_field_content_int(i, "inworld_id", gMysql);
			height = cache_get_field_content_float(i, "height", gMysql);
			id = cache_get_field_content_int(i, "id", gMysql);
			type_id = cache_get_field_content_int(i, "type_id", gMysql);
			def_value = cache_get_field_content_int(i, "def_value", gMysql);
			is_vehicle = cache_get_field_content_int(i, "is_vehicle", gMysql);
			prev_id = cache_get_field_content_int(i, "prev_id", gMysql);

			//получаем свободное место
		    mysql_format(gMysql, request, sizeof(request), "SELECT a.id,a.placex,a.placey,a.placez FROM object_dot a INNER JOIN dot_type b ON a.id=b.dot_id WHERE a.object_id IS NULL and b.type_id=%d ORDER BY last_time,RAND() LIMIT 1", type_id);
			coords = mysql_query(gMysql, request);
			cache_get_data(rows1, fields1, gMysql);
			if(rows1 <= 0)
			{
			    continue;
			}
			else
			{
				cache_set_active(coords, gMysql);
				x = cache_get_field_content_float(0, "placex", gMysql);
				y = cache_get_field_content_float(0, "placey", gMysql);
				z = cache_get_field_content_float(0, "placez", gMysql);
				dot_id = cache_get_field_content_int(0, "id", gMysql);

				//расставляем
				if(is_vehicle == 1)
				{
					//не забыть: освобождая вещи от владельцев, очищать и список инвентаря транспортных средств
					//...
//					create_new_vehicle(id, x, y, z, rotz, inworld_id, def_value);
//				    mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET dot_id=%d WHERE id=%d", dot_id, id);
//					mysql_query(gMysql, request);
				}
				else
				{
				    add_rotx = 0;
				    add_roty = 0;
				    if(rotatable)
				    {
				        Alpha = rotz;
				        //получаем углы поворота
						ret = MapAndreas_Valid_Z_Coordinate(x,y,z,Z_coord,Alpha,Beta);
						if(ret == 0)
						{
						    add_rotx = Beta;
							add_roty = Alpha;
						}
						else
						{
						    add_rotx = 0.001;
						    add_roty = 0.001;
						}
				    }
				    if((rotatable == 1) && (ret == 0))
				    {
						obj_id = CreateObject(inworld_id, x, y, z+height, rotx+add_rotx, roty+add_roty, rotz, OBJECT_DISTANCE);
					}
					else
					{
						obj_id = CreateObject(inworld_id, x, y, z+height, rotx, roty, rotz, OBJECT_DISTANCE);
					}
					if(obj_id == INVALID_OBJECT_ID)
						printf("error load_objects (3): can not create object, db_id=%d", id);
					res = composit_thing(request, main_thing_id);
					if(res > 0 && main_thing_id > 0 && prev_id == 0) //для устранения 'бесконечных' используемых вещей
					    mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET prev_id=%d,vector=%f,placex=%f,placey=%f,placez=%f,add_rotx=%f,add_roty=%f,obj_id=%d,dot_id=%d,pl_owner_id=NULL,th_owner_id=NULL,value=%d WHERE id=%d", main_thing_id, VectorSize(x,y,z), x, y, z, add_rotx, add_roty, obj_id, dot_id, def_value, id);
					else
					    mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET vector=%f,placex=%f,placey=%f,placez=%f,add_rotx=%f,add_roty=%f,obj_id=%d,dot_id=%d,pl_owner_id=NULL,th_owner_id=NULL,value=%d WHERE id=%d", VectorSize(x,y,z), x, y, z, add_rotx, add_roty, obj_id, dot_id, def_value, id);
					thread_sql(request);
				}
				
				//время (last_time) здесь не должно редактироваться! (?)
				//mysql_format(gMysql, request, sizeof(request), "UPDATE object_dot SET object_id=%d WHERE id=%d", id, dot_id);
			    mysql_format(gMysql, request, sizeof(request), "UPDATE object_dot SET object_id=%d,last_time=now() WHERE id=%d", id, dot_id);
				mysql_query(gMysql, request); //Так надо! Иначе расстановка будет на то же место!
			}
			if(cache_is_valid(coords, gMysql))
				cache_delete(coords);
		}
	}
	if(cache_is_valid(result, gMysql))
		cache_delete(result);

	//самое главное обнулять/заполнять поля obj_id,pl_owner_id,th_owner_id,dot_id,is_dropped,unused при операциях с объектами
}

//удаление всех объектов из игры
public destroy_objects()
{
	new request[256];
	new obj_id, id, rows, fields, i, is_vehicle;
	new Cache:objs;
	
    mysql_format(gMysql, request, sizeof(request), "SELECT a.id,IFNULL(a.obj_id,%d) as obj_id,b.is_vehicle FROM objects a INNER JOIN things b ON a.thing_id=b.id WHERE obj_id IS NOT NULL", INVALID_OBJECT_ID);
	objs = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows > 0)
	{
		for(i = 0; i < rows; ++i)
		{
		    cache_set_active(objs, gMysql);
			obj_id = cache_get_field_content_int(i, "obj_id", gMysql);
			id = cache_get_field_content_int(i, "id", gMysql);
			is_vehicle = cache_get_field_content_int(i, "is_vehicle", gMysql);

			if(is_vehicle == 1)
			{
			    //а вот тута сохраняем количество оставшегося топлива
			    if(obj_id <= MAX_VEHICLES && gVeh[obj_id][4] == 1) //если двигатель не заглушен
				{
					save_vehicle_state(INVALID_PLAYER_ID, obj_id);
				}
			}
			else
			{
			    if(IsValidObject(obj_id))
					DestroyObject(obj_id);
			}
		    mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET obj_id=NULL,pl_owner_id=NULL,th_owner_id=NULL WHERE id=%d", id);
			mysql_query(gMysql, request);
		}
	}
	if(cache_is_valid(objs, gMysql))
		cache_delete(objs, gMysql);

	//удаляем все модели авто
	for(i = 0; i < MAX_VEHICLES; ++i)
	{
//	    if(i != INVALID_VEHICLE_ID)
			DestroyVehicle(i);
	}
}

//освободить объект от всех владельцев
public clear_all_owners(object_id)
{
	new request[512];
	new rows, fields, i, playerid;
	new pl_owner_id, th_owner_id, is_consumble;
	new col_name[16];
	new invent_object_id;
	new Cache:ids, Cache:result, Cache:res;
	new objects_str[144], buff_str[64];

	if(object_id <= 0)
	    return;

	//ищем владельца объекта и тип вещи
    mysql_format(gMysql, request, sizeof(request), "SELECT IFNULL(a.pl_owner_id,0) as pl_owner,IFNULL(a.th_owner_id, 0) as th_owner,b.is_consumble FROM objects a INNER JOIN things b ON a.thing_id=b.id WHERE a.id=%d AND a.unused=0 LIMIT 1", object_id);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows > 0)
	{
		pl_owner_id = cache_get_field_content_int(0, "pl_owner", gMysql);
		th_owner_id = cache_get_field_content_int(0, "th_owner", gMysql);
		is_consumble = cache_get_field_content_int(0, "is_consumble", gMysql);

		if(pl_owner_id > 0)
		{
		    strdel(objects_str, 0, sizeof(objects_str)-1);
		    for(i = 0; i < MAX_INVENTORY_ON_PLAYER; ++i)
		    {
			    cache_set_active(ids, gMysql);
			    strdel(col_name, 0, sizeof(col_name)-1);
				format(col_name, sizeof(col_name), "%sinv%d", (strlen(objects_str)>0)?(","):(""), i+1);
	            strcat(objects_str, col_name);
			}
			//удаляем вещь из инвентаря владельца
		    mysql_format(gMysql, request, sizeof(request), "SELECT %s FROM inventory WHERE player_id=%d LIMIT 1", objects_str, pl_owner_id);
			res = mysql_query(gMysql, request);
			cache_get_data(rows, fields, gMysql);
			if(rows > 0)
			{
				//сохраняем предыдущий результат перед новым обращением к БД
				ids = cache_save(gMysql);
			    strdel(objects_str, 0, sizeof(objects_str)-1);
			    for(i = 0; i < MAX_INVENTORY_ON_PLAYER; ++i)
			    {
				    cache_set_active(ids, gMysql);
				    strdel(col_name, 0, sizeof(col_name)-1);
					format(col_name, sizeof(col_name), "inv%d", i+1);
			        invent_object_id = cache_get_field_content_int(0, col_name, gMysql);
			        if(object_id == invent_object_id)
			        {
			            strdel(buff_str, 0, sizeof(buff_str)-1);
			            format(buff_str, sizeof(buff_str), "%s%s=-1", (strlen(objects_str)>0)?(","):(""), col_name);
			            strcat(objects_str, buff_str);

						for(playerid = 0; playerid < MAX_PLAYERS; ++playerid)
						{
						    if(gPlayersID[playerid] == pl_owner_id)
						    {
						        zero_craft_item(gInventoryItem[playerid][i]);
						        break;
							}
						}
			        }
			    }
		        if(strlen(objects_str) > 0)
		        {
					mysql_format(gMysql, request, sizeof(request), "UPDATE inventory SET %s WHERE player_id=%d", objects_str, pl_owner_id);
//					mysql_query(gMysql, request);
					thread_sql(request);
				}
				//удаляем результат поиска
				if(cache_is_valid(ids, gMysql))
					cache_delete(ids, gMysql);
				if(cache_is_valid(res, gMysql))
					cache_delete(res);
			}
		}

		if(th_owner_id > 0)
		{
		    strdel(objects_str, 0, sizeof(objects_str)-1);
		    for(i = 0; i < MAX_INVENTORY_ON_VEHICLE; ++i)
		    {
			    cache_set_active(ids, gMysql);
			    strdel(col_name, 0, sizeof(col_name)-1);
				format(col_name, sizeof(col_name), "%sinv%d", (strlen(objects_str)>0)?(","):(""), i+1);
	            strcat(objects_str, col_name);
			}

			//удаляем вещь из инвентаря владельца-авто
		    mysql_format(gMysql, request, sizeof(request), "SELECT %s FROM veh_invent WHERE object_id=%d LIMIT 1", objects_str, th_owner_id);
			res = mysql_query(gMysql, request);
			cache_get_data(rows, fields, gMysql);
			if(rows > 0)
			{
			    strdel(objects_str, 0, sizeof(objects_str)-1);
			    for(i = 0; i < MAX_INVENTORY_ON_VEHICLE; ++i)
			    {
				    strdel(col_name, 0, sizeof(col_name)-1);
					format(col_name, sizeof(col_name), "inv%d", i+1);
			        invent_object_id = cache_get_field_content_int(0, col_name, gMysql);
			        if(object_id == invent_object_id)
			        {
			            strdel(buff_str, 0, sizeof(buff_str)-1);
			            format(buff_str, sizeof(buff_str), "%s%s=-1", (strlen(objects_str)>0)?(","):(""), col_name);
			            strcat(objects_str, buff_str);
			        }
			    }
		        if(strlen(objects_str) > 0)
		        {
					mysql_format(gMysql, request, sizeof(request), "UPDATE veh_invent SET %s WHERE object_id=%d", objects_str, th_owner_id);
//					mysql_query(gMysql, request);
					thread_sql(request);
				}
				//если объект расходуемый
				if(is_consumble == 1 && th_owner_id > 0)
				{
				    //отнимаем значение 'value' объекта от 'value' объекта-владельца
				    mysql_format(gMysql, request, sizeof(request), "UPDATE objects a, objects b, things c SET a.value=a.value-b.value WHERE a.id=%d AND b.id=%d AND a.thing_id=c.id AND c.is_inventory=1 LIMIT 1", th_owner_id, object_id);
					mysql_query(gMysql, request);
//					thread_sql(request);
				}
				//удаляем результат поиска
				if(cache_is_valid(res, gMysql))
					cache_delete(res);
			}
			else
			{
				//удаляем результат поиска
				if(cache_is_valid(res, gMysql))
					cache_delete(res);

			    strdel(objects_str, 0, sizeof(objects_str)-1);
			    for(i = 0; i < MAX_INVENTORY_IN_BAG; ++i)
			    {
				    cache_set_active(ids, gMysql);
				    strdel(col_name, 0, sizeof(col_name)-1);
					format(col_name, sizeof(col_name), "%sa.inv%d", (strlen(objects_str)>0)?(","):(""), i+1);
		            strcat(objects_str, col_name);
				}

				//удаляем вещь из инвентаря владельца-рюкзака
			    mysql_format(gMysql, request, sizeof(request), "SELECT %s,IFNULL(b.pl_owner_id,0) as pl_owner FROM bag_invent a INNER JOIN objects b ON b.id=a.object_id WHERE object_id=%d LIMIT 1", objects_str, th_owner_id);
				res = mysql_query(gMysql, request);
				cache_get_data(rows, fields, gMysql);
				if(rows > 0)
				{
				    strdel(objects_str, 0, sizeof(objects_str)-1);
					pl_owner_id = cache_get_field_content_int(0, "pl_owner", gMysql);
				    for(i = 0; i < MAX_INVENTORY_IN_BAG; ++i)
				    {
						cache_set_active(res, gMysql);
					    strdel(col_name, 0, sizeof(col_name)-1);
						format(col_name, sizeof(col_name), "inv%d", i+1);
				        invent_object_id = cache_get_field_content_int(0, col_name, gMysql);
				        if(object_id == invent_object_id)
				        {
				            strdel(buff_str, 0, sizeof(buff_str)-1);
				            format(buff_str, sizeof(buff_str), "%s%s=-1", (strlen(objects_str)>0)?(","):(""), col_name);
				            strcat(objects_str, buff_str);

							for(playerid = 0; playerid < MAX_PLAYERS; ++playerid)
							{
							    if(gPlayersID[playerid] == pl_owner_id && gBag[playerid][1] > 0)
							    {
							        zero_craft_item(gBagItem[playerid][i]);
							        break;
								}
							}
				        }
       				}
			        if(strlen(objects_str) > 0)
			        {
						mysql_format(gMysql, request, sizeof(request), "UPDATE bag_invent SET %s WHERE object_id=%d", objects_str, th_owner_id);
//						mysql_query(gMysql, request);
						thread_sql(request);
				    }
					//если объект расходуемый
					if(is_consumble == 1 && th_owner_id > 0)
					{
					    //отнимаем значение 'value' объекта от 'value' объекта-владельца
					    mysql_format(gMysql, request, sizeof(request), "UPDATE objects a, objects b, things c SET a.value=a.value-b.value WHERE a.id=%d AND b.id=%d AND a.thing_id=c.id AND c.is_inventory=1", th_owner_id, object_id);
						mysql_query(gMysql, request);
//						thread_sql(request);
					}
				}
			}
			//удаляем результат поиска
			if(cache_is_valid(res, gMysql))
				cache_delete(res);
		}
	}

	if(cache_is_valid(result, gMysql))
		cache_delete(result);

	mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET pl_owner_id=NULL,th_owner_id=NULL,is_dropped=NULL,last_time=0 WHERE id=%d", object_id);
//	mysql_query(gMysql, request);
	thread_sql(request);
}

public load_vehicles()
{
	new request[1024];
	new Float:x, Float:y, Float:z, Float:rotz, Float:add_rotz;
	new rows, fields, rows1, fields1, i, inworld_id, id, type_id, dot_id, def_value, is_vehicle;
	new Cache:result, Cache:coords;

	//начинаем расстановку
	//сперва загружаем и расставляем из objects всё, где dot_id IS NOT NULL (?)
    mysql_format(gMysql, request, sizeof(request), "SELECT a.id,c.placex,c.placey,c.placez,b.rotatable,c.id as dot_id,b.inworld_id,b.posx,b.posy,b.posz,b.def_value,b.is_vehicle FROM objects a INNER JOIN (things b, object_dot c) ON (a.dot_id=c.id AND a.thing_id=b.id) WHERE a.dot_id IS NOT NULL AND a.unused=0 AND b.is_vehicle=1");
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows > 0)
	{
//		dots = cache_save(gMysql);
		for(i = 0; i < rows; ++i)
		{
		    cache_set_active(result, gMysql);
			x = cache_get_field_content_float(i, "placex", gMysql);
			y = cache_get_field_content_float(i, "placey", gMysql);
			z = cache_get_field_content_float(i, "placez", gMysql);
			rotz = cache_get_field_content_float(i, "posz", gMysql);
			inworld_id = cache_get_field_content_int(i, "inworld_id", gMysql);
			id = cache_get_field_content_int(i, "id", gMysql);
			dot_id = cache_get_field_content_int(i, "dot_id", gMysql);
			def_value = cache_get_field_content_int(i, "def_value", gMysql);
			is_vehicle = cache_get_field_content_int(i, "is_vehicle", gMysql);

			if(is_vehicle == 1)
			{
			    create_new_vehicle(id, x, y, z, rotz, inworld_id, def_value);
			}
			else
			{
				continue;
			}

		    mysql_format(gMysql, request, sizeof(request), "UPDATE object_dot SET object_id=%d WHERE id=%d", id, dot_id);
			mysql_query(gMysql, request);
		}
//		if(cache_is_valid(dots, gMysql))
//			cache_delete(dots, gMysql);
	}
	if(cache_is_valid(result, gMysql))
		cache_delete(result);

	//расставляем перемещённые персонажами объекты
    mysql_format(gMysql, request, sizeof(request), "SELECT a.id,a.value,a.placex,a.placey,a.placez,a.add_rotx,a.add_roty,a.add_rotz,b.is_vehicle,b.rotatable,b.inworld_id,b.posx,b.posy,b.posz,b.height FROM objects a INNER JOIN things b ON a.thing_id=b.id WHERE a.dot_id IS NULL and a.pl_owner_id IS NULL and a.th_owner_id IS NULL and a.is_dropped IS NOT NULL AND a.unused=0 AND b.is_vehicle=1");
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows > 0)
	{
		for(i = 0; i < rows; ++i)
		{
		    cache_set_active(result, gMysql);
			x = cache_get_field_content_float(i, "placex", gMysql);
			y = cache_get_field_content_float(i, "placey", gMysql);
			z = cache_get_field_content_float(i, "placez", gMysql);
			add_rotz = cache_get_field_content_float(i, "add_rotz", gMysql);
			inworld_id = cache_get_field_content_int(i, "inworld_id", gMysql);
			id = cache_get_field_content_int(i, "id", gMysql);
			is_vehicle = cache_get_field_content_int(i, "is_vehicle", gMysql);

			if(is_vehicle == 1)
			{
			    create_old_vehicle(id, x, y, z, add_rotz, inworld_id);
			}
			else
			{
				continue;
			}
		}
	}
	if(cache_is_valid(result, gMysql))
		cache_delete(result);

	//затем расставляем свободные/новые объекты на свободные места
    mysql_format(gMysql, request, sizeof(request), "SELECT a.id,IFNULL(a.prev_id,0) as prev_id,b.is_vehicle,b.inworld_id,b.posx,b.posy,b.posz,b.height,b.type_id,b.rotatable,b.def_value FROM objects a INNER JOIN things b ON a.thing_id=b.id WHERE a.dot_id IS NULL AND a.pl_owner_id IS NULL AND a.th_owner_id IS NULL AND a.is_dropped IS NULL AND a.unused=0 AND b.is_vehicle=1 ORDER BY RAND()");
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows > 0)
	{
		for(i = 0; i < rows; ++i)
		{
		    cache_set_active(result, gMysql);
			rotz = cache_get_field_content_float(i, "posz", gMysql);
			inworld_id = cache_get_field_content_int(i, "inworld_id", gMysql);
			id = cache_get_field_content_int(i, "id", gMysql);
			type_id = cache_get_field_content_int(i, "type_id", gMysql);
			def_value = cache_get_field_content_int(i, "def_value", gMysql);
			is_vehicle = cache_get_field_content_int(i, "is_vehicle", gMysql);

			//получаем свободное место
		    mysql_format(gMysql, request, sizeof(request), "SELECT a.id,a.placex,a.placey,a.placez FROM object_dot a INNER JOIN dot_type b ON a.id=b.dot_id WHERE a.object_id IS NULL and b.type_id=%d ORDER BY last_time,RAND() LIMIT 1", type_id);
			coords = mysql_query(gMysql, request);
			cache_get_data(rows1, fields1, gMysql);
			if(rows1 <= 0)
			{
			    continue;
			}
			else
			{
				cache_set_active(coords, gMysql);
				x = cache_get_field_content_float(0, "placex", gMysql);
				y = cache_get_field_content_float(0, "placey", gMysql);
				z = cache_get_field_content_float(0, "placez", gMysql);
				dot_id = cache_get_field_content_int(0, "id", gMysql);

				//расставляем
				if(is_vehicle == 1)
				{
					//не забыть: освобождая вещи от владельцев, очищать и список инвентаря транспортных средств
					//...
					create_new_vehicle(id, x, y, z, rotz, inworld_id, def_value);
				    mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET dot_id=%d WHERE id=%d", dot_id, id);
					mysql_query(gMysql, request);
				}
				else
				{
					continue;
				}

				//время (last_time) здесь не должно редактироваться! (?)
				//mysql_format(gMysql, request, sizeof(request), "UPDATE object_dot SET object_id=%d WHERE id=%d", id, dot_id);
			    mysql_format(gMysql, request, sizeof(request), "UPDATE object_dot SET object_id=%d,last_time=now() WHERE id=%d", id, dot_id);
				mysql_query(gMysql, request);
			}
			if(cache_is_valid(coords, gMysql))
				cache_delete(coords);
		}
	}
	if(cache_is_valid(result, gMysql))
		cache_delete(result);
}

//расставляем ворота
public load_gates(door_type[])
{
	new request[512];
	new Float:x, Float:y, Float:z, Float:rotx, Float:roty, Float:rotz;
	new rows, fields, i, inworld_id, id, obj_id, fis_opened;
	new Cache:result;

	//расставляем перемещённые персонажами объекты
    mysql_format(gMysql, request, sizeof(request), "SELECT a.id,b.inworld_id,a.th_owner_id,a.placex,a.placey,a.placez,a.add_rotx,a.add_roty,a.add_rotz,d.placex as x,d.placey as y,d.placez as z,d.add_rotx as rx,d.add_roty as ry,d.add_rotz as rz FROM objects a INNER JOIN (things b, thing_type c, objects d) ON (a.thing_id=b.id AND b.type_id=c.id AND a.owner=d.id) WHERE a.is_dropped IS NOT NULL AND b.is_inventory=-1 AND a.owner>0 AND c.name=\"%s\"", door_type);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows > 0)
	{
		for(i = 0; i < rows; ++i)
		{
		    cache_set_active(result, gMysql);
			fis_opened = cache_get_field_content_int(i, "th_owner_id", gMysql);
		    if(fis_opened==0)
		    {
				x = cache_get_field_content_float(i, "placex", gMysql);
				y = cache_get_field_content_float(i, "placey", gMysql);
				z = cache_get_field_content_float(i, "placez", gMysql);
				rotx = cache_get_field_content_float(i, "add_rotx", gMysql);
				roty = cache_get_field_content_float(i, "add_roty", gMysql);
				rotz = cache_get_field_content_float(i, "add_rotz", gMysql);
			}
			else
			{
				x = cache_get_field_content_float(i, "x", gMysql);
				y = cache_get_field_content_float(i, "y", gMysql);
				z = cache_get_field_content_float(i, "z", gMysql);
				rotx = cache_get_field_content_float(i, "rx", gMysql);
				roty = cache_get_field_content_float(i, "ry", gMysql);
				rotz = cache_get_field_content_float(i, "rz", gMysql);
			}
			inworld_id = cache_get_field_content_int(i, "inworld_id", gMysql);
			id = cache_get_field_content_int(i, "id", gMysql);

			//сохраняем для объектов координаты персонажа и разницу высот
			obj_id = CreateDynamicObject(inworld_id,x,y,z,rotx,roty,rotz,-1,-1,-1,500.0,800.0);
			if(obj_id == INVALID_OBJECT_ID)
				printf("error load_gates: can not create object, db_id=%d", id);
			mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET obj_id=%d WHERE id=%d", obj_id, id);
			mysql_query(gMysql, request);
		}
	}
	if(cache_is_valid(result, gMysql))
		cache_delete(result);
}

public set_new_objects_on_places()
{
	new request[1024];
	// new i;

	// //обнулим кэш
	// for(i = 0; i < sizeof(gPreviousDotID); ++i)
	// {
		// gPreviousDotID[i] = 0;
	// }

	//расставляем свободные/новые объекты на свободные места
    mysql_format(gMysql, request, sizeof(request), "SELECT a.id,IFNULL(a.prev_id,0) as prev_id,b.is_vehicle,b.inworld_id,b.posx,b.posy,b.posz,b.height,b.type_id,b.rotatable,b.def_value FROM objects a INNER JOIN things b ON a.thing_id=b.id WHERE a.dot_id IS NULL AND a.pl_owner_id IS NULL AND a.th_owner_id IS NULL AND a.is_dropped IS NULL AND a.unused=0 AND b.is_inventory>=0 ORDER BY RAND()");
	mysql_tquery(gMysql, request, "set_new_objects_on_places_th");
}

public set_new_objects_on_places_th()
{
	new request[512];
	new Float:rotx, Float:roty, Float:rotz, Float:height;
	new inworld_id, id, type_id, def_value, is_vehicle;
	new rotatable, prev_id;
	new i, rows, fields, rows_dots, fields_dots;
	new Cache:dots;

	new Float:x, Float:y, Float:z;
	new Float:add_rotx, Float:add_roty, Float:Z_coord, Float:Alpha, Float:Beta;
	new res, main_thing_id, ret, dot_index, obj_id, dot_id;
	new Cache:coords;	

	dots = cache_save(gMysql);
	cache_get_data(rows, fields, gMysql);
	if(rows > 0)
	{
		for(i = 0; i < rows; ++i)
		{
		    cache_set_active(dots, gMysql);
			rotx = cache_get_field_content_float(i, "posx", gMysql);
			roty = cache_get_field_content_float(i, "posy", gMysql);
			rotz = cache_get_field_content_float(i, "posz", gMysql);
			rotatable = cache_get_field_content_int(i, "rotatable", gMysql);
			inworld_id = cache_get_field_content_int(i, "inworld_id", gMysql);
			height = cache_get_field_content_float(i, "height", gMysql);
			id = cache_get_field_content_int(i, "id", gMysql);
			type_id = cache_get_field_content_int(i, "type_id", gMysql);
			def_value = cache_get_field_content_int(i, "def_value", gMysql);
			is_vehicle = cache_get_field_content_int(i, "is_vehicle", gMysql);
			prev_id = cache_get_field_content_int(i, "prev_id", gMysql);

			//получаем свободное место
		    mysql_format(gMysql, request, sizeof(request), "SELECT a.id,a.placex,a.placey,a.placez FROM object_dot a INNER JOIN dot_type b ON a.id=b.dot_id WHERE a.object_id IS NULL AND b.type_id=%d ORDER BY last_time,RAND() LIMIT 1", type_id);
			coords = mysql_query(gMysql, request);

//			mysql_tquery(gMysql, request, "set_new_objects_on_places_th_t","fffddfddddd",rotx,roty,rotz,rotatable,inworld_id,height,id,type_id,def_value,is_vehicle,prev_id);
	// }
// }
// if(cache_is_valid(dots, gMysql))
	// cache_delete(dots, gMysql);	
//}

//public set_new_objects_on_places_th_t(Float:rotx,Float:roty,Float:rotz,rotatable,inworld_id,Float:height,id,type_id,def_value,is_vehicle,prev_id)
//{
	// new request[512];
	// new Float:x, Float:y, Float:z;
	// new Float:add_rotx, Float:add_roty, Float:Z_coord, Float:Alpha, Float:Beta;
	// new i, rows_dots, fields_dots, obj_id, dot_id;
	// new res, main_thing_id, ret, dot_index;
	// new Cache:coords;
	
	// coords = cache_save(gMysql);
			cache_get_data(rows_dots, fields_dots, gMysql);
			if(rows_dots <= 0)
			{
				if(cache_is_valid(coords, gMysql))
					cache_delete(coords, gMysql);			
				continue;
//				return;
			}
			else
			{
				for(dot_index = 0; dot_index < rows_dots; ++dot_index)
				{
//					cache_set_active(coords, gMysql);
					x = cache_get_field_content_float(dot_index, "placex", gMysql);
					y = cache_get_field_content_float(dot_index, "placey", gMysql);
					z = cache_get_field_content_float(dot_index, "placez", gMysql);
					dot_id = cache_get_field_content_int(dot_index, "id", gMysql);

					// //проверяем, не занято ло уже место
					// for(i = 0; i < sizeof(gPreviousDotID); ++i)
					// {
						// if(gPreviousDotID[i] == dot_id)
							// continue;
					// }

					// //сдвигаем кэш
					// for(i = 0; i < sizeof(gPreviousDotID)-2; ++i) //2 для того, чтобы последним всегда был неиспользуемый id=0
					// {
						// gPreviousDotID[i] = gPreviousDotID[i+1];
					// }
					// gPreviousDotID[i] = dot_id; //неразрывно от предыдущего цикла!

					//время (last_time) здесь не должно редактироваться! (?)
					//mysql_format(gMysql, request, sizeof(request), "UPDATE object_dot SET object_id=%d WHERE id=%d", id, dot_id);
					mysql_format(gMysql, request, sizeof(request), "UPDATE object_dot SET object_id=%d,last_time=now() WHERE id=%d", id, dot_id);
					mysql_query(gMysql, request); //не иначе!

					//расставляем
					if(is_vehicle == 1)
					{
						//не забыть: освобождая вещи от владельцев, очищать и список инвентаря транспортных средств
						//...
						create_new_vehicle(id, x, y, z, rotz, inworld_id, def_value);
						mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET dot_id=%d WHERE id=%d", dot_id, id);
			//			mysql_query(gMysql, request);
						thread_sql(request);
					}
					else
					{
						add_rotx = 0;
						add_roty = 0;
						if(rotatable)
						{
							Alpha = rotz;
							//получаем углы поворота
							ret = MapAndreas_Valid_Z_Coordinate(x,y,z,Z_coord,Alpha,Beta);
							if(ret == 0)
							{
								add_rotx = Beta;
								add_roty = Alpha;
							}
							else
							{
								add_rotx = 0.001;
								add_roty = 0.001;
							}
						}
						if((rotatable == 1) && (ret == 0))
						{
							obj_id = CreateObject(inworld_id, x, y, z+height, rotx+add_rotx, roty+add_roty, rotz, OBJECT_DISTANCE);
						}
						else
						{
							obj_id = CreateObject(inworld_id, x, y, z+height, rotx, roty, rotz, OBJECT_DISTANCE);
						}
						res = composit_thing(request, main_thing_id);
						if(obj_id == INVALID_OBJECT_ID)
							printf("error set_new_objects_on_places_th: can not create object, db_id=%d", id);
						if(res > 0 && main_thing_id > 0 && prev_id == 0) //для устранения 'бесконечных' используемых вещей
							mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET prev_id=%d,vector=%f,placex=%f,placey=%f,placez=%f,add_rotx=%f,add_roty=%f,obj_id=%d,dot_id=%d,pl_owner_id=NULL,th_owner_id=NULL,value=%d WHERE id=%d", main_thing_id, VectorSize(x,y,z), x, y, z, add_rotx, add_roty, obj_id, dot_id, def_value, id);
						else
							mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET vector=%f,placex=%f,placey=%f,placez=%f,add_rotx=%f,add_roty=%f,obj_id=%d,dot_id=%d,pl_owner_id=NULL,th_owner_id=NULL,value=%d WHERE id=%d", VectorSize(x,y,z), x, y, z, add_rotx, add_roty, obj_id, dot_id, def_value, id);
			//					mysql_query(gMysql, request);
						thread_sql(request);
					}
					break;
				}
			}
			if(cache_is_valid(coords, gMysql))
				cache_delete(coords, gMysql);
		}
	}
	if(cache_is_valid(dots, gMysql))
		cache_delete(dots, gMysql);				
}

public unset_objects_on_places(playerid, Float:range)
{
	new request[512];
	new rows, fields;
	new i, object_id;
	new Float:x, Float:y, Float:z;
	new Float:placex, Float:placey, Float:placez;
	new Cache:result;
	new Float:vector, Float:distance;
	
	if(range <= 0)
		range = 5.0;

	GetPlayerPos(playerid, x, y, z);

	vector = VectorSize(x, y, z);
    mysql_format(gMysql, request, sizeof(request), "SELECT a.id,a.placex,a.placey,a.placez,b.is_inventory FROM objects a INNER JOIN things b ON a.thing_id=b.id WHERE a.vector IS NOT NULL AND ABS(a.vector-%f)<%f AND b.is_inventory>=0 LIMIT 500",vector,range);

	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);

	if(rows <= 0)
	{
		if(cache_is_valid(result, gMysql))
			cache_delete(result);
	    return;
	}
	
	for(i = 0; i < rows; ++i)
	{
	    cache_set_active(result, gMysql);
	    
		placex = cache_get_field_content_float(i, "placex", gMysql);
		placey = cache_get_field_content_float(i, "placey", gMysql);
		placez = cache_get_field_content_float(i, "placez", gMysql);
		object_id = cache_get_field_content_int(i, "id", gMysql);

		distance = VectorSize(placex-x, placey-y, placez-z);

	    if(distance < range)
			free_object_from_owner(object_id);
	}

	if(cache_is_valid(result, gMysql))
		cache_delete(result);
}

//удалить объекты в заданном радиусе от указанной координаты
public unset_objects_on_places_xyz(Float:x, Float:y, Float:z, Float:range)
{
	new request[512];
	new Float:vector;

	if(range <= 0)
		range = 5.0;

	vector = VectorSize(x, y, z);
    mysql_format(gMysql, request, sizeof(request), "SELECT a.id,a.placex,a.placey,a.placez,b.is_inventory FROM objects a INNER JOIN things b ON a.thing_id=b.id WHERE a.vector IS NOT NULL AND ABS(a.vector-%f)<%f AND ABS(placex-%f)<%f AND b.is_inventory>=0 LIMIT 100",vector,range,x,range);
	mysql_tquery(gMysql, request, "unset_objects_on_places_xyz_t", "ffff", x, y, z, range);
}

public unset_objects_on_places_xyz_t(Float:x, Float:y, Float:z, Float:range)
{
	new rows, fields;
	new i, object_id;
	new Float:placex, Float:placey, Float:placez;
	new Cache:result;
	new Float:distance;
	
	result = cache_save(gMysql);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
	{
		if(cache_is_valid(result, gMysql))
			cache_delete(result);
	    return;
	}

	for(i = 0; i < rows; ++i)
	{
	    cache_set_active(result, gMysql);

		placex = cache_get_field_content_float(i, "placex", gMysql);
		placey = cache_get_field_content_float(i, "placey", gMysql);
		placez = cache_get_field_content_float(i, "placez", gMysql);
		object_id = cache_get_field_content_int(i, "id", gMysql);

		distance = VectorSize(placex-x, placey-y, placez-z);

	    if(distance < range)
			full_free_object_from_owner(object_id);
	}
}

//удаление всех авто из игры
public destroy_vehicles()
{
	new request[256];
	new obj_id, id, rows, fields, i, is_vehicle;
	new Cache:objs;

    mysql_format(gMysql, request, sizeof(request), "SELECT a.id,IFNULL(a.obj_id,%d) as obj_id,b.is_vehicle FROM objects a INNER JOIN things b ON a.thing_id=b.id WHERE obj_id IS NOT NULL AND b.is_vehicle=1", INVALID_OBJECT_ID);
	objs = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows > 0)
	{
		for(i = 0; i < rows; ++i)
		{
		    cache_set_active(objs, gMysql);
			obj_id = cache_get_field_content_int(i, "obj_id", gMysql);
			id = cache_get_field_content_int(i, "id", gMysql);
			is_vehicle = cache_get_field_content_int(i, "is_vehicle", gMysql);

			if(is_vehicle == 1)
			{
			    //а вот тута сохраняем количество оставшегося топлива
			    if(obj_id <= MAX_VEHICLES && gVeh[obj_id][4] == 1) //если двигатель не заглушен
				{
					save_vehicle_state(INVALID_PLAYER_ID, obj_id);
				}
			}
		    mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET obj_id=NULL,pl_owner_id=NULL,th_owner_id=NULL WHERE id=%d", id);
			mysql_query(gMysql, request);
		}
	}
	if(cache_is_valid(objs, gMysql))
		cache_delete(objs, gMysql);

	//удаляем все модели авто
	for(i = 0; i < MAX_VEHICLES; ++i)
	{
//	    if(i != INVALID_VEHICLE_ID)
			DestroyVehicle(i);
	}
}

//удаляем все ворота
public destroy_gates(door_type[])
{
	new request[256];
	new obj_id, id, rows, fields, i;
	new Cache:objs;

    mysql_format(gMysql, request, sizeof(request), "SELECT a.id,IFNULL(a.obj_id,%d) as obj_id FROM objects a INNER JOIN (things b, thing_type c) ON (a.thing_id=b.id AND b.type_id=c.id) WHERE obj_id IS NOT NULL AND owner IS NOT NULL AND c.name=\"%s\"", INVALID_OBJECT_ID, door_type);
	objs = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows > 0)
	{
		for(i = 0; i < rows; ++i)
		{
		    cache_set_active(objs, gMysql);
			obj_id = cache_get_field_content_int(i, "obj_id", gMysql);
			id = cache_get_field_content_int(i, "id", gMysql);

		    if(IsValidObject(obj_id))
				DestroyObject(obj_id);
		    mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET obj_id=NULL WHERE id=%d", id);
			mysql_query(gMysql, request);
		}
	}
	if(cache_is_valid(objs, gMysql))
		cache_delete(objs, gMysql);
}

//создать кэш вещей, лежащих рядом с игроком, и вызвать некоторую функцию
public find_and_cache_objects(playerid, Float:range)
{
	new i, j;
	new Float:x, Float:y, Float:z, Float:vector;
	new part_one[512], request[2048];

	GetPlayerPos(playerid, x, y, z);

	for(i = 0; i < MAX_INVENTORY_ON_GROUND; ++i)
	{
		zero_craft_item(gGroundItem[playerid][i]);
	}

	//если игрок находится в зоне уже созданного кэша - новый не создаётся
	//зоной считается область, зависящая от половины максимального радиуса разброса вещей при выкладывании
	if(VectorSize(gCachedPlayers[playerid][cached_player_pos][f_X]-x, gCachedPlayers[playerid][cached_player_pos][f_Y]-y, gCachedPlayers[playerid][cached_player_pos][f_Z]-z) < floatsub(gCachedPlayers[playerid][cached_range],(floatadd(gStandartRangeValue,3.0))))
	{
		if(gObjectsMenuShow[playerid] > 0)
		{
			for(i = 0, j = 0; (i < CACHED_OBJECTS_COUNT) && (j < MAX_INVENTORY_ON_GROUND); ++i)
			{
				if(gCachedItems[playerid][i][db_id] > 0 && VectorSize(gCachedItems[playerid][i][obj_coord][f_X]-x, gCachedItems[playerid][i][obj_coord][f_Y]-y, gCachedItems[playerid][i][obj_coord][f_Z]-z) < gStandartRangeValue)
				{
					copy_craft_item(gGroundItem[playerid][j], gCachedItems[playerid][i]);
					j++;
				}
			}
			create_views_of_items(playerid, -1, -1, GROUND_AREA);
		}
		return 2;
	}

	vector = VectorSize(x, y, z);

	format(part_one, sizeof(part_one), "SELECT a.id as db_id,b.id as tp_id,IFNULL(a.prev_id,0) as pr_id,b.invent_id as inv_id,b.inworld_id as gnd_id,b.rotx as isrotx,b.roty as isroty,b.rotz as isrotz,b.inventx as degx,b.inventy as degy,b.inventz as degz,b.zoom,b.rotatable,b.posx as addx,b.posy as addy");
	mysql_format(gMysql, request, sizeof(request), "%s,b.posz as addz,b.height,b.is_auto,IFNULL(a.obj_id,%d) as obj_id,b.is_inventory,a.value,IFNULL(a.owner,0) as owner_id,IFNULL(a.placex,0) as placex,IFNULL(a.placey,0) as placey,IFNULL(a.placez,0) as placez FROM objects a,things b WHERE a.placex IS NOT NULL AND a.thing_id=b.id AND ABS(a.vector-%f)<%f AND ABS(placex-%f)<%f AND ABS(placey-%f)<%f AND ABS(placez-%f)<%f LIMIT 1024",part_one,INVALID_OBJECT_ID,vector,range,x,range,y,range,z,range);
	mysql_tquery(gMysql, request, "find_and_cache_objects_t", "dffff", playerid, range, x, y, z);

	return 1;
}

public find_and_cache_objects_t(playerid, Float:range, Float:player_x, Float:player_y, Float:player_z)
{
	new i, j;
	new Float:x, Float:y, Float:z;
	new rows, fields;
	new Cache:result;

	for(i = 0; i < CACHED_OBJECTS_COUNT; ++i)
	{
		zero_craft_item(gCachedItems[playerid][i]);
	}
	for(i = 0; i < MAX_INVENTORY_ON_GROUND; ++i)
	{
		zero_craft_item(gGroundItem[playerid][i]);
	}

	result = cache_save(gMysql);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
	{
		if(cache_is_valid(result, gMysql))
			cache_delete(result);
	    return -1;
	}
	for(i = 0, j = 0; (i < rows) && (j < CACHED_OBJECTS_COUNT); ++i)
	{
		x = cache_get_field_content_int(i, "placex", gMysql);
		y = cache_get_field_content_int(i, "placey", gMysql);
		z = cache_get_field_content_int(i, "placez", gMysql);

		if(VectorSize(x-player_x, y-player_y, z-player_z) < range)
		{
			gCachedItems[playerid][j][db_id] = cache_get_field_content_int(i, "db_id", gMysql);
			gCachedItems[playerid][j][tp_id] = cache_get_field_content_int(i, "tp_id", gMysql);
			gCachedItems[playerid][j][pr_id] = cache_get_field_content_int(i, "pr_id", gMysql);
			gCachedItems[playerid][j][object] = cache_get_field_content_int(i, "obj_id", gMysql);
			gCachedItems[playerid][j][inv_id] = cache_get_field_content_int(i, "inv_id", gMysql);
			gCachedItems[playerid][j][gnd_id] = cache_get_field_content_int(i, "gnd_id", gMysql);
			gCachedItems[playerid][j][isrot][n_X] = cache_get_field_content_int(i, "isrotx", gMysql);
			gCachedItems[playerid][j][isrot][n_Y] = cache_get_field_content_int(i, "isroty", gMysql);
			gCachedItems[playerid][j][isrot][n_Z] = cache_get_field_content_int(i, "isrotz", gMysql);
			gCachedItems[playerid][j][deg][f_X] = cache_get_field_content_float(i, "degx", gMysql);
			gCachedItems[playerid][j][deg][f_Y] = cache_get_field_content_float(i, "degy", gMysql);
			gCachedItems[playerid][j][deg][f_Z] = cache_get_field_content_float(i, "degz", gMysql);
			gCachedItems[playerid][j][zoom] = cache_get_field_content_float(i, "zoom", gMysql);
			gCachedItems[playerid][j][obj_rotatable] = cache_get_field_content_int(i, "rotatable", gMysql);
			gCachedItems[playerid][j][rot][f_X] = cache_get_field_content_float(i, "addx", gMysql);
			gCachedItems[playerid][j][rot][f_Y] = cache_get_field_content_float(i, "addy", gMysql);
			gCachedItems[playerid][j][rot][f_Z] = cache_get_field_content_float(i, "addz", gMysql);
			gCachedItems[playerid][j][obj_height] = cache_get_field_content_float(i, "height", gMysql);
			gCachedItems[playerid][j][obj_owner] = cache_get_field_content_int(i, "owner_id", gMysql);
			gCachedItems[playerid][j][obj_auto] = cache_get_field_content_int(i, "is_auto", gMysql);
			gCachedItems[playerid][j][obj_inventory] = cache_get_field_content_int(i, "is_inventory", gMysql);
			gCachedItems[playerid][j][obj_value] = cache_get_field_content_int(i, "value", gMysql);
			gCachedItems[playerid][j][obj_coord][f_X] = x;
			gCachedItems[playerid][j][obj_coord][f_Y] = y;
			gCachedItems[playerid][j][obj_coord][f_Z] = z;
			j++;
		}
	}

	if(cache_is_valid(result, gMysql))
		cache_delete(result);

	gCachedPlayers[playerid][cached_player_pos][f_X] = player_x;
	gCachedPlayers[playerid][cached_player_pos][f_Y] = player_y;
	gCachedPlayers[playerid][cached_player_pos][f_Z] = player_z;
	gCachedPlayers[playerid][cached_range] = range;

	if(gObjectsMenuShow[playerid] > 0)
	{
		for(i = 0, j = 0; (i < CACHED_OBJECTS_COUNT) && (j < MAX_INVENTORY_ON_GROUND); ++i)
		{
			if(gCachedItems[playerid][i][db_id] > 0 && VectorSize(gCachedItems[playerid][i][obj_coord][f_X]-player_x, gCachedItems[playerid][i][obj_coord][f_Y]-player_y, gCachedItems[playerid][i][obj_coord][f_Z]-player_z) < gStandartRangeValue)
			{
				copy_craft_item(gGroundItem[playerid][j], gCachedItems[playerid][i]);
				j++;
			}
		}
		create_views_of_items(playerid, -1, -1, GROUND_AREA);
	}

	return 1;
}

//определить, лежит ли какой-нибудь объект в указанном радиусе от заданной точки
public is_any_object_in_range(playerid, Float:x, Float:y, Float:z, Float:range, Float:cache_distance, object_id)
{
	new request[256];
	new rows, fields;
	new i, id, ret_value;
	new Float:placex, Float:placey, Float:placez;
	new Float:obj_x, Float:obj_y, Float:obj_z;
	new Cache:result;
	new Float:vector, Float:distance;
	new need_cache;
	static sDistanceCache[MAX_PLAYERS][CACHED_OBJECTS_COUNT][CACHED_OBJECTS_DATA];

	//добавить в локальный кэш
	if(object_id != INVALID_OBJECT_ID)
	{
		for(i = 0; i < CACHED_OBJECTS_COUNT; ++i)
		{
			if(sDistanceCache[playerid][i][db_id] == INVALID_OBJECT_ID)
			{
				sDistanceCache[playerid][i][db_id] = object_id;
				sDistanceCache[playerid][i][obj_coord][f_X] = x;
				sDistanceCache[playerid][i][obj_coord][f_Y] = y;
				sDistanceCache[playerid][i][obj_coord][f_Z] = z;
				return 1;
			}
		}
	}

	ret_value = 0;

	//проверка, нужно ли кэшировать
	if( playerid != INVALID_PLAYER_ID )
	{
		GetPlayerPos(playerid, placex, placey, placez);
		if(VectorSize(placex-gCachedPlayers[playerid][cached_player_pos][f_X],
						   placey-gCachedPlayers[playerid][cached_player_pos][f_Y],
						   placez-gCachedPlayers[playerid][cached_player_pos][f_Z]) < (gCachedPlayers[playerid][cached_range]-(gStandartRangeValue+3.0)))
		{
			for(i = 0; i < CACHED_OBJECTS_COUNT; ++i)
			{
				sDistanceCache[playerid][i][db_id] = gCachedItems[playerid][i][db_id];
				sDistanceCache[playerid][i][obj_coord][f_X] = gCachedItems[playerid][i][obj_coord][f_X];
				sDistanceCache[playerid][i][obj_coord][f_Y] = gCachedItems[playerid][i][obj_coord][f_Y];
				sDistanceCache[playerid][i][obj_coord][f_Z] = gCachedItems[playerid][i][obj_coord][f_Z];
				//gPlayerPlacesXYZ[playerid][0] = gCachedPlayers[playerid][cached_player_pos][f_X];
				//gPlayerPlacesXYZ[playerid][1] = gCachedPlayers[playerid][cached_player_pos][f_Y];
			 	//gPlayerPlacesXYZ[playerid][2] = gCachedPlayers[playerid][cached_player_pos][f_Z];
			}
		    need_cache = 0;
		}
		else if(placex > floatsub(gPlayerPlacesXYZ[playerid][0],0.1) && placex < floatadd(gPlayerPlacesXYZ[playerid][0],0.1) &&
				placey > floatsub(gPlayerPlacesXYZ[playerid][1],0.1) && placey < floatadd(gPlayerPlacesXYZ[playerid][1],0.1) &&
				placez > floatsub(gPlayerPlacesXYZ[playerid][2],0.1) && placez < floatadd(gPlayerPlacesXYZ[playerid][2],0.1) )
				need_cache = 0;
		else
			need_cache = 1;
	}
	else
		need_cache = 1;

	if(need_cache == 1)
	{
		if(playerid != INVALID_PLAYER_ID)
			vector = VectorSize(placex, placey, placez);
		else
		{
			vector = VectorSize(x, y, z);
			placex = x;
			placey = y;
			placez = z;
		}
		mysql_format(gMysql, request, sizeof(request), "SELECT a.id,b.invent_id,a.placex,a.placey,a.placez FROM objects a INNER JOIN things b ON a.thing_id=b.id WHERE a.vector IS NOT NULL AND ABS(a.vector-%f)<%f AND b.is_inventory>=0 LIMIT 80",vector,range);
		result = mysql_query(gMysql, request);
		cache_get_data(rows, fields, gMysql);
		if(rows <= 0)
		{
			if(cache_is_valid(result, gMysql))
				cache_delete(result);
			return ret_value;
		}

		for(i = 0; i < CACHED_OBJECTS_COUNT; ++i)
		{
			sDistanceCache[playerid][i][db_id] = INVALID_OBJECT_ID;
			sDistanceCache[playerid][i][obj_coord][f_X] = 0.0;
			sDistanceCache[playerid][i][obj_coord][f_Y] = 0.0;
			sDistanceCache[playerid][i][obj_coord][f_Z] = 0.0;
		}

		for(i = 0; i < rows; ++i)
		{
			id = cache_get_field_content_int(i, "id", gMysql);
			obj_x = cache_get_field_content_float(i, "placex", gMysql);
			obj_y = cache_get_field_content_float(i, "placey", gMysql);
			obj_z = cache_get_field_content_float(i, "placez", gMysql);
			distance = VectorSize(placex-x, placey-y, placez-z);
			if(distance < cache_distance)
			{
				for(i = 0; i < CACHED_OBJECTS_COUNT; ++i)
				{
					if(sDistanceCache[playerid][i][db_id] == INVALID_OBJECT_ID)
					{
						sDistanceCache[playerid][i][db_id] = id;
						sDistanceCache[playerid][i][obj_coord][f_X] = obj_x;
						sDistanceCache[playerid][i][obj_coord][f_Y] = obj_y;
						sDistanceCache[playerid][i][obj_coord][f_Z] = obj_z;
						break;
					}
				}
			}
		}

		if(cache_is_valid(result, gMysql))
			cache_delete(result);
	}

	for(i = 0; i < CACHED_OBJECTS_COUNT; ++i)
	{
		if(sDistanceCache[playerid][i][db_id] != INVALID_OBJECT_ID)
		{
			distance = VectorSize(sDistanceCache[playerid][i][obj_coord][f_X]-x, sDistanceCache[playerid][i][obj_coord][f_Y]-y, sDistanceCache[playerid][i][obj_coord][f_Z]-z);
			if(distance < range)
			{
				ret_value = 1;
				break;
			}
		}
		else
			break;
	}

	return ret_value;
}

//положить объект в ячейку инвентаря
//этой функцией можно освобождать ячейку (передать object_id=-1)
//функция не доделана! Требуется инициализация остальных полей структуры gIventoryItem[playerid][cell]
public set_character_inventory_cell(playerid, cell, object_id, bool:init)
{
	new request[256];
	new item[CRAFT_ITEM];

	if(gPlayersID[playerid] <= 0)
	    return -1;

	//защита
	if(cell < 0 || cell >= MAX_INVENTORY_ON_PLAYER/* || (object_id != -1 && !init && gInventoryItem[playerid][cell][db_id] != -1)*/)
	    return -1;

	if(object_id == -1)
	{
		sub_item_from_global_cache(gInventoryItem[playerid][cell]);
		//освобождаем ячейку
	    mysql_format(gMysql, request, sizeof(request), "UPDATE inventory SET inv%d=-1 WHERE player_id=%d",cell+1,gPlayersID[playerid]);
		thread_sql(request);
		if(init)
		    zero_craft_item(gInventoryItem[playerid][cell]);
	    return -1;
	}

	if(init)
	{
		if(init_craft_item(item, object_id) < 0)
		{
			//освобождаем ячейку
		    mysql_format(gMysql, request, sizeof(request), "UPDATE inventory SET inv%d=-1 WHERE player_id=%d",cell+1,gPlayersID[playerid]);
			mysql_query(gMysql, request);
		    zero_craft_item(gInventoryItem[playerid][cell]);
		    return -1;
		}
		if(item[obj_owner] != 0 && item[obj_owner] != gPlayersID[playerid])
		    return -5; //чужая вещь!
		if(item[obj_inventory] == 0) //тут надо бы выкидывать объект
		    return -3;
		//не даём взять второй рюкзак
		if(item[obj_inventory] == 2 && gBag[playerid][1] > 0)
		    return -2;
		copy_craft_item(gInventoryItem[playerid][cell], item);
	}

	if(gInventoryItem[playerid][cell][obj_inventory] == 2) //если это рюкзак
	{
	    gBag[playerid][0] = gInventoryItem[playerid][cell][obj_value];
	    gBag[playerid][1] = object_id;
		if(gBag[playerid][0] > MAX_INVENTORY_IN_BAG)
		    gBag[playerid][0] = MAX_INVENTORY_IN_BAG;
		if(gBag[playerid][0] < 0)
		    gBag[playerid][0] = 0;
	}

	//поскольку работаем с инвентарём игрока, обращаемся непосредственно к gInventoryItem
	if(gInventoryItem[playerid][cell][object] != INVALID_OBJECT_ID)
	{
		if(IsValidObject(gInventoryItem[playerid][cell][object]))
			DestroyObject(gInventoryItem[playerid][cell][object]);
	    gInventoryItem[playerid][cell][object] = INVALID_OBJECT_ID;
	}

	//занимаем ячейку
    mysql_format(gMysql, request, sizeof(request), "UPDATE inventory SET inv%d=%d WHERE player_id=%d",cell+1,object_id,gPlayersID[playerid]);
	//mysql_query(gMysql, request);
	thread_sql(request);

	//оптимизация!
	//объединить раздельные UPDATE-ы в один (это возможно)
	//...

	//указываем вледельца для объекта и обнуляем поле игрового объекта, точки появления объекта и флаг неиспользования объекта
	//если объект до этого принадлежал другому персонажу, сохраняем id прежнего владельца
    mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET vector=NULL,placex=NULL,placey=NULL,placez=NULL,add_rotx=0,add_roty=0,add_rotz=0,pl_owner_id=%d,th_owner_id=NULL,obj_id=NULL,dot_id=NULL,unused=0 WHERE id=%d",gPlayersID[playerid],object_id);
	mysql_query(gMysql, request);

	//обНУЛЛяем объект для точки появления и обновляем время обновления точки
    mysql_format(gMysql, request, sizeof(request), "UPDATE object_dot SET object_id=NULL,last_time=now() WHERE object_id=%d",object_id);
	thread_sql(request);

	gPlayerPlacesXYZ[playerid][0] = 0.0; //сбрасываем
	gPlayerPlacesXYZ[playerid][1] = 0.0; //координаты
	gPlayerPlacesXYZ[playerid][2] = 0.0; //персонажа
	gPlayerPlaces[playerid] = 1; //сбрасываем флаг итерации

	sub_item_from_global_cache(gInventoryItem[playerid][cell]);
	
	return 1;
}

//положить объект в ячейку инвентаря транспорта
//этой функцией можно освобождать ячейку (передать object_id=-1)
public set_vehicle_inventory_cell(vehicleid, cell, object_id, bool:init)
{
	new request[256];
	new item[CRAFT_ITEM];

	//защита
	if(cell < 0)
	    return -1;

	if(object_id == -1)
	{
		sub_item_from_global_cache(gVehicleItem[vehicleid][cell]);
		//освобождаем ячейку
	    mysql_format(gMysql, request, sizeof(request), "UPDATE veh_invent SET inv%d=-1 WHERE object_id=%d",cell+1,gVeh[vehicleid][0]);
		thread_sql(request);
		if(init)
		    zero_craft_item(gVehicleItem[vehicleid][cell]);
	    return -2;
	}

	if(init)
	{
		if(init_craft_item(item, object_id) < 0)
		{
			//освобождаем ячейку
		    mysql_format(gMysql, request, sizeof(request), "UPDATE veh_invent SET inv%d=-1 WHERE object_id=%d",cell+1,gVeh[vehicleid][0]);
			mysql_query(gMysql, request);
		    zero_craft_item(gVehicleItem[vehicleid][cell]);
		    return -1;
		}
//		if(item[obj_inventory] == 0) //тут надо бы выкидывать объект
//		    return -3;
		copy_craft_item(gVehicleItem[vehicleid][cell], item);
	}

	if(gVehicleItem[vehicleid][cell][object] != INVALID_OBJECT_ID)
	{
		if(IsValidObject(gVehicleItem[vehicleid][cell][object]))
			DestroyObject(gVehicleItem[vehicleid][cell][object]);
	    gVehicleItem[vehicleid][cell][object] = INVALID_OBJECT_ID;
	}

	//занимаем ячейку
    mysql_format(gMysql, request, sizeof(request), "UPDATE veh_invent SET inv%d=%d WHERE object_id=%d",cell+1,object_id,gVeh[vehicleid][0]);
	thread_sql(request);

	//указываем вледельца для объекта и обнуляем поле игрового объекта, точки появления объекта и флаг неиспользования объекта
	//если объект до этого принадлежал другому персонажу, сохраняем id прежнего владельца
    mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET vector=NULL,placex=NULL,placey=NULL,placez=NULL,add_rotx=0,add_roty=0,add_rotz=0,pl_owner_id=NULL,th_owner_id=%d,obj_id=NULL,dot_id=NULL,unused=0 WHERE id=%d",gVeh[vehicleid][0],object_id);
	mysql_query(gMysql, request);

	//обНУЛЛяем объект для точки появления и обновляем время обновления точки
    mysql_format(gMysql, request, sizeof(request), "UPDATE object_dot SET object_id=NULL,last_time=now() WHERE object_id=%d",object_id);
	thread_sql(request);

	sub_item_from_global_cache(gVehicleItem[vehicleid][cell]);
	
	return 1;
}

//положить объект в ячейку инвентаря рюкзака
//этой функцией можно освобождать ячейку (передать object_id=-1)
//object_id - это id объекта, когда init=true и индекс ячейки когда init=false
public set_bag_inventory_cell(playerid, cell, object_id, bool:init)
{
	new request[256];
	new item[CRAFT_ITEM];
	new id;

	if(gPlayersID[playerid] <= 0)
	    return -255;

	//защита
	if(cell < 0)
	    return -15;

	if(gBag[playerid][0] <= 0 || gBag[playerid][1] <= 0)
	    return -16;

	if(object_id == -1)
	{
//		add_item_from_global_cache(gBagItem[playerid][cell]);
	    mysql_format(gMysql, request, sizeof(request), "UPDATE bag_invent SET inv%d=-1 WHERE object_id=%d",cell+1,gBag[playerid][1]);
		thread_sql(request);
	    if(init)
	        zero_craft_item(gBagItem[playerid][cell]);
	    return -17;
	}

	if(init)
	{
	    if(init_craft_item(item, object_id) < 0)
	    {
			//освобождаем ячейку
		    mysql_format(gMysql, request, sizeof(request), "UPDATE inventory SET inv%d=-1 WHERE player_id=%d",cell+1,gPlayersID[playerid]);
			mysql_query(gMysql, request);
		    zero_craft_item(gBagItem[playerid][cell]);
		    return -1;
		}
		copy_craft_item(gBagItem[playerid][cell], item);
	}
	else
		copy_craft_item(item, gGroundItem[playerid][object_id]);

	if(item[obj_owner] != 0 && item[obj_owner] != gPlayersID[playerid])
	    return -5; //чужая вещь!
	if(item[obj_inventory] == 0) //тут надо бы выкидывать объект
	    return -3;
	//не даём положить рюкзак в рюкзак
	if(item[obj_inventory] == 2)
	    return -2;

	//поскольку работаем с инвентарём игрока, обращаемся непосредственно к gBagItem
	if(item[object] != INVALID_OBJECT_ID)
	{
		if(IsValidObject(item[object]))
			DestroyObject(item[object]);
	    //сбрасываем id объекта в стримере
	    item[object] = INVALID_OBJECT_ID;
	}

	if(init)
	    id = object_id;
	else
	    id = gGroundItem[playerid][object_id][db_id];

	//занимаем ячейку
	if(object_id > 0)
	    mysql_format(gMysql, request, sizeof(request), "UPDATE bag_invent a,objects b,things c SET a.inv%d=%d WHERE a.object_id=%d AND b.id=%d AND b.thing_id=c.id AND c.is_inventory=1",cell+1,id,gBag[playerid][1],id);
	else
	    mysql_format(gMysql, request, sizeof(request), "UPDATE bag_invent SET inv%d=%d WHERE object_id=%d",cell+1,id,gBag[playerid][1]);
	thread_sql(request);

	//указываем вледельца для объекта и обнуляем поле игрового объекта, точки появления объекта и флаг неиспользования объекта
	//если объект до этого принадлежал другому персонажу, сохраняем id прежнего владельца
    mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET vector=NULL,placex=NULL,placey=NULL,placez=NULL,add_rotx=0,add_roty=0,add_rotz=0,pl_owner_id=NULL,th_owner_id=%d,obj_id=NULL,dot_id=NULL,unused=0 WHERE id=%d",gBag[playerid][1],id);
	mysql_query(gMysql, request);

	//обНУЛЛяем объект для точки появления и обновляем время обновления точки
    mysql_format(gMysql, request, sizeof(request), "UPDATE object_dot SET object_id=NULL,last_time=now() WHERE object_id=%d",id);
	thread_sql(request);

	gPlayerPlacesXYZ[playerid][0] = 0.0; //сбрасываем
	gPlayerPlacesXYZ[playerid][1] = 0.0; //координаты
	gPlayerPlacesXYZ[playerid][2] = 0.0; //персонажа
	gPlayerPlaces[playerid] = 1; //сбрасываем флаг итерации

	sub_item_from_global_cache(item);
		
	return 1;
}

//разместить вещь рядом с игроком
stock post_item(playerid, vehicleid, inv[CRAFT_ITEM], obj_cell, Float:x, Float:y, Float:z)
{
	new request[432];
	new modelid, rotatable;
	new Float:Z_coord, Float:ang, Float:old_ang, Float:dx, Float:dy;
	new Float:dx1, Float:dy1, Float:Z_coord1;
	new Float:dx2, Float:dy2, Float:Z_coord2;
	new Float:Alpha, Float:Beta, Float:Alpha1, Float:Beta1, Float:Alpha2, Float:Beta2;
	new Float:rotx, Float:roty, Float:rotz;
	new Float:height;
	new obj_id, ret, is_any, iteration, found, id;
	new bool:flag;
	new Float:iter_val;
	new Float:distance;

#if defined DEBUG
	new opsDebug0, opsDebug1, opsDebug2;
	opsDebug1 = opsDebug2 = opsDebug0 = GetTickCount();
#endif
	
	if(inv[db_id] == -1 || inv[gnd_id] == -1)
		return INVALID_OBJECT_ID;
	
	rotx = inv[rot][f_X];
	roty = inv[rot][f_Y];
	rotz = inv[rot][f_Z];
	height = inv[obj_height];
	modelid = inv[gnd_id];
	rotatable = inv[obj_rotatable];
	id = inv[db_id];

	//если объект - оружие в руках, то сохраняем количество патронов и убираем из рук
	if(playerid != INVALID_PLAYER_ID && id == gPlayerWeapon[playerid][0])
	{
	    //сохраняем количество патронов
	    save_character_ammo(playerid, -1, -1);

	    //убираем оружие из рук
	    ResetPlayerWeapons(playerid);
	    gPlayerWeapon[playerid][0] = 0;
	    gPlayerWeapon[playerid][1] = 0;
	    gPlayerWeapon[playerid][2] = 0;
	    gPlayerWeapon[playerid][3] = 0;
	}

//	GetPlayerPos(playerid, x, y, z);
	if((playerid != INVALID_PLAYER_ID && IsPlayerInAnyVehicle(playerid)) || vehicleid != INVALID_VEHICLE_ID)
	{
		distance = DROP_DISTANCE_FROM_PLAYER + 3.0;
	}
	else
	{
		distance = DROP_DISTANCE_FROM_PLAYER;
	}
	
	if(playerid != INVALID_PLAYER_ID)
		GetPlayerFacingAngle(playerid, ang);
	else if(vehicleid == INVALID_VEHICLE_ID)
		GetVehicleZAngle(vehicleid, ang);
	else
	    ang = 0.0;

	ang = floatdiv(floatmul(floatadd(ang,90.0),3.14), 180.0);
	old_ang = ang;
	dx = floatadd(x, floatmul(floatcos(ang),distance));
	dy = floatadd(y, floatmul(floatsin(ang),distance));
	Alpha = rotz; //в градусах!

	//эту проверку можно запихнуть в Valid_Z_Coordinate (?) //оптимизация!
	//надо бы создать отдельную функцию для определения координат, чтобы с её помощью разбрасывать вещи из авто
	//...
	ret = MapAndreas_Valid_Z_Coordinate(dx,dy,z,Z_coord,Alpha,Beta); //ищем место, куда бы выложить объект
    dx1 = dx;
    dy1 = dy;
    Z_coord1 = Z_coord;
    flag = false;
    iter_val = 1.0;
    found = 0;
	is_any = 0;

#if defined DEBUG
	opsDebug2 = GetTickCount();
	printf("post_item, 1 label: %d, %d", opsDebug2-opsDebug0,opsDebug2-opsDebug1);
	opsDebug1 = opsDebug2;
#endif

	if( playerid != INVALID_PLAYER_ID && vehicleid == INVALID_VEHICLE_ID &&
		x > floatsub(gPlayerPlacesXYZ[playerid][0],0.1) && x < floatadd(gPlayerPlacesXYZ[playerid][0],0.1) &&
		y > floatsub(gPlayerPlacesXYZ[playerid][1],0.1) && y < floatadd(gPlayerPlacesXYZ[playerid][1],0.1) &&
		z > floatsub(gPlayerPlacesXYZ[playerid][2],0.1) && z < floatadd(gPlayerPlacesXYZ[playerid][2],0.1) )
	{
	    iteration = gPlayerPlaces[playerid];
	    dx = gPlayerPlacesXYZ[playerid][3];//dx1;
	    dy = gPlayerPlacesXYZ[playerid][4];//dy1;
	    Z_coord = gPlayerPlacesXYZ[playerid][5];//Z_coord1;
	    Alpha1 = gPlayerPlacesXYZ[playerid][6];//rotz;
        ang = gPlayerPlacesXYZ[playerid][7];//
        iter_val = gPlayerPlacesXYZ[playerid][8];
		dx1 = gPlayerPlacesXYZ[playerid][9];
		dy1 = gPlayerPlacesXYZ[playerid][10];
		if(iteration > 1)
			flag = true;
		ret = MapAndreas_Valid_Z_Coordinate(dx1,dy1,z,Z_coord1,Alpha1,Beta1); //ищем новое место для объекта
	}
	else
	{
	    iteration = 1;
	    if(playerid != INVALID_PLAYER_ID)
			gPlayerPlaces[playerid] = iteration;
	}
	
#if defined DEBUG
	opsDebug2 = GetTickCount();
	printf("post_item, 2 label: %d, %d", opsDebug2-opsDebug0,opsDebug2-opsDebug1);
	opsDebug1 = opsDebug2;
#endif

    //пока место плохое или рядом лежит другой объект, и при этом не сделан полный оборот вокруг персонажа
    while( (ret == 1 || (is_any = is_any_object_in_range(playerid,dx1,dy1,floatadd(floatadd(Z_coord1,height),1.0),0.8,floatadd(distance,1.2),INVALID_OBJECT_ID))) && (ang > floatsub(old_ang,3.14)) )
    {
        //оптимизация!
        //вычислять место исходя из координат персонажа и лежащих объектов (намного быстрей, чем десяток обращений к базе)
        //...
		if(ret == 0 && is_any == 1)
		{
	        dx2 = dx1;
	        dy2 = dy1;
	        Z_coord2 = Z_coord1;
	        Alpha2 = Alpha1;
	        Beta2 = Beta1;
		    found = 1;
		}
        flag = true;
	    dx = dx1;
	    dy = dy1;
	    Z_coord = Z_coord1;
	    Alpha1 = rotz;
	    //раскачиваем место как маятник
        ang = floatsub(old_ang,(iteration%2 == 0)?floatmul(-0.148,iter_val):floatmul(0.148,iter_val)); //проверяем места с шагом в 20 градусов (0.348)
        if(iteration%2 == 0)
	        iter_val = floatadd(iter_val,1.0);
		iteration++;
		dx1 = floatadd(x, floatmul(floatcos(ang),distance));
		dy1 = floatadd(y, floatmul(floatsin(ang),distance));
		ret = MapAndreas_Valid_Z_Coordinate(dx1,dy1,z,Z_coord1,Alpha1,Beta1); //ищем новое место для объекта
    }

#if defined DEBUG
	opsDebug2 = GetTickCount();
	printf("post_item, 3 label: %d, %d", opsDebug2-opsDebug0,opsDebug2-opsDebug1);
	opsDebug1 = opsDebug2;
#endif

	if(playerid != INVALID_PLAYER_ID)
	{
	    gPlayerPlacesXYZ[playerid][3] = dx;
	    gPlayerPlacesXYZ[playerid][4] = dy;
	    gPlayerPlacesXYZ[playerid][5] = Z_coord;
	    gPlayerPlacesXYZ[playerid][6] = Alpha1;
	    gPlayerPlacesXYZ[playerid][7] = ang;
	    gPlayerPlacesXYZ[playerid][8] = iter_val;
		gPlayerPlacesXYZ[playerid][9] = dx1;
		gPlayerPlacesXYZ[playerid][10] = dy1;
	}

    if(flag) //если был заход в цикл
	{
	    if(ret == 0 && is_any == 0) //если последнее место хорошее - помещаем объект на него
        {
	        dx = dx1;
	        dy = dy1;
	        Z_coord = Z_coord1;
	        Alpha = Alpha1;
	        Beta = Beta1;
		}
		else //иначе - размещаем позади персонажа
		{
		    if(found == 1)
		    {
		        dx = dx2;
		        dy = dy2;
		        Z_coord = Z_coord2;
		        Alpha = Alpha2;
		        Beta = Beta2;
		    }
		    else
		    {
			    Z_coord = floatsub(z,1.0);
				ang = floatadd(old_ang,3.14);
				dx = floatadd(x, floatmul(floatcos(ang),distance));
				dy = floatadd(y, floatmul(floatsin(ang),distance));
			}
		}
    }

	if((rotatable == 1) && (ret == 0))
	{
	    //если место вполне подходит
	    obj_id = CreateObject(modelid, dx, dy, floatadd(floatadd(Z_coord,height),1.0), floatadd(rotx,Beta), floatadd(roty,Alpha), rotz, OBJECT_DISTANCE);
	}
	else
	{
	    //если место находится под навесом, либо рядом со стеной
		obj_id = CreateObject(modelid, dx, dy, floatadd(floatadd(Z_coord,height),1.0), rotx, roty, rotz, OBJECT_DISTANCE);
	}
	if(obj_id == INVALID_OBJECT_ID)
		printf("error post_item: can not create object, db_id=%d", inv[db_id]);
	inv[object] = obj_id;
	inv[obj_coord][f_X] = dx;
	inv[obj_coord][f_Y] = dy;
	inv[obj_coord][f_Z] = floatadd(floatadd(Z_coord,height),1.0);

	//добавляем размещённый объект в кэш
	is_any_object_in_range(playerid, dx, dy, floatadd(floatadd(Z_coord,height),1.0), 0, 0, inv[db_id]);
	
#if defined DEBUG
	opsDebug2 = GetTickCount();
	printf("post_item, 4 label: %d, %d", opsDebug2-opsDebug0,opsDebug2-opsDebug1);
	opsDebug1 = opsDebug2;
#endif

	//указываем координаты объекта, обнуляем поля владельца и точки появления объекта, указываем кто выложил и obj_id
	if(rotatable == 1 && ret == 0)
	{
	    if(vehicleid != INVALID_VEHICLE_ID)
		    mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET vector=%f,placex=%f,placey=%f,placez=%f,add_rotx=%f,add_roty=%f,add_rotz=%f,pl_owner_id=NULL,th_owner_id=NULL,obj_id=%d,dot_id=NULL WHERE id=%d", VectorSize(dx,dy,Z_coord+1.0), dx, dy, floatadd(Z_coord,1.0), Beta, Alpha, 0.0, obj_id, id);
		else
		    mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET vector=%f,placex=%f,placey=%f,placez=%f,add_rotx=%f,add_roty=%f,add_rotz=%f,pl_owner_id=NULL,th_owner_id=NULL,obj_id=%d,dot_id=NULL,is_dropped=%d,last_time=NOW() WHERE id=%d",VectorSize(dx,dy,floatadd(Z_coord,1.0)),dx,dy,floatadd(Z_coord,1.0),Beta,Alpha,0.0,obj_id,gPlayersID[playerid],id);
	}
	else
	{
	    if(vehicleid != INVALID_VEHICLE_ID)
		    mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET vector=%f,placex=%f,placey=%f,placez=%f,add_rotx=0,add_roty=0,add_rotz=0,pl_owner_id=NULL,th_owner_id=NULL,obj_id=%d,dot_id=NULL WHERE id=%d", VectorSize(dx,dy,Z_coord+1.0), dx, dy, Z_coord+1.0, obj_id, id);
		else
		    mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET vector=%f,placex=%f,placey=%f,placez=%f,add_rotx=0,add_roty=0,add_rotz=0,pl_owner_id=NULL,th_owner_id=NULL,obj_id=%d,dot_id=NULL,is_dropped=%d,last_time=NOW() WHERE id=%d",VectorSize(dx,dy,floatadd(Z_coord,1.0)),dx,dy,floatadd(Z_coord,1.0),obj_id,gPlayersID[playerid],id);
	}
	mysql_query(gMysql, request);

	//обНУЛЛяем объект для точки появления и обновляем время обновления точки
    mysql_format(gMysql, request, sizeof(request), "UPDATE object_dot SET object_id=NULL,last_time=now() WHERE object_id=%d", id);
	thread_sql(request);

	if(obj_cell >= 0)
	{
		if(vehicleid != INVALID_VEHICLE_ID)
		{
			//для обновления стримера
			SetVehiclePos(vehicleid, floatadd(x,0.001), y, z);
		}
		else
		{
			//для обновления стримера
			SetPlayerPos(playerid, floatadd(x,0.001), y, z);
		}
	}

	if(playerid != INVALID_PLAYER_ID)
	{
		gPlayerPlacesXYZ[playerid][0] = x;
		gPlayerPlacesXYZ[playerid][1] = y;
		gPlayerPlacesXYZ[playerid][2] = z;
		gPlayerPlaces[playerid] = iteration + 1;
	}
	
#if defined DEBUG
	opsDebug2 = GetTickCount();
	printf("post_item, 5 (out) label: %d, %d", opsDebug2-opsDebug0,opsDebug2-opsDebug1);
	opsDebug1 = opsDebug2;
#endif

    add_item_to_global_cache(inv);

	return obj_id;
}

//выложить объект из ячейки инвентаря авто
//функция подходит для "разбрасывания" объектов инвентаря
public drop_vehicle_inventory_cell(vehicleid, cell)
{
	new request[256];
	new Float:x, Float:y, Float:z;
	new inv[CRAFT_ITEM];

	if(cell < 0)
	    return;

	if(cell >= 0)
	{
		//защита от дурака
	    if(gVehicleItem[vehicleid][cell][db_id] == -1)
	        return;
	}

	//освобождаем ячейку
    mysql_format(gMysql, request, sizeof(request), "UPDATE veh_invent SET inv%d=-1 WHERE object_id=%d",cell+1,gVeh[vehicleid][0]);
	mysql_query(gMysql, request);

	//копируем кэш
	copy_craft_item(inv, gVehicleItem[vehicleid][cell]);
	GetVehiclePos(vehicleid, x, y, z);
	post_item(INVALID_PLAYER_ID, vehicleid, inv, cell, x, y, z);

    zero_craft_item(gVehicleItem[vehicleid][cell]);
}

//выложить объект из ячейки инвентаря
//функция подходит для "разбрасывания" объектов инвентаря (при obj_cell равном -1)
//не работает, если игрок не находится в игре!
public drop_character_inventory_cell(playerid, cell, obj_cell, Float:x,Float:y,Float:z)
{
	new request[256];
	new obj_id;
	new inv[CRAFT_ITEM];

	if(gPlayersID[playerid] <= 0)
	    return;
	    
	if(cell < 0)
	    return;

	if(cell >= MAX_INVENTORY_ON_PLAYER || obj_cell >= MAX_INVENTORY_ON_GROUND)
        return;

	if(obj_cell >= 0)
	{
		//защита от дурака
	    if( (gInventoryItem[playerid][cell][db_id] == -1 && gGroundItem[playerid][obj_cell][db_id] == -1) ||
	        (gInventoryItem[playerid][cell][db_id] != -1 && gGroundItem[playerid][obj_cell][db_id] != -1) )
	        return;

		//создаём копию кэша независимо от того, была уже замена или нет
		if(gGroundItem[playerid][obj_cell][db_id] != -1)
			copy_craft_item(inv, gGroundItem[playerid][obj_cell]);
		else
			copy_craft_item(inv, gInventoryItem[playerid][cell]);
	}
	else
		copy_craft_item(inv, gInventoryItem[playerid][cell]);

	//освобождаем ячейку
    mysql_format(gMysql, request, sizeof(request), "UPDATE inventory SET inv%d=-1 WHERE player_id=%d", cell+1, gPlayersID[playerid]);
	thread_sql(request);

	obj_id = post_item(playerid, INVALID_VEHICLE_ID, inv, obj_cell, x, y, z);
	
	if(gInventoryItem[playerid][cell][db_id] != -1)
	{
	    gInventoryItem[playerid][cell][object] = obj_id;
	    gInventoryItem[playerid][cell][obj_coord][f_X] = x;
	    gInventoryItem[playerid][cell][obj_coord][f_Y] = y;
	    gInventoryItem[playerid][cell][obj_coord][f_Z] = z;

	}
	else
	{
		if(obj_cell >= 0)
		{
			gGroundItem[playerid][obj_cell][object] = obj_id;
			gGroundItem[playerid][obj_cell][obj_coord][f_X] = x;
			gGroundItem[playerid][obj_cell][obj_coord][f_Y] = y;
			gGroundItem[playerid][obj_cell][obj_coord][f_Z] = z;
		}
	}
}

//выложить объект из рюкзака
//функция подходит для "разбрасывания" объектов инвентаря (при obj_cell равном -1)
public drop_bag_inventory_cell(playerid, cell, obj_cell, Float:in_x,Float:in_y,Float:in_z)
{
	new request[256];
	new Float:x, Float:y, Float:z;
	new obj_id;
	new inv[CRAFT_ITEM];

	if(gPlayersID[playerid] <= 0)
	    return -1;
	    
	if(cell < 0)
	    return -2;

	if(obj_cell >= 0)
	{
		//защита от дурака
	    if( (gBagItem[playerid][cell][db_id] == -1) && (gGroundItem[playerid][obj_cell][db_id] == -1) ||
			(gBagItem[playerid][cell][db_id] != -1) && (gGroundItem[playerid][obj_cell][db_id] != -1) )
	        return -3;
	}

	//создаём копию кэша независимо от того, была уже замена или нет
	if(gBagItem[playerid][cell][db_id] != -1)
		copy_craft_item(inv, gBagItem[playerid][cell]);
	else
	{
	    if(obj_cell >= 0)
			copy_craft_item(inv, gGroundItem[playerid][obj_cell]);
	}

	if(obj_cell == -2)
	{
	    GetPlayerPos(playerid, x, y, z);
	}
	else
	{
	    x = in_x;
	    y = in_y;
	    z = in_z;
	}

	//освобождаем ячейку
    mysql_format(gMysql, request, sizeof(request), "UPDATE bag_invent SET inv%d=-1 WHERE object_id=%d", cell+1, gBag[playerid][1]);
	thread_sql(request);

	obj_id = post_item(playerid, INVALID_VEHICLE_ID, inv, obj_cell, x, y, z);

	if(obj_cell >= 0 && gGroundItem[playerid][obj_cell][db_id] != -1)
	    gGroundItem[playerid][obj_cell][object] = obj_id;
	else
	    gBagItem[playerid][cell][object] = obj_id;

	return 1;
}

//положить объект на землю
//функция не обновляет глобальный кэш (!) временно
public drop_object_on_ground(playerid, obj_id)
{
	new request[432];
	new rows, fields;
	new modelid, rotatable;
	new Float:x, Float:y, Float:z, Float:Z_coord, Float:ang, Float:old_ang, Float:dx, Float:dy;
	new Float:dx1, Float:dy1, Float:Z_coord1;
	new Float:dx2, Float:dy2, Float:Z_coord2;
	new Float:Alpha, Float:Beta, Float:Alpha1, Float:Beta1, Float:Alpha2, Float:Beta2;
	new Float:rotx, Float:roty, Float:rotz;
	new Float:height;
	new ret;
	new Cache:result;
	new bool:flag;
	new is_any;
	new iteration;
	new Float:iter_val;
	new found;
	new id;
	new Float:distance;
	new object_id, is_vehicle;
	new inv[CRAFT_ITEM];

	if(gPlayersID[playerid] <= 0)
	    return;
	    
	//защита от дурака
	if(obj_id < 0 || playerid == INVALID_PLAYER_ID)
	    return;

	//получаем свойства объекта
    mysql_format(gMysql, request, sizeof(request), "SELECT c.posx,c.posy,c.posz,c.height,c.inworld_id,b.id,c.rotatable,IFNULL(b.obj_id,%d) as object_id,c.is_vehicle FROM objects b INNER JOIN things c ON b.thing_id=c.id WHERE b.id=%d LIMIT 1", INVALID_OBJECT_ID, obj_id);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
	    return;
	rotx = cache_get_field_content_float(0, "posx", gMysql);
	roty = cache_get_field_content_float(0, "posy", gMysql);
	rotz = cache_get_field_content_float(0, "posz", gMysql);
	height = cache_get_field_content_float(0, "height", gMysql);
	modelid = cache_get_field_content_int(0, "inworld_id", gMysql);
	rotatable = cache_get_field_content_int(0, "rotatable", gMysql);
	id = cache_get_field_content_int(0, "id", gMysql);
	object_id = cache_get_field_content_int(0, "object_id", gMysql);
	is_vehicle = cache_get_field_content_int(0, "is_vehicle", gMysql);
	
	if(cache_is_valid(result, gMysql))
		cache_delete(result);

	//если это авто - выходим
	//if(is_vehicle == 1)
	//    return;

	GetPlayerPos(playerid, x, y, z);
	if(IsPlayerInAnyVehicle(playerid))
	{
		distance = DROP_DISTANCE_FROM_PLAYER + 3.0;
	}
	else
	{
		distance = DROP_DISTANCE_FROM_PLAYER;
	}
	GetPlayerFacingAngle(playerid, ang);
	ang = floatdiv(floatmul(floatadd(ang,90.0),3.14), 180.0);
	old_ang = ang;
	dx = x + floatmul(floatcos(ang),distance);
	dy = y + floatmul(floatsin(ang),distance);
	Alpha = rotz; //в градусах!

	//эту проверку можно запихнуть в Valid_Z_Coordinate (?) //оптимизация!
	//надо бы создать отдельную функцию для определения координат, чтобы с её помощью разбрасывать вещи из авто
	//...
	ret = MapAndreas_Valid_Z_Coordinate(dx,dy,z,Z_coord,Alpha,Beta); //ищем место, куда бы выложить объект
    dx1 = dx;
    dy1 = dy;
    Z_coord1 = Z_coord;
    flag = false;
    iter_val = 1.0;
    found = 0;
	is_any = 0;

	if( x > floatsub(gPlayerPlacesXYZ[playerid][0],0.1) && x < floatadd(gPlayerPlacesXYZ[playerid][0],0.1) &&
		y > floatsub(gPlayerPlacesXYZ[playerid][1],0.1) && y < floatadd(gPlayerPlacesXYZ[playerid][1],0.1) &&
		z > floatsub(gPlayerPlacesXYZ[playerid][2],0.1) && z < floatadd(gPlayerPlacesXYZ[playerid][2],0.1) )
	{
/*
	    iteration = gPlayerPlaces[playerid];
	    for(new j = 1; j < iteration+1; ++j)
	    {
		    dx = dx1;
		    dy = dy1;
		    Z_coord = Z_coord1;
		    Alpha1 = rotz;
	        ang = floatsub(old_ang,(iteration%2 == 0)?floatmul(-0.348,iter_val):floatmul(0.348,iter_val)); //проверяем места с шагом в 20 градусов
	        if(j%2 == 0)
		        iter_val = floatadd(iter_val,1.0);
			dx1 = x + floatmul(floatcos(ang),distance);
			dy1 = y + floatmul(floatsin(ang),distance);
			ret = MapAndreas_Valid_Z_Coordinate(dx1,dy1,z,Z_coord1,Alpha1,Beta1); //ищем новое место для объекта
		}
*/
	    iteration = gPlayerPlaces[playerid];
	    dx = gPlayerPlacesXYZ[playerid][3];//dx1;
	    dy = gPlayerPlacesXYZ[playerid][4];//dy1;
	    Z_coord = gPlayerPlacesXYZ[playerid][5];//Z_coord1;
	    Alpha1 = gPlayerPlacesXYZ[playerid][6];//rotz;
        ang = gPlayerPlacesXYZ[playerid][7];//
        iter_val = gPlayerPlacesXYZ[playerid][8];
		dx1 = gPlayerPlacesXYZ[playerid][9];
		dy1 = gPlayerPlacesXYZ[playerid][10];
		if(iteration > 1)
			flag = true;
		ret = MapAndreas_Valid_Z_Coordinate(dx1,dy1,z,Z_coord1,Alpha1,Beta1); //ищем новое место для объекта
	}
	else
	{
	    iteration = 1;
		gPlayerPlaces[playerid] = iteration;
	}

    //пока место плохое или рядом лежит другой объект, и при этом не сделан полный оборот вокруг персонажа
    while( (ret == 1 || (is_any = is_any_object_in_range(playerid,dx1,dy1,Z_coord1+height+1.0,1.11,distance+1.11,INVALID_OBJECT_ID))) && (ang > floatsub(old_ang,3.14)) )
    {
        //оптимизация!
        //вычислять место исходя из координат персонажа и лежащих объектов (намного быстрей, чем десяток обращений к базе)
        //...
		if(ret == 0 && is_any == 1)
		{
	        dx2 = dx1;
	        dy2 = dy1;
	        Z_coord2 = Z_coord1;
	        Alpha2 = Alpha1;
	        Beta2 = Beta1;
		    found = 1;
		}
        flag = true;
	    dx = dx1;
	    dy = dy1;
	    Z_coord = Z_coord1;
	    Alpha1 = rotz;
	    //раскачиваем место как маятник
        ang = floatsub(old_ang,(iteration%2 == 0)?floatmul(-0.348,iter_val):floatmul(0.348,iter_val)); //проверяем места с шагом в 20 градусов
        if(iteration%2 == 0)
	        iter_val = floatadd(iter_val,1.0);
		iteration++;
		dx1 = x + floatmul(floatcos(ang),distance);
		dy1 = y + floatmul(floatsin(ang),distance);
		ret = MapAndreas_Valid_Z_Coordinate(dx1,dy1,z,Z_coord1,Alpha1,Beta1); //ищем новое место для объекта
    }
    
    gPlayerPlacesXYZ[playerid][3] = dx;
    gPlayerPlacesXYZ[playerid][4] = dy;
    gPlayerPlacesXYZ[playerid][5] = Z_coord;
    gPlayerPlacesXYZ[playerid][6] = Alpha1;
    gPlayerPlacesXYZ[playerid][7] = ang;
    gPlayerPlacesXYZ[playerid][8] = iter_val;
	gPlayerPlacesXYZ[playerid][9] = dx1;
	gPlayerPlacesXYZ[playerid][10] = dy1;

    if(flag) //если был заход в цикл
	{
	    if(ret == 0 && is_any == 0) //если последнее место хорошее - помещаем объект на него
        {
	        dx = dx1;
	        dy = dy1;
	        Z_coord = Z_coord1;
	        Alpha = Alpha1;
	        Beta = Beta1;
		}
		else //иначе - размещаем позади персонажа
		{
		    if(found == 1)
		    {
		        dx = dx2;
		        dy = dy2;
		        Z_coord = Z_coord2;
		        Alpha = Alpha2;
		        Beta = Beta2;
		    }
		    else
		    {
			    Z_coord = floatsub(z,1.0);
				ang = floatadd(old_ang,3.14);
				dx = x + floatmul(floatcos(ang),distance);
				dy = y + floatmul(floatsin(ang),distance);
			}
		}
    }
    
    if(IsValidObject(object_id))
		DestroyObject(object_id);

	clear_all_owners(obj_id);

	if(is_vehicle)
	{
		create_old_vehicle(obj_id, dx+3.0, dy+3.0, Z_coord+height+1.0, 0, modelid);
	}
	else
	{
		if((rotatable == 1) && (ret == 0))
		{
		    //если место вполне подходит
		    object_id = CreateObject(modelid, dx, dy, Z_coord+height+1.0, rotx+Beta, roty+Alpha, rotz, OBJECT_DISTANCE);
		}
		else
		{
		    //если место находится под навесом, либо рядом со стеной
			object_id = CreateObject(modelid, dx, dy, Z_coord+height+1.0, rotx, roty, rotz, OBJECT_DISTANCE);
		}
		//добавляем размещённый объект в кэш
		is_any_object_in_range(playerid, dx, dy, floatadd(floatadd(Z_coord,height),1.0), 0, 0, obj_id);
		if(object_id == INVALID_OBJECT_ID)
			printf("error drop_object_on_ground: can not create object, db_id=%d", id);
		//указываем координаты объекта, обнуляем поля владельца и точки появления объекта, указываем кто выложил и obj_id
		if(rotatable == 1 && ret == 0)
		    mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET vector=%f,placex=%f,placey=%f,placez=%f,add_rotx=%f,add_roty=%f,add_rotz=%f,pl_owner_id=NULL,th_owner_id=NULL,obj_id=%d,dot_id=NULL,is_dropped=%d,last_time=NOW() WHERE id=%d", VectorSize(dx,dy,Z_coord+1.0), dx, dy, Z_coord+1.0, Beta, Alpha, 0.0, object_id, gPlayersID[playerid], id);
		else
		    mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET vector=%f,placex=%f,placey=%f,placez=%f,add_rotx=0,add_roty=0,add_rotz=0,pl_owner_id=NULL,th_owner_id=NULL,obj_id=%d,dot_id=NULL,is_dropped=%d,last_time=NOW() WHERE id=%d", VectorSize(dx,dy,Z_coord+1.0), dx, dy, Z_coord+1.0, object_id, gPlayersID[playerid], id);
		mysql_query(gMysql, request);
	}
	
	//обНУЛЛяем объект для точки появления и обновляем время обновления точки
    mysql_format(gMysql, request, sizeof(request), "UPDATE object_dot SET object_id=NULL,last_time=now() WHERE object_id=%d", id);
	thread_sql(request);

	//для обновления стримера
	SetPlayerPos(playerid, x+0.001, y, z);
	
	gPlayerPlacesXYZ[playerid][0] = x;
	gPlayerPlacesXYZ[playerid][1] = y;
	gPlayerPlacesXYZ[playerid][2] = z;
	gPlayerPlaces[playerid] = iteration + 1;
	
	init_craft_item(inv, obj_id);
	add_item_to_global_cache(inv);
}

//функция обнуляет кэш
public drop_bag_object_on_ground(playerid, obj_id)
{
	new i;
	new request[256];

	if(playerid < 0 || playerid > MAX_PLAYERS)
	    return;

	if(gPlayersID[playerid] <= 0)
	    return;

	if(gBag[playerid][1] <= 0)
	    return;
	    
	for(i = 0; i < MAX_INVENTORY_IN_BAG; ++i)
	{
	    if(gBagItem[playerid][i][db_id] == obj_id)
	    {
		    mysql_format(gMysql, request, sizeof(request), "UPDATE bag_invent SET inv%d=-1 WHERE object_id=%d LIMIT 1",i+1,gBag[playerid][1]);
			thread_sql(request);
			drop_object_on_ground(playerid, obj_id);
			//обнуляем кэш
			zero_craft_item(gBagItem[playerid][i]);
	        break;
		}
	}
}

public drop_last_object_on_ground(playerid)
{
	new request[256];
	new rows, fields;
	new object_id;
	new Cache:result;

	if(playerid < 0 || playerid > MAX_PLAYERS)
	    return;

	if(gPlayersID[playerid] <= 0)
	    return;

    mysql_format(gMysql, request, sizeof(request), "SELECT id FROM objects ORDER BY id DESC LIMIT 1");
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
	    return;
	object_id = cache_get_field_content_int(0, "id", gMysql);
	
	if(cache_is_valid(result, gMysql))
		cache_delete(result);

	drop_object_on_ground(playerid, object_id);
}

//переложить объект из ячейки инвентаря транспорта в инвентарь игрока
public take_vehicle_inventory_cell(playerid, vehicleid, cell, veh_cell)
{
	new request[256];
	new inv[CRAFT_ITEM];

	if(gPlayersID[playerid] <= 0)
	    return -1;

	if(playerid < 0 || vehicleid < 0)
	    return -2;

	//защита от дурака
    if( (gVehicleItem[vehicleid][veh_cell][db_id] == -1 && gInventoryItem[playerid][cell][db_id] == -1) ||
	    (gVehicleItem[vehicleid][veh_cell][db_id] != -1 && gInventoryItem[playerid][cell][db_id] != -1) )
        return -4;

	if(gVehicleItem[vehicleid][veh_cell][db_id] != -1)
		copy_craft_item(inv, gVehicleItem[vehicleid][veh_cell]);
	else
		copy_craft_item(inv, gInventoryItem[playerid][cell]);

	if(inv[obj_owner] != 0 && inv[obj_owner] != gPlayersID[playerid])
	    return -5; //чужая вещь!

	//перемещаем объект в инвентарь персонажа
    mysql_format(gMysql, request, sizeof(request),
				"UPDATE inventory a,objects b,veh_invent c SET c.inv%d=-1,a.inv%d=%d,b.pl_owner_id=%d,b.th_owner_id=NULL \
				WHERE a.player_id=%d AND b.id=%d AND c.object_id=%d",
				veh_cell+1,
				cell+1,gVehicleItem[vehicleid][veh_cell][db_id],
				gPlayersID[playerid],
				gPlayersID[playerid],
				gVehicleItem[vehicleid][veh_cell][db_id],
				gVeh[vehicleid][0]);
	thread_sql(request);
	
	if(gInventoryItem[playerid][cell][db_id] == -1 && gVehicleItem[vehicleid][veh_cell][db_id] != -1)
	    move_craft_item(gInventoryItem[playerid][cell], gVehicleItem[vehicleid][veh_cell]);

    return 1;
}

//переложить объект из инвентаря игрока в ячейку инвентаря транспорта
public give_vehicle_inventory_cell(playerid, vehicleid, cell, veh_cell)
{
	new request[256];
	new inv[CRAFT_ITEM];

	if(gPlayersID[playerid] <= 0)
	    return -1;

	if(playerid < 0 || vehicleid < 0)
	    return -2;

	//защита от дурака
    if( (gVehicleItem[vehicleid][veh_cell][db_id] == -1 && gInventoryItem[playerid][cell][db_id] == -1) ||
	    (gVehicleItem[vehicleid][veh_cell][db_id] != -1 && gInventoryItem[playerid][cell][db_id] != -1) )
        return -4;

	if(gVehicleItem[vehicleid][veh_cell][db_id] != -1)
		copy_craft_item(inv, gVehicleItem[vehicleid][veh_cell]);
	else
		copy_craft_item(inv, gInventoryItem[playerid][cell]);

	if(inv[obj_owner] != 0 && inv[obj_owner] != gPlayersID[playerid])
	    return -5; //чужая вещь!

	//если объект - оружие в руках, то сохраняем количество патронов и убираем из рук
	if(inv[db_id] == gPlayerWeapon[playerid][0])
	{
	    //сохраняем количество патронов
	    save_character_ammo(playerid, -1, -1);

	    //убираем оружие из рук
	    ResetPlayerWeapons(playerid);
	    gPlayerWeapon[playerid][0] = 0;
	    gPlayerWeapon[playerid][1] = 0;
		gPlayerWeapon[playerid][2] = 0;
		gPlayerWeapon[playerid][3] = 0;
	}

	//перемещаем объект в инвентарь транспорта
    mysql_format(gMysql, request, sizeof(request),
				"UPDATE veh_invent a,objects b,inventory c \
				SET a.inv%d=%d,c.inv%d=-1,b.pl_owner_id=NULL,b.th_owner_id=%d \
				WHERE a.object_id=%d AND b.id=%d AND c.player_id=%d",
				veh_cell+1,inv[db_id],cell+1,gVeh[vehicleid][0],gVeh[vehicleid][0],inv[db_id],gPlayersID[playerid]);
	thread_sql(request);
	
	if(gVehicleItem[vehicleid][veh_cell][db_id] == -1 && gInventoryItem[playerid][cell][db_id] != -1)
	    move_craft_item(gVehicleItem[vehicleid][veh_cell], gInventoryItem[playerid][cell]);

	return 1;
}

//переложить объект из инвентаря рюкзака в ячейку инвентаря транспорта
public give_veh_invent_cell_from_bag(playerid, vehicleid, cell, veh_cell)
{
	new request[256];
	new inv[CRAFT_ITEM];

	if(gPlayersID[playerid] <= 0)
	    return -1;

	if(playerid < 0 || vehicleid < 0)
	    return -2;

	if(gBag[playerid][0] <= 0 || gBag[playerid][1] <= 0)
	    return -3;

	//защита от дурака
    if( (gVehicleItem[vehicleid][veh_cell][db_id] == -1 && gBagItem[playerid][cell][db_id] == -1) ||
	    (gVehicleItem[vehicleid][veh_cell][db_id] != -1 && gBagItem[playerid][cell][db_id] != -1) )
        return -4;

	if(gVehicleItem[vehicleid][veh_cell][db_id] != -1)
		copy_craft_item(inv, gVehicleItem[vehicleid][veh_cell]);
	else
		copy_craft_item(inv, gBagItem[playerid][cell]);

	if(inv[obj_owner] != 0 && inv[obj_owner] != gPlayersID[playerid])
	    return -5; //чужая вещь!

	//если объект - оружие в руках, то сохраняем количество патронов и убираем из рук
	if(inv[db_id] == gPlayerWeapon[playerid][0])
	{
	    //сохраняем количество патронов
	    save_character_ammo(playerid, -1, -1);

	    //убираем оружие из рук
	    ResetPlayerWeapons(playerid);
	    gPlayerWeapon[playerid][0] = 0;
	    gPlayerWeapon[playerid][1] = 0;
		gPlayerWeapon[playerid][2] = 0;
		gPlayerWeapon[playerid][3] = 0;
	}

	//перемещаем объект в инвентарь транспорта
    mysql_format(gMysql, request, sizeof(request),
				"UPDATE veh_invent a,objects b,bag_invent c \
				SET a.inv%d=%d,c.inv%d=-1,b.pl_owner_id=NULL,b.th_owner_id=%d \
				WHERE a.object_id=%d AND b.id=%d AND c.object_id=%d",
				veh_cell+1,inv[db_id],cell+1,gVeh[vehicleid][0],gVeh[vehicleid][0],inv[db_id],gBag[playerid][1]);
	thread_sql(request);
	
	if(gVehicleItem[vehicleid][veh_cell][db_id] == -1 && gBagItem[playerid][cell][db_id] != -1)
	    move_craft_item(gVehicleItem[vehicleid][veh_cell], gBagItem[playerid][cell]);

	return 1;
}

//переложить объект из инвентаря игрока в ячейку рюкзака
public give_bag_inventory_cell(playerid, cell, bag_cell)
{
	new request[256];
	new inv[CRAFT_ITEM];

	if(gPlayersID[playerid] <= 0)
	    return -1;

	if(gBag[playerid][0] <= 0 || gBag[playerid][1] <= 0)
	    return -2;

	//защита от дурака
    if( (gInventoryItem[playerid][cell][db_id] == -1 && gBagItem[playerid][bag_cell][db_id] == -1) ||
	    (gInventoryItem[playerid][cell][db_id] != -1 && gBagItem[playerid][bag_cell][db_id] != -1) )
        return -4;

	if(gInventoryItem[playerid][cell][db_id] != -1)
		copy_craft_item(inv, gInventoryItem[playerid][cell]);
	else
		copy_craft_item(inv, gBagItem[playerid][bag_cell]);

	if(inv[obj_owner] != 0 && inv[obj_owner] != gPlayersID[playerid])
	{
		drop_object_on_ground(playerid, inv[db_id]);
	    return -5; //чужая вещь!
	}
	if(inv[obj_inventory] == 2)
		return -6; //рюкзак
	if(inv[obj_inventory] == 0)
	{
//		drop_object_on_ground(playerid, inv[db_id]); //закомментировано, чтобы не выложить авто
		return -7; //не для инвентаря
	}
	//если объект - оружие в руках, то сохраняем количество патронов и убираем из рук
	if(inv[db_id] == gPlayerWeapon[playerid][0])
	{
	    //сохраняем количество патронов
	    save_character_ammo(playerid, -1, -1);

	    //убираем оружие из рук
	    ResetPlayerWeapons(playerid);
	    gPlayerWeapon[playerid][0] = 0;
	    gPlayerWeapon[playerid][1] = 0;
		gPlayerWeapon[playerid][2] = 0;
		gPlayerWeapon[playerid][3] = 0;
	}

	//перемещаем объект в рюкзак
    mysql_format(gMysql, request, sizeof(request),
				"UPDATE bag_invent a,objects b,inventory c \
				SET a.inv%d=%d,c.inv%d=-1,b.pl_owner_id=NULL,b.th_owner_id=%d \
				WHERE a.object_id=%d AND b.id=%d AND c.player_id=%d",
				bag_cell+1,inv[db_id],cell+1,gBag[playerid][1],gBag[playerid][1],inv[db_id],gPlayersID[playerid]);
	thread_sql(request);

	if(gBagItem[playerid][bag_cell][db_id] == -1 && gInventoryItem[playerid][cell][db_id] != -1)
	    move_craft_item(gBagItem[playerid][bag_cell], gInventoryItem[playerid][cell]);

    return 1;
}

//переложить объект из инвентаря авто в ячейку рюкзака
public give_bag_invent_cell_from_veh(playerid, vehicleid, cell, bag_cell)
{
	new request[256];
	new inv[CRAFT_ITEM];
	
	if(playerid < 0 || vehicleid < 0)
	    return -1;
	    
	if(gPlayersID[playerid] <= 0)
	    return -2;

	if(gBag[playerid][0] <= 0 || gBag[playerid][1] <= 0)
	    return -3;

	//защита от дурака
    if( (gVehicleItem[vehicleid][cell][db_id] == -1 && gBagItem[playerid][bag_cell][db_id] == -1) ||
	    (gVehicleItem[vehicleid][cell][db_id] != -1 && gBagItem[playerid][bag_cell][db_id] != -1) )
        return -4;

	if(gVehicleItem[vehicleid][cell][db_id] != -1)
		copy_craft_item(inv, gVehicleItem[vehicleid][cell]);
	else
		copy_craft_item(inv, gBagItem[playerid][bag_cell]);

	if(inv[obj_owner] != 0 && inv[obj_owner] != gPlayersID[playerid])
	{
	    return -5; //чужая вещь!
	}
	if(inv[obj_inventory] == 2)
		return -6; //рюкзак
	if(inv[obj_inventory] == 0)
	{
//		drop_object_on_ground(playerid, inv[db_id]);
		return -7; //не для инвентаря
	}

	//перемещаем объект в рюкзак
    mysql_format(gMysql, request, sizeof(request),
				"UPDATE bag_invent a,objects b,veh_invent c \
				SET a.inv%d=%d,c.inv%d=-1,b.pl_owner_id=NULL,b.th_owner_id=%d \
				WHERE a.object_id=%d AND b.id=%d AND c.object_id=%d",
				bag_cell+1,inv[db_id],cell+1,gBag[playerid][1],gBag[playerid][1],inv[db_id],gVeh[vehicleid][0]);
	thread_sql(request);

	if(gBagItem[playerid][bag_cell][db_id] == -1 && gVehicleItem[vehicleid][cell][db_id] != -1)
	    move_craft_item(gBagItem[playerid][bag_cell], gVehicleItem[vehicleid][cell]);

    return 1;
}

//переложить объект из ячейки инвентаря рюкзака в инвентарь игрока
public take_bag_inventory_cell(playerid, cell, bag_cell)
{
	new request[256];
	new inv[CRAFT_ITEM];

	if(gPlayersID[playerid] <= 0)
	    return -1;

	if(gBag[playerid][0] <= 0 || gBag[playerid][1] <= 0)
	    return -2;

	//защита от дурака
    if( (gInventoryItem[playerid][cell][db_id] == -1 && gBagItem[playerid][bag_cell][db_id] == -1) ||
	    (gInventoryItem[playerid][cell][db_id] != -1 && gBagItem[playerid][bag_cell][db_id] != -1) )
        return -4;

	if(gInventoryItem[playerid][cell][db_id] != -1)
		copy_craft_item(inv, gInventoryItem[playerid][cell]);
	else
		copy_craft_item(inv, gBagItem[playerid][bag_cell]);

	if(inv[obj_owner] != 0 && inv[obj_owner] != gPlayersID[playerid])
	    return -5; //чужая вещь!

	//перемещаем объект в инвентарь персонажа
    mysql_format(gMysql, request, sizeof(request),
				"UPDATE inventory a,objects b,bag_invent c SET c.inv%d=-1,a.inv%d=%d,b.pl_owner_id=%d,b.th_owner_id=NULL \
				WHERE a.player_id=%d AND b.id=%d AND c.object_id=%d",
				bag_cell+1,
				cell+1,inv[db_id],
				gPlayersID[playerid],
				gPlayersID[playerid],
				inv[db_id],
				gBag[playerid][1]);
	thread_sql(request);

	if(gInventoryItem[playerid][cell][db_id] == -1 && gBagItem[playerid][bag_cell][db_id] != -1)
	    move_craft_item(gInventoryItem[playerid][cell], gBagItem[playerid][bag_cell]);

    return 1;
}

//положить объект в ячейку рюкзака
public give_bag_invent_cell_from_grnd(playerid, cell, bag_cell)
{
	new ret;

	if(playerid < 0)
	    return -2;

	if(gPlayersID[playerid] <= 0)
	    return -1;

	if(gBag[playerid][0] <= 0 || gBag[playerid][1] <= 0)
	    return -20;

	//защита от дурака
    if(gGroundItem[playerid][cell][db_id] == -1 || gBagItem[playerid][bag_cell][db_id] != -1)
        return -30;

	ret = set_bag_inventory_cell(playerid, bag_cell, cell, false);
	if(ret < 0)
	    return ret;

    return 1;
}

//переложить объект в инвентаре на пустое место
public move_character_inventory_cell(playerid, cell1, cell2)
{
	new request[128];

	if(gPlayersID[playerid] <= 0)
	    return;

    if(gInventoryItem[playerid][cell2][db_id] != -1 ||
	   gInventoryItem[playerid][cell1][db_id] == -1)
		return;

    mysql_format(gMysql, request, sizeof(request), "UPDATE inventory SET inv%d=inv%d,inv%d=-1 WHERE player_id=%d AND inv%d=-1",cell2+1,cell1+1,cell1+1,gPlayersID[playerid],cell2+1);
	thread_sql(request);

	//перемещаем кэш
	move_craft_item(gInventoryItem[playerid][cell2], gInventoryItem[playerid][cell1]);
}

//переложить объект в инвентаре транспорта на пустое место
public move_vehicle_inventory_cell(vehicleid, cell1, cell2)
{
	new request[128];

	if(gVehicleItem[vehicleid][cell1][db_id] == -1 ||
	   gVehicleItem[vehicleid][cell2][db_id] != -1)
		return;

    mysql_format(gMysql, request, sizeof(request), "UPDATE veh_invent SET inv%d=inv%d,inv%d=-1 WHERE object_id=%d AND inv%d=-1",cell2+1,cell1+1,cell1+1,gVeh[vehicleid][0],cell2+1);
	thread_sql(request);

	move_craft_item(gVehicleItem[vehicleid][cell2], gVehicleItem[vehicleid][cell1]);
}

//переложить объект в рюкзаке на пустое место
public move_bag_inventory_cell(playerid, cell1, cell2)
{
	new request[128];

	if(gPlayersID[playerid] <= 0)
	    return;

	if(gBag[playerid][0] <= 0 || gBag[playerid][1] <= 0)
	    return;

	if(gBagItem[playerid][cell2][db_id] != -1 || gBagItem[playerid][cell2][db_id] != -1 ||
	   gBagItem[playerid][cell1][db_id] == -1 || gBagItem[playerid][cell1][db_id] == -1 )
	    return;

    mysql_format(gMysql, request, sizeof(request),
				"UPDATE bag_invent SET inv%d=inv%d,inv%d=-1 WHERE object_id=%d AND inv%d=-1",
				cell2+1, cell1+1, cell1+1, gBag[playerid][1], cell2+1);
	thread_sql(request);

	//перемещаем кэш
	move_craft_item(gBagItem[playerid][cell2], gBagItem[playerid][cell1]);
}

//получить имя и значение вещи объекта
public get_object_data(playerid, cell, area, name[128], &value)
{
	new request[256];
	new rows, fields;
	new Cache:result;

	if(gPlayersID[playerid] <= 0)
	    return -1;

	strdel(name, 0, sizeof(name)-1);

	if(cell < 0)
	    return -1;
	
	switch(area)
	{
	    case INVENTORY_AREA:
	    {
	        mysql_format(gMysql, request, sizeof(request), "SELECT a.value,b.name FROM objects a INNER JOIN things b ON (a.thing_id=b.id AND a.id=%d)",gInventoryItem[playerid][cell][db_id]);
		}
		case GROUND_AREA:
		{
			if(gObjectsMenuShow[playerid] == 0)
			    return -1;
	        mysql_format(gMysql, request, sizeof(request), "SELECT a.value,b.name FROM objects a INNER JOIN things b ON a.thing_id=b.id WHERE a.id=%d", gGroundItem[playerid][cell][db_id]);
		}
		case VEHICLE_AREA:
		{
			if(gVehicleMenuShow[playerid] == 0)
			    return -1;
	        mysql_format(gMysql, request, sizeof(request), "SELECT a.value,b.name FROM objects a INNER JOIN (things b, objects d, things e) ON (a.thing_id=b.id AND a.id=%d AND d.thing_id=e.id) WHERE d.id=%d AND e.is_vehicle=1",gVehicleItem[gVehicleMenuShow[playerid]][cell][db_id],gVeh[gVehicleMenuShow[playerid]][0]);
		}
		case BAG_AREA:
		{
			if(gBagMenuShow[playerid] == 0 || gBag[playerid][1] <= 0)
			    return -1;
	        mysql_format(gMysql, request, sizeof(request), "SELECT a.value,b.name FROM objects a INNER JOIN (things b, objects d, things e) ON (a.thing_id=b.id AND a.id=%d AND d.thing_id=e.id) WHERE d.id=%d AND e.is_inventory=2",gBagItem[playerid][cell][db_id],gBag[playerid][1]);
		}
		default: return -1;
	}

	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows > 0)
	{
		cache_get_field_content(0, "name", name, gMysql);
		value = cache_get_field_content_int(0, "value", gMysql);
	}
	else
	{
	    return -1;
	}
	if(cache_is_valid(result, gMysql))
		cache_delete(result);
    return 1;
}

//получить имя,значение,хозяина,последнего владельца,их страны и время выкладывания объекта
public get_object_data_all(playerid, cell, area, name[128], &value, owner[128], owner_country[128], last_owner[128], last_owner_country[128], last_time[128], type[128])
{
	new request[1024], buff[512];
	new rows, fields;
	new Cache:result;
	new id;

	if(gPlayersID[playerid] <= 0)
	    return -1;

	strdel(name, 0, sizeof(name)-1);

	if(cell < 0)
	    return -1;

	id = gPlayersID[playerid];
	
	switch(area)
	{
	    case INVENTORY_AREA:
	    {
	        format(buff, sizeof(buff), "SELECT a.value,b.name,IF(a.owner IS NULL,'-',d.name) as ow,IF(a.owner IS NULL,'-',d.country) as ow_cntr,IF(a.is_dropped IS NULL,'-',e.name) as lo,IF(a.is_dropped IS NULL,'-',e.country) as pl_cntr,IF(a.last_time=0,'-',a.last_time) as lt,f.name as tp_nm");
	        mysql_format(gMysql,request,sizeof(request),"%s FROM objects a INNER JOIN (things b,inventory c,players d,players e,thing_type f) ON (a.thing_id=b.id AND a.id=c.inv%d AND d.id=IFNULL(a.owner,c.player_id) AND e.id=IFNULL(a.is_dropped,c.player_id) AND b.type_id=f.id) WHERE c.player_id=%d",buff,cell+1,gPlayersID[playerid]);
//	        printf("%s",request); //отладка!!!
		}
		case GROUND_AREA:
		{
			if(gObjectsMenuShow[playerid] == 0)
			    return -1;
			format(buff, sizeof(buff), "SELECT a.value,b.name,IF(a.owner IS NULL,'-',d.name) as ow,IF(a.owner IS NULL,'-',d.country) as ow_cntr,IF(a.is_dropped IS NULL,'-',e.name) as lo,IF(a.is_dropped IS NULL,'-',e.country) as pl_cntr,IF(a.last_time=0,'-',a.last_time) as lt,f.name as tp_nm");
	        mysql_format(gMysql,request,sizeof(request),"%s FROM objects a INNER JOIN (things b,players d,players e,thing_type f) ON (a.thing_id=b.id AND d.id=IFNULL(a.owner,%d) AND e.id=IFNULL(a.is_dropped,%d) AND b.type_id=f.id) WHERE a.id=%d",buff,id,id,gGroundItem[playerid][cell][db_id]);
		}
		case VEHICLE_AREA:
		{
			if(gVehicleMenuShow[playerid] == 0)
			    return -1;
			format(buff, sizeof(buff), "SELECT a.value,b.name,IF(a.owner IS NULL,'-',f.name) as ow,IF(a.owner IS NULL,'-',f.country) as ow_cntr,IF(a.is_dropped IS NULL,'-',g.name) as lo,IF(a.is_dropped IS NULL,'-',g.country) as pl_cntr,IF(a.last_time=0,'-',a.last_time) as lt,h.name as tp_nm");
	        mysql_format(gMysql,request,sizeof(request),"%s FROM objects a INNER JOIN (things b,veh_invent c,objects d,things e,players f,players g,thing_type h) ON (a.thing_id=b.id AND a.id=c.inv%d AND d.id=c.object_id AND d.thing_id=e.id AND f.id=IFNULL(a.owner,%d) AND g.id=IFNULL(a.is_dropped,%d) AND b.type_id=h.id) WHERE d.id=%d AND e.is_vehicle=1",buff,cell+1,id,id,gVeh[gVehicleMenuShow[playerid]][0]);
		}
		case BAG_AREA:
		{
			if(gBagMenuShow[playerid] == 0 || gBag[playerid][1] <= 0)
			    return -1;
			format(buff, sizeof(buff), "SELECT a.value,b.name,IF(a.owner IS NULL,'-',f.name) as ow,IF(a.owner IS NULL,'-',f.country) as ow_cntr,IF(a.is_dropped IS NULL,'-',g.name) as lo,IF(a.is_dropped IS NULL,'-',g.country) as pl_cntr,IF(a.last_time=0,'-',a.last_time) as lt,h.name as tp_nm");
	        mysql_format(gMysql,request,sizeof(request),"%s FROM objects a INNER JOIN (things b,bag_invent c,objects d,things e,players f,players g,thing_type h) ON (a.thing_id=b.id AND a.id=c.inv%d AND d.id=c.object_id AND d.thing_id=e.id AND f.id=IFNULL(a.owner,%d) AND g.id=IFNULL(a.is_dropped,%d) AND b.type_id=h.id) WHERE d.id=%d AND e.is_inventory=2",buff,cell+1,id,id,gBag[playerid][1]);
		}
		default: return -1;
	}

	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows > 0)
	{
		cache_get_field_content(0, "name", name, gMysql);
		value = cache_get_field_content_int(0, "value", gMysql);
		cache_get_field_content(0, "ow", owner, gMysql, sizeof(owner));
		cache_get_field_content(0, "ow_cntr", owner_country, gMysql, sizeof(last_owner));
		cache_get_field_content(0, "lo", last_owner, gMysql, sizeof(last_owner));
		cache_get_field_content(0, "pl_cntr", last_owner_country, gMysql, sizeof(last_owner));
		cache_get_field_content(0, "lt", last_time, gMysql, sizeof(last_time));
		cache_get_field_content(0, "tp_nm", type, gMysql, sizeof(type));
	}
	else
	{
	    return -1;
	}
	if(cache_is_valid(result, gMysql))
		cache_delete(result);
    return 1;
}

//задаёт текущее оружие персонажа и количество патронов
public give_character_weapon(playerid, cell)
{
	new request[512];
	new rows, fields;
	new object_id, ammo, extra;
	new Cache:result;

	if(gPlayersID[playerid] <= 0)
	    return;

    mysql_format(gMysql, request, sizeof(request), "SELECT b.id,b.value,d.extra FROM inventory a INNER JOIN (objects b,objects c,things d) ON (b.id=a.inv%d AND c.th_owner_id=b.id AND c.thing_id=d.id) WHERE a.player_id=%d AND b.pl_owner_id=%d AND d.is_consumble=1 LIMIT 1", cell+1, gPlayersID[playerid], gPlayersID[playerid]);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows > 0)
	{
		object_id = cache_get_field_content_int(0, "id", gMysql);
		ammo = cache_get_field_content_int(0, "value", gMysql);
		extra = cache_get_field_content_int(0, "extra", gMysql);

		if(gPlayerWeapon[playerid][0] > 0 && gPlayerWeapon[playerid][0] != object_id)
			save_character_ammo(playerid, -1, -1);

		gPlayerWeapon[playerid][0] = object_id;
		gPlayerWeapon[playerid][1] = ammo;
		gPlayerWeapon[playerid][3] = extra;

		//обновляем количество патронов в обоймах (на всякий случай, можно этого и не делать)
		save_character_ammo(playerid, -1, -1);
	}
	else
	{
		if(cache_is_valid(result, gMysql))
			cache_delete(result);
			
	    mysql_format(gMysql, request, sizeof(request), "SELECT b.id,b.value FROM inventory a INNER JOIN objects b ON b.id=a.inv%d WHERE a.player_id=%d AND b.pl_owner_id=%d LIMIT 1", cell+1, gPlayersID[playerid], gPlayersID[playerid]);
		result = mysql_query(gMysql, request);
		cache_get_data(rows, fields, gMysql);
		if(rows > 0)
		{
			object_id = cache_get_field_content_int(0, "id", gMysql);
			ammo = cache_get_field_content_int(0, "value", gMysql);

			if(gPlayerWeapon[playerid][0] > 0 && gPlayerWeapon[playerid][0] != object_id)
				save_character_ammo(playerid, -1, -1);

			gPlayerWeapon[playerid][0] = object_id;
			gPlayerWeapon[playerid][1] = ammo;
			gPlayerWeapon[playerid][3] = extra;

			//обновляем количество патронов в обоймах (на всякий случай, можно этого и не делать)
			save_character_ammo(playerid, -1, -1);
		}
		else
		{
			save_character_ammo(playerid, -1, -1);
			gPlayerWeapon[playerid][0] = 0;
			gPlayerWeapon[playerid][1] = 0;
			gPlayerWeapon[playerid][2] = 0;
			gPlayerWeapon[playerid][3] = 0;
			//отнимаем у персонажа что там у него незаконно лежит
		    mysql_format(gMysql, request, sizeof(request), "UPDATE inventory SET inv%d=-1 WHERE player_id=%d", cell+1, gPlayersID[playerid]);
			mysql_query(gMysql, request);
		}
	}
	if(cache_is_valid(result, gMysql))
		cache_delete(result);
}

//найти следующее оружие в инвентаре
public find_character_weapon(playerid, &cell)
{
	new request[512];
	new rows, fields;
	new Cache:result;
	new i, j;

	if(gPlayersID[playerid] <= 0)
	    return;

	cell = -1;
	j = gIndexCharacterWeapon[playerid]+1;

	for(i = 0; i < MAX_INVENTORY_ON_PLAYER; ++i, ++j)
	{
	    if(j >= MAX_INVENTORY_ON_PLAYER)
			j = 0;

		//ищем всё оружие в инвентаре
	    mysql_format(gMysql, request, sizeof(request), "SELECT a.inv%d as inv FROM inventory a INNER JOIN (objects b, things c, thing_type d) ON (a.inv%d=b.id AND b.thing_id=c.id AND c.type_id=d.id) WHERE d.name in ('ORDINARY_RIFLE_TYPE','ORDINARY_GUN_TYPE','RARE_GUN_TYPE','HAND_WEAPON_TYPE','RARE_HAND_WEAPON_TYPE') AND b.value>0 AND a.player_id=%d LIMIT 1",j+1,j+1,gPlayersID[playerid]);
		result = mysql_query(gMysql, request);
		cache_get_data(rows, fields, gMysql);
		if(rows > 0)
	    {
			gIndexCharacterWeapon[playerid] = j;
			cell = j;
			if(cache_is_valid(result, gMysql))
				cache_delete(result);
			break;
	    }
		if(cache_is_valid(result, gMysql))
			cache_delete(result);
	}
}

//сохраняем количество патронов в самом объекте-оружии
//(а разбрасываем это количество по коробкам только при разборе оружия)
public save_character_ammo(playerid, in_object, in_value)
{
	new request[256];
	new rows, fields;
	new ammo, object_id, main_object, value, row;
	new Cache:result;

	if(gPlayersID[playerid] <= 0)
	    return;

	if(in_object == -1)
	{
		//задаём количество патронов в самом оружии
		if(gPlayerWeapon[playerid][0] != 0)
		{
			mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET value=%d WHERE id=%d", gPlayerWeapon[playerid][1], gPlayerWeapon[playerid][0]);
			mysql_query(gMysql, request);
		}
		else
			return;
		main_object = gPlayerWeapon[playerid][0];
	}
	else
	{
		mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET value=%d WHERE id=%d", in_value, in_object);
		mysql_query(gMysql, request);
		main_object = in_object;
	}
	
	//количество патронов для распределения
	if(in_object == -1)
		value = gPlayerWeapon[playerid][1];
	else
		value = in_value;

	//корректируем расходуемые объекты в составе оружия
    mysql_format(gMysql, request, sizeof(request), "SELECT a.id,a.value,b.extra FROM objects a INNER JOIN things b ON a.thing_id=b.id WHERE a.th_owner_id=%d AND b.is_consumble=1 ORDER BY b.extra", main_object);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows > 0)
	{
	    if(value <= 0)
	    {
			//освобождаем пустые обоймы
			for(row = 0; row < rows; ++row)
			{
			    cache_set_active(result, gMysql);
				object_id = cache_get_field_content_int(row, "id", gMysql);
			    free_object_from_owner(object_id);
			}
			if(cache_is_valid(result, gMysql))
				cache_delete(result);
			return;
		}

	    row = 0;
		while(value > 0 && rows > row) //пока есть патроны для распределения
		{
		    cache_set_active(result, gMysql);
			ammo = cache_get_field_content_int(row, "value", gMysql);
			object_id = cache_get_field_content_int(row, "id", gMysql);
			if(in_object == -1)
				gPlayerWeapon[playerid][3] = cache_get_field_content_int(row, "extra", gMysql);
			
			if(value > ammo)
			{
			    value = value - ammo;
			    row++;
			    continue;
			}
			else
			{
				if(value < ammo)
				{
				    mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET value=%d WHERE id=%d", value, object_id);
					mysql_query(gMysql, request);
//					thread_sql(request);
				}
				//освобождаем пустые обоймы
				for(row = row+1; row < rows; ++row)
				{
				    cache_set_active(result, gMysql);
					object_id = cache_get_field_content_int(row, "id", gMysql);
				    mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET value=%d WHERE id=%d", value, object_id);
					mysql_query(gMysql, request);
				    free_object_from_owner(object_id);
				}
			    break;
			}
			row++;
		}
		
		if(value < 0)
		{
		    //а тут можно античит поставить на патроны (кик там, или бан)
		    //...
		}
		
		if(cache_is_valid(result, gMysql))
			cache_delete(result);
	}
}

//сохранить состояние и координаты авто
public save_vehicle_state(playerid, vehicleid)
{
	new request[1536];
	new is_working, is_engine, is_lights, is_alarm, is_doors, is_bonnet, is_boot, is_objective, panels, doors, lights, tires, patrol;
//	new engine_id;
	new Float:x, Float:y, Float:z, Float:ang, Float:health;
	new rows, fields;
	new bool:is_dotted;
	new Cache:result;

//	gVeh[vehicleid][0] - id объекта

	if(gVeh[vehicleid][0] <= 0)
	{
	    //античит
	    if(!IsPlayerAdmin(playerid))
	    {
	        SendClientMessage(playerid, 0xFFAACCFF, "It was an admin's vehicle!");
	        DestroyVehicle(vehicleid);
	    }
		return;
	}
		
	is_dotted = false;

	//если авто находится на точке респавна - выходим, т.к. обновлять нечего!
    mysql_format(gMysql, request, sizeof(request), "SELECT a.id,b.is_working,b.patrol,b.is_lights,b.accumul FROM objects a INNER JOIN veh_data b ON a.id=b.object_id WHERE id=%d AND dot_id IS NOT NULL LIMIT 1", gVeh[vehicleid][0]);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows > 0)
	{
		is_working = cache_get_field_content_int(0, "is_working", gMysql);
		patrol = cache_get_field_content_int(0, "patrol", gMysql);
		if(cache_is_valid(result, gMysql))
			cache_delete(result);
		if(is_working == gVeh[vehicleid][4] && gVeh[vehicleid][3] == patrol)
		{
			return;
		}
		is_dotted = true;
	}
	if(cache_is_valid(result, gMysql))
		cache_delete(result);

	GetVehicleParamsEx(vehicleid, is_engine, is_lights, is_alarm, is_doors, is_bonnet, is_boot, is_objective);
	
    gVeh[vehicleid][7] = is_lights;

	if(gVeh[vehicleid][3] <= 0 && gVeh[vehicleid][5] > 0)
	{
	    gVeh[vehicleid][3] = 0;
	    gVeh[vehicleid][4] = 0;
		for(new i = 0; i < MAX_PLAYERS; ++i)
		{
		    if(IsPlayerInVehicle(i, vehicleid))
				update_vehicle_sensors(i);
		}
	}
	if(gVeh[vehicleid][2] < 0)
	{
	    gVeh[vehicleid][2] = 0;
	    gVeh[vehicleid][4] = 0;

	    //"освобождение" двигателя от авто
	    mysql_format(gMysql, request, sizeof(request), "SELECT engine_id FROM veh_data WHERE object_id=%d AND engine_id > 0 LIMIT 1", gVeh[vehicleid][0]);
		mysql_query(gMysql, request);
		cache_get_data(rows, fields, gMysql);
		if(rows > 0)
		{
//			engine_id = cache_get_field_content_int(0, "engine_id", gMysql);
			//осторожно! объект может не удалиться при перезагрузке сервера (повторное появление после удаления всех объектов)
			//выход - не вызывать функцию save_vehicle_state при закрытии сервера (создать отдельную функцию для этого, которая не вызывает free_object_from_owner())
			
//			free_object_from_owner(engine_id);

			//думаю вместо поля 'value' объекта-авто использовать 'value' объекта-двигателя (?)
		    mysql_format(gMysql, request, sizeof(request), "UPDATE veh_data SET engine_id=NULL WHERE object_id=%d LIMIT 1", gVeh[vehicleid][0]);
			//mysql_query(gMysql, request);
			thread_sql(request);
		}
	}
	SetVehicleParamsEx(vehicleid, gVeh[vehicleid][4], is_lights, is_alarm, is_doors, is_bonnet, is_boot, is_objective);
	GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
	GetVehiclePos(vehicleid, x, y, z);
	GetVehicleZAngle(vehicleid, ang);
	GetVehicleHealth(vehicleid, health);

	if(playerid != INVALID_PLAYER_ID)
	{
	    if(is_dotted)
	    {
			//сохраняем состояние авто
		    mysql_format(gMysql, request, sizeof(request), "UPDATE objects a,veh_data b SET a.vector=%f,a.placex=%f,a.placey=%f,a.placez=%f,a.add_rotz=%f,a.value=%d,b.panels=%d,b.doors=%d,b.light=%d,b.tires=%d,b.patrol=%d,b.is_working=%d,b.is_lights=%d,b.is_alarm=%d,b.is_bonnet=%d,b.is_boot=%d,b.is_objective=%d,b.health=%f WHERE  a.id=%d AND b.object_id=%d",
															VectorSize(x,y,z),x,y,z,ang,gVeh[vehicleid][2],panels,doors,lights,tires,gVeh[vehicleid][3],gVeh[vehicleid][4],is_lights,is_alarm,is_bonnet,is_boot,is_objective,health,gVeh[vehicleid][0],gVeh[vehicleid][0]);
	    }
	    else
	    {
			//задаём поле 'value' для владельца
		    mysql_format(gMysql, request, sizeof(request), "UPDATE objects a,veh_data b SET a.vector=%f,a.placex=%f,a.placey=%f,a.placez=%f,a.add_rotz=%f,a.dot_id=NULL,is_dropped=%d,a.last_time=NOW(),a.value=%d,b.panels=%d,b.doors=%d,b.light=%d,b.tires=%d,b.patrol=%d,b.is_working=%d,b.is_lights=%d,b.is_alarm=%d,b.is_bonnet=%d,b.is_boot=%d,b.is_objective=%d,b.health=%f,b.accumul=%d WHERE a.id=%d AND (b.object_id=%d)",
															VectorSize(x,y,z),x,y,z,ang,gPlayersID[playerid],gVeh[vehicleid][2],panels,doors,lights,tires,gVeh[vehicleid][3],gVeh[vehicleid][4],is_lights,is_alarm,is_bonnet,is_boot,is_objective,health,gVeh[vehicleid][9],gVeh[vehicleid][0],gVeh[vehicleid][0]);
		}
	}
	else
	{
		//задаём поле 'value' для владельца
	    mysql_format(gMysql, request, sizeof(request), "UPDATE objects a, veh_data b SET a.vector=%f,a.placex=%f,a.placey=%f,a.placez=%f,a.add_rotz=%f,a.dot_id=NULL,a.value=%d,b.panels=%d,b.doors=%d,b.light=%d,b.tires=%d,b.patrol=%d,b.is_working=%d,b.is_lights=%d,b.is_alarm=%d,b.is_bonnet=%d,b.is_boot=%d,b.is_objective=%d,b.health=%f,b.accumul=%d WHERE (a.id=%d) AND b.object_id=%d",
														VectorSize(x,y,z),x,y,z,ang,gVeh[vehicleid][2],panels,doors,lights,tires,gVeh[vehicleid][3],gVeh[vehicleid][4],is_lights,is_alarm,is_bonnet,is_boot,is_objective,health,gVeh[vehicleid][9],gVeh[vehicleid][0],gVeh[vehicleid][0]);
	}
	
	//mysql_query(gMysql, request);
	thread_sql(request);
}

//обязательное сохранение состояния авто
public save_vehicle_position(vehicleid)
{
	new request[1536];
	new Float:x, Float:y, Float:z, Float:ang, Float:health;
	new is_engine, is_lights, is_alarm, is_doors, is_bonnet, is_boot, is_objective, panels, doors, lights, tires;
	new trailerid;
/*
	for(new i = 0; i < MAX_VEHICLES; ++i)
	{
		if(IsTrailerAttachedToVehicle(i))
		{
	    	trailerid = GetVehicleTrailer(i);
	    	if(trailerid == vehicleid) //если это прицеп - выходим
	    	    return;
		}
	}
*/
	GetVehicleParamsEx(vehicleid, is_engine, is_lights, is_alarm, is_doors, is_bonnet, is_boot, is_objective);
	GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
	GetVehiclePos(vehicleid, x, y, z);
	GetVehicleZAngle(vehicleid, ang);
	GetVehicleHealth(vehicleid, health);

    mysql_format(gMysql, request, sizeof(request), "UPDATE objects a,veh_data b SET a.vector=%f,a.placex=%f,a.placey=%f,a.placez=%f,a.add_rotz=%f,a.dot_id=NULL,b.panels=%d,b.doors=%d,b.light=%d,b.tires=%d,b.is_lights=%d,b.is_alarm=%d,b.is_bonnet=%d,b.is_boot=%d,b.is_objective=%d,b.health=%f,b.accumul=%d WHERE a.id=%d AND b.object_id=%d",VectorSize(x,y,z),x,y,z,ang,panels,doors,lights,tires,is_lights,is_alarm,is_bonnet,is_boot,is_objective,health,gVeh[vehicleid][9],gVeh[vehicleid][0],gVeh[vehicleid][0]);
//	mysql_query(gMysql, request);
	thread_sql(request);

	if(IsTrailerAttachedToVehicle(vehicleid))
	{
	    trailerid = GetVehicleTrailer(vehicleid);
	    if(gVeh[trailerid][0] > 0)
		{
	    	mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET vector=%f,placex=%f,placey=%f,placez=%f,add_rotz=%f,dot_id=NULL WHERE id=%d",VectorSize(x,y,z),x+3,y+3,z,ang,gVeh[trailerid][0]);
//			mysql_query(gMysql, request);
			thread_sql(request);
		}
	}
}

//создать новое авто
public create_new_vehicle(object_id, Float:x, Float:y, Float:z, Float:rotz, inworld_id, def_value)
{
	new vehicleid, color1, color2, cells, panels, doors, light, tires, patrol, patrol_cons, max_patrol, is_locked, is_lights, is_alarm, is_bonnet, is_boot, is_objective, accumul_cons, max_accumul, has_num, number[32];
	new request[1536];
	new rows, fields;
	new Cache:result;

	mysql_format(gMysql, request, sizeof(request), "SELECT object_id FROM veh_data WHERE object_id=%d", object_id);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
	{
	    mysql_format(gMysql, request, sizeof(request), "INSERT INTO veh_data(object_id) values(%d)", object_id);
		mysql_query(gMysql, request);
	}
	if(cache_is_valid(result, gMysql))
		cache_delete(result);

	mysql_format(gMysql, request, sizeof(request), "SELECT object_id FROM veh_invent WHERE object_id=%d", object_id);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
	{
	    mysql_format(gMysql, request, sizeof(request), "INSERT INTO veh_invent(object_id) values(%d)", object_id);
		mysql_query(gMysql, request);
	}
	if(cache_is_valid(result, gMysql))
		cache_delete(result);

	mysql_format(gMysql, request, sizeof(request), "UPDATE veh_data SET panels=0,doors=0,light=0,tires=0,patrol=0,is_working=0 WHERE object_id=%d", object_id);
	mysql_query(gMysql, request);

	mysql_format(gMysql, request, sizeof(request), "SELECT a.cells,a.def_panels,a.def_doors,a.def_light,a.def_tires,a.def_patrol,a.patrol_cons,a.max_patrol,a.accumul_cons,a.max_accumul,b.is_locked,b.color1,b.color2,b.is_lights,b.is_alarm,b.is_bonnet,b.is_boot,b.is_objective,b.has_num,b.number FROM objects c INNER JOIN (vehicles a, veh_data b) ON (c.id=b.object_id AND c.thing_id=a.thing_id) WHERE c.id=%d LIMIT 1", object_id);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows > 0)
	{
		color1 = cache_get_field_content_int(0, "color1", gMysql);
		color2 = cache_get_field_content_int(0, "color2", gMysql);
		cells = cache_get_field_content_int(0, "cells", gMysql);
		panels = cache_get_field_content_int(0, "def_panels", gMysql);
		doors = cache_get_field_content_int(0, "def_doors", gMysql);
		light = cache_get_field_content_int(0, "def_light", gMysql);
		tires = cache_get_field_content_int(0, "def_tires", gMysql);
		patrol = cache_get_field_content_int(0, "def_patrol", gMysql);
		patrol_cons = cache_get_field_content_int(0, "patrol_cons", gMysql);
		max_patrol = cache_get_field_content_int(0, "max_patrol", gMysql);
		is_locked = cache_get_field_content_int(0, "is_locked", gMysql);
		is_lights = cache_get_field_content_int(0, "is_lights", gMysql);
		is_alarm = cache_get_field_content_int(0, "is_alarm", gMysql);
		is_bonnet = cache_get_field_content_int(0, "is_bonnet", gMysql);
		is_boot = cache_get_field_content_int(0, "is_boot", gMysql);
		is_objective = cache_get_field_content_int(0, "is_objective", gMysql);
		accumul_cons = cache_get_field_content_int(0, "accumul_cons", gMysql);
		max_accumul = cache_get_field_content_int(0, "max_accumul", gMysql);
		has_num = cache_get_field_content_int(0, "has_num", gMysql);
		if(has_num > 0)
		    cache_get_field_content(0, "number", number, gMysql);
	}
	else
	{
	    is_locked = 0;
	    has_num = 0;
	}
	if(cache_is_valid(result, gMysql))
		cache_delete(result);
	vehicleid = CreateVehicle(inworld_id, x, y, z, rotz, color1, color2, -1); //don't respawn the vehicle
	UpdateVehicleDamageStatus(vehicleid, panels, doors, light, tires);
	gVeh[vehicleid][0] = object_id;
	gVeh[vehicleid][1] = cells; //количество ячеек инвентаря транспорта
	gVeh[vehicleid][2] = def_value; //состояние двигателя по-умолчанию
	gVeh[vehicleid][3] = patrol; //количество бензина по-умолчанию
	gVeh[vehicleid][4] = 0; //двигатель заглушен
	gVeh[vehicleid][5] = patrol_cons; //расход топлива
	gVeh[vehicleid][6] = max_patrol; //объём бака
	gVeh[vehicleid][7] = is_lights; //фары
	gVeh[vehicleid][8] = accumul_cons; //расход заряда
	gVeh[vehicleid][9] = 0; //заряд аккумулятора
	gVeh[vehicleid][10] = max_accumul; //max заряд аккумулятора
	SetVehicleParamsEx(vehicleid, 0, is_lights, is_alarm, is_locked, is_bonnet, is_boot, is_objective); //а вот тут можно включить/выключить фары
	SetVehicleVirtualWorld(vehicleid, 0);
	if(has_num > 0)
		SetVehicleNumberPlate(vehicleid, number);

	//начальная инициализация инвентаря
	cache_vehicle_inventory(vehicleid);

	//сохраняем состояние авто
	mysql_format(gMysql,request,sizeof(request),"UPDATE objects a,veh_data b SET a.unused=0,a.add_rotx=0,a.add_roty=0,a.pl_owner_id=NULL,a.th_owner_id=NULL,a.is_dropped=NULL,a.last_time=0,a.obj_id=%d,a.vector=%f,a.placex=%f,a.placey=%f,a.placez=%f,a.add_rotz=%f,a.value=%d,b.panels=%d,b.doors=%d,b.light=%d,b.tires=%d,b.patrol=%d,b.is_working=%d WHERE a.id=%d AND b.object_id=%d",vehicleid,VectorSize(x,y,z),x,y,z,rotz,def_value,panels,doors,light,tires,patrol,0,object_id,object_id);
	thread_sql(request);
}

//создать перемещённое авто
public create_old_vehicle(object_id, Float:x, Float:y, Float:z, Float:rotz, inworld_id)
{
	new vehicleid, value, color1, color2, cells, panels, doors, light, tires, patrol, patrol_cons, max_patrol, is_working, is_locked, is_lights, is_alarm, is_bonnet, is_boot, is_objective, accumul_cons, max_accumul, accumul, has_num, number[32];
	new Float:health;
	new request[1024];
	new rows, fields;
	new Cache:result;

	mysql_format(gMysql, request, sizeof(request), "SELECT object_id FROM veh_data WHERE object_id=%d", object_id);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
	{
	    mysql_format(gMysql, request, sizeof(request), "INSERT INTO veh_data(object_id) values(%d)", object_id);
		mysql_query(gMysql, request);
	}
	if(cache_is_valid(result, gMysql))
		cache_delete(result);

	mysql_format(gMysql, request, sizeof(request), "SELECT object_id FROM veh_invent WHERE object_id=%d", object_id);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
	{
	    mysql_format(gMysql, request, sizeof(request), "INSERT INTO veh_invent(object_id) values(%d)", object_id);
		mysql_query(gMysql, request);
	}
	if(cache_is_valid(result, gMysql))
		cache_delete(result);

	mysql_format(gMysql, request, sizeof(request), "SELECT c.value,a.cells,a.patrol_cons,a.max_patrol,a.accumul_cons,a.max_accumul,b.color1,b.color2,b.panels,b.doors,b.light,b.tires,b.patrol,b.is_working,b.is_locked,b.is_lights,b.is_alarm,b.is_bonnet,b.is_boot,b.is_objective,b.health,b.accumul,b.has_num,b.number FROM objects c INNER JOIN (vehicles a, veh_data b) ON (c.id=b.object_id AND c.thing_id=a.thing_id) WHERE c.id=%d LIMIT 1", object_id);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows > 0)
	{
		color1 = cache_get_field_content_int(0, "color1", gMysql);
		color2 = cache_get_field_content_int(0, "color2", gMysql);
		cells = cache_get_field_content_int(0, "cells", gMysql);
		panels = cache_get_field_content_int(0, "panels", gMysql);
		doors = cache_get_field_content_int(0, "doors", gMysql);
		light = cache_get_field_content_int(0, "light", gMysql);
		tires = cache_get_field_content_int(0, "tires", gMysql);
		patrol = cache_get_field_content_int(0, "patrol", gMysql);
		patrol_cons = cache_get_field_content_int(0, "patrol_cons", gMysql);
		is_working = cache_get_field_content_int(0, "is_working", gMysql);
		value = cache_get_field_content_int(0, "value", gMysql);
		max_patrol = cache_get_field_content_int(0, "max_patrol", gMysql);
		is_locked = cache_get_field_content_int(0, "is_locked", gMysql);
		is_lights = cache_get_field_content_int(0, "is_lights", gMysql);
		is_alarm = cache_get_field_content_int(0, "is_alarm", gMysql);
		is_bonnet = cache_get_field_content_int(0, "is_bonnet", gMysql);
		is_boot = cache_get_field_content_int(0, "is_boot", gMysql);
		is_objective = cache_get_field_content_int(0, "is_objective", gMysql);
		health = cache_get_field_content_float(0, "health", gMysql);
		accumul_cons = cache_get_field_content_int(0, "accumul_cons", gMysql);
		max_accumul = cache_get_field_content_int(0, "max_accumul", gMysql);
		accumul = cache_get_field_content_int(0, "accumul", gMysql);
		has_num = cache_get_field_content_int(0, "has_num", gMysql);
		if(has_num)
		    cache_get_field_content(0, "number", number, gMysql);
	}
	else
	{
	    is_locked = 0;
	    patrol_cons = 10;
	    patrol = 0;
	    is_lights = 0;
	    accumul = 0;
	    accumul_cons = 10;
	    health = 1000.0;
	    has_num = 0;
	}
	if(cache_is_valid(result, gMysql))
		cache_delete(result);
	vehicleid = CreateVehicle(inworld_id, x, y, z, rotz, color1, color2, -1); //don't respawn the vehicle
	SetVehicleParamsEx(vehicleid, is_working, is_lights, is_alarm, is_locked, is_bonnet, is_boot, is_objective); //а вот тут можно включить/выключить фары
	SetVehicleHealth(vehicleid, health);
	UpdateVehicleDamageStatus(vehicleid, panels, doors, light, tires);
	gVeh[vehicleid][0] = object_id;
	gVeh[vehicleid][1] = cells; //количество ячеек инвентаря транспорта
	gVeh[vehicleid][2] = value; //состояние двигателя
	gVeh[vehicleid][3] = patrol; //количество бензина
	gVeh[vehicleid][4] = is_working; //двигатель работает/заглушен
	gVeh[vehicleid][5] = patrol_cons; //расход топлива
	gVeh[vehicleid][6] = max_patrol; //объём бака
	gVeh[vehicleid][7] = is_lights; //фары
	gVeh[vehicleid][8] = accumul_cons; //расход заряда
	gVeh[vehicleid][9] = accumul; //заряд аккумулятора
	gVeh[vehicleid][10] = max_accumul; //max заряд аккумулятора
	SetVehicleVirtualWorld(vehicleid, 0);
	if(has_num > 0)
		SetVehicleNumberPlate(vehicleid, number);

	//начальная инициализация инвентаря
	cache_vehicle_inventory(vehicleid);

	mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET obj_id=%d WHERE id=%d", vehicleid, object_id);
	thread_sql(request);
}

public set_vehicle_number(playerid, number[32])
{
	new vehicleid;
	new request[256];
	new color_number[32];
	
	format(color_number, sizeof(color_number), "{000000}%s", number);
	vehicleid = GetPlayerVehicleID(playerid);
	SetVehicleNumberPlate(vehicleid, color_number);
	
    mysql_format(gMysql, request, sizeof(request), "UPDATE veh_data SET has_num=1,number=\"%s\" WHERE object_id=%d", color_number, gVeh[vehicleid][0]);
	thread_sql(request);
}

//создать новый рюкзак
public create_new_bag(obj_id)
{
	new request[128];
	new rows, fields;
	new Cache:result;

	mysql_format(gMysql, request, sizeof(request), "SELECT object_id FROM bag_invent WHERE object_id=%d", obj_id);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
	{
	    mysql_format(gMysql, request, sizeof(request), "INSERT INTO bag_invent(object_id) values(%d)", obj_id);
		mysql_query(gMysql, request);
	}
	if(cache_is_valid(result, gMysql))
		cache_delete(result);
}

//удалить авто из точки появления, если оно не находится в этой точке
public drop_vehicle_from_dot(playerid, vehicleid)
{
	new request[1024];
	new Float:x, Float:y, Float:z;

	if(gPlayersID[playerid] <= 0)
	    return;

	GetVehiclePos(vehicleid, x, y, z);

	mysql_format(gMysql, request, sizeof(request), "UPDATE object_dot a, objects b SET a.last_time=NOW(),a.object_id=NULL,b.dot_id=NULL,b.is_dropped=%d WHERE a.object_id=%d AND b.id=%d AND (a.placex-%f)*(a.placex-%f)+(a.placey-%f)*(a.placey-%f)+(a.placez-%f)*(a.placez-%f)>10", gPlayersID[playerid], gVeh[vehicleid][0], gVeh[vehicleid][0], x, x, y, y, z, z);
	thread_sql(request);
}

public load_a_bag(playerid, cell)
{
	new request[128];
	new rows, fields;
	new value, id, owner;
	new Cache:result;

	if(gPlayersID[playerid] <= 0)
	    return;

    mysql_format(gMysql, request, sizeof(request), "SELECT id,value,IFNULL(owner,0) as owner FROM objects WHERE id=%d LIMIT 1",gInventoryItem[playerid][cell][db_id]);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows > 0)
	{
		id = cache_get_field_content_int(0, "id", gMysql);
		owner = cache_get_field_content_int(0, "owner", gMysql);
		if(owner != 0 && owner != gPlayersID[playerid])
		{
			drop_object_on_ground(playerid, id);
		    gBag[playerid][0] = 0; //ячеек в рюкзаке
		    gBag[playerid][1] = 0; //объект рюкзака
		    return;
		}
		value = cache_get_field_content_int(0, "value", gMysql);
		
		if(value > MAX_INVENTORY_IN_BAG)
		    value = MAX_INVENTORY_IN_BAG;
		if(value < 0)
		    value = 0;
	    gBag[playerid][0] = value; //ячеек в рюкзаке
	    gBag[playerid][1] = id; //объект рюкзака
	}
	else
	{
	    gBag[playerid][0] = 0;
	    gBag[playerid][1] = 0;
	}
	if(cache_is_valid(result, gMysql))
		cache_delete(result);
}

//присвоить объект новому объекту-владельцу
//т.к. объект становится присвоенным объекту, то он больше не может находиться в инвентаре
//но (!) эта функция не меняет инвентарь персонажа (необходимо позаботиться об этом при вызове данной функции)
//зато это позволяет вызывать функцию для всех объектов, а не только тех, что в инвентаре
public set_object_owner(th_owner_id, object_id)
{
	new request[512];
	new rows, fields;
	new value, old_value, max_value;
	new Cache:result;
	new obj_id, is_catalyst;

	//объект не может принадлежать сам себе (по-идее)
	if(th_owner_id == object_id)
	    return -1;

    mysql_format(gMysql, request, sizeof(request), "SELECT a.value as value,d.is_catalyst,IFNULL(a.obj_id,%d) as obj_id,b.value as old_value,c.max_value FROM objects a, objects b, things c, things d WHERE a.id=%d AND b.id=%d AND c.id=b.thing_id AND a.thing_id=d.id LIMIT 1",INVALID_OBJECT_ID,object_id,th_owner_id);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows > 0)
	{
		is_catalyst = cache_get_field_content_int(0, "is_catalyst", gMysql);
		if(is_catalyst == 1)
		{
			if(cache_is_valid(result, gMysql))
				cache_delete(result);
		    return -1;
		}
		value = cache_get_field_content_int(0, "value", gMysql);
		obj_id = cache_get_field_content_int(0, "obj_id", gMysql);
		old_value = cache_get_field_content_int(0, "old_value", gMysql);
		max_value = cache_get_field_content_int(0, "max_value", gMysql);
	}
	else
	    value = 0;
	if(cache_is_valid(result, gMysql))
		cache_delete(result);

	if( (max_value != 0) && ((old_value + value) > max_value) )
	    return -2;

	if(IsValidObject(obj_id))
	    DestroyObject(obj_id);

	//задаём поле 'value' для владельца
    mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET value=value+%d WHERE id=%d",value,th_owner_id);
	mysql_query(gMysql, request);
	
	//немного корректируем базу
	//указываем вледельца для объекта и обнуляем поле игрового объекта и точки появления объекта, а также  указываем unused=0
	//сохраняем id прежнего владельца, если таковой был (!)
    mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET vector=NULL,placex=NULL,placey=NULL,placez=NULL,add_rotx=0,add_roty=0,add_rotz=0,pl_owner_id=NULL,th_owner_id=%d,obj_id=NULL,dot_id=NULL,unused=0 WHERE id=%d",th_owner_id,object_id);
	mysql_query(gMysql, request);
//	thread_sql(request);

	//обНУЛЛяем объект для точки появления и обновляем время обновления точки
    mysql_format(gMysql, request, sizeof(request), "UPDATE object_dot SET object_id=NULL,last_time=now() WHERE object_id=%d",object_id);
	thread_sql(request);

	return 1;
}

//получить из базы свободный (unused=true) объект заданного типа, либо создать новый такой
//используется для создания композитных объектов-владельцев из комбинации некоторых существующих объектов
public get_unused_object(thing_id)
{
	new request[256];
	new rows, fields;
	new object_id;
	new Cache:result, Cache:res;

    mysql_format(gMysql, request, sizeof(request), "SELECT id FROM objects WHERE thing_id=%d AND unused=1 LIMIT 1", thing_id);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
	{
	    mysql_format(gMysql, request, sizeof(request), "INSERT INTO objects SET thing_id=%d,next_id=%d,unused=1,value=(SELECT def_value FROM things WHERE id=%d LIMIT 1)", thing_id, thing_id, thing_id);
		mysql_query(gMysql, request);

	    mysql_format(gMysql, request, sizeof(request), "SELECT id FROM objects WHERE thing_id=%d AND unused=1 LIMIT 1", thing_id);
		res = mysql_query(gMysql, request);
		cache_get_data(rows, fields, gMysql);
		if(rows == 0)
		{
		    return -1;
		}
		else
		{
			object_id = cache_get_field_content_int(0, "id", gMysql);
		}
		if(cache_is_valid(res, gMysql))
			cache_delete(res);
	}
	else
	{
		object_id = cache_get_field_content_int(0, "id", gMysql);
	}
	if(cache_is_valid(result, gMysql))
		cache_delete(result);

	return object_id;
}

//создать резидентный объект (для объектов, помеченных как '!' в файле описания вещей)
public create_resident_object(object_id, old_thing_id, new_thing_id)
{
	new request[256];

	//если вещи совпадают - сохраняем value!
	if(old_thing_id == new_thing_id)
	{
	    mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET thing_id=%d,prev_id=%d WHERE id=%d", new_thing_id, old_thing_id, object_id);
	}
	else
	{
	    mysql_format(gMysql, request, sizeof(request), "UPDATE objects a, things b SET a.thing_id=%d,a.prev_id=IF(prev_id is NULL OR prev_id<0,%d,prev_id),a.value=b.def_value WHERE a.id=%d AND b.id=%d", new_thing_id, old_thing_id, object_id, new_thing_id);
	}
	mysql_query(gMysql, request);
}

//проверяем составляющие объекты на максимальное значение
public check_object_owner(playerid, vehicleid, owner_cell, area)
{
	new request[512];
	new out[512];
	new buff[128];
	new rows, fields;
	new Cache:result;
	new summa, value, max_value;
	
    strdel(out, 0, sizeof(out)-1);

	switch(area)
	{
		case INVENTORY_AREA:
		{
		    //проверяем выбранные объекты
			for(new i = 0; i < MAX_INVENTORY_ON_PLAYER; ++i)
			{
			    //если ячейка выбрана и не является ячейкой объекта-владельца
			    if(gRotate[playerid][i] > 0 && i != owner_cell)
			    {
					strdel(buff, 0, sizeof(buff)-1);
					if(strlen(out) > 0)
					    format(buff, sizeof(buff), " OR a.id=%d", gInventoryItem[playerid][i][db_id]);
					else
					    format(buff, sizeof(buff), "a.id=%d", gInventoryItem[playerid][i][db_id]);
					strcat(out, buff);
				}
			}
			if(strlen(out) == 0)
			    return 1;
		    mysql_format(gMysql, request, sizeof(request), "SELECT SUM(a.value) as summa,b.value,c.max_value FROM objects a,objects b,things c WHERE (%s) AND (b.id=%d AND c.id=b.thing_id)",out,gInventoryItem[playerid][owner_cell][db_id]);
			result = mysql_query(gMysql, request);
			cache_get_data(rows, fields, gMysql);
			if(rows <= 0)
			    return 2;
			summa = cache_get_field_content_int(0, "summa", gMysql);
			value = cache_get_field_content_int(0, "value", gMysql);
			max_value = cache_get_field_content_int(0, "max_value", gMysql);
			if(cache_is_valid(result, gMysql))
				cache_delete(result);

			if(max_value == 0)
			    return 1;

			if((summa + value) <= max_value)
				return 1;
			else
			    return 0;
  		}
  		case VEHICLE_AREA:
  		{
			//получаем инвентарь авто
			//load_vehicle_inventory(vehicleid, inv_veh, obj_veh, thng_veh);
			
		    //проверяем выбранные объекты
			for(new i = 0; i < gVeh[vehicleid][1]; ++i)
			{
			    //если ячейка выбрана и не является ячейкой объекта-владельца
			    if(gRotateVehicle[playerid][i] > 0 && i != owner_cell)
			    {
					strdel(buff, 0, sizeof(buff)-1);
					if(strlen(out) > 0)
					    format(buff, sizeof(buff), " OR a.id=%d", gVehicleItem[vehicleid][i][db_id]);
					else
					    format(buff, sizeof(buff), "a.id=%d", gVehicleItem[vehicleid][i][db_id]);
					strcat(out, buff);
				}
			}
			if(strlen(out) == 0)
			    return 1;
		    mysql_format(gMysql, request, sizeof(request), "SELECT SUM(a.value) as summa,b.value,c.max_value FROM objects a,objects b,things c WHERE (%s) AND (b.id=%d AND c.id=b.thing_id)",out,gVehicleItem[vehicleid][owner_cell][db_id]);
			result = mysql_query(gMysql, request);
			cache_get_data(rows, fields, gMysql);
			if(rows <= 0)
			    return 2;
			summa = cache_get_field_content_int(0, "summa", gMysql);
			value = cache_get_field_content_int(0, "value", gMysql);
			max_value = cache_get_field_content_int(0, "max_value", gMysql);
			if(cache_is_valid(result, gMysql))
				cache_delete(result);

			if(max_value == 0)
			    return 1;

			if((summa + value) <= max_value)
				return 1;
			else
			    return 0;
		}
		case GROUND_AREA:
		{
			//получаем объекты с земли
			//load_ground_inventory(playerid, invent_ground);
			
		    //проверяем выбранные объекты
			for(new i = 0; i < MAX_INVENTORY_ON_GROUND; ++i)
			{
			    //если ячейка выбрана и не является ячейкой объекта-владельца
			    if(gRotateObject[playerid][i] > 0 && i != owner_cell)
			    {
					strdel(buff, 0, sizeof(buff)-1);
					if(strlen(out) > 0)
					    format(buff, sizeof(buff), " OR a.id=%d", gGroundItem[playerid][i][db_id]);
					else
					    format(buff, sizeof(buff), "a.id=%d", gGroundItem[playerid][i][db_id]);
					strcat(out, buff);
				}
			}
			if(strlen(out) == 0)
			    return 1;
		    mysql_format(gMysql, request, sizeof(request), "SELECT SUM(a.value) as summa,b.value,c.max_value FROM objects a,objects b,things c WHERE (%s) AND (b.id=%d AND c.id=b.thing_id)",out,gGroundItem[playerid][owner_cell][db_id]);
			result = mysql_query(gMysql, request);
			cache_get_data(rows, fields, gMysql);
			if(rows <= 0)
			    return 2;
			summa = cache_get_field_content_int(0, "summa", gMysql);
			value = cache_get_field_content_int(0, "value", gMysql);
			max_value = cache_get_field_content_int(0, "max_value", gMysql);
			if(cache_is_valid(result, gMysql))
				cache_delete(result);

			if(max_value == 0)
			    return 1;

			if(summa + value <= max_value)
				return 1;
			else
			    return 0;
		}
		case BAG_AREA:
		{
			//получаем инвентарь рюкзака
			//load_bag_inventory(playerid, inv_bag, obj_bag, thng_bag);
			
		    //проверяем выбранные объекты
			for(new i = 0; i < gBag[playerid][0]; ++i)
			{
			    //если ячейка выбрана и не является ячейкой объекта-владельца
			    if(gRotateBag[playerid][i] > 0 && i != owner_cell)
			    {
					strdel(buff, 0, sizeof(buff)-1);
					if(strlen(out) > 0)
					    format(buff, sizeof(buff), " OR a.id=%d", gBagItem[playerid][i][db_id]);
					else
					    format(buff, sizeof(buff), "a.id=%d", gBagItem[playerid][i][db_id]);
					strcat(out, buff);
				}
			}
			if(strlen(out) == 0)
			    return 1;
		    mysql_format(gMysql, request, sizeof(request), "SELECT SUM(a.value) as summa,b.value,c.max_value FROM objects a,objects b,things c WHERE (%s) AND (b.id=%d AND c.id=b.thing_id)",out,gBagItem[playerid][owner_cell][db_id]);
			result = mysql_query(gMysql, request);
			cache_get_data(rows, fields, gMysql);
			if(rows <= 0)
			    return 2;
			summa = cache_get_field_content_int(0, "summa", gMysql);
			value = cache_get_field_content_int(0, "value", gMysql);
			max_value = cache_get_field_content_int(0, "max_value", gMysql);
			if(cache_is_valid(result, gMysql))
				cache_delete(result);

			if(max_value == 0)
			    return 1;

			if((summa + value) <= max_value)
				return 1;
			else
			    return 0;
		}
		default: return 3;
	}
	
	return 1;
}

//создать новую составную вещь
public create_composite_object(playerid, extra[], &cell)
{
	new i,res;
	new request[256];
	new thing[8];
	new owner_cell; //ячейка, где будет находиться созданный объект
	new owner_id; //id объекта-владельца
	new no_selected;
	new main_thing_id;

	owner_id = -1;
	owner_cell = -1;

	cell = -1;

	//для начала определяем, какие ячейки инвентаря выбраны и генерируем запрос
	strdel(request, 0, sizeof(request)-1);
	for(i = 0, no_selected = 1; i < MAX_INVENTORY_ON_PLAYER; ++i)
	{
	    if(gRotate[playerid][i] > 0)
	    {
	        if(strlen(request) != 0)
	            strcat(request, ",");
			strdel(thing, 0, sizeof(thing)-1);
	        format(thing, sizeof(thing), "%d", gInventoryItem[playerid][i][tp_id]);
			strcat(request, thing);
			no_selected = 0;
		}
	}

	if(no_selected == 1)
	    return 0;

	res = composit_thing_ex(request, extra, main_thing_id);

//	printf("res=%d,main_thing_id=%d,request=%s,extra=%s",res,main_thing_id,request,extra); //отладка!!!

	if(res > 0) //если объект создаётся
	{
	    //создаём объект-владелец (если он уже находится среди выбранных объектов)
		for(i = 0; i < MAX_INVENTORY_ON_PLAYER; ++i)
		{
		    //если объект выбран
            if(gRotate[playerid][i] > 0)
            {
				//если в правиле прописан резидентный объект (значок '!')
				//задаём приоритет резидентному объекту
                if(main_thing_id != 0)
                {
				    //если объект резидентный
				    if( main_thing_id == gInventoryItem[playerid][i][tp_id] || gInventoryItem[playerid][i][tp_id] == -main_thing_id )
				    {
					    //проверяем выбранные объекты на максимальное значение
				        if(check_object_owner(playerid, -1, i, INVENTORY_AREA) == 0)
				            return -1;

						//заменяем id вещи этого объекта на id вещи создаваемого
						//при этом запоминаем прежний id в поле objects.prev_id (изменения касаются только БД)
			            create_resident_object(gInventoryItem[playerid][i][db_id], main_thing_id, res);
				        //оставляем этот объект в его ячейке как есть (т.е делаем его владельцем)
				        owner_cell = i;
				        owner_id = gInventoryItem[playerid][i][db_id];
						set_character_inventory_cell(playerid, owner_cell, owner_id, true);
				        break;
					}
                }
                else if(gInventoryItem[playerid][i][tp_id] == res) //если тип объекта совпадает с типом создаваемой вещи
			    {
				    //проверяем выбранные объекты на максимальное значение
			        if(check_object_owner(playerid, -1, i, INVENTORY_AREA) == 0)
			            return -1;

			        //оставляем этот объект в его ячейке как есть (т.е делаем его владельцем)
			        owner_cell = i;
			        owner_id = gInventoryItem[playerid][i][db_id];
			        break;
				}
			}
		}

		//создаём объект-владелец
		if(owner_id < 0)
		{
		    //а тут проверка на максимум не требуется!

		    //получаем свободный объект с заданного типа (либо создаём новый свободный этого типа)
		    owner_id = get_unused_object(res);
		    if(owner_id < 0)
		    {
				print("no free unused object!");
		        return 0;
			}
		}

		if(owner_id == gPlayerWeapon[playerid][0])
		{
			//сохраним патрончики
    		save_character_ammo(playerid, -1, -1);
		}

	    //присваиваем выбранные объекты (попутно освобождая инвентарь)
		for(i = 0; i < MAX_INVENTORY_ON_PLAYER; ++i)
		{
		    //если ячейка выбрана и не является ячейкой объекта-владельца
		    if(gRotate[playerid][i] > 0 && i != owner_cell)
		    {
		        //присваиваем объекту-владельцу
		        set_object_owner(owner_id, gInventoryItem[playerid][i][db_id]);
		        //удаляем из инвентаря (сбрасываем gInv и gInvThing для текущей ячейки)
		        set_character_inventory_cell(playerid, i, -1, true);
			}
		}

		//выбираем для объекта-владельца самую старшую ячейку (если ячейка для него ещё не выбрана)
        if(owner_cell < 0) //если объект-владелец ещё не находится в ячейке
        {
			//ищем самую старшую освобождённую ячейку
			for(i = 0; i < MAX_INVENTORY_ON_PLAYER; ++i)
			{
			    if(gRotate[playerid][i] > 0)
			    {
			    	owner_cell = i;
			    	break;
				}
			}

			//помещаем объект-владелец в найденную ячейку
			//эта функция автоматически установит unused=0
			set_character_inventory_cell(playerid, owner_cell, owner_id, true);
//			print("zero()"); //отладка!!!
		}
//		SendClientMessage(playerid, 0x00FF00, "ok!"); //отладка!!!
	}
	else
	{
	    //по-сути, тут надо бы организовать добавление элементов к композитному объекту
	    return 0;
	}

	cell = owner_cell;
	
//	printf("res=%d,main_thing_id=%d,db_id=%d,tp_id=%d,playerid=%d,cell=%d,owner_id=%d",res,main_thing_id,gInventoryItem[playerid][cell][db_id],gInventoryItem[playerid][cell][tp_id],playerid,cell,owner_id); //отладка!!!
	
	if(owner_id == gPlayerWeapon[playerid][0])
	    return 1; //если обновилось активное оружие игрока, сообщаем об этом
	else
		return 0; //owner_cell; //возвращаем номер ячейки с новым объектом
}

//создать новую составную вещь
public create_composite_object_veh(playerid, vehicleid, extra[], &cell)
{
	new i,res;
	new request[256];
	new thing[32];
	new owner_cell; //ячейка, где будет находиться созданный объект
	new owner_id; //id объекта-владельца
	new no_selected;
	new main_thing_id;

	owner_id = -1;
	owner_cell = -1;

	cell = -1;

	//для начала определяем, какие ячейки инвентаря выбраны
	//и генерируем запрос
	strdel(request, 0, sizeof(request)-1);
	for(i = 0, no_selected = 1; i < gVeh[vehicleid][1]; ++i)
	{
	    if(gRotateVehicle[playerid][i] > 0)
	    {
	        if(strlen(request) != 0)
	            strcat(request, ",");
			strdel(thing, 0, sizeof(thing)-1);
	        format(thing, sizeof(thing), "%d", gVehicleItem[vehicleid][i][tp_id]);
			strcat(request, thing);
			no_selected = 0;
		}
	}

	if(no_selected == 1)
	{
	    return 0;
	}

	res = composit_thing_ex(request, extra, main_thing_id);

//	printf("res=%d,main_thing_id=%d,request=%s",res,main_thing_id,request); //отладка!!!

	if(res > 0) //если объект создаётся
	{
	    //создаём объект-владелец (если он уже находится среди выбранных объектов)
		for(i = 0; i < gVeh[vehicleid][1]; ++i)
		{
		    //если объект выбран
            if(gRotateVehicle[playerid][i] > 0)
            {
				//если в правиле прописан резидентный объект (значок '!')
				//задаём приоритет резидентному объекту
                if(main_thing_id != 0)
                {
				    //если объект резидентный
				    if( main_thing_id == gVehicleItem[vehicleid][i][tp_id] || gVehicleItem[vehicleid][i][tp_id] == -main_thing_id )
				    {
					    //проверяем выбранные объекты на максимальное значение
				        if(check_object_owner(playerid, vehicleid, i, VEHICLE_AREA) == 0)
				            return -1;

						//заменяем id вещи этого объекта на id вещи создаваемого
						//при этом запоминаем прежний id в поле objects.prev_id
			            create_resident_object(gVehicleItem[vehicleid][i][db_id], main_thing_id, res);
				        //оставляем этот объект в его ячейке как есть (т.е делаем его владельцем)
				        owner_cell = i;
				        owner_id = gVehicleItem[vehicleid][i][db_id];
						set_vehicle_inventory_cell(vehicleid, owner_cell, owner_id, true);
				        break;
					}
                }
                else if(gVehicleItem[vehicleid][i][tp_id] == res) //если тип объекта совпадает с типом создаваемой вещи
			    {
				    //проверяем выбранные объекты на максимальное значение
			        if(check_object_owner(playerid, vehicleid, i, VEHICLE_AREA) == 0)
			            return -1;

			        //оставляем этот объект в его ячейке как есть (т.е делаем его владельцем)
			        owner_cell = i;
			        owner_id = gVehicleItem[vehicleid][i][db_id];
			        break;
				}
			}
		}

		//создаём объект-владелец
		if(owner_id < 0)
		{
		    //получаем свободный объект с заданного типа (либо создаём новый свободный этого типа)
		    owner_id = get_unused_object(res);
		    if(owner_id < 0)
		    {
				print("no free unused object!");
		        return 0;
			}
		}

	    //присваиваем выбранные объекты (попутно освобождая инвентарь)
		for(i = 0; i < gVeh[vehicleid][1]; ++i)
		{
		    //если ячейка выбрана и не является ячейкой объекта-владельца
		    if(gRotateVehicle[playerid][i] > 0 && i != owner_cell)
		    {
		        //присваиваем объекту-владельцу
		        set_object_owner(owner_id, gVehicleItem[vehicleid][i][db_id]);
		        //удаляем из инвентаря (сбрасываем gInv и gInvThing для текущей ячейки)
		        set_vehicle_inventory_cell(vehicleid, i, -1, true);
			}
		}

		//выбираем для объекта-владельца самую старшую ячейку (если ячейка для него ещё не выбрана)
        if(owner_cell < 0) //если объект-владелец ещё не находится в ячейке
        {
			//ищем самую старшую освобождённую ячейку
			for(i = 0; i < gVeh[vehicleid][1]; ++i)
			{
			    if(gRotateVehicle[playerid][i] > 0)
			    {
			    	owner_cell = i;
			    	break;
				}
			}

			//помещаем объект-владелец в найденную ячейку
			//эта функция автоматически установит unused=0
			set_vehicle_inventory_cell(vehicleid, owner_cell, owner_id, true);
		}
	}
	else
	{
	    //по-сути, тут надо бы организовать добавление элементов к композитному объекту
	    return 0;
	}

	cell = owner_cell;

	return 1;
}

//создать новую составную вещь на земле
public create_composite_object_obj(playerid, extra[])
{
	new i,res;
	new request[256];
	new thing[32];
	new owner_cell;
	new owner_id; //id объекта-владельца
	new no_selected;
	new main_thing_id;
	new Float:x,Float:y,Float:z;

	//для начала определяем, какие ячейки инвентаря выбраны
	//и генерируем запрос
	strdel(request, 0, sizeof(request)-1);
	for(i = 0, no_selected = 1; i < MAX_INVENTORY_ON_GROUND; ++i)
	{
	    if(gRotateObject[playerid][i] > 0)
	    {
	        if(strlen(request) != 0)
	            strcat(request, ",");
			strdel(thing, 0, sizeof(thing)-1);
	        format(thing, sizeof(thing), "%d", gGroundItem[playerid][i][tp_id]);
			strcat(request, thing);
			no_selected = 0;
		}
	}

	if(no_selected == 1)
	    return -1;

	res = composit_thing_ex(request, extra, main_thing_id);

	//printf("ground: res=%d,main_thing_id=%d,request=%s",res,main_thing_id,request); //отладка!!!

	if(res > 0) //если объект создаётся
	{
	    //создаём объект-владелец (если он уже находится среди выбранных объектов)
		for(i = 0; i < MAX_INVENTORY_ON_GROUND; ++i)
		{
		    //если объект выбран
            if(gRotateObject[playerid][i] > 0)
            {
				//если в правиле прописан резидентный объект (значок '!')
				//задаём приоритет резидентному объекту
                if(main_thing_id != 0)
                {
				    //если объект резидентный
				    if( main_thing_id == gGroundItem[playerid][i][tp_id] || gGroundItem[playerid][i][tp_id] == -main_thing_id )
				    {
					    //проверяем выбранные объекты на максимальное значение
				        if(check_object_owner(playerid, -1, i, GROUND_AREA) == 0)
				            return -3;

						//заменяем id вещи этого объекта на id вещи создаваемого
						//при этом запоминаем прежний id в поле objects.prev_id
			            create_resident_object(gGroundItem[playerid][i][db_id], main_thing_id, res);
				        //оставляем этот объект в его ячейке как есть (т.е делаем его владельцем)
				        owner_id = gGroundItem[playerid][i][db_id];
				        owner_cell = i;
						//set_ground_inventory_cell(playerid, owner_cell, owner_id, true);
						init_craft_item(gGroundItem[playerid][i], owner_id);
				        break;
					}
                }
                else if(gGroundItem[playerid][i][tp_id] == res) //если тип объекта совпадает с типом создаваемой вещи
			    {
				    //проверяем выбранные объекты на максимальное значение
			        if(check_object_owner(playerid, -1, i, GROUND_AREA) == 0)
			            return -3;

			        //оставляем этот объект в его ячейке как есть (т.е делаем его владельцем)
			        owner_id = gGroundItem[playerid][i][db_id];
			        owner_cell = i;
			        break;
				}
			}
		}

		//создаём объект-владелец
		if(owner_id < 0)
		{
		    //получаем свободный объект с заданного типа (либо создаём новый свободный этого типа)
		    owner_id = get_unused_object(res);
		    if(owner_id < 0)
		    {
				print("no free unused object!");
		        return -2;
			}
		}

	    //присваиваем выбранные объекты (попутно освобождая инвентарь)
		for(i = 0; i < MAX_INVENTORY_ON_GROUND; ++i)
		{
		    //если ячейка выбрана и не является ячейкой объекта-владельца
		    if(gRotateObject[playerid][i] > 0 && i != owner_cell)
		    {
		        //присваиваем объекту-владельцу
		        set_object_owner(owner_id, gGroundItem[playerid][i][db_id]);
				zero_craft_item(gGroundItem[playerid][i]);
			}
		}
	}
	else
	{
	    //по-сути, тут надо бы организовать добавление элементов к композитному объекту
	    return -4;
	}

	GetPlayerPos(playerid, x,y,z);
	SetPlayerPos(playerid, x+0.001,y,z);
	//необходимо обновить меню объектов в вызвавшей функции

	//printf("ground: res=%d,main_thing_id=%d,db_id=%d,tp_id=%d,playerid=%d,cell=%d,owner_id=%d,+1=%d",res,main_thing_id,gGroundItem[playerid][owner_cell][db_id],gGroundItem[playerid][owner_cell][tp_id],playerid,owner_cell,owner_id,gGroundItem[playerid][owner_cell+1][db_id]); //отладка!!!
	
	//cache_ground_inventory(playerid, gStandartRangeValue);
	
	return owner_cell;
}

public create_composite_object_bag(playerid, extra[], &cell)
{
	new i,res;
	new request[256];
	new thing[32];
	new owner_cell; //ячейка, где будет находиться созданный объект
	new owner_id; //id объекта-владельца
	new no_selected;
	new main_thing_id;

	owner_id = -1;
	owner_cell = -1;

	cell = -1;

	if(gBag[playerid][0] <= 0 || gBag[playerid][1] <= 0)
	    return -1;

	//для начала определяем, какие ячейки инвентаря выбраны
	//и генерируем запрос
	strdel(request, 0, sizeof(request)-1);
	for(i = 0, no_selected = 1; i < gBag[playerid][0]; ++i)
	{
	    if(gRotateBag[playerid][i] > 0)
	    {
	        if(strlen(request) != 0)
	            strcat(request, ",");
			strdel(thing, 0, sizeof(thing)-1);
	        format(thing, sizeof(thing), "%d", gBagItem[playerid][i][tp_id]);
			strcat(request, thing);
			no_selected = 0;
		}
	}

	if(no_selected == 1)
	{
	    return -2;
	}

	res = composit_thing_ex(request, extra, main_thing_id);

	//printf("res=%d,main_thing_id=%d,request=%s,gBag[playerid][0]=%d,gBag[playerid][1]=%d",res,main_thing_id,request,gBag[playerid][0],gBag[playerid][1]); //отладка!!!

	if(res > 0) //если объект создаётся
	{
	    //создаём объект-владелец (если он уже находится среди выбранных объектов)
		for(i = 0; i < gBag[playerid][0]; ++i)
		{
		    //если объект выбран
            if(gRotateBag[playerid][i] > 0)
            {
				//если в правиле прописан резидентный объект (значок '!')
				//задаём приоритет резидентному объекту
                if(main_thing_id != 0)
                {
				    //если объект резидентный
				    if( main_thing_id == gBagItem[playerid][i][tp_id] || gBagItem[playerid][i][tp_id] == -main_thing_id )
				    {
					    //проверяем выбранные объекты на максимальное значение
				        if(check_object_owner(playerid, -1, i, BAG_AREA) == 0)
				            return -3;

						//заменяем id вещи этого объекта на id вещи создаваемого
						//при этом запоминаем прежний id в поле objects.prev_id
			            create_resident_object(gBagItem[playerid][i][db_id], main_thing_id, res);
				        //оставляем этот объект в его ячейке как есть (т.е делаем его владельцем)
				        owner_cell = i;
				        owner_id = gBagItem[playerid][i][db_id];
						set_bag_inventory_cell(playerid, owner_cell, owner_id, true);
				        break;
					}
                }
                else if(gBagItem[playerid][i][tp_id] == res) //если тип объекта совпадает с типом создаваемой вещи
			    {
				    //проверяем выбранные объекты на максимальное значение
			        if(check_object_owner(playerid, -1, i, BAG_AREA) == 0)
			            return -3;

			        //оставляем этот объект в его ячейке как есть (т.е делаем его владельцем)
			        owner_cell = i;
			        owner_id = gBagItem[playerid][i][db_id];
			        break;
				}
			}
		}

		//создаём объект-владелец
		if(owner_id < 0)
		{
		    //получаем свободный объект с заданного типа (либо создаём новый свободный этого типа)
		    owner_id = get_unused_object(res);
		    if(owner_id < 0)
		    {
				print("no free unused object!");
		        return -4;
			}
		}

	    //присваиваем выбранные объекты (попутно освобождая инвентарь)
		for(i = 0; i < gBag[playerid][0]; ++i)
		{
		    //если ячейка выбрана и не является ячейкой объекта-владельца
		    if(gRotateBag[playerid][i] > 0 && i != owner_cell)
		    {
		        //присваиваем объекту-владельцу
		        set_object_owner(owner_id, gBagItem[playerid][i][db_id]);
		        //удаляем из инвентаря (сбрасываем gBagObj и gBagMod для текущей ячейки)
		        set_bag_inventory_cell(playerid, i, -1, true);
			}
		}

		//выбираем для объекта-владельца самую старшую ячейку (если ячейка для него ещё не выбрана)
        if(owner_cell < 0) //если объект-владелец ещё не находится в ячейке
        {
			//ищем самую старшую освобождённую ячейку
			for(i = 0; i < gBag[playerid][0]; ++i)
			{
			    if(gRotateBag[playerid][i] > 0)
			    {
			    	owner_cell = i;
			    	break;
				}
			}

			//помещаем объект-владелец в найденную ячейку
			//эта функция автоматически установит unused=0
			set_bag_inventory_cell(playerid, owner_cell, owner_id, true);
		}
	}
	else
	{
	    //по-сути, тут надо бы организовать добавление элементов к композитному объекту
	    return -5;
	}

	cell = owner_cell;
	
	if(owner_id == gPlayerWeapon[playerid][0])
	    return 1; //если обновилось активное оружие игрока, сообщаем об этом
	else
		return 0; //owner_cell; //возвращаем номер ячейки с новым объектом
}

//разобрать композитный объект
public disassemble_resident_object(object_id, prev_id)
{
	new request[256];

	//если объект неразбираемый, либо не резидентный - выходим!
	if(prev_id <= 0)
	    return;

	//value можно также сохранять, как и thing_id
	//а вообще можно устанавливать value в def_value прежнего объекта(прямо в этом же запросе)
	//...
//    mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET prev_id=thing_id,thing_id=%d,value=0 WHERE id=%d", prev_id, object_id);
    mysql_format(gMysql, request, sizeof(request), "UPDATE objects a, things b SET a.prev_id=NULL,a.thing_id=%d,a.value=b.def_value WHERE a.id=%d AND b.id=%d", prev_id, object_id, prev_id);
	mysql_query(gMysql, request);
//	thread_sql(request);
}

//разобрать композитный объект
//подразумевает появление составляющих объектов в инвентаре игрока, либо рядом с игроком
public disassemble_cell_object(playerid, cell)
{
	new request[256];
	new rows, fields;
	new object_id, pl_owner_id, thing_id, prev_id, is_inventory;
	new i, j, pl_id;
	new th_owner_id;
	new Cache:ids;
	new Float:x, Float:y, Float:z;
	//new prev_cell;

	if(cell < 0)
	    return -10;

	if(playerid < 0)
	    return -20;

	if(gPlayersID[playerid] <= 0)
	    return -25;

    GetPlayerPos(playerid, x, y, z);

	//ищем объект (можно найти все объекты инвентаря и исходя из этого искать свободные ячейки) (?)
	th_owner_id = gInventoryItem[playerid][cell][db_id];
	if(th_owner_id < 0)
	    return -30;
	pl_owner_id = gInventoryItem[playerid][cell][obj_owner];
	thing_id = gInventoryItem[playerid][cell][tp_id];
	prev_id = gInventoryItem[playerid][cell][pr_id];
	is_inventory = gInventoryItem[playerid][cell][obj_inventory];

	//если это неразбираемый композитный объект - выходим!
	if(prev_id < 0)
	    return -50;

	//а вот тута необходимо проверить, разбираемый (композитный) это объект или нет!
	if(is_composit(thing_id) < 0)
	    return -60;

	pl_id = gPlayersID[playerid];
	
	//если такого игрока не существует - выходим
	if(pl_id == INVALID_PLAYER_ID)
	{
	    print("error: invalid playerid!");
	    return -80;
 	}

	//надо сверить playerid и pl_id. если не совпадают, удалить объект pl_owner_id у playerid из ячейки cell
	if(pl_owner_id > 0 && pl_owner_id != pl_id)
	{
	    print("error: wrong playerid!");
	    //удаляем объект
	    //...
	    return -70;
	}

	//сохраним-ка мы тут патрончики, не помешает
	save_character_ammo(playerid, -1, -1);

	//освободим рюкзак от содержимого
	if(is_inventory == 2)
	    free_owner_from_objects(playerid, th_owner_id);

	//ищем все объекты, для которых разбираемый объект является хозяином
    mysql_format(gMysql, request, sizeof(request), "SELECT id FROM objects WHERE th_owner_id=%d AND unused=0 ORDER BY id DESC", th_owner_id);
	ids = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows > 0)
	{
		if(prev_id == 0)
		{
			//полностью освобождаем ячейку с композитным/резидентным объектом
			set_character_inventory_cell(playerid, cell, -1, true);
		}

		for(i = 0; i < rows; ++i)
		{
			//ищем свободную ячейку
			for(j = 0; j < MAX_INVENTORY_ON_PLAYER; ++j)
			{
				if(gInventoryItem[playerid][j][db_id] == -1)
				{
				    cache_set_active(ids, gMysql);
				    //если находим пустую ячейку - помещаем туда объект
					object_id = cache_get_field_content_int(i, "id", gMysql);
					set_character_inventory_cell(playerid, j, object_id, true);
					break;
				}
			}
			if(j == MAX_INVENTORY_ON_PLAYER)
			{
			    if(is_inventory != 2 && gBag[playerid][1] > 0)
			    {
					//ищем свободную ячейку
					for(j = 0; j < gBag[playerid][0]; ++j)
					{
						if(gBagItem[playerid][j][db_id] == -1)
						{
						    cache_set_active(ids, gMysql);
						    //если находим пустую ячейку - помещаем туда объект
							object_id = cache_get_field_content_int(i, "id", gMysql);
							set_bag_inventory_cell(playerid, j, object_id, true);
							break;
						}
					}
			    }

				if( (is_inventory == 2 && gBag[playerid][1] > 0) || gBag[playerid][1] <= 0 || j == gBag[playerid][0])
				{
				    cache_set_active(ids, gMysql);
					object_id = cache_get_field_content_int(i, "id", gMysql);
					drop_object_on_ground(playerid, object_id);
				}
			}
		}
		//удаляем результат поиска
		if(cache_is_valid(ids, gMysql))
			cache_delete(ids, gMysql);
	}
	else
	{
		//удаляем результат поиска
		if(cache_is_valid(ids, gMysql))
			cache_delete(ids, gMysql);

	    //если композитный нерезидентный объект не является хозяином ни для одного другого объекта - выходим!
		if(prev_id == 0)
		    return -90;
	}

	if(prev_id > 0)
	{
	    //разбираем резидентный объект
	    disassemble_resident_object(th_owner_id, prev_id);
	    init_craft_item(gInventoryItem[playerid][cell], th_owner_id);
	}
	else if(prev_id == 0)
	{
		//т.к. у композитного объекта больше нету составляющих, он удаляется
		mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET vector=NULL,placex=NULL,placey=NULL,placez=NULL,add_rotx=0,add_roty=0,add_rotz=0,pl_owner_id=NULL,th_owner_id=NULL,obj_id=NULL,dot_id=NULL,value=0,unused=1 WHERE id=%d", th_owner_id);
		mysql_query(gMysql, request);
//		thread_sql(request);
	}

	if(th_owner_id == gPlayerWeapon[playerid][0])
	{
		//убираем оружие из рук
		ResetPlayerWeapons(playerid);
		gPlayerWeapon[playerid][0] = 0;
		gPlayerWeapon[playerid][1] = 0;
		gPlayerWeapon[playerid][2] = 0;
		gPlayerWeapon[playerid][3] = 0;
	}

	//остаётся только обновить меню у вызвавшего игрока (делается это в вызвавшей функции)

	return 0;
}

//разобрать композитный объект из инвентаря авто
//подразумевает появление составляющих объектов в инвентаре авто, либо в инвентаре игрока, либо рядом с авто
public disassemble_cell_object_veh(vehicleid, cell)
{
	new request[256];
	new rows, fields;
	new object_id, thing_id, prev_id, prev_cell;
	new i, j, count;
	new th_owner_id;
	new Cache:ids;

	if(vehicleid <= 0 || cell < 0)
	    return -1;

//	strdel(col_name, 0, sizeof(col_name)-1);
//	format(col_name, sizeof(col_name), "inv%d", cell+1);
//	get_character_value(playerid, col_name, "inventory", result);

	th_owner_id = gVehicleItem[vehicleid][cell][db_id];
	if(th_owner_id < 0)
	    return -1;

	thing_id = gVehicleItem[vehicleid][cell][tp_id];
	prev_id = gVehicleItem[vehicleid][cell][pr_id];

	//если это неразбираемый композитный объект - выходим!
	if(prev_id < 0)
	    return -1;

	//а вот тута необходимо проверить, разбираемый (композитный) это объект или нет!
	if(is_composit(thing_id) < 0)
	    return -1;

	//ищем все объекты, для которых разбираемый объект является хозяином
    mysql_format(gMysql, request, sizeof(request), "SELECT id FROM objects WHERE th_owner_id=%d AND unused=0 ORDER BY id DESC", th_owner_id);
	mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows > 0)
	{
		//сосчитаем свободные ячейки инвентаря авто
		if(prev_id > 0)
		    count = 0; //ячейка не освободится
		else
		{
			prev_cell = cell;
			count = 1; //одна освободится из-под композитного объекта
		}

		for(i = 0; i < gVeh[vehicleid][1]; ++i)
		{
		    if(gVehicleItem[vehicleid][i][db_id] == -1)
		    {
			    prev_cell = i;
		        count++;
			}
		}

		//если нет свободных ячеек - выходим
		if(count <= 0)
		    return -1;

		//сохраняем предыдущий результат перед новым обращением к БД
		ids = cache_save(gMysql);

		if(prev_id == 0)
		{
			//полностью освобождаем ячейку с композитным/резидентным объектом
			set_vehicle_inventory_cell(vehicleid, cell, -1, true);
		}
		
		for(i = 0; i < rows; ++i)
		{
			//ищем свободную ячейку
			//...
			for(j = 0; j < gVeh[vehicleid][1]; ++j)
			{
				if(gVehicleItem[vehicleid][j][db_id] == -1)
				{
					prev_cell = j;
				    //если находим пустую ячейку - помещаем туда объект
				    cache_set_active(ids, gMysql);
					object_id = cache_get_field_content_int(i, "id", gMysql);
					set_vehicle_inventory_cell(vehicleid, j, object_id, true);
					break;
				}
			}
			if(j == gVeh[vehicleid][1])
			{
			    //если пустой ячейки нет - выкладываем из последней занятой ячейки и помещаем туда
	            drop_vehicle_inventory_cell(vehicleid, prev_cell);
			    cache_set_active(ids, gMysql);
				object_id = cache_get_field_content_int(i, "id", gMysql);
				set_vehicle_inventory_cell(vehicleid, prev_cell, object_id, true);
				break;
			}
		}
		//удаляем результат поиска
		if(cache_is_valid(ids, gMysql))
			cache_delete(ids, gMysql);
	}
	else
	{
		//удаляем результат поиска
		if(cache_is_valid(ids, gMysql))
			cache_delete(ids, gMysql);

	    //если композитный нерезидентный объект не является хозяином ни для одного другого объекта - выходим!
		if(prev_id == 0)
		    return -1;
	}

	if(prev_id > 0)
	{
	    //разбираем резидентный объект
	    disassemble_resident_object(th_owner_id, prev_id);
	    init_craft_item(gVehicleItem[vehicleid][cell], th_owner_id);
	}
	else if(prev_id == 0)
	{
		//т.к. у композитного объекта больше нету составляющих, он удаляется
		mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET vector=NULL,placex=NULL,placey=NULL,placez=NULL,add_rotx=0,add_roty=0,add_rotz=0,pl_owner_id=NULL,th_owner_id=NULL,obj_id=NULL,dot_id=NULL,value=0,unused=1 WHERE id=%d", th_owner_id);
		mysql_query(gMysql, request);
//		thread_sql(request);
	}

	//остаётся только обновить меню у вызвавшего игрока (делается это в вызвавшей функции)

	return 0;
}

public disassemble_cell_object_bag(playerid, cell)
{
	new request[256];
	new rows, fields;
	new object_id, thing_id, prev_id;
	new i, j, count;
	new th_owner_id;
	new Cache:ids;
	//new Float:x, Float:y, Float:z;
	//new prev_cell;

	if(playerid < 0 || cell < 0)
	    return -1;

	th_owner_id = gBagItem[playerid][cell][db_id];
	if(th_owner_id < 0)
	    return -1;

	thing_id = gBagItem[playerid][cell][tp_id];
	prev_id = gBagItem[playerid][cell][pr_id];

	//если это неразбираемый композитный объект - выходим!
	if(prev_id < 0)
	    return -1;

	//а вот тута необходимо проверить, разбираемый (композитный) это объект или нет!
	if(is_composit(thing_id) < 0)
	    return -1;

	//ищем все объекты, для которых разбираемый объект является хозяином
    mysql_format(gMysql, request, sizeof(request), "SELECT id FROM objects WHERE th_owner_id=%d AND unused=0 ORDER BY id DESC", th_owner_id);
	ids = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows > 0)
	{
		//сосчитаем свободные ячейки инвентаря рюкзака
		if(prev_id > 0)
		    count = 0; //ячейка не освободится
		else
		{
			//prev_cell = cell;
			count = 1; //одна освободится из-под композитного объекта
		}

		for(i = 0; i < gBag[playerid][0]; ++i)
		{
		    if(gBagItem[playerid][i][db_id] == -1)
		    {
			    //prev_cell = i;
		        count++;
			}
		}

		//если нет свободных ячеек - выходим
		if(count <= 0)
		    return -1;

		if(prev_id == 0)
		{
			//полностью освобождаем ячейку с композитным/резидентным объектом
			set_bag_inventory_cell(playerid, cell, -1, true);
		}

		for(i = 0; i < rows; ++i)
		{
			//ищем свободную ячейку
			for(j = 0; j < gBag[playerid][0]; ++j)
			{
				if(gBagItem[playerid][j][db_id] == -1)
				{
					//prev_cell = j;
				    //если находим пустую ячейку - помещаем туда объект
				    cache_set_active(ids, gMysql);
					object_id = cache_get_field_content_int(i, "id", gMysql);
					set_bag_inventory_cell(playerid, j, object_id, true);
					break;
				}
			}
			if(j == gBag[playerid][0])
			{
				for(j = 0; j < MAX_INVENTORY_ON_PLAYER; ++j)
				{
					if(gInventoryItem[playerid][j][db_id] == -1)
					{
					    //prev_cell = j;
					    //если находим пустую ячейку - помещаем туда объект
					    cache_set_active(ids, gMysql);
						object_id = cache_get_field_content_int(i, "id", gMysql);
						set_character_inventory_cell(playerid, j, object_id, true);
						break;
					}
				}
				if(j == MAX_INVENTORY_ON_PLAYER)
				{
				    cache_set_active(ids, gMysql);
					object_id = cache_get_field_content_int(i, "id", gMysql);
					drop_object_on_ground(playerid, object_id);
				}
			}
		}
		//удаляем результат поиска
		if(cache_is_valid(ids, gMysql))
			cache_delete(ids, gMysql);
	}
	else
	{
		//удаляем результат поиска
		if(cache_is_valid(ids, gMysql))
			cache_delete(ids, gMysql);

	    //если композитный нерезидентный объект не является хозяином ни для одного другого объекта - выходим!
		if(prev_id == 0)
		    return -1;
	}

	if(prev_id > 0)
	{
	    //разбираем резидентный объект
	    disassemble_resident_object(th_owner_id, prev_id);
	    init_craft_item(gBagItem[playerid][cell], th_owner_id);
	}
	else if(prev_id == 0)
	{
		//т.к. у композитного объекта больше нету составляющих, он удаляется
		mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET vector=NULL,placex=NULL,placey=NULL,placez=NULL,add_rotx=0,add_roty=0,add_rotz=0,pl_owner_id=NULL,th_owner_id=NULL,obj_id=NULL,dot_id=NULL,value=0,unused=1 WHERE id=%d", th_owner_id);
		mysql_query(gMysql, request);
//		thread_sql(request);
	}

	//остаётся только обновить меню у вызвавшего игрока (делается это в вызвавшей функции)

	return 0;
}

//разобрать объект
public disassemble_inventory_object(object_id)
{
	new request[256];
	new rows, fields, i;
	new playerid, cell, pl_owner_id;
	new Cache:result;

	if(object_id <= 0)
	    return -1;

    mysql_format(gMysql, request, sizeof(request), "SELECT IFNULL(pl_owner_id,0) as pl_owner FROM objects WHERE id=%d LIMIT 1", object_id);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
	    return -1;
	pl_owner_id = cache_get_field_content_int(0, "pl_owner", gMysql);
	if(cache_is_valid(result, gMysql))
		cache_delete(result);

	playerid = INVALID_PLAYER_ID;
	for(i = 0; i < MAX_PLAYERS; ++i)
	{
	    if(gPlayersID[i] == pl_owner_id)
	    {
	        playerid = i;
	        break;
	    }
	}
	if(playerid == INVALID_PLAYER_ID)
	    return -1;

	cell = -1;
	for(i = 0; i < MAX_INVENTORY_ON_PLAYER; ++i)
	{
	    if(gInventoryItem[playerid][i][db_id] == object_id)
	    {
	        cell = i;
	        break;
		}
	}
	if(cell < 0)
	    return -1;

	disassemble_cell_object(playerid, cell);

	return cell;
}

//разобрать композитный объект, лежащий на земле
//подразумевает появление составляющих объектов рядом с игроком
public disassemble_ground_object(playerid, cell)
{
	new request[256];
	new rows, fields;
	new object_id, thing_id, prev_id, obj_id;
	new i;
	new th_owner_id;
	new Cache:ids;

	if(playerid < 0 || cell < 0)
	    return -1;

	th_owner_id = gGroundItem[playerid][cell][db_id];
	if(th_owner_id < 0)
	    return -2;

	obj_id = gGroundItem[playerid][cell][object];
	thing_id = gGroundItem[playerid][cell][tp_id];
	prev_id = gGroundItem[playerid][cell][pr_id];

	//если это неразбираемый композитный объект - выходим!
	if(prev_id < 0)
	    return -4;

	//а вот тута необходимо проверить, разбираемый (композитный) это объект или нет!
	if(is_composit(thing_id) < 0)
	    return -5;

	//ищем все объекты, для которых разбираемый объект является хозяином
    mysql_format(gMysql, request, sizeof(request), "SELECT id FROM objects WHERE th_owner_id=%d AND unused=0 ORDER BY id DESC", th_owner_id);
	ids = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows > 0)
	{
		for(i = 0; i < rows; ++i)
		{
			//восстанавливаем кэш, т.к. он изменяется другими функциями
			cache_set_active(ids, gMysql);
			object_id = cache_get_field_content_int(i, "id", gMysql);
            drop_object_on_ground(playerid, object_id);
		}
		//удаляем результат поиска
		if(cache_is_valid(ids, gMysql))
			cache_delete(ids, gMysql);
	}
	else
	{
		//удаляем результат поиска
		if(cache_is_valid(ids, gMysql))
			cache_delete(ids, gMysql);

	    //если композитный нерезидентный объект не является хозяином ни для одного другого объекта - выходим!
		if(prev_id == 0)
		    return -6;
	}

	if(prev_id > 0)
	{
	    //разбираем резидентный объект
	    disassemble_resident_object(th_owner_id, prev_id);
	    //создаём его новое отображение
		drop_object_on_ground(playerid, th_owner_id);
	}
	else if(prev_id == 0)
	{
		//т.к. у композитного объекта больше нету составляющих, он удаляется
		mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET vector=NULL,placex=NULL,placey=NULL,placez=NULL,add_rotx=0,add_roty=0,add_rotz=0,pl_owner_id=NULL,th_owner_id=NULL,obj_id=NULL,dot_id=NULL,value=0,unused=1 WHERE id=%d", th_owner_id);
		mysql_query(gMysql, request);
//		thread_sql(request);
		//удаляем отображение объекта
		if(IsValidObject(obj_id))
			DestroyObject(obj_id);
	}

	//остаётся только обновить меню у вызвавшего игрока (делается это в вызвавшей функции)

	return 0;
}

//выковырять объект из композитного объекта
//подразумевает появление объекта в инвентаре, либо рядом с игроком
public pick_object_from_owner(obj_id)
{
}

//освободить объект, находящийся в ячейке инвентаря
public free_cell_from_owner(playerid, cell)
{
	new Float:x,Float:y,Float:z;

	free_object_from_owner(gInventoryItem[playerid][cell][db_id]);

	if(IsPlayerInAnyVehicle(playerid) && gVehicleMenuShow[playerid] > 0)
	{
		GetVehiclePos(gVehicleMenuShow[playerid], x,y,z);
		SetVehiclePos(gVehicleMenuShow[playerid], x+0.001,y,z);
	}
	else
	{
		GetPlayerPos(playerid, x,y,z);
		SetPlayerPos(playerid, x+0.001,y,z);
	}

	zero_craft_item(gInventoryItem[playerid][cell]);
}

//освободить объект, находящийся в ячейке инвентаря
public free_cell_from_owner_veh(vehicleid, cell)
{
	free_object_from_owner(gVehicleItem[vehicleid][cell][db_id]);
	zero_craft_item(gVehicleItem[vehicleid][cell]);
}

//освободить объект, находящийся на земле
public free_cell_from_owner_obj(playerid, cell)
{
	new Float:x,Float:y,Float:z;

	if(cell >= 0)
	{
		if(gGroundItem[playerid][cell][db_id] > 0)
			free_object_from_owner(gGroundItem[playerid][cell][db_id]);
	}
	GetPlayerPos(playerid, x,y,z);
	SetPlayerPos(playerid, x+0.001,y,z);

	zero_craft_item(gGroundItem[playerid][cell]);
}

public free_cell_from_owner_bag(playerid, cell)
{
	free_object_from_owner(gBagItem[playerid][cell][db_id]);
	zero_craft_item(gBagItem[playerid][cell]);
}

//освободить объект от владельца (для таких заканчивающихся объектов, как патроны, колёса, двигатели и т.д.)
//освободить все объекты, зависимые от данного
//подразумевает появление объекта на свободном месте в игровом мире
public full_free_object_from_owner(object_id)
{
	new rows, fields, i, id;
	new request[512];
	new Cache:result;

	if(object_id <= 0)
	    return;

	//освободим объект от владельца
	clear_all_owners(object_id);

	//находим и освобождаем всё, для чего объект является владельцем
	//не разбираются вложенные композитные объекты!!!
    mysql_format(gMysql, request, sizeof(request), "SELECT id FROM objects WHERE th_owner_id=%d", object_id);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows > 0)
	{
		for(i = 0; i < rows; ++i)
		{
			cache_set_active(result, gMysql);
			id = cache_get_field_content_int(i, "id", gMysql);
			//освободим объект от владельца
			clear_all_owners(id);
			put_object_on_free_place(id);
		}
	}
	if(cache_is_valid(result, gMysql))
		cache_delete(result);

	//размещаем объект в свободном месте (эта функция обНУЛЛяет многие поля объекта)
	put_object_on_free_place(object_id);
}

//освободить объект от владельца (для таких заканчивающихся объектов, как патроны, колёса, двигатели и т.д.)
//подразумевает появление объекта на свободном месте в игровом мире
public free_object_from_owner(object_id)
{
	if(object_id <= 0)
	    return;

	//освободим объект от владельца
	clear_all_owners(object_id);
	//размещаем объект в свободном месте (эта функция обНУЛЛяет многие поля объекта)
	put_object_on_free_place(object_id);
}

//недоработанная функция (не подходит для опустошения рюкзаков!)
public free_owner_from_objects(playerid, object_id)
{
	new request[256];
	new rows, fields;
	new id, i, j, is_inventory;
	new Cache:result;

	if(object_id <= 0)
	    return;

	//ищем владельца объекта и тип вещи
    mysql_format(gMysql, request, sizeof(request), "SELECT a.id, c.is_inventory FROM objects a INNER JOIN (objects b, things c) ON (b.thing_id=c.id AND a.th_owner_id=b.id) WHERE a.th_owner_id=%d", object_id);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows > 0)
	{
		is_inventory = cache_get_field_content_int(0, "is_inventory", gMysql);

		for(i = 0; i < rows; ++i)
		{
			//ищем свободную ячейку
			for(j = 0; j < MAX_INVENTORY_ON_PLAYER; ++j)
			{
				if(is_inventory != 2 && gInventoryItem[playerid][j][db_id] == -1)
				{
				    cache_set_active(result, gMysql);
				    //если находим пустую ячейку - помещаем туда объект
					id = cache_get_field_content_int(i, "id", gMysql);
					set_character_inventory_cell(playerid, j, id, true);
					break;
				}
			}
			if(j == MAX_INVENTORY_ON_PLAYER)
			{
			    cache_set_active(result, gMysql);
				id = cache_get_field_content_int(i, "id", gMysql);
				if(is_inventory != 2)
					drop_object_on_ground(playerid, id);
				else
					drop_bag_object_on_ground(playerid, id);
			}
		}
	}

	if(cache_is_valid(result, gMysql))
		cache_delete(result);
}

public full_free_object_by_ingame_id(ingame_id)
{
	new id, object_id, prev_id, rows, fields;
	new request[512];
	new Cache:result;

	if(ingame_id == INVALID_OBJECT_ID)
	    return;

	//получаем высоту, тип вещи, вращение и модель объекта
    mysql_format(gMysql, request, sizeof(request), "SELECT a.id,IFNULL(a.prev_id,0) as prev_id FROM objects a INNER JOIN things b ON a.thing_id=b.id WHERE a.obj_id=%d AND b.is_disappeared=1 LIMIT 1", ingame_id);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
	{
	    printf("error in full_free_object_by_ingame_id: no such object (id=%d)", ingame_id);
	    return;
	}
	object_id = cache_get_field_content_int(0, "id", gMysql);
	prev_id = cache_get_field_content_int(0, "prev_id", gMysql);

	if(cache_is_valid(result, gMysql))
		cache_delete(result);

	//освободим объект от владельца
	clear_all_owners(object_id);

	//находим и освобождаем всё, для чего объект является владельцем
	//не разбираются вложенные композитные объекты!!!
    mysql_format(gMysql, request, sizeof(request), "SELECT id FROM objects WHERE th_owner_id=%d", object_id);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows > 0)
	{
		for(new i = 0; i < rows; ++i)
		{
		    cache_set_active(result, gMysql);
			id = cache_get_field_content_int(i, "id", gMysql);
			//освободим объект от владельца
			clear_all_owners(id);
			put_object_on_free_place(id);
		}
	}
	if(cache_is_valid(result, gMysql))
		cache_delete(result);
		
	//разбираем, если объект резидентный
	disassemble_resident_object(object_id, prev_id);
	
	//размещаем объект в свободном месте (эта функция обНУЛЛяет многие поля объекта)
	put_object_on_free_place(object_id);
}

stock put_object_on_free_place(object_id)
{
	new rows, fields, dot_id, obj_id, inworld_id, type_id, def_value, is_vehicle, rotatable, ret, next_id, count;
	new request[512];
	new Float:x, Float:y, Float:z, Float:rotx, Float:roty, Float:rotz, Float:height, Float:add_rotx, Float:add_roty;
	new Float:Z_coord, Float:Alpha, Float:Beta;
	new Cache:result;

	if(object_id <= 0)
	    return;

   	mysql_format(gMysql, request, sizeof(request), "SELECT count(*) as cnt FROM objects WHERE th_owner_id=%d", object_id);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
	    return;
	count = cache_get_field_content_int(0, "cnt", gMysql);

	//получаем высоту, тип вещи, вращение и модель объекта
	if(count > 0)
	    mysql_format(gMysql, request, sizeof(request), "SELECT b.posx,b.posy,b.posz,b.height,b.inworld_id,b.type_id,b.rotatable,b.def_value,b.is_vehicle,IFNULL(a.obj_id,%d) as object_id,IFNULL(a.dot_id,0) as dot_id,a.next_id FROM objects a INNER JOIN things b ON a.next_id=b.id WHERE a.id=%d LIMIT 1", INVALID_OBJECT_ID, object_id);
	else
    	mysql_format(gMysql, request, sizeof(request), "SELECT b.posx,b.posy,b.posz,b.height,b.inworld_id,b.type_id,b.rotatable,b.def_value,b.is_vehicle,IFNULL(a.obj_id,%d) as object_id,IFNULL(a.dot_id,0) as dot_id, a.next_id FROM objects a INNER JOIN things b ON a.thing_id=b.id WHERE a.id=%d LIMIT 1", INVALID_OBJECT_ID, object_id);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
	{
	    print("error in put_object_on_free_place(): no such object");
	    return;
	}
	rotx = cache_get_field_content_float(0, "posx", gMysql);
	roty = cache_get_field_content_float(0, "posy", gMysql);
	rotz = cache_get_field_content_float(0, "posz", gMysql);
	height = cache_get_field_content_float(0, "height", gMysql);
	inworld_id = cache_get_field_content_int(0, "inworld_id", gMysql);
	type_id = cache_get_field_content_int(0, "type_id", gMysql);
	rotatable = cache_get_field_content_int(0, "rotatable", gMysql);
	def_value = cache_get_field_content_int(0, "def_value", gMysql);
	is_vehicle = cache_get_field_content_int(0, "is_vehicle", gMysql);
	obj_id = cache_get_field_content_int(0, "object_id", gMysql);
	dot_id = cache_get_field_content_int(0, "dot_id", gMysql);
	next_id = cache_get_field_content_int(0, "next_id", gMysql);
	if(cache_is_valid(result, gMysql))
		cache_delete(result);

	if(dot_id > 0)
	{
	    mysql_format(gMysql, request, sizeof(request), "UPDATE object_dot a, objects b SET a.object_id=NULL,a.last_time=NOW(),b.dot_id=NULL WHERE a.object_id=%d AND b.id=%d", object_id, object_id);
		thread_sql(request);
	}

	//получаем координаты
    mysql_format(gMysql, request, sizeof(request), "SELECT a.id,a.placex,a.placey,a.placez FROM object_dot a INNER JOIN dot_type b ON a.id=b.dot_id WHERE object_id IS NULL AND b.type_id=%d ORDER BY last_time LIMIT 1", type_id);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
	{
		//удаляем прежнюю модель
		if(IsValidObject(obj_id))
		    DestroyObject(obj_id);

		//обновляем БД
		if(count <= 0)
		    mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET thing_id=%d,prev_id=NULL,vector=NULL,placex=NULL,placey=NULL,placez=NULL,add_rotx=0,add_roty=0,add_rotz=0,obj_id=NULL,dot_id=NULL,pl_owner_id=NULL,th_owner_id=NULL,value=%d,unused=0 WHERE id=%d", next_id, def_value, object_id);
		else
		    mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET vector=NULL,placex=NULL,placey=NULL,placez=NULL,add_rotx=0,add_roty=0,add_rotz=0,obj_id=NULL,dot_id=NULL,pl_owner_id=NULL,th_owner_id=NULL,value=%d,unused=0 WHERE id=%d", def_value, object_id);
		mysql_query(gMysql, request);
	    return;
	}
	dot_id = cache_get_field_content_int(0, "id", gMysql);
	x = cache_get_field_content_float(0, "placex", gMysql);
	y = cache_get_field_content_float(0, "placey", gMysql);
	z = cache_get_field_content_float(0, "placez", gMysql);
	if(cache_is_valid(result, gMysql))
		cache_delete(result);

	//создаём саму модель
	if(is_vehicle == 1)
	{
	    for(new i = 0; i < MAX_VEHICLES; ++i)
	    {
	        if(gVeh[i][0] == object_id)
	        {
		        DestroyVehicle(i);
				for(new k = 0; k < VEHICLE_BUFFER_DATA_NUMBER; ++k)
				{
			        gVeh[i][k] = 0;
				}
		        break;
	        }
		}
		create_new_vehicle(object_id, x, y, z, rotz, inworld_id, def_value);
	    mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET dot_id=%d,unused=0 WHERE id=%d", dot_id, object_id);
		mysql_query(gMysql, request);
	}
	else
	{
	    add_rotx = 0;
	    add_roty = 0;
	    if(rotatable)
	    {
	        Alpha = rotz;
	        //получаем углы поворота
			ret = MapAndreas_Valid_Z_Coordinate(x,y,z,Z_coord,Alpha,Beta);
			if(ret == 0)
			{
			    add_rotx = Beta;
			    add_roty = Alpha;
			}
			else
			{
			    add_rotx = 0.001;
			    add_roty = 0.001;
			}
	    }
	    
		//удаляем прежнюю модель
		if(IsValidObject(obj_id))
		    DestroyObject(obj_id);

	    if((rotatable == 1) && (ret == 0))
			obj_id = CreateObject(inworld_id, x, y, z+height, rotx+add_rotx, roty+add_roty, rotz, OBJECT_DISTANCE);
	    else
			obj_id = CreateObject(inworld_id, x, y, z+height, rotx, roty, rotz, OBJECT_DISTANCE);
		if(obj_id == INVALID_OBJECT_ID)
			printf("error put_object_on_free_place: can not create object, db_id=%d", object_id);
		if(count <= 0)
		    mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET thing_id=%d,prev_id=NULL,vector=%f,placex=%f,placey=%f,placez=%f,add_rotx=%f,add_roty=%f,add_rotz=0,obj_id=%d,dot_id=%d,pl_owner_id=NULL,th_owner_id=NULL,value=%d,unused=0 WHERE id=%d", next_id, VectorSize(x,y,z), x, y, z, add_rotx, add_roty, obj_id, dot_id, def_value, object_id);
		else
		    mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET vector=%f,placex=%f,placey=%f,placez=%f,add_rotx=%f,add_roty=%f,add_rotz=0,obj_id=%d,dot_id=%d,pl_owner_id=NULL,th_owner_id=NULL,value=%d,unused=0 WHERE id=%d", VectorSize(x,y,z), x, y, z, add_rotx, add_roty, obj_id, dot_id, def_value, object_id);
		mysql_query(gMysql, request);
//		thread_sql(request);
	}

	//обновляем БД
    mysql_format(gMysql, request, sizeof(request), "UPDATE object_dot SET object_id=%d WHERE id=%d", object_id, dot_id);
	mysql_query(gMysql, request); //так надо!
}

//добавить в инвентарь объекты, лежащие рядом с игроком
public add_objects_from_ground(playerid, Float:range)
{
	new request[768];
	new i, j;
	new Float:x, Float:y, Float:z;
	new Float:vector;
//	new Cache:result;	

	if(playerid < 0 || range < 0)
	{
	    gAltWait[playerid] = 0;
		return -1;
	}

	for(i = 0, j = 0; i < MAX_INVENTORY_ON_PLAYER; ++i)
	{
		if(gInventoryItem[playerid][i][db_id] == -1)
		    j++;
	}

	if(gBag[playerid][1] > 0)
	{
		for(i = 0; i < gBag[playerid][0]; ++i)
		{
			if(gBagItem[playerid][i][db_id] == -1)
			    j++;
		}
	}

	//в инвентаре места нет - выходим
	if(j == 0)
	{
		gAltWait[playerid] = 0;
	    return -1;
	}

	GetPlayerPos(playerid, x, y, z);

	vector = VectorSize(x, y, z);
    mysql_format(gMysql, request, sizeof(request), "SELECT a.id,a.placex,a.placey,a.placez FROM objects a INNER JOIN things b ON a.thing_id=b.id WHERE a.vector IS NOT NULL AND b.is_vehicle < 1 AND ABS(a.vector-%f)<%f AND ABS(a.placex-%f)<%f AND b.is_inventory > 0 ORDER BY b.is_inventory DESC LIMIT 200",vector,range,x,range);
	mysql_tquery(gMysql, request, "add_objects_from_ground_t", "dffff", playerid, range, x, y, z);
//	result = mysql_query(gMysql, request);

//	printf("add_objects_from_ground, mysql_tquery:  ok, gMysql=%d", gMysql); //отладка!!!
//	gAltWait[playerid] = 0; //отладка!!!
//	
	return 1;
}	

public add_objects_from_ground_t(playerid, Float:range, Float:x, Float:y, Float:z)
{
	new rows, fields;
	new i, j;
	new Float:placex, Float:placey, Float:placez;
	new Cache:result;
	new Float:distance;
	new object_id[32];

	result = cache_save(gMysql);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
	{
		if(cache_is_valid(result, gMysql))
			cache_delete(result);
		gAltWait[playerid] = 0;
	    return 0;
	}

	for(i = 0; i < 32; ++i)
	{
	    object_id[i] = -1;
	}

	for(i = 0, j = 0; i < rows; ++i)
	{
		placex = cache_get_field_content_float(i, "placex", gMysql);
		placey = cache_get_field_content_float(i, "placey", gMysql);
		placez = cache_get_field_content_float(i, "placez", gMysql);
		distance = VectorSize(placex-x, placey-y, placez-z);
	    if(distance < range)
		{
			object_id[j] = cache_get_field_content_int(i, "id", gMysql);
			//printf("distance=%f, range=%f, placex=%f, placey=%f, placez=%f,object_id[%d]=%d", distance, range, placex, placey, placez, j, object_id[j]); //отладка!!!
			if(j >= 31)
			    break;
			j++;
		}
	}

	if(cache_is_valid(result, gMysql))
		cache_delete(result);

	for(i = 0; i < MAX_INVENTORY_ON_PLAYER; ++i)
	{
		copy_craft_item(gCachePlayerInventory[playerid][i], gInventoryItem[playerid][i]);
	}
	for(i = 0; i < MAX_INVENTORY_IN_BAG; ++i)
	{
		copy_craft_item(gCacheBagInventory[playerid][i], gBagItem[playerid][i]);
	}
	
	for(i = 0; i < MAX_INVENTORY_ON_PLAYER; ++i)
	{
		if(gInventoryItem[playerid][i][db_id] == -1)
		{
		    for(j = 0; j < 32; ++j)
		    {
		        if(object_id[j] > 0)
		        {
					//тут ещё можно добавить проверку на наличае этой вещи у соседних игроков
					//...
					if(set_character_inventory_cell(playerid, i, object_id[j], true) > 0)
					{
			    		//inv[i] = object_id[j];
					}
					else
					{
					    i--;
					    if(i < 0)
					        i = -1;
					}
					object_id[j] = -1;
		            j = 32;
		        }
		    }
		}
	}

	for(i = 0; i < gBag[playerid][0]; ++i)
	{
		if(gBagItem[playerid][i][db_id] == -1)
		{
		    for(j = 0; j < 32; ++j)
		    {
		        if(object_id[j] > 0)
		        {
					//тут ещё можно добавить проверку на наличае этой вещи у соседних игроков
					//...
					if(set_bag_inventory_cell(playerid, i, object_id[j], true) > 0)
					{
			    		//inv_bag[i] = object_id[j];
					}
					else
					{
					    i--;
					    if(i < 0)
					        i = -1;
					}
					object_id[j] = -1;
		            j = 32;
		        }
		    }
		}
	}

	alt_post_handle(playerid);

	return 1;
}

//получить значение поля таблицы
public get_character_value(playerid, row_name[], table_name[], result[64])
{
	new request[128];
	new Cache:res;
	new rows, fields;
	
	if(gPlayersID[playerid] <= 0)
	    return;

	if( (strcmp(table_name, "characters", true, 10) != 0) && (strcmp(table_name, "inventory", true, 9) != 0) )
	    return;

    mysql_format(gMysql, request, sizeof(request), "SELECT %s FROM %s WHERE player_id=%d", row_name, table_name, gPlayersID[playerid]);
	res = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows > 0)
		cache_get_field_content(0, row_name, result, gMysql, sizeof(result));
	else
	    strdel(result, 0, sizeof(result)-1);
	if(cache_is_valid(res, gMysql))
		cache_delete(res);
}

//получить значение поля таблицы
public get_players_value(row_name[], table_name[], id, result[64])
{
	new request[128];
	new Cache:res;
	new rows, fields;
	
	if( (strcmp(table_name, "players", true, 7) != 0) && (strcmp(table_name, "objects", true, 7) != 0))
	    return;

    mysql_format(gMysql, request, sizeof(request), "SELECT %s FROM %s WHERE id=%d", row_name, table_name, id);
	res = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows > 0)
		cache_get_field_content(0, row_name, result, gMysql, sizeof(result));
	else
	    strdel(result, 0, sizeof(result)-1);
	if(cache_is_valid(res, gMysql))
		cache_delete(res);
}

//получить значение поля таблицы
public get_vehicle_value(vehicleid, row_name[], table_name[], result[64])
{
	new request[128];
	new Cache:res;
	new rows, fields;

	if( (strcmp(table_name, "veh_data", true, 8) != 0) && (strcmp(table_name, "veh_invent", true, 10) != 0) )
	    return;

    mysql_format(gMysql, request, sizeof(request), "SELECT %s FROM %s WHERE object_id=%d", row_name, table_name, gVeh[vehicleid][0]);
	res = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows > 0)
		cache_get_field_content(0, row_name, result, gMysql, sizeof(result));
	else
	    strdel(result, 0, sizeof(result)-1);
	if(cache_is_valid(res, gMysql))
		cache_delete(res);
}

//получить значение поля таблицы
public get_bag_value(playerid, row_name[], table_name[], result[64])
{
	new request[128];
	new Cache:res;
	new rows, fields;
	
	if( (strcmp(table_name, "bag_invent", true, 10) != 0) || gBag[playerid][0] <= 0 || gBag[playerid][1] <= 0)
	    return;

    mysql_format(gMysql, request, sizeof(request), "SELECT %s FROM %s WHERE object_id=%d", row_name, table_name, gBag[playerid][1]);
	res = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows > 0)
		cache_get_field_content(0, row_name, result, gMysql, sizeof(result));
	else
	    strdel(result, 0, sizeof(result)-1);
	if(cache_is_valid(res, gMysql))
		cache_delete(res);
}

public get_thing_field(field_name[], thing[], out_data[64])
{
	new rows, fields;
	new request[256];
	new Cache:result;

	if(strlen(field_name) == 0 || strlen(thing) == 0)
	{
	    print("error in get_thing_value(): empty request");
	    return;
	}

	//получаем значение поля
    mysql_format(gMysql, request, sizeof(request), "SELECT %s FROM things WHERE name=\"%s\" LIMIT 1", field_name, thing);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
	{
	    print("error in get_thing_value(): no such thing");
	    printf("%s",request);
	    return;
	}
	cache_get_field_content(0, field_name, out_data, gMysql);
	if(cache_is_valid(result, gMysql))
		cache_delete(result);
}

public set_character_cell_value(playerid, cell, value)
{
	new request[256];

	if(gPlayersID[playerid] <= 0)
	    return;

    mysql_format(gMysql, request, sizeof(request), "UPDATE objects a, inventory b SET a.value=%d WHERE a.id=b.inv%d AND b.player_id=%d", value, cell+1, gPlayersID[playerid]);
//	mysql_query(gMysql, request);
	thread_sql(request);
}

public set_vehicle_cell_value(vehicleid, cell, value)
{
	new request[256];

    mysql_format(gMysql, request, sizeof(request), "UPDATE objects a, veh_invent b SET a.value=%d WHERE a.id=b.inv%d AND b.object_id=%d", value, cell+1, gVeh[vehicleid][0]);
//	mysql_query(gMysql, request);
	thread_sql(request);
}

public set_ground_cell_value(playerid, cell, value)
{
	new request[256];

	if(cell < 0)
	    return;

	if(gGroundItem[playerid][cell][db_id] <= 0)
	    return;

    mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET value=%d WHERE id=%d", value, gGroundItem[playerid][cell][db_id]);
//	mysql_query(gMysql, request);
	thread_sql(request);
}

public set_bag_cell_value(playerid, cell, value)
{
	new request[256];

	if(gBag[playerid][0] <= 0 || gBag[playerid][1] <= 0 || cell < 0 || cell >= MAX_INVENTORY_IN_BAG)
	    return;

    mysql_format(gMysql, request, sizeof(request), "UPDATE objects a, bag_invent b SET a.value=%d WHERE a.id=b.inv%d AND b.object_id=%d", value, cell+1, gBag[playerid][1]);
//	mysql_query(gMysql, request);
	thread_sql(request);
}

public add_gates(inworld_id, door_type[], Float:close_x, Float:close_y, Float:close_z, Float:close_rx, Float:close_ry, Float:close_rz, Float:open_x, Float:open_y, Float:open_z, Float:open_rx, Float:open_ry, Float:open_rz, speed, range) //создать ворота
{
	new rows, fields;
	new request[512];
	new Cache:result;
	new thing_id, open_id;

    mysql_format(gMysql, request, sizeof(request), "SELECT a.id FROM things a INNER JOIN thing_type b ON a.type_id=b.id WHERE a.inworld_id=%d AND b.name=\"%s\" LIMIT 1", inworld_id, door_type);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
	{
	    //если такого объекта нету - выходим
		if(cache_is_valid(result, gMysql))
			cache_delete(result);
		return -1;
	}
	thing_id = cache_get_field_content_int(0, "id", gMysql);
	if(cache_is_valid(result, gMysql))
		cache_delete(result);
		
    mysql_format(gMysql, request, sizeof(request), "SELECT id FROM objects WHERE thing_id=%d AND ABS(placex-%f)<0.2 AND ABS(placey-%f)<0.2 AND ABS(placez-%f)<0.2 AND ABS(add_rotx-%f)<0.2 AND ABS(add_roty-%f)<0.2 AND ABS(add_rotz-%f)<0.2", thing_id, open_x, open_y, open_z, open_rx, open_ry, open_rz);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
	{
	    mysql_format(gMysql, request, sizeof(request), "INSERT INTO objects(thing_id,next_id,prev_id,placex,placey,placez,add_rotx,add_roty,add_rotz,owner,is_dropped,vector) VALUES(%d,%d,NULL,%f,%f,%f,%f,%f,%f,0,1,0.0)", thing_id, thing_id, open_x, open_y, open_z, open_rx, open_ry, open_rz);
		result = mysql_query(gMysql, request);
		if(cache_is_valid(result, gMysql))
			cache_delete(result);

	    mysql_format(gMysql, request, sizeof(request), "SELECT id FROM objects WHERE thing_id=%d AND ABS(placex-%f)<0.2 AND ABS(placey-%f)<0.2 AND ABS(placez-%f)<0.2 AND ABS(add_rotx-%f)<0.2 AND ABS(add_roty-%f)<0.2 AND ABS(add_rotz-%f)<0.2", thing_id, open_x, open_y, open_z, open_rx, open_ry, open_rz);
		result = mysql_query(gMysql, request);
		cache_get_data(rows, fields, gMysql);
		if(rows <= 0)
		    return -2;
	}
	open_id = cache_get_field_content_int(0, "id", gMysql);
	if(cache_is_valid(result, gMysql))
		cache_delete(result);

    mysql_format(gMysql, request, sizeof(request), "SELECT id FROM objects WHERE thing_id=%d AND ABS(placex-%f)<0.2 AND ABS(placey-%f)<0.2 AND ABS(placez-%f)<0.2 AND ABS(add_rotx-%f)<0.2 AND ABS(add_roty-%f)<0.2 AND ABS(add_rotz-%f)<0.2", thing_id, close_x, close_y, close_z, close_rx, close_ry, close_rz);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows > 0)
	{
		if(cache_is_valid(result, gMysql))
			cache_delete(result);
		return -3;
	}

	//owner - id открытой двери
	//is_dropped - открыто/закрыто (1 - открыто)
	//dot_id - скорость открывания
	//value - радиус действия ключа
    mysql_format(gMysql, request, sizeof(request), "INSERT INTO objects(thing_id,next_id,prev_id,placex,placey,placez,add_rotx,add_roty,add_rotz,owner,dot_id,is_dropped,th_owner_id,value,vector) VALUES(%d,%d,NULL,%f,%f,%f,%f,%f,%f,%d,%d,0,0,%d,%f)", thing_id, thing_id, close_x, close_y, close_z, close_rx, close_ry, close_rz, open_id, speed, range, VectorSize(close_x,close_y,close_z));
	result = mysql_query(gMysql, request);
	if(cache_is_valid(result, gMysql))
		cache_delete(result);

	return 1;
}

//открыть/закрыть ворота
public open_a_gate(playerid, key_type[], door_type[])
{
	new rows, fields;
	new request[1536];
	new buff[1536];
	new Cache:result;
	new door_id, door_ingame_id, fno_objects, fis_opened, i;
	new Float:x, Float:y, Float:z, Float:rotx, Float:roty, Float:rotz, Float:speed;

	if(strlen(key_type) <= 0)
	    return 0;
	    
	if(playerid < 0)
	    return 0;

	//ищем ключи в инвентаре
	fno_objects = 1;
	format(buff, sizeof(buff), "SELECT d.object_id,a.value FROM key_data d INNER JOIN (objects a,things b,thing_type c,objects e,things f,thing_type g) ON (a.thing_id=b.id AND b.type_id=c.id AND d.key_id=a.id AND d.object_id=e.id AND e.thing_id=f.id AND f.type_id=g.id) WHERE c.name='%s' AND g.name='%s' AND a.id IN (", key_type, door_type);
	for(i = 0; i < MAX_INVENTORY_ON_PLAYER; ++i)
	{
	    if(gInventoryItem[playerid][i][db_id] > 0)
	    {
			if(fno_objects == 1)
			{
		        format(request, sizeof(request), "%d", gInventoryItem[playerid][i][db_id]);
				fno_objects = 0;
			}
			else
		        format(request, sizeof(request), ",%d", gInventoryItem[playerid][i][db_id]);
	        strcat(buff, request);
	    }
	}

	if(fno_objects)
		return 0;

	if(gBag[playerid][1] > 0)
	{
		for(i = 0; i < MAX_INVENTORY_IN_BAG; ++i)
		{
		    if(gBagItem[playerid][i][db_id] > 0)
		    {
			    format(request, sizeof(request), ",%d", gBagItem[playerid][i][db_id]);
		        strcat(buff, request);
		    }
		}
	}
	
	strcat(buff, ")");

	//сперва находим все ключи в инвентаре и рюкзаке персонажа
    mysql_format(gMysql, request, sizeof(request), buff);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
	{
	    //если такого объекта нету - выходим
		if(cache_is_valid(result, gMysql))
			cache_delete(result);
		return -1;
	}
	//ищем все двери в заданном самими дверьми диапазоне
	GetPlayerPos(playerid, x, y, z);
	format(buff, sizeof(buff), "SELECT a.id,a.value,IFNULL(a.dot_id,0) as dot_id,a.placex as ax,a.placey as ay,a.placez as az,a.add_rotx as rx,a.add_roty as ry,a.add_rotz as rz,ABS(a.vector-%f) as path,a.obj_id,a.th_owner_id,d.placex as dx,d.placey as dy,d.placez as dz,d.add_rotx as drx,d.add_roty as dry,d.add_rotz as drz FROM objects a INNER JOIN (things b,thing_type c,objects d)", VectorSize(x,y,z));
	format(request, sizeof(request), " ON (a.thing_id=b.id AND b.type_id=c.id AND a.owner=d.id) WHERE a.owner>0 AND c.name=\"%s\" AND (ABS(a.vector-%f)<=a.value) AND (ABS(a.placex-%f)<=a.value) AND (ABS(a.placey-%f)<=a.value) AND (ABS(a.placez-%f)<=a.value) AND a.id IN (", door_type, VectorSize(x,y,z), x, y, z);
	strcat(buff, request);
	fno_objects = 1;
	for(i = 0; i < rows; ++i)
	{
		door_id = cache_get_field_content_int(i, "object_id", gMysql);
		if(fno_objects == 1)
		{
			format(request, sizeof(request), "%d", door_id);
			fno_objects = 0;
		}
		else
		{
			format(request, sizeof(request), ",%d", door_id);
		}
		strcat(buff, request);
	}
	if(cache_is_valid(result, gMysql))
		cache_delete(result);

	strcat(buff, ") ORDER BY path");
    mysql_format(gMysql, request, sizeof(request), buff);
    //отправляем запрос
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
	    return 0;
	for(i = 0; i < rows; ++i)
	{
	    cache_set_active(result, gMysql);
		door_ingame_id = cache_get_field_content_int(i, "obj_id", gMysql); //obj_id лучше не использовать для хранения id модели
		door_id = cache_get_field_content_int(i, "id", gMysql); //obj_id лучше не использовать для хранения id модели
		fis_opened = cache_get_field_content_int(i, "th_owner_id", gMysql);
		speed = cache_get_field_content_int(i, "dot_id", gMysql);
		if(fis_opened==1)
		{
		    x = cache_get_field_content_float(i, "ax", gMysql);
		    y = cache_get_field_content_float(i, "ay", gMysql);
		    z = cache_get_field_content_float(i, "az", gMysql);
		    rotx = cache_get_field_content_float(i, "rx", gMysql);
		    roty = cache_get_field_content_float(i, "ry", gMysql);
		    rotz = cache_get_field_content_float(i, "rz", gMysql);
		}
		else
		{
		    x = cache_get_field_content_float(i, "dx", gMysql);
		    y = cache_get_field_content_float(i, "dy", gMysql);
		    z = cache_get_field_content_float(i, "dz", gMysql);
		    rotx = cache_get_field_content_float(i, "drx", gMysql);
		    roty = cache_get_field_content_float(i, "dry", gMysql);
		    rotz = cache_get_field_content_float(i, "drz", gMysql);
		}
		MoveDynamicObject(door_ingame_id, x, y, z, speed, rotx, roty, rotz);

//		new msg[256]; //отладка!!!
//		format(msg, sizeof(msg), "door_ingame_id=%d, x=%f,y=%f,z=%f,rotx=%f,roty=%f,rotz=%f,speed=%f",door_ingame_id,x,y,z,rotx,roty,rotz,speed); //отладка!!!
//		SendClientMessage(playerid, 0xFFFFFF, msg); //отладка!!!

	    mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET th_owner_id=%d WHERE id=%d", (fis_opened==1)?0:1, door_id);
		mysql_query(gMysql, request);
//		thread_sql(request);
	}
	if(cache_is_valid(result, gMysql))
		cache_delete(result);
		
	return 1;
}

public open_a_car(playerid, key_type[], car_type[])
{
	new rows, fields;
	new request[1024];
	new buff[1024];
	new Cache:result;
	new door_id, fno_objects, fis_locked, obj_id, i;
	new Float:x, Float:y, Float:z;
	new bound, engine, lights, alarm, doors, bonnet, boot, objective;

	if(strlen(key_type) <= 0)
	    return -1;

	if(playerid < 0)
	    return -2;

	//ищем ключи в инвентаре
	fno_objects = 1;
	format(buff, sizeof(buff), "SELECT d.object_id,a.value FROM key_data d INNER JOIN (objects a,things b,thing_type c,objects e,things f,thing_type g) ON (a.thing_id=b.id AND b.type_id=c.id AND d.key_id=a.id AND d.object_id=e.id AND e.thing_id=f.id AND f.type_id=g.id) WHERE c.name='%s' AND g.name='%s' AND a.id IN (", key_type, car_type);
	for(i = 0; i < MAX_INVENTORY_ON_PLAYER; ++i)
	{
	    if(gInventoryItem[playerid][i][db_id] > 0)
	    {
			if(fno_objects == 1)
			{
		        format(request, sizeof(request), "%d", gInventoryItem[playerid][i][db_id]);
				fno_objects = 0;
			}
			else
		        format(request, sizeof(request), ",%d", gInventoryItem[playerid][i][db_id]);
	        strcat(buff, request);
	    }
	}

	if(fno_objects)
		return -3;

	if(gBag[playerid][1] > 0)
	{
		for(i = 0; i < MAX_INVENTORY_IN_BAG; ++i)
		{
		    if(gBagItem[playerid][i][db_id] > 0)
		    {
			    format(request, sizeof(request), ",%d", gBagItem[playerid][i][db_id]);
		        strcat(buff, request);
		    }
		}
	}

	strcat(buff, ")");

	//сперва находим все ключи в инвентаре и рюкзаке персонажа
	strdel(request, 0, sizeof(request)-1);
    mysql_format(gMysql, request, sizeof(request), buff);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
	{
	    //если такого ключа нету - выходим
		if(cache_is_valid(result, gMysql))
			cache_delete(result);
		return -4;
	}
	
	//ищем все авто в заданном самими ключами диапазоне
	bound = cache_get_field_content_int(0, "value", gMysql);
	GetPlayerPos(playerid, x, y, z);
	strdel(buff, 0, sizeof(buff)-1);
	strdel(request, 0, sizeof(request)-1);
	format(buff, sizeof(buff), "SELECT a.id,SQRT((a.placex-%f)*(a.placex-%f)+(a.placey-%f)*(a.placey-%f)+(a.placez-%f)*(a.placez-%f)) as path,a.obj_id,d.is_locked FROM objects a INNER JOIN (things b,thing_type c,veh_data d) ON (a.thing_id=b.id AND b.type_id=c.id AND a.id=d.object_id) WHERE c.name=\"%s\" AND (ABS(a.vector-%f)<=%d) AND (ABS(a.placex-%f)<=%d) AND (ABS(a.placey-%f)<=%d) AND (ABS(a.placez-%f)<=%d) AND a.id IN (", x,x,y,y,z,z, car_type, VectorSize(x,y,z), bound, x, bound, y, bound, z, bound);
	fno_objects = 1;
	for(i = 0; i < rows; ++i)
	{
		door_id = cache_get_field_content_int(i, "object_id", gMysql);
		if(fno_objects == 1)
		{
			format(request, sizeof(request), "%d", door_id);
			fno_objects = 0;
		}
		else
		{
			format(request, sizeof(request), ",%d", door_id);
		}
//		SendClientMessage(playerid, 0xFFFFFF, request); //отладка!!!
		strcat(buff, request, sizeof(buff));
	}
	//выбираем только самое ближнее авто
	strcat(buff, ") ORDER BY path LIMIT 1", sizeof(buff));
	strdel(request, 0, sizeof(request)-1);
	
    mysql_format(gMysql, request, sizeof(request), buff);
	if(cache_is_valid(result, gMysql))
		cache_delete(result);
    //отправляем запрос
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
	    return -5;
	i = 0;
	door_id = cache_get_field_content_int(i, "id", gMysql);
	obj_id = cache_get_field_content_int(i, "obj_id", gMysql);
	fis_locked = cache_get_field_content_int(i, "is_locked", gMysql);
	if(fis_locked==0)
	{
	    GetVehicleParamsEx(obj_id, engine, lights, alarm, doors, bonnet, boot, objective);
	    SetVehicleParamsEx(obj_id, engine, 1, alarm, 1, bonnet, boot, objective);
	    //подмигнём разок фарами при закрытии
	    GetObjectPos(obj_id, x, y, z);
	    for(new j = 0; j < MAX_PLAYERS; ++j)
	    {
	        if(IsPlayerInRangeOfPoint(j, 50, x, y, z))
	            PlayerPlaySound(j, 32401, x, y, z);
	    }
	    if(lights == 0)
	    {
		    SetTimerEx("timer_lights_off", 300, false, "i", obj_id);
		    SetTimerEx("timer_lights_off", 1000, false, "i", obj_id);
		}
		else
		{
		    SetTimerEx("timer_lights_off", 300, false, "i", obj_id);
		    SetTimerEx("timer_lights_on", 700, false, "i", obj_id);
		    SetTimerEx("timer_lights_on", 1000, false, "i", obj_id);
		}
	}
	else
	{
	    GetVehicleParamsEx(obj_id, engine, lights, alarm, doors, bonnet, boot, objective);
	    SetVehicleParamsEx(obj_id, engine, 1, alarm, 0, bonnet, boot, objective);
	    //подмигнём пару раз фарами при открытии
	    GetObjectPos(obj_id, x, y, z);
	    for(new j = 0; j < MAX_PLAYERS; ++j)
	    {
	        if(IsPlayerInRangeOfPoint(j, 50.0, x, y, z))
	            PlayerPlaySound(j, 32401, 0, 0, 0);
	    }
	    if(lights == 0)
	    {
		    SetTimerEx("timer_lights_off", 300, false, "i", obj_id);
		    SetTimerEx("timer_lights_on", 600, false, "i", obj_id);
		    SetTimerEx("timer_lights_off", 900, false, "i", obj_id);
		    SetTimerEx("timer_lights_off", 1200, false, "i", obj_id);
		}
		else
		{
		    SetTimerEx("timer_lights_off", 300, false, "i", obj_id);
		    SetTimerEx("timer_lights_on", 600, false, "i", obj_id);
		    SetTimerEx("timer_lights_off", 900, false, "i", obj_id);
		    SetTimerEx("timer_lights_on", 1200, false, "i", obj_id);
		    SetTimerEx("timer_lights_on", 1500, false, "i", obj_id);
		}
	}
	for(i = 0; i < MAX_PLAYERS; ++i)
	{
	    if(IsPlayerInVehicle(i, obj_id))
			update_vehicle_sensors(i);
	}
    mysql_format(gMysql, request, sizeof(request), "UPDATE objects a,veh_data b SET b.is_locked=%d WHERE a.id=%d AND a.id=b.object_id", (fis_locked==1)?0:1, door_id);
	mysql_query(gMysql, request);
	//thread_sql(request);
	if(cache_is_valid(result, gMysql))
		cache_delete(result);

	return 1;
}

public timer_lights_on(obj_id)
{
	new Float:x, Float:y, Float:z;
	new engine, lights, alarm, doors, bonnet, boot, objective;

    GetVehicleParamsEx(obj_id, engine, lights, alarm, doors, bonnet, boot, objective);
    SetVehicleParamsEx(obj_id, engine, 1, alarm, doors, bonnet, boot, objective);
    GetObjectPos(obj_id, x, y, z);
    for(new j = 0; j < MAX_PLAYERS; ++j)
    {
        if(IsPlayerInRangeOfPoint(j, 50.0, x, y, z))
            PlayerPlaySound(j, 32401, 0, 0, 0);
    }
}

public timer_lights_off(obj_id)
{
	new engine, lights, alarm, doors, bonnet, boot, objective;

    GetVehicleParamsEx(obj_id, engine, lights, alarm, doors, bonnet, boot, objective);
    SetVehicleParamsEx(obj_id, engine, 0, alarm, doors, bonnet, boot, objective);
}

public set_a_key(playerid, cell_key, cell_gate)
{
	new rows, fields;
	new request[512];
	new Cache:result;

    mysql_format(gMysql, request, sizeof(request), "SELECT key_id,object_id FROM key_data WHERE key_id=%d AND object_id=%d", gGroundItem[playerid][cell_key][db_id], gGroundItem[playerid][cell_gate][db_id]);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
	{
		if(cache_is_valid(result, gMysql))
			cache_delete(result);

	    mysql_format(gMysql, request, sizeof(request), "INSERT INTO key_data(key_id,object_id) VALUES(%d,%d)", gGroundItem[playerid][cell_key][db_id], gGroundItem[playerid][cell_gate][db_id]);
		mysql_query(gMysql, request);

	    return 1;
	}
	
	if(cache_is_valid(result, gMysql))
		cache_delete(result);

    mysql_format(gMysql, request, sizeof(request), "DELETE FROM key_data WHERE key_id=%d AND object_id=%d", gGroundItem[playerid][cell_key][db_id], gGroundItem[playerid][cell_gate][db_id]);
	mysql_query(gMysql, request);

	return -1;
}

public mute_player(playerid, time)
{
	new request[256];

	if(gPlayersID[playerid] <= 0)
	    return;

	//корректируем интервал
	if(time <= 0)
	    time = 1;

	//затыкаем
    mysql_format(gMysql, request, sizeof(request), "UPDATE players a,characters b SET a.mute=addtime(now(),time(\"%d:00:00\")),b.mute_count=b.mute_count+1 WHERE a.id=%d AND b.player_id=a.id", time, gPlayersID[playerid]);
	mysql_query(gMysql, request);
	
	gMute[playerid] = GetTickCount();
}

public unmute_player(PlayerID)
{
	new request[256];
	new playerid;

	if(PlayerID <= 0)
	    return;

	//растыкаем
    mysql_format(gMysql, request, sizeof(request), "UPDATE players SET mute=0 WHERE id=%d LIMIT 1", PlayerID);
	mysql_query(gMysql, request);

	for(new i = 0; i < MAX_PLAYERS; ++i)
	{
	    if(gPlayersID[i] == PlayerID)
	    {
	        playerid = i;
	        break;
	    }
	}

	gMute[playerid] = 0;
}

//получить значение доступности чата для игрока
public get_player_mute(playerid)
{
	new rows, fields;
	new request[512];
	new name[64];
	new Cache:result;
	new ret, ret_h, ret_m, i, j, k;
	new time_value[64], minute_value[64];

	ret = 0;

	GetPlayerName(playerid, name, sizeof(name));
	
	//узнаем, открыт ли чат для игрока
    mysql_format(gMysql, request, sizeof(request), "SELECT id,IF(((now()>mute)>0),0,1) as chat,TIMEDIFF(mute,now()) as sign FROM players WHERE name=\"%s\" LIMIT 1", name);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
	{
	    //чтобы входящие новенькие игроки могли задавать вопросы
	    gMute[playerid] = 0;
	    return 0;
	}
	gPlayersID[playerid] = cache_get_field_content_int(0, "id", gMysql);
	gMute[playerid] = cache_get_field_content_int(0, "chat", gMysql);
	if(gMute[playerid] > 0)
	{
		cache_get_field_content(0, "sign", time_value, gMysql, sizeof(time_value));
		ret = strval(time_value);
		strdel(minute_value, 0, sizeof(minute_value)-1);
		for(i = 0, k = 0, j = 0; i < strlen(time_value); ++i)
		{
			if(time_value[i] == ':')
			    k++;
			if(k >= 2)
			    break;
			if(k == 1 && time_value[i] != ':')
			{
				minute_value[j] = time_value[i];
				j++;
			}
		}
		ret_m = strval(minute_value);
		ret = ret_h*3600000+(ret_m+1)*60000;
	}
	if(cache_is_valid(result, gMysql))
		cache_delete(result);
		
	return ret;
}

public get_character_state(playerid, &temperature, &health, &hunger, &thirst, &wound)
{
	new rows, fields;
	new request[256];
	new Cache:result;

	if(gPlayersID[playerid] <= 0)
	    return 0;

	//получаем высоту, тип вещи, вращение и модель объекта
    mysql_format(gMysql, request, sizeof(request), "SELECT temperature,health,hunger,thirst,wound FROM characters WHERE player_id=%d LIMIT 1", gPlayersID[playerid]);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
	    return 0;
	temperature = cache_get_field_content_int(0, "temperature", gMysql);
	health = cache_get_field_content_int(0, "health", gMysql);
	hunger = cache_get_field_content_int(0, "hunger", gMysql);
	thirst = cache_get_field_content_int(0, "thirst", gMysql);
	wound = cache_get_field_content_int(0, "wound", gMysql);
	if(cache_is_valid(result, gMysql))
		cache_delete(result);

	return 1;
}

public set_character_state(playerid, temperature, health, hunger, thirst, wound)
{
	new request[256];

	if(gPlayersID[playerid] <= 0)
	    return;

	//получаем высоту, тип вещи, вращение и модель объекта
    mysql_format(gMysql, request, sizeof(request), "UPDATE characters SET temperature=%d,health=%d,hunger=%d,thirst=%d,wound=%d WHERE player_id=%d LIMIT 1", temperature, health, hunger, thirst, wound, gPlayersID[playerid]);
//	mysql_query(gMysql, request);
	thread_sql(request);
}

public get_character_temp(playerid)
{
	new result[64];

	strdel(result, 0, sizeof(result)-1);
    get_character_value(playerid,"temperature","characters",result);
	return strval(result);
}

public set_character_temp(playerid, temp)
{
	new request[128];

	if(gPlayersID[playerid] <= 0)
	    return;

    mysql_format(gMysql, request, sizeof(request), "UPDATE characters SET temperature=%d WHERE player_id=%d LIMIT 1", temp, gPlayersID[playerid]);
//	mysql_query(gMysql, request);
	thread_sql(request);

	update_sensor_temp(playerid, temp);
}

public get_character_health(playerid)
{
	new result[64];
	
	strdel(result, 0, sizeof(result)-1);
    get_character_value(playerid,"health","characters",result);
	return strval(result);
}

public set_character_health(playerid, health)
{
	new request[128];

	if(gPlayersID[playerid] <= 0)
	    return;

    mysql_format(gMysql, request, sizeof(request), "UPDATE characters SET health=%d WHERE player_id=%d LIMIT 1", (health>MAX_HEALTH_VALUE)?MAX_HEALTH_VALUE:health, gPlayersID[playerid]);
//	mysql_query(gMysql, request);
	thread_sql(request);

	update_sensor_health(playerid, health);
}

public get_character_hunger(playerid)
{
	new result[64];

	strdel(result, 0, sizeof(result)-1);
    get_character_value(playerid,"hunger","characters",result);
	return strval(result);
}

public set_character_hunger(playerid, hunger)
{
	new request[128];

	if(gPlayersID[playerid] <= 0)
	    return;

    mysql_format(gMysql, request, sizeof(request), "UPDATE characters SET hunger=%d WHERE player_id=%d LIMIT 1", (hunger>MAX_HUNGER_VALUE)?MAX_HUNGER_VALUE:hunger, gPlayersID[playerid]);
//	mysql_query(gMysql, request);
	thread_sql(request);

	update_sensor_hunger(playerid, hunger);
}

public get_character_thirst(playerid)
{
	new result[64];

	strdel(result, 0, sizeof(result)-1);
    get_character_value(playerid,"thirst","characters",result);
	return strval(result);
}

public set_character_thirst(playerid, thirst)
{
	new request[128];

	if(gPlayersID[playerid] <= 0)
	    return;

    mysql_format(gMysql, request, sizeof(request), "UPDATE characters SET thirst=%d WHERE player_id=%d LIMIT 1", (thirst>MAX_THIRST_VALUE)?MAX_THIRST_VALUE:thirst, gPlayersID[playerid]);
//	mysql_query(gMysql, request);
	thread_sql(request);

	update_sensor_thirst(playerid, thirst);
}

public get_character_wound(playerid)
{
	new result[64];

	strdel(result, 0, sizeof(result)-1);
    get_character_value(playerid,"wound","characters",result);
	return strval(result);
}

public set_character_wound(playerid, wound)
{
	new request[128];

	if(gPlayersID[playerid] <= 0)
	    return;

    mysql_format(gMysql, request, sizeof(request), "UPDATE characters SET wound=%d WHERE player_id=%d LIMIT 1", wound, gPlayersID[playerid]);
//	mysql_query(gMysql, request);
	thread_sql(request);

	update_sensor_wound(playerid, wound);
}

public get_character_scores(playerid)
{
	new result[64];

	strdel(result, 0, sizeof(result)-1);
    get_character_value(playerid,"scores","characters",result);
	return strval(result);
}

public set_character_scores(playerid, scores)
{
	new request[128];

	if(gPlayersID[playerid] <= 0)
	    return;

    mysql_format(gMysql, request, sizeof(request), "UPDATE characters SET scores=%d WHERE player_id=%d LIMIT 1", scores, gPlayersID[playerid]);
//	mysql_query(gMysql, request);
	thread_sql(request);
//	update_sensor_scores(playerid, scores);
}

public get_character_killer_name(playerid, name[64])
{
	new rows, fields;
	new request[128];
	new Cache:result;

	if(gPlayersID[playerid] <= 0)
	    return;

    mysql_format(gMysql, request, sizeof(request), "SELECT a.name FROM players a INNER JOIN characters b ON a.id=b.killer_id WHERE b.player_id=%d LIMIT 1", gPlayersID[playerid]);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows > 0)
		cache_get_field_content(0, "name", name, gMysql);
	else
	    format(name, sizeof(name), "no killer");
	if(cache_is_valid(result, gMysql))
		cache_delete(result);
}

//запомнить последнего попавшего
public set_character_c_killer(playerid)
{
	new request[128];

	if(playerid < 0)
		return;

	if(gPlayersID[playerid] <= 0)
	    return;

	//c_killer - последний персонаж, который нанёс урон
	if(gKiller[playerid] < 0)
	    mysql_format(gMysql, request, sizeof(request), "UPDATE characters SET c_killer=NULL WHERE player_id=%d LIMIT 1", gPlayersID[playerid]);
	else
	    mysql_format(gMysql, request, sizeof(request), "UPDATE characters SET c_killer=%d WHERE player_id=%d LIMIT 1", gKiller[playerid], gPlayersID[playerid]);
//	mysql_query(gMysql, request);
	thread_sql(request);
}

//запомнить убийцу
public set_character_killer(playerid)
{
	new request[128];

	if(playerid < 0)
		return;

	if(gPlayersID[playerid] <= 0)
	    return;

	//c_killer - последний персонаж, который нанёс урон
	if(gKiller[playerid] < 0)
	    mysql_format(gMysql, request, sizeof(request), "UPDATE characters SET c_killer=NULL WHERE player_id=%d LIMIT 1", gPlayersID[playerid]);
	else
	    mysql_format(gMysql, request, sizeof(request), "UPDATE characters SET killer_id=%d,c_killer=NULL WHERE player_id=%d LIMIT 1", gKiller[playerid], gPlayersID[playerid]);
//	mysql_query(gMysql, request);
	thread_sql(request);

	gKiller[playerid] = -1;
	update_statistic_data(playerid, false);
}

//увеличить очки персонажа
public upscore_character(db_playerid)
{
	new request[128];
	new playerid;
	
	if(db_playerid < 0)
		return;

    mysql_format(gMysql, request, sizeof(request), "UPDATE characters SET scores=scores+1 WHERE player_id=%d LIMIT 1", db_playerid);
//	mysql_query(gMysql, request);
	thread_sql(request);

	for(playerid = 0; playerid < MAX_PLAYERS; ++playerid)
	{
	    if(gPlayersID[playerid] == db_playerid)
	    {
			gScores[playerid]++;
			SetPlayerScore(playerid, gScores[playerid]);
			update_statistic_data(playerid, false);
			break;
	    }
	}
}

public save_player_position(playerid)
{
	new request[256];
	new Float:x, Float:y, Float:z, Float:ang;
	
	if(gPlayersID[playerid] <= 0)
	    return;

	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, ang);

    mysql_format(gMysql, request, sizeof(request), "update characters set placex=%f,placey=%f,placez=%f,angle=%f where player_id=%d LIMIT 1", x, y, z, ang, gPlayersID[playerid]);
//	mysql_query(gMysql, request);
	thread_sql(request);
}

public save_player_bakup_position(playerid)
{
	new request[256];

	if(gPlayersID[playerid] <= 0)
	    return;

    mysql_format(gMysql, request, sizeof(request), "update characters set bplacex=placex,bplacey=placey,bplacez=placez,bangle=angle,cheater=0 where player_id=%d LIMIT 1", gPlayersID[playerid]);
//	mysql_query(gMysql, request);
	thread_sql(request);
}

public load_player_bakup_position(playerid)
{
	new request[256];

	if(gPlayersID[playerid] <= 0)
	    return;

    mysql_format(gMysql, request, sizeof(request), "update characters set placex=bplacex,placey=bplacey,placez=bplacez,angle=bangle,cheater=0 where player_id=%d LIMIT 1", gPlayersID[playerid]);
	mysql_query(gMysql, request);
}

public load_player_position(playerid)
{
	new rows, fields;
	new request[256];
	new Float:x, Float:y, Float:z, Float:ang, Float:valid_z;
	new cheater, skin, is_zombie;
	new Cache:result;

	if(set_player_id(playerid) < 0)
	    return;
	
	if(gPlayersID[playerid] <= 0)
	    return;

	skin = 188;
	is_zombie = 0;
	
    mysql_format(gMysql, request, sizeof(request), "SELECT a.placex,a.placey,a.placez,a.angle,a.skin,a.bplacex,a.bplacey,a.bplacez,a.bangle,a.cheater,b.is_zombie FROM characters a,players b WHERE a.player_id=%d AND a.player_id=b.id LIMIT 1", gPlayersID[playerid]);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows > 0)
	{
		cheater = cache_get_field_content_int(0, "cheater", gMysql);
		is_zombie = cache_get_field_content_int(0, "is_zombie", gMysql);
		if(cheater >= gMaxAnticheat)
		{
			if(is_zombie == 0)
				get_spawn_place(playerid, false); //меняет координаты в БД, а заодно обнуляет флаг cheater
   			else
				get_spawn_place(playerid, true); //меняет координаты в БД, а заодно обнуляет флаг cheater
		    mysql_format(gMysql, request, sizeof(request), "SELECT placex,placey,placez,angle,bplacex,bplacey,bplacez,bangle,cheater,skin FROM characters WHERE player_id=%d LIMIT 1", gPlayersID[playerid]);
			result = mysql_query(gMysql, request);
			cache_get_data(rows, fields, gMysql);
			if(rows > 0)
			{
				x = cache_get_field_content_float(0, "placex", gMysql);
				y = cache_get_field_content_float(0, "placey", gMysql);
				z = cache_get_field_content_float(0, "placez", gMysql);
				ang = cache_get_field_content_float(0, "angle", gMysql);
				skin = cache_get_field_content_int(0, "skin", gMysql);
			}
			else
			{
			    GetPlayerName(playerid, request, sizeof(request));
			    printf("Error: no such player in database %s", request);
			    //load on spawn number 1 (from `spawns` table)
			    x = -2347.0;
			    y = -1600.0;
			    z = 484.0;
			    ang = 111.48;
			    skin = 188;
			}
		}
		else
		{
			x = cache_get_field_content_float(0, "placex", gMysql);
			y = cache_get_field_content_float(0, "placey", gMysql);
			z = cache_get_field_content_float(0, "placez", gMysql);
			ang = cache_get_field_content_float(0, "angle", gMysql);
			skin = cache_get_field_content_int(0, "skin", gMysql);
		}
	}
	else
	{
		//а лучше бы тут кикнуть...
		//...
//		Kick(playerid);
		new name[64];
		new msg[256];

		//сообщение в низ экрана
		GetPlayerName(playerid, name, sizeof(name));
		format(msg, sizeof(msg), "%s(id:%d) no character player (kick)", name, playerid);
		update_sensor_messager_cheat(msg);
		//гарантируем игроку кик
		gPlayerCheaterLevel[playerid] = gMaxAnticheat;
		return;
/*
	    GetPlayerName(playerid, request, sizeof(request));
	    printf("Error: no such player in database %s", request);
	    //load on spawn number 1 (from `spawns` table)
	    x = -2347.0;
	    y = -1600.0;
	    z = 484.0;
	    ang = 111.48;
	    skin = 188;
*/
	}

	if(cache_is_valid(result, gMysql))
		cache_delete(result);

	if(is_zombie == 0)
	{
	    valid_z = 0;
		SetPlayerSkinFix(playerid, skin);
		MapAndreas_FindZ_For2DCoord(x, y, valid_z);
		//если игрок под водой
		if(z <= 0 && valid_z > -1.0 && valid_z < 1.0)
		{
			SetPlayerPosFindZ(playerid, x, y, z);
		}
		else
			SetPlayerPos(playerid, x, y, z);

		SetPlayerFacingAngle(playerid, ang);
		SetCameraBehindPlayer(playerid);
		
		GetPlayerPos(playerid, x, y, z);

		//для античита
		gNonCheaters[playerid][0] = x;
		gNonCheaters[playerid][1] = y;
		gNonCheaters[playerid][2] = z;
	}
	else
	{
	    FCNPC_Spawn(playerid, skin, x, y, z);
	}
	//необходимо обнулить счётчик читов, чтобы не выкинуло при следующем входе в игру!
    mysql_format(gMysql, request, sizeof(request), "UPDATE characters SET cheater=0 WHERE player_id=%d LIMIT 1", gPlayersID[playerid]);
//	mysql_query(gMysql, request);
	thread_sql(request);
}

public init_npc_zombies()
{
	new request[128];
	new rows, fields;
	new Cache:result;
	new name[64];
	new npcid, i;

    mysql_format(gMysql, request, sizeof(request), "SELECT count(*) as count FROM players WHERE is_zombie=1");
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows > 0)
	{
		gNPCCount = cache_get_field_content_int(0, "count", gMysql);
		
		if(cache_is_valid(result, gMysql))
			cache_delete(result);
	}
	else
	{
		gNPCCount = 0;
	    return;
	}
	
    mysql_format(gMysql, request, sizeof(request), "SELECT name FROM players WHERE is_zombie=1");
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows > 0)
	{
		for(i = 0; i < rows; ++i)
		{
	        strdel(name, 0, sizeof(name)-1);
			cache_get_field_content(i, "name", name, gMysql);
			npcid = FCNPC_Create(name);
			if(npcid >= 0 && npcid < MAX_PLAYERS)
				load_player_position(npcid);
		    cache_set_active(result, gMysql);
		}
	}
	if(cache_is_valid(result, gMysql))
		cache_delete(result);
}

public save_state_and_position(playerid)
{
	new request[256];
	new Float:x, Float:y, Float:z, Float:ang;
	new skin;
	
	if(gPlayersID[playerid] <= 0)
	    return;

	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, ang);
	skin = GetPlayerSkin(playerid);
	if(skin == 0)
	    skin = 188;

    mysql_format(gMysql, request, sizeof(request), "UPDATE characters SET placex=%f,placey=%f,placez=%f,angle=%f,skin=%d,temperature=%d,health=%d,hunger=%d,thirst=%d,wound=%d,killer_id=%d WHERE player_id=%d LIMIT 1", x,y,z,ang,skin,gTemperature[playerid],gHealth[playerid],gHunger[playerid],gThirst[playerid],gWound[playerid],gKiller[playerid],gPlayersID[playerid]);
//	mysql_query(gMysql, request);
	thread_sql(request);
}

public mark_player_as_cheater(playerid, value)
{
	new request[256];

	if(gPlayersID[playerid] <= 0)
	    return;

    mysql_format(gMysql, request, sizeof(request), "UPDATE characters SET cheater=cheater+%d,kick_count=kick_count+1 WHERE player_id=%d LIMIT 1", value, gPlayersID[playerid]);
	mysql_query(gMysql, request);
//	thread_sql(request);
}

public mark_player_as_banned(playerid, tm)
{
	new request[1536];
	new rows, fields;
	new Cache:result;
	new addr[24];
	new ban_mask[24];
	new i, dot, id;
	
	//printf("mark_player_as_banned: start, playerid=%d, tm=%d", playerid, tm); //отладка!!!
	
	if(set_player_id(playerid) < 0)
	    return;
	
	if(gPlayersID[playerid] <= 0)
	    return;

	GetPlayerIp(playerid, addr, sizeof(addr));
	strdel(ban_mask, 0, sizeof(ban_mask)-1);
	for(i = 0, dot = 0; i < sizeof(addr); ++i)
	{
		if(addr[i] == '.')
		    dot++;
		if(dot >= 2)
		    break;
		ban_mask[i] = addr[i];
	}

	//printf("mark_player_as_banned: 1 ban_mask=\"%s\", ip=\"%s\"", ban_mask, addr); //отладка!!!

	if(strcmp(ban_mask,"192.168") == 0)
	    return;
    mysql_format(gMysql, request, sizeof(request), "UPDATE players a,characters b,players c,characters d SET c.ban_date=NOW(),c.ban=1,d.ban_count=d.ban_count+1 WHERE b.player_id=a.id AND (c.reg_ip_mask=a.reg_ip_mask OR c.reg_ip_mask=a.last_ip_mask OR c.last_ip_mask=a.reg_ip_mask OR c.last_ip_mask=a.last_ip_mask OR c.reg_ip_mask=\"%s\" OR c.last_ip_mask=\"%s\") AND a.id=%d ",ban_mask,ban_mask,gPlayersID[playerid]);
    strcat(request, "AND c.passwd=a.passwd AND d.player_id=c.id AND a.reg_ip_mask!=\"192.168\" AND a.last_ip_mask!=\"192.168\" AND c.ban=0");
	mysql_query(gMysql, request);
    mysql_format(gMysql, request, sizeof(request), "INSERT INTO ban_ip(ip,ban_date,ban_until) VALUES(\"%s\",NOW(),ADDTIME(now(),time(\"%d:00:00\")))",ban_mask,tm);
	mysql_query(gMysql, request);
    mysql_format(gMysql, request, sizeof(request), "INSERT INTO ban_ip(ip,ban_date,ban_until) SELECT reg_ip_mask,NOW(),ADDTIME(now(),time(\"%d:00:00\")) FROM players WHERE id=%d",tm,gPlayersID[playerid]);
	mysql_query(gMysql, request);
    mysql_format(gMysql, request, sizeof(request), "INSERT INTO ban_ip(ip,ban_date,ban_until) SELECT last_ip_mask,NOW(),ADDTIME(now(),time(\"%d:00:00\")) FROM players WHERE id=%d",tm,gPlayersID[playerid]);
	mysql_query(gMysql, request);

    mysql_format(gMysql, request, sizeof(request), "SELECT id FROM ban_ip WHERE ip=\"%s\" ORDER BY id DESC LIMIT 1", ban_mask);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
	    return;
	id = cache_get_field_content_int(0, "id", gMysql);
	if(cache_is_valid(result, gMysql))
		cache_delete(result);

	//printf("mark_player_as_banned: 2 id=%d", id); //отладка!!!
	
    mysql_format(gMysql, request, sizeof(request), "INSERT INTO ban_list(player_id,ban_mask,ban_until) (SELECT b.id,%d,ADDTIME(NOW(),TIME(\"%d:00:00\")) FROM players a,players b WHERE (b.reg_ip=a.reg_ip OR b.reg_ip=a.last_ip OR b.last_ip=a.reg_ip OR b.last_ip=a.last_ip) AND a.passwd=b.passwd AND a.id=%d)",id,tm,gPlayersID[playerid]);
	mysql_query(gMysql, request);

	//print("mark_player_as_banned: exit"); //отладка!!!
}

public mark_player_as_banned_name(name[], tm)
{
	new request[2048];
	new rows, fields;
	new Cache:result;
	new addr[24];
	new ban_mask[24];
	new i, dot, id;

   	mysql_format(gMysql, request, sizeof(request), "UPDATE players a,characters b,players c,characters d SET c.ban_date=NOW(),c.ban=1,d.ban_count=d.ban_count+1 WHERE b.player_id=a.id AND (c.reg_ip_mask=a.reg_ip_mask OR c.reg_ip_mask=a.last_ip_mask OR c.last_ip_mask=a.reg_ip_mask OR c.last_ip_mask=a.last_ip_mask) AND c.passwd=a.passwd AND d.player_id=c.id AND a.reg_ip_mask!=\"192.168\" AND a.last_ip_mask!=\"192.168\" AND a.name=\"%s\" AND c.ban=0",name);
	mysql_query(gMysql, request);

    mysql_format(gMysql, request, sizeof(request), "SELECT last_ip FROM players WHERE name=\"%s\" LIMIT 1",name);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
	    return;
	cache_get_field_content(0, "last_ip", addr, gMysql);
	if(cache_is_valid(result, gMysql))
		cache_delete(result);

	strdel(ban_mask, 0, sizeof(ban_mask)-1);
	for(i = 0, dot = 0; i < sizeof(addr); ++i)
	{
		if(addr[i] == '.')
		    dot++;
		if(dot >= 2)
		    break;
		ban_mask[i] = addr[i];
	}
	if(strcmp(ban_mask,"192.168") == 0)
	    return;
    mysql_format(gMysql, request, sizeof(request), "INSERT INTO ban_ip(ip,ban_date,ban_until) VALUES(\"%s\",NOW(),ADDTIME(now(),time(\"%d:00:00\")))",ban_mask,tm);
	mysql_query(gMysql, request);

    mysql_format(gMysql, request, sizeof(request), "SELECT id FROM ban_ip WHERE ip=\"%s\" ORDER BY id DESC LIMIT 1", ban_mask);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
	    return;
	id = cache_get_field_content_int(0, "id", gMysql);
	if(cache_is_valid(result, gMysql))
		cache_delete(result);

    mysql_format(gMysql, request, sizeof(request), "INSERT INTO ban_list(player_id,ban_mask,ban_until) (SELECT b.id,%d,ADDTIME(NOW(),TIME(\"%d:00:00\")) FROM players a,players b WHERE (b.reg_ip=a.reg_ip OR b.reg_ip=a.last_ip OR b.last_ip=a.reg_ip OR b.last_ip=a.last_ip) AND a.passwd=b.passwd AND a.name=\"%s\")",id,tm,name);
	mysql_query(gMysql, request);
//	thread_sql(request);
}

public mark_player_as_unbanned(name[])
{
	new request[768];
	new rows, fields;
	new Cache:result;
	new addr[24];
	new i;

    mysql_format(gMysql, request, sizeof(request), "UPDATE ban_ip a,ban_list b SET a.ip=\"\",a.ban_until=0,b.player_id=0 WHERE a.id=b.ban_mask AND b.player_id IN (SELECT b.id FROM players a,players b WHERE (b.reg_ip_mask=a.reg_ip_mask OR b.reg_ip_mask=a.last_ip_mask OR b.last_ip_mask=a.reg_ip_mask OR b.last_ip_mask=a.last_ip_mask) AND a.passwd=b.passwd AND a.name=\"%s\")",name);
	mysql_query(gMysql, request);
	
    mysql_format(gMysql, request, sizeof(request), "SELECT b.last_ip FROM players a,players b WHERE (b.reg_ip_mask=a.reg_ip_mask OR b.reg_ip_mask=a.last_ip_mask OR b.last_ip_mask=a.reg_ip_mask OR b.last_ip_mask=a.last_ip_mask) AND a.passwd=b.passwd AND a.name=\"%s\"", name);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows > 0)
	{
	    for(i = 0; i < rows; ++i)
	    {
	        strdel(addr, 0, sizeof(addr)-1);
			cache_get_field_content(i, "last_ip", addr, gMysql);
		    format(request, sizeof(request), "unbanip %s", addr);
		    SendRconCommand(request);
		}
	}
	if(cache_is_valid(result, gMysql))
		cache_delete(result);

    mysql_format(gMysql, request, sizeof(request), "UPDATE players a,players c SET a.ban_date=0,a.ban=0,c.ban_date=0,c.ban=0 WHERE (c.reg_ip_mask=a.reg_ip_mask OR c.reg_ip_mask=a.last_ip_mask OR c.last_ip_mask=a.reg_ip_mask OR c.last_ip_mask=a.last_ip_mask) AND c.passwd=a.passwd AND a.name=\"%s\"",name);
	mysql_query(gMysql, request);
}

public create_banned_list(list[], list_size)
{
	new rows, fields;
	new request[128];
	new Cache:result;
	new i;
	new name[64];

    mysql_format(gMysql, request, sizeof(request), "SELECT name FROM players WHERE ban>0 ORDER BY ban_date DESC LIMIT 30");
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
	    return -1;
	for(i = 0; i < rows; ++i)
	{
		cache_get_field_content(i, "name", name, gMysql);
		strcat(list, name, list_size);
		strcat(list, "\n", list_size);
		if(strlen(list) > (list_size - 30))
		    break;
	}
	if(cache_is_valid(result, gMysql))
		cache_delete(result);
	return 1;
}

public load_player_cheater_level(playerid)
{
	new rows, fields;
	new request[128];
	new Cache:result;
	new out_value;

	if(set_player_id(playerid) < 0)
	    return -100;
	
	if(gPlayersID[playerid] <= 0)
	    return -1;

    mysql_format(gMysql, request, sizeof(request), "SELECT cheater FROM characters WHERE player_id=%d LIMIT 1", gPlayersID[playerid]);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
	    return -1;
	out_value = cache_get_field_content_int(0, "cheater", gMysql);
	if(cache_is_valid(result, gMysql))
		cache_delete(result);

	return out_value;
}

public zero_craft_item(inv[CRAFT_ITEM])
{
	inv[db_id] = -1;//инвентарь
	inv[tp_id] = -1;//инвентарь
	inv[pr_id] = 0;//инвентарь
	inv[object] = INVALID_OBJECT_ID;//инвентарь
	inv[inv_id] = -1;//инвентарь
	inv[gnd_id] = -1;//инвентарь
	inv[isrot][n_X] = 0;//инвентарь
	inv[isrot][n_Y] = 0;//инвентарь
	inv[isrot][n_Z] = 0;//инвентарь
	inv[deg][f_X] = 0.0;//инвентарь
	inv[deg][f_Y] = 0.0;//инвентарь
	inv[deg][f_Z] = 0.0;//инвентарь
	inv[zoom] = 0.0;//инвентарь
	inv[obj_rotatable] = 0;
	inv[rot][f_X] = 0.0;
	inv[rot][f_Y] = 0.0;
	inv[rot][f_Z] = 0.0;
	inv[obj_height] = 0.0;
	inv[obj_owner] = 0;
	inv[obj_auto] = 0;
	inv[obj_inventory] = 0;
	inv[obj_value] = 0;
	inv[obj_coord][f_X] = 0.0;
	inv[obj_coord][f_Y] = 0.0;
	inv[obj_coord][f_Z] = 0.0;
}

public copy_craft_item(inv_to[CRAFT_ITEM], inv_from[CRAFT_ITEM])
{
	inv_to[db_id] = inv_from[db_id];
	inv_to[tp_id] = inv_from[tp_id];
	inv_to[pr_id] = inv_from[pr_id];
	inv_to[object] = inv_from[object];
	inv_to[inv_id] = inv_from[inv_id];
	inv_to[gnd_id] = inv_from[gnd_id];
	inv_to[isrot][n_X] = inv_from[isrot][n_X];
	inv_to[isrot][n_Y] = inv_from[isrot][n_Y];
	inv_to[isrot][n_Z] = inv_from[isrot][n_Z];
	inv_to[deg][f_X] = inv_from[deg][f_X];
	inv_to[deg][f_Y] = inv_from[deg][f_Y];
	inv_to[deg][f_Z] = inv_from[deg][f_Z];
	inv_to[zoom] = inv_from[zoom];
	inv_to[obj_rotatable] = inv_from[obj_rotatable];
	inv_to[rot][f_X] = inv_from[rot][f_X];
	inv_to[rot][f_Y] = inv_from[rot][f_Y];
	inv_to[rot][f_Z] = inv_from[rot][f_Z];
	inv_to[obj_height] = inv_from[obj_height];
	inv_to[obj_owner] = inv_from[obj_owner];
	inv_to[obj_auto] = inv_from[obj_auto];
	inv_to[obj_inventory] = inv_from[obj_inventory];
	inv_to[obj_value] = inv_from[obj_value];
	inv_to[obj_coord][f_X] = inv_from[obj_coord][f_X];
	inv_to[obj_coord][f_Y] = inv_from[obj_coord][f_Y];
	inv_to[obj_coord][f_Z] = inv_from[obj_coord][f_Z];
}

public move_craft_item(inv_to[CRAFT_ITEM], inv_from[CRAFT_ITEM])
{
	copy_craft_item(inv_to, inv_from);
	zero_craft_item(inv_from);
}

public init_craft_item(item[CRAFT_ITEM], object_id)
{
	new part_one[512], request[1536];
	new rows, fields;
	new Cache:result;

	//начальная инициализация модели объекта
	item[object] = INVALID_OBJECT_ID;
	//невозможно при помощи этой функции забрать вещь из чужого инвентаря!
	format(part_one, sizeof(part_one), "SELECT a.id as db_id,IFNULL(a.placex,0) as placex,IFNULL(a.placey,0) as placey,IFNULL(a.placez,0) as placez,b.id as tp_id,IFNULL(a.prev_id,0) as pr_id,b.invent_id as inv_id,b.inworld_id as gnd_id,b.rotx as isrotx,b.roty as isroty,b.rotz as isrotz");
	mysql_format(gMysql, request, sizeof(request), "%s,b.inventx as degx,b.inventy as degy,b.inventz as degz,b.zoom,b.rotatable,b.posx as addx,b.posy as addy,b.posz as addz,b.height,b.is_auto,IFNULL(a.obj_id,%d) as obj_id,b.is_inventory,a.value,IFNULL(a.owner,0) as owner_id FROM objects a INNER JOIN things b ON a.thing_id=b.id WHERE a.id=%d LIMIT 1",part_one,INVALID_OBJECT_ID,object_id);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
	{
	    zero_craft_item(item);
		if(cache_is_valid(result, gMysql))
			cache_delete(result);
	    return -1;
	}
	item[db_id] = cache_get_field_content_int(0, "db_id", gMysql);
	item[tp_id] = cache_get_field_content_int(0, "tp_id", gMysql);
	item[pr_id] = cache_get_field_content_int(0, "pr_id", gMysql);
	item[object] = cache_get_field_content_int(0, "obj_id", gMysql);
	item[inv_id] = cache_get_field_content_int(0, "inv_id", gMysql);
	item[gnd_id] = cache_get_field_content_int(0, "gnd_id", gMysql);
	item[isrot][n_X] = cache_get_field_content_int(0, "isrotx", gMysql);
	item[isrot][n_Y] = cache_get_field_content_int(0, "isroty", gMysql);
	item[isrot][n_Z] = cache_get_field_content_int(0, "isrotz", gMysql);
	item[deg][f_X] = cache_get_field_content_float(0, "degx", gMysql);
	item[deg][f_Y] = cache_get_field_content_float(0, "degy", gMysql);
	item[deg][f_Z] = cache_get_field_content_float(0, "degz", gMysql);
	item[zoom] = cache_get_field_content_float(0, "zoom", gMysql);
	item[obj_rotatable] = cache_get_field_content_int(0, "rotatable", gMysql);
	item[rot][f_X] = cache_get_field_content_float(0, "addx", gMysql);
	item[rot][f_Y] = cache_get_field_content_float(0, "addy", gMysql);
	item[rot][f_Z] = cache_get_field_content_float(0, "addz", gMysql);
	item[obj_height] = cache_get_field_content_float(0, "height", gMysql);
	item[obj_owner] = cache_get_field_content_int(0, "owner_id", gMysql);
	item[obj_auto] = cache_get_field_content_int(0, "is_auto", gMysql);
	item[obj_inventory] = cache_get_field_content_int(0, "is_inventory", gMysql);
	item[obj_value] = cache_get_field_content_int(0, "value", gMysql);
	item[obj_coord][f_X] = cache_get_field_content_float(0, "placex", gMysql);
	item[obj_coord][f_Y] = cache_get_field_content_float(0, "placey", gMysql);
	item[obj_coord][f_Z] = cache_get_field_content_float(0, "placez", gMysql);

	if(cache_is_valid(result, gMysql))
		cache_delete(result);

	return 1;
}

public add_item_to_global_cache(item[CRAFT_ITEM])
{
	new i, j;

	if(item[db_id] == -1)
	    return;

	for(i = 0; i < MAX_PLAYERS; ++i)
	{
	    if(!IsPlayerSpawned(i) || IsPlayerNPC(i))
	        continue;
	    //проверяем, нет ли этого объекта уже в кэше
		for(j = 0; j < CACHED_OBJECTS_COUNT; ++j)
		{
			if(gCachedPlayers[i][cached_range] == 0.0 || gCachedItems[i][j][db_id] == item[db_id])
			{
				break;
			}
		}
		if(j < CACHED_OBJECTS_COUNT)
		    continue;
		if(VectorSize(item[obj_coord][f_X]-gCachedPlayers[i][cached_player_pos][f_X],
					  item[obj_coord][f_Y]-gCachedPlayers[i][cached_player_pos][f_Y],
					  item[obj_coord][f_Z]-gCachedPlayers[i][cached_player_pos][f_Z]) < gCachedPlayers[i][cached_range])
		{
			for(j = 0; j < CACHED_OBJECTS_COUNT; ++j)
			{
				if(gCachedItems[i][j][db_id] == -1)
				{
					copy_craft_item(gCachedItems[i][j], item);
					break;
				}
			}
		}
	}
}

public sub_item_from_global_cache(item[CRAFT_ITEM])
{
	new i, j;
	
	if(item[db_id] == -1)
		return;

	for(i = 0; i < MAX_PLAYERS; ++i)
	{
		for(j = 0; j < CACHED_OBJECTS_COUNT; ++j)
		{
			if(gCachedItems[i][j][db_id] == item[db_id])
			{
				zero_craft_item(gCachedItems[i][j]);
			}
		}
	}
}

public cache_player_inventory(playerid)
{
	new rows, fields;
	new part_one[512];
	new request[2048];
	new Cache:result;
	new i, j, id, owner;
	new objects_str[144], buff_str[64];
	new inv[MAX_INVENTORY_ON_PLAYER][CRAFT_ITEM];

	//проверка id игрока
	if(playerid == INVALID_PLAYER_ID)
	    return;

	//проверка id игрока
	if(gPlayersID[playerid] <= 0)
		if(set_player_id(playerid) < 0)
		    return;

	//проверка id игрока
 	if(gPlayersID[playerid] <= 0)
	    return;

	strdel(objects_str, 0, sizeof(objects_str)-1);
	for(i = 0; i < MAX_INVENTORY_ON_PLAYER; ++i)
	{
	    zero_craft_item(inv[i]);
	    strdel(buff_str, 0, sizeof(buff_str)-1);
		format(buff_str, sizeof(buff_str), "%sinv%d", (strlen(objects_str)>0)?(","):(""), i+1);
		strcat(objects_str, buff_str);
	}

    mysql_format(gMysql, request, sizeof(request), "SELECT %s FROM inventory WHERE player_id=%d LIMIT 1", objects_str, gPlayersID[playerid]);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows > 0)
	{
		for(i = 0; i < MAX_INVENTORY_ON_PLAYER; ++i)
		{
		    strdel(buff_str, 0, sizeof(buff_str)-1);
			format(buff_str, sizeof(buff_str), "inv%d", i+1);
			inv[i][db_id] = cache_get_field_content_int(0, buff_str, gMysql);
		}
	}

	if(cache_is_valid(result, gMysql))
		cache_delete(result);

	strdel(objects_str, 0, sizeof(objects_str)-1);
	for(i = 0; i < MAX_INVENTORY_ON_PLAYER; ++i)
	{
	    if(inv[i][db_id] > 0)
		{
		    strdel(buff_str, 0, sizeof(buff_str)-1);
			format(buff_str, sizeof(buff_str), "%s%d", (strlen(objects_str)>0)?(","):(""), inv[i][db_id]);
			strcat(objects_str, buff_str);
		}
	}

	if(strlen(objects_str) > 0)
	{
	    format(part_one, sizeof(part_one), "SELECT a.id as db_id,IFNULL(a.prev_id,0) as pr_id,IFNULL(a.obj_id,%d) as object,b.id as tp_id,b.invent_id as inv_id,b.inworld_id as gnd_id,b.rotx as isrotx,b.roty as isroty,b.rotz as isrotz",INVALID_OBJECT_ID);
	    mysql_format(gMysql, request, sizeof(request), "%s,b.inventx as degx,b.inventy as degy,b.inventz as degz,b.zoom,b.rotatable,b.posx as addx,b.posy as addy,b.posz as addz,b.height,b.is_auto,b.is_inventory,a.value,IFNULL(a.owner,0) as owner_id FROM objects a,things b WHERE a.id in (%s) AND a.thing_id=b.id",part_one,objects_str);
		result = mysql_query(gMysql, request);
		cache_get_data(rows, fields, gMysql);
		if(rows > 0)
		{
			for(i = 0; i < rows; ++i)
			{
			    cache_set_active(result, gMysql);
			    id = cache_get_field_content_int(i, "db_id", gMysql);
				owner = cache_get_field_content_int(i, "owner_id", gMysql);

			    for(j = 0; j < MAX_INVENTORY_ON_PLAYER; ++j)
			    {
			        if(inv[j][db_id] == id)
			        {
						if(owner != 0 && owner != gPlayersID[playerid])
						{
						    drop_object_on_ground(playerid, inv[j][db_id]);
						    zero_craft_item(inv[j]);
						}
						else
						{
							inv[j][tp_id] = cache_get_field_content_int(i, "tp_id", gMysql);
							inv[j][pr_id] = cache_get_field_content_int(i, "pr_id", gMysql);
							inv[j][object] = cache_get_field_content_int(i, "object", gMysql);
							inv[j][inv_id] = cache_get_field_content_int(i, "inv_id", gMysql);
							inv[j][gnd_id] = cache_get_field_content_int(i, "gnd_id", gMysql);
							inv[j][isrot][n_X] = cache_get_field_content_int(i, "isrotx", gMysql);
							inv[j][isrot][n_Y] = cache_get_field_content_int(i, "isroty", gMysql);
							inv[j][isrot][n_Z] = cache_get_field_content_int(i, "isrotz", gMysql);
							inv[j][deg][f_X] = cache_get_field_content_float(i, "degx", gMysql);
							inv[j][deg][f_Y] = cache_get_field_content_float(i, "degy", gMysql);
							inv[j][deg][f_Z] = cache_get_field_content_float(i, "degz", gMysql);
							inv[j][zoom] = cache_get_field_content_float(i, "zoom", gMysql);
							inv[j][obj_rotatable] = cache_get_field_content_int(i, "rotatable", gMysql);
							inv[j][rot][f_X] = cache_get_field_content_float(i, "addx", gMysql);
							inv[j][rot][f_Y] = cache_get_field_content_float(i, "addy", gMysql);
							inv[j][rot][f_Z] = cache_get_field_content_float(i, "addz", gMysql);
							inv[j][obj_height] = cache_get_field_content_float(i, "height", gMysql);
							inv[j][obj_owner] = owner;
							inv[j][obj_auto] = cache_get_field_content_int(i, "is_auto", gMysql);
							inv[j][obj_inventory] = cache_get_field_content_int(i, "is_inventory", gMysql);
							inv[j][obj_value] = cache_get_field_content_int(i, "value", gMysql);
							inv[j][obj_coord][f_X] = 0.0;
							inv[j][obj_coord][f_Y] = 0.0;
							inv[j][obj_coord][f_Z] = 0.0;
						}
					}
				}
			}
		}
		if(cache_is_valid(result, gMysql))
			cache_delete(result);
	}
	
	for(i = 0; i < MAX_INVENTORY_ON_PLAYER; ++i)
	{
		copy_craft_item(gInventoryItem[playerid][i], inv[i]);
	}
}

public cache_vehicle_inventory(vehicleid)
{
	new i, j, k, id, rows, fields;
	new request[1536];
	new buff[512];
	new column[32];
	new Cache:result;
	new objects_str[256];
	new inv[MAX_INVENTORY_ON_VEHICLE][CRAFT_ITEM];

//	set_vehicle_id(vehicleid);

	strdel(objects_str, 0, sizeof(objects_str)-1);
	for(i = 0; i < MAX_INVENTORY_ON_VEHICLE; ++i)
	{
		zero_craft_item(inv[i]);
		strdel(column, 0, sizeof(column)-1);
		format(column, sizeof(column), "%sinv%d", (strlen(objects_str)>0)?(","):(""), i+1);
		strcat(objects_str, column);
	}

    mysql_format(gMysql, request, sizeof(request), "SELECT %s FROM veh_invent WHERE object_id=%d LIMIT 1", objects_str, gVeh[vehicleid][0]);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
	{
		for(i = 0; i < MAX_INVENTORY_ON_VEHICLE; ++i)
		{
			copy_craft_item(gVehicleItem[vehicleid][i], inv[i]);//в машине
		}
	    return;
	}

	for(k = 0; k < MAX_INVENTORY_ON_VEHICLE; ++k)
	{
	    strdel(column, 0, sizeof(column)-1);
	    format(column, sizeof(column), "inv%d", k+1);
		inv[k][db_id] = cache_get_field_content_int(0, column, gMysql);
	}
	if(cache_is_valid(result, gMysql))
		cache_delete(result);

	strdel(objects_str, 0, sizeof(objects_str)-1);
	for(i = 0; i < MAX_INVENTORY_ON_VEHICLE; ++i)
	{
		if(inv[i][db_id] > 0)
		{
		    strdel(column, 0, sizeof(column)-1);
		    format(column, sizeof(column), "%s%d", (strlen(objects_str)>0)?(","):(""), inv[i][db_id]);
			strcat(objects_str, column);
		}
	}

	if(strlen(objects_str) > 0)
	{
		format(buff, sizeof(buff), "SELECT a.id as db_id,IFNULL(a.prev_id,0) as prev_id,IFNULL(a.obj_id,%d) as object,b.id as tp_id,b.invent_id as inv_id,b.inworld_id as gnd_id,b.rotx as isrotx",INVALID_OBJECT_ID);
	    mysql_format(gMysql, request, sizeof(request), "%s,b.roty as isroty,b.rotz as isrotz,b.inventx as degx,b.inventy as degy,b.inventz as degz,b.zoom,b.rotatable,b.posx as addx,b.posy as addy,b.posz as addz,b.height,b.is_auto,b.is_inventory,a.value,IFNULL(a.owner,0) as owner_id FROM objects a,things b WHERE a.id in (%s) AND a.thing_id=b.id",buff,objects_str);
		result = mysql_query(gMysql, request);
		cache_get_data(rows, fields, gMysql);
		if(rows > 0)
		{
		    for(i = 0; i < rows; ++i)
		    {
		        id = cache_get_field_content_int(i, "db_id", gMysql);
		        for(j = 0; j < MAX_INVENTORY_ON_VEHICLE; ++j)
		        {
		            if(id == inv[j][db_id])
		            {
						inv[j][tp_id] = cache_get_field_content_int(i, "tp_id", gMysql);
						inv[j][pr_id] = cache_get_field_content_int(i, "prev_id", gMysql);
						inv[j][object] = cache_get_field_content_int(i, "object", gMysql);
						inv[j][inv_id] = cache_get_field_content_int(i, "inv_id", gMysql);
						inv[j][gnd_id] = cache_get_field_content_int(i, "gnd_id", gMysql);
						inv[j][isrot][n_X] = cache_get_field_content_int(i, "isrotx", gMysql);
						inv[j][isrot][n_Y] = cache_get_field_content_int(i, "isroty", gMysql);
						inv[j][isrot][n_Z] = cache_get_field_content_int(i, "isrotz", gMysql);
						inv[j][deg][f_X] = cache_get_field_content_float(i, "degx", gMysql);
						inv[j][deg][f_Y] = cache_get_field_content_float(i, "degy", gMysql);
						inv[j][deg][f_Z] = cache_get_field_content_float(i, "degz", gMysql);
						inv[j][zoom] = cache_get_field_content_float(i, "zoom", gMysql);
						inv[j][obj_rotatable] = cache_get_field_content_int(i, "rotatable", gMysql);
						inv[j][rot][f_X] = cache_get_field_content_float(i, "addx", gMysql);
						inv[j][rot][f_Y] = cache_get_field_content_float(i, "addy", gMysql);
						inv[j][rot][f_Z] = cache_get_field_content_float(i, "addz", gMysql);
						inv[j][obj_height] = cache_get_field_content_float(i, "height", gMysql);
						inv[j][obj_owner] = cache_get_field_content_int(i, "owner_id", gMysql);
						inv[j][obj_auto] = cache_get_field_content_int(i, "is_auto", gMysql);
						inv[j][obj_inventory] = cache_get_field_content_int(i, "is_inventory", gMysql);
						inv[j][obj_value] = cache_get_field_content_int(i, "value", gMysql);
						inv[j][obj_coord][f_X] = 0.0;
						inv[j][obj_coord][f_Y] = 0.0;
						inv[j][obj_coord][f_Z] = 0.0;
					}
				}
			}
		}
		else
		    print("error in load_vehicle_inventory()");
		if(cache_is_valid(result, gMysql))
			cache_delete(result);
	}
	
	for(i = 0; i < MAX_INVENTORY_ON_VEHICLE; ++i)
	{
		copy_craft_item(gVehicleItem[vehicleid][i], inv[i]);//в машине
	}
}

public cache_bag_inventory(playerid)
{
	new i, j, k, id, rows, fields, owner;
	new request[1536];
	new buff[512];
	new column[32];
	new Cache:result;
	new objects_str[144];
	new inv[MAX_INVENTORY_IN_BAG][CRAFT_ITEM];

	if(gPlayersID[playerid] <= 0)
	    return -1;

	if(gBag[playerid][1] <= 0 || gBag[playerid][0] <= 0)
	    return -1;

	strdel(objects_str, 0, sizeof(objects_str)-1);
	for(i = 0; i < MAX_INVENTORY_IN_BAG; ++i)
	{
		zero_craft_item(inv[i]);//в рюкзаке
	    strdel(column, 0, sizeof(column)-1);
		format(column, sizeof(column), "%sinv%d", (strlen(objects_str)>0)?(","):(""), i+1);
		strcat(objects_str, column);
	}

    mysql_format(gMysql, request, sizeof(request), "SELECT %s FROM bag_invent WHERE object_id=%d LIMIT 1",objects_str,gBag[playerid][1]);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
	{
	    create_new_bag(gBag[playerid][1]);
	    for(i = 0; i < MAX_INVENTORY_IN_BAG; ++i)
	    {
			copy_craft_item(gBagItem[playerid][i], inv[i]);//в рюкзаке
	    }
	    return 0;
	}
	for(k = 0; k < MAX_INVENTORY_IN_BAG; ++k)
	{
	    strdel(column, 0, sizeof(column)-1);
	    format(column, sizeof(column), "inv%d", k+1);
		inv[k][db_id] = cache_get_field_content_int(0, column, gMysql);
	}
	if(cache_is_valid(result, gMysql))
		cache_delete(result);

	strdel(objects_str, 0, sizeof(objects_str)-1);
	for(i = 0; i < MAX_INVENTORY_IN_BAG; ++i)
	{
		if(inv[i][db_id] > 0)
		{
		    strdel(column, 0, sizeof(column)-1);
		    format(column, sizeof(column), "%s%d", (strlen(objects_str)>0)?(","):(""), inv[i][db_id]);
			strcat(objects_str, column);
		}
	}

	if(strlen(objects_str) > 0)
	{
		format(buff, sizeof(buff), "SELECT a.id as db_id,IFNULL(a.prev_id,0) as prev_id,IFNULL(a.obj_id,%d) as object,b.id as tp_id,b.invent_id as inv_id,b.inworld_id as gnd_id",INVALID_OBJECT_ID);
	    mysql_format(gMysql, request, sizeof(request), "%s,b.rotx as isrotx,b.roty as isroty,b.rotz as isrotz,b.inventx as degx,b.inventy as degy,b.inventz as degz,b.zoom,b.rotatable,b.posx as addx,b.posy as addy,b.posz as addz,b.height,b.is_auto,b.is_inventory,a.value,IFNULL(a.owner,0) as owner_id FROM objects a,things b WHERE a.id in (%s) AND a.thing_id=b.id",buff,objects_str);
		result = mysql_query(gMysql, request);
		cache_get_data(rows, fields, gMysql);
		if(rows > 0)
		{
		    for(i = 0; i < rows; ++i)
		    {
			    id = cache_get_field_content_int(i, "db_id", gMysql);
				for(j = 0; j < MAX_INVENTORY_IN_BAG; ++j)
				{
				    if(id == inv[j][db_id])
				    {
						owner = cache_get_field_content_int(i, "owner_id", gMysql);
						if(owner != 0 && owner != gPlayersID[playerid])
						{
							zero_craft_item(inv[i]);//в рюкзаке
							inv[i][tp_id] = -5;//в рюкзаке
						}
						else
						{
							inv[j][tp_id] = cache_get_field_content_int(i, "tp_id", gMysql);
							inv[j][pr_id] = cache_get_field_content_int(i, "prev_id", gMysql);
							inv[j][object] = cache_get_field_content_int(i, "object", gMysql);
							inv[j][inv_id] = cache_get_field_content_int(i, "inv_id", gMysql);
							inv[j][gnd_id] = cache_get_field_content_int(i, "gnd_id", gMysql);
							inv[j][isrot][n_X] = cache_get_field_content_int(i, "isrotx", gMysql);
							inv[j][isrot][n_Y] = cache_get_field_content_int(i, "isroty", gMysql);
							inv[j][isrot][n_Z] = cache_get_field_content_int(i, "isrotz", gMysql);
							inv[j][deg][f_X] = cache_get_field_content_float(i, "degx", gMysql);
							inv[j][deg][f_Y] = cache_get_field_content_float(i, "degy", gMysql);
							inv[j][deg][f_Z] = cache_get_field_content_float(i, "degz", gMysql);
							inv[j][zoom] = cache_get_field_content_float(i, "zoom", gMysql);
							inv[j][obj_rotatable] = cache_get_field_content_int(i, "rotatable", gMysql);
							inv[j][rot][f_X] = cache_get_field_content_float(i, "addx", gMysql);
							inv[j][rot][f_Y] = cache_get_field_content_float(i, "addy", gMysql);
							inv[j][rot][f_Z] = cache_get_field_content_float(i, "addz", gMysql);
							inv[j][obj_height] = cache_get_field_content_float(i, "height", gMysql);
							inv[j][obj_owner] = owner;
							inv[j][obj_auto] = cache_get_field_content_int(i, "is_auto", gMysql);
							inv[j][obj_inventory] = cache_get_field_content_int(i, "is_inventory", gMysql);
							inv[j][obj_value] = cache_get_field_content_int(i, "value", gMysql);
							inv[j][obj_coord][f_X] = 0.0;
							inv[j][obj_coord][f_Y] = 0.0;
							inv[j][obj_coord][f_Z] = 0.0;
						}
					}
				}
			}
		}
		else
		    print("error in load_bag_inventory()");
		if(cache_is_valid(result, gMysql))
			cache_delete(result);
	}
	
	for(i = 0; i < MAX_INVENTORY_IN_BAG; ++i)
	{
		copy_craft_item(gBagItem[playerid][i], inv[i]);//в рюкзаке
	}

	return 1;
}

public cache_ground_inventory(playerid, Float:range)
{
	new request[1536];
	new part_one[1024];
	new rows, fields;
	new i, j;
	new Float:x, Float:y, Float:z;
	new Float:placex, Float:placey, Float:placez;
	new Cache:result;
	new Float:vector, Float:distance;
	new gnd[MAX_INVENTORY_ON_GROUND][CRAFT_ITEM];

	//проверка id игрока
	if(playerid == INVALID_PLAYER_ID)
	    return;

	//проверка id игрока
	if(gPlayersID[playerid] <= 0)
		if(set_player_id(playerid) < 0)
		    return;

	//проверка id игрока
 	if(gPlayersID[playerid] <= 0)
	    return;

	for(i = 0; i < MAX_INVENTORY_ON_GROUND; ++i)
	{
		zero_craft_item(gnd[i]);//на земле
	}
	
	GetPlayerPos(playerid, x, y, z);

//SELECT a.id as db_id,b.id as tp_id,b.invent_id as inv_id,b.inworld_id as gnd_id,b.rotx as isrotx,b.roty as isroty,b.rotz as isrotz,b.inventx as degx,b.inventy as degy,b.inventz as degz,b.zoom,b.rotatable,b.posx as addx,b.posy as addy,b.posz as addz,b.height,IFNULL(a.owner,0) as owner_id FROM objects a,things b WHERE a.id in (%s) AND a.thing_id=b.id
	vector = VectorSize(x, y, z);
	format(part_one, sizeof(part_one), "SELECT a.placex,a.placey,a.placez,a.id as db_id,IFNULL(a.prev_id,0) as pr_id,IFNULL(a.obj_id,%d) as object,b.id as tp_id,b.invent_id as inv_id,b.inworld_id as gnd_id",INVALID_OBJECT_ID);
    mysql_format(gMysql, request, sizeof(request), "%s,b.rotx as isrotx,b.roty as isroty,b.rotz as isrotz,b.inventx as degx,b.inventy as degy,b.inventz as degz,b.zoom,b.rotatable,b.posx as addx,b.posy as addy,b.posz as addz,b.height,b.is_auto,b.is_inventory,a.value,IFNULL(a.owner,0) as owner_id FROM objects a,things b WHERE a.thing_id=b.id AND a.vector IS NOT NULL AND ABS(a.vector-%f)<%f LIMIT 400",part_one,vector,range);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);

	if(rows <= 0)
	{
		if(cache_is_valid(result, gMysql))
			cache_delete(result);
	    return;
	}

	for(i = 0, j = 0; i < rows; ++i)
	{
		placex = cache_get_field_content_float(i, "placex", gMysql);
		placey = cache_get_field_content_float(i, "placey", gMysql);
		placez = cache_get_field_content_float(i, "placez", gMysql);

//		distance = floatsqroot( floatadd( floatadd( floatmul(floatsub(placex,x),floatsub(placex,x)), floatmul(floatsub(placey,y),floatsub(placey,y)) ), floatmul(floatsub(placez,z),floatsub(placez,z)) ) );
		distance = VectorSize(placex-x, placey-y, placez-z);

	    if(distance < range)
		{
			gnd[j][db_id] = cache_get_field_content_int(i, "db_id", gMysql);
			gnd[j][tp_id] = cache_get_field_content_int(i, "tp_id", gMysql);
			gnd[j][pr_id] = cache_get_field_content_int(i, "pr_id", gMysql);
			gnd[j][object] = cache_get_field_content_int(i, "object", gMysql);
			gnd[j][inv_id] = cache_get_field_content_int(i, "inv_id", gMysql);
			gnd[j][gnd_id] = cache_get_field_content_int(i, "gnd_id", gMysql);
			gnd[j][isrot][n_X] = cache_get_field_content_int(i, "isrotx", gMysql);
			gnd[j][isrot][n_Y] = cache_get_field_content_int(i, "isroty", gMysql);
			gnd[j][isrot][n_Z] = cache_get_field_content_int(i, "isrotz", gMysql);
			gnd[j][deg][f_X] = cache_get_field_content_float(i, "degx", gMysql);
			gnd[j][deg][f_Y] = cache_get_field_content_float(i, "degy", gMysql);
			gnd[j][deg][f_Z] = cache_get_field_content_float(i, "degz", gMysql);
			gnd[j][zoom] = cache_get_field_content_float(i, "zoom", gMysql);
			gnd[j][obj_rotatable] = cache_get_field_content_int(i, "rotatable", gMysql);
			gnd[j][rot][f_X] = cache_get_field_content_float(i, "addx", gMysql);
			gnd[j][rot][f_Y] = cache_get_field_content_float(i, "addy", gMysql);
			gnd[j][rot][f_Z] = cache_get_field_content_float(i, "addz", gMysql);
			gnd[j][obj_height] = cache_get_field_content_float(i, "height", gMysql);
			gnd[j][obj_owner] = cache_get_field_content_int(i, "owner_id", gMysql);
			gnd[j][obj_auto] = cache_get_field_content_int(i, "is_auto", gMysql);
			gnd[j][obj_inventory] = cache_get_field_content_int(i, "is_inventory", gMysql);
			gnd[j][obj_value] = cache_get_field_content_int(i, "value", gMysql);
			gnd[j][obj_coord][f_X] = 0.0;
			gnd[j][obj_coord][f_Y] = 0.0;
			gnd[j][obj_coord][f_Z] = 0.0;
//		    printf("db_obj=%d",gnd[j][db_id]);//отладка!!!!
			if(j >= (MAX_INVENTORY_ON_GROUND-1))
			    break;
			j++;
		}
	}

	if(cache_is_valid(result, gMysql))
		cache_delete(result);
		
	for(i = 0; i < MAX_INVENTORY_ON_GROUND; ++i)
	{
		copy_craft_item(gGroundItem[playerid][i], gnd[i]);//на земле
	}
}

public set_unusual_objects()
{
	new rows, fields;
	new request[128];
	new Cache:result;
	new thing_name[128];

	mysql_format(gMysql, request, sizeof(request), "SELECT a.id,a.name FROM things a INNER JOIN thing_type b ON a.type_id=b.id WHERE b.name=\"SOME_UNUSUAL_TYPE\"");
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
	{
		for(new i = 0; i < UNUSUAL_OBJECTS_COUNT; ++i)
		{
		    gUnusualObject[i] = 0;
		}
	    return;
	}
	for(new i = 0; i < rows; ++i)
	{
		strdel(thing_name, 0, sizeof(thing_name)-1);
		cache_get_field_content(i, "name", thing_name, gMysql);
		if(strcmp(thing_name, "FIRE_OBJECT") == 0)
		{
			gUnusualObject[FIRE_OBJECT] = cache_get_field_content_int(i, "id", gMysql);
			continue;
		}
		if(strcmp(thing_name, "GAS_OBJECT") == 0)
		{
			gUnusualObject[GAS_OBJECT] = cache_get_field_content_int(i, "id", gMysql);
			continue;
		}
		if(strcmp(thing_name, "WATER_OBJECT") == 0)
		{
			gUnusualObject[WATER_OBJECT] = cache_get_field_content_int(i, "id", gMysql);
			continue;
		}
		if(strcmp(thing_name, "VEHICLE_OBJECT") == 0)
		{
			gUnusualObject[VEHICLE_OBJECT] = cache_get_field_content_int(i, "id", gMysql);
			continue;
		}
	}
	if(cache_is_valid(result, gMysql))
		cache_delete(result);
}

public update_tickval_objects(type[], sub_value)
{
	new rows, fields;
	new request[1024];
	new Cache:result;
	new id, value;
	new i;

	//ищем временные объекты
    mysql_format(gMysql, request, sizeof(request), "SELECT a.id,a.value FROM objects a INNER JOIN (things b, thing_type c) ON (a.thing_id=b.id AND b.type_id=c.id) WHERE c.name in (%s)", type);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows > 0)
	{
	    for(i = 0; i < rows; ++i)
	    {
		    cache_set_active(result, gMysql);
			id = cache_get_field_content_int(i, "id", gMysql);
			value = cache_get_field_content_int(i, "value", gMysql);
			if(value <= sub_value)
			{
			    //разбираем и удаляем объект
			    full_free_object_from_owner(id);
			}
			else
			{
			    //уменьшаем значение объекта на значение sub_value
			    mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET value=value-%d WHERE id=%d", sub_value, id);
//				mysql_query(gMysql, request);
				thread_sql(request);
			}
	    }
	}
	if(cache_is_valid(result, gMysql))
		cache_delete(result);
}

public init_key_labels()
{
	new request[128];

	mysql_format(gMysql, request, sizeof(request), "DELETE FROM key_icon");
	mysql_query(gMysql, request);
}

public create_key_labels(key_type[])
{
	new request[1536], buff[512];

#if defined DEBUG
	new opsDebug0, opsDebug1, opsDebug2;
	opsDebug0 = GetTickCount();
	opsDebug1 = GetTickCount();
	opsDebug2 = GetTickCount();
	printf("create_key_labels, 1 label: %d, %d", opsDebug2-opsDebug0,opsDebug2-opsDebug1);
	opsDebug1 = opsDebug2;
#endif

	init_key_labels();

#if defined DEBUG
	opsDebug2 = GetTickCount();
	printf("create_key_labels, 2 label: %d, %d", opsDebug2-opsDebug0,opsDebug2-opsDebug1);
	opsDebug1 = opsDebug2;
#endif

	//ищем ключи в инвентаре и в рюкзаках игроков (поиск по всем объектам - не лучшая идея)
	//для ускорения нужно добавить функцию поиска в инвентаре+рюкзаке
	format(buff, sizeof(buff), "SELECT a.key_id,i.id,a.object_id,e.obj_id,g.name FROM key_data a INNER JOIN (objects b,things c,thing_type d,objects e,things f,thing_type g,objects h,players i)");
    mysql_format(gMysql, request, sizeof(request), "%s ON (a.key_id=b.id AND i.id=IF(b.pl_owner_id IS NULL,h.pl_owner_id,b.pl_owner_id) AND h.id=IF(b.th_owner_id IS NULL,a.key_id,b.th_owner_id) AND b.thing_id=c.id AND c.type_id=d.id AND a.object_id=e.id AND e.thing_id=f.id AND f.type_id=g.id) WHERE d.name='%s' AND (b.pl_owner_id IS NOT NULL OR b.th_owner_id IS NOT NULL) ORDER BY i.id",buff,key_type);
	mysql_tquery(gMysql, request, "create_key_labels_t");

#if defined DEBUG
	opsDebug2 = GetTickCount();
	printf("create_key_labels, 3 label: %d, %d", opsDebug2-opsDebug0,opsDebug2-opsDebug1);
	opsDebug1 = opsDebug2;
#endif
}

public create_key_labels_t()	
{
	new rows, fields;
	new request[256], name[128];
	new Cache:result;
	new key_id, playerid, player_id, object_id, obj_id, icon_id, prev_player_id;
	new Float:x, Float:y, Float:z;
	new i, j;

#if defined DEBUG
	new opsDebug0, opsDebug1, opsDebug2;
	opsDebug2 = opsDebug1 = opsDebug0 = GetTickCount();
	printf("create_key_labels_t, 1 label: %d, %d", opsDebug2-opsDebug0,opsDebug2-opsDebug1);
	opsDebug1 = opsDebug2;
#endif

	result = cache_save(gMysql);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
	{
#if defined DEBUG
		opsDebug2 = GetTickCount();
		printf("create_key_labels_t, 2_1 label: %d, %d", opsDebug2-opsDebug0,opsDebug2-opsDebug1);
		opsDebug1 = opsDebug2;
#endif
	    //если такого объекта нету - выходим
		if(cache_is_valid(result, gMysql))
			cache_delete(result);
		return -1;
	}

	prev_player_id = 0;
	icon_id = 0;
	for(i = 0; i < rows; ++i)
	{
	    cache_set_active(result, gMysql);
		player_id = cache_get_field_content_int(i, "id", gMysql);
		if(player_id != prev_player_id)
		    icon_id = 0;
		if(icon_id == 100)
		    continue;
		prev_player_id = player_id;
		for(j = 0; j < MAX_PLAYERS; ++j)
		{
		    if(gPlayersID[j] == player_id)
		    {
		        playerid = j;
		        break;
		    }
		}
		if(j == MAX_PLAYERS)
		    continue;
		key_id = cache_get_field_content_int(i, "key_id", gMysql);
		object_id = cache_get_field_content_int(i, "object_id", gMysql);
		obj_id = cache_get_field_content_int(i, "obj_id", gMysql);
		cache_get_field_content(i, "name", name, gMysql);
		if( strcmp(name, "SOME_VEHICLE", false) == 0 ||
			strcmp(name, "SOME_TANK", false) == 0 ||
			strcmp(name, "SOME_BUS_VEH", false) == 0 ||
		    strcmp(name, "SOME_HELICOPTER_TYPE", false) == 0 ||
		    strcmp(name, "SOME_BOAT_TYPE", false) == 0 )
		{
			GetVehiclePos(obj_id, x, y, z);
			SetPlayerMapIcon(playerid, icon_id, x, y, z, 55, 0xFFFFFFFF, MAPICON_GLOBAL); //метка авто
		}
		else if(strcmp(name, "SOME_DOOR_TYPE", false) == 0)
		{
			GetDynamicObjectPos(obj_id, x, y, z);
			SetPlayerMapIcon(playerid, icon_id, x, y, z, 31, 0xFFFFFFFF, MAPICON_GLOBAL); //метка домика
		}
	    mysql_format(gMysql, request, sizeof(request), "INSERT INTO key_icon(key_id,player_id,icon_id,object_id) VALUES(%d,%d,%d,%d)",key_id,player_id,icon_id,object_id);
		mysql_query(gMysql, request);
		icon_id++;
	}

	if(cache_is_valid(result, gMysql))
		cache_delete(result);

#if defined DEBUG
	opsDebug2 = GetTickCount();
	printf("create_key_labels_t, exit label: %d, %d", opsDebug2-opsDebug0,opsDebug2-opsDebug1);
	opsDebug1 = opsDebug2;
#endif

	return 1;
}

public set_key_labels(playerid, cell, area, fset)
{
	new rows, fields;
	new request[512];
	new Cache:result;
	new i, j, key_id, player_id, icon_id, object_id;
	new Float:x, Float:y, Float:z;
	new type_name[128];

	if(gPlayersID[playerid] <= 0)
	    return;

	//удаляем прежние метки ключа
	switch(area)
	{
		case INVENTORY_AREA:
		{
		    mysql_format(gMysql, request, sizeof(request), "SELECT a.key_id,a.player_id,a.icon_id FROM key_icon a INNER JOIN inventory b ON b.player_id=%d WHERE a.key_id=b.inv%d",gPlayersID[playerid], cell+1);
		}
		case BAG_AREA:
		{
			if(gBag[playerid][1] <= 0)
			    return;
		    mysql_format(gMysql, request, sizeof(request), "SELECT a.key_id,a.player_id,a.icon_id FROM key_icon a INNER JOIN bag_invent b ON b.object_id=%d WHERE a.key_id=b.inv%d",gBag[playerid][1],cell+1);
		}
		default:
		    return;
	}
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows > 0)
	{
	    cache_set_active(result, gMysql);
		key_id = cache_get_field_content_int(0, "key_id", gMysql);
		for(i = 0; i < rows; ++i)
		{
			player_id = cache_get_field_content_int(i, "player_id", gMysql);
			//если игрок ещё в игре - удаляем у него метку
			for(j = 0; j < MAX_PLAYERS; ++j)
			{
			    if(player_id == gPlayersID[j])
			        break;
			}
			if(j == MAX_PLAYERS)
			    break;
			    
			icon_id = cache_get_field_content_int(i, "icon_id", gMysql);
			RemovePlayerMapIcon(j, icon_id);
		}
	}
	else
	{
		if(cache_is_valid(result, gMysql))
			cache_delete(result);

		switch(area)
		{
			case INVENTORY_AREA:
			{
			    mysql_format(gMysql, request, sizeof(request), "SELECT inv%d as key_id FROM inventory WHERE player_id=%d",cell+1,gPlayersID[playerid]);
			}
			case BAG_AREA:
			{
				if(gBag[playerid][1] <= 0)
				    return;
			    mysql_format(gMysql, request, sizeof(request), "SELECT inv%d as key_id FROM bag_invent WHERE object_id=%d",cell+1,gBag[playerid][1]);
			}
			default:
			    return;
		}
		result = mysql_query(gMysql, request);
		cache_get_data(rows, fields, gMysql);
		if(rows <= 0)
		    return;
		key_id = cache_get_field_content_int(0, "key_id", gMysql);
	}
	if(cache_is_valid(result, gMysql))
		cache_delete(result);

    mysql_format(gMysql, request, sizeof(request), "DELETE FROM key_icon WHERE key_id=%d", key_id);
	mysql_query(gMysql, request);

	if(!fset)
	    return;

    mysql_format(gMysql, request, sizeof(request), "SELECT MAX(icon_id) as max_value FROM key_icon WHERE player_id=%d",gPlayersID[playerid]);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows > 0)
	{
	    icon_id = cache_get_field_content_int(0, "max_value", gMysql) + 1;
	    if(icon_id == 100)
	    {
			//вот тут надо бы переделать все метки на карте для игрока
			//затем найти максимум и назначить его icon_id (max+1)
			//...
		}
	}
	else
	    icon_id = 0;

	if(cache_is_valid(result, gMysql))
		cache_delete(result);

	//достигнут максимум меток на карте для игрока
	if(icon_id >= 100)
        return;

    mysql_format(gMysql, request, sizeof(request), "SELECT b.object_id,a.placex,a.placey,a.placez,d.name FROM objects a INNER JOIN (key_data b,things c,thing_type d) ON (b.object_id=a.id AND a.thing_id=c.id AND c.type_id=d.id) WHERE b.key_id=%d",key_id);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows > 0)
	{
		for(i = 0; i < rows; ++i)
		{
			//достигнут максимум меток на карте для игрока
			if(icon_id >= 100)
		        break;

			cache_set_active(result, gMysql);
			object_id = cache_get_field_content_int(i, "object_id", gMysql);
		    x = cache_get_field_content_float(i, "placex", gMysql);
		    y = cache_get_field_content_float(i, "placey", gMysql);
		    z = cache_get_field_content_float(i, "placez", gMysql);
		    cache_get_field_content(i, "name", type_name, gMysql, sizeof(type_name));
		    if(strcmp(type_name, "SOME_DOOR_TYPE") == 0)
		    {
			    SetPlayerMapIcon(playerid, icon_id, x, y, z, 31, 0xFFFFFFFF, MAPICON_GLOBAL); //метка домика
			}
		    else if(strcmp(type_name, "SOME_VEHICLE") == 0)
		    {
			    SetPlayerMapIcon(playerid, icon_id, x, y, z, 55, 0xFFFFFFFF, MAPICON_GLOBAL); //метка авто
			}
		    else if(strcmp(type_name, "SOME_BUS_VEH") == 0)
		    {
			    SetPlayerMapIcon(playerid, icon_id, x, y, z, 55, 0xFFFFFFFF, MAPICON_GLOBAL); //метка авто
			}
		    else if(strcmp(type_name, "SOME_TANK") == 0)
		    {
			    SetPlayerMapIcon(playerid, icon_id, x, y, z, 55, 0xFFFFFFFF, MAPICON_GLOBAL); //метка авто
			}
		    else if(strcmp(type_name, "SOME_HELICOPTER_TYPE") == 0)
		    {
			    SetPlayerMapIcon(playerid, icon_id, x, y, z, 55, 0xFFFFFFFF, MAPICON_GLOBAL); //метка авто
			}
		    else if(strcmp(type_name, "SOME_BOAT_TYPE") == 0)
		    {
			    SetPlayerMapIcon(playerid, icon_id, x, y, z, 55, 0xFFFFFFFF, MAPICON_GLOBAL); //метка авто
			}
		    mysql_format(gMysql, request, sizeof(request), "INSERT INTO key_icon(key_id,player_id,icon_id,object_id) VALUES(%d,%d,%d,%d)",key_id,gPlayersID[playerid],icon_id,object_id);
			mysql_query(gMysql, request);
			icon_id++;
		}
	}

	if(cache_is_valid(result, gMysql))
		cache_delete(result);
}

public reset_player_key_labels(playerid)
{
	new rows, fields;
	new request[512];
	new Cache:result;
	new icon_id, i;

	if(gPlayersID[playerid] <= 0)
	    return;
	    
    mysql_format(gMysql, request, sizeof(request), "SELECT icon_id FROM key_icon WHERE player_id=%d", gPlayersID[playerid]);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
		return;
	for(i = 0; i < rows; ++i)
	{
		icon_id = cache_get_field_content_int(i, "icon_id", gMysql);
		RemovePlayerMapIcon(playerid, icon_id);
	}
	if(cache_is_valid(result, gMysql))
		cache_delete(result);

    mysql_format(gMysql, request, sizeof(request), "DELETE FROM key_icon WHERE player_id=%d", gPlayersID[playerid]);
	mysql_query(gMysql, request);
}

//обновить метки авто на карте игроков (у которых ключ к этим авто)
public update_key_cars(car_type[])
{
	new rows, fields;
	new request[512];
	new Cache:result;
	new playerid, player_id, icon_id, obj_id;
	new Float:x, Float:y, Float:z;
	new i, j;

    mysql_format(gMysql, request, sizeof(request), "SELECT a.player_id,a.icon_id,b.obj_id FROM key_icon a INNER JOIN (objects b,things c,thing_type d) ON (a.object_id=b.id AND b.thing_id=c.id AND c.type_id=d.id) WHERE d.name=\"%s\"", car_type);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
		return;
	for(i = 0; i < rows; ++i)
	{
	    player_id = cache_get_field_content_int(i, "player_id", gMysql);
		icon_id = cache_get_field_content_int(i, "icon_id", gMysql);
		obj_id = cache_get_field_content_int(i, "obj_id", gMysql);
		for(j = 0; j < MAX_PLAYERS; ++j)
		{
		    if(gPlayersID[j] == player_id)
		    {
		        playerid = j;
		        break;
			}
		}
		if(j == MAX_PLAYERS) //если игрок уже вышел
		    continue;
		GetVehiclePos(obj_id, x, y, z);
		RemovePlayerMapIcon(playerid, icon_id);
		SetPlayerMapIcon(playerid, icon_id, x, y, z, 55, 0xFFFFFFFF, MAPICON_GLOBAL); //метка авто
	}
	if(cache_is_valid(result, gMysql))
		cache_delete(result);
}

public set_admin_level(playerid, level)
{
	new request[256];

	if(playerid < 0 || playerid > MAX_PLAYERS)
	    return;
	    
	if(gPlayersID[playerid] <= 0)
	    return;

    mysql_format(gMysql, request, sizeof(request), "UPDATE players SET admin=%d WHERE id=%d", level, gPlayersID[playerid]);
	mysql_query(gMysql, request);
}

public get_admin_level(playerid)
{
	new rows, fields;
	new request[128];
	new Cache:result;

	if(gPlayersID[playerid] <= 0)
	{
		gAdminLevel[playerid] = 0;
	    return;
	}
	    
    mysql_format(gMysql, request, sizeof(request), "SELECT admin FROM players WHERE id=%d LIMIT 1", gPlayersID[playerid]);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
	{
        gAdminLevel[playerid] = 0;
        return;
	}
	gAdminLevel[playerid] = cache_get_field_content_int(0, "admin", gMysql);
	if(cache_is_valid(result, gMysql))
		cache_delete(result);
}

public get_the_same_players(playerid, list[], list_size)
{
	new rows, fields;
	new request[512];
	new Cache:result;
	new i, ln, ban;
	new name[64];

	if(gPlayersID[playerid] <= 0)
	    return;

    mysql_format(gMysql, request, sizeof(request), "SELECT a.name,a.ban FROM players a INNER JOIN players b WHERE (a.last_ip_mask=b.last_ip_mask OR a.reg_ip_mask=b.last_ip_mask OR a.last_ip_mask=b.reg_ip_mask OR a.reg_ip_mask=b.reg_ip_mask) AND a.passwd=b.passwd AND a.id!=b.id AND b.id=%d ORDER BY a.last_date DESC LIMIT 10", gPlayersID[playerid]);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
	{
        format(list, list_size, "-");
        return;
	}
	strdel(list, 0, list_size);
	for(i = 0, ln = 3; i < rows; ++i)
	{
		cache_get_field_content(i, "name", name, gMysql);
		ban = cache_get_field_content_int(i, "ban", gMysql);
		strcat(list, name, list_size);
		if(strlen(list) > 170)
		{
		    strcat(list, ",...", list_size);
		    break;
		}
		if(ban > 0)
		{
		    strcat(list, "(ban)", list_size);
		}
		if(i < (rows-1))
		{
		    strcat(list, ",", list_size);
		}
		if((strlen(list) > 45 && (ln == 3)) ||
		   (strlen(list) > 90 && (ln == 2)) ||
		   (strlen(list) > 135 && (ln == 1)) ||
		   (strlen(list) > 180 && (ln == 0)))
		{
		    strcat(list, " ", list_size);
		    ln--;
		}
	}
	if(cache_is_valid(result, gMysql))
		cache_delete(result);
}

public get_the_same_players_ip(playerid, list[], list_size)
{
	new rows, fields;
	new request[512];
	new Cache:result;
	new i, ln, ban;
	new name[64];

	if(gPlayersID[playerid] <= 0)
	    return;

    mysql_format(gMysql, request, sizeof(request), "SELECT a.name,a.ban FROM players a INNER JOIN players b WHERE (a.last_ip_mask=b.last_ip_mask OR a.reg_ip_mask=b.last_ip_mask OR a.last_ip_mask=b.reg_ip_mask OR a.reg_ip_mask=b.reg_ip_mask) AND a.id!=b.id AND b.id=%d ORDER BY a.last_date DESC LIMIT 20", gPlayersID[playerid]);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
	{
        format(list, list_size, "-");
        return;
	}
	strdel(list, 0, list_size);
	for(i = 0, ln = 3; i < rows; ++i)
	{
		cache_get_field_content(i, "name", name, gMysql);
		ban = cache_get_field_content_int(i, "ban", gMysql);
		strcat(list, name, list_size);
		if(strlen(list) > 170)
		{
		    strcat(list, ",...", list_size);
		    break;
		}
		if(ban > 0)
		{
		    strcat(list, "(ban)", list_size);
		}
		if(i < (rows-1))
		{
		    strcat(list, ",", list_size);
		}
		if((strlen(list) > 45 && (ln == 3)) ||
		   (strlen(list) > 90 && (ln == 2)) ||
		   (strlen(list) > 135 && (ln == 1)) ||
		   (strlen(list) > 180 && (ln == 0)))
		{
		    strcat(list, " ", list_size);
		    ln--;
		}
	}
	if(cache_is_valid(result, gMysql))
		cache_delete(result);
}

public bool:is_player_near_objects(playerid, object_names[], Float:radius)
{
	new i, rows, fields;
	new request[1536];
	new Cache:result;
	new Float:x, Float:y, Float:z, Float:vector;
	
	if(gPlayersID[playerid] <= 0)
	    return false;

	GetPlayerPos(playerid, x, y, z);
	vector = VectorSize(x, y, z);

    mysql_format(gMysql, request, sizeof(request), "SELECT placex,placey,placez FROM objects a INNER JOIN things b ON a.thing_id=b.id WHERE b.name in (%s) AND ABS(a.vector-%f)<%f",object_names,vector,radius);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
        return false;
	for(i = 0; i < rows; ++i)
	{
		x = cache_get_field_content_int(i, "placex", gMysql);
		y = cache_get_field_content_int(i, "placey", gMysql);
		z = cache_get_field_content_int(i, "placez", gMysql);
		if(IsPlayerInRangeOfPoint(playerid, radius, x, y, z))
		{
			if(cache_is_valid(result, gMysql))
				cache_delete(result);
		    return true;
		}
	}
	
	if(cache_is_valid(result, gMysql))
		cache_delete(result);

	return false;
}

public mark_players_near_fire()
{
	new i, playerid, rows, fields;
	new request[512];
	new Cache:result;
	new Float:x, Float:y, Float:z;
	new near_fire[MAX_PLAYERS];

	for(playerid = 0; playerid < MAX_PLAYERS; ++playerid)
	{
		near_fire[playerid] = 0;
	}

    mysql_format(gMysql, request, sizeof(request), "SELECT placex,placey,placez FROM objects a INNER JOIN things b ON a.thing_id=b.id WHERE b.name in (\"FIRE_OBJECT\",\"NODJA_OBJECT\")");
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows > 0)
	{
		for(i = 0; i < rows; ++i)
		{
			x = cache_get_field_content_int(i, "placex", gMysql);
			y = cache_get_field_content_int(i, "placey", gMysql);
			z = cache_get_field_content_int(i, "placez", gMysql);
			for(playerid = 0; playerid < MAX_PLAYERS; ++playerid)
			{
				if(IsPlayerSpawned(playerid) && IsPlayerInRangeOfPoint(playerid, 5.0, x, y, z))
				{
				    near_fire[playerid] = 1;
				}
			}
		}
	}
	
	for(playerid = 0; playerid < MAX_PLAYERS; ++playerid)
	{
	    gPlayersNearFire[playerid] = near_fire[playerid];
	}

	if(cache_is_valid(result, gMysql))
		cache_delete(result);
}

#if defined LOAD_DEBUG
public update_player_position(playerid)
{
	new request[256];
	new Float:x, Float:y, Float:z, Float:ang;
	
	x = -1420.64;
	y = -2897.94;
	z = 48.0911;
	ang = 38.8824;

    mysql_format(gMysql, request, sizeof(request), "UPDATE characters SET placex=%f,placey=%f,placez=%f,angle=%f WHERE player_id=%d LIMIT 1", x, y, z, ang, gPlayersID[playerid]);
	mysql_query(gMysql, request);
}

public add_spawn_place(playerid)
{
	new request[128];
	new Float:x, Float:y, Float:z, Float:ang;

	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, ang);

    mysql_format(gMysql, request, sizeof(request), "INSERT INTO spawns(placex, placey, placez, angle) VALUES(%f,%f,%f,%f)", x, y, z, ang);
	mysql_query(gMysql, request);
}

public add_spawn_place_zombie(playerid)
{
	new request[256];
	new Float:x, Float:y, Float:z, Float:ang;

	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, ang);

    mysql_format(gMysql, request, sizeof(request), "INSERT INTO spawns(placex,placey,placez,angle,is_zombie) VALUES(%f,%f,%f,%f,1)", x, y, z, ang);
	mysql_query(gMysql, request);
}

//добавить новую точку появления вещи
public add_dot_place(playerid, type)
{
	new rows, fields, id;
	new request[128];
	new Float:x, Float:y, Float:z;
	new Cache:result;

	GetPlayerPos(playerid, x, y, z);

    mysql_format(gMysql, request, sizeof(request), "INSERT INTO object_dot(placex, placey, placez) values(%f,%f,%f)", x, y, z);
	mysql_query(gMysql, request);
	
	if(type == 0)
		return;

    mysql_format(gMysql, request, sizeof(request), "SELECT id FROM object_dot ORDER BY id DESC LIMIT 1");
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
	    return;
	id = cache_get_field_content_int(0, "id", gMysql);
	if(cache_is_valid(result, gMysql))
		cache_delete(result);

    mysql_format(gMysql, request, sizeof(request), "INSERT INTO dot_type(dot_id, type_id) values(%d,%d)", id, type);
	mysql_query(gMysql, request);
}

//добавить тип вещи к последней созданной точке
public upd_dot_place(type)
{
	new rows, fields, id;
	new request[128];
	new Cache:result;

    mysql_format(gMysql, request, sizeof(request), "SELECT id FROM object_dot ORDER BY id DESC LIMIT 1");
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
	    return;
	id = cache_get_field_content_int(0, "id", gMysql);
	if(cache_is_valid(result, gMysql))
		cache_delete(result);

	if(type < 0)
	{
	    //удаляем тип
	    mysql_format(gMysql, request, sizeof(request), "DELETE FROM dot_type WHERE dot_id=%d AND type_id=%d LIMIT 1", id, -type);
		mysql_query(gMysql, request);
	}
	else
	{
	    //добавляем тип
	    mysql_format(gMysql, request, sizeof(request), "INSERT INTO dot_type(dot_id, type_id) VALUES(%d,%d)", id, type);
		mysql_query(gMysql, request);
	}
}

//добавить объект в игровой мир
public add_objects_to_gm(type, dup)
{
	new request[128];

	if(type < 0 || dup <= 0)
	{
	    return;
	}

	for(new i = 0; i < dup; ++i)
	{
	    //добавляем объекты
	    mysql_format(gMysql, request, sizeof(request), "INSERT INTO objects SET thing_id=%d,next_id=%d,value=(SELECT def_value FROM things WHERE id=%d LIMIT 1)", type,type,type);
		mysql_query(gMysql, request);
	}
}

public add_car_place(playerid)
{
	new rows, fields, id;
	new request[128];
	new Float:x, Float:y, Float:z;
	new Cache:result;

	GetPlayerPos(playerid, x, y, z);

    mysql_format(gMysql, request, sizeof(request), "INSERT INTO object_dot(placex, placey, placez) values(%f,%f,%f)", x, y, z);
	mysql_query(gMysql, request);

    mysql_format(gMysql, request, sizeof(request), "SELECT id FROM object_dot ORDER BY id DESC LIMIT 1");
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
	    return;
	id = cache_get_field_content_int(0, "id", gMysql);
	if(cache_is_valid(result, gMysql))
		cache_delete(result);

    mysql_format(gMysql, request, sizeof(request), "INSERT INTO dot_type(dot_id, type_id) values(%d,11)", id);
	mysql_query(gMysql, request);
}

public go_to_thing_place(playerid, thing_type[])
{
	new rows, fields;
	new request[512];
	new Float:x, Float:y, Float:z;
	new Cache:result;
	static count;
	new vehicleflag, id;

	vehicleflag = 0;

	if(strcmp(thing_type, "SOME_VEHICLE") == 0 ||
	   strcmp(thing_type, "SOME_BUS_VEH") == 0 ||
	   strcmp(thing_type, "SOME_TANK") == 0 ||
	   strcmp(thing_type, "SOME_HELICOPTER_TYPE") == 0 ||
	   strcmp(thing_type, "SOME_BOAT_TYPE") == 0)
	{
	    count++;
	    vehicleflag = 1;
	}

	if(vehicleflag)
	    mysql_format(gMysql, request, sizeof(request), "SELECT a.id,a.placex,a.placey,a.placez FROM objects a INNER JOIN (things b, thing_type c) ON (a.thing_id=b.id AND b.type_id=c.id) WHERE c.name='%s' ORDER BY a.id", thing_type);
    else
	    mysql_format(gMysql, request, sizeof(request), "SELECT a.id,a.placex,a.placey,a.placez FROM objects a INNER JOIN (things b, thing_type c) ON (a.thing_id=b.id AND b.type_id=c.id) WHERE c.name REGEXP '%s' AND a.placex IS NOT NULL ORDER BY a.view_time LIMIT 1", thing_type);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
	{
	    //format(request, sizeof(request), "%s", thing_type);
	    //SendClientMessage(playerid, 0xFFFF00FF, thing_type);//отладка!!!
	    //SendClientMessage(playerid, 0xFFFF00FF, "go_to_thing_place(): Request error!");//отладка!!!
	    return;
	}

	if(!vehicleflag)
	{
		x = cache_get_field_content_float(0, "placex", gMysql);
		y = cache_get_field_content_float(0, "placey", gMysql);
		z = cache_get_field_content_float(0, "placez", gMysql);
	}
	else
	{
	    if(count >= rows)
	        count = 0;
		x = cache_get_field_content_float(count, "placex", gMysql);
		y = cache_get_field_content_float(count, "placey", gMysql);
		z = cache_get_field_content_float(count, "placez", gMysql);
	}
	id = cache_get_field_content_int(0, "id", gMysql);
	if(cache_is_valid(result, gMysql))
		cache_delete(result);

    mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET view_time=NOW() WHERE id=%d", id);
	mysql_query(gMysql, request);

	SetPlayerPos(playerid, x+1, y+1, z+3);
}

public go_to_thing_place_name(playerid, thing_name[])
{
	new rows, fields;
	new request[512];
	new Float:x, Float:y, Float:z;
	new Cache:result;
	static count;

    mysql_format(gMysql, request, sizeof(request), "SELECT a.id,a.placex,a.placey,a.placez FROM objects a INNER JOIN things b ON a.thing_id=b.id WHERE b.name REGEXP '%s' AND a.placex IS NOT NULL ORDER BY a.is_dropped", thing_name);
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
	{
	    //format(request, sizeof(request), "%s", thing_name);
	    //SendClientMessage(playerid, 0xFFFF00FF, thing_name);//отладка!!!
	    //SendClientMessage(playerid, 0xFFFF00FF, "go_to_thing_place(): Request error!");//отладка!!!
	    return;
	}

    if(count >= rows)
        count = 0;
	x = cache_get_field_content_float(count, "placex", gMysql);
	y = cache_get_field_content_float(count, "placey", gMysql);
	z = cache_get_field_content_float(count, "placez", gMysql);
    count++;

	if(cache_is_valid(result, gMysql))
		cache_delete(result);
		
	SetPlayerPos(playerid, x, y, z+2);
}

public go_to_thing_place_height(playerid)
{
	new rows, fields, id;
	new request[512];
	new Float:x, Float:y, Float:z;
	new Float:Z_coord, Float:Alpha, Float:Beta;
	new Cache:result;
	static count;

    mysql_format(gMysql, request, sizeof(request), "SELECT a.id,a.placex,a.placey,a.placez FROM objects a INNER JOIN things b ON a.thing_id=b.id WHERE a.placex IS NOT NULL ORDER BY a.view_time");
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
	{
	    //SendClientMessage(playerid, 0xFFFF00FF, "go_to_thing_place_height(): Request error!");//отладка!!!
	    return;
	}

    if(count >= rows)
        count = 0;
	do {
		id = cache_get_field_content_int(count, "id", gMysql);
		x = cache_get_field_content_float(count, "placex", gMysql);
		y = cache_get_field_content_float(count, "placey", gMysql);
		z = cache_get_field_content_float(count, "placez", gMysql);
	    count++;
	    
	    MapAndreas_Valid_Z_Coordinate(x, y, z, Z_coord, Alpha, Beta);
	    if(z > (Z_coord+3) || z < -3)
	    {
			SetPlayerPos(playerid, x, y, z+1);

			if(cache_is_valid(result, gMysql))
				cache_delete(result);

		    mysql_format(gMysql, request, sizeof(request), "UPDATE objects SET view_time=NOW() WHERE id=%d", id);
			mysql_query(gMysql, request);

			return;
	    }

	}
	while(count < rows);


	if(cache_is_valid(result, gMysql))
		cache_delete(result);

	SetPlayerPos(playerid, x, y, z+2);
}

public get_spawn_place(playerid, bool:zombie)
{
	new rows, fields, id;
	new request[256];
	new Float:x, Float:y, Float:z, Float:ang;
	new Cache:result;

	if(gPlayersID[playerid] <= 0)
	    return;

	if(zombie)
    	mysql_format(gMysql, request, sizeof(request), "SELECT id,placex,placey,placez,angle FROM spawns WHERE is_zombie=1 ORDER BY last_time LIMIT 1");
	else
    	mysql_format(gMysql, request, sizeof(request), "SELECT id,placex,placey,placez,angle FROM spawns WHERE is_zombie=0 ORDER BY last_time LIMIT 1");
	result = mysql_query(gMysql, request);
	cache_get_data(rows, fields, gMysql);
	if(rows <= 0)
	    return;
	id = cache_get_field_content_int(0, "id", gMysql);
	x = cache_get_field_content_float(0, "placex", gMysql);
	y = cache_get_field_content_float(0, "placey", gMysql);
	if(zombie)
		MapAndreas_FindZ_For2DCoord_I(x, y, z);
	else
		z = cache_get_field_content_float(0, "placez", gMysql);
	ang = cache_get_field_content_float(0, "angle", gMysql);
	if(cache_is_valid(result, gMysql))
		cache_delete(result);

	if(!zombie)
		SetSpawnInfo(playerid, 0, 188, x, y, z, ang, 0, 0, 0, 0, 0, 0);
	
	strdel(request, 0, sizeof(request)-1);
	mysql_format(gMysql, request, sizeof(request), "UPDATE spawns SET last_time=NOW() WHERE id=%d", id);
	mysql_query(gMysql, request);
	
    mysql_format(gMysql, request, sizeof(request), "UPDATE characters SET placex=%f,placey=%f,placez=%f,angle=%f,cheater=0 WHERE player_id=%d LIMIT 1", x, y, z, ang, gPlayersID[playerid]);
	mysql_query(gMysql, request);
}

public SetPlayerSkinFix(playerid, skinid)
{
	new
	    Float:tmpPos[4],
		vehicleid = GetPlayerVehicleID(playerid),
		seatid = GetPlayerVehicleSeat(playerid);
	GetPlayerPos(playerid, tmpPos[0], tmpPos[1], tmpPos[2]);
	GetPlayerFacingAngle(playerid, tmpPos[3]);
	if(skinid < 0 || skinid > 299) return 0;
	if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_DUCK)
	{
	    SetPlayerPos(playerid, tmpPos[0], tmpPos[1], tmpPos[2]);
		SetPlayerFacingAngle(playerid, tmpPos[3]);
		TogglePlayerControllable(playerid, 1); // preventing any freeze - optional
		return SetPlayerSkin(playerid, skinid);
	}
	else if(IsPlayerInAnyVehicle(playerid))
	{
	    new
	        tmp;
	    RemovePlayerFromVehicle(playerid);
	    SetPlayerPos(playerid, tmpPos[0], tmpPos[1], tmpPos[2]);
		SetPlayerFacingAngle(playerid, tmpPos[3]);
		TogglePlayerControllable(playerid, 1); // preventing any freeze - important - because of doing animations of exiting vehicle
		tmp = SetPlayerSkin(playerid, skinid);
		PutPlayerInVehicle(playerid, vehicleid, (seatid == 128) ? 0 : seatid);
		return tmp;
	}
	else
	{
	    return SetPlayerSkin(playerid, skinid);
	}
}

//совственно обезглавить персонаж
public kill_character(playerid)
{
	if(!IsPlayerNPC(playerid))
	{
	    if(IsPlayerSpawned(playerid))
	    {
			destroy_sensors(playerid);
			SetPlayerHealth(playerid, -10.0);
		}
	}
	else
	{
	    if(!FCNPC_IsDead(playerid))
			FCNPC_Kill(playerid);
	}
}
