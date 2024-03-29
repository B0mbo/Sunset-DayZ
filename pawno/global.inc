#if defined _GLABAL_INC_
	#endinput
#endif

#define _GLOBAL_INC_

#include<a_samp>
#include"defines.inc"

enum {INVENTORY_AREA=0, VEHICLE_AREA, GROUND_AREA, BAG_AREA};
enum {FIRE_OBJECT=0, GAS_OBJECT, WATER_OBJECT, VEHICLE_OBJECT};

new gMysql;

new gChatHistory[CHAT_HISTORY_LEN][CHAT_HISTORY_MESSAGE_LEN];
new gHistoryIndex;
new gPrivateOut[MAX_PLAYERS]; //���� ���������� ��������� ��������� ���������
new gPrivateIn[MAX_PLAYERS]; //�� ���� �������� ��������� ��������� ���������

new gPlayerPasswordRequest[MAX_PLAYERS];
new gPlayerPasswordCheckCount[MAX_PLAYERS];
new gIsPlayerLogin[MAX_PLAYERS];

new gPlayersID[MAX_PLAYERS];
new gNPCCount;

new gCheatersList[MAX_PLAYERS];
new gPlayerCheaterLevel[MAX_PLAYERS];

new gPlayerDeathCount[MAX_PLAYERS][2];

new gPlayerLocated[MAX_PLAYERS];

new gPlayersNearFire[MAX_PLAYERS];

new gInventoryMenuShow[MAX_PLAYERS];
new gObjectsMenuShow[MAX_PLAYERS];
new gVehicleMenuShow[MAX_PLAYERS];
new gBagMenuShow[MAX_PLAYERS];

new gHideMapZone;

new Float:gRadius;

new Float:gNonCheaters[MAX_PLAYERS][3];

new gVehicleDataShow[MAX_PLAYERS];

new PlayerText:gTdInventory[MAX_PLAYERS][MAX_INVENTORY_ON_PLAYER][MAX_TURNS_OF_PREVIEW];//���������� ���� ���������
new PlayerText:gTdObject[MAX_PLAYERS][MAX_INVENTORY_ON_GROUND][MAX_TURNS_OF_PREVIEW]; 	//���������� ���� ��������
new PlayerText:gTdVehicle[MAX_PLAYERS][MAX_INVENTORY_ON_VEHICLE][MAX_TURNS_OF_PREVIEW];	//���������� ���� ����������
new PlayerText:gTdDataVehicle[MAX_PLAYERS][TD_COUNT_VEHICLE]; 	//���������� ������ ����������
new PlayerText:gStatisticData[MAX_PLAYERS][TD_STATISTIC_DATA];	//���������� ���������� ������
new PlayerText:gTdBag[MAX_PLAYERS][MAX_INVENTORY_IN_BAG][MAX_TURNS_OF_PREVIEW];    //���������� ����������� �������

new PlayerText:gTdMenu[MAX_PLAYERS][TD_COUNT]; 			//�������������� ���������� ����
new Text:gTdInvCells[MAX_INVENTORY_ON_PLAYER];
new Text:gTdVehCells[MAX_INVENTORY_ON_VEHICLE];
new Text:gTdBagCells[MAX_INVENTORY_IN_BAG];

new PlayerText:gSensors[MAX_PLAYERS][SENSORS_NUMBER];
new Text:gSmokescreen[3];

new Text:gSpectateFon[SPECTATE_FON_NUMBER]; //��� ������ ������ ��� ��������
new PlayerText:gSpectateData[MAX_PLAYERS][SPECTATE_DATA_NUMBER]; //������ ������ ��� ����������� � ���� ��� ��������
new Text:gAdminPanel[ADMIN_PANEL_NUMBER]; //������ ���������� ������

new gYourTime[MAX_PLAYERS][16]; //����� ������ � ����

new Text:gSpawnShadow[TD_SPAWN_SHADOWS]; //�������� ��������� ��������

new Text:gServerTime;
new gServerTimeString[32];
new Text:gTranslatorState;
new gTranslatorStateString[32];

new gAltWait[MAX_PLAYERS];
new gFullInvent[MAX_PLAYERS];

enum DECART_INT {n_X, n_Y, n_Z}
enum DECART_FLOAT{Float:f_X, Float:f_Y, Float:f_Z}
enum CRAFT_ITEM {
			db_id,  //id ������� � ���� ������
			tp_id,  //id ���� ������� �� ���� ������
			pr_id,  //prev_id ������
			object, //id ���� � �������� ��������
			inv_id, //id ���� �������, ������������� � ���������
			gnd_id, //id ���� �������, ������������� �� �����
			isrot[DECART_INT],		//��������� �� ������ �� �������� ���
			Float:deg[DECART_FLOAT],//���������� �������� ������� � ���������
			Float:zoom,				//������� ������� � ���������
			obj_rotatable,          //��������� ������ �� �����
			Float:rot[DECART_FLOAT],//���������� ��������
			Float:obj_height,       //������
			obj_owner,              //��������
			obj_auto,               //��������������� �������
			obj_inventory,          //��� ���� (����� �������� � ��������� ��� ���)
			obj_value,              //��������
			obj_coord[DECART_FLOAT]//���������� ���� (0, ���� ������� ��� � ���������)
}
enum CACHED_OBJECTS_DATA {
			db_id,	//id ������� � ���� ������
			Float:obj_coord[DECART_FLOAT]
}
enum CACHED_PLAYER_DATA {
			cached_player_pos[DECART_FLOAT], //���������� ������, ��� �������� ������� ���
			Float:cached_range //������ �������� ������������ ��������
}

new gInventoryItem[MAX_PLAYERS][MAX_INVENTORY_ON_PLAYER][CRAFT_ITEM];	//���������
new gGroundItem[MAX_PLAYERS][MAX_INVENTORY_ON_GROUND][CRAFT_ITEM];		//�� �����
new gVehicleItem[MAX_VEHICLES][MAX_INVENTORY_ON_VEHICLE][CRAFT_ITEM];	//� ������
new gBagItem[MAX_PLAYERS][MAX_INVENTORY_IN_BAG][CRAFT_ITEM];			//� �������

new gCachedItems[MAX_PLAYERS][CACHED_OBJECTS_COUNT][CRAFT_ITEM];	//��� �������� ��������, ������������ ���������� �������
new gCachedPlayers[MAX_PLAYERS][CACHED_PLAYER_DATA];				//������ ������, ��� �������� ������ ���

new gCachePlayerInventory[MAX_PLAYERS][MAX_INVENTORY_ON_PLAYER][CRAFT_ITEM];//��� ��� ����������
new gCacheBagInventory[MAX_PLAYERS][MAX_INVENTORY_IN_BAG][CRAFT_ITEM];		//��� ��� ����������

new gIndex[MAX_PLAYERS][MAX_INVENTORY_ON_PLAYER];	//�������� ��������� ��� ������ ������ ���������
new gRotate[MAX_PLAYERS][MAX_INVENTORY_ON_PLAYER];	//���������� ������ (������� ��� ���)
new gIndexObject[MAX_PLAYERS][MAX_INVENTORY_ON_GROUND];    //�������� ��������� ������� (���, ������� �����)
new gRotateObject[MAX_PLAYERS][MAX_INVENTORY_ON_GROUND];   //�������� ������ ������� (������� ��� ���)
new gIndexVehicle[MAX_PLAYERS][MAX_INVENTORY_ON_VEHICLE];  //�������� ��������� ������� (���, ������� �����)
new gRotateVehicle[MAX_PLAYERS][MAX_INVENTORY_ON_VEHICLE]; //�������� ������ ������� (������� ��� ���)
new gIndexBag[MAX_PLAYERS][MAX_INVENTORY_IN_BAG]; 	//�������� ��������� ������� (���, ������� �����)
new gRotateBag[MAX_PLAYERS][MAX_INVENTORY_IN_BAG]; 	//�������� ������ ������� (������� ��� ���)

new gVeh[MAX_VEHICLES][VEHICLE_BUFFER_DATA_NUMBER]; //�������� ������ � ������������ ��������� � ����
			   //0-id �������
			   //1-���-�� �����
			   //2-���������
			   //3-���������� �������
			   //4-�������� �� ���������
			   //5-������ �������
			   //6-����� ����
			   //7-�������� �� ����
			   //8-������ ������ ������������
			   //9-����� ������������
			   //10-������������ ����� ������������

new gBag[MAX_PLAYERS][2]; //�������� ������ � ������� ���������
				//0 - ���������� �����
				//1 - id ������� �������

new gTimerid; 				//������ ���������� ���������
new gTimeridUpdateSensors; 	//������ ���������� ��������
new gTimeridSaveSensors; 	//������ ���������� �������� � ������� ��������� � ��
new gTimeridUpdateVehicles; //������ ���������� ��������� ���� ����
new gTimerNonCheaters;		//������ ������ �������
new gTimeridAFK;	        //������ �������� �� ���
new gTimerCarLabels;        //������ ���������� ����� ���� �� �����
new gTimerServerTime;       //������ ���������� ����� �� ������
new gTimerDolgSound;        //������ ������� ����� �� ����
new gTimerZombieAttack;     //������ ����� �����
new gTimerDestroyBug;		//������ �������� �������� �� ���� ����
new gTimerPlayerZoneMark;   //������ ����� ������� � ���� 51
new gTimerMarkFire;         //������ ����������� �������, ������� ��������� ����� � �������

new gLoadPositionTimer;     //������ ��������� ����� ����� ������

new gAntiRadar[MAX_PLAYERS];//����� ���������� ���������� � ������
new PlayerText:gTdAntiCountDown[MAX_PLAYERS]; //����� �� ���������� ����������

new gUnmuteTimers[MAX_PLAYERS]; //������� ������ ��������

new gUnoccupiedUpdateTimer;	//������ ���������� ��������� ��������� ����
new gUpdateWeaponTimer; //������ ���������� ���������� ��������

//0.3.7
//new gActors[MAX_ACTORS]; //id ���

new gUnoccupiedVehData[MAX_VEHICLES]; //�������� "�������" ����

new gWeaponUpdate[MAX_PLAYERS]; //�������� �������, ��� ������� ��������� ���������� ���������� ��������
new gIndexCharacterWeapon[MAX_PLAYERS]; //��������� ��������� ������ � �������
new gPlayerWeapon[MAX_PLAYERS][4]; //������:
				//0 - id �������-������
				//1 - ���������� ���������� ��������
				//2 - weaponid (������������� id ������, ��� ��������)
				//3 - ��� �������� (�������, ���������)

new gGunMode[MAX_PLAYERS];
new gTemperature[MAX_PLAYERS];
new gHealth[MAX_PLAYERS];
new gHunger[MAX_PLAYERS];
new gThirst[MAX_PLAYERS];
new gWound[MAX_PLAYERS];
new gKiller[MAX_PLAYERS];
new gScores[MAX_PLAYERS];

new Text:gMessage[2];

new Text:gMessagerTD[MESSAGER_STRINGS_COUNT][4];
new gMessagerColors[MESSAGER_STRINGS_COUNT][4];
new Float:gMessagerSize[MESSAGER_STRINGS_COUNT][4];
new gMessagerString0[MAX_MESSAGE_LEN];
new gMessagerString1[MAX_MESSAGE_LEN], gMessagerString1_1[MAX_MESSAGE_LEN], gMessagerString1_2[MAX_MESSAGE_LEN], gMessagerString1_3[MAX_MESSAGE_LEN];
new gMessagerString2[MAX_MESSAGE_LEN], gMessagerString2_1[MAX_MESSAGE_LEN], gMessagerString2_2[MAX_MESSAGE_LEN], gMessagerString2_3[MAX_MESSAGE_LEN];
new gMessagerString3[MAX_MESSAGE_LEN], gMessagerString3_1[MAX_MESSAGE_LEN], gMessagerString3_2[MAX_MESSAGE_LEN], gMessagerString3_3[MAX_MESSAGE_LEN];
new gMessagerString4[MAX_MESSAGE_LEN], gMessagerString4_1[MAX_MESSAGE_LEN], gMessagerString4_2[MAX_MESSAGE_LEN], gMessagerString4_3[MAX_MESSAGE_LEN];
new gMessagerString5[MAX_MESSAGE_LEN], gMessagerString5_1[MAX_MESSAGE_LEN], gMessagerString5_2[MAX_MESSAGE_LEN], gMessagerString5_3[MAX_MESSAGE_LEN];
new gMessagerString6[MAX_MESSAGE_LEN], gMessagerString6_1[MAX_MESSAGE_LEN], gMessagerString6_2[MAX_MESSAGE_LEN], gMessagerString6_3[MAX_MESSAGE_LEN];
new gMessagerString7[MAX_MESSAGE_LEN], gMessagerString7_1[MAX_MESSAGE_LEN], gMessagerString7_2[MAX_MESSAGE_LEN], gMessagerString7_3[MAX_MESSAGE_LEN];
new gMessagerString8[MAX_MESSAGE_LEN], gMessagerString8_1[MAX_MESSAGE_LEN], gMessagerString8_2[MAX_MESSAGE_LEN], gMessagerString8_3[MAX_MESSAGE_LEN];

new gAntiDebug; //���� ������� ��������

new gMaxAnticheat; //���������� ���������

new gAdminLevel[MAX_PLAYERS]; //������ ���������������

new gUnusualObject[UNUSUAL_OBJECTS_COUNT]; //id ������������� ��������

new gTickCnt; //����� ������� ��� ��������

new gPsp[MAX_PLAYERS][MAX_PLAYERS]; //������ � ���, ��� �� ��� ������

new Float:gPlayerPlacesXYZ[MAX_PLAYERS][11]; //������ ���� ������� ������ ���� ������ ������
new gPlayerPlaces[MAX_PLAYERS]; //�������� ���� - ����� ���������� ���������� �����

new gMute[MAX_PLAYERS]; //������� ���� ��� ������

new gTranslate;
new gChatTime;
new gSinhro[MAX_PLAYERS];
new gShowSecond[MAX_PLAYERS]; //���� ��� ������ �������� (��� �������)
new gPlayerLand[MAX_PLAYERS][4]; //����������� ������ ������� ������
new gPlayerLang[MAX_PLAYERS][4]; //���� ������� ������
new gPlayerCountry[MAX_PLAYERS][64]; //������ ������� ������
new gPlayerCity[MAX_PLAYERS][64]; //����� ������� ������
new gPlayerLangSecond[MAX_PLAYERS][4]; //���� ��� �������
new gAllLangs[31][4]={"en","ru","es","ro","pt","tr","pl","de","uk","cs","fr","it","bg","sk","lt","hr","lv","sr","sq","hu","az","be","ca","da","et","fi","mk","nl","no","sl","sv"};
new gLangsNumber;
new gPlayerColorID[MAX_PLAYERS];
new gColor;
new gPlayerColors[200] = {
0x70524DFF,0xC715FFFF,0x111493FF,0xDC143CFF,0xFF8C13FF,0x6495EDFF,0xf0e68cFF,0x20B2AAFF,
0xF4A460FF,0xEE82EEFF,0xFFD720FF,0x8b4513FF,0x4949A0FF,0x148b8bFF,0x14ff7fFF,0x556b2fFF,
0x0FD9FAFF,0x10DC29FF,0x534081FF,0x0495CDFF,0xEF6CE8FF,0xBD34DAFF,0x247C1BFF,0x0C8E5DFF,
0x635B03FF,0xCB7ED3FF,0x65ADEBFF,0x5C1ACCFF,0xF2F853FF,0x11F891FF,0x7B39AAFF,0x53EB10FF,
0x54137DFF,0x275222FF,0xF09F5BFF,0x3D0A4FFF,0x22F767FF,0xD63034FF,0x9A6980FF,0xDFB935FF,
0x3793FAFF,0x90239DFF,0xE9AB2FFF,0xAF2FF3FF,0x057F94FF,0xB98519FF,0x388EEAFF,0x778899FF,
0xA55043FF,0x0DE018FF,0x93AB1CFF,0x95BAF0FF,0x369976FF,0x18F71FFF,0x4B8987FF,0x491B9EFF,
0x829DC7FF,0xBCE635FF,0xCEA6DFFF,0x20D4ADFF,0x2D74FDFF,0x3C1C0DFF,0x12D6D4FF,0x48C000FF,
0x2A51E2FF,0xE3AC12FF,0xFC42A8FF,0x2FC827FF,0x1A30BFFF,0xB740C2FF,0x42ACF5FF,0x2FD9DEFF,
0xFAFB71FF,0x05D1CDFF,0xC471BDFF,0x94436EFF,0xC1F7ECFF,0xCE79EEFF,0xBD1EF2FF,0x93B7E4FF,
0x3214AAFF,0x184D3BFF,0xAE4B99FF,0x7E49D7FF,0x4C436EFF,0xFA24CCFF,0xCE76BEFF,0xA04E0AFF,
0x9F945CFF,0xDCDE3DFF,0x10C9C5FF,0x70524DFF,0x0BE472FF,0x8A2CD7FF,0x6152C2FF,0xCF72A9FF,
0xE59338FF,0xEEDC2DFF,0xD8C762FF,0xD8C762FF,0x22DD22FF,0xC715FFFF,0x20B2AAFF,0xDC143CFF,
0x6495EDFF,0xf0e68cFF,0x778899FF,0xFF1493FF,0xF4A460FF,0xEE82EEFF,0xFFD720FF,0x8b4513FF,
0x4949A0FF,0x148b8bFF,0x14ff7fFF,0x556b2fFF,0x0FD9FAFF,0x10DC29FF,0x534081FF,0x0495CDFF,
0xEF6CE8FF,0xBD34DAFF,0x247C1BFF,0x0C8E5DFF,0x635B03FF,0xCB7ED3FF,0x65ADEBFF,0x5C1ACCFF,
0xF2F853FF,0x11F891FF,0x7B39AAFF,0x53EB10FF,0x54137DFF,0x275222FF,0xF09F5BFF,0x3D0A4FFF,
0x22F767FF,0xD63034FF,0x9A6980FF,0xDFB935FF,0x3793FAFF,0x90239DFF,0xE9AB2FFF,0xAF2FF3FF,
0x057F94FF,0xB98519FF,0x388EEAFF,0x028151FF,0xA55043FF,0x0DE018FF,0x93AB1CFF,0x95BAF0FF,
0x369976FF,0x18F71FFF,0x4B8987FF,0x491B9EFF,0x829DC7FF,0xBCE635FF,0xCEA6DFFF,0x20D4ADFF,
0x2D74FDFF,0x3C1C0DFF,0x12D6D4FF,0x48C000FF,0x2A51E2FF,0xE3AC12FF,0xFC42A8FF,0x2FC827FF,
0x1A30BFFF,0xB740C2FF,0x42ACF5FF,0x2FD9DEFF,0xFAFB71FF,0x05D1CDFF,0xC471BDFF,0x94436EFF,
0xC1F7ECFF,0xCE79EEFF,0xBD1EF2FF,0x93B7E4FF,0x3214AAFF,0x184D3BFF,0xAE4B99FF,0x7E49D7FF,
0x4C436EFF,0xFA24CCFF,0xCE76BEFF,0xA04E0AFF,0x9F945CFF,0xDCDE3DFF,0x10C9C5FF,0x028151FF,
0x0BE472FF,0x8A2CD7FF,0x6152C2FF,0xCF72A9FF,0xE59338FF,0xEEDC2DFF,0xD8C762FF,0xD8C762FF
};

new Float:gStandartRangeValue;

new gAFK[MAX_PLAYERS];
new gAFK_update[MAX_PLAYERS];

new gPlayerMarker[MAX_PLAYERS]; //����� ������� � ���� 51
new Text3D:gMarkerText[MAX_PLAYERS]; //������� �������

// new gPreviousDotID[PREVIOUS_DOT_INDEX_CACHE_ZISE];


#pragma unused gIndex
#pragma unused gKiller
#pragma unused gScores
#pragma unused gTdObject
#pragma unused gLangsNumber
#pragma unused gIndexObject
#pragma unused gIndexVehicle
#pragma unused gTdDataVehicle
#pragma unused gVehicleDataShow
#pragma unused gVehicleMenuShow
#pragma unused gUpdateWeaponTimer
#pragma unused gInventoryMenuShow
#pragma unused gPlayerCheaterLevel
#pragma unused gTimeridUpdateSensors
#pragma unused gTimeridUpdateVehicles
#pragma unused gTranslatorStateString
#pragma unused gPlayerPasswordCheckCount
#pragma unused gPlayerPasswordRequest
#pragma unused gUnoccupiedUpdateTimer
#pragma unused gIndexCharacterWeapon
#pragma unused gCachePlayerInventory
#pragma unused gTimerPlayerZoneMark
#pragma unused gStandartRangeValue
#pragma unused gTimeridSaveSensors
#pragma unused gUnoccupiedVehData
#pragma unused gTimerZombieAttack
#pragma unused gLoadPositionTimer
#pragma unused gMessagerString1_1
#pragma unused gMessagerString2_1
#pragma unused gMessagerString3_1
#pragma unused gMessagerString4_1
#pragma unused gMessagerString5_1
#pragma unused gMessagerString6_1
#pragma unused gMessagerString7_1
#pragma unused gMessagerString8_1
#pragma unused gMessagerString1_2
#pragma unused gMessagerString2_2
#pragma unused gMessagerString3_2
#pragma unused gMessagerString4_2
#pragma unused gMessagerString5_2
#pragma unused gMessagerString6_2
#pragma unused gMessagerString7_2
#pragma unused gMessagerString8_2
#pragma unused gMessagerString1_3
#pragma unused gMessagerString2_3
#pragma unused gMessagerString3_3
#pragma unused gMessagerString4_3
#pragma unused gMessagerString5_3
#pragma unused gMessagerString6_3
#pragma unused gMessagerString7_3
#pragma unused gMessagerString8_3
#pragma unused gCacheBagInventory
#pragma unused gPlayerDeathCount
#pragma unused gPlayerLangSecond
#pragma unused gTimerNonCheaters
#pragma unused gServerTimeString
#pragma unused gPlayersNearFire
#pragma unused gTimerDestroyBug
#pragma unused gTimerServerTime
#pragma unused gObjectsMenuShow
#pragma unused gPlayerPlacesXYZ
#pragma unused gMessagerString0
#pragma unused gMessagerString1
#pragma unused gMessagerString2
#pragma unused gMessagerString3
#pragma unused gMessagerString4
#pragma unused gMessagerString5
#pragma unused gMessagerString6
#pragma unused gMessagerString7
#pragma unused gMessagerString8
#pragma unused gTranslatorState
#pragma unused gTimerDolgSound
#pragma unused gTimerCarLabels
#pragma unused gMessagerColors
//#pragma unused gPreviousDotID
#pragma unused gPlayerLocated
#pragma unused gIsPlayerLogin
#pragma unused gPlayerColorID
#pragma unused gUnusualObject
#pragma unused gStatisticData
#pragma unused gRotateVehicle
#pragma unused gPlayerCountry
#pragma unused gTimerMarkFire
#pragma unused gInventoryItem
#pragma unused gCachedPlayers
#pragma unused gHistoryIndex
#pragma unused gUnmuteTimers
#pragma unused gMessagerSize
#pragma unused gPlayerPlaces
#pragma unused gCheatersList
#pragma unused gMaxAnticheat
#pragma unused gRotateObject
#pragma unused gWeaponUpdate
#pragma unused gPlayerColors
#pragma unused gPlayerWeapon
#pragma unused gSpectateData
#pragma unused gPlayerMarker
#pragma unused gCachedItems
#pragma unused gSpectateFon
#pragma unused gTemperature
#pragma unused gBagMenuShow
#pragma unused gNonCheaters
#pragma unused gSmokescreen
#pragma unused gTdInventory
#pragma unused gHideMapZone
#pragma unused gSpawnShadow
#pragma unused gChatHistory
#pragma unused gVehicleItem
#pragma unused gMarkerText
#pragma unused gAdminPanel
#pragma unused gPlayerCity
#pragma unused gServerTime
#pragma unused gMessagerTD
#pragma unused gTimeridAFK
#pragma unused gAdminLevel
#pragma unused gPlayerLang
#pragma unused gAFK_update
#pragma unused gPlayerLand
#pragma unused gShowSecond
#pragma unused gTdInvCells
#pragma unused gTdVehCells
#pragma unused gTdBagCells
#pragma unused gGroundItem
#pragma unused gPrivateOut
#pragma unused gFullInvent
#pragma unused gPrivateIn
#pragma unused gAntiDebug
#pragma unused gTdVehicle
#pragma unused gTranslate
#pragma unused gRotateBag
#pragma unused gPlayersID
#pragma unused gAntiRadar
#pragma unused gNPCCount
#pragma unused gYourTime
#pragma unused gAllLangs
#pragma unused gIndexBag
#pragma unused gChatTime
#pragma unused gAllLangs
#pragma unused gAltWait
#pragma unused gGunMode
#pragma unused gMessage
#pragma unused gSensors
#pragma unused gTimerid
#pragma unused gTickCnt
#pragma unused gBagItem
#pragma unused gRotate
#pragma unused gSinhro
#pragma unused gTdMenu
#pragma unused gHealth
#pragma unused gHunger
#pragma unused gThirst
#pragma unused gRadius
#pragma unused gColor
#pragma unused gMysql
#pragma unused gWound
#pragma unused gTdBag
#pragma unused gMute
#pragma unused gBag
#pragma unused gPsp
#pragma unused gAFK
#pragma unused gVeh
