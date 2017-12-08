/********************************************************************
 * Copyright (C) 2009 by Ensimag and Verimag			    *
 * Initial author: Joris Collomb					    *
 ********************************************************************/

#include "ensitlm.h"
#include "generator.h"
#include "memory.h"
#include "bus.h"
#include "LCDC.h"
#include "ROM.h"

#include "constants.h"

#include <sysc/kernel/sc_time.h>

int sc_main(int argc, char **argv) {
	(void)argc;
	(void)argv;

	using namespace sc_core;
	/*
	  +---------+	 +-------------+    +--------+
	  |	   +++	+-+	      +++  +++	     |
	  | Alice  | +--+ |  Router   | +--+ |	Bob  |
	  |	   +++	+-+	      +++  +++	     |
	  +---------+	 +-------------+    +--------+
	*/

	Generator g("generator");
	Bus bus("bus");
  Memory m("memory",0x15400);
	LCDC lcd("LCD", sc_time(1.0 / 25, SC_SEC));
	ROM rom("ROM_image");

	sc_signal < bool , SC_MANY_WRITERS > irq_signal ( "IRQ" );


	/* Bob is mapped at addresses [0, 100[, i.e. ... */
	bus.map(m.target, 					MAP_MEMORY_BASE,  MAP_MEMORY_LENGTH);
	bus.map(lcd.target_socket, 	MAP_LCD_BASE,  		MAP_LCD_LENGTH);
	bus.map(rom.socket,				 	MAP_ROM_BASE,  		MAP_ROM_LENGTH);

	/* connect components to the bus */
	g.initiator.bind(bus.target);
	bus.initiator.bind(m.target);
	bus.initiator.bind(lcd.target_socket);
	lcd.initiator_socket.bind(bus.target);
	bus.initiator.bind(rom.socket);

	//Connection signal d'interruption
	lcd.display_int.bind(irq_signal);
	g.display_int.bind(irq_signal);


	/* and start simulation */
	sc_core::sc_start();
	return 0;
}
