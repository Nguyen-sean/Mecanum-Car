#ifndef Oled_menu_SEAN__
#define Oled_menu_SEAN__
#include "Arduino.h"
#include "kxnTask.h"

#include <U8x8lib.h>

#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

// uint8_t r;
int a;
// uint8_t c;
int i;
uint8_t c, r, d;
U8X8_SH1106_128X64_NONAME_HW_I2C u8x8(/* reset=*/U8X8_PIN_NONE);

DEFINE_TASK_STATE(Oled_menu){
    Oled_menu_1,
    Oled_menu_2};

CREATE_TASK(Oled_menu)

private:
uint32_t time1_ = 3000; // ms
uint32_t time2_ = 1000;

public:
// Oled_menu();
// Oled_menu() : u8x8(/* reset=*/U8X8_PIN_NONE) {}

void setup()
{
    u8x8.begin();
    // setState(Oled_menu_1);
    // u8x8.setFlipMode(1); // lật màn hình
}

void start()
{
    kxnTaskManager.add(this);
    setState(Oled_menu_1);
}

void pre(void)
{
    u8x8.setFont(u8x8_font_amstrad_cpc_extended_f);
    u8x8.clear();

    u8x8.inverse();
    u8x8.print("MakerLab GamePad");
    u8x8.setFont(u8x8_font_chroma48medium8_r);
    u8x8.noInverse();
    u8x8.setCursor(0, 1);
}

void draw_bar(uint8_t c, uint8_t is_inverse)
{
    u8x8.setInverseFont(is_inverse);
    for (uint8_t r = 0; r < u8x8.getRows(); r++)
    {
        u8x8.setCursor(c, r);
        u8x8.print(" ");
    }
}

void draw_ascii_row(uint8_t r, int start)
{
    for (c = 0; c < u8x8.getCols(); c++)
    {
        u8x8.setCursor(c, r);
        a = start + c;
        if (a <= 255)
            u8x8.write(a);
    }
}

void loop()
{

    switch (getState())
    {
    case Oled_menu_1:
        pre();
        u8x8.drawString(0, 2, "Test Gamepad");
        u8x8.setFont(u8x8_font_px437wyse700b_2x2_r);
        u8x8.drawString(0, 5, "Hshop.vn");

        setState(Oled_menu_2);
        kDelay(time1_);
        break;

    case Oled_menu_2:

        pre();
        u8x8.drawString(2, 2, "Small");
        u8x8.drawString(0, 5, "Scale Up");
        setState(Oled_menu_1);
        kDelay(time2_);
        break;
    }

    //   delay(3000);

    //   delay(3000);
    // pre();
    // u8x8.print("github.com/");
    // u8x8.setCursor(0,2);
    // u8x8.print("olikraus/u8g2");
    // delay(2000);
    // u8x8.setCursor(0,3);
    // u8x8.print("Tile size:");
    // u8x8.print((int)u8x8.getCols());
    // u8x8.print("x");
    // u8x8.print((int)u8x8.getRows());

    // delay(2000);

    //   pre();
    //   for( i = 50; i > 0; i-- )
    //   {
    //     u8x8.setCursor(3,2);
    //     u8x8.print(i);
    //     u8x8.print("  ");
    //     delay(10);
    //   }

    //   draw_bar(0, 1);
    //   for( c = 1; c < u8x8.getCols(); c++ )
    //   {
    //     draw_bar(c, 1);
    //     draw_bar(c-1, 0);
    //     delay(50);
    //   }
    //   draw_bar(u8x8.getCols()-1, 0);

    // pre();
    // u8x8.setFont(u8x8_font_amstrad_cpc_extended_f);
    // for( d = 0; d < 8; d ++ )
    // {
    //   for( r = 1; r < u8x8.getRows(); r++ )
    //   {
    //     draw_ascii_row(r, (r-1+d)*u8x8.getCols() + 32);
    //   }
    //   delay(400);
    // }

    // draw_bar(u8x8.getCols()-1, 1);
    // for( c = u8x8.getCols()-1; c > 0; c--)
    // {
    //   draw_bar(c-1, 1);
    //   draw_bar(c, 0);
    //   delay(50);
    // }
    // draw_bar(0, 0);

    // pre();
    // u8x8.drawString(0, 1, "3x6 Font");
    // u8x8.setFont(u8x8_font_inb33_3x6_n);
    // for(i = 0; i < 100; i++ )
    // {
    //   u8x8.setCursor(0, 2);
    //   u8x8.print(i);			// Arduino Print function
    //   delay(10);
    // }
    // for(i = 0; i < 100; i++ )
    // {
    //   u8x8.drawString(0, 2, u8x8_u16toa(i, 5));	// U8g2 Build-In functions
    //   delay(10);
    // }

    // pre();
    // u8x8.drawString(0, 2, "Weather");
    // u8x8.setFont(u8x8_font_open_iconic_weather_4x4);
    // for(c = 0; c < 6; c++ )
    // {
    //   u8x8.drawGlyph(0, 4, '@'+c);
    //   delay(300);
    // }

    // pre();
    // u8x8.print("print \\n\n");
    // delay(500);
    // u8x8.println("println");
    // delay(500);
    // u8x8.println("done");
    // delay(1500);

    // pre();
    // u8x8.fillDisplay();
    // for( r = 0; r < u8x8.getRows(); r++ )
    // {
    //   u8x8.clearLine(r);
    //   delay(100);
    // }
    // delay(1000);
}
END

#endif