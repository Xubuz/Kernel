#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <print.h>

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

void kernel_main(void) {
	print_terminal("");
	print_terminal("hi\n");
	print_terminal("hi\n");
	print_terminal("hi\n");
	print_terminal("hi\n");
	print_terminal("hi\n");
	print_terminal("hi\n");
	print_terminal("hi\n");
	print_terminal("hi\n");
	print_terminal("hi\n");
	print_terminal("hi\n");
	print_terminal("hi\n");
	print_terminal("hi\n");
	print_terminal("hi\n");
	print_terminal("hi\n");
	print_terminal("hi\n");
	print_terminal("hi\n");
	print_terminal("hi\n");
	print_terminal("hi\n");
	print_terminal("hi\n");
	print_terminal("hi\n");
	print_terminal("hi\n");
	print_terminal("hi\n");
	print_terminal("hi\n");
	print_terminal("hi\n");
	print_terminal("hitest\n");
	print_terminal("hitwst2\n");
	print_terminal("hWFti\n");
}

void kernel_start(void){
	initialize_terminal();
	kernel_main();
}

