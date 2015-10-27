// PID namespace 'Hello world'.
//
// Steps:
// 1. Build and run:
//    $ gcc pid_namespace.c
//    $ sudo ./a.out (root privilege is required)
//    We'll see that the child process has pid 1
// 2. List all processes:
//    $ sudo ./a.out bash
//    # ps aux
//    We'll see that the new namespace can still see all processes. To make
//    it only see the processes in its namespace, we need to mount /proc
//    # mount -t proc proc /proc/

#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

static char child_stack[1048576];

struct clone_args {
  char **argv;
};

static int child_exec(void *stuff) {
  printf("PID: %ld\n", (long)getpid()); /* 1 */
  printf("Parent PID: %ld\n", (long)getppid()); /* 0 */
  struct clone_args *args = (struct clone_args *)stuff;
  if (execvp(args->argv[0], args->argv) != 0) {
    fprintf(stderr, "failed to execvp argments %d\n", strerror(errno));
    exit(-1);
  }
  // We should never reach here!
  exit(-1);
}

int main(int argc, char **argv) {
  struct clone_args args;
  args.argv = &argv[1];
  // The clone() function has created a new process by cloning the current one
  // and started execution at the beginning of the child_fn() function. However,
  // while doing so, it detached the new process from the original process tree
  // and created a separate process tree for the new process.
  pid_t child_pid = clone(child_exec, child_stack+1048576, CLONE_NEWPID | SIGCHLD, &args);
  // The child pid here is the pid of the new child process in 'current namespace';
  // in the new namespace, the pid is 0, as printed in the child_fn() above.
  printf("clone() = %ld\n", (long)child_pid); /* e.g. 25658 */

  // Note these processes still have unrestricted access to other common or
  // shared resources. For example, the networking interface: if the child
  // process created above were to listen on port 80, it would prevent every
  // other process on the system from being able to listen on it. Therefore,
  // we need other kind of namespace, e.g. net.

  waitpid(child_pid, NULL, 0);
  return 0;
}