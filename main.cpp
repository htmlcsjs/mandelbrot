#include <complex>
#include <cstring>
#include <cmath>
#include <fstream>
#include <future>
#include <iostream>
#include <string>
#include <thread>
#include <vector>


// Declare global varibles
int imgWidth;
int imgHeight;
int iterations = 200;
int bailout = 16;
std::string threadMode;
double widthChange = -1.5;
double heightChange = -0.5;
double freqMult = (iterations/20)*5;
bool juliaSet = true;
double scale = 1;

/*double freqR = 1;
double freqG = 0.5;
double freqB = 0.12;*/

/*double freqR = .98;
double freqG = .91;
double freqB = .86;*/

double freqR = 1;
double freqG = .74;
double freqB = .11;

/* I dont really know how this works */
double mandelbrot(int x, int y, double changeWidth, double changeHeight)
{
    std::complex<double> z;
    std::complex<double> c;
    if (juliaSet)
    {
        std::complex<double> jz((float)(x / imgWidth) * scale + changeWidth, (float)(y / imgHeight) * scale + changeHeight);
        std::complex<double> jc(-0.52, 0.570);
        c = jc;
        z = jz;
    }
    else
    {
        std::complex<float> mc((float)(x / imgWidth) * scale + changeWidth, (float)(y / imgHeight) * scale + changeHeight);
        std::complex<float> mz(0, 0);
        c=mc;
        z=mz;
    }
    
    int nb_iter = 0;
    while (std::abs(z) < bailout && nb_iter <= iterations)
    {
        z = z * z + c;
        nb_iter++;
    }
    if (nb_iter < iterations)
    {
        double magsq = z.real()*z.real() + z.imag()*z.imag();
        return ((double)nb_iter - std::log(std::log(std::sqrt(magsq)) / std::log(bailout*2)) / (double)0.69314718055994529) / (double)iterations;
    }
    return 0;
}

double normalisedSin(double input)
{
    return (std::sin(input)+1)*0.5;
}

std::string threadLoop(int startY, int endY, int width)
{
    std::vector<std::vector<std::string>> imgData; // declare the 2D image data vector

    for (int y = startY; y < endY; y++)
    {
        std::vector<std::string> rowData; // row data vector

        for (int x = 0; x < width; x++)
        {
            double val = mandelbrot(x, y, widthChange, heightChange);
            int r = (int)(normalisedSin(val * freqR * freqMult)*255);
            int g = (int)(normalisedSin(val * freqG * freqMult)*255);
            int b = (int)(normalisedSin(val * freqB * freqMult)*255);
            std::string toAppend = std::to_string(r) + " " + std::to_string(g) + " "+ std::to_string(b) + "\n";
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

    // If the thread count is supplied, remember it
    if (argc > 3)
    {
        threadMode = argv[3];
    }
    
        
    // If the scale change is supplied, remember it
    if (argc > 4)
    {
        scale = atof(argv[4]);
    }
    
    // If the type is supplied, remember it 
    if (argc > 5 && strcmp(argv[5], "j") == false)
    {
        juliaSet = false;
    }
    else if (argc > 5 && strcmp(argv[5], "j") == true)
    {
        juliaSet = true;
    }
    // print freqMult
    std::cout << "freqMult is:" << freqMult << "\n";


    // makes sure we can open the output file
    std::ofstream myImage("mandelbrot.ppm");
    if (myImage.is_open())
    {
        myImage.close(); // close it for more ram

        std::string data;
        if (threadMode == "m")
        {
            // generate the 1st thread
            auto t1 = std::async(std::launch::async, threadLoop, 0, imgHeight / 12, imgWidth);                             
            // generate the 2nd thread
            auto t2 = std::async(std::launch::async, threadLoop, imgHeight / 12 + 1, imgHeight / 12 * 2, imgWidth);        
            //generate the 3rd thread
            auto t3 = std::async(std::launch::async, threadLoop, imgHeight / 12 * 2 + 1, imgHeight / 12 * 3, imgWidth);    
            // generate the 4th thread
            auto t4 = std::async(std::launch::async, threadLoop, imgHeight / 12 * 3 + 1, imgHeight / 12 * 4, imgWidth);    
            // generate the 5th thread
            auto t5 = std::async(std::launch::async, threadLoop, imgHeight / 12 * 4 + 1, imgHeight / 12 * 5, imgWidth);    
            // generate the 6th thread
            auto t6 = std::async(std::launch::async, threadLoop, imgHeight / 12 * 5 + 1, imgHeight / 12 * 6, imgWidth);    
            // generate the 7th thread
            auto t7 = std::async(std::launch::async, threadLoop, imgHeight / 12 * 6 + 1, imgHeight / 12 * 7, imgWidth);    
            // generate the 8th thread
            auto t8 = std::async(std::launch::async, threadLoop, imgHeight / 12 * 7 + 1, imgHeight / 12 * 8, imgWidth);    
            // generate the 9th thread
            auto t9 = std::async(std::launch::async, threadLoop, imgHeight / 12 * 8 + 1, imgHeight / 12 * 9, imgWidth);    
            // generate the 10th thread
            auto t10 = std::async(std::launch::async, threadLoop, imgHeight / 12 * 9 + 1, imgHeight / 12 * 10, imgWidth);  
            // generate the 11th thread
            auto t11 = std::async(std::launch::async, threadLoop, imgHeight / 12 * 10 + 1, imgHeight / 12 * 11, imgWidth); 
            // generate the 12th thread
            auto t12 = std::async(std::launch::async, threadLoop, imgHeight / 12 * 11 + 1, imgHeight + 11, imgWidth); 

            data = t1.get();
            data = data + t2.get();            
            data = data + t3.get();
            data = data + t4.get();
            data = data + t5.get();
            data = data + t6.get();
            data = data + t7.get();
            data = data + t8.get();
            data = data + t9.get();
            data = data + t10.get();
            data = data + t11.get();
            data = data + t12.get();            
        }
        else
        {
            data = threadLoop(0, imgHeight, imgWidth); 
        }
        

            

        std::ofstream myImage("mandelbrot.ppm"); // open the output file for writing

        myImage << "P3\n" << imgWidth << " " << imgHeight << " 255\n"; // write metadata
        myImage << data;                                               // write data
        myImage.close();                                               // close the output file
    }
    else
    {
        // write error to console
        std::cout << "Could not open the file";
        return -1;
    }
    return 0;
}

