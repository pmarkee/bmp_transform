all:
	gcc -I. transform.c bmp_tools.c transform_tools.c -o transform

preproc:
	gcc -I. -E transform.c -o transform.i
	gcc -I. -E bmp_tools.c -o bmp_tools.i
	gcc -I. -E transform_tools.c -o transform_tools.i

debug:
	gcc -g -I. transform.c bmp_tools.c transform_tools.c -o transform -DDEBUG
