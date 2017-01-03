
#define IOBASE   0x20000000

#define GPIO_BASE (IOBASE + 0x200000)

#define GPFSEL0	*(gpio.addr + 0)
#define GPFSEL1	*(gpio.addr + 1)
#define GPFSEL2	*(gpio.addr + 2)
#define GPFSEL3	*(gpio.addr + 3)
#define GPFSEL4	*(gpio.addr + 4)
#define GPFSEL5	*(gpio.addr + 5)
// Reserved @ word offset 6
#define GPSET0	*(gpio.addr + 7)
#define GPSET1	*(gpio.addr + 8)
// Reserved @ word offset 9
#define GPCLR0	*(gpio.addr + 10)
#define GPCLR1	*(gpio.addr + 11)
// Reserved @ word offset 12
#define GPLEV0	*(gpio.addr + 13)
#define GPLEV1	*(gpio.addr + 14)

#define PADS_BASE (IOBASE + 0x100000)

#define PADS0	*(pads.addr + 11)
#define PADS1	*(pads.addr + 12)
#define PADS2	*(pads.addr + 13)

#define PAGESIZE 4096
#define BLOCK_SIZE 4096

/*  Textual names for each GPFSELn bit triplet (0 - 7) */
char *gpfsel_names[] = { "GPIO In", "GPIO Out", "ALT5", "ALT4", "ALT0", "ALT1", "ALT2", "ALT3" };

/*  Lookup to convert from GPFSELn bit triplet to an index in the gpfsel_desc array */
unsigned char gpfsel_conv[8] = {0, 0, 5, 4, 0, 1, 2, 3 };

/* Array of pin and alternate function descriptions, as per datasheet */
char *gpfsel_desc[][8] = {
	{ "GPIO0","High","SDA0","SA5","<reserved>","  -  ","  -  ","  -  " },
	{ "GPIO1","High","SCL0","SA4","<reserved>","  -  ","  -  ","  -  " },
	{ "GPIO2","High","SDA1","SA3","<reserved>","  -  ","  -  ","  -  " },
	{ "GPIO3","High","SCL1","SA2","<reserved>","  -  ","  -  ","  -  " },
	{ "GPIO4","High","GPCLK0","SA1","<reserved>","  -  ","  -  ","ARM_TDI" },
	{ "GPIO5","High","GPCLK1","SA0","<reserved>","  -  ","  -  ","ARM_TDO" },
	{ "GPIO6","High","GPCLK2","SOE_N/SE","<reserved>","  -  ","  -  ","ARM_RTCK" },
	{ "GPIO7","High","SPI0_CE1_N","SWE_N/SRW_N","<reserved>","  -  ","  -  ","  -  " },
	{ "GPIO8","High","SPI0_CE0_N","SD0","<reserved>","  -  ","  -  ","  -  " },
	{ "GPIO9","Low","SPI0_MISO","SD1","<reserved>","  -  ","  -  ","  -  " },
	{ "GPIO10","Low","SPI0_MOSI","SD2","<reserved>","  -  ","  -  ","  -  " },
	{ "GPIO11","Low","SPI0_SCLK","SD3","<reserved>","  -  ","  -  ","  -  " },
	{ "GPIO12","Low","PWM0","SD4","<reserved>","  -  ","  -  ","ARM_TMS" },
	{ "GPIO13","Low","PWM1","SD5","<reserved>","  -  ","  -  ","ARM_TCK" },
	{ "GPIO14","Low","TXD0","SD6","<reserved>","  -  ","  -  ","TXD1" },
	{ "GPIO15","Low","RXD0","SD7","<reserved>","  -  ","  -  ","RXD1" },
	{ "GPIO16","Low","<reserved>","SD8","<reserved>","CTS0","SPI1_CE2_N","CTS1" },
	{ "GPIO17","Low","<reserved>","SD9","<reserved>","RTS0","SPI1_CE1_N","RTS1" },
	{ "GPIO18","Low","PCM_CLK","SD10","<reserved>","BSCSL SDA/MOSI","SPI1_CE0_N","PWM0" },
	{ "GPIO19","Low","PCM_FS","SD11","<reserved>","BSCSL SCL/SCLK","SPI1_MISO","PWM1" },
	{ "GPIO20","Low","PCM_DIN","SD12","<reserved>","BSCSL/MISO","SPI1_MOSI","GPCLK0" },
	{ "GPIO21","Low","PCM_DOUT","SD13","<reserved>","BSCSL/CE_N","SPI1_SCLK","GPCLK1" },
	{ "GPIO22","Low","<reserved>","SD14","<reserved>","SD1_CLK","ARM_TRST","  -  " },
	{ "GPIO23","Low","<reserved>","SD15","<reserved>","SD1_CMD","ARM_RTCK","  -  " },
	{ "GPIO24","Low","<reserved>","SD16","<reserved>","SD1_DAT0","ARM_TDO","  -  " },
	{ "GPIO25","Low","<reserved>","SD17","<reserved>","SD1_DAT1","ARM_TCK","  -  " },
	{ "GPIO26","Low","<reserved>","<reserved>","<reserved>","SD1_DAT2","ARM_TDI","  -  " },
	{ "GPIO27","Low","<reserved>","<reserved>","<reserved>","SD1_DAT3","ARM_TMS","  -  " },
	{ "GPIO28","-","SDA0","SA5","PCM_CLK","<reserved>","  -  ","  -  " },
	{ "GPIO29","-","SCL0","SA4","PCM_FS","<reserved>","  -  ","  -  " },
	{ "GPIO30","Low","<reserved>","SA3","PCM_DIN","CTS0","  -  ","CTS1" },
	{ "GPIO31","Low","<reserved>","SA2","PCM_DOUT","RTS0","  -  ","RTS1" },
	{ "GPIO32","Low","GPCLK0","SA1","<reserved>","TXD0","  -  ","TXD1" },
	{ "GPIO33","Low","<reserved>","SA0","<reserved>","RXD0","  -  ","RXD1" },
	{ "GPIO34","High","GPCLK0","SOE_N/SE","<reserved>","<reserved>","  -  ","  -  " },
	{ "GPIO35","High","SPI0_CE1_N","SWE_N/SRW_N","  -  ","<reserved>","  -  ","  -  " },
	{ "GPIO36","High","SPI0_CE0_N","SD0","TXD0","<reserved>","  -  ","  -  " },
	{ "GPIO37","Low","SPI0_MISO","SD1","RXD0","<reserved>","  -  ","  -  " },
	{ "GPIO38","Low","SPI0_MOSI","SD2","RTS0","<reserved>","  -  ","  -  " },
	{ "GPIO39","Low","SPI0_SCLK","SD3","CTS0","<reserved>","  -  ","  -  " },
	{ "GPIO40","Low","PWM0","SD4","  -  ","<reserved>","SPI2_MISO","TXD1" },
	{ "GPIO41","Low","PWM1","SD5","<reserved>","<reserved>","SPI2_MOSI","RXD1" },
	{ "GPIO42","Low","GPCLK1","SD6","<reserved>","<reserved>","SPI2_SCLK","RTS1" },
	{ "GPIO43","Low","GPCLK2","SD7","<reserved>","<reserved>","SPI2_CE0_N","CTS1" },
	{ "GPIO44","-","GPCLK1","SDA0","SDA1","<reserved>","SPI2_CE1_N","  -  " },
	{ "GPIO45","-","PWM1","SCL0","SCL1","<reserved>","SPI2_CE2_N","  -  " },
	{ "GPIO46","High","<Internal>","  -  ","  -  ","  -  ","  -  ","  -  " },
	{ "GPIO47","High","<Internal>","  -  ","  -  ","  -  ","  -  ","  -  " },
	{ "GPIO48","High","<Internal>","  -  ","  -  ","  -  ","  -  ","  -  " },
	{ "GPIO49","High","<Internal>","  -  ","  -  ","  -  ","  -  ","  -  " },
	{ "GPIO50","High","<Internal>","  -  ","  -  ","  -  ","  -  ","  -  " },
	{ "GPIO51","High","<Internal>","  -  ","  -  ","  -  ","  -  ","  -  " },
	{ "GPIO52","High","<Internal>","  -  ","  -  ","  -  ","  -  ","  -  " },
	{ "GPIO53","High","<Internal>","  -  ","  -  ","  -  ","  -  ","  -  " }
};
