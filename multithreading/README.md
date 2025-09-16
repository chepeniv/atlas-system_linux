# `MULTITHREADING`

## Resources

## Objectives

- what is a thread ?
- what is the difference between a thread and a process ?
- what is the difference between concurrency and parallelism ?
- how to create a thread ?
- how to handle mutual execution ?
- what is a deadlock ?
- what is a race condition ?

## Requirements

- compilation will happen on `Ubuntu 20.04 LTS` using `gcc 9.4.0` with flags
`-Wall -Werror -Wextra -pedantic`
- all `c` code should be `Betty` compliant
- no more than five functions per file
- all function prototypes should be included in the `multithreading.h` header
file
- all header files should be include-guarded
- `global` variables and `static` functions and variables are _permitted_
- unless specified otherwise, use of the C standard library is _allowed_

### Data Structures

these are the data structures used throughout the project. include them in
`multithreading.h`

```c
#include <stddef.h>
#include <stdint.h>

/**
 * struct pixel_s - RGB pixel
 *
 * @r: Red component
 * @g: Green component
 * @b: Blue component
 */
typedef struct pixel_s
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} pixel_t;

/**
 * struct img_s - Image
 *
 * @w:      Image width
 * @h:      Image height
 * @pixels: Array of pixels
 */
typedef struct img_s
{
    size_t w;
    size_t h;
    pixel_t *pixels;
} img_t;

/**
 * struct kernel_s - Convolution kernel
 *
 * @size:   Size of the matrix (both width and height)
 * @matrix: Kernel matrix
 */
typedef struct kernel_s
{
    size_t size;
    float **matrix;
} kernel_t;

/**
 * struct blur_portion_s - Information needed to blur a portion of an image
 *
 * @img:      Source image
 * @img_blur: Destination image
 * @x:        X position of the portion in the image
 * @y:        Y position of the portion in the image
 * @w:        Width of the portion
 * @h:        Height of the portion
 * @kernel:   Convolution kernel to use
 */
typedef struct blur_portion_s
{
    img_t const *img;
    img_t *img_blur;
    size_t x;
    size_t y;
    size_t w;
    size_t h;
    kernel_t const *kernel;
} blur_portion_t;
```
