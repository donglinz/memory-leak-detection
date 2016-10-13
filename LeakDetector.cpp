/*
* LeakDetector.cpp
*
*/

#ifndef __LEAK_DETECTOR__
#define __LEAK_DETECTOR__



void * operator new (size_t _size, char *_file, unsigned int _line);
void * operator new[] (size_t _size, char * _file, unsigned int _line);

#ifndef __NEW_OVERLOAD_IMPLEMENTATION_
#define __NEW_OVERLOAD_IMPLEMENTATION_
#define new new(__FILE__, __LINE__)

#endif // __NEW_OVERLOAD_IMPLEMENTATION_


class _leak_detector {
public:
  static unsigned int callCount;
  _leak_detector() noexcept {
    ++callCount;
  }
  ~_leak_detector() noexcept {

  }
};



#endif // __LEAK_DETECTOR__
