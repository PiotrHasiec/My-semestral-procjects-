#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include "Field.h"
#include "GameControler.h"
#include <vector>
#include<iostream>
#include <cmath>
#include "MyQueue.h"
//#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <thread>
                                        
                                        
                                        

int main()
{
   //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    bool color = 1;
    GameControler gc{color,85};
    gc.Run();

    return 0;
}
