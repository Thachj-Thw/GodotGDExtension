#ifndef CONVERT_H_
#define CONVERT_H_

#include <godot_cpp/godot.hpp>
#include <godot_cpp/variant/packed_byte_array.hpp>
using namespace godot;

void convert_BGRA2RGBA_without_alpha(uint8_t * buffer, int64_t len);
void mirrorX(uint8_t * buffer, int64_t width, int64_t height);
void mirrorY(uint8_t * buffer, int64_t width, int64_t height);
void set_alpha(uint8_t * buffer, int64_t len);
void crop_buffer(uint8_t * buffer, int64_t width, int64_t startX, int64_t startY, int64_t endX, int64_t endY, uint8_t * out);

#endif //CONVERT_H_