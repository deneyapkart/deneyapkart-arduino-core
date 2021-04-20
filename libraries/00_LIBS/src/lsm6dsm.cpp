/******************************************************************************
LSM6DSM.cpp
LSM6DSM Deneyap DevKit Library

Library for LSM6DSM 6-axis Inertial Measurement Unit (IMU)
--> Configuration functions
--> Data manipulation functions
--> I2C communication functions

Ozgur BOSTAN @ RFtek Electronics
ozgur.bostan@rftek.com.tr
April 25, 2020

2020 Copyright (c) RFtek Electronics Ltd.  All right reserved.
******************************************************************************/

#include <Arduino.h>
#include "lsm6dsm.h"
#include "deneyap.h"

/**
  * @brief  I2C initialization and read check  
  * @param  None
  * @retval Return state (status_t)
  */
status_t LSM6DSMCore::beginCore(void)
{
	status_t returnError = IMU_SUCCESS;

	Wire.begin(IMUSD, IMUSC, 0);

	// Spin for a few ms
	volatile uint8_t temp = 0;
	for( uint16_t i = 0; i < 10000; i++ )
	{
		temp++;
	}

	// Check the ID register for a successful initialization
	uint8_t readCheck;
	readRegister(WHO_AM_I, &readCheck);
	if( readCheck != WHO_AM_I_REG_VALUE )
	{
		returnError = IMU_HW_ERROR;
	}

	return returnError;
}

/**
  * @brief  I2C read command for specified data length  
  * @param  Output pointer, register address, data length
  * @retval Return state (status_t)
  */
status_t LSM6DSMCore::readRegisterRegion(uint8_t regAddress, uint8_t *outputPointer, uint8_t length)
{
	status_t returnError = IMU_SUCCESS;

	uint8_t i = 0;
	uint8_t c = 0;

	Wire.beginTransmission((uint8_t)LSM6DSM_ADDRESS);
	Wire.write((uint8_t)regAddress);
	if( Wire.endTransmission() != 0 )
	{
		returnError = IMU_HW_ERROR;
	}
	else 
	{
		Wire.requestFrom((uint8_t)LSM6DSM_ADDRESS, (uint8_t)length);
		while ( (Wire.available()) && (i < length))  // slave may send less than requested
		{
			c = Wire.read(); // receive a byte as character
			*outputPointer = c;
			outputPointer++;
			i++;
		}
	}

	return returnError;
}

/**
  * @brief  I2C read command for 8bit unsigned data
  * @param  Output pointer, register address
  * @retval Return state (status_t)
  */
status_t LSM6DSMCore::readRegister(uint8_t regAddress, uint8_t* outputPointer) 
{
	uint8_t result = 0;
	status_t returnError = IMU_SUCCESS;

	Wire.beginTransmission((uint8_t)LSM6DSM_ADDRESS);
	Wire.write((uint8_t)regAddress);
	if( Wire.endTransmission() != 0 )
	{
		returnError = IMU_HW_ERROR;
	}
	Wire.requestFrom((uint8_t)LSM6DSM_ADDRESS, (uint8_t)1);
	while ( Wire.available() ) // slave may send less than requested
	{
		result = Wire.read(); // receive a byte as a proper uint8_t
	}

	*outputPointer = result;
	return returnError;
}

/**
  * @brief  I2C read command for 16bit signed data
  * @param  Output pointer, register address
  * @retval Return state (status_t)
  */
status_t LSM6DSMCore::readRegisterInt16(uint8_t regAddress, int16_t* outputPointer)
{
	uint8_t myBuffer[2];
	status_t returnError = readRegisterRegion((uint8_t)regAddress, myBuffer, (uint8_t)2); 
	int16_t output = (int16_t)myBuffer[0] | int16_t(myBuffer[1] << 8);
	
	*outputPointer = output;
	return returnError;
}

/**
  * @brief  I2C write command for 8bit unsigned data
  * @param  Register address, data to write
  * @retval Return state (status_t)
  */
status_t LSM6DSMCore::writeRegister(uint8_t regAddress, uint8_t data) 
{
	status_t returnError = IMU_SUCCESS;

	Wire.beginTransmission((uint8_t)LSM6DSM_ADDRESS);
	Wire.write((uint8_t)regAddress);
	Wire.write((uint8_t)data);
	if( Wire.endTransmission() != 0 )
	{
		returnError = IMU_HW_ERROR;
	}

	return returnError;
}

/**
  * @brief  Inherited class constructor  
  * @param  None
  * @retval None
  */
LSM6DSM::LSM6DSM()
{
	// Construct with these default settings
  // Settings for gyro
	settings.gyroEnabled           = 1;      // 0 or 1
	settings.gyroRange             = 245;    // Max deg/s: 125, 245, 500, 1000, 2000
	settings.gyroSampleRate        = 416;    // Hz: 13, 26, 52, 104, 208, 416, 833, 1666, 3330, 6660
	settings.gyroBandWidth         = 400;    // Hz: 50, 100, 200, 400
  settings.gyroLowPowerEnabled   = 0;      // 0 or 1  
	settings.gyroFifoEnabled       = 1;      // Set to include gyro in FIFO
	settings.gyroFifoDecimation    = 1;      // Set 1 for on /1
  // Settings for accelerometer
	settings.accelEnabled          = 1;      // 0 or 1
	//settings.accelOdrOff         = 1;      // 0 or 1
	settings.accelRange            = 2;      // Max G force readable: 2, 4, 8, 16
	settings.accelSampleRate       = 416;    // Hz: 1, 13, 26, 52, 104, 208, 416, 833, 1666, 3330, 6660
	settings.accelBandWidth        = 400;    // Hz: 400, 1500
  settings.accelLowPowerEnabled  = 0;      // 0 or 1
	settings.accelFifoEnabled      = 1;      // Set to include accelerometer in the FIFO
	settings.accelFifoDecimation   = 1;      // Set 1 for on /1

	settings.tempEnabled           = 1;
	// Interface mode selection
	settings.commMode              = 1;      // Can be modes 1, 2 or 3
	// FIFO control data
	settings.fifoThreshold         = 3000;   // 0 to 4096 (16 bit bytes)
	settings.fifoSampleRate        = 10;     // Default 10Hz
	settings.fifoModeWord          = 0;      // Default off
  // Variables used for error check
	allOnesCounter                 = 0;
	nonSuccessCounter              = 0;
}

/**
  * @brief  Settings configuration
  * @param  Sensor settings
  * @retval Return state (status_t)
  */
status_t LSM6DSM::begin(SensorSettings* pSettingsYouWanted)
{
	// Check the settings structure values to determine how to setup the device
	uint8_t dataToWrite = 0;               // Temporary variable

	// Begin the inherited core
	status_t returnError = beginCore();
  if(returnError != IMU_SUCCESS)
  {
    return returnError;
  }
	
	// Copy the values from the user's settings into the output 'pSettingsYouWanted'
	// Compare settings with 'pSettingsYouWanted' after 'begin' to see if anything changed
	if(pSettingsYouWanted != NULL){ 
		pSettingsYouWanted->gyroEnabled         = settings.gyroEnabled;
		pSettingsYouWanted->gyroRange           = settings.gyroRange;
		pSettingsYouWanted->gyroSampleRate      = settings.gyroSampleRate;
		pSettingsYouWanted->gyroBandWidth       = settings.gyroBandWidth;
		pSettingsYouWanted->gyroFifoEnabled     = settings.gyroFifoEnabled;
		pSettingsYouWanted->gyroFifoDecimation  = settings.gyroFifoDecimation;
		pSettingsYouWanted->accelEnabled        = settings.accelEnabled;
		//pSettingsYouWanted->accelOdrOff         = settings.accelOdrOff;
		pSettingsYouWanted->accelRange          = settings.accelRange;
		pSettingsYouWanted->accelSampleRate     = settings.accelSampleRate;
		pSettingsYouWanted->accelBandWidth      = settings.accelBandWidth;
		pSettingsYouWanted->accelFifoEnabled    = settings.accelFifoEnabled;
		pSettingsYouWanted->accelFifoDecimation = settings.accelFifoDecimation;
		pSettingsYouWanted->tempEnabled         = settings.tempEnabled;
		pSettingsYouWanted->commMode            = settings.commMode;
		pSettingsYouWanted->fifoThreshold       = settings.fifoThreshold;
		pSettingsYouWanted->fifoSampleRate      = settings.fifoSampleRate;
		pSettingsYouWanted->fifoModeWord        = settings.fifoModeWord;
	}

	// Setup the accelerometer
	dataToWrite = 0;                       // Start Fresh!

	if (settings.accelEnabled == 1) 
  {
		// Build config reg
		// First patch in filter bandwidth
		switch (settings.accelBandWidth) 
    {
  		default:                             // Set default case to max passthrough
  			settings.accelBandWidth = 400;
  			break;
  		case 400:
  			dataToWrite |= BW0_XL_400Hz;
  			break;
      case 1500:
        dataToWrite |= BW0_XL_1500Hz;
		}
		// Next, patch in full scale
		switch (settings.accelRange) 
    {
  		case 2:
  			dataToWrite |= FS_XL_2g;
  			break;
  		case 4:
  			dataToWrite |= FS_XL_4g;
  			break;
  		case 8:
  			dataToWrite |= FS_XL_8g;
  			break;
  		default:                            // Set default case to 16 (max)
  			settings.accelRange = 16;
  			break;
  		case 16:
  			dataToWrite |= FS_XL_16g;
  			break;
		}
		// Lastly, patch in accelerometer ODR
		switch (settings.accelSampleRate) 
    {
  		case 13:
  			dataToWrite |= ODR_XL_12_5Hz;
  			break;
  		case 26:
  			dataToWrite |= ODR_XL_26Hz;
  			break;
  		case 52:
  			dataToWrite |= ODR_XL_52Hz;
  			break;
  		default:                            // Set default to 104
  			settings.accelSampleRate = 104;
  			break;
  		case 104:
  			dataToWrite |= ODR_XL_104Hz;
  			break;
  		case 208:
  			dataToWrite |= ODR_XL_208Hz;
  			break;
  		case 416:
  			dataToWrite |= ODR_XL_416Hz;
  			break;
  		case 833:
  			dataToWrite |= ODR_XL_833Hz;
  			break;
  		case 1660:
  			dataToWrite |= ODR_XL_1660Hz;
  			break;
  		case 3330:
  			dataToWrite |= ODR_XL_3330Hz;
  			break;
  		case 6660:
  			dataToWrite |= ODR_XL_6660Hz;
  			break;
  		case 1:
  			dataToWrite |= ODR_XL_1_6Hz;
  			break;
  		}
	}
	else
	{
		//dataToWrite already = 0 (powerdown);
	}

	// Now, write the patched together data
	returnError = writeRegister(CTRL1_XL, dataToWrite);
  if(returnError != IMU_SUCCESS)
  {
    return returnError;
  }
  // Accelerometer low-power mode configuration
  dataToWrite = 0;
  dataToWrite |= XL_HM_MODE_ENABLED;
  if(settings.accelLowPowerEnabled == 1)
  {
    returnError = writeRegister(CTRL6_C, dataToWrite);

    if(returnError != IMU_SUCCESS)
    {
      return returnError;
    }
  }
  /*
	// Set the ODR bit
	readRegister(&dataToWrite, CTRL4_C);
	dataToWrite &= ~((uint8_t)BW_SCAL_ODR_ENABLED);
	if ( settings.accelOdrOff == 1) 
  {
		dataToWrite |= BW_SCAL_ODR_ENABLED;
	}
	writeRegister(CTRL4_C, dataToWrite);
  */
	// Setup the gyroscope
	dataToWrite = 0;                       // Start Fresh!
	if (settings.gyroEnabled == 1) 
  {
		// Build config reg
		// First, patch in full scale
		switch (settings.gyroRange) 
    {
  		case 125:
  			dataToWrite |= FS_125_ENABLED;
  			break;
  		case 245:
  			dataToWrite |= FS_G_245dps;
  			break;
  		case 500:
  			dataToWrite |= FS_G_500dps;
  			break;
  		case 1000:
  			dataToWrite |= FS_G_1000dps;
  			break;
  		default:                          // Default to full 2000DPS range
  			settings.gyroRange = 2000;
  			break;
  		case 2000:
  			dataToWrite |= FS_G_2000dps;
  			break;
		}
		// Lastly, patch in gyro ODR
		switch (settings.gyroSampleRate) 
    {
  		case 13:
  			dataToWrite |= ODR_G_13Hz;
  			break;
  		case 26:
  			dataToWrite |= ODR_G_26Hz;
  			break;
  		case 52:
  			dataToWrite |= ODR_G_52Hz;
  			break;
  		default:                          // Set default to 104
  			settings.gyroSampleRate = 104;
  			break;
  		case 104:
  			dataToWrite |= ODR_G_104Hz;
  			break;
  		case 208:
  			dataToWrite |= ODR_G_208Hz;
  			break;
  		case 416:
  			dataToWrite |= ODR_G_416Hz;
  			break;
  		case 833:
  			dataToWrite |= ODR_G_833Hz;
  			break;
  		case 1660:
  			dataToWrite |= ODR_G_1660Hz;
  			break;
      case 3330:
        dataToWrite |= ODR_G_3330Hz;
        break;
      case 6660:
        dataToWrite |= ODR_G_6660Hz;
        break;
		}
	}
	else
	{
		//dataToWrite already = 0 (powerdown);
	}
	// Write the byte
	returnError = writeRegister(CTRL2_G, dataToWrite);
  if(returnError != IMU_SUCCESS)
  {
    return returnError;
  }
  // Gyro low-power mode configuration
  dataToWrite = 0;
  dataToWrite |= G_HM_MODE_ENABLED;
  if(settings.gyroLowPowerEnabled == 1)
  {
    returnError = writeRegister(CTRL7_G, dataToWrite);

    if(returnError != IMU_SUCCESS)
    {
      return returnError;
    }
  }
	// Setup the internal temperature sensor
	if (settings.tempEnabled == 1) 
  {

	}

	return returnError;
}

/**
  * @brief  Read accelerometer X-axis raw data   
  * @param  None
  * @retval X-axis raw data
  */
int16_t LSM6DSM::readRawAccelX(void)
{
	int16_t data;
	status_t returnError = readRegisterInt16(OUTX_L_XL, &data);
	if(returnError != IMU_SUCCESS)
	{
		if(returnError == IMU_ALL_ONES_WARNING)
		{
			allOnesCounter++;
		}
		else
		{
			nonSuccessCounter++;
		}
	}

	return data;
}

/**
  * @brief  Read accelerometer X-axis manipulated data   
  * @param  None
  * @retval X-axis manipulated data
  */
float LSM6DSM::readFloatAccelX(void)
{
	float data = calcAccel(readRawAccelX());

	return data;
}

/**
  * @brief  Read accelerometer Y-axis raw data   
  * @param  None
  * @retval Y-axis raw data
  */
int16_t LSM6DSM::readRawAccelY(void)
{
	int16_t data;
	status_t returnError = readRegisterInt16(OUTY_L_XL, &data);
	if(returnError != IMU_SUCCESS)
	{
		if(returnError == IMU_ALL_ONES_WARNING)
		{
			allOnesCounter++;
		}
		else
		{
			nonSuccessCounter++;
		}
	}

	return data;
}

/**
  * @brief  Read accelerometer Y-axis manipulated data   
  * @param  None
  * @retval Y-axis manipulated data
  */
float LSM6DSM::readFloatAccelY(void)
{
	float data = calcAccel(readRawAccelY());

	return data;
}

/**
  * @brief  Read accelerometer Z-axis raw data   
  * @param  None
  * @retval Z-axis raw data
  */
int16_t LSM6DSM::readRawAccelZ(void)
{
	int16_t data;
	status_t returnError = readRegisterInt16(OUTZ_L_XL, &data);
	if(returnError != IMU_SUCCESS)
	{
		if(returnError == IMU_ALL_ONES_WARNING)
		{
			allOnesCounter++;
		}
		else
		{
			nonSuccessCounter++;
		}
	}

	return data;
}

/**
  * @brief  Read accelerometer Z-axis manipulated data   
  * @param  None
  * @retval Z-axis manipulated data
  */
float LSM6DSM::readFloatAccelZ(void)
{
	float data = calcAccel(readRawAccelZ());

	return data;
}

/**
  * @brief  Accelerometer data manipulation   
  * @param  Axis data to manipulate
  * @retval Manipulated data
  */
float LSM6DSM::calcAccel(int16_t input)
{
	float data = (float)input * 0.061 * (settings.accelRange >> 1) / 1000;

	return data;
}

/**
  * @brief  Read gyro Z-axis raw data   
  * @param  None
  * @retval X-axis raw data
  */
int16_t LSM6DSM::readRawGyroX(void)
{
	int16_t data;
	status_t returnError = readRegisterInt16(OUTX_L_G, &data);
	if(returnError != IMU_SUCCESS)
	{
		if(returnError == IMU_ALL_ONES_WARNING)
		{
			allOnesCounter++;
		}
		else
		{
			nonSuccessCounter++;
		}
	}

	return data;
}

/**
  * @brief  Read gyro X-axis manipulated data   
  * @param  None
  * @retval X-axis manipulated data
  */
float LSM6DSM::readFloatGyroX( void )
{
	float data = calcGyro(readRawGyroX());

	return data;
}

/**
  * @brief  Read gyro Y-axis raw data   
  * @param  None
  * @retval Y-axis raw data
  */
int16_t LSM6DSM::readRawGyroY(void)
{
	int16_t data;
	status_t returnError = readRegisterInt16(OUTY_L_G, &data);
	if(returnError != IMU_SUCCESS)
	{
		if(returnError == IMU_ALL_ONES_WARNING)
		{
			allOnesCounter++;
		}
		else
		{
			nonSuccessCounter++;
		}
	}

	return data;
}

/**
  * @brief  Read gyro Y-axis manipulated data   
  * @param  None
  * @retval Y-axis manipulated data
  */
float LSM6DSM::readFloatGyroY(void)
{
	float data = calcGyro(readRawGyroY());

	return data;
}

/**
  * @brief  Read gyro Z-axis raw data   
  * @param  None
  * @retval Z-axis raw data
  */
int16_t LSM6DSM::readRawGyroZ(void)
{
	int16_t data;
	status_t returnError = readRegisterInt16(OUTZ_L_G, &data);
	if(returnError != IMU_SUCCESS)
	{
		if(returnError == IMU_ALL_ONES_WARNING)
		{
			allOnesCounter++;
		}
		else
		{
			nonSuccessCounter++;
		}
	}

	return data;
}

/**
  * @brief  Read gyro Z-axis manipulated data   
  * @param  None
  * @retval Z-axis manipulated data
  */
float LSM6DSM::readFloatGyroZ(void)
{
	float data = calcGyro(readRawGyroZ());

	return data;
}

/**
  * @brief  Gyro data manipulation   
  * @param  Axis data to manipulate
  * @retval Manipulated data
  */
float LSM6DSM::calcGyro( int16_t input )
{
	uint8_t gyroRangeDivisor = settings.gyroRange / 125;
	if ( settings.gyroRange == 245 ) {
		gyroRangeDivisor = 2;
	}

	float data = (float)input * 4.375 * (gyroRangeDivisor) / 1000;

	return data;
}

/**
  * @brief  Read temperature raw data   
  * @param  None
  * @retval Temperature raw data
  */
int16_t LSM6DSM::readRawTemp(void)
{
	int16_t data;
	readRegisterInt16(OUT_TEMP_L, &data);

	return data;
}  

/**
  * @brief  Read temperature manipulated data in Celsius   
  * @param  None
  * @retval Temperature manipulated data
  */
float LSM6DSM::readTempC(void)
{
	float data = (float)readRawTemp() / 256;	// Divide by 16 to scale
	data += 25;                            		// Add 25 degrees to remove offset

	return data;
}

/**
  * @brief  Read temperature manipulated data in Fahrenheit   
  * @param  None
  * @retval Fahrenheit manipulated data
  */
float LSM6DSM::readTempF(void)
{
	float data = (float)readRawTemp() / 256;	// Divide by 16 to scale
	data += 25;                              	// Add 25 degrees to remove offset
	data = (data * 9) / 5 + 32;

	return data;
}

/**
  * @brief  Read all raw data (acc, gyro, temp)
  * @param  Array to write data
  * @retval None
  */
void LSM6DSM::readAllAxesRawData(int16_t* axisData)
{
	uint8_t rawData[14];
	status_t returnError = readRegisterRegion((uint8_t)OUT_TEMP_L, &rawData[0], (uint8_t)14);
	if(returnError != IMU_SUCCESS)
	{
		if(returnError == IMU_ALL_ONES_WARNING)
		{
			allOnesCounter++;
		}
		else
		{
			nonSuccessCounter++;
		}
	}
	axisData[0] = rawData[0] 	| ((int16_t)rawData[1] 	<< 8);
	axisData[1] = rawData[2] 	| ((int16_t)rawData[3] 	<< 8);
	axisData[2] = rawData[4] 	| ((int16_t)rawData[5] 	<< 8);
	axisData[3] = rawData[6] 	| ((int16_t)rawData[7] 	<< 8);
	axisData[4] = rawData[8] 	| ((int16_t)rawData[9] 	<< 8);
	axisData[5] = rawData[10] | ((int16_t)rawData[11] << 8);
	axisData[6] = rawData[12] | ((int16_t)rawData[13] << 8);
}

/**
  * @brief  Read all manipulated data (acc, gyro)
  * @param  Array to write data
  * @retval None
  */
void LSM6DSM::readAllAxesFloatData(float* axisData)
{
	int16_t rawData[7];
	readAllAxesRawData(rawData);

	uint8_t gyroRangeDivisor = settings.gyroRange / 125;
	if ( settings.gyroRange == 245 )
		gyroRangeDivisor = 2;
	// Gyro axes
	axisData[0] = (float)rawData[1] * 4.375 * (gyroRangeDivisor) / 1000;
	axisData[1] = (float)rawData[2] * 4.375 * (gyroRangeDivisor) / 1000;
	axisData[2] = (float)rawData[3] * 4.375 * (gyroRangeDivisor) / 1000;

	axisData[3] = (float)rawData[4] * 0.061 * (settings.accelRange >> 1) / 1000;
	axisData[4] = (float)rawData[5] * 0.061 * (settings.accelRange >> 1) / 1000;
	axisData[5] = (float)rawData[6] * 0.061 * (settings.accelRange >> 1) / 1000;
}

/**
  * @brief  FIFO configuration
  * @param  None
  * @retval None
  */
void LSM6DSM::fifoBegin(void) 
{
	// Split and mask the threshold
	uint8_t thresholdLByte = settings.fifoThreshold & 0x00FF;
	uint8_t thresholdHByte = (settings.fifoThreshold & 0x0F00) >> 8;

	// Configure FIFO_CTRL3
	uint8_t tempFIFO_CTRL3 = 0;
	if (settings.gyroFifoEnabled == 1)
	{
		// Set up gyro stuff
		// Build on FIFO_CTRL3
		// Set decimation
		tempFIFO_CTRL3 |= (settings.gyroFifoDecimation & 0x07) << 3;
	}
	if (settings.accelFifoEnabled == 1)
	{
		// Set up accelerometer stuff
		// Build on FIFO_CTRL3
		// Set decimation
		tempFIFO_CTRL3 |= (settings.accelFifoDecimation & 0x07);
	}

	// Configure FIFO_CTRL4  (nothing for now-- sets data sets 3 and 4)
	uint8_t tempFIFO_CTRL4 = 0;


	// Configure FIFO_CTRL5
	uint8_t tempFIFO_CTRL5 = 0;
	switch (settings.fifoSampleRate) 
	{
		default:  //set default case to 10Hz(slowest)
			break;
		case 10:
			tempFIFO_CTRL5 |= ODR_FIFO_12_5Hz;
			break;
		case 25:
			tempFIFO_CTRL5 |= ODR_FIFO_26Hz;
			break;
		case 50:
			tempFIFO_CTRL5 |= ODR_FIFO_52Hz;
			break;
		case 100:
			tempFIFO_CTRL5 |= ODR_FIFO_104Hz;
			break;
		case 200:
			tempFIFO_CTRL5 |= ODR_FIFO_208Hz;
			break;
		case 400:
			tempFIFO_CTRL5 |= ODR_FIFO_416Hz;
			break;
		case 800:
			tempFIFO_CTRL5 |= ODR_FIFO_833Hz;
			break;
		case 1600:
			tempFIFO_CTRL5 |= ODR_FIFO_1660Hz;
			break;
		case 3300:
			tempFIFO_CTRL5 |= ODR_FIFO_3330Hz;
			break;
		case 6600:
			tempFIFO_CTRL5 |= ODR_FIFO_6660Hz;
			break;
	}
	// Hard code the fifo mode here:
	tempFIFO_CTRL5 |= settings.fifoModeWord = 6;  //set mode:

	// Write data
	writeRegister(FIFO_CTRL1, thresholdLByte);
	writeRegister(FIFO_CTRL2, thresholdHByte);
	writeRegister(FIFO_CTRL3, tempFIFO_CTRL3);
	writeRegister(FIFO_CTRL4, tempFIFO_CTRL4);
	writeRegister(FIFO_CTRL5, tempFIFO_CTRL5);
}

/**
  * @brief  Clear FIFO
  * @param  None
  * @retval None
  */
void LSM6DSM::fifoClear(void) {
	// Drain the fifo data and dump it
	while((fifoGetStatus() & 0x1000) == 0) 
	{
		fifoRead();
	}
}

/**
  * @brief  Read data from FIFO
  * @param  None
  * @retval Data from FIFO
  */
int16_t LSM6DSM::fifoRead(void) 
{
	// Pull the last data from the fifo
	uint8_t tempReadByte = 0;
	uint16_t tempAccumulator = 0;
	readRegister(FIFO_DATA_OUT_L, &tempReadByte);
	tempAccumulator = tempReadByte;
	readRegister(FIFO_DATA_OUT_H, &tempReadByte);
	tempAccumulator |= ((uint16_t)tempReadByte << 8);

	return tempAccumulator;
}

/**
  * @brief  Read FIFO status
  * @param  None
  * @retval FIFO status
  */
uint16_t LSM6DSM::fifoGetStatus( void ) {
	// Return some data on the state of the fifo
	uint8_t tempReadByte = 0;
	uint16_t tempAccumulator = 0;
	readRegister(FIFO_STATUS1, &tempReadByte);
	tempAccumulator = tempReadByte;
	readRegister(FIFO_STATUS2, &tempReadByte);
	tempAccumulator |= (tempReadByte << 8);

	return tempAccumulator;  
}

/**
  * @brief  Disable FIFO
  * @param  None
  * @retval None
  */
void LSM6DSM::fifoEnd( void ) {
	// turn off fifo
	writeRegister(FIFO_CTRL5, 0x00);  // Disable
}

