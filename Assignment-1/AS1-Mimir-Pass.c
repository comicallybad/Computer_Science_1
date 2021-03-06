#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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

//Create a monster and assign its name, element, and population
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

//Create an array of monsters by calling createMonster for each one
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
    }
    return monsterList;
}

//Create a region and assign it's name, nmonsters, associated monsters and total_population
region *createRegion(FILE *infile, char *name, int nmonsters, int monsterCount, monster **monsters)
{
    char monsterName[50];
    region *region = malloc(sizeof(region));
    region->name = malloc((strlen(name) + 1) * sizeof(char));
    strcpy(region->name, name);
    region->monsters = malloc(nmonsters * sizeof(monster));
    region->nmonsters = nmonsters;

    int totalPop = 0;
    for (int i = 0; i < nmonsters; i++)
    {
        fscanf(infile, "%s", monsterName);
        for (int j = 0; j < monsterCount; j++)
        {
            if (strcmp(monsters[j]->name, monsterName) == 0)
            {
                region->monsters[i] = monsters[j];
                totalPop += monsters[j]->population;
            }
        }
    }

    region->total_population = totalPop;

    return region;
}

//Create an array of regions by calling createRegion for each one
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
    }

    return regionList;
}

//Create array of trainers and assign their name, captures, and regions
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

        for (int j = 0; j < regions; j++)
        {
            fscanf(infile, "%s", regionName);
            for (int k = 0; k < countRegions; k++)
            {
                if (strcmp(regionList[k]->name, regionName) == 0)
                {
                    trainerList[i].visits->regions[j] = regionList[k];
                }
            }
        }
    }
    return trainerList;
}

//Using the itinerary, this searches through, and calculates the amount of monsters a trainer will catch in each region
void process_inputs(FILE *ofp, monster **monsterList, int monsterCount, region **regionList, int regionCount, trainer *trainerList, int trainerCount)
{
    for (int i = 0; i < trainerCount; i++)
    {
        fprintf(ofp, "%s\n", trainerList[i].name);
        printf("%s\n", trainerList[i].name);
        for (int j = 0; j < trainerList[i].visits->nregions; j++)
        {
            int mPopulation;
            fprintf(ofp, "%s\n", trainerList[i].visits->regions[j]->name);
            printf("%s\n", trainerList[i].visits->regions[j]->name);
            for (int k = 0; k < trainerList[i].visits->regions[j]->nmonsters; k++)
            {
                int tPopulation = trainerList[i].visits->regions[j]->monsters[k]->population;
                int captures = trainerList[i].visits->captures;
                float mcount = (double)tPopulation / trainerList[i].visits->regions[j]->total_population;
                mcount *= captures;
                int caught = round(mcount);
                if (caught != 0)
                {
                    fprintf(ofp, "%d %s\n", caught, trainerList[i].visits->regions[j]->monsters[k]->name);
                    printf("%d %s\n", caught, trainerList[i].visits->regions[j]->monsters[k]->name);
                }
            }
            mPopulation = 0;
        }
        if (i < trainerCount - 1)
        {
            fprintf(ofp, "\n");
            printf("\n");
        }
    }
}

//Release all memory that has been allocated throughout the program and for structures
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

//Main function, start by scanning in monster count, region count, trainer count, then process inputs, release mem and write data
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

        monster **monsterList = readMonsters(inFile, &monsterCount);

        fscanf(inFile, "%d %s", &regionCount, temp);

        region **regionList = readRegions(inFile, &regionCount, monsterList, monsterCount);

        fscanf(inFile, "%d %s", &trainerCount, temp);

        trainer *trainerList = readTrainers(inFile, &trainerCount, regionList, regionCount);

        outFile = fopen("out.txt", "w");

        process_inputs(outFile, monsterList, monsterCount, regionList, regionCount, trainerList, trainerCount);

        release_memory(monsterList, monsterCount, regionList, regionCount, trainerList, trainerCount);

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