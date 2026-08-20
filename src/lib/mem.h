#ifndef MEM_H
#define MEM_H

/* ================== *
 * REDEFINABLE MACROS *
 * ================== */

/*
 * The user should define an even memory alignment to use because the library
 * assumes it's 4 otherwise.
 */

#ifndef MEM_ALIGNMENT
/* Memory alignment used by mem.h. */
#define MEM_ALIGNMENT   4
#warning "[mem.h]: User did not define the macro: MEM_ALIGNMENT."
#endif /* MEM_ALIGNMENT */

#if (MEM_ALIGNMENT % 2)
#error "[mem.h]: User did not define an even MEM_ALIGNMENT value."
#endif /* Check for abnormal MEM_ALIGNMENT value. */

#ifndef NULL
/* A nothing pointer. */
#define NULL    (void *)0
#endif /* NULL */

#ifndef MEM_SIZE_T
/* Relies on the architecture's biggest supported data type instead. */
#define MEM_SIZE_T  unsigned long long
#endif /* MEM_SIZE_T*/

/* =============== *
 * PROVIDED MACROS *
 * =============== */

/*
 * Because kilobytes (KB) and megabytes (MB) are too ambiguous, rely on IEC's
 * binary units, which are also naturally aligned to both 64-bite and 32-bit
 * architectures.
 */

/* A binary friendly version of kilobyte. */
#define KIBIBYTE(n) ((n) * 1024)

/* A binary friendly version of megabyte. */
#define MEBIBYTE(n) ((n) * KIBIBYTE(1024))

/* The memory byte size mem.h operates on. */
#define MEM_POOLSIZE    MEBIBYTE(4)

/* ========= *
 * FUNCTIONS *
 * ========= */

/* Returns a pointer to a free memory. */
void *malloc(unsigned long n);

/* Frees a pointer to a memory allocated by mem.h. */
void free(void *ptr);

#endif /* MEM_H */