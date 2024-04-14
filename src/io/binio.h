#ifndef _BINIO_H
#define _BINIO_H

#include <stdio.h>
#include <stdint.h>

/* sizes of the binary format sections */
#define HEADER_TOTAL_BYTES 40
#define CODEWORD_TOTAL_BYTES 3
#define SOL_HEADER_TOTAL_BYTES 5
#define SOL_STEP_TOTAL_BYTES 2;

/* binary format according to specs */
struct bin_format {
    struct {
        uint32_t FID;
        uint8_t ESC;
        uint16_t COLS;
        uint16_t ROWS;
        uint16_t SX;
        uint16_t SY;
        uint16_t EX;
        uint16_t EY;
        uint32_t RESERVED_1;
        uint32_t RESERVED_2;
        uint32_t RESERVED_3;
        uint32_t CNTR;
        uint32_t SOFF;
        uint8_t SEP;
        uint8_t WALL;
        uint8_t PATH;
    } HEADER;
    struct {
        uint8_t SEP;
        uint8_t VAL;
        uint8_t CNT;
    } CODEWORD;
    struct {
        uint32_t SID;
        uint8_t STEPS;
    } SOL_HEADER;
    struct {
        uint8_t DIR;
        uint8_t CNT;
    } SOL_STEP;
};

/**
 * @brief reads a byte of data from a data buffer and advances the buffer by
 * amount read
 *
 * @param buffer pointer to the first character to read
 * @param val variable where the read data will be stored
 * @return advanced buffer pointer
 */
char* read_uint8(char* buffer, uint8_t* val);

/**
 * @brief reads 2 bytes of little endian data from a data buffer and advances
 * the buffer by amount read
 *
 * @param buffer pointer to the first character to read
 * @param val variable where the read data will be stored
 * @return advanced buffer pointer
 */
char* read_uint16_le(char* buffer, uint16_t* val);

/**
 * @brief reads 4 bytes of little endian data from a data buffer and advances
 * the buffer by amount read
 *
 * @param buffer pointer to the first character to read
 * @parazzm val variable where the read data will be stored
 * @return advanced buffer pointer
 */
char* read_uint32_le(char* buffer, uint32_t* val);

/**
 * @brief given a binary file at the beginning of the header section, stores the
 * header metadata in the binary format structure; advances the file past the
 * header section
 *
 * @param bf binary file format
 * @param in binary input file at the beginning of the header section
 * @return 1 if there was an error reading the file, 2 if input invalid, 0 if ok
 */
int serialize_header(struct bin_format* bf, FILE* in);

/**
 * @brief given a file at the start of a codeword, stores that codeword inside
 * of the binary format codeword field, advancing the binary input file past
 * the codeword
 *
 * @param bf binary file format
 * @param in binary input file at the start of a codeword
 * @return 1 if there was an error reading the file, 2 if input invalid, 0 if ok
 */
int serialize_codeword(struct bin_format* bf, FILE* in);

#endif
