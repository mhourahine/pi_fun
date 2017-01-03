/*
* gpfsel_list.c - lists the current values of the GPFSELn registers.
* 
* Copyright 2012 Kevin Sangeelee.
* Released as GPLv2, see <http://www.gnu.org/licenses/>
*
* This code lists the current GPIO Function Select settings, and the
* configuration of the PADS registers.. Use at your own risk or not
* at all.
*/
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>

#include "gpfsel_list.h"

struct bcm2835_peripheral {
	unsigned long addr_p;	// Physical address
	int mem_fd;		// File Descriptor for /dev/mem
	void *map;		// The mmap() 
	volatile unsigned int *addr;
};

struct bcm2835_peripheral gpio = {GPIO_BASE};
struct bcm2835_peripheral pads = {PADS_BASE};

// Some forward declarations...
int map_peripheral(struct bcm2835_peripheral *p);
void unmap_peripheral(struct bcm2835_peripheral *p);

////////////////
//  main()
////////////////
int main(int argc, char *argv[]) {

	if(map_peripheral(&gpio) == -1 || map_peripheral(&pads) == -1) {
		printf("Failed to map the physical GPIO and PADS registers into the virtual memory space.\n");
		return -1;
	}

	unsigned int n, i, val;

	// Display PADS settings
	char *ranges[] = { " 0-27", "28-45", "46-53" };
	
	printf("PADS configuration\n");
	
	for(n=0; n < 3; n++) {
		val = *(pads.addr + 11 + n);
		
		printf("  GPIO %s: DRIVE %2dma, HYST %s, SLEW %s\n",
			ranges[n],
			(val & 7) * 2 + 2,
			val & 8 ? "On" : "Off",
			val & 16 ? "Off" : "On");
	}
	
	printf("GPFSELn states\n");
	
	// Loop for GPFSEL0 to GPFSEL5
	for(n=0; n < 6; n++) {
	
		// Mask out reserved bits for completeness (irrelevant here, but good practice elsewhere)
		val = *(gpio.addr + n) & (n < 5 ? 0x3fffffff : 0x00000fff);
		
		// Loop for the 9 bit-triplets in each GPFSELn register
		for(i=0; i < 10; i++) {
		
			int fsel_num = n * 10 + i;	// The logical FSEL number
			int bit_pos = i*3;	// The position of the least significant bit in the triplet
			unsigned int triplet = (val >> bit_pos) & 0x7;	// Extract the bit- triplet 

			char description[128];	// Buffer to build a description string

			// For 0 and 1 (input and output), we display the direction, for 2..7 we display the
			// function name and the function description (e.g. ALT0 - SPI0_MOSI).
			if(triplet < 2) {
				sprintf(description, "%s - [%s]", gpfsel_names[triplet],
					( fsel_num < 32 ? GPLEV0 & (1 << fsel_num) : GPLEV1 & (1 << (fsel_num - 32)) ) ? "High" : "Low");
			} else {
				sprintf(description, "%s - %s", gpfsel_names[triplet],
					gpfsel_desc[fsel_num][gpfsel_conv[triplet] + 2]);
			}

			printf("  FSEL%d (GPFSEL%d[%02d-%02d]) = %d (%s)\n",
			fsel_num, n, bit_pos, bit_pos+2, triplet,
			description);

			if(n == 5 && i == 3)	// break out of loop after FSEL53 (last triplet)
				break;
		}
	}
	
	unmap_peripheral(&pads);
	unmap_peripheral(&gpio);
	
	// end of main()
}

// Exposes the physical address defined in the passed structure using mmap on /dev/mem
int map_peripheral(struct bcm2835_peripheral *p)
{
	// Open /dev/mem 
	if ((p->mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0) {
		printf("Failed to open /dev/mem, try checking permissions.\n");
		return -1;
	}

	p->map = mmap(
	NULL,
	BLOCK_SIZE,
	PROT_READ|PROT_WRITE,
	MAP_SHARED,
	p->mem_fd,  // File descriptor to physical memory virtual file '/dev/mem'
	p->addr_p	  // Address in physical map that we want this memory block to expose
	);

	if (p->map == MAP_FAILED) {
		perror("mmap");
		return -1;
	}

	p->addr = (volatile unsigned int *)p->map;

	return 0;
}

void unmap_peripheral(struct bcm2835_peripheral *p) {

	munmap(p->map, BLOCK_SIZE);
	close(p->mem_fd);
}
