#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vf1_fsm.h"
#include "vbuddy.cpp"
#define MAX_SIM_CYC 1000000

int main(int argc, char **argv, char **env){
    int simcyc;
    int tick;

    Verilated::commandArgs(argc, argv);
    //instatiate the counter module as Vcounter
    //this is the DUT (name of all generated files)
    Vf1_fsm* top = new Vf1_fsm;
    //turn on signal tracing and tell Verilator to
    //dump the waveform data to counter.vcd
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace (tfp, 99);
    tfp->open ("f1_fsm.vcd");

    // init Vbuddy
    if (vbdOpen()!=1) return(-1);
    vbdHeader("Lab 3 Task 2");
    vbdSetMode(1);

    //initialize simulation inputs
    top->clk = 1;
    top->rst = 1;
    top->en = 0;

        //run simulation for many clock cycles
    for (simcyc=0; simcyc<300; simcyc++) {

        //dump variables into VCD file and toggle clock
        for (tick=0; tick<2; tick++) {
            tfp->dump (2*simcyc+tick);
            top->clk = !top->clk;
            top->eval ();
        }

        // ++++ Send count value to Vbuddy
        //vbdHex(2, (top->data_out >> 4) & 0xF);
        //vbdHex(1, top->data_out & 0xF);
        vbdBar(top->data_out & 0xFF);
        // ---- end of Vbuddy output section


        if (Verilated::gotFinish()) exit(0);
    }

    vbdClose();     // ++++
    tfp->close();
    exit(0);

}