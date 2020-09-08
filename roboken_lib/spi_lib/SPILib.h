/*
* SPILib.h 更新履歴
* 2016/6/24
*   Ver1.0.0    一次完成
* 2016/9/17
*   Ver1.0.1    Driverの通信失敗フラグをデフォルトでTRUEに
* 2017/3/3
* 	Ver1.0.2	SPI通信状態が確認できる関数を追加
* 				get~で取得できる最終送信データは通信成功時のみ更新に変更
* 2017/3/15
* 	Ver1.0.3	const変数をPascal Caseに書き換え
* 2017/8/18
* 	Ver1.0.4    MMD,SAD用の関数を追加
* 2018/6/24
* 	Ver1.0.5	MD開放用の関数を追加
*/
#ifndef SPI_LIB_H_
#define SPI_LIB_H_

#include <SPIDefLib.h>
#include <SPIComm.h>
#include "../basic/basic.h"


using namespace spi_lib;

namespace spi_lib
{ 
    class SPILib
    {
    private:
        // ドライバー数上限
        static const int SPIDriverNum = 32;
        static const int SPISensorReceiverNum = 2;
    
        // SPIデータ
        static const int SPISize = 4;
    
        // DUMMYデータ←通信データの埋め合わせ
        static const char Dummy = 0x55;
    
        // スレーブ未選択時SSピンをhighへ
        static const int SlaveNoSelect = -1;
    
        /********** Mode **********/
        // INIT
        static const char InitMode = 0x0F;
    
        // MD-Motor_Driver
        static const char NormalMode	= 0xF0;
        static const char EncMode		= 0xB0;// MOT | ENC_ON
        static const char EncGet		= 0xB0;
        static const char EncSet		= 0xC0;
        static const char Lider			= 0xD0;
        static const char CurrentSet	= 0xE0;
        static const char CurrentGet	= 0x0E;
        static const char SwStateGet	= 0x0B;
        static const char FunwariHSet	= 0x10;
        static const char FunwariLSet	= 0x20;
        static const char FreeMode		= 0x7c;
    
        // AD-Air_Driver
        static const char AirDrive		= 0xD0;
    
        // SD-Servo_Driver
        static const char ServoSpin		= 0x09;

        // SAD-Servo_Air_Driver
		static const char ServoAirDrive      = 0xD9;
    
        // SR-Sensor Receiver
        static const char LimSw			= 0x04;
        static const char LimSwAll		= 0x40;
        static const char GYSensor		= 0x07;
        static const char ACSensor		= 0x87;
        static const char ADSensor		= 0x70;
        static const char PSDPhoto		= 0xA0;
        static const char ColorRed		= 0x08;
        static const char ColorGreen	= 0x80;
        static const char ColorBlue		= 0x0A;
        static const char ColorInfra	= 0x78;
    
        /*----電流センサ関係----*/
        // 電流センサの上面からMagnetic Sensorまでの距離(mm)
        // static const char ToMagneticSensorDistance   = 0.47;
        static const char ToMagneticSensorDistance   = 0;
        // 電流センサの上面から銅線の中心までの距離(mm)
        static const char ToWireCenterDistance       = 2;
    
        // リミットスイッチ使用可能数
        static const int LimSwNum = 8;
        // アナログセンサ使用可能数
        static const int AnalogNum = 13;
        // PSDセンサ・フォトインタラプタ
        static const int PSDPhotoNum = 16;
        // カラーセンサ
        static const int ColorSensNum = 16;
    
        SPIComm *spi;
        BusOut *select;
        BusOut *ss;
        
        // DigitalIn *currentCutPin;
        // DigitalIn *spiStopPin;
    
        // SPI通信成功状況確認フラグ
        int isFailureDriver[SPIDriverNum];
        int isFailureSensor[SPISensorReceiverNum];
        // スレーブ数
        int slaveNum;
        // MD数
        int mdNum;
        // MMD数
        int mmdNum;
        // AD数
        int adNum;
        // SD数
        int sdNum;
        // SAD数
		int sadNum;
		// ENC数
		int encNum;
        // 初期化データ
        char initData[SPIDriverNum][SPISize];
        // SPI通信送信データ
        char driverData[SPIDriverNum][SPISize];
        // DUMMYデータ←送信するデータが特にないとき
        char dummyData[SPISize];
        // ADの出力データ
        int airData[SPIDriverNum];
        // サーボアングル
        int servoPulse[SPIDriverNum][8];
        // モータドライバのリミットスイッチの状態格納配列
        bool swStateMDENC[2];
        // MDの電流センサA/D変換値
        int currentValue[SPIDriverNum];
        // MDの電流センサ限界値
        int currentLimit[SPIDriverNum];
        // MDのDuty
        int duty[SPIDriverNum];
        // MDの漸増周期
        int funwariH[SPIDriverNum];
        // MDの漸減周期
        int funwariL[SPIDriverNum];
        // リミットスイッチの状態
        bool limSwState[SPISensorReceiverNum][LimSwNum];
        // リミットスイッチの全状態
        char allLimitSwState[SPISensorReceiverNum];
        // ジャイロセンサの状態
        signed short gyData[SPISensorReceiverNum][3];
        // 加速度センサの状態
        unsigned short acData[SPISensorReceiverNum][3];
        // アナログセンサAD変換値
        unsigned short anData[SPISensorReceiverNum][AnalogNum];
        // PSDセンサ・フォトインタラプタの状態
        bool psdPhotoState[SPISensorReceiverNum][PSDPhotoNum];
        // カラーセンサ
        unsigned short coData[ColorSensNum][4];
        // エンコーダとliderのスロット番号バッファ
        int SlotBuff;


        // DriverとのSPI通信中フラグ
        bool isSPIDriverComm;
        // Sensor ReceiverとのSPI通信中フラグ
        bool isSPISensorComm;
    
        // ビットから互換数字へ変換
        int bitNumConv(int bit);
        // SPI通信関数
        void ss_init(void);
        void output_ss(int slot);
        int spiDriverComm(char data[SPISize], char mode, int slot);
    
    public:
        // エンコーダカウント値格納配列
        signed int encCnt[SPIDriverNum];
        //　lider値格納配列
        signed int lider[SPIDriverNum];
    
        SPILib(int md, int ad, int sd);
        SPILib(int md, int mmd, int ad, int sd, int sad, int enc);
        SPILib(int md, int mmd, int ad, int sd, int sad, int enc, int lider);

        // SPI通信状態確認関数
        bool checkDriverComm();
        bool checkSensorComm();
    
        /************** セッター ****************/
        // ドライバーモードセット
        void setInitMode(int slot, int mode);
    
        /*---------------- MD ------------------*/
        // 漸増周期セット
        void setInitFunwariH(int slot, int data);
        // 漸減周期セット
        void setInitFunwariL(int slot, int data);
        // Dutyセット
        void setMotorDuty(int slot, int data);
        // 上限電流セット
        int setCurrentLim(int slot, int currentLim);
        // 漸増周期セット
        int setFunwariH(int slot, int data);
        // 漸減周期セット
        int setFunwariL(int slot, int data);
    
        /*---------------- AD ------------------*/
        // AD出力データ入力
        void setAirData(int slot, char data);
    
        /*---------------- SD ------------------*/
        // サーボの制御数セット
        void setServoNum(int slot, int data);
        // SDの動作パルス入力
        void setServoPulse(int slot, char num, int pulse);

        /*---------------- SAD ------------------*/
        // サーボとソレノイド同時入力
		void setDataSAD(int slot, char airNum, char servoNum, int pulse);

		/*---------------- ENC ------------------*/
        // エンコーダカウントセット
        int setEncCnt(int slot, int encSlot, signed int count);
		/****************************************/
    
        /************** ゲッター ****************/
        // SPI通信成功状況確認
        int getFailureDriver(int slot);
        int getFailureSensor(void);
    
        // SLAVE数をゲット
        int getSlaveNum(void);
        // MD数をゲット
        int getMDNum(void);
        // MMD数をゲット
        int getMMDNum(void);
        // AD数をゲット
        int getADNum(void);
        // SD数をゲット
        int getSDNum(void);
        // SAD数をゲット
		int getSADNum(void);
		// ENC数をゲット
		int getENCNum(void);
        // ドライバーモードゲット
        int getInitMode(int slot);
    
        /*---------------- MD ------------------*/
        // 漸増周期ゲット
        int getInitFunwariH(int slot);
        // 漸減周期ゲット
        int getInitFunwariL(int slot);
        // Dutyゲット
        int getMotorDuty(int slot);
        // 上限電流ゲット
        int getCurrentLim(int slot);
        // 漸増周期セット
        int getFunwariH(int slot);
        // 漸減周期セット
        int getFunwariL(int slot);
        // 電流値ゲット
        int getCurrent(int slot);
        // MDのスイッチの状態ゲット
        bool getSwState(int slot, int swNum);
        // 電流カットチェック
        int getCurrentCut(void);
    
        /*---------------- AD ------------------*/
        // AD出力データ出力
        int getAirData(int slot);
    
        /*---------------- SD ------------------*/
        // サーボの制御数ゲット
        int getServoNum(int slot);
        // サーボ角度ゲット
        int getServoPulse(int slot, int num);

        /*---------------- ENC -----------------*/
        // エンコーダ の(pulse / count)をゲット
        int getInitEncPulse(int slot);
        // エンコーダカウントゲット
        signed int getEncCnt(int slot, int encSlot);
        /****************************************/

        /*--------------- LIDER ----------------*/
        // lider値ゲット
        signed int getLider(int slot, int liderSlot);
        /****************************************/
    
        /*************** 駆動関数 *****************/
        // ドライバ初期化関数
        int driverInit(int slot);
        int driverInit(int slot, int mode);
    
        /*---------------- MD ------------------*/
        // Dutyセット及び送信
        int driverSendMD(int slot);
        int driverSendMD(int slot, int dutyBuff);
        int driverFreeMD(int slot);
        // A/D変換値を電流に変換
        double currentConv(int dataADC);

        /*---------------- MMD ------------------*/
		// Dutyセット及び送信
		int driverSendMMD(int slot, int num);
		int driverSendMMD(int slot, int num, int duty);
    
        /*---------------- AD ------------------*/
        // ソレノイド開閉
        int driverSendAD(int slot);
        int driverSendAD(int slot, char num);
    
        /*---------------- SD ------------------*/
        // サーボ回転
        int driverSendSD(int slot, char num);
        int driverSendSD(int slot, char num, signed int angle);

        /*---------------- SAD ------------------*/
        // ソレノイド開閉＆サーボ回転
	    int driverSendSAD(int slot);
	    int driverSendSAD(int slot, char airNum, char servoNum, int pulse);
        /****************************************/
    
        /************** センサ取得関数 ****************/
        // リミットスイッチ・PSDセンサ・フォトインタラプタ状態取得
        bool input(int sensorNum);
        // リミットスイッチ状態取得一括取得モード
        char input(void);
        // ジャイロセンサAD変換値取得モード
        signed short readGy(int axis);
        // 加速度センサAD変換値取得モード
        unsigned short readAc(int axis);
        // アナログセンサAD変換値取得モード
        unsigned short readADC(int analogNum);
        // カラーセンサ取得モード
        unsigned short readCol(int color, int sensorNum);
    };
}

#endif
