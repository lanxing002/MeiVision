#pragma once
#include <QImage>
#include <string>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <windows.h>

using namespace std;

namespace vision {
	
	typedef unsigned __int8 pixel_t;
	// a palne data for read/write
	class Plane {
	public:
		Plane(const size_t row, const size_t columnf);
		virtual ~Plane() {};

		vector<pixel_t>& operator[](size_t index) {
			if (index >= data.size())
				throw std::out_of_range("out range of row");
			return data[index];
		}

		void resize(size_t row, size_t column) {
			data.resize(row);
			for (auto& t : data)
				t.resize(column);
		}
		size_t row_len() { return data.size(); }
		size_t column_len() { return data[0].size(); }

	private:
		vector<vector<pixel_t>> data;
		//size_t row_size, column_size;  planesize = row_size * column_size;
	};

	class Mat_old {
	public:
		Mat_old(const string& filename);
		Mat_old(size_t dim, size_t row_size, size_t column_size);
		
		~Mat_old() {};

		Plane& operator[](size_t index) {
			if (index >= dim)
				throw std::out_of_range("out range of dim");
			return this->data[index];
		}

		struct BmpFileHeader {
			__int16 bfType;
			__int32 bfSize;
			__int16 bfReserved1;
			__int16 bfReserved2;
			__int32 bfOffBits;
		};

		struct BmpHeader {
			__int32 biSize;
			__int16 biWidth;
			__int16 biHeight;
			__int16 biPlanes;
		    __int16 biBitCount;
			__int32 biCompression;
			__int32 biSizeImage;
			__int16 biXPelsPerMeter;
			__int16 biYPelsPerMeter;
			__int32 biClrUsed;
			__int32 biClrImportant;
		};

	private:
		void read_byte(ifstream& fin);
		vector<Plane> data;
		BmpFileHeader file_header;
		BmpHeader bmp_header;
		//vector<char> header_data;
		size_t dim, row_size, column_size;
	};

	class Mat : public QImage {
	public:
		Mat(string& filename):
		QImage(QString::fromStdString(filename)){
			
		}

		QRgb at(int x, int y) const { return this->pixel(x, y); }

		virtual ~Mat() {  }

	private:
	};
}

namespace LuaFunction {
	
}