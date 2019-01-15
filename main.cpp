#include <Magick++.h>
#include <iostream>

using namespace std;
using namespace Magick;

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


        image.type( Magick::GrayscaleType );
        image.write(result_filename);
    }
    catch( Exception &error_ )
    {
        cout << "Caught exception: " << error_.what() << endl;
        return 1;
    }


    return 0;
}