/******************************************************************************************
 * @file	ringbuffer.c
 * @author  Kurt Hildebrand
 * @version V1.0.0
 * @date	7/7/2014
 * @brief	Implementation for a simple FIFO queue. No checking is performed while putting
 *			data onto the buffer. Instead, the oldest data is overwritten. Also, it is
 *			assumed only one producer and one consumer will use the ringbuffer.
 *
 *****************************************************************************************/
#include "ringbuffer.h"

/* ring_buffer_init *******************************************************************//**
 * @brief	Initializes a ring_buffer
 * @param	Ring_Buffer* const rb: the ring buffer to be operated on.
 * @return	None
 */
void ring_buffer_init(Ring_Buffer* const rb)
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
void ring_buffer_clear(Ring_Buffer* const rb)
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
void ring_buffer_put(Ring_Buffer* const rb, const ring_buffer_t var)
{
	/* Place the data a the back of the buffer. Logical AND-ing with the ring buffer size
	 * effectively MODs the index enabling wraparound. Preincrement is used to reduce the
	 * number of instructions. */
	rb->data[(++rb->back) & (RING_BUFFER_SIZE - 1)] = var;
}


/* ring_buffer_get ********************************************************************//**
 * @brief	Gets a variable from the ring buffer.
 * @param	Ring_Buffer* const rb: the ring buffer to be operated on.
 * @return	ring_buffer_t: the oldest value from the buffer.
 */
ring_buffer_t ring_buffer_get(Ring_Buffer* const rb)
{
	/* Check to see if the buffer is full and adjust the read position accordingly. */
	if(rb->back - rb->front >= RING_BUFFER_SIZE)
		rb->front = rb->back - RING_BUFFER_SIZE;

	/* Return the data from the front of the buffer. Like ring_buffer_put(), logical
	 * AND-ing with the size of the buffer enables wrap around. Preincrement reduces the
	 * number of instructions. */
	return rb->data[(++rb->front) & (RING_BUFFER_SIZE - 1)];
}


/* ring_buffer_count ******************************************************************//**
 * @brief	Returns the number of entries in the ring buffer.
 * @param	const Ring_Buffer* const rb: the ring buffer to be checked.
 * @return	unsigned: count of the entries in the ring buffer.
 */
unsigned ring_buffer_count(const Ring_Buffer* const rb)
{
	return ring_buffer_full(rb) ? RING_BUFFER_SIZE : rb->back - rb->front;
}


/* ring_buffer_full *******************************************************************//**
 * @brief	Tests a ring buffer to see if it is full or not.
 * @param	const Ring_Buffer* const rb: the ring buffer to be checked.
 * @return	int: 1 if the buffer is full. 0 if the buffer is not full.
 */
unsigned ring_buffer_full(const Ring_Buffer* const rb)
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
unsigned ring_buffer_empty(const Ring_Buffer* const rb)
{
	/* Since the indices are absolute, they can be compared directly.
	 * The condition for an empty ring buffer is if back == front. */
	return rb->back == rb->front;
}

/************************************** END OF FILE **************************************/
