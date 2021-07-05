void dmy(){
  if(stepNo==0){
    datefn();
  lcd.setCursor(1 , 0);
  lcd.noBlink(); 
  delay(100);
  // Turn on the cursor:
  lcd.blink();
  delay(200);
  }
  if(stepNo==1){
    monthfn();
  lcd.setCursor(4 , 0);  
  lcd.noBlink();  
  delay(100);
  // Turn on the cursor:
  lcd.blink();
  delay(200);
  }
  if(stepNo==2){
    yearfn();
  lcd.setCursor(7 , 0);  
  lcd.noBlink(); 
  delay(100);
  // Turn on the cursor:
  lcd.blink();
  delay(200); 
  }
  if(stepNo==3){
    
  lcd.setCursor(16 , 0);  
  lcd.noBlink(); 
  delay(100);
  // Turn on the cursor:
  lcd.blink();
  delay(200); 
  }
  if(stepNo==4){
  lcd.setCursor(19 , 0);  
  lcd.noBlink(); 
  delay(100);
  // Turn on the cursor:
  lcd.blink();
  delay(200); 
  }
  if(stepNo==5){
   
  lcd.setCursor(7 , 1);  
  lcd.noBlink(); 
  delay(100);
  // Turn on the cursor:
  lcd.blink();
  delay(200); 
  }
  if(stepNo==6){
   
  lcd.setCursor(19 , 1);  
  lcd.noBlink(); 
  delay(100);
  // Turn on the cursor:
  lcd.blink();
  delay(200); 
  }
  if(stepNo==7){
   uvtfn(); 
  lcd.setCursor(6 , 2);  
  lcd.noBlink(); 
  delay(100);
  // Turn on the cursor:
  lcd.blink();
  delay(200); 
  }
  if(stepNo==8){
    flvfn(); 
  lcd.setCursor(18 , 2);  
  lcd.noBlink(); 
  delay(100);
  // Turn on the cursor:
  lcd.blink();
  delay(200); 
  }
  if(stepNo==9){
    
fanfn(); 
  lcd.setCursor(6 , 3);  
  lcd.noBlink(); 
  delay(100);
  // Turn on the cursor:
  lcd.blink();
  delay(200); 
  }
  if(stepNo==10){
  exhfn(); 
  lcd.setCursor(18 , 3);  
  lcd.noBlink(); 
  delay(100);
  // Turn on the cursor:
  lcd.blink();
  delay(200); 
  } 
  if(stepNo==11){
    lcd.setCursor(14 , 0);  
  lcd.noBlink(); 
  delay(100);
  // Turn on the cursor:
  lcd.blink();
  delay(200); 
  } 
  if(stepNo==12){
    Thourfn();
    lcd.setCursor(12 , 1);  
  lcd.noBlink(); 
  delay(100);
  // Turn on the cursor:
  lcd.blink();
  delay(200); 
  } 
    if(stepNo==13){
      Tmintfn();
    lcd.setCursor(15 , 1);  
  lcd.noBlink(); 
  delay(100);
  // Turn on the cursor:
  lcd.blink();
  delay(200); 
  } 
    if(stepNo==14){
      Tsecfn();
    lcd.setCursor(18 , 1);  
  lcd.noBlink(); 
  delay(100);
  // Turn on the cursor:
  lcd.blink();
  delay(200); 
  } 
  if(stepNo==15){
    lcd.setCursor(13 , 2);  
  lcd.noBlink(); 
  delay(100);
  // Turn on the cursor:
  lcd.blink();
  delay(200); 
  } 
  if(stepNo==16){
    lcd.setCursor(14 , 3);  
  lcd.noBlink(); 
  delay(100);
  // Turn on the cursor:
  lcd.blink();
  delay(200); 
  } 
  } 
