#include <cmlib.h>

void main(void)
{
	t_field field;
	t_field* f = &field;
	(*f).index = 1;

	//reset pointer
	f->current = 0;
	f->start = 0;
	f->end = 0;
	f->temp = 0;
	ShowMenu(f);

	_getch();
}
