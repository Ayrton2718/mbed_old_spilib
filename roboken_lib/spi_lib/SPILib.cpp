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
*   Ver1.0.4    MMD,SAD用の関数を追加
* 2017/9/18
* 	Ver1.0.5 	SadDriveをServoAirDriveに変更
* 2018/6/24
* 	Ver1.0.5	MD開放用の関数を追加
*/

#include "SPILib.h"

namespace spi_lib
{
	SPILib::SPILib(int md, int ad, int sd)
    {
        for(int i = 0; i < SPISize; i++)
            dummyData[i] = Dummy;

        for(int i = 0; i < SPIDriverNum; i++)
        {
            currentValue[i] = 512;
            currentLimit[i] = 612;
            encCnt[i] = 0;
            duty[i] = 0x80;
            funwariH[i] = 2;
            funwariL[i] = 2;
            airData[i] = ALL_OFF;
            isFailureDriver[i] = SPI_SUCCESS;

            for(int j = 0; j < 8; j++)
                servoPulse[i][j] = 0;
        }

        for(int i = 0; i < 2; i++)
            swStateMDENC[i] = 0;

        for(int i = 0; i < SPISensorReceiverNum; i++)
        {
            for(int j = 0; j < LimSwNum; j++)
                limSwState[i][j] = 0;

            for(int j = 0; j < AnalogNum; j++)
                anData[i][j] = 0;

            for(int j = 0; j < PSDPhotoNum; j++)
                psdPhotoState[i][j] = 0;

            for(int j = 0; j < 3; j++)
            {
                gyData[i][j] = 0;
                acData[i][j] = 0;
            }

            allLimitSwState[i] = 0x00;
            isFailureSensor[i] = SPI_SUCCESS;
        }

        mdNum  = md;
        adNum  = ad;
        sdNum  = sd;
        slaveNum = mdNum + adNum + sdNum;

        isSPIDriverComm = false;
        isSPISensorComm = false;

        printf("1\n");

        ss_init();
        printf("2\n");
        // SSpin初期化
        output_ss(SlaveNoSelect);
        printf("3\n");

        // currentCutPin = new DigitalIn(p14);
        // spiStopPin = new DigitalIn(p17);

        roboken_basic::safetyHigh();
    }

    SPILib::SPILib(int md, int mmd, int ad, int sd, int sad, int enc)
    {
        for(int i = 0; i < SPISize; i++)
            dummyData[i] = Dummy;
    
        for(int i = 0; i < SPIDriverNum; i++)
        {
            currentValue[i] = 512;
            currentLimit[i] = 612;
            encCnt[i] = 0;
            duty[i] = 0x80;
            funwariH[i] = 2;
            funwariL[i] = 2;
            airData[i] = ALL_OFF;
            isFailureDriver[i] = SPI_SUCCESS;
            
            for(int j = 0; j < 8; j++)
                servoPulse[i][j] = 0;
        }
    
        for(int i = 0; i < 2; i++)
            swStateMDENC[i] = 0;
    
        for(int i = 0; i < SPISensorReceiverNum; i++)
        {
            for(int j = 0; j < LimSwNum; j++)
                limSwState[i][j] = 0;
    
            for(int j = 0; j < AnalogNum; j++)
                anData[i][j] = 0;
    
            for(int j = 0; j < PSDPhotoNum; j++)
                psdPhotoState[i][j] = 0;
    
            for(int j = 0; j < 3; j++)
            {
                gyData[i][j] = 0;
                acData[i][j] = 0;
            }
    
            allLimitSwState[i] = 0x00;
            isFailureSensor[i] = SPI_SUCCESS;
        }
    
        mdNum  = md;
        mmdNum = mmd;
        adNum  = ad;
        sdNum  = sd;
        sadNum = sad;
        encNum = enc;
        slaveNum = mdNum + mmdNum + adNum + sdNum + sadNum + encNum;

        isSPIDriverComm = false;
        isSPISensorComm = false;
    
        ss_init();
        // SSpin初期化
        output_ss(SlaveNoSelect);
    
        // currentCutPin = new DigitalIn(p14);
        // spiStopPin = new DigitalIn(p17);
    
        roboken_basic::safetyHigh();
    }
    
    SPILib::SPILib(int md, int mmd, int ad, int sd, int sad, int enc, int lider)
	{
		for(int i = 0; i < SPISize; i++)
			dummyData[i] = Dummy;

		for(int i = 0; i < SPIDriverNum; i++)
		{
			currentValue[i] = 512;
			currentLimit[i] = 612;
			encCnt[i] = 0;
			duty[i] = 0x80;
			funwariH[i] = 2;
			funwariL[i] = 2;
			airData[i] = ALL_OFF;
			isFailureDriver[i] = SPI_SUCCESS;

			for(int j = 0; j < 8; j++)
				servoPulse[i][j] = 0;
		}

		for(int i = 0; i < 2; i++)
			swStateMDENC[i] = 0;

		for(int i = 0; i < SPISensorReceiverNum; i++)
		{
			for(int j = 0; j < LimSwNum; j++)
				limSwState[i][j] = 0;

			for(int j = 0; j < AnalogNum; j++)
				anData[i][j] = 0;

			for(int j = 0; j < PSDPhotoNum; j++)
				psdPhotoState[i][j] = 0;

			for(int j = 0; j < 3; j++)
			{
				gyData[i][j] = 0;
				acData[i][j] = 0;
			}

			allLimitSwState[i] = 0x00;
			isFailureSensor[i] = SPI_SUCCESS;
		}

		mdNum  = md;
		mmdNum = mmd;
		adNum  = ad;
		sdNum  = sd;
		sadNum = sad;
		encNum = enc;
		slaveNum = mdNum + mmdNum + adNum + sdNum + sadNum + encNum;

		isSPIDriverComm = false;
		isSPISensorComm = false;

		ss_init();
		// SSpin初期化
		output_ss(SlaveNoSelect);

		// currentCutPin = new DigitalIn(p14);
		// spiStopPin = new DigitalIn(p17);

		roboken_basic::safetyHigh();
	}

    // SPI初期化
    void SPILib::ss_init(void)
    {
        // SPI通信ピン設定
        printf("1\n");
        spi     = new SPIComm(PA_7, PA_6, PA_5);
        printf("2\n");
        // select = new BusOut(PA_3, PA_1, PA_0);
        select = new BusOut(A2, A1, A0);
        printf("3\n");
        ss = new BusOut(PB_0, PB_7, PB_6, PB_1); //p15~p25
        // ss = new BusOut(D3, D4, D5, D6); //p15~p25
    }
    
    void SPILib::output_ss(int slot)
    {
        int val = 0x0f;
        int shift = 0x01;
    
        // SSpin-High
        *ss = val;
    
        // SSpin-Low
        if(slot >= 0)
        {
            *select = slot % 8;
    
            shift <<= (slot / 8);
            *ss = val & ~shift;
        }
    }
    
    // ビットから互換数字へ変換(16bit対応)
    int SPILib::bitNumConv(int bit)
    {
        int i, j, len;
        
        if      (bit < 256)     len = 8;
        else if (bit < 65536)   len = 16;
        else                    return 0;
        
        for(i = 0, j = 0x01; i < len; i++, j <<= 1)
        {
            if(bit & j) break;
        }
        
        return i;
    }
    
    // SPI通信関数
    int SPILib::spiDriverComm(char data[SPISize], char mode, int slot)
    {
        int failure = SPI_SUCCESS;
        char checksum;
        char modeBuff;
        char driverChecksum;
        unsigned char sensData[4] = {0};

        if(isSPIDriverComm == true)
        {
            isFailureDriver[slot] = SPI_FAILED;
            roboken_basic::led1 =  1;
            return SPI_FAILED;
        }
        else
        	isSPIDriverComm = true;
    
        // チェックサム生成
        checksum = mode;
        for(int i = 0; i < SPISize; i++)
            checksum += data[i];
                        
        // 通信開始(10us待ちは重要！)
        output_ss(slot);
        wait_us(10);

        modeBuff = mode;

        //上位4bitをエンコーダのset, getの判定に
        //下位4bitをエンコーダ集約基板のスロット判定に
        if(mode == EncSet || mode == EncGet || mode == Lider)
	  {
		mode |= (char)(((SlotBuff) % 4) & 0x0f);
	  }
            
        // データ送信
        spi->spi_write(mode);
        wait_us(20);       // ※このディレイがないとうまく動かない(受信側のタイミングがずれる)
        
        // 1Byte目送信 & mode受信
        if(spi->spi_write(data[0])  != mode)          failure = SPI_FAILED;
        
        if(( (mode == NormalMode) && (initData[slot][0] & ENC_ON) ) || mode == CurrentGet)
        {
            sensData[0] = (char)spi->spi_write(data[1]);         wait_us(1);
            sensData[1] = (char)spi->spi_write(data[2]);         wait_us(1);
            sensData[2] = (char)spi->spi_write(data[3]);         wait_us(1);
            sensData[3] = (char)spi->spi_write(checksum);        wait_us(1);
            wait_us(10);
            driverChecksum = (char)spi->spi_write(Dummy);
            
            checksum = mode;
            for(int i = 0; i < SPISize; i++)
                checksum += sensData[i];
    
            if(checksum != driverChecksum)          failure = SPI_FAILED;
            
            // 電流測定値格納
            else if(mode == CurrentGet)
                currentValue[slot] = (int)roboken_basic::make16(sensData[1], sensData[0]);
            
            // エンコーダ値格納
            else
                encCnt[slot] = (signed int)roboken_basic::make32(sensData[3], sensData[2], sensData[1], sensData[0]);
        }
        else if(modeBuff == EncGet)
        {
        	wait_us(3405);//エンコーダー集約基板から値をもらうまでまつ(これはしゃあないで)
            sensData[0] = (char)spi->spi_write(data[1]);         wait_us(1);
            sensData[1] = (char)spi->spi_write(data[2]);         wait_us(1);
            sensData[2] = (char)spi->spi_write(data[3]);         wait_us(1);
            sensData[3] = (char)spi->spi_write(checksum);        wait_us(1);
            wait_us(10);
            driverChecksum = (char)spi->spi_write(Dummy);

            checksum = modeBuff;
            for(int i = 0; i < SPISize; i++)
                checksum += sensData[i];
            if(checksum != driverChecksum)          failure = SPI_FAILED;

            // エンコーダ値格納
            else
                encCnt[slot] = (signed int)roboken_basic::make32(sensData[3], sensData[2], sensData[1], sensData[0]);
        }
        else if(modeBuff == Lider)
		{
			wait_us(10);
			sensData[0] = (char)spi->spi_write(data[1]);         wait_us(1);
			sensData[1] = (char)spi->spi_write(data[2]);         wait_us(1);
			sensData[2] = (char)spi->spi_write(data[3]);         wait_us(1);
			sensData[3] = (char)spi->spi_write(checksum);        wait_us(1);
			wait_us(10);
			driverChecksum = (char)spi->spi_write(Dummy);

			checksum = modeBuff;
			for(int i = 0; i < SPISize; i++)
				checksum += sensData[i];
			if(checksum != driverChecksum)          failure = SPI_FAILED;

			// lider値格納
			else
				lider[slot] = (signed int)roboken_basic::make32(sensData[3], sensData[2], sensData[1], sensData[0]);
		}
        else if(mode == SwStateGet)
        {
            // スレーブ側のデータ準備のため
            wait_us(2);
            
            sensData[0] = (char)spi->spi_write(data[1]);     wait_us(1);
            sensData[1] = (char)spi->spi_write(data[2]);     wait_us(1);
            sensData[2] = (char)spi->spi_write(data[3]);     wait_us(1);
    
            sensData[3] = (char)spi->spi_write(checksum);
            wait_us(10);
            driverChecksum = (char)spi->spi_write(Dummy);
    
            checksum = mode;
            for(int i = 0; i < SPISize; i++)
                checksum += sensData[i];
    
            if(checksum != driverChecksum)          failure = SPI_FAILED;
    
            // スイッチ状態格納
            else if(mode == SwStateGet)
                swStateMDENC[(int)data[0]] = (bool)sensData[0];
         }
        else
        {
            if(spi->spi_write(data[1])       != data[0])    failure = SPI_FAILED;
            if(spi->spi_write(data[2])       != data[1])    failure = SPI_FAILED;
            if(spi->spi_write(data[3])       != data[2])    failure = SPI_FAILED;
            if(spi->spi_write(checksum) != data[3])         failure = SPI_FAILED;
            wait_us(10);
            if((char)spi->spi_write(Dummy) != checksum)     failure = SPI_FAILED;
        }
    
        // 通信終了(10us待ちは重要！)
        wait_us(10);
        output_ss(SlaveNoSelect);
    
        // SPI通信失敗LED点灯
        if(failure == SPI_FAILED)
            roboken_basic::led1 = 1;
        else
            roboken_basic::led1 = 0;
    
        isSPIDriverComm = false;
        isFailureDriver[slot] = failure;
    
        // 通信結果を返す  
        return failure;
    }
    
    // SPI通信状態確認関数
    bool SPILib::checkDriverComm()
    {
    	return isSPIDriverComm;
    }

    bool SPILib::checkSensorComm()
    {
    	return isSPISensorComm;
    }

    /************** セッター ****************/
    
    // ドライバーモードセット
    void SPILib::setInitMode(int slot, int mode)
    {
        initData[slot][0] = mode;
        
        switch(mode)
        {
            case AIR:
                for(int i = 1; i < SPISize; i++)
                    initData[slot][i] = Dummy;
                break;
                
            case SERVO:
                for(int i = 2; i < SPISize; i++)
                    initData[slot][i] = Dummy;
                break;
                
            case SERVO_AIR:
				for(int i = 2; i < SPISize; i++)
					initData[slot][i] = Dummy;
				break;

            default:
                initData[slot][3] = Dummy;
        }
    }
    
    /*---------------- MD ------------------*/
    // 漸増周期セット
    void SPILib::setInitFunwariH(int slot, int data)
    {
        initData[slot][1] = data;
    }
    
    // 漸減周期セット
    void SPILib::setInitFunwariL(int slot, int data)
    {
        initData[slot][2]   = data;
    }
    
    // Dutyセット
    void SPILib::setMotorDuty(int slot, int data)
    {
        driverData[slot][0] = data;
        driverData[slot][1] = Dummy;
        driverData[slot][2] = Dummy;
        driverData[slot][3] = Dummy;
    }
    
    // 上限電流(A/D変換値)セット
    int SPILib::setCurrentLim(int slot, int currentLim)
    {
    	int failure;

        driverData[slot][0] = roboken_basic::make8(currentLim, 0);
        driverData[slot][1] = roboken_basic::make8(currentLim, 1);
        driverData[slot][2] = Dummy;
        driverData[slot][3] = Dummy;
    
        failure = spiDriverComm(driverData[slot], CurrentSet, slot);
        if(failure == SPI_SUCCESS)
        	currentLimit[slot] = currentLim;
    
        return failure;
    }
    
    // 漸増周期セット
    int SPILib::setFunwariH(int slot, int data)
    {
    	int failure;

        driverData[slot][0] = data;
        driverData[slot][1] = Dummy;
        driverData[slot][2] = Dummy;
        driverData[slot][3] = Dummy;
    
        failure = spiDriverComm(driverData[slot], FunwariHSet, slot);
        if(failure == SPI_SUCCESS)
        	funwariH[slot] = data;
    
        return failure;
    }
    
    // 漸減周期セット
    int SPILib::setFunwariL(int slot, int data)
    {
    	int failure;

        driverData[slot][0] = data;
        driverData[slot][1] = Dummy;
        driverData[slot][2] = Dummy;
        driverData[slot][3] = Dummy;
    
        failure = spiDriverComm(driverData[slot], FunwariLSet, slot);
        if(failure == SPI_SUCCESS)
        	funwariL[slot] = data;
    
        return failure;
    }
    
    /*---------------- AD ------------------*/
    // AD出力データセット
    void SPILib::setAirData(int slot, char num)
    {
        driverData[slot][0] = (int)num;
        driverData[slot][1] = Dummy;
        driverData[slot][2] = Dummy;
        driverData[slot][3] = Dummy;
    }
    
    /*---------------- SD ------------------*/
    // サーボの制御数セット
    void SPILib::setServoNum(int slot, int data)
    {
        initData[slot][1] = data;
    }
    
    // SDの動作パルス入力
    void SPILib::setServoPulse(int slot, char num, int pulse)
    {
        if(pulse > 2000)
            pulse = 2000;
        else if(pulse < 0)
            pulse = 0;
    
        driverData[slot][0] = num;
        driverData[slot][1] = roboken_basic::make8(pulse, 0);
        driverData[slot][2] = roboken_basic::make8(pulse, 1);
        driverData[slot][3] = Dummy;
    }

    /*---------------- SAD ------------------*/
	// SADのサーボ動作パルス,Air出力データ入力
	void SPILib::setDataSAD(int slot, char airNum, char servoNum, int pulse)
	{
		if(pulse > 2000)
		{
			pulse = 2000;
		}
		else if(pulse < 0)
		{
			pulse = 0;
		}

		driverData[slot][0] = (int)airNum;
		driverData[slot][1] = servoNum;
		driverData[slot][2] = roboken_basic::make8(pulse, 0);
		driverData[slot][3] = roboken_basic::make8(pulse, 1);
	}

	/*--------------- ENC -------------------*/
    // エンコーダカウントセット
    int SPILib::setEncCnt(int slot, int encSlot, signed int count)
    {
        driverData[slot][0] = roboken_basic::make8(count, 0);
        driverData[slot][1] = roboken_basic::make8(count, 1);
        driverData[slot][2] = roboken_basic::make8(count, 2);
        driverData[slot][3] = roboken_basic::make8(count, 3);

        SlotBuff = encSlot;
        return spiDriverComm(driverData[slot], EncSet, slot);
    }
    /****************************************/
    
    /************** ゲッター ****************/
    
    // SPI通信成功状況確認
    int SPILib::getFailureDriver(int slot)
    {
        return isFailureDriver[slot];
    }
    
    int SPILib::getFailureSensor(void)
    {
        return isFailureSensor[SLOT1];
    }
    
    // SLAVE数をゲット
    int SPILib::getSlaveNum(void)
    {
        return slaveNum;
    }
    
    // MD数をゲット
    int SPILib::getMDNum(void)
    {
        return mdNum;
    }
    
    // MMD数をゲット
    int SPILib::getMMDNum(void)
    {
    	return mmdNum;
    }

    // AD数をゲット
    int SPILib::getADNum(void)
    {
        return adNum;
    }
    
    // SD数をゲット
    int SPILib::getSDNum(void)
    {
        return sdNum;
    }
    
	// SAD数をゲット
	int SPILib::getSADNum(void)
	{
		return sadNum;
	}

	//ENC数をゲット
	int SPILib::getENCNum(void)
	{
	   return encNum;
	}

    // ドライバーモードゲット
    int SPILib::getInitMode(int slot)
    {
        return initData[slot][0];
    }
    
    /*---------------- MD ------------------*/
    // 漸増周期ゲット
    int SPILib::getInitFunwariH(int slot)
    {
        return initData[slot][1];
    }
    
    // 漸減周期ゲット
    int SPILib::getInitFunwariL(int slot)
    {
        return initData[slot][2];
    }

    // Dutyゲット
    int SPILib::getMotorDuty(int slot)
    {
        return duty[slot];
    }

    // 上限電流ゲット
    int SPILib::getCurrentLim(int slot)
    {
        return currentLimit[slot];
    }
    
    // 漸増周期セット
    int SPILib::getFunwariH(int slot)
    {
        return funwariH[slot];
    }
    
    // 漸減周期セット
    int SPILib::getFunwariL(int slot)
    {
        return funwariL[slot];
    }
    
    // 電流値ゲット
    int SPILib::getCurrent(int slot)
    {
        spiDriverComm(dummyData, CurrentGet, slot);
    
        return currentValue[slot];
    }
    
    // MDのスイッチの状態ゲット
    bool SPILib::getSwState(int slot, int swNum)
    {
        driverData[slot][0] = swNum;
        driverData[slot][1] = Dummy;
        driverData[slot][2] = Dummy;
        driverData[slot][3] = Dummy;
    
        spiDriverComm(driverData[slot], SwStateGet, slot);
    
        return swStateMDENC[swNum];
    }
    
    // 電流カットチェック(1・・・電流カット)
    int SPILib::getCurrentCut(void)
    {
        // return !(int)currentCutPin->read();
        return 0;
    }
    
    /*---------------- AD ------------------*/
    // AD出力データゲット
    int SPILib::getAirData(int slot)
    {
        return airData[slot];
    }
    
    /*---------------- SD ------------------*/
    // サーボの制御数ゲット
    int SPILib::getServoNum(int slot)
    {
        return initData[slot][1];
    }
    
    // サーボパルスゲット
    int SPILib::getServoPulse(int slot, int num)
    {
        return servoPulse[slot][bitNumConv(num)];
    }

	/*--------------- ENC -------------------*/
    // エンコーダ の(pulse / count)をゲット
    int SPILib::getInitEncPulse(int slot)
    {
        return initData[slot][3];
    }

    // エンコーダカウント値取得
    signed int SPILib::getEncCnt(int slot, int encSlot)
    {
    	SlotBuff = encSlot;

        spiDriverComm(dummyData, EncGet, slot);

        return encCnt[slot];
    }

   //Lider
   signed int SPILib::getLider(int slot, int liderSlot)
   {
	   SlotBuff = liderSlot;

		spiDriverComm(dummyData, Lider, slot);

		return lider[slot];
   }
    /****************************************/
    
    /************** 駆動関数 ****************/
    
    // ドライバ初期化関数
    int SPILib::driverInit(int slot)
    {
        return spiDriverComm(initData[slot], InitMode, slot);
    }
    
    // ドライバ初期化関数
    int SPILib::driverInit(int slot, int mode)
    {
        setInitMode(slot, mode);
    
        return spiDriverComm(initData[slot], InitMode, slot);
    }
    
    /*---------------- MD ------------------*/
    // setMotorDuty()によりセット済みのDutyを送る
    int SPILib::driverSendMD(int slot)
    {
    	int failure;
    	failure = spiDriverComm(driverData[slot], NormalMode, slot);

		if(failure == SPI_SUCCESS)
			duty[slot] = driverData[slot][0];

        return failure;
    }
    
    // 引数のDutyを送る
    int SPILib::driverSendMD(int slot, int dutyBuff)
    {
    	int failure;
        setMotorDuty(slot, dutyBuff);
        failure = spiDriverComm(driverData[slot], NormalMode, slot);

        if(failure == SPI_SUCCESS)
			duty[slot] = dutyBuff;
        
        return failure;
    }
    
    int SPILib::driverFreeMD(int slot)
    {
    	int failure;
    	setMotorDuty(slot, 0x80);
    	failure = spiDriverComm(driverData[slot], FreeMode, slot);

		if(failure == SPI_SUCCESS)
			duty[slot] = 0x80;

        return failure;
    }

    /*------------------------------------------------------------------------------*/
    /* FHS 40-P/SP600                                                               */
    /*                                                                              */
    /* ICの上面からMagnetic Sensorの距離...0.47mm                                       */
    /* Vout...A/D変換出力                                                               */
    /* Vref...2.5Vの出力←基準電圧                                                      */
    /* Ip.....線を流れる電流値                                                          */
    /* r'.....IC上面から銅線の中心までの距離                                              */
    /* r......Magnetic Sensorから銅線の中心までの距離                                       */
    /* Vout = G・Ip + Vref                                                           */
    /* G    = Vs / Ip = (Vout - Vref) / Ip = (1.2 * 10^-4) / ( r * 10^-3 )          */
    /*                                                                              */
    /* ∴Ip ≒ ((Vout - 2.5) * (r' + 0.47)) * 10) / 1.2                               */
    /*------------------------------------------------------------------------------*/
    
    // A/D変換値を電流に変換
    double SPILib::currentConv(int dataADC)
    {
        // A/D変換値を電流値に変換
        double vol = ((double)dataADC * 5) / 1024;
        double vs  = vol - 2.5;
        double r   = (ToMagneticSensorDistance + ToWireCenterDistance);
        double g   = (1.2 * 0.0001) / (r * 0.001);
        double ip  = vs / g;
    
        return ip;
    }
    
    /*---------------- MMD ------------------*/
	// setMotorDuty()によりセット済みのDutyを送る
	int SPILib::driverSendMMD(int slot, int num)
	{
		int failure;

		driverData[slot][1] = num;

		failure = spiDriverComm(driverData[slot], NormalMode, slot);

		if(failure == SPI_SUCCESS)
			duty[slot] = driverData[slot][0];

		return failure;
	}

	// 引数のDutyを送る
	int SPILib::driverSendMMD(int slot, int num, int dutyBuff)
	{
		int failure;
		setMotorDuty(slot, dutyBuff);
		driverData[slot][1] = num;
		failure = spiDriverComm(driverData[slot], NormalMode, slot);

		if(failure == SPI_SUCCESS)
			duty[slot] = dutyBuff;

		return failure;
	}

    /*---------------- AD ------------------*/
    //シングルソレノイド送信関数
    int SPILib::driverSendAD(int slot)
    {
    	int failure;
    	failure = spiDriverComm(driverData[slot], AirDrive, slot);

    	if(failure == SPI_SUCCESS)
    		airData[slot] = driverData[slot][0];

        return failure;
    }
    
    int SPILib::driverSendAD(int slot, char num)
    {
    	int failure;
        setAirData(slot, num);
        failure = spiDriverComm(driverData[slot], AirDrive, slot);

        if(failure == SPI_SUCCESS)
        	airData[slot] = num;
    
        return failure;
    }
    
    /*---------------- SD ------------------*/
    // サーボ回転
    int SPILib::driverSendSD(int slot, char num)
    {
    	int failure;
    	failure = spiDriverComm(driverData[slot], ServoSpin, slot);

    	if(failure == SPI_SUCCESS)
    		servoPulse[slot][bitNumConv(driverData[slot][0])] = roboken_basic::make16(driverData[slot][2], driverData[slot][1]);

        return failure;
    }
    
    int SPILib::driverSendSD(int slot, char num, int pulse)
    {
    	int failure;
        setServoPulse(slot, num, pulse);
        failure = spiDriverComm(driverData[slot], ServoSpin, slot);

        if(failure == SPI_SUCCESS)
        	servoPulse[slot][bitNumConv(num)] = pulse;
    
        return failure;
    }

    /*---------------- SAD ------------------*/
    // シングルソレノイド,サーボ回転送信関数
    int SPILib::driverSendSAD(int slot)
    {
    	int failure;
		failure = spiDriverComm(driverData[slot], ServoAirDrive, slot);

		if(failure == SPI_SUCCESS)
		{
			airData[slot] = driverData[slot][0];
			servoPulse[slot][bitNumConv(driverData[slot][1])] =roboken_basic::make16(driverData[slot][3], driverData[slot][2]);
		}

		return failure;
    }

    int SPILib::driverSendSAD(int slot, char airNum, char servoNum, int pulse)
   	{
       	int failure;
    	setDataSAD(slot, airNum, servoNum, pulse);
    	failure = spiDriverComm(driverData[slot], ServoAirDrive, slot);

   		if(failure == SPI_SUCCESS)
   		{
   			airData[slot] = airNum;
   			servoPulse[slot][bitNumConv(servoNum)] = pulse;
   		}

   		return failure;
   	}
    /****************************************/
    
    /************** センサ取得 *****************/
    /*---------------- SR ------------------*/
    // リミットスイッチ・PSDセンサ・フォトインタラプタ状態取得
    bool SPILib::input(int sensorNum)
    {
        char data[SPISize];
        char mode;
        int failure = SPI_SUCCESS;
    
        if(sensorNum & 0x80)    mode = PSDPhoto;
        else                    mode = LimSw;
    
        if(mode == LimSw)
        {
            data[0] = sensorNum;
            data[1] = Dummy;
            data[2] = Dummy;
            data[3] = Dummy;
        }
        else if(mode == PSDPhoto)
        {
            data[0] = sensorNum & 0x7f;// 最上位ビットを落とす
            data[1] = Dummy;
            data[2] = Dummy;
            data[3] = Dummy;
        }
    
        if(mode == LimSw)
            return limSwState[SLOT1][(int)data[0]];
        else if(mode == PSDPhoto)
            return psdPhotoState[SLOT1][(int)data[0]];
    
        return failure;
    }
    
    // リミットスイッチ状態取得一括取得モード
    char SPILib::input(void)
    {
        char data[SPISize];
    
        data[0] = Dummy;
        data[1] = Dummy;
        data[2] = Dummy;
        data[3] = Dummy;    
        return allLimitSwState[SLOT1];
    }
    
    // ジャイロセンサAD変換値取得モード
    signed short SPILib::readGy(int axis)
    {
        char data[SPISize];
    
        data[0] = axis;
        data[1] = Dummy;
        data[2] = Dummy;
        data[3] = Dummy;
        
        return gyData[SLOT1][axis];
    }
    
    // 加速度センサAD変換値取得モード
    unsigned short SPILib::readAc(int axis)
    {
        char data[SPISize];
    
        data[0] = axis;
        data[1] = Dummy;
        data[2] = Dummy;
        data[3] = Dummy;    
        return acData[SLOT1][axis];
    }
    
    // アナログセンサAD変換値取得モード
    unsigned short SPILib::readADC(int analogNum)
    {
        char data[SPISize];
    
        data[0] = analogNum;
        data[1] = Dummy;
        data[2] = Dummy;
        data[3] = Dummy;    
        return anData[SLOT1][analogNum];
    }

    unsigned short SPILib::readCol(int color, int sensorNum)
    {
    	char data[SPISize];

		data[0] = sensorNum;
		data[1] = Dummy;
		data[2] = Dummy;
		data[3] = Dummy;

		switch(color)
		{
		case RED :
			break;

		case GREEN :
			break;

		case BLUE :
			break;

		case INFRA :
			break;

		default :
			break;
		}

		return coData[sensorNum][color];
    }
}
