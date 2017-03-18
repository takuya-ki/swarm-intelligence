// PSOによる最適解探索
// (参照：http://msdn.microsoft.com/ja-jp/magazine/hh335067.aspx)
#include "pso.hpp"

// [0~1]のdouble型乱数生成
std::random_device rd;
std::mt19937 mt(rd());
std::uniform_real_distribution<double> getrand(0.0,1.0);

typedef Eigen::MatrixXd dmatrix;
// -------------------- PSO パラメータ --------------------- //
const int numberParticle=10;                  // 粒子メンバ数
const int numberIterations=10000;             // 反復処理回数
const int Dim=2;                              // 求めたい解の数

const double minX=-100;                       // 位置の解の最低限界
const double maxX=100;                        // 位置の解の最高限界
const double minV=-1.0*(maxX/5);              // 速度の解の最低限界
const double maxV=(maxX/5);                   // 速度の解の最高限界

dmatrix bestGlobalPosition = dmatrix(1,Dim);  // 全ての群れの中で最適な粒子の位置
double bestGlobalFitness=INT_MAX;             // 位置の適合度(※正の最大値を代入)

const double w=0.729;                         // 慣性質量(推奨値)
const double c1=1.49445;                      // 認識質量(推奨値)
const double c2=1.49445;                      // 社会的質量(推奨値)
// ------------------------------------------------------- //

// ------------------ Particle 粒子を扱う構造体 ----------------- //
class Particles{
public:

  // 拡張性を考えてすべてmatrixで定義
  dmatrix position = dmatrix(numberParticle,Dim);       // 位置
  dmatrix fitness = dmatrix(1,numberParticle);          // 位置の解がどの程度最適解に近いかを示す尺度
  dmatrix velocity = dmatrix(numberParticle,Dim);       // 速度
  dmatrix bestPosition = dmatrix(numberParticle,Dim);   // これまで検出した中で最適な粒子の位置
  dmatrix bestFitness = dmatrix(1,numberParticle);      // 最適位置に関する尺度

  void initializeParticles();
};

double calObjFunc(dmatrix x) {       // 目的関数による解の評価値算出
   return( 3.0 + pow(x(0,0),2) + pow(x(0,1),2) );
}

// ---------- 群れの初期化 ---------- //
void Particles::initializeParticles(){
  static dmatrix randomPosition(1,Dim);
  static dmatrix randomVelocity(1,Dim);
  static double fit=0;
  static double hi;
  static double lo;

  for(int i=0; i<numberParticle; i++){
       // ----- 位置の初期化 ----- //
       for(int j=0; j<Dim; j++){
           lo=minX;
           hi=maxX;
           randomPosition(0,j)=(hi-lo)*getrand(mt)+lo;
       }

       // -- 現在のランダムな位置での適合度計算 -- //
       fit=calObjFunc(randomPosition);

       // ----- 速度の初期化 ----- /
       for(int j=0; j<Dim; j++){
           lo=minV;
           hi=maxV;
           randomVelocity(0,j)=(hi-lo)*getrand(mt)+lo;
       }

       // ----- 初期値代入 ----- //
       position.row(i)=randomPosition.row(0);
       fitness(0,i)=fit;
       velocity.row(i)=randomVelocity.row(0);
       bestPosition.row(i)=randomPosition.row(0);
       bestFitness(0,i)=fit;

       // --- Particleオブジェクトの適合度がこれまでで最適な適合度 --- //
       if(fit<bestGlobalFitness){
           bestGlobalFitness=fit;
           bestGlobalPosition.row(0)=position.row(i);
       }
  }

  printLine();
  print(numberParticle);
  printstr("Finished Initialize.");
  print(bestGlobalFitness);
  printstr("Initial Best Fitness:");
  print(bestGlobalPosition(0,0));
  print(bestGlobalPosition(0,1));
  printLine();
}

int main()
{
  // ---------- 目的関数 ---------- //
  printstr("Objective Function: f(x)=3.0+(x(1)^2)+(x(2)^2)");

  // 粒子群生成
  Particles p;

  // 粒子群の初期化
  p.initializeParticles();

  // PSO メインルーチン
  dmatrix newVelocity(1,Dim);
  dmatrix newPosition(1,Dim);
  double newFitness=0;
  int cnt=1;

  // // gnuplotの制御
  // FILE *fp = popen("gnuplot", "w");  // popen(): 標準入力に書き込む
  // if (fp == NULL) { return -1; }
  // fputs("set mouse\n", fp);
  // fputs("splot \"origin_data.dat\",\"PCA_data2.dat\",\"PCA_data1.dat\"\n", fp);
  // fflush(fp); //バッファに格納されているデータを吐き出す
  // cin.get();
  // pclose(fp);
  //
  // // plot
  // plot(bestGlobalPosition(1), bestGlobalPosition(2), 'o');
  // disp(' ');
  // disp(' PSO process実行 ');
  // x=[num2str(cnt),'番目の最適位置 : '];
  // disp(x);
  // x=[' x0 = ', num2str(bestGlobalPosition(1))];
  // disp(x);
  // x=[' x1 = ', num2str(bestGlobalPosition(2))];
  // disp(x);
  // title('最適解へ向かう粒子の動き');
  // xlabel('x0');
  // ylabel('x1');
  // hold on

  for(int iteration=1; iteration<numberIterations; iteration++) {
      for(int i=0; i<numberParticle; i++) {

          // step3:粒子の速度と位置の更新
          // --- 各粒子の速度更新 --- //
          for(int j=0; j<Dim; j++) {
              double r1=getrand(mt);  // 乱数コンポーネント
              double r2=getrand(mt);  // 乱数コンポーネント

              // PSO 速度更新式
              newVelocity(0,j)=((w*p.velocity(i,j))
                  + (c1*r1*(p.bestPosition(i,j)-p.position(i,j)))
                  + (c2*r2*(bestGlobalPosition(0,j)-p.position(i,j))));

              // --- 更新した速度が最小値と最大値の間にあるかどうか確認 --- //
              if(newVelocity(0,j)<minV) {
                  newVelocity(0,j)=minV;
              }else if(newVelocity(0,j)>maxV) {
                  newVelocity(0,j)=maxV;
              }
          }
          // Particleオブジェクトの速度更新
          p.velocity.row(i)=newVelocity.row(0);

          // --- 各粒子の位置更新 --- //
          for(int j=0; j<Dim; j++) {
              // PSO 位置更新式
              newPosition(0,j)=p.position(i,j)+newVelocity(0,j);

              // --- 更新した位置が最小値と最大値の間にあるかどうか確認 --- //
              if(newPosition(0,j)<minX) {
                  newPosition(0,j)=minX;
              }else if(newPosition(0,j)>maxX) {
                  newPosition(0,j)=maxX;
              }
          }
          // Particleオブジェクトの位置更新
          p.position.row(i)=newPosition.row(0);

          newFitness=calObjFunc(newPosition);  // 新しい適合度計算
          p.fitness(0,i)=newFitness;           // Particleオブジェクトの適合度更新

          // step1:pbest更新
          if(newFitness<p.bestFitness(0,i)) {
              p.bestPosition.row(i)=newPosition.row(0);
              p.bestFitness(0,i)=newFitness;
          }
          // step2:gbest更新
          if(newFitness<bestGlobalFitness) {
              cnt=cnt+1;
              bestGlobalPosition=newPosition;
              bestGlobalFitness=newFitness;
              // plot(bestGlobalPosition(1), bestGlobalPosition(2), 'o');
              print(cnt);
              print(bestGlobalPosition(0,0));
              print(bestGlobalPosition(0,1));
              print(bestGlobalFitness);
              printLine();
          }
      }
  }

  // hold off
  printstr("PSO process completed");
  print(bestGlobalPosition(0,0));
  print(bestGlobalPosition(0,1));
  print(bestGlobalFitness);
  printLine();

  return 0;
}
