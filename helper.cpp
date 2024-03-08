#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Header {
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;
};

//reads the header data for given image
void getHeader(Header &H, string fileName) {
    ifstream image;
    image.open(fileName, ios::binary);

    image.read(&H.idLength, 1);
    image.read(&H.colorMapType, 1);
    image.read(&H.dataTypeCode, 1);
    image.read((char *) &H.colorMapOrigin, 2);
    image.read((char *) &H.colorMapLength, 2);
    image.read(&H.colorMapDepth, 1);
    image.read((char *) &H.xOrigin, 2);
    image.read((char *) &H.yOrigin, 2);
    image.read((char *) &H.width, 2);
    image.read((char *) &H.height, 2);
    image.read(&H.bitsPerPixel, 1);
    image.read(&H.imageDescriptor, 1);

    image.close();
}

//populates an array with BGR values
void populatePixelArray(unsigned char *pixelArray, string fileName, int size) {
    ifstream image;
    image.open(fileName, ios::binary);

    if (!image.is_open()) {
        std::cerr << "Error opening file: " << fileName << std::endl;
        return; // Return early if the file couldn't be opened
    }

    image.seekg(18, ios::beg); //skips the first 18 bytes
    image.read((char *)pixelArray, size * 3);
    image.close();
}

//writes the image data to a new file
void writePixelArray(unsigned char *pixelArray, string fileName, int size, Header H) {
    ofstream image;
    image.open(fileName, ios::binary);

    //writes the header (first 18 bytes) to the file
    image.write(&H.idLength, 1);
    image.write(&H.colorMapType, 1);
    image.write(&H.dataTypeCode, 1);
    image.write((char *) &H.colorMapOrigin, 2);
    image.write((char *) &H.colorMapLength, 2);
    image.write(&H.colorMapDepth, 1);
    image.write((char *) &H.xOrigin, 2);
    image.write((char *) &H.yOrigin, 2);
    image.write((char *) &H.width, 2);
    image.write((char *) &H.height, 2);
    image.write(&H.bitsPerPixel, 1);
    image.write(&H.imageDescriptor, 1);

    //write the array to the file
    image.write((char *)pixelArray, size * 3);

    image.close();
}

void Multiply(unsigned char* pixelArray1,
              unsigned char* pixelArray2,
              unsigned char* combinedPixelArray,
              int size,
              Header H) {
    for (int i = 0; i < size * 3; i++) {
        combinedPixelArray[i] = ((((float) pixelArray1[i] / 255) * ((float) pixelArray2[i] / 255)) * 255) + 0.5f;
    }
}

void Subtract(unsigned char* pixelArray1,
              unsigned char* pixelArray2,
              unsigned char* subtractedPixelArray,
              int size,
              Header H) {
    for (int i = 0; i < size * 3; i++) {
        int newValue = (int)pixelArray1[i] - (int)pixelArray2[i];
        if (newValue < 0) {
            newValue = 0;
        }
        subtractedPixelArray[i] = newValue;
    }
}

void Addition(unsigned char* pixelArray1,
              unsigned char* pixelArray2,
              unsigned char* subtractedPixelArray,
              int size,
              Header H) {
    for (int i = 0; i < size * 3; i++) {
        int newValue = (int)pixelArray1[i] + (int)pixelArray2[i];
        if (newValue > 255) {
            newValue = 255;
        }
        subtractedPixelArray[i] = newValue;
    }
}

void executeTask1() {
    Header H1;
    Header H2;

    getHeader(H1, "layer1.tga");
    getHeader(H2, "pattern1.tga");

    int size1 = H1.height * H1.width;
    unsigned char* pixelArray1 = new unsigned char[size1 * 3];

    int size2 = H2.height * H2.width;
    unsigned char* pixelArray2 = new unsigned char[size2 * 3];

    populatePixelArray(pixelArray1, "layer1.tga", size1);
    populatePixelArray(pixelArray2, "pattern1.tga", size2);

    unsigned char* combinedImageArray = new unsigned char[size1 * 3];
    Multiply(pixelArray1, pixelArray2, combinedImageArray, size1, H1);

    writePixelArray(combinedImageArray, "newCombinedImage.tga", size1, H1);

    delete[] pixelArray1;
    delete[] pixelArray2;
    delete[] combinedImageArray;
}

void executeTask2() {
    Header H1;
    Header H2;

    getHeader(H1, "car.tga");
    getHeader(H2, "layer2.tga");

    int size1 = H1.height * H1.width;
    unsigned char* pixelArray1 = new unsigned char[size1 * 3];

    int size2 = H2.height * H2.width;
    unsigned char* pixelArray2 = new unsigned char[size2 * 3];

    populatePixelArray(pixelArray1, "car.tga", size1);
    populatePixelArray(pixelArray2, "layer2.tga", size2);

    unsigned char* combinedImageArray = new unsigned char[size1 * 3];
    Subtract(pixelArray1, pixelArray2, combinedImageArray, size1, H1);

    writePixelArray(combinedImageArray, "subtractedImage.tga", size1, H1);

    delete[] pixelArray1;
    delete[] pixelArray2;
    delete[] combinedImageArray;
}

void executeTask6() {
    Header H1;

    getHeader(H1, "car.tga");

    int size1 = H1.height * H1.width;
    unsigned char* pixelArray1 = new unsigned char[size1 * 3];

    populatePixelArray(pixelArray1, "car.tga", size1);

    for (int i = 0; i < size1 * 3; i += 3) {
        int greenChannel = (int)pixelArray1[i + 1] + 200;
        if (greenChannel > 255) {
            greenChannel = 255;
        }
        pixelArray1[i + 1] = greenChannel;
    }

    writePixelArray(pixelArray1, "greenChannelCar.tga", size1, H1);
}

