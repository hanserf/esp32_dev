#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <assert.h>

#include "ring_buffer.h"
#include "user_functions.h"

#define BUFFERSIZE 256


int buffer_test(void)
{
	uint8_t * buffer  = malloc(BUFFERSIZE * sizeof(uint8_t));

	printf("\n=== C Circular Buffer Check ===\n");

	cbuf_handle_t cbuf = circular_buf_init(buffer, BUFFERSIZE);

	printf("Buffer initialized. ");
	print_buffer_status(cbuf);

	printf("\n******\nAdding %d values\n", BUFFERSIZE - 1);
	for(uint8_t i = 0; i < (BUFFERSIZE - 1); i++)
	{
		circular_buf_put(cbuf, i);
		printf("Added %u, Size now: %zu\n", i, circular_buf_size(cbuf));
	}

	print_buffer_status(cbuf);

	printf("\n******\nAdding %d values\n", BUFFERSIZE);
	for(uint8_t i = 0; i < BUFFERSIZE; i++)
	{
		circular_buf_put(cbuf, i);
		printf("Added %u, Size now: %zu\n", i, circular_buf_size(cbuf));
	}

	print_buffer_status(cbuf);

	printf("\n******\nReading back values: ");
	while(!circular_buf_empty(cbuf))
	{
		uint8_t data;
		circular_buf_get(cbuf, &data);
		printf("%u ", data);
	}
	printf("\n");

	print_buffer_status(cbuf);

	printf("\n******\nAdding %d values\n", BUFFERSIZE + 5);
	for(uint8_t i = 0; i < BUFFERSIZE + 5; i++)
	{
		circular_buf_put(cbuf, i);
		printf("Added %u, Size now: %zu\n", i, circular_buf_size(cbuf));
	}

	print_buffer_status(cbuf);

	printf("\n******\nReading back values: ");
	while(!circular_buf_empty(cbuf))
	{
		uint8_t data;
		circular_buf_get(cbuf, &data);
		printf("%u ", data);
	}
	printf("\n");

	printf("\n******\nAdding %d values using non-overwrite version\n", BUFFERSIZE + 5);
	for(uint8_t i = 0; i < BUFFERSIZE + 5; i++)
	{
		circular_buf_put2(cbuf, i);
	}

	print_buffer_status(cbuf);

	printf("\n******\nReading back values: ");
	while(!circular_buf_empty(cbuf))
	{
		uint8_t data;
		circular_buf_get(cbuf, &data);
		printf("%u ", data);
	}
	printf("\n");

	free(buffer);
	circular_buf_free(cbuf);

	return 0;
}

void print_buffer_status(cbuf_handle_t cbuf)
{
	printf("Full: %d, empty: %d, size: %zu\n",
		circular_buf_full(cbuf),
		circular_buf_empty(cbuf),
		circular_buf_size(cbuf));
}