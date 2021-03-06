#include <iostream> 
#include <thread>
#include <mutex> 

using namespace std; 
          
float measured = 0.0;
int records  = 1; 
string unitsSymbol;
mutex doorx; 

class deviceMeasurements {
   public:    
   // virtual function providing interface for the sevcondary class.
   virtual float getFacts() = 0;
   protected:
      double lighting = 9.00;        float temperature = 8.00;      
      double presure = 7.00;         float powerlev = 5.00;           
      double unitBox =  999999.999;  string deviceName;                
};
            // secondary classes
class deviceMaker: public deviceMeasurements {
   public:
     float getFacts() {   return (unitBox * unitBox); }
     void operator()(int x, string deviceName)     { 
         doorx.lock(); 
         {     
         auto timenow = chrono::system_clock::to_time_t(chrono::system_clock::now());
         this_thread::sleep_for(chrono::seconds(1));

         if(deviceName=="Lighting:") {unitBox=lighting;    unitsSymbol="-cd   ";}
         if(deviceName=="Temperat:") {unitBox=temperature; unitsSymbol="-°C   ";}
         if(deviceName=="Pressure:") {unitBox=presure;     unitsSymbol="-kPa  ";}
         if(deviceName=="PowerLev:") {unitBox=powerlev;    unitsSymbol="-watt ";}

            cout<<" | Thread Count.:"<< records <<"  |  "<<deviceName<<" | "<<getFacts() 
            <<unitsSymbol<<" | TimeStamp : "<<ctime(&timenow); records++;
         } doorx.unlock();
    } 
};

int main() {
   deviceMaker Lighting;     deviceMaker Temperat;    
   deviceMaker PowerLev;    deviceMaker Presure;     
   for(int z=0;    z<1;    z++)
   {
   thread device1(deviceMaker(), 3, "Lighting:" );   
   thread device2(deviceMaker(), 3, "Temperat:"); 
   thread device3(deviceMaker(), 3, "Pressure:"); 
   thread device4(deviceMaker(), 3, "PowerLev:"); 
   // Wait for thread D1 to finish then cleanup
		device1.join(); 
      device2.join();         
      device3.join();
      device4.join();
   }
   return 0;
}
