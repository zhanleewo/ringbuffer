/******************************************************************************************
 * @file	ringbuffer.h
 * @author  Kurt Hildebrand
 * @version V2.0.0
 * @date	10/13/2014
 * @brief	Public structures and functions for a ring buffer. For maximum speed the ring
 *			buffer's size is a power of two and the implementation of the ring buffer is
 *			inlined. The ring buffer must be a power of two to also exploit unsigned
 *			integer overflow.
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


/* ring_buffer_init *******************************************************************//**
 * @brief	Initializes a ring_buffer
 * @param	Ring_Buffer* const rb: the ring buffer to be operated on.
 * @return	None
 */
inline void ring_buffer_init(Ring_Buffer* const rb)
{
	rb->front = 0;
	rb->back = 0;
	memset((void*)rb->data, 0, sizeof(ring_buffer_t) * RING_BUFFER_SIZE);
}


/* ring_buffer_clear ******************************************************************//**
 * @brief	Zeros a ring buffer's array.
 * @param	Ring_Buffer* const rb: the ring buffer to be operated on.
 * @return	None
 */
inline void ring_buffer_clear(Ring_Buffer* const rb)
{
	memset((void*)rb->data, 0, sizeof(ring_buffer_t) * RING_BUFFER_SIZE);
	rb->front = rb->back;
}


/* ring_buffer_put ********************************************************************//**
 * @brief	Puts are variable onto the the ring buffer. Once the ring buffer becomes full
 *			old data is overwritten.
 * @param	Ring_Buffer* const rb: the ring buffer to be operated on.
 * @param	const unsigned var: the variable to put onto the buffer.
 * @return	None
 */
inline void ring_buffer_put(Ring_Buffer* const rb, const ring_buffer_t var)
{
	/* Place the data a the back of the buffer. Uses MOD to wrap around. */
	rb->data[(++rb->back) % RING_BUFFER_SIZE] = var;
}


/* ring_buffer_get ********************************************************************//**
 * @brief	Gets a variable from the ring buffer.
 * @param	Ring_Buffer* const rb: the ring buffer to be operated on.
 * @return	ring_buffer_t: the oldest value from the buffer.
 */
inline ring_buffer_t ring_buffer_get(Ring_Buffer* const rb)
{
	/* Check to see if the buffer is full and adjust the read position accordingly. */
	if(rb->back - rb->front >= RING_BUFFER_SIZE)
		rb->front = rb->back - RING_BUFFER_SIZE;

	/* Return the data from the front of the buffer. Uses MOD to wrap around. */
	return rb->data[(++rb->front) % RING_BUFFER_SIZE];
}


/* ring_buffer_peek *******************************************************************//**
 * @brief	Peeks at the next element to be popped from the ring buffer. It may change the
 *			index of the front pointer.
 * @param	const Ring_Buffer* const rb: the ring buffer to be operated on.
 * @return	ring_buffer_t: the oldest value from the buffer.
 */
inline ring_buffer_t ring_buffer_peek(Ring_Buffer* const rb)
{
	/* Check to see if the buffer is full and adjust the read position accordingly. */
	if(rb->back - rb->front >= RING_BUFFER_SIZE)
		rb->front = rb->back - RING_BUFFER_SIZE;

	/* Return the data from the front of the buffer. Uses MOD to wrap around. */
	return rb->data[(rb->front+1) % RING_BUFFER_SIZE];
}


/* ring_buffer_full *******************************************************************//**
 * @brief	Tests a ring buffer to see if it is full or not.
 * @param	const Ring_Buffer* const rb: the ring buffer to be checked.
 * @return	int: 1 if the buffer is full. 0 if the buffer is not full.
 */
inline unsigned ring_buffer_full(const Ring_Buffer* const rb)
{
	/* Since the indices are absolute, they can be compared directly.
	 * The condition for a full ring buffer is back - front == size. */
	return rb->back - rb->front >= RING_BUFFER_SIZE;
}


/* ring_buffer_empty ******************************************************************//**
 * @brief	Tests a ring buffer to see if it is empty.
 * @param	const Ring_Buffer* const rb: the ring buffer to be checked.
 * @return	int: 1 if the buffer is empty. 0 if the buffer is not empty.
 */
inline unsigned ring_buffer_empty(const Ring_Buffer* const rb)
{
	/* Since the indices are absolute, they can be compared directly.
	 * The condition for an empty ring buffer is if back == front. */
	return rb->back == rb->front;
}


/* ring_buffer_count ******************************************************************//**
 * @brief	Returns the number of entries in the ring buffer.
 * @param	const Ring_Buffer* const rb: the ring buffer to be checked.
 * @return	unsigned: count of the entries in the ring buffer.
 */
inline unsigned ring_buffer_count(const Ring_Buffer* const rb)
{
	return ring_buffer_full(rb) ? RING_BUFFER_SIZE : rb->back - rb->front;
}


#endif
/************************************** END OF FILE **************************************/
