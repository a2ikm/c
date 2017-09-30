#include <stdio.h>
#include <stdlib.h>

void do_cat(const int argc, const char *argv[]);
void put_stream(FILE *f);

int
main(const int argc, const char *argv[])
{
  if (argc == 1) {
    put_stream(stdin);
  } else {
    do_cat(argc, argv);
  }
  exit(1);
}

void
do_cat(const int argc, const char *argv[])
{
  int i;
  for (i = 1; i < argc; i++) {
    FILE *f;
    f = fopen(argv[i], "r");
    if (!f) {
      perror(argv[i]);
      exit(1);
    }
    put_stream(f);
    fclose(f);
  }
}

void
put_stream(FILE *f)
{
  int c;
  while ((c = fgetc(f)) != EOF) {
    if (putchar(c) < 0) exit(1);
  }
}
