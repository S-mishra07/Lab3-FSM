module top #(
    parameter WIDTH = 16
) (
    input logic clk,
    input logic rst,
    input logic en,
    input logic [WIDTH-1:0] N,
    output logic [7:0] data_out
);

logic tick;


clktick clktick_instance(
    .clk (clk),
    .rst (rst),
    .en (en),
    .N (N),
    .tick (tick)
);

f1_fsm f1_fsm_instance (
    .clk (clk),
    .rst (rst),
    .en (tick),
    .data_out (data_out)
);

endmodule
