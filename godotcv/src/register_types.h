#ifndef GODOTCV_REGISTER_TYPES_H
#define GODOTCV_REGISTER_TYPES_H

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void initialize_godot_opencv_module(ModuleInitializationLevel p_level);
void uninitialize_godot_opencv_module(ModuleInitializationLevel p_level);

#endif // GODOTCV_REGISTER_TYPES_H    