#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct cell{
    char symbol;
    int hardness;
    int mutable;
} cell;

typedef struct dungeon{
    cell map[160][96];
} dungeon;

void printDungeon(dungeon *dungeon)
{
    int x, y;
    for (y = 0; y < 96; y++)
    {
        for (x = 0; x < 160; x++)
        {
            printf("%c", dungeon->map[x][y].symbol);
        }
        printf("\n");
    }
    printf("\n");
}

int isOutermostWall(int x, int y)
{
    if (x == 0 || x == 159 || y == 0 || y == 95)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

int passesHausdorff(dungeon *dungeon, room *testRoom)
{
    int i, j, k, l, m;

    if (dungeon->numRooms <= 0)
    {
        return 1;
    }

    for (i = 0; i < dungeon->numRooms; i++)
    {
        for (j = dungeon->rooms[i].startX; j <= dungeon->rooms[i].endX; j++)
        {
            for (k = dungeon->rooms[i].startY; k <= dungeon->rooms[i].endY; k++)
            {
                for (l = testRoom->startX; l <= testRoom->endX; l++)
                {
                    for (m = testRoom->startY; m <= testRoom->endY; m++)
                    {
                        if (sqrt((j - l) * (j - l) + (k - m) * (k - m)) <= 6)
                        {
                            return -1;
                        }
                    }
                }
            }
        }
    }
    return 1;
}
void generateDungeon()
{    
    dungeon dungeon;

    int x, y;

    for (y = 0; y < 96; y++)
    {
        for (x = 0; x < 160; x++)
        {
            cell *cell = &dungeon.map[x][y];
            cell->symbol = '#'; 
            cell->mutable = isOutermostWall(x, y);
            
            /* assigns the cell a hardness between 0 and 6 this isn't the */
            /* most random, but works for our purposes */
            cell->hardness = rand() % 7;
        }
    }
    printDungeon(&dungeon);
}

int main (int argc, char *argv[])
{
    srand(time(NULL));
    generateDungeon();

    return 0;
}