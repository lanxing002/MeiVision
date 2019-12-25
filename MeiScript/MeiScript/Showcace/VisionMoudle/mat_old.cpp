#include "mat_old.h"

namespace vision {
	Plane::Plane(const size_t row = 0, const size_t column = 0){
		data.resize(row);
		for (auto c : data)
			c.resize(column);  // allocate data;
	}

	Mat_old::Mat_old(const string& filename) {
		ifstream fin(filename, ifstream::binary);
		read_byte(fin);
	}

	Mat_old::Mat_old(size_t dim, size_t row, size_t column)
	:dim(dim), row_size(row), column_size(column) {
		for (int i = 0; i < dim; i++) {
			data.emplace_back(row, column);
		}
	}

	void Mat_old::read_byte(ifstream& fin) {
		char header[54];
		fin.read(header, 54);
		file_header.bfOffBits = *(__int32*)(header + 10);
		bmp_header.biWidth = *(__int32*)(header + 18);
		bmp_header.biHeight = *(__int32*)(header + 22);
		bmp_header.biSizeImage = *(__int32*)(header + 34);

		//fin.read((char*)(&file_header), sizeof(file_header));
		//fin.read((char*)(&bmp_header), sizeof(bmp_header));
		//__int32* t = (__int32*)(&file_header + 2);

		data.resize(3);
		for (auto& c : data)
			c.resize(bmp_header.biHeight, bmp_header.biWidth);

		auto& R_plane = data[0];
		auto& G_plane = data[1];
		auto& B_plane = data[2];


		fin.seekg(file_header.bfOffBits, fin.beg);
		vector<char> img_data(bmp_header.biSizeImage);
		fin.read(img_data.data(), img_data.size());


		for(int i = 0; i < bmp_header.biHeight; i++)
			for (int j = 0; j < bmp_header.biWidth; j++) {
				size_t pixel_offset = i * (int)bmp_header.biWidth + j * 3;
				R_plane[i][j] = img_data[pixel_offset + 0];
				G_plane[i][j] = img_data[pixel_offset + 1];
				B_plane[i][j] = img_data[pixel_offset + 2];
			}
		return;
	}
}


