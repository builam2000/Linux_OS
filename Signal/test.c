
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

static void logInfo(const char *who, const char *message);

static void pexit(const char *fCall);

int
main() {
  logInfo("Parent", "creating child");

  switch (fork()) {
    case -1:
      pexit("fork");
      break;

    case 0:
      /* child code: give a chance for parent finish itself (very basic means of
       * process synchronization */
      logInfo("Child", "child created, waiting parent to finish");
      sleep(5);

      char msg[BUFSIZ];
      snprintf(msg, BUFSIZ, "parent PID = %ld", (long) getppid());

      logInfo("Child", msg);
      break;

    default:
      /* parent: nothing to do but finish */
      logInfo("Parent", "finishing up");
      exit(EXIT_SUCCESS);
  }

  /* only child should get to this point */
  exit(EXIT_SUCCESS);
}

static void
logInfo(const char *who, const char *message) {
  char buf[BUFSIZ];
  int size;

  size = snprintf(buf, BUFSIZ, "[%s %ld] %s\n", who, (long) getpid(), message);
  if (write(STDOUT_FILENO, buf, size) == -1) {
    pexit("write");
  }
}

static void
pexit(const char *fCall) {
  perror(fCall);
  exit(EXIT_FAILURE);
}
