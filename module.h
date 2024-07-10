/*Struct to find address in PCC*/
typedef struct PCC_Str
{
	char cEmpty1[128];
	volatile unsigned int FTFC;
	volatile unsigned int DMAMUX;
	char cEmpty2[8];
	volatile unsigned int FlexCAN0;
	volatile unsigned int FlexCAN1;
	volatile unsigned int FTM3;
	volatile unsigned int ADC1;
	char cEmpty3[12];
	volatile unsigned int FlexCAN2;
	volatile unsigned int LPSPI0;
	volatile unsigned int LPSPI1;
	volatile unsigned int LPSPI2;
	char cEmpty4[8];
	volatile unsigned int PDB1;
	volatile unsigned int CRC;
	char cEmpty5[12];
	volatile unsigned int PDB0;
	volatile unsigned int LPIT;
	volatile unsigned int FTM0;
	volatile unsigned int FTM1;
	volatile unsigned int FTM2;
	volatile unsigned int ADC0;
	char cEmpty6[4];
	volatile unsigned int RTC;
	char cEmpty7[8];
	volatile unsigned int LPTMR0;
	char cEmpty8[32];
	volatile unsigned int PORTA;
	volatile unsigned int PORTB;
	volatile unsigned int PORTC;
	volatile unsigned int PORTD;
	volatile unsigned int PORTE;
	char cEmpty9[24];
	volatile unsigned int SAI0;
	volatile unsigned int SAI1;
	char cEmpty10[16];
	volatile unsigned int FlexIO;
	char cEmpty11[24];
	volatile unsigned int EWM;
	char cEmpty12[16];
	volatile unsigned int LPI2C0;
	volatile unsigned int LPI2C1;
	char cEmpty13[8];
	volatile unsigned int LPUART0;
	volatile unsigned int LPUART1;
	volatile unsigned int LPUART2;
	char cEmpty14[4];
	volatile unsigned int FTM4;
	volatile unsigned int FTM5;
	volatile unsigned int FTM6;
	volatile unsigned int FTM7;
	char cEmpty15[4];
	volatile unsigned int CMP0;
	char cEmpty16[8];
	volatile unsigned int QSPI;
	char cEmpty17[8];
	volatile unsigned int ENET;
}PCC_Type;

#define PCC_Base (0x40065000)
#define PCC ((PCC_Type*) PCC_Base)

/*Struct to find pin address in PORT*/
typedef struct PORT_Str
{
	volatile unsigned int PCR0;
	volatile unsigned int PCR1;
	volatile unsigned int PCR2;
	volatile unsigned int PCR3;
	volatile unsigned int PCR4;
	volatile unsigned int PCR5;
	volatile unsigned int PCR6;
	volatile unsigned int PCR7;
	volatile unsigned int PCR8;
	volatile unsigned int PCR9;
	volatile unsigned int PCR10;
	volatile unsigned int PCR11;
	volatile unsigned int PCR12;
	volatile unsigned int PCR13;
	volatile unsigned int PCR14;
	volatile unsigned int PCR15;
	volatile unsigned int PCR16;
	volatile unsigned int PCR17;
	volatile unsigned int PCR18;
	volatile unsigned int PCR19;
	volatile unsigned int PCR20;
	volatile unsigned int PCR21;
	volatile unsigned int PCR22;
	volatile unsigned int PCR23;
	volatile unsigned int PCR24;
	volatile unsigned int PCR25;
	volatile unsigned int PCR26;
	volatile unsigned int PCR27;
	volatile unsigned int PCR28;
	volatile unsigned int PCR29;
	volatile unsigned int PCR30;
	volatile unsigned int PCR31;
	volatile unsigned int GPCLR;
	volatile unsigned int GPCHR;
	volatile unsigned int GICLR;
	volatile unsigned int GICHR;
	char cEmpty1[16];
	volatile unsigned int ISFR;
	char cEmpty2[28];
	volatile unsigned int DFER;
	volatile unsigned int DFCR;
	volatile unsigned int DFWR;
}PORT_Type;

/*Find pin address in Port A */
#define PORTA_Base (0x40049000)
#define PortA ((PORT_Type*) PORTA_Base)

/*Find pin address in Port B */
#define PORTB_Base (0x4004A000)
#define PortB ((PORT_Type*) PORTB_Base)

/*Find pin address in Port C */
#define PORTC_Base (0x4004B000)
#define PortC ((PORT_Type*) PORTC_Base)

/*Find pin address in Port D */
#define PORTD_Base (0x4004C000)
#define PortD ((PORT_Type*) PORTD_Base)

/*Find pin address in Port E */
#define PORTE_Base (0x4004D000)
#define PortE ((PORT_Type*) PORTE_Base)

/*Struct to find address in GPIO*/
typedef struct GIPO_Str
{
	volatile unsigned int PDOR;
	volatile unsigned int PSOR;
	volatile unsigned int PCOR;
	volatile unsigned int PTOR;
	const volatile unsigned int PDIR;
	volatile unsigned int PDDR;
	volatile unsigned int PIDR;
}GPIO_Type;

/*Find  GPIO address in Port A */
#define GPIOA_Base (0x400FF000)
#define GPIOA ((GPIO_Type*) GPIOA_Base)

/*Find  GPIO address in Port B */
#define GPIOB_Base (0x400FF040)
#define GPIOB ((GPIO_Type*) GPIOB_Base)

/*Find  GPIO address in Port C */
#define GPIOC_Base (0x400FF080)
#define GPIOC ((GPIO_Type*) GPIOC_Base)

/*Find  GPIO address in Port D */
#define GPIOD_Base (0x400FF0C0)
#define GPIOD ((GPIO_Type*) GPIOD_Base)

/*Find  GPIO address in Port E */
#define GPIOE_Base (0x400FF100)
#define GPIOE ((GPIO_Type*) GPIOE_Base)

/*Struct to find address in ISER*/
typedef struct ISER_Str
{
	volatile unsigned int ISER0;
	volatile unsigned int ISER1;
	volatile unsigned int ISER2;
	volatile unsigned int ISER3;
	volatile unsigned int ISER4;
	volatile unsigned int ISER5;
	volatile unsigned int ISER6;
	volatile unsigned int ISER7;
}ISER_Type;

#define ISER_Base (0xE000E100)
#define ISER ((ISER_Type*) ISER_Base)

/*Struct to find address in ICER*/
typedef struct ICER_Str
{
	volatile unsigned int ICER0;
	volatile unsigned int ICER1;
	volatile unsigned int ICER2;
	volatile unsigned int ICER3;
	volatile unsigned int ICER4;
	volatile unsigned int ICER5;
	volatile unsigned int ICER6;
	volatile unsigned int ICER7;
}ICER_Type;

#define ICER_Base (0xE000E180)
#define ICER ((ICER_Type*) ICER_Base)

/*Struct to find address in ISPR*/
typedef struct ISPR_Str
{
	volatile unsigned int ISPR0;
	volatile unsigned int ISPR1;
	volatile unsigned int ISPR2;
	volatile unsigned int ISPR3;
	volatile unsigned int ISPR4;
	volatile unsigned int ISPR5;
	volatile unsigned int ISPR6;
	volatile unsigned int ISPR7;
}ISPR_Type;

#define ISPR_Base (0xE000E200)
#define ISPR ((ISPR_Type*) ISPR_Base)

/*Struct to find address in ICPR*/
typedef struct ICPR_Str
{
	volatile unsigned int ICPR0;
	volatile unsigned int ICPR1;
	volatile unsigned int ICPR2;
	volatile unsigned int ICPR3;
	volatile unsigned int ICPR4;
	volatile unsigned int ICPR5;
	volatile unsigned int ICPR6;
	volatile unsigned int ICPR7;
}ICPR_Type;

#define ICPR_Base (0xE000E280)
#define ICPR ((ICPR_Type*) ICPR_Base)

/*Struct to find address in IABR*/
typedef struct IABR_Str
{
	volatile unsigned int IABR0;
	volatile unsigned int IABR1;
	volatile unsigned int IABR2;
	volatile unsigned int IABR3;
	volatile unsigned int IABR4;
	volatile unsigned int IABR5;
	volatile unsigned int IABR6;
	volatile unsigned int IABR7;
}IABR_Type;

#define IABR_Base (0xE000E300)
#define IABR ((IABR_Type*) IABR_Base)

/*Struct to find address in IPR*/
typedef struct IPR_Str
{
	volatile unsigned int IPR0;
	volatile unsigned int IPR1;
	volatile unsigned int IPR2;
	volatile unsigned int IPR3;
	volatile unsigned int IPR4;
	volatile unsigned int IPR5;
	volatile unsigned int IPR6;
	volatile unsigned int IPR7;
	volatile unsigned int IPR8;
	volatile unsigned int IPR9;
	volatile unsigned int IPR10;
	volatile unsigned int IPR11;
	volatile unsigned int IPR12;
	volatile unsigned int IPR13;
	volatile unsigned int IPR14;
	volatile unsigned int IPR15;
	volatile unsigned int IPR16;
	volatile unsigned int IPR17;
	volatile unsigned int IPR18;
	volatile unsigned int IPR19;
	volatile unsigned int IPR20;
	volatile unsigned int IPR21;
	volatile unsigned int IPR22;
	volatile unsigned int IPR23;
	volatile unsigned int IPR24;
	volatile unsigned int IPR25;
	volatile unsigned int IPR26;
	volatile unsigned int IPR27;
	volatile unsigned int IPR28;
	volatile unsigned int IPR29;
	volatile unsigned int IPR30;
	volatile unsigned int IPR31;
	volatile unsigned int IPR32;
	volatile unsigned int IPR33;
	volatile unsigned int IPR34;
	volatile unsigned int IPR35;
	volatile unsigned int IPR36;
	volatile unsigned int IPR37;
	volatile unsigned int IPR38;
	volatile unsigned int IPR39;
	volatile unsigned int IPR40;
	volatile unsigned int IPR41;
	volatile unsigned int IPR42;
	volatile unsigned int IPR43;
	volatile unsigned int IPR44;
	volatile unsigned int IPR45;
	volatile unsigned int IPR46;
	volatile unsigned int IPR47;
	volatile unsigned int IPR48;
	volatile unsigned int IPR49;
	volatile unsigned int IPR50;
	volatile unsigned int IPR51;
	volatile unsigned int IPR52;
	volatile unsigned int IPR53;
	volatile unsigned int IPR54;
	volatile unsigned int IPR55;
	volatile unsigned int IPR56;
	volatile unsigned int IPR57;
	volatile unsigned int IPR58;
	volatile unsigned int IPR59;
}IPR_Type;

#define IPR_Base (0xE000E400)
#define IPR ((IPR_Type*) IPR_Base)

/*Struct to find address in SYST*/
typedef struct SYST_Str
{
	volatile unsigned int CSR;
	volatile unsigned int RVR;
	volatile unsigned int CVR;
	const volatile unsigned int CALIB;
}SYST_Type;

#define SYST_Base (0xE000E010)
#define SYST ((SYST_Type*) SYST_Base)

/*Struct to find address in SCG*/
typedef struct SCG_Str
{
	const volatile unsigned int VERID;
	const volatile unsigned int PARAM;
	char cEmpty1 [8];
	const volatile unsigned int CSR;
	volatile unsigned int RCCR;
	volatile unsigned int VCCR;
	volatile unsigned int HCCR;
	volatile unsigned int CLKOUTCNFG;
	char cEmpty2 [220];	
	volatile unsigned int SOSCCSR;
	volatile unsigned int SOSCDIV;
	volatile unsigned int SOSCCFG;
	char cEmpty3 [244];
	volatile unsigned int SIRCCSR;
	volatile unsigned int SIRCDIV;
	volatile unsigned int SIRCCFG;
	char cEmpty4 [244];
	volatile unsigned int FIRCCSR;
	volatile unsigned int FIRCDIV;
	volatile unsigned int FIRCCFG;
	char cEmpty5 [756];
	volatile unsigned int SPLLCSR;
	volatile unsigned int SPLLDIV;
	volatile unsigned int SPLLCFG;
}SCG_Type;

#define SCG_Base (0x40064000)
#define SCG ((SCG_Type*) SCG_Base)


/*Struct to find address in LPUART*/
typedef struct LPUART_Str
{
	const volatile unsigned int VERID;
	const volatile unsigned int PARAM;
	volatile unsigned int GLOBAL;
	volatile unsigned int PINCFG;
	volatile unsigned int BAUD;
	volatile unsigned int STAT;
	volatile unsigned int CTRL;
	volatile unsigned int DATA;
	volatile unsigned int MATCH;
	volatile unsigned int MODIR;
	volatile unsigned int FIFO;
	volatile unsigned int WATER;
}LPUART_Type;

/*Find address in LPUART0 */
#define LPUART0_Base (0x4006A000)
#define LPUART_0 ((LPUART_Type*) LPUART0_Base)

/*Find address in LPUART1 */
#define LPUART1_Base (0x4006B000)
#define LPUART_1 ((LPUART_Type*) LPUART1_Base)

/*Find address in LPUART2 */
#define LPUART2_Base (0x4006C000)
#define LPUART_2 ((LPUART_Type*) LPUART2_Base)


/*Struct to find address in LPUSPI*/
typedef struct LPSPI_Str
{
	const volatile unsigned int VERID;
	const volatile unsigned int PARAM;
	char cTemp1[8];
	volatile unsigned int CR;
	volatile unsigned int SR;
	volatile unsigned int IER;
	volatile unsigned int DER;
	volatile unsigned int CFGR0;
	volatile unsigned int CFGR1;
	char cTemp2[8];
	volatile unsigned int DMRO;
	volatile unsigned int DMR1;
	char cTemp3[8];
	volatile unsigned int CCR;
	char cTemp4[20];
	volatile unsigned int FCR;
	volatile unsigned int FSR;
	volatile unsigned int TCR;
	volatile unsigned int TDR;
	char cTemp5[8];
	volatile unsigned int RSR;
	volatile unsigned int RDR;
}LPSPI_Type;

/*Find address in LPSPI0 */
#define LPSPI0_Base (0x4002C000)
#define LPSPI_0 ((LPSPI_Type*) LPSPI0_Base)

/*Find address in LPSPI1 */
#define LPSPI1_Base (0x4002D000)
#define LPSPI_1 ((LPSPI_Type*) LPSPI1_Base)

/*Find address in LPSPI2 */
#define LPSPI2_Base (0x4002E000)
#define LPSPI_2 ((LPSPI_Type*) LPSPI2_Base)

/*Struct to find address in LPIT*/
typedef struct LPIT_Str
{
	const volatile unsigned int VERID;
	const volatile unsigned int PARAM;
	volatile unsigned int MCR;
	volatile unsigned int MSR;
	volatile unsigned int MIER;
	volatile unsigned int SETTEN;
	volatile unsigned int CLRTEN;
	char cTemp1[4];
	volatile unsigned int TVAL0;
	const volatile unsigned int CVAL0;
	volatile unsigned int TCTRL0;
	char cTemp2[4];
	volatile unsigned int TVAL1;
	const volatile unsigned int CVAL1;
	volatile unsigned int TCTRL1;
	char cTemp3[4];
	volatile unsigned int TVAL2;
	const volatile unsigned int CVAL2;
	volatile unsigned int TCTRL2;
	char cTemp4[4];
	volatile unsigned int TVAL3;
	const volatile unsigned int CVAL3;
	volatile unsigned int TCTRL3;
}LPIT_Type;

/*Find address in LPIT */
#define LPIT_Base (0x40037000)
#define LPIT_Timer ((LPIT_Type*) LPIT_Base)
