/*
* Simd Library (http://ermig1979.github.io/Simd).
*
* Copyright (c) 2011-2023 Yermalayeu Ihar.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/
#include "Simd/SimdMemory.h"
#include "Simd/SimdStore.h"
#include "Simd/SimdResizer.h"
#include "Simd/SimdResizerCommon.h"
#include "Simd/SimdUpdate.h"

namespace Simd
{
#ifdef SIMD_NEON_ENABLE    
    namespace Neon
    {
        void * ResizerInit(size_t srcX, size_t srcY, size_t dstX, size_t dstY, size_t channels, SimdResizeChannelType type, SimdResizeMethodType method)
        {
            ResParam param(srcX, srcY, dstX, dstY, channels, type, method, sizeof(float32x4_t));
            if (param.IsNearest())
                return new Base::ResizerNearest(param);
            else if (param.IsByteBilinear() && dstX >= A)
                return new ResizerByteBilinear(param);
            else if (param.IsByteArea1x1())
                return new ResizerByteArea1x1(param);
            else if (param.IsShortBilinear() && channels == 1)
                return new ResizerShortBilinear(param);
            else if (param.IsFloatBilinear())
                return new ResizerFloatBilinear(param);
            else
                return Base::ResizerInit(srcX, srcY, dstX, dstY, channels, type, method);
        }
    }
#endif
}
