#include <assert.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>


int main() {
  void *handle = NULL;
  const char *s;
  handle = dlopen("libMockup.so", RTLD_LAZY);
  assert(handle);

  int (*ptr_foo)() = (int (*)())(intptr_t)dlsym(handle, "foo");
  s = dlerror();
  if (s) {
    fprintf(stderr, "Error finding 'foo': %s!\n", s);
    exit(1);
  }
  void (*ptr_bar)(int) = (void (*)(int))(intptr_t)dlsym(handle, "bar");
  s = dlerror();
  if (s) {
    fprintf(stderr, "Error finding 'bar': %s!\n", s);
    exit(1);
  }
  int *var = (int *)dlsym(handle, "var");
  s = dlerror();
  if (s) {
    fprintf(stderr, "Error finding 'var': %s!\n", s);
    exit(1);
  }
  ptr_bar(5);
  assert(5 == *var);
  assert(10 == ptr_foo());
  *var = 10;
  assert(20 == ptr_foo());
  return 0;
}

