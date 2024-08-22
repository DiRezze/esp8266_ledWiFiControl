//Endereço IP do módulo ESP8266
const ESP8266_IP = "";

//Estado incial do led embutido; nesse caso, definido pelo sistema embarcado como HIGH(apagado)
let builtInLed_state = false;

const builtLedControl = () => {
    const xmlhttp = new XMLHttpRequest();
    const status = builtInLed_state ? "builtLed_off" : "builtLed_on";
    const setStatus = `http://${ESP8266_IP}/?function=${status}`;
    xmlhttp.open("GET", setStatus, true);

    xmlhttp.onreadystatechange = () => {
        if(xmlhttp.readyState === 4 && xmlhttp.status === 200){
            builtInLed_state = !builtInLed_state;

            const builtLedButton = document.getElementById('builtLedToggle');
            builtLedButton.textContent = builtInLed_state ? 'Desligar' : 'Ligar';
        }
    }

    xmlhttp.send();
}

const builtInLed = () => {
    var builtLedButton = document.getElementById('builtLedToggle');
    builtLedButton.addEventListener("click", builtLedControl)
}

window.onload = () => {
    builtInLed();
}
