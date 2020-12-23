#ifndef __BUFFERLIB_H__
#define __BUFFERLIB_H__
#ifdef __cplusplus
/* clang-format off */
extern "C"
{
/* clang-format on */
#endif /* Start C linkage */

#include <stdlib.h>

typedef void *buffer_instance_handle;
typedef struct
{
    buffer_instance_handle instance;
    char *(*read_next)(buffer_instance_handle);
    char *(*write_next)(buffer_instance_handle);
    void (*init)(buffer_instance_handle);
    void (*deinit)(buffer_instance_handle);
} buffer_handle;


buffer_handle bufferlib_ringbuf(size_t size);

#ifdef __cplusplus
/* clang-format off */
}
/* clang-format on */
#endif /* End C linkage */
#endif /* __BUFFERLIB_H__ */
