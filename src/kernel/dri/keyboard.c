/*----------------*\
|Nanite OS         |
|Copyright (C) 2025|
|Tyler McGurrin    |
\*----------------*/
#include "keyboard.h"

#include <arch/i686/irq.h>
#include <arch/i686/io.h>
#include <stdio.h>

void Print_Key(int scancode) {
   char* key;
   switch (scancode) {

      case KEYSCAN_1:
      key = "1";
      break;

      case KEYSCAN_2:
      key = "2";
      break;

      case KEYSCAN_3:
      key = "3";
      break;

      case KEYSCAN_4:
      key = "4";
      break;

      case KEYSCAN_5:
      key = "5";
      break;

      case KEYSCAN_6:
      key = "6";
      break;

      case KEYSCAN_7:
      key = "7";
      break;

      case KEYSCAN_8:
      key = "8";
      break;

      case KEYSCAN_9:
      key = "9";
      break;

      case KEYSCAN_0:
      key = "0";
      break;

      case KEYSCAN_Minus:
      key = "-";
      break;

      case KEYSCAN_Equals:
      key = "=";
      break;

      case KEYSCAN_Q:
      key = "q";
      break;

      case KEYSCAN_W:
      key = "w";
      break;
      
      case KEYSCAN_E:
      key = "e";
      break;

      case KEYSCAN_R:
      key = "r";
      break;

      case KEYSCAN_T:
      key = "t";
      break;

      case KEYSCAN_Y:
      key = "y";
      break;

      case KEYSCAN_U:
      key = "u";
      break;

      case KEYSCAN_I:
      key = "i";
      break;

      case KEYSCAN_O:
      key = "o";
      break;

      case KEYSCAN_P:
      key = "p";
      break;

      case KEYSCAN_LeftBracket:
      key = "[";
      break;

      case KEYSCAN_RightBracket:
      key = "]";
      break;

      case KEYSCAN_A:
      key = "a";
      break;

      case KEYSCAN_S:
      key = "s";
      break;

      case KEYSCAN_D:
      key = "d";
      break;

      case KEYSCAN_F:
      key = "f";
      break;

      case KEYSCAN_G:
      key = "g";
      break;

      case KEYSCAN_H:
      key = "h";
      break;

      case KEYSCAN_J:
      key = "j";
      break;

      case KEYSCAN_K:
      key = "k";
      break;

      case KEYSCAN_L:
      key = "l";
      break;

      case KEYSCAN_Semicolon:
      key = ";";
      break;

      case KEYSCAN_Apostrophe:
      key = "'";
      break;

      case KEYSCAN_Grave:
      key = "`";
      break;

      case KEYSCAN_Backslash:
      key = "\\";
      break;

      case KEYSCAN_Z:
      key = "z";
      break;

      case KEYSCAN_X:
      key = "x";
      break;

      case KEYSCAN_C:
      key = "c";
      break;

      case KEYSCAN_V:
      key = "v";
      break;

      case KEYSCAN_B:
      key = "b";
      break;

      case KEYSCAN_N:
      key = "n";
      break;

      case KEYSCAN_M:
      key = "m";
      break;

      case KEYSCAN_Comma:
      key = ",";
      break;

      case KEYSCAN_Period:
      key = ".";
      break;

      case KEYSCAN_Forwardslash:
      key = "/";
      break;

      case KEYSCAN_Space:
      key = " ";
      break;

      case KEYSCAN_Enter:
      key = "\n";
      break;

      case KEYSCAN_BackSpace:
      key = "\b \b";
      break;

      case KEYSCAN_Tab:
      key = "\t";
      break;

      case KEYSCAN_CTRL:
      key = "";
      break;

      case KEYSCAN_LShift:
      key = "";
      break;

      case KEYSCAN_RShift:
      key = "";
      break;

      case KEYSCAN_PrtSc:
      key = "";
      break;

      case KEYSCAN_Alt:
      key = "";
      break;

      case KEYSCAN_Caps:
      key = "";
      break;

      case KEYSCAN_F1:
      key = "";
      break;

      case KEYSCAN_F2:
      key = "";
      break;

      case KEYSCAN_F3:
      key = "";
      break;

      case KEYSCAN_F4:
      key = "";
      break;

      case KEYSCAN_F5:
      key = "";
      break;

      case KEYSCAN_F6:
      key = "";
      break;

      case KEYSCAN_F7:
      key = "";
      break;

      case KEYSCAN_F8:
      key = "";
      break;

      case KEYSCAN_F9:
      key = "";
      break;

      case KEYSCAN_F10:
      key = "";
      break;

      case KEYSCAN_Num:
      key = "";
      break;

      case KEYSCAN_Scroll:
      key = "";
      break;

      case KEYSCAN_Home:
      key = "";
      break;

      case KEYSCAN_Up:
      key = "";
      break;

      case KEYSCAN_PgUp:
      key = "";
      break;

      case KEYSCAN_Minus2:
      key = "";
      break;

      case KEYSCAN_Left:
      key = "";
      break;

      case KEYSCAN_Center:
      key = "";
      break;

      case KEYSCAN_Right:
      key = "";
      break;

      case KEYSCAN_Plus:
      key = "";
      break;

      case KEYSCAN_End:
      key = "";
      break;

      case KEYSCAN_Down:
      key = "";
      break;

      case KEYSCAN_PgDn:
      key = "";
      break;

      case KEYSCAN_Ins:
      key = "";
      break;
      
      case KEYSCAN_Delete:
      key = "";
      break;

      case KEYSCAN_ESC:
      key = "";
      break;

      default:
      break;

   }
   printf("%s", key);
}