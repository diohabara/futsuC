#include <stdio.h>
#include <stdlib.h>

static void do_cat(FILE *fp);

int main(int argc, char *argv[]) {
  if (argc == 1) {
    do_cat(stdin);
    exit(0);
  }
  for (int i = 1; i < argc; i++) {
    FILE *fp = fopen(argv[i], "r");
    if (!fp) {
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
    switch (c) {
    case '\n':
      if (fputs("\\t", stdout) == EOF)
        exit(1);
      break;
    case '\t':
      if (fputs("\\n", stdout) == EOF)
        exit(1);
      break;
    default:
      if (putchar(c) < 0)
        exit(1);
      break;
    }
  }
}
