#include <cmlib.h>

void EntryPrompt(t_field* f)
{
	int i = 0;
	int entrycount = 0;
	printf("How many entries do you want to add?\n\nAmount: ");
	scanf("%i", &entrycount);
	fflush(stdin);


	for (i; i < entrycount; i++)
	{
		printf("Insert vehicle manufacturer!:-");
		scanf("%s", f->manufacturer);
		fflush(stdin);
		printf("Insert vehicle model!:-");
		scanf("%s", f->model);
		fflush(stdin);
		printf("Insert vehicle year!:-");
		scanf("%s", f->year);
		fflush(stdin);
		AddEntry(f);
	}
	// setting pointer to 'NULL' because before entry can't have a after entry
	if (entrycount == 0)
	{
		return;
	}
	else
	{
		f->current->after = NULL;
		f->end = f->current;
	}
}

void AddEntry(t_field* f)
{
	f->current = (t_car*)malloc(sizeof(t_car)); //allocate memory for entry
	StructureList(f);
	f->current->before = f->temp;
	f->current->after;
	if (f->temp == 0)f->start = f->current;
	else f->temp->after = f->current;
	SetIndex(f);
	f->temp = f->current;

}

void SetIndex(t_field* f)
{
	if (!f->current->before)
	{
		f->current->index = (*f).index;
	}
	else
	{
		f->current->index = ((*f->temp).index)+1;
	}
}

void StructureList(t_field * f)
{
	strcpy(f->current->year, f->year);
	strcpy(f->current->manufacturer, f->manufacturer);
	strcpy(f->current->model, f->model);
}

void DeleteEntry(t_field* f, int indnumber)
{	
	//int indnumber = 2;
	FindEntryByIndex(f, indnumber);
	
	if (!f->current) 
	{
		return;
	}
	else if (f->current->before && f->current->after) //Entry between others
	{													
		f->current->before->after = f->current->after;
		f->current->after->before = f->current->before;
		free(f->current);
		f->current = f->start;
	}
	else if (f->current->after) //Is first Entry
		{							
		f->current->after->before = 0;
		f->start = f->current->after;
		free(f->current);
		f->current = f->start;
		}
	else if (f->current->before) //Is last Entry
	{							
		f->current->before->after = 0;
		free(f->current);
		f->current = f->start;
	}
	}

void ClearAllEntries(t_field* f)
{
	while(f->current != NULL)
	{
		f->current = 0;
		f->start = 0;
		f->end = 0;
		f->temp = 0;
	}
}

t_car* FindEntryByIndex(t_field* f, int wanted)
{
	//wanted = 0;
	f->current = f->start;
	while (f->current)
	{
		if (wanted == f->current->index)
		{
			return f->current;
		}
		f->current = f->current->after;
	}
	return 0;
}

void Hex(t_field * f)
{
	f->current = f->start;
	while (f->current)
	{
		printf("\n %-10s %X %X %X", f->current, f->current->before, f->current->after, f->current->year);
		f->current = f->current->after;
	}
		_getch();
}

void ShowEntries(t_field* f)
{
	int listcount = 0;
	f->current = f->start;

	GUIHead();
		while (f->current != NULL)
		{
			if (listcount == 4)
			{
				printf("press l to load more entries or d to delete an entry\n\n");
				char choice = _getch();
				if (choice == 'l') listcount = 0;
				if (choice == 'd')
				{
					printf("Please write the index number of the entry that will be deleted: ");
					char choice2 = _getch();
					DeleteEntry(f, choice2);
				}
			}
			else
			{
				printf("\t%-10i %-20s %-20s %-20s\n", f->current->index, f->current->manufacturer, f->current->model, f->current->year);
				listcount++;
				if (f->current != f->end)
				{
					f->current = f->current->after;
				}
				else
				{
					break;
				}
			}
		}
		_getch();
	//}
}
