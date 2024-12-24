#include "struct-definitions.h"

// Linux
#include <json/json.h>
// Windows
// #include "external/jsoncpp-master/src/lib_json/json_reader.cpp"
// #include "external/jsoncpp-master/src/lib_json/json_value.cpp"
// #include "external/jsoncpp-master/src/lib_json/json_writer.cpp"

void printTitle(string);
list<animation>* getAnimations(Json::Value);
void printAnimationData(list<animation>*);
list<keyframe*>* getKeyframes(Json::Value);
keyframe* extractKeyframeByType(Json::Value);
void printKeyframeData(list<keyframe*>*);
void printKeyframeTypeData(keyframe*);
list<layer*>* getLayers(Json::Value);
layer* extractLayerByType(Json::Value);
void printLayerData(list<layer*>*);
void printLayerTypeData(layer*);
paletteMap* getPaletteMap(Json::Value);
void printPaletteMapData(paletteMap*);
list<symbol*>* getSymbols(Json::Value);
symbol* extractSymbolByType(Json::Value);
void printSymbolData(list<symbol*>*);
void printSymbolTypeData(symbol*);