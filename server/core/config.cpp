/*
	configuration loading/saving
*/

#include <iostream>//std::cout, std::clog
#include <sstream>//ostringstream
#include "config.h"
#include "key.h"
#include "common/iniParserWrapper.h"
#include "common/misc.h"
#include "client.h"
#undef SetPort

namespace D2K {
	namespace Config {
		const char *iniFilename = "ds2key.ini";

		int Load() {
			dictionary *ini = D2K::iniParser::load(iniFilename);

			if(ini == NULL) {
				int err = errno;
				std::clog << "Error (iniParser::load): #" << err << "\nFailed to open file: " << iniFilename << "\n";
				SetPort(DefaultPort);
				Save();

				return err;
			}

			iniParser::dump(ini, stderr);

			SetPort(iniParser::getint(ini, "settings:port", DefaultPort));
			iniParser::freedict(ini);

			return 0;
		}

		int LoadProfile(ProfileData *Profile, uint8_t profileNumber) {
			std::ostringstream ssfilename;
			ssfilename << "ds2key.p" << (int)profileNumber << ".ini";

			dictionary *ini = iniParser::load(ssfilename.str().c_str());
			iniParser::dump(ini, stderr);
			if(ini == NULL) {
				int err = errno;
				std::clog << "Error (iniParser::load): #" << err << "\nFailed to open file: " << iniFilename << "\n";
				Profile->Mouse = "Relative";
				Profile->Joy = "0";
				Profile->SetVirtualKey(kUp, KEY_UP);
				Profile->SetVirtualKey(kDown, KEY_DOWN);
				Profile->SetVirtualKey(kLeft, KEY_LEFT);
				Profile->SetVirtualKey(kRight, KEY_RIGHT);
				Profile->SetVirtualKey(kA, KEY_A);
				Profile->SetVirtualKey(kB, KEY_B);
				Profile->SetVirtualKey(kX, KEY_X);
				Profile->SetVirtualKey(kY, KEY_Y);
				Profile->SetVirtualKey(kL, KEY_L);
				Profile->SetVirtualKey(kR, KEY_R);
				Profile->SetVirtualKey(kStart, KEY_RETURN);
				Profile->SetVirtualKey(kSelect, KEY_RSHIFT);
				Profile->SetVirtualKey(kLid, KEY_ESCAPE);
				Profile->SetVirtualKey(kBlue, KEY_C);
				Profile->SetVirtualKey(kYellow, KEY_D);
				Profile->SetVirtualKey(kRed, KEY_E);
				Profile->SetVirtualKey(kGreen, KEY_F);

				Profile->SetVirtualKey(kTouch00, KEY_0);
				Profile->SetVirtualKey(kTouch01, KEY_1);
				Profile->SetVirtualKey(kTouch02, KEY_2);
				Profile->SetVirtualKey(kTouch03, KEY_3);
				Profile->SetVirtualKey(kTouch04, KEY_4);
				Profile->SetVirtualKey(kTouch05, KEY_5);
				Profile->SetVirtualKey(kTouch06, KEY_6);
				Profile->SetVirtualKey(kTouch07, KEY_7);
				Profile->SetVirtualKey(kTouch08, KEY_8);
				Profile->SetVirtualKey(kTouch09, KEY_9);
				Profile->SetVirtualKey(kTouch10, KEY_G);
				Profile->SetVirtualKey(kTouch11, KEY_H);

				for(int i = 0; i <= 11; i++) {
					Profile->TouchString[i] = "Command ";
					Profile->TouchString[i].append(itos(i));
					Profile->TouchString[i].resize(10);
				}

				const int screenW = 256;
				const int screenH = 192;
				int TouchButton = 0;
				for(int y = 0; y < screenH; y += screenH / 3)
					for(int x = 0; x < screenW; x += screenW / 4)
						Profile->SetTouchPos(	TouchButton++,	//buttons 0 - 11
												x,				//x
												y,				//y
												screenW / 4,	//w
												screenH / 3		//h
												);

				SaveProfile(Profile, profileNumber);

				return 1;
			}

			iniParser::dump(ini, stderr);

			std::string mouse = iniParser::getstring(ini, "profile:mouse", "Relative");

			if(mouse == "Absolute")
				Profile->Mouse = mouse;
			else
				Profile->Mouse = "Relative";

			Profile->Joy = iniParser::getstring(ini, "profile:joy", "0");
			Profile->SetCommand(kUp, iniParser::getstring(ini, "profile:up", "Key_None"));
			Profile->SetCommand(kDown, iniParser::getstring(ini, "profile:down", "Key_None"));
			Profile->SetCommand(kLeft, iniParser::getstring(ini, "profile:left", "Key_None"));
			Profile->SetCommand(kRight, iniParser::getstring(ini, "profile:right", "Key_None"));
			Profile->SetCommand(kA, iniParser::getstring(ini, "profile:a", "Key_None"));
			Profile->SetCommand(kB, iniParser::getstring(ini, "profile:b", "Key_None"));
			Profile->SetCommand(kX, iniParser::getstring(ini, "profile:x", "Key_None"));
			Profile->SetCommand(kY, iniParser::getstring(ini, "profile:y", "Key_None"));
			Profile->SetCommand(kL, iniParser::getstring(ini, "profile:l", "Key_None"));
			Profile->SetCommand(kR, iniParser::getstring(ini, "profile:r", "Key_None"));
			Profile->SetCommand(kStart, iniParser::getstring(ini, "profile:start", "Key_None"));
			Profile->SetCommand(kSelect, iniParser::getstring(ini, "profile:select", "Key_None"));
			Profile->SetCommand(kLid, iniParser::getstring(ini, "profile:lid", "Key_None"));
			Profile->SetCommand(kBlue, iniParser::getstring(ini, "profile:blue", "Key_None"));
			Profile->SetCommand(kYellow, iniParser::getstring(ini, "profile:yellow", "Key_None"));
			Profile->SetCommand(kRed, iniParser::getstring(ini, "profile:red", "Key_None"));
			Profile->SetCommand(kGreen, iniParser::getstring(ini, "profile:green", "Key_None"));

			Profile->SetCommand(kTouch00, iniParser::getstring(ini, "profile:touch00", "Key_None"));
			Profile->SetCommand(kTouch01, iniParser::getstring(ini, "profile:touch01", "Key_None"));
			Profile->SetCommand(kTouch02, iniParser::getstring(ini, "profile:touch02", "Key_None"));
			Profile->SetCommand(kTouch03, iniParser::getstring(ini, "profile:touch03", "Key_None"));
			Profile->SetCommand(kTouch04, iniParser::getstring(ini, "profile:touch04", "Key_None"));
			Profile->SetCommand(kTouch05, iniParser::getstring(ini, "profile:touch05", "Key_None"));
			Profile->SetCommand(kTouch06, iniParser::getstring(ini, "profile:touch06", "Key_None"));
			Profile->SetCommand(kTouch07, iniParser::getstring(ini, "profile:touch07", "Key_None"));
			Profile->SetCommand(kTouch08, iniParser::getstring(ini, "profile:touch08", "Key_None"));
			Profile->SetCommand(kTouch09, iniParser::getstring(ini, "profile:touch09", "Key_None"));
			Profile->SetCommand(kTouch10, iniParser::getstring(ini, "profile:touch10", "Key_None"));
			Profile->SetCommand(kTouch11, iniParser::getstring(ini, "profile:touch11", "Key_None"));

			Profile->TouchString[0] = iniParser::getstring(ini, "profile:touchstring00", "Command 0");
			Profile->TouchString[1] = iniParser::getstring(ini, "profile:touchstring01", "Command 1");
			Profile->TouchString[2] = iniParser::getstring(ini, "profile:touchstring02", "Command 2");
			Profile->TouchString[3] = iniParser::getstring(ini, "profile:touchstring03", "Command 3");
			Profile->TouchString[4] = iniParser::getstring(ini, "profile:touchstring04", "Command 4");
			Profile->TouchString[5] = iniParser::getstring(ini, "profile:touchstring05", "Command 5");
			Profile->TouchString[6] = iniParser::getstring(ini, "profile:touchstring06", "Command 6");
			Profile->TouchString[7] = iniParser::getstring(ini, "profile:touchstring07", "Command 7");
			Profile->TouchString[8] = iniParser::getstring(ini, "profile:touchstring08", "Command 8");
			Profile->TouchString[9] = iniParser::getstring(ini, "profile:touchstring09", "Command 9");
			Profile->TouchString[10] = iniParser::getstring(ini, "profile:touchstring10", "Command 10");
			Profile->TouchString[11] = iniParser::getstring(ini, "profile:touchstring11", "Command 11");

			Profile->TouchX[0] = D2K::stoi(iniParser::getstring(ini, "profile:touch00X", "0"));
			Profile->TouchX[1] = D2K::stoi(iniParser::getstring(ini, "profile:touch01X", "0"));
			Profile->TouchX[2] = D2K::stoi(iniParser::getstring(ini, "profile:touch02X", "0"));
			Profile->TouchX[3] = D2K::stoi(iniParser::getstring(ini, "profile:touch03X", "0"));
			Profile->TouchX[4] = D2K::stoi(iniParser::getstring(ini, "profile:touch04X", "0"));
			Profile->TouchX[5] = D2K::stoi(iniParser::getstring(ini, "profile:touch05X", "0"));
			Profile->TouchX[6] = D2K::stoi(iniParser::getstring(ini, "profile:touch06X", "0"));
			Profile->TouchX[7] = D2K::stoi(iniParser::getstring(ini, "profile:touch07X", "0"));
			Profile->TouchX[8] = D2K::stoi(iniParser::getstring(ini, "profile:touch08X", "0"));
			Profile->TouchX[9] = D2K::stoi(iniParser::getstring(ini, "profile:touch09X", "0"));
			Profile->TouchX[10] = D2K::stoi(iniParser::getstring(ini, "profile:touch10X", "0"));
			Profile->TouchX[11] = D2K::stoi(iniParser::getstring(ini, "profile:touch11X", "0"));

			Profile->TouchY[0] = D2K::stoi(iniParser::getstring(ini, "profile:touch00Y", "0"));
			Profile->TouchY[1] = D2K::stoi(iniParser::getstring(ini, "profile:touch01Y", "0"));
			Profile->TouchY[2] = D2K::stoi(iniParser::getstring(ini, "profile:touch02Y", "0"));
			Profile->TouchY[3] = D2K::stoi(iniParser::getstring(ini, "profile:touch03Y", "0"));
			Profile->TouchY[4] = D2K::stoi(iniParser::getstring(ini, "profile:touch04Y", "0"));
			Profile->TouchY[5] = D2K::stoi(iniParser::getstring(ini, "profile:touch05Y", "0"));
			Profile->TouchY[6] = D2K::stoi(iniParser::getstring(ini, "profile:touch06Y", "0"));
			Profile->TouchY[7] = D2K::stoi(iniParser::getstring(ini, "profile:touch07Y", "0"));
			Profile->TouchY[8] = D2K::stoi(iniParser::getstring(ini, "profile:touch08Y", "0"));
			Profile->TouchY[9] = D2K::stoi(iniParser::getstring(ini, "profile:touch09Y", "0"));
			Profile->TouchY[10] = D2K::stoi(iniParser::getstring(ini, "profile:touch10Y", "0"));
			Profile->TouchY[11] = D2K::stoi(iniParser::getstring(ini, "profile:touch11Y", "0"));

			Profile->TouchW[0] = D2K::stoi(iniParser::getstring(ini, "profile:touch00W", "0"));
			Profile->TouchW[1] = D2K::stoi(iniParser::getstring(ini, "profile:touch01W", "0"));
			Profile->TouchW[2] = D2K::stoi(iniParser::getstring(ini, "profile:touch02W", "0"));
			Profile->TouchW[3] = D2K::stoi(iniParser::getstring(ini, "profile:touch03W", "0"));
			Profile->TouchW[4] = D2K::stoi(iniParser::getstring(ini, "profile:touch04W", "0"));
			Profile->TouchW[5] = D2K::stoi(iniParser::getstring(ini, "profile:touch05W", "0"));
			Profile->TouchW[6] = D2K::stoi(iniParser::getstring(ini, "profile:touch06W", "0"));
			Profile->TouchW[7] = D2K::stoi(iniParser::getstring(ini, "profile:touch07W", "0"));
			Profile->TouchW[8] = D2K::stoi(iniParser::getstring(ini, "profile:touch08W", "0"));
			Profile->TouchW[9] = D2K::stoi(iniParser::getstring(ini, "profile:touch09W", "0"));
			Profile->TouchW[10] = D2K::stoi(iniParser::getstring(ini, "profile:touch10W", "0"));
			Profile->TouchW[11] = D2K::stoi(iniParser::getstring(ini, "profile:touch11W", "0"));

			Profile->TouchH[0] = D2K::stoi(iniParser::getstring(ini, "profile:touch00H", "0"));
			Profile->TouchH[1] = D2K::stoi(iniParser::getstring(ini, "profile:touch01H", "0"));
			Profile->TouchH[2] = D2K::stoi(iniParser::getstring(ini, "profile:touch02H", "0"));
			Profile->TouchH[3] = D2K::stoi(iniParser::getstring(ini, "profile:touch03H", "0"));
			Profile->TouchH[4] = D2K::stoi(iniParser::getstring(ini, "profile:touch04H", "0"));
			Profile->TouchH[5] = D2K::stoi(iniParser::getstring(ini, "profile:touch05H", "0"));
			Profile->TouchH[6] = D2K::stoi(iniParser::getstring(ini, "profile:touch06H", "0"));
			Profile->TouchH[7] = D2K::stoi(iniParser::getstring(ini, "profile:touch07H", "0"));
			Profile->TouchH[8] = D2K::stoi(iniParser::getstring(ini, "profile:touch08H", "0"));
			Profile->TouchH[9] = D2K::stoi(iniParser::getstring(ini, "profile:touch09H", "0"));
			Profile->TouchH[10] = D2K::stoi(iniParser::getstring(ini, "profile:touch10H", "0"));
			Profile->TouchH[11] = D2K::stoi(iniParser::getstring(ini, "profile:touch11H", "0"));
			iniParser::freedict(ini);

			for(int i = 0; i <= 11; i++) {
                if(Profile->TouchW[i] == 0 &&  Profile->TouchH[i] == 0)     //if the button won't even show
                    Profile->TouchString[i].clear();
                else                                //otherwise shrink down to our max chars
                    Profile->TouchString[i].resize(10);
			}

			return 0;
		}

		int Save() {
			FILE *file = fopen(iniFilename, "w");

			if(file == NULL) {
				int err = errno;
				std::clog << "Error (fopen): #" << err << "\nFailed to open file: " << iniFilename << "\n";

				return err;
			}

			fprintf(file, "[Settings]\n");
			fprintf(file, "Port=%u\n", GetPort());

			fclose(file);
			Load();

			return 0;
		}

		int SaveProfile(ProfileData *Profile, uint8_t profileNumber) {
			std::ostringstream ssfilename;
			ssfilename << "ds2key.p" << (int)profileNumber << ".ini";

			FILE *file = fopen(ssfilename.str().c_str(), "w");
			if(file == NULL) {
				int err = errno;
				std::clog << "Error (fopen): #" << err << "\nFailed to save file: " << iniFilename << "\n";

				return err;
			}

			fprintf(file, "[Profile]\n");
			fprintf(file, "Mouse=%s\n", Profile->Mouse.c_str());
			fprintf(file, "Joy=%s\n", Profile->Joy.c_str());
			fprintf(file, "Up=%s\n", Profile->GetButtonString(kUp).c_str());
			fprintf(file, "Down=%s\n", Profile->GetButtonString(kDown).c_str());
			fprintf(file, "Left=%s\n", Profile->GetButtonString(kLeft).c_str());
			fprintf(file, "Right=%s\n", Profile->GetButtonString(kRight).c_str());
			fprintf(file, "A=%s\n", Profile->GetButtonString(kA).c_str());
			fprintf(file, "B=%s\n", Profile->GetButtonString(kB).c_str());
			fprintf(file, "X=%s\n", Profile->GetButtonString(kX).c_str());
			fprintf(file, "Y=%s\n", Profile->GetButtonString(kY).c_str());
			fprintf(file, "L=%s\n", Profile->GetButtonString(kL).c_str());
			fprintf(file, "R=%s\n", Profile->GetButtonString(kR).c_str());
			fprintf(file, "Start=%s\n", Profile->GetButtonString(kStart).c_str());
			fprintf(file, "Select=%s\n", Profile->GetButtonString(kSelect).c_str());
			fprintf(file, "Lid=%s\n", Profile->GetButtonString(kLid).c_str());
			fprintf(file, "Blue=%s\n", Profile->GetButtonString(kBlue).c_str());
			fprintf(file, "Yellow=%s\n", Profile->GetButtonString(kYellow).c_str());
			fprintf(file, "Red=%s\n", Profile->GetButtonString(kRed).c_str());
			fprintf(file, "Green=%s\n", Profile->GetButtonString(kGreen).c_str());

			for(int i = 0; i <= 11; i++) {
				fprintf(file, "Touch%.2d=%s\n", i, Profile->GetButtonString(kTouch00 + i).c_str());
				fprintf(file, "TouchString%.2d=%s\n", i, Profile->TouchString[i].c_str());
				fprintf(file, "Touch%.2dX=%i\n", i, Profile->TouchX[i]);
				fprintf(file, "Touch%.2dY=%i\n", i, Profile->TouchY[i]);
				fprintf(file, "Touch%.2dW=%i\n", i, Profile->TouchW[i]);
				fprintf(file, "Touch%.2dH=%i\n", i, Profile->TouchH[i]);
			}

			fclose(file);

			return 0;
		}

		//private
		//Currently assigned port
		uint16_t Port = DefaultPort;

		//public
		uint16_t GetPort() {
			return Config::Port;
		}

		void SetPort(uint16_t Port) {
			if(Port == 0)
				Config::Port = DefaultPort;
			else
				Config::Port = Port;
		}
	}
}