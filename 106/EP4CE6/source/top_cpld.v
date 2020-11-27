//file name:       top_cpld.v
//author:           ETree
//date:             2017.9.9
//function:        top file of project
//log:              led light

module top_cpld(
    //global signal
    input clk,  //50MHz
    input rst_n,//low active
    
    //led
    output led, //high active

	inout PS2_CLK, PS2_DAT
);

//寄存器定义
reg [31:0] timer;
reg led_r;

reg  led_en;
wire key_valid;


//-------按键去抖模块--------
key_jitter key_jitter_inst
(
	.clk(clk) ,					// input  clk_sig
	.key_n(rst_n) ,			// input  key_n_sig
	.key_valid(key_valid) 	// output key_valid_sig
);

//LED 使能控制
always @(posedge clk)
	if(key_valid)
		led_en <= ~led_en;
	else
		led_en <= led_en;

		
assign led = led_r;

always @(posedge clk)
	 if(~led_en)
		 if (timer == 32'd49_999_999) //0.5 秒计数(50M-1=49_999_999)
			  timer <= 0; //计数器清零
		 else
			  timer <= timer + 1'b1; //计数器加 1
	 else
		 timer <= timer;

//LED控制
always @(posedge clk)
	 if(~led_en)
		 if (timer == 32'd24_999_999) //计数器计到 0.5 秒，
			  led_r <= 1'b1; //LED 点亮
		 else if (timer == 32'd49_999_999) //计数器计到 1 秒，
			  led_r <= 1'b0; //LED灯灭
		 else
			  led_r <= led_r;
	 else
		 led_r <= led_r;


keyboard_ps2 (.PS2_CLK(PS2_CLK), .PS2_DAT(PS2_DAT), .clock_50(clk), .reset(!rst_n));

		  
endmodule
