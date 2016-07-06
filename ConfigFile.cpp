#include "ConfigFile.h"


ConfigFile::ConfigFile() {

}

ConfigFile::ConfigFile(const std::string &filename) {
	load(filename);
}

bool ConfigFile::load(const std::string &filename) {
	m_loaded = false;
	std::ifstream file(filename);
	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			auto delimiter = line.find('=');
			if (delimiter == std::string::npos) {
				return false;
			}
			m_values[line.substr(0, delimiter)] = line.substr(delimiter + 1, line.size());
		}
		m_location = filename.substr(0, filename.rfind('/') + 1);
		m_loaded = true;
		return true;
	}
	return false;
}

bool ConfigFile::loaded() {
	return m_loaded;
}

const std::string &ConfigFile::getLocation() {
	return m_location;
}

bool ConfigFile::valueExists(const std::string &name) {
	return m_values.find(name) != m_values.end();
}

std::pair<std::string, bool> ConfigFile::getValueString(const std::string &name) {
	if (valueExists(name)) {
		return std::make_pair(m_values[name], true);
	}
	return std::make_pair("", false);
}

std::pair<bool, bool> ConfigFile::getValueBool(const std::string &name) {
	if (valueExists(name)) {
		std::string value = m_values[name];
		std::transform(value.begin(), value.end(), value.begin(), ::tolower);
		if (m_values[name] == "true" || m_values[name] == "1") {
			return std::make_pair(true, true);
		}
		else if (m_values[name] == "false" || m_values[name] == "0") {
			return std::make_pair(false, true);
		}
	}
	return std::make_pair(false, false);
}

std::pair<int, bool> ConfigFile::getValueInt(const std::string &name) {
	if (valueExists(name)) {
		try {
			return std::make_pair(std::stoi(m_values[name]), true);
		}
		catch(...) {
			MessageBoxA(NULL, "Invalid argument (ConfigFile::getValueInt)", "Something bad happened.", MB_OK | MB_ICONERROR);
		}
	}
	return std::make_pair(0, false);
}

std::pair<float, bool> ConfigFile::getValueFloat(const std::string &name) {
	if (valueExists(name)) {
		try {
			return std::make_pair(std::stof(m_values[name]), true);
		} catch(...) {
			MessageBoxA(NULL, "Invalid argument (ConfigFile::getValueFloat)", "Something bad happened.", MB_OK | MB_ICONERROR);
		}
	}
	return std::make_pair(0.0f, false);
}

ConfigFile::~ConfigFile() {

}
