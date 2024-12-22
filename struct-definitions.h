#include <list>
#include "enum-definitions.h"
using namespace std;

typedef struct animation {
	string id;
	list<string> layerIDs;
	string name = "";
} animation;

typedef struct keyframe {
	string id;
	unsigned int length = 1;
	KEYFRAME_LAYER_TYPE type;
	virtual ~keyframe() = default;
} keyframe;

struct keyframeScript : keyframe {
	keyframeScript(){
		this->type = KL_FRAME_SCRIPT;
	}
	string code = "";
};

struct keyframeAnimated : keyframe {
	keyframeAnimated(KEYFRAME_LAYER_TYPE type){
		this->type = type;
	}
	string symbolID;
	TWEEN_TYPE tweenType = TW_LINEAR;
	bool tweened = false;
};

struct keyframeLabel : keyframe {
	keyframeLabel(){
		this->type = KL_LABEL;
	}
	string name = "";
};


typedef struct layer {
	string id;
	bool hidden = false;
	list<string> keyframeIDs;
	bool locked = false;
	string name = "";
	KEYFRAME_LAYER_TYPE type;
	virtual ~layer() = default;
} layer;

struct layerScript : layer {
	layerScript(){
		this->type = KL_FRAME_SCRIPT;
	}
	string language = "";
};

struct layerCollisionBox : layer {
	layerCollisionBox(){
		this->type = KL_COLLISION_BOX;
	}
	float defaultAlpha = 0.5;
	string defaultColor = "0x000000";
	COLLISION_BOX_TYPE collisionBoxType = NONE;
	int collisionBoxIndex = 0;
};

struct layerCollisionBody : layer {
	layerCollisionBody(){
		this->type = KL_COLLISION_BODY;
	}
	float defaultAlpha = 0.5;
	string defaultColor = "0xffa500";
	unsigned int defaultHead = 100.0;
	unsigned int defaultHipWidth = 50.0;
	unsigned int defaultHipXOffset = 0.0;
	unsigned int defaultHipYOffset = 0.0;
	unsigned int defaultFoot = 0.0;
};

typedef struct {
	string palletteCollectionID;
	string paletteMapID;
} paletteMap;


typedef struct symbol {
	string id;
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
	string imageAssetID;
};

struct symbolCollisionBox : symbolWithScale {
	symbolCollisionBox(){
		this->type = SYM_COLLISION_BOX;
	}
	string color = "null";
};

struct symbolCollisionBody : symbol {
	symbolCollisionBody(){
		this->type = SYM_COLLISION_BODY;
	}
	string color = "null";
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
	string color = "0xff0000";
};

struct symbolLineSegment : symbol {
	symbolLineSegment(){
		this->type = SYM_LINE_SEGMENT;
	}
	string color = "0xcccccc";
	float x1 = 0.0;
	float y1 = 0.0;
	float x2 = 0.0;
	float y2 = 0.0;
};

typedef struct {
	list<animation>* animations;
	bool shouldExport = true;
	string guid;
	string id;
	list<keyframe*>* keyframes;
	list<layer*>* layers;
	::paletteMap* paletteMap;
	list<symbol*>* symbols;
} entityData;
