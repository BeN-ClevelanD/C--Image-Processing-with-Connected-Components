#include "PGMimageProcessor.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <typeinfo>

int main(int argc, char *argv[])	{
	
	
	//sets up variables to capture commandline input to later feed into functions
	std::string inputFileName;
	int min_valid_comp_size;
	int max_valid_comp_size;
	int threshold_value;

	std::string out_image_name;
	
	//flags to see if the user has given the respective info per flag, so that defaults can be provided if they have not been given by the user
	bool sflag = false;
	bool tflag = false;
	bool pflag = false;
	bool wflag = false;
	
	
	//if there are no command line inputs other than the input file name then 
	if(argc == 2){
	inputFileName = argv[1];
	}
	else
	{
		
		
		inputFileName = argv[argc-1];
		
	}
	if(argc == 1)
	{
		std::cout << "Please try again and enter the required input file name" << std::endl;
	}
	
	//looping through command line inputs and collecting the inputs
	for(int x = 1; x < argc; ++x)
	{
		if(std::string(argv[x])  == "-s")
		{
			sflag = true;
			++x;
			min_valid_comp_size = std::stoi(argv[x]);
			++x;
			max_valid_comp_size = std::stoi(argv[x]);
			
		}
		
		if(std::string(argv[x])  == "-t")
		{
			tflag = true;
			++x;
			threshold_value = std::stoi(argv[x]);
		
			
		}
		
		if(std::string(argv[x])  == "-p")
		{
			pflag = true;
		
		
			
		}
		
		if(std::string(argv[x])  == "-w")
		{
			wflag = true;
			++x;
			out_image_name = argv[x];
		}
	
	}
	//if no threshold value is given by the user then it is set by default to 128
	if(tflag == false)
	{
		threshold_value = 128;
	}
	
	
	
	//create a PGMimageProcessor object
	PGMimageProcessor processor = PGMimageProcessor();
	//read in the image using the objects readInImage function
	processor.readInImage(inputFileName);

	
	//obtaining the image height and width in order to work with these values
	int pWidth = processor.returnImageWidth();
	int pHeight = processor.returnImageHeight();
	
	//if no min and max component size has been given by the user then these defaults are set
	if(!sflag)
	{
		min_valid_comp_size = 3;
		max_valid_comp_size = pWidth * pHeight;
	}
	

	//extracts components using the processor object's extractComponents method
	processor.extractComponents((unsigned char)(threshold_value), min_valid_comp_size);
	
	//filters components by size using the processor object's filterComponentsBySize method
	processor.filterComponentsBySize(min_valid_comp_size, max_valid_comp_size);

	
	
	
	
	//if the user has included the -p flag then all of the component info will be printed using the processor object's printAllComponentData method (which in turn uses the method printComponentData)
	if(pflag){
		
	processor.printAllComponentData(processor.getSmallestSize(),processor.getLargestSize());
	
	}
	
	//set the default output file name if no output file name has been specified by the user
	if(!wflag)
	{
			
		out_image_name = "Default_output.pgm";
	}
	//writes out the components using the processor object's writeComponents method	
	processor.writeComponents(out_image_name);

	
	
	
}
