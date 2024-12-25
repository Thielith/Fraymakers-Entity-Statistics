#include "main.h"

using namespace std;

int main(int argc, char *argv[]){
	// printRepetitiveCode();

	if(argc < 2){
		printHelpMessage();
		return 0;
	}

	bool fileDefined = false;
	string filePath;
	bool outputDefined = false;
	string outputFilePath = "";

	int i=1;
	while(i<argc){
		// cout << "Argument " << i << ": " << argv[i] << endl;
		string argument(argv[i]);

		if(!argument.compare("-h")){
			printHelpMessage();
			return 0;
		}
		else if(!fileDefined && (!argument.compare("--file") || !argument.compare("-f"))){
			fileDefined = true;

			string path(argv[i+1]);
			filePath = path;
			i++;
		}
		else if(!outputDefined && (!argument.compare("--output") || !argument.compare("-o"))){
			outputDefined = true;

			string file(argv[i+1]);
			outputFilePath = file;
			
			i += 2;
		}

		i++;
	}
	
	if(!fileDefined){
		cout << "Error: No file defined.\n";
		return -1;
	}

	entityDataExtractor extractor;
	extractor.extractEntityData(filePath);
	extractor.printStats(outputFilePath);

}

void printRepetitiveCode(){
	string variables[] = {
		"Animations", "LayersInAllAnimations",

		"Keyframes", "ImageKeyframes", "ScriptKeyframes", "LabelKeyframes",
		"CollisionBoxKeyframes", "CollisionBodyKeyframes", "PointKeyframes",
		"LineSegmentKeyframes", "ContainerKeyframes",
		"TweensEnabled",
		"LinearTweens", "EaseInTweens", "EaseOutTweens", "EaseInOutTweens",
		"QuadTweens", "CubicTweens", "QuartTweens", "QuintTweens",

		"Layers", "ImageLayers", "ScriptLayers", "LabelLayers",
		"CollisionBoxLayers", "CollisionBodyLayers", "PointLayers",
		"LineSegmentLayers", "ContainerLayers",

		"NoneBoxes", "HurtBoxes", "HitBoxes", "GrabBoxes", "LedgeGrabBoxes",
		"ReflectBoxes", "AbsorbBoxes", "CounterBoxes",
		"CustomBoxAs", "CustomBoxBs", "CustomBoxCs",

		"Symbols", "ImageSymbols", "CollisionBoxSymbols",
		"CollisionBodySymbols", "PointSymbols", "LineSegmentSymbols"
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

void printHelpMessage(){
	cout << "Usage:  program -f [file] [options]\n"
		 << endl;

	cout << "Options:\n"
		 << setw(30) << left << "-h:" << "Prints program usage" << endl
		 << setw(30) << left << "-f, --file [path]" << "Path to .entity file" << endl
		 << setw(30) << left << "-o, --output [path+name]" << "Outputs statistics to a file named [name] in [path]" << endl

		 << endl;
}

