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

void STEPCOUNT::init(){
    for(int i = 0; i < FIFOLENGTH; i++)
    {
    *(tempStorage+i) = 0;
    *(tempStorage2+i) = 0;
    *(diffSum+i) = 0;
    }
}

void STEPCOUNT::calculateSteps(int16_t* fifo, uint16_t* steps){
    //int counter = 0;
    for(int i=1; i<FIFOLENGTH; i++)
    {
        *(tempStorage + i) = sq(*(fifo + i) - *(fifo  + (i-1)));  //square the difference
        if(i > 4)
        {
            *(tempStorage2 + i) = *(tempStorage+(i-3)) + *(tempStorage+(i-2)) + *(tempStorage+(i-1)) + *(tempStorage+i);                   //sum the squared differences, integrate
            if(i > 5)
            {
                    *(diffSum + i) = (-(*(tempStorage2+(i-4))-(2 * (*(tempStorage2+(i-3))))) + (*(tempStorage2+(i-1))+ (2 * (*(tempStorage2+(i))))));        //find the difference in the integrals
            }
        }
        //delay(5);
    }

    uint8_t stepscalc = findPeaks(diffSum);
    updateSteps(steps,stepscalc);

}

void STEPCOUNT::updateSteps(uint16_t* pdata, uint8_t data){
    *(pdata) = data + *(pdata);
}

uint8_t STEPCOUNT::findPeaks(int16_t* pArray){
    uint8_t flag = 0;
    uint8_t steps = 0;
    for(int i=0;i<FIFOLENGTH; i++){
        if (*(pArray+i) > THRESHOLD && *(pArray+i) < OVERTHRESHOLD && flag==0)
        {
            //Serial.println(*(pArray+i));
            steps=steps+1;
            flag=1;
        }
        else if (*(pArray+i) > THRESHOLD && flag==1)
        {
            //do nothing 
        }
        if (*(pArray + i) < THRESHOLD  && flag==1)
        {
            flag=0;
        }
    }
    return steps;
}