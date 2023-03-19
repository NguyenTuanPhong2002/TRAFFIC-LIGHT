function greenLight1(){
    var green1=document.getElementById("green1");
    var red1=document.getElementById("red1");
    var yellow1=document.getElementById("yellow1");
    green1.style.opacity=1;
    red1.style.opacity=.3;
    yellow1.style.opacity=.3;    
}

function yellowLight1() {
    var green1=document.getElementById("green1");
    var red1=document.getElementById("red1");
    var yellow1=document.getElementById("yellow1");
    green1.style.opacity=.3;
    red1.style.opacity=.3;
    yellow1.style.opacity=1;    
}

function redLight1 (){
    var green1=document.getElementById("green1");
    var red1=document.getElementById("red1");
    var yellow1=document.getElementById("yellow1");
    green1.style.opacity=.3;
    red1.style.opacity=1;
    yellow1.style.opacity=.3;    
}

function greenLight2(){
    var green2=document.getElementById("green2");
    var red2=document.getElementById("red2");
    var yellow2=document.getElementById("yellow2");
    green2.style.opacity=1;
    red2.style.opacity=.3;
    yellow2.style.opacity=.3;    
}

function yellowLight2() {
    var green2=document.getElementById("green2");
    var red2=document.getElementById("red2");
    var yellow2=document.getElementById("yellow2");
    green2.style.opacity=.3;
    red2.style.opacity=.3;
    yellow2.style.opacity=1;    
}

function redLight2 (){
    var green2=document.getElementById("green2");
    var red2=document.getElementById("red2");
    var yellow2=document.getElementById("yellow2");
    green2.style.opacity=.3;
    yellow2.style.opacity=.3;    
    red2.style.opacity=1;
}

function greenLight3(){
    var green3=document.getElementById("green3");
    var red3=document.getElementById("red3");
    var yellow3=document.getElementById("yellow3");
    green3.style.opacity=1;
    red3.style.opacity=.3;
    yellow3.style.opacity=.3;    
}

function yellowLight3() {
    var green3=document.getElementById("green3");
    var red3=document.getElementById("red3");
    var yellow3=document.getElementById("yellow3");
    green3.style.opacity=.3;
    red3.style.opacity=.3;
    yellow3.style.opacity=1;    
}

function redLight3 (){
    var green3=document.getElementById("green3");
    var red3=document.getElementById("red3");
    var yellow3=document.getElementById("yellow3");
    green3.style.opacity=.3;
    yellow3.style.opacity=.3;    
    red3.style.opacity=1;
}

function greenLight4(){
    var green4=document.getElementById("green4");
    var red4=document.getElementById("red4");
    var yellow4=document.getElementById("yellow4");
    green4.style.opacity=1;
    red4.style.opacity=.3;
    yellow4.style.opacity=.3;    
}

function yellowLight4() {
    var green4=document.getElementById("green4");
    var red4=document.getElementById("red4");
    var yellow4=document.getElementById("yellow4");
    green4.style.opacity=.3;
    red4.style.opacity=.3;
    yellow4.style.opacity=1;    
}

function redLight4 (){
    var green4=document.getElementById("green4");
    var red4=document.getElementById("red4");
    var yellow4=document.getElementById("yellow4");
    green4.style.opacity=.3;
    yellow4.style.opacity=.3;    
    red4.style.opacity=1;
}

function offAll (){
    if(isBlink==1){
        offBlink();
    }
    clearInterval(countdownTimer);
    seconds = 0;
    updateTime();
    clearInterval(countdownTimer2);
    seconds2 = 0;
    updateTime2();
    var green1=document.getElementById("green1");
    var red1=document.getElementById("red1");
    var yellow1=document.getElementById("yellow1");
    green1.style.opacity=.3;
    red1.style.opacity=.3;
    yellow1.style.opacity=.3;

    var green2=document.getElementById("green2");
    var red2=document.getElementById("red2");
    var yellow2=document.getElementById("yellow2");
    green2.style.opacity=.3;
    red2.style.opacity=.3;
    yellow2.style.opacity=.3; 

    var green3=document.getElementById("green3");
    var red3=document.getElementById("red3");
    var yellow3=document.getElementById("yellow3");
    green3.style.opacity=.3;
    red3.style.opacity=.3;
    yellow3.style.opacity=.3; 

    var green4=document.getElementById("green4");
    var red4=document.getElementById("red4");
    var yellow4=document.getElementById("yellow4");
    green4.style.opacity=.3;
    red4.style.opacity=.3;
    yellow4.style.opacity=.3;     
}

var countdownTimer;
var seconds = 10;
var countDownStatus = 1;
var pauseTime = 0;

function startTimer1() {
    clearInterval(countdownTimer);
    countDownStatus = 1;
    seconds = 10;
    greenLight1();
    greenLight2();
    countdownTimer = setInterval(function () {
    if (countDownStatus == 1) {
        seconds--;
        if (seconds < 0) {
            countDownStatus = 2;
            seconds = 3;
            yellowLight1();
            yellowLight2();
        }
    } else if (countDownStatus == 2) {
        seconds--;
        if (seconds < 0) {
            countDownStatus = 3;
            seconds = 14;
            redLight1();
            redLight2();
        }
    } else {
        seconds--;
        if (seconds < 0) {
            countDownStatus = 1;
            seconds = 10;
            greenLight1();
            greenLight2();
        }
    }
    updateTime();
    }, 1000); 
}

var countdownTimer2;
var seconds2 = 10;
var countDownStatus2 = 1;
var pauseTime2 = 0;

function startTimer2() {
    clearInterval(countdownTimer2);
    countDownStatus2 = 1;
    seconds2 = 14;
    redLight3();
    redLight4();
    countdownTimer2 = setInterval(function () {
    if (countDownStatus2 == 1) {
        seconds2--;
        if (seconds2 < 0) {
            countDownStatus2 = 2;
            seconds2 = 10;
            greenLight3();
            greenLight4();
        }
    } else if (countDownStatus2 == 2) {
        seconds2--;
        if (seconds2 < 0) {
            countDownStatus2 = 3;
            seconds2 = 3;
            yellowLight3();
            yellowLight4();
        }
    } else {
        seconds2--;
        if (seconds2 < 0) {
            countDownStatus2 = 1;
            seconds2 = 14;
            redLight3();
            redLight4();
        }
    }
    updateTime2();
    }, 1000); 
}

function stop(element) {
    clearInterval(countdownTimer);
    seconds = 0;
    countDownStatus = 1;
    pauseTime = 0;

    clearInterval(countdownTimer2);
    seconds2 = 0;
    countDownStatus2 = 1;
    pauseTime2 = 0;

    offAll();
    updateTime();
    updateTime2();

    resetPosition(element);
}

function red(element) {
    offAll();
    redLight1();
    redLight2();
    redLight3();
    redLight4();
    resetPosition(element);
}

var isBlink = 0;

function yellowBlink(element) {
    offAll();
    isBlink = 1;
    var yellow1=document.getElementById("yellow1");
    var yellow2=document.getElementById("yellow2");
    var yellow3=document.getElementById("yellow3");
    var yellow4=document.getElementById("yellow4");
    blink = setInterval(function(){
        yellow1.classList.toggle('blink');
        yellow2.classList.toggle('blink');
        yellow3.classList.toggle('blink');
        yellow4.classList.toggle('blink');
    },500)

    resetPosition(element);
}   

function offBlink() {
    clearInterval(blink);
    isBlink = 0;
    var yellow1=document.getElementById("yellow1");
    var yellow2=document.getElementById("yellow2");
    var yellow3=document.getElementById("yellow3");
    var yellow4=document.getElementById("yellow4");
    yellow1.classList.remove('blink');
    yellow2.classList.remove('blink');
    yellow3.classList.remove('blink');
    yellow4.classList.remove('blink');
}

function updateTime() {
    document.getElementById("timer1").innerHTML = seconds;
    document.getElementById("timer3").innerHTML = seconds;
}

function updateTime2() {
    document.getElementById("timer2").innerHTML = seconds2;
    document.getElementById("timer4").innerHTML = seconds2;
}

function onAll(element){
    if(isBlink==1){
        offBlink();
    }
    startTimer1();
    startTimer2();
    resetPosition(element);
}

function resetPosition(element){
    var xhr = new XMLHttpRequest();
    xhr.open("GET", "/"+element.id, true);
    console.log(element.id);
    xhr.send();
}