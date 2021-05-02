#include <stdio.h>
#include <stdlib.h>

static void do_cat(const char *path);
static void die(const char *s);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "%s: file name not given\n", argv[0]);
    exit(1);
  }
  for (int i = 1; i < argc; i++) {
    do_cat(argv[i]);
  }
  exit(0);
}

#define BUFFER_SIZE 2048

static void do_cat(const char *path) {
  unsigned char buf[BUFFER_SIZE];
  FILE *fp = fopen(path, "r");

  if (!fp)
    die(path);

  for (;;) {
    size_t n_read = fread(buf, 1, sizeof(buf), fp);
    if (ferror(fp))
      die(path);
    size_t n_written = fwrite(buf, 1, sizeof(buf), stdout);
    if (n_written < n_read)
      die(path);
    if (n_read < sizeof(buf))
      break;
  }
  if (fclose(fp) != 0)
    die(path);
}

static void die(const char *s) {
  perror(s);
  exit(1);
}
