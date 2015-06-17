#include"TApplication.h"
#include"NPOnline.h"
#include<cstdlib>
int main(int argc , char** argv){
  TApplication* app = new TApplication("NPOnline",0,0);
  if(argc==3){
   NPL::NPOnline* instance = new NPL::NPOnline(argv[1],std::atoi(argv[2]));
  }
  else{
    NPL::NPOnline* instance = new NPL::NPOnline();
  }
  app->Run();
  return 0;
}

