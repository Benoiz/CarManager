#include <cmlib.h>

void EntryPrompt(t_field* f, int indx)
{
	//va_list opt_ptr;
	int i = 0;
	int entrycount = 0;
	printf("How many entries do you want to add?\n\nAmount: ");
	scanf("%i", &entrycount);
	fflush(stdin);
	//va_start(opt_ptr, f, opt);
	//int optional = va_arg(opt_ptr, int);

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
		if (indx == 0)
		{
			AddEntry(f);
		}
		else
		{
			AddEntryAnywhere(f, indx);
		}
	}
	//va_end(opt_ptr);
	
	// setting pointer to 'NULL' because last entry can't have an next entry
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

void AdaptIndex(t_field* f)
{	

	f->current = f->start;
	(*f->current).index = 1;
	f->current = f->current->after;
	while (f->current != f->end)
	{
		(*f->current).index = (*f->current->after).index +1;
		f->current = f->current->after;
	}


}

void DelMultiEnt(t_field* f)
{
	int input, n, i;
	int count = 0;
	int* numbers = NULL;
	int* more_numbers = NULL;

	do {
		printf("Enter index number of entry to delete (0 to finish): ");
		scanf("%d", &input);
		count++;

		more_numbers = (int*)realloc(numbers, count * sizeof(int));

		if (more_numbers != NULL) {
			numbers = more_numbers;
			numbers[count - 1] = input;
		}
		else {
			free(numbers);
			puts("Error (re)allocating memory");
			exit(1);
		}
	} while (input != 0);

	printf("Numbers entered: ");
	for (n = 0; n < count; n++) printf("%d ", numbers[n]);

	printf("Are you sure (y/n)");
	char choice =_getch();
	if (choice == 'y')
	{
		for (i = 0; i < count; i++) DeleteEntry(f, numbers[i]);
	}
	else
	{
		return;
	}
	free(numbers);
	AdaptIndex(f);


}

void CopyEntryAndEdit(t_field* f)
{

}

void AddEntryAnywhere(t_field* f, int indx)
{
	f->current=FindEntryByIndex(f, indx);


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
		//free(f->current);
		//f->current = f->start;
	}
	else if (f->current->after) //Is first Entry
		{							
		f->current->after->before = 0;
		f->start = f->current->after;
		//free(f->current);
		//f->current = f->start;
		}
	else if (f->current->before) //Is last Entry
	{	
		f->end = f->current->before;
		f->current->before->after = 0;
	}
	free(f->current);
	f->current = f->start;
	AdaptIndex(f);
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
	f->current = f->start;
	int min = 1;
	int max = (*f->current).index;
	if (wanted > 1 && wanted < max)
	{
		while (f->current)
		{
			if (wanted == f->current->index)
			{
				return f->current;
			}
			f->current = f->current->after;
		}
	}
	else
	{
		return NULL;
	}
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
	int countmax = 4;
	int indxinput = 0;
	int choice;
	f->current = f->start;
	system("cls");
	GUIHead();
		while (f->current != f->end)
		{
			if (listcount == countmax)
			{	
				printf("\nOptions:\n");
				printf("1: load next entries\n");
				printf("2: load previous entries\n");
				printf("3: Select entry\n");
				printf("4: Go back\n");
				choice = scanf("%i", &choice);

				switch (choice)
				{
				case 1:
					countmax = countmax + 4;
					break;
				case 2:
					break;
				case 3:
					printf("\nIndex number: ");
					scanf("%i", &indxinput);
					ShowSelectedEntry(f, indxinput);
					break;
				case 4:
					ShowMenu(f);
					break;
				default:
					printf("bad choice!");
					//goto RELOOP;
					break;
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
					printf("\t%-10i %-20s %-20s %-20s\n", f->current->index, f->current->manufacturer, f->current->model, f->current->year);

					break;
				}
			}
		}

		_getch();
}
