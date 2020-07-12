#ifndef HAMURABI_H
#define HAMURABI_H

#include "banned.h"
#include <stdint.h>

typedef struct city_of_sumeria {
	uint8_t bushels_preserved;
	uint8_t bushels_destroyed;
	uint8_t bushels_per_acre;
	uint8_t year;
	uint8_t people_starved;
	uint8_t people_arrived;
	uint8_t population;
} city_of_sumeria_t;

// api's
void hamurabi_init(void);
const city_of_sumeria_t *city_new(void);
void city_destroy(const city_of_sumeria_t *city_of_sumeria);

#endif /* HAMURABI_H */
