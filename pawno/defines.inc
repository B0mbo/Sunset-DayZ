#if defined _DEFINES_INC_
	#endinput
#endif

#define _DEFINES_INC_

//#define SAMP_ICQ
#define CHATTIME

//database connection data
#define HOST "mariadb"		//host name/addr
#define USER "user"		//user name
#define PASSWD "passwd"		//user password
#define DBNAME "dayz_old"	//database name

//#define DEBUG

#define MAX_NPC 30
//#define MAX_VEH 100

#define CHAT_HISTORY_LEN 15
#define CHAT_HISTORY_MESSAGE_LEN 144

#define TD_COUNT 17		//���������� �������������� ����������� ����
#define TD_COUNT_VEHICLE 9	//���������� ����������� ����������� ���������� (5)

#define TD_STATISTIC_DATA 17

#define TD_SPAWN_SHADOWS 2 //���������� ��������� ��������� ��������

#define SENSORS_NUMBER 6

#define VEHICLE_BUFFER_DATA_NUMBER 11

#define MAX_TURNS_OF_PREVIEW 4

#define MAX_INVENTORY_ON_GROUND 10
#define MAX_INVENTORY_ON_PLAYER 9
#define MAX_INVENTORY_ON_VEHICLE 12
#define MAX_INVENTORY_IN_BAG 16

#define INVENTORY_CELLS_PER_ROW 3 //����� �� �������
#define INVENTORY_CELLS_PER_COL 3 //����� �� �������

#define GROUND_CELLS_PER_ROW 5 //����� �� �������
#define GROUND_CELLS_PER_COL 2 //����� �� �������

#define VEHICLE_CELLS_PER_ROW 6 //����� �� �������
#define VEHICLE_CELLS_PER_COL 2 //����� �� �������

#define BACKPACK_LINE 4

#define AFK_TIMER_UPDATE 2000
#define INVENTORY_TIMER_UPDATE 400
#define SENSORS_TIMER_UPDATE 10100
#define SENSORS_TIMER_SAVE 30250
#define SENSORS_TIMER_VEHICLES 15100
#define VEHICLE_DATA_SHOW_CHECK 5050
#define UPDATE_WEAPON_AMMO_TIMER 5030 //����� ���������� ���������� �������� ����� ������� ��������
#define DOLG_SOUND_INTERVAL 600000
#define ZOMBIE_ATTACK_INTERVAL 510
#define DESTROY_BUG_INTERVAL 601100
#define ZONE_MARK_INTERVAL 5310
#define NEAR_FIRE_TIMER 10111

#define NON_CHEATERS_INTERVAL 5070 //������ �������� �� ���������

#define SERVER_TIME_INTERVAL 500 //�������� ���������� �����

#define UPDATE_CAR_LABELS_INTERVAL 60700 //������ ���������� ����� ���� �� �����

#define START_TEMP_VALUE 3660
#define MAX_TEMP_VALUE 4200
#define MIN_TEMP_VALUE 3200
#define START_HEALTH_VALUE 12000
#define MAX_HEALTH_VALUE 14000
#define START_HUNGER_VALUE 1000
#define MAX_HUNGER_VALUE 1200
#define START_THIRST_VALUE 1000
#define MAX_THIRST_VALUE 1200
#define START_WOUND_VALUE 0
#define MAX_WOUND_VALUE 1000 	   //max �������� ������� ��� ����� �������
#define MAX_WOUND_REAL_VALUE 14000 //max �������� ������ �������
#define FIRE_WOUND_VALUE 2000 //�������� ������� �� ����
#define EXTING_WOUND_VALUE 50

#define CELL_SIZE 65.0
#define CELL_SIZE_BAG 48.75

#define MENU_BORDER 10
#define CELL_BORDER 3
#define CELL_BORDER_BAG 2

#define INVENTORY_START_POSITION_X 190.0
#define INVENTORY_START_POSITION_Y 190.0

#define VEHICLE_START_POSITION_X  34.0 //���������� 32.0
#define VEHICLE_START_POSITION_Y 130.0 //���������� 150.0

#define MESSAGER_STRINGS_COUNT 9
#define MAX_MESSAGE_LEN 128 //������������ ����� ��������� ����� ������

#define MESSAGE_START_POSITION_CH_X  470.0
#define MESSAGE_START_POSITION_CH_Y  430.0

#define MESSAGE_START_POSITION_PL_X    8.0
#define MESSAGE_START_POSITION_PL_Y  320.0

#define SERVER_TIME_POSITION_X 570.0
#define SERVER_TIME_POSITION_Y 135.0

#define SPECTATE_START_POSITION_X 390
#define SPECTATE_START_POSITION_Y 150
#define PANEL_START_POSITION_X 100
#define PANEL_START_POSITION_Y 150

#define SPECTATE_FON_NUMBER 25
#define SPECTATE_DATA_NUMBER 25
#define ADMIN_PANEL_NUMBER 25

//0.3z defines:
#define WEAPON_BODY_PART_CHEST 3
#define WEAPON_BODY_PART_CROTCH 4
#define WEAPON_BODY_PART_LEFT_ARM 5
#define WEAPON_BODY_PART_RIGHT_ARM 6
#define WEAPON_BODY_PART_LEFT_LEG 7
#define WEAPON_BODY_PART_RIGHT_LEG 8
#define WEAPON_BODY_PART_HEAD 9

#define BULLET_HIT_TYPE_NONE            0
#define BULLET_HIT_TYPE_PLAYER          1
#define BULLET_HIT_TYPE_VEHICLE         2
#define BULLET_HIT_TYPE_OBJECT          3
#define BULLET_HIT_TYPE_PLAYER_OBJECT   4

#define CACHED_OBJECTS_COUNT 256 //���������� ���������� �������� ������ ������ ��� ������������� �����

#define OBJECT_DISTANCE 130.0
//#define STANDART_RANGE_VALUE 3.0 //������������ ��������� �� ����������� ��������

#define DROP_DISTANCE_FROM_PLAYER 1.5 //��������� �� �������������� �������

#define UNUSUAL_OBJECTS_COUNT 4 //���������� ��������������� ��������

// #define PREVIOUS_DOT_INDEX_CACHE_ZISE 2048 //������ ���� id ����� ��� ���������� ����� �����

#define CreateObject(%1,%2,%3,%4,%5,%6,%7,%8) CreateDynamicObject(%1, %2, %3, %4, %5, %6, %7, -1, -1, -1, %8, %8)
#define IsValidObject IsValidDynamicObject
#define DestroyObject DestroyDynamicObject
#define MoveObject MoveDynamicObject
