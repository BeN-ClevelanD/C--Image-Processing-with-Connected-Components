#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include "PGMimageProcessor.h"






using namespace bnjcle001;


	
	//Custom constructor (and works as default constructor) of PGMimageProcessor class
	PGMimageProcessor::PGMimageProcessor(){};

	//Custom destructor for PGMimageProcessor class, deletes the dynamically allocated memory that was used to hold the original image, and then repurposed for the write out image
	PGMimageProcessor::~PGMimageProcessor(void)
	{
		for(int x = 0; x < pHeight; ++x)
			{
				delete image_holder[x];
			}
			
			delete image_holder;
			
	}
	//Custom copy constructor for PGMimageProcessor class
	PGMimageProcessor::PGMimageProcessor(const PGMimageProcessor & rhs) : pHeight(rhs.pHeight), pWidth(rhs.pWidth), image_holder(rhs.image_holder) {}
	//Custom move constructor for PGMimageProcessor class
	PGMimageProcessor::PGMimageProcessor(PGMimageProcessor && rhs) : pHeight(rhs.pHeight), pWidth(rhs.pWidth), image_holder(std::move(rhs.image_holder)) {}
	//Custom copy assignment operator for PGMimageProcessor class
	PGMimageProcessor & PGMimageProcessor::operator=(const PGMimageProcessor & rhs)
	{
		if(this != &rhs)
	{
		pHeight = rhs.pHeight;
		pWidth = rhs.pWidth;
		image_holder = rhs.image_holder;
		
	}
	return *this;
		
	}
	//Custom move assignment operator for PGMimageProcessor class
	PGMimageProcessor & PGMimageProcessor::operator=(PGMimageProcessor && rhs)
	{
		if(this != &rhs){
		pHeight = rhs.pHeight;
		pWidth = rhs.pWidth;
		image_holder = std::move(rhs.image_holder);
}
return *this;
	}
	//variables that will hold the original image's width and height
	int pWidth;
	int pHeight;
	//method to return the height of the image housed by the PGMimageProcessor object
	int PGMimageProcessor::returnImageHeight(void)
	{
		return pHeight;
	}
	
	//method to return the width of the image housed by the PGMimageProcessor object
	
	int PGMimageProcessor::returnImageWidth(void)
	{
		return pWidth;
	}
	
	//declaring 2d array for original picture so that i can access it in the rest of the class
	unsigned char ** image_holder;
	
	//method that iterates through the PGMprocessorImage object's vector of unique pointers, and removes the unique pointers pointing to ConnectedComponent objects that have a 
	//pixel count that is either larger than the maxSize or smaller than the minSize
	
	int PGMimageProcessor::filterComponentsBySize(int minSize, int maxSize)
	{
		//int place_tracker = 0;

		for(auto i = comps.begin(); i != comps.end(); ++i)
		{
			
			int sizer = i->get()->coords.size();
			if (sizer < minSize || sizer > maxSize)
			{	
				
				
				comps.erase(i);
				--i;
			
					
			}
			
			
			
		}
		//corrects the component id's to be coherent with their position in the vector
		for(int x = 0; x < comps.size(); ++x)
		{
			comps[x].get()->setComponentId(x);
		}
			
		
		return comps.size();
	}
	//Method that returns the number of pixels in the largest component by looping through the vector of pointers to ConnectedComponents (ie. looping through "comps") and comparing each component pixel
	//number to the current max pixel number
	int PGMimageProcessor::getLargestSize(void) const
	{
		int maxer = comps[0].get()->getNumPixels();
		for(int x = 1; x < comps.size(); ++x)
		{
			if (maxer < comps[x].get()->getNumPixels())
			{
				maxer = comps[x].get()->getNumPixels();
			}
		}
		
	
	return maxer;
	}
	//Method that returns the number of pixels in the smallest component by looping through the vector of pointers to ConnectedComponents (ie. looping through "comps") and comparing each component pixel
	//number to the current mminimum pixel number
	int PGMimageProcessor::getSmallestSize(void) const
	{
		int minner = comps[0].get()->getNumPixels();
		for(int x = 1; x <  comps.size(); ++x)
		{
			if (minner > comps[x].get()->getNumPixels())
			{
				minner = comps[x].get()->getNumPixels();
			}
		}
		
	
	return minner;
	}
	//method that prints the data for each component in comps using the "printComponentData" method as well as returning the total component number, and the max and min component pixel counts
	void PGMimageProcessor::printAllComponentData(int minCompSize, int maxCompSize)
	{
		
		for(int x = 0; x < comps.size(); ++x)
		{
			
			
			printComponentData((*(comps[x].get())));
			
		}
		
		std::cout << "Size of largest component " << std::to_string(maxCompSize) << std::endl;
		std::cout << "\n" << std::endl;
		
		std::cout << "Size of smallest component " << std::to_string(minCompSize) << std::endl;
		std::cout << "\n" << std::endl;
		
		std::cout << "Total number of components " << std::to_string(comps.size()) << std::endl;
		std::cout << "\n" << std::endl;
		
		
	}
	//Method that uses ConnectedComponent's accessor methods in order to print the data for a ConnectedComponent object
	void PGMimageProcessor::printComponentData(const ConnectedComponent & theComponent) const
	{
			std::cout << "Component id: " << std::to_string(theComponent.getComponentId()) << std::endl;
			std::cout << "Component number of pixels in component: " << std::to_string(theComponent.getNumPixels()) << std::endl;
			std::cout << "\n" << std::endl;
		
	}


	//Method that uses the helper method BFSalso to extract the component
	//Based on an input threshold size, the method will iterate from top left to bottom right through the image (image_holder) and will stop and call BFSalso when a pixel value bigger than or equal to
	//the threshold value is encountered. The BFSalso returns a ConnectedComponent object, which is used to create a new ConnectedComponent object, which is in turn used to create a unique pointer
	//that points to this ConnectedComponent object. If the new ConnectedComponent object obeys the minimum pixel size parameter, it is pushed back onto PGMimageProcessor's vector (comps)
	int PGMimageProcessor::extractComponents(unsigned char threshold, int minValidSize)
	{
		
		int id_tracker = 0;
		bool knowhow = false;
		
		for (int y = 0; y< pHeight; ++y)
		{
			
			for (int x = 0 ; x < pWidth; ++x)
			{
		
				
				
				
				if ((int)image_holder[y][x] >= threshold)
				{
					//creates new pointer with the new ConnectedComponent object
					std::unique_ptr<ConnectedComponent> newComponentPointer(new ConnectedComponent(BFSalgo(pHeight, pWidth, threshold, x, y, id_tracker)));
					//check to see if new ConnectedComponent object adheres to the minValidSize parameter
					if(newComponentPointer.get()->coords.size() >= minValidSize)
					{
						//if it adheres, push it back onto "comps"
						comps.push_back(std::move(newComponentPointer));
						//id's start at 0, and increments with each new component created
						++id_tracker;
					}
					
				}
			
				
			}
			
		
			
			
		}
		
		
	
		
		
		return comps.size();
	}
	

	//The BFSalgo follows a basic floodfill algorigthm implementation. It takes in image height and width, threshold size, an x and a y coordinate, and a component id 
	
	ConnectedComponent PGMimageProcessor::BFSalgo(int imgHeight, int imgWidth, int threshold, int pixelX, int pixelY, int component_id)
	{
		//creating a vector that will act as a q for nodes that need to be processed
		std::vector< std::pair<int,int> >process_queue;
		//create a pair object out of the x and y coordinates that are passed in (which will be the x and y coords of the start of the component, ie. where the extractComponents method encountered
		//a pixel value that met or exceeded the threshold value
		std::pair<int,int> pixel(pixelX,pixelY);
		//push the current (starting) pixel onto the q to be processed
		process_queue.push_back(pixel);
		
		//creating a temporary vector that wil collect all pixels that need to be added to a component later on
		std::vector< std::pair<int,int> > items;
		//since we know this first and current pixel adheres to the threshold requirement, we push it onto the temp vector, to be added to a component later
		items.push_back(pixel);
		//set the current pixel to 0 so that we can detect that it has been processed
		image_holder[pixelY][pixelX] = 0;
		
		
	
		//while the q still has pixels to be processed this loop will continue
		while(process_queue.size() > 0)
		{
			//creates a pair object using the pair object that is last on the vector which is the process_queue
			std::pair<int,int> thisPixel = process_queue.back();
			//removes the last element off the process_queue (ie the one we just used to make a pair object)
			process_queue.pop_back();
			
			//gets the x and y position of the pixel that was just popped off the process_queue
			int yer = thisPixel.second;
			int xer = thisPixel.first;
			
			//this checks to see if a pixel has already been processed, and if it has not, then we push it onto the temp vector that we will later use to create a component with
			//and we set the coords at this current pixel to 0 to show that it has been processed
			if (image_holder[yer][xer] != 0 )
			{
				
				items.push_back(thisPixel);
				image_holder[yer][xer] = 0;
			
			}
			
			//checks the neighbor above the current pixel, and if it is not outside of the image bounds and the pixel's value is larger than or equal to the threshold value, it is pushed onto the process_queue
			//to be processed
			if ( !(xer < 0 || yer +1 < 0 || imgWidth <= xer || imgHeight <= yer +1 || image_holder[yer +1][xer] < threshold))
			{
				//constructing a pair (pixel) using this neighbor's coord values
				pixel.first = xer;
				pixel.second = yer +1;
				process_queue.push_back(pixel);
			
			}
			//checks the neighbor to the left of the current pixel, and if it is not outside of the image bounds and the pixel's value is larger than or equal to the threshold value, it is pushed onto the process_queue
			//to be processed
			if(!(xer -1 < 0 || yer < 0 || imgWidth <= xer -1 || imgHeight <= yer || image_holder[yer][xer -1] < threshold))
			{
			//constructing a pair (pixel) using this neighbor's coord values
				pixel.first = xer - 1;
				pixel.second = yer;
				process_queue.push_back(pixel);
			
			}
		
			//checks the neighbor to the right of the current pixel, and if it is not outside of the image bounds and the pixel's value is larger than or equal to the threshold value, it is pushed onto the process_queue
			//to be processed
			if(!(xer +1 < 0 || yer < 0 || imgWidth <= xer +1 || imgHeight <= yer || image_holder[yer][xer +1] < threshold))
			{
				//constructing a pair (pixel) using this neighbor's coord values
				pixel.first = xer + 1;
				pixel.second = yer;
				process_queue.push_back(pixel);
		
			}
		//checks the neighbor below the current pixel, and if it is not outside of the image bounds and the pixel's value is larger than or equal to the threshold value, it is pushed onto the process_queue
			//to be processed
			if ( !(xer < 0 || yer -1 < 0 || imgWidth <= xer || imgHeight <= yer -1 || image_holder[yer -1][xer] < threshold))
			{
				//constructing a pair (pixel) using this neighbor's coord values
				
				
				pixel.first = xer;
				pixel.second = yer - 1;
				process_queue.push_back(pixel);
			
			}
		
			
		}
		
		
		//creates a new ConnectedComponent object that takes in the temp vectors size for num_pixel parameter, the passed in component_id, and the temp vector of pixels to be added to the component
		ConnectedComponent obbo = ConnectedComponent(items.size(), component_id, items);
		return obbo;
		
		
		
		
		
	}
	

	
	
	
	
	//reads in the PGM file line by line 
	
	void PGMimageProcessor::readInImage(std::string inputFileName){
	
	std::string firstLine;
	std::string lastLine;

	
		//Open up file with the inputFileName in binary and reading mode
		std::ifstream pgmfile (inputFileName, std::ifstream::binary);
		//to handle if a file name is not valid
		if(!pgmfile)
		{
			std::cout << "Invalid file name please try again" << std::endl;
			exit(1);
		}
		std::string line;
		std::getline(pgmfile, line);
		
		
		
		
	
		
		//loop to read in the variable number of comment lines
		std::getline(pgmfile, line);
		while(line.starts_with("#"))
		{

	
			std::getline(pgmfile, line);
			
		}

		//ead in and assign the width and height values of the PGM image
		std::stringstream is(line);
		is >> pWidth >> pHeight;

		//read in the max opacity value
		std::getline(pgmfile, line);
		//
	
		//Creating 2D array to house the image
		
		image_holder = new unsigned char *[pHeight];
		for(int x = 0 ; x < pHeight; ++x)
		
		{
			
		unsigned char * restofbytes = new unsigned char [pWidth];
		
		pgmfile.read((char *)restofbytes, pWidth);
		
	
		image_holder[x] = restofbytes;
	
		
		
		}
		
		pgmfile.close();
		
	}
	
	
	//method to write out the components in white onto a black backdrop	
	bool PGMimageProcessor::writeComponents(const std::string & outFileName){
		
		//loops through the original image and sets each pixel to black. Here I am REPURPOSING the memory originally used to house the image
			for(int y = 0 ; y < pHeight; ++y)
			{
				for (int x = 0; x < pWidth; ++x)
				{
					image_holder[y][x] = 0;
				}
			}
		//loops through the component list (comps) and writes over each black pixel that is in the position of one of the pixels in a component and makes it white
			for(int iter = 0; iter < comps.size(); ++iter)
			{
				for(int secondIter = 0; secondIter < comps[iter].get()->coords.size()-1; ++secondIter)
				{	
					
					int xpart = comps[iter].get()->coords[secondIter].first;
					int ypart = comps[iter].get()->coords[secondIter].second;
					image_holder[ypart][xpart] = 255;
								
				}
			}
		
			std::ofstream pgmfileOut (outFileName, std::ofstream::binary);
		//writes out the usual header fields for a PGM image
			pgmfileOut << "P5" << "\n";
			pgmfileOut << pWidth << " " << pHeight << "\n";
			pgmfileOut << 255 << "\n" ;
		//writes out the image_holders new contents to a PGM
			for(int x = 0; x < pHeight; ++x)
			{
				pgmfileOut.write((const char*)image_holder[x], pWidth);
			}
			
			
			return true;
	}
	
	
		
		
	
