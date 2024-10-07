
#include "PngProc.h"
#include <string.h>
#include <stdio.h>
#include <iostream>

using namespace std;

void ImageProcessingGray(unsigned char* pOut
	, unsigned char* pIn
	, size_t nWidth
	, size_t nHeight);

void FloydSteinberg(unsigned char* pOut
	, unsigned char* pIn
	, size_t nWidth
	, size_t nHeight
	, size_t n);

void FloydSteinbergEvenOdd(unsigned char* pOut
	, unsigned char* pIn
	, size_t nWidth
	, size_t nHeight
	, size_t n); 

void Stucki(unsigned char* pOut
	, unsigned char* pIn
	, size_t nWidth
	, size_t nHeight
	, size_t n);

int main(int argc, char* argv[])
{

	class CBitsPtrGuard
	{
	public:
		CBitsPtrGuard(unsigned char** pB) : m_ppBits(pB) { }
		~CBitsPtrGuard() { if (*m_ppBits) delete* m_ppBits, * m_ppBits = 0; }
	protected:
		unsigned char** m_ppBits;
	};
	//printf(argv[1]);
	//printf(argv[2]);
	//std::cout << argc << std::endl;
	//std::cout << argv[1] << std::endl;
	// parse input parameters
	char	szInputFileName[256];
	char    szOutputFileName[256];
	if (argc < 2)
		printf("\nformat: pngtest <input_file> [<output_file>]");
	else
	{
		strcpy(szInputFileName, argv[1]);

		if (argc > 2)
			strcpy(szOutputFileName, argv[2]);
		else
		{
			strcpy(szOutputFileName, szInputFileName);
			strcat(szOutputFileName, "_out.png");
		}
	}


	size_t nReqSize = NPngProc::readPngFile(szInputFileName, 0, 0, 0, 0);
	if (nReqSize == NPngProc::PNG_ERROR)
	{
		printf("\nError ocured while pngfile was read");
		return -1;
	}


	unsigned char* pInputBits = new unsigned char[nReqSize];
	if (!pInputBits)
	{
		printf("\nCan't allocate memory for image, required size is %u", nReqSize);
		return -1;
	}
	CBitsPtrGuard InputBitsPtrGuard(&pInputBits);


	unsigned char* pOutputBits = new unsigned char[nReqSize];
	if (!pOutputBits)
	{
		printf("\nCan't allocate memory for image, required size is %u", nReqSize);
		return -1;
	}


	CBitsPtrGuard OutputBitsPtrGuard(&pOutputBits);

	size_t nWidth, nHeight;
	unsigned int nBPP;

	size_t nRetSize = NPngProc::readPngFileGray(szInputFileName, pInputBits, &nWidth, &nHeight/*, &nBPP*/);
	nBPP = 8;


	// ASSERT(nRetSize == nReqSize);

	// TODO: image processing 
	//ImageProcessingGray(pOutputBits, pInputBits, nWidth, nHeight);
	size_t n = 2;
	FloydSteinbergEvenOdd(pOutputBits, pInputBits, nWidth, nHeight, n);


	if (NPngProc::writePngFile(szOutputFileName, pOutputBits, nWidth, nHeight, nBPP) == NPngProc::PNG_ERROR)
	{
		printf("\nError ocuured during png file was written");
		return -1;
	}


	return 0;
}

void ImageProcessingGray(unsigned char* pOut
	, unsigned char* pIn
	, size_t nWidth
	, size_t nHeight)
{
	// ASSERT(pOut != NULL && pIn != NULL && nWidth > 0 && nHeight > 0)

	// for example, inversion of image
	for (size_t y = 0; y < nHeight; ++y)
	{
		for (size_t x = 0; x < nWidth; ++x)
		{
			*pOut++ = 255 - *pIn++;
		}
	}
	return;
}


void FloydSteinberg(unsigned char* pOut
	, unsigned char* pIn
	, size_t nWidth
	, size_t nHeight
	, size_t n)
{
	int new_values[256];
	for (int i = 0; i < 256; ++i) {
		new_values[i] = int(int(i * (1 << n - 1) / 255 + 0.5) * 255 / (1 << n - 1));
	}
	for (size_t y = 0; y < nHeight; ++y)
	{
		for (size_t x = 0; x < nWidth; ++x)
		{
			size_t numberPixel = y * nWidth + x;
			int new_value = new_values[pIn[numberPixel]];
			int error_value = pIn[numberPixel] - new_value;
			pOut[numberPixel] = new_value;
			if (y < nHeight - 1)
			{
				pIn[(y + 1) * nWidth + x] = max(0, min(255, pIn[(y + 1) * nWidth + x] + 5 * error_value / 16));
				if (x < nWidth - 1)
				{
					pIn[(y + 1) * nWidth + x + 1] = max(0, min(255, pIn[(y + 1) * nWidth + x + 1] + 1 * error_value / 16));
				}
				if (x > 0)
				{
					pIn[(y + 1) * nWidth + x - 1] = max(0, min(255, pIn[(y + 1) * nWidth + x - 1] + 3 * error_value / 16));
					
				}
			}
			if (x < nWidth - 1)
			{
				pIn[numberPixel + 1] = max(0, min(255, pIn[numberPixel + 1] + 7 * error_value / 16));
			}
		}
	}
	return;
}



void FloydSteinbergEvenOdd(unsigned char* pOut
	, unsigned char* pIn
	, size_t nWidth
	, size_t nHeight
	, size_t n)
{
	int new_values[256];
	for (int i = 0; i < 256; ++i) {
		new_values[i] = int(int(i * (1 << n - 1) / 255 + 0.5) * 255 / (1 << n - 1));
	}
	for (size_t y = 0; y < nHeight; ++y)
	{
		if (!(y&1))
		{
			for (size_t x = 0; x < nWidth; ++x)
			{
				size_t numberPixel = y * nWidth + x;
				int new_value = new_values[pIn[numberPixel]];
				int error_value = pIn[numberPixel] - new_value;
				pOut[numberPixel] = new_value;
				if (y < nHeight - 1)
				{
					pIn[(y + 1) * nWidth + x] = max(0, min(255, pIn[(y + 1) * nWidth + x] + 5 * error_value / 16));
					if (x < nWidth - 1)
					{
						pIn[(y + 1) * nWidth + x + 1] = max(0, min(255, pIn[(y + 1) * nWidth + x + 1] + 1 * error_value / 16));
					}
					if (x > 0)
					{
						pIn[(y + 1) * nWidth + x - 1] = max(0, min(255, pIn[(y + 1) * nWidth + x - 1] + 3 * error_value / 16));
					}
				}
				if (x < nWidth - 1)
				{
					pIn[numberPixel + 1] = max(0, min(255, pIn[numberPixel + 1] + 7 * error_value / 16));
				}
			}
		}
		else
		{
			for (int x = nWidth - 1; x >= 0; --x)
			{
				size_t numberPixel = y * nWidth + x;
				int new_value = new_values[pIn[numberPixel]];
				int error_value = pIn[numberPixel] - new_value;
				pOut[numberPixel] = new_value;
				if (y < nHeight - 1)
				{
					pIn[(y + 1) * nWidth + x] = max(0, min(255, pIn[(y + 1) * nWidth + x] + 5 * error_value / 16));
					if (x > 0)
					{
						pIn[(y + 1) * nWidth + x - 1] = max(0, min(255, pIn[(y + 1) * nWidth + x - 1] + 1 * error_value / 16));
					}
					if (x < nWidth - 1)
					{
						pIn[(y + 1) * nWidth + x + 1] = max(0, min(255, pIn[(y + 1) * nWidth + x + 1] + 3 * error_value / 16));
					}
				}
				if (x > 0)
				{
					pIn[numberPixel - 1] = max(0, min(255, pIn[numberPixel - 1] + 7 * error_value / 16));
				}
			}
		}
	}
	return;
}


void Stucki(unsigned char* pOut
	, unsigned char* pIn
	, size_t nWidth
	, size_t nHeight
	, size_t n)
{
	int new_values[256];
	for (int i = 0; i < 256; ++i) {
		new_values[i] = int(int(i * (1 << n - 1) / 255 + 0.5) * 255 / (1 << n - 1));
	}
	for (size_t y = 0; y < nHeight; ++y)
	{
		for (size_t x = 0; x < nWidth; ++x)
		{
			size_t numberPixel = y * nWidth + x;
			int new_value = new_values[pIn[numberPixel]];
			int error_value = pIn[numberPixel] - new_value;
			pOut[numberPixel] = new_value;
			if (y < nHeight - 1)
			{
				pIn[(y + 1) * nWidth + x] = max(0, min(255, pIn[(y + 1) * nWidth + x] + 8 * error_value / 42));
				if (x < nWidth - 1)
				{
					pIn[(y + 1) * nWidth + x + 1] = max(0, min(255, pIn[(y + 1) * nWidth + x + 1] + 4 * error_value / 42));
					if (x < nWidth - 2)
					{
						pIn[(y + 1) * nWidth + x + 2] = max(0, min(255, pIn[(y + 1) * nWidth + x + 2] + 2 * error_value / 42));
					}
				}

				if (x > 0)
				{
					pIn[(y + 1) * nWidth + x - 1] = max(0, min(255, pIn[(y + 1) * nWidth + x - 1] + 4 * error_value / 42));
					if (x > 1)
					{
						pIn[(y + 1) * nWidth + x - 2] = max(0, min(255, pIn[(y + 1) * nWidth + x - 2] + 2 * error_value / 42));
					}
				}

				if (y < nHeight - 2)
				{
					pIn[(y + 2) * nWidth + x] = max(0, min(255, pIn[(y + 2) * nWidth + x] + 4 * error_value / 42));
					if (x < nWidth - 1)
					{
						pIn[(y + 2) * nWidth + x + 1] = max(0, min(255, pIn[(y + 2) * nWidth + x + 1] + 2 * error_value / 42));
						if (x < nWidth - 2)
						{
							pIn[(y + 2) * nWidth + x + 2] = max(0, min(255, pIn[(y + 2) * nWidth + x + 2] + 1 * error_value / 42));
						}
					}
					if (x > 0)
					{
						pIn[(y + 2) * nWidth + x - 1] = max(0, min(255, pIn[(y + 2) * nWidth + x - 1] + 2 * error_value / 42));
						if (x > 1)
						{
							pIn[(y + 2) * nWidth + x - 2] = max(0, min(255, pIn[(y + 2) * nWidth + x - 2] + 1 * error_value / 42));
						}
					}
				}

			}

			if (x < nWidth - 1)
			{
				pIn[numberPixel + 1] = max(0, min(255, pIn[numberPixel + 1] + 8 * error_value / 42));
				if (x < nWidth - 2)
				{
					pIn[numberPixel + 2] = max(0, min(255, pIn[numberPixel + 2] + 4 * error_value / 42));
				}
			}
			pOut[numberPixel] = new_value;
		}
	}
	return;
}
