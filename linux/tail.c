#include <stdio.h>
#include <stdlib.h>

#define N_LINES 10
#define MAX_LINE_LENGTH 1024

static void tail(FILE *f);

int main(int argc, char *argv[]) {
  if (argc != 1) {
    fprintf(stderr, "Usage: %s < infile\n", argv[0]);
    exit(1);
  }
  tail(stdin);
  exit(0);
}

static char ring_buffer[N_LINES][MAX_LINE_LENGTH];

#define RING_BUFFER_INC(idx)                                                   \
  do {                                                                         \
    idx++;                                                                     \
    if (N_LINES <= idx) {                                                      \
      idx = 0;                                                                 \
    }                                                                          \
  } while (0)

static void tail(FILE *f) {
  long cur = 0;
  long n_read_lines = 0;

  // read all lines into rign buffer
  while (fgets(ring_buffer[cur], MAX_LINE_LENGTH, f)) {
    RING_BUFFER_INC(cur);
    n_read_lines++;
  }

  if (n_read_lines < N_LINES) {
    cur = 0;
  }

  for (int n = N_LINES; 0 < n && n_read_lines; n--, n_read_lines--) {
    printf("%s", ring_buffer[cur]);
    RIND_BUFFER_INC(cur);
  }
}