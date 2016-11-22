`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    14:41:09 06/10/2015 
// Design Name: 
// Module Name:    i2c_top 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
//*****************************************
//master slave read write 
//*****************************************


module i2c_top
(
//	s_wr_reg,
//	s_rd_reg,
//	s_addr,
//	s_data,
	i2c_wr_done,
	
   i2c_scl,  
	i2c_sda,
   i2c_test,
	sys_clk_50mhz
);

	reg       [7:0]    s_addr=8'b10111010;
	reg       [7:0]    s_wr_reg=8'b00101000;
	reg       [15:0]   s_data=16'b0000001010000100;
	reg       [7:0]    s_rd_reg=8'b00101000;
	
	output     wire      i2c_wr_done;
	output     wire      i2c_scl;   //???????
	inout      wire      i2c_sda;   //????????
   output     reg       i2c_test;
	input      wire      sys_clk_50mhz;    //??????

	
	
//****************************************
//         register
//****************************************
   reg     i2c_wr_done1;
   reg     clk_in;
   reg     reset;     //????¦Ë
	reg     [5:0]   reset_cnt=6'd0;
	reg     scl_out;
	reg     sda_out;
	reg     i2c_busy;
	reg     i2c_start;
	reg     restart;
	reg     restart1;
	reg     i2c_stop;
	reg     stop;
	reg     i2c_wr;
	reg     i2c_rd;
	reg     read;
   reg     sda_in;
	reg     [15:0]  sda_in_data=16'd0;
	reg     scl_bit;
	reg     scl_bit1;
	reg     scl_bit2;
	reg     scl_bit3;	
	reg     bit_cnt_en;
	reg     [5:0]   bit_cnt;
	reg     [5:0]   bit_cnt2;
	reg     [3:0]   clk_cnt;
	reg     [7:0]   clk_cnt0;
   reg     [7:0]   head;
	reg     [4:0]   i2c_start_cnt1;
	reg     [4:0]   i2c_start_cnt2;
	reg     [4:0]   i2c_start_cnt3;
	reg     [4:0]   restart1_cnt;
	reg     i2c_start_rst;
	reg     [3:0]   i2c_rd_cnt;
	reg     i2c_rd_rst;
   reg     m_s_data;
	assign      i2c_scl = scl_out;      
	assign      i2c_sda = (!reset)? sda_out : 1'bz;	
   assign      i2c_wr_done = i2c_wr_done1;
	
	reg         scl_cnt_en;
	reg         scl_cnt_rst;
	parameter   [3:0]   clk_cnt1=4'b0010;
	parameter   [3:0]   clk_cnt2=4'b1000;
	parameter   [5:0]   clk_1mhz_cnt=6'b110001;
	parameter   [3:0]   clk_cnt4=4'b0100;
	
	parameter   [3:0]   bit_cnt1=4'b0111;
   
	
	reg    [5:0]   counter=6'd0;
   always@(posedge sys_clk_50mhz)
	begin
        counter<=counter+4'd1;
        if(counter==clk_1mhz_cnt)
		      counter<=6'd0;
		  else if(counter>6'd25)
		      clk_in<=1;
		  else
		      clk_in<=0;
		  
	end

//***************main machine
  reg        [2:0]   state;
  parameter  [2:0]   idle=3'd0, address=3'd1,address_ack=3'd2,rcv_data=3'd3,data_ack=3'd4,tx_data=3'd5,wait_ack=3'd6;   

//****************************************
//        scl_bit xia jiang yan cai yang shi zhong
//****************************************
   always@(posedge clk_in)
	scl_bit=scl_out;


//****************************************
//        wei ji cun qi
//****************************************
	always @ (negedge scl_bit or posedge reset)
	    if(reset)
		     bit_cnt2<=6'd0;	 
		 else if(state==3'd0 | state==3'd2 | state==3'd4 | state==3'd6)
		     bit_cnt2<=6'd0;
		 else if(state==3'd1 | state==3'd3 | state==3'd5)
			  bit_cnt2<=bit_cnt2+1'b1;
			  
	always @ (negedge scl_bit or posedge reset)
	    if(reset)
		     bit_cnt<=6'd0;	 
		 else if(state==3'd0)
		     bit_cnt<=6'd0;
		 else if(state==3'd1 | state==3'd2 | state==3'd3 | state==3'd4 | state==3'd5 | state==3'd6)
			  bit_cnt<=bit_cnt+1'b1;
//****************************************
//        §Õ???? 
//****************************************			  
   always@(posedge clk_in or posedge reset)
	    if(reset)
		 begin
		     i2c_test    <=1'b0;
			  restart     <=1'b0;
		     m_s_data<=0;
       end			  
	    else if(i2c_wr==1)  		         			  
	    case(bit_cnt)
		     6'd0: begin m_s_data<=s_addr[7];i2c_test<=state[0];end
			  6'd1: m_s_data<=s_addr[6];
			  6'd2: m_s_data<=s_addr[5];
			  6'd3: m_s_data<=s_addr[4];
			  6'd4: m_s_data<=s_addr[3];
			  6'd5: m_s_data<=s_addr[2];
			  6'd6: m_s_data<=s_addr[1];
			  6'd7: m_s_data<=s_addr[0];					


		     6'd9 : m_s_data<=s_wr_reg[7];
			  6'd10: m_s_data<=s_wr_reg[6];
			  6'd11: m_s_data<=s_wr_reg[5];
			  6'd12: m_s_data<=s_wr_reg[4];
			  6'd13: m_s_data<=s_wr_reg[3];
			  6'd14: m_s_data<=s_wr_reg[2];
			  6'd15: m_s_data<=s_wr_reg[1];
			  6'd16: m_s_data<=s_wr_reg[0];
//           6'd17: m_s_data<=s_wr_reg[0];
			  
		     6'd18: m_s_data<=s_data[15];
			  6'd19: m_s_data<=s_data[14];
			  6'd20: m_s_data<=s_data[13];
			  6'd21: m_s_data<=s_data[12];
			  6'd22: m_s_data<=s_data[11];
			  6'd23: m_s_data<=s_data[10];
			  6'd24: m_s_data<=s_data[9];
			  6'd25: m_s_data<=s_data[8];

		     6'd27: m_s_data<=s_data[7];
			  6'd28: m_s_data<=s_data[6];
			  6'd29: m_s_data<=s_data[5];
			  6'd30: m_s_data<=s_data[4];
			  6'd31: m_s_data<=s_data[3];
			  6'd32: m_s_data<=s_data[2];
			  6'd33: m_s_data<=s_data[1];
			  6'd34: m_s_data<=s_data[0];
			  6'd35: stop<=1;
			  
		 endcase
//****************************************
//        ?????? 
//****************************************

	    else if(i2c_rd==1)		 
	    case(bit_cnt)
		     6'd0: begin stop<=1'b0;m_s_data<=s_addr[7];end
			  6'd1: m_s_data<=s_addr[6];
			  6'd2: m_s_data<=s_addr[5];
			  6'd3: m_s_data<=s_addr[4];
			  6'd4: m_s_data<=s_addr[3];
			  6'd5: m_s_data<=s_addr[2];
			  6'd6: m_s_data<=s_addr[1];
			  6'd7: m_s_data<=s_addr[0];

		     6'd9 : m_s_data<=s_rd_reg[7];
			  6'd10: m_s_data<=s_rd_reg[6];
			  6'd11: m_s_data<=s_rd_reg[5];
			  6'd12: m_s_data<=s_rd_reg[4];
			  6'd13: m_s_data<=s_rd_reg[3];
			  6'd14: m_s_data<=s_rd_reg[2];
			  6'd15: m_s_data<=s_rd_reg[1];
			  6'd16: m_s_data<=s_rd_reg[0];
			  
//			  6'd17: m_s_data<=0;
			  6'd18: restart<=1'b1;
		 endcase
		 else if(read==1)	  
		 case(bit_cnt)
			  6'd0: m_s_data<=s_addr[7];
			  6'd1: m_s_data<=s_addr[6];
			  6'd2: m_s_data<=s_addr[5];
			  6'd3: m_s_data<=s_addr[4];
			  6'd4: m_s_data<=s_addr[3];
			  6'd5: m_s_data<=s_addr[2];
			  6'd6: m_s_data<=s_addr[1];
			  6'd7: m_s_data<=1;
           
		     6'd9: sda_in_data[15]<=i2c_sda;
			  6'd10: sda_in_data[14]<=i2c_sda;
			  6'd11: sda_in_data[13]<=i2c_sda;
			  6'd12: sda_in_data[12]<=i2c_sda;
			  6'd13: sda_in_data[11]<=i2c_sda;
			  6'd14: sda_in_data[10]<=i2c_sda;
			  6'd15: sda_in_data[9] <=i2c_sda;
			  6'd16: sda_in_data[8] <=i2c_sda;
           6'd17: m_s_data<=1'b0;
		     6'd18: sda_in_data[7] <=i2c_sda;
			  6'd19: sda_in_data[6] <=i2c_sda;
			  6'd20: sda_in_data[5] <=i2c_sda;
			  6'd21: sda_in_data[4] <=i2c_sda;
			  6'd22: sda_in_data[3] <=i2c_sda;
			  6'd23: sda_in_data[2] <=i2c_sda;
			  6'd24: sda_in_data[1] <=i2c_sda;
			  6'd25: sda_in_data[0] <=i2c_sda;

//			  6'd26: m_s_data<=1;
//           6'd26: stop<=1;
		 endcase			 
	
	
//****************************************
//         shi zhong ji shu qi
//****************************************

	always @ (posedge clk_in or posedge reset)
		if (reset)
			clk_cnt<=4'd0;
		else if(scl_cnt_rst==1'b1)
		   clk_cnt<=4'd0;
		else if(scl_cnt_en==1'b1)
		   clk_cnt<=clk_cnt+1'b1;
//****************************************
//         set master scl and sda
//****************************************


	reg		   [2:0]   scl_state;
	parameter scl_idle = 3'd0 ,scl_start = 3'd1, scl_low_edge = 3'd2,scl_low = 3'd3, scl_high_edge = 3'd4 ,scl_high = 3'd5, scl_stop = 3'd6;

	always @ (posedge clk_in or posedge reset)	
	begin
	    if(reset)
		 begin
		 scl_cnt_rst <=1'b1;
		 scl_cnt_en  <=1'b0;
		 sda_out     <=1'b1;
		 scl_out     <=1'b1;
		 scl_state<=scl_idle;
		 end 
	    else if((i2c_wr==1) | (i2c_rd==1 ) | (restart==1))	 
		 case (scl_state)
			  scl_idle:
				   scl_state <= scl_start;
				
			  scl_start:
			  begin
				   scl_cnt_rst <=1'b0;
					scl_cnt_en  <=1'b1;
					scl_out     <=1'b1;
					sda_out     <=1'b0;
					if(clk_cnt==clk_cnt2)
					    scl_state<=scl_low_edge;
					else
					    scl_state<=scl_start;
			  end		 
			  scl_low_edge:
			  begin
				   scl_cnt_rst <=1'b1;
					scl_cnt_en  <=1'b0;
					scl_out     <=1'b0;
	//				i2c_test    <=1'b0;
					scl_state   <=scl_low;
			  end
			  scl_low:
			  begin
			      scl_cnt_rst <=1'b0;
					scl_cnt_en  <=1'b1;
					scl_out     <=1'b0;
					
					if(clk_cnt==clk_cnt1)
					begin
					    sda_out<=m_s_data;
                   if(restart1==1'b1)						 
						     sda_out<=1'b1;
					end
					else if(clk_cnt==clk_cnt2)
					    scl_state<=scl_high_edge;
					
			  end
			  scl_high_edge:
			  begin
				   scl_cnt_rst <=1'b1;
					scl_out     <=1'b1;
					bit_cnt_en  <=1'b0;
					scl_state   <=scl_high;
			  end
			  scl_high:
			  begin
			      scl_cnt_rst <=1'b0;
					scl_cnt_en  <=1'b1;
					scl_out     <=1'b1;
					if(clk_cnt==clk_cnt4)
					begin
					    if(restart1==1)
						     sda_out<=1'b0;
						 else if(stop)
						     scl_state <= scl_stop;
					end
					else if(clk_cnt==clk_cnt2) 
					    if(restart1==1)
					        scl_state <=scl_low_edge;
					    else
					    scl_state <=scl_low_edge;
					else
					    scl_state   <=scl_high;
			  end
			  scl_stop:
			  begin
			      scl_cnt_rst <=1'b0;
				   scl_cnt_en  <=1'b1;
				   sda_out     <=1'b1;
				   scl_out     <=1'b1;

				   if (clk_cnt == clk_cnt4)
					    scl_state <= scl_idle;
//				   else
//					    scl_state <= scl_stop;
			  end
					
			  default:
				   scl_state<=scl_idle;
		endcase


	end



//****************************************
//         i2c_wr i2c_rd read restart start stop busy
//****************************************   
	always @ (posedge clk_in)
		 sda_in<=i2c_sda;
	always @ (posedge clk_in or posedge reset)
	    if(reset)
		     restart1_cnt<=5'd0;
	    else if(restart1_cnt==5'd16)
		     restart1_cnt<=restart1_cnt;
       else if(restart==1)
		     restart1_cnt<=restart1_cnt+5'd1;
           		 
   always @ (posedge clk_in) //reset restart1(yong zuo chongqi fuwei)
		 if(restart1_cnt==5'd16)
		     restart1<=0;
		 else
		     restart1<=restart;
	always @ (posedge clk_in or posedge reset)// fuwei i2c_start signal
	    if(reset)
		 begin
		     i2c_start_cnt1<=5'd0;
			  i2c_start_cnt2<=5'd0;
			  i2c_start_cnt3<=5'd0;
		 end
		 
		 else if(i2c_wr==1)
		     i2c_start_cnt1<=i2c_start_cnt1+1'b1;    
		 else if(i2c_rd==1)
		     i2c_start_cnt2<=i2c_start_cnt2+1'b1;
		 else if(restart==1)
		     i2c_start_cnt3<=i2c_start_cnt3+1'b1;
	always @ (posedge clk_in or posedge reset) // reset i2c_rd
	    if(reset)
		     i2c_rd_cnt<=4'd0;
		 else if(i2c_rd_cnt==4'd15)
		 begin
		     i2c_rd_cnt<=i2c_rd_cnt;
			  i2c_rd_rst<=1'b1;
		 end
		 else if(restart==1)
		     i2c_rd_cnt<=i2c_rd_cnt+4'd1;
	always @ (posedge clk_in or posedge reset) //set read
	    if(reset)
		     read<=1'b0;
	    else if(restart==1)
		     read<=1'b1;
	
   always @ (posedge clk_in or posedge reset) //i2c_rd
	    if(reset)
		     clk_cnt0<=8'd0;
   	 else if(stop==1'b1)
	    begin    
		     if(clk_cnt0==8'd50)
		     begin
		         clk_cnt0<=clk_cnt0;
			      i2c_rd  <=1'b1;
			  end
			  else
			  begin
			      clk_cnt0<=clk_cnt0+8'd1;
					i2c_rd  <=1'b0;
			  end
					
		 end
       else if(i2c_rd_rst==1)
           i2c_rd  <=1'b0;	
			  
	always @ (posedge clk_in or posedge reset) //reset i2c_wr
	    if(reset)
		     i2c_wr<=1'b1;
		 else if(clk_cnt0==8'd15)
		     i2c_wr<=1'b0;
           		 
			  
			  
	always @ (posedge clk_in)// global reset
	    
		 if (reset_cnt == 6'd50)
		 begin
		     reset_cnt<=reset_cnt;
	        reset<=1'b0;			      
		 end
		 else	
		 begin
       	  reset_cnt<=reset_cnt+6'd1;	     
		     reset<=1'b1;
		 end

	always @ (posedge clk_in or posedge reset)//i2c_start
	    if(reset)
		     i2c_start<=1'b0;  
		 else if(scl_out==1)
		     if((sda_in==1) && (i2c_sda==0))
		         i2c_start<=1'b1;
		 else if((i2c_start_cnt1==5'd15) | (i2c_start_cnt2==5'd20) | (i2c_start_cnt3==5'd15))
		         i2c_start<=1'b0;
		 
	always @ (posedge clk_in or posedge reset)//i2c_stop
		 if (reset == 1'b1)
	        i2c_stop<=1'b0;
		 else if(clk_cnt0==8'd30) 
		     i2c_stop<=1'b0;
		 else if(scl_out==1)
		     if((sda_in==0) && (i2c_sda==1))
		         i2c_stop<=1'b1;
		 	

//****************************************
//         MAIN STATE machine
//**************************************** 
		  
	always @ (negedge scl_bit or posedge reset or posedge clk_cnt0 or posedge restart1_cnt)
		 if (reset==1)
		     state<=idle;
		 else	if((i2c_stop==1) | (restart1==1))
			  state<=idle;
		 else
		     case(state)			          
						 
			  idle:	     if(i2c_start==1)
						         state<=address;
						     else
						         state<=idle;						  						 
						 
			  address:    if(bit_cnt2==bit_cnt1)
							      state<=address_ack;
						     else
						         state<=address;						 
						 
			  address_ack:if(scl_out==0)	
			                  if(i2c_sda==0)
									    state<=tx_data;
							      else if(i2c_sda==1)
									    state<=rcv_data;
						     else
							      state<=idle; 																	  						 
						 
			  rcv_data:	  if(bit_cnt2==bit_cnt1)
						         state<=data_ack;
						     else
						         state<=rcv_data;						 
						
			  data_ack:   if(scl_out==0)
						         if(i2c_sda==0)							          
						         state<=rcv_data;
//                           else
//                               state<=idle;									
						 
			  tx_data:	  if(bit_cnt2==bit_cnt1)
						         state<=wait_ack;
						     else
						         state<=tx_data;						 			
                   
			  wait_ack:	  if(scl_out==0)
			                  if(i2c_sda==0)
						             state<=tx_data;
						         else
						             state<=idle;
			  endcase
			  

endmodule