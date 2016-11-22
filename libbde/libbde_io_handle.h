/*
 * Input/Output (IO) handle functions
 *
 * Copyright (C) 2011-2016, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#if !defined( _LIBBDE_IO_HANDLE_H )
#define _LIBBDE_IO_HANDLE_H

#include <common.h>
#include <types.h>

#include "libbde_encryption.h"
#include "libbde_libbfio.h"
#include "libbde_libcerror.h"
#include "libbde_libfcache.h"
#include "libbde_libfdata.h"

#if defined( __cplusplus )
extern "C" {
#endif

extern const char* bde_signature;

typedef struct libbde_io_handle libbde_io_handle_t;

struct libbde_io_handle
{
	/* The format version
	 */
	int version;

	/* The bytes per sector
	 */
	uint16_t bytes_per_sector;

	/* The sectors per cluster block
	 */
	uint8_t sectors_per_cluster_block;

	/* The first metadata offset
	 */
	off64_t first_metadata_offset;

	/* The second metadata offset
	 */
	off64_t second_metadata_offset;

	/* The third metadata offset
	 */
	off64_t third_metadata_offset;

	/* The metadata (block) size
	 */
	size64_t metadata_size;

	/* The volume size
	 */
	size64_t volume_size;

	/* The encrypted volume size
	 */
	size64_t encrypted_volume_size;

	union
	{
		/* The MFT mirror cluster block number
		 * Used by Windows Vista (version 1)
		 */
		uint64_t mft_mirror_cluster_block_number;

		/* The volume header offset
		 * Used by Windows 7 (version 2)
		 */
		off64_t volume_header_offset;
	};

	/* The volume header size
	 * Used by Windows 7 (version 2)
	 */
	size64_t volume_header_size;

	/* The encryption context
	 */
	libbde_encryption_context_t *encryption_context;

	/* External provided full volume encryption key
	 */
	uint8_t full_volume_encryption_key[ 32 ];

	/* Size of the external provided full volume encryption key
	 */
	size_t full_volume_encryption_key_size;

	/* External provided tweak key
	 */
	uint8_t tweak_key[ 32 ];

	/* Size of the tweak key
	 */
	size_t tweak_key_size;

	/* Value to indicate the keys are set
	 */
	uint8_t keys_are_set;

	/* Value to indicate if abort was signalled
	 */
	int abort;
};

int libbde_io_handle_initialize(
     libbde_io_handle_t **io_handle,
     libcerror_error_t **error );

int libbde_io_handle_free(
     libbde_io_handle_t **io_handle,
     libcerror_error_t **error );

int libbde_io_handle_clear(
     libbde_io_handle_t *io_handle,
     libcerror_error_t **error );

int libbde_io_handle_read_volume_header(
     libbde_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error );

int libbde_io_handle_read_sector(
     libbde_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libfdata_vector_t *vector,
     libfcache_cache_t *cache,
     int element_index,
     int element_data_file_index,
     off64_t element_data_offset,
     size64_t element_data_size,
     uint32_t element_data_flags,
     uint8_t read_flags,
     libcerror_error_t **error );

int libbde_io_handle_read_unencrypted_volume_header(
     libbde_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBBDE_IO_HANDLE_H ) */

