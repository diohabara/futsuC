#include <stdio.h>
#include <stdlib.h>

static void do_wc_l(FILE *fp);

int main(int argc, char *argv[]) {
  if (argc == 1) {
    do_wc_l(stdin);
  }
  for (int i = 1; i < argc; i++) {
    FILE *fp;

    fp = fopen(argv[i], "r");
    if (!fp) {
      perror(argv[i]);
      exit(1);
    }
    do_wc_l(fp);
    fclose(fp);
  }
  exit(1);
}

static void do_wc_l(FILE *fp) {
  unsigned long n;
  int c;
  int prev = '\n';

  n = 0;
  while ((c = getc(fp)) != EOF) {
    if (c == '\n') {
      n++;
    }
    prev = c;
  }
  if (prev != '\n') {
    n++;
  }
  printf("%lu\n", n);
}
