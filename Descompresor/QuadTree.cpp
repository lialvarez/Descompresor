#include "QuadTree.h"
#include <cmath>
#include <boost/algorithm/string/replace.hpp>

#define PIXEL_SIZE	4

typedef enum { R, G, B, A }pixel;

void QuadTree::QTDecompress(std::string fileName)
{
	compressedFile.open(fileName.c_str(), std::ifstream::binary);
	if (compressedFile.fail())
	{
		return;
	}
	unsigned char aux;
	aux = compressedFile.get();
	totSide = exp2(aux);

	//Inicializo el rawData TODO en cero
	rawData.clear();
	for (unsigned int i = 0; i < 4 * totSide * totSide; i++)
	{
		rawData.push_back(0);
	}

	quadTree(0, 0, totSide);
	compressedFile.close();

	std::string outFileName(fileName);
	boost::replace_all(outFileName, ".eda", " - Decompressed.png");

	unsigned error = lodepng::encode(outFileName, rawData, totSide, totSide);
	if (error)
	{
		std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
	}
	rawData.clear();
}

void QuadTree::quadTree(unsigned int x0, unsigned int y0, unsigned int side)
{
	unsigned char aux = compressedFile.get();
	unsigned char rPixel, gPixel, bPixel, alpha;
	if (compressedFile.good())
	{
		switch (aux)
		{
		case '1':
			quadTree(x0, y0, side / 2);
			quadTree(x0 + side / 2, y0, side / 2);
			quadTree(x0, y0 + side / 2, side / 2);
			quadTree(x0 + side / 2, y0 + side / 2, side / 2);
			break;
		case '0':
			rPixel = compressedFile.get();
			gPixel = compressedFile.get();
			bPixel = compressedFile.get();
			alpha = compressedFile.get();
			for (unsigned int i = y0; i < y0 + side; i++)
			{
				for (unsigned int j = x0; j < x0 + side; j++)
				{
					rawData[(i*totSide + j) * PIXEL_SIZE + R] = rPixel;
					rawData[(i*totSide + j) * PIXEL_SIZE + G] = gPixel;
					rawData[(i*totSide + j) * PIXEL_SIZE + B] = bPixel;
					rawData[(i*totSide + j) * PIXEL_SIZE + A] = alpha;
				}
			}
			return;
		default:
			break;
		}
	}
}