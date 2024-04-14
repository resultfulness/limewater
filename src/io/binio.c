#include <stdio.h>
#include <stdint.h>
#include "binio.h"

char* read_uint8(char* buffer, uint8_t* val) {
    *val = *buffer++;
    return buffer;
}

char* read_uint16_le(char* buffer, uint16_t* val) {
    uint8_t low, high;

    buffer = read_uint8(buffer, &high);
    buffer = read_uint8(buffer, &low);
    /* low first because little endian */
    *val = (low << 8) | high;
    return buffer;
}

char* read_uint32_le(char* buffer, uint32_t* val) {
    uint16_t low, high;

    buffer = read_uint16_le(buffer, &high);
    buffer = read_uint16_le(buffer, &low);
    /* low first because little endian */
    *val = (low << 16) | high;
    return buffer;
}

int serialize_header(struct bin_format* bf, FILE* in) {
    char b[HEADER_TOTAL_BYTES];
    char* buf = b;
    
    fread(buf, sizeof b, 1, in);
    if (feof(in) || ferror(in))
        return 1;
    buf = read_uint32_le(buf, &bf->HEADER.FID);
    buf = read_uint8(buf, &bf->HEADER.ESC);
    buf = read_uint16_le(buf, &bf->HEADER.COLS);
    buf = read_uint16_le(buf, &bf->HEADER.ROWS);
    buf = read_uint16_le(buf, &bf->HEADER.SX);
    buf = read_uint16_le(buf, &bf->HEADER.SY);
    buf = read_uint16_le(buf, &bf->HEADER.EX);
    buf = read_uint16_le(buf, &bf->HEADER.EY);
    buf = read_uint32_le(buf, &bf->HEADER.RESERVED_1);
    buf = read_uint32_le(buf, &bf->HEADER.RESERVED_2);
    buf = read_uint32_le(buf, &bf->HEADER.RESERVED_3);
    buf = read_uint32_le(buf, &bf->HEADER.CNTR);
    buf = read_uint32_le(buf, &bf->HEADER.SOFF);
    buf = read_uint8(buf, &bf->HEADER.SEP);
    buf = read_uint8(buf, &bf->HEADER.WALL);
    buf = read_uint8(buf, &bf->HEADER.PATH);

    if (bf->HEADER.COLS <= 0 ||
        bf->HEADER.ROWS <= 0 ||
        bf->HEADER.SX <= 0 ||
        bf->HEADER.SY <= 0 ||
        bf->HEADER.EX <= 0 ||
        bf->HEADER.EY <= 0 ||
        bf->HEADER.SEP >= 240)
        return 2;

    return 0;
}

int serialize_codeword(struct bin_format* bf, FILE* in) {
    char b[CODEWORD_TOTAL_BYTES];
    char* buf = b;
    
    fread(buf, sizeof b, 1, in);
    if (feof(in) || ferror(in))
        return 1;

    buf = read_uint8(buf, &bf->CODEWORD.SEP);
    buf = read_uint8(buf, &bf->CODEWORD.VAL);
    buf = read_uint8(buf, &bf->CODEWORD.CNT);

    if ((bf->CODEWORD.VAL != bf->HEADER.WALL &&
        bf->CODEWORD.VAL != bf->HEADER.PATH) ||
        bf->CODEWORD.SEP != bf->HEADER.SEP)
        return 2;

    return 0;
}
