#include "city.h"

char admin_password[ADMIN_PASSWORD_MAX] = "1234";

static Building buildings[MAX_BUILDINGS] = {
    {RESIDENTIAL, "Residential Area", 'R', 2000, 0, 0, 0, 20, 0, 0, 0},
    {FARM, "Farm", 'F', 1500, 0, 30, 0, 0, 0, 0, 0},
    {POWER_PLANT, "Power Plant", 'P', 3000, 0, 0, 100, 0, -1, 0, 0},
    {HOSPITAL, "Hospital", 'H', 2500, 0, 0, 0, 0, 5, 5, 0},
    {SCHOOL, "School", 'S', 2000, 0, 0, 0, 0, 5, 0, 5},
    {PARK, "Park", 'K', 1800, 0, 0, 0, 0, 8, 2, 0}};

static int building_count = BUILDING_TYPE_COUNT;

