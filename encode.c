#include <stdio.h>
#include <string.h>
#include "encode.h"
#include "types.h"
#include "common.h"

/* Function Definitions */
Status do_encoding(EncodeInfo *encInfo)
{
		if( open_files(encInfo) == e_success)
		{
				printf("INFO: Opening required files\n");
				printf("INFO: Opened beautiful.bmp\n");
				printf("INfo: Opened secret.txt\n");
				printf("INFO: Opened Stego_img.bmp\n");
				printf("INFO: Done\n");
		}
		else
		{
				printf("ERROR: File Opening Failure");
				return e_failure;
		}
		if( check_capacity(encInfo) == e_success)
		{
				printf("INFO: Checking for beautiul.bmp capacity to handle secret.txt\n");
				printf("INFO: Done. Found OK\n");
		}
		else
		{
				printf("check capacity failure\n");
				return e_failure;
		}
		if( copy_bmp_header( encInfo -> fptr_src_image, encInfo -> fptr_stego_image) == e_success)
		{
				printf("INFO: Coping Image Header\n");
				printf("INFO: Done\n");
		}
		else
		{
				printf("ERROR: Coping Image Header Unsuccessfull\n");
				return e_failure;
		}
		if( encode_magic_string(MAGIC_STRING, encInfo) == e_success)
		{
			printf("INFO: Encoding Magic String Signature \n");
			printf("INFO: Done\n");
		}
		else
		{
			printf("ERROR: Encoding Magic String Signature Unsuccessfull\n");
			return e_failure;
		}
		if(	encode_secret_file_extn_size( strlen( encInfo -> extn_secret_file), encInfo) == e_success)
		{
				printf("INFO: Encoding secret.txt File Extention Size\n");
				printf("INFO: Done\n");
		}
		else
		{
				printf("ERROR: Encoding secret.txt File Extention Size Unsuccessfull\n");
				return e_failure;
		}
		if( encode_secret_file_extn(encInfo -> extn_secret_file, encInfo) == e_success)
		{
				printf("INFO: Encoding secret.txt File Extention \n");
				printf("INFO: Done\n");
		}
		else
		{
				printf("ERROR: Encoding secret.txt FIle Extention Unseccessfull\n");
				return e_failure;
		}
		if( encode_secret_file_size( encInfo -> size_secret_file, encInfo) == e_success)
		{
				printf("INFO: Encoding secret.txt File Size\n");
				printf("INFO: Done\n");
		}
		else
		{
				printf("ERROR: Encoding secret.txt File Size Unsuccessful\n");
				return e_failure;
		}
		if( encode_secret_file_data(encInfo) == e_success)
		{
				printf("INFO: Encodeing secret.txt File Data\n");
				printf("INFO: Done\n");
		}
		else
		{
				printf("ERROR: Encoding secret.txt File Data Unsuccessfull\n");
				return e_failure;
		}
		if( copy_remaining_img_data(encInfo -> fptr_src_image, encInfo -> fptr_stego_image) == e_success)
		{
				printf("INFO: Coping Left Over Data\n");
				printf("INFO: Done\n");
		}
		else
		{
				printf("ERROR: Coping Left Over Data Unsuccessfull\n");
				return e_failure;
		}		
		return e_success;
}
Status read_and_validate_encode_args(char *argv[], EncodeInfo *encInfo)
{
		if(!(strcmp( strstr( argv[2], ".") , ".bmp")))
		{
				encInfo -> src_image_fname = argv[2];
		}
		else
		{
				return e_failure;
		}
		if(argv[3] != NULL)
		{
			encInfo -> secret_fname = argv[3];
	        strcpy(encInfo -> extn_secret_file, strstr(argv[3], "."));
		}
		else
		{
				return e_failure;
		}
		if(argv[4] != NULL)
		{
				encInfo -> stego_image_fname = argv[4];
		}
		else
		{
				encInfo -> stego_image_fname = "default steged.bmp";
				printf("INFO: Output File not mentioned. Creating steged_img.bmp as default\n");
		}
		return e_success;
}

Status check_capacity(EncodeInfo *encInfo)
{
		encInfo -> image_capacity = get_image_size_for_bmp( encInfo -> fptr_src_image);
		encInfo -> size_secret_file = get_file_size( encInfo -> fptr_secret);
		if(encInfo -> image_capacity  > ( strlen(MAGIC_STRING) + ( sizeof(int) + sizeof(int) + sizeof(int)) * 8 + ( encInfo -> size_secret_file) * 8 ))
		{
				return e_success;
		}
		else
		{
				return e_failure;
		}
}

Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image)
{
		rewind(fptr_src_image);
		char str[54];
		fread(str, sizeof(char), 54, fptr_src_image);
		fwrite(str, sizeof(char), 54, fptr_dest_image);

		return e_success;
}
/* Get image size
 * Input: Image Imagefile ptr
 * Output: width * height * bytes per pixel (3 in our case)
 * Description: In BMP Image, width is stored in offset 18,
 * and height after that. size is 4 bytes
 */
uint get_image_size_for_bmp(FILE *fptr_image)
{
    uint width, height;
    // Seek to 18th byte
    fseek(fptr_image, 18, SEEK_SET);

    // Read the width (an int)
    fread(&width, sizeof(int), 1, fptr_image);
   
	// printf("width = %u\n", width);

    // Read the height (an int)
    fread(&height, sizeof(int), 1, fptr_image);
   
	// printf("height = %u\n", height);

    // Return image capacity
    return width * height * 3;
}

uint get_file_size(FILE *ptr)
{
		rewind(ptr);
		fseek(ptr, 0, SEEK_END);
		return ftell(ptr);
}

/* 
 * Get File pointers for i/p and o/p files
 * Inputs: Src Image file, Secret file and
 * Stego Image file
 * Output: FILE pointer for above files
 * Return Value: e_success or e_failure, on file errors
 */
Status open_files(EncodeInfo *encInfo)
{
    // Src Image file
    encInfo -> fptr_src_image = fopen(encInfo -> src_image_fname, "r");
    // Do Error handling
    if (encInfo -> fptr_src_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo -> src_image_fname);

    	return e_failure;
    }

    // Secret file
    encInfo -> fptr_secret = fopen(encInfo -> secret_fname, "r");
    // Do Error handling
    if (encInfo -> fptr_secret == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo -> secret_fname);

    	return e_failure;
    }

    // Stego Image file
    encInfo -> fptr_stego_image = fopen(encInfo -> stego_image_fname, "w");
    // Do Error handling
    if (encInfo -> fptr_stego_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo -> stego_image_fname);

    	return e_failure;
    }

    // No failure return e_success
    return e_success;
}

Status encode_byte_to_lsb(char data, char *image_buffer)
{
		for(int i=0;i<8;i++)
		{
				image_buffer[i] = (image_buffer[i] & 0xfe ) | ((data & (1 << ( 7 - i ))) >> ( 7 - i));
		}
	// 	printf("c == %c \n",data);
}

Status encode_data_to_image(char *data, int size, FILE *fptr_src_image, FILE *fptr_stego_image, EncodeInfo *encInfo)
{
		for(int i=0; i<size; i++)
		{
				fread(encInfo -> image_data, 8, sizeof(char), fptr_src_image);
				encode_byte_to_lsb(data[i],encInfo -> image_data);
				fwrite(encInfo->image_data, 8, sizeof(char), fptr_stego_image);
		}
}

Status encode_magic_string(char *magic_string, EncodeInfo *encInfo)

{
		encode_data_to_image(magic_string, strlen(magic_string), encInfo->fptr_src_image, encInfo->fptr_stego_image, encInfo);
		return e_success;
}

Status encode_secret_file_extn_size(int size, EncodeInfo *encInfo)
{
		char str[32];
		fread(str, 32, sizeof(char), encInfo -> fptr_src_image);
		encode_size_to_lsb(size, str);
		fwrite(str, 32, sizeof(char), encInfo -> fptr_stego_image);
		return e_success;
}
Status encode_size_to_lsb(int size, char*image_buffer)
{
		for(int i=0;i<32;i++)
		{
				image_buffer[i] = (image_buffer[i] & 0xfffffffe ) | (( size & ( 1 << ( 31 - i ))) >> ( 31 - i ));
		}
		// printf("%d \n",size);
}

Status encode_secret_file_extn(char *file_extn, EncodeInfo *encInfo)
{
		encode_data_to_image(file_extn, strlen(encInfo -> extn_secret_file), encInfo -> fptr_src_image, encInfo -> fptr_stego_image, encInfo);
	//	printf("extension = %ld\n", strlen(file_extn));
	//	printf("extension = %s\n", encInfo->extn_secret_file);
		return e_success;

}
Status encode_secret_file_size(long file_size, EncodeInfo *encInfo)
{
		encode_secret_file_extn_size(file_size, encInfo);
		return e_success;
}
Status encode_secret_file_data(EncodeInfo *encInfo)
{
		fseek(encInfo -> fptr_secret,0,SEEK_SET);

		char str[encInfo -> size_secret_file];

		fread(str,encInfo -> size_secret_file, sizeof(char), encInfo -> fptr_secret);

		encode_data_to_image(str, encInfo -> size_secret_file, encInfo -> fptr_src_image, encInfo -> fptr_stego_image, encInfo);
		//printf("data = %s\n", str);
		//printf("size = %ld\n", encInfo -> size_secret_file);

		return e_success;
}
Status copy_remaining_img_data(FILE *fptr_src, FILE *fptr_dest)
{
			char str;

			while(	fread(&str, 1, 1, fptr_src ) > 0)

			fwrite(&str, 1, 1,fptr_dest);

			return e_success;

		
}

