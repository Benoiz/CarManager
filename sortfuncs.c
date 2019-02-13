#include <cmlib.h>

void BubbleSort(t_field* f, int sortValue)
{
	int i = 1;
	int j = 1;
	int lc = 18;
	for (i = 1; i < lc; i++) 
	{
		for (j = 2; j < lc; j++) 
		{
			t_car* carA = FindEntryByIndex(f, j-1);
			t_car* carB = FindEntryByIndex(f, j);
			if (sortValue == 1) 
			{ //Sort by index
				if (carA->index > carB->index) 
				{
					switchEntries(f, j - 1, j);
				}
			}
			if (sortValue == 2) { //Sort by manufacturer
				if (strcmp(carA->manufacturer, carB->manufacturer) > 0) 
				{
					switchEntries(f, j - 1, j);
				}
			}
			if (sortValue == 3) 
			{ //Sort by model
				if (strcmp(carA->model, carB->model) > 0) 
				{
					switchEntries(f, j - 1, j);
				}
			}
		}
	}
}

//void QuickSort(t_field* f, int left, int right, int sortValue)
//{
//	int indexL = left,indexR = right, med = (left + right) / 2;
//	while (indexL <indexR) 
//	{
//		switch (sortValue) 
//		{
//		case 2:		//Sort by index
//			while (FindEntryByIndex(indexL)->index < FindEntryByIndex( med)->index) 
//			{
//				indexL++;
//			}
//			while (FindEntryByIndex(indexR)->index > FindEntryByIndex( med)->index) 
//			{
//				indexR--;
//			}
//			break;
//		case 0:		//Sort by manufacturer
//			while (strcmp(FindEntryByIndex(indexL)->manufacturer, FindEntryByIndex( med)->manufacturer) < 0) 
//			{
//				indexL++;
//			}
//			while (strcmp(FindEntryByIndex(indexR)->manufacturer, FindEntryByIndex( med)->manufacturer) > 0) 
//			{
//				indexR--;
//			}
//			break;
//		case 1:		//Sort by model
//			while (strcmp(FindEntryByIndex(indexL)->model, FindEntryByIndex( med)->model) < 0) 
//			{
//				indexL++;
//			}
//			while (strcmp(FindEntryByIndex(indexR)->model, FindEntryByIndex( med)->model) > 0) 
//			{
//				indexR--;
//			}
//			break;
//		}
//
//		switchEntries(f,indexL,indexR);
//		if (indexL == med) 
//		{
//			med =indexR;
//		}
//		else {
//			if (indexR == med) 
//			{
//				med =indexL;
//			}
//		}
//		if (indexL < med) 
//		{
//			indexL++;
//		}
//		if (indexR > med) 
//		{
//			indexR--;
//		}
//	}
//	if (left < med - 1) 
//	{
//		quick_sort_alg(f, left, med - 1, sortValue);
//	}
//	if (right > med + 1) 
//	{
//		QuickSort(f, med + 1, right, sortValue);
//	}
//}

void switchEntries(t_field *f, int indexA, int indexB) 
{

	t_car *carA_before = FindEntryByIndex(f, indexA - 1);
	t_car *carA = FindEntryByIndex(f, indexA);
	t_car *carA_after = FindEntryByIndex(f, indexA + 1);

	t_car *carB_before = FindEntryByIndex(f, indexB - 1);
	t_car *carB = FindEntryByIndex(f, indexB);
	t_car *carB_after = FindEntryByIndex(f, indexB + 1);

	if (carA_after == carB && carB_before == carA) 
	{								//CASE 1: carB is after to carA
		if (carA_before) 
		{
			carB->before = carA_before;
			carA_before->after = carB;
		}
		else 
		{
			carB->before = 0;
			f->start = carB;
		}
		if (carB_after) {
			carB_after->before = carA;
			carA->after = carB_after;
		}
		else 
		{
			carA->after = 0;
			f->temp = carA;
		}
		carA->before = carB;
		carA->after = carB->after;
		carB->before = carA_before;
		carB->after = carA;
	}
	else 
	{
		if (carA_before && carA_after && carB_before && carB_after) 
		{				//CASE 2: carA and carB are somwhere inside the List
			carA_before->after = carB;
			carB->after = carA_after;
			carB->before = carA_before;
			carA_after->before = carB;

			carB_before->after = carA;
			carA->after = carB_after;
			carA->before = carB_before;
			carB_after->before = carA;
		}
		else {
			if (!carA_before && carA_after && carB_before && carB_after) 
			{			//CASE 3: carA is first Item
				carB->before = 0;
				f->start = carB;
				carB->after = carA_after;

				carB_before->after = carA;
				carA->after = carB_after;
				carA->before = carB_before;
				carB_after->before = carA;
			}
			else {
				if (carA_before && carA_after && carB_before && !carB_after) 
				{		//CASE 4: carB is before Item
					carA->after = 0;
					f->temp = carA;
					carA->before = carB_before;
					carB_before->after = carA;

					carA_before->after = carB;
					carB->after = carA_after;
					carB->before = carA_before;
					carA_after->before = carB;
				}
				else {
					if (!carA_before && carA_after && carB_before && !carB_after) 
					{	//CASE 5: carA ist first and carB ist before Item
						carB->before = 0;
						f->start = carB;
						carB->after = carA_after;

						carA->after = 0;
						f->temp = carA;
						carA->before = carB_before;


						carA_after->before = carB;
						carB_before->after = carA;
					}
				}

			}
		}
	}
}