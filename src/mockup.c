#include <pthread.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
static int (*_foo_ptr)();

static pthread_once_t _init = PTHREAD_ONCE_INIT;
static __thread volatile int in_init = 0;
static volatile int _initialized = 0;

extern void bar(int);
extern int var;

static void _load_target() {
  char *s = NULL;
  void *handle = NULL;
  void *tmp;

  s = getenv("LIBTARGET");
  if (s)
    handle = dlopen(s, RTLD_LAZY | RTLD_GLOBAL | RTLD_DEEPBIND);
  else {
    fprintf(stderr, "LIBTARGET nor defined\n!");
    exit(1);
  }
  s = dlerror();
  if( !handle ) {
    fprintf(stderr, "Failure: could not load target library: %s!\n", s);
    exit(1);
  }
  _foo_ptr = (int (*)())(intptr_t)dlsym(handle, "foo");
  s = dlerror();
  if (s) {
    fprintf(stderr, "Error finding 'foo': %s!\n", s);
    exit(1);
  }
  tmp = dlsym(handle, "bar");
  fprintf(stderr, "'bar' in libTarget: %p\n", tmp);
  s = dlerror();
  if (s) {
    fprintf(stderr, "Error finding 'bar': %s!\n", s);
    exit(1);
  } else {
    fprintf(stderr, "'bar': %p\n", (void*)(intptr_t)&bar);
  }
  tmp = dlsym(handle, "var");
  fprintf(stderr, "'var' in libTarget: %p\n", tmp);
  s = dlerror();
  if (s) {
    fprintf(stderr, "Error finding 'var': %s!\n", s);
    exit(1);
  } else {
    fprintf(stderr, "'var': %p\n", (void*)&var);
  }
  fprintf(stderr, "libTarget initialized!\n");
}

void __attribute__((constructor)) _init_target() {
  if( __builtin_expect (_initialized, 1) )
    return;
  /* Avoid reentrancy */
  if (!in_init) {
    in_init=1;
    __sync_synchronize();
    pthread_once(&_init, _load_target);
    __sync_synchronize();
    in_init=0;
  }
  _initialized = 1;
}


int foo() {
  return 2 * _foo_ptr();
}
