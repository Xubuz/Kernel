#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <print.h>

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t *terminal_buffer_tmp;
uint16_t *terminal_buffer;

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg)
{
    return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color)
{
    return (uint16_t)uc | (uint16_t)color << 8;
}

size_t strlen(const char *str)
{
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}

void push_buffer(void)
{
    for (size_t i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++)
    {
        terminal_buffer[i] = terminal_buffer_tmp[i];
    }
}

void scroll(void){
    for (size_t i = VGA_WIDTH; i < VGA_WIDTH*VGA_HEIGHT; i++)
    {
        terminal_buffer_tmp[i-VGA_WIDTH] = terminal_buffer_tmp[i];
    }
    push_buffer();
}

void initialize_terminal(void)
{
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
    terminal_buffer = (uint16_t *)0xB8000;
    for (size_t y = 0; y < VGA_HEIGHT; y++)
    {
        for (size_t x = 0; x < VGA_WIDTH; x++)
        {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer_tmp[index] = vga_entry(' ', terminal_color);
        }
    }
    push_buffer();
}

void put_char(char c)
{
    if (c == '\n')
    {
        ++terminal_row;
        terminal_column = 0;
    }
    else
    {
        const size_t index = terminal_column + (terminal_row * VGA_WIDTH);
        terminal_buffer_tmp[index] = vga_entry(c, terminal_color);
        if (++terminal_column == VGA_WIDTH)
        {
            terminal_column = 0;
        }
        if (++terminal_row == VGA_HEIGHT /*&& terminal_column == VGA_WIDTH*/){
            terminal_row=0;
        }
    }
}

void write_terminal(const char *data, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        put_char(data[i]);
    }
    push_buffer();
}

void print_terminal(const char *data)
{
    write_terminal(data, strlen(data));
}
