#ifndef WAVE_H
#define WAVE_H

typedef double (*WaveShapeMethod)(double,double);

  static double wsm_triangle(double phase,double n){ return (((phase>0.5)?1.0-((phase-0.5)*2):phase*2)-0.5)*2; }
  static double wsm_sawtooth(double phase,double n){  return (phase-0.5)*2; }
  static double wsm_square  (double phase,double n){ return phase>n?-1:1; }

  WaveShapeMethod waveShapeList[]={ wsm_triangle,wsm_sawtooth,wsm_square };
  
struct Wave{
  double phase;
  double frequency;
  double frame;
  byte shape;
  struct{
    const double *data;
    unsigned size;
  }table;
  static const int TRIANGLE = 0;
  static const int SAWTOOTH = 1;
  static const int SQUARE   = 2;
  static const int TABLE    = 3;
  int sampleRate;
  Wave(sampleRate=48000,const double *v=0,unsigned num=0){
    if(num>0){
      shape=TABLE;
      setTable(num,v);
    }else{
      shape=0;
    }
    setFrequency(440);
    reset();
  }
  void setFrequency(double f){
    if(f!=frequency){
      frame=(1.0/sampleRate)*f;
      frequency=f;
    }
  }
  void setTable(const double *v,unsigned num){
    table.size=num;
    table.data=v;
  }
  void update(){
    phase+=frame;
    while(phase>1) phase-=1;
  }
  
  virtual double get(double PWM=0.5){
    if(shape==TABLE) return table.data[(int)((table.size-1)*phase)];
    return waveShapeList[shape](phase,PWM);
  }
  void reset(){
    phase=0.5;
  }
};


#endif
