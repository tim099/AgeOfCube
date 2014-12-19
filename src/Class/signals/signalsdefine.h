#ifndef SIGNALS
#define SIGNALS
//define signal


//===================================================================================
//null type
const int T_NULL=0;
const int S_NULL=0;
//===================================================================================
const int BUTTON_SIGNAL=1000;
const int BUTTON_GROUP_SIGNAL=1000;

//===================================================================================
const int FIELD_SIGNAL=2000;
const int T_FIELD_BUILDING=2000;
const int S_BUILD_UNFINISHED=2000;
const int S_BUILD=2001;
const int S_CREAT_CUBE=2002;
const int S_DESTRUCT=2003;
const int T_MODE_SIGNAL=2100;
const int S_DP_RECRUIT_INFO=2101;
const int S_MODE_RECRUIT=2102;
const int S_MODE_DP=2103;
//===================================================================================
//Stage signal type
const int STAGE_SIGNAL=3000;
const int T_STAGE_MENU=3000;

//--------------------------------------------------------------------------------
const int T_STAGE_CREAT_MAP=3100;//creat map stage
const int S_SAVE_MAP= 3101;
const int S_LOAD_MAP= 3102;
//--------------------------------------------------------------------------------
const int T_STAGE_LOAD_MAP=3200;//creat map stage
const int S_SELECTED_MAP_NAME=3201;//creat map stage
const int S_DELETE_MAP_NAME=3203;//creat map stage
const int S_S_L_PREV =3204;
const int S_S_L_NEXT =3205;


//===================================================================================
//Game signal type , >10000
const int GAME_SIGNAL=10000;
const int T_SWITCH_STAGE=10000;
//switch stage
const int S_START=10000;
const int S_BACK=10001;
const int S_OPTION=10002;
const int S_CREAT_MAP=10003;
const int S_MENU=10004;
const int S_PREPARE_SAVE_MAP=10005;
const int S_PREPARE_LOAD_MAP=10006;
//------------------------------------------------------
//Game operation type
const int T_GAME_OPERATION=10100;
//operation
const int S_LOAD_GAME=10100;
const int S_SAVE_GAME=10101;
const int S_LOAD_MAP_NAME=10102;
const int S_SAVE_MAP_NAME=10103;
//===================================================================================



#endif
