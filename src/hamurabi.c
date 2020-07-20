#include "../include/hamurabi.h"
#include <inttypes.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct city_of_sumeria {
	uint16_t bushels_preserved;
	uint16_t bushels_destroyed;
	uint16_t bushels_per_acre;
	uint16_t year;
	uint16_t people_starved;
	uint16_t people_arrived;
	uint16_t population;
};

enum city_event_type {
	OK,
	PLAGUE,
};

city_of_sumeria_t *city_new(void)
{
	city_of_sumeria_t *city;

	city = (city_of_sumeria_t *)malloc(sizeof(city_of_sumeria_t));
	if (city == NULL) {
		printf("Unable to intialize city. Exiting...\n");
		exit(EXIT_FAILURE);
	}

	memset((void *)city, 0, sizeof(city_of_sumeria_t));

	city->bushels_preserved = (uint16_t)2800;
	city->bushels_destroyed = (uint16_t)200;
	city->bushels_per_acre = (uint16_t)3;
	city->year = (uint16_t)1;
	city->people_starved = (uint16_t)0;
	city->people_arrived = (uint16_t)5;
	city->population = (uint16_t)95;

	return city;
}

void city_destroy(city_of_sumeria_t *city_of_sumeria)
{

	free((void *)city_of_sumeria);
	return;
}

void hamurabi_end(void)
{

	for (int i = 0; i < 10; i++) {
		printf("\a"); // beep sound
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
	       "%" PRIu16 " bushels of grain. Now then, ",
	       bushels_total);
	return;
}

void hamurabi_illegal_acres_input(uint16_t acres_total)
{

	printf("Hamurabi: Think again. You own only "
	       "%" PRIu16 " acres. Now then, ",
	       acres_total);
	return;
}

int hamurabi_random_event_value(void)
{
	int random_event_value;
	RAND(1, &random_event_value);

	random_event_value = ((int)(random_event_value * 5)) + 1;

	return random_event_value;
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

void report_summary(const city_of_sumeria_t *city)
{

	printf("Hamurabi: I beg to report to you, "
	       "In year %" PRIu16 ", "
	       "%" PRIu16 " people starved, "
	       "%" PRIu16 " came to the city.\n",
	       city->year,
	       city->people_starved,
	       city->people_arrived);

	return;
}

city_event_type set_plague(uint16_t acres_buy_or_sell, city_of_sumeria_t *city)
{

	if (acres_buy_or_sell <= 0) {
		city->population = (uint16_t)(city->population / 2);
		return PLAGUE;
	}

	return OK;
}

void hamurabi_start(void)
{
	uint16_t people_starved;
	uint16_t year;
	uint16_t people_arrived;
	uint16_t acres_buy_or_sell;
	uint16_t bushels_preserved;
	uint16_t bushels_destroyed;
	uint16_t total_bushels;
	uint16_t bushels_per_acre;
	uint16_t acres_owned;
	uint16_t random_event_value;
	uint16_t population_starved_per_yr;
	uint16_t people_died_total;
	uint16_t acres_per_person;

	printf("Try your and at governing ancient sumeria,"
	       "successfully for a 10-yr term of office.\n");

	city_of_sumeria_t *city = city_new();

	year = get_year(city);
	people_arrived = get_people_arrived(city);
	people_starved = get_people_starved(city);
	bushels_preserved = get_bushels_preserved(city);
	bushels_destroyed = get_bushels_destroyed(city);
	total_bushels = bushels_preserved + bushels_destroyed;
	bushels_per_acre = get_bushels_per_acre(city);
	acres_owned = total_bushels / bushels_per_acre;
	acres_buy_or_sell = 1;

	for (;;) {
		report_summary(city);

		city->year += 1;
		city->population += people_arrived;

		if (set_plague(acres_buy_or_sell, city) == PLAGUE) {
			printf("A horrible plague struck! "
			       "Half the people died.\n");
		}

		printf("population is now %" PRIu16 "\n", city->population);
		printf("The city owns %" PRIu16 " acres.\n", acres_owned);
		printf("You have harvested %" PRIu16 " bushels per acre.\n", bushels_per_acre);
		printf("Rats ate %" PRIu16 " bushels.\n", bushels_destroyed);
		printf("You now have %" PRIu16 " bushels in store.\n", bushels_preserved);

		if (city->year < 11) {
			RAND(10, &random_event_value);
			bushels_per_acre = random_event_value + 17;
			printf("Land is trading at %" PRIu16 " bushels per acre.\n", bushels_per_acre);

buy_acres:
			printf("How many acres do you wish to buy?");
			scanf("%" PRIu16, &acres_buy_or_sell);
			if (acres_buy_or_sell < 0) {
				hamurabi_illegal_input();
				goto end;
			}
			if ((bushels_per_acre * acres_buy_or_sell) > bushels_preserved) {
				hamurabi_illegal_bushels_input(bushels_preserved);
				goto buy_acres;
			}
			if (acres_buy_or_sell != 0) {
				acres_owned += acres_buy_or_sell;
				bushels_preserved = bushels_preserved - (bushels_per_acre * acres_buy_or_sell);
				random_event_value = 0;
				goto feed_people;
			}
sell_acres:
			printf("How many acres do you wish to sell?");
			scanf("%" PRIu16, &acres_buy_or_sell);
			if (acres_buy_or_sell < 0) {
				hamurabi_illegal_input();
				goto end;
			}
			if (acres_buy_or_sell >= acres_owned) {
				hamurabi_illegal_acres_input(acres_owned);
				goto sell_acres;
			}

			acres_owned -= acres_buy_or_sell;
			bushels_preserved = bushels_preserved + (bushels_per_acre * acres_buy_or_sell);
			random_event_value = 0;
feed_people:
			printf("How many bushels do you wish to feed your people?");
			scanf("%" PRIu16, &acres_buy_or_sell);
			if (acres_buy_or_sell < 0) {
				hamurabi_illegal_input();
				goto end;
			}
			if (acres_buy_or_sell > bushels_preserved) {
				hamurabi_illegal_bushels_input(bushels_preserved);
				goto feed_people;
			}

			bushels_preserved = bushels_preserved - acres_buy_or_sell;
			random_event_value = 1;
plant_seeds:
			printf("How many acres do you wish to plant with seed?");
			scanf("%" PRIu16, &people_starved);
			if (people_starved < 0) {
				hamurabi_illegal_input();
				goto end;
			}
			if (people_starved == 0) {
				goto bounty_harvest;
			}
			if (people_starved > acres_owned) {
				hamurabi_illegal_acres_input(acres_owned);
				goto plant_seeds;
			}
			if (((uint16_t)(people_starved / 2)) >= bushels_preserved) {
				hamurabi_illegal_bushels_input(bushels_preserved);
				goto plant_seeds;
			}
			if (people_starved >= (10 * city->population)) {
				printf("But you have only %" PRIu16 " people to tend"
				       " the fields. Now then, ",
				       city->population);
				goto plant_seeds;
			}

			bushels_preserved = bushels_preserved - ((uint16_t)(people_starved / 2));
bounty_harvest:
			random_event_value = hamurabi_random_event_value();
			bushels_per_acre = random_event_value;
			total_bushels = people_starved * bushels_per_acre;
			bushels_destroyed = 0;
			random_event_value = hamurabi_random_event_value();
			if (((uint16_t)(random_event_value / 2.0)) == (random_event_value / 2.0)) {
				bushels_destroyed = (uint16_t)(bushels_preserved / random_event_value);
			}

			bushels_preserved += total_bushels - bushels_destroyed;
			random_event_value = hamurabi_random_event_value();
			people_arrived = (uint16_t)(random_event_value * ((20 * acres_owned) + bushels_preserved) / city->population / (100 + 1));
			random_event_value = (uint16_t)(acres_buy_or_sell / 20);
			acres_buy_or_sell = (uint16_t)(10 * ((2 * RANDOM(1)) - 0.3));
			if (city->population < random_event_value) {
				people_starved = 0;
				continue;
			}

			people_starved = city->population - random_event_value;
			if (people_starved > (0.45 * city->population)) {
				printf("You starved %" PRIu16 " people in one year\n", people_starved);
				goto hamurabi_judgement_worse;
			}
			population_starved_per_yr =
			    (((city->year - 1) * population_starved_per_yr) + (people_starved * 100 / city->population)) / city->year;
			city->population = random_event_value;
			people_died_total += people_starved;
			continue;
		} else {

			acres_per_person = acres_owned / city->population;

			printf("In your 10-yr term of office, %" PRIu16 " percent of the "
			       "population starved per year on average, i.e., A total of "
			       "%" PRIu16 " people died!! You started with 10 acres per person "
			       "and ended with %" PRIu16 " acres per person.\n",
			       population_starved_per_yr,
			       people_died_total,
			       acres_per_person);

			if ((population_starved_per_yr > 33) || (acres_per_person < 7)) {
				goto hamurabi_judgement_worse;
			}
			if ((population_starved_per_yr > 10) || (acres_per_person < 9)) {
				goto hamurabi_judgement_bad;
			}
			if ((population_starved_per_yr > 3) || (acres_per_person < 10)) {
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

hamurabi_judgement_fair : {
	uint16_t x = (uint16_t)(city->population * 0.8 * RANDOM(1));
	printf("Your performance could have been somewhat better, but really wasn't "
	       "too bad at all. %" PRIu16 " people would dearly like to see you "
	       "assasinated but we all have our trivial problems.\n",
	       x);
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
