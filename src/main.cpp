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

int main(int argc, char *argv[]) {
    string outputFile = argv[1];
    string inputFile = argv[2];
    ImageProcessing *finalImage = new ImageProcessing(inputFile);
    for (int i = 3; i < argc;) {
        if (argv[i] == "multiply") {
            ImageProcessing *multiplyImage = new ImageProcessing(argv[i + 1]);
            finalImage = finalImage->Multiply(multiplyImage);
            i += 2;
        }

        if (argv[i] == "subtract") {
            ImageProcessing *subtractImage = new ImageProcessing(argv[i + 1]);
            finalImage = finalImage->Subtract(subtractImage);
            i += 2;
        }

        if (argv[i] == "overlay") {
            ImageProcessing *overlayImage = new ImageProcessing(argv[i + 1]);
            finalImage = finalImage->Overlay(overlayImage);
            i += 2;
        }

        if (argv[i] == "screen") {
            ImageProcessing *screenImage = new ImageProcessing(argv[i + 1]);
            finalImage = finalImage->Overlay(screenImage);
            i += 2;
        }

        if (argv[i] == "combine") {
            ImageProcessing *greenImage = new ImageProcessing(argv[i + 1]);
            ImageProcessing *blueImage = new ImageProcessing(argv[i + 2]);
            finalImage->CombineChannel(blueImage, greenImage, finalImage);
            i += 3;
        }

        if (argv[i] == "flip") {
            finalImage->FlipImage();
            i++;
        }

        if (argv[i] == "onlyred") {
            ImageProcessing** imageArray = finalImage->SeparateChannel();
            finalImage = imageArray[2];
            i++;
        }

        if (argv[i] == "onlygreen") {
            ImageProcessing** imageArray = finalImage->SeparateChannel();
            finalImage = imageArray[1];
            i++;
        }

        if (argv[i] == "onlyblue") {
            ImageProcessing** imageArray = finalImage->SeparateChannel();
            finalImage = imageArray[0];
            i++;
        }

        if (argv[i] == "addred") {
            finalImage->AddConstantToChannel(stoi(argv[i + 1]), 2);
            i += 2;
        }

        if (argv[i] == "addgreen") {
            finalImage->AddConstantToChannel(stoi(argv[i + 1]), 1);
            i += 2;
        }

        if (argv[i] == "addblue") {
            finalImage->AddConstantToChannel(stoi(argv[i + 1]), 0);
            i += 2;
        }

        if (argv[i] == "scalered") {
            finalImage->MultiplyConstantToChannel(stoi(argv[i + 1]), 2);
            i += 2;
        }

        if (argv[i] == "scalegreen") {
            finalImage->MultiplyConstantToChannel(stoi(argv[i + 1]), 1);
            i += 2;
        }

        if (argv[i] == "scaleblue") {
            finalImage->MultiplyConstantToChannel(stoi(argv[i + 1]), 0);
            i += 2;
        }
    }
}