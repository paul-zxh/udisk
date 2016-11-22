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

#ifndef _MEM_H
#define _MEM_H

void   memcpy32_r (uint32_t * dst, uint32_t * src, INT32S len);
void   memcpy32 (uint32_t * dst, uint32_t * src, INT32S len);
void   memcpy8_r (BYTE * dst, BYTE * src, INT32S len);
void   memcpy8 (BYTE * dst, BYTE * src, INT32S len);
void   memset32 (uint32_t * dst, uint32_t val, INT32S len);
void   memset8 (BYTE * dst, uint32_t val, INT32S len);
void   memcpy32 (uint32_t * dst, uint32_t * src, INT32S len);
void   memcpy32htonl (uint32_t * dst, uint32_t * src, INT32S len);
void   memcpy32htonl_r (uint32_t * dst, uint32_t * src, INT32S len);
INT32S memcmp32(uint32_t *src1, uint32_t *src2, INT32S len);
INT32S memcmp8(BYTE *src1, BYTE *src2, INT32S len);
BYTE*  memmem(const BYTE* haystack, uint32_t haystack_len, const BYTE* needle, 
              uint32_t needle_len);

uint32_t htonl(uint32_t x);

uint32_t read_uint32(BYTE *p, uint32_t offset);
uint16_t read_uint16(BYTE *p, uint32_t offset);
void   write_uint16(BYTE *p, uint32_t offset, uint16_t data);
void   write_uint32(BYTE *p, uint32_t offset, uint32_t data);
void   write_uint64(BYTE *p, uint32_t offset, INT64U data);

void*  memcpy (void* dst, const void* src, uint32_t len);
void*  memset (void* dst, INT32S val, uint32_t len);

#endif


