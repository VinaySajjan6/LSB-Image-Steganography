LSB Image Steganography
This repository contains a C-based implementation of LSB (Least Significant Bit) Image Steganography, a technique used to hide secret text within an image file. The project encodes a secret message into an image and decodes it back from the image.

Table of Contents
  * Introduction
  * Features
  * Requirements
  * Installation
  * Usage
  * Project Structure
  * How It Works
  * Example
  * Contributing
  * License
1) Introduction
        Image Steganography is the art of hiding information within an image in such a way that the image appears unchanged to the naked eye.
        This project uses the Least Significant Bit (LSB) technique, where the LSB of each pixel is altered to encode the secret message.

2) Features
    Encoding: Hide a secret text message within a BMP image file.
    Decoding: Extract the hidden text from the steganographic image.
    Command Line Interface: Easy-to-use command line arguments for encoding and decoding.
    Error Handling: Proper validation of inputs and error handling.
3) Requirements
    C compiler (e.g., GCC)
    Make (optional, for automated build process)
    BMP image file for encoding/decoding
4) Installation
    Clone the repository:
   bash
Copy code
git clone https://github.com/VinaySajjan6/lsb-image-steganography.git
cd lsb-image-steganography
Compile the code:

bash
Copy code
gcc -o steganography steganography.c
(Optional) Using Makefile: If a Makefile is provided, you can simply run:

bash
Copy code
make
Usage
Encoding
To encode a secret message into an image:

bash
Copy code
./steganography -e <input_image.bmp> <output_image.bmp> "<secret_message>"
<input_image.bmp>: The original BMP image file.
<output_image.bmp>: The resulting image file with the hidden message.
"<secret_message>": The text message you want to hide.
Decoding
To decode the hidden message from an image:

bash
Copy code
./steganography -d <input_image.bmp>
<input_image.bmp>: The BMP image file with the hidden message.
Example
bash
Copy code
# Encode a message
./steganography -e input.bmp output.bmp "Hello, World!"

# Decode the message
./steganography -d output.bmp
Project Structure
graphql
Copy code
lsb-image-steganography/
│
├── steganography.c      # Main source code for encoding/decoding
├── Makefile             # Optional file for building the project
├── README.md            # Documentation
└── examples/            # Example BMP files for testing
How It Works
Encoding Process
The secret message is converted into a binary format.
The LSB of each pixel in the image is replaced with the bits of the secret message.
The modified image is saved as the output image.
Decoding Process
The program reads the LSB of each pixel from the steganographic image.
The bits are combined to reconstruct the hidden message.
Example
Before Encoding:
Original Image: input.bmp
Secret Message: "Hello, World!"
After Encoding:
Steganographic Image: output.bmp
Decoding:
Hidden Message: "Hello, World!"
Contributing
Contributions are welcome! Please fork the repository and submit a pull request for any improvements or bug fixes.

License
This project is licensed under the MIT License. See the LICENSE file for more details.
