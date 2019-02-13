#include <cmlib.h>

void ShowMenu(t_field* f)
{
	system("cls");
	printf("Welcome to the CarManager!\n");
	printf("Car Management Software by Marc-Andre Gonser\n");
	printf("-------------------------------------------\n");
	printf("Please choose one of the following options!\n");
	printf("-------------------------------------------\n");
	printf("1. Read data from file\n");
	printf("2. Save data to file\n");
	printf("3. Add entry\n");
	printf("4. Sort entries\n");
	printf("5. edit and show entries\n");
	printf("6. Show hex\n");
	printf("7. Clear whole list\n");
	printf("8. Exit\n");

	char choice = _getch();
	printf("%c %i\n", choice, choice);

	switch (choice)
	{
	case'1':
		system("cls");
		ReadFileTxt(f);
		ShowMenu(f);
		break;
	case'2':
		system("cls");
		WriteToFileTxt(f);
		ShowMenu(f);
		break;
	case'3':
		system("cls");
		EntryPrompt(f);
		ShowMenu(f);
		break;
	case'4':
		system("cls");
		printf("1. BubbleSort\n2. QuickSort\n");
		printf("Selection: ");
		char choice2 = _getch();

		switch (choice2)
		{
		case '1':
			system("cls");
			printf("1. Sort by index\n");
			printf("2. Sort by manufacturer\n");
			printf("3. Sort by model\n");
			char choice3 = _getch();
			switch (choice3)
			{
			case '1':
				BubbleSort(f, 1);
				break;
			case'2':
				BubbleSort(f, 2);
				break;
			case'3':
				BubbleSort(f, 3);
				break;
			}
			break;
		case '2':
			//QuickSort(f);
			break;
		case 27:
			ShowMenu(f);
			break;
		default:
			ShowMenu(f);
			break;
			
		}
		ShowMenu(f);
		break;
	case'5':
		system("cls");
		ShowEntries(f);
		ShowMenu(f);
		break;
	case'6':
		Hex(f);
		ShowMenu(f);
		break;
	case'7':
		ClearAllEntries(f);
		ShowMenu(f);
		break;
	case'8':
		printf("Goodbye and thank god the program didn't crash!\n");
		break;
	case 27: //ESC as char int
			printf("Goodbye and thank god the program didn't crash!\n");
			break;
	default:
		printf("Error occurred! What did you do?\n");
			break;

	}
}

	void FileHead(FILE* p_file)
	{
		fprintf(p_file, "*** Vehicle List of the CarManager\n");
		fprintf(p_file, "*** a list of available vehicles\n");
		fprintf(p_file, "***\n");
		fprintf(p_file, "*** Hersteller          Modell                  Baujahr\n");
		fprintf(p_file, "***----------------------------------------------------\n");
	}

	void GUIHead(void)
	{
		printf("*** Vehicle List of the CarManager\n");
		printf("*** a list of available vehicles\n");
		printf("***\n");
		printf("*** Ind            Hersteller           Modell            Baujahr\n");
		printf("***--------------------------------------------------------------\n");
	}