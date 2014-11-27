/******************************************************************************************
 * @file	ringbuffer.c
 * @author  Kurt Hildebrand
 * @version V2.0.0
 * @date	10/13/2014
 * @brief	Implementation for a simple FIFO queue. No checking is performed while putting
 *			data onto the buffer. Instead, the oldest data is overwritten. Also, it is
 *			assumed only one producer and one consumer will use the ringbuffer. This file
 *			creates one external instance for all the inlined functions for the ringbuffer
 *			in case the compiler fails to inline.
 *
 *****************************************************************************************/
#include "ringbuffer.h"

/* External Function Definitions ------------------------------------------------------- */
extern void ring_buffer_init(Ring_Buffer*);
extern void ring_buffer_clear(Ring_Buffer*);
extern void ring_buffer_put(Ring_Buffer*, const ring_buffer_t);
extern ring_buffer_t ring_buffer_get(Ring_Buffer*);
extern ring_buffer_t ring_buffer_peek(Ring_Buffer*);
extern unsigned ring_buffer_full(const Ring_Buffer*);
extern unsigned ring_buffer_empty(const Ring_Buffer*);
extern unsigned ring_buffer_count(const Ring_Buffer*);

/************************************** END OF FILE **************************************/
