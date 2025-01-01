#pragma once


#include<string>
#include <vector>
#include <cstdint>
#include <dcmtk/dcmdata/dctk.h>



namespace Inspectis
{
	struct BlobMetadata
	{
		int height = 0;
		int	width = 0;
		int channels = 0;
		std::vector<unsigned char> pixelData;
	};
	
	class Converter
	{
	public:
		Converter(const std::vector<std::byte> blob);
		BlobMetadata getBlobMetadata();
	
	private:
		const std::vector<std::byte> m_blob;
	
	};
}
