console.log("Calculator JS loaded");

const display=document.getElementById("display")

function playSound() {
    const sound = document.getElementById("click-sound");
    sound.currentTime = 0;
    sound.play().catch(error => {
        console.log("Sound play error:", error);
    });
}

function appendToDisplay(input) {
    playSound();
    display.value += input;
}

function clearDisplay() {
    playSound();
    display.value="";
}

function calculate() {
    playSound();
    try {
        let result = eval(display.value);
        if (result == 69) {
            alert("bruh");
        }
        if (result == 822008) {
            alert("Hey! That's my birthday!");
        }
        if (result == new Date().getFullYear() - 2008) {
            alert("My current age this year!");
        }
        if (result == new Date().getFullYear()) {
            alert("Current year??");
        }
        document.getElementById("history").innerHTML += `<p>${display.value} = ${result}</p>`;
        display.value = result;
    }
    catch(error) {
        display.value = "";
    }}
