namespace GB{
    
    bool creatingConnection = false;
    std::vector<int*> blockGUIConection_aux;
    int indexNewBlock = -1;
    int indexDropBlock = -1;    
    
    struct dataBlock{
        float val = 1;
        const char* blockName;
        dataBlock(){

        }
    };

    //default blocks function
    namespace fnc{
        dataBlock data;

        void ref(arma::Mat<double> *U,arma::Mat<double> *Y){
            if((*Y).size()<2) (*Y) = arma::zeros(2,1);
            SIM::i = (SIM::t_index%(t_samples-1));
            SIM::i_1 = ((SIM::t_index+1)%(t_samples-1));
            if(typeSignal <=1)
                (*Y)(1,0) = AmpRef*sin(2*M_PI*frecRef*SIM::t_index*Ts);
            if(typeSignal == 1)
                (*Y)(1,0) = AmpRef*signnum_typical((*Y)(1,0));
            if(typeSignal == 2)
                (*Y)(1,0) = AmpRef * ((float)(SIM::i%((int)(1/(frecRef*Ts))))/t_samples);
        }
        void CL0(arma::Mat<double> *U,arma::Mat<double> *Y){
            static std::vector<ImVec2> auxVec(2);
            static std::vector<ImVec2> auxVec_f(2);
            static mat ref = zeros(2,1);

                if(SIM::t_index>=4){
                    SIM::dTRef = (Ref_A_std_vec[SIM::index_max].y-Ref_A_std_vec[SIM::index_max-2].y)/(2*Ts);
                    SIM::dTRes = (Res_A_std_vec[SIM::index_max].y-Res_A_std_vec[SIM::index_max-2].y)/(2*Ts);
                }

                ref = (*U);
                auxVec_f[0].y = ref(1,0);
                ref(1,0)=(ref(1,0)-GE::var::JointA[1])*Kp + (SIM::dTRef*Kb - SIM::dTRes) ;
                Res.col(SIM::i_1) = A*Res.col(SIM::i) + B*ref; 
                Ref.col(SIM::i_1) = ref;            
                auxVec[0] = ImVec2(SIM::t_index*Ts,ref(1,0));
                auxVec[1] = ImVec2(SIM::t_index*Ts,Res(1,SIM::i_1));      
                
                auxVec_f[0].x = SIM::t_index*Ts;
                auxVec_f[1].x = SIM::t_index*Ts;
                
                auxVec_f[1].y = AngleW(0,0)*GE::var::JointA[1] + AngleW(0,1)*Res(1,SIM::i_1) + AngleW(0,2)*Res(1,SIM::i) ;

                if(SIM::t_index>=10/Ts){
                    Ref_std_vec = subVector(Ref_std_vec, 1 , 10/Ts - 1);
                    Res_std_vec = subVector(Res_std_vec, 1 , 10/Ts - 1); 
                    Ref_A_std_vec = subVector(Ref_A_std_vec, 1 , 10/Ts - 1); 
                    Res_A_std_vec = subVector(Res_A_std_vec, 1 , 10/Ts - 1); 
                    SIM::index_max = 10/Ts - 1;
                }else{
                    SIM::index_max = SIM::t_index;
                }
                Ref_std_vec.push_back(auxVec[0]);
                Res_std_vec.push_back(auxVec[1]);
                Ref_A_std_vec.push_back(auxVec_f[0]);
                Res_A_std_vec.push_back(auxVec_f[1]);

            
                //GE::var::JointAD[1] = auxVec_f[0].y;
                //GE::var::JointA[1] =  auxVec_f[1].y;
                (*Y)<<auxVec_f[0].y<<endr<<auxVec_f[1].y<<endr;
        }
        void sum(arma::Mat<double> *U,arma::Mat<double> *Y){
            (*Y) = (*U) + 1.0f;
        }
        void mult(arma::Mat<double> *U,arma::Mat<double> *Y){
            (*Y) = (*U) * 2.0;
        }
        void pow(arma::Mat<double> *U,arma::Mat<double> *Y){
            (*Y) = (*U) * (*U);
        }
        void plot1(arma::Mat<double> *U,arma::Mat<double> *Y){
            GE::var::plot1 = true;
        }
        void plot2(arma::Mat<double> *U,arma::Mat<double> *Y){
            GE::var::plot2 = true;
        }    
        void print(arma::Mat<double> *U,arma::Mat<double> *Y){
            (*U).print("\nplot >> ");
        }
        void Exoesqueleton(arma::Mat<double> *U,arma::Mat<double> *Y){
            GE::var::JointAD[1] = (*U)(0,0);
            GE::var::JointA[1] =  (*U)(1,0);
        }
        
        void gui_SUM(){
            if (ImGui::TreeNode(data.blockName)){
                    ImGui::TreePop(); 
                }
        }
        
        void inactive(){}
    }

    namespace Type{ // Falta implementar 23/06/20020
        struct TypeBlock{

            dataBlock data;

            std::function<void(arma::Mat<double> *U,arma::Mat<double> *Y)> eval;
            std::function<void()> ControlPanel;
            std::function<void()> Awake;
            std::function<void()> Destoy;
            TypeBlock(){
                this->ControlPanel = fnc::inactive;
                this->Awake = fnc::inactive;
                this->Destoy = fnc::inactive;
            }
            TypeBlock(std::function<void(arma::Mat<double> *U,arma::Mat<double> *Y)> eval,std::function<void()> ControlPanel,std::function<void()> Awake,std::function<void()> Destoy){
                this->eval = eval;
                this->ControlPanel = ControlPanel;
                this->Destoy = Destoy;
                this->Awake = Awake;
            }
        };

        TypeBlock SUM(fnc::sum ,fnc::gui_SUM,fnc::inactive,fnc::inactive);
        TypeBlock MUL(fnc::mult,fnc::inactive,fnc::inactive,fnc::inactive);
        TypeBlock POW(fnc::pow ,fnc::inactive,fnc::inactive,fnc::inactive);
        TypeBlock PLOT1(fnc::plot1,fnc::inactive,fnc::inactive,fnc::inactive);
        TypeBlock PLOT2(fnc::plot2,fnc::inactive,fnc::inactive,fnc::inactive);
    }

    struct blockGUI // structure block
    {
        // Attributes 
        dataBlock data;
        Type::TypeBlock type;
        const char* blockName;
        ImVec2 posBlock;
        ImVec2 posBlock2;
        ImVec2 sizeBlock;
        ImVec2 posText;
        ImVec2 posIn = ImVec2(-1,-1);
        ImVec2 posOut = ImVec2(-1,-1);
        arma::Mat<double> *U;
        arma::Mat<double> Y;
        bool movable = true;
        bool erasable = true;
        bool active = true;
        int flip = 0;
        int index = 0;
        std::function<void(arma::Mat<double> *U,arma::Mat<double> *Y)> eval;
        
        // Events keyboard
        bool  flipFree = false;
        bool  connectionFree = false;
        bool  ctrlFree = false;

        // Constructors
        blockGUI(){

        }

        blockGUI(const char* blockName_,ImVec2 posBlock_,ImVec2 sizeBlock_,std::function<void(arma::Mat<double> *U,arma::Mat<double> *Y)> func_block_){
            blockName = blockName_;
            data.blockName = blockName_;
            posBlock = posBlock_;
            posBlock2 = posBlock_;
            sizeBlock = sizeBlock_;
            rotate(flip);
            posText = posBlock-ImGui::CalcTextSize(blockName)/2+ImVec2(sizeBlock.x/2,sizeBlock.y*1.1);
            eval = func_block_;
        }
        blockGUI(const char* blockName_,ImVec2 posBlock_,ImVec2 sizeBlock_,Type::TypeBlock type){
            blockName = blockName_;
            data.blockName = blockName_;
            posBlock = posBlock_;
            posBlock2 = posBlock_;
            sizeBlock = sizeBlock_;
            rotate(flip);
            posText = posBlock-ImGui::CalcTextSize(blockName)/2+ImVec2(sizeBlock.x/2,sizeBlock.y*1.1);
            this->type = type;
        }

        // Methods
        void draw(){
            if(!active)return;
            ImGuiWindow* windowCur = ImGui::GetCurrentWindow();
            ImVec2 cur = windowCur->DC.CursorPos;
            ImGuiContext& g = *GImGui;
            ImGuiID id = windowCur->GetID(blockName); 

            ImGui::PushID(id);
            
            bool hovered = ImGui::ItemHoverable(ImRect(posBlock+cur,sizeBlock+posBlock+cur),id);
            bool hoveredIn  = ImGui::ItemHoverable(ImRect(posIn -ImVec2(4,4)+cur,posIn +ImVec2(4,4)+cur),id);
            bool hoveredOut = ImGui::ItemHoverable(ImRect(posOut-ImVec2(4,4)+cur,posOut+ImVec2(4,4)+cur),id);
            bool ctrl_press = g.IO.KeyCtrl;
                        
            if((hoveredIn || hoveredOut) && g.IO.MouseDown[0]){
                if(!connectionFree&&movable){
                    connectionFree = true;
                    
                    if(blockGUIConection_aux.size() == 2) blockGUIConection_aux.clear();

                    if(blockGUIConection_aux.size() == 0 && hoveredOut){
                        blockGUIConection_aux.push_back(&index);    
                    }else if(blockGUIConection_aux.size() == 1 && hoveredIn){
                        blockGUIConection_aux.push_back(&index);    
                    }else blockGUIConection_aux.clear();
                }
                
            }else{
                connectionFree = false;
            }

            if(hovered  && g.IO.MouseDown[0] && ctrl_press){
                if(!ctrlFree){
                    ctrlFree = true;
                    indexNewBlock = index;

                }
                
            }else if(hovered  && g.IO.MouseDown[1] && ctrl_press&&erasable){
                if(!ctrlFree){
                    ctrlFree = true;
                    indexDropBlock = index;
                }
                
            }else{
                ctrlFree = false;
            }


            if(hovered && g.IO.MouseDown[0] && !ctrl_press&&movable){
                ImGui::SetActiveID(id, windowCur);
            }
            if (g.ActiveId == id  ) {
                if (g.IO.MouseDown[0]) {
                    ImVec2 mouse = g.IO.MousePos-cur;

                    posBlock = posBlock2+ImGui::GetMouseDragDelta();

                    rotate(flip);
                    posText = posBlock-ImGui::CalcTextSize(blockName)/2+ImVec2(sizeBlock.x/2,sizeBlock.y*1.1);
                }else{
                    posBlock2 = posBlock;
                    ImGui::ClearActiveID();
                }
            }

            if(hovered && g.IO.MouseDown[1]&&!ctrl_press&&movable){
                if(!flipFree){
                    flipFree = true;
                    flip = (flip+1)%4;
                    rotate(flip);
                }
                
            }else{
                flipFree = false;
            }

            

            ImGui::PopID();
        
            windowCur->DrawList->AddRectFilled(posBlock+cur,posBlock+sizeBlock+cur,colDark,10.0f);
            windowCur->DrawList->AddText(g.Font, g.FontSize,posText+cur,colPrimaryText,blockName);
            
            if(hoveredIn && blockGUIConection_aux.size() == 1)windowCur->DrawList->AddCircleFilled(posIn+cur,6.0f,colTextIcons);
            if(hoveredOut&& blockGUIConection_aux.size() == 0)windowCur->DrawList->AddCircleFilled(posOut+cur,6.0f,colTextIcons);

            windowCur->DrawList->AddCircleFilled(posIn +cur,4.0f,colAccentColor);
            windowCur->DrawList->AddCircleFilled(posOut+cur,4.0f,colAccentColor);
            
            
        }

        void rotate(int flip_){
            flip = flip_;
            switch (flip)
                    {
                    case 0: posIn  = ImVec2(posBlock.x,posBlock.y+sizeBlock.y/2);
                            posOut = ImVec2(posBlock.x+sizeBlock.x,posBlock.y+sizeBlock.y/2);  
                            break;
                    case 1: posIn  = ImVec2(posBlock.x+sizeBlock.x/2,posBlock.y);
                            posOut = ImVec2(posBlock.x+sizeBlock.x/2,posBlock.y+sizeBlock.y);  
                            break;
                    case 3: posIn  = ImVec2(posBlock.x+sizeBlock.x/2,posBlock.y+sizeBlock.y);  
                            posOut  = ImVec2(posBlock.x+sizeBlock.x/2,posBlock.y);
                            break;
                    case 2: posIn  = ImVec2(posBlock.x+sizeBlock.x,posBlock.y+sizeBlock.y/2);  
                            posOut = ImVec2(posBlock.x,posBlock.y+sizeBlock.y/2);
                            break;                                        
                    
                    }
        }
        
        float val = 0;
        void ControlPanel(){
            if(!active)return;
            if (ImGui::TreeNode(blockName)){
                
                    ImGui::SliderFloat(blockName,&val,1,5);
                    ImGui::TreePop(); 
                }
        }
        
    };
                
    struct blockGUIConection // structure connections
    {
        blockGUI *U;
        blockGUI *Y;
    
        // Events
        bool  connectionDrop = false; 

        // Constructors
        blockGUIConection(blockGUI *U_,blockGUI *Y_){
            U = U_;
            Y = Y_;
            (*Y).U = &(*U).Y;
        }
         
        // Methods
        int draw(){
            
            if(connectionDrop) return -1;

            ImGuiWindow* windowCur = ImGui::GetCurrentWindow();
            ImVec2 cur = windowCur->DC.CursorPos;
            ImGuiContext& g = *GImGui;

            ImVec2 dropPos = ((*U).posOut + (*Y).posIn )/2.0f + cur;

            windowCur->DrawList->AddLine((*U).posOut+cur,(*Y).posIn+cur,colAccentColor,2);
            windowCur->DrawList->AddCircleFilled(dropPos,1.0f,colPrimaryText);

            bool hovered = ImGui::ItemHoverable(ImRect(dropPos-ImVec2(4,4),dropPos+ImVec2(4,4)),ImGui::GetID(&dropPos));          

            if(hovered){
                windowCur->DrawList->AddCircleFilled(dropPos,4.0f,colPrimaryText);
            } 
            if(hovered && g.IO.MouseDown[0]){
                windowCur->DrawList->AddCircleFilled(dropPos,4.0f,colPrimaryText);
                if(!connectionDrop){
                    connectionDrop = true;                    
                    return -1;
                }
            }
            return 0;
        }

    };

    std::vector<blockGUI>  blocksGUI;
    std::vector<blockGUIConection>  blockGUIConections;   

}