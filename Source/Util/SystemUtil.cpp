#include "StdAfx.h"
#include <SDL.h>
#include "Config.h"
#include "GameContent.h"

//#include <crtdbg.h>

/////////////////////////////////////////////////////////////////////////////////
//		Memory check
/////////////////////////////////////////////////////////////////////////////////
//void win32_check()
//{
//	_ASSERTE(_CrtCheckMemory()) ;
//}

/////////////////////////////////////////////////////////////////////////////////
//		Keys
/////////////////////////////////////////////////////////////////////////////////

//If you wonder why we are converting SDL2 keys into VK_*, mostly to keep compatibility with controls.init and
//existing code

bool isPressed(uint32_t key) {
    if (!applicationHasFocus()) return false;

    //According to key type, use diff SDL2 methods
    SDL_Keycode keycode = 0;
    std::vector<SDL_Keycode> keycodes;
    switch (key) {
        case VK_LBUTTON:
        case VK_MBUTTON:
        case VK_RBUTTON:
            return SDL_GetMouseState(nullptr, nullptr) & key;
        case VK_SHIFT:
            return SDL_GetModState() & KMOD_SHIFT;
        case VK_CONTROL:
            return SDL_GetModState() & KMOD_CTRL;
        case VK_MENU:
            return SDL_GetModState() & KMOD_ALT;
        case VK_BACK:           keycode = SDLK_BACKSPACE; break;
        case VK_TAB:            keycode = SDLK_TAB; break;
        case VK_RETURN:
            keycodes.emplace_back(SDLK_RETURN);
            keycodes.emplace_back(SDLK_KP_ENTER);
            break;
        case VK_PAUSE:          keycode = SDLK_PAUSE; break;
        case VK_CAPITAL:        keycode = SDLK_CAPSLOCK; break;
        case VK_ESCAPE:         keycode = SDLK_ESCAPE; break;
        case VK_SPACE:          keycode = SDLK_SPACE; break;
        case VK_PRIOR:          keycode = SDLK_PAGEUP; break;
        case VK_NEXT:           keycode = SDLK_PAGEDOWN; break;
        case VK_END:            keycode = SDLK_END; break;
        case VK_HOME:           keycode = SDLK_HOME; break;
        case VK_LEFT:           keycode = SDLK_LEFT; break;
        case VK_UP:             keycode = SDLK_UP; break;
        case VK_RIGHT:          keycode = SDLK_RIGHT; break;
        case VK_DOWN:           keycode = SDLK_DOWN; break;
        case VK_INSERT:         keycode = SDLK_INSERT; break;
        case VK_DELETE:         keycode = SDLK_DELETE; break;
        case VK_F1:             keycode = SDLK_F1; break;
        case VK_F2:             keycode = SDLK_F2; break;
        case VK_F3:             keycode = SDLK_F3; break;
        case VK_F4:             keycode = SDLK_F4; break;
        case VK_F5:             keycode = SDLK_F5; break;
        case VK_F6:             keycode = SDLK_F6; break;
        case VK_F7:             keycode = SDLK_F7; break;
        case VK_F8:             keycode = SDLK_F8; break;
        case VK_F9:             keycode = SDLK_F9; break;
        case VK_F10:            keycode = SDLK_F10; break;
        case VK_F11:            keycode = SDLK_F11; break;
        case VK_F12:            keycode = SDLK_F12; break;
        case VK_TILDE:          keycode = SDLK_BACKQUOTE; break;
        case VK_SLASH:          keycode = SDLK_SLASH; break;
        case VK_BKSLASH:        keycode = SDLK_BACKSLASH; break;
        case VK_NUMPAD0:        keycode = SDLK_KP_0; break;
        case VK_NUMPAD1:        keycode = SDLK_KP_1; break;
        case VK_NUMPAD2:        keycode = SDLK_KP_2; break;
        case VK_NUMPAD3:        keycode = SDLK_KP_3; break;
        case VK_NUMPAD4:        keycode = SDLK_KP_4; break;
        case VK_NUMPAD5:        keycode = SDLK_KP_5; break;
        case VK_NUMPAD6:        keycode = SDLK_KP_6; break;
        case VK_NUMPAD7:        keycode = SDLK_KP_7; break;
        case VK_NUMPAD8:        keycode = SDLK_KP_8; break;
        case VK_NUMPAD9:        keycode = SDLK_KP_9; break;
        case VK_MULTIPLY:       keycode = SDLK_KP_MULTIPLY; break;
        case VK_DIVIDE:         keycode = SDLK_KP_DIVIDE; break;
        case VK_NUMLOCK:        keycode = SDLK_NUMLOCKCLEAR; break;
        case VK_SCROLL:         keycode = SDLK_SCROLLLOCK; break;
        case VK_ADD:
            keycodes.emplace_back(SDLK_PLUS);
            keycodes.emplace_back(SDLK_KP_PLUS);
            break;
        case VK_SEPARATOR:      keycode = SDLK_SEPARATOR; break;
        case VK_SUBTRACT:
            keycodes.emplace_back(SDLK_MINUS);
            keycodes.emplace_back(SDLK_KP_MINUS);
            break;
        default:
#ifdef PERIMETER_DEBUG
            printf("Unknown VK keycode requested %u\n", key);
#endif
            return false;
    }

    //Get state of keys
    int numkeys;
    const Uint8 *state = SDL_GetKeyboardState(&numkeys);

    do {
        //If we have more keycodes put them
        if (!keycodes.empty()) {
            keycode = keycodes.back();
            keycodes.pop_back();
        }
        
        //Convert VK to scancode and return state
        SDL_Scancode scancode = SDL_GetScancodeFromKey(keycode);
        if (scancode >= numkeys) continue;
        if (state[scancode]) return true;
    } while (!keycodes.empty());
    return false;
}

sKey::sKey(SDL_Keysym keysym, bool set_by_async_funcs) {
    fullkey = 0;
    switch (keysym.sym) {
        case SDLK_LGUI:
        case SDLK_RGUI:
        case SDLK_PRINTSCREEN:
            //Ignore these
            break;
        case SDLK_BACKSPACE:    fullkey = VK_BACK; break;
        case SDLK_TAB:          fullkey = VK_TAB; break;
        case SDLK_KP_ENTER:
        case SDLK_RETURN:       fullkey = VK_RETURN; break;
        case SDLK_LSHIFT:
        case SDLK_RSHIFT:       fullkey = VK_SHIFT; break;
        case SDLK_LCTRL:
        case SDLK_RCTRL:        fullkey = VK_CONTROL; break;
        case SDLK_LALT:
        case SDLK_RALT:         fullkey = VK_MENU; break;
        case SDLK_PAUSE:        fullkey = VK_PAUSE; break;
        case SDLK_CAPSLOCK:     fullkey = VK_CAPITAL; break;
        case SDLK_ESCAPE:       fullkey = VK_ESCAPE; break;
        case SDLK_SPACE:        fullkey = VK_SPACE; break;
        case SDLK_PAGEUP:       fullkey = VK_PRIOR; break;
        case SDLK_PAGEDOWN:     fullkey = VK_NEXT; break;
        case SDLK_END:          fullkey = VK_END; break;
        case SDLK_HOME:         fullkey = VK_HOME; break;
        case SDLK_LEFT:         fullkey = VK_LEFT; break;
        case SDLK_UP:           fullkey = VK_UP; break;
        case SDLK_RIGHT:        fullkey = VK_RIGHT; break;
        case SDLK_DOWN:         fullkey = VK_DOWN; break;
        case SDLK_INSERT:       fullkey = VK_INSERT; break;
        case SDLK_DELETE:       fullkey = VK_DELETE; break;
        case SDLK_F1:           fullkey = VK_F1; break;
        case SDLK_F2:           fullkey = VK_F2; break;
        case SDLK_F3:           fullkey = VK_F3; break;
        case SDLK_F4:           fullkey = VK_F4; break;
        case SDLK_F5:           fullkey = VK_F5; break;
        case SDLK_F6:           fullkey = VK_F6; break;
        case SDLK_F7:           fullkey = VK_F7; break;
        case SDLK_F8:           fullkey = VK_F8; break;
        case SDLK_F9:           fullkey = VK_F9; break;
        case SDLK_F10:          fullkey = VK_F10; break;
        case SDLK_F11:          fullkey = VK_F11; break;
        case SDLK_F12:          fullkey = VK_F12; break;
        case SDLK_BACKQUOTE:    fullkey = VK_TILDE; break;
        case SDLK_SLASH:        fullkey = VK_SLASH; break;
        case SDLK_BACKSLASH:    fullkey = VK_BKSLASH; break;
        case SDLK_KP_0:         fullkey = VK_NUMPAD0; break;
        case SDLK_KP_1:         fullkey = VK_NUMPAD1; break;
        case SDLK_KP_2:         fullkey = VK_NUMPAD2; break;
        case SDLK_KP_3:         fullkey = VK_NUMPAD3; break;
        case SDLK_KP_4:         fullkey = VK_NUMPAD4; break;
        case SDLK_KP_5:         fullkey = VK_NUMPAD5; break;
        case SDLK_KP_6:         fullkey = VK_NUMPAD6; break;
        case SDLK_KP_7:         fullkey = VK_NUMPAD7; break;
        case SDLK_KP_8:         fullkey = VK_NUMPAD8; break;
        case SDLK_KP_9:         fullkey = VK_NUMPAD9; break;
        case SDLK_KP_MULTIPLY:  fullkey = VK_MULTIPLY; break;
        case SDLK_KP_DIVIDE:    fullkey = VK_DIVIDE; break;
        case SDLK_NUMLOCKCLEAR: fullkey = VK_NUMLOCK; break;
        case SDLK_SCROLLLOCK:   fullkey = VK_SCROLL; break;
        case SDLK_KP_PLUS:
        case SDLK_PLUS:         fullkey = VK_ADD; break;
        case SDLK_SEPARATOR:    fullkey = VK_SEPARATOR; break;
        case SDLK_KP_MINUS:
        case SDLK_MINUS:        fullkey = VK_SUBTRACT; break;
        default:
            //Apparently game uses uppercase ASCII codes for keys
            uint8_t byte = keysym.sym & 0xFF;
            if (byte >= 'a' && byte <= 'z') {
                fullkey = toupper(byte);
            } else if (byte >= '0' && byte <= '9') {
                fullkey = byte;
            } else {
#ifdef PERIMETER_DEBUG
                printf("Unknown SDL key requested scan %d sym %d\n", keysym.scancode, keysym.sym);
#endif
            }
    }
    
    //Add modifiers
    auto mod = keysym.mod;
    if ((mod & KMOD_SHIFT) != 0) {
        fullkey |= KBD_SHIFT;
        shift |= 1;
    }
    if ((mod & KMOD_CTRL) != 0) {
        fullkey |= KBD_CTRL;
        ctrl |= 1;
    }
    if ((mod & KMOD_ALT) != 0) {
        fullkey |= KBD_MENU;
        menu |= 1;
    }
    
    // Same as normal sKey constructor

    if(set_by_async_funcs){
        ctrl = isControlPressed();
        shift = isShiftPressed();
        menu = isAltPressed();
    }

    // добавляем расширенные коды для командных кодов
    if(key == VK_CONTROL)
        ctrl |= 1;
    if(key == VK_SHIFT)
        shift |= 1;
    if(key == VK_MENU)
        menu |= 1;
}

sKey::sKey(int fullkey_, bool set_by_async_funcs) {
    fullkey = fullkey_;
    if(set_by_async_funcs){
        ctrl = isControlPressed();
        shift = isShiftPressed();
        menu = isAltPressed();
    }
    // добавляем расширенные коды для командных кодов
    if(key == VK_CONTROL)
        ctrl |= 1;
    if(key == VK_SHIFT)
        shift |= 1;
    if(key == VK_MENU)
        menu |= 1;
}

/////////////////////////////////////////////////////////////////////////////////
//		File/Paths
/////////////////////////////////////////////////////////////////////////////////

bool create_directories(const char* path, std::error_code* error) {
    bool result;
    if (error) {
        result = std::filesystem::create_directories(path, *error);
    } else {
        result = std::filesystem::create_directories(path);
    }
    if (result) {
        scan_resource_paths(path);
    }
    return result;
}

// ---   Ini file   ---------------------
IniManager::IniManager(const char* fname, bool check_existence, bool full_path) {
    fname_ = fname;
    check_existence_ = check_existence;
    is_full_path = full_path;
}

const char* IniManager::get(const char* section, const char* key)
{
	static char buf[256];
    static char path[MAX_PATH];
    
    if (!is_full_path) {
        std::string pathres = convert_path_resource(fname_.c_str());
        if (pathres.empty())
            ErrH.Abort("Ini file not found: ", XERR_USER, 0, fname_.c_str());

        //GetPrivateProfileString needs full path
        if (_fullpath(path, pathres.c_str(), MAX_PATH) == NULL)
            ErrH.Abort("Ini full path not found: ", XERR_USER, 0, pathres.c_str());
    } else {
        strncpy(path, fname_.c_str(), MAX_PATH);
    }
    
	if(!GetPrivateProfileString(section,key,NULL,buf,256,path)){
		*buf = 0;
		if (check_existence_) {
            fprintf(stderr, "INI key not found %s %s %s\n", path, section, key);
        }
	}

	return buf;
}
void IniManager::put(const char* section, const char* key, const char* val)
{
    static char path[MAX_PATH];

    if (!is_full_path) {
        std::string pathres = convert_path_resource(fname_.c_str());
        if(pathres.empty())
            ErrH.Abort("Ini file not found: ", XERR_USER, 0, fname_.c_str());
    
        //WritePrivateProfileString needs full path
        if(_fullpath(path, pathres.c_str(), MAX_PATH) == NULL)
            ErrH.Abort("Ini full path not found: ", XERR_USER, 0, pathres.c_str());
    } else {
        strncpy(path, fname_.c_str(), MAX_PATH);
    }

	WritePrivateProfileString(section,key,val,path);
}

int IniManager::getInt(const char* section, const char* key) 
{ 
	return atoi(get(section, key));
}

bool IniManager::getInt(const char* section, const char* key, int& value) 
{
	const char* str=get(section, key);
	if(*str) {
		value=atoi(str);
		return true;
	}
	else return false;

}
void IniManager::putInt(const char* section, const char* key, int val) 
{
	std::string str = std::to_string(val);
	put(section, key, str.c_str());
}

float IniManager::getFloat(const char* section, const char* key) 
{ 
	return atof(get(section, key)); 
}
void IniManager::putFloat(const char* section, const char* key, float val) 
{
	XBuffer buf;
	buf <= val;
	put(section, key, buf);
}

void IniManager::getFloatArray(const char* section, const char* key, int size, float array[])
{
	const char* str = get(section, key); 
	XBuffer buf((void*)str, strlen(str) + 1);
	for(int i = 0; i < size; i++)
		buf >= array[i];
}
void IniManager::putFloatArray(const char* section, const char* key, int size, const float array[])
{
	XBuffer buf(256, 1);
	for(int i = 0; i < size; i++)
		buf <= array[i] < " ";
	put(section, key, buf);
}

static IniManager* settingsManager;

IniManager* getSettings() {
    if (!settingsManager) {
        std::string prefPath = GET_PREF_PATH();
        terminate_with_char(prefPath, PATH_SEP);
        prefPath = prefPath + "Settings.ini";
        if (!std::filesystem::exists(prefPath)) {
            //Create file if doesn't exist
            XStream f(prefPath,XS_OUT);
            f.close();
        }
        settingsManager = new IniManager(prefPath.c_str(), false, true);
    }
    return settingsManager;
}

std::string getStringSettings(const std::string& keyName, const std::string& defaultValue) {
    std::string res;
    bool found = false;

    IniManager* ini = getSettings();
    std::string key = terGameContentBase == GAME_CONTENT::CONTENT_NONE ? "Global" : getEnumName(terGameContentBase);
    const char* result = ini->get(key.c_str(), keyName.c_str());
    if (result) {
        found = true;
        res = result;
    }
    
    //In case of Windows try checking registry if this fails
#ifdef _WIN32
    if (!found) {
        HKEY hKey;
        char name[PERIMETER_CONTROL_NAME_SIZE];
        DWORD nameLen = PERIMETER_CONTROL_NAME_SIZE;
        LONG lRet;
    
        lRet = RegOpenKeyEx( HKEY_CURRENT_USER, mainCurrUserRegFolder, 0, KEY_QUERY_VALUE, &hKey );
    
        if ( lRet == ERROR_SUCCESS ) {
            lRet = RegQueryValueEx( hKey, keyName.c_str(), NULL, NULL, (LPBYTE) name, &nameLen );
    
            if ( (lRet == ERROR_SUCCESS) && nameLen && (nameLen <= PERIMETER_CONTROL_NAME_SIZE) ) {
                found = true;
                res = name;
            }
    
            RegCloseKey( hKey );
        }
    }
#endif
    return found ? res : defaultValue;
}

void putStringSettings(const std::string& keyName, const std::string& value) {
    IniManager* ini = getSettings();
    std::string key = terGameContentBase == GAME_CONTENT::CONTENT_NONE ? "Global" : getEnumName(terGameContentBase); 
    ini->put(key.c_str(), keyName.c_str(), value.c_str());
}

std::string formatTimeWithHour(int timeMilis) {
	std::string res;
	if (timeMilis >= 0) {
		int sec = timeMilis / 1000.0f;
		int min = sec / 60.0f;
		sec -= min * 60;
		int hour = min / 60.0f; 
		min -= hour * 60; 
		char str[11];
		sprintf(str, "%d", hour);
		res = (hour < 10) ? "0" : "";
		res += std::string(str) + ":";
		sprintf(str, "%d", min);
		res += (min < 10) ? "0" : "";
		res += std::string(str) + ":";
		sprintf(str, "%d", sec);
		res += (sec < 10) ? "0" : "";
		res += std::string(str);
	}
	return res;
}

std::string formatTimeWithoutHour(int timeMilis) {
	std::string res;
	if (timeMilis >= 0) {
		int sec = timeMilis / 1000.0f;
		int min = sec / 60.0f;
		sec -= min * 60;
		char str[11];
		sprintf(str, "%d", min);
		res = (min < 10) ? "0" : "";
		res += std::string(str) + ":";
		sprintf(str, "%d", sec);
		res += (sec < 10) ? "0" : "";
		res += std::string(str);
	}
	return res;
}
