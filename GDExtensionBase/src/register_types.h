#ifndef EXTENSION_NAME_REGISTER_TYPES_H
#define EXTENSION_NAME_REGISTER_TYPES_H

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void initialize_extension_name_module(ModuleInitializationLevel p_level);
void uninitialize_extension_name_module(ModuleInitializationLevel p_level);

#endif // EXTENSION_NAME_REGISTER_TYPES_H