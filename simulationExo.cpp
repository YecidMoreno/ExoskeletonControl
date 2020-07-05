
void exoSimulationTask(std::string msg)
{
    loadDatasfromMatlab();
    SIM::t_index = 0;
    SIM::i=0;
    SIM::i_1=0;
    Ref_std_vec.clear();
    Res_std_vec.clear();
    Ref_A_std_vec.clear();
    Res_A_std_vec.clear();
    SIM::index_max = 0;
    SIM::dTRef = 0;
    SIM::dTRes = 0;

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    while(true){                 

        Res_usage.store(true);
        
            int index;
            for(index = 0 ; index<GB::blockGUIConections.size() ; index ++){
                GB::blockGUI *U = (GB::blockGUIConections[index].U);
                (*U).eval((*U).U,&(*U).Y); 
            }    
            GB::blockGUI *U = (GB::blockGUIConections[index-1].Y);
            (*U).eval((*U).U,&(*U).Y); 
      
        Res_usage.store(false);

        SIM::t_index++;

        if (exoTask_mutex_end.load()) break; 

        while(std::chrono::duration_cast<std::chrono::nanoseconds> (std::chrono::steady_clock::now() - begin).count()/1000000000.f <= SIM::t_index*Ts);        
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout<<"\n"<<msg<<"  -  "<< SIM::t_index << std::endl ;    
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count()/1000.f << "[S]" << std::endl;
    //thread_1_must_end.store(false);
}
