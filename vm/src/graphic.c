#include "vm.h"

/* Function that adds informations on the GUI, feel free to add anything you want. */

void            init_gui(t_gui *gui)
{
	gui->win = init_screen(gui->win, MAX_X + 1, 1, 1);
	gui->win_info = init_screen(gui->win_info, 30, 1, MAX_X + 2);
	gui->speed = 1;
}

void            print_info(t_gui *gui, t_vm *vm)
{
	init_pair(9, COLOR_WHITE, COLOR_BLACK);
	wattron(gui->win, COLOR_PAIR(9));
	mvwprintw(gui->win_info, 1, 1, "Cycle: %d", vm->corewar.cycle);
	mvwprintw(gui->win_info, 2, 1, "Speed: x%u", gui->speed);
	mvwprintw(gui->win_info, 3, 1, "Kill cycle: %d", vm->corewar.kill_cycle);
	wattroff(gui->win, COLOR_PAIR(9));
}               

/* Update current status of window */

char        	update_screen(WINDOW *win)
{
	usleep(2500);
	clear();
	wrefresh(win);
	return (wgetch(win));
}

/* Terminate GUI */

void            end_screen(void)
{
	endwin();
	exit(1);
}

/* Fills main window with 0's */

static void     fill_map(WINDOW *win)
{
	int x;
	int y;

	x = -2;
	y = 1;

	while (y != MAX_Y)
	{
	   if (x == MAX_X - 2)
		{
			x = -2;
			y++;
		}
		else { 
		x += 3;
		mvwprintw(win, y, x, "00");
		}
	}
}

/*
** Updates both GUI windows and checks for users input.
*/

void			update_gui(t_vm *vm, t_gui *gui)
{
	if (update_screen(gui->win) == ESC || update_screen(gui->win_info) == ESC)
		end_screen();
	if (update_screen(gui->win) == SPACE || update_screen(gui->win_info) == SPACE)
		gui->speed = (gui->speed == 5) ? 1 : gui->speed + 1;
	print_info(gui, vm);	
    print_mem(vm, gui);
}

/* Initialise a new window */

WINDOW            *init_screen(WINDOW *win, int max_x, int y, int x)
{
	initscr();
	start_color();
	cbreak();
	noecho();
	curs_set(0);
	win = newwin(MAX_Y + 1, max_x, y, x);
	nodelay(win, true);
	box(win, 0, 0);
	keypad(win, true);
	if (x == 1)
		fill_map(win);
	return (win);
}