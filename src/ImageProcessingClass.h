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

class ImageProcessing {
    public:
        string fileName;
        int size;
        Header H;
        unsigned char* pixelArray;

        ImageProcessing() {}

        ImageProcessing(string file) {
            fileName = file;
            getHeader();
            size = H.height * H.width;
            pixelArray = new unsigned char[size * 3];
            populatePixelArray();
        }

        ~ImageProcessing() {
            delete[] pixelArray;
        }

        void getHeader() {
            ifstream image;
            image.open(fileName, ios::binary);

            image.read(&H.idLength, 1);
            image.read(&H.colorMapType, 1);
            image.read(&H.dataTypeCode, 1);
            image.read((char*) &H.colorMapOrigin, 2);
            image.read((char*) &H.colorMapLength, 2);
            image.read(&H.colorMapDepth, 1);
            image.read((char*) &H.xOrigin, 2);
            image.read((char*) &H.yOrigin, 2);
            image.read((char*) &H.width, 2);
            image.read((char*) &H.height, 2);
            image.read(&H.bitsPerPixel, 1);
            image.read(&H.imageDescriptor, 1);

            image.close();
        }

        void populatePixelArray() {
            ifstream image;
            image.open(fileName, ios::binary);

            if (!image.is_open()) {
                cerr << "Error opening file: " << fileName << endl;
                return;
            }

            image.seekg(18, ios::beg); //skips the first 18 bytes
            image.read((char*)pixelArray, size * 3);
            image.close();
        }

        void writePixelArray(string file) {
            ofstream image;
            image.open(file, ios::binary);

            //writes the header (first 18 bytes) to the file
            image.write(&H.idLength, 1);
            image.write(&H.colorMapType, 1);
            image.write(&H.dataTypeCode, 1);
            image.write((char*) &H.colorMapOrigin, 2);
            image.write((char*) &H.colorMapLength, 2);
            image.write(&H.colorMapDepth, 1);
            image.write((char*) &H.xOrigin, 2);
            image.write((char*) &H.yOrigin, 2);
            image.write((char*) &H.width, 2);
            image.write((char*) &H.height, 2);
            image.write(&H.bitsPerPixel, 1);
            image.write(&H.imageDescriptor, 1);

            //write the array to the file
            image.write((char*)pixelArray, size * 3);

            image.close();
        }

        void populateHeader(Header header){
            H.idLength = header.idLength;
            H.colorMapType = header.colorMapType;
            H.dataTypeCode = header.dataTypeCode;
            H.colorMapOrigin = header.colorMapOrigin;
            H.colorMapLength = header.colorMapLength;
            H.colorMapDepth = header.colorMapDepth;
            H.xOrigin = header.xOrigin;
            H.yOrigin = header.yOrigin;
            H.width = header.width;
            H.height = header.height;
            H.bitsPerPixel = header.bitsPerPixel;
            H.imageDescriptor = header.imageDescriptor;
        }

        ImageProcessing* Multiply(ImageProcessing* secondImage) {
            ImageProcessing* multipliedImage = new ImageProcessing;
            multipliedImage->size = size;
            multipliedImage->populateHeader(H);
            multipliedImage->pixelArray = new unsigned char[multipliedImage->size * 3];
            for (int i = 0; i < size * 3; i++) {
                multipliedImage->pixelArray[i] = ((((float) pixelArray[i] / 255) * ((float) secondImage->pixelArray[i] / 255)) * 255) + 0.5f;
            }
            return multipliedImage;
        }

        ImageProcessing* Subtract(ImageProcessing* secondImage) {
            ImageProcessing* subtractedImage = new ImageProcessing;
            subtractedImage->size = size;
            subtractedImage->populateHeader(H);
            subtractedImage->pixelArray = new unsigned char[subtractedImage->size * 3];

            for (int i = 0; i < size * 3; i++) {
                int newValue = (int)pixelArray[i] - (int)secondImage->pixelArray[i];
                if (newValue < 0) {
                    newValue = 0;
                }
                subtractedImage->pixelArray[i] = newValue;
            }

            return subtractedImage;
        }

        ImageProcessing* Addition(ImageProcessing* secondImage) {
            ImageProcessing* addedImage = new ImageProcessing;
            addedImage->size = size;
            addedImage->populateHeader(H);
            addedImage->pixelArray = new unsigned char[addedImage->size * 3];
            for (int i = 0; i < size * 3; i++) {
                int newValue = (int)pixelArray[i] + (int)secondImage->pixelArray[i];
                if (newValue > 255) {
                    newValue = 255;
                }
                addedImage->pixelArray[i] = newValue;
            }
            return addedImage;
        }

        void AddConstantToChannel(int value, int channelNumber) {
            for (int i = 0; i < size * 3; i += 3) {
                int newValue = pixelArray[i + channelNumber] + value;

                if (newValue > 255) {
                    newValue = 255;
                }

                pixelArray[i + channelNumber] = newValue;
            }
        }

        void MultiplyConstantToChannel(int value, int channelNumber) {
            for (int i = 0; i < size * 3; i += 3) {
                int newValue = ((((float)pixelArray[i + channelNumber]/255) * value) * 255) + 0.5f;

                if (newValue > 255) {
                    newValue = 255;
                }

                pixelArray[i + channelNumber] = newValue;
            }
        }

        //for task 8
        ImageProcessing** SeparateChannel() {
            ImageProcessing* redChannel = new ImageProcessing;
            ImageProcessing* blueChannel = new ImageProcessing;
            ImageProcessing* greenChannel = new ImageProcessing;

            redChannel->size = size;
            blueChannel->size = size;
            greenChannel->size = size;

            redChannel->populateHeader(H);
            blueChannel->populateHeader(H);
            greenChannel->populateHeader(H);

            redChannel->pixelArray = new unsigned char[size * 3];
            blueChannel->pixelArray = new unsigned char[size * 3];
            greenChannel->pixelArray = new unsigned char[size * 3];

            for (int i = 0; i < size * 3; i += 3) {
                blueChannel->pixelArray[i] = pixelArray[i];
                blueChannel->pixelArray[i + 1] = pixelArray[i];
                blueChannel->pixelArray[i + 2] = pixelArray[i];

                greenChannel->pixelArray[i] = pixelArray[i + 1];
                greenChannel->pixelArray[i + 1] = pixelArray[i + 1];
                greenChannel->pixelArray[i + 2] = pixelArray[i + 1];

                redChannel->pixelArray[i] = pixelArray[i + 2];
                redChannel->pixelArray[i + 1] = pixelArray[i + 2];
                redChannel->pixelArray[i + 2] = pixelArray[i + 2];
            }

            ImageProcessing** imageArray = new ImageProcessing*[3];
            imageArray[0] = blueChannel;
            imageArray[1] = greenChannel;
            imageArray[2] = redChannel;

            return imageArray;
        }

        //for task 9
        void CombineChannel(ImageProcessing* blueImage, ImageProcessing* greenImage, ImageProcessing* redImage) {
            for (int i = 0; i < size * 3; i += 3) {
                pixelArray[i] = blueImage->pixelArray[i];
                pixelArray[i + 1] = greenImage->pixelArray[i + 1];
                pixelArray[i + 2] = redImage->pixelArray[i + 2];
            }
        }

        void FlipImage() {
            unsigned char* flippedPixelArray = new unsigned char[size * 3];

            for (int i = 0; i < size; i++) {
                flippedPixelArray[i * 3] = pixelArray[(size - i - 1) * 3];
                flippedPixelArray[(i * 3) + 1] = pixelArray[((size - i - 1) * 3) + 1];
                flippedPixelArray[(i * 3) + 2] = pixelArray[((size - i - 1) * 3) + 2];
            }

            delete[] pixelArray;
            pixelArray = flippedPixelArray;
        }

        ImageProcessing* Screen(ImageProcessing* secondImage) {
            ImageProcessing* screenImage = new ImageProcessing;
            screenImage->size = size;
            screenImage->populateHeader(H);
            screenImage->pixelArray = new unsigned char[screenImage->size * 3];
            for (int i = 0; i < size * 3; i++) {
                screenImage->pixelArray[i] = ((1 - ((1 - ((float)pixelArray[i]/255)) * (1 - ((float)secondImage->pixelArray[i]/255)))) * 255) + 0.5f;
            }
            return screenImage;
        }

        ImageProcessing* Overlay(ImageProcessing* secondImage) {
            ImageProcessing* overlayImage = new ImageProcessing;
            overlayImage->size = size;
            overlayImage->populateHeader(H);
            overlayImage->pixelArray = new unsigned char[overlayImage->size * 3];
            float NP2;
            for (int i = 0; i < size * 3; i++) {
                NP2 = (float)secondImage->pixelArray[i]/255;

                if (NP2 <= 0.5) {
                    overlayImage->pixelArray[i] = ((2 * ((float)pixelArray[i]/255) * NP2) * 255) + 0.5f;
                }

                if (NP2 > 0.5) {
                    overlayImage->pixelArray[i] = ((1 - (2 * (1 - ((float)pixelArray[i]/255)) * (1 - NP2))) * 255) + 0.5f;
                }
            }
            return overlayImage;
        }
};