#pragma once

#include <iostream>
#include <cstdlib>

#include <cryptopp/sha.h>
#include <cryptopp/filters.h>
#include <crypto++/base64.h>

namespace HashHelper
{
	inline std::string SHA256HashString(std::string aString)
	{
		std::string digest;
		CryptoPP::SHA256 hash;

		CryptoPP::StringSource foo(aString, true,
				new CryptoPP::HashFilter(hash,
					new CryptoPP::Base64Encoder (
						new CryptoPP::StringSink(digest), false)));

		return digest;
	}
}
