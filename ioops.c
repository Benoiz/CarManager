#include <cmlib.h>

void ReadFileTxt(t_field* f)
{
	char path[21];
	char line[81];
	char delimiter[2] = " ";
	char* p_del;
	FILE *p_file = NULL;
	int count=0; // for assigning structure values

	printf("Type file name in: ");
	scanf("%s", &path);

	p_file = fopen(path, "r");
	if (p_file != NULL) //check for errors
	{	
		while (!feof(p_file))
		{
			fgets(line, 81, p_file);
			if (line[0] == '*')
			{

			}
			else
			{

				p_del = strtok(line, delimiter); //truncate string to get struct values
				strcpy(f->manufacturer, p_del); //manufacturer

				while (p_del != NULL)
				{
					//printf("%s\n", p_del);
					if (count == 1)
					{
						p_del = strtok(NULL, delimiter); //year
						strcpy(f->year, p_del);
						count=0;
						AddEntry(f);
						p_del = NULL;
					}
					else
					{
						p_del = strtok(NULL, delimiter); //model
						if (p_del != 0)
						{
							strcpy(f->model, p_del);
							count++;
						}
					}
				}
			}
				//printf("%s", line);
		}
		
		f->current->after = NULL; // ....->after=NULL after all entries are added
		f->end = f->current;
		printf("...finished reading.\n Press any key to continue!");
		fclose(p_file);
		_getch();
		//ShowMenu(f);
	}
	else
	{
		printf("Error while reading file!\n Press any key to continue.\n");
		_getch();
		free(p_file);
		//ShowMenu(f);
	}

}

void WriteToFileTxt(t_field* f)
{
	char path[21];
	FILE *p_file = NULL;

	printf("Type file name in: ");
	scanf("%s", &path);

	p_file = fopen(path, "w+");
	if (p_file != NULL) //check for errors
	{
		FileHead(p_file); //write title and header

		f->current = f->start;

		while (f->current != NULL)
		{
			fprintf(p_file, "%-10i %-20s %-20s %-20s\n", f->current->index, f->current->manufacturer, f->current->model, f->current->year);
			if (f->current != f->end)
			{
				f->current = f->current->after;
			}
			else
			{
				break;
			}
		}
		printf("...finished writing.\n Press any key to continue!");
		fclose(p_file);
		_getch();
		//ShowMenu(f);
	}
	else
	{
	printf("Error while writing in file!\n Press any key to continue.\n");
	_getch();
	free(p_file);
	//ShowMenu(f);
	}
}