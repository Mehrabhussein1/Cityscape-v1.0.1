#ifndef CITY_H
#define CITY_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define RESET   "\033[0m"
#define BOLD    "\033[1m"


#define MAP_SIZE 10
#define START_MONEY 10000
#define START_FOOD 100
#define START_ELECTRICITY 50
#define START_POPULATION 10
#define START_POPULATION_LIMIT 20
#define START_HAPPINESS 70
#define START_HEALTH 70
#define START_EDUCATION 20
#define MAX_CITIZENS 500
#define MAX_SAVE_SLOTS 10
#define SAVE_DIRECTORY "city_saves"
#define SAVE_FILE_PREFIX "save_"
#define SAVE_TIMESTAMP_SIZE 64
#define MAX_BUILDINGS 32
#define BUILDING_DATA_FILE "custom_structures.txt"
#define ADMIN_PASSWORD_FILE "admin_pass.txt"
#define ADMIN_PASSWORD_MAX  64
extern char admin_password[ADMIN_PASSWORD_MAX];
#define showFailmsg goto fail

typedef enum {  //all structures in enum. 
    RESIDENTIAL,
    FARM,
    POWER_PLANT,
    HOSPITAL,
    SCHOOL,
    PARK,
    BUILDING_TYPE_COUNT //its index is 6 (total structure koyta ta indicate kore)
} BuildingType; //enumerated  type er naam

typedef struct { 
    BuildingType type; //game er vitor bivinno function er vitor structure niye kaj korar shomoy jeno eta kon structure ta identify korte subidha hoy 
    char name[40];
    char symbol;
    int cost;
    int daily_money_effect;
    int daily_food_effect;
    int daily_electricity_effect;
    int population_capacity_effect;
    int happiness_effect;
    int health_effect;
    int education_effect;
} Building;

typedef struct {
    int id;
    char name[32];
    int satisfaction;
    int rating;
    int active;
} Citizen;

typedef struct {
    char name[64];
    char save_timestamp[SAVE_TIMESTAMP_SIZE];
    int day;
    int money;
    int food;
    int electricity;
    int population;
    int population_limit;
    int happiness;
    int health;
    int education;
    int mayor_rating;
    int citizen_count;
    int citizen_seed;
    char map[MAP_SIZE][MAP_SIZE];
    Citizen citizens[MAX_CITIZENS];
} City;

typedef union {
    int money;
    int food;
    int population;
} EventData;

void clearInput(void);
void showGuide(void);
void initializeCity(City *city);
void showStatus(const City *city);
void showMap(const City *city);
void showBuildings(void);
void addBuilding(City *city);
void deleteBuilding(City *city);
void advanceDay(City *city);
void randomEvent(City *city);
void saveGame(City *city);
void loadGame(City *city);
void listSaves(void);
void checkWinCond(const City *city);
void checkWin(const City *city);
void addMoney(int *money, int amount);
void showBitwiseStatus(const City *city);
void showDynamicBuildings(void);
void showCitizens(const City *city);
void calculateCitizenRatings(City *city);
void calculateMayorRating(City *city);
void loadAdminPassword(void);
void adminManageBuildings(void);
void loadCustomBuildings(void);
const Building *getBuilding(BuildingType type);
int countBuilding(const City *city, BuildingType type);
void applyBuildingEffects(City *city, BuildingType type, int direction);
void getSaveFilename(int slot, char *filename, size_t size);
void getCurrentTimestamp(char *buffer, size_t size);




#endif