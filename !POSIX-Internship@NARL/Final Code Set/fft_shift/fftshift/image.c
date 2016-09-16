#include <assert.h>
#include <math.h>
#include <qdbmp.h>
#include <stdlib.h>

#include "debug.h"
#include "image.h"
#include "xmalloc.h"

/*
 * A function that allocates a 2D array.
 *
 * INPUT:
 *      N: number of rows
 *      M: number of columns
 *
 * RETURN VALUES:
 *      A char** pointer to the allocated 2D array.
 *
 * SIDE EFFECTS:
 *      If memory cannot be allocated, the program is terminated with an error
 *      message printed on stderr.
 */
unsigned char** malloc_2d_chars(unsigned int N, unsigned int M)
{
    unsigned char **a = (unsigned char **)xmalloc(sizeof (char*) * N);
    unsigned int i;
    unsigned int row_size = sizeof(char) * M;

    for (i = 0; i < N; i++)
    {
        a[i] = (unsigned char *)xmalloc(row_size);
        if (a[i] == NULL)
        {
            perror("could not allocate 2D array");
            exit(MEM_ERROR);
        }
    }

    return a;
}


/*
 * Rotates an image returning an image with the same size
 * (crops pixels outside).
 */
void rotate_image(const Image *im, Image *out, double alpha, char verbose)
{
    unsigned int x, y, xx, yy;
    double angle = (M_PI * alpha) / 180.0;
    unsigned int height, width;
    height = im->height;
    width = im->width;
    out->height = im->height;
    out->width = im->width;

    if (verbose >= VERBOSE_DEBUG)
    {
        fprintf(stderr, "Rotating to %f\n", alpha);
    }

    for (x = 0; x < width; ++x) {
        for (y = 0; y < height; ++y) {
            unsigned int hwidth = width / 2;
            unsigned int hheight = height / 2;

            int xt = x - hwidth;
            int yt = y - hheight;

            double sinma = sin(-angle);
            double cosma = cos(-angle);

            xx = (unsigned int)round((cosma * xt - sinma * yt) + hwidth);
            yy = (unsigned int)round((sinma * xt + cosma * yt) + hheight);

            if (xx < width && yy < height) {
                out->data[x][y] = im->data[xx][yy];
            } else {
                out->data[x][y] = 255.0;
            }
        }
    }
}

void scale_image(const Image *im, Image *out, double factor, char verbose)
{
    unsigned int x, y, xx, yy;
    unsigned int hh, ww;
    hh = ceil(factor * im->height);
    ww = ceil(factor * im->width);
    out->height = hh;
    out->width = ww;

    if (verbose >= VERBOSE_DEBUG)
    {
        fprintf(stderr, "Scaling %f\n", factor);
    }

    for (x = 0; x < hh; ++x) {
        for (y = 0; y < ww; ++y) {
            xx = (unsigned int)(x / factor) % im->height;
            yy = (unsigned int)(y / factor) % im->width;
            out->data[x][y] = im->data[xx][yy];
        }
    }
}

Image * malloc_image(unsigned int h, unsigned int w)
{
    assert(w>0);
    assert(h>0);
    Image* img = (Image*)xmalloc(sizeof(Image));
    img->data = malloc_2d_chars(h, w);
    img->height = h;
    img->width = w;
    return img;
}

ComplexImage * malloc_complex_image(unsigned int h, unsigned w)
{
    assert(w>0);
    assert(h>0);
    ComplexImage* img = (ComplexImage*)xmalloc(sizeof(Image));
    img->data = malloc_2d_complex(h, w);
    img->height = h;
    img->width = w;
    return img;
}

COMPLEX ** malloc_2d_complex(unsigned int N, unsigned int M)
{
    COMPLEX **a = (COMPLEX **)xmalloc(sizeof (COMPLEX*) * N);
    unsigned int i;
    unsigned int row_size = sizeof(COMPLEX) * M;

    if (a == NULL) 
    {
        perror("could not allocate 2D array");
        exit(MEM_ERROR);
    }

    for (i = 0; i < N; i++)
    {
        a[i] = (COMPLEX *)xmalloc(row_size);
        if(a[i] == NULL)
        {
            perror("could not allocate 2D array");
            exit(MEM_ERROR);
        }
    }

    return a;
}

/*
 * A function that frees a 2D array.
 *
 * INPUT:
 *      N: number of rows
 *      M: number of columns
 *
 * RETURN VALUES:
 *      None.
 *
 * SIDE EFFECTS:
 *      Frees memory and the memory pointed by `a` becomes unusable.
 */
void free_2d(void **a, unsigned int N, unsigned int M)
{
    unsigned int i;
    for (i = 0; i < N; i++)
    {
        free(a[i]);
    }
    free(a);
}

/*
 * Load a BMP image from file, converting it into greyscale on-the-fly.
 *
 * INPUT:
 *      `filepath` the path to the image file.
 *
 * OUTPUT:
 *      Populates the Image struct pointed by `img`.
 *
 * RETURN VALUES:
 *      0 on success, -1 on failure.
 *
 */
char load_image_greyscale(const char * const filepath, Image **img)
{   
    UCHAR   r, g, b;
    UINT    width, height;
    UINT    x, y;
    BMP*    bmp;

    bmp = BMP_ReadFile(filepath);
    BMP_CHECK_ERROR(stderr, -1);

    height = BMP_GetHeight(bmp);
    width = BMP_GetWidth(bmp);
    assert(height > 0);
    assert(width > 0);

    *img = malloc_image(height, width);

    /* Iterate through all the image's pixels */
    for (x = 0; x < width; ++x)
    {
        for (y = 0; y < height; ++y)
        {
            /* Get pixel's RGB values.
             * NOTE: We want a standard coordinate system starting from
             * top-left corner of image, so swap the x, y arguments of the call
             * to QDBMP, which uses a coordinate system starting from the
             * bottom left corner.
             */
            BMP_GetPixelRGB(bmp, y, x, &r, &g, &b);

            /* Convert to grayscale */
            /* img->data[x][y] = 0.2989 * r + 0.5870 * g + 0.1140 * b; */
            (*img)->data[x][y] = (r + g + b) / 3.0;
        }
    }

    BMP_Free(bmp);
    BMP_CHECK_ERROR(stderr, -1);
    return 0;
}

int write_image(const char * const filepath, Image *img)
{
    unsigned int i, j;
    BMP* bmp = BMP_Create(img->width, img->height, 24);
    for(i = 0; i < img->height; ++i)
    {
        for(j = 0; j < img->width; ++j)
        {
            BMP_SetPixelRGB(bmp, j, i, img->data[i][j], img->data[i][j], img->data[i][j]);
        }
    }
    BMP_WriteFile(bmp, filepath);
    BMP_CHECK_ERROR(stderr, -1);
    return 0;
}

int write_image_complex(const char * const filepath, ComplexImage *c)
{
    unsigned int i, j, px;
    BMP* bmp = BMP_Create(c->width, c->height, 24);
    for(i = 0; i < c->height; ++i)
    {
        for(j = 0; j < c->width; ++j)
        {
            px = cabs(c->data[i][j]);
            BMP_SetPixelRGB(bmp, j, i, px, px, px);
        }
    }
    BMP_WriteFile(bmp, filepath);
    BMP_CHECK_ERROR(stderr, -1);
    return 0;
}

/*
 * Free memory allocated for an image.
 *
 * INPUT:
 *      `img` the Image struct representing the image to be freed.
 *
 * RETURN VALUES:
 *      None.
 *
 * SIDE EFFECTS:
 *      Frees the memory allocated for the image. `img.data` becomes unusable.
 */
void free_image(Image *img)
{
    if (img == NULL)
    {
        return;
    }
    unsigned int i;
    for (i = 0; i < img->height; ++i)
    {
        free(img->data[i]);
    }
    free(img->data);
    free(img);
}

Image * image_from_complex_real(CArray *c)
{
    unsigned int i, j;
    Image * img = malloc_image(c->rows, c->cols);
    for(i = 0; i < c->rows; ++i)
    {
        for(j = 0; j < c->cols; ++j)
        {
            img->data[i][j] = creal(carray_get(c, i, j));
        }
    }
    return img;
}

Image * image_from_complex_abs(CArray *c)
{
    unsigned int i, j;
    Image * img = malloc_image(c->rows, c->cols);
    for(i = 0; i < c->rows; ++i)
    {
        for(j = 0; j < c->cols; ++j)
        {
            img->data[i][j] = cabs(carray_get(c, i, j));
        }
    }
    return img;
}

void fill_complex_image_and_template(const Image *img, CArray *a, Image* t, CArray *b)
{
    unsigned i, j, offi, offj;

    assert((a->rows == b->rows) && (a->cols == b->cols));
    assert((a->rows >= img->height) && (a->cols >= img->width));

    carray_fill(a, 0.0, 0.0);
    carray_fill(b, 0.0, 0.0);

    offi = (a->rows - img->height) / 2;
    offj = (a->cols - img->width) / 2;
    for(i = 0; i < img->height; ++i)
    {
        for(j = 0; j < img->width; ++j)
        {
            creal_set(carray_get(a, offi + i, offj + j), 255.0 - img->data[i][j]);
        }
    }

    offi = (a->rows - t->height) / 2;
    offj = (a->cols - t->width) / 2;
    for(i = 0; i < t->height; ++i)
    {
        for(j = 0; j < t->width; ++j)
        {
            creal_set(carray_get(b, offi + i, offj + j), 255.0 - t->data[i][j]);
        }
    }
}

int debug_image(char * image_path, char * pattern_path, Image *img)
{
  char output_path[500] = "";
  assert(img != NULL);
  assert(img->height > 0);
  assert(img->width > 0);

  strcpy(output_path, basename(pattern_path));
  strcat(output_path, basename(image_path));
  return write_image(output_path, img);
}
