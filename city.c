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

int countBuilding(const City *city, BuildingType type){
    int r, c, count =0;
    const Building *b = getBuilding(type);
    if(!b) return 0;
    for(r =0; r<MAP_SIZE;r++)
        for(c=0;c<MAP_SIZE;c++)
            if(city->map[r][c] == b-> symbol)
                count++;
    return count;
}


 void applyBuildingEffects(City *city, BuildingType type, int direction){
    const Building *b = getBuilding(type);
    if(!b) return;

    city-> population_limit += direction * b-> population_capacity_effect;

    city-> happiness = clampstat(city->happiness + direction* b->happiness_effect);

    city->health = clampstat(city-> health + direction* b->health_effect);

    city-> education = clampstat(city-> education + direction* b->education_effect);

    if(city->population_limit < city->population){
        city-> population_limit = city->population;
    }

 }

static BuildingType symbolToType(char symbol) {
    int i;
    for (i = 0; i < building_count; i++)
        if (buildings[i].symbol == symbol) return buildings[i].type;
    return (BuildingType)building_count;
}

void addBuilding(City *city) {
    int choice, row, col;
    showMap(city);
    showBuildings();
    printf("Choose building (1-%d): ", building_count);
    if (scanf("%d", &choice) != 1) { clearInput(); printf("Invalid choice.\n"); return; }
    clearInput();
    if (choice < 1 || choice > building_count) { printf("Invalid building.\n"); return; }

    const Building *b = &buildings[choice - 1];
    if (city->money < b->cost) { printf("Not enough money. Need $%d.\n", b->cost); return; }

    printf("Enter row (0-%d): ", MAP_SIZE - 1);

    if (scanf("%d", &row) != 1) { clearInput(); printf("Invalid row.\n"); return; }

    printf("Enter column (0-%d): ", MAP_SIZE - 1);

    if (scanf("%d", &col) != 1) { clearInput(); printf("Invalid column.\n"); return; }

    clearInput();
    if (row < 0 || row >= MAP_SIZE || col < 0 || col >= MAP_SIZE) { printf("Invalid location.\n"); return; }

    if (city->map[row][col] != '.') { printf("That location is occupied.\n"); return; }

    city->map[row][col] = b->symbol;
    city->money -= b->cost;
    applyBuildingEffects(city, b->type, 1);
    printf("%s built successfully for $%d.\n", b->name, b->cost);
    showMap(city);
}


void deleteBuilding(City *city) {
    int row, col;
    showMap(city);
    printf("Enter row to delete: ");
    if (scanf("%d", &row) != 1) { clearInput(); printf("Invalid row.\n"); return; }
    printf("Enter column to delete: ");
    if (scanf("%d", &col) != 1) { clearInput(); printf("Invalid column.\n"); return; }
    clearInput();
    if (row < 0 || row >= MAP_SIZE || col < 0 || col >= MAP_SIZE) { printf("Invalid location.\n"); return; }
    if (city->map[row][col] == '.') { printf("That location is empty.\n"); return; }

    BuildingType type = symbolToType(city->map[row][col]);
    if ((int)type == building_count) { printf("Unknown structure.\n"); return; }
    const Building *b = getBuilding(type);
    city->map[row][col] = '.';
    city->money += b->cost / 2;
    applyBuildingEffects(city, type, -1);
    printf("%s removed. Half of its cost ($%d) was refunded.\n", b->name, b->cost / 2);
    showMap(city);
}



void calculateCitizenRatings(City *city) {
    int i;
    int base = (city->happiness + city->health + city->education) / 3;
    if (city->food <= 0) base -= 20;
    if (city->electricity <= 0) base -= 20;
    base = clampStat(base);
    if (city->citizen_count > MAX_CITIZENS) city->citizen_count = MAX_CITIZENS;
    for (i = 0; i < city->citizen_count; i++) {
        if (!city->citizens[i].active) city->citizens[i].active = 1;
        city->citizens[i].satisfaction = clampStat(base + (rand() % 10)-5);
        city->citizens[i].rating = city->citizens[i].satisfaction;
    }
}

void calculateMayorRating(City *city) {
    int i, total = 0;
    if (city -> citizen_count <= 0){
        city -> mayor_rating = 0; 
        return; 
    }
    for (i = 0; i < city->citizen_count; i++) 
        total += city->citizens[i].rating;
    city->mayor_rating = total / city->citizen_count;
}