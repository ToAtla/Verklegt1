//
//  PrepUI.hpp
//  PizzaKerfi
//
//  Created by Nokkvi Karlsson on 11/29/17.
//  Copyright © 2017 Þórður Atlason. All rights reserved.
//

#ifndef PrepUI_hpp
#define PrepUI_hpp

#include <stdio.h>
#include "Global.hpp"

class PrepUI{
public:
    void startPrepUI();
private:
    void waitingOverview();
    void preppingOverview();
    void readyOverview();
};
#endif /* PrepUI_hpp */
