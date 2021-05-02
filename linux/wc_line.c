#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int count_loc(FILE *fp);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "%s: file name not given\n", argv[0]);
    exit(1);
  }

  for (int i = 1; i < argc; i++) {
    FILE *fp;
    int lineCount;

    fp = fopen(argv[i], "r");
    if (fp < 0) {
      perror(argv[i]);
      exit(1);
    }
    lineCount = count_loc(fp);
    printf("%s has %d lines of code\n", argv[i], lineCount);
    fclose(fp);
  }
  exit(0);
}

static int count_loc(FILE *fp) {
  int c;
  int lineCount = 0;

  while ((c = fgetc(fp)) != EOF) {
    if (c == '\n')
      lineCount++;
  }
  return lineCount;
}
