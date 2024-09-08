#ifndef HANDLEWINDOW_H_
#define HANDLEWINDOW_H_
#define UNICODE

#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/image.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/rect2i.hpp>
#include <windows.h>


namespace godot {

	class HandleWindow : public Object
	{
		GDCLASS(HandleWindow, Object)

	private:
		HWND hwnd;
		BITMAPINFOHEADER bi;
		Rect2i crop;

	protected:
		static void _bind_methods();

	public:
		void create_from_classname(String);
		void create_from_title(String);
		void create_from_pid(int);

		HandleWindow();
		~HandleWindow();

		bool HWND_valid();
        Ref<Image> screenshot();

		int get_hwnd();
		void set_hwnd(int);

		Rect2i get_crop();
		void set_crop(Rect2i);
	};
}

#endif // HANDLEWINDOW_H_
