#include "ring_buffer.h"
#include "main.h"
#include "user_functions.h"

void init_ringbuffer(void){
    uint8_t * buffer  = malloc(EXAMPLE_BUFFER_SIZE * sizeof(uint8_t));
    cbuf_handle_t cbuf = circular_buf_init(buffer, 
        EXAMPLE_BUFFER_SIZE);
}