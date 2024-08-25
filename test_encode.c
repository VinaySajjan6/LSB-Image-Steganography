#include <stdio.h>
#include <string.h>
#include "encode.h"
#include "types.h"
#include "decode.h"

int main(int argc, char *argv[])
{
		int option = check_operation_type(argv);
		if(option == e_encode)
		{	
				if(argc > 3)
				{
						EncodeInfo encInfo;
						printf("INFO: ## Encoding Procedure Started ##\n");
						if( read_and_validate_encode_args(argv, &encInfo) == e_success)
						{
								printf("INFO: Read and Validate ENC Argc Successfully Done\n");
							if( do_encoding(&encInfo) == e_success)
							{
									printf("INFO: ## Encoding Done Successfully ##\n");
							}
							else
							{
									printf("ERROR: ## Encoding Unsccessfully ##\n");
							}
						}	

						else
						{
								printf("ERROR: Read and Validate ENC Args is Failure\n");
						}
				}
		else
				{
						printf("ERROR: Encoding Not Possible\n");
				}
		}
		else if(option == e_decode)
		{
			if(argc > 2)
			{
				DecodeInfo decInfo;
				printf("INFO: ## Decoing Procedure Started\n");
				if( read_and_validate_decode_args(argv, &decInfo) == d_success)
				{
						printf("INFO: Read and Validate Decryption Argc Successfully Done\n");
							if( do_decoding(&decInfo) == d_success)
							{
									printf("INFO: ## Decoding Done Successfully ##\n");
							}
							else
							{
									printf("ERROR: Decoging Unsuccessfull\n");
							}
				}
				else
				{
						printf("ERROR: Read and Validate Decryption Args is Failure\n");
				}
			}
			else
			{
					printf("ERROR: Decoding Not Possible\n");
			}
		}
		else
		{
				printf("Invalid option\n");
		}
}

OperationType check_operation_type(char *argv[])
{
		if(!(strcmp(argv[1], "-e")))
		{
				return e_encode;
		}
		else if(!(strcmp(argv[1], "-d")))
		{
				return e_decode;
		}
		else
		{
				return e_unsupported;
		}
}
