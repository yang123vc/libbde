/*
 * Library aes_ccm_encrypted_key type testing program
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

#include "../libbde/libbde_aes_ccm_encrypted_key.h"

#if defined( __GNUC__ )

/* Tests the libbde_aes_ccm_encrypted_key_initialize function
 * Returns 1 if successful or 0 if not
 */
int bde_test_aes_ccm_encrypted_key_initialize(
     void )
{
	libbde_aes_ccm_encrypted_key_t *aes_ccm_encrypted_key = NULL;
	libcerror_error_t *error                              = NULL;
	int result                                            = 0;

#if defined( HAVE_BDE_TEST_MEMORY )
	int number_of_malloc_fail_tests                       = 1;
	int number_of_memset_fail_tests                       = 1;
	int test_number                                       = 0;
#endif

	/* Test regular cases
	 */
	result = libbde_aes_ccm_encrypted_key_initialize(
	          &aes_ccm_encrypted_key,
	          &error );

	BDE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        BDE_TEST_ASSERT_IS_NOT_NULL(
         "aes_ccm_encrypted_key",
         aes_ccm_encrypted_key );

        BDE_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libbde_aes_ccm_encrypted_key_free(
	          &aes_ccm_encrypted_key,
	          &error );

	BDE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        BDE_TEST_ASSERT_IS_NULL(
         "aes_ccm_encrypted_key",
         aes_ccm_encrypted_key );

        BDE_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libbde_aes_ccm_encrypted_key_initialize(
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

	aes_ccm_encrypted_key = (libbde_aes_ccm_encrypted_key_t *) 0x12345678UL;

	result = libbde_aes_ccm_encrypted_key_initialize(
	          &aes_ccm_encrypted_key,
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

	aes_ccm_encrypted_key = NULL;

#if defined( HAVE_BDE_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libbde_aes_ccm_encrypted_key_initialize with malloc failing
		 */
		bde_test_malloc_attempts_before_fail = test_number;

		result = libbde_aes_ccm_encrypted_key_initialize(
		          &aes_ccm_encrypted_key,
		          &error );

		if( bde_test_malloc_attempts_before_fail != -1 )
		{
			bde_test_malloc_attempts_before_fail = -1;

			if( aes_ccm_encrypted_key != NULL )
			{
				libbde_aes_ccm_encrypted_key_free(
				 &aes_ccm_encrypted_key,
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
			 "aes_ccm_encrypted_key",
			 aes_ccm_encrypted_key );

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
		/* Test libbde_aes_ccm_encrypted_key_initialize with memset failing
		 */
		bde_test_memset_attempts_before_fail = test_number;

		result = libbde_aes_ccm_encrypted_key_initialize(
		          &aes_ccm_encrypted_key,
		          &error );

		if( bde_test_memset_attempts_before_fail != -1 )
		{
			bde_test_memset_attempts_before_fail = -1;

			if( aes_ccm_encrypted_key != NULL )
			{
				libbde_aes_ccm_encrypted_key_free(
				 &aes_ccm_encrypted_key,
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
			 "aes_ccm_encrypted_key",
			 aes_ccm_encrypted_key );

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
	if( aes_ccm_encrypted_key != NULL )
	{
		libbde_aes_ccm_encrypted_key_free(
		 &aes_ccm_encrypted_key,
		 NULL );
	}
	return( 0 );
}

/* Tests the libbde_aes_ccm_encrypted_key_free function
 * Returns 1 if successful or 0 if not
 */
int bde_test_aes_ccm_encrypted_key_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libbde_aes_ccm_encrypted_key_free(
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
	 "libbde_aes_ccm_encrypted_key_initialize",
	 bde_test_aes_ccm_encrypted_key_initialize );

	BDE_TEST_RUN(
	 "libbde_aes_ccm_encrypted_key_free",
	 bde_test_aes_ccm_encrypted_key_free );

	/* TODO: add tests for libbde_aes_ccm_encrypted_key_read */

#endif /* defined( __GNUC__ ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

