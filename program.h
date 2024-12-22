#include <json/json.h>
#include "struct-definitions.h"

void printTitle(string);
list<animation>* getAnimations(Json::Value);
void printAnimationData(list<animation>*);
list<keyframe*>* getKeyframes(Json::Value);
keyframe* extractKeyframeByType(Json::Value);
void printKeyframeData(list<keyframe*>*);
void printKeyframeTypeData(keyframe*, KEYFRAME_LAYER_TYPE);
list<layer*>* getLayers(Json::Value);
layer* extractLayerByType(Json::Value);
void printLayerData(list<layer*>*);
void printLayerTypeData(layer*, KEYFRAME_LAYER_TYPE);
paletteMap* getPaletteMap(Json::Value);
void printPaletteMapData(paletteMap*);
list<symbol*>* getSymbols(Json::Value);
symbol* extractSymbolByType(Json::Value);
void printSymbolData(list<symbol*>*);
void printSymbolTypeData(symbol*, SYMBOL_TYPE);