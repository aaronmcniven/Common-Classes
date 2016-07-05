#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

class ConfigFile {
private:
	std::string m_location;
	std::vector<std::string> m_names;
	std::vector<std::string> m_values;
	std::ifstream file;

public:
	ConfigFile();
	ConfigFile(const std::string &filename);
	bool load(const std::string &filename);
	std::string getLocation();
	bool valueExists(const std::string &name);
    std::string getValueString(const std::string &name);
    bool getValueBool(const std::string &name);
    int getValueInt(const std::string &name);
    float getValueFloat(const std::string &name);
	~ConfigFile();
};

