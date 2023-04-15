# Image Compressor

## Overview
This is an image compressor that utilizes data structures like hashing, binary tree, minimum queue, and linked list to compress images. The program reads pixel values and stores them in a matrix. Then, it counts all of the frequency of every reoccurring RGB value and stores it. The pixel values and their frequencies are then used in a priority queue. The priority queue is used to output values into a binary tree. This binary tree is then traversed while adding a ‘1’ when it goes to the right node and a ‘0’ while going to the left node to return a binary tree at each leaf node. This binary code becomes the code for that respective RGB value, which is stored in the compressed file.

## Data Structures Used
- Hashing: to store the RGB values and their frequencies
- Binary Tree: to represent the Huffman coding tree
- Minimum Queue: to build the Huffman coding tree
- Linked List: to store the compressed binary code

## Requirements
- C++ Compiler

## Credits
This project was created by Shehryar Ahmad as a project for Data Structures And Algorithms Lab.

