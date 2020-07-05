

template<typename T>
arma::Mat<T> load_mat(std::ifstream &file, const std::string &keyword) {
	std::string line;
	std::stringstream ss;
	bool process_data = false;
	bool has_data = false;
	while (std::getline(file, line)) {
		if (line.find(keyword) != std::string::npos) {
			process_data = !process_data;
			if (process_data == false) break;
			continue;
		}
		if (process_data) {
			ss << line << '\n';
			has_data = true;
		}
	}

	arma::Mat<T> val;
	if (has_data) {
		val.load(ss);
	}
	return val;
}

bool loadDatasfromMatlab(){
   std::ifstream file("Matlab/Loadinit/datas.txt");
    A = load_mat<double>(file, "A");
    AngleW = load_mat<double>(file, "AngleW");
    B = load_mat<double>(file, "B");
    Ref = load_mat<double>(file, "Ref");
    Ts = load_mat<double>(file, "Ts")(0,0);
    file.close();
 
    Res_ptr = Res.memptr();
    t_samples = 4/Ts;

    t_Ts = regspace( 0, t_samples-1 )*Ts;
    t_Ts = t_Ts.t();
    
    Res = zeros(2,t_samples) ; 
    Ref = zeros(2,t_samples) ; 
    t_Ts = zeros(1,t_samples); 

    buf_size = t_samples;

    x_data  = new float[t_samples]();
    y_data1 = new float[t_samples]();
    y_data2 = new float[t_samples]();
    y_data3 = new float[t_samples]();

    ref = Ref; 
    return true;
}

template<typename T>
std::vector<T> subVector(std::vector<T>  &v, int m, int n) {
   auto first = v.begin() + m;
   auto last = v.begin() + n + 1;
   std::vector<T> vector(first, last);
   return vector;
}
int signnum_typical(double x) {
   if (x > 0.0) return 1;
   if (x < 0.0) return -1;
   return 0;
}   