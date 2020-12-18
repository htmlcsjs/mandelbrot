#include <complex>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int width;
int height;
double widthChange = -1.5;
double heightChange = -0.5;

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
    if (argc < 2)
    {
        return 1;
    }
    
    width = atoi(argv[1]);
    height = atoi(argv[2]);
    if (argc > 3 && strcmp(argv[3], "d") == false)
    {
        widthChange = atof(argv[3]);
    }
    
    
    if (argc > 4 && strcmp(argv[4], "d") == false)
    {
        heightChange = atof(argv[4]);
    }
        
    
    std::ofstream myImage("mandelbrot.ppm");
    float rowCount = 0.0;
    if (myImage.is_open())
    {
        myImage << "P3\n" << width << " " << height << " 255\n";
        std::vector<std::vector<std::string>> imgData;
        for (int y = 0; y < height; y++)
        {
            std::vector<std::string> rowData;
            for (int x = 0; x < width; x++)
            {
                int val = value(x, y, widthChange, heightChange);
                std::string toAppend = std::to_string(val) + " 0 0" + "\n";
                rowData.push_back(toAppend);
            }
            imgData.push_back(rowData);
            rowCount++;
            std::cout << (rowCount/height)*100 << "%\n";
        }
        for (size_t i = 0; i < imgData.size(); i++)
        {
            for (size_t j = 0; j < imgData[i].size(); j++)
            {
                myImage << imgData[i][j];
            }
        }
        myImage.close();
    }
    else
    {
        std::cout << "Could not open the file";
        return -1;
    }
    return 0;
}

