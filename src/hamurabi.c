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

	city->bushels_preserved = (uint16_t) 2800;
	city->bushels_destroyed = (uint16_t) 200;
	city->bushels_per_acre  = (uint16_t) 3;
	city->year = (uint16_t) 1;
	city->people_starved = (uint16_t) 0;
	city->people_arrived = (uint16_t) 5;
	city->population = (uint16_t) 95;

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

void hamurabi_illegal_bushels_input(uint16_t bushels_total)
{

	printf("Hamurabi: Think again. You have only "
		"%" PRIu16 " bushels of grain. Now then, ", bushels_total);
	return;
}

void hamurabi_illegal_acres_input(uint16_t acres_total)
{

	printf("Hamurabi: Think again. You own only "
		"%" PRIu16 " acres. Now then, ", acres_total);
	return;
}

int hamurabi_random_event_value(void)
{
	int c;
	RAND(1, &c);

	c = ((int) (c * 5)) + 1;

	return c;
}

uint16_t get_population(const city_of_sumeria_t *city)
{

	return city->population;
}

uint16_t get_year(const city_of_sumeria_t *city)
{

	return city->year;
}

uint16_t get_people_arrived(const city_of_sumeria_t *city)
{

	return city->people_arrived;
}

uint16_t get_people_starved(const city_of_sumeria_t *city)
{

	return city->people_starved;
}

uint16_t get_bushels_per_acre(const city_of_sumeria_t *city)
{

	return city->bushels_per_acre;
}

uint16_t get_bushels_preserved(const city_of_sumeria_t *city)
{

	return city->bushels_preserved;
}

uint16_t get_bushels_destroyed(const city_of_sumeria_t *city)
{

	return city->bushels_destroyed;
}

void hamurabi_start(void)
{
	uint16_t d; // people starved
	uint16_t z; // year
	uint16_t i; // people came to the city
	uint16_t q; // acres to buy/sell
	uint16_t p; // population of the city
	uint16_t s; // bushels preserved
	uint16_t e; // bushels destroyed
	uint16_t h; // total bushels
	uint16_t y; // bushels per acre
	uint16_t a; // acres owned by city
	uint16_t c; // random value
	uint16_t p1; // percentage of population starved per year
	uint16_t d1;// total people who died
	uint16_t l;  // acres per person

	printf("Try your hand at governing ancient sumeria,"
	    "successfully for a 10-yr term of office.\n");

	city_of_sumeria_t *city = city_new();

	z = get_year(city);
	i = get_people_arrived(city);
	d = get_people_starved(city);
	p = get_population(city);
	s = get_bushels_preserved(city);
	e = get_bushels_destroyed(city);
	h = s + e;
	y = get_bushels_per_acre(city);
	a = h / y;
	q = 1;

	for(;;) {
		printf("Hamurabi: I beg to report to you, "
		    "In year %" PRIu16 ", "
		    "%" PRIu16 " people starved, "
		    "%" PRIu16 " came to the city.\n",
		    z, d, i);

		z = z + 1;
		p = p + i;

		if (q <= 0) {
			printf("A horrible plague struck! "
				"Half the people died.\n");
			p = (uint16_t) (p / 2);
		}

		printf("population is now %" PRIu16 "\n", p);
		printf("The city owns %" PRIu16 " acres.\n", a);
		printf("You have harvested %" PRIu16 " bushels per acre.\n", y);
		printf("Rats ate %" PRIu16 " bushels.\n", e);
		printf("You now have %" PRIu16 " bushels in store.\n", s);

		if (z < 11) {
			RAND(10, &c);
			y = c + 17;
			printf("Land is trading at %" PRIu16 " bushels per acre.\n", y);

buy_acres:
			printf("How many acres do you wish to buy?");
			scanf("%" PRIu16, &q);
			if (q < 0) {
				hamurabi_illegal_input();
				goto end;
			}
			if ((y * q) > s) {
				hamurabi_illegal_bushels_input(s);
				goto buy_acres;
			}
			if (q != 0) {
				a = a + q;
				s = s - (y * q);
				c = 0;
				goto feed_people;
			}
sell_acres:
			printf("How many acres do you wish to sell?");
			scanf("%" PRIu16, &q);
			if (q < 0) {
				hamurabi_illegal_input();
				goto end;
			}
			if (q >= a) {
				hamurabi_illegal_acres_input(a);
				goto sell_acres;
			}

			a = a - q;
			s = s + (y * q);
			c = 0;
feed_people:
			printf("How many bushels do you wish to feed your people?");
			scanf("%" PRIu16, &q);
			if (q < 0) {
				hamurabi_illegal_input();
				goto end;
			}
			if (q > s) {
				hamurabi_illegal_bushels_input(s);
				goto feed_people;
			}

			s = s - q;
			c = 1;
plant_seeds:
			printf("How many acres do you wish to plant with seed?");
			scanf("%" PRIu16, &d);
			if (d < 0) {
				hamurabi_illegal_input();
				goto end;
			}
			if (d == 0) {
				goto bounty_harvest;
			}
			if (d > a) {
				hamurabi_illegal_acres_input(a);
				goto plant_seeds;
			}
			if (((uint16_t) (d / 2)) >= s) {
				hamurabi_illegal_bushels_input(s);
				goto plant_seeds;
			}
			if (d >= (10 * p)) {
				printf("But you have only %" PRIu16 " people to tend"
					" the fields. Now then, ", p);
				goto plant_seeds;
			}

			s = s - ((uint16_t) (d / 2));
bounty_harvest:
			c = hamurabi_random_event_value();
			y = c;
			h = d * y;
			e = 0;
			c = hamurabi_random_event_value();
			if (((uint16_t) (c / 2.0)) == (c / 2.0)) {
				e = (uint16_t) (s / c);
			}

			s = s - e + h;
			c = hamurabi_random_event_value();
			i = (uint16_t) (c * ((20 * a) + s) / p / (100 + 1));
			c = (uint16_t) (q / 20);
			q = (uint16_t) (10 * ((2 * RANDOM(1)) - 0.3));
			if (p < c) {
				d = 0;
				continue;
			}

			d = p - c;
			if (d > (0.45 * p)) {
				printf("You starved %" PRIu16 " people in one year\n", d);
				goto hamurabi_judgement_worse;
			}
			p1 = (((z - 1) * p1) + (d * 100 / p)) / z;
			p = c;
			d1 = d1 + d;
			continue;
		} else {

			l = a / p;

			printf("In your 10-yr term of office, %" PRIu16 " percent of the "
				"population starved per year on average, i.e., A total of "
				"%" PRIu16 " people died!! You started with 10 acres per person "
				"and ended with %" PRIu16 " acres per person.\n", p1, d1, l);

			if ((p1 > 33) || (l < 7)) {
				goto hamurabi_judgement_worse;
			}
			if ((p1 > 10) || (l < 9)) {
				goto hamurabi_judgement_bad;
			}
			if ((p1 > 3) || (l < 10)) {
				goto hamurabi_judgement_fair;
			}
			goto hamurabi_judgement_good;
		}

hamurabi_judgement_worse:
		printf("Due to this extreme mismanagement you have not only been impeached "
			"and thrown out of office but you have also been declared "
			"'NATIONAL FINK'!!\n");
		goto end;

hamurabi_judgement_bad:
		printf("Your heavy handed performance smacks of Nero and Ivan IV. The people "
			"(remaining) find you an unpleasant ruler, and, frankly, hate your "
			"guts!\n");
		goto end;

hamurabi_judgement_fair:
		{
			uint16_t x = (uint16_t) (p * 0.8 * RANDOM(1));
			printf("Your performance could have been somewhat better, but really wasn't "
			    "too bad at all. %" PRIu16 " people would dearly like to see you "
			    "assasinated but we all have our trivial problems.\n", x);
		}
		goto end;

hamurabi_judgement_good:
		printf("A fantastic performance!!! Charlemange, Disraeli, and Jefferson combined could "
			"not have done better!\n");
		goto end;
	}

end:
	hamurabi_end();

cleanup:
	city_destroy(city);

	return;
}
