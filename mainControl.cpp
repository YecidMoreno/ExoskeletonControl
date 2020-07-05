//MAY 8, 2020
//  Exoskeleton control.
//  Control of Robotic systems
//  Yecid Moreno, USP - EESC

#include "libs.cpp"
#include "declarations.cpp"
#include "additionalMethods.cpp"
#include "graphicsExo.cpp" 
#include "graphicsBlocks.cpp"
#include "simulationExo.cpp"


typedef int (__stdcall *f_Add)(int a,int b);
typedef void (__stdcall *f_void)();  

typedef int   * v_int;  
typedef float * v_float;
typedef double* v_double;
typedef arma::Mat<double>* v_armaDouble;



int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{            
    {   // load data from DLL (Testando)  
    if(!true){
        system("cd .. & x86_64-w64-mingw32-g++ -c -o dll\\add_var.o dll\\add_var.cpp -D ADD_EXPORTS -I C:\\DEV\\Requeriments\\include -L C:\\DEV\\Requeriments\\lib_win64 -l gdi32 -l shell32 -l shell32 -l blas_win64_MT -l lapack_win64_MT");
        system("cd .. & x86_64-w64-mingw32-g++ -o  build\\add_var.dll dll\\add_var.o -s -shared -Wl,--subsystem,windows");
        
    } 

     for (int i = 10; i < 10; i++)
    {
        /*
        
        x86_64-w64-mingw32-g++ -c -o dll/add_var.o dll/add_var.cpp -D ADD_EXPORTS -I C:\DEV\Requeriments\include -L C:\DEV\Requeriments\lib_win64 -l gdi32 -l shell32 -l shell32 -l blas_win64_MT -l lapack_win64_MT
        x86_64-w64-mingw32-g++ -o  build/add_var.dll dll/add_var.o -s -shared -Wl,--subsystem,windows

        */
  
        HINSTANCE hGetProcIDDLL = LoadLibrary("add_var.dll"); 

        f_void __init = (f_void)GetProcAddress(hGetProcIDDLL, "__init");
        __init();

        f_Add Add = (f_Add)GetProcAddress(hGetProcIDDLL, "Add"); 
        f_void Add2 = (f_void)GetProcAddress(hGetProcIDDLL, "Add2");
        Add2();
        int N = *((v_int)GetProcAddress(hGetProcIDDLL, "foo2"));    
        arma::Mat<double> N2 = *((v_armaDouble)GetProcAddress(hGetProcIDDLL, "foo3"));        
       
        
        printf(">> %d",Add(i,10));
        printf(">> %d",N ); 
        N2.print(" N2 : ");    

        FreeLibrary(hGetProcIDDLL);
        system("pause");
        
    } 
    }

    if(loadDatasfromMatlab() == false) return -1;     
    
    if(GE::InitWindowExo()==-1)return -1; 

    ImGuiIO& io = ImGui::GetIO();
    GE::loadTextures();    

    while (!GE::var::done) // graphical interface loop
    {  
        {   //Initial Events   
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {   
            ImGui_ImplSDL2_ProcessEvent(&event);    
            if (event.type == SDL_QUIT) GE::var::done = true;
        }  
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();       
        }  

        // variables    
        static bool firstTime = true;
        static float * L = GE::var::JointL;
        static float * A = GE::var::JointA; 
        static float * AD = GE::var::JointAD;
        
        GE::var::TimeCur += io.DeltaTime;

        GE::Interface::drawDock(); 
        GE::Interface::drawMain(); 
        
        {   // Control Panel
            ImGui::Begin("Control Panel");          
  
            if (ImGui::TreeNode("Exoskeleton Values")){
                ImGui::SliderAngle("Sl1",&A[0],-45,45);  
                ImGui::SliderAngle("Sl2",&A[1],-45,45);
                ImGui::SliderAngle("Sl3",&A[2],0-15,0+15);
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("Signal designer")){      
        
                ImGui::SliderFloat("Frecuencia",&frecRef,0.0f,2.0f);
                ImGui::SliderFloat("Amplitud",&AmpRef,0.0f,.5f);

                ImGui::RadioButton("Sin", &typeSignal, 0); ImGui::SameLine();
                ImGui::RadioButton("Square", &typeSignal, 1); ImGui::SameLine();
                ImGui::RadioButton("Sawtooth", &typeSignal, 2);
                ImGui::TreePop();
            }   
            if (ImGui::TreeNode("Controller options")){      
        
                ImGui::SliderFloat("Kp",&Kp,0.0f,100.f);
                ImGui::SliderFloat("Kb",&Kb,0.00f,10.0f);
                ImGui::TreePop();  
            }                   
            if (ImGui::TreeNode("Performance"))
            {
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("Graph options"))
            {
                ImGui::SliderFloat("spam_time",&spamTimePlot,1,10); 
                
                ImGui::SliderFloat("lineSize0",&lineSize[0],1,5); 
                ImGui::SliderFloat("lineSize1",&lineSize[1],1,5); 

                ImGui::TreePop(); 
            }
             
            for(GB::blockGUI &curBlock : GB::blocksGUI){
                curBlock.ControlPanel();   
            }      
     
             
            int posFrame = (((int)GE::var::TimeCur)%2 == 0)+4;
            ImGui::Image((void*)GE::textures[posFrame],GE::dimensions[posFrame]);
            ImGui::SameLine();
            ImGui::Image((void*)GE::textures[posFrame],GE::dimensions[posFrame]);

            ImGui::Image((void*)GE::textures[posFrame+5],GE::dimensions[posFrame]);
            ImGui::SameLine();
            ImGui::Image((void*)GE::textures[posFrame+5],GE::dimensions[posFrame]);
            
            ImGui::End();
                   
          }   
 
        {   // Graphics
            
             
                ImGui::Begin("Angle graphics");  
                    static ImGui::PlotInterface plot_1;
                    
                    static std::vector<ImGui::PlotItem> items_1(2); 
                    while (Res_usage.load()); 
                    if(!exoTask_mutex_end.load() && Ref_std_vec.size()>=4){
                            plot_1.x_axis.minimum = Ref_std_vec[Ref_std_vec.size()-1].x - spamTimePlot;
                            plot_1.x_axis.maximum = Ref_std_vec[Ref_std_vec.size()-1].x;
                    } 

                    items_1[0].type = ImGui::PlotItem::Line;          
                    items_1[0].data =  Ref_A_std_vec ;
                    items_1[0].color = {1,0,0,1};
                    items_1[0].label = "Target";  
                    items_1[0].size = lineSize[0];
        
    
                    items_1[1].type = ImGui::PlotItem::Line;
                    items_1[1].data = Res_A_std_vec;  
                    items_1[1].color = {0,1,0,1}; 
                    items_1[1].label = "Obtained";
                    items_1[1].size = lineSize[1]; 
                    
                    if(GE::var::plot1)        
                        ImGui::Plot("My Plot 1", plot_1, items_1); 

                ImGui::End(); 
            
                ImGui::Begin("Torque graphics");
                ImGuiWindow* windowCur = ImGui::GetCurrentWindow();    

                static ImGui::PlotInterface plot;
                

                //static std::vector<double*> Result=dynamic_cast<double*>(Res.memptr());

                static std::vector<ImGui::PlotItem> items(2); 
                while (Res_usage.load()); 
                if(!exoTask_mutex_end.load() && Ref_std_vec.size()>=4){
                        plot.x_axis.minimum = Ref_std_vec[Ref_std_vec.size()-1].x - spamTimePlot;
                        plot.x_axis.maximum = Ref_std_vec[Ref_std_vec.size()-1].x;
                } 

                items[0].type = ImGui::PlotItem::Line;        
                items[0].data =  Ref_std_vec ;
                items[0].color = {1,0,0,1};
                items[0].label = "Target";  
                items[0].size = lineSize[0];


                items[1].type = ImGui::PlotItem::Line;
                items[1].data = Res_std_vec;
                items[1].color = {0,1,0,1}; 
                items[1].label = "Obtained";
                items[1].size = lineSize[1]; 
                
                if(GE::var::plot2)
                    ImGui::Plot("My Plot 2", plot, items);

                ImGui::End();    
        }
    
        {    // Simulation
            
            ImGui::Begin("Simulation", NULL,  ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoScrollbar|ImGuiWindowFlags_NoScrollWithMouse);
            ImGuiWindow* windowCur = ImGui::GetCurrentWindow();          
            ImVec2 cur = windowCur->DC.CursorPos;

            if(ImGui::ImageButton((void*)GE::textures[exoTask_mutex_end.load()?Texture_Play:Texture_Pause],ImVec2(25,25))){                      
                if(exoTask_mutex_end.load()){
                    exoTask_mutex_end.store(false);
                    thread_1 = std::thread(exoSimulationTask, "----");
                }else{
                    exoTask_mutex_end.store(true); 
                    thread_1.join();
                }          
            } 
            
        
            GE::scaleExoAnimation(windowCur->Size*.9);  
             
            //cout << windowCur->Size.y <<"\n"; 

            cur.x += windowCur->InnerRect.GetWidth()/2.0;
            cur.y += (windowCur->InnerRect.GetHeight() * 0.05);
        
            ImVec2 P11 = ImVec2(0,0)+cur;
            ImVec2 P21 = ImVec2(SDL_sin(A[0]),SDL_cos(A[0]))*L[0]+cur;
  
            ImVec2 P12 = ImVec2(P21.x,P21.y);    
            ImVec2 P22 = ImVec2(SDL_sin(A[1]),SDL_cos(A[1]))*L[1]+ P21;
        
            ImVec2 P13 = ImVec2(P22.x,P22.y);
            ImVec2 P23 = ImVec2(SDL_sin(A[2]),SDL_cos(A[2]))*L[2]+ P22;
                       
            ImVec2 Pi1 = P11 + ImVec2(SDL_sin(A[0]),SDL_cos(A[0]))*L[0]/2.515 ;
            ImVec2 Pi2 = P21 + ImVec2(SDL_sin(A[1]),SDL_cos(A[1]))*L[1]/2.662 ;
            ImVec2 Pi3 = P22 + ImVec2(SDL_sin(A[2]),SDL_cos(A[2]))*L[2]/4.666  + ImVec2(-SDL_cos(A[2]),SDL_sin(A[2]))*L[2]/-2.230 ;


            ImVec2 P11d = ImVec2(0,0)+cur;
            ImVec2 P21d = ImVec2(SDL_sin(AD[0]),SDL_cos(AD[0]))*L[0]+cur;
  
            ImVec2 P12d = ImVec2(P21d.x,P21d.y);    
            ImVec2 P22d = ImVec2(SDL_sin(AD[1]),SDL_cos(AD[1]))*L[1]+ P21d;
        
            ImVec2 P13d = ImVec2(P22d.x,P22d.y);
            ImVec2 P23d = ImVec2(SDL_sin(AD[2]),SDL_cos(AD[2]))*L[2]+ P22d;
                       
            ImVec2 Pi1d = P11d + ImVec2(SDL_sin(AD[0]),SDL_cos(AD[0]))*L[0]/2.515 ;
            ImVec2 Pi2d = P21d + ImVec2(SDL_sin(AD[1]),SDL_cos(AD[1]))*L[1]/2.662 ;
            ImVec2 Pi3d = P22d + ImVec2(SDL_sin(AD[2]),SDL_cos(AD[2]))*L[2]/4.666  + ImVec2(-SDL_cos(AD[2]),SDL_sin(AD[2]))*L[2]/-2.230 ;





            ImageRotated((void*)GE::textures[1+10],Pi1d, GE::dimensions[1], -GE::var::JointAD[0]); 
            ImageRotated((void*)GE::textures[2+10],Pi2d, GE::dimensions[2], -GE::var::JointAD[1]); 
            ImageRotated((void*)GE::textures[3+10],Pi3d, GE::dimensions[3], -GE::var::JointAD[2]);

            ImageRotated((void*)GE::textures[1],Pi1, GE::dimensions[1], -A[0]); 
            ImageRotated((void*)GE::textures[2],Pi2, GE::dimensions[2], -A[1]); 
            ImageRotated((void*)GE::textures[3],Pi3, GE::dimensions[3], -A[2]);

            

            //ImageRotated((void*)GE::textures[3],Pi3, GE::dimensions[3], -A[2]); 
            //static float move1 = 2;
            //ImGui::SliderFloat("SlMove",&move1,-5,10);
            //static float move2 = 2;
            //ImGui::SliderFloat("SlMove2",&move2,-5,10);
            //windowCur->DrawList->AddCircle(P21, 3.0f, IM_COL32(255,0,0,255), 4);

            ImGui::End();
                      
        }
    
        {   // Block Programming
            ImGui::Begin("Blocks");  
     
                ImGuiWindow* windowCur = ImGui::GetCurrentWindow();          
                ImVec2 cur = windowCur->DC.CursorPos;
                ImGuiContext& g = *GImGui;       
      
 
    
                if(firstTime){  
                     int blockCur = 0;
                     GB::blocksGUI.push_back(GB::blockGUI("Ref1",  ImVec2(10+blockCur*70,10),ImVec2(50,50),GB::fnc::ref));   GB::blocksGUI.back().movable = true; GB::blocksGUI.back().erasable = false;   blockCur++;
                     GB::blocksGUI.push_back(GB::blockGUI("CL0",  ImVec2(10+blockCur*70,10),ImVec2(50,50),GB::fnc::CL0));   GB::blocksGUI.back().movable = true; GB::blocksGUI.back().erasable = false;   blockCur++;
                     GB::blocksGUI.push_back(GB::blockGUI("Sum", ImVec2(10+blockCur*70,10),ImVec2(50,50),GB::fnc::sum));  GB::blocksGUI.back().movable = false; GB::blocksGUI.back().erasable = false;   blockCur++;
                     //GB::blocksGUI.push_back(GB::blockGUI("Sum__2", ImVec2(10+blockCur*70,10),ImVec2(50,50),GB::Type::SUM));  GB::blocksGUI.back().movable = false; GB::blocksGUI.back().erasable = false;   blockCur++;
                     GB::blocksGUI.push_back(GB::blockGUI("Mult",ImVec2(10+blockCur*70,10),ImVec2(50,50),GB::fnc::mult)); GB::blocksGUI.back().movable = false; GB::blocksGUI.back().erasable = false;   blockCur++;
                     GB::blocksGUI.push_back(GB::blockGUI("Pow", ImVec2(10+blockCur*70,10),ImVec2(50,50),GB::fnc::pow));  GB::blocksGUI.back().movable = false; GB::blocksGUI.back().erasable = false;   blockCur++;
                     GB::blocksGUI.push_back(GB::blockGUI("PlotAngle",  ImVec2(10+blockCur*70,10),ImVec2(50,50),GB::fnc::plot1));  GB::blocksGUI.back().movable = true; GB::blocksGUI.back().erasable = false;   blockCur++;
                     GB::blocksGUI.push_back(GB::blockGUI("PlotTorque",  ImVec2(10+blockCur*70,10),ImVec2(50,50),GB::fnc::plot2));  GB::blocksGUI.back().movable = true; GB::blocksGUI.back().erasable = false;   blockCur++;
                     GB::blocksGUI.push_back(GB::blockGUI("Print",  ImVec2(10+blockCur*70,10),ImVec2(50,50),GB::fnc::print));  GB::blocksGUI.back().movable = false; GB::blocksGUI.back().erasable = false;   blockCur++;
                     GB::blocksGUI.push_back(GB::blockGUI("DrawExo",  ImVec2(10+blockCur*70,10),ImVec2(50,50),GB::fnc::Exoesqueleton));  GB::blocksGUI.back().movable = true; GB::blocksGUI.back().erasable = false;   blockCur++;
                                    
                    //GB::blockGUIConections.push_back(GB::blockGUIConection(&GB::blocksGUI[0],&GB::blocksGUI[1]));
                    //GB::blockGUIConections.push_back(GB::blockGUIConection(&GB::blocksGUI[1],&GB::blocksGUI[2]));
                    //GB::blockGUIConections.push_back(GB::blockGUIConection(&GB::blocksGUI[2],&GB::blocksGUI[3]));
                    //GB::blockGUIConections.push_back(GB::blockGUIConection(&GB::blocksGUI[3],&GB::blocksGUI[4]));
                }                
                   
                int index = 0; 
 
                static int indexCp = 1; 
                if(GB::indexNewBlock != -1){
                    
                    GB::blockGUI curBLK =  GB::blocksGUI[GB::indexNewBlock];
             
                    char *nameAux =  new char[100];

                    sprintf(&(*nameAux),"%s_%d",curBLK.blockName,indexCp);

                    GB::blockGUI newBLK =  GB::blockGUI(nameAux,curBLK.posBlock+ImVec2(0,70),ImVec2(50,50),curBLK.eval);

                    GB::blocksGUI.push_back(newBLK);
                    GB::indexNewBlock = -1;
                    indexCp ++; 
                }   

                if(GB::indexDropBlock != -1){
                    
                    GB::blockGUI * curBLK =  &GB::blocksGUI[GB::indexDropBlock];
                    
                    for(index = 0;index<GB::blockGUIConections.size()+0;index++){
                        if(curBLK == GB::blockGUIConections[index].U || curBLK == GB::blockGUIConections[index].Y)
                            GB::blockGUIConections[index].connectionDrop = true;   
                    }
                    if((*curBLK).erasable)
                    (*curBLK).active = false;
                    GB::indexDropBlock = -1;
                }

                for(GB::blockGUI &curBlock : GB::blocksGUI){
                    curBlock.index = index;
                    index++;
                }                  

                for(GB::blockGUI &curBlock : GB::blocksGUI){   
                    curBlock.draw();
                } 

                index = 0;
                for(GB::blockGUIConection &curConnect : GB::blockGUIConections){ 
                    if(curConnect.draw()==-1) GB::blockGUIConections.erase(GB::blockGUIConections.begin()+index);
                    index++;
                }   

                index = 0; 
                for(int* curConnect_aux : GB::blockGUIConection_aux){
                   if(index==0) windowCur->DrawList->AddCircleFilled(GB::blocksGUI[*curConnect_aux].posOut+cur,6.0f,colTextIcons);
                   else 
                   if(index==1){
                       windowCur->DrawList->AddCircleFilled(GB::blocksGUI[*curConnect_aux].posIn+cur,6.0f,colTextIcons);
                       GB::blockGUIConections.push_back(GB::blockGUIConection(&GB::blocksGUI[(*GB::blockGUIConection_aux[0])],&GB::blocksGUI[(*GB::blockGUIConection_aux[1])]));
                       GB::blockGUIConection_aux.clear();
                       }
                   index++;
                }  

                //GB::ref(&GB::blocksGUI[0].U,&GB::blocksGUI[0].Y);
                //GB::sum_4(&GB::blocksGUI[0].Y,&GB::blocksGUI[1].Y);
                //GB::mult_2(&GB::blocksGUI[1].Y,&GB::blocksGUI[2].Y);
                //GB::pow_2(&GB::blocksGUI[2].Y,&GB::blocksGUI[3].Y); 
                //GB::plot(&GB::blocksGUI[3].Y,&GB::blocksGUI[4].Y);

   
    
                //GB::blockGUIConection auxIterProccess = GB::blockGUIConections[0];
                //for(index = 0 ; index<GB::blockGUIConections.size() ; index ++){
                //    GB::blocksGUI[index].eval(GB::blocksGUI[index].U,&GB::blocksGUI[index].Y);
                //}
                  
             
              


            ImGui::End();
        }
        
        if (ImGui::BeginPopup("testMenu", ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_AlwaysAutoResize))
    {  
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("test1")) 
            {   
                ImGui::MenuItem("test1_1"); 
                ImGui::MenuItem("test1_2");
                ImGui::EndMenu();
            }
            
            if (ImGui::MenuItem("test3"))
            {
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndMenuBar();
        }
        ImGui::Button("test");  
        ImGui::EndPopup();
    }
 

        GE::Interface::render();
        firstTime = false;
        
    }

    if(GE::var::done){   // Cleanup
        ImGui_ImplOpenGL2_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();

        SDL_GL_DeleteContext(gl_context);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
    
    return 0;
}

