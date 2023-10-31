#include<ac.h>



double AC::getAC_val(){  //姿勢制御の値返す関数
  dir = getnowdir();

  kkp = -dir;  //比例制御の値を計算
  kkd = ((kkp - kkp_old) * time) * kd;  //微分制御の値を計算
  kkp_old = kkp;  //前Fの方向を更新
  kkp *= kp;
  if(100 < abs(kkd)){
    kkd = (kkd < 0 ? -100 : 100);
  }
  
  val = kkp + kkd;  //最終的に返す値を計算
  ac_timer.reset();

  return val;  //値返す
}



float AC::getCam_val(float cam){
  this->getnowdir();
  kkp = cam;  
  kkd = ((kkp - kkp_old) * time) * kd;  //微分制御の値を計算
  if(100 < abs(kkd)){
    kkd = (kkd < 0 ? -100 : 100);
  }
  kkp_old = kkp;
  kkp *= kp;
  dir = getnowdir();

  val = kkp + kkd;
  return val;  //値返す 
}



float AC::getnowdir(){
  bno.getEvent(&event);
  dir = event.orientation.x - dir_target;
  if(180 < abs(dir)){
    dir += (dir < 0 ? 360 : -360);
  }
  
  return dir;
}


void AC::print(){  //現在の角度、正面方向、姿勢制御の最終的な値を表示
  Serial.print(" 角度 : ");
  Serial.print(dir);
  Serial.print(" 正面方向 : ");
  Serial.print(dir_target);
  Serial.print(" 最終的に出たやつ : ");
  Serial.print(val);
}




void AC::setup(){  //セットアップ
  bno.begin();
  delay(100);
  bno.getEvent(&event);

  this->first = event.orientation.x;
  this->dir_target = this->first;
}

void AC::setup_2(){
  bno.getEvent(&event);

  dir_target = event.orientation.x;
  this->first = dir_target;
}