#include<line.h>
#include<angle.h>


LINE::LINE(){
}

void LINE::begin(){
  Serial6.begin(57600);
  for(int i = 0; i < 24; i++){
    ele_Y[i] = sin(radians(15 * i));
    ele_X[i] = cos(radians(15 * i));
  }
}


int LINE::getLINE_Vec() { //ラインのベクトル(距離,角度)を取得する関数
  float X = 0;
  float Y = 0;
  uint8_t Line_byte[4] = {data_byte[0],data_byte[1],data_byte[2],data_byte[3]};

  int flag = 0;
  int block_first[Long];
  int block_last[Long];
  int block_num = -1;
  float block_X[Long];
  float block_Y[Long];

  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 8; j++){
      data_on[i * 8 + j] = Line_byte[i] % 2;
      Line_byte[i] /= 2;
      if(i == 3 && 2 <= j){
        break;
      }
    }
  }
  for(int i = 0; i < 24; i++){
    // Serial.print(" ");
    // Serial.print(data_on[i]);
    if(i == 3){
      continue;
    }
    if(flag == 0){
      if(data_on[i] == 1){
        block_num++;
        block_first[block_num] = i;
        flag = 1;
      }
    }
    else{
      if(data_on[i] == 0){
        block_last[block_num] = i - 1;
        flag = 0;
      }
    }

    if(i == 23){
      if(data_on[23] == 1 && data_on[0] == 1){
        block_first[0] = block_first[block_num];
        block_first[block_num] = 0;
        block_num--;
      }

      if(data_on[23] == 1 && data_on[0] == 0){
        block_last[block_num] = 23;
      }
    }
  }

  if(data_on[24] == 1 && data_on[25] == 0){
    side_flag = 1;
  }
  else if(data_on[24] == 0 && data_on[25] == 1){
    side_flag = 2;
  }
  else if(data_on[24] == 1 && data_on[25] == 1 && data_on[26] == 0){
    side_flag = 3;
  }
  else if(data_on[26] == 1 && data_on[25] == 0 && data_on[24] == 0){
    side_flag = 4;
  }
  else if(data_on[24] == 1 && data_on[25] == 1 && data_on[26] == 1){
    side_flag = 4;
  }
  else{
    side_flag = 0;
  }


  for(int i = 0; i <= block_num; i++){
    block_X[i] = ele_X[block_first[i]] + ele_X[block_last[i]];
    block_Y[i] = ele_Y[block_first[i]] + ele_Y[block_last[i]];
    X += block_X[i];
    Y += block_Y[i];
  }
  block_num++;

  X /= block_num;
  Y /= block_num;
  dis_X = -X;
  dis_Y = -Y;
  num = block_num;
  ang = degrees(atan2(dis_Y,dis_X));
  if(num == 0){
    LINE_on = 0;
  }
  else{
    LINE_on = 1;
  }
  return LINE_on;
}


int LINE::switchLineflag(angle linedir){
  linedir.to_range(-45,false);
  line_flag = 0;
  for(int i = 0; i < 4; i++){  //角度を四つに区分して、それぞれどの区分にいるか判定するよ
    if(-45 +(i * 90) < linedir.degree && linedir.degree <= 45 +(i * 90)){  //それ以外の三つの区分(右、後ろ、左で判定してるよ)
      line_flag = i + 1;
    }
  }
  
  return line_flag;
}


double line_switch(int,double,int);


float LINE::decideGoang(angle linedir,int line_flag){
  float goang = 0;
  linedir.to_range(-15,false);
  for(int i = 0; i < 12; i++){  //角度を12つに区分して、それぞれどの区分にいるか判定する
    if(-15 +(i * 30) < linedir.degree && linedir.degree <= 15 +(i * 30)){  //時計回りにどの区分にいるか判定してるよ
      goang = line_switch(i,linedir.degree,line_flag);
    }
  }
  return goang;
}


double line_switch(int i,double ang,int line_flag){  //ラインを踏みこしてるときの処理とか判定とか書いてあるよ
  if(i == 11 || i <= 1){
    if(line_flag == 3){
      return 0.0;
    }
  }
  else if(2 <= i && i <= 4){
    if(line_flag == 4){
      return 90.0;
    }
  }
  else if(5 <= i && i <= 7){
    if(line_flag == 1){
      return 180.0;
    }
  }
  else if(8 <= i && i <= 10){
    if(line_flag == 2){
      return -90.0;
    }
  }

  double goang = (i * 30.0)- 180.0;


  return goang;
}




void LINE::print(){
  Serial.print(" 個数 : ");
  Serial.print(num);
  Serial.print(" 角度 : ");
  Serial.print(ang); //ラインのベクトルを表示
  Serial.print(" 距離 : ");
  Serial.print(dis); //ラインのベクトルを表示
  // Serial.print("  X : ");
  // Serial.print(dis_X); //ラインのベクトルを表示
  // Serial.print("  Y : ");
  // Serial.print(dis_Y); //ラインのベクトルを表示
  Serial.print(" side : ");
  Serial.print(side_flag);
  Serial.print(" flag : ");
  Serial.print(line_flag);
}