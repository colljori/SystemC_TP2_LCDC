/********************************************************************
 * Copyright (C) 2009 by Ensimag and Verimag			    *
 * Initial author: Matthieu Moy					    *
 ********************************************************************/

#include "ensitlm.h"
#include "bus.h"

struct Generator : sc_core::sc_module {
	ensitlm::initiator_socket<Generator> initiator;
	sc_core::sc_in <bool> display_int;
	sc_core::sc_event display_done;

	int off=0;

	void thread(void);
	void handling_lcd_interrupt(void);

	SC_CTOR(Generator);
};
