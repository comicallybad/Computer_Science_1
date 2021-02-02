#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leak_detector_c.h"

typedef struct monster
{
    char *name;
    char *element;
    int population;
} monster;

typedef struct region
{
    char *name;
    int nmonsters;
    int total_population;
    monster **monsters;
} region;

typedef struct itinerary
{
    int nregions;
    region **regions;
    int captures;
} itinerary;

typedef struct trainer
{
    char *name;
    itinerary *visits;
} trainer;

monster *createMonster(char *name, char *element, int population)
{
    monster *monster = malloc(sizeof(monster));
    monster->name = malloc((strlen(name) + 1) * sizeof(char));
    monster->element = malloc((strlen(element) + 1) * sizeof(char));
    strcpy(monster->name, name);
    strcpy(monster->element, element);
    monster->population = population;

    return monster;
}

monster **readMonsters(FILE *infile, int *monsterCount)
{
    char name[50];
    char element[50];
    int population;
    monster **monsterList = malloc(sizeof(monster) * *monsterCount);

    for (int i = 0; i < *monsterCount; i++)
    {
        fscanf(infile, "%s %s %d", name, element, &population);
        monsterList[i] = createMonster(name, element, population);
        printf("%s %s %d\n", monsterList[i]->name, monsterList[i]->element, monsterList[i]->population);
    }
    return monsterList;
}

region *createRegion(FILE *infile, char *name, int nmonsters, int monsterCount, monster **monsters)
{
    char monsterName[50];
    region *region = malloc(sizeof(region));
    region->name = malloc((strlen(name) + 1) * sizeof(char));
    strcpy(region->name, name);
    region->monsters = malloc(nmonsters * sizeof(monster));

    printf("%s\n", region->name);
    printf("%d monsters\n", nmonsters);
    for (int i = 0; i < nmonsters; i++)
    {
        fscanf(infile, "%s", monsterName);
        for (int j = 0; j < monsterCount; j++)
        {
            if (strcmp(monsters[j]->name, monsterName) == 0)
            {
                region->monsters[i] = monsters[j];
                printf("%s\n", region->monsters[i]->name);
            }
        }
    }

    return region;
}

region **readRegions(FILE *infile, int *countRegions, monster **monsterList, int monsterCount)
{
    char temp[50];
    char name[50];
    int mcount;
    region **regionList = malloc(sizeof(region) * *countRegions);

    for (int i = 0; i < *countRegions; i++)
    {
        fscanf(infile, "%s", name);
        fscanf(infile, "%d %s", &mcount, temp);

        regionList[i] = createRegion(infile, name, mcount, monsterCount, monsterList);

        printf("\n\n");
    }

    return regionList;
}

trainer *readTrainers(FILE *infile, int *trainerCount, region **regionList, int countRegions)
{
    char temp[50];
    char name[50];
    char regionName[50];
    int captures;
    int regions;

    trainer *trainerList = malloc(*trainerCount * sizeof(trainer));

    for (int i = 0; i < *trainerCount; i++)
    {
        fscanf(infile, "%s", name);
        trainerList[i].name = malloc((strlen(name) + 1) * sizeof(char));
        strcpy(trainerList[i].name, name);

        fscanf(infile, "%d %s", &captures, temp);
        fscanf(infile, "%d %s", &regions, temp);

        trainerList[i].visits = malloc(sizeof(itinerary));
        trainerList[i].visits->nregions = regions;
        trainerList[i].visits->captures = captures;

        trainerList[i].visits->regions = malloc(regions * sizeof(region));

        printf("%s\n", trainerList[i].name);
        printf("%d captures\n", trainerList[i].visits->captures);
        printf("%d regions\n", regions);

        for (int j = 0; j < regions; j++)
        {
            fscanf(infile, "%s", regionName);
            for (int k = 0; k < countRegions; k++)
            {
                if (strcmp(regionList[k]->name, regionName) == 0)
                {
                    trainerList[i].visits->regions[i] = regionList[k];
                    printf("%s\n", trainerList[i].visits->regions[i]->name);
                }
            }
        }
        printf("\n");
    }
    return trainerList;
}

void process_inputs(monster **monsterList, int monsterCount, region **regionList, int regionCount, trainer *trainerList, int trainerCount)
{
}

void release_memory(monster **monsterList, int monsterCount, region **regionList, int regionCount, trainer *trainerList, int trainerCount)
{
    for (int i = 0; i < monsterCount; i++)
    {
        free(monsterList[i]->name);
        free(monsterList[i]->element);
        free(monsterList[i]);
    }

    free(monsterList);

    for (int i = 0; i < regionCount; i++)
    {
        free(regionList[i]->name);
        free(regionList[i]->monsters);
        free(regionList[i]);
    }

    free(regionList);

    for (int i = 0; i < trainerCount; i++)
    {
        free(trainerList[i].name);
        free(trainerList[i].visits->regions);
        free(trainerList[i].visits);
    }
    free(trainerList);
}

int main(void)
{
    atexit(report_mem_leak); //for memory leak detector.
    FILE *inFile, *outFile;

    inFile = fopen("in.txt", "r");

    if (inFile != NULL)
    {
        char temp[50];
        int monsterCount;
        int regionCount;
        int trainerCount;

        fscanf(inFile, "%d %s", &monsterCount, temp);

        printf("%d Monsters\n", monsterCount);

        monster **monsterList = readMonsters(inFile, &monsterCount);

        fscanf(inFile, "%d %s", &regionCount, temp);

        printf("\n%d Regions\n", regionCount);

        region **regionList = readRegions(inFile, &regionCount, monsterList, monsterCount);

        fscanf(inFile, "%d %s", &trainerCount, temp);

        printf("%d Trainers\n", trainerCount);

        trainer *trainerList = readTrainers(inFile, &trainerCount, regionList, regionCount);

        release_memory(monsterList, monsterCount, regionList, regionCount, trainerList, trainerCount);

        outFile = fopen("out.txt", "w");

        fclose(inFile);
        fclose(outFile);
    }
    else
    {
        printf("Please provide correct input file");
        exit(-1);
    }

    return 0;
}