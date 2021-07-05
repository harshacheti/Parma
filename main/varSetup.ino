void datefn() {   
  //lcd.setCursor(0 , 0);  
 // lcd.print(date); 
 //unsigned long currentMillis = millis();   
   valu = digitalRead(up);
   vald = digitalRead(down); 
   
if(valu==LOW){
  dateme++;   
  //delay(100);
//  buttonPushedMillis = currentMillis; 
  if(dateme==31){
    dateme=0;
    lcd.clear();
    }  
  } 
if(vald==LOW){ 
  dateme--; 
  //delay(100);
  if(dateme==0){ 
   dateme=31;
    }  
    if(dateme==9){  
     lcd.clear();  
    }
  }
  }

void monthfn() {   
 // lcd.setCursor(3 , 0);   
  //lcd.print(month); 

   valu = digitalRead(up);
   vald = digitalRead(down); 
   
if(valu==LOW){
  monthme++;   
  //delay(100);
  if(monthme==13){
    monthme=1;
    lcd.clear();  
    } 
  } 
if(vald==LOW){
  monthme--; 
  //delay(100);
  if(monthme==0){ 
    monthme=12; 
    }  
    if(monthme==9){  
     lcd.clear();  
    } 
  }
  }


void yearfn() {   
 // lcd.setCursor(6 , 0);  
  //lcd.print(year); 

   valu = digitalRead(up);
   vald = digitalRead(down); 
   
if(valu==LOW){
  yearme++;   
 // delay(100);
  if(yearme==99){
    yearme=0;
    lcd.clear();  
    } 
  } 
if(vald==LOW){
  yearme--; 
  //delay(100); 
  if(yearme==0){ 
    yearme=99;
    }
    if(yearme==9){
     lcd.clear();  
    }
  }
  } 

void uvtfn() {   
   valu = digitalRead(up);
   vald = digitalRead(down); 
if(valu==LOW){
  uvt=true;   
  } 
if(vald==LOW){ 
  uvt=false;   
  }
}

  void fanfn() {   
   valu = digitalRead(up);
   vald = digitalRead(down); 
if(valu==LOW){
  uvt=true;   
  } 
if(vald==LOW){ 
  uvt=false;   
  }
  }

  void flvfn() {   
   valu = digitalRead(up);
   vald = digitalRead(down); 
if(valu==LOW){
  uvt=true;   
  } 
if(vald==LOW){ 
  uvt=false;   
  }
  }

  void exhfn() {   
   valu = digitalRead(up);
   vald = digitalRead(down); 
if(valu==LOW){
  uvt=true;   
  } 
if(vald==LOW){ 
  uvt=false;   
  }
  }

void Thourfn() {
   valu = digitalRead(up);
   vald = digitalRead(down); 
   
if(valu==LOW){
  Thour++;   
  if(Thour==99){
    Thour=0;
    lcd.clear();
    }  
  } 
if(vald==LOW){ 
  Thour--; 
  //delay(100);
  if(Thour==0){ 
   Thour=99;
    }  
    if(Thour==9){  
     lcd.clear();
    }
  }
  }

  
  void Tmintfn() {
   valu = digitalRead(up);
   vald = digitalRead(down); 
   
   if(valu==LOW){
     Tmint++;   
   if(Tmint==60){
     Tmint=0;
     lcd.clear();
    }  
  } 
if(vald==LOW){
  Tmint--; 
  //delay(100);
  if(Tmint==0){ 
   Tmint=60;
    }  
    if(Tmint==9){  
     lcd.clear();
    }
  }
  }
  
  void Tsecfn() {
   valu = digitalRead(up);
   vald = digitalRead(down); 
   
if(valu==LOW){
  Tsec++;   
  if(Tsec==60){
    Tsec=0;
    lcd.clear();
    }  
  } 
if(vald==LOW){ 
  Tsec--; 
  //delay(100);
  if(Tsec==0){ 
   Tsec=60;
    }  
    if(Tsec==9){  
     lcd.clear();
    }
  }
  }












  
