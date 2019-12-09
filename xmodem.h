/***********************************************************************************************************************
 * XMODEM implementation with YMODEM support
 ***********************************************************************************************************************
 * Copyright 2001-2019 Georges Menie (www.menie.org)
 * Modified by Thuffir in 2019
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

#ifndef XMODEM_H_
#define XMODEM_H_

/** Config Section ****************************************************************************************************/
/* Define this if you have your own CCITT-CRC-16 implementation */
/* #define HAVE_CRC16 */

/* Define this if you want XMODEM-1K support, it will increase stack usage by 896 bytes */
#define XMODEM_1K

#define DLY_1S 1000
#define MAXRETRANS 25
/** End Config Section ************************************************************************************************/

int _inbyte(unsigned short t);
void _outbyte(int c);

int xmodemReceive(void (*storeChunk)(void *funcCtx, void *xmodemBuffer, int xmodemSize),
  void *ctx, int destsz, int usecrc, int mode);
int xmodemTransmit(void (*fetchChunk)(void *funcCtx, void *xmodemBuffer, int xmodemSize),
  void *ctx, int srcsz, int onek, int mode);

#endif // XMODEM_H_
