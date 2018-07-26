#include <STEPCOUNT.hpp>

STEPCOUNT* STEPCOUNT::_pInstance = NULL;

STEPCOUNT* STEPCOUNT::getInstance(){
    if(!_pInstance)
    {
        _pInstance = new STEPCOUNT();
    }
    return _pInstance;
}

STEPCOUNT::STEPCOUNT(){
    //does nothing
}

uint8_t STEPCOUNT::calculateSteps(uint8_t* fifo){
    for(int i=0; i<32; i++)
    {
        
    }
    return 0;
}