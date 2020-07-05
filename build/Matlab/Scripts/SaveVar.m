clear all
close all
clc 

disp('Leyendo Variables')
% Variables para guardar

    load exportCpp.mat
    
    
% No editar
disp('Comenzando a guardar')
vars = whos;
vars = {vars.name};
fileName = '../LoadInit/datas.txt' ;
dlmwrite(fileName,'', 'delimiter', '');
for v = vars
    var = v{1};
    varData = eval(var);
    append_value(fileName, var, varData);
end
disp('Terminado')


fprintf(1,'\n\n');
for v = vars
    var = v{1};
    varData = eval(var);
    
    if(isscalar(eval(var)))
        disp(['double ' var ';'])        
    else
        disp(['arma::Mat<double> ' var ';'])        
    end
end

fprintf(1,'\n\n');
disp('std::ifstream file("Matlab/Loadinit/datas.txt");')
for v = vars
    var = v{1};
    varData = eval(var);
    
    if(isscalar(eval(var)))
        disp([var ' = load_mat<double>(file, "' var '")(0,0);'])        
    else
        disp([ var ' = load_mat<double>(file, "' var '");'])        
    end
end
disp('file.close();')