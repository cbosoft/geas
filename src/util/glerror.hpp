#pragma once

#include <string>

std::string glstrerror(unsigned int e);

void gl_error_check(std::string context);
