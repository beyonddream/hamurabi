#ifndef HAMURABI_H
#define HAMURABI_H

#include "banned.h"
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define RAND(n, x) do {	\
	srand(time(NULL));	\
	*(x) = (uint8_t) ((double) rand()/(double) (RAND_MAX + 1u) * (n));	\
} while (0);

typedef struct city_of_sumeria {
	uint8_t bushels_preserved;
	uint8_t bushels_destroyed;
	uint8_t bushels_per_acre;
	uint8_t year;
	uint8_t people_starved;
	uint8_t people_arrived;
	uint8_t population;
} city_of_sumeria_t;

/**
 * Start the game.
 */
void hamurabi_start(void);

/**
 * Get a new city object.
 */
city_of_sumeria_t *city_new(void);

/**
 * Destroy the city object.
 */
void city_destroy(city_of_sumeria_t *city_of_sumeria);

/**
 * get the population of the city.
 */
uint8_t get_population(const city_of_sumeria_t *city);

/**
 * get the current year
 */
uint8_t get_year(const city_of_sumeria_t *city);

/**
 * get the number of people arrived at the city.
 */
uint8_t get_people_arrived(const city_of_sumeria_t *city);

/**
 * get the number of people starved in a given year.
 */
uint8_t get_people_starved(const city_of_sumeria_t *city);


#endif /* HAMURABI_H */
