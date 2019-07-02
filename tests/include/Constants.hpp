#pragma once
#include <string>
#include <vector>

const std::string ppm_path = "..\\..\\..\\tests\\TestInput\\PPM\\";
const std::string ppm_temp_folder = ppm_path + "temp\\";

const std::vector<std::string> PPM_ASCII_FILE_NAMES = {"snail.ascii.ppm"};
const std::vector<std::string> PPM_BINARY_FILE_NAMES = {"Billes.256.ppm"};

const std::string pgm_path = "..\\..\\..\\tests\\TestInput\\PGM\\";
const std::string pgm_temp_folder = pgm_path + "temp\\";

const std::vector<std::string> PGM_BINARY_FILE_NAMES = {"coins.pgm", "mona_lisa.pgm"};
const std::vector<std::string> PGM_ASCII_FILE_NAMES
    = {"coins.ascii.pgm", "mona_lisa.ascii.pgm"};