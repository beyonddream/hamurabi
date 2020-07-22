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
	uint16_t acres_owned;
};

enum city_event_type {
	NONE,
	PLAGUE,
	RAT_MENACE,
	BUY_ACRES,
	SELL_ACRES,
	FEED_PEOPLE,
	PLANT_SEEDS,
	BOUNTY_HARVEST,
	JUDGEMENT_GOOD,
	JUDGEMENT_FAIR,
	JUDGEMENT_BAD,
	JUDGEMENT_WORSE,
	UNKNOWN, /* unknown event type is considered error */
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
	city->acres_owned = (get_bushels_preserved(city) + get_bushels_destroyed(city)) / get_bushels_per_acre(city);

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

void update_report_summary(uint16_t acres_buy_or_sell, city_of_sumeria_t *city)
{
	uint16_t total_bushels;

	printf("Hamurabi: I beg to report to you, "
	       "In year %" PRIu16 ", "
	       "%" PRIu16 " people starved, "
	       "%" PRIu16 " came to the city.\n",
	       city->year,
	       city->people_starved,
	       city->people_arrived);

	city->year += 1;
	city->population += city->people_arrived;

	if (check_plague(acres_buy_or_sell, city) == PLAGUE) {
		printf("A horrible plague struck! "
		       "Half the people died.\n");
	}

	printf("population is now %" PRIu16 "\n", city->population);
	printf("The city owns %" PRIu16 " acres.\n", city->acres_owned);
	printf("You have harvested %" PRIu16 " bushels per acre.\n", city->bushels_per_acre);
	printf("Rats ate %" PRIu16 " bushels.\n", city->bushels_destroyed);
	printf("You now have %" PRIu16 " bushels in store.\n", city->bushels_preserved);

	return;
}

city_event_type check_plague(uint16_t acres_buy_or_sell, city_of_sumeria_t *city)
{

	if (acres_buy_or_sell <= 0) {
		city->population = (uint16_t)(city->population / 2);
		return PLAGUE;
	}

	return NONE;
}

city_event_type check_rat_menace(city_of_sumeria_t *city)
{
	city->bushels_destroyed = 0;
	uint16_t random_event_value = hamurabi_random_event_value();

	if (((uint16_t)(random_event_value / 2.0)) == (random_event_value / 2.0)) {
		city->bushels_destroyed = (uint16_t)(city->bushels_preserved / random_event_value);
		return RAT_MENACE;
	}

	return NONE;
}

city_event_type check_judgement(city_of_sumeria_t *city, uint16_t population_starved_per_yr, uint16_t people_died_total)
{
	uint16_t acres_per_person = city->acres_owned / city->population;

	printf("In your 10-yr term of office, %" PRIu16 " percent of the "
	       "population starved per year on average, i.e., A total of "
	       "%" PRIu16 " people died!! You started with 10 acres per person "
	       "and ended with %" PRIu16 " acres per person.\n",
	       population_starved_per_yr,
	       people_died_total,
	       acres_per_person);

	if ((population_starved_per_yr > 33) || (acres_per_person < 7)) {
		return JUDGEMENT_WORSE;
	}
	if ((population_starved_per_yr > 10) || (acres_per_person < 9)) {
		return JUDGEMENT_BAD;
	}
	if ((population_starved_per_yr > 3) || (acres_per_person < 10)) {
		return JUDGEMENT_FAIR;
	}

	return JUDGEMENT_GOOD;
}

void print_judgement_worse_message()
{

	printf("Due to this extreme mismanagement you have not only been impeached "
	       "and thrown out of office but you have also been declared "
	       "'NATIONAL FINK'!!\n");

	return;
}

void print_judgement_bad_message()
{

	printf("Your heavy handed performance smacks of Nero and Ivan IV. The people "
	       "(remaining) find you an unpleasant ruler, and, frankly, hate your "
	       "guts!\n");

	return;
}

void print_judgement_fair_message(uint16_t population)
{
	uint16_t x = (uint16_t)(population * 0.8 * RANDOM(1));

	printf("Your performance could have been somewhat better, but really wasn't "
	       "too bad at all. %" PRIu16 " people would dearly like to see you "
	       "assasinated but we all have our trivial problems.\n",
	       x);

	return;
}

void print_judgement_good_message()
{

	printf("A fantastic performance!!! Charlemange, Disraeli, and Jefferson combined could "
	       "not have done better!\n");

	return;
}

city_event_type buy_acres(city_of_sumeria_t *city)
{
	uint16_t acres_to_buy;
	uint16_t bushels_preserved = get_bushels_preserved(city);
	uint16_t bushels_per_acre = get_bushels_per_acre(city);

	printf("How many acres do you wish to buy?");
	scanf("%" PRIu16, &acres_to_buy);

	if (acres_to_buy < 0) {
		hamurabi_illegal_input();
		return UNKNOWN;
	}

	if ((bushels_per_acre * acres_to_buy) > bushels_preserved) {
		hamurabi_illegal_bushels_input(bushels_preserved);
		return BUY_ACRES;
	}

	if (acres_to_buy != 0) {
		city->acres_owned += acres_to_buy;
		city->bushels_preserved -= (bushels_per_acre * acres_to_buy);
		return FEED_PEOPLE;
	}

	return NONE;
}

city_event_type sell_acres(city_of_sumeria_t *city)
{
	uint16_t acres_to_sell;
	uint16_t bushels_preserved = get_bushels_preserved(city);
	uint16_t bushels_per_acre = get_bushels_per_acre(city);

	printf("How many acres do you wish to sell?");
	scanf("%" PRIu16, &acres_to_sell);

	if (acres_to_sell < 0) {
		hamurabi_illegal_input();
		return UNKNOWN;
	}

	if (acres_to_sell >= city->acres_owned) {
		hamurabi_illegal_acres_input(city->acres_owned);
		return SELL_ACRES;
	}

	city->acres_owned -= acres_to_sell;
	city->bushels_preserved += (bushels_per_acre * acres_to_sell);

	return FEED_PEOPLE;
}

city_event_type feed_people(city_of_sumeria_t *city)
{
	uint16_t bushels_to_feed_people;
	uint16_t bushels_preserved = get_bushels_preserved(city);

	printf("How many bushels do you wish to feed your people?");
	scanf("%" PRIu16, &bushels_to_feed_people);

	if (bushels_to_feed_people < 0) {
		hamurabi_illegal_input();
		return UNKNOWN;
	}

	if (bushels_to_feed_people > bushels_preserved) {
		hamurabi_illegal_bushels_input(bushels_preserved);
		return FEED_PEOPLE;
	}

	city->bushels_preserved -= bushels_to_feed_people;

	return PLANT_SEEDS;
}

city_event_type plant_seeds(city_of_sumeria_t *city)
{

	return NONE;
}

city_event_type harvest_bounty(city_of_sumeria_t *city)
{

	return NONE;
}

void hamurabi_start(void)
{
	uint16_t people_starved;
	uint16_t acres_buy_or_sell;
	uint16_t total_bushels;
	uint16_t bushels_per_acre;
	uint16_t random_event_value;
	uint16_t population_starved_per_yr;
	uint16_t people_died_total;
	uint16_t acres_per_person;

	printf("Try your and at governing ancient sumeria,"
	       "successfully for a 10-yr term of office.\n");

	city_of_sumeria_t *city = city_new();

	for (;;) {

		people_starved = get_people_starved(city);
		total_bushels = get_bushels_preserved(city) + get_bushels_destroyed(city);
		bushels_per_acre = get_bushels_per_acre(city);
		city->acres_owned = total_bushels / bushels_per_acre;
		acres_buy_or_sell = 1;

		update_report_summary(acres_buy_or_sell, city);

		if (city->year < 11) {
			RAND(10, &random_event_value);
			bushels_per_acre = random_event_value + 17;
			printf("Land is trading at %" PRIu16 " bushels per acre.\n", bushels_per_acre);

buy_acres:
			switch (buy_acres(city)) {
			case BUY_ACRES:
				goto buy_acres;
			case FEED_PEOPLE:
				goto feed_people;
			case UNKNOWN:
				goto end;
			default:
				break;
			}
sell_acres:
			switch (sell_acres(city)) {
			case SELL_ACRES:
				goto sell_acres;
			case FEED_PEOPLE:
				goto feed_people;
			case UNKNOWN:
				goto end;
			default:
				break;
			}
feed_people:
			switch (feed_people(city)) {
			case PLANT_SEEDS:
				goto plant_seeds;
			case FEED_PEOPLE:
				goto feed_people;
			case UNKNOWN:
				goto end;
			default:
				break;
			}
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
			if (people_starved > city->acres_owned) {
				hamurabi_illegal_acres_input(city->acres_owned);
				goto plant_seeds;
			}
			if (((uint16_t)(people_starved / 2)) >= city->bushels_preserved) {
				hamurabi_illegal_bushels_input(city->bushels_preserved);
				goto plant_seeds;
			}
			if (people_starved >= (10 * city->population)) {
				printf("But you have only %" PRIu16 " people to tend"
				       " the fields. Now then, ",
				       city->population);
				goto plant_seeds;
			}

			city->bushels_preserved -= ((uint16_t)(people_starved / 2));
bounty_harvest:
			bushels_per_acre = hamurabi_random_event_value();
			total_bushels = people_starved * bushels_per_acre;
			city->bushels_preserved += total_bushels;
			if (check_rat_menace(city) == RAT_MENACE) {
				city->bushels_preserved -= city->bushels_destroyed;
			}

			city->people_arrived = (uint16_t)(hamurabi_random_event_value() * ((20 * city->acres_owned) + city->bushels_preserved) /
			                                  city->population / (100 + 1));

			random_event_value = (uint16_t)(acres_buy_or_sell / 20);
			acres_buy_or_sell = (uint16_t)(10 * ((2 * RANDOM(1)) - 0.3));
			if (city->population < random_event_value) {
				people_starved = 0;
				continue;
			}

			people_starved = city->population - random_event_value;
			if (people_starved > (0.45 * city->population)) {
				printf("You starved %" PRIu16 " people in one year\n", people_starved);
				print_judgement_worse_message();
				goto end;
			}
			population_starved_per_yr =
			    (((city->year - 1) * population_starved_per_yr) + (people_starved * 100 / city->population)) / city->year;
			city->population = random_event_value;
			people_died_total += people_starved;
			continue;
		} else {

			switch (check_judgement(city, population_starved_per_yr, people_died_total)) {
			case JUDGEMENT_WORSE:
				print_judgement_worse_message();
				goto end;
			case JUDGEMENT_BAD:
				print_judgement_bad_message();
				goto end;
			case JUDGEMENT_FAIR:
				print_judgement_fair_message(city->population);
				goto end;
			case JUDGEMENT_GOOD:
				print_judgement_good_message();
				goto end;
			default:
				continue;
			}
		}
	}
end:
	hamurabi_end();

cleanup:
	city_destroy(city);

	return;
}
