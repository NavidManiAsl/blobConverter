#include "pch.h"

#include "Converter.h"
#include <stdexcept>
#include <jpeglib.h>
#include <vector>


 Inspectis::BlobMetadata Inspectis::Converter::getBlobMetadata(std::vector<std::byte> byteVector)
{
	BlobMetadata metadata;
	
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;

	cinfo.err = jpeg_std_error(&jerr);
	jpeg_CreateDecompress(&cinfo, JPEG_LIB_VERSION, sizeof(jpeg_decompress_struct));

	try
	{
		jpeg_mem_src(&cinfo, reinterpret_cast<const unsigned char*>(byteVector.data()), byteVector.size());
		if (jpeg_read_header(&cinfo, TRUE) != JPEG_HEADER_OK) {
			throw std::runtime_error("Failed to read JPEG header.");
		}
		// Start decompression
		jpeg_start_decompress(&cinfo);

		// Retrieve image dimensions and channels
		metadata.width = cinfo.output_width;
		metadata.height = cinfo.output_height;
		metadata.channels = cinfo.output_components;

		// Allocate buffer for uncompressed data
		size_t dataSize = metadata.width * metadata.height * metadata.channels;
		std::vector<unsigned char> data;
		data.resize(dataSize);

		// Read scanlines
		unsigned char* buffer = data.data();
		while (cinfo.output_scanline < cinfo.output_height) {
			unsigned char* rowPointer[1] = { buffer + cinfo.output_scanline * metadata.width * metadata.channels };
			jpeg_read_scanlines(&cinfo, rowPointer, 1);
		}
		metadata.pixelData.resize(dataSize);
		std::transform(data.begin(), data.end(), metadata.pixelData.begin(),
			[](unsigned char c) { return static_cast<std::byte>(c); });

		// Finish decompression
		jpeg_finish_decompress(&cinfo);
		jpeg_destroy_decompress(&cinfo);
		}
	catch (const std::exception&)
	{
		jpeg_destroy_decompress(&cinfo);
		throw; // Rethrow the exception after cleanup
	}

	return metadata;
}
