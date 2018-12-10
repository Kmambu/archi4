#include "stdio.h"

#define BLKSIZ 512
#define FBSIZE 128
#define IMGSIZ FBSIZE*FBSIZE
#define BLKPERIMG IMGSIZ/BLKSIZ

__attribute__((constructor)) void main_display()
{
	char c;
	char buf[FBSIZE*FBSIZE];

	int img;
	for (img = 0; img < 4; img++) {
		tty_printf("loading image no %d\n", img+1);
		if (ioc_read(img*BLKPERIMG, (void *)buf, BLKPERIMG) != 0) {
			tty_puts("ioc_read : error!!!\n");
		}

		if (ioc_completed() != 0) {
			tty_puts("ioc_completed : error!!!\n");
		}
		tty_printf("image no %d\n loaded\n", img+1);

		tty_printf("displaying image no %d\n", img+1);
		if (fb_write(0, (void *)buf, IMGSIZ) != 0) {
			tty_puts("fb_write : error!!!\n");
		}

		if (fb_completed() != 0) {
			tty_puts("fb_completed : error!!!\n");
		}
		tty_printf("image no %d displaying\n", img+1);

		tty_printf("image no %d generated\n", img+1);
		tty_puts("press any key to continue\n");
		tty_getc_irq(&c);
	}
	exit();
} // end main_display

__attribute__((constructor)) void main_timer()
{
	int quit = 0;
	char c;
	timer_set_period(500000);
	timer_set_mode(0x3);
	while(!quit) {
		tty_puts("\n(a)ctivate timer; (d)eactivate timer; (q)uit program : ");
		tty_getc_irq(&c);
		switch(c) {
			case 'a':
				timer_set_mode(0x3);
				tty_puts("\nActivating timer");
				break;
			case 'd':
				timer_set_mode(0x0);
				tty_puts("\nDeactivating timer");
				break;
			case 'q':
				timer_set_mode(0x0);
				quit = 1;
				tty_puts("\nBye-bye!");
				break;
			default:
				tty_puts("\nUnrecognized command ^^'");

		}
	}

	exit();
} // end main

__attribute__((constructor)) void main_roadrollada()
{
	char c;
	while (1) {
		tty_puts("Za Warudo!");
		tty_getc_irq(&c);
	}
	exit();
} // end main
