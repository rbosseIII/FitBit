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

void STEPCOUNT::calculateSteps(uint8_t* fifo, uint8_t* steps){
    int counter = 0;
    for(int i=0; i<FIFOLENGTH; i++)
    {

        counter ++;
    }
}

void STEPCOUNT::updateSteps(uint8_t* pdata){
    
}