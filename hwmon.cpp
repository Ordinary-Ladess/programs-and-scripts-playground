//     Best viewed with JED editor, terminal font monospace 7, and minimum 1920 pixel wide,
//     Comments are justified left where possible
//    
//  #       #     #        #   #    ##   # #      This  program   is  bassed   off  of   my  hwmon.sh   script.
//  # # #   #  #  #  ###  #  #  #  #  #  #   #    It's mainly for monitoring laptop batteries in detail, mainly
//  #   #    #   #        #     #   ##   #   #    on sysfs layouts that are compatable to that of a Lenovo T400,
//                                                though should also support Dell E7440 and compatibles soonTM.
//                                                This is always unfinished,  fan control is planned "SOON"(tm)
//  B y    D e d R 4 M                            Assume   the    latest   BSD   licence    if   not   attached
//
#include <signal.h>                                                   //  // Included to support CTRL+C cleanup
#include <unistd.h>                                                  //  //  Included for usleep()
#include <stdio.h>
#include <stdlib.h>
#define WATT 1
#define AMPS 0

float get_data(char filename[42]);              //  //                         get and prepare data from files.
void quit_cleanly(int sig);                    //  //  run cleanup stuff like return console cursor with e[25h
int CrudeMain();                              //  //  Temporary main called by main(), change to unmain()
void dell_main();
void lenovo_main();


int unmain() //unmain shall become main when complete
{
   int dell;
   if (dell)                            //Need to make a case-statemet for laptop model, check for files and
     {                                 // then figure out what temperature sensor and battery kit to use.
	int Global_WattMode = AMPS;
	dell_main();
     }
   else
     {
	int Global_WattMode = WATT;
	lenovo_main();
     }
   
   return 0;
}

int main()
{
   printf("\033[H\033[J\033[s\e[?25l");                                    //  //   and then setup  the screen
   //CrudeMain();  //temporary things and stuff to get the stuff and things working
   dell_main();
   return 0;
}


float get_data(char filename[42])
{   
   FILE *file_source = 0; float data = 0;
   char string_data[8];                             //If this overflows, then, maybe: YOUR BATTERY IS ON FIRE!!!

   file_source = fopen(filename, "r");                                              //  // Try opening file and 
        if(!file_source) {printf("\033[2J\e[?25h!%s\n", filename); exit(1); }      //  //     quit on !filename
                                                                                  //  // 
   fscanf(file_source, "%s", string_data);                                       //  //    get  the  raw  data,
   data = atof(string_data); data = (int)(data / 10.0f) / 100.0f;               //  //     pre-sanatize   data,
   fclose(file_source); return data;                                           //  //      Cleanup and return... 
}

void quit_cleanly(int sig)     //The example does mention don't use printf here, also something atexit function?
{                                                                           //  //
   printf("\033[2J\e[?25h"); exit(1);                                      //  //          show cursor and quit
}                                                                         //  //


void display_output(float therm, float volt, float watt, float amp, float eFull, float eNow, int WattMode, int mode2, int mode3, int mode4)
{
      float Temp_C, Amps, Watts, e_Full, e_Now, Volts;                      //  //  create sanitized data vars
      printf("CPU Temp:\t%4.1f \u00B0C\n",   therm);                     //  //
      printf("Battery Volts:\t%5.2f Volts \n",volt);                      //  //
      printf("Battery Amps:\t %4.2f Amps \n",  amp);                     //  //           :dothethings:
      printf("Battery Load:\t%5.2f Watts \n", watt);                    //  //        AKA output the stuffs
      printf("Capacity:\t %4.2f Ah\n",       eFull);                   //  //
      printf("Remaining:\t %4.2f Ah\n\033[u", eNow);  usleep(500000); //  //
}

void dell_main()
{
   while(true)
     {
	float Temp_C, Amps, current, Watts, e_Full, e_Now, Volts;                      //  // create sanitized
	//get all the things and stuff.                                               //  //  data varibles
	Temp_C = get_data("/sys/class/thermal/thermal_zone1/temp"    );              //  //
	Volts  = get_data("/sys/class/power_supply/BAT0/voltage_now" );             //  //    Get the  data we
	Amps   = get_data("/sys/class/power_supply/BAT0/current_now");             //  //     need for battery
	e_Full = get_data("/sys/class/power_supply/BAT0/charge_full" );           //  //      and  temperature
	e_Now  = get_data("/sys/class/power_supply/BAT0/charge_now"  );          //  //
	
	Watts = Volts*Amps;                     //Calculate the power drawn by using Ohm's Law power formula
	
	Volts = Volts / 1000.0f; Amps = Amps / 1000.0f; Watts = Watts / 1000000.0f; e_Full = e_Full / 1000.0f; e_Now = e_Now / 1000.0f;
	
	display_output(Temp_C, Volts, Watts, Amps, e_Full, e_Now, AMPS, 0, 0, 0); //I can has display! TODO: Determine WattHours vs AmpHours
     };
}

void lenovo_main()
{
   while(true)
     {
	float Temp_C, Amps, Watts, e_Full, e_Now, Volts;                                //  // create sanitized
	//get all the stuff and things... Already dunnit for De Novo Bruv              //  //  data varibles
	Temp_C = get_data("/sys/class/thermal/thermal_zone0/temp"   );                //  //
	Volts  = get_data("/sys/class/power_supply/BAT0/voltage_now");               //  //    Get the  data we
	Watts  = get_data("/sys/class/power_supply/BAT0/power_now"  );              //  //     need for battery
	e_Full = get_data("/sys/class/power_supply/BAT0/energy_full");             //  //      and  temperature
	e_Now  = get_data("/sys/class/power_supply/BAT0/energy_now" );            //  //

	Amps = Watts / Volts;                   //Calculate the current drawn by using Ohm's Law power formula

	Volts = Volts / 1000.0f; Amps = Amps / 1000.0f;  Watts = Watts / 1000.0f; e_Full = e_Full / 10000.0f; e_Now = e_Now / 10000.0f;
	
	display_output(Temp_C, Volts, Watts, Amps, e_Full, e_Now, WATT, 0, 0, 0); //I can has display, reserve all the thing
	
     };
}




// Cheat-sheet because I'm a super-noob:                                                                     //
// \033[2J clears the entire screen,                                                                         //
// \e[?25l  and \e[?25h  sets and resets hide cursor respectively,                                           //
// \033[H moves cursor to top left of screen,                                                                //
// \033[J clears the line on the screen where the cursor is placed,                                          //
// \033[s and \033[u saves  and restores the cursor position respectively,                                   //
//                                                                                                           //
// Reminder: fVar = atof(sVar) Convert string sVar to floating point fVar.                                   //
// ^^ I need to remember because other example functions are not avail anymore                               //
//                                                                                                           //
//                                                                                                           //
//  TODO:                                                                                                    //
//  figure out time and percent remaining.... All in WH or AH?? Butcher the AH method for now...             //
// percent  ==  ( ( e_now / e_full ) * 100 ) // remaining divided by last-full                               //
// ETA  ==  ( ( e_now / Amps ) ) //apparently in seconds. remaining divided by rate                          //
//                                                                                                           //
// int ETA_Hour, ETA_Minutes, ETA_Seconds, ETA_base                                                          //
// ETA_Seconds == ETA; // Keep ETA as the base until I know what I'm doing ._.                               //
// ETA_Minutes == (ETA_Seconds / 60 ) // took from ACPITOOL, does it just minutes only or hour's minutes too?//
// ETA_Hour == (ETA_Minutes / 60 ) //    If ACPITOOL is good.                                                //
//                                                                                                           //
// Charging ETA:                                                                                             //
// ETA == ( ( e_full - e_now) / Amps )                                                                       //
// 