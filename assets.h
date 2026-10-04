#ifndef ASSETS_H
#define ASSETS_H

#define MAX_ASSETS 40

typedef struct {
    int id;
    char name[50];
    char type[30];
    float value;
    char department[30];
    char condition[20];
} Asset;

void assetManagement();
void addAsset();
void displayAssets();

#endi
