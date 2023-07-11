/**************************************************************************
  
  Simple library to parse and compare semantic version strings
  in the format "major.minor.patch", i.e. "1.23.456".
  
  Version: 1.0.0
  
  License: GNU GENERAL PUBLIC LICENSE Version 3
  
  GitHub: https://github.com/ciberbob1987/SemanticVersion
  
/**************************************************************************/

#ifndef _SemanticVersion_h
#define _SemanticVersion_h

#include <Arduino.h>

class SemanticVersion
{
public:
  
  SemanticVersion() {
    _major = 0;
    _minor = 0;
    _patch = 0;
  };
  
  SemanticVersion(String versionStr) : SemanticVersion(versionStr.c_str()) {};
  
  SemanticVersion(const char* versionStr) {
    uint32_t tmpNum[3] = {0};
    
    char iChar = versionStr[0];
    uint8_t i=0, j=0;
    uint8_t vLen = strlen(versionStr);
    
    if (vLen > _V_STR_MAX_LEN) vLen = 0;

    String buffString = "";
    
    while (i < vLen && i < _V_STR_MAX_LEN) {
      if (versionStr[i] >= '0' && versionStr[i] <= '9') buffString += versionStr[i];
      
      if (versionStr[i] == '.' || i == vLen - 1) {
        if (j <= 2) {
          tmpNum[j] = buffString.toInt();
          buffString = "";
          
          j++;
        }
        else break;
      }
      i++;
    }
    
    _major = tmpNum[0];
    _minor = tmpNum[1];
    _patch = tmpNum[2];
  };
  
  const uint32_t major() { return _major; };
  const uint32_t minor() { return _minor; };
  const uint32_t patch() { return _patch; };
  
  bool operator>(SemanticVersion& other) {
    COMPARE_RESULT res = _compare(other);
    
    return res == COMPARE_RESULT::MAJOR;
  }
  
  bool operator<(SemanticVersion& other) {
    COMPARE_RESULT res = _compare(other);
    
    return res == COMPARE_RESULT::MINOR;
  }
  
  bool operator==(SemanticVersion& other) {
    COMPARE_RESULT res = _compare(other);
    
    return res == COMPARE_RESULT::EQUAL;
  }
  
  bool operator>=(SemanticVersion& other) {
    COMPARE_RESULT res = _compare(other);
    
    return (res == COMPARE_RESULT::EQUAL) || (res == COMPARE_RESULT::MAJOR);
  }
  
  bool operator<=(SemanticVersion& other) {
    COMPARE_RESULT res = _compare(other);
    
    return (res == COMPARE_RESULT::EQUAL) || (res == COMPARE_RESULT::MINOR);
  }
  
private:
  
  uint32_t _major;
  uint32_t _minor;
  uint32_t _patch;
  
  enum class COMPARE_RESULT : uint8_t {
    MINOR,
    MAJOR,
    EQUAL
  };
  
  const uint8_t _V_STR_MAX_LEN = 10;
  
  COMPARE_RESULT _compare(SemanticVersion& other) {
    if ((this->_major == other.major()) &&
        (this->_minor == other.minor()) &&
        (this->_patch == other.patch()) ) return COMPARE_RESULT::EQUAL;
    
    if ((this->_major > other.major()) ||
       ((this->_major == other.major()) && (this->_minor > other.minor())) ||
       ((this->_major == other.major()) && (this->_minor == other.minor()) && (this->_patch == other.patch()))) return COMPARE_RESULT::MAJOR;
    
    return COMPARE_RESULT::MINOR;
  };
};
#endif