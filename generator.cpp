/********************************************************************
 * Copyright (C) 2009 by Ensimag and Verimag                        *
 * Initial author: Joris Collomb                                    *
 ********************************************************************/

#include "generator.h"
#include "constants.h"
#include "LCDC_registermap.h"

#define DEBUG false

using namespace std;

void Generator::thread(void) {

	ensitlm::data_t dataRom, dataRam1, dataRam2;

	initiator.write(MAP_LCD_BASE + LCDC_START_REG, 	0X00000001);
	initiator.write(MAP_LCD_BASE + LCDC_ADDR_REG, 	MAP_VIDEO_MEMORY_BASE);

//BOUCLE MEMOIRE BLANCHE
	// for ( int i = 0; i < IMG_SIZE/4 ; i ++) {		//pixel sur 1 octet
	// 	initiator.write(addr + 4*i, PXL_4_WHITE);
	// }

	while(1){

	//BOUCLE IMAGE ROM IMG_SIZE/8
		for ( int i = 0; i < IMG_SIZE/8 ; i ++) {
			initiator.read(MAP_ROM_BASE + 4*i , dataRom);

			dataRam1= (dataRom >> 4*3 & 0xF0 			)	| (dataRom >> 4*2 & 0xF000 		)|
								(dataRom >> 4*1 & 0xF00000	)	| (dataRom >> 4*0 & 0xF0000000);

			dataRam2= (dataRom << 4*1 & 0xF0 			)	| (dataRom << 4*2 & 0xF000 		)|
								(dataRom << 4*3 & 0xF00000	)	| (dataRom << 4*4 & 0xF0000000);

			// Affichage standard
			// initiator.write	(MAP_VIDEO_MEMORY_BASE + 8*i 	,	dataRam1);
			// initiator.write	(MAP_VIDEO_MEMORY_BASE + 8*i+4,	dataRam2);

			// Affichage avec defillement
			initiator.write	(MAP_VIDEO_MEMORY_BASE +
				((8*i + 		IMG_WIDTH * off)%(IMG_SIZE)) ,	dataRam1);
			initiator.write	(MAP_VIDEO_MEMORY_BASE +
				((8*i +4 +	IMG_WIDTH * off)%(IMG_SIZE)) ,	dataRam2);
		}

		wait(display_done);
		wait(1,sc_core::SC_SEC);
		off++;
	}
}

void Generator::handling_lcd_interrupt(){
	if(display_int.posedge()){
	initiator.write(MAP_LCD_BASE + LCDC_INT_REG, 0X00000000);
	cout << "generator notified by lcd" << endl;
	display_done.notify();
	}
}

Generator::Generator(sc_core::sc_module_name name) : sc_core::sc_module(name) {
	SC_THREAD(thread);
	SC_METHOD(handling_lcd_interrupt);
	sensitive << display_int;
}
