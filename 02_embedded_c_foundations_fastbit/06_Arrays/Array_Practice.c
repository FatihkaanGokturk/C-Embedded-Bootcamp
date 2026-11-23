/**
 * @file      Array_Practice.c
 * @author    Fatih Kaan GÖKTÜRK
 * @brief     Embedded C array operations, const-correctness, and O(1) ping-pong pointer swapping.
 *
 * @details   Demonstrates defensive array traversal, read-only Flash vs. mutable RAM buffer handling,
 *            O(N) element-by-element array swapping, and O(1) double-pointer (uint16_t **) swapping
 *            used in DMA ping-pong double buffering.
 */

#include <stdint.h>
#include <stdio.h>
#include <stddef.h>

/* Simulated Flash-stored reference limits (Read-Only!) */
static const uint16_t MAX_ALLOWED_LIMITS[5] = {3000, 3000, 3000, 3000, 3000};

/**
 * @brief  Prints all elements of a 16-bit unsigned integer buffer on a single line.
 *
 * @param[in] label  Null-terminated string label printed before the buffer contents.
 * @param[in] buf    Pointer to the read-only or mutable uint16_t array to print.
 * @param[in] len    Number of elements in the array.
 */
void print_buffer(const char *label, const uint16_t *buf, size_t len) {
    if (buf == NULL || len == 0 || label == NULL) {
        return;
    }
    printf("%s: ", label);
    for (size_t i = 0; i < len; i++) {
        printf("%u ", buf[i]);
    }
    printf("\n");
}

/**
 * @brief  Scans an array and returns its maximum 16-bit unsigned value.
 *
 * @param[in] buf  Pointer to the uint16_t array to scan (not modified).
 * @param[in] len  Number of elements in the array.
 * @return    Highest value found in the array, or 0 if buf is NULL or len is 0.
 */
uint16_t find_max(const uint16_t *buf, size_t len) {
    if (buf == NULL || len == 0) {
        return 0;
    }
    uint16_t max_val = buf[0];
    for (size_t i = 1; i < len; i++) {
        if (buf[i] > max_val) {
            max_val = buf[i];
        }
    }

    return max_val;
}

/**
 * @brief  Swaps the contents of two equal-sized arrays element-by-element in O(N) time.
 *
 * @param[in,out] arr_a  Pointer to the first mutable uint16_t array.
 * @param[in,out] arr_b  Pointer to the second mutable uint16_t array.
 * @param[in]     len    Number of elements in each array.
 */
void swap_array_contents(uint16_t *arr_a, uint16_t *arr_b, size_t len) {
    if (arr_a == NULL || len == 0 || arr_b == NULL) {
        return;
    }
    for (size_t i = 0; i < len; i++) {
        uint16_t temp = arr_a[i];
        arr_a[i] = arr_b[i];
        arr_b[i] = temp;
    }
}

/**
 * @brief  Swaps two buffer pointers in O(1) time without copying array data (Ping-Pong pattern).
 *
 * @param[in,out] ptr_a  Double pointer (address of the caller's first uint16_t * pointer).
 * @param[in,out] ptr_b  Double pointer (address of the caller's second uint16_t * pointer).
 */
void swap_buffer_pointers(uint16_t **ptr_a, uint16_t **ptr_b) {
    if (ptr_a == NULL || ptr_b == NULL) {
        return;
    }
    uint16_t *temp = *ptr_a;
    *ptr_a = *ptr_b;
    *ptr_b = temp;
}

int main(void) {
    uint16_t sensor_buf_a[5] = {1020, 1050, 1100, 1080, 1040};
    uint16_t sensor_buf_b[5] = {2400, 2550, 2600, 2490, 2510};

    /* Compute element count safely at compile time */
    size_t len = sizeof(sensor_buf_a) / sizeof(sensor_buf_a[0]);

    /* 1. Test const-correctness by passing a Flash-like const array */
    print_buffer("Limits  ", MAX_ALLOWED_LIMITS, len);
    print_buffer("Buffer A", sensor_buf_a, len);
    print_buffer("Buffer B", sensor_buf_b, len);

    /* 2. Test read-only scan */
    printf("Max in Buffer A: %u\n", find_max(sensor_buf_a, len));
    printf("Max in Buffer B: %u\n\n", find_max(sensor_buf_b, len));

    /* 3. Test O(N) element-by-element swap */
    printf("--- Swapping Array Contents ---\n");
    swap_array_contents(sensor_buf_a, sensor_buf_b, len);
    print_buffer("Buffer A", sensor_buf_a, len);
    print_buffer("Buffer B", sensor_buf_b, len);

    /* 4. Test O(1) double-pointer (Ping-Pong) swap */
    uint16_t *active_rx   = sensor_buf_a;
    uint16_t *process_buf = sensor_buf_b;

    printf("\n--- Swapping Buffer Pointers (**) ---\n");
    swap_buffer_pointers(&active_rx, &process_buf);
    print_buffer("Active RX  ", active_rx, len);
    print_buffer("Process Buf", process_buf, len);

    return 0;
}