/*
 * Library read testing program
 *
 * Copyright (c) 2011-2014, Joachim Metz <joachim.metz@gmail.com>
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

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include <stdio.h>

#include "bde_test_libbde.h"
#include "bde_test_libcerror.h"
#include "bde_test_libcnotify.h"
#include "bde_test_libcstring.h"
#include "bde_test_libcsystem.h"
#include "bde_test_unused.h"

/* Define to make bde_test_read generate verbose output
#define BDE_TEST_READ_VERBOSE
 */

#define BDE_TEST_READ_BUFFER_SIZE	4096

/* Tests libbde_volume_seek_offset
 * Returns 1 if successful, 0 if not or -1 on error
 */
int bde_test_seek_offset(
     libbde_volume_t *volume,
     off64_t input_offset,
     int input_whence,
     off64_t expected_offset )
{
	libbde_error_t *error = NULL;
	off64_t result_offset   = 0;
	int result              = 0;

	if( volume == NULL )
	{
		return( -1 );
	}
	result_offset = libbde_volume_seek_offset(
	                 volume,
	                 input_offset,
	                 input_whence,
	                 &error );

	if( expected_offset != result_offset )
	{
		fprintf(
		 stderr,
		 "Unexpected result offset: %" PRIi64 "\n",
		 result_offset );
	}
	else
	{
		result = 1;
	}
	if( error != NULL )
	{
		if( result != 1 )
		{
			libbde_error_backtrace_fprint(
			 error,
			 stderr );
		}
		libbde_error_free(
		 &error );
	}
	return( result );
}

/* Tests libbde_volume_read_buffer
 * Returns 1 if successful, 0 if not or -1 on error
 */
int bde_test_read_buffer(
     libbde_volume_t *volume,
     size64_t input_size,
     size64_t expected_size )
{
	uint8_t buffer[ BDE_TEST_READ_BUFFER_SIZE ];

	libbde_error_t *error = NULL;
	size64_t remaining_size = 0;
	size64_t result_size    = 0;
	size_t read_size        = 0;
	ssize_t read_count      = 0;
	int result              = 0;

	if( volume == NULL )
	{
		return( -1 );
	}
	remaining_size = input_size;

	while( remaining_size > 0 )
	{
		read_size = BDE_TEST_READ_BUFFER_SIZE;

		if( remaining_size < (size64_t) read_size )
		{
			read_size = (size_t) remaining_size;
		}
		read_count = libbde_volume_read_buffer(
			      volume,
			      buffer,
			      read_size,
			      &error );

		if( read_count < 0 )
		{
			break;
		}
		remaining_size -= (size64_t) read_count;
		result_size    += (size64_t) read_count;

		if( read_count != (ssize_t) read_size )
		{
			break;
		}
	}
	if( expected_size != result_size )
	{
		fprintf(
		 stderr,
		 "Unexpected read count: %" PRIu64 "\n",
		 result_size );
	}
	else
	{
		result = 1;
	}
	if( error != NULL )
	{
		if( result != 1 )
		{
			libbde_error_backtrace_fprint(
			 error,
			 stderr );
		}
		libbde_error_free(
		 &error );
	}
	return( result );
}

/* Tests libbde_volume_read_buffer_at_offset
 * Returns 1 if successful, 0 if not or -1 on error
 */
int bde_test_read_buffer_at_offset(
     libbde_volume_t *volume,
     off64_t input_offset,
     size64_t input_size,
     off64_t expected_offset,
     size64_t expected_size )
{
	uint8_t buffer[ BDE_TEST_READ_BUFFER_SIZE ];

	libbde_error_t *error = NULL;
	off64_t result_offset   = 0;
	size64_t remaining_size = 0;
	size64_t result_size    = 0;
	size_t read_size        = 0;
	ssize_t read_count      = 0;
	int result              = 0;

	if( volume == NULL )
	{
		return( -1 );
	}
	remaining_size = input_size;

	fprintf(
	 stdout,
	 "Testing reading buffer at offset: %" PRIi64 " with size: %" PRIu64 "\t",
	 input_offset,
	 input_size );

	while( remaining_size > 0 )
	{
		read_size = BDE_TEST_READ_BUFFER_SIZE;

		if( remaining_size < (size64_t) read_size )
		{
			read_size = (size_t) remaining_size;
		}
		read_count = libbde_volume_read_buffer_at_offset(
			      volume,
			      buffer,
			      read_size,
			      input_offset,
			      &error );

		if( read_count < 0 )
		{
			break;
		}
		input_offset   += (size64_t) read_count;
		remaining_size -= (size64_t) read_count;
		result_size    += (size64_t) read_count;

		if( read_count != (ssize_t) read_size )
		{
			break;
		}
	}
	if( libbde_volume_get_offset(
	     volume,
	     &result_offset,
	     &error ) != 1 )
	{
		result = -1;
	}
	if( expected_offset != result_offset )
	{
		fprintf(
		 stderr,
		 "Unexpected offset: %" PRIi64 "\n",
		 result_offset );
	}
	else if( expected_size != result_size )
	{
		fprintf(
		 stderr,
		 "Unexpected read count: %" PRIu64 "\n",
		 result_size );
	}
	else
	{
		result = 1;
	}
	if( result == 1 )
	{
		fprintf(
		 stdout,
		 "(PASS)" );
	}
	else
	{
		fprintf(
		 stdout,
		 "(FAIL)" );
	}
	fprintf(
	 stdout,
	 "\n" );

	if( error != NULL )
	{
		if( result != 1 )
		{
			libbde_error_backtrace_fprint(
			 error,
			 stderr );
		}
		libbde_error_free(
		 &error );
	}
	return( result );
}

/* Tests reading data at a specific offset
 * Returns 1 if successful, 0 if not or -1 on error
 */
int bde_test_seek_offset_and_read_buffer(
     libbde_volume_t *volume,
     off64_t input_offset,
     int input_whence,
     size64_t input_size,
     off64_t expected_offset,
     size64_t expected_size )
{
	const char *whence_string = NULL;
	int result                = 0;

	if( volume == NULL )
	{
		return( -1 );
	}
	if( input_whence == SEEK_CUR )
	{
		whence_string = "SEEK_CUR";
	}
	else if( input_whence == SEEK_END )
	{
		whence_string = "SEEK_END";
	}
	else if( input_whence == SEEK_SET )
	{
		whence_string = "SEEK_SET";
	}
	else
	{
		whence_string = "UNKNOWN";
	}
	fprintf(
	 stdout,
	 "Testing reading buffer at offset: %" PRIi64 " with whence: %s and size: %" PRIu64 "\t",
	 input_offset,
	 whence_string,
	 input_size );

	result = bde_test_seek_offset(
	          volume,
	          input_offset,
	          input_whence,
	          expected_offset );

	if( result == 1 )
	{
		if( input_offset >= 0 )
		{
			result = bde_test_read_buffer(
				  volume,
				  input_size,
				  expected_size );
		}
	}
	if( result == 1 )
	{
		fprintf(
		 stdout,
		 "(PASS)" );
	}
	else
	{
		fprintf(
		 stdout,
		 "(FAIL)" );
	}
	fprintf(
	 stdout,
	 "\n" );

	return( result );
}

/* Tests reading data from a volume
 * Returns 1 if successful, 0 if not or -1 on error
 */
int bde_test_read_from_volume(
     libbde_volume_t *volume,
     size64_t volume_size )
{
	int result = 0;

	if( volume == NULL )
	{
		return( -1 );
	}
	if( volume_size > (size64_t) INT64_MAX )
	{
		fprintf(
		 stderr,
		 "Volume size exceeds maximum.\n" );

		return( -1 );
	}
	/* Case 0: test full read
	 */

	/* Test: offset: 0 size: <volume_size>
	 * Expected result: offset: 0 size: <volume_size>
	 */
	result = bde_test_seek_offset_and_read_buffer(
	          volume,
	          0,
	          SEEK_SET,
	          volume_size,
	          0,
	          volume_size );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset and read buffer.\n" );

		return( result );
	}
	/* Test: offset: 0 size: <volume_size>
	 * Expected result: offset: 0 size: <volume_size>
	 */
	result = bde_test_seek_offset_and_read_buffer(
	          volume,
	          0,
	          SEEK_SET,
	          volume_size,
	          0,
	          volume_size );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset and read buffer.\n" );

		return( result );
	}

	/* Case 1: test buffer at offset read
	 */

	/* Test: offset: <volume_size / 7> size: <volume_size / 2>
	 * Expected result: offset: <volume_size / 7> size: <volume_size / 2>
	 */
	result = bde_test_seek_offset_and_read_buffer(
	          volume,
	          (off64_t) ( volume_size / 7 ),
	          SEEK_SET,
	          volume_size / 2,
	          (off64_t) ( volume_size / 7 ),
	          volume_size / 2 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset and read buffer.\n" );

		return( result );
	}
	/* Test: offset: <volume_size / 7> size: <volume_size / 2>
	 * Expected result: offset: <volume_size / 7> size: <volume_size / 2>
	 */
	result = bde_test_seek_offset_and_read_buffer(
	          volume,
	          (off64_t) ( volume_size / 7 ),
	          SEEK_SET,
	          volume_size / 2,
	          (off64_t) ( volume_size / 7 ),
	          volume_size / 2 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset and read buffer.\n" );

		return( result );
	}

	/* Case 2: test read beyond volume size
	 */

	if( volume_size < 1024 )
	{
		/* Test: offset: <volume_size - 1024> size: 4096
		 * Expected result: offset: -1 size: <undetermined>
		 */
		result = bde_test_seek_offset_and_read_buffer(
		          volume,
		          (off64_t) ( volume_size - 1024 ),
		          SEEK_SET,
		          4096,
		          -1,
		          (size64_t) -1 );

		if( result != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test seek offset and read buffer.\n" );

			return( result );
		}
		/* Test: offset: <volume_size - 1024> size: 4096
		 * Expected result: offset: -1 size: <undetermined>
		 */
		result = bde_test_seek_offset_and_read_buffer(
		          volume,
		          (off64_t) ( volume_size - 1024 ),
		          SEEK_SET,
		          4096,
		          -1,
		          (size64_t) -1 );

		if( result != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test seek offset and read buffer.\n" );

			return( result );
		}
	}
	else
	{
		/* Test: offset: <volume_size - 1024> size: 4096
		 * Expected result: offset: <volume_size - 1024> size: 1024
		 */
		result = bde_test_seek_offset_and_read_buffer(
		          volume,
		          (off64_t) ( volume_size - 1024 ),
		          SEEK_SET,
		          4096,
		          (off64_t) ( volume_size - 1024 ),
		          1024 );

		if( result != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test read.\n" );

			return( result );
		}
		/* Test: offset: <volume_size - 1024> size: 4096
		 * Expected result: offset: <volume_size - 1024> size: 1024
		 */
		result = bde_test_seek_offset_and_read_buffer(
		          volume,
		          (off64_t) ( volume_size - 1024 ),
		          SEEK_SET,
		          4096,
		          (off64_t) ( volume_size - 1024 ),
		          1024 );

		if( result != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test seek offset and read buffer.\n" );

			return( result );
		}
	}
	/* Case 3: test buffer at offset read
	 */

	/* Test: offset: <volume_size / 7> size: <volume_size / 2>
	 * Expected result: offset: < ( volume_size / 7 ) + ( volume_size / 2 ) > size: <volume_size / 2>
	 */
	result = bde_test_read_buffer_at_offset(
	          volume,
	          (off64_t) ( volume_size / 7 ),
	          volume_size / 2,
	          (off64_t) ( volume_size / 7 ) + ( volume_size / 2 ),
	          volume_size / 2 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test read buffer at offset.\n" );

		return( result );
	}
	/* Test: offset: <volume_size / 7> size: <volume_size / 2>
	 * Expected result: offset: < ( volume_size / 7 ) + ( volume_size / 2 ) > size: <volume_size / 2>
	 */
	result = bde_test_read_buffer_at_offset(
	          volume,
	          (off64_t) ( volume_size / 7 ),
	          volume_size / 2,
	          (off64_t) ( volume_size / 7 ) + ( volume_size / 2 ),
	          volume_size / 2 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test read buffer at offset.\n" );

		return( result );
	}
	return( 1 );
}

/* The main program
 */
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
	libbde_volume_t *volume                                 = NULL;
	libcstring_system_character_t *option_password          = NULL;
	libcstring_system_character_t *option_recovery_password = NULL;
	libcstring_system_character_t *source                   = NULL;
	libcerror_error_t *error                                = NULL;
	libcstring_system_integer_t option                      = 0;
	size64_t volume_size                                    = 0;
	size_t string_length                                    = 0;

	while( ( option = libcsystem_getopt(
	                   argc,
	                   argv,
	                   _LIBCSTRING_SYSTEM_STRING( "p:r:" ) ) ) != (libcstring_system_integer_t) -1 )
	{
		switch( option )
		{
			case (libcstring_system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_LIBCSTRING_SYSTEM ".\n",
				 argv[ optind - 1 ] );

				return( EXIT_FAILURE );

			case (libcstring_system_integer_t) 'p':
				option_password = optarg;

				break;

			case (libcstring_system_integer_t) 'r':
				option_recovery_password = optarg;

				break;
		}
	}
	if( optind == argc )
	{
		fprintf(
		 stderr,
		 "Missing source file or device.\n" );

		return( EXIT_FAILURE );
	}
	source = argv[ optind ];

#if defined( HAVE_DEBUG_OUTPUT ) && defined( BDE_TEST_OPEN_CLOSE_VERBOSE )
	libbde_notify_set_verbose(
	 1 );
	libbde_notify_set_stream(
	 stderr,
	 NULL );
#endif
	/* Initialization
	 */
	if( libbde_volume_initialize(
	     &volume,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to create volume.\n" );

		goto on_error;
	}
	if( option_password != NULL )
	{
		string_length = libcstring_system_string_length(
		                 option_password );

#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		if( libbde_volume_set_utf16_password(
		     volume,
		     (uint16_t *) option_password,
		     string_length,
		     &error ) != 1 )
#else
		if( libbde_volume_set_utf8_password(
		     volume,
		     (uint8_t *) option_password,
		     string_length,
		     &error ) != 1 )
#endif
		{
			fprintf(
			 stderr,
			 "Unable to set password." );

			goto on_error;
		}
	}
	if( option_recovery_password != NULL )
	{
		string_length = libcstring_system_string_length(
		                 option_recovery_password );

#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		if( libbde_volume_set_utf16_recovery_password(
		     volume,
		     (uint16_t *) option_recovery_password,
		     string_length,
		     &error ) != 1 )
#else
		if( libbde_volume_set_utf8_recovery_password(
		     volume,
		     (uint8_t *) option_recovery_password,
		     string_length,
		     &error ) != 1 )
#endif
		{
			fprintf(
			 stderr,
			 "Unable to set recovery password." );

			goto on_error;
		}
	}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	if( libbde_volume_open_wide(
	     volume,
	     source,
	     LIBBDE_OPEN_READ,
	     &error ) != 1 )
#else
	if( libbde_volume_open(
	     volume,
	     source,
	     LIBBDE_OPEN_READ,
	     &error ) != 1 )
#endif
	{
		fprintf(
		 stderr,
		 "Unable to open file.\n" );

		goto on_error;
	}
	if( libbde_volume_get_size(
	     volume,
	     &volume_size,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to retrieve volume size.\n" );

		goto on_error;
	}
	fprintf(
	 stdout,
	 "Volume size: %" PRIu64 " bytes\n",
	 volume_size );

	if( bde_test_read_from_volume(
	     volume,
	     volume_size ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to read from volume.\n" );

		goto on_error;
	}
	/* Clean up
	 */
	if( libbde_volume_close(
	     volume,
	     &error ) != 0 )
	{
		fprintf(
		 stderr,
		 "Unable to close volume.\n" );

		goto on_error;
	}
	if( libbde_volume_free(
	     &volume,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to free volume.\n" );

		goto on_error;
	}
	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libbde_error_backtrace_fprint(
		 error,
		 stderr );
		libbde_error_free(
		 &error );
	}
	if( volume != NULL )
	{
		libbde_volume_close(
		 volume,
		 NULL );
		libbde_volume_free(
		 &volume,
		 NULL );
	}
	return( EXIT_FAILURE );
}
