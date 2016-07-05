#include "ConfigFile.h"


ConfigFile::ConfigFile() {

}

ConfigFile::ConfigFile(const std::string &filename) {
	load(filename);
}

bool ConfigFile::load(const std::string &filename) {
	file.open(filename);
	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			int delimiter = line.find('=');
			m_names.push_back(line.substr(0, delimiter));
			m_values.push_back(line.substr(delimiter + 1, line.size()));
		}
		m_location = filename.substr(0, filename.rfind('/') + 1);
		return true;
	}
	return false;
}

std::string ConfigFile::getLocation() {
	return m_location;
}

bool ConfigFile::valueExists(const std::string &name) {
	for (size_t index = 0; index < m_names.size(); ++index) {
		if (name == m_names[index]) {
			return true;
		}
	}
	return false;
}

std::pair<std::string, bool> ConfigFile::getValueString(const std::string &name) {
	for (size_t index = 0; index < m_names.size(); ++index) {
		if (name == m_names[index]) {
			return std::make_pair(m_values[index], true);
		}
	}
	return std::make_pair("", false);
}

std::pair<bool, bool> ConfigFile::getValueBool(const std::string &name) {
	for (size_t index = 0; index < m_names.size(); ++index) {
		if (name == m_names[index]) {
			std::transform(m_values[index].begin(), m_values[index].end(), m_values[index].begin(), ::tolower);
			if (m_values[index] == "true" || m_values[index] == "1") {
				return std::make_pair(true, true);
			}
		}
	}
	return std::make_pair(false, false);
}

std::pair<int, bool> ConfigFile::getValueInt(const std::string &name) {
	for (size_t index = 0; index < m_names.size(); ++index) {
		if (name == m_names[index]) {
			return std::make_pair(atoi(m_values[index].c_str()), true);
		}
	}
	return std::make_pair(0, false);
}

std::pair<float, bool> ConfigFile::getValueFloat(const std::string &name) {
	for (size_t index = 0; index < m_names.size(); ++index) {
		if (name == m_names[index]) {
			return std::make_pair(static_cast<float>(atof(m_values[index].c_str())), true);
		}
	}
	return std::make_pair(0, false);
}

ConfigFile::~ConfigFile() {
	m_names.clear();
	m_values.clear();
}
