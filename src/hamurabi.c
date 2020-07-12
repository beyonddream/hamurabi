#include "../include/hamurabi.h"
#include <stdarg.h>
#include <stdio.h>
#include <inttypes.h>

void start_game(void) {
	uint8_t d; // people starved
	uint8_t z; // year
	uint8_t i; // people came to the city

	printf("Try your hand at governing ancient sumeria,"
	    "successfully for a 10-yr term of office.\n");
	z = 0, i = 5, d = 0;
	for(;;) {
		printf("Hamurabi: I beg to report to you, "
		    "In year %" PRIu8 ", "
		    "%" PRIu8 " people starved, "
		    "%" PRIu8 " came to the city.\n",
		    z, d, i);
	}
}
