#ifndef __LSM6DSM_H__
#define __LSM6DSM_H__

#include <Wire.h>

#define LSM6DSM_ADDRESS				(0x6A)
#define WHO_AM_I_REG_VALUE		(0x6A)

// Return states 
typedef enum
{
	IMU_SUCCESS,
	IMU_HW_ERROR,
	IMU_NOT_SUPPORTED,
	IMU_GENERIC_ERROR,
	IMU_OUT_OF_BOUNDS,
	IMU_ALL_ONES_WARNING,
} status_t;

// Core class includes read and write operations
// Higher level functions can be accessed via LSM6DSM class inherited from core class
class LSM6DSMCore
{
public:
	//LSM6DSMCore();
	~LSM6DSMCore() = default;
	
	status_t beginCore(void);
	status_t readRegisterRegion(uint8_t, uint8_t*, uint8_t);
	status_t readRegister(uint8_t, uint8_t*);
	status_t readRegisterInt16(uint8_t, int16_t*);
	status_t writeRegister(uint8_t, uint8_t);
};

// Struct variables used as settings for calculations
struct SensorSettings {
public:
	//Gyro settings
	uint8_t 	gyroEnabled;
	uint16_t 	gyroRange;
	uint16_t 	gyroSampleRate;
	uint16_t 	gyroBandWidth;
	uint8_t		gyroLowPowerEnabled;
	uint8_t 	gyroFifoEnabled;
	uint8_t 	gyroFifoDecimation;
	//Accelerometer settings
	uint8_t 	accelEnabled;
	uint8_t 	accelOdrOff;
	uint16_t 	accelRange;
	uint16_t 	accelSampleRate;
	uint16_t 	accelBandWidth;	
	uint8_t		accelLowPowerEnabled;
	uint8_t 	accelFifoEnabled;
	uint8_t 	accelFifoDecimation;	
	//Temperature settings
	uint8_t 	tempEnabled;	
	//Non-basic mode settings
	uint8_t 	commMode;	
	//FIFO control data
	uint16_t 	fifoThreshold;
	int16_t 	fifoSampleRate;
	uint8_t 	fifoModeWord;	
};

// Higher level class inherited from core class includes begin() method
// and data manipulation functions
class LSM6DSM : public LSM6DSMCore
{
public:
	// IMU settings
	SensorSettings settings;	
	// Error checking
	uint16_t allOnesCounter;
	uint16_t nonSuccessCounter;
	// Constructor generates default SensorSettings.
	// (over-ride after construction if desired)
	LSM6DSM();
	~LSM6DSM() = default;	
	// Call to apply SensorSettings
	status_t begin(SensorSettings* pSettingsYouWanted = NULL);
	// Returns the raw bits from the sensor cast as 16-bit signed integers
	int16_t readRawAccelX(void);
	int16_t readRawAccelY(void);
	int16_t readRawAccelZ(void);
	int16_t readRawGyroX(void);
	int16_t readRawGyroY(void);
	int16_t readRawGyroZ(void);
	// Returns the values as floats
	float readFloatAccelX(void);
	float readFloatAccelY(void);
	float readFloatAccelZ(void);
	float readFloatGyroX(void);
	float readFloatGyroY(void);
	float readFloatGyroZ(void);
	// Acc and Gyro manipulations
	float calcGyro(int16_t);
	float calcAccel(int16_t);
	// Temperature related methods
	int16_t readRawTemp(void);
	float readTempC(void);
	float readTempF(void);
	// Read all data together (acc, gyro, temp)
	void readAllAxesRawData(int16_t*);
	void readAllAxesFloatData(float*);
	// FIFO stuff
	void fifoBegin(void);
	void fifoClear(void);
	int16_t fifoRead(void);
	uint16_t fifoGetStatus(void);
	void fifoEnd(void);	
};

/* REGISTERS */
#define FUNC_CFG_ACCESS					(0X01)
#define SENSOR_SYNC_TIME_FRAME	(0X04)
#define SENSOR_SYNC_RES_RATIO		(0X05)
#define FIFO_CTRL1  						(0X06)
#define FIFO_CTRL2  						(0X07)
#define FIFO_CTRL3  						(0X08)
#define FIFO_CTRL4  						(0X09)
#define FIFO_CTRL5  						(0X0A)
#define DRDY_PULSE_CFG 					(0X0B)
#define INT1_CTRL  							(0X0D)
#define INT2_CTRL  							(0X0E)
#define WHO_AM_I  							(0X0F)
#define CTRL1_XL  							(0X10)
#define CTRL2_G  								(0X11)
#define CTRL3_C  								(0X12)
#define CTRL4_C  								(0X13)
#define CTRL5_C  								(0X14)
#define CTRL6_C  								(0X15)
#define CTRL7_G  								(0X16)
#define CTRL8_XL  							(0X17)
#define CTRL9_XL  							(0X18)
#define CTRL10_C  							(0X19)
#define MASTER_CONFIG  					(0X1A)
#define WAKE_UP_SRC  						(0X1B)
#define TAP_SRC  								(0X1C)
#define D6D_SRC  								(0X1D)
#define STATUS_REG  						(0X1E)
#define OUT_TEMP_L  						(0X20)
#define OUT_TEMP_H  			      (0X21)
#define OUTX_L_G  				      (0X22)
#define OUTX_H_G  				      (0X23)
#define OUTY_L_G  				      (0X24)
#define OUTY_H_G  				      (0X25)
#define OUTZ_L_G  				      (0X26)
#define OUTZ_H_G  				      (0X27)
#define OUTX_L_XL  				      (0X28)
#define OUTX_H_XL  				      (0X29)
#define OUTY_L_XL  				      (0X2A)
#define OUTY_H_XL  				      (0X2B)
#define OUTZ_L_XL  				      (0X2C)
#define OUTZ_H_XL  				      (0X2D)
#define SENSORHUB1_REG  		    (0X2E)
#define SENSORHUB2_REG  		    (0X2F)
#define SENSORHUB3_REG  		    (0X30)
#define SENSORHUB4_REG  		    (0X31)
#define SENSORHUB5_REG  		    (0X32)
#define SENSORHUB6_REG  		    (0X33)
#define SENSORHUB7_REG  		    (0X34)
#define SENSORHUB8_REG  		    (0X35)
#define SENSORHUB9_REG  		    (0X36)
#define SENSORHUB10_REG  		    (0X37)
#define SENSORHUB11_REG  		    (0X38)
#define SENSORHUB12_REG  		    (0X39)
#define FIFO_STATUS1  			    (0X3A)
#define FIFO_STATUS2  			    (0X3B)
#define FIFO_STATUS3  			    (0X3C)
#define FIFO_STATUS4  			    (0X3D)
#define FIFO_DATA_OUT_L  		    (0X3E)
#define FIFO_DATA_OUT_H  		    (0X3F)
#define TIMESTAMP0_REG  		    (0X40)
#define TIMESTAMP1_REG  		    (0X41)
#define TIMESTAMP2_REG  		    (0X42)
#define STEP_TIMESTAMP_L		    (0x49)
#define STEP_TIMESTAMP_H		    (0x4A)
#define STEP_COUNTER_L  		    (0X4B)
#define STEP_COUNTER_H  		    (0X4C)
#define SENSORHUB13_REG  		    (0X4D)
#define SENSORHUB14_REG  		    (0X4E)
#define SENSORHUB15_REG  		    (0X4F)
#define SENSORHUB16_REG  		    (0X50)
#define SENSORHUB17_REG  		    (0X51)
#define SENSORHUB18_REG  		    (0X52)
#define FUNC_SRC1  				      (0X53)
#define FUNC_SRC2  				      (0X54)
#define WRIST_TILT_IA			      (0x55)
#define TAP_CFG  				        (0X58)
#define TAP_THS_6D  			      (0X59)
#define INT_DUR2  				      (0X5A)
#define WAKE_UP_THS  			      (0X5B)
#define WAKE_UP_DUR  			      (0X5C)
#define FREE_FALL  				      (0X5D)
#define MD1_CFG  								(0X5E)
#define MD2_CFG  								(0X5F)
#define MASTER_CMD_CODE					(0x60)
#define INT_OIS 								(0x6F)
#define CTRL1_OIS 							(0x70)
#define CTRL2_OIS 							(0x71)
#define CTRL3_OIS 							(0x72)
#define X_OFS_USR				        (0x73)
#define Y_OFS_USR				        (0x74)
#define Z_OFS_USR				        (0x75)

/* EMBEDDED FUNCTIONS REGISTERS */
#define SLV0_ADD                     	(0x02)
#define SLV0_SUBADD                  	(0x03)
#define SLAVE0_CONFIG                	(0x04)
#define SLV1_ADD                     	(0x05)
#define SLV1_SUBADD                  	(0x06)
#define SLAVE1_CONFIG                	(0x07)
#define SLV2_ADD                     	(0x08)
#define SLV2_SUBADD                  	(0x09)
#define SLAVE2_CONFIG                	(0x0A)
#define SLV3_ADD                     	(0x0B)
#define SLV3_SUBADD                  	(0x0C)
#define SLAVE3_CONFIG                	(0x0D)
#define DATAWRITE_SRC_MODE_SUB_SLV0  	(0x0E)
#define CONFIG_PEDO_THS_MIN          	(0x0F)
#define SM_THS                  			(0x13)
#define PEDO_DEB_REG									(0X14)
#define STEP_COUNT_DELTA							(0x15)
#define MAG_SI_XX                    	(0x24)
#define MAG_SI_XY                    	(0x25)
#define MAG_SI_XZ                    	(0x26)
#define MAG_SI_YX                    	(0x27)
#define MAG_SI_YY                    	(0x28)
#define MAG_SI_YZ                    	(0x29)
#define MAG_SI_ZX                    	(0x2A)
#define MAG_SI_ZY                    	(0x2B)
#define MAG_SI_ZZ                    	(0x2C)
#define MAG_OFFX_L                   	(0x2D)
#define MAG_OFFX_H                   	(0x2E)
#define MAG_OFFY_L                   	(0x2F)
#define MAG_OFFY_H                   	(0x30)
#define MAG_OFFZ_L                   	(0x31)
#define MAG_OFFZ_H                   	(0x32)

/*******************************************************************************
* Register      : FUNC_CFG_ACCESS
* Address       : 0X01
* Bit Group Name: FUNC_CFG_EN_B
* Permission    : RW
*******************************************************************************/
typedef enum {
	FUNC_CFG_EN_B_DISABLED		= 0x00,
	FUNC_CFG_EN_B_ENABLED 		= 0x20,
} FUNC_CFG_EN_B_t;

/*******************************************************************************
* Register      : RAM_ACCESS
* Address       : 0X01
* Bit Group Name: FUNC_CFG_EN
* Permission    : RW
*******************************************************************************/
typedef enum {
	FUNC_CFG_EN_DISABLED 			= 0x00,
	FUNC_CFG_EN_ENABLED 			= 0x80,
} FUNC_CFG_EN_t;

/*******************************************************************************
* Register      : SENSOR_SYNC_TIME_FRAME
* Address       : 0X04
* Bit Group Name: TPH
* Permission    : RW
*******************************************************************************/
#define TPH_MASK  					0xFF
#define TPH_POSITION  			0

/*******************************************************************************
* Register      : SENSOR_SYNC_RES_RATIO
* Address       : 0X05
* Bit Group Name: RR
* Permission    : RW
*******************************************************************************/
typedef enum {
	RR_2_11 		 							= 0x00,
	RR_2_12 		 							= 0x01,
	RR_2_13 		 							= 0x02,
	RR_2_14 		 							= 0x03,
} RR_t;

/*******************************************************************************
* Register      : FIFO_CTRL1
* Address       : 0X06
* Bit Group Name: WTM_FIFO
* Permission    : RW
*******************************************************************************/
#define WTM_FIFO_CTRL1_MASK  		0xFF
#define WTM_FIFO_CTRL1_POSITION 0
#define WTM_FIFO_CTRL2_MASK  		0x07
#define WTM_FIFO_CTRL2_POSITION	0

/*******************************************************************************
* Register      : FIFO_CTRL2
* Address       : 0X07
* Bit Group Name: FIFO_TEMP_EN
* Permission    : RW
*******************************************************************************/
typedef enum {
	FIFO_TEMP_EN_DISABLED			= 0x00,
	FIFO_TEMP_EN_ENABLED			= 0x08,
} FIFO_TEMP_EN_t;

/*******************************************************************************
* Register      : FIFO_CTRL2
* Address       : 0X07
* Bit Group Name: TIM_PEDO_FIFO_DRDY
* Permission    : RW
*******************************************************************************/
typedef enum {
	TIM_PEDO_FIFO_DRDY_DISABLED		= 0x00,
	TIM_PEDO_FIFO_DRDY_ENABLED		= 0x40,
} TIM_PEDO_FIFO_DRDY_t;

/*******************************************************************************
* Register      : FIFO_CTRL2
* Address       : 0X07
* Bit Group Name: TIM_PEDO_FIFO_EN
* Permission    : RW
*******************************************************************************/
typedef enum {
	TIM_PEDO_FIFO_EN_DISABLED = 0x00,
	TIM_PEDO_FIFO_EN_ENABLED	= 0x80,
} TIM_PEDO_FIFO_EN_t;

/*******************************************************************************
* Register      : FIFO_CTRL3
* Address       : 0X08
* Bit Group Name: DEC_FIFO_XL
* Permission    : RW
*******************************************************************************/
typedef enum {
	DEC_FIFO_XL_DATA_NOT_IN_FIFO	= 0x00,
	DEC_FIFO_XL_NO_DECIMATION 	 	= 0x01,
	DEC_FIFO_XL_DECIMATION_BY_2 	= 0x02,
	DEC_FIFO_XL_DECIMATION_BY_3 	= 0x03,
	DEC_FIFO_XL_DECIMATION_BY_4 	= 0x04,
	DEC_FIFO_XL_DECIMATION_BY_8 	= 0x05,
	DEC_FIFO_XL_DECIMATION_BY_16 	= 0x06,
	DEC_FIFO_XL_DECIMATION_BY_32	= 0x07,
} DEC_FIFO_XL_t;

/*******************************************************************************
* Register      : FIFO_CTRL3
* Address       : 0X08
* Bit Group Name: DEC_FIFO_G
* Permission    : RW
*******************************************************************************/
typedef enum {
	DEC_FIFO_G_DATA_NOT_IN_FIFO		= 0x00,
	DEC_FIFO_G_NO_DECIMATION 		  = 0x08,
	DEC_FIFO_G_DECIMATION_BY_2 		= 0x10,
	DEC_FIFO_G_DECIMATION_BY_3 		= 0x18,
	DEC_FIFO_G_DECIMATION_BY_4 		= 0x20,
	DEC_FIFO_G_DECIMATION_BY_8 		= 0x28,
	DEC_FIFO_G_DECIMATION_BY_16 	= 0x30,
	DEC_FIFO_G_DECIMATION_BY_32 	= 0x38,
} DEC_FIFO_G_t;

/*******************************************************************************
* Register      : FIFO_CTRL4
* Address       : 0X09
* Bit Group Name: DEC_DS3_FIFO
* Permission    : RW
*******************************************************************************/
typedef enum {
	DEC_DS3_FIFO_DATA_NOT_IN_FIFO	= 0x00,
	DEC_DS3_FIFO_NO_DECIMATION 		= 0x01,
	DEC_DS3_FIFO_DECIMATION_BY_2 	= 0x02,
	DEC_DS3_FIFO_DECIMATION_BY_3 	= 0x03,
	DEC_DS3_FIFO_DECIMATION_BY_4 	= 0x04,
	DEC_DS3_FIFO_DECIMATION_BY_8 	= 0x05,
	DEC_DS3_FIFO_DECIMATION_BY_16 = 0x06,
	DEC_DS3_FIFO_DECIMATION_BY_32 = 0x07,
} DEC_DS3_FIFO_t;

/*******************************************************************************
* Register      : FIFO_CTRL4
* Address       : 0X09
* Bit Group Name: DEC_DS4_FIFO
* Permission    : RW
*******************************************************************************/
typedef enum {
	DEC_DS4_FIFO_DATA_NOT_IN_FIFO	= 0x00,
	DEC_DS4_FIFO_NO_DECIMATION 		= 0x08,
	DEC_DS4_FIFO_DECIMATION_BY_2 	= 0x10,
	DEC_DS4_FIFO_DECIMATION_BY_3 	= 0x18,
	DEC_DS4_FIFO_DECIMATION_BY_4 	= 0x20,
	DEC_DS4_FIFO_DECIMATION_BY_8 	= 0x28,
	DEC_DS4_FIFO_DECIMATION_BY_16 = 0x30,
	DEC_DS4_FIFO_DECIMATION_BY_32 = 0x38,
} DEC_DS4_FIFO_t;

/*******************************************************************************
* Register      : FIFO_CTRL4
* Address       : 0X09
* Bit Group Name: HI_DATA_ONLY
* Permission    : RW
*******************************************************************************/
typedef enum {
	HI_DATA_ONLY_DISABLED 		= 0x00,
	HI_DATA_ONLY_ENABLED 			= 0x40,
} HI_DATA_ONLY_t;

/*******************************************************************************
* Register      : FIFO_CTRL4
* Address       : 0X09
* Bit Group Name: STOP_ON_FTH
* Permission    : RW
*******************************************************************************/
typedef enum {
	STOP_ON_FTH_DISABLED 			= 0x00,
	STOP_ON_FTH_ENABLED 			= 0x80,
} STOP_ON_FTH_t;

/*******************************************************************************
* Register      : FIFO_CTRL5
* Address       : 0X0A
* Bit Group Name: FIFO_MODE
* Permission    : RW
*******************************************************************************/
typedef enum {
	FIFO_MODE_BYPASS					= 0x00,
	FIFO_MODE_FIFO 						= 0x01,
	FIFO_MODE_RESERVED1				= 0x02,
	FIFO_MODE_CONT_UTD 				= 0x03,
	FIFO_MODE_BYPASS_UTD 			= 0x04,
	FIFO_MODE_RESERVED2 			= 0x05,
	FIFO_MODE_CONT 						= 0x06,
	FIFO_MODE_RESERVED3	 			= 0x07,
} FIFO_MODE_t;

/*******************************************************************************
* Register      : FIFO_CTRL5
* Address       : 0X0A
* Bit Group Name: ODR_FIFO
* Permission    : RW
*******************************************************************************/
typedef enum {
	ODR_FIFO_DISABLED					= 0x00,
	ODR_FIFO_12_5Hz		 				= 0x08,
	ODR_FIFO_26Hz 		 				= 0x10,
	ODR_FIFO_52Hz 		 				= 0x18,
	ODR_FIFO_104Hz 						= 0x20,
	ODR_FIFO_208Hz 						= 0x28,
	ODR_FIFO_416Hz 						= 0x30,
	ODR_FIFO_833Hz 						= 0x38,
	ODR_FIFO_1660Hz 					= 0x40,
	ODR_FIFO_3330Hz 					= 0x48,
	ODR_FIFO_6660Hz 					= 0x50,
} ODR_FIFO_t;

/*******************************************************************************
* Register      : DRDY_PULSE_CFG
* Address       : 0X0B
* Bit Group Name: INT2_WRIST_TILT
* Permission    : RW
*******************************************************************************/
typedef enum {
	INT2_WRIST_TILT_DISABLED	= 0x00,
	INT2_WRIST_TILT_ENABLED		= 0x01,
} INT2_WRIST_TILT_t;

/*******************************************************************************
* Register      : DRDY_PULSE_CFG
* Address       : 0X0B
* Bit Group Name: DRDY_PULSED
* Permission    : RW
*******************************************************************************/
typedef enum {
	DRDY_PULSED_DISABLED			= 0x00,
	DRDY_PULSED_ENABLED				= 0x01,
} DRDY_PULSED_t;

/*******************************************************************************
* Register      : INT1_CTRL
* Address       : 0X0D
* Bit Group Name: INT1_DRDY_XL
* Permission    : RW
*******************************************************************************/
typedef enum {
	INT1_DRDY_XL_DISABLED			= 0x00,
	INT1_DRDY_XL_ENABLED 			= 0x01,
} INT1_DRDY_XL_t;

/*******************************************************************************
* Register      : INT1_CTRL
* Address       : 0X0D
* Bit Group Name: INT1_DRDY_G
* Permission    : RW
*******************************************************************************/
typedef enum {
	INT1_DRDY_G_DISABLED			= 0x00,
	INT1_DRDY_G_ENABLED 			= 0x02,
} INT1_DRDY_G_t;

/*******************************************************************************
* Register      : INT1_CTRL
* Address       : 0X0D
* Bit Group Name: INT1_BOOT
* Permission    : RW
*******************************************************************************/
typedef enum {
	INT1_BOOT_DISABLED				= 0x00,
	INT1_BOOT_ENABLED 				= 0x04,
} INT1_BOOT_t;

/*******************************************************************************
* Register      : INT1_CTRL
* Address       : 0X0D
* Bit Group Name: INT1_FTH
* Permission    : RW
*******************************************************************************/
typedef enum {
	INT1_FTH_DISABLED 				= 0x00,
	INT1_FTH_ENABLED 					= 0x08,
} INT1_FTH_t;

/*******************************************************************************
* Register      : INT1_CTRL
* Address       : 0X0D
* Bit Group Name: INT1_FIFO_OVR
* Permission    : RW
*******************************************************************************/
typedef enum {
	INT1_FIFO_OVR_DISABLED 		= 0x00,
	INT1_FIFO_OVR_ENABLED 		= 0x10,
} INT1_FIFO_OVR_t;

/*******************************************************************************
* Register      : INT1_CTRL
* Address       : 0X0D
* Bit Group Name: INT1_FULL_FLAG
* Permission    : RW
*******************************************************************************/
typedef enum {
	INT1_FULL_FLAG_DISABLED		= 0x00,
	INT1_FULL_FLAG_ENABLED 		= 0x20,
} INT1_FULL_FLAG_t;

/*******************************************************************************
* Register      : INT1_CTRL
* Address       : 0X0D
* Bit Group Name: INT1_SIGN_MOT
* Permission    : RW
*******************************************************************************/
typedef enum {
	INT1_SIGN_MOT_DISABLED 		= 0x00,
	INT1_SIGN_MOT_ENABLED 		= 0x40,
} INT1_SIGN_MOT_t;

/*******************************************************************************
* Register      : INT1_CTRL
* Address       : 0X0D
* Bit Group Name: INT1_STEP_DETECTOR
* Permission    : RW
*******************************************************************************/
typedef enum {
	INT1_STEP_DETECTOR_DISABLED		= 0x00,
	INT1_STEP_DETECTOR_ENABLED 		= 0x80,
} INT1_STEP_DETECTOR_t;

/*******************************************************************************
* Register      : INT2_CTRL
* Address       : 0X0E
* Bit Group Name: INT2_DRDY_XL
* Permission    : RW
*******************************************************************************/
typedef enum {
	INT2_DRDY_XL_DISABLED 		= 0x00,
	INT2_DRDY_XL_ENABLED 			= 0x01,
} INT2_DRDY_XL_t;

/*******************************************************************************
* Register      : INT2_CTRL
* Address       : 0X0E
* Bit Group Name: INT2_DRDY_G
* Permission    : RW
*******************************************************************************/
typedef enum {
	INT2_DRDY_G_DISABLED 			= 0x00,
	INT2_DRDY_G_ENABLED 			= 0x02,
} INT2_DRDY_G_t;

/*******************************************************************************
* Register      : INT2_CTRL
* Address       : 0X0E
* Bit Group Name: INT2_DRDY_TEMP
* Permission    : RW
*******************************************************************************/
typedef enum {
	INT2_DRDY_TEMP_DISABLED		= 0x00,
	INT2_DRDY_TEMP_ENABLED 		= 0x04,
} INT2_DRDY_TEMP_t;

/*******************************************************************************
* Register      : INT2_CTRL
* Address       : 0X0E
* Bit Group Name: INT2_FTH
* Permission    : RW
*******************************************************************************/
typedef enum {
	INT2_FTH_DISABLED 				= 0x00,
	INT2_FTH_ENABLED 					= 0x08,
} INT2_FTH_t;

/*******************************************************************************
* Register      : INT2_CTRL
* Address       : 0X0E
* Bit Group Name: INT2_FIFO_OVR
* Permission    : RW
*******************************************************************************/
typedef enum {
	INT2_FIFO_OVR_DISABLED		= 0x00,
	INT2_FIFO_OVR_ENABLED 		= 0x10,
} INT2_FIFO_OVR_t;

/*******************************************************************************
* Register      : INT2_CTRL
* Address       : 0X0E
* Bit Group Name: INT2_FULL_FLAG
* Permission    : RW
*******************************************************************************/
typedef enum {
	INT2_FULL_FLAG_DISABLED		= 0x00,
	INT2_FULL_FLAG_ENABLED 		= 0x20,
} INT2_FULL_FLAG_t;

/*******************************************************************************
* Register      : INT2_CTRL
* Address       : 0X0E
* Bit Group Name: INT2_STEP_COUNTER_OV
* Permission    : RW
*******************************************************************************/
typedef enum {
	INT2_STEP_COUNTER_OV_DISABLED	= 0x00,
	INT2_STEP_COUNTER_OV_ENABLED	= 0x40,
} INT2_STEP_COUNTER_OV_t;

/*******************************************************************************
* Register      : INT2_CTRL
* Address       : 0X0E
* Bit Group Name: INT2_STEP_DELTA
* Permission    : RW
*******************************************************************************/
typedef enum {
	INT2_STEP_DELTA_DISABLED	= 0x00,
	INT2_STEP_DELTA_ENABLED 	= 0x80,
} INT2_STEP_DELTA_t;

/*******************************************************************************
* Register      : WHO_AM_I
* Address       : 0X0F
* Bit Group Name: WHO_AM_I_BIT
* Permission    : RO
*******************************************************************************/
#define  WHO_AM_I_BIT_MASK  		0xFF
#define  WHO_AM_I_BIT_POSITION  0

/*******************************************************************************
* Register      : CTRL1_XL
* Address       : 0X10
* Bit Group Name: BW0_XL
* Permission    : RW
*******************************************************************************/
typedef enum {
	BW0_XL_1500Hz 		 				= 0x00,
	BW0_XL_400Hz 		 					= 0x01,
} BW0_XL_t;

/*******************************************************************************
* Register      : CTRL1_XL
* Address       : 0X10
* Bit Group Name: LPF1_BW_SEL
* Permission    : RW
*******************************************************************************/
typedef enum {
	LPF1_BW_SEL_ODR_DIV2			= 0x00,
	LPF1_BW_SEL_ODR_DIV4 			= 0x02,
} LPF1_BW_SEL_t;

/*******************************************************************************
* Register      : CTRL1_XL
* Address       : 0X10
* Bit Group Name: FS_XL
* Permission    : RW
*******************************************************************************/
typedef enum {
	FS_XL_2g 		 							= 0x00,
	FS_XL_16g 		 						= 0x04,
	FS_XL_4g 		 							= 0x08,
	FS_XL_8g 		 							= 0x0C,
} FS_XL_t;

/*******************************************************************************
* Register      : CTRL1_XL
* Address       : 0X10
* Bit Group Name: ODR_XL
* Permission    : RW
*******************************************************************************/
typedef enum {
	ODR_XL_POWER_DOWN 				= 0x00,
	ODR_XL_12_5Hz 		    		= 0x10,
	ODR_XL_26Hz 		    			= 0x20,
	ODR_XL_52Hz 		    			= 0x30,
	ODR_XL_104Hz 		 					= 0x40,
	ODR_XL_208Hz 		 					= 0x50,
	ODR_XL_416Hz 		 					= 0x60,
	ODR_XL_833Hz 		 					= 0x70,
	ODR_XL_1660Hz 		 				= 0x80,
	ODR_XL_3330Hz 		 				= 0x90,
	ODR_XL_6660Hz 		 				= 0xA0,
	ODR_XL_1_6Hz 		 					= 0xB0,
	ODR_XL_NA1	 		 					= 0xC0,
	ODR_XL_NA2	 		 					= 0xD0,
	ODR_XL_NA3	 		 					= 0xE0,
	ODR_XL_NA4	 		 					= 0xF0,
} ODR_XL_t;

/*******************************************************************************
* Register      : CTRL2_G
* Address       : 0X11
* Bit Group Name: FS_125
* Permission    : RW
*******************************************************************************/
typedef enum {
	FS_125_DISABLED 					= 0x00,
	FS_125_ENABLED 						= 0x02,
} FS_125_t;

/*******************************************************************************
* Register      : CTRL2_G
* Address       : 0X11
* Bit Group Name: FS_G
* Permission    : RW
*******************************************************************************/
typedef enum {
	FS_G_245dps 		 					= 0x00,
	FS_G_500dps 		 					= 0x04,
	FS_G_1000dps 		 					= 0x08,
	FS_G_2000dps 		 					= 0x0C,
} FS_G_t;

/*******************************************************************************
* Register      : CTRL2_G
* Address       : 0X11
* Bit Group Name: ODR_G
* Permission    : RW
*******************************************************************************/
typedef enum {
	ODR_G_POWER_DOWN 	 				= 0x00,
	ODR_G_13Hz 		 						= 0x10,
	ODR_G_26Hz 		 						= 0x20,
	ODR_G_52Hz 		 						= 0x30,
	ODR_G_104Hz 		 					= 0x40,
	ODR_G_208Hz 		 					= 0x50,
	ODR_G_416Hz 		 					= 0x60,
	ODR_G_833Hz 		 					= 0x70,
	ODR_G_1660Hz 		 					= 0x80,
	ODR_G_3330Hz 		 					= 0x90,
	ODR_G_6660Hz 		 					= 0xA0,
	ODR_G_NA	 		 						= 0xB0,
} ODR_G_t;

/*******************************************************************************
* Register      : CTRL3_C
* Address       : 0X12
* Bit Group Name: SW_RESET
* Permission    : RW
*******************************************************************************/
typedef enum {
	SW_RESET_NORMAL_MODE 			= 0x00,
	SW_RESET_RESET_DEVICE 		= 0x01,
} SW_RESET_t;

/*******************************************************************************
* Register      : CTRL3_C
* Address       : 0X12
* Bit Group Name: BLE
* Permission    : RW
*******************************************************************************/
typedef enum {
	BLE_LSB 		 							= 0x00,
	BLE_MSB 		 							= 0x02,
} BLE_t;

/*******************************************************************************
* Register      : CTRL3_C
* Address       : 0X12
* Bit Group Name: IF_INC
* Permission    : RW
*******************************************************************************/
typedef enum {
	IF_INC_DISABLED 					= 0x00,
	IF_INC_ENABLED 						= 0x04,
} IF_INC_t;

/*******************************************************************************
* Register      : CTRL3_C
* Address       : 0X12
* Bit Group Name: SIM
* Permission    : RW
*******************************************************************************/
typedef enum {
	SIM_4_WIRE 		 						= 0x00,
	SIM_3_WIRE 		 						= 0x08,
} SIM_t;

/*******************************************************************************
* Register      : CTRL3_C
* Address       : 0X12
* Bit Group Name: PP_OD
* Permission    : RW
*******************************************************************************/
typedef enum {
	PP_OD_PUSH_PULL 					= 0x00,
	PP_OD_OPEN_DRAIN 					= 0x10,
} PP_OD_t;

/*******************************************************************************
* Register      : CTRL3_C
* Address       : 0X12
* Bit Group Name: INT_ACT_LEVEL
* Permission    : RW
*******************************************************************************/
typedef enum {
	INT_ACT_LEVEL_ACTIVE_HI 	= 0x00,
	INT_ACT_LEVEL_ACTIVE_LO 	= 0x20,
} INT_ACT_LEVEL_t;

/*******************************************************************************
* Register      : CTRL3_C
* Address       : 0X12
* Bit Group Name: BDU
* Permission    : RW
*******************************************************************************/
typedef enum {
	BDU_CONTINUOS 		 				= 0x00,
	BDU_BLOCK_UPDATE 					= 0x40,
} BDU_t;

/*******************************************************************************
* Register      : CTRL3_C
* Address       : 0X12
* Bit Group Name: BOOT
* Permission    : RW
*******************************************************************************/
typedef enum {
	BOOT_NORMAL_MODE 					= 0x00,
	BOOT_REBOOT_MODE 					= 0x80,
} BOOT_t;

/*******************************************************************************
* Register      : CTRL4_C
* Address       : 0X13
* Bit Group Name: LPF1_SEL_G
* Permission    : RW
*******************************************************************************/
typedef enum {
	LPF1_SEL_G_DISABLED 			= 0x00,
	LPF1_SEL_G_ENABLED 				= 0x02,
} LPF1_SEL_G_t;

/*******************************************************************************
* Register      : CTRL4_C
* Address       : 0X13
* Bit Group Name: I2C_DISABLE
* Permission    : RW
*******************************************************************************/
typedef enum {
	I2C_DISABLE_I2C_AND_SPI		= 0x00,
	I2C_DISABLE_SPI_ONLY 			= 0x04,
} I2C_DISABLE_t;

/*******************************************************************************
* Register      : CTRL4_C
* Address       : 0X13
* Bit Group Name: DRDY_MSK
* Permission    : RW
*******************************************************************************/
typedef enum {
	DRDY_MSK_DISABLED 				= 0x00,
	DRDY_MSK_ENABLED 					= 0x08,
} DRDY_MSK_t;

/*******************************************************************************
* Register      : CTRL4_C
* Address       : 0X13
* Bit Group Name: DEN_DRDY_INT1
* Permission    : RW
*******************************************************************************/
typedef enum {
	DEN_DRDY_INT1_DISABLED		= 0x00,
	DEN_DRDY_INT1_ENABLED 		= 0x10,
} DEN_DRDY_INT1_t;

/*******************************************************************************
* Register      : CTRL4_C
* Address       : 0X13
* Bit Group Name: INT2_ON_INT1
* Permission    : RW
*******************************************************************************/
typedef enum {
	INT2_ON_INT1_DISABLED 		= 0x00,
	INT2_ON_INT1_ENABLED 			= 0x20,
} INT2_ON_INT1_t;

/*******************************************************************************
* Register      : CTRL4_C
* Address       : 0X13
* Bit Group Name: SLEEP_G
* Permission    : RW
*******************************************************************************/
typedef enum {
	SLEEP_G_DISABLED 					= 0x00,
	SLEEP_G_ENABLED 					= 0x40,
} SLEEP_G_t;

/*******************************************************************************
* Register      : CTRL4_C
* Address       : 0X13
* Bit Group Name: DEN_XL_EN
* Permission    : RW
*******************************************************************************/
typedef enum {
	DEN_XL_EN_DISABLED 				= 0x00,
	DEN_XL_EN_ENABLED 				= 0x80,
} DEN_XL_EN_t;

/*******************************************************************************
* Register      : CTRL5_C
* Address       : 0X14
* Bit Group Name: ST_XL
* Permission    : RW
*******************************************************************************/
typedef enum {
	ST_XL_NORMAL_MODE 				= 0x00,
	ST_XL_POS_SIGN_TEST 			= 0x01,
	ST_XL_NEG_SIGN_TEST 			= 0x02,
	ST_XL_NA 		 							= 0x03,
} ST_XL_t;

/*******************************************************************************
* Register      : CTRL5_C
* Address       : 0X14
* Bit Group Name: ST_G
* Permission    : RW
*******************************************************************************/
typedef enum {
	ST_G_NORMAL_MODE 					= 0x00,
	ST_G_POS_SIGN_TEST 				= 0x04,
	ST_G_NA 		 							= 0x08,
	ST_G_NEG_SIGN_TEST 				= 0x0C,
} ST_G_t;

/*******************************************************************************
* Register      : CTRL5_C
* Address       : 0X14
* Bit Group Name: DEN_LH
* Permission    : RW
*******************************************************************************/
typedef enum {
	DEN_LH_ACTIVE_LOW 				= 0x00,
	DEN_LH_ACTIVE_HIGH 				= 0x10,
} DEN_LH_t;

/*******************************************************************************
* Register      : CTRL5_C
* Address       : 0X14
* Bit Group Name: ROUNDING
* Permission    : RW
*******************************************************************************/
typedef enum {
	ROUNDING_NO_ROUNDING					= 0x00,
	ROUNDING_ACC_ONLY							= 0x20,
	ROUNDING_GYRO_ONLY						= 0x40,
	ROUNDING_GYRO_ACC							= 0x60,
	ROUNDING_SH1_SH6							= 0x80,
	ROUNDING_ACC_SH1_SH6					= 0xA0,
	ROUNDING_GYRO_ACC_SH1_SH12		= 0xC0,
	ROUNDING_GYRO_ACC_SH1_SH6			= 0xE0,
} ROUNDING_t;

/*******************************************************************************
* Register      : CTRL6_C
* Address       : 0X15
* Bit Group Name: FTYPE
* Permission    : RW
*******************************************************************************/
typedef enum {
	FTYPE_00 									= 0x00,
	FTYPE_01 		 							= 0x01,
	FTYPE_10 									= 0x10,
	FTYPE_11 									= 0x11,
} FTYPE_t;

/*******************************************************************************
* Register      : CTRL6_C
* Address       : 0X15
* Bit Group Name: USR_OFF_W
* Permission    : RW
*******************************************************************************/
typedef enum {
	USR_OFF_W_2g_LSB 					= 0x00,
	USR_OFF_W_10g_LSB 				= 0x80,
} USR_OFF_W_t;

/*******************************************************************************
* Register      : CTRL6_C
* Address       : 0X15
* Bit Group Name: XL_HM_MODE
* Permission    : RW
*******************************************************************************/
typedef enum {
	XL_HM_MODE_DISABLED 			= 0x00,
	XL_HM_MODE_ENABLED 				= 0x10,
} XL_HM_MODE_t;

/*******************************************************************************
* Register      : CTRL6_C
* Address       : 0X15
* Bit Group Name: TRIG_MODE
* Permission    : RW
*******************************************************************************/
typedef enum {
	TRIG_MODE_LEVEL_SENS					= 0x40,
	TRIG_MODE_LEVEL_SENS_LATCHED	= 0x60,
	TRIG_MODE_EDGE_SENS						= 0x80,
	TRIG_MODE_LEVEL_SENS_FIFO_EN	= 0xC0,
} TRIG_MODE_t;

/*******************************************************************************
* Register      : CTRL7_G
* Address       : 0X16
* Bit Group Name: ROUNDING_STATUS
* Permission    : RW
*******************************************************************************/
typedef enum {
	ROUNDING_STATUS_DISABLED	= 0x00,
	ROUNDING_STATUS_ENABLED	 	= 0x04,
} ROUNDING_STATUS_t;

/*******************************************************************************
* Register      : CTRL7_G
* Address       : 0X16
* Bit Group Name: HPM_G
* Permission    : RW
*******************************************************************************/
typedef enum {
	HPM_G_16mHz 							= 0x00,
	HPM_G_65mHz		 						= 0x10,
	HPM_G_260mHz 							= 0x20,
	HPM_G_1040mHz							= 0x30,
} HPM_G_t;

/*******************************************************************************
* Register      : CTRL7_G
* Address       : 0X16
* Bit Group Name: HP_EN_G
* Permission    : RW
*******************************************************************************/
typedef enum {
	HP_EN_G_DISABLED 					= 0x00,
	HP_EN_G_ENABLED 		 			= 0x40,
} HP_EN_G_t;

/*******************************************************************************
* Register      : CTRL7_G
* Address       : 0X16
* Bit Group Name: G_HM_MODE
* Permission    : RW
*******************************************************************************/
typedef enum {
	G_HM_MODE_DISABLED 				= 0x00,
	G_HM_MODE_ENABLED 				= 0x80,
} G_HM_MODE_t;

/*******************************************************************************
* Register      : CTRL8_XL
* Address       : 0X17
* Bit Group Name: LOW_PASS_ON_6D
* Permission    : RW
*******************************************************************************/
typedef enum {
	LOW_PASS_ON_6D_DISABLED		= 0x00,
	LOW_PASS_ON_6D_ENABLED 		= 0x01,
} LOW_PASS_ON_6D_t;

/*******************************************************************************
* Register      : CTRL8_XL
* Address       : 0X17
* Bit Group Name: HP_SLOPE_XL_EN
* Permission    : RW
*******************************************************************************/
typedef enum {
	HP_SLOPE_XL_EN_DISABLED		= 0x00,
	HP_SLOPE_XL_EN_ENABLED 		= 0x04,
} HP_SLOPE_XL_EN_t;

/*******************************************************************************
* Register      : CTRL8_XL
* Address       : 0X17
* Bit Group Name: INPUT_COMPOSITE
* Permission    : RW
*******************************************************************************/
typedef enum {
	INPUT_COMPOSITE_ODR_DIV2	= 0x00,
	INPUT_COMPOSITE_ODR_DIV4 	= 0x80,
} INPUT_COMPOSITE_t;

/*******************************************************************************
* Register      : CTRL8_XL
* Address       : 0X17
* Bit Group Name: HP_REF_MODE
* Permission    : RW
*******************************************************************************/
typedef enum {
	HP_REF_MODE_DISABLED			= 0x00,
	HP_REF_MODE_ENABLED 			= 0x10,
} HP_REF_MODE_t;

/*******************************************************************************
* Register      : CTRL8_XL
* Address       : 0X17
* Bit Group Name: HPCF_XL
* Permission    : RW
*******************************************************************************/
typedef enum {
	HPCF_XL_00								= 0x00,
	HPCF_XL_01 								= 0x20,
	HPCF_XL_10 								= 0x40,
	HPCF_XL_11								= 0x60,
} HPCF_XL_t;

/*******************************************************************************
* Register      : CTRL8_XL
* Address       : 0X17
* Bit Group Name: LPF2_XL_EN
* Permission    : RW
*******************************************************************************/
typedef enum {
	LPF2_XL_EN_DISABLED				= 0x00,
	LPF2_XL_EN_ENABLED 				= 0x80,
} LPF2_XL_EN_t;

/*******************************************************************************
* Register      : CTRL9_XL
* Address       : 0X18
* Bit Group Name: SOFT_EN
* Permission    : RW
*******************************************************************************/
typedef enum {
	SOFT_EN_DISABLED					= 0x00,
	SOFT_EN_ENABLED 					= 0x40,
} SOFT_EN_t;

/*******************************************************************************
* Register      : CTRL9_XL
* Address       : 0X18
* Bit Group Name: DEN_XL_G
* Permission    : RW
*******************************************************************************/
typedef enum {
	DEN_XL_G_GYRO							= 0x00,
	DEN_XL_G_ACC 							= 0x10,
} YEN_XL_t;

/*******************************************************************************
* Register      : CTRL9_XL
* Address       : 0X18
* Bit Group Name: DEN_Z
* Permission    : RW
*******************************************************************************/
typedef enum {
	DEN_Z_NOT_STORED_IN_Z_AXIS		= 0x00,
	DEN_Z_STORED_IN_Z_AXIS				= 0x20,		
} DEN_Z_t;

/*******************************************************************************
* Register      : CTRL9_XL
* Address       : 0X18
* Bit Group Name: DEN_Y
* Permission    : RW
*******************************************************************************/
typedef enum {
	DEN_Y_NOT_STORED_IN_Y_AXIS		= 0x00,
	DEN_Y_STORED_IN_Y_AXIS				= 0x40,		
} DEN_Y_t;

/*******************************************************************************
* Register      : CTRL9_XL
* Address       : 0X18
* Bit Group Name: DEN_X
* Permission    : RW
*******************************************************************************/
typedef enum {
	DEN_X_NOT_STORED_IN_X_AXIS		= 0x00,
	DEN_X_STORED_IN_X_AXIS				= 0x80,		
} DEN_X_t;

/*******************************************************************************
* Register      : CTRL10_C
* Address       : 0X19
* Bit Group Name: SIGN_MOTION_EN
* Permission    : RW
*******************************************************************************/
typedef enum {
	SIGN_MOTION_EN_DISABLED 	= 0x00,
	SIGN_MOTION_EN_ENABLED 		= 0x01,
} SIGN_MOTION_EN_t;

/*******************************************************************************
* Register      : CTRL10_C
* Address       : 0X19
* Bit Group Name: PEDO_RST_STEP
* Permission    : RW
*******************************************************************************/
typedef enum {
	PEDO_RST_STEP_DISABLED 		= 0x00,
	PEDO_RST_STEP_ENABLED 		= 0x02,
} PEDO_RST_STEP_t;

/*******************************************************************************
* Register      : CTRL10_C
* Address       : 0X19
* Bit Group Name: FUNC_EN
* Permission    : RW
*******************************************************************************/
typedef enum {
	FUNC_EN_DISABLED 					= 0x00,
	FUNC_EN_ENABLED 					= 0x04,
} FUNC_EN_t;

/*******************************************************************************
* Register      : CTRL10_C
* Address       : 0X19
* Bit Group Name: TILT_EN
* Permission    : RW
*******************************************************************************/
typedef enum {
	TILT_EN_DISABLED 					= 0x00,
	TILT_EN_ENABLED 					= 0x80,
} TILT_EN_t;

/*******************************************************************************
* Register      : CTRL10_C
* Address       : 0X19
* Bit Group Name: PEDO_EN
* Permission    : RW
*******************************************************************************/
typedef enum {
	PEDO_EN_DISABLED 					= 0x00,
	PEDO_EN_ENABLED 					= 0x10,
} PEDO_EN_t;

/*******************************************************************************
* Register      : CTRL10_C
* Address       : 0X19
* Bit Group Name: TIMER_EN
* Permission    : RW
*******************************************************************************/
typedef enum {
	TIMER_EN_DISABLED 				= 0x00,
	TIMER_EN_ENABLED 					= 0x40,
} TIMER_EN_t;

/*******************************************************************************
* Register      : CTRL10_C
* Address       : 0X19
* Bit Group Name: WRIST_TILT_EN
* Permission    : RW
*******************************************************************************/
typedef enum {
	WRIST_TILT_EN_DISABLED 		= 0x00,
	WRIST_TILT_EN_ENABLED 		= 0x80,
} WRIST_TILT_EN_t;

/*******************************************************************************
* Register      : MASTER_CONFIG
* Address       : 0X1A
* Bit Group Name: MASTER_ON
* Permission    : RW
*******************************************************************************/
typedef enum {
	MASTER_ON_DISABLED 				= 0x00,
	MASTER_ON_ENABLED 				= 0x01,
} MASTER_ON_t;

/*******************************************************************************
* Register      : MASTER_CONFIG
* Address       : 0X1A
* Bit Group Name: IRON_EN
* Permission    : RW
*******************************************************************************/
typedef enum {
	IRON_EN_DISABLED 					= 0x00,
	IRON_EN_ENABLED 					= 0x02,
} IRON_EN_t;

/*******************************************************************************
* Register      : MASTER_CONFIG
* Address       : 0X1A
* Bit Group Name: PASS_THRU_MODE
* Permission    : RW
*******************************************************************************/
typedef enum {
	PASS_THRU_MODE_DISABLED		= 0x00,
	PASS_THRU_MODE_ENABLED 		= 0x04,
} PASS_THRU_MODE_t;

/*******************************************************************************
* Register      : MASTER_CONFIG
* Address       : 0X1A
* Bit Group Name: PULL_UP_EN
* Permission    : RW
*******************************************************************************/
typedef enum {
	PULL_UP_EN_DISABLED				= 0x00,
	PULL_UP_EN_ENABLED 				= 0x08,
} PULL_UP_EN_t;

/*******************************************************************************
* Register      : MASTER_CONFIG
* Address       : 0X1A
* Bit Group Name: START_CONFIG
* Permission    : RW
*******************************************************************************/
typedef enum {
	START_CONFIG_XL_G_DRDY 		= 0x00,
	START_CONFIG_EXT_INT2 		= 0x10,
} START_CONFIG_t;

/*******************************************************************************
* Register      : MASTER_CONFIG
* Address       : 0X1A
* Bit Group Name: DATA_VAL_SEL_FIFO
* Permission    : RW
*******************************************************************************/
typedef enum {
	DATA_VAL_SEL_FIFO_XL_G_DRDY		= 0x00,
	DATA_VAL_SEL_FIFO_SHUB_DRDY 	= 0x40,
} DATA_VAL_SEL_FIFO_t;

/*******************************************************************************
* Register      : MASTER_CONFIG
* Address       : 0X1A
* Bit Group Name: DRDY_ON_INT1
* Permission    : RW
*******************************************************************************/
typedef enum {
	DRDY_ON_INT1_DISABLED 		= 0x00,
	DRDY_ON_INT1_ENABLED 			= 0x80,
} DRDY_ON_INT1_t;

/*******************************************************************************
* Register      : WAKE_UP_SRC
* Address       : 0X1B
* Bit Group Name: Z_WU
* Permission    : RO
*******************************************************************************/
typedef enum {
	Z_WU_NOT_DETECTED 				= 0x00,
	Z_WU_DETECTED 		 				= 0x01,
} Z_WU_t;

/*******************************************************************************
* Register      : WAKE_UP_SRC
* Address       : 0X1B
* Bit Group Name: Y_WU
* Permission    : RO
*******************************************************************************/
typedef enum {
	Y_WU_NOT_DETECTED 				= 0x00,
	Y_WU_DETECTED 		 				= 0x02,
} Y_WU_t;

/*******************************************************************************
* Register      : WAKE_UP_SRC
* Address       : 0X1B
* Bit Group Name: X_WU
* Permission    : RO
*******************************************************************************/
typedef enum {
	X_WU_NOT_DETECTED 				= 0x00,
	X_WU_DETECTED 		 				= 0x04,
} X_WU_t;

/*******************************************************************************
* Register      : WAKE_UP_SRC
* Address       : 0X1B
* Bit Group Name: WU_EV_STATUS
* Permission    : RO
*******************************************************************************/
typedef enum {
	WU_EV_STATUS_NOT_DETECTED = 0x00,
	WU_EV_STATUS_DETECTED 		= 0x08,
} WU_EV_STATUS_t;

/*******************************************************************************
* Register      : WAKE_UP_SRC
* Address       : 0X1B
* Bit Group Name: SLEEP_EV_STATUS
* Permission    : RO
*******************************************************************************/
typedef enum {
	SLEEP_EV_STATUS_NOT_DETECTED 	= 0x00,
	SLEEP_EV_STATUS_DETECTED 			= 0x10,
} SLEEP_EV_STATUS_t;

/*******************************************************************************
* Register      : WAKE_UP_SRC
* Address       : 0X1B
* Bit Group Name: FF_EV_STATUS
* Permission    : RO
*******************************************************************************/
typedef enum {
	FF_EV_STATUS_NOT_DETECTED	= 0x00,
	FF_EV_STATUS_DETECTED 		= 0x20,
} FF_EV_STATUS_t;

/*******************************************************************************
* Register      : TAP_SRC
* Address       : 0X1C
* Bit Group Name: Z_TAP
* Permission    : RO
*******************************************************************************/
typedef enum {
	Z_TAP_NOT_DETECTED 				= 0x00,
	Z_TAP_DETECTED 						= 0x01,
} Z_TAP_t;

/*******************************************************************************
* Register      : TAP_SRC
* Address       : 0X1C
* Bit Group Name: Y_TAP
* Permission    : RO
*******************************************************************************/
typedef enum {
	Y_TAP_NOT_DETECTED 				= 0x00,
	Y_TAP_DETECTED 						= 0x02,
} Y_TAP_t;

/*******************************************************************************
* Register      : TAP_SRC
* Address       : 0X1C
* Bit Group Name: X_TAP
* Permission    : RO
*******************************************************************************/
typedef enum {
	X_TAP_NOT_DETECTED 				= 0x00,
	X_TAP_DETECTED 						= 0x04,
} X_TAP_t;

/*******************************************************************************
* Register      : TAP_SRC
* Address       : 0X1C
* Bit Group Name: TAP_SIGN
* Permission    : RO
*******************************************************************************/
typedef enum {
	TAP_SIGN_POS_SIGN 				= 0x00,
	TAP_SIGN_NEG_SIGN 				= 0x08,
} TAP_SIGN_t;

/*******************************************************************************
* Register      : TAP_SRC
* Address       : 0X1C
* Bit Group Name: DOUBLE_TAP_EV_STATUS
* Permission    : RO
*******************************************************************************/
typedef enum {
	DOUBLE_TAP_EV_STATUS_NOT_DETECTED = 0x00,
	DOUBLE_TAP_EV_STATUS_DETECTED 		= 0x10,
} DOUBLE_TAP_EV_STATUS_t;

/*******************************************************************************
* Register      : TAP_SRC
* Address       : 0X1C
* Bit Group Name: SINGLE_TAP_EV_STATUS
* Permission    : RO
*******************************************************************************/
typedef enum {
	SINGLE_TAP_EV_STATUS_NOT_DETECTED = 0x00,
	SINGLE_TAP_EV_STATUS_DETECTED 		= 0x20,
} SINGLE_TAP_EV_STATUS_t;

/*******************************************************************************
* Register      : TAP_SRC
* Address       : 0X1C
* Bit Group Name: TAP_EV_STATUS
* Permission    : RO
*******************************************************************************/
typedef enum {
	TAP_EV_STATUS_NOT_DETECTED 		= 0x00,
	TAP_EV_STATUS_DETECTED 				= 0x40,
} TAP_EV_STATUS_t;

/*******************************************************************************
* Register      : D6D_SRC
* Address       : 0X1D
* Bit Group Name: DSD_XL
* Permission    : RO
*******************************************************************************/
typedef enum {
	DSD_XL_NOT_DETECTED 			= 0x00,
	DSD_XL_DETECTED 					= 0x01,
} DSD_XL_t;

/*******************************************************************************
* Register      : D6D_SRC
* Address       : 0X1D
* Bit Group Name: DSD_XH
* Permission    : RO
*******************************************************************************/
typedef enum {
	DSD_XH_NOT_DETECTED 			= 0x00,
	DSD_XH_DETECTED 					= 0x02,
} DSD_XH_t;

/*******************************************************************************
* Register      : D6D_SRC
* Address       : 0X1D
* Bit Group Name: DSD_YL
* Permission    : RO
*******************************************************************************/
typedef enum {
	DSD_YL_NOT_DETECTED 			= 0x00,
	DSD_YL_DETECTED 					= 0x04,
} DSD_YL_t;

/*******************************************************************************
* Register      : D6D_SRC
* Address       : 0X1D
* Bit Group Name: DSD_YH
* Permission    : RO
*******************************************************************************/
typedef enum {
	DSD_YH_NOT_DETECTED 			= 0x00,
	DSD_YH_DETECTED 					= 0x08,
} DSD_YH_t;

/*******************************************************************************
* Register      : D6D_SRC
* Address       : 0X1D
* Bit Group Name: DSD_ZL
* Permission    : RO
*******************************************************************************/
typedef enum {
	DSD_ZL_NOT_DETECTED 			= 0x00,
	DSD_ZL_DETECTED 					= 0x10,
} DSD_ZL_t;

/*******************************************************************************
* Register      : D6D_SRC
* Address       : 0X1D
* Bit Group Name: DSD_ZH
* Permission    : RO
*******************************************************************************/
typedef enum {
	DSD_ZH_NOT_DETECTED 			= 0x00,
	DSD_ZH_DETECTED 					= 0x20,
} DSD_ZH_t;

/*******************************************************************************
* Register      : D6D_SRC
* Address       : 0X1D
* Bit Group Name: D6D_EV_STATUS
* Permission    : RO
*******************************************************************************/
typedef enum {
	D6D_EV_STATUS_NOT_DETECTED		= 0x00,
	D6D_EV_STATUS_DETECTED 				= 0x40,
} D6D_EV_STATUS_t;

/*******************************************************************************
* Register      : D6D_SRC
* Address       : 0X1D
* Bit Group Name: DEN_DRDY
* Permission    : RO
*******************************************************************************/
typedef enum {
	DEN_DRDY_ACTIVE						= 0x00,
	DEN_DRDY_NOT_ACTIVE				= 0x80,
} DEN_DRDY_t;

/*******************************************************************************
* Register      : STATUS_REG
* Address       : 0X1E
* Bit Group Name: XLDA
* Permission    : RO
*******************************************************************************/
typedef enum {
	XLDA_NO_DATA_AVAIL 				= 0x00,
	XLDA_DATA_AVAIL 					= 0x01,
} XLDA_t;

/*******************************************************************************
* Register      : STATUS_REG
* Address       : 0X1E
* Bit Group Name: GDA
* Permission    : RO
*******************************************************************************/
typedef enum {
	GDA_NO_DATA_AVAIL 				= 0x00,
	GDA_DATA_AVAIL 						= 0x02,
} GDA_t;

/*******************************************************************************
* Register      : STATUS_REG
* Address       : 0X1E
* Bit Group Name: TDA
* Permission    : RO
*******************************************************************************/
typedef enum {
	TDA_NO_DATA_AVAIL 				= 0x00,
	TDA_DATA_AVAIL 						= 0x04,
} TDA_t;

/*******************************************************************************
* Register      : FIFO_STATUS1
* Address       : 0X3A
* Bit Group Name: DIFF_FIFO
* Permission    : RO
*******************************************************************************/
#define DIFF_FIFO_STATUS1_MASK  		0xFF
#define DIFF_FIFO_STATUS1_POSITION  0
#define DIFF_FIFO_STATUS2_MASK  		0x07
#define DIFF_FIFO_STATUS2_POSITION	0

/*******************************************************************************
* Register      : FIFO_STATUS2
* Address       : 0X3B
* Bit Group Name: FIFO_EMPTY
* Permission    : RO
*******************************************************************************/
typedef enum {
	FIFO_EMPTY_FIFO_NOT_EMPTY = 0x00,
	FIFO_EMPTY_FIFO_EMPTY 		= 0x10,
} FIFO_EMPTY_t;

/*******************************************************************************
* Register      : FIFO_STATUS2
* Address       : 0X3B
* Bit Group Name: FIFO_FULL
* Permission    : RO
*******************************************************************************/
typedef enum {
	FIFO_FULL_FIFO_NOT_FULL 	= 0x00,
	FIFO_FULL_FIFO_FULL 			= 0x20,
} FIFO_FULL_t;

/*******************************************************************************
* Register      : FIFO_STATUS2
* Address       : 0X3B
* Bit Group Name: OVERRUN
* Permission    : RO
*******************************************************************************/
typedef enum {
	OVERRUN_NO_OVERRUN 				= 0x00,
	OVERRUN_OVERRUN 					= 0x40,
} OVERRUN_t;

/*******************************************************************************
* Register      : FIFO_STATUS2
* Address       : 0X3B
* Bit Group Name: WTM
* Permission    : RO
*******************************************************************************/
typedef enum {
	WTM_BELOW_WTM 		 				= 0x00,
	WTM_ABOVE_OR_EQUAL_WTM 		= 0x80,
} WTM_t;

/*******************************************************************************
* Register      : FIFO_STATUS3
* Address       : 0X3C
* Bit Group Name: FIFO_PATTERN
* Permission    : RO
*******************************************************************************/
#define FIFO_STATUS3_PATTERN_MASK  			0xFF
#define FIFO_STATUS3_PATTERN_POSITION 	0
#define FIFO_STATUS4_PATTERN_MASK  			0x03
#define FIFO_STATUS4_PATTERN_POSITION 	0

/*******************************************************************************
* Register      : FUNC_SRC1
* Address       : 0X53
* Bit Group Name: SENS_HUB_END
* Permission    : RO
*******************************************************************************/
typedef enum {
	SENS_HUB_END_STILL_ONGOING		= 0x00,
	SENS_HUB_END_OP_COMPLETED 		= 0x01,
} SENS_HUB_END_t;

/*******************************************************************************
* Register      : FUNC_SRC1
* Address       : 0X53
* Bit Group Name: SOFT_IRON_END
* Permission    : RO
*******************************************************************************/
typedef enum {
	SOFT_IRON_END_NOT_COMPLETED		= 0x00,
	SOFT_IRON_END_COMPLETED 			= 0x02,
} SOFT_IRON_END_t;

/*******************************************************************************
* Register      : FUNC_SRC1
* Address       : 0X53
* Bit Group Name: HI_FAIL
* Permission    : RO
*******************************************************************************/
typedef enum {
	HIA_NOT_FAILED						= 0x00,
	HIA_FAILED 								= 0x04,
} HIA_t;

/*******************************************************************************
* Register      : FUNC_SRC1
* Address       : 0X53
* Bit Group Name: STEP_OVERFLOW
* Permission    : RO
*******************************************************************************/
typedef enum {
	STEP_OVERFLOW_UNDER_THRES			= 0x00,
	STEP_OVERFLOW_REACHED_THRESH	= 0x08,
} STEP_OVERFLOW_t;

/*******************************************************************************
* Register      : FUNC_SRC1
* Address       : 0X53
* Bit Group Name: STEP_EV_STATUS
* Permission    : RO
*******************************************************************************/
typedef enum {
	STEP_EV_STATUS_NOT_DETECTED 	= 0x00,
	STEP_EV_STATUS_DETECTED 			= 0x10,
} PEDO_EV_STATUS_t;

/*******************************************************************************
* Register      : FUNC_SRC1
* Address       : 0X53
* Bit Group Name: TILT_EV_STATUS
* Permission    : RO
*******************************************************************************/
typedef enum {
	TILT_EV_STATUS_NOT_DETECTED 	= 0x00,
	TILT_EV_STATUS_DETECTED 			= 0x20,
} TILT_EV_STATUS_t;

/*******************************************************************************
* Register      : FUNC_SRC1
* Address       : 0X53
* Bit Group Name: SIGN_MOT_EV_STATUS
* Permission    : RO
*******************************************************************************/
typedef enum {
	SIGN_MOT_EV_STATUS_NOT_DETECTED 	= 0x00,
	SIGN_MOT_EV_STATUS_DETECTED 			= 0x40,
} SIGN_MOT_EV_STATUS_t;

/*******************************************************************************
* Register      : FUNC_SRC1
* Address       : 0X53
* Bit Group Name: STEP_COUNT_DELTA_EV_STATUS
* Permission    : RO
*******************************************************************************/
typedef enum {
	STEP_COUNT_DELTA_EV_STATUS_NOT_DETECTED 	= 0x00,
	STEP_COUNT_DELTA_EV_STATUS_DETECTED 			= 0x40,
} STEP_COUNT_DELTA_EV_STATUS_t;

/*******************************************************************************
* Register      : FUNC_SRC2
* Address       : 0X54
* Bit Group Name: WRIST_TILT_EV_STATUS
* Permission    : RO
*******************************************************************************/
typedef enum {
	WRIST_TILT_EV_STATUS_NOT_DETECTED	= 0x00,
	WRIST_TILT_EV_STATUS_DETECTED 		= 0x01,
} WRIST_TILT_EV_STATUS_t;

/*******************************************************************************
* Register      : FUNC_SRC2
* Address       : 0X54
* Bit Group Name: SLAVE0_NACK
* Permission    : RO
*******************************************************************************/
typedef enum {
	SLAVE0_NACK_NOT_OCCURED		= 0x00,
	SLAVE0_NACK_OCCURED 			= 0x08,
} SLAVE0_NACK_t;

/*******************************************************************************
* Register      : FUNC_SRC2
* Address       : 0X54
* Bit Group Name: SLAVE1_NACK
* Permission    : RO
*******************************************************************************/
typedef enum {
	SLAVE1_NACK_NOT_OCCURED		= 0x00,
	SLAVE1_NACK_OCCURED 			= 0x10,
} SLAVE1_NACK_t;

/*******************************************************************************
* Register      : FUNC_SRC2
* Address       : 0X54
* Bit Group Name: SLAVE2_NACK
* Permission    : RO
*******************************************************************************/
typedef enum {
	SLAVE2_NACK_NOT_OCCURED		= 0x00,
	SLAVE2_NACK_OCCURED 			= 0x20,
} SLAVE2_NACK_t;

/*******************************************************************************
* Register      : FUNC_SRC2
* Address       : 0X54
* Bit Group Name: SLAVE3_NACK
* Permission    : RO
*******************************************************************************/
typedef enum {
	SLAVE3_NACK_NOT_OCCURED		= 0x00,
	SLAVE3_NACK_OCCURED 			= 0x40,
} SLAVE3_NACK_t;

/*******************************************************************************
* Register      : WRIST_TILT_IA
* Address       : 0X55
* Bit Group Name: WRIST_TILT_IA_Zneg_EV_STATUS
* Permission    : RO
*******************************************************************************/
typedef enum {
	WRIST_TILT_IA_Zneg_EV_STATUS_NOT_DETECTED	= 0x00,
	WRIST_TILT_IA_Zneg_EV_STATUS_DETECTED 		= 0x04,
} WRIST_TILT_IA_Zneg_EV_STATUS_t;

/*******************************************************************************
* Register      : WRIST_TILT_IA
* Address       : 0X55
* Bit Group Name: WRIST_TILT_IA_Zpos_EV_STATUS
* Permission    : RO
*******************************************************************************/
typedef enum {
	WRIST_TILT_IA_Zpos_EV_STATUS_NOT_DETECTED	= 0x00,
	WRIST_TILT_IA_Zpos_EV_STATUS_DETECTED 		= 0x08,
} WRIST_TILT_IA_Zpos_EV_STATUS_t;

/*******************************************************************************
* Register      : WRIST_TILT_IA
* Address       : 0X55
* Bit Group Name: WRIST_TILT_IA_Yneg_EV_STATUS
* Permission    : RO
*******************************************************************************/
typedef enum {
	WRIST_TILT_IA_Yneg_EV_STATUS_NOT_DETECTED	= 0x00,
	WRIST_TILT_IA_Yneg_EV_STATUS_DETECTED 		= 0x10,
} WRIST_TILT_IA_Yneg_EV_STATUS_t;

/*******************************************************************************
* Register      : WRIST_TILT_IA
* Address       : 0X55
* Bit Group Name: WRIST_TILT_IA_Ypos_EV_STATUS
* Permission    : RO
*******************************************************************************/
typedef enum {
	WRIST_TILT_IA_Ypos_EV_STATUS_NOT_DETECTED	= 0x00,
	WRIST_TILT_IA_Ypos_EV_STATUS_DETECTED 		= 0x20,
} WRIST_TILT_IA_Ypos_EV_STATUS_t;

/*******************************************************************************
* Register      : WRIST_TILT_IA
* Address       : 0X55
* Bit Group Name: WRIST_TILT_IA_Xneg_EV_STATUS
* Permission    : RO
*******************************************************************************/
typedef enum {
	WRIST_TILT_IA_Xneg_EV_STATUS_NOT_DETECTED	= 0x00,
	WRIST_TILT_IA_Xneg_EV_STATUS_DETECTED 		= 0x40,
} WRIST_TILT_IA_Xneg_EV_STATUS_t;

/*******************************************************************************
* Register      : WRIST_TILT_IA
* Address       : 0X55
* Bit Group Name: WRIST_TILT_IA_Xpos_EV_STATUS
* Permission    : RO
*******************************************************************************/
typedef enum {
	WRIST_TILT_IA_Xpos_EV_STATUS_NOT_DETECTED	= 0x00,
	WRIST_TILT_IA_Xpos_EV_STATUS_DETECTED 		= 0x80,
} WRIST_TILT_IA_Xpos_EV_STATUS_t;

/*******************************************************************************
* Register      : TAP_CFG1
* Address       : 0X58
* Bit Group Name: LIR
* Permission    : RW
*******************************************************************************/
typedef enum {
	LIR_DISABLED 							= 0x00,
	LIR_ENABLED 							= 0x01,
} LIR_t;

/*******************************************************************************
* Register      : TAP_CFG1
* Address       : 0X58
* Bit Group Name: TAP_Z_EN
* Permission    : RW
*******************************************************************************/
typedef enum {
	TAP_Z_EN_DISABLED 				= 0x00,
	TAP_Z_EN_ENABLED 					= 0x02,
} TAP_Z_EN_t;

/*******************************************************************************
* Register      : TAP_CFG1
* Address       : 0X58
* Bit Group Name: TAP_Y_EN
* Permission    : RW
*******************************************************************************/
typedef enum {
	TAP_Y_EN_DISABLED 				= 0x00,
	TAP_Y_EN_ENABLED 					= 0x04,
} TAP_Y_EN_t;

/*******************************************************************************
* Register      : TAP_CFG1
* Address       : 0X58
* Bit Group Name: TAP_X_EN
* Permission    : RW
*******************************************************************************/
typedef enum {
	TAP_X_EN_DISABLED 				= 0x00,
	TAP_X_EN_ENABLED 					= 0x08,
} TAP_X_EN_t;

/*******************************************************************************
* Register      : TAP_CFG1
* Address       : 0X58
* Bit Group Name: SLOPE_FDS
* Permission    : RW
*******************************************************************************/
typedef enum {
	SLOPE_FDS_SLOPE_FILTER		= 0x00,
	SLOPE_FDS_HPF 						= 0x10,
} SLOPE_FDS_t;


/*******************************************************************************
* Register      : TAP_CFG1
* Address       : 0X58
* Bit Group Name: INACT_EN
* Permission    : RW
*******************************************************************************/
typedef enum {
	INACT_EN_DISABLED 										= 0x00,
	INACT_EN_SET_ACC_LP_GYRO_NO_CHANGE		= 0x20,
	INACT_EN_SET_ACC_LP_GYRO_SLEEP				= 0x40,
	INACT_EN_SET_ACC_LP_GYRO_PW_DOWN			= 0x60,
} INACT_EN_t;

/*******************************************************************************
* Register      : TAP_CFG1
* Address       : 0X58
* Bit Group Name: INTERRUPTS_EN
* Permission    : RW
*******************************************************************************/
typedef enum {
	INTERRUPTS_EN_DISABLED		= 0x00,
	INTERRUPTS_EN_ENABLED 		= 0x80,
} INTERRUPTS_EN_t;

/*******************************************************************************
* Register      : TAP_THS_6D
* Address       : 0X59
* Bit Group Name: TAP_THS
* Permission    : RW
*******************************************************************************/
#define TAP_THS_MASK  			0x1F
#define TAP_THS_POSITION  	0

/*******************************************************************************
* Register      : TAP_THS_6D
* Address       : 0X59
* Bit Group Name: SIXD_THS
* Permission    : RW
*******************************************************************************/
typedef enum {
	SIXD_THS_80_degree 				= 0x00,
	SIXD_THS_70_degree 				= 0x20,
	SIXD_THS_60_degree 				= 0x40,
	SIXD_THS_50_degree 				= 0x60,
} SIXD_THS_t;

/*******************************************************************************
* Register      : TAP_THS_6D
* Address       : 0X59
* Bit Group Name: D4D_EN
* Permission    : RW
*******************************************************************************/
typedef enum {
	D4D_EN_DISABLED						= 0x00,
	D4D_EN_ENABLED 						= 0x80,
} D4D_EN_t;

/*******************************************************************************
* Register      : INT_DUR2
* Address       : 0X5A
* Bit Group Name: SHOCK
* Permission    : RW
*******************************************************************************/
#define SHOCK_MASK  				0x03
#define SHOCK_POSITION  		0

/*******************************************************************************
* Register      : INT_DUR2
* Address       : 0X5A
* Bit Group Name: QUIET
* Permission    : RW
*******************************************************************************/
#define QUIET_MASK  				0x0C
#define QUIET_POSITION  		2

/*******************************************************************************
* Register      : INT_DUR2
* Address       : 0X5A
* Bit Group Name: DUR
* Permission    : RW
*******************************************************************************/
#define DUR_MASK  					0xF0
#define DUR_POSITION  			4

/*******************************************************************************
* Register      : WAKE_UP_THS
* Address       : 0X5B
* Bit Group Name: WK_THS
* Permission    : RW
*******************************************************************************/
#define WK_THS_MASK  				0x3F
#define WK_THS_POSITION  		0

/*******************************************************************************
* Register      : WAKE_UP_THS
* Address       : 0X5B
* Bit Group Name: SINGLE_DOUBLE_TAP
* Permission    : RW
*******************************************************************************/
typedef enum {
	SINGLE_DOUBLE_TAP_DOUBLE_TAP	= 0x00,
	SINGLE_DOUBLE_TAP_SINGLE_TAP 	= 0x80,
} SINGLE_DOUBLE_TAP_t;

/*******************************************************************************
* Register      : WAKE_UP_DUR
* Address       : 0X5C
* Bit Group Name: SLEEP_DUR
* Permission    : RW
*******************************************************************************/
#define SLEEP_DUR_MASK  		0x0F
#define SLEEP_DUR_POSITION  0

/*******************************************************************************
* Register      : WAKE_UP_DUR
* Address       : 0X5C
* Bit Group Name: TIMER_HR
* Permission    : RW
*******************************************************************************/
typedef enum {
	TIMER_HR_6_4ms 						= 0x00,
	TIMER_HR_25us 		 				= 0x10,
} TIMER_HR_t;

/*******************************************************************************
* Register      : WAKE_UP_DUR
* Address       : 0X5C
* Bit Group Name: WAKE_DUR
* Permission    : RW
*******************************************************************************/
#define WAKE_DUR_MASK  			0x60
#define WAKE_DUR_POSITION  	5

/*******************************************************************************
* Register      : FREE_FALL
* Address       : 0X5D
* Bit Group Name: FF_DUR
* Permission    : RW
*******************************************************************************/
#define	FF_FREE_FALL_DUR_MASK  			0xF8
#define	FF_FREE_FALL_DUR_POSITION  	3
#define	FF_WAKE_UP_DUR_MASK  				0x80
#define	FF_WAKE_UP_DUR_POSITION  		7

/*******************************************************************************
* Register      : FREE_FALL
* Address       : 0X5D
* Bit Group Name: FF_THS
* Permission    : RW
*******************************************************************************/
typedef enum {
	FF_THS_156mg							= 0x00,
	FF_THS_219mg 		 					= 0x01,
	FF_THS_250mg 		 					= 0x02,
	FF_THS_312mg 		 					= 0x03,
	FF_THS_344mg 		 					= 0x04,
	FF_THS_406mg 		 					= 0x05,
	FF_THS_469mg 		 					= 0x06,
	FF_THS_500mg 		 					= 0x07,
} FF_THS_t;

/*******************************************************************************
* Register      : MD1_CFG
* Address       : 0X5E
* Bit Group Name: INT1_TIMER
* Permission    : RW
*******************************************************************************/
typedef enum {
	INT1_TIMER_DISABLED 			= 0x00,
	INT1_TIMER_ENABLED 				= 0x01,
} INT1_TIMER_t;

/*******************************************************************************
* Register      : MD1_CFG
* Address       : 0X5E
* Bit Group Name: INT1_TILT
* Permission    : RW
*******************************************************************************/
typedef enum {
	INT1_TILT_DISABLED 				= 0x00,
	INT1_TILT_ENABLED 				= 0x02,
} INT1_TILT_t;

/*******************************************************************************
* Register      : MD1_CFG
* Address       : 0X5E
* Bit Group Name: INT1_6D
* Permission    : RW
*******************************************************************************/
typedef enum {
	INT1_6D_DISABLED 					= 0x00,
	INT1_6D_ENABLED 					= 0x04,
} INT1_6D_t;

/*******************************************************************************
* Register      : MD1_CFG
* Address       : 0X5E
* Bit Group Name: INT1_TAP
* Permission    : RW
*******************************************************************************/
typedef enum {
	INT1_TAP_DISABLED 				= 0x00,
	INT1_TAP_ENABLED 					= 0x08,
} INT1_TAP_t;

/*******************************************************************************
* Register      : MD1_CFG
* Address       : 0X5E
* Bit Group Name: INT1_FF
* Permission    : RW
*******************************************************************************/
typedef enum {
	INT1_FF_DISABLED 					= 0x00,
	INT1_FF_ENABLED 					= 0x10,
} INT1_FF_t;

/*******************************************************************************
* Register      : MD1_CFG
* Address       : 0X5E
* Bit Group Name: INT1_WU
* Permission    : RW
*******************************************************************************/
typedef enum {
	INT1_WU_DISABLED 					= 0x00,
	INT1_WU_ENABLED 					= 0x20,
} INT1_WU_t;

/*******************************************************************************
* Register      : MD1_CFG
* Address       : 0X5E
* Bit Group Name: INT1_SINGLE_TAP
* Permission    : RW
*******************************************************************************/
typedef enum {
	INT1_SINGLE_TAP_DISABLED	= 0x00,
	INT1_SINGLE_TAP_ENABLED 	= 0x40,
} INT1_SINGLE_TAP_t;

/*******************************************************************************
* Register      : MD1_CFG
* Address       : 0X5E
* Bit Group Name: INT1_SLEEP
* Permission    : RW
*******************************************************************************/
typedef enum {
	INT1_SLEEP_DISABLED 			= 0x00,
	INT1_SLEEP_ENABLED 				= 0x80,
} INT1_SLEEP_t;

/*******************************************************************************
* Register      : MD2_CFG
* Address       : 0X5F
* Bit Group Name: INT2_IRON
* Permission    : RW
*******************************************************************************/
typedef enum {
	INT2_IRON_DISABLED 				= 0x00,
	INT2_IRON_ENABLED 				= 0x01,
} INT2_IRON_t;

/*******************************************************************************
* Register      : MD2_CFG
* Address       : 0X5F
* Bit Group Name: INT2_TILT
* Permission    : RW
*******************************************************************************/
typedef enum {
	INT2_TILT_DISABLED 				= 0x00,
	INT2_TILT_ENABLED 				= 0x02,
} INT2_TILT_t;

/*******************************************************************************
* Register      : MD2_CFG
* Address       : 0X5F
* Bit Group Name: INT2_6D
* Permission    : RW
*******************************************************************************/
typedef enum {
	INT2_6D_DISABLED 					= 0x00,
	INT2_6D_ENABLED 					= 0x04,
} INT2_6D_t;

/*******************************************************************************
* Register      : MD2_CFG
* Address       : 0X5F
* Bit Group Name: INT2_TAP
* Permission    : RW
*******************************************************************************/
typedef enum {
	INT2_TAP_DISABLED 				= 0x00,
	INT2_TAP_ENABLED 					= 0x08,
} INT2_TAP_t;

/*******************************************************************************
* Register      : MD2_CFG
* Address       : 0X5F
* Bit Group Name: INT2_FF
* Permission    : RW
*******************************************************************************/
typedef enum {
	INT2_FF_DISABLED 					= 0x00,
	INT2_FF_ENABLED 					= 0x10,
} INT2_FF_t;

/*******************************************************************************
* Register      : MD2_CFG
* Address       : 0X5F
* Bit Group Name: INT2_WU
* Permission    : RW
*******************************************************************************/
typedef enum {
	INT2_WU_DISABLED 					= 0x00,
	INT2_WU_ENABLED 					= 0x20,
} INT2_WU_t;

/*******************************************************************************
* Register      : MD2_CFG
* Address       : 0X5F
* Bit Group Name: INT2_SINGLE_TAP
* Permission    : RW
*******************************************************************************/
typedef enum {
	INT2_SINGLE_TAP_DISABLED	= 0x00,
	INT2_SINGLE_TAP_ENABLED 	= 0x40,
} INT2_SINGLE_TAP_t;

/*******************************************************************************
* Register      : MD2_CFG
* Address       : 0X5F
* Bit Group Name: INT2_SLEEP
* Permission    : RW
*******************************************************************************/
typedef enum {
	INT2_SLEEP_DISABLED 			= 0x00,
	INT2_SLEEP_ENABLED 				= 0x80,
} INT2_SLEEP_t;

/*******************************************************************************
* Register      : INT_OIS
* Address       : 0X6F
* Bit Group Name: LVL2_OIS
* Permission    : RW
*******************************************************************************/
typedef enum {
	LVL2_OIS_DISABLED 				= 0x00,
	LVL2_OIS_ENABLED 					= 0x40,
} LVL2_OIS_t;

/*******************************************************************************
* Register      : INT_OIS
* Address       : 0X6F
* Bit Group Name: INT2_DRDY_OIS
* Permission    : RW
*******************************************************************************/
typedef enum {
	INT2_DRDY_OIS_DISABLED 		= 0x00,
	INT2_DRDY_OIS_ENABLED 		= 0x80,
} INT2_DRDY_OIS_t;

/*******************************************************************************
* Register      : CTRL1_OIS
* Address       : 0X70
* Bit Group Name: OIS_EN_SPI2
* Permission    : RW
*******************************************************************************/
typedef enum {
	OIS_EN_SPI2_DISABLED 			= 0x00,
	OIS_EN_SPI2_ENABLED 			= 0x01,
} OIS_EN_SPI2_t;

/*******************************************************************************
* Register      : CTRL1_OIS
* Address       : 0X70
* Bit Group Name: FS_125_OIS
* Permission    : RW
*******************************************************************************/
typedef enum {
	FS_125_OIS_DISABLED				= 0x00,
	FS_125_OIS_ENABLED 				= 0x02,
} FS_125_OIS_t;

/*******************************************************************************
* Register      : CTRL1_OIS
* Address       : 0X70
* Bit Group Name: FS_G_OIS
* Permission    : RW
*******************************************************************************/
typedef enum {
	FS_G_OIS_250dps						= 0x00,
	FS_G_OIS_500dps 					= 0x04,
	FS_G_OIS_1000dps 					= 0x08,
	FS_G_OIS_2000dps 					= 0x0C,
} FS_G_OIS_t;

/*******************************************************************************
* Register      : CTRL1_OIS
* Address       : 0X70
* Bit Group Name: MODE4_EN
* Permission    : RW
*******************************************************************************/
typedef enum {
	MODE4_EN_DISABLED					= 0x00,
	MODE4_EN_ENABLED 					= 0x10,
} MODE4_EN_t;

/*******************************************************************************
* Register      : CTRL1_OIS
* Address       : 0X70
* Bit Group Name: SIM_OIS
* Permission    : RW
*******************************************************************************/
typedef enum {
	SIM_OIS_4WIRE_SPI2				= 0x00,
	SIM_OIS_3WIRE_SPI2 				= 0x20,
} SIM_OIS_t;

/*******************************************************************************
* Register      : CTRL1_OIS
* Address       : 0X70
* Bit Group Name: LVL1_OIS
* Permission    : RW
*******************************************************************************/
typedef enum {
	LVL1_OIS_DISABLED					= 0x00,
	LVL1_OIS_ENABLED 					= 0x40,
} LVL1_OIS_t;

/*******************************************************************************
* Register      : CTRL1_OIS
* Address       : 0X70
* Bit Group Name: BLE_OIS
* Permission    : RW
*******************************************************************************/
typedef enum {
	BLE_OIS_LSbyte_LOWER_RA		= 0x00,
	BLE_OIS_LSbyte_HIGHER_RA	= 0x80,
} BLE_OIS_t;

/*******************************************************************************
* Register      : CTRL2_OIS
* Address       : 0X71
* Bit Group Name: HP_EN_OIS
* Permission    : RW
*******************************************************************************/
typedef enum {
	HP_EN_OIS_DISABLED				= 0x00,
	HP_EN_OIS_ENABLED 				= 0x01,
} HP_EN_OIS_t;

/*******************************************************************************
* Register      : CTRL2_OIS
* Address       : 0X71
* Bit Group Name: FTYPE_OIS
* Permission    : RW
*******************************************************************************/
typedef enum {
	FTYPE_OIS_351Hz						= 0x00,
	FTYPE_OIS_237Hz 					= 0x02,
	FTYPE_OIS_173Hz						= 0x04,
	FTYPE_OIS_937Hz 					= 0x06,
} FTYPE_OIS_t;

/*******************************************************************************
* Register      : CTRL2_OIS
* Address       : 0X71
* Bit Group Name: HPM_OIS
* Permission    : RW
*******************************************************************************/
typedef enum {
	HPM_OIS_16mHz							= 0x00,
	HPM_OIS_65mHz 						= 0x10,
	HPM_OIS_260mHz						= 0x20,
	HPM_OIS_1040mHz 					= 0x30,
} HPM_OIS_t;

/*******************************************************************************
* Register      : CTRL3_OIS
* Address       : 0X72
* Bit Group Name: ST_OIS_CLAMPDIS
* Permission    : RW
*******************************************************************************/
typedef enum {
	ST_OIS_CLAMPDIS_DISABLED	= 0x00,
	ST_OIS_CLAMPDIS_ENABLED		= 0x01,
} ST_OIS_CLAMPDIS_t;

/*******************************************************************************
* Register      : CTRL3_OIS
* Address       : 0X72
* Bit Group Name: ST_OIS
* Permission    : RW
*******************************************************************************/
typedef enum {
	ST_OIS_NORMAL_MODE0				= 0x00,
	ST_OIS_POS_SIGN_SELF_TEST = 0x02,
	ST_OIS_NORMAL_MODE1				= 0x04,
	ST_OIS_NEG_SIGN_SELF_TEST	= 0x06,
} ST_OIS_t;

/*******************************************************************************
* Register      : CTRL3_OIS
* Address       : 0X72
* Bit Group Name: FILTER_XL_CONF_OIS
* Permission    : RW
*******************************************************************************/
typedef enum {
	FILTER_XL_CONF_OIS_00  		= 0x00,
	FILTER_XL_CONF_OIS_01  		= 0x08,
	FILTER_XL_CONF_OIS_10  		= 0x10,
	FILTER_XL_CONF_OIS_11  		= 0x18,
} FILTER_XL_CONF_OIS_t;

/*******************************************************************************
* Register      : CTRL3_OIS
* Address       : 0X72
* Bit Group Name: FS_XL_OIS
* Permission    : RW
*******************************************************************************/
typedef enum {
	FS_XL_OIS_2g							= 0x00,
	FS_XL_OIS_16g 						= 0x20,
	FS_XL_OIS_4g							= 0x40,
	FS_XL_OIS_8g							= 0x60,
} FS_XL_OIS_t;

/*******************************************************************************
* Register      : CTRL3_OIS
* Address       : 0X72
* Bit Group Name: DEN_LH_OIS
* Permission    : RW
*******************************************************************************/
typedef enum {
	DEN_LH_OIS_ACTIVE_LOW			= 0x00,
	DEN_LH_OIS_ACTIVE_HIGH		= 0x80,
} DEN_LH_OIS_t;

#endif  // End of __LSM6DSM_H__ definition check
