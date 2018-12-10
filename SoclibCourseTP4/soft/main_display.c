#include "stdio.h"

#define BLKSIZ 512
#define FBSIZE 128
#define IMGSIZ FBSIZE*FBSIZE
#define BLKPERIMG IMGSIZ/BLKSIZ
__attribute__((constructor)) void main()
{
	char c;
	char buf[FBSIZE*FBSIZE];

	//timer_set_period(500000);
	//timer_set_mode(0x3);

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
		tty_getc(&c);
	}
	exit();
} // end main
