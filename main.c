#include "module.h"
#include "define.h"

static volatile unit32 nStatusFlag;								//Flag to execute in while(1)
static volatile unit32 nIntensityFlag;						//Flag to execute in while(1)
static volatile unit32 nStatus = 1;
static volatile unit32 nCountStatus;
static volatile unit32 nDayFlag;
static volatile unit32 nTimeFlag;
static volatile char cDataReceived[10];
static volatile unit32 nReceiveDataFlag;	
static volatile unit32 nSignal ;
static volatile unit32 nAlarmFlag;
static volatile unit32 nCountAlarm;

static volatile char cDay[3] = "01";
static volatile char cMonth[3] = "01";
static volatile char cYear[5] = "1991";
static volatile char cHour[3] = "18";
static volatile char cMinute[3] = "00";
static volatile char cSecond[3] = "00";
static volatile char cAlarmHour[3] = "00";
static volatile char cAlarmMinute[3] = "00";
static volatile char cAlarmSecond[3] = "00";

int main()
{
	volatile char cDisplay1[] = "Select mode display via the button";
	volatile char cDisplay2[] = "Press Button 1\n\t1: Auto display mode\n\t2: Display the date\n\t3: Display the time\n\t4: Display the alarm";
	volatile char cDisplay3[] = "Press Button 2\n\tDecrease bright of LED 7 SEG";
	
	volatile unit32 iTemp;							//Use temporary variables for variables that can only be recorded as 32 bits
	volatile char cMessage1[] = "\nWrong format";
	volatile char cMessage2[] = "\nOK";
	
	/*********************************** Config CLOCK *************************************/
	
	/*Config  SOSC*/
	 
	iTemp = SCG->SOSCCFG;
	iTemp |= (1u << 2);				//EREFS = 1 (Internal crystal oscillator of OSC selected)
	iTemp |= (1u << 3);				//HGO = 1 (Configure crystal oscillator for high-gain operation) 
	iTemp &= ~(0x3u << 4);		//Clear bit 4 5 (RANGE)
	iTemp |= (0x2u << 4);			//RANGE = 10 (Medium frequency range selected for the crytstal oscillator)
	SCG->SOSCCFG = iTemp;
				
	iTemp = SCG->SOSCCSR;     
	iTemp &= ~(1u << 23);			//Clear bit 23 to write 				
	SCG->SOSCCSR = iTemp;			
	iTemp |= 1u;							//Set 1 bit 0 to enable
	SCG->SOSCCSR = iTemp;			
	
	/*Loop used to wait for bit 24(SOSCCSR) = 1*/
	while((SCG->SOSCCSR & (1u << 24)) != (1u << 24));
	
	/*Config SPLL*/
	
	iTemp = SCG->SPLLCFG;
	iTemp |= (0x0u << 8);					//Config Divide Factor = 1 (PREDIV = 000)
	iTemp |= (0x14u << 16);				//Config Multiply Factor = 36 (MULT = 10100)
	SCG->SPLLCFG = iTemp;
	
	iTemp = SCG->SPLLDIV;
	iTemp |= (4u << 8);					//Config SPLLDIV2 divide by 8 (100)
	SCG->SPLLDIV = iTemp;				

	iTemp = SCG->SPLLCSR;     
	iTemp &= ~(1u << 23);				//Clear bit 23 to write 				
	SCG->SPLLCSR = iTemp;			
	iTemp |= 1u;								//Set 1 bit 0 to enable
	SCG->SPLLCSR = iTemp;		
	
	/*Loop used to wait for bit 24(SPLLCSR)= 1*/
	while((SCG->SPLLCSR & (1u << 24)) != (1u << 24));
	
	/*Connfig RCCR*/
	
	iTemp = SCG->RCCR;     
	iTemp &= ~(0xFu << 24);			//Clear bit 24-27 (SCS)				
	iTemp |= (6u << 24);				//Set 0110 to set System PLL (SPLL_CLK)
	iTemp &= ~(0xFu << 4);			//Clear bit 16-19 (DIVCORE)
	iTemp |= (0x1u << 16);			//Set 0001 to Divide-by-2	
	iTemp &= ~(0xFu << 4);			//Clear bit 4-7 (DIVBUS)	
	iTemp |= (3u << 4);					//Set 0011 to Divide-by-4
	iTemp &= ~(0xFu);						//Clear bit 0-3 (DIVSLOW)	
	iTemp |= (5u);							//Set 0101 to Divide-by-6
	SCG->RCCR = iTemp;		
	
	/*Loop used to wait for SCG->CSR = SCG->RCCR*/
	while(SCG->CSR != SCG->RCCR);
	
	/*Clock SPLLDIV2 = 18 MHz
		CORE_Clk = 72 MHz
		BUS_Clk = 36 MHz
		FLASH_Clk = 24 MHz*/
		
		/*********************************** Config LPUART1 *************************************/

	PCC->PORTC |= (1 << 30);										// set bit 30 = 1 to enable clock in port C
	
	PortC->PCR6 &= ~(7u << 8);									// clear bit 8 9 10 of MUX 
	PortC->PCR6 |= (2u << 8);										// set 0 1 0 (Alternative 2)
	
	PortC->PCR7 &= ~(7u << 8);									// clear bit 8 9 10 of MUX 
	PortC->PCR7 |= (2u << 8);										// set 0 1 0 (Alternative 2)
	
	PCC->LPUART1 &= ~(1u << 30);								// set bit 30 = 0 to disable clock in LPUART1
	PCC->LPUART1 &= ~(7u << 24);								// clear bit 24 25 26  of PCS 
	PCC->LPUART1 |= (6u << 24);  								// set 1 1 0 for bit 24 25 26(SPLLDIV2_Clk)
	PCC->LPUART1 |= (1u << 30);									// set bit 30 = 1 to enable clock in LPUART1
	
	iTemp = LPUART_1->BAUD;
	iTemp &= ~(0x1Fu << 24);										//Clear bit 24-28 (OSR)
	iTemp |= (25u << 24);												//Set (OSR+1) = 26  
	iTemp &= ~0x1FFFu;													//Clear bit 0-12 (SBR)
	iTemp |= 18u;																//Set SBR = 18
	iTemp &= ~(1u << 13);
	LPUART_1->BAUD = iTemp;
	
	LPUART_1->CTRL |= (1u << 4);								//Set bit 4 (M) = 1  (Receiver and transmitter use 9-bit data characters)
	LPUART_1->CTRL |= (1u << 1);								//Set bit 1 (PE) = 1  to enable parity
	LPUART_1->CTRL &= ~(1u);										//Set bit 0 (PT) = 0  to select even parity
	LPUART_1->CTRL |= (1u << 18);								//Set bit 18 (RE) = 1 to enable receiver 
	LPUART_1->CTRL |= (1u << 19);								//Set bit 19 (TE) = 1 to enable transmitter
	LPUART_1->CTRL |= (1u << 2);								//Set bit 2 (ILT) = 1 to idle character bit count starts after stop bit
	
	ISER->ISER1 |= (1u << 1);										//NVIC configuration to enable LPUART1 Transmit/Receive Interrupt
	LPUART_1->CTRL |= (1u << 21);								//Set bit 21 (RIE) = 1 to enable interrupt requested when RDRF flag is 1
	LPUART_1->CTRL |= (1u << 20);								//Set bit 20 (ILIE) = 1 to enable interrupt requested when IDLE flag is 1
	
	/*********************************** Config LPSPI0 *************************************/
	
	PCC->PORTE |= (1u << 30);										// set bit 30 = 1 to enable clock in port E
	
	PortE->PCR0 &= ~(7u << 8);									// clear bit 8 9 10  of MUX 
	PortE->PCR0 |= (2u << 8);										// set 2 for bit 8 to become 0 1 0 (Alternative 2 LPSPI0_SCK )
	
	PortE->PCR1 &= ~(7u << 8);									// clear bit 8 9 10  of MUX 
	PortE->PCR1 |= (2u << 8);										// set 2 for bit 8 to become 0 1 0 (Alternative 2 LPSPI0_SIN)
	
	PortE->PCR2 &= ~(7u << 8);									// clear bit 8 9 10  of MUX 
	PortE->PCR2 |= (2u << 8);										// set 2 for bit 8 to become 0 1 0 (Alternative 2 LPSPI0_SOUT)
	
	PortE->PCR6 &= ~(7u << 8);									// clear bit 8 9 10  of MUX 
	PortE->PCR6 |= (2u << 8);										// set 2 for bit 8 to become 0 1 0 (Alternative 2 LPSPI0_PCS2)
	
	PCC->LPSPI0 &= ~(1u << 30);									// set bit 30 = 0 to disable clock in LPSPI0
	PCC->LPSPI0 &= ~(7u << 24);									// clear bit 24 25 26  of PCS 
	PCC->LPSPI0 |= (6u << 24);  								// set 1 1 0 for bit 24 25 26(SPLLDIV2_Clk)
	PCC->LPSPI0 |= (1u << 30);									// set bit 30 = 1 to enable clock in LPSPI0
	
	LPSPI_0->CCR &= ~(0xFFu);										//Clear bit 0-7 (SCKDIV = 0)		(SCK Clock = 9MHz < 10MHz)
	LPSPI_0->CCR &= ~(0xFFu << 8);							//Clear bit 8-15 (DBT = 0)			(Delay between transfer = 9MHz < 20MHz)
	LPSPI_0->CCR &= ~(0xFFu << 16);							//Clear bit 16-23 (PCSSCK = 0)	(PCS to SCK Delay = 18MHz < 40MHz)
	LPSPI_0->CCR &= ~(0xFFu << 24);							//Clear bit 24-31 (SCKPCS = 0)	(SCK to PCS Delay = 18MHz > 0MHz)
	
	iTemp = LPSPI_0->TCR;
	iTemp &= ~(0x7u << 27);											//Clear bit 27-29 (PRESCALE = 1)
	iTemp &= ~(0xFFFu);													//Clear bit 0-11 (FRAMESZ)
	iTemp |= (0x1Fu);														//Set FRAMESZ = 32 bits 
	iTemp &= ~(1u << 23);												//Clear bit 23 ( Data is transferred MSB first)
	iTemp &= ~(1u << 30);												//CPHA = 0
	iTemp &= ~(1u << 31);												//CPOL = 0
	iTemp &= ~(0x3u << 24);											//Clear bit 24 25 
	iTemp |= (0x2u << 24);											//Set 1 0 (Transfer using LPSPI_PCS[2])
	LPSPI_0->TCR = iTemp;
	
	LPSPI_0->FCR &= ~(0x3u);											//Clear bit 0 1 TXWATER = 1
	
	LPSPI_0->CFGR1 |= (1u << 3);									//Set bit 3 = 1 (Transfers will not stall, allowing transmit FIFO underruns to occur)
	LPSPI_0->CFGR1 |= (1u);												//Bit 0 = 1 (Master mode)
	
	LPSPI_0->CR |= (1u << 3);											//LPSPI module is enabled in debug mode
	LPSPI_0->CR |= (1u);													// Module is enabled
	
	/*********************************** Config LPIT *************************************/
	
	PCC->LPIT &= ~(1u << 30);									// set bit 30 = 0 to disable clock in LPIT
	PCC->LPIT &= ~(7u << 24);									// clear bit 24 25 26  of PCS 
	PCC->LPIT |= (6u << 24);  								// set 1 1 0 for bit 24 25 26(SPLLDIV2_Clk)
	PCC->LPIT |= (1u << 30);									// set bit 30 = 1 to enable clock in LPSPI0

	LPIT_Timer->MCR |= (1u);									//Enable peripheral clock to timers
	LPIT_Timer->MCR	|= (1u << 3);							//Allow timer channels to continue to run in Debug mode
	
	ISER->ISER1 |= (1u << 16);								//NVIC configuration to enable LPIT interrupt with Channel 0
	ISER->ISER1 |= (1u << 17);								//NVIC configuration to enable LPIT interrupt with Channel 1
	ISER->ISER1 |= (1u << 18);								//NVIC configuration to enable LPIT interrupt with Channel 2
	ISER->ISER1 |= (1u << 19);								//NVIC configuration to enable LPIT interrupt with Channel 3
	
	LPIT_Timer->MIER |= (1u);									//Enable channel 0 Timer Interrupt Enable
	LPIT_Timer->MIER |= (1u << 1);						//Enable channel 1 Timer Interrupt Enable
	LPIT_Timer->MIER |= (1u << 2);						//Enable channel 2 Timer Interrupt Enable
	LPIT_Timer->MIER |= (1u << 3);						//Enable channel 3 Timer Interrupt Enable
	
	LPIT_Timer->TVAL0 = (0x112A87F);					//Cofig Timer Value Register 0 = 17999999 Hz
	LPIT_Timer->TVAL1 = (0x112A87F);					//Cofig Timer Value Register 1 = 17999999 Hz
	LPIT_Timer->TVAL2 = (0x112A87F);					//Cofig Timer Value Register 2 = 17999999 Hz
	LPIT_Timer->TVAL3 = (0x89543F);						//Cofig Timer Value Register 3 = 8999999 Hz
	
	LPIT_Timer->TCTRL0 &= ~(3u << 2);					//Clear 0 0 to choose 32-bit Periodic Counter
	LPIT_Timer->TCTRL1 &= ~(3u << 2);					//Clear 0 0 to choose 32-bit Periodic Counter
	LPIT_Timer->TCTRL2 &= ~(3u << 2);					//Clear 0 0 to choose 32-bit Periodic Counter
	LPIT_Timer->TCTRL3 &= ~(3u << 2);					//Clear 0 0 to choose 32-bit Periodic Counter
	
	LPIT_Timer->TCTRL0 |= (1u);								//Timer Channel 0 is enabled
	LPIT_Timer->TCTRL1 |= (1u);								//Timer Channel 1 is enabled
	
	/*********************************** Config GPIO *************************************/
	
	PCC->PORTD |= (1u << 30);										// set bit 30 = 1 to enable clock in port D
	PCC->PORTC |= (1u << 30);										// set bit 30 = 1 to enable clock in port C
	
	PortD->PCR16 &= (7u << 8);									// clear bit 8 9 10  of MUX 
	PortD->PCR16 |= (1u << 8);									// set 1 for bit 8 to become 0 0 1 (Alternative 1 GPIO) 
	PortC->PCR12 &= ~(7u << 8);									// clear bit 8 9 10  of MUX  
	PortC->PCR12 |= (1u << 8);									// set 1 for bit 8 to become 0 0 1 (Alternative 1 GPIO) 
	PortC->PCR13 &= ~(7u << 8);									// clear bit 8 9 10  of MUX  
	PortC->PCR13 |= (1u << 8);									// set 1 for bit 8 to become 0 0 1 (Alternative 1 GPIO) 
	
	PortD->PCR16 &= ~(1u << 1);									//not enable pull up or pull down 
	PortC->PCR12 &= ~(1u << 1);									//not enable pull up or pull down
	PortC->PCR13 &= ~(1u << 1);									//not enable pull up or pull down
	
	GPIOD->PDDR |= (1u << 16);									// configured PORT D pin 16 for output
	GPIOC->PDDR &= ~(1u << 12);									// configured PORT C pin 12 for input
	GPIOC->PDDR &= ~(1u << 13);									// configured PORT C pin 13 for input
	
	GPIOD->PDOR |= (1u << 16);									//set level 1 for pin 16 port D
	
	ISER->ISER1 |= (1u << 29);									//NVIC configuration to enable interrupt port C
	
	/*Setup interrupt type*/
	PortC->PCR12 &= ~(0xFu << 16);							//Clear bit
	PortC->PCR12 |= (0x9u << 16);								//Set interrupt on rising-edge
	PortC->PCR13 &= ~(0xFu << 16);							//Clear bit
  PortC->PCR13 |= (0x9u << 16);								//Set interrupt on rising-edge
	
	/*********************************************************************************/
	
	LPUART1_TransmitData (cDisplay1);
	LPUART1_TransmitData (cDisplay2);
	LPUART1_TransmitData (cDisplay3);
	
	LPSPI0_TransmitData(0x09FF);								//Code B decode for digits 7–0
	LPSPI0_TransmitData(0x0A0F);								//The initial brightness level is 5
	LPSPI0_TransmitData(0x0B07);								//Display digits 0 1 2 3 4 5 6 7
	LPSPI0_TransmitData(0x0C01);								//Normal Operation
	
	DisplayTime (cHour, cMinute, cSecond);
	
	while (1)
	{		
		if (nIntensityFlag == 1)
		{
			static volatile unit32 nBrightness = 4;   
			
			switch (nBrightness)
			{
				case 0:
					LPSPI0_TransmitData(0x0C00);					//Turn off
					nBrightness = 5;											//Resert brightness level	
					break;
				
				default:
					LPSPI0_TransmitData(0x0C01);					//Turn on
					ControlBrightness (nBrightness);			//Call function to control brightness
					nBrightness --;												//Decrease brightness level	
			}
			
			nIntensityFlag = 0;											//Resert flag
		}
		
		if (nStatusFlag == 1)
		{
			nStatus ++;
			
			switch (nStatus)
			{
				case 1:
					LPIT_Timer->TCTRL1 |= (1u);								//Timer Channel 1 is enabled
					break;
				
				case 2:
					LPIT_Timer->TCTRL1 &= ~(1u);							//Timer Channel 1 is disabled
					DisplayDate (cDay, cMonth, cYear);
					break;
				
				case 3:
					LPIT_Timer->TCTRL1 &= ~(1u);							//Timer Channel 1 is disabled
					DisplayTime (cHour, cMinute, cSecond);
					break;	
				
				case 4:
					LPIT_Timer->TCTRL1 &= ~(1u);							//Timer Channel 1 is disabled
					DisplayTime (cAlarmHour, cAlarmMinute, cAlarmSecond);
					nStatus = 0;
					break;
			}
			
			nStatusFlag = 0;
		}
		
		if (nDayFlag == 1)						////nDayFlag = 1 when hour ís max
		{
			volatile unit32 nMonth;
			volatile unit32 nFlag = 0;
			volatile unit32 nMarkYear;
			
			nMarkYear = CheckYear (cYear);     					//Check whether it is a leap year or not
			nMonth = ConvertStringToDec (cMonth); 			//Convert to integers
			
			if (nMonth == 4 || nMonth == 6 || nMonth == 9 || nMonth == 11)    //Month has 30 days
			{
				if ((cDay[0] == '3') && (cDay[1] == '0'))
				{
					cDay[1] = '1';
					cDay[0] ='0';
					nFlag = 1;
				}
				else if (cDay[1] == '9')
				{
					cDay[1] = '0';
					cDay[0] ++;
				}
				else
				{
					cDay[1] ++;
				}
			}
			else if ((nMonth == 2) && (nMarkYear == 1))						//February of leap year
			{
				if ((cDay[0] == '2') && (cDay[1] == '9'))
				{
					cDay[1] = '1';
					cDay[0] ='0';
					nFlag = 1;
				}
				else if (cDay[1] == '9')
				{
					cDay[1] = '0';
					cDay[0] ++;
				}
				else
				{
					cDay[1] ++;
				}
			}
			else if ((nMonth == 2) && (nMarkYear == 0)) 			//February of non-leap years
			{
				if ((cDay[0] == '2') && (cDay[1] == '8'))
				{
					cDay[1] = '1';
					cDay[0] ='0';
					nFlag = 1;
				}
				else if (cDay[1] == '9')
				{
					cDay[1] = '0';
					cDay[0] ++;
				}
				else
				{
					cDay[1] ++;
				}
			}
			else								//Month has 31 days
			{
				if ((cDay[0] == '3') && (cDay[1] == '1'))
				{
					cDay[1] = '1';
					cDay[0] ='0';
					nFlag = 1;     
				}
				else if (cDay[1] == '9')
				{
					cDay[1] = '0';
					cDay[0] ++;
				}
				else
				{
					cDay[1] ++;
				}
			}
		
			if (nFlag == 1)     // nFlag = 1 when Day is max
			{
				if ((cMonth[0] == '1') && (cMonth[1] == '2'))
				{
					cMonth[1] = '1';
					cMonth[0] ='0';
					nFlag = 2;
				}
				else if (cMonth[1] == '9')
				{
					cMonth[1] = '0';
					cMonth[0] ++;
				}
				else
				{
					cMonth[1] ++;
				}
			}
			
			if (nFlag == 2)						// nFlag = 1 when Month is max
			{
				if ((cYear[1] == '9') && (cYear[2] == '9') && (cYear[3] == '9'))
				{
					cYear[3] = '0';
					cYear[2] = '0';
					cYear[1] = '0';
					cYear[0] ++;
				}
				else if ((cYear[2] == '9') && (cYear[3] == '9'))
				{
					cYear[3] = '0';
					cYear[2] = '0';
					cYear[1] ++;
				}
				else if (cYear[3] == '9')
				{
					cYear[3] = '0';
					cYear[2] ++;
				}
				else
				{
					cYear[3] ++;
				}
			}
			
			if ((nStatus == 2) || ((nStatus == 1) && (nCountStatus == 1)))   // When in button state press 1 and 2
			{
				DisplayDate (cDay, cMonth, cYear);				//Display Date every update
			}	
			
			nDayFlag = 0;							//resert flag
		}	

		if (nTimeFlag == 1)    //nTimeFlag = 1 when second ís max
		{
			volatile unit32 nFlag = 0;
			
			if ((cMinute[0] == '5') && (cMinute[1] == '9'))
			{
				cMinute[1] = '0';
				cMinute[0] = '0';
				nFlag = 1;
			}
			else if (cMinute[1] == '9')
			{
				cMinute[1] = '0';
				cMinute[0]++;
			}
			else
			{
				cMinute[1] ++;
			}
			
			if (nFlag == 1)							//nFlag = 1 when minute ís max
			{
				if ((cHour[0] == '2') && (cHour[1] == '3'))
				{
					cHour[1] = '0';
					cHour[0] = '0';
					nDayFlag = 1; 
				}
				else if (cHour[1] == '9')
				{
					cHour[1] = '0';
					cHour[0]++;
				}
				else
				{
					cHour[1] ++;
				}
			}
			
			if ((nStatus == 3) || ((nStatus == 1) && (nCountStatus == 0)))      //When in button state press 1 and 3
			{
				DisplayTime (cHour, cMinute, cSecond);				//Display Date every update
			}
			
			if (nAlarmFlag == 1)
			{
				/*When time and alarm are equal*/
				if((cAlarmHour[0] == cHour[0]) && (cAlarmHour[1] == cHour[1]) && (cAlarmMinute[0] == cMinute[0]) && (cAlarmMinute[1] == cMinute[1]) && (cAlarmSecond[0] == cSecond[0]) && (cAlarmSecond[1] == cSecond[1]))
				{
					LPIT_Timer->TCTRL3 |= (1u);								//Timer Channel 3 is enabled
				}
			}
			
			nTimeFlag = 0;      //Resert flag
		}
		
		if (nReceiveDataFlag == 1)
		{
			volatile unit32 nCheck;
			
			nCheck = CheckFormat(cDataReceived);   //Call function to check format
			
			if (nCheck == 1)    //Correct format
			{
				LPUART1_TransmitData (cMessage2);
				
				/*Displays the newly entered data*/
				if ((cDataReceived[0] == 'd') || (cDataReceived[0] == 'D'))
				{
					DisplayDate (cDay, cMonth, cYear);
				}
				else if ((cDataReceived[0] == 't') || (cDataReceived[0] == 'T'))
				{
					DisplayTime (cHour, cMinute, cSecond);
				}
				else if ((cDataReceived[0] == 'a') || (cDataReceived[0] == 'A'))
				{
					nAlarmFlag = 1;
					DisplayTime (cAlarmHour, cAlarmMinute, cAlarmSecond);
				}
				
				nSignal = 1;
				LPIT_Timer->TCTRL2 |= (1u);								//Timer Channel 2 is enabled
				
			}
			else if (nCheck == 0)					//Wrong format
			{
				LPUART1_TransmitData (cMessage1);
			} 
			ClearArray(cDataReceived,10);   //Delete old data
			nReceiveDataFlag = 0;				//Clear Flag
		}
		
		if (nSignal == 0)
		{
			LPIT_Timer->TCTRL2 &= ~(1u);								//Timer Channel 2 is disable
		}
		
		if (nCountAlarm == 20)
		{
			nCountAlarm = 0;      //Resert
			nAlarmFlag = 0;				//Resert
			LPIT_Timer->TCTRL3 &= ~(1u);					////Timer Channel 3 is disabled
		}
	}	
}

void LPUART1_TransmitData(volatile char cArray[])				//Function to transmit data string by LPUART
{
	static volatile unit32 nIndexArray ;
	
	while(1)
	{
		if (cArray[nIndexArray] == '\0')					//The last character
		{
			nIndexArray = 0;
			/*Wait for  buffer to be empty (bit 23 = 1)*/ 
			while ((LPUART_1->STAT & (1u << 23)) != (1u << 23));
			LPUART_1->DATA = '\n';
			break;
		}
		/*Wait for  buffer to be empty (bit 23 = 1)*/ 
		while ((LPUART_1->STAT & (1u << 23)) != (1u << 23));
		LPUART_1->DATA = cArray[nIndexArray];
		nIndexArray ++;
	}
}

void LPSPI0_TransmitData(volatile unit32 nData)					//Function to transmit data by LPSPI
{
	/*Wait for  buffer to be empty (bit 0 = 1) */
	while ((LPSPI_0->SR & (1u)) != (1u));
	LPSPI_0->TDR = nData;	
}

void LPUART1_RxTx_IRQHandler(void)					//Function of LPUART1 interrupt
{
	static volatile unit32 nIndexDR ;
	
	if ((LPUART_1->STAT & (1 << 21)) == (1 << 21))					//Interrupt requested when RDRF flag is 1
	{
		cDataReceived[nIndexDR] = (char)LPUART_1->DATA;
		nIndexDR++;
	}
	if ((LPUART_1->STAT & (1 << 20)) == (1 << 20))					//Interrupt requested when IDLE flag is 1
	{
		LPUART_1->STAT |= (1u << 20);						//Clear flag
		nIndexDR = 0;
		nReceiveDataFlag = 1;
	}
}

void PORTC_IRQHandler(void)    				//Function to interrupt in Port C
{
	if (((PortC->PCR12 & (1u << 24)) == (1u << 24)) && (nCountAlarm > 0))    //Interrupt pin 12 when alarm active
	{
		PortC->PCR12 |= (1u << 24);					//Delete flag
		LPIT_Timer->TCTRL3 &= ~(1u);				//Timer Channel 3 is disabled
		GPIOD->PDOR |= (1u << 16);					//Set level 1 for pin 16 port D
		nAlarmFlag = 0;											
		nCountAlarm = 0;
	}
	else if (((PortC->PCR13 & (1u << 24)) == (1u << 24)) && (nCountAlarm > 0))	//Interrupt pin 13 when alarm active
	{
		PortC->PCR13 |= (1u << 24);					//Delete flag
		LPIT_Timer->TCTRL3 &= ~(1u);				//Timer Channel 3 is disabled
		GPIOD->PDOR |= (1u << 16);					//Set level 1 for pin 16 port D
		nAlarmFlag = 0;
		nCountAlarm = 0;
	}
	else if ((PortC->PCR12 & (1u << 24)) == (1u << 24))    		//Interrupt pin 12
	{
		PortC->PCR12 |= (1u << 24);					//Delete flag
		nStatusFlag = 1;
	}
	else if ((PortC->PCR13 & (1u << 24)) == (1u << 24))   //Interrupt pin 13
	{
		PortC->PCR13 |= (1u << 24);					//Delete flag
		nIntensityFlag = 1;
	}
}

void ControlBrightness (volatile unit32 nBrightnessLevel)								//Function to control brightness
{
	LPSPI0_TransmitData (0x0A00 | (nBrightnessLevel * 3));								//Change brightness 
}

void DisplayDate (volatile char cDayData[], volatile char cMonthData[], volatile char cYearData[])      //Function to display date
{
	volatile unit32 nTemp;
	
	for (volatile unit32 i = 1; i <= 4; i++)    //Display year
	{
		nTemp = 0x0000;
		nTemp |= (i << 8);
		nTemp |= (cYearData[4-i] - '0');
		LPSPI0_TransmitData(nTemp);
	}
	
	for (volatile unit32 i = 5; i <= 6; i++)		//Display month
	{
		if (i == 5)
		{
			nTemp = 0x0000;
			nTemp |= (8u << 4);
			nTemp |= (i << 8);
			nTemp |= (cMonthData[6-i] - '0');
			LPSPI0_TransmitData(nTemp);
		}
		else					
		{
			nTemp = 0x0000;
			nTemp |= (i << 8);
			nTemp |= (cMonthData[6-i] - '0');
			LPSPI0_TransmitData(nTemp);
		}
	}
	
	for (volatile unit32 i = 7; i <= 8; i++)			//Display day
	{
		if (i == 7)
		{
			nTemp = 0x0000;
			nTemp |= (8u << 4);
			nTemp |= (i << 8);
			nTemp |= (cDayData[8-i] - '0');
			LPSPI0_TransmitData(nTemp);
		}
		else
		{
			nTemp = 0x0000;
			nTemp |= (i << 8);
			nTemp |= (cDayData[8-i] - '0');
			LPSPI0_TransmitData(nTemp);
		}
	}
}

void DisplayTime (volatile char cHourData[], volatile char cMinuteData[], volatile char cSecondData[])				//Function to display time and alarm
{
	volatile unit32 nTemp;
	
	for (volatile unit32 i = 1; i <= 2; i++)					//Display second
	{
		nTemp = 0x0000;
		nTemp |= (i << 8);
		nTemp |= (cSecondData[2-i] - '0');
		LPSPI0_TransmitData(nTemp);
	}
	
	LPSPI0_TransmitData(0x030A);										//Display '-'
	
	for (volatile unit32 i = 4; i <= 5; i++)				//Display minute
	{
		nTemp = 0x0000;
		nTemp |= (i << 8);
		nTemp |= (cMinuteData[5-i] - '0');
		LPSPI0_TransmitData(nTemp);
	}
	
	LPSPI0_TransmitData(0x060A);											//Display '-'
	
	for (volatile unit32 i = 7; i <= 8; i++)				////Display hour
	{
		nTemp = 0x0000;
		nTemp |= (i << 8);
		nTemp |= ((cHourData[8-i]) - '0');
		LPSPI0_TransmitData(nTemp);
	}
}

void LPIT0_Ch0_IRQHandler (void)								//Timer Channel 0 interrupt
{
	LPIT_Timer->MSR |= (1u);				//Clear flag Channel 0
	
	if ((cSecond[0] == '5') && (cSecond[1] == '9'))
	{
		cSecond[1] = '0';
		cSecond[0] = '0';
		nTimeFlag = 1;
	}
	else if (cSecond[1] == '9')
	{
		cSecond[1] = '0';
		cSecond[0] ++;
	}
	else
	{
		cSecond[1]++;
	}
	
	if ((nStatus == 3) || ((nStatus == 1) && (nCountStatus == 0)))							 //When in button state press 1 and 3
	{
	DisplayTime (cHour, cMinute, cSecond);					//Display every update
	}
	
	if (nAlarmFlag == 1)
	{
		/*When time and alarm are equal*/
		if((cAlarmHour[0] == cHour[0]) && (cAlarmHour[1] == cHour[1]) && (cAlarmMinute[0] == cMinute[0]) && (cAlarmMinute[1] == cMinute[1]) && (cAlarmSecond[0] == cSecond[0]) && (cAlarmSecond[1] == cSecond[1]))
		{
			LPIT_Timer->TCTRL3 |= (1u);								//Timer Channel 3 is enabled
		}
	}
}

void LPIT0_Ch1_IRQHandler (void)								//Timer Channel 1 interrupt
{
	static volatile unit32 nCountTimes = 0;
	
	LPIT_Timer->MSR |= (1u << 1);				//Clear flag Channel 1

	nCountTimes ++;

	if ((nCountTimes == 5) && (nCountStatus == 0))     //Change every 5s
	{
		DisplayDate (cDay, cMonth, cYear);
		nCountStatus ++;
		nCountTimes = 0;
	}
	else if ((nCountTimes == 3) && (nCountStatus == 1))		//Change every 3s
	{
		DisplayTime (cHour, cMinute, cSecond);
		nCountStatus = 0;
		nCountTimes = 0;
	}
}

void LPIT0_Ch2_IRQHandler (void)						//Timer Channel 2 interrupt
{
	volatile unit32 nCount = 0;
	
	LPIT_Timer->MSR |= (1u << 2);				//Clear flag Channel 2
	
	if (nSignal == 1)
	{
		nCount ++;
		nSignal = 0;
		
		if ((nStatus == 2) && (nCount == 1))
		{
			DisplayDate (cDay, cMonth, cYear);
		}
		else if ((nStatus == 3) && (nCount == 1))
		{
			DisplayTime (cHour, cMinute, cSecond);
		}
		else if ((nStatus == 0) && (nCount == 1))
		{
			DisplayTime (cAlarmHour, cAlarmMinute, cAlarmSecond);
		}
	}
}

void LPIT0_Ch3_IRQHandler (void)			//Timer Channel 3 interrupt
{
	LPIT_Timer->MSR |= (1u << 3);				//Clear flag Channel 3
	
	nCountAlarm ++;
	
	GPIOD->PDOR ^= (1u << 16);      //reverse status
}

unit32 ConvertStringToDec( volatile char cSring[])			//Function to convert data string to number
{	
	volatile unit32 nIndexString = 0;
	volatile unit32 nValueNumber = 0;
	
	while(1)
	{
		if (cSring[nIndexString] == '\0')				//The last character
		{
			return nValueNumber;
		}
		
		nValueNumber = (nValueNumber * 10) + (cSring[nIndexString] - '0');
		nIndexString ++;
	}
}

unit32 CheckYear (volatile char cYearArr[])							//Function to check leap year or not
{
	volatile unit32 nYear;
	
	nYear = ConvertStringToDec (cYearArr);				//Convert to interger
	
	if ((nYear % 400) == 0) 
	{
    return 1;
  }
  else if ((nYear % 4) == 0 && (nYear % 100) != 0) 
	{
    return 1;
  }
  else 
	{
    return 0;
  }
}

unit32 CheckFormat (volatile char cData[])				//Function to check format
{
	volatile unit32 nIndexData = 0;
	volatile unit32 nCount = 0;													//Variable to mark location
	volatile unit32 nMarkYear;
	volatile unit32 nMonth;
	volatile unit32 nDay;
	
	if ((cData[nIndexData] == 'd') || (cData[nIndexData] == 'D'))  //Date data
	{
		nIndexData ++;
		
		while (1)
		{
			if (((cData[nIndexData] >= '0') && (cData[nIndexData] <= '3')) && (nCount == 0)) 
			{
				if ((cData[nIndexData] == '3') && ((cData[nIndexData + 1] > '1') && (cData[nIndexData + 1] <= '9')))  // Data > 31 
				{
					return 0;
				}
				
				cDay[0] = cData[nIndexData];
				nIndexData ++;
				nCount++;		
			}
			else if (((cData[nIndexData] >= '0') && (cData[nIndexData] <= '9')) && (nCount == 1))
			{
				cDay[1] = cData[nIndexData];
				nIndexData ++;
				nCount++;
			}
			else if (((cData[nIndexData] >= '0') && (cData[nIndexData] <= '1')) && (nCount == 2))
			{
				if ((cData[nIndexData] == '1') && ((cData[nIndexData + 1] > '2') && (cData[nIndexData + 1] <= '9')))  //Data > 12
				{
					return 0;
				}
				
				cMonth[0] = cData[nIndexData];
				nIndexData ++;
				nCount++;
			}
			else if (((cData[nIndexData] >= '0') && (cData[nIndexData] <= '9')) && (nCount == 3))
			{
				cMonth[1] = cData[nIndexData];
				nIndexData ++;
				nCount++;
			}
			else if (((cData[nIndexData] >= '0') && (cData[nIndexData] <= '9')) && (nCount == 4))
			{
				cYear[0] = cData[nIndexData];
				nIndexData ++;
				nCount++;
			}
			else if (((cData[nIndexData] >= '0') && (cData[nIndexData] <= '9')) && (nCount == 5))
			{
				cYear[1] = cData[nIndexData];
				nIndexData ++;
				nCount++;
			}
			else if (((cData[nIndexData] >= '0') && (cData[nIndexData] <= '9')) && (nCount == 6))
			{
				cYear[2] = cData[nIndexData];
				nIndexData ++;
				nCount++;
			}
			else if (((cData[nIndexData] >= '0') && (cData[nIndexData] <= '9')) && (nCount == 7))
			{
				cYear[3] = cData[nIndexData];
				nIndexData ++;
				nCount++;
				
			}
			else if ((nCount == 8) && (cData[nIndexData] == '\0'))
			{
				nMarkYear = CheckYear (cYear);					//Check leap year
				nMonth = ConvertStringToDec (cMonth);   //Convert to interger
				nDay = ConvertStringToDec (cDay);				//Convert to interger
				
				if (nMonth == 4 || nMonth == 6 || nMonth == 9 || nMonth == 11)    //Month has 30 days
				{
					if (nDay <= 30)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else if ((nMonth == 2) && (nMarkYear == 1))						//February of leap year
				{
					if (nDay <= 29)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else if ((nMonth == 2) && (nMarkYear == 0))						//February of non-leap year
				{
					if (nDay <= 28)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else								//Month has 31 days
				{
					if (nDay <= 31)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}	
			}
			else
			{
				return 0;
			}
		}	
	}
	else if ((cData[0] == 't') || (cData[0] == 'T'))  //Time data
	{
		nIndexData ++;
		
		while (1)
		{
			if (((cData[nIndexData] >= '0') && (cData[nIndexData] <= '2')) && (nCount == 0))
			{
				if ((cData[nIndexData] == '2') && ((cData[nIndexData + 1] > '3') && (cData[nIndexData + 1] <= '9')))  //Data > 24 
				{
					return 0;
				}
				
				cHour[0] = cData[nIndexData];
				nIndexData ++;
				nCount++;		
			}
			else if (((cData[nIndexData] >= '0') && (cData[nIndexData] <= '9')) && (nCount == 1))
			{
				cHour[1] = cData[nIndexData];
				nIndexData ++;
				nCount++;
			}
			else if (((cData[nIndexData] >= '0') && (cData[nIndexData] <= '5')) && (nCount == 2))
			{
				cMinute[0] = cData[nIndexData];
				nIndexData ++;
				nCount++;
			}
			else if (((cData[nIndexData] >= '0') && (cData[nIndexData] <= '9')) && (nCount == 3))
			{
				cMinute[1] = cData[nIndexData];
				nIndexData ++;
				nCount++;
			}
			else if (((cData[nIndexData] >= '0') && (cData[nIndexData] <= '5')) && (nCount == 4))
			{
				cSecond[0] = cData[nIndexData];
				nIndexData ++;
				nCount++;
			}
			else if (((cData[nIndexData] >= '0') && (cData[nIndexData] <= '9')) && (nCount == 5))
			{
				cSecond[1] = cData[nIndexData];
				nIndexData ++;
				nCount++;
			}
			else if ((nCount == 6) && (cData[nIndexData] == '\0'))
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}	
	}
	else if ((cData[0] == 'a') || (cData[0] == 'A'))     //Alarm data
	{
		nIndexData ++;
		
		while (1)
		{
			if (((cData[nIndexData] >= '0') && (cData[nIndexData] <= '2')) && (nCount == 0))
			{
				if ((cData[nIndexData] == '2') && ((cData[nIndexData + 1] > '3') && (cData[nIndexData + 1] <= '9')))   //Data > 24 
				{
					return 0;
				}
				
				cAlarmHour[0] = cData[nIndexData];
				nIndexData ++;
				nCount++;		
			}
			else if (((cData[nIndexData] >= '0') && (cData[nIndexData] <= '9')) && (nCount == 1))
			{
				cAlarmHour[1] = cData[nIndexData];
				nIndexData ++;
				nCount++;
			}
			else if (((cData[nIndexData] >= '0') && (cData[nIndexData] <= '5')) && (nCount == 2))
			{
				cAlarmMinute[0] = cData[nIndexData];
				nIndexData ++;
				nCount++;
			}
			else if (((cData[nIndexData] >= '0') && (cData[nIndexData] <= '9')) && (nCount == 3))
			{
				cAlarmMinute[1] = cData[nIndexData];
				nIndexData ++;
				nCount++;
			}
			else if (((cData[nIndexData] >= '0') && (cData[nIndexData] <= '5')) && (nCount == 4))
			{
				cAlarmSecond[0] = cData[nIndexData];
				nIndexData ++;
				nCount++;
			}
			else if (((cData[nIndexData] >= '0') && (cData[nIndexData] <= '9')) && (nCount == 5))
			{
				cAlarmSecond[1] = cData[nIndexData];
				nIndexData ++;
				nCount++;
			}
			else if ((nCount == 6) && (cData[nIndexData] == '\0'))
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}	
	}
	else
	{
		return 0;
	}
}

void ClearArray(volatile char ClearArray[], volatile unit32 nSize)				//Function to clear array 
{
	for (volatile unit32 i = 0; i <= (nSize - 1); i++)
	{
		ClearArray[i] = 0;
	}
}

