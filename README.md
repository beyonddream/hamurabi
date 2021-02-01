# Hamurabi
Hamurabi game implemented in C

# Dependencies

1. CMake >= 3.17 for building.
2. Check 0.15.1 for running unit tests.

Tested with clang version 11.0 compiler.

# Building

1. `./br`

# Testing

1. Build
1. go to build/
2. run `ctest`

# Running the Game

1. `./br r`

# Game details

player - ancient babylonian king Hammurabi.  
resources - people, acres of land, bushels of grain.  
rounds - 10 (unit = year)

A person can 
1. farm a set amount of land and produce grain.
2. Buy a land from neighbors in exchange for grain.
3. Die next round if not fed the previous round.

A grain can 
1. used to feed the people current round.
2. planted next round.

Each round, an advisor mention
1. current status of the city.
2. prior years harvest.
3. change in population.
4. Series of questions:   
    a. how many bushels of grain to spend on land.   
    b. seeds.   
    c. feeding the people.   

The games variation is drive by random number.

For each round, the below are decided by random number. The min and max are enclosed in brackets.

1. price of land (17 - 26 bushels per acre, bushel is a type of currency).
2. amount of bushels.
3. bushels eaten by rats.
4. new people in city.
5. possibility of plague reducing the population by half.

The game ends if any of the below condition satisfies:
1. after 10 rounds
2. entire population of city dies
3. atleast 45% of population starve in a round

# Development
In your local development, you can run ctags on the project to make it easy to jump around functions:

1. `ctags -R -a .`

# TODO
- [ ] Add tests
- [ ] Add web interface
