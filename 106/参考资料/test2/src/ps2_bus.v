module ps2_bus(
  inout tri PS2_CLK, PS2_DAT,
  input clock, clk_out, dat_out,
  output reg clk_in, dat_in
);

assign PS2_CLK = clk_out ? 1'bZ : 1'b0;
assign PS2_DAT = dat_out ? 1'bZ : 1'b0;

always @ (posedge clock)
  begin
	 clk_in <= PS2_CLK;
	 dat_in <= PS2_DAT;
  end

endmodule
