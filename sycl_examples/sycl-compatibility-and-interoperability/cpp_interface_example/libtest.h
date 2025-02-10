#ifndef LIBTEST_H
#define LIBTEST_H

#include <cstddef>

#ifdef _WIN32
//#define DllImport   __declspec( dllimport )
#define DllExport   __declspec( dllexport )
#else //only consider linux 
#define DllExport __attribute__((visibility("default")))
#endif 

//cpp compatible interface
DllExport int vector_add_cpp(const std::vector<int>& a, const std::vector<int>& b, std::vector<int>& c);

#ifdef __cplusplus
extern "C" {
#endif

DllExport int vector_add_c(int *a, int *b, int *c, unsigned long vector_len);


#ifdef __cplusplus
}
#endif

#endif // LIBTEST_H
