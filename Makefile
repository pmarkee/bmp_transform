all:
	gcc -I. transform.c bmp_tools.c transform_tools.c -o transform

debug:
	gcc -g -I. transform.c bmp_tools.c transform_tools.c -o transform -DDEBUG
