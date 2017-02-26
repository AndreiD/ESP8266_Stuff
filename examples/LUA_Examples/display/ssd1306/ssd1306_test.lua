-- setup I2c and connect display
function init_i2c_display()
     local sda = 5 -- GPIO14
     local scl = 6 -- GPIO12
     local sla = 0x3c
     i2c.setup(0, sda, scl, i2c.SLOW)
     disp = u8g.ssd1306_128x64_i2c(sla)
end

function to_display(the_text)
      disp:firstPage()
      repeat
           disp:setFont(u8g.font_6x10)
           disp:setScale2x2()
           disp:drawStr(0, 12, string.format("%d °C", math.floor(25.42)))
           
           disp:undoScale() 
           disp:drawStr(0, 35, the_text)
      until disp:nextPage() == false
      tmr.wdclr()
end


print("~~~~~~~~~~ Start ~~~~~~~~~~")
init_i2c_display()
to_display("Hello World")
print("~~~~~~~~~~ Bye ~~~~~~~~~~")
