#include "extension_name.h"

using namespace godot;


void ExtensionName::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_property", "new_property"), &ExtensionName::set_property);
	ClassDB::bind_method(D_METHOD("get_property"), &ExtensionName::get_property);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "property"), "set_property", "get_property");
}

ExtensionName::ExtensionName()
{
    
}

ExtensionName::~ExtensionName()
{

}

void ExtensionName::set_property(int new_property)
{
    property = new_property;
}

int ExtensionName::get_property()
{
    return property;
}
