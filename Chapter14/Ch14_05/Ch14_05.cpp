//------------------------------------------------
//               Ch14_05.cpp
//------------------------------------------------

#include "stdafx.h"
#include <iostream>
#include <stdexcept>
#include <iomanip>
#include "Ch14_05.h"
#include "ImageMatrix.h"
#include "AlignedMem.h"

using namespace std;

extern "C" const int c_NumPixelsMin = 64;
extern "C" const int c_NumPixelsMax = 16 * 1024 * 1024;

// RBG to grayscale conversion coefficients
const float c_Coef[3] {0.2126f, 0.7152f, 0.0722f};

bool CompareGsImages(const uint8_t* pb_gs1,const uint8_t* pb_gs2, int num_pixels)
{
    for (int i = 0; i < num_pixels; i++)
    {
        if (abs((int)pb_gs1[i] - (int)pb_gs2[i]) > 1)
            return false;
    }

    return true;
}

bool Avx512RgbToGsCpp(uint8_t* pb_gs, const uint8_t* const* pb_rgb, int num_pixels, const float coef[3])
{
    if (num_pixels < c_NumPixelsMin || num_pixels > c_NumPixelsMax)
        return false;
    if (num_pixels % 64 != 0)
        return false;
    if (!AlignedMem::IsAligned(pb_gs, 64))
        return false;

    const size_t align = 64;
    const uint8_t* pb_r = pb_rgb[0];
    const uint8_t* pb_g = pb_rgb[1];
    const uint8_t* pb_b = pb_rgb[2];

    if (!AlignedMem::IsAligned(pb_r, align))
        return false;
    if (!AlignedMem::IsAligned(pb_g, align))
        return false;
    if (!AlignedMem::IsAligned(pb_b, align))
        return false;

    for (int i = 0; i < num_pixels; i++)
    {
        uint8_t r = pb_r[i];
        uint8_t g = pb_g[i];
        uint8_t b = pb_b[i];

        float gs_temp = r * coef[0] + g * coef[1] + b * coef[2] + 0.5f;

        if (gs_temp < 0.0f)
            gs_temp = 0.0f;
        else if (gs_temp > 255.0f)
            gs_temp = 255.0f;

        pb_gs[i] = (uint8_t)gs_temp;
    }

    return true;
}

void Avx512RgbToGs(void)
{
    const wchar_t* fn_rgb = L"..\\Ch14_Data\\TestImage3.bmp";
    const wchar_t* fn_gs1 = L"Ch14_05_Avx512RgbToGs_TestImage3_GS1.bmp";
    const wchar_t* fn_gs2 = L"Ch14_05_Avx512RgbToGs_TestImage3_GS2.bmp";
    const wchar_t* fn_gs3 = L"Ch14_05_Avx512RgbToGs_TestImage3_GS3.bmp";

    ImageMatrix im_rgb(fn_rgb);
    int im_h = im_rgb.GetHeight();
    int im_w = im_rgb.GetWidth();
    int num_pixels = im_h * im_w;
    ImageMatrix im_r(im_h, im_w, PixelType::Gray8);
    ImageMatrix im_g(im_h, im_w, PixelType::Gray8);
    ImageMatrix im_b(im_h, im_w, PixelType::Gray8);
    RGB32* pb_rgb = im_rgb.GetPixelBuffer<RGB32>();
    uint8_t* pb_r = im_r.GetPixelBuffer<uint8_t>();
    uint8_t* pb_g = im_g.GetPixelBuffer<uint8_t>();
    uint8_t* pb_b = im_b.GetPixelBuffer<uint8_t>();
    uint8_t* pb_rgb_cp[3] {pb_r, pb_g, pb_b};

    for (int i = 0; i < num_pixels; i++)
    {
        pb_rgb_cp[0][i] = pb_rgb[i].m_R;
        pb_rgb_cp[1][i] = pb_rgb[i].m_G;
        pb_rgb_cp[2][i] = pb_rgb[i].m_B;
    }

    ImageMatrix im_gs1(im_h, im_w, PixelType::Gray8);
    ImageMatrix im_gs2(im_h, im_w, PixelType::Gray8);
    ImageMatrix im_gs3(im_h, im_w, PixelType::Gray8);
    uint8_t* pb_gs1 = im_gs1.GetPixelBuffer<uint8_t>();
    uint8_t* pb_gs2 = im_gs2.GetPixelBuffer<uint8_t>();
    uint8_t* pb_gs3 = im_gs3.GetPixelBuffer<uint8_t>();

    // Exercise conversion functions
    bool rc1 = Avx512RgbToGsCpp(pb_gs1, pb_rgb_cp, num_pixels, c_Coef);
    bool rc2 = Avx512RgbToGs_(pb_gs2, pb_rgb_cp, num_pixels, c_Coef);
    bool rc3 = Avx2RgbToGs_(pb_gs3, pb_rgb_cp, num_pixels, c_Coef);

    if (rc1 && rc2 && rc3)
    {
        im_gs1.SaveToBitmapFile(fn_gs1);
        im_gs2.SaveToBitmapFile(fn_gs2);
        im_gs2.SaveToBitmapFile(fn_gs3);

        bool c1 = CompareGsImages(pb_gs1, pb_gs2, num_pixels);
        bool c2 = CompareGsImages(pb_gs2, pb_gs3, num_pixels);

        if (c1 && c2)
            cout << "Grayscale image compare OK\n";
        else
            cout << "Grayscale image compare failed\n";
    }
    else
        cout << "Invalid return code\n";
}

int main()
{
    try
    {
        Avx512RgbToGs();
        Avx512RgbToGs_BM();
    }

    catch (runtime_error& rte)
    {
        cout << "'runtime_error' exception has occurred - " << rte.what() << '\n';
    }

    catch (...)
    {
        cout << "Unexpected exception has occurred\n";
    }

    return 0;
}
