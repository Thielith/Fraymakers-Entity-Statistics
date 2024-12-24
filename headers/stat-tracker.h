#ifndef ENTITY_DATA_STAT_TRACKER_H
#define ENTITY_DATA_STAT_TRACKER_H

#include <iostream>
#include <fstream>
#include <streambuf>

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

		void printStats(std::string outputPath = ""){
			std::ofstream output(outputPath);
			
			std::streambuf* coutBuf = std::cout.rdbuf();
			if(outputPath.compare("")){
				std::cout.rdbuf(output.rdbuf());
			}

			std::cout << std::boolalpha;
			
			std::cout << ".----------------------------.\n"
				 << "|   Entity Stats According   |\n"
				 << "|         To The File        |\n"
				 << "'----------------------------'\n\n";
				 
            std::cout << "Animations: " << numAnimations << std::endl
				 << "Average number of layers per animation: " << getAverageLayersPerAnimation() << std::endl
				 << std::endl;

            std::cout << "Unique keyframes: " << numKeyframes << std::endl
                 << "Unique image keyframes: " << numImageKeyframes << std::endl
                 << "Unique script keyframes: " << numScriptKeyframes << std::endl
                 << "Unique label keyframes: " << numLabelKeyframes << std::endl
                 << "Unique collision box keyframes: " << numCollisionBoxKeyframes << std::endl
                 << "Unique collision body keyframes: " << numCollisionBodyKeyframes << std::endl
                 << "Unique point keyframes: " << numPointKeyframes << std::endl
                 << "Unique line segment keyframes: " << numLineSegmentKeyframes << std::endl
                 << "Unique container keyframes: " << numContainerKeyframes << std::endl
				 << std::endl;

			std::cout << "Tweened keyframes: " << numTweensEnabled << std::endl
                 << "Linear tweens: " << numLinearTweens << std::endl
                 << "Ease in tweens: " << numEaseInTweens << std::endl
                 << "Ease out tweens: " << numEaseOutTweens << std::endl
                 << "Ease in out tweens: " << numEaseInOutTweens << std::endl
                 << "Quad tweens: " << numQuadTweens << std::endl
                 << "Cubic tweens: " << numCubicTweens << std::endl
                 << "Quart tweens: " << numQuartTweens << std::endl
                 << "Quint tweens: " << numQuintTweens << std::endl
				 << std::endl;

			std::cout << "Percentage of keyframes tweened: " << getPercentOfKeyframesTweened() << "%" << std::endl
				 << std::endl;

            std::cout << "Layers: " << numLayers << std::endl
                 << "Image layers: " << numImageLayers << std::endl
                 << "Script layers: " << numScriptLayers << std::endl
                 << "Label layers: " << numLabelLayers << std::endl
                 << "Collision box layers: " << numCollisionBoxLayers << std::endl
                 << "Collision body layers: " << numCollisionBodyLayers << std::endl
                 << "Point layers: " << numPointLayers << std::endl
                 << "Line segment layers: " << numLineSegmentLayers << std::endl
                 << "Container layers: " << numContainerLayers << std::endl
				 << std::endl;

            std::cout << "Collision Box Types:\n"
				 << "None boxes: " << numNoneBoxes << std::endl
                 << "Hurt boxes: " << numHurtBoxes << std::endl
                 << "Hit boxes: " << numHitBoxes << std::endl
                 << "Grab boxes: " << numGrabBoxes << std::endl
                 << "Ledge grab boxes: " << numLedgeGrabBoxes << std::endl
                 << "Reflect boxes: " << numReflectBoxes << std::endl
                 << "Absorb boxes: " << numAbsorbBoxes << std::endl
                 << "Counter boxes: " << numCounterBoxes << std::endl
                 << "Custom box As: " << numCustomBoxAs << std::endl
                 << "Custom box Bs: " << numCustomBoxBs << std::endl
                 << "Custom box Cs: " << numCustomBoxCs << std::endl
				 << std::endl;
			
			std::cout << "Symbols: " << numSymbols << std::endl
                 << "Image symbols: " << numImageSymbols << std::endl
                 << "Collision box symbols: " << numCollisionBoxSymbols << std::endl
                 << "Collision body symbols: " << numCollisionBodySymbols << std::endl
                 << "Point symbols: " << numPointSymbols << std::endl
                 << "Line segment symbols: " << numLineSegmentSymbols << std::endl

				 << std::endl;
			
			std::cout.rdbuf(coutBuf);
			output.close();
		}
};

#endif