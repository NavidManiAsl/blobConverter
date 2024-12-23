#include "pch.h"
#include "Converter.h"
#include <stdexcept>

Inspectis::Converter::Converter(const std::vector<std::byte>& blob) : m_blob(blob)
{
}

Inspectis::BlobMetadata Inspectis::Converter::getBlobMetadata()
{
	BlobMetadata metadata;
	int width, height, channels;

	// Decode the blob data to get metadata
	const unsigned char* blobData = reinterpret_cast<const unsigned char*>(m_blob.data());
	unsigned char* pixelData = stbi_load_from_memory(blobData, static_cast<int>(m_blob.size()),
		&width, &height, &channels, 0);

	if (!pixelData) {
		// Handle decoding failure
		throw std::runtime_error("Failed to decode image blob: " + std::string(stbi_failure_reason()));
	}

	// Populate metadata structure
	metadata.row = height;
	metadata.column = width;
	metadata.channels = channels;

	// Free the pixel data as we only need metadata
	stbi_image_free(pixelData);

	
	return metadata;
}
