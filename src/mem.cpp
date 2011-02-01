#include "Galois/Runtime/mm/mem.h"

#include <linux/mman.h>
#include <sys/mman.h>

using namespace GaloisRuntime;
using namespace MM;

static const int _PROT = PROT_READ | PROT_WRITE;
static const int _MAP_BASE = MAP_ANONYMOUS | MAP_PRIVATE;
static const int _MAP_POP  = MAP_POPULATE | _MAP_BASE;
static const int _MAP_HUGE = MAP_HUGETLB | _MAP_POP;

void* mmapWrapper::_alloc() {
  //First try huge
  void* ptr = mmap(0, AllocSize, _PROT, _MAP_HUGE, -1, 0);
  //Then try populate
  if (!ptr || ptr == MAP_FAILED)
    ptr = mmap(0, AllocSize, _PROT, _MAP_POP, -1, 0);
  //Then try normal
  if (!ptr || ptr == MAP_FAILED)
    ptr = mmap(0, AllocSize, _PROT, _MAP_BASE, -1, 0);

  return ptr;
}

void mmapWrapper::_free(void* ptr) {
  munmap(ptr, AllocSize);
}

template<typename RealBase>
SelfLockFreeListHeap<RealBase> SystemBaseAllocator<RealBase>::Source;

//Dummy function to force initialize SystemBaseAllocator<mmapWrapper>::Source
static void dummy() __attribute__((used));
static void dummy() {
  SystemBaseAlloc B;
  B.allocate(0);
}
