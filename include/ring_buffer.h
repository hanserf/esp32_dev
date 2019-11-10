#pragma once

#include "stdint.h"
#include "stddef.h"
#include "stdbool.h"

#define BUFFERSIZE = 256

typedef struct circular_buf_t {
	uint8_t * buffer;
	size_t head;
	size_t tail;
	size_t max; //of the buffer
	bool full;
}circular_buf_t;

/* Handle type, to interact with this API*/
typedef circular_buf_t* cbuf_handle_t;


extern cbuf_handle_t circular_buf_init(uint8_t* buffer, size_t size);
extern void circular_buf_free(cbuf_handle_t cbuf);
extern void circular_buf_reset(cbuf_handle_t cbuf);
extern void circular_buf_put(cbuf_handle_t cbuf, uint8_t data);
extern int circular_buf_put2(cbuf_handle_t cbuf, uint8_t data);
extern int circular_buf_get(cbuf_handle_t cbuf, uint8_t * data);
extern bool circular_buf_empty(cbuf_handle_t cbuf);
extern bool circular_buf_full(cbuf_handle_t cbuf);
extern size_t circular_buf_capacity(cbuf_handle_t cbuf);
extern size_t circular_buf_size(cbuf_handle_t cbuf);

