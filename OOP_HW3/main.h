# include <iostream>
# include <cstdlib>
# include <cstdio>
using namespace std;

struct RGB{
    unsigned char B;
    unsigned char G;
    unsigned char R;
};

void set_bmp(FILE* input, FILE* output, float brightness){
    // read the input bitmap file header and check input format is right.
    char Header[54];               // file header 14 Bytes + info header 40 Bytes = Header 40 bytes.
    fread(Header, 1, 54, input);
    unsigned short int type = *(unsigned short int *)&Header[0];         // type is require 0x4d42.
    unsigned int offset = *(unsigned int *)&Header[10];                  // offset is required 14+40=54.
    unsigned int bisize = *(unsigned int *)&Header[14];                  // bisize is requires 40
    unsigned short int bitcount = *(unsigned short int *)&Header[28];    // bitcount is required 24-bit.
    unsigned int compression = *(unsigned int *)&Header[30];             // compression is required 0, the most common.
    if (type != 0x4d42 || offset != 54 || bisize != 40 || bitcount != 24 || compression != 0){
        fclose(input);
        fclose(output);
        cerr << "ERROR: Unsupported file format.\n";
        throw 'a';
    }

    // get the information what is needed and write down the info into output file.
    int width = *(int *)&Header[18];
    if (width < 0) width = - width;
    int height = *(int *)&Header[22];
    if (height < 0) height = - height;
    fwrite(Header, 1, 54, output);

    ////////// detail info //////////
    /*
    unsigned short int bfsize = *(unsigned short int *)&Header[2];
    cout << "Width: " << width << endl;
    cout << "Height: " << height << endl;
    cout << "Bitcount: " << bitcount << endl;
    cout << "type: " << type << endl;
    cout << "bfsize: " << bfsize << endl;
    cout << "bisize: " << bisize << endl;
    cout << "compression: " << compression << endl;
    cout << "offbit: " << offset << endl;
    cout << "type: " << bf.bfType << endl;
    cout << "bfsize: " << bf.bfSize << endl;
    cout << "bisize: " << bi.biSize << endl;
    cout << "compression: " << bi.biCompression << endl;
    */
    ////////// detail info //////////

    // get the padding information.
    int BytePerPixel = bitcount / 8;
    int padding = (4 - ((width * BytePerPixel) % 4)) % 4;

    // processing the each pixel by multiply to the argument, and use exception handling the overflow.
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            RGB pixel;
            fread(&pixel, sizeof(RGB), 1, input);
            int value;
            try{
                value = (int)(unsigned char)pixel.B;
                value = value * brightness;
                if (value > 255) throw 1;
            }
            catch(int &){
                cerr << "WARNING: Pixel(" << j << ", " << i << ") B is overflow.\n";
                value = 255;
            }
            pixel.B = (unsigned char) value;
            try{
                value = (int)(unsigned char)pixel.G;
                value = value * brightness;
                if (value > 255) throw 1;
            }
            catch(int &){
                cerr << "WARNING: Pixel(" << j << ", " << i << ") G is overflow.\n";
                value = 255;
            }
            pixel.G = (unsigned char) value;
            try{
                value = (int)(unsigned char)pixel.R;
                value = value * brightness;
                if (value > 255) throw 1;
            }
            catch(int &){
                cerr << "WARNING: Pixel(" << j << ", " << i << ") R is overflow.\n";
                value = 255;
            }
            pixel.R = (unsigned char) value;
            fwrite(&pixel, sizeof(RGB), 1, output);
            //cout << (int)((unsigned)pixel.B) << " " << (int)((unsigned)pixel.G) << " " << (int)((unsigned)pixel.R) << endl;
        }
        fseek(input, padding, SEEK_CUR);     // avoid read the padding part in the input file.
        for (int k = 0; k < padding; k++){
            fputc(0x00, output);             // write down the padding part in the input file which are not be read.
        }
    }

    // close the file.
    fclose(input);
    fclose(output);
}

int main(int argc, char** argv);
