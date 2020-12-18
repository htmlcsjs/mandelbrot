#include <complex>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Declare global varibles
int width;
int height;
double widthChange = -1.5;
double heightChange = -0.5;

/* I dont really know how this works */
int value(int x, int y, double changeWidth, double changeHeight)
{
    std::complex<float> point((float)x / width + changeWidth, (float)y / height + changeHeight);
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

int main(int argc, char const *argv[])
{
    // If the Width and hight aruments are not presnt, return
    if (argc < 2)
    {
        return 1;
    }
    
    // Set Width and hight
    width = atoi(argv[1]);
    height = atoi(argv[2]);

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
        
    // count the rows for a percent done
    float rowCount = 0.0;
    
    // makes sure we can open the output file
    std::ofstream myImage("mandelbrot.ppm");
    if (myImage.is_open())
    {
        myImage.close(); // close it for more ram

        std::vector<std::vector<std::string>> imgData; // declare the 2D image data vector

        for (int y = 0; y < height; y++)
        {
            std::vector<std::string> rowData; // row data vector

            for (int x = 0; x < width; x++)
            {
                int val = value(x, y, widthChange, heightChange);
                std::string toAppend = std::to_string(val) + " 0 0" + "\n";
                rowData.push_back(toAppend); // write the pixel data to rowData
            }
            imgData.push_back(rowData); // write rowData to imgData

            rowCount++; // increse rowCount
            std::cout << (rowCount/height)*100 << "%\n"; // print percentage done
        }

        std::ofstream myImage("mandelbrot.ppm"); // open the output file for writeing
        
        myImage << "P3\n" << width << " " << height << " 255\n"; // write metadata

        // loop over each vector, then cell and write it
        for (size_t i = 0; i < imgData.size(); i++)
        {
            for (size_t j = 0; j < imgData[i].size(); j++)
            {
                myImage << imgData[i][j];
            }
        }
        
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

