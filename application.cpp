/**
 * @file application.cpp
 * @author Shehryar Ahmad
 * @brief This application is is the core of our image compression technique. It takes an image, breaks it down into its pixel components and then uses the widely used huffman encoding technique to output a compressed data file, we use the SFML library to use its image reading data structures to read an image directly and then apply our huffman encoding
 * @version 0.1
 * @date 2022-12-28
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "huffman.h"
using namespace std;
using namespace sf;

int main()
{
    // Image is being read from a png file below
    Image photo;
    HuffmanTree<int> t;
    HashMap<int> hf;

    if (!photo.loadFromFile("sample.png"))
        return -1;

    Vector2<unsigned int> size = photo.getSize();
    int height = size.y, width = size.x;

    // Create an array of the Color object ro store pixel values in RGB
    Color **photoArr = new Color *[width];
    for (int i = 0; i < width; i++)
        photoArr[i] = new Color[height];

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
            photoArr[i][j] = photo.getPixel(i, j);
    }

    // Calculating the pixel frequencies of each RGB value and storing then in a HashMap
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            Color temp = photoArr[i][j];
            int vals[3] = {temp.r, temp.g, temp.b};

            if (hf.search(vals))
            {
                int *freq = hf.search(vals);
                hf.insert(vals, *(freq) + 1);
            }
            else
                hf.insert(vals, 1);
        }
    }

    // Creating a list of all frequencies and making a tree of 
    // them that uses huffman encoding to return their binary values
    listNode<int> *node = hf.traverse();

    while (node)
    {
        t.insert(node->pix, node->code);
        node = node->prev;
    }
    t.buildTree();
    t.makeHuffcode();

    // Output the compressed values as in the image file in a compressed data file
    ofstream file("compressed.data");

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            int col[3] = {photoArr[i][j].r, photoArr[i][j].g, photoArr[i][j].b};
            string code = t.search(col);
            file << code;
        }
        file << '\n';
    }

    return 0;
}