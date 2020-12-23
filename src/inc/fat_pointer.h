#ifndef __FAT_POINTER_H__
#define __FAT_POINTER_H__
#ifdef __cplusplus
/* clang-format off */
extern "C"
{
/* clang-format on */
#endif /* Start C linkage */

#include <stdlib.h>

struct fat_pointer
{
    char * start;
    size_t size;
};


#ifdef __cplusplus
/* clang-format off */
}
/* clang-format on */
#endif /* End C linkage */
#endif /* __FAT_POINTER_H__ */
