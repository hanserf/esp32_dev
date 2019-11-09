#include "user_functions.h"
#include "ring_buffer.h"

void init_ringbuffer(void){
    uint8_t * buffer  = malloc(BUFFERSIZE * sizeof(uint8_t));
    cbuf_handle_t cbuf = circular_buf_init(buffer, 
        EXAMPLE_BUFFER_SIZE);
}