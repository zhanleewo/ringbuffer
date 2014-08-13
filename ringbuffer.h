/******************************************************************************************
 * @file	ringbuffer.h
 * @author  Kurt Hildebrand
 * @version V1.0.0
 * @date	7/7/2014
 * @brief	Public structures and functions for a ring buffer. The ring buffer should have
 *			a size of a power of two.
 *
 *****************************************************************************************/
#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#define RING_BUFFER_SIZE	4

#if !(RING_BUFFER_SIZE && !(RING_BUFFER_SIZE & (RING_BUFFER_SIZE-1)))
#error RING_BUFFER_SIZE not a power of 2!
#endif

/* Ring Buffer Type Declaration -------------------------------------------------------- */
typedef unsigned ring_buffer_t;		/* Type of the data stored in the data array. */

typedef struct Ring_Buffer {
	unsigned volatile front, back;
	ring_buffer_t volatile data[RING_BUFFER_SIZE];
} Ring_Buffer;

/* Public Function Prototypes ---------------------------------------------------------- */
void ring_buffer_init(Ring_Buffer*);
void ring_buffer_clear(Ring_Buffer*);
void ring_buffer_put(Ring_Buffer*, ring_buffer_t);
ring_buffer_t ring_buffer_get(Ring_Buffer*);
unsigned ring_buffer_count(const Ring_Buffer*);
unsigned ring_buffer_full(const Ring_Buffer*);
unsigned ring_buffer_empty(const Ring_Buffer*);

#endif
/************************************** END OF FILE **************************************/
