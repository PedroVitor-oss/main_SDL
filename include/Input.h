#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include <SDL_Image.h>
#include <Vec2.h>

struct KeyControle {
    int Unknown = SDLK_UNKNOWN;
    int Return = SDLK_RETURN;
    int Escape = SDLK_ESCAPE;
    int Backspace = SDLK_BACKSPACE;
    int Tab = SDLK_TAB;
    int Space = SDLK_SPACE;
    int Exclaim = SDLK_EXCLAIM;
    int Quotedbl = SDLK_QUOTEDBL;
    int Hash = SDLK_HASH;
    int Percent = SDLK_PERCENT;
    int Dollar = SDLK_DOLLAR;
    int Ampersand = SDLK_AMPERSAND;
    int Quote = SDLK_QUOTE;
    int LeftParen = SDLK_LEFTPAREN;
    int RightParen = SDLK_RIGHTPAREN;
    int Asterisk = SDLK_ASTERISK;
    int Plus = SDLK_PLUS;
    int Comma = SDLK_COMMA;
    int Minus = SDLK_MINUS;
    int Period = SDLK_PERIOD;
    int Slash = SDLK_SLASH;
    int Num0 = SDLK_0;
    int Num1 = SDLK_1;
    int Num2 = SDLK_2;
    int Num3 = SDLK_3;
    int Num4 = SDLK_4;
    int Num5 = SDLK_5;
    int Num6 = SDLK_6;
    int Num7 = SDLK_7;
    int Num8 = SDLK_8;
    int Num9 = SDLK_9;
    int Colon = SDLK_COLON;
    int Semicolon = SDLK_SEMICOLON;
    int Less = SDLK_LESS;
    int Equals = SDLK_EQUALS;
    int Greater = SDLK_GREATER;
    int Question = SDLK_QUESTION;
    int At = SDLK_AT;
    int LeftBracket = SDLK_LEFTBRACKET;
    int Backslash = SDLK_BACKSLASH;
    int RightBracket = SDLK_RIGHTBRACKET;
    int Caret = SDLK_CARET;
    int Underscore = SDLK_UNDERSCORE;
    int Backquote = SDLK_BACKQUOTE;
    int A = SDLK_a;
    int B = SDLK_b;
    int C = SDLK_c;
    int D = SDLK_d;
    int E = SDLK_e;
    int F = SDLK_f;
    int G = SDLK_g;
    int H = SDLK_h;
    int I = SDLK_i;
    int J = SDLK_j;
    int K = SDLK_k;
    int L = SDLK_l;
    int M = SDLK_m;
    int N = SDLK_n;
    int O = SDLK_o;
    int P = SDLK_p;
    int Q = SDLK_q;
    int R = SDLK_r;
    int S = SDLK_s;
    int T = SDLK_t;
    int U = SDLK_u;
    int V = SDLK_v;
    int W = SDLK_w;
    int X = SDLK_x;
    int Y = SDLK_y;
    int Z = SDLK_z;
    int CapsLock = SDLK_CAPSLOCK;
    int F1 = SDLK_F1;
    int F2 = SDLK_F2;
    int F3 = SDLK_F3;
    int F4 = SDLK_F4;
    int F5 = SDLK_F5;
    int F6 = SDLK_F6;
    int F7 = SDLK_F7;
    int F8 = SDLK_F8;
    int F9 = SDLK_F9;
    int F10 = SDLK_F10;
    int F11 = SDLK_F11;
    int F12 = SDLK_F12;
    int PrintScreen = SDLK_PRINTSCREEN;
    int ScrollLock = SDLK_SCROLLLOCK;
    int Pause = SDLK_PAUSE;
    int Insert = SDLK_INSERT;
    int Home = SDLK_HOME;

};

struct MouseButtonControle {
    int Left = 0;
    int Right = 1;
    int Center = 2;
};

class InputControle
{
	public:
		bool KeyIsPressed(  int CodeKey );
		bool KeyDown(  int CodeKey );
		bool KeyUp(  int CodeKey);

		void KeyEvent();
		bool MousePressed(int m);
		Vec2 GetPositionMouse();
		bool GetExit();
	protected:

	private:
	    int keyInPressed[10] = {0};
	    bool btn_mouse[3] = {false,false,false};
        Vec2 MousePosition = Vec2(0,0);
		int maxQuantKey = 10;
		int QuantKey = 0;
		int newKeyDown = 0;
		int newKeyUp = 0;
		void AddKey(int newKey);
		void RemoveKey(int Key);
		bool EventQuit = false;
};

#endif // INPUT_H
