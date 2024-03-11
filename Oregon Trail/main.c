#include "game.c"

int main(int argc, char* argv[])
{
    int menuSelection = 0;
    char userChoice;

    fileName = argv[1];

    do
    {

        do
        {
            //menu
            printf("1. Start Game\n");
            printf("2. Display Instructions\n");
            printf("3. Quit\n");
            printf("Enter Choice: ");


            scanf("%d", &menuSelection);
            while ((getchar()) != '\n');

            if (menuSelection < 1 || menuSelection > 3)
            {
                printf("Invalid Input!\n");
            }

        } while (menuSelection < 1 || menuSelection > 3);


        //welcome message
        switch (menuSelection)
        {
        case 1:
            printf("Welcome to Oregon Trail! \n");
            green();
            printf("\n"
                "\n           _____                              _____         _ _ "
                "\n          |  _  |                            |_   _|       (_) | "
                "\n          | | | |_ __ ___  __ _  ___  _ __     | |_ __ __ _ _| | "
                "\n          | | | | `__/ _ |/ _` |/ _ || `_  |   | | `__/ _` | | | "
                "\n          | |_/ / | |  __/ (_| | (_) | | | |   | | | | (_| | | | "
                "\n           |__/|_|  |__||_, ||__/|_| |_|   |_/_|  |__,_|_|_|     "
                "\n                           __/ |                                 "
                "\n                          |___/       _continue\n\n");

            reset();
            if (!startGame())
            {
                menuSelection = 3;
            }
            else
            {
                //asking user if they want to replay
                printf("Would you like to play again? (y/n) ");
                userChoice = tolower(getchar());
                while ((getchar()) != '\n');

                if (userChoice != 'y')
                {
                    menuSelection = 3;
                }
            }
            break;

        case 2:
            printf("The goal of Oregon trail is to traverse the map from starting location to ending location without running out of food. Obstacles you encounter will deplete or increase your food stockpile depending on the given obstacle: \nAnimals: Grizzly (G) -10 food, Boar (B) -5 food, Elk (E) 0 food, Hare (H) +5 food \nDisease: cold (C)-5 food, FLU (F) -10 food, Dysentery (D) -15 food, River (R)-20 food to cross.\n");
            break;

        case 3:
            printf("Thank you for playing!\n");
            break;
        }


    } while (menuSelection != 3);

}