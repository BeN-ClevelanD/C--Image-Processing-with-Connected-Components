#include "ConnectedComponent.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <typeinfo>




using namespace bnjcle001;

//custom constructor for ConnectedComponent class
ConnectedComponent::ConnectedComponent(int numpixels, int componentid, std::vector< std::pair<int,int> > items)
{
	num_pixels = numpixels;
	component_id = componentid;
	for(int x = 0; x < items.size(); ++x)
	{
		coords.push_back(items[x]);
	}
	
	
}


//default constructor for ConnectedComponent class
ConnectedComponent::ConnectedComponent(void): num_pixels(0), component_id(0){}
//custom destructor for ConnectedComponent class
ConnectedComponent::~ConnectedComponent(void){}
//custom copy constructor for ConnectedComponent class
ConnectedComponent::ConnectedComponent(const ConnectedComponent & rhs) : num_pixels(rhs.num_pixels), component_id(rhs.component_id), coords(rhs.coords){}
//custom move constructor for ConnectedComponent class
ConnectedComponent::ConnectedComponent(ConnectedComponent && rhs) : num_pixels(rhs.num_pixels), component_id(rhs.component_id), coords(std::move(rhs.coords)){}
//custom copy assignment operator for ConnectedComponent class
ConnectedComponent & ConnectedComponent::operator=(const ConnectedComponent & rhs) 
{
	if(this != &rhs)
	{
		num_pixels = rhs.num_pixels;
		component_id = rhs.component_id;
		coords = rhs.coords;
		
	}
	return *this;
}
//custom move assignment operator for ConnectedComponent class
ConnectedComponent & ConnectedComponent::operator=(ConnectedComponent && rhs)
{
	if(this != &rhs){
	num_pixels = rhs.num_pixels;
	component_id = rhs.component_id;
	coords = std::move(rhs.coords);
}
return *this;
}
//Method that returns private variable num_pixels
int ConnectedComponent::getNumPixels(void) const
{
	return num_pixels;
}
//Method that returns private variable component_id
int ConnectedComponent::getComponentId(void) const
		{
			return component_id;
		}

//Method that sets private variable num_pixels
void ConnectedComponent::setNumPixels(int value)
	{
		num_pixels = value;
	}
//Method that sets private variable component_id
void ConnectedComponent::setComponentId(int value)
{
	component_id = value;
}
