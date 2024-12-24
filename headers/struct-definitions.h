#ifndef ENTITY_DATA_STRUCT_DEF_H
#define ENTITY_DATA_STRUCT_DEF_H

#include <list>
#include "enum-definitions.h"

typedef struct animation {
	std::string id;
	std::list<std::string> layerIDs;
	std::string name = "";
} animation;

typedef struct keyframe {
	std::string id;
	unsigned int length = 1;
	KEYFRAME_LAYER_TYPE type;
	virtual ~keyframe() = default;
} keyframe;

struct keyframeScript : keyframe {
	keyframeScript(){
		this->type = KL_FRAME_SCRIPT;
	}
	std::string code = "";
};

struct keyframeAnimated : keyframe {
	keyframeAnimated(KEYFRAME_LAYER_TYPE type){
		this->type = type;
	}
	std::string symbolID;
	TWEEN_TYPE tweenType = TW_LINEAR;
	bool tweened = false;
};

struct keyframeLabel : keyframe {
	keyframeLabel(){
		this->type = KL_LABEL;
	}
	std::string name = "";
};


typedef struct layer {
	std::string id;
	bool hidden = false;
	std::list<std::string> keyframeIDs;
	bool locked = false;
	std::string name = "";
	KEYFRAME_LAYER_TYPE type;
	virtual ~layer() = default;
} layer;

struct layerScript : layer {
	layerScript(){
		this->type = KL_FRAME_SCRIPT;
	}
	std::string language = "";
};

struct layerCollisionBox : layer {
	layerCollisionBox(){
		this->type = KL_COLLISION_BOX;
	}
	float defaultAlpha = 0.5;
	std::string defaultColor = "0x000000";
	COLLISION_BOX_TYPE collisionBoxType = NONE;
	int collisionBoxIndex = 0;
};

struct layerCollisionBody : layer {
	layerCollisionBody(){
		this->type = KL_COLLISION_BODY;
	}
	float defaultAlpha = 0.5;
	std::string defaultColor = "0xffa500";
	unsigned int defaultHead = 100.0;
	unsigned int defaultHipWidth = 50.0;
	unsigned int defaultHipXOffset = 0.0;
	unsigned int defaultHipYOffset = 0.0;
	unsigned int defaultFoot = 0.0;
};

typedef struct {
	std::string palletteCollectionID;
	std::string paletteMapID;
} paletteMap;


typedef struct symbol {
	std::string id;
	float alpha = 1.0;
	SYMBOL_TYPE type;
	virtual ~symbol() = default;
} symbol;

struct symbolWithOrigin : symbol {
	float x = 0.0;
	float y = 0.0;
	float rotation = 0.0;
};

struct symbolWithScale : symbolWithOrigin {
	float scaleX = 1.0;
	float scaleY = 1.0;
	float pivotX = 0.0;
	float pivotY = 0.0;
};

struct symbolImage : symbolWithScale {
	symbolImage(){
		this->type = SYM_IMAGE;
	}
	std::string imageAssetID;
};

struct symbolCollisionBox : symbolWithScale {
	symbolCollisionBox(){
		this->type = SYM_COLLISION_BOX;
	}
	std::string color = "null";
};

struct symbolCollisionBody : symbol {
	symbolCollisionBody(){
		this->type = SYM_COLLISION_BODY;
	}
	std::string color = "null";
	float head = 100.0;
	float hipWidth = 50.0;
	float hipXOffset = 0.0;
	float hipYOffset = 0.0;
	float foot = 0.0;
};

struct symbolPoint : symbolWithOrigin {
	symbolPoint(){
		this->type = SYM_POINT;
	}
	std::string color = "0xff0000";
};

struct symbolLineSegment : symbol {
	symbolLineSegment(){
		this->type = SYM_LINE_SEGMENT;
	}
	std::string color = "0xcccccc";
	float x1 = 0.0;
	float y1 = 0.0;
	float x2 = 0.0;
	float y2 = 0.0;
};

typedef struct entityData {
	std::list<animation>* animations;
	bool shouldExport;
	std::string guid;
	std::string id;
	std::list<keyframe*>* keyframes;
	std::list<layer*>* layers;
	::paletteMap* paletteMap;
	std::list<symbol*>* symbols;
	OBJECT_TYPE objectType;
	std::string objectVersion;
} entityData;

#endif