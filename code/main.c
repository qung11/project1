#include <main.h>

#define UP input(PIN_B0)
#define DOWN input(PIN_B1)
#define OK input(PIN_B2)
#define BACK input(PIN_B3)
#define BTN_DEN input(PIN_B6)
#define BTN_QUAT input(PIN_B7)
#define BTN_QUAT2 input(PIN_C0)
//!
//!#define SPBRG (int8*)0x99
//!#define RCSTA (int8*)0x18
//!#define TXSTA (int*)0x98
//!

unsigned char select = 1;
int time = 0;
int time1 = 0;
int time_light=0;
int flag_dasetup = 0;
int flag = 1;
int flag_manual = 0;
float Tam;
float GiatriADC;
float Nhietdo;
void hienthi(unsigned char select)
{       
   lcd_gotoxy(1, 1);
   printf(lcd_putc,"     DISPLAY        ");
   lcd_gotoxy(1, 2);
   printf(lcd_putc,"     SETTING        ");   
   lcd_gotoxy(1,select);
   printf(lcd_putc,">"); 
}
void hienthi_mode(unsigned char select)
{       
   lcd_gotoxy(1, 1);
   printf(lcd_putc,"     MANUAL         ");
   lcd_gotoxy(1, 2);
   printf(lcd_putc,"     AUTO           ");   
   lcd_gotoxy(1,select);
   printf(lcd_putc,">"); 
}
void print_select(unsigned char select)
{
   lcd_gotoxy(1,select);
   printf(lcd_putc,">"); 
}
void xoamanhinh()
{
   lcd_gotoxy(1, 1);
   printf(lcd_putc,"                ");
   lcd_gotoxy(1, 2);
   printf(lcd_putc,"                "); 
}
void mode_manual(unsigned char select)
{
   lcd_gotoxy(1, 1);
   printf(lcd_putc,"    -- ON --   ");
   lcd_gotoxy(1, 2);
   printf(lcd_putc,"    -- OFF --  ");   
   lcd_gotoxy(1,select);
   printf(lcd_putc,">"); 
}
void luachon_caidat(unsigned char select)
{
   lcd_gotoxy(0, 1);
   printf(lcd_putc,"    -- FAN --  ");
   lcd_gotoxy(0, 2);
   printf(lcd_putc,"    -- LED --  ");   
   lcd_gotoxy(1,select);
   printf(lcd_putc,">"); 
}

void caidat_fan(unsigned char select)
{
   lcd_gotoxy(1, 1);
   printf(lcd_putc,"     TOP:");
   lcd_gotoxy(1, 2);
   printf(lcd_putc,"     BOT:");   
   lcd_gotoxy(1,select);
   printf(lcd_putc,">"); 
}

void caidat_light(unsigned char select)
{
   lcd_gotoxy(1, 1);
   printf(lcd_putc,"  -- LIGHT --"); 
   lcd_gotoxy(1, 2);
   printf(lcd_putc,"  TIME:");
   lcd_gotoxy(15, 2);
   printf(lcd_putc,"s");
}
int dem1 = 0;
int bien_light;
void timerbatquat_batden()
{
   set_timer0(61);
   enable_interrupts(INT_TIMER0);
   enable_interrupts(GlOBAL);
//!   if(time_fan!= 0)
//!   {
//!      bien_fan = time_fan;
//!      flag_time=1;
//!   }
//!   if(time_light!=0)
//!   {
//!      bien_light = time_light;
//!   }
}
//!void batquat()
//!{
//!   if(time==100)  //1s
//!   {
//!      dem=dem+1;
//!      time = 0;
//!      lcd_gotoxy(12, 1);
//!      printf(lcd_putc,"%3d",bien_fan = (bien_fan>0) ? bien_fan-1 : 0 );
//!   }
//!   if(dem == time_fan )
//!   {
//!      output_high(PIN_B4);
//!      time_fan = 0;
//!   }
//!}
void batden()
{
//!   if(time1==100)  //1s
//!   {
//!      dem1=dem1+1;
//!      time1 = 0;
//!      lcd_gotoxy(12, 2);
//!      printf(lcd_putc,"%3d",bien_light = (bien_light>0) ? bien_light-1 : 0 );                          
//!   }
   if(dem1==bien_light && flag == 1 )
   {
      output_high(PIN_B5);
      dem1 = 0;
      flag = 0;
   }
   else if(time1==100 && flag_dasetup ==1 && flag ==1 )  //1s
   {
      dem1=dem1+1;
      time1 = 0;
      time_light = (time_light>0) ? time_light-1 : 0; 
   } 
}

#int_TIMER0
void TIMER0_isr() 
{
set_timer0(61);   //10ms
//!if(flag_time==1)
//!{
//!   time = time + 1;
//!   batquat();
//!}
   time1 = time1 +1;
   batden();
}
void delaytimer0_10ms(void)
{
   set_timer0(0);
   while(get_timer0()<195);
   time = time + 1;
}
struct NGUONG
{
   int top;
   int bot;
};
   int a =0;
void display_onoff()
{
   
    if(input_state(PIN_B4)==1)
    {
      lcd_gotoxy(2, 1);
      printf(lcd_putc,"F1:ON ");           
    }
    else
    {
      lcd_gotoxy(2, 1);
      printf(lcd_putc,"F1:OFF");          
    }
    if(input_state(PIN_C1)==1)
    {
      lcd_gotoxy(10, 1);
      printf(lcd_putc,"F2:ON ");           
    }
    else
    {
      lcd_gotoxy(10, 1);
      printf(lcd_putc,"F2:OFF");          
    }
    if(input_state(PIN_B5)==1)
    {
      lcd_gotoxy(2, 2);
      printf(lcd_putc,"L:ON ");            
    }
    else
    {
      lcd_gotoxy(2, 2);
      printf(lcd_putc,"L:OFF");              
    }
}

void bat_tat_quat(int top,int bot)
{
   if(Nhietdo>top)
   {
      output_high(PIN_B4);
      output_high(PIN_C1);
   }
   else if(Nhietdo>bot && Nhietdo<top)
   {
      output_high(PIN_B4);
      output_low(PIN_C1);
   }
   else if(Nhietdo<bot)
   {
      //output_low(PIN_B4);
      output_bit(PIN_B4,0);
      output_low(PIN_C1);
   }
}
void main()
{
   lcd_init();
   lcd_gotoxy(1, 1);
   printf(lcd_putc,"     DISPLAY");
   lcd_gotoxy(1, 2);
   printf(lcd_putc,"     SETTING");
   lcd_gotoxy(1,1);
   printf(lcd_putc,">"); 
   setup_timer_0(T0_INTERNAL|T0_DIV_256); 
   setup_adc(ADC_CLOCK_INTERNAL);
   setup_adc_ports(AN0_AN1_VSS_VREF);
   set_adc_channel(0);
   struct NGUONG Nguongnhietdo;
   Nguongnhietdo.TOP = 45;
   Nguongnhietdo.BOT = 40;
   output_low(PIN_B5); 
   output_low(PIN_B4); 
   output_low(PIN_C1); 
   while(TRUE)
   {
      GiatriADC = read_adc();
      Tam = GiatriADC*5/1023.0f;
      Nhietdo = Tam/0.01;
      if(UP==0)
      {
         while(UP==0);
         select = (select == 1)? 2: select-1;
         hienthi(select);
      }
      else if(DOWN==0)
      {
         while(DOWN==0);
         select = (select == 2)? 1: select+1;
         hienthi(select);
      } 
//-----------------------------------------------------------------------//
      if(OK==0 && select == 1)
      {
         xoamanhinh();
         select = 1;
         while(TRUE)
         {
            GiatriADC = read_adc();
            Tam = GiatriADC*5/1023.0f;
            Nhietdo = Tam/0.01;
            display_onoff();
            lcd_gotoxy(8,2);
            printf(lcd_putc,"Temp:%02.0f",Nhietdo);
            lcd_putc(223);
            lcd_putc("C");
            if(BACK==0)
            {
               while(BACK==0);
               xoamanhinh();
               hienthi(select);
               break;
            }
            else if(BTN_QUAT==0)
            {
              while(BTN_QUAT==0);
              if(flag_manual!=0)
              output_toggle(PIN_B4);
            }
            else if(BTN_DEN==0)
            {
              while(BTN_DEN==0);
              if(flag_manual!=0)
              output_toggle(PIN_B5);
            }
            else if(BTN_QUAT2==0)
            {
              while(BTN_QUAT2==0);
              if(flag_manual!=0)
              output_toggle(PIN_C1);
            }            
         }
      }
      ////////////////SETTING/////////////////
      else if(OK==0 && select == 2)
      {
         while(OK==0);
         xoamanhinh();
         hienthi_mode(select);
         while(TRUE)
         {
            if(UP==0)
            {
               while(UP==0);
               select = (select == 1)? 2: select-1;
               hienthi_mode(select);
            }
            else if(DOWN==0)
            {
               while(DOWN==0);
               select = (select == 2)? 1: select+1;
               hienthi_mode(select);
            }
            else if(BACK==0)
            {
               while(BACK==0);
               xoamanhinh();
               hienthi(select);
               break;
            }
            else if(BTN_QUAT==0)
            {
               while(BTN_QUAT==0);
               if(flag_manual!=0)
               output_toggle(PIN_B4);
            }
            else if(BTN_DEN==0)
            {
               while(BTN_DEN==0);
               if(flag_manual!=0)
               output_toggle(PIN_B5);
            }  
            else if(BTN_QUAT2==0)
            {
               while(BTN_QUAT2==0);
               if(flag_manual!=0)
               output_toggle(PIN_C1);
            }           
            ////////////MANUAL////////////////
            else if(OK==0 && select==1)
            {
               while(OK==0);
               mode_manual(select);
               while(TRUE)
               {
                  if(UP==0)
                  {
                     while(UP==0);
                     select = (select == 1)? 2: select-1;
                     mode_manual(select);
                     a=1;
                  }
                  else if(DOWN==0)
                  {
                     while(DOWN==0);
                     select = (select == 2)? 1: select+1;
                     mode_manual(select);
                     a=1;
                  }               
                  else if(BACK==0)
                  {
                     while(BACK==0);
                     xoamanhinh();
                     hienthi_mode(select);
                     break;
                  }
                  else if(BTN_QUAT==0)
                  {
                    while(BTN_QUAT==0);
                    if(flag_manual!=0)
                    output_toggle(PIN_B4);
                  }
                  else if(BTN_DEN==0)
                  {
                    while(BTN_DEN==0);
                    if(flag_manual!=0)
                    output_toggle(PIN_B5);
                  }  
                  else if(BTN_QUAT2==0)
                  {
                     while(BTN_QUAT2==0);
                     if(flag_manual!=0)
                     output_toggle(PIN_C1);
                  }                  
                  else if(OK==0 && select == 1)
                  {
                    while(OK==0);
                     lcd_gotoxy(1,1);
                     printf(lcd_putc,"  -- MANUAL --");                    
                     lcd_gotoxy(1,2);
                     printf(lcd_putc,"   READY !!!  ");
                     flag_manual =1;
                     select = 1;
                     while(TRUE)
                     {
                         if(BACK==0)
                        {
                           while(BACK==0);
                           xoamanhinh();
                           mode_manual(select);
                           
                           break;
                        }
                        else if(BTN_QUAT==0)
                        {
                           while(BTN_QUAT==0);
                           if(flag_manual!=0)
                           output_toggle(PIN_B4);
                        }
                        else if(BTN_DEN==0)
                        {
                           while(BTN_DEN==0);
                           if(flag_manual!=0)
                           output_toggle(PIN_B5);
                        } 
                     }
                  }     
                  else if(OK==0 && select == 2)
                  {
                     while(OK==0);
                     lcd_gotoxy(1,1);
                     printf(lcd_putc,"  -- MANUAL --");                    
                     lcd_gotoxy(1,2);
                     printf(lcd_putc,"   SHUTDOWN !!!");
                     flag_manual =0;
                     select = 1;
                     while(TRUE)
                     {
                         if(BACK==0)
                        {
                           while(BACK==0);
                           xoamanhinh();
                           mode_manual(select);
                           break;
                        }
                        else if(BTN_QUAT==0)
                        {
                           while(BTN_QUAT==0);
                           if(flag_manual!=0)
                           output_toggle(PIN_B4);
                        }
                        else if(BTN_DEN==0)
                        {
                           while(BTN_DEN==0);
                           if(flag_manual!=0)
                           output_toggle(PIN_B5);
                        }
                     }                     
                  }                  
               }
            }
            ////////////AUTO////////////////
            else if(OK==0 && select==2)
            {
               while(OK==0);
               xoamanhinh();
               luachon_caidat(select);
               while(TRUE)
               {
                  GiatriADC = read_adc();
                  Tam = GiatriADC*5/1023.0f;
                  Nhietdo = Tam/0.01;
                  bat_tat_quat(Nguongnhietdo.TOP,Nguongnhietdo.BOT);
                  if(UP==0)
                  {
                     while(UP==0);
                     select = (select == 1)? 2: select-1;
                     luachon_caidat(select);
                  }
                  else if(DOWN==0)
                  {
                     while(DOWN==0);
                     select = (select == 2)? 1: select+1;
                     luachon_caidat(select);
                  }
                  else if(BACK==0)
                  {
                     while(BACK==0);
                     xoamanhinh();
                     hienthi_mode(select);
                     break;
                  }
                  ////////////////FAN/////////////////
                  else if(OK==0 && select == 1)
                  {
                     while(OK==0);
                     xoamanhinh();
                     caidat_fan(select);
                     lcd_gotoxy(12, 1);
                     printf(lcd_putc,"%3d",Nguongnhietdo.TOP);
                     lcd_gotoxy(12, 2);
                     printf(lcd_putc,"%3d",Nguongnhietdo.BOT);   
                     while(TRUE)
                     {
                        GiatriADC = read_adc();
                        Tam = GiatriADC*5/1023.0f;
                        Nhietdo = Tam/0.01;
                        bat_tat_quat(Nguongnhietdo.TOP,Nguongnhietdo.BOT);
                        if(UP==0)
                        {
                           while(UP==0);
                           select = (select == 1)? 2: select-1;
                           caidat_fan(select);
                        }
                        else if(DOWN==0)
                        {
                           while(DOWN==0);
                           select = (select == 2)? 1: select+1;
                           caidat_fan(select);
                        }                        
                        if(OK==0 && select == 1)  //CHONTOP
                        {
                           while(OK==0);
                           lcd_gotoxy(16, 1);
                           lcd_putc("*");
                           while(TRUE)
                           {
                              if(UP==0)
                              {
                                 while(UP==0);
                                  lcd_gotoxy(12, 1);
                                  printf(lcd_putc,"%3d",Nguongnhietdo.TOP  = Nguongnhietdo.TOP +1);
                              }
                              else if(DOWN==0)
                              {
                                 while(DOWN==0);
                                  lcd_gotoxy(12, 1);
                                  printf(lcd_putc,"%3d",Nguongnhietdo.TOP  = Nguongnhietdo.TOP -1);
                              }
                              else if(OK==0)
                              {
                                 while(OK==0);
                                 lcd_gotoxy(16, 1);
                                 lcd_putc(" ");
                                 break;     
                              }
                           }
                        }
                        else if(OK==0 && select == 2) //CHONBOT
                        {
                           while(OK==0);
                           lcd_gotoxy(16, 2);
                           lcd_putc("*");
                           while(TRUE)
                           {
                              if(UP==0)
                              {
                                 while(UP==0);
                                  lcd_gotoxy(12, 2);
                                  printf(lcd_putc,"%3d",Nguongnhietdo.BOT  = Nguongnhietdo.BOT +1);
                              }
                              else if(DOWN==0)
                              {
                                 while(DOWN==0);
                                  lcd_gotoxy(12, 2);
                                  printf(lcd_putc,"%3d",Nguongnhietdo.BOT  = Nguongnhietdo.BOT -1);
                              } 
                              else if(OK==0)
                              {
                                 while(OK==0);
                                 lcd_gotoxy(16, 2);
                                 lcd_putc(" ");
                                 break;
                              }
                           }                           
                        }
                        else if(BACK==0)
                        {
                           while(BACK==0);
                           xoamanhinh();
                           luachon_caidat(select);
                           break;
                        }                        
                     }
                  }
                  ////////////////LIGHT/////////////////
                  else if(OK==0 && select == 2)
                  {
                     while(OK==0);
                     xoamanhinh();
                     caidat_light(select);
                     lcd_gotoxy(10, 2);
                     printf(lcd_putc,"%3d",time_light);
                     flag_dasetup = 0;
                     while(TRUE)
                     {
                        GiatriADC = read_adc();
                        Tam = GiatriADC*5/1023.0f;
                        Nhietdo = Tam/0.01;
                        if(Nhietdo>Nguongnhietdo.TOP || Nhietdo <Nguongnhietdo.BOT)
                        {
                           output_high(PIN_B4);
                        }
                        else
                        output_low(PIN_B4);                     
                        if(UP==0)
                        {
                           while(UP==0);
                            lcd_gotoxy(10, 2);
                            printf(lcd_putc,"%3d",time_light = time_light+1);
                        }
                        else if(DOWN==0)
                        {
                           while(DOWN==0);
                            lcd_gotoxy(10, 2);
                            printf(lcd_putc,"%3d",time_light = time_light-1);
                        }        
                        else if(OK==0)
                        {
                           while(OK==0);
                           caidat_light(select);
                           bien_light = time_light;
                           timerbatquat_batden();
                           flag = 1;
                        }
                        else if(time1==100 && flag ==1)  //1s
                         {
                           dem1=dem1+1;
                           time1 = 0;
                           lcd_gotoxy(10, 2);
                           printf(lcd_putc,"%3d",time_light = (time_light>0) ? time_light-1 : 0);  
                        }                        
                        else if(BACK==0)
                        {
                           while(BACK==0);
                           xoamanhinh();
                           luachon_caidat(select);
                           flag_dasetup = 1;     
                           break;
                        }
                     }
                  }
               }            
            }
         }
      } 
   } 
}
