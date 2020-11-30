#pragma once
#include <exception>
#include <string>
#include <iostream>
#include <cstring>

#include "colour.hpp"
#include "formatter.hpp"
#include "../renderer/OpenGL/glerror.hpp"



class Exception : public virtual std::exception {
  private:

    std::string detail = "";
    std::string type = "";
    std::string cause = "";
    bool cause_set;
    bool use_errno;

  public:
    Exception(std::string detail, std::string type, std::string cause) 
    { 
      this->detail = detail; 
      this->type = type; 
      this->cause = cause;
      this->cause_set = cause.size() > 0;
      this->use_errno = false;
    }

    Exception(std::string detail, std::string type) 
    { 
      this->detail = detail; 
      this->type = type; 
      this->cause_set = false;
      this->use_errno = false;
    }

    Exception(std::string detail, std::string type, bool use_errno)
    {
      this->detail = detail;
      this->type = type;
      this->cause_set = false;
      this->use_errno = use_errno;
    }

    void pretty_print() const
    {
      std::cerr << BOLD << BG_RED << this->type << RESET << ": " << this->detail;
      
      if (use_errno) {
          char errbuf[100] = { 0 };
#ifdef WINDOWS
          strerror_s(errbuf, 100, errno);
#else
          strerror_r(errno, errbuf, 100);
#endif
        std::cerr << "(" << errno << ": " << &(errbuf[0]) << ")";
      }

      if (this->cause_set) {
        std::cerr << this->cause;
      }

      std::cerr << std::endl;
    }

    const char *what() const noexcept override
    {
      std::stringstream ss;
      ss << BOLD << BG_RED << this->type << RESET << ": " << this->detail;
      
      if (use_errno) {
          char errbuf[100] = { 0 };
#ifdef WINDOWS
          strerror_s(errbuf, 100, errno);
#else
          strerror_r(errno, errbuf, 100);
#endif
        ss << "(" << errno << ": " << &(errbuf[0]) << ")";
      }

      if (this->cause_set) {
        ss << this->cause;
      }

      std::string s = ss.str();

#ifdef WINDOWS
      // Microsoft don't like the posix names; they want you to add an underscore? :(
      return _strdup(s.c_str());
#else
      return strdup(s.c_str());
#endif
    }
};





#define EXCEPTION(N,S)\
  class N : virtual public Exception {\
    public:\
           N(std::string detail, std::string cause) : Exception(detail, S, cause) { }\
           N(std::string detail) : Exception(detail, S) { }\
           N(std::string detail, bool use_errno) : Exception(detail, S, use_errno) { }\
  };

#define EXCEPTION_ERRNO(N,S)\
  class N : virtual public Exception {\
    public:\
           N(std::string detail, std::string cause) : Exception(detail, S, cause) { }\
           N(std::string detail) : Exception(detail, S, true) { }\
  };

EXCEPTION(InitialisationError, "InitialisationError");
EXCEPTION(ShaderError, "ShaderError");
EXCEPTION(ShaderCompileError, "ShaderCompileError");
EXCEPTION(OutOfRange, "OutOfRange");
EXCEPTION(GLError, "GLError");
EXCEPTION_ERRNO(IOError, "IOError");
EXCEPTION(SizeMismatch, "SizeMismatch");
EXCEPTION(PositionError, "PositionError");
EXCEPTION(NotFound, "NotFound");
EXCEPTION(UnexpectedNullPointer, "UnexpectedNullPointer");
EXCEPTION(NameConflict, "NameConflict");



EXCEPTION(AssertError, "AssertError");
inline void aite_assert(bool expression, std::string detail)
{
  if (!expression)
    throw AssertError(detail);
}
