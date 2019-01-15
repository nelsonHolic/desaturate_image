#include <Magick++.h>
#include <iostream>

using namespace std;
using namespace Magick;

void desaturateImage(Image *image) {
    size_t w = image->columns();
    size_t h = image->rows();

    // get a "pixel cache" for the entire &image
    PixelPacket *pixels = image->getPixels(0, 0, w, h);

    // now you can access single pixels like a vector
    int row = 0;
    int column = 0;
    int desaturatedColor = 0;
    PixelPacket currentPixel;


    for (row = 0; row < h; row++) {
        for (column = 0; column < w; column++) {
            currentPixel = pixels[w * row + column];
            desaturatedColor = (currentPixel.red + currentPixel.green  + currentPixel.blue) / 3;
            pixels[w * row + column] = Color(desaturatedColor, desaturatedColor, desaturatedColor);
        }
    }

    image->syncPixels();
}

void desaturateImageConvolve(Image *image) {
    double kernel[9] = { 0, -1, 0, -1, 5, -1, 0, -1, 0};
    image->convolve(9, kernel);
}


int main(int argc,char **argv)
{
    InitializeMagick(*argv); // Create base image

    Image image;

    if( argc < 2) {
        cerr << "there are not enough params, you need to set at least the file name" << endl;
        exit(1);
    }

    try {
        // Read a file into image object
        image.read(argv[1]);

        string result_filename;



        if(argc >= 3) {
            result_filename = argv[2];
        } else {
            result_filename = "result_image.png";
        }

        desaturateImage(&image);

        image.write(result_filename);
    }
    catch( Exception &error_ )
    {
        cout << "Caught exception: " << error_.what() << endl;
        return 1;
    }


    return 0;
}