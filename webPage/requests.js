//Endereço IP do módulo ESP8266
const ESP8266_IP = "";

var led_controle = function(status) {
    var xmlhttp = new XMLHttpRequest();
    var set_status = "http://" + ESP8266_IP + "/?function=" + status;
    xmlhttp.open("GET", set_status);
    xmlhttp.send();
}

var builtInLed = function() {
    var ligar = document.querySelector(".on");
    ligar.onclick = function() {
        led_controle("builtLed_on");
    }

    var desligar = document.querySelector(".off");
    desligar.onclick = function() {
        led_controle("builtLed_off");
    }
}

window.onload = function() {
    builtInLed();
}