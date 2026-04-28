
#include <BleCombo.h>
#include <DNSServer.h>
#include <WebServer.h>
#include <WiFi.h>

#ifndef KEY_PRINT_SCREEN
#define KEY_PRINT_SCREEN 0xCE
#endif
#ifndef KEY_SCROLL_LOCK
#define KEY_SCROLL_LOCK 0xCF
#endif
#ifndef KEY_PAUSE
#define KEY_PAUSE 0xD0
#endif
#ifndef KEY_NUM_LOCK
#define KEY_NUM_LOCK 0xDB
#endif
#ifndef KEY_MENU
#define KEY_MENU 0xED
#endif

#include "index_html.h"

const char *ssid = "ShadowGlint";
const char *password = "12345678";

WebServer server(80);
DNSServer dnsServer;

String pendingScript = "";
bool hasScript = false;
int defaultDelay = 0;
String lastDuckyLine = "";

int mouseSensitivity = 5; // 1-10

void setup() {
  Serial.begin(115200);
  delay(1000);

  // WiFi Access Point
  Serial.println("[*] Starting WiFi AP...");
  WiFi.mode(WIFI_AP);
  WiFi.setSleep(false);
  IPAddress IP(192, 168, 4, 1);
  WiFi.softAPConfig(IP, IP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(ssid, password);
  Serial.print("[+] AP IP: ");
  Serial.println(WiFi.softAPIP());

  dnsServer.start(53, "*", IP);

  Serial.println("[*] Starting BLE HID...");
  Keyboard.begin();
  Mouse.begin();
  delay(1000);

  server.on("/", []() { server.send_P(200, "text/html", index_html); });

  server.on("/cmd", handleCmd);
  server.on("/mouse", handleMouse);
  server.on("/mouseaction", handleMouseAction);
  server.on("/script", HTTP_POST, handleScript);
  server.on("/status", handleStatus);

  server.onNotFound([]() {
    server.sendHeader("Location", "http://192.168.4.1/", true);
    server.send(302, "text/plain", "");
  });

  server.begin();
  Serial.println("[+] HTTP Server started!");
  Serial.println("[+] System ready.");
}

//  CMD HANDLER
void handleCmd() {
  if (!server.hasArg("type") || !server.hasArg("val")) {
    server.send(400, "text/plain", "Bad");
    return;
  }
  String type = server.arg("type");
  String val = server.arg("val");

  if (type == "key") {
    Keyboard.write(val.toInt());
  } else if (type == "press") {
    Keyboard.press(val.toInt());
  } else if (type == "release") {
    Keyboard.release(val.toInt());
  } else if (type == "releaseall") {
    Keyboard.releaseAll();
  } else if (type == "text") {
    Keyboard.print(val);
  } else if (type == "scroll") {
    int a = 3;
    if (val == "up")
      Mouse.move(0, 0, a);
    else if (val == "down")
      Mouse.move(0, 0, -a);
    else if (val == "left")
      Mouse.move(0, 0, 0, -a);
    else if (val == "right")
      Mouse.move(0, 0, 0, a);
  } else if (type == "mouse") {
    if (val == "click_left")
      Mouse.click(MOUSE_LEFT);
    else if (val == "click_right")
      Mouse.click(MOUSE_RIGHT);
    else if (val == "click_middle")
      Mouse.click(MOUSE_MIDDLE);
    else if (val == "dbl_click") {
      Mouse.click(MOUSE_LEFT);
      delay(60);
      Mouse.click(MOUSE_LEFT);
    }
  } else if (type == "macro") {
    executeMacro(val);
  } else if (type == "sensitivity") {
    mouseSensitivity = constrain(val.toInt(), 1, 10);
  }

  server.send(200, "text/plain", "OK");
}

//  MOUSE MOVE
void handleMouse() {
  if (server.hasArg("dx") && server.hasArg("dy")) {
    float mult = mouseSensitivity / 5.0;
    int dx = constrain((int)(server.arg("dx").toInt() * mult), -127, 127);
    int dy = constrain((int)(server.arg("dy").toInt() * mult), -127, 127);
    Mouse.move(dx, dy);
    server.send(200, "text/plain", "OK");
  } else {
    server.send(400, "text/plain", "Bad");
  }
}

//  MOUSE PRESS/RELEASE (DRAG)
void handleMouseAction() {
  if (server.hasArg("action")) {
    String a = server.arg("action");
    if (a == "press_left")
      Mouse.press(MOUSE_LEFT);
    else if (a == "release_left")
      Mouse.release(MOUSE_LEFT);
    else if (a == "press_right")
      Mouse.press(MOUSE_RIGHT);
    else if (a == "release_right")
      Mouse.release(MOUSE_RIGHT);
    server.send(200, "text/plain", "OK");
  } else {
    server.send(400, "text/plain", "Bad");
  }
}

void handleScript() {
  if (server.hasArg("plain")) {
    pendingScript = server.arg("plain");
    hasScript = true;
    server.send(200, "text/plain", "Executing...");
  } else {
    server.send(400, "text/plain", "No script");
  }
}

// STATUS  69
void handleStatus() {
  String j = "{\"ble\":";
  j += Keyboard.isConnected() ? "true" : "false";
  j += ",\"ip\":\"" + WiFi.softAPIP().toString() + "\"";
  j += ",\"clients\":" + String(WiFi.softAPgetStationNum());
  j += ",\"sens\":" + String(mouseSensitivity);
  j += ",\"ssid\":\"" + String(ssid) + "\"}";
  server.send(200, "application/json", j);
}

void executeMacro(String val) {
  // PAk System
  if (val == "lock") {
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('l');
    delay(100);
    Keyboard.releaseAll();
  } else if (val == "desktop") {
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('d');
    delay(100);
    Keyboard.releaseAll();
  } else if (val == "screenshot") {
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press('s');
    delay(100);
    Keyboard.releaseAll();
  } else if (val == "task_mgr") {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press(KEY_ESC);
    delay(100);
    Keyboard.releaseAll();
  } else if (val == "run") {
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('r');
    delay(100);
    Keyboard.releaseAll();
  } else if (val == "settings") {
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('i');
    delay(100);
    Keyboard.releaseAll();
  } else if (val == "explorer") {
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('e');
    delay(100);
    Keyboard.releaseAll();
  } else if (val == "sleep") {
    openRunAndType("rundll32.exe powrprof.dll,SetSuspendState 0,1,0");
  } else if (val == "shutdown") {
    openRunAndType("shutdown /s /t 0");
  } else if (val == "restart") {
    openRunAndType("shutdown /r /t 0");
  } else if (val == "logoff") {
    openRunAndType("logoff");
  } else if (val == "chrome") {
    openRunAndType("chrome");
  } else if (val == "youtube") {
    openRunAndType("chrome youtube.com");
  } else if (val == "notepad") {
    openRunAndType("notepad");
  } else if (val == "cmd") {
    openRunAndType("cmd");
  } else if (val == "powershell") {
    openRunAndType("powershell");
  } else if (val == "calc") {
    openRunAndType("calc");
  } else if (val == "devmgr") {
    openRunAndType("devmgmt.msc");
  } else if (val == "copy") {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('c');
    delay(100);
    Keyboard.releaseAll();
  } else if (val == "paste") {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('v');
    delay(100);
    Keyboard.releaseAll();
  } else if (val == "cut") {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('x');
    delay(100);
    Keyboard.releaseAll();
  } else if (val == "undo") {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('z');
    delay(100);
    Keyboard.releaseAll();
  } else if (val == "redo") {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('y');
    delay(100);
    Keyboard.releaseAll();
  } else if (val == "select_all") {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('a');
    delay(100);
    Keyboard.releaseAll();
  } else if (val == "find") {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('f');
    delay(100);
    Keyboard.releaseAll();
  } else if (val == "save") {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('s');
    delay(100);
    Keyboard.releaseAll();
  }
  // Window Management
  else if (val == "close_window") {
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_F4);
    delay(100);
    Keyboard.releaseAll();
  } else if (val == "minimize") {
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press(KEY_DOWN_ARROW);
    delay(100);
    Keyboard.releaseAll();
  } else if (val == "maximize") {
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press(KEY_UP_ARROW);
    delay(100);
    Keyboard.releaseAll();
  } else if (val == "alt_tab") {
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_TAB);
    delay(200);
    Keyboard.releaseAll();
  } else if (val == "snap_left") {
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press(KEY_LEFT_ARROW);
    delay(100);
    Keyboard.releaseAll();
  } else if (val == "snap_right") {
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press(KEY_RIGHT_ARROW);
    delay(100);
    Keyboard.releaseAll();
  }
  // Media
  else if (val == "vol_up") {
    Keyboard.write(KEY_MEDIA_VOLUME_UP);
  } else if (val == "vol_down") {
    Keyboard.write(KEY_MEDIA_VOLUME_DOWN);
  } else if (val == "mute") {
    Keyboard.write(KEY_MEDIA_MUTE);
  } else if (val == "play_pause") {
    Keyboard.write(KEY_MEDIA_PLAY_PAUSE);
  } else if (val == "next_track") {
    Keyboard.write(KEY_MEDIA_NEXT_TRACK);
  } else if (val == "prev_track") {
    Keyboard.write(KEY_MEDIA_PREVIOUS_TRACK);
  }
  // Browser
  else if (val == "new_tab") {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('t');
    delay(100);
    Keyboard.releaseAll();
  } else if (val == "close_tab") {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('w');
    delay(100);
    Keyboard.releaseAll();
  } else if (val == "reopen_tab") {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press('t');
    delay(100);
    Keyboard.releaseAll();
  } else if (val == "refresh") {
    Keyboard.write(KEY_F5);
  } else if (val == "address_bar") {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('l');
    delay(100);
    Keyboard.releaseAll();
  } else if (val == "incognito") {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press('n');
    delay(100);
    Keyboard.releaseAll();
  } else if (val == "fullscreen") {
    Keyboard.write(KEY_F11);
  } else if (val == "zoom_in") {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('=');
    delay(100);
    Keyboard.releaseAll();
  } else if (val == "zoom_out") {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('-');
    delay(100);
    Keyboard.releaseAll();
  }
  //  Utility
  else if (val == "wifi_pass") {
    // Open PowerShell and show WiFi profiles
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('r');
    delay(100);
    Keyboard.releaseAll();
    delay(600);
    Keyboard.print("powershell");
    delay(200);
    Keyboard.write(KEY_RETURN);
    delay(1200);
    Keyboard.print("netsh wlan show profiles | Select-String '\\:(.+)$' | "
                   "%{$n=$_.Matches[0].Groups[1].Value.Trim(); $p=(netsh wlan "
                   "show profile name=\"$n\" key=clear | Select-String 'Key "
                   "Content\\W+\\:(.+)$'); if($p){\"$n = "
                   "$($p.Matches[0].Groups[1].Value.Trim())\"}}");
    delay(100);
    Keyboard.write(KEY_RETURN);
  } else if (val == "ipconfig") {
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('r');
    delay(100);
    Keyboard.releaseAll();
    delay(600);
    Keyboard.print("cmd /k ipconfig /all");
    delay(200);
    Keyboard.write(KEY_RETURN);
  } else if (val == "sysinfo") {
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('r');
    delay(100);
    Keyboard.releaseAll();
    delay(600);
    Keyboard.print("cmd /k systeminfo");
    delay(200);
    Keyboard.write(KEY_RETURN);
  } else if (val == "printscreen") {
    Keyboard.write(KEY_PRINT_SCREEN);
  }
}

void openRunAndType(String cmd) {
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  delay(100);
  Keyboard.releaseAll();
  delay(600);
  Keyboard.print(cmd);
  delay(200);
  Keyboard.write(KEY_RETURN);
}

void executeDuckyScript() {
  hasScript = false;
  String script = pendingScript;
  defaultDelay = 0;
  lastDuckyLine = "";

  int lineStart = 0;
  int nl = script.indexOf('\n');

  while (nl != -1 || lineStart < (int)script.length()) {
    String line;
    if (nl == -1) {
      line = script.substring(lineStart);
      lineStart = script.length();
    } else {
      line = script.substring(lineStart, nl);
      lineStart = nl + 1;
      nl = script.indexOf('\n', lineStart);
    }
    line.trim();
    if (line.length() == 0)
      continue;

    executeDuckyLine(line);

    if (defaultDelay > 0)
      delay(defaultDelay);
    delay(50);
  }
}

void executeDuckyLine(String line) {
  Serial.println("DUCK> " + line);

  if (line.startsWith("REM")) {
  } else if (line.startsWith("DEFAULTDELAY") ||
             line.startsWith("DEFAULT_DELAY")) {
    defaultDelay = line.substring(line.indexOf(' ') + 1).toInt();
  } else if (line.startsWith("DELAY")) {
    delay(line.substring(6).toInt());
  } else if (line.startsWith("STRING ")) {
    String text = line.substring(7);
    for (int i = 0; i < text.length(); i++) {
      Keyboard.write(text.charAt(i));
      delay(20);
    }
  } else if (line.startsWith("REPEAT")) {
    int n = line.substring(7).toInt();
    if (n < 1)
      n = 1;
    for (int i = 0; i < n; i++) {
      executeDuckyLine(lastDuckyLine);
      delay(50);
    }
    return;
  } else if (line == "ENTER" || line == "RETURN") {
    Keyboard.write(KEY_RETURN);
  } else if (line == "SPACE") {
    Keyboard.write(' ');
  } else if (line == "TAB") {
    Keyboard.write(KEY_TAB);
  } else if (line == "ESC" || line == "ESCAPE") {
    Keyboard.write(KEY_ESC);
  } else if (line == "BACKSPACE") {
    Keyboard.write(KEY_BACKSPACE);
  } else if (line == "DELETE" || line == "DEL") {
    Keyboard.write(KEY_DELETE);
  } else if (line == "INSERT") {
    Keyboard.write(KEY_INSERT);
  } else if (line == "HOME") {
    Keyboard.write(KEY_HOME);
  } else if (line == "END") {
    Keyboard.write(KEY_END);
  } else if (line == "PAGEUP") {
    Keyboard.write(KEY_PAGE_UP);
  } else if (line == "PAGEDOWN") {
    Keyboard.write(KEY_PAGE_DOWN);
  } else if (line == "UPARROW" || line == "UP") {
    Keyboard.write(KEY_UP_ARROW);
  } else if (line == "DOWNARROW" || line == "DOWN") {
    Keyboard.write(KEY_DOWN_ARROW);
  } else if (line == "LEFTARROW" || line == "LEFT") {
    Keyboard.write(KEY_LEFT_ARROW);
  } else if (line == "RIGHTARROW" || line == "RIGHT") {
    Keyboard.write(KEY_RIGHT_ARROW);
  } else if (line == "CAPSLOCK") {
    Keyboard.write(KEY_CAPS_LOCK);
  } else if (line == "NUMLOCK") {
    Keyboard.write(KEY_NUM_LOCK);
  } else if (line == "SCROLLLOCK") {
    Keyboard.write(KEY_SCROLL_LOCK);
  } else if (line == "PRINTSCREEN") {
    Keyboard.write(KEY_PRINT_SCREEN);
  } else if (line == "PAUSE" || line == "BREAK") {
    Keyboard.write(KEY_PAUSE);
  } else if (line == "MENU" || line == "APP") {
    Keyboard.write(KEY_MENU);
  }

  else if (line == "F1") {
    Keyboard.write(KEY_F1);
  } else if (line == "F2") {
    Keyboard.write(KEY_F2);
  } else if (line == "F3") {
    Keyboard.write(KEY_F3);
  } else if (line == "F4") {
    Keyboard.write(KEY_F4);
  } else if (line == "F5") {
    Keyboard.write(KEY_F5);
  } else if (line == "F6") {
    Keyboard.write(KEY_F6);
  } else if (line == "F7") {
    Keyboard.write(KEY_F7);
  } else if (line == "F8") {
    Keyboard.write(KEY_F8);
  } else if (line == "F9") {
    Keyboard.write(KEY_F9);
  } else if (line == "F10") {
    Keyboard.write(KEY_F10);
  } else if (line == "F11") {
    Keyboard.write(KEY_F11);
  } else if (line == "F12") {
    Keyboard.write(KEY_F12);
  }

  else if (line.startsWith("GUI") || line.startsWith("WIN") ||
           line.startsWith("WINDOWS")) {
    pressModCombo(KEY_LEFT_GUI, line);
  } else if (line.startsWith("CTRL") || line.startsWith("CONTROL")) {
    pressModCombo(KEY_LEFT_CTRL, line);
  } else if (line.startsWith("ALT")) {
    pressModCombo(KEY_LEFT_ALT, line);
  } else if (line.startsWith("SHIFT")) {
    pressModCombo(KEY_LEFT_SHIFT, line);
  }

  lastDuckyLine = line;
}

void pressModCombo(uint8_t mod, String line) {
  Keyboard.press(mod);

  int sp = line.indexOf(' ');
  if (sp != -1) {
    String rest = line.substring(sp + 1);
    rest.trim();
    if (rest.startsWith("SHIFT")) {
      Keyboard.press(KEY_LEFT_SHIFT);
      rest = rest.substring(5);
      rest.trim();
    }
    if (rest.startsWith("CTRL") || rest.startsWith("CONTROL")) {
      Keyboard.press(KEY_LEFT_CTRL);
      int s2 = rest.indexOf(' ');
      rest = (s2 != -1) ? rest.substring(s2 + 1) : "";
      rest.trim();
    }
    if (rest.startsWith("ALT")) {
      Keyboard.press(KEY_LEFT_ALT);
      int s2 = rest.indexOf(' ');
      rest = (s2 != -1) ? rest.substring(s2 + 1) : "";
      rest.trim();
    }
    if (rest.startsWith("GUI") || rest.startsWith("WIN")) {
      Keyboard.press(KEY_LEFT_GUI);
      int s2 = rest.indexOf(' ');
      rest = (s2 != -1) ? rest.substring(s2 + 1) : "";
      rest.trim();
    }

    if (rest.length() > 0) {
      if (rest == "ENTER" || rest == "RETURN")
        Keyboard.press(KEY_RETURN);
      else if (rest == "ESC" || rest == "ESCAPE")
        Keyboard.press(KEY_ESC);
      else if (rest == "BACKSPACE")
        Keyboard.press(KEY_BACKSPACE);
      else if (rest == "DELETE" || rest == "DEL")
        Keyboard.press(KEY_DELETE);
      else if (rest == "TAB")
        Keyboard.press(KEY_TAB);
      else if (rest == "SPACE")
        Keyboard.press(' ');
      else if (rest == "UP")
        Keyboard.press(KEY_UP_ARROW);
      else if (rest == "DOWN")
        Keyboard.press(KEY_DOWN_ARROW);
      else if (rest == "LEFT")
        Keyboard.press(KEY_LEFT_ARROW);
      else if (rest == "RIGHT")
        Keyboard.press(KEY_RIGHT_ARROW);
      else if (rest == "F1")
        Keyboard.press(KEY_F1);
      else if (rest == "F2")
        Keyboard.press(KEY_F2);
      else if (rest == "F3")
        Keyboard.press(KEY_F3);
      else if (rest == "F4")
        Keyboard.press(KEY_F4);
      else if (rest == "F5")
        Keyboard.press(KEY_F5);
      else if (rest == "F6")
        Keyboard.press(KEY_F6);
      else if (rest == "F7")
        Keyboard.press(KEY_F7);
      else if (rest == "F8")
        Keyboard.press(KEY_F8);
      else if (rest == "F9")
        Keyboard.press(KEY_F9);
      else if (rest == "F10")
        Keyboard.press(KEY_F10);
      else if (rest == "F11")
        Keyboard.press(KEY_F11);
      else if (rest == "F12")
        Keyboard.press(KEY_F12);
      else if (rest == "PRINTSCREEN")
        Keyboard.press(KEY_PRINT_SCREEN);
      else if (rest == "HOME")
        Keyboard.press(KEY_HOME);
      else if (rest == "END")
        Keyboard.press(KEY_END);
      else if (rest == "PAGEUP")
        Keyboard.press(KEY_PAGE_UP);
      else if (rest == "PAGEDOWN")
        Keyboard.press(KEY_PAGE_DOWN);
      else if (rest == "INSERT")
        Keyboard.press(KEY_INSERT);
      else if (rest.length() == 1)
        Keyboard.press(rest.charAt(0));
    }
  }
  delay(50);
  Keyboard.releaseAll();
}

// MAIN LOOP
void loop() {
  dnsServer.processNextRequest();
  server.handleClient();

  if (hasScript) {
    executeDuckyScript();
  }

  delay(5);
}
