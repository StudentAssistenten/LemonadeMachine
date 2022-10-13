console.log("test");

function setValues() {
  setValue("scaleValue");
  setValue("machineState");
  setTimeout("setValues();", 1000);
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
  var req = new XMLHttpRequest();
  let url = "/api/makeLemonade?lemonade=".concat(type);
  req.open("GET", url, false);
  req.send(null);
  if (req.status == 200) console.log(req.responseText);
}

window.onload = function () {
  setValues();
};
