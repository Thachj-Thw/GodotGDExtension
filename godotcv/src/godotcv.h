#ifndef GODOTCV_H_
#define GODOTCV_H_

#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/image.hpp>
#include <godot_cpp/classes/object.hpp>
#include <opencv2/opencv.hpp>

namespace godot {

	class VideoCapture : public Object
	{
		GDCLASS(VideoCapture, Object)

	private:
		int camera_id;
		cv::VideoCapture* cap;
		cv::Mat frame;

	protected:
		static void _bind_methods();

	public:
		VideoCapture();
		~VideoCapture();
		void release();
		Ref<Image> read();
		Ref<Image> cvMat_to_Image();

		void set_camera_id(int);
		int get_camera_id(void);
	};
}

#endif // GODOTCV_H_
