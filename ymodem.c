/***********************************************************************************************************************
 * YMODEM implementation
 ***********************************************************************************************************************
 * By Thuffir in 2019
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the University of California, Berkeley nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE REGENTS AND CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 **********************************************************************************************************************/

#include <stdio.h>
#include "ymodem.h"

/***********************************************************************************************************************
 * YMODEM Header Context
 **********************************************************************************************************************/
typedef struct {
  char *filename;
  int size;
} YmodemHeaderContextType;

/***********************************************************************************************************************
 * Transmit minimal YMODEM Header (filename and size)
 **********************************************************************************************************************/
static void YmodemTransmitHeader(void *funcCtx, void *xmodemBuffer, int xmodemSize)
{
  YmodemHeaderContextType *ctx = funcCtx;
  snprintf(xmodemBuffer, xmodemSize, "%s%c%u", ctx->filename, 0, ctx->size);
}

/***********************************************************************************************************************
 * Do nothing (leave packet zero)
 **********************************************************************************************************************/
static void YmodemDoNothing(void *funcCtx, void *xmodemBuffer, int xmodemSize)
{
}

/***********************************************************************************************************************
 * YMODEM Transmit (Single file)
 **********************************************************************************************************************/
int YmodemTransmit(char *fileName, FetchChunkType fetchChunk, void *ctx, int size)
{
  YmodemHeaderContextType header = { fileName, size };
  int res, tmp;

  /* Transmit YMODEM header */
  tmp = XmodemTransmit(YmodemTransmitHeader, &header, 128, 0, 1);
  if( tmp < 0) {
    return tmp;
  }

  /* Transmit Data */
  res = XmodemTransmit(fetchChunk, ctx, size, 1, 0);
  if( res < 0) {
    return res;
  }

  /* Transmit End Block*/
  tmp = XmodemTransmit(YmodemDoNothing, NULL, 128, 0, 1);
  if( tmp < 0) {
    return tmp;
  }

  return res;
}
