// ePSOによる最適解探索
// (参照：http://msdn.microsoft.com/ja-jp/magazine/hh335067.aspx)
// (参照:オンライン同定のための適応pso)
#include "pso.hpp"

// [0~1]のdouble型乱数生成
std::random_device rd;
std::mt19937 mt(rd());
std::uniform_real_distribution<double> getrand(0.0,1.0);

typedef matrix<double> dmatrix;
// -------------------- PSO パラメータ --------------------- //
const int numberParticle=100;        // 粒子メンバ数
const int timeSteps=628;            // ステップ時間
const int Dim=2;                    // 求めたい解の数

const double minX=0;                // 位置の解の最低限界
const double maxX=500;              // 位置の解の最高限界
const double minV=-1.0*(maxX/2);    // 速度の解の最低限界
const double maxV=(maxX/2);         // 速度の解の最高限界

vector<double> bestGlobalPosition(Dim);  // 全ての群れの中で最適な粒子の位置
double bestGlobalFitness=INT_MAX;   // 位置の適合度(※正の最大値を代入)

const double w=0.729;               // 慣性質量(推奨値)
const double c1=1.4955;             // 認識質量(推奨値)
const double c2=1.4955;             // 社会的質量(推奨値)

const double eps=0.1;               // 最良解の評価値に与える小さな正の定数(由来)
// ------------------------------------------------------- //

// ------------------ Particle 粒子を扱う構造体 ----------------- //
class Particles{
public:

  // 拡張性を考えてすべてmatrixで定義
  dmatrix position = dmatrix(numberParticle,Dim);
  dmatrix fitness = dmatrix(1,numberParticle);
  dmatrix velocity = dmatrix(numberParticle,Dim);
  dmatrix bestPosition = dmatrix(numberParticle,Dim);
  dmatrix bestFitness = dmatrix(1,numberParticle);
  //dmatrix position[numberParticle][Dim];         // 位置
  // dmatrix fitness[1][numberParticle];            // 位置の解がどの程度最適解に近いかを示す尺度
  // dmatrix velocity[numberParticle][Dim];        // 速度
  // dmatrix bestPosition[numberParticle][Dim];    // これまで検出した中で最適な粒子の位置
  // dmatrix bestFitness[1][numberParticle];       // 最適位置に関する尺度

  void initializeParticles();
};

double calObjFunc(vector<double> x, int k) {       // "時変"目的関数による解の評価値算出

  double m1, m2, f;
  m1 = - (std::pow((x[0]-250-125*std::sin(0.01*k)),2)) / (2*std::pow(40,2));
  m2 = - (std::pow((x[1]-250+125*std::cos(0.01*k)),2)) / (2*std::pow(40,2));
  f = 1 - exp(m1+m2);

  return(f);
}

// ---------- 群れの初期化 ---------- //
void Particles::initializeParticles(){
  static vector<double> randomPosition(Dim);
  static vector<double> randomVelocity(Dim);
  static double fit=0;
  static double hi;
  static double lo;

  for(int i=0; i<numberParticle; i++){
       // ----- 位置の初期化 ----- //
       for(int j=0; j<Dim; j++){
           lo=minX;
           hi=maxX;
           randomPosition[j]=(hi-lo)*getrand(mt)+lo;
       }

       // -- 現在のランダムな位置での適合度計算 -- //
       fit=calObjFunc(randomPosition,0);

       // ----- 速度の初期化 ----- /
       for(int j=0; j<Dim; j++){
           lo=minV;
           hi=maxV;
           randomVelocity[j]=(hi-lo)*getrand(mt)+lo;
       }

       // ----- 初期値代入 ----- //
       row(position,i)=randomPosition;
       fitness(0,i)=fit;
       row(velocity,i)=randomVelocity;
       row(bestPosition,i)=randomPosition;
       bestFitness(0,i)=fit;

       // --- Particleオブジェクトの適合度がこれまでで最適な適合度 --- //
       if(fit<bestGlobalFitness){
           bestGlobalFitness=fit;
           bestGlobalPosition=row(position,i);
       }
  }

  printLine();
  print(numberParticle);
  printstr("Finished Initialize.");
  print(bestGlobalFitness);
  printstr("Initial Best Fitness:");
  print(bestGlobalPosition[0]);
  print(bestGlobalPosition[1]);
  printLine();
}

int main()
{

  // 粒子群生成
  Particles p;

  // 粒子群の初期化
  p.initializeParticles();

  // PSO メインルーチン
  vector<double> newVelocity(Dim);
  vector<double> newPosition(Dim);
  vector<double> tmpPosition(Dim);
  double newFitness=0;
  double tmpFitness=0;

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

  for(int iteration=1; iteration<=timeSteps; iteration++) {
      for(int i=0; i<numberParticle; i++) {
        // step1: 過去の最適値の評価を忘却させる
        p.bestFitness(0,i) = p.bestFitness(0,i) + eps;

        // step2:pbest更新
        tmpPosition = row(p.position,i);
        tmpFitness=calObjFunc(tmpPosition,iteration);  // 新しい適合度計算
        p.fitness(0,i)=tmpFitness;           // Particleオブジェクトの適合度更新

        if(newFitness<p.bestFitness(0,i)) {
            row(p.bestPosition,i)=tmpPosition;
            p.bestFitness(0,i)=tmpFitness;
        }
      }

      // step3: 前時刻の各粒子の最適解を現時刻の評価関数で再評価
      // 現時刻の評価関数における最良解に最も近いpbest
      vector<double> g3 = row(p.bestFitness,0);
      vector<double>::iterator ite3 = min_element(g3.begin(),g3.end());
      int i3 = distance(g3.begin(),ite3);
      bestGlobalPosition = row(p.bestPosition,i3);
      bestGlobalFitness = *ite3;

      // step4: 各粒子の速度と位置の更新
      for(int i=0; i<numberParticle; i++) {
          // --- 各粒子の速度更新 --- //
          for(int j=0; j<Dim; j++) {
              double r1=getrand(mt);  // 乱数コンポーネント
              double r2=getrand(mt);  // 乱数コンポーネント

              // PSO 速度更新式
              newVelocity[j]=((w*p.velocity(i,j))
                  + (c1*r1*(p.bestPosition(i,j)-p.position(i,j)))
                  + (c2*r2*(bestGlobalPosition[j]-p.position(i,j))));

              // --- 更新した速度が最小値と最大値の間にあるかどうか確認 --- //
              if(newVelocity[j]<minV) {
                  newVelocity[j]=minV;
              }else if(newVelocity[j]>maxV) {
                  newVelocity[j]=maxV;
              }
          }
          // Particleオブジェクトの速度更新
          row(p.velocity,i)=newVelocity;

          // --- 各粒子の位置更新 --- //
          for(int j=0; j<Dim; j++) {
              // PSO 位置更新式
              newPosition[j]=p.position(i,j)+newVelocity[j];

              // --- 更新した位置が最小値と最大値の間にあるかどうか確認 --- //
              if(newPosition[j]<minX) {
                  newPosition[j]=minX;
              }else if(newPosition[j]>maxX) {
                  newPosition[j]=maxX;
              }
          }
          // Particleオブジェクトの位置更新
          row(p.position,i)=newPosition;
      }

      // Display results
      print(iteration);
      print(bestGlobalPosition[0]);
      print(bestGlobalPosition[1]);
      print(bestGlobalFitness);
      printLine();
  }

  // hold off
  printstr("PSO process completed");
  printLine();

  return 0;
}
