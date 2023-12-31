#ifndef SETTINGS_HTML
#define SETTINGS_HTML

const char settings_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>Connection settings</title>
<style>
body{align-items:center;background-color:#f8f9fc;display:flex;justify-content:center;height:100vh;margin:0}
.form{background-color:#fff;border-radius:20px;box-sizing:border-box;padding:20px;width:320px;box-shadow:0 .15rem 1.75rem 0 rgba(58,59,69,.15)}
[class="form"]:before{content:'';display:block;position:relative;height:2px;width:100%%;background:transparent;top:-20px;left:0}
[class="form"]:after{content:'';display:block;position:relative;height:2px;width:100%%;background:transparent;bottom:0px;left:0}
.wser:before{content:'';display:block;position:relative;height:2px;width:100%%;background:linear-gradient(to left,#fff,#dc2f55,#fff);top:-20px;left:0}
.wsok:before{content:'';display:block;position:relative;height:2px;width:100%%;background:linear-gradient(to left,#fff,#1cc88a,#fff);top:-20px;left:0}
.wsco:before{content:'';display:block;position:relative;height:2px;width:100%%;background:linear-gradient(to left,#fff,#08d,#fff);top:-20px;left:0}
.svok:after{content:'';display:block;position:relative;height:2px;width:100%%;background:linear-gradient(to left,#fff,#1cc88a,#fff);bottom:-20px;left:0}
.sver:after{content:'';display:block;position:relative;height:2px;width:100%%;background:linear-gradient(to left,#fff,#dc2f55,#fff);bottom:-20px;left:0}
.title{color:#5a5c69;font-family:sans-serif;font-size:21px;font-weight:600;margin-top:2px;text-align:center}
.subtitle{color:#65657b;font-family:sans-serif;font-size:16px;font-weight:600;margin-top:10px;text-align:center}.input-container{height:50px;position:relative;width:100%%;margin-top:30px}
.input{background-color:#eaecf4;border-radius:12px;border:2px solid transparent;box-sizing:border-box;color:#5a5c69;font-size:18px;height:100%%;outline:0;padding:4px 20px 0;width:100%%}
.cut{background-color:#fff;border-radius:10px;height:20px;left:20px;position:absolute;top:-20px;transform:translateY(0);transition:transform 200ms}
.placeholder{color:#858796;font-family:sans-serif;left:20px;line-height:14px;pointer-events:none;position:absolute;transform-origin:0 50%%;transition:transform 200ms,color 200ms;top:20px}
.submit{background-color:#08d;border-radius:12px;border:0;box-sizing:border-box;color:#eee;cursor:pointer;font-size:18px;height:50px;margin-top:38px;outline:0;text-align:center;width:100%%}
#togglePass{width:20%%;cursor:pointer;border-radius:0 12px 12px 0;float:right;padding:0;align-items:center;justify-content:center;display:flex}
.toggle{border:2px solid transparent;border-left:0!important}.input:focus~.placeholder,.input:not(:placeholder-shown)~.placeholder{transform:translateY(-30px) translateX(10px) scale(.75)}
.input:focus~.cut,.input:not(:placeholder-shown)~.cut{transform:translateY(8px)}#togglePass.is-valid>svg,#togglePass.is-invalid>svg{transform:translateX(0)}.incorrect{color:#dc2f55}
.input:not(:placeholder-shown)~.placeholder{color:#65657b}#togglePass.is-valid,#togglePass.is-invalid{border-left:0}#PASS.is-valid,#PASS.is-invalid{border-right:0}.correct{color:#1cc88a}
.input:focus~.placeholder{color:#65657b}.is-invalid{border:2px solid #dc2f55}.submit:active{background-color:#06b}.is-valid{border:2px solid #1cc88a}svg{color:#858796}
</style>
</head>
<body>
<div id="FORM" class="form wsco">
<div class="title">Connection settings</div>
<div id="WIFI-CONN" class="subtitle %STA_WIFI_CONN_CLASS%">%STA_WIFI_CONN%</div>
<div id="API-CONN" class="subtitle %STA_API_CONN_CLASS%">%STA_API_CONN%</div>
<div class="input-container">
<input id="SSID" class="input" type="text" placeholder=" " value="%STA_SSID%">
<div class="cut" style="width:76px"></div>
<label for="SSID" class="placeholder">WiFi SSID</label>
</div>
<div class="input-container">
<input id="PASS" class="input" type="password" style="width:80%%;border-radius:12px 0 0 12px" placeholder=" " value="%STA_PASS%">
<div class="cut" style="width:100px"></div>
<label for="PASS" class="placeholder">WiFi password</label>
<button type="text" id="togglePass" class="input toggle">
<svg xmlns="http://www.w3.org/2000/svg" width="40" height="40" fill="currentColor" class="bi bi-key" viewBox="0 0 16 16" id="IconChangeColor">
<path d="M0 8a4 4 0 0 1 7.465-2H14a.5.5 0 0 1 .354.146l1.5 1.5a.5.5 0 0 1 0 .708l-1.5 1.5a.5.5 0 0 1-.708 0L13 9.207l-.646.647a.5.5 0 0 1-.708 0L11 9.207l-.646.647a.5.5 0 0 1-.708 0L9 9.207l-.646.647A.5.5 0 0 1 8 10h-.535A4 4 0 0 1 0 8zm4-3a3 3 0 1 0 2.712 4.285A.5.5 0 0 1 7.163 9h.63l.853-.854a.5.5 0 0 1 .708 0l.646.647.646-.647a.5.5 0 0 1 .708 0l.646.647.646-.647a.5.5 0 0 1 .708 0l.646.647.793-.793-1-1h-6.63a.5.5 0 0 1-.451-.285A3 3 0 0 0 4 5z" id="mainIconPathAttribute"></path>
<path d="M4 8a1 1 0 1 1-2 0 1 1 0 0 1 2 0z" id="mainIconPathAttribute"></path>
</svg>
</button>
</div>
<div class="input-container">
<input id="HOST" class="input" type="text" maxlength="80" placeholder=" " value="%STA_HOST%">
<div class="cut" style="width:105px"></div>
<label for="HOST" class="placeholder">API server host</label>
</div>
<div class="input-container">
<input id="PORT" class="input" type="text" onkeypress="return portInput(event)" maxlength="5" placeholder=" " value="%STA_PORT%">
<div class="cut" style="width:105px"></div>
<label for="PORT" class="placeholder">API server port</label>
</div>
<button type="text" class="submit" onclick="submit()">Submit</button>
</div>
<script>
const togglePass = document.querySelector('#togglePass');
const ssid = document.querySelector('#SSID');
const pass = document.querySelector('#PASS');
const host = document.querySelector('#HOST');
const port = document.querySelector('#PORT');
const form = document.querySelector('#FORM');
const wifi = document.querySelector('#WIFI-CONN');
const api = document.querySelector('#API-CONN');

const ws_connection_class = "wsco";
const ws_connected_class = "wsok";
const ws_error_class = "wser";
const sv_ok_class = "svok";
const sv_error_class = "sver";

var gateway = `ws://${window.location.hostname}/device`;
var socket;

togglePass.addEventListener('click', () => {
var type = pass.getAttribute('type') == 'text' ? 'password' : 'text';
pass.setAttribute('type', type);
});

function removeValidationStyle() {
document.querySelectorAll('.is-valid').forEach(element => { element.classList.remove('is-valid'); });
document.querySelectorAll('.is-invalid').forEach(element => { element.classList.remove('is-invalid'); });
}
function removeServerConfirmationStyle() {
form.classList.remove(sv_error_class);
form.classList.remove(sv_ok_class);
}
function setServerConfirmationStyle(sv_class) {
removeServerConfirmationStyle();
form.classList.add(sv_class);
}
function setWebSocketStyle(ws_class) {
form.classList.remove(ws_connection_class);
form.classList.remove(ws_error_class);
form.classList.remove(ws_connected_class);
form.classList.add(ws_class);
}
function setServerCtrlInterval() {
if (!form.classList.contains(sv_ok_class)) {
setServerConfirmationStyle(sv_error_class);
setTimeout(removeServerConfirmationStyle, 5000);
}
}
function isInvalid(obj) {
obj.classList.remove("is-valid");
obj.classList.add("is-invalid");
}
function portInput(event) {
var aCode = event.which ? event.which : event.keyCode;
if (aCode >= 48 && aCode <= 57) return true;
return false;
}
function hostInput(event) {
var aCode = event.which ? event.which : event.keyCode;
if (aCode == 46 || (aCode >= 48 && aCode <= 57)) return true;
return false;
}
function submit() {
let format = /^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$/;
var err = false;
if (!form.classList.contains(ws_connected_class)) {
alert("Server connection error!");
return;
}

//if (!host.value.match(format) || host.value.length < 7 || host.value.length > 15) { 
//isInvalid(host);
//err = true;   
//}  

if (!Number.parseInt(port.value) || port.value.length < 1 || port.value.length > 5) { 
isInvalid(port);
err = true; 
}

if (pass.value.length < 8) { 
isInvalid(pass);
err = true; 
}

if (ssid.value.length < 1) { 
isInvalid(ssid);
err = true; 
}

if (err) {
alert("You has an invalid values in form, checkout!");
return;
}

const msg = {
type: "save",
SSID: ssid.value,
PASS: pass.value,
HOST: host.value,
PORT: port.value,
};
socket.send(JSON.stringify(msg));
setTimeout(setServerCtrlInterval, 500);
}  
function onOpen(event) { 
setWebSocketStyle(ws_connected_class);
}
function onClose(event) { 
setTimeout(onLoad, 2000); 
setWebSocketStyle(ws_error_class);
}
function onMessage(event) {
var json = JSON.parse(event.data);
console.log(json);
var type = json.type;
if (type == "save") {
if (json.info == "ok") {
setServerConfirmationStyle(sv_ok_class);
ssid.value = json.SSID;
pass.value = json.PASS;
host.value = json.HOST;
port.value = json.PORT;
}
else {
setServerConfirmationStyle(sv_error_class);
}
setTimeout(removeServerConfirmationStyle, 5000);
}
else if (type == "wifi_connection_success") {
wifi.classList.remove('incorrect');
wifi.classList.add('correct');
wifi.innerHTML = "Connected to WiFi";
}
else if (type == "wifi_connection_failed") {
wifi.classList.remove('correct');
wifi.classList.add('incorrect');
wifi.innerHTML = "Not connected to WiFi";
}
else if (type == "api_connection_success") {
api.classList.remove('incorrect');
api.classList.add('correct');
api.innerHTML = "Connected to API";
}
else if (type == "api_connection_failed") {
api.classList.remove('correct');
api.classList.add('incorrect');
api.innerHTML = "Not connected to API";
}
}
function onLoad(event) {
socket = new WebSocket(gateway);
socket.onopen    = onOpen;
socket.onclose   = onClose;
socket.onmessage = onMessage; 
}

window.addEventListener('load', onLoad);

</script>
</body>
</html>
)rawliteral";

#endif
