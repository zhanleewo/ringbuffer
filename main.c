#include <stdio.h>
#include <stdlib.h>

#include "ringbuffer.h"

Ring_Buffer rb;

int main()
{
	unsigned int var;
	ring_buffer_init(&rb);

	ring_buffer_put(&rb, 10);
	ring_buffer_put(&rb, 20);
	ring_buffer_put(&rb, 30);
	ring_buffer_put(&rb, 40);
	ring_buffer_put(&rb, 50);
	ring_buffer_put(&rb, 60);

	if(ring_buffer_full(&rb))
		printf("Ring Buffer is full with %d elements!\n", ring_buffer_count(&rb));

	while(!ring_buffer_empty(&rb))
		printf("%d ", ring_buffer_get(&rb));

	ring_buffer_clear(&rb);

    return 0;
}
