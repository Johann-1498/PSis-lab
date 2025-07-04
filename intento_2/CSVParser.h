#pragma once
#include <string>
#include <vector>
#include "DataTypes.h"

class CSVParser {
public:
    std::vector<ParadaRuta> parse(const std::string& nombre_archivo);
};