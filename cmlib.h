#pragma once

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <malloc.h>
#include <stdarg.h>

typedef struct m_car
{
	char year[21];
	char manufacturer[21];
	char model[21];
	int index;
	struct m_car* before;
	struct m_car* after;
}t_car;

typedef struct
{
	char year[21];
	char manufacturer[21];
	char model[21];
	int index;
	t_car* current, *temp, *start, *end, *tcopy;

}t_field;

// prototypes of functions

//list functions
void AddEntry(t_field* f);
void AddEntryAnywhere(t_field* f, int indx);
void StructureList(t_field* f);
void Hex(t_field* f);
void EntryPrompt(t_field* f, int opt);

void DeleteEntry(t_field* f, int indnumber);
void DelMultiEnt(t_field* f);
void ClearAllEntries(t_field* f);

void SetIndex(t_field* f);
void AdaptIndex(t_field* f);

void ShowEntries(t_field* f);
t_car* FindEntryByIndex(t_field* f, int wanted);
//gui functions
void ShowMenu(t_field* f);
void FileHead(FILE* p_file);
void GUIHead(void);
void ShowSelectedEntry(t_field* f, int indx);
//sort functions
void BubbleSort(t_field* f, int sortValue);
//void QuickSort(t_field* f);
void switchEntries(t_field *f, int indexA, int indexB);
//io functions
void ReadFileTxt(t_field* f);
void WriteToFileTxt(t_field* f);


