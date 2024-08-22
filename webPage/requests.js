//wndereço IP do módulo ESP8266
const ESP8266_IP = "";

//estado incial do led embutido; nesse caso, definido pelo sistema embarcado como HIGH(apagado)
let builtInLed_state = false;

//função para controlar o led embutido
const builtLedControl = () => {
    const xmlhttp = new XMLHttpRequest();
    const status = builtInLed_state ? "builtLed_off" : "builtLed_on";
    const setStatus = `http://${ESP8266_IP}/?function=${status}`;
    //inicializa uma requisição GET
    xmlhttp.open("GET", setStatus, true);

    xmlhttp.onreadystatechange = () => {
        if(xmlhttp.readyState === 4 && xmlhttp.status === 200){

            //alterna o estado do led em uma requisição bem sucedida
            builtInLed_state = !builtInLed_state;

            //atualiza o conteúdo do botão com base no estado do led
            const builtLedButton = document.getElementById('builtLedToggle');
            builtLedButton.textContent = builtInLed_state ? 'Desligar' : 'Ligar';

        }

    }

    //envia a requisição para o servidor
    xmlhttp.send();
}

//configura o botão de controle do led
const builtInLed = () => {
    var builtLedButton = document.getElementById('builtLedToggle');
    builtLedButton.addEventListener("click", builtLedControl)
}

//inicializa a configuração do botão ao carregar a janela
window.onload = () => {
    builtInLed();
}
