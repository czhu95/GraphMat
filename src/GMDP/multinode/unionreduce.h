/******************************************************************************
 * ** Copyright (c) 2016, Intel Corporation                                     **
 * ** All rights reserved.                                                      **
 * **                                                                           **
 * ** Redistribution and use in source and binary forms, with or without        **
 * ** modification, are permitted provided that the following conditions        **
 * ** are met:                                                                  **
 * ** 1. Redistributions of source code must retain the above copyright         **
 * **    notice, this list of conditions and the following disclaimer.          **
 * ** 2. Redistributions in binary form must reproduce the above copyright      **
 * **    notice, this list of conditions and the following disclaimer in the    **
 * **    documentation and/or other materials provided with the distribution.   **
 * ** 3. Neither the name of the copyright holder nor the names of its          **
 * **    contributors may be used to endorse or promote products derived        **
 * **    from this software without specific prior written permission.          **
 * **                                                                           **
 * ** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS       **
 * ** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT         **
 * ** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR     **
 * ** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT      **
 * ** HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,    **
 * ** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED  **
 * ** TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR    **
 * ** PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF    **
 * ** LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING      **
 * ** NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS        **
 * ** SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * * ******************************************************************************/
/* Michael Anderson (Intel Corp.)
 *  * ******************************************************************************/


#ifndef SRC_MULTINODE_UNIONREDUCE_H_
#define SRC_MULTINODE_UNIONREDUCE_H_

#include "GMDP/singlenode/unionreduce.h"

template <typename Ta, typename Tb, typename Tc>
void UnionReduce_tile(const SpVec<Ta> & veca,
                          const SpVec<Tb> & vecb,
                          SpVec<Tc> * vecc, int start, int end,
                          void (*op_fp)(Ta, Tb, Tc*, void*), void* vsp) {
  int global_myrank = get_global_myrank();
  for (int i = start; i < end; i++) {
    if (veca.nodeIds[i] == global_myrank) {
      union_segment(veca.segments[i], vecb.segments[i], &(vecc->segments[i]), op_fp, vsp);
    }
  }
}

template <typename Ta, typename Tb, typename Tc>
void UnionReduce(const SpVec<Ta> & v1, const SpVec<Tb> & v2, SpVec<Tc> * v3, void (*op_fp)(Ta,Tb,Tc*,void*), void* vsp=NULL)
{
  UnionReduce_tile(v1, v2, v3, 0, v1.nsegments, op_fp, vsp);
}



#endif  // SRC_MULTINODE_UNIONREDUCE_H_
