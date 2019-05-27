#ifndef KERNEL_H
#define KERNEL_H

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;


#define VGA_ADDRESS 0xB8000
#define BUFSIZE 2200
#define NULL 0

uint16* vga_buffer;

extern void keyboard_handler(void);
extern void write_port(unsigned short port, unsigned char data);
extern char read_port(unsigned short port);
extern void print(char *str);
extern void putnbr(int nb);
extern unsigned int new_line(void);
extern void black_screen(void);

enum vga_color {
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    GREY,
    DARK_GREY,
    BRIGHT_BLUE,
    BRIGHT_GREEN,
    BRIGHT_CYAN,
    BRIGHT_RED,
    BRIGHT_MAGENTA,
    YELLOW,
    WHITE,
};

#endif
