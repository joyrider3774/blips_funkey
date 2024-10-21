#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <SDL_rotozoom.h>
#include "CInput.h"
#include "Common.h"
#include "GameFuncs.h"

void TitleScreen()
{
	int alpha = 0;
    SDL_Surface *Tmp;
	int Teller, Selection = 1;
	CInput *Input = new CInput(InputDelay, disableJoysticks);
	SDL_Rect Rect;
	char *Tekst = new char[300];
	Tmp = SDL_DisplayFormat(Buffer);
	while (GameState == GSTitleScreen)
	{
        if(MusicCount > 0)
		{
            if(GlobalSoundEnabled)
			{
                if(!Mix_PlayingMusic())
                {
                    SelectedMusic = 0;
                    Mix_PlayMusic(Music[SelectedMusic],0);
                    SetVolume(Volume);
                }
			}
		}
		SDL_BlitSurface(IMGTitleScreen,NULL,Tmp,NULL);
		Input->Update();

		if(Input->KeyboardHeld[SDLK_ESCAPE] || Input->SpecialsHeld[SPECIAL_QUIT_EV])
            GameState = GSQuit;

		if(Input->JoystickHeld[0][JoystickSetup->GetButtonValue(BUT_R)] || Input->KeyboardHeld[SDLK_n])
        {
            if(Input->Ready() && (Input->JoystickHeld[0][JoystickSetup->GetButtonValue(BUT_LEFT)] || Input->KeyboardHeld[SDLK_l] || Input->KeyboardHeld[SDLK_LEFT] ))
            {
                if(StartScreenX - 2 >= 0)
                    StartScreenX -=2;
                Input->Delay();
            }

            if(Input->Ready() && (Input->JoystickHeld[0][JoystickSetup->GetButtonValue(BUT_RIGHT)] || Input->KeyboardHeld[SDLK_r] || Input->KeyboardHeld[SDLK_RIGHT] ))
            {
                if(StartScreenX + 2 + Buffer->w <= Screen->w)
                    StartScreenX +=2;
                Input->Delay();
            }

            if(Input->Ready() && (Input->JoystickHeld[0][JoystickSetup->GetButtonValue(BUT_UP)] || Input->KeyboardHeld[SDLK_u] || Input->KeyboardHeld[SDLK_UP] ))
            {
                if(StartScreenY - 2 >=0)
                    StartScreenY -=2;
                Input->Delay();
            }

            if(Input->Ready() && (Input->JoystickHeld[0][JoystickSetup->GetButtonValue(BUT_DOWN)] || Input->KeyboardHeld[SDLK_d] || Input->KeyboardHeld[SDLK_DOWN] ))
            {
                if(StartScreenY + 2 + Buffer->h <= Screen->h)
                    StartScreenY +=2;
                Input->Delay();
            }
        }

        if (Input->Ready() && (Input->JoystickHeld[0][JoystickSetup->GetButtonValue(BUT_VOLUP)] || Input->KeyboardHeld[SDLK_o]))
        {
            IncVolume();
            Input->Delay();
        }

        if (Input->Ready() && (Input->JoystickHeld[0][JoystickSetup->GetButtonValue(BUT_VOLMIN)] || Input->KeyboardHeld[SDLK_v]))
        {
            DecVolume();
            Input->Delay();
        }

        if (Input->Ready() && (Input->JoystickHeld[0][JoystickSetup->GetButtonValue(BUT_LEFT)] || Input->KeyboardHeld[SDLK_l] || Input->KeyboardHeld[SDLK_LEFT] ))
        {
            if(Selection==3)
                if (InstalledLevelPacksCount > 0)
                    if(SelectedLevelPack > 0)
                    {
                        SelectedLevelPack--;
                        sprintf(LevelPackName,"%s",InstalledLevelPacks[SelectedLevelPack]);
                        sprintf(LevelPackFileName,"%s",InstalledLevelPacks[SelectedLevelPack]);
                        AddUnderScores(LevelPackFileName);
                    }
            Input->Delay();
        }

        if (Input->Ready() && (Input->JoystickHeld[0][JoystickSetup->GetButtonValue(BUT_RIGHT)] || Input->KeyboardHeld[SDLK_r] || Input->KeyboardHeld[SDLK_RIGHT] ))
        {
            if (Selection==3)
                if (InstalledLevelPacksCount > 0)
                    if(SelectedLevelPack < InstalledLevelPacksCount-1)
                    {
                        SelectedLevelPack++;
                        sprintf(LevelPackName,"%s",InstalledLevelPacks[SelectedLevelPack]);
                        sprintf(LevelPackFileName,"%s",InstalledLevelPacks[SelectedLevelPack]);
                        AddUnderScores(LevelPackFileName);
                    }
            Input->Delay();
        }

        if((Input->Ready()) && (Input->KeyboardHeld[SDLK_d] || Input->KeyboardHeld[SDLK_DOWN] || Input->JoystickHeld[0][JoystickSetup->GetButtonValue(BUT_DOWN)]) &&
           !(Input->JoystickHeld[0][JoystickSetup->GetButtonValue(BUT_R)] || Input->KeyboardHeld[SDLK_n]))
        {
            if (Selection < 5)
            {
                Selection++;
                if (GlobalSoundEnabled)
                    Mix_PlayChannel(-1,Sounds[SND_MENU],0);
            }

            Input->Delay();
        }

        if((Input->Ready()) && (Input->KeyboardHeld[SDLK_u] || Input->KeyboardHeld[SDLK_UP] || Input->JoystickHeld[0][JoystickSetup->GetButtonValue(BUT_UP)]) &&
           !(Input->JoystickHeld[0][JoystickSetup->GetButtonValue(BUT_R)] || Input->KeyboardHeld[SDLK_n]))
        {
            if (Selection > 1)
            {
                Selection--;
                if (GlobalSoundEnabled)
                    Mix_PlayChannel(-1,Sounds[SND_MENU],0);
            }
            Input->Delay();
        }

        if(Input->JoystickHeld[0][JoystickSetup->GetButtonValue(BUT_A)] || Input->KeyboardHeld[SDLK_a] || Input->KeyboardHeld[SDLK_SPACE] || Input->KeyboardHeld[SDLK_s] || Input->KeyboardHeld[SDLK_RETURN] )
        {
            switch(Selection)
            {
                case 1:
                    if (InstalledLevelPacksCount >0)
                    {
                        FindLevels();
                        if(InstalledLevels > 0)
                        {
                            LoadUnlockData();
                            SelectedLevel=UnlockedLevels;
                            LevelEditorMode=false;
                            GameState=GSStageSelect;
                            if (GlobalSoundEnabled)
                                Mix_PlayChannel(-1,Sounds[SND_SELECT],0);
                        }
                        else
                        {
                            if (GlobalSoundEnabled)
                                Mix_PlayChannel(-1,Sounds[SND_SELECT],0);
                            SDL_BlitSurface(IMGTitleScreen,NULL,Buffer,NULL);
                            sprintf(Tekst,"There are no levels found in levelpack\n%s\n\nPlease create a level for this level pack\nfirst!",LevelPackName);
                            PrintForm(Tekst);
                            Input->Reset();
                        }
                    }
                    break;
                case 2:
                    GameState=GSLevelEditorMenu;
                    LevelEditorMode=true;
                    if (GlobalSoundEnabled)
                        Mix_PlayChannel(-1,Sounds[SND_SELECT],0);
                    break;
                case 4:
                    GameState=GSCredits;
                    if (GlobalSoundEnabled)
                        Mix_PlayChannel(-1,Sounds[SND_SELECT],0);
                    break;
                case 5:
                //     GameState = GSSetupUsbJoystickButtons;
                //     if (GlobalSoundEnabled)
                //         Mix_PlayChannel(-1,Sounds[SND_SELECT],0);
                //     break;
                // case 6:
                    GameState = GSQuit;
                    if (GlobalSoundEnabled)
                        Mix_PlayChannel(-1,Sounds[SND_SELECT],0);
                    break;

            }

        }
   		boxRGBA(Tmp,40*UI_WIDTH_SCALE,80*UI_HEIGHT_SCALE,280*UI_WIDTH_SCALE,160*UI_HEIGHT_SCALE,MenuBoxColor.r,MenuBoxColor.g,MenuBoxColor.b,MenuBoxColor.unused);
		rectangleRGBA(Tmp,40*UI_WIDTH_SCALE,80*UI_HEIGHT_SCALE,280*UI_WIDTH_SCALE,160*UI_HEIGHT_SCALE,MenuBoxBorderColor.r,MenuBoxBorderColor.g,MenuBoxBorderColor.b,MenuBoxBorderColor.unused);
		rectangleRGBA(Tmp,41*UI_WIDTH_SCALE,81*UI_HEIGHT_SCALE,279*UI_WIDTH_SCALE,159*UI_HEIGHT_SCALE,MenuBoxBorderColor.r,MenuBoxBorderColor.g,MenuBoxBorderColor.b,MenuBoxBorderColor.unused);
		sprintf(Tekst,"Play Selected LevelPack\nLevel Editor\n<%s>\nCredits\nQuit",LevelPackName);
		WriteText(Tmp,BigFont,Tekst,strlen(Tekst),70*UI_WIDTH_SCALE,85*UI_HEIGHT_SCALE,2,MenuTextColor,false);
		if (Selection > 1)
		{
			strcpy(Tekst,"\n");
			for(Teller=2;Teller<Selection;Teller++)
				strcat(Tekst, "\n");
			strcat(Tekst,">>");
		}
		else
			sprintf(Tekst,">>");
		WriteText(Tmp,BigFont,Tekst,strlen(Tekst),45*UI_WIDTH_SCALE,85*UI_HEIGHT_SCALE,2,MenuTextColor,false);
		Rect.w = Buffer->w;
        Rect.h = Buffer->h;
        Rect.x = StartScreenX;
        Rect.y = StartScreenY;
		if (alpha < 255)
        {
            if(alpha+AlphaInc > MaxAlpha)
            {
                alpha = 255;
                SDL_SetAlpha(Tmp,SDL_SRCALPHA | SDL_RLEACCEL,alpha);
            }
            else
            {
                alpha+=AlphaInc;
                SDL_SetAlpha(Tmp,SDL_SRCALPHA | SDL_RLEACCEL,alpha);
            }
        }
        SDL_BlitSurface(Tmp,NULL,Buffer,NULL);
        SDL_FillRect(Buffer1,NULL,SDL_MapRGB(Buffer1->format,0,0,0));
        SDL_BlitSurface(Buffer,NULL,Buffer1,&Rect);
#ifdef FUNKEY        
		SDL_BlitSurface(Buffer1,NULL,Screen,NULL);
#else
		SDL_Surface *ScreenBufferZoom = zoomSurface(Buffer1,(double)WINDOW_WIDTH / ORIG_WINDOW_WIDTH,(double)WINDOW_HEIGHT / ORIG_WINDOW_HEIGHT,0);
        SDL_BlitSurface(ScreenBufferZoom,NULL,Screen,NULL);
        SDL_FreeSurface(ScreenBufferZoom);
#endif
        SDL_Flip(Screen);
        SDL_framerateDelay(&Fpsman);
	}
	delete[] Tekst;
	SDL_FreeSurface(Tmp);
	delete Input;
}
