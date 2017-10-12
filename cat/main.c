#include <stdio.h>
#include <stdlib.h>

void do_cat(const int argc, const char *argv[]);
void put_stream(FILE *f);
void die(const char *s);

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
      die(argv[1]);
    }
    put_stream(f);
    fclose(f);
  }
}

void
put_stream(FILE *f)
{
  char buf[64];
  for (;;) {
    size_t n_read = fread(buf, 1, sizeof(buf), f);
    if (ferror(f)) die(""); // FIXME
    size_t n_written = fwrite(buf, 1, n_read, stdout);
    if (n_written < n_read) die(""); // FIXME
    if (n_read < sizeof(buf)) break;
  }
}

void
die(const char *s)
{
  perror(s);
  exit(1);
}
