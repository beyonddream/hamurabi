#ifndef HAMURABI_H
#define HAMURABI_H

#include "banned.h"
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define RAND(n, x)         \
	do {                   \
		srand(time(NULL)); \
		*(x) = RANDOM(n);  \
	} while (0);

#define RANDOM(n) (uint16_t)(((double)rand() / (double)(RAND_MAX + 1u)) * (n))

typedef struct city_of_sumeria city_of_sumeria_t;
typedef enum city_event_type city_event_type;

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
uint16_t get_population(const city_of_sumeria_t *city);

/**
 * get the current year
 */
uint16_t get_year(const city_of_sumeria_t *city);

/**
 * get the number of people arrived at the city.
 */
uint16_t get_people_arrived(const city_of_sumeria_t *city);

/**
 * get the number of people starved in a given year.
 */
uint16_t get_people_starved(const city_of_sumeria_t *city);

/**
 * get bushels per acre
 */
uint16_t get_bushels_per_acre(const city_of_sumeria_t *city);

/**
 * get bushels preserved
 */
uint16_t get_bushels_preserved(const city_of_sumeria_t *city);

/**
 * get bushels destroyed
 */
uint16_t get_bushels_destroyed(const city_of_sumeria_t *city);

/**
 * check and induce plague based on the value of acres_buy_or_sell
 */
city_event_type check_plague(uint16_t acres_buy_or_sell, city_of_sumeria_t *city);

/**
 * check and include rate menaced that destroy bushels
 */
city_event_type check_rat_menace(city_of_sumeria_t *city);

/**
 * check and return the judgement type
 */
city_event_type check_judgement(uint16_t population_starved_per_yr, uint16_t acres_per_person);

#endif /* HAMURABI_H */
