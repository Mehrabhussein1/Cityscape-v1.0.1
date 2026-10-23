#include "city.h"

int main(int argc, char *argv[]) {
    City city;
    int choice;

    srand((unsigned int)time(NULL));
    initializeCity(&city);
    loadAdminPassword();

    if (argc >= 2) {
        strncpy(city.name, argv[1], sizeof(city.name) - 1);
        city.name[sizeof(city.name) - 1] = '\0';
    } else {
        printf("Enter your city name: ");
        if (fgets(city.name, sizeof(city.name), stdin)) {
            city.name[strcspn(city.name, "\r\n")] = '\0';
        }
        if (city.name[0] == '\0') strcpy(city.name, "My City");
    }

    showGuide();

    while (1) {
        showStatus(&city);
        printf("\n=============== MAIN MENU ===============\n");
        printf("1. Add Building\n");
        printf("2. Delete Building\n");
        printf("3. View City Map\n");
        printf("4. View Building Information\n");
        printf("5. Advance One Day\n");
        printf("6. Save City\n");
        printf("7. Load City\n");
        printf("8. Admin / Manage Structures\n");
        printf("9. View Citizens & Mayor Rating\n");
        printf("10. Check Winning Condition\n");
        printf("11. View City Status Flags\n");
        printf("12. View Dynamic Building Data\n");
        printf("0. Exit\n");
        printf("==========================================\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            clearInput();
            printf("Invalid input. Please enter a number.\n");
            continue;
        }
        clearInput();

    switch (choice) {
        case 1: addBuilding(&city); break;
        case 2: deleteBuilding(&city); break;
        case 3: showMap(&city); break;
        case 4: showBuildings(); break;
         case 5: advanceDay(&city); break;
        case 6: saveGame(&city); break;
        case 7: loadGame(&city); break;
        case 8: adminManageBuildings(); break;
        case 9: calculateCitizenRatings(&city); calculateMayorRating(&city); showCitizens(&city); break;
        case 10: checkWinCond(&city); break;
        case 11: showBitwiseStatus(&city); break;
        case 12: showDynamicBuildings(); break;
        case 0:
            printf("Thanks for playing Cityscape!\n");
            return 0;
        default:
            printf("Unknown menu option.\n");
        }
    }
}