#include <stdio.h>
#include <stdlib.h>

static void do_cat(FILE *);

int main(int argc, char *argv[]) {
  if (argc == 1) {
    do_cat(stdin);
    exit(0);
  }

  for (int i = 1; i < argc; i++) {
    FILE *fp;

    fp = fopen(argv[i], "r");
    if (fp < 0) {
      perror(argv[i]);
      exit(1);
    }
    do_cat(fp);
    fclose(fp);
  }
  exit(0);
}

static void do_cat(FILE *fp) {
  int c;

  while ((c = fgetc(fp)) != EOF) {
    if (putchar(c) < 0)
      exit(1);
  }
}
