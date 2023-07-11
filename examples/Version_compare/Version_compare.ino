#include <SemanticVersion.h>

void setup() {
  
  Serial.begin(115200);
  
  Serial.println();
  Serial.println("Version compare");
  Serial.println();
  
  SemanticVersion test_0;
  
  Serial.println("---- constructor SemanticVersion() ----");
  Serial.print("Major: "); Serial.println(test_0.major());
  Serial.print("Minor: "); Serial.println(test_0.minor());
  Serial.print("Patch: "); Serial.println(test_0.patch());
  Serial.println("---- constructor SemanticVersion() ----");
  
  Serial.println();
  Serial.println();
  
  String auxStr_1 = "";
  auxStr_1 = "1.2.3";
  SemanticVersion test_1(auxStr_1);
  
  Serial.println("---- " + auxStr_1 + " ----");
  Serial.print("Major: "); Serial.println(test_1.major());
  Serial.print("Minor: "); Serial.println(test_1.minor());
  Serial.print("Patch: "); Serial.println(test_1.patch());
  Serial.println("---- " + auxStr_1 + " ----");
  
  Serial.println();
  Serial.println();
  
  String auxStr_2 = "";
  auxStr_2 = "1.4.5";
  SemanticVersion test_2(auxStr_2);
  
  Serial.println("---- " + auxStr_2 + " ----");
  Serial.print("Major: "); Serial.println(test_2.major());
  Serial.print("Minor: "); Serial.println(test_2.minor());
  Serial.print("Patch: "); Serial.println(test_2.patch());
  Serial.println("---- " + auxStr_2 + " ----");
  
  Serial.println();
  Serial.println();
  
  Serial.print(auxStr_2 + " > " + auxStr_1 + "  -->  ");
  Serial.println(test_2 > test_1);
  Serial.println();
  
  Serial.print(auxStr_1 + " > " + auxStr_2 + "  -->  ");
  Serial.println(test_1 > test_2);
  Serial.println();
  
  Serial.print(auxStr_2 + " < " + auxStr_1 + "  -->  ");
  Serial.println(test_2 < test_1);
  Serial.println();
  
  Serial.print(auxStr_1 + " < " + auxStr_2 + "  -->  ");
  Serial.println(test_1 < test_2);
  Serial.println();
  
  Serial.print(auxStr_1 + " == " + auxStr_1 + "  -->  ");
  Serial.println(test_1 == test_1);
  Serial.println();
  
  Serial.print(auxStr_1 + " >= " + auxStr_1 + "  -->  ");
  Serial.println(test_1 >= test_1);
  Serial.println();
  
  Serial.print(auxStr_1 + " > " + auxStr_1 + "  -->  ");
  Serial.println(test_1 > test_1);
  Serial.println();
}

void loop() { 
}