#include <iostream>
#include <fstream>
#include <vector>
//#include "helper.cpp"
#include "ImageProcessingClass.h"
using namespace std;

int main() {
    //execute task 1
    ImageProcessing* multiply1 = new ImageProcessing("layer1.tga");
    ImageProcessing* multiply2 = new ImageProcessing("pattern1.tga");
    ImageProcessing* multiply3 = multiply1->Multiply(multiply2);
    multiply3->writePixelArray("task1.tga");

    //execute task 2
    ImageProcessing* subtract1 = new ImageProcessing("layer2.tga");
    ImageProcessing* subtract2 = new ImageProcessing("car.tga");
    ImageProcessing* subtract3 = subtract2->Subtract(subtract1);
    subtract3->writePixelArray("task2.tga");

    //execute task 3
    ImageProcessing* task3_1 = new ImageProcessing("layer1.tga");
    ImageProcessing* task3_2 = new ImageProcessing("pattern2.tga");
    ImageProcessing* task3_3 = task3_1->Multiply(task3_2);

    ImageProcessing* task3_4 = new ImageProcessing("text.tga");
    ImageProcessing* task3_5 = task3_3->Screen(task3_4);

    task3_5->writePixelArray("task3.tga");

    //execute task 4
    ImageProcessing* task4_1 = new ImageProcessing("layer2.tga");
    ImageProcessing* task4_2 = new ImageProcessing("circles.tga");
    ImageProcessing* task4_3 = task4_1->Multiply(task4_2);

    ImageProcessing* task4_4 = new ImageProcessing("pattern2.tga");
    ImageProcessing* task4_5 = task4_3->Subtract(task4_4);

    task4_5->writePixelArray("task4.tga");

    //execute task 5
    ImageProcessing* overlay1 = new ImageProcessing("layer1.tga");
    ImageProcessing* overlay2 = new ImageProcessing("pattern1.tga");
    ImageProcessing* overlay3 = overlay1->Overlay(overlay2);
    overlay3->writePixelArray("task5.tga");

    //execute task 6
    ImageProcessing* task6_1 = new ImageProcessing("car.tga");
    task6_1->AddConstantToChannel(200, 1);
    task6_1->writePixelArray("task6.tga");

    //execute task 7
    ImageProcessing* task7_1 = new ImageProcessing("car.tga");
    task7_1->MultiplyConstantToChannel(4, 2);
    task7_1->MultiplyConstantToChannel(0, 0);
    task7_1->writePixelArray("task7.tga");

    //execute task 8
    ImageProcessing* task8_1 = new ImageProcessing("car.tga");
    ImageProcessing** imageArray = task8_1->SeparateChannel();
    imageArray[0]->writePixelArray("part8_b.tga");
    imageArray[1]->writePixelArray("part8_g.tga");
    imageArray[2]->writePixelArray("part8_r.tga");

    //execute task 9
    ImageProcessing* task9_1 = new ImageProcessing("layer_blue.tga");
    ImageProcessing* task9_2 = new ImageProcessing("layer_green.tga");
    ImageProcessing* task9_3 = new ImageProcessing("layer_red.tga");
    ImageProcessing* task9_4 = new ImageProcessing;
    task9_4->size = task9_1->size;
    task9_4->populateHeader(task9_1->H);
    task9_4->pixelArray = new unsigned char[task9_4->size * 3];
    task9_4->CombineChannel(task9_1, task9_2, task9_3);
    task9_4->writePixelArray("task9.tga");

    //execute task 10
    ImageProcessing* task10_1 = new ImageProcessing("text2.tga");
    task10_1->FlipImage();
    task10_1->writePixelArray("task10.tga");
}