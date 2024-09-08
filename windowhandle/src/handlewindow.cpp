#include "handlewindow.h"
#include "convert.h"

using namespace godot;


void HandleWindow::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_hwnd", "hwnd"), &HandleWindow::set_hwnd);
	ClassDB::bind_method(D_METHOD("get_hwnd"), &HandleWindow::get_hwnd);
    ClassDB::bind_method(D_METHOD("create_from_pid", "pid"), &HandleWindow::create_from_pid);
    ClassDB::bind_method(D_METHOD("create_from_classname", "classname"), &HandleWindow::create_from_classname);
    ClassDB::bind_method(D_METHOD("create_from_title", "title"), &HandleWindow::create_from_title);
	ClassDB::bind_method(D_METHOD("screenshot"), &HandleWindow::screenshot);
    ClassDB::bind_method(D_METHOD("set_crop", "is_crop"), &HandleWindow::set_crop);
    ClassDB::bind_method(D_METHOD("get_crop"), &HandleWindow::get_crop);
    ClassDB::bind_method(D_METHOD("HWND_valid"), &HandleWindow::HWND_valid);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "hwnd"), "set_hwnd", "get_hwnd");
	ADD_PROPERTY(PropertyInfo(Variant::RECT2I, "crop"), "set_crop", "get_crop");
}

HandleWindow::HandleWindow()
{
    this->hwnd = NULL;
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biPlanes = 1;
    bi.biBitCount = 32;
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 1;
    bi.biYPelsPerMeter = 2;
    bi.biClrUsed = 3;
    bi.biClrImportant = 4;

    crop = Rect2i(0, 0, 0, 0);
}

HandleWindow::~HandleWindow()
{

}

void HandleWindow::create_from_classname(String name)
{
    hwnd = FindWindow((LPCWCHAR)name.wide_string().get_data(), NULL);
}

void HandleWindow::create_from_title(String title)
{
    hwnd = FindWindow(NULL, (LPCWCHAR)title.wide_string().get_data());
}

struct param_t {
    int pid;
    HWND * hwnd;
};

BOOL CALLBACK EnumWindowsProc(HWND hWND, LPARAM lParam)
{
    DWORD lpdwProcessId;
    struct param_t * param = (struct param_t *)lParam;
    GetWindowThreadProcessId(hWND, &lpdwProcessId);
    if (IsWindowVisible(hWND) && lpdwProcessId == param->pid)
    {
        *param->hwnd = hWND;
        return FALSE;
    }
    return TRUE;
}


void HandleWindow::create_from_pid(int pid)
{
    struct param_t param = {pid, &hwnd};
    EnumWindows(EnumWindowsProc, (long long)&param);
}


Ref<Image> HandleWindow::screenshot()
{
    HDC hdcScreen;
    HDC hdcMemDC = NULL;
    PackedByteArray bytes;
    HBITMAP hbmScreen = NULL;
    DWORD dwBmpSize = 0;

    hdcScreen = GetDC(hwnd);
    hdcMemDC = CreateCompatibleDC(hdcScreen);
    if (!hdcMemDC)
    {
        UtilityFunctions::printerr("CreateCompatibleDC has failed");
        goto done;
    }

    RECT rc;
    int width, height;
    if (hwnd != NULL)
    {
        GetClientRect(hwnd, &rc);
        width = rc.right - rc.left;
        height = rc.bottom - rc.top;
    } 
    else
    {
        width = GetSystemMetrics(SM_CXSCREEN);
        height = GetSystemMetrics(SM_CYSCREEN);
    }
    hbmScreen = CreateCompatibleBitmap(hdcScreen, width, height);
    if (!hbmScreen)
    {
        UtilityFunctions::printerr("CreateCompatibleBitmap has failed");
        goto done;
    }
    SelectObject(hdcMemDC, hbmScreen);

    if (!BitBlt(hdcMemDC,
        0, 0,
        width, height,
        hdcScreen,
        0, 0,
        SRCCOPY))
    {
        UtilityFunctions::printerr("BitBlt has failed");
        goto done;
    }

    bi.biWidth = width;
    bi.biHeight = -height;
    int32_t out_width = width;
    int32_t out_height = height;
    
    dwBmpSize = width * height * 4;
    if (crop.size.x > 0 && crop.size.y > 0)
    {
        BYTE * buffer = new BYTE[dwBmpSize];
        GetDIBits(hdcScreen, hbmScreen, 0, (UINT)height, buffer, (BITMAPINFO*)&bi, DIB_RGB_COLORS);
        out_width = crop.size.x;
        out_height = crop.size.y;
        bytes.resize(out_width * out_height * 4);
        crop_buffer(buffer, width, crop.position.x, crop.position.y, crop.position.x + crop.size.x, crop.position.y + crop.size.y, bytes.ptrw());
        delete[] buffer;
    }
    else
    {
        bytes.resize(dwBmpSize);
        GetDIBits(hdcScreen, hbmScreen, 0, (UINT)height, bytes.ptrw(), (BITMAPINFO*)&bi, DIB_RGB_COLORS);
    }
done:
    DeleteObject(hbmScreen);
    DeleteObject(hdcMemDC);
    ReleaseDC(NULL, hdcScreen);

    Ref<Image> img;
    img.instantiate();
    if (bytes.size() > 0)
    {
        convert_BGRA2RGBA_without_alpha(bytes.ptrw(), bytes.size());
        return img->create_from_data(out_width, out_height, false, Image::FORMAT_RGBA8, bytes);
    }
    return img;
}


bool HandleWindow::HWND_valid()
{
    return GetDC(hwnd) != NULL;
}

void HandleWindow::set_hwnd(int new_hwnd)
{
    hwnd = (HWND)new_hwnd;
}

int HandleWindow::get_hwnd(void)
{
    return (int)hwnd;
}

Rect2i HandleWindow::get_crop()
{
    return crop;
}

void HandleWindow::set_crop(Rect2i new_is_crop)
{
    crop = new_is_crop;
}
