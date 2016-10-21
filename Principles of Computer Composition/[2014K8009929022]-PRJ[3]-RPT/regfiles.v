module regfiles(clk,rst,wen,raddr1,raddr2,waddr,wdata,rdata1,rdata2);
  input clk,rst,wen;
  input [31:0]wdata;
  input [4:0]raddr1,raddr2,waddr;
  output [31:0]rdata1,rdata2;
  wire clk;
  reg [31:0]r[31:0];
  
  always @(posedge clk or posedge rst)
  begin
    if(rst)
      begin
        r[0]=32'b0;r[1]=32'b0;r[2]=32'b0;r[3]=32'b0;
        
        
        
        
        
        
        
      
    
  
 	  else
      r[waddr]<=r[waddr];
  end
  
  assign rdata1= (raddr1==5'b0)? 32'b0:r[raddr1];
  //assign rdata1= r[raddr1];
  assign rdata2= (raddr2==5'b0)? 32'b0:r[raddr2];
  
endmodule