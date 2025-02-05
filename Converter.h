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
		std::vector<std::byte> pixelData;
	};
	
	class Converter
	{
	public:
		Converter()=default;
		static BlobMetadata getBlobMetadata(std::vector<std::byte>);
	
	
	
	};
}//namespace Inspectis
