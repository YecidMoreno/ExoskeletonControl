
arma::Mat<double> Res; 
arma::Mat<double> ref; 
arma::Mat<double> t_Ts; 

arma::Mat<double> A;
arma::Mat<double> AngleW;
arma::Mat<double> B;
arma::Mat<double> Ref;


double Ts;
int t_samples;

static float frecRef = 0.5;
static float AmpRef = 0.2;
static int typeSignal = 0;
double *Res_ptr;

std::atomic<bool> exoTask_mutex_end(true);
std::atomic<bool> Res_usage(false);

std::thread thread_1;

//constexpr size_t ;
static int buf_size ;
static float *x_data ;
static float *y_data1;
static float *y_data2;
static float *y_data3;
static uint32_t selection_start = 0, selection_length = 0;

float spamTimePlot = 5;
float colorsPlot[4];
float lineSize[] = {1,1,1,1};

static std::vector<ImVec2> Res_std_vec ;
static std::vector<ImVec2> Ref_std_vec ;

static std::vector<ImVec2> Res_A_std_vec ;
static std::vector<ImVec2> Ref_A_std_vec ;

static float Kp = 50;
static float Kb = 0.5;


enum textureContent{
    Texture_default   = 0 ,
    Texture_Exo_Elo_1 = 1 ,
    Texture_Exo_Elo_2 = 2 ,
    Texture_Exo_Elo_3 = 3 ,
    Texture_Xsens_OFF = 4 ,
    Texture_Xsens_ON  = 5 ,
    Texture_Play      = 6 ,
    Texture_Pause     = 7 ,
    Texture_Rerob_1   = 8 ,
    Texture_EMG_OFF   = 9 ,
    Texture_EMG_ON    = 10,
};

ImU32 colDark = 0xFF645A45;
ImU32 colPrimaryText = 0xFF212121;
ImU32 colSecondaryText = 0xFF757575;
ImU32 colAccentColor = 0xFFFE6D53;
ImU32 colTextIcons = 0xFFFFFFFF;

namespace SIM{
    long t_index = 0;
    long i = 0;
    long i_1 = 0;
    float dTRef = 0;
    float dTRes = 0;
    int index_max = 0;
}