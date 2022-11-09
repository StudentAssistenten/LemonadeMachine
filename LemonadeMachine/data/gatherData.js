console.log("test");

function setValues() {
  console.log("Getting values");
  // setValue("machineState");
  console.log("Setting values");
}

function feedback() // Todo: make better function
{
  alert("Uw limonade wordt gemaakt!");
}

function setValue(valueName) {
  let data = document.getElementById(valueName);
  var req = new XMLHttpRequest();
  let url = "/api/".concat(valueName);
  req.open("GET", url, false);
  req.send(null);
  if (req.status == 200) data.textContent = req.responseText;
}

function makeLemonadeRequest(type)
{
  var sweetness;
  if(type == 3) {
    type  = Math.floor(randomNumber(0, 3));
    sweetness = Math.floor((Math.random() * 10) + 1) / 10;
  } else {
    sweetness = document.getElementById("lemonadeSweetness".concat(type)).value;
  }
  console.log("Making lemonade request type: " + type + " sweetness: " + sweetness);
  var req = new XMLHttpRequest();
  let url = "/api/makeLemonade?lemonade=".concat(type).concat("&sweetness=").concat(sweetness);
  req.open("GET", url, false);
  req.send(null);
  if (req.status == 200) console.log(req.responseText);
  if(req.responseText == "OK")
  {
    feedback();
  }
}

window.onload = function () {
  setValues();
};

function randomNumber(min, max) { 
  return Math.random() * (max - min) + min;
} 
