
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <typeinfo>
#include "ConnectedComponent.h"


using namespace bnjcle001;

class PGMimageProcessor{
	
	
	private:
		
		//Private helper method to extractComponents()
		ConnectedComponent BFSalgo(int imgHeight, int imgWidth, int threshold, int pixelX, int pixelY, int component_id);
		
		//private 2d array to store image pixels (original image)
		unsigned char ** image_holder;
	
	public:
	
		int pHeight;
		int pWidth;
		
		
		
		//The big 6 method headers
		PGMimageProcessor();
		~PGMimageProcessor(void);
		PGMimageProcessor(const PGMimageProcessor & rhs);
		PGMimageProcessor(PGMimageProcessor && rhs);
		PGMimageProcessor & operator=(const PGMimageProcessor & rhs);
		PGMimageProcessor & operator=(PGMimageProcessor && rhs);
		
		
		
		//All other public method headers (defined (and explained via comments) in PGMimageProcessor.cpp )
		void printComponentData(const ConnectedComponent & theComponent) const;
		
		int extractComponents(unsigned char threshold, int minValidSize);
		
		int filterComponentsBySize(int minSize, int maxSize);
		
		int getLargestSize(void) const;
		
		int getSmallestSize(void) const;
		
		void printAllComponentData(int minCompSize, int maxCompSize);		
		
		int returnImageHeight(void);
		
		int returnImageWidth(void);

		std::vector< std::unique_ptr<ConnectedComponent> > comps;
	
		void readInImage(std::string inputFileName);
		
		bool writeComponents(const std::string & outFileName);
	
	
	
	
	
};

