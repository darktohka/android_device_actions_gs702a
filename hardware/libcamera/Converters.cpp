/*
 * Copyright (C) 2011 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * Contains implemenation of framebuffer conversion routines.
 */
#include "CameraHalDebug.h"

#include "Converters.h"

namespace android
{

static void _YUV420SToRGB565(const uint8_t* Y,
                             const uint8_t* U,
                             const uint8_t* V,
                             int dUV,
                             uint16_t* rgb,
                             int width,
                             int height)
{
    const uint8_t* U_pos = U;
    const uint8_t* V_pos = V;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x += 2, U += dUV, V += dUV)
        {
            const uint8_t nU = *U;
            const uint8_t nV = *V;
            *rgb = YUVToRGB565(*Y, nU, nV);
            Y++;
            rgb++;
            *rgb = YUVToRGB565(*Y, nU, nV);
            Y++;
            rgb++;
        }
        if (y & 0x1)
        {
            U_pos = U;
            V_pos = V;
        }
        else
        {
            U = U_pos;
            V = V_pos;
        }
    }
}


static void _RGB565ToYUV420S(const uint16_t* rgb,
                             uint8_t* Y,
                             uint8_t* U,
                             uint8_t* V,
                             int dUV,
                             int width,
                             int height)
{
    uint8_t y, u0, u1,u2,u3, v0,v1,v2,v3;

    for (int h = 0; h < (height>>1); h++)
    {
        for (int w = 0; (w < (width>>1)); w++,rgb+=2, Y+=2,U += dUV, V += dUV)
        {

            RGB565ToYUV(*rgb, &y, &u0, &v0);
            *Y = y;
            RGB565ToYUV(*(rgb+1), &y, &u1, &v1);
            *(Y+1) = y;
            RGB565ToYUV(*(rgb+width), &y, &u2, &v2);
            *(Y+width) = y;
            RGB565ToYUV(*(rgb+width+1), &y, &u3, &v3);
            *(Y+width+1) = y;

            *U = (u1+u1+u2+u3)>>2;
            *V = (v1+v1+v2+v3)>>2;
        }
        Y+=width;
    }
}


static void _YUV420SToRGB32(const uint8_t* Y,
                            const uint8_t* U,
                            const uint8_t* V,
                            int dUV,
                            uint32_t* rgb,
                            int width,
                            int height)
{
    const uint8_t* U_pos = U;
    const uint8_t* V_pos = V;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x += 2, U += dUV, V += dUV)
        {
            const uint8_t nU = *U;
            const uint8_t nV = *V;
            *rgb = YUVToRGB32(*Y, nU, nV);
            Y++;
            rgb++;
            *rgb = YUVToRGB32(*Y, nU, nV);
            Y++;
            rgb++;
        }
        if (y & 0x1)
        {
            U_pos = U;
            V_pos = V;
        }
        else
        {
            U = U_pos;
            V = V_pos;
        }
    }
}

void YV12ToRGB565(const void* yv12, void* rgb, int width, int height)
{
    const int pix_total = width * height;
    const uint8_t* Y = reinterpret_cast<const uint8_t*>(yv12);
    const uint8_t* V = Y + pix_total;
    const uint8_t* U = V + pix_total / 4;
    _YUV420SToRGB565(Y, U, V, 1, reinterpret_cast<uint16_t*>(rgb), width, height);
}

void YV12ToRGB32(const void* yv12, void* rgb, int width, int height)
{
    const int pix_total = width * height;
    const uint8_t* Y = reinterpret_cast<const uint8_t*>(yv12);
    const uint8_t* V = Y + pix_total;
    const uint8_t* U = V + pix_total / 4;
    _YUV420SToRGB32(Y, U, V, 1, reinterpret_cast<uint32_t*>(rgb), width, height);
}


void YU12ToRGB565(const void* yv12, void* rgb, int width, int height)
{
    const int pix_total = width * height;
    const uint8_t* Y = reinterpret_cast<const uint8_t*>(yv12);
    const uint8_t* U = Y + pix_total;
    const uint8_t* V = U + pix_total / 4;
    _YUV420SToRGB565(Y, U, V, 1, reinterpret_cast<uint16_t*>(rgb), width, height);
}


void YU12ToRGB32(const void* yu12, void* rgb, int width, int height)
{
    const int pix_total = width * height;
    const uint8_t* Y = reinterpret_cast<const uint8_t*>(yu12);
    const uint8_t* U = Y + pix_total;
    const uint8_t* V = U + pix_total / 4;
    _YUV420SToRGB32(Y, U, V, 1, reinterpret_cast<uint32_t*>(rgb), width, height);
}

/* Common converter for YUV 4:2:0 interleaved to RGB565.
 * y, u, and v point to Y,U, and V panes, where U and V values are interleaved.
 */
static void _NVXXToRGB565(const uint8_t* Y,
                          const uint8_t* U,
                          const uint8_t* V,
                          uint16_t* rgb,
                          int width,
                          int height)
{
    _YUV420SToRGB565(Y, U, V, 2, rgb, width, height);
}

/* Common converter for YUV 4:2:0 interleaved to RGB565.
 * y, u, and v point to Y,U, and V panes, where U and V values are interleaved.
 */

static void _RGB565ToNVXX(const uint16_t* rgb,
                          uint8_t* Y,
                          uint8_t* U,
                          uint8_t* V,
                          int width,
                          int height)
{
    _RGB565ToYUV420S(rgb, Y, U, V, 2, width, height);
}

/* Common converter for YUV 4:2:0 interleaved to RGB32.
 * y, u, and v point to Y,U, and V panes, where U and V values are interleaved.
 */
static void _NVXXToRGB32(const uint8_t* Y,
                         const uint8_t* U,
                         const uint8_t* V,
                         uint32_t* rgb,
                         int width,
                         int height)
{
    _YUV420SToRGB32(Y, U, V, 2, rgb, width, height);
}

void NV12ToRGB565(const void* nv12, void* rgb, int width, int height)
{
    const int pix_total = width * height;
    const uint8_t* y = reinterpret_cast<const uint8_t*>(nv12);
    _NVXXToRGB565(y, y + pix_total, y + pix_total + 1,
                  reinterpret_cast<uint16_t*>(rgb), width, height);
}

void NV12ToRGB32(const void* nv12, void* rgb, int width, int height)
{
    const int pix_total = width * height;
    const uint8_t* y = reinterpret_cast<const uint8_t*>(nv12);
    _NVXXToRGB32(y, y + pix_total, y + pix_total + 1,
                 reinterpret_cast<uint32_t*>(rgb), width, height);
}

void NV21ToRGB565(const void* nv21, void* rgb, int width, int height)
{
    const int pix_total = width * height;
    const uint8_t* y = reinterpret_cast<const uint8_t*>(nv21);
    _NVXXToRGB565(y, y + pix_total + 1, y + pix_total,
                  reinterpret_cast<uint16_t*>(rgb), width, height);
}

void NV21ToRGB32(const void* nv21, void* rgb, int width, int height)
{
    const int pix_total = width * height;
    const uint8_t* y = reinterpret_cast<const uint8_t*>(nv21);
    _NVXXToRGB32(y, y + pix_total + 1, y + pix_total,
                 reinterpret_cast<uint32_t*>(rgb), width, height);
}


void RGB565ToNV12(const void* rgb, void* nv21,  int width, int height)
{
    const int pix_total = width * height;
    uint8_t* y = reinterpret_cast<uint8_t*>(nv21);
    _RGB565ToNVXX(reinterpret_cast<const uint16_t*>(rgb), y, y + pix_total, y + pix_total + 1,
                  width, height);
}

}; /* namespace android */
