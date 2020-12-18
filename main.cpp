#include <complex>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

// Declare global varibles
int imgWidth;
int imgHeight;
double widthChange = -1.5;
double heightChange = -0.5;

/* I dont really know how this works */
int value(int x, int y, double changeWidth, double changeHeight)
{
    std::complex<float> point((float)x / imgWidth + changeWidth, (float)y / imgHeight + changeHeight);
    std::complex<float> z(0, 0);
    int nb_iter = 0;
    while (std::abs(z) < 2 && nb_iter <= 80)
    {
        z = z * z + point;
        nb_iter++;
    }
    if (nb_iter < 20)
    {
        return (255 * nb_iter) / 20;
    }
    else
    {
    return 0;
    }
}

std::string threadLoop(int startY, int endY, int width)
{
    std::vector<std::vector<std::string>> imgData; // declare the 2D image data vector

    for (int y = startY; y < endY; y++)
    {
        std::vector<std::string> rowData; // row data vector

        for (int x = 0; x < width; x++)
        {
            int val = value(x, y, widthChange, heightChange);
            std::string toAppend = std::to_string(val) + " 0 0" + "\n";
            rowData.push_back(toAppend); // write the pixel data to rowData
        }
        imgData.push_back(rowData); // write rowData to imgData
    }
    std::string returnVal; // declare the return string
    // loop over each pixel and add it to return string
    for (size_t i = 0; i < imgData.size(); i++)
    {
        for (size_t j = 0; j < imgData[i].size(); j++)
        {
            returnVal.append(imgData[i][j]);
        }
    }
    return returnVal;
}

int main(int argc, char const *argv[])
{
    // If the Width and hight aruments are not presnt, return
    if (argc < 2)
    {
        return 1;
    }
    
    // Set Width and hight
    imgWidth = atoi(argv[1]);
    imgHeight = atoi(argv[2]);

    // If the Width change is supplied, remember it 
    if (argc > 3 && strcmp(argv[3], "d") == false)
    {
        widthChange = atof(argv[3]);
    }
    
    // If the Height change is supplied, remember it
    if (argc > 4 && strcmp(argv[4], "d") == false)
    {
        heightChange = atof(argv[4]);
    }
         
    // makes sure we can open the output file
    std::ofstream myImage("mandelbrot.ppm");
    if (myImage.is_open())
    {
        myImage.close(); // close it for more ram

        std::string data = threadLoop(0, imgHeight, imgWidth); // call a loop of entire image set (for testing)
        std::ofstream myImage("mandelbrot.ppm"); // open the output file for writing
       
        myImage << "P3\n" << imgWidth << " " << imgHeight << " 255\n"; // write metadata
        myImage << data; // write data
        myImage.close(); // close the output file
    }
    else
    {
        // write error to console
        std::cout << "Could not open the file";
        return -1;
    }
    return 0;
}

