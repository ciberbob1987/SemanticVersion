/**************************************************************************
  
  Simple library to parse and compare semantic version strings
  in the format "major.minor.patch", i.e. "1.23.456".
  
  Version: 1.2.1
  
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
    _versionNum[0] = 0;
    _versionNum[1] = 0;
    _versionNum[2] = 0;
  };
  
  SemanticVersion(String versionStr) {
    parseV(versionStr.c_str());
  };
  
  SemanticVersion(const char* versionStr) {
    parseV(versionStr);
  };
  
  const uint16_t major() { return _versionNum[0]; };
  const uint16_t minor() { return _versionNum[1]; };
  const uint16_t patch() { return _versionNum[2]; };
  
  const char* getCString() { return _versionStr; };
  
  void parseV(String versionStr) {
    parseV(versionStr.c_str());
  };
  
  void parseV(const char* versionStr) {
    _versionNum[0] = 0;
    _versionNum[1] = 0;
    _versionNum[2] = 0;
    
    char iChar = versionStr[0];
    uint8_t i=0, j=0;
    uint8_t vLen = strlen(versionStr);
    
    if (vLen > _V_STR_MAX_LEN) vLen = 0;

    String buffString = "";
    
    while (i < vLen && i < _V_STR_MAX_LEN) {
      if (versionStr[i] >= '0' && versionStr[i] <= '9') buffString += versionStr[i];
      
      if (versionStr[i] == '.' || i == vLen - 1) {
        if (j <= 2) {
          _versionNum[j] = buffString.toInt();
          buffString = "";
          
          j++;
        }
        else break;
      }
      i++;
    }
    
    _makeCString();
  };
  
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
  
  static const uint8_t _V_STR_MAX_LEN = 15;
  
  /* _versionNum[0] -> Major */
  /* _versionNum[1] -> Minor */
  /* _versionNum[2] -> Patch */
  uint16_t _versionNum[3];
  
  char _versionStr[_V_STR_MAX_LEN];
  
  enum class COMPARE_RESULT : uint8_t {
    MINOR,
    MAJOR,
    EQUAL
  };
  
  
  COMPARE_RESULT _compare(SemanticVersion& other) {
    if ((this->_versionNum[0] == other.major()) &&
        (this->_versionNum[1] == other.minor()) &&
        (this->_versionNum[2] == other.patch()) ) return COMPARE_RESULT::EQUAL;
    
    if ((this->_versionNum[0] > other.major()) ||
       ((this->_versionNum[0] == other.major()) && (this->_versionNum[1] > other.minor())) ||
       ((this->_versionNum[0] == other.major()) && (this->_versionNum[1] == other.minor()) && (this->_versionNum[2] > other.patch()))) return COMPARE_RESULT::MAJOR;
    
    return COMPARE_RESULT::MINOR;
  };
  
  void _makeCString() {
    String aux = "";
    
    for (uint8_t i=0; i<3; i++) {
      String buffer = String(_versionNum[i], DEC);
      aux += buffer + ".";
    }
    
    aux.remove(aux.length()-1, 1);
    strncpy(_versionStr, aux.c_str(), _V_STR_MAX_LEN);
  };
};
#endif