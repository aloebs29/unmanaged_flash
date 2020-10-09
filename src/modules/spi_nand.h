/**
 * @file		spi_nand.h
 * @author		Andrew Loebs
 * @brief		Header file of the spi nand module
 *
 * SPI NAND flash chip driver for the Micron MT29F1G01ABAFDWB.
 *
 */

#ifndef __SPI_NAND_H
#define __SPI_NAND_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/// @brief SPI return statuses
enum {
    SPI_NAND_RET_OK = 0,
    SPI_NAND_RET_BAD_SPI = -1,
    SPI_NAND_RET_TIMEOUT = -2,
    SPI_NAND_RET_DEVICE_ID = -3,
    SPI_NAND_RET_BAD_ADDRESS = -4,
    SPI_NAND_RET_BUFFER_LEN = -5,
    SPI_NAND_RET_ECC_REFRESH = -6,
    SPI_NAND_RET_ECC_ERR = -7,
    SPI_NAND_RET_P_FAIL = -8,
    SPI_NAND_RET_E_FAIL = -9,
};

#define SPI_NAND_PAGE_SIZE       2048
#define SPI_NAND_OOB_SIZE        64
#define SPI_NAND_PAGES_PER_BLOCK 64
#define SPI_NAND_BLOCKS_PER_LUN  1024

#define SPI_NAND_MAX_PAGE_ADDRESS  (SPI_NAND_PAGES_PER_BLOCK - 1) // zero-indexed
#define SPI_NAND_MAX_BLOCK_ADDRESS (SPI_NAND_BLOCKS_PER_LUN - 1)  // zero-indexed

/// @brief Nand block address (valid range 0-1023)
typedef uint16_t block_address_t;
/// @brief Nand page address (valid range 0-63)
typedef uint8_t page_address_t;
/// @brief Nand column address (valid range 0-2175)
typedef uint16_t column_address_t;

/// @brief Initializes the spi nand driver
int spi_nand_init(void);

/// @brief Performs a read page operation
int spi_nand_page_read(block_address_t block, page_address_t page, column_address_t column,
                       uint8_t *data_out, size_t data_out_len);

/// @brief Performs a page program operation
int spi_nand_page_program(block_address_t block, page_address_t page, column_address_t column,
                          uint8_t *data_in, size_t data_in_len);

/// @brief Performs a block erase operation
int spi_nand_block_erase(block_address_t block);

/// @brief Checks if a given block is bad
/// @return SPI_NAND_RET_OK if good block, SPI_NAND_RET_BAD_BLOCK if bad, other returns if error is
/// encountered
int spi_nand_block_is_bad(block_address_t block, bool *is_bad);

/// @brief Marks a given block as bad
int spi_nand_block_mark_bad(block_address_t block);

/// @brief Checks if a given page is free
int spi_nand_page_is_free(block_address_t block, page_address_t page, bool *is_free);

#endif // __SPI_NAND_H
