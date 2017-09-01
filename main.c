#include <assert.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "lodepng.h"
#include "hilbert_curve.h"

const uint32_t bytes_per_pixel = 3;

void print_usage()
{
    puts("Usage: ./bin2img [binfile] [pngfile]");
}

void hcurve_copy(uint8_t const * from, uint8_t* to, uint degree, uint count)
{
    uint edge_len = i4_power(2, degree);
    assert(count < edge_len * edge_len);
    for (size_t i = 0; i < count; ++i)
    {
        int x,y;
        d2xy(degree, i, &x, &y);

        assert(x < edge_len);
        assert(y < edge_len);

        int pixel_idx = x + y * edge_len;
        memcpy(to + 3 * pixel_idx, from + 3 * i, 3);
    }
}

uint degree_for_width(uint width)
{
    uint exponent = 0;
    while ((1 << exponent) < width) ++exponent;
    return exponent;
}

uint filesize(const char* filename)
{
    struct stat filestat;
    if (stat(filename, &filestat)) {
        printf("Could not stat() %s\n", filename);
        abort();
    }

    return filestat.st_size;
}

int main(int argc, char *argv[])
{
    if (argc != 3) return print_usage(), 0;

    const char* binfile = argv[1];
    const char* pngfile = argv[2];

    uint num_bytes_in = filesize(binfile);
    uint num_pixels_in = (num_bytes_in + (bytes_per_pixel - 1)) / bytes_per_pixel;
    printf("Converting input file of %d pixels.\n", num_pixels_in);

    // Read the binary file
    uint8_t* bin_buffer = calloc(bytes_per_pixel, num_pixels_in);
    FILE* hbinary = fopen(binfile, "r");
    fread(bin_buffer, num_bytes_in, 1, hbinary);
    fclose(hbinary);

    // Reorder as Hilbert curve
    uint degree = degree_for_width((uint)ceil(sqrt(num_pixels_in)));
    uint width = (1 << degree);
    uint8_t* img_buffer = calloc(bytes_per_pixel, width * width);
    hcurve_copy(bin_buffer, img_buffer, degree, num_pixels_in);


    lodepng_encode24_file(pngfile, img_buffer, width, width);

    free(bin_buffer);
    free(img_buffer);
}
