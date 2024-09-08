#ifndef EXTENSION_NAME_H_
#define EXTENSION_NAME_H_

#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/class_db.hpp>

namespace godot {

	class ExtensionName : public Object
	{
		GDCLASS(ExtensionName, Object)

	private:
		int property;

	protected:
		static void _bind_methods();

	public:
		ExtensionName();
		~ExtensionName();

		void set_property(int);
		int get_property(void);
	};
}

#endif // EXTENSION_NAME_H_
