/*
* SPIDefLib.h 更新履歴
* 2017/1/5
*   Ver1.0.0    一次完成
* 2017/3/15
* 	Ver1.0.1	enumを#defineに置き換え
* 2017/8/18
* 	Ver1.0.2    SADのモード"SERVO_AIR"を追加
* 				MMD用マクロMOTORx(x=1~3)を追加
*/
#ifndef SPI_DEF_LIB_H_
#define SPI_DEF_LIB_H_

// SPI関係
#define MOSI1 p5
#define MISO1 p6
#define SCK1  p7
#define SS1   p8

#define MOSI2 p11
#define MISO2 p12
#define SCK2  p13
#define SS2   p14

// SLOT
#define SLOT1	0
#define SLOT2	1
#define SLOT3	2
#define SLOT4	3
#define SLOT5	4
#define SLOT6	5
#define SLOT7	6
#define SLOT8	7
#define SLOT9	8
#define SLOT10	9
#define SLOT11	10
#define SLOT12	11
#define SLOT13	12
#define SLOT14	13
#define SLOT15	14
#define SLOT16	15
#define SLOT17	16
#define SLOT18	17
#define SLOT19	18
#define SLOT20	19
#define SLOT21	20
#define SLOT22	21
#define SLOT23	22
#define SLOT24	23
#define SLOT25	24
#define SLOT26	25
#define SLOT27	26
#define SLOT28	27
#define SLOT29	28
#define SLOT30	29
#define SLOT31	30
#define SLOT32	31

// SPI通信成功・失敗状態
#define SPI_FAILED  -1
#define SPI_SUCCESS  0

#define MOT        0x30
#define AIR        0x40
#define SERVO      0x60
#define SERVO_AIR  0x90

// INIT OR
#define ENC_ON      0x80
#define ENC_OFF     0x00
#define DIG_ADJ_ON  0x80
#define DIG_ADJ_OFF 0x00
#define CURRENT     0x01
#define CURRENT_CUT 0x02

/*********** MD **********/
#define R_SW        0x00
#define L_SW        0x01

/********** MMD *********/
#define MOTOR1      0
#define MOTOR2      1
#define MOTOR3      2

/*********** AD **********/
#define sAIR1       0x01
#define sAIR2       0x02
#define sAIR3       0x04
#define sAIR4       0x08
#define sAIR5       0x10
#define sAIR6       0x20
#define sAIR7       0x40
#define sAIR8       0x80

#define ALL_OFF     0x00  //全部OFF
#define ALL_ON      0xFF  //全部ON

/*********** SD **********/
//サーボたち
#define SERVO1      0x01
#define SERVO2      0x02
#define SERVO3      0x04
#define SERVO4      0x08
#define SERVO5      0x10
#define SERVO6      0x20
#define SERVO7      0x40
#define SERVO8      0x80

/********** ENC **********/
#define ENC1    0
#define ENC2	1
#define ENC3	2
#define ENC4	3

/********** LIDER **********/
#define LIDER1  0
#define LIDER2	1
#define LIDER3	2
#define LIDER4	3

/*********** SR **********/
#define X_AXIS      0
#define Y_AXIS      1
#define Z_AXIS      2

/************CS***********/
#define RED			0
#define GREEN		1
#define BLUE		2
#define INFRA		3

// PSDセンサ・フォトインタラプタ番号
#define PSD_PHOTO_1          0 | 0x80
#define PSD_PHOTO_2          1 | 0x80
#define PSD_PHOTO_3          2 | 0x80
#define PSD_PHOTO_4          3 | 0x80
#define PSD_PHOTO_5          4 | 0x80
#define PSD_PHOTO_6          5 | 0x80
#define PSD_PHOTO_7          6 | 0x80
#define PSD_PHOTO_8          7 | 0x80
#define PSD_PHOTO_9          8 | 0x80
#define PSD_PHOTO_10         9 | 0x80
#define PSD_PHOTO_11        10 | 0x80
#define PSD_PHOTO_12        11 | 0x80
#define PSD_PHOTO_13        12 | 0x80
#define PSD_PHOTO_14        13 | 0x80
#define PSD_PHOTO_15        14 | 0x80
#define PSD_PHOTO_16        15 | 0x80

// リミットスイッチ番号
#define LIM_SW_1	0
#define LIM_SW_2	1
#define LIM_SW_3	2
#define LIM_SW_4	3
#define LIM_SW_5	4
#define LIM_SW_6	5
#define LIM_SW_7	6
#define LIM_SW_8	7

// アナログセンサ番号
#define ANALOG_1	0
#define ANALOG_2	1
#define ANALOG_3	2
#define ANALOG_4	3
#define ANALOG_5	4
#define ANALOG_6	5
#define ANALOG_7	6
#define ANALOG_8	7
#define ANALOG_9	8
#define ANALOG_10	9
#define ANALOG_11	10
#define ANALOG_12	11
#define ANALOG_13	12

//カラーセンサ番号
#define COLOR_1		0
#define COLOR_2		1
#define COLOR_3		2
#define COLOR_4		3
#define COLOR_5		4
#define COLOR_6		5
#define COLOR_7		6
#define COLOR_8		7
#define COLOR_9		8
#define COLOR_10	9
#define COLOR_11	10
#define COLOR_12	11
#define COLOR_13	12
#define COLOR_14	13
#define COLOR_15	14
#define COLOR_16	15

#endif
