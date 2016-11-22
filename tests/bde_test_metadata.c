/*
 * Library metadata type testing program
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

#include <common.h>
#include <file_stream.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "bde_test_libbde.h"
#include "bde_test_libcerror.h"
#include "bde_test_macros.h"
#include "bde_test_memory.h"
#include "bde_test_unused.h"

#include "../libbde/libbde_metadata.h"

#if defined( __GNUC__ )

/* Tests the libbde_metadata_initialize function
 * Returns 1 if successful or 0 if not
 */
int bde_test_metadata_initialize(
     void )
{
	libbde_metadata_t *metadata     = NULL;
	libcerror_error_t *error        = NULL;
	int result                      = 0;

#if defined( HAVE_BDE_TEST_MEMORY )
	int number_of_malloc_fail_tests = 1;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libbde_metadata_initialize(
	          &metadata,
	          &error );

	BDE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        BDE_TEST_ASSERT_IS_NOT_NULL(
         "metadata",
         metadata );

        BDE_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libbde_metadata_free(
	          &metadata,
	          &error );

	BDE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        BDE_TEST_ASSERT_IS_NULL(
         "metadata",
         metadata );

        BDE_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libbde_metadata_initialize(
	          NULL,
	          &error );

	BDE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        BDE_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	metadata = (libbde_metadata_t *) 0x12345678UL;

	result = libbde_metadata_initialize(
	          &metadata,
	          &error );

	BDE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        BDE_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	metadata = NULL;

#if defined( HAVE_BDE_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libbde_metadata_initialize with malloc failing
		 */
		bde_test_malloc_attempts_before_fail = test_number;

		result = libbde_metadata_initialize(
		          &metadata,
		          &error );

		if( bde_test_malloc_attempts_before_fail != -1 )
		{
			bde_test_malloc_attempts_before_fail = -1;

			if( metadata != NULL )
			{
				libbde_metadata_free(
				 &metadata,
				 NULL );
			}
		}
		else
		{
			BDE_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			BDE_TEST_ASSERT_IS_NULL(
			 "metadata",
			 metadata );

			BDE_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		/* Test libbde_metadata_initialize with memset failing
		 */
		bde_test_memset_attempts_before_fail = test_number;

		result = libbde_metadata_initialize(
		          &metadata,
		          &error );

		if( bde_test_memset_attempts_before_fail != -1 )
		{
			bde_test_memset_attempts_before_fail = -1;

			if( metadata != NULL )
			{
				libbde_metadata_free(
				 &metadata,
				 NULL );
			}
		}
		else
		{
			BDE_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			BDE_TEST_ASSERT_IS_NULL(
			 "metadata",
			 metadata );

			BDE_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( HAVE_BDE_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( metadata != NULL )
	{
		libbde_metadata_free(
		 &metadata,
		 NULL );
	}
	return( 0 );
}

/* Tests the libbde_metadata_free function
 * Returns 1 if successful or 0 if not
 */
int bde_test_metadata_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libbde_metadata_free(
	          NULL,
	          &error );

	BDE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        BDE_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libbde_metadata_get_creation_time function
 * Returns 1 if successful or 0 if not
 */
int bde_test_metadata_get_creation_time(
     void )
{
	libbde_metadata_t *metadata = NULL;
	libcerror_error_t *error    = NULL;
	uint64_t creation_time      = 0;
	int creation_time_is_set    = 0;
	int result                  = 0;

	/* Initialize test
	 */
	result = libbde_metadata_initialize(
	          &metadata,
	          &error );

	BDE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BDE_TEST_ASSERT_IS_NOT_NULL(
	 "metadata",
	 metadata );

	BDE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libbde_metadata_get_creation_time(
	          metadata,
	          &creation_time,
	          &error );

	BDE_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BDE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	creation_time_is_set = result;

	/* Test error cases
	 */
	result = libbde_metadata_get_creation_time(
	          NULL,
	          &creation_time,
	          &error );

	BDE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BDE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	if( creation_time_is_set != 0 )
	{
		result = libbde_metadata_get_creation_time(
		          metadata,
		          NULL,
		          &error );

		BDE_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		BDE_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Clean up
	 */
	result = libbde_metadata_free(
	          &metadata,
	          &error );

	BDE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BDE_TEST_ASSERT_IS_NULL(
	 "metadata",
	 metadata );

	BDE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( metadata != NULL )
	{
		libbde_metadata_free(
		 &metadata,
		 NULL );
	}
	return( 0 );
}

/* Tests the libbde_metadata_get_utf8_description_size function
 * Returns 1 if successful or 0 if not
 */
int bde_test_metadata_get_utf8_description_size(
     void )
{
	libbde_metadata_t *metadata      = NULL;
	libcerror_error_t *error         = NULL;
	size_t utf8_description_size     = 0;
	int result                       = 0;
	int utf8_description_size_is_set = 0;

	/* Initialize test
	 */
	result = libbde_metadata_initialize(
	          &metadata,
	          &error );

	BDE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BDE_TEST_ASSERT_IS_NOT_NULL(
	 "metadata",
	 metadata );

	BDE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libbde_metadata_get_utf8_description_size(
	          metadata,
	          &utf8_description_size,
	          &error );

	BDE_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BDE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf8_description_size_is_set = result;

	/* Test error cases
	 */
	result = libbde_metadata_get_utf8_description_size(
	          NULL,
	          &utf8_description_size,
	          &error );

	BDE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BDE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	if( utf8_description_size_is_set != 0 )
	{
		result = libbde_metadata_get_utf8_description_size(
		          metadata,
		          NULL,
		          &error );

		BDE_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		BDE_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Clean up
	 */
	result = libbde_metadata_free(
	          &metadata,
	          &error );

	BDE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BDE_TEST_ASSERT_IS_NULL(
	 "metadata",
	 metadata );

	BDE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( metadata != NULL )
	{
		libbde_metadata_free(
		 &metadata,
		 NULL );
	}
	return( 0 );
}

/* Tests the libbde_metadata_get_utf8_description function
 * Returns 1 if successful or 0 if not
 */
int bde_test_metadata_get_utf8_description(
     void )
{
	uint8_t utf8_description[ 512 ];

	libbde_metadata_t *metadata = NULL;
	libcerror_error_t *error    = NULL;
	int result                  = 0;
	int utf8_description_is_set = 0;

	/* Initialize test
	 */
	result = libbde_metadata_initialize(
	          &metadata,
	          &error );

	BDE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BDE_TEST_ASSERT_IS_NOT_NULL(
	 "metadata",
	 metadata );

	BDE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libbde_metadata_get_utf8_description(
	          metadata,
	          utf8_description,
	          512,
	          &error );

	BDE_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BDE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf8_description_is_set = result;

	/* Test error cases
	 */
	result = libbde_metadata_get_utf8_description(
	          NULL,
	          utf8_description,
	          512,
	          &error );

	BDE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BDE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	if( utf8_description_is_set != 0 )
	{
		result = libbde_metadata_get_utf8_description(
		          metadata,
		          NULL,
		          512,
		          &error );

		BDE_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

	        BDE_TEST_ASSERT_IS_NOT_NULL(
	         "error",
	         error );

		libcerror_error_free(
		 &error );

		result = libbde_metadata_get_utf8_description(
		          metadata,
		          utf8_description,
		          0,
		          &error );

		BDE_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

	        BDE_TEST_ASSERT_IS_NOT_NULL(
	         "error",
	         error );

		libcerror_error_free(
		 &error );

		result = libbde_metadata_get_utf8_description(
		          metadata,
		          utf8_description,
		          (size_t) SSIZE_MAX + 1,
		          &error );

		BDE_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

	        BDE_TEST_ASSERT_IS_NOT_NULL(
	         "error",
	         error );

		libcerror_error_free(
		 &error );
	}
	/* Clean up
	 */
	result = libbde_metadata_free(
	          &metadata,
	          &error );

	BDE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BDE_TEST_ASSERT_IS_NULL(
	 "metadata",
	 metadata );

	BDE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( metadata != NULL )
	{
		libbde_metadata_free(
		 &metadata,
		 NULL );
	}
	return( 0 );
}

/* Tests the libbde_metadata_get_utf16_description_size function
 * Returns 1 if successful or 0 if not
 */
int bde_test_metadata_get_utf16_description_size(
     void )
{
	libbde_metadata_t *metadata       = NULL;
	libcerror_error_t *error          = NULL;
	size_t utf16_description_size     = 0;
	int result                        = 0;
	int utf16_description_size_is_set = 0;

	/* Initialize test
	 */
	result = libbde_metadata_initialize(
	          &metadata,
	          &error );

	BDE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BDE_TEST_ASSERT_IS_NOT_NULL(
	 "metadata",
	 metadata );

	BDE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libbde_metadata_get_utf16_description_size(
	          metadata,
	          &utf16_description_size,
	          &error );

	BDE_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BDE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf16_description_size_is_set = result;

	/* Test error cases
	 */
	result = libbde_metadata_get_utf16_description_size(
	          NULL,
	          &utf16_description_size,
	          &error );

	BDE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BDE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	if( utf16_description_size_is_set != 0 )
	{
		result = libbde_metadata_get_utf16_description_size(
		          metadata,
		          NULL,
		          &error );

		BDE_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		BDE_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Clean up
	 */
	result = libbde_metadata_free(
	          &metadata,
	          &error );

	BDE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BDE_TEST_ASSERT_IS_NULL(
	 "metadata",
	 metadata );

	BDE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( metadata != NULL )
	{
		libbde_metadata_free(
		 &metadata,
		 NULL );
	}
	return( 0 );
}

/* Tests the libbde_metadata_get_utf16_description function
 * Returns 1 if successful or 0 if not
 */
int bde_test_metadata_get_utf16_description(
     void )
{
	uint16_t utf16_description[ 512 ];

	libbde_metadata_t *metadata  = NULL;
	libcerror_error_t *error     = NULL;
	int result                   = 0;
	int utf16_description_is_set = 0;

	/* Initialize test
	 */
	result = libbde_metadata_initialize(
	          &metadata,
	          &error );

	BDE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BDE_TEST_ASSERT_IS_NOT_NULL(
	 "metadata",
	 metadata );

	BDE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libbde_metadata_get_utf16_description(
	          metadata,
	          utf16_description,
	          512,
	          &error );

	BDE_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BDE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf16_description_is_set = result;

	/* Test error cases
	 */
	result = libbde_metadata_get_utf16_description(
	          NULL,
	          utf16_description,
	          512,
	          &error );

	BDE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BDE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	if( utf16_description_is_set != 0 )
	{
		result = libbde_metadata_get_utf16_description(
		          metadata,
		          NULL,
		          512,
		          &error );

		BDE_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

	        BDE_TEST_ASSERT_IS_NOT_NULL(
	         "error",
	         error );

		libcerror_error_free(
		 &error );

		result = libbde_metadata_get_utf16_description(
		          metadata,
		          utf16_description,
		          0,
		          &error );

		BDE_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

	        BDE_TEST_ASSERT_IS_NOT_NULL(
	         "error",
	         error );

		libcerror_error_free(
		 &error );

		result = libbde_metadata_get_utf16_description(
		          metadata,
		          utf16_description,
		          (size_t) SSIZE_MAX + 1,
		          &error );

		BDE_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

	        BDE_TEST_ASSERT_IS_NOT_NULL(
	         "error",
	         error );

		libcerror_error_free(
		 &error );
	}
	/* Clean up
	 */
	result = libbde_metadata_free(
	          &metadata,
	          &error );

	BDE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BDE_TEST_ASSERT_IS_NULL(
	 "metadata",
	 metadata );

	BDE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( metadata != NULL )
	{
		libbde_metadata_free(
		 &metadata,
		 NULL );
	}
	return( 0 );
}

/* Tests the libbde_metadata_get_number_of_volume_master_keys function
 * Returns 1 if successful or 0 if not
 */
int bde_test_metadata_get_number_of_volume_master_keys(
     void )
{
	libbde_metadata_t *metadata             = NULL;
	libcerror_error_t *error                = NULL;
	int number_of_volume_master_keys        = 0;
	int number_of_volume_master_keys_is_set = 0;
	int result                              = 0;

	/* Initialize test
	 */
	result = libbde_metadata_initialize(
	          &metadata,
	          &error );

	BDE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BDE_TEST_ASSERT_IS_NOT_NULL(
	 "metadata",
	 metadata );

	BDE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libbde_metadata_get_number_of_volume_master_keys(
	          metadata,
	          &number_of_volume_master_keys,
	          &error );

	BDE_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BDE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	number_of_volume_master_keys_is_set = result;

	/* Test error cases
	 */
	result = libbde_metadata_get_number_of_volume_master_keys(
	          NULL,
	          &number_of_volume_master_keys,
	          &error );

	BDE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BDE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	if( number_of_volume_master_keys_is_set != 0 )
	{
		result = libbde_metadata_get_number_of_volume_master_keys(
		          metadata,
		          NULL,
		          &error );

		BDE_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		BDE_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Clean up
	 */
	result = libbde_metadata_free(
	          &metadata,
	          &error );

	BDE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BDE_TEST_ASSERT_IS_NULL(
	 "metadata",
	 metadata );

	BDE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( metadata != NULL )
	{
		libbde_metadata_free(
		 &metadata,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) */

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc BDE_TEST_ATTRIBUTE_UNUSED,
     wchar_t * const argv[] BDE_TEST_ATTRIBUTE_UNUSED )
#else
int main(
     int argc BDE_TEST_ATTRIBUTE_UNUSED,
     char * const argv[] BDE_TEST_ATTRIBUTE_UNUSED )
#endif
{
	BDE_TEST_UNREFERENCED_PARAMETER( argc )
	BDE_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ )

	BDE_TEST_RUN(
	 "libbde_metadata_initialize",
	 bde_test_metadata_initialize );

	BDE_TEST_RUN(
	 "libbde_metadata_free",
	 bde_test_metadata_free );

	/* TODO: add tests for libbde_metadata_read_block */

	/* TODO: add tests for libbde_metadata_read_header */

	/* TODO: add tests for libbde_metadata_read_entries */

	/* TODO: add tests for libbde_metadata_read_volume_master_key */

	/* TODO: add tests for libbde_metadata_read_full_volume_encryption_key */

	/* TODO: add tests for libbde_metadata_get_volume_identifier */

	BDE_TEST_RUN(
	 "libbde_metadata_get_creation_time",
	 bde_test_metadata_get_creation_time );

	BDE_TEST_RUN(
	 "libbde_metadata_get_utf8_description_size",
	 bde_test_metadata_get_utf8_description_size );

	BDE_TEST_RUN(
	 "libbde_metadata_get_utf8_description",
	 bde_test_metadata_get_utf8_description );

	BDE_TEST_RUN(
	 "libbde_metadata_get_utf16_description_size",
	 bde_test_metadata_get_utf16_description_size );

	BDE_TEST_RUN(
	 "libbde_metadata_get_utf16_description",
	 bde_test_metadata_get_utf16_description );

	BDE_TEST_RUN(
	 "libbde_metadata_get_number_of_volume_master_keys",
	 bde_test_metadata_get_number_of_volume_master_keys );

	/* TODO: add tests for libbde_metadata_get_volume_master_key_by_index */

#endif /* defined( __GNUC__ ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

