#pragma once

#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <map>

class ConfigFile {
private:
	bool m_loaded;
	std::string m_location;
	std::map<std::string, std::string> m_values;

public:
	ConfigFile();
	ConfigFile(const std::string &filename);
	bool load(const std::string &filename);
	bool loaded();
	const std::string &getLocation();
	bool valueExists(const std::string &name);
    	std::pair<std::string, bool> getValueString(const std::string &name);
    	std::pair<bool, bool> getValueBool(const std::string &name);
    	std::pair<int, bool> getValueInt(const std::string &name);
    	std::pair<float, bool> getValueFloat(const std::string &name);
	~ConfigFile();
};

