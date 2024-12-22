#include <cstdlib>
#include <ios>
#include <iostream>
#include <fstream>
#include <json/json.h>
#include <list>

using namespace std;

// struct {
//
// } pluginMetadata

typedef struct animation {
	string id;
	list<string> layerIDs;
	string name = "";
} animation;

enum KEYFRAME_LAYER_TYPE {
	KL_IMAGE,
	KL_FRAME_SCRIPT,
	KL_LABEL,
	KL_COLLISION_BOX,
	KL_COLLISION_BODY,
	KL_POINT,
	KL_LINE_SEGMENT,
	KL_CONTAINER // wtf does this even do
};

enum TWEEN_TYPE {
	LINEAR,
	EASE_IN_QUAD,
	EASE_OUT_QUAD,
	EASE_IN_OUT_QUAD,
	EASE_IN_CUBIC,
	EASE_OUT_CUBIC,
	EASE_IN_OUT_CUBIC,
	EASE_IN_QUART,
	EASE_OUT_QUART,
	EASE_IN_OUT_QUART,
	EASE_IN_QUINT,
	EASE_OUT_QUINT,
	EASE_IN_OUT_QUINT
};

map<string, KEYFRAME_LAYER_TYPE> mapToKeyframeLayerType {
	{"IMAGE", KL_IMAGE},
	{"FRAME_SCRIPT", KL_FRAME_SCRIPT},
	{"LABEL", KL_LABEL},
	{"COLLISION_BOX", KL_COLLISION_BOX},
	{"COLLISION_BODY", KL_COLLISION_BODY},
	{"POINT", KL_POINT},
	{"LINE_SEGMENT", KL_LINE_SEGMENT},
	{"CONTAINER", KL_CONTAINER}
};

map<KEYFRAME_LAYER_TYPE, string> mapToKeyframeLayerTypeName {
	{KL_IMAGE, "IMAGE"},
	{KL_FRAME_SCRIPT, "FRAME_SCRIPT"},
	{KL_LABEL, "LABEL"},
	{KL_COLLISION_BOX, "COLLISION_BOX"},
	{KL_COLLISION_BODY, "COLLISION_BODY"},
	{KL_POINT, "POINT"},
	{KL_LINE_SEGMENT, "LINE_SEGMENT"},
	{KL_CONTAINER, "CONTAINER"}
};

map<string, TWEEN_TYPE> mapToTweenType {
	{"LINEAR", LINEAR},
	{"EASE_IN_QUAD", EASE_IN_QUAD},
	{"EASE_OUT_QUAD", EASE_OUT_QUAD},
	{"EASE_IN_OUT_QUAD", EASE_IN_OUT_QUAD},
	{"EASE_IN_CUBIC", EASE_IN_CUBIC},
	{"EASE_OUT_CUBIC", EASE_OUT_CUBIC},
	{"EASE_IN_OUT_CUBIC", EASE_IN_OUT_CUBIC},
	{"EASE_IN_QUART", EASE_IN_QUART},
	{"EASE_OUT_QUART", EASE_OUT_QUART},
	{"EASE_IN_OUT_QUART", EASE_IN_OUT_QUART},
	{"EASE_IN_QUINT", EASE_IN_QUINT},
	{"EASE_OUT_QUINT", EASE_OUT_QUINT},
	{"EASE_IN_OUT_QUINT", EASE_IN_OUT_QUINT}
};

typedef struct keyframe {
	string id;
	uint length = 1;
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
	TWEEN_TYPE tweenType = LINEAR;
	bool tweened = false;
};

struct keyframeLabel : keyframe {
	keyframeLabel(){
		this->type = KL_LABEL;
	}
	string name = "";
};

enum COLLISION_BOX_TYPE {
	NONE,
	HURT_BOX,
	HIT_BOX,
	GRAB_BOX,
	LEDGE_GRAB_BOX,
	REFLECT_BOX,
	ABSORB_BOX,
	COUNTER_BOX,
	CUSTOM_BOX_A,
	CUSTOM_BOX_B,
	CUSTOM_BOX_C
};

map<string, COLLISION_BOX_TYPE> mapToCollisionBoxType {
	{"NONE", NONE},	
	{"HURT_BOX", HURT_BOX},
	{"HIT_BOX", HIT_BOX},
	{"GRAB_BOX", GRAB_BOX},
	{"LEDGE_GRAB_BOX", LEDGE_GRAB_BOX},
	{"REFLECT_BOX", REFLECT_BOX},
	{"ABSORB_BOX", ABSORB_BOX},
	{"COUNTER_BOX", COUNTER_BOX},
	{"CUSTOM_BOX_A", CUSTOM_BOX_A},
	{"CUSTOM_BOX_B", CUSTOM_BOX_B},
	{"CUSTOM_BOX_C", CUSTOM_BOX_C}
};

map<COLLISION_BOX_TYPE, string> mapToCollisionBoxTypeName {
	{NONE, "NONE"},	
	{HURT_BOX, "HURT_BOX"},
	{HIT_BOX, "HIT_BOX"},
	{GRAB_BOX, "GRAB_BOX"},
	{LEDGE_GRAB_BOX, "LEDGE_GRAB_BOX"},
	{REFLECT_BOX, "REFLECT_BOX"},
	{ABSORB_BOX, "ABSORB_BOX"},
	{COUNTER_BOX, "COUNTER_BOX"},
	{CUSTOM_BOX_A, "CUSTOM_BOX_A"},
	{CUSTOM_BOX_B, "CUSTOM_BOX_B"},
	{CUSTOM_BOX_C, "CUSTOM_BOX_C"}
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
	uint defaultHead = 100.0;
	uint defaultHipWidth = 50.0;
	uint defaultHipXOffset = 0.0;
	uint defaultHipYOffset = 0.0;
	uint defaultFoot = 0.0;
};

typedef struct {
	string palletteCollectionID;
	string paletteMapID;
} paletteMap;

enum SYMBOL_TYPE {
	SYM_IMAGE,
	SYM_COLLISION_BOX,
	SYM_COLLISION_BODY,
	SYM_POINT,
	SYM_LINE_SEGMENT
};

map<string, SYMBOL_TYPE> mapToSymbolType {
	{"IMAGE", SYM_IMAGE},
	{"COLLISION_BOX", SYM_COLLISION_BOX},
	{"COLLISION_BODY", SYM_COLLISION_BODY},
	{"POINT", SYM_POINT},
	{"LINE_SEGMENT", SYM_LINE_SEGMENT}
};

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

typedef struct data {
	list<animation> animations;
	bool shouldExport = true;
	string guid;
	string id;
	list<keyframe*> keyframes;
	list<layer*> layers;
	::paletteMap paletteMap;
	list<symbol*> symbols;
} data;

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
list<symbol*>* getSymbols(Json::Value data);
symbol* extractSymbolByType(Json::Value);
void printSymbolData(list<symbol*>*);
void printSymbolTypeData(symbol*, SYMBOL_TYPE);

class statTracker {
    private:
        uint numAnimations = 0;

		uint numKeyframes = 0;
        uint numImageKeyframes = 0;
        uint numScriptKeyframes = 0;
        uint numLabelKeyframes = 0;
        uint numCollisionBoxKeyframes = 0;
        uint numCollisionBodyKeyframes = 0;
        uint numPointKeyframes = 0;
        uint numLineSegmentKeyframes = 0;
        uint numContainerKeyframes = 0;
		
		uint numTweensEnabled = 0;
        uint numLinearTweens = 0;
        uint numEaseInTweens = 0;
        uint numEaseOutTweens = 0;
        uint numEaseInOutTweens = 0;
        uint numQuadTweens = 0;
        uint numCubicTweens = 0;
        uint numQuartTweens = 0;
        uint numQuintTweens = 0;

        uint numLayers = 0;
        uint numImageLayers = 0;
        uint numScriptLayers = 0;
        uint numLabelLayers = 0;
        uint numCollisionBoxLayers = 0;
        uint numCollisionBodyLayers = 0;
        uint numPointLayers = 0;
        uint numLineSegmentLayers = 0;
        uint numContainerLayers = 0;

        uint numNoneBoxes = 0;
        uint numHurtBoxes = 0;
        uint numHitBoxes = 0;
        uint numGrabBoxes = 0;
        uint numLedgeGrabBoxes = 0;
        uint numReflectBoxes = 0;
        uint numAbsorbBoxes = 0;
        uint numCounterBoxes = 0;
        uint numCustomBoxAs = 0;
        uint numCustomBoxBs = 0;
        uint numCustomBoxCs = 0;

		uint numSymbols = 0;
        uint numImageSymbols = 0;
        uint numCollisionBoxSymbols = 0;
        uint numCollisionBodySymbols = 0;
        uint numPointSymbols = 0;
        uint numLineSegmentSymbols = 0;
    public:
		float getAverageLayersPerAnimation(){ return (float)numLayers / numAnimations; };
		float getPercentOfKeyframesTweened(){
			return (numTweensEnabled == 0)?
				0
			  : (float)numKeyframes / numTweensEnabled;
		};

        void incrementAnimations(){ numAnimations++; };
        int getTotalAnimations(){ return numAnimations; };

        void incrementKeyframes(){ numKeyframes++; };
        int getTotalKeyframes(){ return numKeyframes; };
        void incrementImageKeyframes(){ numImageKeyframes++; };
        int getTotalImageKeyframes(){ return numImageKeyframes; };
        void incrementScriptKeyframes(){ numScriptKeyframes++; };
        int getTotalScriptKeyframes(){ return numScriptKeyframes; };
        void incrementLabelKeyframes(){ numLabelKeyframes++; };
        int getTotalLabelKeyframes(){ return numLabelKeyframes; };
        void incrementCollisionBoxKeyframes(){ numCollisionBoxKeyframes++; };
        int getTotalCollisionBoxKeyframes(){ return numCollisionBoxKeyframes; };
        void incrementCollisionBodyKeyframes(){ numCollisionBodyKeyframes++; };
        int getTotalCollisionBodyKeyframes(){ return numCollisionBodyKeyframes; };
        void incrementPointKeyframes(){ numPointKeyframes++; };
        int getTotalPointKeyframes(){ return numPointKeyframes; };
        void incrementLineSegmentKeyframes(){ numLineSegmentKeyframes++; };
        int getTotalLineSegmentKeyframes(){ return numLineSegmentKeyframes; };
        void incrementContainerKeyframes(){ numContainerKeyframes++; };
        int getTotalContainerKeyframes(){ return numContainerKeyframes; };
		
		void incrementTweensEnabled(){ numTweensEnabled++; };
		int getTotalTweensEnabled(){ return numTweensEnabled; };
        void incrementLinearTweens(){ numLinearTweens++; };
        int getTotalLinearTweens(){ return numLinearTweens; };
        void incrementEaseInTweens(){ numEaseInTweens++; };
        int getTotalEaseInTweens(){ return numEaseInTweens; };
        void incrementEaseOutTweens(){ numEaseOutTweens++; };
        int getTotalEaseOutTweens(){ return numEaseOutTweens; };
        void incrementEaseInOutTweens(){ numEaseInOutTweens++; };
        int getTotalEaseInOutTweens(){ return numEaseInOutTweens; };
        void incrementQuadTweens(){ numQuadTweens++; };
        int getTotalQuadTweens(){ return numQuadTweens; };
        void incrementCubicTweens(){ numCubicTweens++; };
        int getTotalCubicTweens(){ return numCubicTweens; };
        void incrementQuartTweens(){ numQuartTweens++; };
        int getTotalQuartTweens(){ return numQuartTweens; };
        void incrementQuintTweens(){ numQuintTweens++; };
        int getTotalQuintTweens(){ return numQuintTweens; };

        void incrementLayers(){ numLayers++; };
        int getTotalLayers(){ return numLayers; };
        void incrementImageLayers(){ numImageLayers++; };
        int getTotalImageLayers(){ return numImageLayers; };
        void incrementScriptLayers(){ numScriptLayers++; };
        int getTotalScriptLayers(){ return numScriptLayers; };
        void incrementLabelLayers(){ numLabelLayers++; };
        int getTotalLabelLayers(){ return numLabelLayers; };
        void incrementCollisionBoxLayers(){ numCollisionBoxLayers++; };
        int getTotalCollisionBoxLayers(){ return numCollisionBoxLayers; };
        void incrementCollisionBodyLayers(){ numCollisionBodyLayers++; };
        int getTotalCollisionBodyLayers(){ return numCollisionBodyLayers; };
        void incrementPointLayers(){ numPointLayers++; };
        int getTotalPointLayers(){ return numPointLayers; };
        void incrementLineSegmentLayers(){ numLineSegmentLayers++; };
        int getTotalLineSegmentLayers(){ return numLineSegmentLayers; };
        void incrementContainerLayers(){ numContainerLayers++; };
        int getTotalContainerLayers(){ return numContainerLayers; };

        void incrementNoneBoxes(){ numNoneBoxes++; };
        int getTotalNoneBoxes(){ return numNoneBoxes; };
        void incrementHurtBoxes(){ numHurtBoxes++; };
        int getTotalHurtBoxes(){ return numHurtBoxes; };
        void incrementHitBoxes(){ numHitBoxes++; };
        int getTotalHitBoxes(){ return numHitBoxes; };
        void incrementGrabBoxes(){ numGrabBoxes++; };
        int getTotalGrabBoxes(){ return numGrabBoxes; };
        void incrementLedgeGrabBoxes(){ numLedgeGrabBoxes++; };
        int getTotalLedgeGrabBoxes(){ return numLedgeGrabBoxes; };
        void incrementReflectBoxes(){ numReflectBoxes++; };
        int getTotalReflectBoxes(){ return numReflectBoxes; };
        void incrementAbsorbBoxes(){ numAbsorbBoxes++; };
        int getTotalAbsorbBoxes(){ return numAbsorbBoxes; };
        void incrementCounterBoxes(){ numCounterBoxes++; };
        int getTotalCounterBoxes(){ return numCounterBoxes; };
        void incrementCustomBoxAs(){ numCustomBoxAs++; };
        int getTotalCustomBoxAs(){ return numCustomBoxAs; };
        void incrementCustomBoxBs(){ numCustomBoxBs++; };
        int getTotalCustomBoxBs(){ return numCustomBoxBs; };
        void incrementCustomBoxCs(){ numCustomBoxCs++; };
        int getTotalCustomBoxCs(){ return numCustomBoxCs; };

        void incrementSymbols(){ numSymbols++; };
        int getTotalSymbols(){ return numSymbols; };
        void incrementImageSymbols(){ numImageSymbols++; };
        int getTotalImageSymbols(){ return numImageSymbols; };
        void incrementCollisionBoxSymbols(){ numCollisionBoxSymbols++; };
        int getTotalCollisionBoxSymbols(){ return numCollisionBoxSymbols; };
        void incrementCollisionBodySymbols(){ numCollisionBodySymbols++; };
        int getTotalCollisionBodySymbols(){ return numCollisionBodySymbols; };
        void incrementPointSymbols(){ numPointSymbols++; };
        int getTotalPointSymbols(){ return numPointSymbols; };
        void incrementLineSegmentSymbols(){ numLineSegmentSymbols++; };
        int getTotalLineSegmentSymbols(){ return numLineSegmentSymbols; };

		void printStats(){
			cout << ".----------------------------.\n"
				 << "|   Entity Stats According   |\n"
				 << "|         To The File        |\n"
				 << "'----------------------------'\n\n";
				 
            cout << "Animations: " << numAnimations << endl
				 << "Average number of layers per animation: " << getAverageLayersPerAnimation() << endl
				 << endl;

            cout << "Unique keyframes: " << numKeyframes << endl
                 << "Unique image keyframes: " << numImageKeyframes << endl
                 << "Unique script keyframes: " << numScriptKeyframes << endl
                 << "Unique label keyframes: " << numLabelKeyframes << endl
                 << "Unique collision box keyframes: " << numCollisionBoxKeyframes << endl
                 << "Unique collision body keyframes: " << numCollisionBodyKeyframes << endl
                 << "Unique point keyframes: " << numPointKeyframes << endl
                 << "Unique line segment keyframes: " << numLineSegmentKeyframes << endl
                 << "Unique container keyframes: " << numContainerKeyframes << endl
				 << endl;

			cout << "Tweened keyframes: " << numTweensEnabled << endl
                 << "Linear tweens: " << numLinearTweens << endl
                 << "Ease in tweens: " << numEaseInTweens << endl
                 << "Ease out tweens: " << numEaseOutTweens << endl
                 << "Ease in out tweens: " << numEaseInOutTweens << endl
                 << "Quad tweens: " << numQuadTweens << endl
                 << "Cubic tweens: " << numCubicTweens << endl
                 << "Quart tweens: " << numQuartTweens << endl
                 << "Quint tweens: " << numQuintTweens << endl
				 << endl;

			cout << "Percentage of keyframes tweened: " << getPercentOfKeyframesTweened() << "%" << endl
				 << endl;

            cout << "Layers: " << numLayers << endl
                 << "Image layers: " << numImageLayers << endl
                 << "Script layers: " << numScriptLayers << endl
                 << "Label layers: " << numLabelLayers << endl
                 << "Collision box layers: " << numCollisionBoxLayers << endl
                 << "Collision body layers: " << numCollisionBodyLayers << endl
                 << "Point layers: " << numPointLayers << endl
                 << "Line segment layers: " << numLineSegmentLayers << endl
                 << "Container layers: " << numContainerLayers << endl
				 << endl;

            cout << "Collision Box Types:\n"
				 << "None boxes: " << numNoneBoxes << endl
                 << "Hurt boxes: " << numHurtBoxes << endl
                 << "Hit boxes: " << numHitBoxes << endl
                 << "Grab boxes: " << numGrabBoxes << endl
                 << "Ledge grab boxes: " << numLedgeGrabBoxes << endl
                 << "Reflect boxes: " << numReflectBoxes << endl
                 << "Absorb boxes: " << numAbsorbBoxes << endl
                 << "Counter boxes: " << numCounterBoxes << endl
                 << "Custom box As: " << numCustomBoxAs << endl
                 << "Custom box Bs: " << numCustomBoxBs << endl
                 << "Custom box Cs: " << numCustomBoxCs << endl
				 << endl;
			
			cout << "Symbols: " << numSymbols << endl
                 << "Image symbols: " << numImageSymbols << endl
                 << "Collision box symbols: " << numCollisionBoxSymbols << endl
                 << "Collision body symbols: " << numCollisionBodySymbols << endl
                 << "Point symbols: " << numPointSymbols << endl
                 << "Line segment symbols: " << numLineSegmentSymbols << endl

				 << endl;
		}
};

statTracker tracker;

int main(){
	/*
	string variables[] = {
		// "Animations", "LayersInAllAnimations"

		// "Keyframes", "ImageKeyframes", "ScriptKeyframes", "LabelKeyframes",
		// "CollisionBoxKeyframes", "CollisionBodyKeyframes", "PointKeyframes",
		// "LineSegmentKeyframes", "ContainerKeyframes",
		// "TweensEnabled",
		// "LinearTweens", "EaseInTweens", "EaseOutTweens", "EaseInOutTweens",
		// "QuadTweens", "CubicTweens", "QuartTweens", "QuintTweens"

		// "Layers", "ImageLayers", "ScriptLayers", "LabelLayers",
		// "CollisionBoxLayers", "CollisionBodyLayers", "PointLayers",
		// "LineSegmentLayers", "ContainerLayers"

		// "NoneBoxes", "HurtBoxes", "HitBoxes", "GrabBoxes", "LedgeGrabBoxes",
		// "ReflectBoxes", "AbsorbBoxes", "CounterBoxes",
		// "CustomBoxAs", "CustomBoxBs", "CustomBoxCs"

		// "Symbols", "ImageSymbols", "CollisionBoxSymbols",
		// "CollisionBodySymbols", "PointSymbols", "LineSegmentSymbols"
	};
	cout << "    private:\n";
	for(string variable : variables){
		cout << "\tuint num" << variable << " = 0;" << endl;
	}
	cout << "    public:\n";
	for(string variable : variables){
		cout << "\tvoid increment" << variable << "(){ num" << variable << "++; };" << endl
			 << "\tint getTotal" << variable << "(){ return num" << variable << "; };" << endl;
	}
	cout << endl;

	for(string variable : variables){
		cout << "                 << \"" << variable << ": \" << num" << variable << " << endl" << endl;
	}
	// */

	// /*
	cout << boolalpha;
	string filePath = "./entity.entity";
	
	ifstream entityFile(filePath, ifstream::binary);
	Json::Value data;
	entityFile >> data;

	// data["export"].asString();
	// data["guid"].asString();
	// data["id"].asString();

	list<animation>* animations = getAnimations(data);
	// printAnimationData(animations);

	list<keyframe*>* keyframes = getKeyframes(data);
	// printKeyframeData(keyframes);

	list<layer*>* layers = getLayers(data);
	// printLayerData(layers);

	paletteMap* paletteMap = getPaletteMap(data);
	// printPaletteMapData(paletteMap);

	list<symbol*>* symbols = getSymbols(data);
	// printSymbolData(symbols);

	tracker.printStats();

	// */

}

void printTitle(string title){
	cout << "=========================================\n";
	cout << title << endl;
	cout << "=========================================\n";
}

list<animation>* getAnimations(Json::Value data){
	const string sectionName = "animations";
	list<animation> *extractedAnimations = new list<animation>;

	uint dataIndex = 0;
	while(data[sectionName][dataIndex]){
		Json::Value dataSnippit = data[sectionName][dataIndex];
		animation entry;
		
		entry.id = dataSnippit["$id"].asString();
		entry.name = dataSnippit["name"].asString();

		uint layerIndex = 0;
		while(dataSnippit["layers"][layerIndex]){
			entry.layerIDs.push_back(dataSnippit["layers"][layerIndex].asString());
			layerIndex++;
		}

		extractedAnimations->push_back(entry);
		tracker.incrementAnimations();

		dataIndex++;
	}

	return extractedAnimations;
}

void printAnimationData(list<animation>* data){
	printTitle("Animations");
	for(animation entry : *data){
		cout << entry.name << endl;
		cout << "\tid: " << entry.id << endl;
		
		cout << "\tlayer IDs:\n";
		for(string layerID : entry.layerIDs){
			cout << "\t\t" << layerID << endl;
		}
	}
}

list<keyframe*>* getKeyframes(Json::Value data){
	const string sectionName = "keyframes";
	list<keyframe*> *extractedKeyframes = new list<keyframe*>;

	uint dataIndex = 0;
	while(data[sectionName][dataIndex]){
		Json::Value dataSnippit = data[sectionName][dataIndex];
		keyframe* entry = extractKeyframeByType(dataSnippit);
		
		entry->id = dataSnippit["$id"].asString();
		entry->length = dataSnippit["length"].asUInt();

		extractedKeyframes->push_back(entry);
		tracker.incrementKeyframes();

		dataIndex++;
	}

	return extractedKeyframes;
}

keyframe* extractKeyframeByType(Json::Value keyframeData){
	KEYFRAME_LAYER_TYPE type = mapToKeyframeLayerType[keyframeData["type"].asString()];
	
	if(type == KL_FRAME_SCRIPT){
		tracker.incrementScriptKeyframes();

		keyframeScript* keyframe = new keyframeScript;
		keyframe->code = keyframeData["code"].asString();
		return keyframe;
	}
	else if(
		type == KL_IMAGE ||
		type == KL_COLLISION_BOX ||
		type == KL_COLLISION_BODY || 
		type == KL_POINT || 
		type == KL_LINE_SEGMENT
	){
		if(type == KL_IMAGE){ tracker.incrementImageKeyframes(); }
		else if(type == KL_COLLISION_BOX){ tracker.incrementCollisionBoxKeyframes(); }
		else if(type == KL_COLLISION_BODY){ tracker.incrementCollisionBodyKeyframes(); }
		else if(type == KL_POINT){ tracker.incrementPointKeyframes(); }
		else if(type == KL_LINE_SEGMENT){ tracker.incrementLineSegmentKeyframes(); }

		keyframeAnimated* keyframe = new keyframeAnimated(type);
		keyframe->symbolID = keyframeData["symbol"].asString();
		keyframe->tweenType = mapToTweenType[keyframeData["tweenType"].asString()];
		keyframe->tweened = keyframeData["tweened"].asBool();

		if(!keyframe->tweened){
			return keyframe;
		}
		if(keyframe->tweenType == LINEAR){ tracker.incrementLinearTweens(); }
		else if(keyframe->tweenType == EASE_IN_QUAD){ tracker.incrementEaseInTweens(); tracker.incrementQuadTweens(); }
		else if(keyframe->tweenType == EASE_OUT_QUAD){ tracker.incrementEaseOutTweens(); tracker.incrementQuadTweens(); }
		else if(keyframe->tweenType == EASE_IN_OUT_QUAD){ tracker.incrementEaseInOutTweens(); tracker.incrementQuadTweens(); }
		else if(keyframe->tweenType == EASE_IN_CUBIC){ tracker.incrementEaseInTweens(); tracker.incrementCubicTweens(); }
		else if(keyframe->tweenType == EASE_OUT_CUBIC){ tracker.incrementEaseOutTweens(); tracker.incrementCubicTweens(); }
		else if(keyframe->tweenType == EASE_IN_OUT_CUBIC){ tracker.incrementEaseInOutTweens(); tracker.incrementCubicTweens(); }
		else if(keyframe->tweenType == EASE_IN_QUART){ tracker.incrementEaseInTweens(); tracker.incrementQuartTweens(); }
		else if(keyframe->tweenType == EASE_OUT_QUART){ tracker.incrementEaseOutTweens(); tracker.incrementQuartTweens(); }
		else if(keyframe->tweenType == EASE_IN_OUT_QUART){ tracker.incrementEaseInOutTweens(); tracker.incrementQuartTweens(); }
		else if(keyframe->tweenType == EASE_IN_QUINT){ tracker.incrementEaseInTweens(); tracker.incrementQuintTweens(); }
		else if(keyframe->tweenType == EASE_OUT_QUINT){ tracker.incrementEaseOutTweens(); tracker.incrementQuintTweens(); }
		else if(keyframe->tweenType == EASE_IN_OUT_QUINT){ tracker.incrementEaseInOutTweens(); tracker.incrementQuintTweens(); }

		return keyframe;
	}
	else if(type == KL_LABEL){
		tracker.incrementLabelKeyframes();

		keyframeLabel* keyframe = new keyframeLabel;
		keyframe->name = keyframeData["name"].asString();
		return keyframe;
	}
	else if(type == KL_CONTAINER){
		tracker.incrementContainerKeyframes();

		keyframe* keyframe = new ::keyframe;
		keyframe->type = KL_CONTAINER;
		return keyframe;
	}

	return nullptr;
}

void printKeyframeData(list<keyframe*>* data){
	printTitle("Keyframes");
	for(keyframe* entry : *data){
		cout << "\tid: " << entry->id << endl;
		cout << "\tlength: " << entry->length << endl;
		cout << "\ttype: " << mapToKeyframeLayerTypeName[entry->type] << endl;

		printKeyframeTypeData(entry, entry->type);

		cout << endl;
	}
}

void printKeyframeTypeData(keyframe* data, KEYFRAME_LAYER_TYPE type){
	if(keyframeScript* converted = dynamic_cast<keyframeScript*>(data)){
		cout << "\tcode: \"" << converted->code << "\"" << endl;
	}
	else if(keyframeAnimated* converted = dynamic_cast<keyframeAnimated*>(data)){
		cout << "\tsymbolID: \"" << converted->symbolID << "\"" << endl;
		cout << "\ttweenType: " << converted->tweenType << endl;
		cout << "\ttweened: " << converted->tweened << endl;
	}
	else if(keyframeLabel* converted = dynamic_cast<keyframeLabel*>(data)){
		cout << "\tname: \"" << converted->name << "\"" << endl;
	}
}

list<layer*>* getLayers(Json::Value data){
	const string sectionName = "layers";
	list<layer*> *extractedLayers = new list<layer*>;

	uint dataIndex = 0;
	while(data[sectionName][dataIndex]){
		Json::Value dataSnippit = data[sectionName][dataIndex];
		layer* entry = extractLayerByType(dataSnippit);
		
		entry->id = dataSnippit["$id"].asString();
		entry->hidden = dataSnippit["hidden"].asBool();
		entry->locked = dataSnippit["locked"].asBool();
		entry->name = dataSnippit["name"].asString();
		
		uint keyframeIndex = 0;
		while(dataSnippit["keyframes"][keyframeIndex]){
			entry->keyframeIDs.push_back(dataSnippit["keyframes"][keyframeIndex].asString());
			keyframeIndex++;
		}

		extractedLayers->push_back(entry);
		tracker.incrementLayers();

		dataIndex++;
	}

	return extractedLayers;
}

layer* extractLayerByType(Json::Value layerData){
	KEYFRAME_LAYER_TYPE type = mapToKeyframeLayerType[layerData["type"].asString()];
	
	if(type == KL_FRAME_SCRIPT){
		tracker.incrementScriptLayers();

		layerScript* layer = new layerScript;
		layer->language = layerData["language"].asString();
		return layer;
	}
	else if(type == KL_COLLISION_BOX){
		tracker.incrementCollisionBoxLayers();

		layerCollisionBox* layer = new layerCollisionBox;
		layer->defaultAlpha = layerData["defaultAlpha"].asFloat();
		layer->defaultColor = layerData["defaultColor"].asString();
		
		// layer->collisionBoxType = 
		if(layerData["pluginMetadata"].compare("{}")){
			Json::Value snippit = layerData["pluginMetadata"]["com.fraymakers.FraymakersMetadata"];
			layer->collisionBoxType = mapToCollisionBoxType[snippit["collisionBoxType"].asString()];
			layer->collisionBoxIndex = snippit["index"].asInt();

			if(layer->collisionBoxType == NONE){ tracker.incrementNoneBoxes(); }
			else if(layer->collisionBoxType == HURT_BOX){ tracker.incrementHurtBoxes(); }
			else if(layer->collisionBoxType == HIT_BOX){ tracker.incrementHitBoxes(); }
			else if(layer->collisionBoxType == GRAB_BOX){ tracker.incrementGrabBoxes(); }
			else if(layer->collisionBoxType == LEDGE_GRAB_BOX){ tracker.incrementLedgeGrabBoxes(); }
			else if(layer->collisionBoxType == REFLECT_BOX){ tracker.incrementReflectBoxes(); }
			else if(layer->collisionBoxType == ABSORB_BOX){ tracker.incrementAbsorbBoxes(); }
			else if(layer->collisionBoxType == COUNTER_BOX){ tracker.incrementCounterBoxes(); }
			else if(layer->collisionBoxType == CUSTOM_BOX_A){ tracker.incrementCustomBoxAs(); }
			else if(layer->collisionBoxType == CUSTOM_BOX_B){ tracker.incrementCustomBoxBs(); }
			else if(layer->collisionBoxType == CUSTOM_BOX_C){ tracker.incrementCustomBoxCs(); }
		}
		return layer;
	}
	else if(type == KL_COLLISION_BODY){
		tracker.incrementCollisionBodyLayers();

		layerCollisionBody* layer = new layerCollisionBody;
		layer->defaultAlpha = layerData["defaultAlpha"].asFloat();
		layer->defaultColor = layerData["defaultColor"].asString();
		layer->defaultHead = layerData["defaultHead"].asUInt();
		layer->defaultHipWidth = layerData["defaultHipWidth"].asUInt();
		layer->defaultHipXOffset = layerData["defaultHipXOffset"].asUInt();
		layer->defaultHipYOffset = layerData["defaultHipYOffset"].asUInt();
		layer->defaultFoot = layerData["defaultFoot"].asUInt();
		return layer;
	}
	else if(type == KL_IMAGE){
		tracker.incrementImageLayers();

		layer* layer = new ::layer;
		layer->type = KL_IMAGE;
		return layer;
	}
	else if(type == KL_LABEL){
		tracker.incrementLabelLayers();
		
		layer* layer = new ::layer;
		layer->type = KL_LABEL;
		return layer;
	}
	else if(type == KL_POINT){
		tracker.incrementPointLayers();

		layer* layer = new ::layer;
		layer->type = KL_POINT;
		return layer;
	}
	else if(type == KL_LINE_SEGMENT){
		tracker.incrementLineSegmentLayers();

		layer* layer = new ::layer;
		layer->type = KL_LINE_SEGMENT;
		return layer;
	}
	else if(type == KL_CONTAINER){
		tracker.incrementContainerLayers();

		layer* layer = new ::layer;
		layer->type = KL_CONTAINER;
		return layer;
	}

	return nullptr;
}

void printLayerData(list<layer*>* data){
	printTitle("Layers");
	for(layer* entry : *data){
		cout << "\tname: " << entry->name << endl;
		cout << "\tid: " << entry->id << endl;
		cout << "\thidden: " << entry->hidden << endl;
		cout << "\tlocked: " << entry->locked << endl;

		cout << "\tkeyframe IDs:\n";
		for(string keyframeID : entry->keyframeIDs){
			cout << "\t\t" << keyframeID << endl;
		}
		cout << "\ttype: " << mapToKeyframeLayerTypeName[entry->type] << endl;

		printLayerTypeData(entry, entry->type);

		cout << endl;
	}
}

void printLayerTypeData(layer* data, KEYFRAME_LAYER_TYPE type){
	if(layerScript* converted = dynamic_cast<layerScript*>(data)){
		cout << "\tlanguage: \"" << converted->language << "\"" << endl;
	}
	else if(layerCollisionBox* converted = dynamic_cast<layerCollisionBox*>(data)){
		cout << "\tdefaultAlpha: " << converted->defaultAlpha << endl;
		cout << "\tdefaultColor: " << converted->defaultColor << endl;
		cout << "\tcollisionBoxType: " << mapToCollisionBoxTypeName[converted->collisionBoxType] << endl;
		cout << "\tindex: " << converted->collisionBoxIndex << endl;

	}
	else if(layerCollisionBody* converted = dynamic_cast<layerCollisionBody*>(data)){
		cout << "\tdefaultAlpha: " << converted->defaultAlpha << endl;
		cout << "\tdefaultColor: " << converted->defaultColor << endl;
		cout << "\tdefaultHead: " << converted->defaultHead << endl;
		cout << "\tdefaultHipWidth: " << converted->defaultHipWidth << endl;
		cout << "\tdefaultHipXOffset: " << converted->defaultHipXOffset << endl;
		cout << "\tdefaultHipYOffset: " << converted->defaultHipYOffset << endl;
		cout << "\tdefaultFoot: " << converted->defaultFoot << endl;
	}
}

paletteMap* getPaletteMap(Json::Value data){
	const string sectionName = "paletteMap";
	paletteMap *extractedPaletteMap = new paletteMap;

	extractedPaletteMap->palletteCollectionID =
		(data[sectionName]["paletteCollection"].asString() != "") ?
		data[sectionName]["paletteCollection"].asString() :
		"null";
	extractedPaletteMap->paletteMapID =
		(data[sectionName]["paletteMap"].asString() != "") ?
		data[sectionName]["paletteMap"].asString() :
		"null";

	return extractedPaletteMap;
}

void printPaletteMapData(paletteMap* data){
	printTitle("Palette Map");
	cout << "\tpaletteCollection ID: " << data->palletteCollectionID << endl;
	cout << "\tpaletteMap ID: " << data->paletteMapID << endl;
}

list<symbol*>* getSymbols(Json::Value data){
	const string sectionName = "symbols";
	list<symbol*> *extracteSymbols = new list<symbol*>;

	uint dataIndex = 0;
	while(data[sectionName][dataIndex]){
		Json::Value dataSnippit = data[sectionName][dataIndex];
		symbol* entry = extractSymbolByType(dataSnippit);

		entry->id = dataSnippit["$id"].asString();
		entry->alpha = dataSnippit["alpha"].asFloat();

		extracteSymbols->push_back(entry);
		tracker.incrementSymbols();

		dataIndex++;
	}

	return extracteSymbols;
}

symbol* extractSymbolByType(Json::Value symbolData){
	SYMBOL_TYPE type = mapToSymbolType[symbolData["type"].asString()];
	
	if(type == SYM_IMAGE){
		tracker.incrementImageSymbols();

		symbolImage* symbol = new symbolImage;
		symbol->x = symbolData["x"].asFloat();
		symbol->y = symbolData["y"].asFloat();
		symbol->rotation = symbolData["rotation"].asFloat();
		symbol->scaleX = symbolData["scaleX"].asFloat();
		symbol->scaleY = symbolData["scaleY"].asFloat();
		symbol->pivotX = symbolData["pivotX"].asFloat();
		symbol->pivotY = symbolData["pivotY"].asFloat();
		return symbol;
	}
	else if(type == SYM_COLLISION_BOX){
		tracker.incrementCollisionBoxSymbols();
		
		symbolCollisionBox* symbol = new symbolCollisionBox;
		symbol->color = symbolData["color"].asString();
		symbol->x = symbolData["x"].asFloat();
		symbol->y = symbolData["y"].asFloat();
		symbol->rotation = symbolData["rotation"].asFloat();
		symbol->scaleX = symbolData["scaleX"].asFloat();
		symbol->scaleY = symbolData["scaleY"].asFloat();
		symbol->pivotX = symbolData["pivotX"].asFloat();
		symbol->pivotY = symbolData["pivotY"].asFloat();
		return symbol;
	}
	else if(type == SYM_COLLISION_BODY){
		tracker.incrementCollisionBodySymbols();

		symbolCollisionBody* symbol = new symbolCollisionBody;
		symbol->color = symbolData["color"].asString();
		symbol->head = symbolData["head"].asFloat();
		symbol->hipWidth = symbolData["hipWidth"].asFloat();
		symbol->hipXOffset = symbolData["hipXOffset"].asFloat();
		symbol->hipYOffset = symbolData["hipYOffset"].asFloat();
		symbol->foot = symbolData["foot"].asFloat();
		return symbol;
	}
	else if(type == SYM_POINT){
		tracker.incrementPointSymbols();

		symbolPoint* symbol = new symbolPoint;
		symbol->color = symbolData["color"].asString();
		symbol->x = symbolData["x"].asFloat();
		symbol->y = symbolData["y"].asFloat();
		symbol->rotation = symbolData["rotation"].asFloat();
		return symbol;
	}
	else if(type == SYM_LINE_SEGMENT){
		tracker.incrementLineSegmentSymbols();

		symbolLineSegment* symbol = new symbolLineSegment;
		symbol->color = symbolData["color"].asString();
		symbol->x1 = symbolData["points"][0].asFloat();
		symbol->y1 = symbolData["points"][1].asFloat();
		symbol->x2 = symbolData["points"][2].asFloat();
		symbol->y2 = symbolData["points"][3].asFloat();
		return symbol;
	}

	return nullptr;
}

void printSymbolData(list<symbol*>* data){
	printTitle("Symbols");
	for(symbol* entry : *data){
		cout << "\tid: " << entry->id << endl;
		cout << "\talpha: " << entry->alpha << endl;

		printSymbolTypeData(entry, entry->type);

		cout << endl;
	}
}

void printSymbolTypeData(symbol* data, SYMBOL_TYPE type){
	if(symbolImage* converted = dynamic_cast<symbolImage*>(data)){
		cout << "\tx: " << converted->x << endl;
		cout << "\ty: " << converted->y << endl;
		cout << "\trotation: " << converted->rotation << endl;
		cout << "\tscaleX: " << converted->scaleX << endl;
		cout << "\tscaleY: " << converted->scaleY << endl;
		cout << "\tpivotX: " << converted->pivotX << endl;
		cout << "\tpivotY: " << converted->pivotY << endl;
	}
	else if(symbolCollisionBox* converted = dynamic_cast<symbolCollisionBox*>(data)){
		cout << "\tcolor: " << converted->color << endl;
		cout << "\tx: " << converted->x << endl;
		cout << "\ty: " << converted->y << endl;
		cout << "\trotation: " << converted->rotation << endl;
		cout << "\tscaleX: " << converted->scaleX << endl;
		cout << "\tscaleY: " << converted->scaleY << endl;
		cout << "\tpivotX: " << converted->pivotX << endl;
		cout << "\tpivotY: " << converted->pivotY << endl;
	}
	else if(symbolCollisionBody* converted = dynamic_cast<symbolCollisionBody*>(data)){
		cout << "\tcolor: " << converted->color << endl;
		cout << "\thead: " << converted->head << endl;
		cout << "\thipWidth: " << converted->hipWidth << endl;
		cout << "\thipXOffset: " << converted->hipXOffset << endl;
		cout << "\thipYOffset: " << converted->hipYOffset << endl;
		cout << "\tfoot: " << converted->foot << endl;
	}
	else if(symbolPoint* converted = dynamic_cast<symbolPoint*>(data)){
		cout << "\tcolor: " << converted->color << endl;
		cout << "\tx: " << converted->x << endl;
		cout << "\ty: " << converted->y << endl;
		cout << "\trotation: " << converted->rotation << endl;
	}
	else if(symbolLineSegment* converted = dynamic_cast<symbolLineSegment*>(data)){
		cout << "\tcolor: " << converted->color << endl;
		cout << "\tx1: " << converted->x1 << endl;
		cout << "\ty1: " << converted->y1 << endl;
		cout << "\tx2: " << converted->x2 << endl;
		cout << "\ty2: " << converted->y2 << endl;
	}
}

