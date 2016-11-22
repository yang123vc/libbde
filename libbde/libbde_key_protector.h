/*
 * Key protector functions
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

#if !defined( _LIBBDE_INTERNAL_KEY_PROTECTOR_H )
#define _LIBBDE_INTERNAL_KEY_PROTECTOR_H

#include <common.h>
#include <types.h>

#include "libbde_extern.h"
#include "libbde_types.h"
#include "libbde_volume_master_key.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libbde_internal_key_protector libbde_internal_key_protector_t;

struct libbde_internal_key_protector
{
	/* The volume master key
	 */
	libbde_volume_master_key_t *volume_master_key;
};

int libbde_key_protector_initialize(
     libbde_key_protector_t **key_protector,
     libbde_volume_master_key_t *volume_master_key,
     libcerror_error_t **error );

LIBBDE_EXTERN \
int libbde_key_protector_free(
     libbde_key_protector_t **key_protector,
     libcerror_error_t **error );

LIBBDE_EXTERN \
int libbde_key_protector_get_identifier(
     libbde_key_protector_t *key_protector,
     uint8_t *identifier,
     size_t size,
     libcerror_error_t **error );

LIBBDE_EXTERN \
int libbde_key_protector_get_type(
     libbde_key_protector_t *key_protector,
     uint16_t *type,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBBDE_INTERNAL_KEY_PROTECTOR_H ) */

