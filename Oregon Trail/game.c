#include "game.h"


bool startGame()
{
    //initialize variables
    viewPortSize = 0;
    playerFood = 50;
    mapSize = 0;

    //read in file
    bool fileExist = readFile();
    if (!fileExist)
    {
        return false;
    }
    else
    {
        //initialize variables
        mapSize = mapSize - 2;
        currX = mapSize - 1;
        currY = mapSize - 1;

        //starts the gameplay
        gamePlay();

        //frees the memory
        freeMem();

        return true;
    }
}
bool readFile()
{
    //checks if something is in the file
    if ((file = fopen(fileName, "r")) == NULL)
    {
        printf("The file doesn't contain any information!");
        return false;
    }
    else
    {
        //initialize variables
        char buffer[BUFFER_LENGTH];
        char* fileInput;
        int fileToken = 0;

        //reads in the viewport and mapsize variables
        for (int x = 0; x < 3; x++)
        {
            fgets(buffer, BUFFER_LENGTH, (FILE*)file);
            fileInput = strtok(buffer, ":");

            while ((sscanf(fileInput, "%d", &fileToken) != 1))
            {
                fileInput = strtok(NULL, ":");
            }

            switch (x)
            {
            case 0:
                mapSize = fileToken + 2;
                break;

            case 1:
                viewPortSize = fileToken;
                break;

            case 2:
                playerFood = fileToken;
                break;
            }
        }


        //gets rid of whitespace in file
        do
        {
            fgets(buffer, BUFFER_LENGTH, (FILE*)file);
        } while (buffer[0] != OCEAN_TOKEN);


        //allocates space for map
        map = (NODE_t**)malloc(((mapSize - 2) * sizeof(NODE_t)));
        fgets(buffer, BUFFER_LENGTH, (FILE*)file);

        //reads in characters
        for (int x = 0; x < mapSize - 2; x++)
        {
            map[x] = (NODE_t*)malloc(((mapSize - 2) * sizeof(NODE_t)));
            for (int y = -1; y < mapSize - 1; y++)
            {
                if (buffer[y + 1] != OCEAN_TOKEN)
                {
                    map[x][y].xPos = x;
                    map[x][y].yPos = y;
                    map[x][y].discovered = false;

                    //connects nodes to each other
                    if (x > 0)
                    {
                        if (y > 0)
                        {
                            //linking the current node to all surrounding nodes
                            map[x][y].left = &map[x][y - 1];
                            map[x][y].up = &map[x - 1][y];

                            //linking the surrounding nodes to current node
                            map[x][y - 1].right = &map[x][y];
                            map[x - 1][y].down = &map[x][y];
                        }
                        else
                        {
                            //linking the current node to all surrounding nodes
                            map[x][y].up = &map[x - 1][y];

                            //linking the surrounding ndoes to current node
                            map[x - 1][y].down = &map[x][y];
                        }
                    }
                    else
                    {
                        if (y > 0)
                        {
                            //linking the current node to all surrounding nodes
                            map[x][y].left = &map[x][y - 1];

                            //linking the surrounding ndoes to current node
                            map[x][y - 1].right = &map[x][y];
                        }
                    }

                    map[x][y].cellChar = buffer[y + 1];
                }

            }
            fgets(buffer, BUFFER_LENGTH, (FILE*)file);
        }


        //allocates memory for viewport
        viewPort = (NODE_t**)malloc(viewPortSize * sizeof(NODE_t));
        for (int x = 0; x < viewPortSize; x++)
        {
            viewPort[x] = (NODE_t*)malloc(viewPortSize * sizeof(NODE_t));
        }

        fclose(file);
        return true;
    }

}

void createViewPort()
{
    //initialize variables
    int posExtractX = currX - (currX / 2);
    int posExtractY = currY - (currY / 2);

    //creates space for viewport, and transfers data to the viewport
    for (int x = posExtractX; x < posExtractX + viewPortSize; x++)
    {
        for (int y = posExtractY; y < posExtractY + viewPortSize; y++)
        {
            if (x > mapSize - 1 || y > mapSize - 1)
            {
                viewPort[x - posExtractX][y - posExtractY].cellChar = OCEAN_TOKEN;
                viewPort[x - posExtractX][y - posExtractY].discovered = true;
            }
            else
            {
                viewPort[x - posExtractX][y - posExtractY].cellChar = map[x][y].cellChar;
                viewPort[x - posExtractX][y - posExtractY].discovered = map[x][y].discovered;
            }


        }
    }


}

void gamePlay()
{
    //initialize variables
    char userMove;
    char replaceChar = ' ';
    map[currX][currY].discovered = true;

    //plays game while the user has not run out of food nor found the ending position
    while (replaceChar != ENDING_POS || !playerFood)
    {
        //displays the current viewport
        createViewPort();
        displayView();

        printf("Enter a direction to move: [up (u), down (d), left (l), right (r)]: ");
        userMove = tolower(getchar());
        while ((getchar()) != '\n');

        //looks for either up, down, left, or right movement
        //in each case, it checks if the user wants to go out of bounds, otherwise it will move
        //the viewport in the corresponding direction, and replaces the current character with the
        //character in the space the user wants to move in
        switch (userMove)
        {
        case 'u':
            if (currX - 1 > 0)
            {
                currX = currX - 1;
                map[currX][currY].discovered = true;
                if (!userInteract(map[currX][currY].cellChar))
                {
                    currX = currX + 1;
                }
                else
                {
                    replaceChar = map[currX][currY].cellChar;
                    map[currX][currY].cellChar = map[currX + 1][currY].cellChar;
                    map[currX + 1][currY].cellChar = replaceChar;
                }
            }
            else
            {
                printf("You cannot pass ocean tiles!\n");
            }
            break;

        case 'd':
            if (currX + 1 < mapSize)
            {
                currX = currX + 1;
                map[currX][currY].discovered = true;
                if (!userInteract(map[currX][currY].cellChar))
                {
                    currX = currX - 1;
                }
                else
                {
                    replaceChar = map[currX][currY].cellChar;
                    map[currX][currY].cellChar = map[currX - 1][currY].cellChar;
                    map[currX - 1][currY].cellChar = replaceChar;
                }
            }
            else
            {
                printf("You cannot pass ocean tiles!\n");
            }
            break;

        case 'l':
            if (currY - 1 > 0)
            {
                currY = currY - 1;
                map[currX][currY].discovered = true;
                if (!userInteract(map[currX][currY].cellChar))
                {
                    currY = currY + 1;
                }
                else
                {
                    replaceChar = map[currX][currY].cellChar;
                    map[currX][currY].cellChar = map[currX][currY + 1].cellChar;
                    map[currX][currY + 1].cellChar = replaceChar;
                }
            }
            else
            {
                printf("You cannot pass ocean tiles!\n");
            }
            break;

        case 'r':
            if (currY + 1 < mapSize)
            {
                currY = currY + 1;
                map[currX][currY].discovered = true;
                if (!userInteract(map[currX][currY].cellChar))
                {
                    currY = currY - 1;
                }
                else
                {
                    replaceChar = map[currX][currY].cellChar;
                    map[currX][currY].cellChar = map[currX][currY - 1].cellChar;
                    map[currX][currY - 1].cellChar = replaceChar;
                }
            }
            else
            {
                printf("You cannot pass ocean tiles!\n");
            }
            break;

        default:
            printf("That's not a valid move!\n");

        }


    }

    //if either player food has run out or the ending position has been reached, the user will be notified
    if (!playerFood)
    {
        printf("Oh no! You ran out of food and died!\n");
    }
    else
    {
        printf("Congratulations! You have sucessfully completed Oregon Trail!\n");
    }

}

bool userInteract(char cellChar)
{
    //checks if the current character is an animal, river, or disease, and checks if the
    //user wants to retreat or hunt
    switch (cellChar)
    {
    case GRIZZLY:
        printf("You have encountered a Grizzly Bear, would you choose to hunt (h) or retreat (r)?: ");
        if (userAction())
        {
            playerFood = playerFood + map[currX][currY].threat.animal.grizzly.food;
            map[currX][currY].cellChar = ' ';
            return true;
        }
        break;

    case BOAR:
        printf("You have encountered a Boar, would you choose to hunt (h) or retreat (r)?: ");
        if (userAction())
        {
            playerFood = playerFood + map[currX][currY].threat.animal.boar.food;
            map[currX][currY].cellChar = ' ';
            return true;
        }
        break;

    case ELK:
        printf("You have encountered a Elk, would you choose to hunt (h) or retreat (r)?: ");
        if (userAction())
        {
            playerFood = playerFood + map[currX][currY].threat.animal.elk.food;
            map[currX][currY].cellChar = ' ';
            return true;
        }
        break;

    case HARE:
        printf("You have encountered a Hare, would you choose to hunt (h) or retreat (r)?: ");
        if (userAction())
        {
            playerFood = playerFood + map[currX][currY].threat.animal.hare.food;
            map[currX][currY].cellChar = ' ';
            return true;
        }
        break;

    case COLD:
        printf("You have contracted the common cold, your food storage drops by 5 as you take a day off to recuperate");
        playerFood = playerFood + map[currX][currY].threat.disease.cold.food;
        map[currX][currY].cellChar = ' ';
        return true;
        break;

    case FLU:
        printf("You have contracted the flu, your food storage drops by 10 as you take a day off to recuperate");
        playerFood = playerFood + map[currX][currY].threat.disease.flu.food;
        map[currX][currY].cellChar = ' ';
        return true;
        break;

    case DYSENTERY:
        printf("You have contracted dysentery, your food storage drops by 15 as you take a day off to recuperate");
        playerFood = playerFood + map[currX][currY].threat.disease.dysentery.food;
        map[currX][currY].cellChar = ' ';
        return true;
        break;

    case RIVER:
        printf("You are attempting to ford a river; you may either choose to ford (f) or retreat(r): ");
        if (userAction())
        {
            playerFood = playerFood + map[currX][currY].threat.disease.river.food;
            return true;
        }
        break;

    case ENDING_POS:
        return true;

    case ' ':
        return true;
    }

    return false;
}

bool userAction()
{
    //initialize variables
    char userInput;
    bool willHunt = false;
    bool nonValid = false;

    //checks if user wants to fort, hunt, or retreat from the threat
    do
    {
        nonValid = false;
        userInput = tolower(getchar());
        while ((getchar()) != '\n');

        switch (userInput)
        {
        case 'h':
            willHunt = true;
            break;

        case 'f':
            willHunt = false;
            break;

        case 'r':
            willHunt = false;
            break;

        default:
            printf("That is not a valid move!\n");
            nonValid = true;
        }
    } while (nonValid);

    return willHunt;
}
void displayView()
{
    printf("Food: %d\n", playerFood);

    //prints out board with color
    for (int x = 0; x < viewPortSize; x++)
    {
        for (int y = 0; y < viewPortSize; y++)
        {
            if (viewPort[x][y].discovered)
            {

                switch (viewPort[x][y].cellChar)
                {
                case CURRENT_POS:
                    purple();
                    break;
                case OCEAN_TOKEN:
                    cyan();
                    break;
                case GRIZZLY:
                    green();
                    break;

                case BOAR:
                    green();
                    break;

                case ELK:
                    green();
                    break;

                case HARE:
                    green();
                    break;

                case COLD:
                    yellow();
                    break;

                case FLU:
                    yellow();
                    break;

                case DYSENTERY:
                    yellow();
                    break;

                case RIVER:
                    blue();
                    break;

                case ENDING_POS:
                    red();
                    break;
                }
                printf("%c", viewPort[x][y].cellChar);
            }
            else
            {
                white();
                printf("%c", 'U');
            }
        }
        printf("\n");
    }

    reset();
}

void freeMem()
{
    //deallocates memory
    for (int x = 0; x < mapSize; x++)
    {
        free(map[x]);
    }
    free(map);

    for (int x = 0; x < viewPortSize; x++)
    {
        free(viewPort[x]);
    }

    free(viewPort);
}

//sets the the colors for the text in the output
void red()
{
    printf("\033[1;31m");
}

void yellow()
{
    printf("\033[1;33m");
}

void green()
{
    printf("\033[0;32m");
}

void blue()
{
    printf("\033[0;34m");
}

void white()
{
    printf("\033[0;37m");
}
void cyan()
{
    printf("\033[0;36m");
}
void purple()
{
    printf("\033[0;35m");
}
void reset()
{
    printf("\033[0m");
}
