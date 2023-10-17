# Machine Learning Library for Linear Regression

This repository hosts a versatile and efficient machine learning library developed in the C programming language. Specifically designed for linear regression, it empowers precise and effective modeling, making it an invaluable tool for a variety of applications.

## Key Highlights

### Linear Regression for Housing Price Prediction
Harness the power of this library to predict housing prices. We've included a sample program that predicts housing prices based on California housing data. With robust linear regression algorithms, this program provides accurate insights into real estate trends, assisting both buyers and sellers in making informed decisions.

### Image Hue Manipulation
In addition to housing price prediction, we've designed a program that utilizes this machine learning library to learn and manipulate the hues of images. This unique application of linear regression enables creative image enhancement and manipulation, making it an essential tool for image processing enthusiasts.

## Files and Their Functions

- `SDL2.framework` and `SDL2_ttf.framework`: These frameworks facilitate the use of the SDL library.

- `Makefile`: This file contains the necessary code to run the program. It includes options for both photo editing and house price prediction (enabled by default).

- `OpenSans-Regular.ttf`: The font file used in the programs.

- `aaa.bmp` and `blue.bmp`: Training data for the photo editor program (enabled by default).

- `data.csv`: Training data for the California housing price prediction model.

- `main.c`: The code for the California housing price prediction program.

- `ml.c` and `ml.h`: The machine learning library implementation and header files.

- `opener.c` and `opener.h`: Code for opening images.

- `photo.c`: Contains functions for performing manipulation on photos.

- `stb_image.h` and `stb_image_write.h`: Necessary libraries for photo manipulation.

- `test.csv`: Testing data for the housing prediction model.

## Usage

1. Clone this repository to your local machine.

2. Ensure you have the required frameworks and libraries (`SDL2.framework` and `SDL2_ttf.framework`) installed for the SDL library.

3. Compile the program using the provided `Makefile`.

4. Run the program to explore housing price prediction and image hue manipulation.


## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
