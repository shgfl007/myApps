//
//  ofPetal.h
//  project
//
//  Created by Apple on 13-12-17.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef project_ofPetal_h
#define project_ofPetal_h
#include"ofMain.h"
#include"simpletest.h"

class ofPetal{
    
public: 
   
    ofPetal(int width, int height);
    void update();
    void drawpetal();
    void clear();
    int petals;
    
    
private:
    ofsimple **mysimple;
    float pwidth[7];
    float pheight[7];
    int npetal;
};



#endif
