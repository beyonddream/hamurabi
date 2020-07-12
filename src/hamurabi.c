#include "../include/hamurabi.h"
#include <stdarg.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

const city_of_sumeria_t *city_new(void)
{
	const city_of_sumeria_t *city;

	city = (const city_of_sumeria_t *) malloc(sizeof (city_of_sumeria_t));

	if (city == NULL) {
		printf("Unable to intialize city. Exiting...\n");
		exit(EXIT_FAILURE);
	}

	return city;
}


void hamurabi_init(void)
{
	uint8_t d; // people starved
	uint8_t z; // year
	uint8_t i; // people came to the city
	uint8_t q; // acres to buy/sell
	uint8_t p; // population of the city

	printf("Try your hand at governing ancient sumeria,"
	    "successfully for a 10-yr term of office.\n");

	z = 0, i = 5, d = 0, q = 0; p = 0;

	for(;;) {
		printf("Hamurabi: I beg to report to you, "
		    "In year %" PRIu8 ", "
		    "%" PRIu8 " people starved, "
		    "%" PRIu8 " came to the city.\n",
		    z, d, i);

		z = z + 1;

		if (q > 0) {

		}

	}
}
