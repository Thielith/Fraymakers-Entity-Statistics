#include <iostream>
#include <fstream>
#include <streambuf>
using namespace std;

class statTracker {
    private:
        unsigned int numAnimations = 0;

		unsigned int numKeyframes = 0;
        unsigned int numImageKeyframes = 0;
        unsigned int numScriptKeyframes = 0;
        unsigned int numLabelKeyframes = 0;
        unsigned int numCollisionBoxKeyframes = 0;
        unsigned int numCollisionBodyKeyframes = 0;
        unsigned int numPointKeyframes = 0;
        unsigned int numLineSegmentKeyframes = 0;
        unsigned int numContainerKeyframes = 0;
		
		unsigned int numTweensEnabled = 0;
        unsigned int numLinearTweens = 0;
        unsigned int numEaseInTweens = 0;
        unsigned int numEaseOutTweens = 0;
        unsigned int numEaseInOutTweens = 0;
        unsigned int numQuadTweens = 0;
        unsigned int numCubicTweens = 0;
        unsigned int numQuartTweens = 0;
        unsigned int numQuintTweens = 0;

        unsigned int numLayers = 0;
        unsigned int numImageLayers = 0;
        unsigned int numScriptLayers = 0;
        unsigned int numLabelLayers = 0;
        unsigned int numCollisionBoxLayers = 0;
        unsigned int numCollisionBodyLayers = 0;
        unsigned int numPointLayers = 0;
        unsigned int numLineSegmentLayers = 0;
        unsigned int numContainerLayers = 0;

        unsigned int numNoneBoxes = 0;
        unsigned int numHurtBoxes = 0;
        unsigned int numHitBoxes = 0;
        unsigned int numGrabBoxes = 0;
        unsigned int numLedgeGrabBoxes = 0;
        unsigned int numReflectBoxes = 0;
        unsigned int numAbsorbBoxes = 0;
        unsigned int numCounterBoxes = 0;
        unsigned int numCustomBoxAs = 0;
        unsigned int numCustomBoxBs = 0;
        unsigned int numCustomBoxCs = 0;

		unsigned int numSymbols = 0;
        unsigned int numImageSymbols = 0;
        unsigned int numCollisionBoxSymbols = 0;
        unsigned int numCollisionBodySymbols = 0;
        unsigned int numPointSymbols = 0;
        unsigned int numLineSegmentSymbols = 0;
    public:
		float getAverageLayersPerAnimation(){ return (float)numLayers / numAnimations; };
		float getPercentOfKeyframesTweened(){
			return (numTweensEnabled == 0)?
				0
			  : (float)numKeyframes / numTweensEnabled;
		};

        void incrementAnimations(){ numAnimations++; };
        unsigned int getTotalAnimations(){ return numAnimations; };

        void incrementKeyframes(){ numKeyframes++; };
        unsigned int getTotalKeyframes(){ return numKeyframes; };
        void incrementImageKeyframes(){ numImageKeyframes++; };
        unsigned int getTotalImageKeyframes(){ return numImageKeyframes; };
        void incrementScriptKeyframes(){ numScriptKeyframes++; };
        unsigned int getTotalScriptKeyframes(){ return numScriptKeyframes; };
        void incrementLabelKeyframes(){ numLabelKeyframes++; };
        unsigned int getTotalLabelKeyframes(){ return numLabelKeyframes; };
        void incrementCollisionBoxKeyframes(){ numCollisionBoxKeyframes++; };
        unsigned int getTotalCollisionBoxKeyframes(){ return numCollisionBoxKeyframes; };
        void incrementCollisionBodyKeyframes(){ numCollisionBodyKeyframes++; };
        unsigned int getTotalCollisionBodyKeyframes(){ return numCollisionBodyKeyframes; };
        void incrementPointKeyframes(){ numPointKeyframes++; };
        unsigned int getTotalPointKeyframes(){ return numPointKeyframes; };
        void incrementLineSegmentKeyframes(){ numLineSegmentKeyframes++; };
        unsigned int getTotalLineSegmentKeyframes(){ return numLineSegmentKeyframes; };
        void incrementContainerKeyframes(){ numContainerKeyframes++; };
        unsigned int getTotalContainerKeyframes(){ return numContainerKeyframes; };
		
		void incrementTweensEnabled(){ numTweensEnabled++; };
		unsigned int getTotalTweensEnabled(){ return numTweensEnabled; };
        void incrementLinearTweens(){ numLinearTweens++; };
        unsigned int getTotalLinearTweens(){ return numLinearTweens; };
        void incrementEaseInTweens(){ numEaseInTweens++; };
        unsigned int getTotalEaseInTweens(){ return numEaseInTweens; };
        void incrementEaseOutTweens(){ numEaseOutTweens++; };
        unsigned int getTotalEaseOutTweens(){ return numEaseOutTweens; };
        void incrementEaseInOutTweens(){ numEaseInOutTweens++; };
        unsigned int getTotalEaseInOutTweens(){ return numEaseInOutTweens; };
        void incrementQuadTweens(){ numQuadTweens++; };
        unsigned int getTotalQuadTweens(){ return numQuadTweens; };
        void incrementCubicTweens(){ numCubicTweens++; };
        unsigned int getTotalCubicTweens(){ return numCubicTweens; };
        void incrementQuartTweens(){ numQuartTweens++; };
        unsigned int getTotalQuartTweens(){ return numQuartTweens; };
        void incrementQuintTweens(){ numQuintTweens++; };
        unsigned int getTotalQuintTweens(){ return numQuintTweens; };

        void incrementLayers(){ numLayers++; };
        unsigned int getTotalLayers(){ return numLayers; };
        void incrementImageLayers(){ numImageLayers++; };
        unsigned int getTotalImageLayers(){ return numImageLayers; };
        void incrementScriptLayers(){ numScriptLayers++; };
        unsigned int getTotalScriptLayers(){ return numScriptLayers; };
        void incrementLabelLayers(){ numLabelLayers++; };
        unsigned int getTotalLabelLayers(){ return numLabelLayers; };
        void incrementCollisionBoxLayers(){ numCollisionBoxLayers++; };
        unsigned int getTotalCollisionBoxLayers(){ return numCollisionBoxLayers; };
        void incrementCollisionBodyLayers(){ numCollisionBodyLayers++; };
        unsigned int getTotalCollisionBodyLayers(){ return numCollisionBodyLayers; };
        void incrementPointLayers(){ numPointLayers++; };
        unsigned int getTotalPointLayers(){ return numPointLayers; };
        void incrementLineSegmentLayers(){ numLineSegmentLayers++; };
        unsigned int getTotalLineSegmentLayers(){ return numLineSegmentLayers; };
        void incrementContainerLayers(){ numContainerLayers++; };
        unsigned int getTotalContainerLayers(){ return numContainerLayers; };

        void incrementNoneBoxes(){ numNoneBoxes++; };
        unsigned int getTotalNoneBoxes(){ return numNoneBoxes; };
        void incrementHurtBoxes(){ numHurtBoxes++; };
        unsigned int getTotalHurtBoxes(){ return numHurtBoxes; };
        void incrementHitBoxes(){ numHitBoxes++; };
        unsigned int getTotalHitBoxes(){ return numHitBoxes; };
        void incrementGrabBoxes(){ numGrabBoxes++; };
        unsigned int getTotalGrabBoxes(){ return numGrabBoxes; };
        void incrementLedgeGrabBoxes(){ numLedgeGrabBoxes++; };
        unsigned int getTotalLedgeGrabBoxes(){ return numLedgeGrabBoxes; };
        void incrementReflectBoxes(){ numReflectBoxes++; };
        unsigned int getTotalReflectBoxes(){ return numReflectBoxes; };
        void incrementAbsorbBoxes(){ numAbsorbBoxes++; };
        unsigned int getTotalAbsorbBoxes(){ return numAbsorbBoxes; };
        void incrementCounterBoxes(){ numCounterBoxes++; };
        unsigned int getTotalCounterBoxes(){ return numCounterBoxes; };
        void incrementCustomBoxAs(){ numCustomBoxAs++; };
        unsigned int getTotalCustomBoxAs(){ return numCustomBoxAs; };
        void incrementCustomBoxBs(){ numCustomBoxBs++; };
        unsigned int getTotalCustomBoxBs(){ return numCustomBoxBs; };
        void incrementCustomBoxCs(){ numCustomBoxCs++; };
        unsigned int getTotalCustomBoxCs(){ return numCustomBoxCs; };

        void incrementSymbols(){ numSymbols++; };
        unsigned int getTotalSymbols(){ return numSymbols; };
        void incrementImageSymbols(){ numImageSymbols++; };
        unsigned int getTotalImageSymbols(){ return numImageSymbols; };
        void incrementCollisionBoxSymbols(){ numCollisionBoxSymbols++; };
        unsigned int getTotalCollisionBoxSymbols(){ return numCollisionBoxSymbols; };
        void incrementCollisionBodySymbols(){ numCollisionBodySymbols++; };
        unsigned int getTotalCollisionBodySymbols(){ return numCollisionBodySymbols; };
        void incrementPointSymbols(){ numPointSymbols++; };
        unsigned int getTotalPointSymbols(){ return numPointSymbols; };
        void incrementLineSegmentSymbols(){ numLineSegmentSymbols++; };
        unsigned int getTotalLineSegmentSymbols(){ return numLineSegmentSymbols; };

		void printStats(string outputPath = ""){
			ofstream output(outputPath);
			
			streambuf* coutBuf = cout.rdbuf();
			if(outputPath.compare("")){
				cout.rdbuf(output.rdbuf());
			}

			cout << boolalpha;
			
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
			
			cout.rdbuf(coutBuf);
			output.close();
		}
};