#include <iostream>
#include <fstream>
#include <vector>
//#include "helper.cpp"
#include "ImageProcessingClass.h"
using namespace std;
//
//int main() {
//    //execute task 1
//    ImageProcessing* multiply1 = new ImageProcessing("input/layer1.tga");
//    ImageProcessing* multiply2 = new ImageProcessing("input/pattern1.tga");
//    ImageProcessing* multiply3 = multiply1->Multiply(multiply2);
//    multiply3->writePixelArray("output/part1.tga");
//
//    //execute task 2
//    ImageProcessing* subtract1 = new ImageProcessing("input/layer2.tga");
//    ImageProcessing* subtract2 = new ImageProcessing("input/car.tga");
//    ImageProcessing* subtract3 = subtract2->Subtract(subtract1);
//    subtract3->writePixelArray("output/part2.tga");
//
//    //execute task 3
//    ImageProcessing* task3_1 = new ImageProcessing("input/layer1.tga");
//    ImageProcessing* task3_2 = new ImageProcessing("input/pattern2.tga");
//    ImageProcessing* task3_3 = task3_1->Multiply(task3_2);
//
//    ImageProcessing* task3_4 = new ImageProcessing("input/text.tga");
//    ImageProcessing* task3_5 = task3_3->Screen(task3_4);
//
//    task3_5->writePixelArray("output/part3.tga");
//
//    //execute task 4
//    ImageProcessing* task4_1 = new ImageProcessing("input/layer2.tga");
//    ImageProcessing* task4_2 = new ImageProcessing("input/circles.tga");
//    ImageProcessing* task4_3 = task4_1->Multiply(task4_2);
//
//    ImageProcessing* task4_4 = new ImageProcessing("input/pattern2.tga");
//    ImageProcessing* task4_5 = task4_3->Subtract(task4_4);
//
//    task4_5->writePixelArray("output/part4.tga");
//
//    //execute task 5
//    ImageProcessing* overlay1 = new ImageProcessing("input/layer1.tga");
//    ImageProcessing* overlay2 = new ImageProcessing("input/pattern1.tga");
//    ImageProcessing* overlay3 = overlay1->Overlay(overlay2);
//    overlay3->writePixelArray("output/part5.tga");
//
//    //execute task 6
//    ImageProcessing* task6_1 = new ImageProcessing("input/car.tga");
//    task6_1->AddConstantToChannel(200, 1);
//    task6_1->writePixelArray("output/part6.tga");
//
//    //execute task 7
//    ImageProcessing* task7_1 = new ImageProcessing("input/car.tga");
//    task7_1->MultiplyConstantToChannel(4, 2);
//    task7_1->MultiplyConstantToChannel(0, 0);
//    task7_1->writePixelArray("output/part7.tga");
//
//    //execute task 8
//    ImageProcessing* task8_1 = new ImageProcessing("input/car.tga");
//    ImageProcessing** imageArray = task8_1->SeparateChannel();
//    imageArray[0]->writePixelArray("output/part8_b.tga");
//    imageArray[1]->writePixelArray("output/part8_g.tga");
//    imageArray[2]->writePixelArray("output/part8_r.tga");
//
//    //execute task 9
//    ImageProcessing* task9_1 = new ImageProcessing("input/layer_blue.tga");
//    ImageProcessing* task9_2 = new ImageProcessing("input/layer_green.tga");
//    ImageProcessing* task9_3 = new ImageProcessing("input/layer_red.tga");
//    ImageProcessing* task9_4 = new ImageProcessing;
//    task9_4->size = task9_1->size;
//    task9_4->populateHeader(task9_1->H);
//    task9_4->pixelArray = new unsigned char[task9_4->size * 3];
//    task9_4->CombineChannel(task9_1, task9_2, task9_3);
//    task9_4->writePixelArray("output/part9.tga");
//
//    //execute task 10
//    ImageProcessing* task10_1 = new ImageProcessing("input/text2.tga");
//    task10_1->FlipImage();
//    task10_1->writePixelArray("output/part10.tga");
//}

void printHelp() {
    cout << "Project 2: Image Processing, Spring 2024\n\nUsage:\n\t./project2.out [output] [firstImage] [method] [...]" << endl;
}
bool checkEnd(string fileName) {
    int length = fileName.length();
    if (length < 4) {
        return false;
    }

    else if (".tga" != fileName.substr(length - 4, 4)) {
        return false;
    }

    return true;
}

bool fileExists (string fileName) {
    ifstream image;
    image.open(fileName, ios::binary);
    return image.good();
//    if(image.is_open()) {
//        return true;
//    }
//
//    else {
//        return false;
//    }
}

bool isDigit(string number) {
    if (number.length() == 1 && number[0] == '-') {
        return false;
    }

    if (number[0] == '-') {
        number = number.substr(1, number.length() -1);
    }

    if (number[0] == '-' && number[1] == '0') {
        return false;
    }

    for (int i = 0; i < number.length(); i++) {
        if (isdigit((char)number[i])) {
            continue;
        }

        else {
            return false;
        }
    }
    return true;
}

int convertToInt(string num) {
    if (num[0] == '-') {
        return -1 * stoi(num.substr(1, num.length() - 1));
    }

    else {
        return stoi(num);
    }
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printHelp();
        return 0;
    }

    if ((string)argv[1] == "--help") {
        printHelp();
        return 0;
    }

    if (checkEnd((string)argv[1]) == false) {
        cout << "Invalid file name." << endl;
        return 0;
    }

    if (checkEnd((string)argv[2]) == false) {
        cout << "Invalid file name." << endl;
        return 0;
    }

    if (fileExists(argv[2]) == false) {
        cout << "File does not exist." << endl;
        return 0;
    }

    string outputFile = argv[1];
    string inputFile = argv[2];
    ImageProcessing *finalImage = new ImageProcessing(inputFile);

    for (int i = 3; i < argc;) {

        if ((string)argv[i] == "multiply") {
            if (argc <= i + 1) {
                cout << "Missing argument." << endl;
                return 0;
            }

            if (checkEnd((string)argv[i + 1]) == false) {
                cout << "Invalid argument, invalid file name." << endl;
                return 0;
            }

            if (fileExists((string)argv[i + 1]) == false) {
                cout << "Invalid argument, file does not exist." << endl;
                return 0;
            }

            ImageProcessing *multiplyImage = new ImageProcessing(argv[i + 1]);
            finalImage = finalImage->Multiply(multiplyImage);

            if (i == 3) {
                cout << "Multiplying " << (string)argv[i + 1] << " and " << (string)argv[2] << " ..." << endl;
            }

            else {
                cout << "... and multiplying " << (string)argv[i + 1] << " from previous step ..." << endl;
            }

            finalImage->writePixelArray((string)argv[1]);
            i += 2;
        }

        else if ((string)argv[i] == "subtract") {
            if (argc <= i + 1) {
                cout << "Missing argument." << endl;
                return 0;
            }

            if (checkEnd((string)argv[i + 1]) == false) {
                cout << "Invalid argument, invalid file name." << endl;
                return 0;
            }

            if (fileExists((string)argv[i + 1]) == false) {
                cout << "Invalid argument, file does not exist." << endl;
                return 0;
            }

            ImageProcessing *subtractImage = new ImageProcessing(argv[i + 1]);
            finalImage = finalImage->Subtract(subtractImage);

            if (i == 3) {
                cout << "Subtracting " << (string)argv[i + 1] << " and " << (string)argv[2] << " ..." << endl;
            }

            else {
                cout << "... and subtracting " << (string)argv[i + 1] << " from previous step ..." << endl;
            }

            finalImage->writePixelArray((string)argv[1]);
            i += 2;
        }

        else if ((string)argv[i] == "overlay") {
            if (argc <= i + 1) {
                cout << "Missing argument." << endl;
                return 0;
            }

            if (checkEnd((string)argv[i + 1]) == false) {
                cout << "Invalid argument, invalid file name." << endl;
                return 0;
            }

            if (fileExists((string)argv[i + 1]) == false) {
                cout << "Invalid argument, file does not exist." << endl;
                return 0;
            }

            ImageProcessing *overlayImage = new ImageProcessing(argv[i + 1]);
            finalImage = finalImage->Overlay(overlayImage);
            finalImage->writePixelArray((string)argv[1]);
            i += 2;
        }

        else if ((string)argv[i] == "screen") {
            if (argc <= i + 1) {
                cout << "Missing argument." << endl;
                return 0;
            }

            if (checkEnd((string)argv[i + 1]) == false) {
                cout << "Invalid argument, invalid file name." << endl;
                return 0;
            }

            if (fileExists((string)argv[i + 1]) == false) {
                cout << "Invalid argument, file does not exist." << endl;
                return 0;
            }

            ImageProcessing *screenImage = new ImageProcessing(argv[i + 1]);
            finalImage = finalImage->Screen(screenImage);

            if (i == 3) {
                cout << "Subtracting " << (string)argv[i + 1] << " and " << (string)argv[2] << " ..." << endl;
            }

            else {
                cout << "... and subtracting " << (string)argv[i + 1] << " from previous step ..." << endl;
            }

            finalImage->writePixelArray((string)argv[1]);
            i += 2;
        }

        else if ((string)argv[i] == "combine") {
            if (argc <= i + 2) {
                cout << "Missing argument." << endl;
                return 0;
            }

            if (checkEnd((string)argv[i + 1]) == false) {
                cout << "Invalid argument, invalid file name." << endl;
                return 0;
            }

            if (checkEnd((string)argv[i + 2]) == false) {
                cout << "Invalid argument, invalid file name." << endl;
                return 0;
            }

            if (fileExists((string)argv[i + 1]) == false) {
                cout << "Invalid argument, file does not exist." << endl;
                return 0;
            }

            if (fileExists((string)argv[i + 2]) == false) {
                cout << "Invalid argument, file does not exist." << endl;
                return 0;
            }

            ImageProcessing *greenImage = new ImageProcessing(argv[i + 1]);
            ImageProcessing *blueImage = new ImageProcessing(argv[i + 2]);
            finalImage->CombineChannel(blueImage, greenImage, finalImage);
            finalImage->writePixelArray((string)argv[1]);
            i += 3;
        }

        else if ((string)argv[i] == "flip") {
            finalImage->FlipImage();
            finalImage->writePixelArray((string)argv[1]);
            i++;
        }

        else if ((string)argv[i] == "onlyred") {
            ImageProcessing** imageArray = finalImage->SeparateChannel();
            finalImage = imageArray[2];
            finalImage->writePixelArray((string)argv[1]);
            i++;
        }

        else if ((string)argv[i] == "onlygreen") {
            ImageProcessing** imageArray = finalImage->SeparateChannel();
            finalImage = imageArray[1];
            finalImage->writePixelArray((string)argv[1]);
            i++;
        }

        else if ((string)argv[i] == "onlyblue") {
            ImageProcessing** imageArray = finalImage->SeparateChannel();
            finalImage = imageArray[0];
            finalImage->writePixelArray((string)argv[1]);
            i++;
        }

        else if ((string)argv[i] == "addred") {
            if (argc <= i + 1) {
                cout << "Missing argument." << endl;
                return 0;
            }

            if (isDigit((string)argv[i + 1]) == false) {
                cout << "Invalid argument, expected number." << endl;
                return 0;
            }

            finalImage->AddConstantToChannel(convertToInt(argv[i + 1]), 2);
            finalImage->writePixelArray((string)argv[1]);
            i += 2;
        }

        else if ((string)argv[i] == "addgreen") {
            if (argc <= i + 1) {
                cout << "Missing argument." << endl;
                return 0;
            }

            if (isDigit((string)argv[i + 1]) == false) {
                cout << "Invalid argument, expected number." << endl;
                return 0;
            }

            finalImage->AddConstantToChannel(convertToInt(argv[i + 1]), 1);
            finalImage->writePixelArray((string)argv[1]);
            i += 2;
        }

        else if ((string)argv[i] == "addblue") {
            if (argc <= i + 1) {
                cout << "Missing argument." << endl;
                return 0;
            }

            if (isDigit((string)argv[i + 1]) == false) {
                cout << "Invalid argument, expected number." << endl;
                return 0;
            }

            finalImage->AddConstantToChannel(convertToInt(argv[i + 1]), 0);
            finalImage->writePixelArray((string)argv[1]);
            i += 2;
        }

        else if ((string)argv[i] == "scalered") {
            if (argc <= i + 1) {
                cout << "Missing argument." << endl;
                return 0;
            }

            if (isDigit((string)argv[i + 1]) == false) {
                cout << "Invalid argument, expected number." << endl;
                return 0;
            }

            finalImage->MultiplyConstantToChannel(convertToInt(argv[i + 1]), 2);
            finalImage->writePixelArray((string)argv[1]);
            i += 2;
        }

        else if ((string)argv[i] == "scalegreen") {
            if (argc <= i + 1) {
                cout << "Missing argument." << endl;
                return 0;
            }

            if (isDigit((string)argv[i + 1]) == false) {
                cout << "Invalid argument, expected number." << endl;
                return 0;
            }

            finalImage->MultiplyConstantToChannel(convertToInt(argv[i + 1]), 1);
            finalImage->writePixelArray((string)argv[1]);
            i += 2;
        }

        else if ((string)argv[i] == "scaleblue") {
            if (argc <= i + 1) {
                cout << "Missing argument." << endl;
                return 0;
            }

            if (isDigit((string)argv[i + 1]) == false) {
                cout << "Invalid argument, expected number." << endl;
                return 0;
            }

            finalImage->MultiplyConstantToChannel(convertToInt(argv[i + 1]), 0);
            finalImage->writePixelArray((string)argv[1]);
            i += 2;
        }

        else {
            cout << "Invalid method name.";
            return 0;
        }
    }
    cout << "... and saving output to " << argv[1] << "!" << endl;

//    if ("output/" != ((string)argv[1]).substr(0, 7)) {
//        (string)argv[1] = ((string)argv[1]).insert(0, "output/");
//    }

//    if ((string)argv[1] != "out.tga") {
//        finalImage->writePixelArray((string)argv[1]);
//    }
    return 0;
    //finalImage->writePixelArray(argv[1]);
}