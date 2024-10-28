#include "pixel.h"
#include "taskfirst.h"
#include "tasksecond.h"
#include "taskthird.h"
#include "taskfourth.h"

int test4()
{
    //vector<Point> vertex1 = {Point(256, 50), Point(398, 460), Point(32, 198), Point(480, 198), Point(114, 460)};
    //vector<Point> vertex2 = { Point(256, 50), Point(398, 460), Point(32, 198), Point(256, 198), Point(480, 198), Point(114, 460) };
    //vector<Point> vertex3 = { Point(256, 50),Point(256, 50), Point(398, 460), Point(32, 198), Point(32, 198), Point(256, 198), Point(480, 198), Point(114, 460) };
    //vector<Point> vertex4 = { Point(256, 50),Point(256, 50), Point(398, 460), Point(32, 198), Point(32, 198), Point(256, 198), Point(480, 198),  Point(256, 358), Point(114, 460) };
    vector<Point> vertex1 = { Point(462, 256), Point(52, 398), Point(314, 32), Point(314, 480), Point(52, 114) };
    vector<Point> vertex2 = { Point(462, 256), Point(52, 398), Point(314, 32), Point(314, 256), Point(314, 480), Point(52, 114) };
    vector<Point> vertex3 = { Point(462, 256), Point(462, 256), Point(52, 398), Point(314, 32), Point(314, 256), Point(314, 480), Point(314, 480), Point(52, 114) };
    vector<Point> vertex4 = { Point(462, 256), Point(462, 256), Point(52, 398), Point(314, 32), Point(314, 256), Point(314, 480), Point(314, 480),  Point(154, 256), Point(52, 114) };
    Mat img4f1(512, 512, CV_8UC3, Scalar(255, 255, 255));
    if (vertex1.size() == 0)
    {
        printf("\nVector is empty");
        return -1;
    }
    for (int i = 0; i < vertex1.size(); i++)
    {
        if (vertex1[i].x < 0 || vertex1[i].y < 0 || vertex1[i].x >= img4f1.cols || vertex1[i].y >= img4f1.rows)
        {
            printf("\nPixel number is outside the image boundaries");
            return -1;
        }
    }
    string color = "#FF00FF";
    EvenOdd(img4f1, vertex1, color);
    imwrite("task4even_odd_vertical_1.png", img4f1);


    Mat img4s1(512, 512, CV_8UC3, Scalar(255, 255, 255));
    if (vertex1.size() == 0)
    {
        printf("\nVector is empty");
        return -1;
    }
    for (int i = 0; i < vertex1.size(); i++)
    {
        if (vertex1[i].x < 0 || vertex1[i].y < 0 || vertex1[i].x >= img4s1.cols || vertex1[i].y >= img4s1.rows)
        {
            printf("\nPixel number is outside the image boundaries");
            return -1;
        }
    }
    NonZeroWinding(img4s1, vertex1, color);
    imwrite("task4non_zero_winding_vertical_1.png", img4s1);

    Mat img4f2(512, 512, CV_8UC3, Scalar(255, 255, 255));
    if (vertex2.size() == 0)
    {
        printf("\nVector is empty");
        return -1;
    }
    for (int i = 0; i < vertex2.size(); i++)
    {
        if (vertex2[i].x < 0 || vertex2[i].y < 0 || vertex2[i].x >= img4f2.cols || vertex2[i].y >= img4f2.rows)
        {
            printf("\nPixel number is outside the image boundaries");
            return -1;
        }
    }
    EvenOdd(img4f2, vertex2, color);
    imwrite("task4even_odd_vertical_2.png", img4f2);


    Mat img4s2(512, 512, CV_8UC3, Scalar(255, 255, 255));
    if (vertex2.size() == 0)
    {
        printf("\nVector is empty");
        return -1;
    }
    for (int i = 0; i < vertex2.size(); i++)
    {
        if (vertex2[i].x < 0 || vertex2[i].y < 0 || vertex2[i].x >= img4s2.cols || vertex2[i].y >= img4s2.rows)
        {
            printf("\nPixel number is outside the image boundaries");
            return -1;
        }
    }
    NonZeroWinding(img4s2, vertex2, color);
    imwrite("task4non_zero_winding_vertical_2.png", img4s2);

    Mat img4f3(512, 512, CV_8UC3, Scalar(255, 255, 255));
    if (vertex3.size() == 0)
    {
        printf("\nVector is empty");
        return -1;
    }
    for (int i = 0; i < vertex3.size(); i++)
    {
        if (vertex3[i].x < 0 || vertex3[i].y < 0 || vertex3[i].x >= img4f3.cols || vertex3[i].y >= img4f3.rows)
        {
            printf("\nPixel number is outside the image boundaries");
            return -1;
        }
    }
    EvenOdd(img4f3, vertex3, color);
    imwrite("task4even_odd_vertical_3.png", img4f3);


    Mat img4s3(512, 512, CV_8UC3, Scalar(255, 255, 255));
    if (vertex3.size() == 0)
    {
        printf("\nVector is empty");
        return -1;
    }
    for (int i = 0; i < vertex3.size(); i++)
    {
        if (vertex3[i].x < 0 || vertex3[i].y < 0 || vertex3[i].x >= img4s3.cols || vertex3[i].y >= img4s3.rows)
        {
            printf("\nPixel number is outside the image boundaries");
            return -1;
        }
    }
    NonZeroWinding(img4s3, vertex3, color);
    imwrite("task4non_zero_winding_vertical_3.png", img4s3);

    Mat img4f4(512, 512, CV_8UC3, Scalar(255, 255, 255));
    if (vertex4.size() == 0)
    {
        printf("\nVector is empty");
        return -1;
    }
    for (int i = 0; i < vertex4.size(); i++)
    {
        if (vertex4[i].x < 0 || vertex4[i].y < 0 || vertex4[i].x >= img4f4.cols || vertex4[i].y >= img4f4.rows)
        {
            printf("\nPixel number is outside the image boundaries");
            return -1;
        }
    }
    EvenOdd(img4f4, vertex4, color);
    imwrite("task4even_odd_vertical_4.png", img4f4);


    Mat img4s4(512, 512, CV_8UC3, Scalar(255, 255, 255));
    if (vertex4.size() == 0)
    {
        printf("\nVector is empty");
        return -1;
    }
    for (int i = 0; i < vertex4.size(); i++)
    {
        if (vertex4[i].x < 0 || vertex4[i].y < 0 || vertex4[i].x >= img4s4.cols || vertex4[i].y >= img4s4.rows)
        {
            printf("\nPixel number is outside the image boundaries");
            return -1;
        }
    }
    NonZeroWinding(img4s4, vertex4, color);
    imwrite("task4non_zero_winding_vertical_4.png", img4s4);
    return 0;
}