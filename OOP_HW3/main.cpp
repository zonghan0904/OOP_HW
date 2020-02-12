# include "main.h"
using namespace std;

int main(int argc, char** argv){
    // check whether the argument format is right.
    if (argc != 4){
        cerr << "Format: main.exe [input.bmp] [output.bmp] [brightness]" << endl;
        return -1;
    }

    // check each argument is okay.
    const char* inputfile = argv[1];
    const char* outputfile = argv[2];
    float brightness = atof(argv[3]);
    if (brightness < 0) brightness = 0;
    FILE *input = fopen(inputfile, "rb");
    if (!input){
        cerr << "ERROR: No [" << inputfile << "] file, please check it and try again.\n";
        return -1;
    }
    FILE *output = fopen(outputfile, "wb");
    if (!output){
        fclose(input);
        cerr << "ERROR: Could not create [" << outputfile << "] file, please try again later.\n";
        return -1;
    }

    // processing the image.
    try{
        set_bmp(input, output, brightness);
    }
    catch(char &){
        return -1;
    }

    return 0;
}
