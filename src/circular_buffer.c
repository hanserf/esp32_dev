
/* Ring buffer struct*/
#include "ring_buffer.h"

/*
* Pass in a storage buffer and size 
* Returns a circular buffer handle
*/
cbuf_handle_t circular_buf_init(uint8_t* buffer, size_t size)
{
	assert(buffer && size);

	cbuf_handle_t cbuf = malloc(sizeof(circular_buf_t));
	assert(cbuf);

	cbuf->buffer = buffer;
	cbuf->max = size;
	circular_buf_reset(cbuf);

	assert(circular_buf_empty(cbuf));

	return cbuf;
}

/*
* Reset the circular buffer to empty, head == tail
*/
void circular_buf_reset(cbuf_handle_t cbuf)
{
    assert(cbuf);

    cbuf->head = 0;
    cbuf->tail = 0;
    cbuf->full = false;
}

/* 
*Free a circular buffer structure.
* Does not free data buffer; owner is responsible for that
*/
void circular_buf_free(cbuf_handle_t cbuf)
{
	assert(cbuf);
	free(cbuf);
}
/*
* Returns true if the buffer is full
*/
bool circular_buf_full(cbuf_handle_t cbuf)
{
	assert(cbuf);

    return cbuf->full;
}

/*
* Returns true if the buffer is empty
*/
bool circular_buf_empty(cbuf_handle_t cbuf)
{
	assert(cbuf);

    return (!cbuf->full && (cbuf->head == cbuf->tail));
}
/*
* Returns the maximum capacity of the buffer
*/
size_t circular_buf_capacity(cbuf_handle_t cbuf)
{
	assert(cbuf);

	return cbuf->max;
}

/*
* Returns the current number of elements in the buffer
*/
size_t circular_buf_size(cbuf_handle_t cbuf)
{
	assert(cbuf);

	size_t size = cbuf->max;

	if(!cbuf->full)
	{
		if(cbuf->head >= cbuf->tail)
		{
			size = (cbuf->head - cbuf->tail);
		}
		else
		{
			size = (cbuf->max + cbuf->head - cbuf->tail);
		}
	}

	return size;
}
/*
*Adding and Removing Data
*Adding and removing data from a circular buffer requires manipulation of the head and tail pointers. 

*Add data to the buffer by inserting new value at the current head, then increment head.
*Remove data from buffer by retrieveing value at current tail pointer and increment tail.
*If buffer full, tail pointer as well as head nedds to be incremented. 
*If inserting a value will trigger buffer full condition.
*If our buffer is already full, we advance tail. We always advance head by one. After the pointer has been advanced,
*we populate the full flag by checking whether head == tail.
*Note the use of the modulo operator (%) below. Modulo will cause the head and tail values to reset to 0 when the maximum size is reached.
*This ensures that head and tail are always valid indices of the underlying data buffer.
**/
static void advance_pointer(cbuf_handle_t cbuf)
{
	assert(cbuf);

	if(cbuf->full)
   	{
		cbuf->tail = (cbuf->tail + 1) % cbuf->max;
	}

	cbuf->head = (cbuf->head + 1) % cbuf->max;
	cbuf->full = (cbuf->head == cbuf->tail);
}

static void retreat_pointer(cbuf_handle_t cbuf)
{
	assert(cbuf);

	cbuf->full = false;
	cbuf->tail = (cbuf->tail + 1) % cbuf->max;
}

/*
* Put version 1 continues to add data if the buffer is full
* Old data is overwritten
*/
void circular_buf_put(cbuf_handle_t cbuf, uint8_t data)
{
	assert(cbuf && cbuf->buffer);

    cbuf->buffer[cbuf->head] = data;

    advance_pointer(cbuf);
}

/*
* Put Version 2 rejects new data if the buffer is full
* Returns 0 on success, -1 if buffer is full
*/
int circular_buf_put2(cbuf_handle_t cbuf, uint8_t data)
{
    int r = -1;

    assert(cbuf && cbuf->buffer);

    if(!circular_buf_full(cbuf))
    {
        cbuf->buffer[cbuf->head] = data;
        advance_pointer(cbuf);
        r = 0;
    }

    return r;
}
/*
* Retrieve a value from the buffer
* Returns 0 on success, -1 if the buffer is empty
*/
int circular_buf_get(cbuf_handle_t cbuf, uint8_t * data)
{
    assert(cbuf && data && cbuf->buffer);

    int r = -1;

    if(!circular_buf_empty(cbuf))
    {
        *data = cbuf->buffer[cbuf->tail];
        retreat_pointer(cbuf);

        r = 0;
    }

    return r;
}