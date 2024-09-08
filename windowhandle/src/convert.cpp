#include "convert.h"

void convert_BGRA2RGBA_without_alpha(uint8_t * buffer, int64_t len)
{
    char temp;
    for (int64_t i = 0; i < len; i+=4)
    {
        temp = buffer[i];
        buffer[i] = buffer[i+2];
        buffer[i+2] = temp;
        buffer[i+3] = 0xFF;
    }
}

void mirrorX(uint8_t * buffer, int64_t width, int64_t height)
{
    char temp;
    width *= 4;
    for (int64_t x = 0; x < width; x++)
    {
        for (int64_t y = 0; y < height / 2; y++)
        {
            temp = buffer[x + y * width];
            buffer[x + y * width] = buffer[x + (height - y - 1) * width];
            buffer[x + (height - y - 1) * width] = temp;
        }
    }
}

void set_alpha(uint8_t * buffer, int64_t len)
{
    for (int64_t i = 3; i < len; i += 4)
    {
        buffer[i] = 0xFF;
    }
}

void crop_buffer(uint8_t * buffer, int64_t width, int64_t startX, int64_t startY, int64_t endX, int64_t endY, uint8_t * out)
{
    int64_t i = 0;
    int64_t x = startY;
    width *= 4;
    for (int64_t row = startY; row < endY; row++)
    {
        for (int64_t col = startX * 4; col < endX * 4; col++)
        {
            out[i++] = buffer[col + row * width];
        }
    }
}