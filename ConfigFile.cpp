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

std::string ConfigFile::getValueString(const std::string &name) {
	for (size_t index = 0; index < m_names.size(); ++index) {
		if (name == m_names[index]) {
			return m_values[index];
		}
	}
	return 0;
}

bool ConfigFile::getValueBool(const std::string &name) {
	for (size_t index = 0; index < m_names.size(); ++index) {
		if (name == m_names[index]) {
			std::transform(m_values[index].begin(), m_values[index].end(), m_values[index].begin(), ::tolower);
			if (m_values[index] == "true" || m_values[index] == "1") {
				return true;
			}
		}
	}
	return false;
}

int ConfigFile::getValueInt(const std::string &name) {
	for (size_t index = 0; index < m_names.size(); ++index) {
		if (name == m_names[index]) {
			return atoi(m_values[index].c_str());
		}
	}
	return 0;
}

float ConfigFile::getValueFloat(const std::string &name) {
	for (size_t index = 0; index < m_names.size(); ++index) {
		if (name == m_names[index]) {
			return static_cast<float>(atof(m_values[index].c_str()));
		}
	}
	return 0;
}

ConfigFile::~ConfigFile() {
	m_names.clear();
	m_values.clear();
}
