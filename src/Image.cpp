#include "Image.hpp"
#include <fstream>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <memory>

Image::Image(std::string filepath) : m_filepath(filepath){}

Image::~Image(){
    // Delete our pixel data
    if(m_pixelData!=NULL){
        delete[] m_pixelData;
    }
}

/**
 * Loads the pixel data from a PPM image.
 * TODO: Expects a very specific version of PPM!
 *
 * @param flip a boolean indicating whether flip the pixels
 */
void Image::LoadPPM(bool flip){

    // Open an input file stream for reading a file
    std::ifstream ppmFile(m_filepath.c_str());

    // If our file successfully opens, begin to process it.
    if (ppmFile.is_open()){
        // line will store one line of input
        std::string line;
        // continue reading input until we reach the end of the file
        std::cout << "Reading in ppm file: " << m_filepath << std::endl;
        unsigned int iteration = 0;
        unsigned int pos = 0;
        while (getline(ppmFile,line)) {
            // Ignore comments in the file
            if (line[0]=='#') { continue; }
            if (line[0]=='P') { magicNumber = line; }
            else if (iteration==1) {

                char *token = strtok((char*)line.c_str(), " ");
                m_width = atoi(token);
                token = strtok(NULL, " ");
                m_height = atoi(token);
                std::cout << "PPM width,height=" << m_width << "," << m_height << "\n";

                if (m_width > 0 && m_height > 0) {
                    m_pixelData = new uint8_t[m_width*m_height*3];
                    if(m_pixelData==NULL){
                        std::cout << "Unable to allocate memory for ppm" << std::endl;
                        exit(1);
                     }
                } else {
                    std::cout << "PPM not parsed correctly, width and/or height dimensions are 0" << std::endl;
                    exit(1);
                }
            } else if(iteration==2) {
                // TODO: max color range is stored here
            } else {
                m_pixelData[pos] = (uint8_t)atoi(line.c_str());
                ++pos;
            }
            iteration++;
        }
        ppmFile.close();
    } else {
        std::cout << "Unable to open ppm file:" << m_filepath << std::endl;
    }

    // Flip all the pixels
    if (flip) {
        // Copy all the data to a temporary stack-allocated array
        uint8_t* copyData = new uint8_t[m_width*m_height*3];
        for(int i =0; i < m_width*m_height*3; ++i){
            copyData[i]=m_pixelData[i];
        }
        // memcpy(copyData,m_pixelData,(m_width*m_height*3)*sizeof(uint8_t));
        unsigned int pos = (m_width*m_height*3)-1;
        for(int i =0; i < m_width*m_height*3; i+=3){
            m_pixelData[pos]=copyData[i+2];
            m_pixelData[pos-1]=copyData[i+1];
            m_pixelData[pos-2]=copyData[i];
            pos-=3;
        }
        delete[] copyData;
    }
}

// Sets a pixel to a specific color
void Image::SetPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b){
  if(x > m_width || y > m_height){
      return;
  } else {
      // std::cout << "modifying pixel at " << x << "," << y << "from (" <<
      //          (int)color[x*y] << "," << (int)color[x*y+1] << "," << (int)color[x*y+2] << ")";
      m_pixelData[(x*3)+m_height*(y*3)] = r;
      m_pixelData[(x*3)+m_height*(y*3)+1] = g;
      m_pixelData[(x*3)+m_height*(y*3)+2] = b;
      // std::cout << " to (" << (int)color[x*y] << "," << (int)color[x*y+1] << "," << (int)color[x*y+2] << ")" << std::endl;
  }
}

void Image::PrintPixels(){
    for(int x = 0; x <  m_width*m_height*3; ++x){
        std::cout << " " << (int)m_pixelData[x];
    }
    std::cout << "\n";
}

uint8_t* Image::GetPixelDataPtr(){
    return m_pixelData;
}
