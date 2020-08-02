// ----------------------------------------------------------------------------
// -                        Open3D: www.open3d.org                            -
// ----------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2018 www.open3d.org
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

#include "open3d/core/linalg/LinalgUtils.h"
#include "open3d/core/linalg/SVD.h"

#include "open3d/core/linalg/LAPACK.h"
// https://software.intel.com/sites/products/documentation/doclib/mkl_sa/11/mkl_lapack_examples/lapacke_dgesvd_row.c.htm
namespace open3d {
namespace core {

void SVDCPU(const void* A_data,
            void* U_data,
            void* S_data,
            void* VT_data,
            void* superb_data,
            int m,
            int n,
            Dtype dtype,
            const Device& device) {
    DISPATCH_LINALG_DTYPE_TO_TEMPLATE(dtype, [&]() {
        gesvd_cpu<scalar_t>(
                LAPACK_ROW_MAJOR, 'A', 'A', m, n,
                const_cast<scalar_t*>(static_cast<const scalar_t*>(A_data)), n,
                static_cast<scalar_t*>(S_data), static_cast<scalar_t*>(U_data),
                m, static_cast<scalar_t*>(VT_data), n,
                static_cast<scalar_t*>(superb_data));
    });
}

}  // namespace core
}  // namespace open3d