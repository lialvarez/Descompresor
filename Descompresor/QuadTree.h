#ifndef QUADTREE_H
#define QUADTREE_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <lodepng.h>

class QuadTree
{
public:
	void QTDecompress(std::string fileName);
private:
	void quadTree(unsigned int x0, unsigned int y0, unsigned int side);
	unsigned int totSide;
	std::vector<unsigned char> rawData;
	std::ifstream compressedFile;
};

#endif // !QUADTREE_H



