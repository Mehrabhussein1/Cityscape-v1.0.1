#include "city.h"

char admin_password[ADMIN_PASSWORD_MAX] = "1234";

static Building buildings[MAX_BUILDINGS] = {
    {RESIDENTIAL, "Residential Area", 'R', 2000, 0, 0, 0, 20, 0, 0, 0},
    {FARM, "Farm", 'F', 1500, 0, 30, 0, 0, 0, 0, 0},
    {POWER_PLANT, "Power Plant", 'P', 3000, 0, 0, 100, 0, -1, 0, 0},
    {HOSPITAL, "Hospital", 'H', 2500, 0, 0, 0, 0, 5, 5, 0},
    {SCHOOL, "School", 'S', 2000, 0, 0, 0, 0, 5, 0, 5},
    {PARK, "Park", 'K', 1800, 0, 0, 0, 0, 8, 2, 0}};

static int building_count = BUILDING_TYPE_COUNT; //from the enum's last element

const Building *getBuilding(BuildingType type){
    if((int)type<0 || (int)type>=building_count){ 
        return NULL;
    }
    return &buildings[type]; //returns the location of the buildings struct at line 5 (points to the type we want)
}

void clearInput(void){
    int c;
    while((c=getchar())!='\n' && c!= EOF){
// only clearing the keyboard's input buffer
}
}


static int clampstat(int value){
    if(value < 0) return 0;
    if(value > 100) return 0;
    return value;
}


void getCurrentTimestamp(char *buffer, size_t size){  /////
    time_t now = time(NULL); //gets the system time and stores within now variable (time_t datatype) . NULL means store in nowhere else!
    struct tm *local = localtime(&now); //localtime converts the random time digits into local date and time components and *local is a structure pointer pointing to those components 
    if(local) //checks if localtime did return a pointer or not . not NULL means OK ! 
    strftime(buffer,size,"%d %B %Y %H:%M:%S",local); //special type of printf to store time components from local's pointed address to the string named "buffer". %B means Month in full form!. 
    else snprintf(buffer,size,"Unknown Time"); //another special printf to store Unknown time inside the string Buffer!
}

void initializeCity(City *city){
    int r,c,i;
    memset(city,0,sizeof(City));
    loadCustomBuildings();
    city->day = 1;
    city->money = START_MONEY;
    city->food = START_FOOD;
    city->electricity = START_ELECTRICITY;
    city->population = START_POPULATION;
    city->population_limit = START_POPULATION_LIMIT;
    city->happiness = START_HAPPINESS;
    city->health = START_HEALTH;
    city->education = START_EDUCATION;
    city->mayor_rating = 70;
    city->citizen_count = START_POPULATION;
    city->citizen_seed = 1;
    city->save_timestamp[0] = '\0';

    for(r=0;r<MAP_SIZE ; r++)
        for(c=0;c<MAP_SIZE;c++)
            city->map[r][c]= '.';

    for(i =0;i< MAX_CITIZENS;i++){
        city->citizens[i].id = i+1;
        snprintf(city->citizens[i].name, sizeof(city->citizens[i].name),"Citizen_%03d",i+1);
        city->citizens[i].satisfaction = 70;
        city->citizens[i].rating = 70;
        city->citizens[i].active = (i< city->citizen_count);
    }
}

void showGuide(void){
    printf("\n==================================================\n");
    printf("                 CITYSCAPE v1.0.1\n");
    printf("==================================================\n");
    printf("Hi! You Sir, are a Mayor now! Build the city of your Dreams.\n Manage the city and build a Megapolis from scratch.\nManage Money, Food, Electricity, Citizen Health and their Education too!\nAdvance days to produce/consume resources and trigger (!random!) events.\n \nAND DON'T FORGET TO SAVE YOUR GAME BEFORE YOU TAKE A BREAK\n \nHAPPY GAMING CITYSCAPE!\n\n");
}

void showStatus(const City *city) {
    float usage = city->population_limit > 0 ? ((float)city->population / city->population_limit) * 100.0f : 0.0f;
    printf("\n---------------- CITY STATUS ----------------\n");
    printf("City: %s\n", city->name);
    printf("Day: %d\n", city->day);
    printf("Money: $%d\n", city->money);
    printf("Population: %d / %d (%.1f%%)\n", city->population, city->population_limit, usage);
    printf("Food: %d\n", city->food);
    printf("Electricity: %d\n", city->electricity);
    printf("Happiness: %d/100\n", city->happiness);
    printf("Health: %d/100\n", city->health);
    printf("Education: %d/100\n", city->education);
    printf("Citizens: %d\n", city->citizen_count);
    printf("Mayor Rating: %d/100\n", city->mayor_rating);
    if (city->food <= 0) printf("WARNING: Food shortage!\n");
    if (city->electricity <= 0) printf("WARNING: Electricity shortage!\n");
    printf("----------------------------------------------\n");
}

void showMap(const City *city) {
int r,c;
printf("\n     ");
for(c =0; c<MAP_SIZE;c++)
    printf("%d ", c);
printf("\n");
for(r=0;r<MAP_SIZE;r++){
    printf("%2d   ",r);
    for(c=0;c<MAP_SIZE;c++) 
        printf("%c ",city->map[r][c]);
    printf("\n");
    }
}


void showBuildings(void) {
    int i;
    printf("\n---------------- BUILDINGS ----------------\n");
    for (i = 0; i < building_count; i++) {
        const Building *b = &buildings[i];
        printf("%d. %s [%c] - $%d\n", i + 1, b->name, b->symbol, b->cost);
        printf("  Daily: Money %+d, Food %+d, Electricity %+d\n", b->daily_money_effect, b->daily_food_effect, b->daily_electricity_effect);
        printf("  Capacity %+d, Happiness %+d, Health %+d, Education %+d\n", b->population_capacity_effect, b->happiness_effect, b->health_effect, b->education_effect);
    }
}


