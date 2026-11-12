#ifndef CWARP_H
#define CWARP_H

/* 
 * Backward jumps:
 * Declares a dummy guard variable at the checkpoint.
 * Calling go_back() before checkpoint() causes a compile-time error.
 */
#define checkpoint(name) \
    const int cwarp_cp_guard_##name = 0; \
    cwarp_cp_##name:;

#define go_back(name) \
    do { \
        (void)cwarp_cp_guard_##name; \
        goto cwarp_cp_##name; \
    } while (0)

/* 
 * Forward jumps:
 * skip_to() jumps forward to skip_point().
 * Placing skip_point() before skip_to() causes a redefinition compile error.
 */
#define skip_to(name) \
    do { \
        enum { cwarp_sp_order_check_##name = 0 }; \
        goto cwarp_sp_##name; \
    } while (0)

#define skip_point(name) \
    cwarp_sp_##name:; \
    const int cwarp_sp_guard_##name = 0; \
    (void)cwarp_sp_guard_##name

#endif
