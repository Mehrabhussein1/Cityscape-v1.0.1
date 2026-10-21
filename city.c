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
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    if(local) strftime(buffer,size,"%d %B %Y %H:%M:%S",local);
    else snprintf(buffer,size,"Unknown Time");
}


