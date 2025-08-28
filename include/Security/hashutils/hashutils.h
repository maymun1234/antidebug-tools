
#ifndef HASHUTILS_H
#define HASHUTILS_H


#pragma once
#include <vector>
#include <string>

std::vector<unsigned char> calculate_sha256(const std::string& filePath);
void print_hash(const std::vector<unsigned char>& hash);


#endif