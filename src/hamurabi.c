#include "../include/hamurabi.h"
#include <stdarg.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

city_of_sumeria_t *city_new(void)
{
	city_of_sumeria_t *city;

	city = (city_of_sumeria_t *) malloc(sizeof (city_of_sumeria_t));
	if (city == NULL) {
		printf("Unable to intialize city. Exiting...\n");
		exit(EXIT_FAILURE);
	}

	memset((void *) city, 0, sizeof(city_of_sumeria_t));

	city->bushels_preserved = (uint8_t) 2800;
	city->bushels_destroyed = (uint8_t) 200;
	city->bushels_per_acre  = (uint8_t) 3;
	city->year = (uint8_t) 0;
	city->people_starved = (uint8_t) 0;
	city->people_arrived = (uint8_t) 5;
	city->population = (uint8_t) 95;

	return city;
}

void city_destroy(city_of_sumeria_t *city_of_sumeria)
{

	free((void *) city_of_sumeria);
	return;
}

void hamurabi_end(void)
{

	for (int i = 0; i < 10; i++) {
		fprintf(stdout, "\a"); // beep sound
	}

	printf("So long for now.\n");
	return;
}

void hamurabi_illegal_input(void)
{

	printf("Hamurabi: I cannot do "
	    "what you wish. Get yourself "
	    "another steward!!!!!\n");
	return;
}

void hamurabi_illegal_bushels_input(uint8_t bushels_total)
{

	printf("Hamurabi: Think again. You have only "
		"%" PRIu8 " bushels of grain. Now then, ", bushels_total);
	return;
}

void hamurabi_illegal_acres_input(uint8_t acres_total)
{

	printf("Hamurabi: Think again. You own only "
		"%" PRIu8 " acres. Now then, ", acres_total);
	return;
}

int hamurabi_random_event_value(void)
{
	int c;
	RAND(1, &c);

	c = ((int) (c * 5)) + 1;

	return c;
}

uint8_t get_population(const city_of_sumeria_t *city)
{

	return city->population;
}

uint8_t get_year(const city_of_sumeria_t *city)
{

	return city->year;
}

uint8_t get_people_arrived(const city_of_sumeria_t *city)
{

	return city->people_arrived;
}

uint8_t get_people_starved(const city_of_sumeria_t *city)
{

	return city->people_starved;
}
void hamurabi_start(void)
{
	uint8_t d; // people starved
	uint8_t z; // year
	uint8_t i; // people came to the city
	uint8_t q; // acres to buy/sell
	uint8_t p; // population of the city

	printf("Try your hand at governing ancient sumeria,"
	    "successfully for a 10-yr term of office.\n");

	city_of_sumeria_t *city = city_new();

	z = get_year(city);
	i = get_people_arrived(city);
	d = get_people_starved(city);
	p = get_population(city);
	q = 0;

	for(;;) {
		printf("Hamurabi: I beg to report to you, "
		    "In year %" PRIu8 ", "
		    "%" PRIu8 " people starved, "
		    "%" PRIu8 " came to the city.\n",
		    z, d, i);

		z = z + 1;
		p = p + i;

		if (q <= 0) {
			printf("A horrible plague struck! "
				"Half the people died.\n");
			p = (uint8_t) (p / 2);
		}

		printf("population is now %" PRIu8 "\n", p);
	}

end:
	hamurabi_end();

cleanup:
	city_destroy(city);

	return;
}
