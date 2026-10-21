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


}


