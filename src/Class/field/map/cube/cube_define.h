#ifndef CUBE_DEFINE
#define CUBE_DEFINE
//movedefine=======================================================================
const unsigned char M_RIGHT=1<<0;
const unsigned char M_UP   =1<<1;
const unsigned char M_FRONT=1<<2;

const unsigned char M_LEFT =1<<3;
const unsigned char M_DOWN =1<<4;
const unsigned char M_BACK =1<<5;

const unsigned char M_STANDABLE =1<<6;
const unsigned char M_LIFTABLE =1<<7;

const unsigned char M_EX_NOT_RIGHT=1<<0;
const unsigned char M_EX_NOT_UP   =1<<1;
const unsigned char M_EX_NOT_FRONT=1<<2;

const unsigned char M_EX_NOT_LEFT =1<<3;
const unsigned char M_EX_NOT_DOWN =1<<4;
const unsigned char M_EX_NOT_BACK =1<<5;

const unsigned char M_EX_DOWN_STANDABLE=1<<6;
const unsigned char M_EX_NOT_ENTER=1<<7;
//cubedefine====================================================================================
const int C_OUT_OF_EDGE=-1;
const int C_STATIC_CUBE=0;
const int C_NULL=0;
//cube type
const int C_CUBE=10000;
const int C_BASIC_CUBE=10000;
const int C_BASIC=10001;
const int C_DARK=10002;
const int C_RED_CORE=10003;
const int C_WHITE_BRICK=10004;
//============================================================================================
const int C_BUILDING=20000;
const int C_BASIC_BUILDING=20001;
const int C_BASE=20002;
const int C_ELEVATOR=20003;
const int C_ONE_WAY=20004;

const int C_UNFINISHED_BUILDING=25001;
//============================================================================================
const int C_CREATURE=30000;
const int C_BASIC_CREATURE=30001;
const int C_CUBE_WORKER=30002;
#endif
