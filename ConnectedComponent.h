#ifndef __CONNECTEDCOMPONENT__
#define __CONNECTEDCOMPONENT__




#include <memory>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <typeinfo>

namespace bnjcle001{
	class ConnectedComponent{
		
	private:
	
		
		int component_id;
		int num_pixels;
	
	public:


		
		std::vector< std::pair<int,int> > coords;
		
		
		//The big 6
		ConnectedComponent(int numpixels, int componentid, std::vector< std::pair<int,int> > items);
		ConnectedComponent(void);
		~ConnectedComponent(void);
		ConnectedComponent(const ConnectedComponent & rhs);
		ConnectedComponent(ConnectedComponent && rhs);
		ConnectedComponent & operator=(const ConnectedComponent & rhs);
		ConnectedComponent & operator=(ConnectedComponent && rhs);
		
		
		void setNumPixels(int value);
		void setComponentId(int value);
		int getNumPixels(void) const;
		
		int getComponentId(void) const;
		
	
		
		
	};
	
	
	
}

#endif
