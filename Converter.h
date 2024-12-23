#pragma once
#include "stb_image.h"
#include<string>
#include <vector>
#include <cstdint>
#include <dcmtk/dcmdata/dctk.h>



namespace Inspectis
{
	struct BlobMetadata
	{
		int row = 0;
		int	column = 0;
		int channels = 0;
	};
	
	class Converter
	{
	public:
		Converter(const std::vector<std::byte>& blob);
		BlobMetadata getBlobMetadata();
	
	private:
		const std::vector<std::byte> m_blob;
	
	};
}
