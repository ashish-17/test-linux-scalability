#ifndef __SYNCHRO_ATOMIC_H__
#define __SYNCHRO_ATOMIC_H__

#include <stdatomic.h>
#include <stdio.h>

#define compare_and_swap32(address, old_value, new_value) \
({ \
	printf("in stdAtomic 32\n"); \
	unsigned long ret_val = 0; \
	ret_val = atomic_compare_exchange_strong(address, &old_value, new_value); \
	ret_val; \
})

#define compare_and_swap64(address, old_value, new_value) \
({ \
	printf("in stdAtomic 64\n"); \
	unsigned long ret_val = 0; \
	ret_val = atomic_compare_exchange_strong(address, &old_value, new_value); \
	ret_val; \
})

#define compare_and_swap_ptr(address, old_value, new_value) compare_and_swap64(address, old_value, new_value)

#endif

