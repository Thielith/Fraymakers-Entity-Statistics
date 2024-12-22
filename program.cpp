#include <iostream>
#include <fstream>

#include <list>

#include "program.h"
#include "stat-tracker.h"

using namespace std;

statTracker tracker;
enumTranslate enumTranslate;

void printRepetitiveCode();

int main(){
	// printRepetitiveCode();

	///*
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
	//*/

}

void printRepetitiveCode(){
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
	KEYFRAME_LAYER_TYPE type = enumTranslate.toKeyframeLayerEnum(keyframeData["type"].asString());
	
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
		keyframe->tweenType = enumTranslate.toTweenEnum(keyframeData["tweenType"].asString());
		keyframe->tweened = keyframeData["tweened"].asBool();

		if(!keyframe->tweened){
			return keyframe;
		}
		if(keyframe->tweenType == TW_LINEAR){ tracker.incrementLinearTweens(); }
		else if(keyframe->tweenType == TW_EASE_IN_QUAD){ tracker.incrementEaseInTweens(); tracker.incrementQuadTweens(); }
		else if(keyframe->tweenType == TW_EASE_OUT_QUAD){ tracker.incrementEaseOutTweens(); tracker.incrementQuadTweens(); }
		else if(keyframe->tweenType == TW_EASE_IN_OUT_QUAD){ tracker.incrementEaseInOutTweens(); tracker.incrementQuadTweens(); }
		else if(keyframe->tweenType == TW_EASE_IN_CUBIC){ tracker.incrementEaseInTweens(); tracker.incrementCubicTweens(); }
		else if(keyframe->tweenType == TW_EASE_OUT_CUBIC){ tracker.incrementEaseOutTweens(); tracker.incrementCubicTweens(); }
		else if(keyframe->tweenType == TW_EASE_IN_OUT_CUBIC){ tracker.incrementEaseInOutTweens(); tracker.incrementCubicTweens(); }
		else if(keyframe->tweenType == TW_EASE_IN_QUART){ tracker.incrementEaseInTweens(); tracker.incrementQuartTweens(); }
		else if(keyframe->tweenType == TW_EASE_OUT_QUART){ tracker.incrementEaseOutTweens(); tracker.incrementQuartTweens(); }
		else if(keyframe->tweenType == TW_EASE_IN_OUT_QUART){ tracker.incrementEaseInOutTweens(); tracker.incrementQuartTweens(); }
		else if(keyframe->tweenType == TW_EASE_IN_QUINT){ tracker.incrementEaseInTweens(); tracker.incrementQuintTweens(); }
		else if(keyframe->tweenType == TW_EASE_OUT_QUINT){ tracker.incrementEaseOutTweens(); tracker.incrementQuintTweens(); }
		else if(keyframe->tweenType == TW_EASE_IN_OUT_QUINT){ tracker.incrementEaseInOutTweens(); tracker.incrementQuintTweens(); }

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
		cout << "\ttype: " << enumTranslate.toString(entry->type) << endl;

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
	KEYFRAME_LAYER_TYPE type = enumTranslate.toKeyframeLayerEnum(layerData["type"].asString());
	
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
			layer->collisionBoxType = enumTranslate.toCollisionBoxEnum(snippit["collisionBoxType"].asString());
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
		cout << "\ttype: " << enumTranslate.toString(entry->type) << endl;

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
		cout << "\tcollisionBoxType: " << enumTranslate.toString(converted->collisionBoxType) << endl;
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
	SYMBOL_TYPE type = enumTranslate.toSymbolEnum(symbolData["type"].asString());
	
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

