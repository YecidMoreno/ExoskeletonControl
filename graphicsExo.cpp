#define N_textures 20

SDL_Window*  window;
SDL_GLContext gl_context;
ImGuiContext& g = *GImGui; 


const auto windowFlags =	ImGuiWindowFlags_MenuBar | 
                                ImGuiWindowFlags_NoCollapse|
                                ImGuiWindowFlags_NoCollapse | 
                                ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoResize|
                                ImGuiWindowFlags_NoBringToFrontOnFocus |ImGuiWindowFlags_AlwaysUseWindowPadding;

namespace GE{

    namespace var
    {
        bool done = false;

        bool firstTime = true;
        float TimeCur = 0;      

        float JointL[] = {200,200,80};
        float JointA[] = {.1,0,0};
        float JointAD[] = {.1,0,0};

        bool plot1 = false;
        bool plot2 = false;
        
    }
}

namespace GE
{
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    
    ImVec2 dimensions[N_textures] ;
    ImVec2 dimensionsInit[N_textures] ;
    GLuint textures [N_textures]= {0};

    int InitWindowExo(){

        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
            {
                printf("Error: %s\n", SDL_GetError());
                return -1;
            }
        
        

        {   //Configure SDL_ImGui
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
            SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
            SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE); //SDL_WINDOW_RESIZABLE|SDL_WINDOW_BORDERLESS
            //SDL_Window*  
            window = SDL_CreateWindow("Exoesqueleto APP", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
            //SDL_GLContext 
            gl_context = SDL_GL_CreateContext(window);
            SDL_GL_MakeCurrent(window, gl_context);
            SDL_GL_SetSwapInterval(1); // Enable vsync

            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGui::StyleColorsLight();//ImGui::StyleColorsClassic();//ImGui::StyleColorsDark()
            //ImGui::StyleColorsClassic();

            ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
            ImGui_ImplOpenGL2_Init(); 
        }

        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking

        return 0;

    }

    void scaleExoAnimation(ImVec2 size){


        float scale  = size.y * 0.00090410779;


        GE::dimensions[1] = GE::dimensionsInit[1]*scale ;
        GE::dimensions[2] = GE::dimensionsInit[2]*scale ;
        GE::dimensions[3] = GE::dimensionsInit[3]*scale ;
    
        var::JointL[0] = GE::dimensions[1].y;
        var::JointL[1] = GE::dimensions[2].y;
        var::JointL[2] = GE::dimensions[3].y;

    }

    void loadTextures(){
    
        int aux[2] = {0,0};
        bool ret;
        char buffer[40]={0};
        for(int i = 0 ; i < N_textures ; i++){
            
            sprintf(buffer,"Textures/texture%d.png",i);
            ret = LoadTextureFromFile(buffer, &textures[i], &aux[0],&aux[1]);
            if(!ret) continue;
            GE::dimensions[i] = ImVec2((int)aux[0],(int)aux[1]);
            GE::dimensionsInit[i] = ImVec2((int)aux[0],(int)aux[1]);
            IM_ASSERT(ret);
            
        }

        float scale = 2.8;
        GE::dimensions[1] = GE::dimensionsInit[1]/scale ;
        GE::dimensions[2] = GE::dimensionsInit[2]/scale ;
        GE::dimensions[3] = GE::dimensionsInit[3]/scale ;
    
        var::JointL[0] = GE::dimensions[1].y;
        var::JointL[1] = GE::dimensions[2].y;
        var::JointL[2] = GE::dimensions[3].y;
    }

 

    namespace Interface
    {
        
      void drawDock(){
        
        ImVec2 WinSize =  ImGui::GetIO().DisplaySize;

        ImGui::SetNextWindowPos(ImVec2(0,0));
        ImGui::SetNextWindowSize(WinSize);
        ImGui::Begin("my_dock",0,windowFlags);
      
        ImGuiID mainDockspaceId = ImGui::GetID("my_dock");
        ImGui::DockSpace(mainDockspaceId, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);

        if (ImGui::BeginMainMenuBar()){
            if (ImGui::BeginMenu("File"))
            {
                if(ImGui::MenuItem("Load data from MatLab")){
                    loadDatasfromMatlab();
                }
                if(ImGui::MenuItem("Refresh textures")){
                    loadTextures();
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Layout"))
            {
                if (ImGui::MenuItem("Defecto")) {GE::var::firstTime = true;}
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("About"))
            {   
                ImGui::OpenPopup("testMenu");
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
 

        if (GE::var::firstTime)
        {
            GE::var::firstTime = false;
            ImGui::DockBuilderRemoveNode(mainDockspaceId);
            ImGui::DockBuilderAddNode(mainDockspaceId, ImGuiDockNodeFlags_PassthruCentralNode);
            ImGui::DockBuilderSetNodeSize(mainDockspaceId,WinSize);

            ImGuiID dockIdR = ImGui::DockBuilderSplitNode(mainDockspaceId, ImGuiDir_Right, 0.20f, nullptr, &mainDockspaceId);
            ImGuiID dockIdL = ImGui::DockBuilderSplitNode(mainDockspaceId, ImGuiDir_Left, 0.20f, nullptr, &mainDockspaceId);
            ImGuiID dockIdC = ImGui::DockBuilderSplitNode(mainDockspaceId, ImGuiDir_Right, 0.20f, nullptr, &mainDockspaceId);

            ImGuiID dockIdC1 = ImGui::DockBuilderSplitNode(dockIdC, ImGuiDir_Up, 0.60f, nullptr, &dockIdC);
            ImGuiID dockIdC2 = ImGui::DockBuilderSplitNode(dockIdC, ImGuiDir_Down, 0.40f, nullptr, &dockIdC);

            ImGui::DockBuilderDockWindow("main", dockIdL);
            ImGui::DockBuilderDockWindow("Simulation", dockIdC1);
            ImGui::DockBuilderDockWindow("Blocks", dockIdC1);
            ImGui::DockBuilderDockWindow("Log", dockIdC1);
            ImGui::DockBuilderDockWindow("Control Panel", dockIdR);
            ImGui::DockBuilderDockWindow("Torque graphics", dockIdC2);
            ImGui::DockBuilderDockWindow("Angle graphics", dockIdC2);

            ImGui::DockBuilderFinish(mainDockspaceId);
        }

        ImGui::End();
      }  
    
      void drawMain(){   //main
            ImGui::Begin("main");   

            ImGuiWindow* windowCur = ImGui::GetCurrentWindow();          
            ImVec2 cur = windowCur->DC.CursorPos;

            //ImGui::Text("Hola\nCómo está");
            

            ImGui::SetCursorPos(windowCur->Size - ImVec2(windowCur->Size.x/2.f+50,170));
            ImGui::Image((void*)GE::textures[Texture_Rerob_1],ImVec2(100,100));

            char txtEval[500];
            sprintf(txtEval,"José Yecid Moreno Villamizar");   
            ImVec2 sizeAux = ImGui::CalcTextSize(txtEval);
            ImGui::SetCursorPos(windowCur->Size - ImVec2(windowCur->Size.x/2.f+sizeAux.x/2.f,sizeAux.y + 30));
            ImGui::Text(txtEval);

            sprintf(txtEval,"N° USP : 11195127");
            sizeAux = ImGui::CalcTextSize(txtEval);
            ImGui::SetCursorPos(windowCur->Size - ImVec2(windowCur->Size.x/2.f+sizeAux.x/2.f,sizeAux.y + 10));
            ImGui::Text(txtEval);
                        
            
            ImGui::End();
        }

      void render(){ 
          ImGuiIO& io = ImGui::GetIO();
          //Graph Frame and render
            ImGui::Render(); 
            glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
            //glClearColor(GE::clear_color.x, GE::clear_color.y, GE::clear_color.z, GE::clear_color.w);
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
            SDL_GL_SwapWindow(window);
        }
    
    } 
    


} 




