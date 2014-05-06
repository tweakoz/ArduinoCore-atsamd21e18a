#ifndef _SERCOM_CLASS_
#define _SERCOM_CLASS_

#include "sam.h"

#define SERCOM_FREQ_REF 48000000

typedef enum
{
	UART_EXT_CLOCK = 0,
	UART_INT_CLOCK = 0x1u
} SercomUartMode;

typedef enum
{
	SPI_SLAVE_OPERATION = 0x2u,
	SPI_MASTER_OPERATION = 0x3u
} SercomSpiMode;

typedef enum
{
	I2C_SLAVE_OPERATION = 0x4u,
	I2C_MASTER_OPERATION = 0x5u
} SercomI2CMode;

typedef enum
{
	SERCOM_EVEN_PARITY = 0,
	SERCOM_ODD_PARITY,
	SERCOM_NO_PARITY
} SercomParityMode;

typedef enum
{
	SERCOM_STOP_BIT_1 = 0,
	SERCOM_STOP_BITS_2
} SercomNumberStopBit;

typedef enum
{
	MSB_FIRST = 0,
	LSB_FIRST
} SercomDataOrder;

typedef enum
{
	UART_CHAR_SIZE_8_BITS = 0,
	UART_CHAR_SIZE_9_BITS,
	UART_CHAR_SIZE_5_BITS = 0x5u,
	UART_CHAR_SIZE_6_BITS,
	UART_CHAR_SIZE_7_BITS
} SercomUartCharSize;

typedef enum
{
	SERCOM_RX_PAD_0 = 0,
	SERCOM_RX_PAD_1,
	SERCOM_RX_PAD_2,
	SERCOM_RX_PAD_3
} SercomRXPad;

typedef enum
{
	UART_TX_PAD_0 = 0,	//Only for Intern Clock
	UART_TX_PAD_1 = 0,	//Only for Extern Clock
	UART_TX_PAD_2 = 1,  //Only for Intern Clock
	UART_TX_PAD_3 = 1	//Only for Extern Clock
} SercomUartTXPad;

typedef enum
{
	SAMPLE_RATE_x16 = 0,	//Arithmetic
	SAMPLE_RATE_x8 = 0x2,	//Arithmetic
	SAMPLE_RATE_x3 = 0x3	//Arithmetic
} SercomUartSampleRate;

typedef enum
{
	SPI_MODE_0 = 0,	// CPOL : 0  | CPHA : 0
	SPI_MODE_1,		// CPOL : 0  | CPHA : 1
	SPI_MODE_2,		// CPOL : 1  | CPHA : 0
	SPI_MODE_3		// CPOL : 1  | CPHA : 1
} SercomSpiClockMode;

typedef enum
{
	SPI_PAD_0_SCK_1 = 0,
	SPI_PAD_2_SCK_3,
	SPI_PAD_3_SCK_1,
	SPI_PAD_0_SCK_3
} SercomSpiTXPad;

typedef enum
{
	SPI_CHAR_SIZE_8_BITS = 0,
	SPI_CHAR_SIZE_9_BITS = 1
} SercomSpiCharSize;

typedef enum
{
	WIRE_UNKNOWN_STATE = 0,
	WIRE_IDLE_STATE,
	WIRE_OWNER_STATE,
	WIRE_BUSY_STATE
} SercomWireBusState;

typedef enum
{
	WIRE_WRITE_FLAG = 0,
	WIRE_READ_FLAG
} SercomWireReadWriteFlag;

typedef enum
{
	WIRE_MASTER_ACT_NO_ACTION = 0,
	WIRE_MASTER_ACT_REPEAT_START,
	WIRE_MASTER_ACT_READ,
	WIRE_MASTER_ACT_STOP
} SercomMasterCommandWire;

typedef enum
{
	WIRE_MASTER_ACK_ACTION = 0,
	WIRE_MASTER_NACK_ACTION
} SercomMasterAckActionWire;
	
class SERCOM
{
	public:
		SERCOM(Sercom* sercom);
	    
		/* ========== UART ========== */
		void initUART(SercomUartMode mode, SercomUartSampleRate sampleRate, uint32_t baudrate=0);
		void initFrame(SercomUartCharSize charSize, SercomDataOrder dataOrder, SercomParityMode parityMode, SercomNumberStopBit nbStopBits);
		void initPads(SercomUartTXPad txPad, SercomRXPad rxPad);
		
		void resetUART();
		void enableUART();
		void flushUART();
		void clearStatusUART();
		bool availableDataUART();
		bool isBufferOverflowErrorUART();
		bool isFrameErrorUART();
		bool isParityErrorUART();
		bool isDataRegisterEmptyUART();
		uint8_t readDataUART();
		int writeDataUART(uint8_t data);
        
		/* ========== SPI ========== */
		void initSPI(SercomSpiTXPad mosi, SercomRXPad miso, SercomSpiCharSize charSize, SercomDataOrder dataOrder);
		void initClock(SercomSpiClockMode clockMode, uint32_t baudrate);
		
		void resetSPI();
		void enableSPI();
		void disableSPI();
		void setDataOrderSPI(SercomDataOrder dataOrder);
		void setBaudrateSPI(uint8_t divider);
		void setClockModeSPI(SercomSpiClockMode clockMode);
		void writeDataSPI(uint8_t data);
		uint8_t readDataSPI();
		bool isBufferOverflowErrorSPI();
		bool isDataRegisterEmptySPI();
		bool isTransmitCompleteSPI();
		bool isReceiveCompleteSPI();
		
		
		/* ========== WIRE ========== */
		void initSlaveWIRE(uint8_t address);
		void initMasterWIRE(uint32_t baudrate);
		
		void resetWIRE();
		void enableWIRE();
		void prepareStopBitWIRE();
		void prepareAckBitWIRE();
		bool startTransmissionWIRE(uint8_t address, SercomWireReadWriteFlag flag);
		bool sendDataMasterWIRE(uint8_t data);
		bool sendDataSlaveWIRE(uint8_t data);
		bool isMasterWIRE();
		bool isSlaveWIRE();
		bool isBusIdleWIRE();
		bool isDataReadyWIRE();
		bool isStopDetectedWIRE();
		bool isRestartDetectedWIRE();
		bool isAddressMatch();
		bool isMasterReadOperationWIRE();
		int availableWIRE();
		uint8_t readDataWIRE();
		
	private:
		Sercom* sercom;
		uint8_t calculateBaudrateSynchronous(uint32_t baudrate);
		uint32_t division(uint32_t dividend, uint32_t divisor);
};

#endif