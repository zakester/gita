#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

int main(int argc, char *argv[]) {

  char cmd[MAX_LINE_LENGTH];
  char buffer[MAX_LINE_LENGTH];

  size_t total_insertion = 0;
  size_t total_deletion = 0;

  char *author = argv[1] == NULL ? "" : argv[1];
  snprintf(cmd, sizeof(cmd), "git log --numstat --pretty=\"%s\" --author=%s",
           "%n", author);

  FILE *pipe = _popen(cmd, "r");
  if (pipe == NULL) {
    perror("Error openning pipa");
    return EXIT_FAILURE;
  }

  while (fgets(buffer, MAX_LINE_LENGTH, pipe) != NULL) {
    if (strlen(buffer) > 0 && buffer[0] >= '0' && buffer[0] <= '9') {
      int insertion, deletion;
      sscanf(buffer, "%d %d", &insertion, &deletion);

      total_insertion += insertion;
      total_deletion += deletion;
    }
  }

  _pclose(pipe);

  printf("Total Insertions: %zu\n", total_insertion);
  printf("Total Deletions: %zu\n", total_deletion);
  printf("-----------------------------------------------\n");
  printf("Total: %zu\n", total_insertion + total_deletion);


  return EXIT_SUCCESS;
}
