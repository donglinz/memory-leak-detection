/*
* LeakDetector.cpp
*
*/

#include <iostream>
#include <cstring>

#define __NEW_OVERLOAD_IMPLEMENTATION__
#include "LeakDetector.hpp"

typedef struct _MemoryList {
  struct _MemoryList *next, *prev;
  size_t size;        // size of allocated memory
  bool isArray;       // is a array?
  char *file;         // file location
  unsigned int line;  // position in file
} _MemoryList;

static unsigned long _memory_allocated = 0;
static _MemoryList _root {
  &_root, &_root, 0, false, NULL, 0
};

unsigned int _leak_detector::callCount = 0;

void *AllocateMemory(size_t _size, bool _array, char *_file, int _line) {
  // re-calculate the size of memory
  size_t newSize = sizeof(_MemoryList) + _size;

  // we can not use operator 'new' cause of override
  _MemoryList *newElem = (_MemoryList *)malloc(newSize);

  newElem->next = _root.next;
  newElem->prev = &_root;
  newElem->size = _size;
  newElem->isArray = _array;
  newElem->file = NULL;

  // save file path if exist
  if(_file) {
    newElem->file = (char *)malloc(strlen(_file) + 1);
    strcpy(newElem->file, _file);
  }

  // save the line number
  newElem->line = _line;

  // update the memory list
  _root.next->prev = newElem;
  _root.next = newElem;

  // calculate the size of memory allocated
  _memory_allocated += _size;

  // return the position of memory
  return (char *)newElem + sizeof(_MemoryList);
}

void DeleteMemory(void *_ptr, bool _array) {
  _MemoryList *currentElem = (_MemoryList *)((char *)_ptr - sizeof(_MemoryList));

  if(currentElem->isArray != _array) return;

  // update the memory list
  currentElem->prev->next = currentElem->next;
  currentElem->next->prev = currentElem->prev;
  _memory_allocated -= currentElem->size;

  if(currentElem->file) free(currentElem->file);
  free(currentElem);
}

void * operator new (size_t _size) {
  return AllocateMemory(_size, false, NULL, 0);
}

void * operator new[] (size_t _size) {
  return AllocateMemory(_size, true, NULL, 0);
}

void * operator new (size_t _size, char *_file, unsigned int _line) {
  return AllocateMemory(_size, false, _file, _line);
}

void * operator new[] (size_t _size, char * _file, unsigned int _line) {
  return AllocateMemory(_size, true, _file, _line);
}

void operator delete (void *_ptr) noexcept {
  DeleteMemory(_ptr, false);
}

void operator delete[] (void *_ptr) noexcept {
  DeleteMemory(_ptr, true);
}

unsigned int _leak_detector::LeakDetector() noexcept {
  unsigned int count = 0;

  // foreach object in list, if there is a memory leak, none of
  // them point to themselves
  _MemoryList *ptr = _root.next;
  while(ptr && ptr != &_root) {
    if(ptr->isArray)
      std::cout << "leak[] ";
    else std::cout << "leak   ";
    std::cout << ptr << " size " << ptr->size;

    if(ptr->file)
      std::cout << " Located in " << ptr->file << " line " << ptr->line;
    else
      std::cout << "(Cannot find position)";
    std::cout << std::endl;
    ++count;
    ptr = ptr->next;
  }

  if(count)
    std::cout << "Total " << count << " leaks, size " << _memory_allocated << "byte." << std::endl;
  return count;
}

#define new new(__FILE__, __LINE__)
