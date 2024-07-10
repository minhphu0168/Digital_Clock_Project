/*typedef variable*/
typedef unsigned int unit32;

/*Define function*/
void LPUART1_RxTx_IRQHandler(void);																		//Function of LPUART1 interrupt
void LPUART1_TransmitData(volatile char cArray[]);										//Function to transmit data string by LPUART
void PORTC_IRQHandler (void);            															//Function to interrupt in port C
void LPSPI0_TransmitData(volatile unit32 nData);											//Function to transmit data by LPSPI
void ControlBrightness (volatile unit32 nBrightnessLevel);						//Function to control brightness
void DisplayDate (volatile char cDayData[], volatile char cMonthData[], volatile char cYearData[]);       //Function to display date
void DisplayTime (volatile char cHourData[], volatile char MinuteData[], volatile char cSecondData[]);		//Function to display time and alarm
unit32 ConvertStringToDec( volatile char cSring[]);										//Function to convert data string to number
void LPIT0_Ch0_IRQHandler (void);																			//Timer Channel 0 interrupt
void LPIT0_Ch1_IRQHandler (void);																			//Timer Channel 1 interrupt
void LPIT0_Ch2_IRQHandler (void);																			//Timer Channel 2 interrupt
void LPIT0_Ch3_IRQHandler (void);																			//Timer Channel 3 interrupt
unit32 CheckYear (volatile char cYearArr[]);													//Function to check leap year or not
unit32 CheckFormat (volatile char cData[]);														//Function to check format
void ClearArray(volatile char ClearArray[], volatile unit32 nSize);		//Function to clear array 
