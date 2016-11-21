/*
********************************************************************************
********************************************************************************
*
*                       Copyright (c) 2016, JETWAY, WuHan
*                              All Rights Reserved.
*
********************************************************************************
********************************************************************************
*/

#include "stdint.h"
#include "j32xx.h"
#include "mem.h"


void memcpy32 (uint32_t * dst, uint32_t * src, INT32S len)
{
    INT32S i;
    for (i = 0; i < len; ++i){
        dst[i] = (src[i]);
    }
}

void memcpy8 (BYTE * dst, BYTE * src, INT32S len)
{
    INT32S i;
    for (i = 0; i < len; ++i) {
        dst[i] = (src[i]);
    }
}

void memcpy8_r (BYTE * dst, BYTE * src, INT32S len)
{
    INT32S i = len, j = 0;
    while ((--i) >= 0) {
        dst[i] = (src[j]);
        j++;
    }
}

void memcpy32_r (uint32_t * dst, uint32_t * src, INT32S len)
{
    INT32S i = len, j = 0;
    while ((--i) >= 0) {
        dst[i] = (src[j]);
        j++;
    }
}

void memset8 (BYTE * dst, uint32_t val, INT32S len)
{
    INT32S i;
    for (i=0; i < len; ++i) {
        dst[i] = val;
    }
}

void memset32 (uint32_t * dst, uint32_t val, INT32S len)
{
    INT32S i;
    for (i = 0; i < len; ++i) {
        dst[i] = val;
    }
}

INT32S memcmp32(uint32_t *src1, uint32_t *src2, INT32S len)
{
    INT32S i;
    INT32S ret = 0;
    for(i = 0; i < len; ++i) {
        if (src1[i] != src2[i]) {
            ret = -1;
            break;
        }
    }
    return ret;
}

INT32S memcmp8(BYTE *src1, BYTE *src2, INT32S len)
{
    INT32S i;
    INT32S ret = 0;
    for(i = 0; i < len; ++i) {
        if (src1[i] != src2[i]) {
            ret = -1;
            break;
        }
    }
    return ret;
}


uint32_t htonl(uint32_t x)
{   
    return ((uint32_t)( (((uint32_t)(x) & (uint32_t)0x000000ff) << 24) | 
            (((uint32_t)(x) & (uint32_t)0x0000ff00) <<  8) | 
            (((uint32_t)(x) & (uint32_t)0x00ff0000) >>  8) | 
            (((uint32_t)(x) & (uint32_t)0xff000000) >> 24) ));
}


void memcpy32htonl (uint32_t * dst, uint32_t * src, INT32S len)
{
    INT32S i;
    for (i = 0; i < len; ++i) {
        dst[i] = htonl(src[i]);
    }

}

void memcpy32htonl_r (uint32_t * dst, uint32_t * src, INT32S len)
{
    INT32S i = len, j = 0;

    while ((--i) >= 0) {       
        dst[i] = htonl ((uint32_t)src[j]);
        j++;
    }
}


uint32_t read_uint32(BYTE  *p, uint32_t offset)
{
    uint32_t data;
    data = ((uint32_t)p[offset] << 24) | ((uint32_t)p[offset + 1] << 16) | 
            ((uint32_t)p[offset + 2] << 8) | ((uint32_t)p[offset + 3]);
    return data;
}

void write_uint64(BYTE *p, uint32_t offset, INT64U data)
{
    p[offset + 0] = (BYTE)((data & 0xff00000000000000LL) >> 56);
    p[offset + 1] = (BYTE)((data & 0x00ff000000000000LL) >> 48);
    p[offset + 2] = (BYTE)((data & 0x0000ff0000000000LL) >> 40);
    p[offset + 3] = (BYTE)((data & 0x000000ff00000000LL) >> 32); 
    p[offset + 4] = (BYTE)((data & 0x00000000ff000000LL) >> 24);
    p[offset + 5] = (BYTE)((data & 0x0000000000ff0000LL) >> 16);
    p[offset + 6] = (BYTE)((data & 0x000000000000ff00LL) >> 8);
    p[offset + 7] = (BYTE)((data & 0x00000000000000ffLL));
}

uint16_t read_uint16(BYTE  *p, uint32_t offset)
{
    uint16_t data;
    data = ((uint16_t)p[offset] << 8) |((uint16_t)p[offset + 1]);
    return data;
}

void write_uint16(BYTE *p, uint32_t offset, uint16_t data)
{
    p[offset] = (BYTE)((data & 0xff00) >> 8);
    p[offset + 1] = (BYTE)(data & 0x00ff);
}

void write_uint32(BYTE *p, uint32_t offset, uint32_t data)
{
    p[offset] = (BYTE)((data & 0xff000000) >> 24);
    p[offset + 1] = (BYTE)((data & 0x00ff0000) >> 16);
    p[offset + 2] = (BYTE)((data & 0x0000ff00) >> 8);
    p[offset + 3] = (BYTE)(data & 0x000000ff);
}

/* Copyright (C) 1991, 92, 93, 94, 96, 97, 98 Free Software Foundation, Inc.
This file is part of the GNU C Library.

  The GNU C Library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Library General Public License as
  published by the Free Software Foundation; either version 2 of the
  License, or (at your option) any later version.
  
    The GNU C Library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.
    
      You should have received a copy of the GNU Library General Public
      License along with the GNU C Library; see the file COPYING.LIB.  If not,
      write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
      Boston, MA 02111-1307, USA.  
*/
      
      
/* Return the first occurrence of NEEDLE in HAYSTACK.  */
BYTE* memmem(const BYTE* haystack, uint32_t haystack_len, const BYTE* needle,
             uint32_t  needle_len)
{
    const BYTE *begin;
    const BYTE *const last_possible = (const BYTE *) haystack + haystack_len - 
                                                     needle_len;

    /*The first occurrence of the empty string is deemed to occur at the 
    beginning of the string.*/
    if (needle_len == 0)
        return (BYTE *) haystack;
  
    for (begin = (const BYTE *) haystack; begin <= last_possible; ++begin)
        if (begin[0] == ((const BYTE *) needle)[0] && 
            !memcmp8 ((BYTE *) &begin[1], (BYTE *) (needle + 1),needle_len - 1)
            )
            return (BYTE *) begin;
    return 0;
}

void* memcpy (void* dst, const void* src, uint32_t len)
{
    uint32_t i;
    BYTE *d = dst;
    const BYTE *s = src;

    for (i = 0; i < len; ++i) {
        d[i] = (s[i]);
    }

    return dst;
}

void* memset (void* dst, INT32S val, uint32_t len)
{
    uint32_t i;
    BYTE *d = dst;
    BYTE  c = (BYTE)(val & 0x000000FF);
    for (i = 0; i < len; ++i) {
        d[i] = c;
    }
    
    return dst;
}

