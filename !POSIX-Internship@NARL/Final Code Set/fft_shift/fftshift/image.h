/*
 * Image loading routines.
 */
#ifndef IMAGE_H
#define IMAGE_H
#include <assert.h>
#include <string.h>
#include <libgen.h>
#include "complex_num.h"
#include "carray.h"

#define PADDING 0.0
#define MEM_ERROR 11

typedef struct {
    unsigned char ** data;
    unsigned int height;
    unsigned int width;
} Image;

typedef struct {
    COMPLEX ** data;
    unsigned int height;
    unsigned int width;
} ComplexImage;

void fill_complex_image_and_template(const Image *img, CArray *a, Image* t, CArray *b);
unsigned char** malloc_2d_chars(unsigned int N, unsigned int M);
COMPLEX ** malloc_2d_complex(unsigned int N, unsigned int M);
void rotate_image(const Image *im, Image *out, double alpha, char verbose);
void scale_image(const Image *im, Image *out, double factor, char verbose);
Image * malloc_image(unsigned int h, unsigned int w);
ComplexImage * malloc_complex_image(unsigned int h, unsigned w);
void free_2d(void **a, unsigned int N, unsigned int M);
char load_image_greyscale(const char * const filepath, Image **img);
int write_image(const char * const filepath, Image *img);
int write_image_complex(const char * const filepath, ComplexImage *c);
void free_image(Image *img);
Image * image_from_complex_real(CArray *c);
Image * image_from_complex_abs(CArray *c);
int debug_image(char * image_path, char * pattern_path, Image *img);
#endif
