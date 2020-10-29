#pragma once

#include <string>

std::string glstrerror(unsigned int e);

void gl_error_check(std::string context);

#ifdef DEBUG
#define GL_ERROR_CHECK_DBG(S) gl_error_check(S);
#else
#define GL_ERROR_CHECK_DBG(S)
#endif
