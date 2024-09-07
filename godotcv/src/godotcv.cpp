#include "godotcv.h"


using namespace godot;


Ref<Image> VideoCapture::cvMat_to_Image()
{
	cv::Mat cv_rgb;
	PackedByteArray bytes;
	Ref<Image> img;

	cv::cvtColor(frame, cv_rgb, cv::COLOR_BGR2RGB);
	int num = cv_rgb.rows * cv_rgb.cols * cv_rgb.channels();
	bytes.resize(num);
	if (cv_rgb.isContinuous())
	{
		std::memcpy(bytes.ptrw(), cv_rgb.ptr(), num);
	}
	else
	{
		for (int i = 0; i < sizeof(cv_rgb); i++)
		{
			std::memcpy(bytes.ptrw(), cv_rgb.ptr(i), num);
		}
	}
	img.instantiate();
	return img->create_from_data(cv_rgb.cols, cv_rgb.rows, false, Image::FORMAT_RGB8, bytes);
}


void VideoCapture::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_camera_id", "camera_id"), &VideoCapture::set_camera_id);
	ClassDB::bind_method(D_METHOD("get_camera_id"), &VideoCapture::get_camera_id);
	ClassDB::bind_method(D_METHOD("release"), &VideoCapture::release);
	ClassDB::bind_method(D_METHOD("read"), &VideoCapture::read);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "camera_id"), "set_camera_id", "get_camera_id");
}

VideoCapture::VideoCapture() 
{
	camera_id = 0;
	cap = new cv::VideoCapture(0);
}

VideoCapture::~VideoCapture()
{
	cap->release();
	if (!frame.empty())
		frame.release();
}

void VideoCapture::release()
{
	cap->release();
}

Ref<Image> VideoCapture::read() 
{
	if (cap->isOpened())
	{
		cap->read(frame);
		return cvMat_to_Image();
	}
	return Ref<Image>();
}

void VideoCapture::set_camera_id(int cam_id)
{
	camera_id = cam_id;
}

int VideoCapture::get_camera_id()
{
	return camera_id;
}
