 /*
  *
  * Hexadecimal input to Binary viewer
  *
  * Copyright (C) 2008-2018 Texas Instruments Incorporated - http://www.ti.com/
  *     Nishanth Menon
  * This program is free software; you can redistribute it and/or modify
  * it under the terms of the GNU General Public License version 2 as
  * published by the Free Software Foundation.
  *
  * This program is distributed "as is" WITHOUT ANY WARRANTY of any
  * kind, whether express or implied; without even the implied warranty
  * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  */

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void help()
{
	printf("Convert hex input to a binary output\n"
	       "Options:\n"
	       "{-v}           : print vertical[default horizontal]\n"
	       "{-h}           : this help\n"
	       "{-r}           : inverted order [default is incremental]\n"
	       "{-s [8|16|32]} : input is 8, 16 or 32 bit wide[default is 32bits]\n"
	       "{-i [val]}     : input value - if provided, will exit, else will"
	       " repeat for multiple entries\n");
}

void print_vert(unsigned int dat, int size, int dec)
{
	int start = (dec) ? size - 1 : 0;
	int end = (dec) ? -1 : size;
	int idx;
	int x = 0;
	int bits = 0;
	for (idx = start; idx != end; (dec) ? idx-- : idx++) {
		printf("[%02d] - %01d\n", idx, (dat & (1 << idx)) ? 1 : 0);
		if (dec) {
			x <<= 1;
			x |= (dat & (1 << idx)) ? 1 : 0;
		} else {
			x |= ((dat & (1 << idx)) ? 1 : 0) << bits;
		}
		if (bits == 3) {
			printf("-- 0x%01x --\n", x);
			bits = 0;
			x = 0;
		} else {
			bits++;
		}
	}
}

void print_horiz(unsigned int dat, int size, int dec)
{
	int start = (dec) ? size - 1 : 0;
	int end = (dec) ? -1 : size;
	int idx;
	char print_buff[255];
	char line_buff[255];
	char tbuff[10];
	int x;
	int bits = 0;
	sprintf(print_buff, "|");
	sprintf(line_buff, "-");
	for (idx = start; idx != end; (dec) ? idx-- : idx++) {
		sprintf(tbuff, " %02d|", idx);
		strcat(print_buff, tbuff);
		strcat(line_buff, "----");
	}
	printf("%s\n%s\n%s\n", line_buff, print_buff, line_buff);
	sprintf(print_buff, "|");
	for (idx = start; idx != end; (dec) ? idx-- : idx++) {
		sprintf(tbuff, " %01d |", (dat & (1 << idx)) ? 1 : 0);
		strcat(print_buff, tbuff);
	}
	printf("%s\n%s\n", print_buff, line_buff);
	x = 0;
	bits = 0;
	sprintf(print_buff, "|");
	for (idx = start; idx != end; (dec) ? idx-- : idx++) {
		if (dec) {
			x <<= 1;
			x |= (dat & (1 << idx)) ? 1 : 0;
		} else {
			x |= ((dat & (1 << idx)) ? 1 : 0) << bits;
		}
		if (bits == 3) {
			sprintf(tbuff, "0x%01x|", x);
			bits = 0;
			x = 0;
		} else {
			sprintf(tbuff, "    ");
			bits++;
		}
		strcat(print_buff, tbuff);
	}
	printf("%s\n%s\n", print_buff, line_buff);
}

int main(int argc, char *argv[])
{
	unsigned int data = 0x0;
	unsigned char loop = 1;
	unsigned char size = 32;
	unsigned char horiz = 1;
	unsigned char dec = 1;
	char opt;
	while ((opt = getopt(argc, argv, "vhrs:i:")) != -1) {
		switch (opt) {
		case 'v':
			horiz = 0;
			break;
		case 'h':
			help();
			return -1;
		case 'r':
			dec = 0;
			break;
		case 's':
			size = atoi(optarg);
			if ((size != 8) && (size != 16) && (size != 32)) {
				printf("size %d should have been 8,16 or 32 \n",
				       size);
				help();
				return -2;
			}
			loop = 0;
			break;
		case 'i':
			sscanf(optarg, "%x", &data);
			loop = 0;
			break;
		default:
			help();
			return (-3);
		}
	}

	/* if required, loop up to gobble more user entry */
	do {
		if (loop) {
			printf("Enter Data(CTRL+C will quit)-size %d bits: ",
			       size);
			if (scanf("%x", &data) != 1) {
				printf("Did not get the data I expected!\n");
				return(-4);
			}
		}
		if (horiz) {
			print_horiz(data, size, dec);
		} else {
			print_vert(data, size, dec);
		}
	} while (loop);
	return 0;
}
