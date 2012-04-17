#include "TemporaryConfigFile.h"
#include <Windows.h>
#include <boost/filesystem.hpp>
#include <common/StringHelper.h>

TemporaryConfigFile::TemporaryConfigFile(const std::string& serializedConfig) {
	wchar_t tmpPath[MAX_PATH];
	wchar_t tmpFileName[MAX_PATH];
	GetTempPath(MAX_PATH, tmpPath);
	if (!GetTempFileName(tmpPath, L"h4x0r", 0, tmpFileName))
		throw std::runtime_error("Error while trying to serialize configuration to file: unable to get path for temp file.");
	fileName_ = (const char*)uberstealth::UnicodeToString(tmpFileName);
	std::ofstream ofs(fileName_.c_str());
	ofs.write(serializedConfig.c_str(), serializedConfig.length());
}

TemporaryConfigFile::~TemporaryConfigFile() {
	try {
		boost::filesystem::remove(fileName_);
	} catch (const std::exception& exception) {
		std::cerr << exception.what();
	}
}
